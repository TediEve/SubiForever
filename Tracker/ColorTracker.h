/* 
 * File:   ColorTracker.h
 * Author: thundy
 *
 * Created on March 17, 2019, 11:23 AM
 */

#ifndef COLORTRACKER_H
#define COLORTRACKER_H

#define USE_SPARSE_PTS

#include <opencv2/opencv.hpp>
using namespace std;

class ColorTracker
{
public:
    static constexpr int ds = 1;
    static constexpr int dsm = pow(2, ds);
    
    static constexpr int Upos = 220;
    static constexpr int Vpos = 70;
    static constexpr int Uvar = 50;
    static constexpr int Vvar = 50;
    
    static constexpr float minFoundPercent = 0.001f;
    
    struct State 
    {
        Point2f pos;
        float angle;
    };
    
    ColorTracker() { }
    
    // State lastState;
    
    static float modAngle(float angle, float minAngle = 0.0f, float maxAngle = M_PI*2.0f)
    {
        while(angle > maxAngle) angle -= M_PI*2.0f;
        while(angle < minAngle) angle += M_PI*2.0f;
        return angle;
    }

    static float closestAngle(float a1, float a2)
    {
        return modAngle(a1 - a2, -M_PI, M_PI);
    }

    bool process(const Mat& mat, State& returnState)
    {
        State lastState = returnState;
        
        rgbSm = mat;
        for(int i = 0; i < ds; ++i)
            pyrDown(rgbSm, rgbSm);
        
        cvtColor(rgbSm, yuvSm, CV_RGB2YUV);
        
        if(carMask.empty())
            carMask = Mat(rgbSm.size(), CV_8UC1, Scalar(0));
        carMask.setTo(0);
        
#ifdef USE_SPARSE_PTS
        vector<Point> pts;
#endif
        float cx = 0.0f, cy = 0.0f;
        int cnum = 0;
        for(int y = 0; y < yuvSm.rows; ++y)
        for(int x = 0; x < yuvSm.cols; ++x)
        {
            const auto& col = yuvSm.at<Vec3b>(y, x);
            if(abs(col[2] - Upos) < Uvar && abs(col[1] - Vpos) < Vvar)
            {
                carMask.at<uint8_t>(y, x) = 255;
                cx += x;
                cy += y;
                ++cnum;
#ifdef USE_SPARSE_PTS
                pts.push_back(Point(x, y));
#endif
            }
        }
        cx /= cnum;
        cy /= cnum;
        
        if(cnum < minFoundPercent * rgbSm.cols * rgbSm.rows)
            return false;
        
        returnState.pos = Point2f(cx, cy)*dsm;
        
        RotatedRect rrect = minAreaRect(pts);
        rrect.angle = rrect.angle/180.0f*M_PI;
        if(rrect.size.width < rrect.size.height)
            rrect.angle += M_PI/2;

//        returnState.angle = rrect.angle;
        returnState.angle = modAngle(rrect.angle);
        // cout<<"CUR: "<<returnState.angle<<" LAST: "<<lastState.angle<<" DIFF: "<<closestAngle(lastState.angle, returnState.angle)<<endl;
        if(abs(closestAngle(lastState.angle, returnState.angle)) > M_PI_2)
        {
            // cout<<"flip angle"<<endl;
            returnState.angle += M_PI;
            returnState.angle = modAngle(returnState.angle);
        }
        
        lastState = returnState;

        return true;
    }
    
    Mat carMask;
    Mat rgbSm;
    Mat yuvSm;
};

#endif /* COLORTRACKER_H */
