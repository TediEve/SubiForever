/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: User
 *
 * Created on 16 March 2019, 13:55
 */

#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int mx, my;
int mc[2] = {0};
void mcb(int event, int x, int y, int flags, void* userdata)
{
    mx = x;
    my = y;
    if(event == EVENT_LBUTTONDOWN) mc[0] = 1;
    if(event == EVENT_LBUTTONUP) mc[1] = 0;
    if(event == EVENT_RBUTTONDOWN) mc[1] = 1;
    if(event == EVENT_RBUTTONUP) mc[1] = 0;
}

class Car
{
public:
    float posx, posy;
    float angle;
    
    float speedx;
    float speedy;
    
    static const float width;
    static const float height;
    
    static const float acceleration;
    static const float damping;
    
    static const float maxTurningRadius;
    
    static const int controlForward = 1;
    static const int controlBackward = 2;
    static const int controlLeft = 4;
    static const int controlRight = 8;
    
    void step(float delta, int control)
    {
        if(control & controlForward) { posy += 1; }
        if(control & controlBackward) { posy -= 1; }
        if(control & controlLeft) { posx -= 1;}
        if(control & controlRight) { posx += 1; }
    }
};

int main(int argc, char** argv)
{
    Mat m(512, 512, CV_8UC3);
//    m = imread("index.jpeg");
    
    namedWindow("cntr");
    cv::setMouseCallback("cntr", mcb);
    
    Car car;
    car.posx = 50;
    car.posy = 50;
    car.speedx = 0;
    car.speedy = 0;
    car.angle = 0.0f;
    int control = 0;
    while(true)
    {
//        circle(m, Point(mx, my), 20, Scalar(0, 0, 255), 2);
//        line(m, Point(50, 50), Point(mx, my), Scalar(0, 255, 0), 2);
        
        
        circle(m, Point(car.posx, car.posy), 20, Scalar(0, 0, 255), 2);
        
        imwrite("save.jpg", m);
        
        car.step(0.01f, control);
        
        m *= 0.95f;
        imshow("cntr", m);
        char c = waitKey(10);
        if(c == 27) break;
        
        if(c == 'a') control ^= Car::controlLeft;
        if(c == 's') control ^= Car::controlBackward;
        if(c == 'd') control ^= Car::controlRight;
        if(c == 'w') control ^= Car::controlForward;
        
        cout<<control<<endl;
    }
    
    
    return 0;
}

