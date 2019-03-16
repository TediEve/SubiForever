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

using namespace std;
using namespace cv;

//class AccBG
//{
//public:
//    Mat acc;
//    Mat mot;
//    
//    void proc(const Mat& frm)
//    {
//        if(acc.empty()) {
//            acc = frm.clone();
//            mot = Mat(frm.size(), CV_8UC1, Scalar(0));
//        }
//        
//        addWeighted(acc, 0.8f, frm, 0.2f, 0.0f, acc);
//        
//    }
//};

int main(int argc, char** argv) {
    cv::VideoCapture cap;
//     cap.open("./VID_20190315_222839.mp4");
    cap.open("./b4.h264");
    
//    Mat chess = imread("chess.jpeg");
//    cap>>chess;
//    pyrDown(chess, chess);
//    ChartCalib calib;
//    calib.calib(chess);
//    
//    cout<<calib.homo<<endl;
//    cv::perspectiveTransform(chess, chess, calib.homo);
//    imshow("chess", chess);
//    waitKey(0);
//    
//    return 0;
    
//    AccBG background;
    
    FeatureFinder ffModel;
    FeatureFinder ffCurrent;
    
    {
        Mat tmp;
        for(int i = 0; i < 100; ++i)
            cap>>tmp;
    }

    constexpr int ds = 2;
    constexpr int dsm = pow(2, ds);
    Mat rgb, rgbSm, yuvSm, carMask;
    while(true)
    {
        
        cap >> rgb;
        if(rgb.empty()) break;
        else pyrDown(rgb, rgb);
        for(int i = 0; i < ds; ++i)
            if(i == 0 ) pyrDown(rgb, rgbSm);
            else pyrDown(rgbSm, rgbSm);
        
        // background.proc(frm);
        
        cvtColor(rgbSm, yuvSm, CV_RGB2YUV);
        
        if(carMask.empty())
            carMask = Mat(rgbSm.size(), CV_8UC1, Scalar(0));
        carMask = 0;
        
//        vector<Point> pts;
        float cx = 0.0f, cy = 0.0f;
        int cnum = 0;
        for(int y = 0; y < yuvSm.rows; ++y)
        for(int x = 0; x < yuvSm.cols; ++x)
        {
            const auto& col = yuvSm.at<Vec3b>(y, x);
            if(abs(col[2] - 220) < 50 && abs(col[1] - 70) < 50)
//            if(abs(col[2] - 220) < 30 && abs(col[1] - 70) < 30)
            {
                carMask.at<uint8_t>(y, x) = 255;
                cx += x;
                cy += y;
                ++cnum;
                // pts.push_back(Point(cx, cy));
            }
            //else if(abs(col[0] - 40) < 50 && abs(col[2] - 127) < 10 && abs(col[1] - 127) < 40)
            //{}
//            else
//            {
//                col = Vec3b(0, 0, 0);
//            }
        }
        cx /= cnum;
        cy /= cnum;
//        imshow("yuv2", yuv);
        
        if(cnum < 50) {
            imshow("mask", carMask);
            imshow("rgb", rgb);
            waitKey(10);
            continue;
        }
        
//        Mat linereg; // vx vy x0 y0
//        fitLine(pts, linereg, CV_DIST_L2, 0, 1, 0.01);
        
//        Moments mnts = moments(mask, true);
        
        circle(carMask, Point(cx, cy), 5, Scalar(127), 2, CV_AA);
//        float vx = linereg.at<float>(0);
//        float vy = linereg.at<float>(1);
//        float x0 = linereg.at<float>(2);
//        float y0 = linereg.at<float>(3);
//        line(mask, Point(cx, cy), Point(cx + vx*200, cy + vy*200), Scalar(127), 1, CV_AA);
        
        Rect modelCropRect;
        {
            int rad = 240;
            int minx = max(0, (int)cx*dsm - rad/2);
            int miny = max(0, (int)cy*dsm - rad/2);
            int maxx = min(rgb.cols - 1, (int)cx*dsm + rad/2);
            int maxy = min(rgb.rows - 1, (int)cy*dsm + rad/2);
            modelCropRect = Rect(minx, miny, maxx - minx, maxy - miny);
        }
        Mat modelCrop(rgb(modelCropRect));
        
        static vector<Point2f> carIn;
        static Point2f carF, carB;
        static int uid = 0;
        if(uid++ == 0) {
            if(false)
            {
                ffModel.detect(modelCrop);
                ffModel.toFile("carModel.orb");
            }
            else
            {
                ffModel.fromFile("carModel.orb");
                cout<<ffModel.descriptors.cols<<" "<<ffModel.descriptors.rows<<endl;
            }
            
            carF = Point2f(cx + 20, cy + 90);
            carB = Point2f(cx + 120, cy + 90);
            carIn.push_back(carF);
            carIn.push_back(carB);
            circle(modelCrop, carIn[0], 5, Scalar(0, 0, 255), 2, CV_AA);
            circle(modelCrop, carIn[1], 5, Scalar(0, 0, 255), 2, CV_AA);
            line(modelCrop, carIn[0], carIn[1], Scalar(0, 0, 255), 2, CV_AA);
        }
        imshow("mc", modelCrop);
        
        ffCurrent.detect(modelCrop);
        
        ffCurrent.match(ffModel);
        Mat draw = rgb(modelCropRect);
//        ffCurrent.showMatches(draw);
        
        Mat H = findHomography(ffModel.matched, ffCurrent.matched, CV_RANSAC);
        // Mat F = findFundamentalMat(ffModel.matched, ffCurrent.matched, CV_RANSAC);
        vector<Point2f> carOut;
        
        if(!H.empty())
        {
            perspectiveTransform(carIn, carOut, H);
            circle(draw, carOut[0], 5, Scalar(0, 0, 255), 2, CV_AA);
            circle(draw, carOut[1], 5, Scalar(0, 0, 255), 2, CV_AA);
            line(modelCrop, carOut[0], carOut[1], Scalar(0, 0, 255), 2, CV_AA);
        }
        
        // imshow("background", background.acc);
        imshow("mask", carMask);
        imshow("rgb", rgb);
        imshow("rgbSm", rgbSm);
        char c = waitKey(0);
        if(c == 27) break;
    }

    return 0;
}
