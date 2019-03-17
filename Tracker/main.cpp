/* 
 * File:   main.cpp
 * Author: thundy
 *
 * Created on March 15, 2019, 12:06 AM
 */

#include <cstdlib>
#include <opencv2/opencv.hpp>

#include <FeatureFinder.h>
#include <ChartCalib.h>
#include <ColorTracker.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    cv::VideoCapture cap;
    
    cap.open("./b4.h264");
//    cap.open("./vid1.h264");
     
    ChartCalib calib;
    ColorTracker ctrack;
    
    vector<Point2f> tracked;
    
    namedWindow("ctrl");
    
//    int uiChessboard = 0;
//    createTrackbar("Find Ground", "ctrl", &uiChessboard, 1);
    
    Mat rgb;
    constexpr int ds = 1;
    while(true)
    {
        cap >> rgb;
        if(rgb.empty()) break;
        else for(int i = 0; i < ds; ++i) pyrDown(rgb, rgb);
        
        ColorTracker::State carState;
        bool isTracked = ctrack.process(rgb, carState);
        
        if(isTracked)
        {
            cout<<"returnState: "<<carState.angle<<endl;
        }
        
        // Draw tracked Car
        {
            int cx = carState.pos.x;
            int cy = carState.pos.y;
            float angle = carState.angle;
            line(rgb, Point(cx - cos(angle)*0, cy - sin(angle)*0), Point(cx + cos(angle)*100, cy + sin(angle)*100), Scalar(255, 255, 0), 2, CV_AA);
            circle(rgb, Point(cx, cy), 5, Scalar(0, 255, 255), 2, CV_AA);
        }
        
        if(!calib.homoshow.empty())
        {
            vector<Point2f> ntv;
            ntv.push_back(carState.pos);
            cv::perspectiveTransform(ntv, ntv, calib.homoshow);
            tracked.push_back(ntv.front());

            {
                Mat uni;
                warpPerspective(rgb, uni, calib.homoshow, rgb.size());
                for(auto& v : tracked)
                    circle(uni, v, 5, Scalar(0, 0, 255));
                imshow("uni", uni);
            }
        }
        
        imshow("rgb", rgb);
        char c = waitKey(10);
        if(c == 27) break;
        if(c == 'c') {
            tracked.clear();
            calib.calib(rgb, Size(rgb.size()), 0.04f);
        }
    }

    return 0;
}
