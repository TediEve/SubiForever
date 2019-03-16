/* 
 * File:   ChartCalib.h
 * Author: thundy
 *
 * Created on March 16, 2019, 4:02 PM
 */

#ifndef CHARTCALIB_H
#define CHARTCALIB_H

#include <vector>
#include <opencv2/opencv.hpp>

#include <iostream>
using namespace std;

using namespace cv;

class ChartCalib
{
public:
    const Size boardSize;
    const float chessWidth = 17.7f;
    const float chessHeight = 12.6f;
    
    ChartCalib() : boardSize(8, 6) {}
    
    Mat homo;
    
    void calib(const Mat& _chess)
    {
        Mat chess = _chess;
        if(chess.channels() == 3)
            cvtColor(chess, chess, CV_RGB2GRAY);
        
        // 12.6 x 17.7
        std::vector<Point2f> chesspts;
        bool found = findChessboardCorners( chess, boardSize, chesspts, CALIB_CB_ADAPTIVE_THRESH );
        if(!found) return;
        
        cv::cornerSubPix(chess, chesspts, 
                cv::Size(5,5), cv::Size(-1,-1), 
                cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 
                30, 0.1));
        
        vector<Point2f> cam;
        cam.push_back(chesspts[0]);
        cam.push_back(chesspts[boardSize.width - 1]);
        cam.push_back(chesspts[boardSize.width*(boardSize.height) - 1]);
        cam.push_back(chesspts[boardSize.width*(boardSize.height-1)]);
        
        circle(chess, chesspts[0], 10, Scalar(0), 2, CV_AA);
        circle(chess, chesspts[boardSize.width - 1], 10, Scalar(80), 2, CV_AA);
        circle(chess, chesspts[boardSize.width*(boardSize.height) - 1], 10, Scalar(127), 2, CV_AA);
        circle(chess, chesspts[boardSize.width*(boardSize.height-1)], 10, Scalar(255), 2, CV_AA);
        
        vector<Point2f> uni;
        uni.push_back(Point2f(0.0f, 0.0f));
        uni.push_back(Point2f(chessWidth, 0.0f));
        uni.push_back(Point2f(chessWidth, chessHeight));
        uni.push_back(Point2f(0.0f, chessHeight));
        
        homo = findHomography(cam, uni, CV_RANSAC);
        
//        cv::drawChessboardCorners(chess, boardSize, chesspts, found);
//        imshow("a", chess);
//        waitKey(0);
//        cout<<"hi: "<<chesspts.size()<<endl;
    }
};

#endif /* CHARTCALIB_H */

