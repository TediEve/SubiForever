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


//fix the global mouse points vector
//see how to read from the mouse

#include <cstdlib>
#include <vector>

#include "Car.hpp"
#include "AckermanModel.hpp"
#include "DrawUtils.hpp"
#include "Map.hpp"

// using namespace std;
// using namespace cv;

void printMatrInd(std::vector<bool> v, int width){
    for (int i = 0; i < v.size(); ++i)
    {
        /* code */
        if(i % width == 0){
            std::cout<<std::endl;
        }
        std::cout<<i<<" ";

    }
}

double distanceCalculate(cv::Point p1, cv::Point p2)
{
    double x = p1.x - p2.x; //calculating number to square in next step
    double y = p1.y - p2.y;
    double dist;

    dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
    dist = sqrt(dist);                  

    return dist;
}

int mx, my;
int mc[2] = {0};
int pointsCount = 1;
std::vector<cv::Point> pathPoints;
// Mat display.display(1024, 1024, CV_8UC3, cv::Scalar(122,122,122));
Display display;



void mcb(int event, int x, int y, int flags, void* userdata)
{
    mx = x;
    my = y;
    if(event == cv::EVENT_LBUTTONDOWN) mc[0] = 1;
    if(event == cv::EVENT_LBUTTONUP) mc[0] = 0;
    if(event == cv::EVENT_RBUTTONDOWN) mc[1] = 1;
    if(event == cv::EVENT_RBUTTONUP) mc[1] = 0;
}

void onPathDrawing(int event, int x, int y, int flags, void* userdata)
{
    cv::Point p = cv::Point(x,y);
    
    if(cv::MouseEventFlags::EVENT_FLAG_LBUTTON == event)
    {
        pointsCount++;
        pathPoints.push_back(p);
      //  pathPoints.size();
        
        cv::circle(display.display, cv::Point(x,y), 0, cv::Scalar(0, 0, 255), 15);

        if(pointsCount == 1) return;
        
        cv::Point prevPoint = pathPoints[pointsCount - 2];
        
       cv::line(display.display, p, prevPoint , cv::Scalar(0,0,255), 10);

    }
}

template<typename T>
void drawPath(T& car, std::string displayName)
{
    display.displayName = displayName;
    double minDist = 10000;
    pathPoints.push_back(cv::Point(car.posx, car.posy));

    cv::namedWindow(displayName);
    // circle(display.display, Point(car.posx, car.posy), 20, Scalar(0, 0, 255), 2);
    cv::setMouseCallback(displayName, onPathDrawing);
   
    DynamicInput currInput = {0};
    AckermanModel useAckerman;
    // bool del = 0 ;
    int pointGoal = 1;

    while(true)
    {    
            display.show(10);
            if(display.del)
            {
            car.drawCar(display, currInput.steerAngle);
            display.del = false;
            }
            double angleToGoal = atan2((car.posy - pathPoints[pointGoal].y), (car.posx - pathPoints[pointGoal].x))*(180/M_PI);
            double distCarGoal = distanceCalculate(cv::Point(car.posx, car.posy), pathPoints[pointGoal]);
            //std::cout<<distCarGoal<< " ";
             
            currInput.steerAngle = - car.angle*180/M_PI + angleToGoal;
            currInput.velocity = 5;
            std::cout<<currInput.steerAngle<< " " << car.angle<<std::endl;
            useAckerman.ackermanSteering(car, currInput);
            if(distCarGoal < 10 && pathPoints.size() > pointGoal){
                pointGoal++;
                currInput.velocity = 0;
            }
            //std::cout<<car.posx<<" "<<car.posy << " ";
            // circle(display.display, Point(car.posx, car.posy), 20, Scalar(0,0,255),2);

            car.drawCar(display, currInput.steerAngle);
            display.del = true;
            //wind.drawCar(State(car.posx, car.posy, car.angle));
       
        if(display.currChar == 27 )
        {
            break;
        }
    }
}




int main(int argc, char** argv)
{

    // DynamicInput currInput = {0};
    // AckermanModel useAckerman;

    // Car car(50,50,0.0f);
    // // drawPath(car, "Kinematic Monocycle Model");
    // KinematicCar kincar(50,50,0.0f,0.5f);

    // drawPath(kincar, "Kinematic Bicycle Model");
    std::vector<bool> v(display.display.rows * display.display.cols);

    // for (int i = 0; i < v.size(); ++i)
    // {
    //     if (i > 100 && i < 200)
    //     {
    //         v[i] = 1;
    //     }
    //     else{
    //         v[i] = 0;
    //     }
    // }
    display.displayName = "test";
    
    Map map(display, v);
    map.makeBorder(display);
    map.drawObstacle(display);
    display.show(10);
    imwrite("img.png",display.display);
    std::cout << "Bye bye! Come again! :) \n";
    return 0;
}