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

    for (unsigned int i = 1; i < FileList.size(); i++) {
		cout<<i<<endl;
		Mat img_object_2 = imread(string(argv[1])+FileList[i], CV_LOAD_IMAGE_GRAYSCALE);
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
			continue;
		}

		//-- Localize the object
		std::vector<Point2f> object_1, object_2;

		for (unsigned int i = 0; i < good_matches.size(); i++) {
			//-- Get the keypoints from the good matches
			object_1.push_back(keypoints_object_1[good_matches[i].queryIdx].pt);
			object_2.push_back(keypoints_object_2[good_matches[i].trainIdx].pt);
		}
		Mat E, R, t, masks;
		
		E = findEssentialMat(object_1, object_2, 537, Point2f(320.1, 247.6), RANSAC, 0.999, 1.0, masks);
		recoverPose(E, object_1, object_2, R, t, 537, Point2f(320.1, 247.6), masks);
		y = x+t;
		cout<<t<<endl;
		cout<<t.at<double>(0)<<" "<<t.at<double>(2)<<endl;
		cout<<Point2d(t.at<double>(0),t.at<double>(2))<<endl;
		line(plot,Point2d(3*x.at<double>(0,0)+127,3*x.at<double>(0,2)+127),Point2d(3*y.at<double>(0,0)+127,3*y.at<double>(0,2)+127),Scalar(255,255,255));
		imshow("Plot",plot);
		waitKey(13);
		//cout<<t;



//		Mat H = findHomography(object_1, object_2, CV_RANSAC);
//		if(H.data == NULL)
//		{
//				cout<<"Couldn't Find Homography";
//				continue;
//		}
//				
//
//		// OutputArrayOfArrays rot, trans, scale;
//		std::vector<Mat> rot, trans, scale;
//		decomposeHomographyMat(H, IntCamMat, rot, trans, scale);
		
		// TODO correct this and plot
		x = x+t;
		//cout<<x<<endl;
		
		descriptors_object_1 = descriptors_object_2;
		keypoints_object_1 = keypoints_object_2;
    }
    waitKey(0);
    return 0;
}

/** @function readme */
void readme()
{
    std::cout << " Give Path and Path only" << std::endl;
}