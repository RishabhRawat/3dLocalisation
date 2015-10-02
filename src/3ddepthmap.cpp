#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"

using namespace cv;
using namespace std;
void readme();
void listFiles(const char* path, vector<string>& returnFileName)
{
    DIR* dirFile = opendir(path);
    if (dirFile) {
	struct dirent* hFile;
	while ((hFile = readdir(dirFile)) != NULL) {
	    if (hFile->d_name[0] == '.') // ignore hidden files, current directory, and up directory
		continue;

	    returnFileName.push_back(string(hFile->d_name));
	    sort(returnFileName.begin(), returnFileName.end());
	}
	closedir(dirFile);
    }
}
static void calcandsaveXYX(const char* filename, Mat& Q, Mat& disparity)
{
	cout<<Q<<endl;
	 cv::Mat Q_32F;
	 Q.convertTo(Q_32F,CV_32F);
	
	FILE* fp = fopen(filename, "wt");
    for(int y = 0; y < disparity.rows; y++)
    {
        for(int x = 0; x < disparity.cols; x++)
        {

			 cv::Mat_<float> vec(4,1);

			 vec(0) = x;
			 vec(1) = y;
			 vec(2) = disparity.at<float>(y,x);

			 // Discard points with 0 disparity    
			 if(vec(2)==0) continue;
			 vec(3)=1;              
			 vec = Q_32F*vec;
			 vec /= vec(3);
			 // Discard points that are too far from the camera, and thus are highly
			 // unreliable
			 if(abs(vec(0))>10 || abs(vec(1))>10 || abs(vec(2))>10) continue;

            fprintf(fp, "%f %f %f\n", vec(0), vec(1), vec(2));
        }
    }
    fclose(fp);
}
static void saveXYZ(const char* filename, const Mat& mat)
{
    const double max_z = 1.0e4;
    FILE* fp = fopen(filename, "wt");
    for(int y = 0; y < mat.rows; y++)
    {
        for(int x = 0; x < mat.cols; x++)
        {
            Vec3f point = mat.at<Vec3f>(y, x);
            if(fabs(point[2] - max_z) < FLT_EPSILON || fabs(point[2]) > max_z) continue;
            fprintf(fp, "%f %f %f\n", point[0], point[1], point[2]);
        }
    }
    fclose(fp);
}

