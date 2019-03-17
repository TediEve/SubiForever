/* 
 * File:   FeatureFinder.h
 * Author: thundy
 *
 * Created on March 16, 2019, 12:09 PM
 */

#ifndef FEATUREFINDER_H
#define FEATUREFINDER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

class FeatureFinder
{
public:
//    typedef uint8_t FDesc_t[32];
//    struct AKP
//    {
//        FDesc_t desc;
//        KeyPoint kp;
//    };
//    std::vector<AKP> akp;
    
    // Ptr<Feature2D> detector;
    Ptr<ORB> orb = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    
    const double ransac_thresh = 2.5f; // RANSAC inlier threshold
    const double nn_match_ratio = 0.8f; // Nearest-neighbour matching ratio
    const int bb_min_inliers = 100; // Minimal number of inliers to draw bounding box
    const int stats_update_period = 10; // On-screen statistics are updated every 10 frames

    Mat descriptors;
    std::vector<KeyPoint> keypoints;
    
    std::vector<KeyPoint> matchedKP;
    std::vector<Point2f> matched;
    
    void clear()
    {
        descriptors = Mat();
        keypoints.clear();
    }
    
    void operator +=(const FeatureFinder& ff)
    {
        Mat newdesc(descriptors.rows + ff.descriptors.rows, descriptors.cols, descriptors.type());
        memcpy(newdesc.data, descriptors.data, descriptors.rows*descriptors.cols);
        memcpy(newdesc.data + descriptors.rows*descriptors.cols, descriptors.data, descriptors.rows*descriptors.cols);
        descriptors = newdesc;
        
        keypoints.insert(keypoints.begin(), ff.keypoints.begin(), ff.keypoints.end());
    }
    
    void toFile(const char* filename)
    {
        std::ofstream file(filename);
        if(!file.is_open())
        {
            std::cerr<<"[Error] Cannot open file: "<<filename<<std::endl;
            return;
        }
        
#define WR(a) file.write((char*)&a, sizeof(a))
        
        WR(descriptors.cols);
        WR(descriptors.rows);
        std::cout<<descriptors.type()<<std::endl;
        
        file.write((char*)descriptors.data, descriptors.cols*descriptors.rows);
        
        int kps = keypoints.size();
        WR(kps);
        for(int i = 0; i < keypoints.size(); ++i)
        {
            WR(keypoints[i].angle);
            WR(keypoints[i].class_id);
            WR(keypoints[i].octave);
            WR(keypoints[i].pt.x);
            WR(keypoints[i].pt.y);
            WR(keypoints[i].response);
            WR(keypoints[i].size);
        }
    }
    
    void fromFile(const char* filename)
    {
        keypoints.clear();
        descriptors = Mat();
        
        std::ifstream file(filename);
        if(!file.is_open())
        {
            std::cerr<<"[Error] Cannot open file: "<<filename<<std::endl;
            return;
        }
        
#undef WR
#define WR(a) file.read((char*)&a, sizeof(a))
        
        int cols, rows;
        WR(cols);
        WR(rows);
        
        descriptors = Mat(rows, cols, CV_8UC1);
        file.read((char*)descriptors.data, descriptors.cols*descriptors.rows);
        
        int kps;
        WR(kps);
        keypoints.resize(kps);
        for(int i = 0; i < keypoints.size(); ++i)
        {
            WR(keypoints[i].angle);
            WR(keypoints[i].class_id);
            WR(keypoints[i].octave);
            WR(keypoints[i].pt.x);
            WR(keypoints[i].pt.y);
            WR(keypoints[i].response);
            WR(keypoints[i].size);
        }
    }
    
    void detect(const Mat& img)
    {
        orb->setEdgeThreshold(10);
        orb->setMaxFeatures(1000);
        orb->detectAndCompute(img, Mat(), keypoints, descriptors);
    }
    
    void match(FeatureFinder& ff)
    {
        matched.clear();
        ff.matched.clear();
        matchedKP.clear();
        ff.matchedKP.clear();
        
        std::vector< std::vector<DMatch> > matches;
        matcher->knnMatch(descriptors, ff.descriptors, matches, 2);
        for(unsigned i = 0; i < matches.size(); i++) {
            if(matches[i][0].distance < nn_match_ratio * matches[i][1].distance) {
                   matchedKP.push_back(   keypoints[matches[i][0].queryIdx]);
                ff.matchedKP.push_back(ff.keypoints[matches[i][0].trainIdx]);
                   matched.push_back(   keypoints[matches[i][0].queryIdx].pt);
                ff.matched.push_back(ff.keypoints[matches[i][0].trainIdx].pt);
            }
        }
    }
    
    void showMatches(Mat& draw)
    {
        cv::drawKeypoints(draw, matchedKP, draw, Scalar(0, 255, 0));
    }
};

#endif /* FEATUREFINDER_H */

