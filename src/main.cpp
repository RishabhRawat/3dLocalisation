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
	    if (!strcmp(hFile->d_name, "."))
		continue;
	    if (!strcmp(hFile->d_name, ".."))
		continue;

	    // in linux hidden files all start with '.'
	    if (hFile->d_name[0] == '.')
		continue;

	    // dirFile.name is the name of the file. Do whatever string comparison
	    // you want here. Something like:
	    // printf( "found an .txt file: %s", hFile->d_name );
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
	
    Mat img_object_1 = imread(string(argv[1])+FileList[0], CV_LOAD_IMAGE_GRAYSCALE);
    detector->detect(img_object_1, keypoints_object_1);
    extractor->compute(img_object_1, keypoints_object_1, descriptors_object_1);
	namedWindow( "MyImage", WINDOW_AUTOSIZE );

    for (unsigned int i = 1; i < FileList.size(); i++) {
		cout<<i<<endl;
		Mat img_object_2 = imread(string(argv[1])+FileList[i], CV_LOAD_IMAGE_GRAYSCALE);
		imshow("MyImage",img_object_2);
		waitKey(25);
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
		//-- Localize the object
		std::vector<Point2f> object_1, object_2;

		for (unsigned int i = 0; i < good_matches.size(); i++) {
			//-- Get the keypoints from the good matches
			object_1.push_back(keypoints_object_1[good_matches[i].queryIdx].pt);
			object_2.push_back(keypoints_object_2[good_matches[i].trainIdx].pt);
		}
		
		Mat H = findHomography(object_1, object_2, CV_RANSAC);
		if(H.data == NULL)
		{
				cout<<"Could'nt Find Homography";
				continue;
		}
				

		// OutputArrayOfArrays rot, trans, scale;
		std::vector<Mat> rot, trans, scale;
		decomposeHomographyMat(H, IntCamMat, rot, trans, scale);
		
		x = x+trans[0];
		cout<<x;
		
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