/** @function main */
int main(int argc, char** argv)
{
    if (argc != 2) {
	readme();
	return -1;
    }
    vector<string> FileList;
    listFiles(argv[1], FileList);

    int minHessian = 400;
    Ptr<xfeatures2d::SURF> detector = xfeatures2d::SURF::create(minHessian);
    Ptr<xfeatures2d::SURF> extractor = xfeatures2d::SURF::create();

    std::vector<KeyPoint> keypoints_object_1, keypoints_object_2;

    Mat descriptors_object_1, descriptors_object_2;

    FlannBasedMatcher matcher;
    std::vector<DMatch> matches;

    double camdata[3][3] = { { 535.4, 0, 320.1 }, { 0, 539.2, 247.6 }, { 0, 0, 1 } };
    Mat IntCamMat = Mat(3, 3, CV_64F, camdata);
	Mat x = Mat::zeros(3, 1, CV_64F);
	Mat y;
	
    Mat img_object_1 = imread(string(argv[1])+FileList[0], CV_LOAD_IMAGE_GRAYSCALE);
    detector->detect(img_object_1, keypoints_object_1);
    extractor->compute(img_object_1, keypoints_object_1, descriptors_object_1);
	namedWindow( "MyImage", WINDOW_AUTOSIZE );
	namedWindow( "Plot", WINDOW_AUTOSIZE );
	
	Mat plot(640, 480, CV_8UC3, Scalar(0,0,0));

	Mat img_object_2 = imread(string(argv[1])+FileList[1], CV_LOAD_IMAGE_GRAYSCALE);
	imshow("MyImage",img_object_2);
	waitKey(13);
	if (!img_object_1.data || !img_object_2.data) {
		std::cout << " --(!) Error reading images " << std::endl;
		return -1;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	detector->detect(img_object_2, keypoints_object_2);

	//-- Step 2: Calculate descriptors (feature vectors)
	extractor->compute(img_object_2, keypoints_object_2, descriptors_object_2);

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	matcher.match(descriptors_object_1, descriptors_object_2, matches);

	//-- Quick calculation of max and min distances between keypoints

	double max_dist = 0;
	double min_dist = 100;

	for (int i = 0; i < descriptors_object_1.rows; i++) {
		double dist = matches[i].distance;
		if (dist < min_dist)
		min_dist = dist;
		if (dist > max_dist)
		max_dist = dist;
	}

	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector<DMatch> good_matches;

	for (int i = 0; i < descriptors_object_1.rows; i++) {
		if (matches[i].distance < 3 * min_dist) {
		good_matches.push_back(matches[i]);
		}
	}
	if(good_matches.size() < 6)
	{
		cout<<"Not Enough Good Matches";
		exit(1);
	}

	//-- Localize the object
	std::vector<Point2f> object_1, object_2;

	for (unsigned int i = 0; i < good_matches.size(); i++) {
		//-- Get the keypoints from the good matches
		object_1.push_back(keypoints_object_1[good_matches[i].queryIdx].pt);
		object_2.push_back(keypoints_object_2[good_matches[i].trainIdx].pt);
	}
	
	Mat E, R, t, masks;
	Mat distortion = Mat::zeros(1,5,CV_64F);
	
	Mat img_matches;
  /*drawMatches( img_object_1, keypoints_object_1, img_object_2, keypoints_object_2,
               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
	imshow("MyImage",img_object_1);
    waitKey(0);
    imshow("plot",img_object_2);
    waitKey(0);
	imshow("MyImage",img_matches);
    waitKey(0);
	while(1);
	*/
	Mat output;
	
	
	
	
	E = findEssentialMat(object_1, object_2, 537, Point2f(320.1, 247.6), RANSAC, 0.999, 1.0, masks);
	recoverPose(E, object_1, object_2, R, t, 537, Point2f(320.1, 247.6), masks);
	Mat R1,R2,P1,P2,Q;
	Rect roi1, roi2;
	Size imgsize = img_object_1.size();
	stereoRectify( IntCamMat, distortion, IntCamMat, distortion, imgsize, R, t, R1, R2, P1, P2, Q, CALIB_ZERO_DISPARITY, -1, imgsize, &roi1, &roi2 );
	int q = Q.type();
	 Mat map11, map12, map21, map22;
	initUndistortRectifyMap(IntCamMat, distortion, R1, P1, imgsize, CV_16SC2, map11, map12);
	initUndistortRectifyMap(IntCamMat, distortion, R2, P2, imgsize, CV_16SC2, map21, map22);

	Mat img1r, img2r;
	remap(img_object_1, img1r, map11, map12, INTER_LINEAR);
	remap(img_object_2, img2r, map21, map22, INTER_LINEAR);
	imshow("MyImage",img_object_1);
    waitKey(0);
	imshow("MyImage",img1r);
    waitKey(0);
    imshow("MyImage",img_object_2);
    waitKey(0);
	imshow("MyImage",img2r);
    waitKey(0);
	
	img_object_1 = img1r;
	img_object_2 = img2r;
 Mat disp, disp8;

	
	Ptr<StereoSGBM> sgbm = StereoSGBM::create(0,64,5);
	int SADWindowSize = 0;
	sgbm->setPreFilterCap(63);
	int sgbmWinSize = SADWindowSize > 0 ? SADWindowSize : 1;
    sgbm->setBlockSize(sgbmWinSize);

    int cn = img_object_1.channels();
	int numberOfDisparities = 64;
    sgbm->setP1(8*cn*sgbmWinSize*sgbmWinSize);
    sgbm->setP2(32*cn*sgbmWinSize*sgbmWinSize);
    sgbm->setMinDisparity(0);
    sgbm->setNumDisparities(numberOfDisparities);
    sgbm->setUniquenessRatio(10);
    sgbm->setSpeckleWindowSize(100);
    sgbm->setSpeckleRange(2);
    sgbm->setDisp12MaxDiff(1);

	sgbm->setMode(StereoSGBM::MODE_HH);

     int64 t1 = getTickCount();
	sgbm->compute(img_object_1, img_object_2, disp);
	t1 = getTickCount() - t1;
    printf("Time elapsed: %fms\n", t1*1000/getTickFrequency());
	Mat imgDisparity32F;
	disp.convertTo(disp8, CV_8U, 255/(numberOfDisparities*16.));
	//disp.convertTo(imgDisparity32F, CV_32F, 1./16);
	
    
	namedWindow("left", 1);
	imshow("left", img_object_1);
	namedWindow("right", 1);
	imshow("right", img_object_2);
	namedWindow("disparity", 0);
	imshow("disparity", disp8);
	printf("press any key to continue...");
	fflush(stdout);
	waitKey();
	printf("\n");

        printf("storing the point cloud...");
        fflush(stdout);
//		calcandsaveXYX("point_cloud.xyz",Q,disp);
        Mat xyz;
        reprojectImageTo3D(disp, xyz, Q, false, CV_32F );
		saveXYZ("point_cloud.xyz", xyz);
        printf("\n");



    return 0;
}

/** @function readme */
void readme()
{
    std::cout << " Give Path and Path only" << std::endl;
}