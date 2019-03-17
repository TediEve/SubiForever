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
#include<vector>

#include "Car.hpp"
#include "AckermanModel.hpp"

using namespace std;
using namespace cv;

int mx, my;
int mc[2] = {0};
int pointsCount = 0;
vector<Point> pathPoints;
Mat pathMatrix(512, 512, CV_8UC3);

void mcb(int event, int x, int y, int flags, void* userdata)
{
    mx = x;
    my = y;
    if(event == EVENT_LBUTTONDOWN) mc[0] = 1;
    if(event == EVENT_LBUTTONUP) mc[0] = 0;
    if(event == EVENT_RBUTTONDOWN) mc[1] = 1;
    if(event == EVENT_RBUTTONUP) mc[1] = 0;
}

void onPathDrawing(int event, int x, int y, int flags, void* userdata)
{
    Point p = Point(x,y);
    
    if(MouseEventFlags::EVENT_FLAG_LBUTTON == event)
    {
        pointsCount++;
        pathPoints.push_back(p);
      //  pathPoints.size();
        
        circle(pathMatrix, Point(x,y), 0,  Scalar(0, 0, 255), 15);
        
        if(pointsCount == 1) return;
        
        Point prevPoint = pathPoints[pointsCount - 2];
        
        line(pathMatrix, p, prevPoint , Scalar(0,0,255), 10);
    }
}

void drawPath()
{
    namedWindow("pathDrawer");
    cv::setMouseCallback("pathDrawer", onPathDrawing);
    
    
    while(true)
    {    
        imshow("pathDrawer", pathMatrix);
        char c = waitKey(10);
        
        if(c == 27)
        {
            break;
        }
    }
}




int main(int argc, char** argv)
{
  //  drawPath();
    Mat m(512, 512, CV_8UC3);
//    m = imread("index.jpeg");
    
    DynamicInput currInput = {0};
    AckermanModel useAckerman;

    namedWindow("cntr");
    cv::setMouseCallback("cntr", mcb);
    
    Car car(50,50,0.0f);
    car.speedx = 0;
    car.speedy = 0;

    int control = 0;
    while(true)
    {
//        circle(m, Point(mx, my), 20, Scalar(0, 0, 255), 2);
//        line(m, Point(50, 50), Point(mx, my), Scalar(0, 255, 0), 2);
        
        
        circle(m, Point(car.posx, car.posy), 20, Scalar(0, 0, 255), 2);
        
        imwrite("save.jpg", m);
        
        // car.step(0.01f, control);
        
        m *= 0.95f;
        imshow("cntr", m);
        char c = waitKey(10);
        if(c == 27) break;
        
        if(c == 'a') {
            currInput.steerAngle += 2;
            useAckerman.ackSteering(car, currInput);
            std::cout<<"left"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;
        }
        if(c == 's') {
            currInput.velocity = -10;
            useAckerman.ackSteering(car, currInput);
            std::cout<<"down"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;

        }

        if(c == 'd') {
            currInput.steerAngle -= 2;
            useAckerman.ackSteering(car, currInput);
            std::cout<<"right"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;

        }
        if(c == 'w') {
            currInput.velocity = 10;
            useAckerman.ackSteering(car, currInput);
            std::cout<<"up"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;

        }
        if(c== 'x'){
            currInput.velocity = 0;
            useAckerman.ackSteering(car, currInput);
            std::cout<<"stop"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;
        }
        
    }
}