/* 
 * File:   main.cpp
 * Author: thundy
 *
 * Created on March 15, 2019, 12:06 AM
 */

#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int mainHist(int argc, char** argv) {
    cv::VideoCapture cap;
    cap.open("/home/thundy/work/projects/opencvtest/VID_20190315_222839.mp4");
    
    Mat yuvscale = imread("yuvscale.png");
    resize(yuvscale, yuvscale, Size(256, 256));
    
    Mat frm;
    while(true)
    {
        cap >> frm;
        if(frm.empty()) break;
        for(int i = 0; i < 1; ++i)
            pyrDown(frm, frm);
        
        Mat yuv;
        cvtColor(frm, yuv, CV_RGB2YUV);
        
        for(int y = 0; y < yuv.rows; ++y)
        for(int x = 0; x < yuv.cols; ++x)
        {
            auto& col = yuv.at<Vec3b>(y, x);
            if(abs(col[2] - 220) < 30 && abs(col[1] - 70) < 30)
            {
                
            }
            else if(abs(col[0] - 40) < 50 && abs(col[2] - 127) < 40 && abs(col[1] - 127) < 40)
            {}
            else
                col = Vec3b(0, 0, 0);
//            Point(220, 70), 30
        }
        imshow("yuv2", yuv);
        
//        Mat crop = yuv(Rect(390, 220, 180, 80));
        Mat crop = yuv(Rect(470, 220, 60, 80));
        imshow("frm", crop);
        
        vector<float> hist(256*256, 0);
        for(int y = 0; y < crop.rows; ++y)
        for(int x = 0; x < crop.cols; ++x)
        {
            auto& col = crop.at<Vec3b>(y, x);
            hist[col[1]*256 + col[2]]++;
        }
        float mmax = *max_element(hist.begin(), hist.end());
        Mat h(256, 256, CV_32F, hist.data());
        h *= 5.0f/mmax;
        
        circle(h, Point(220, 70), 30, Scalar(5));
        imshow("h", h);
        
        imshow("yuv", yuvscale);
        
        waitKey(0);
        
        imshow("frm", frm);
        char c = waitKey(10);
        if(c == 27) break;
    }

    return 0;
}
