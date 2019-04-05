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
#include <cmath>

#include "Car.hpp"
#include "AckermanModel.hpp"
#include "DrawUtils.hpp"

using namespace std;
using namespace cv;

double distanceCalculate(Point p1, Point p2)
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
vector<Point> pathPoints;
// Mat display.display(1024, 1024, CV_8UC3, cv::Scalar(122,122,122));
Display display;



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
        
        circle(display.display, Point(x,y), 0,  Scalar(0, 0, 255), 15);

        if(pointsCount == 1) return;
        
        Point prevPoint = pathPoints[pointsCount - 2];
        
        line(display.display, p, prevPoint , Scalar(0,0,255), 10);

    }
}

template<typename T>
void drawPath(T& car, std::string displayName)
{
    display.displayName = displayName;
    double minDist = 10000;
    pathPoints.push_back(Point(car.posx, car.posy));

    namedWindow(displayName);
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
            double distCarGoal = distanceCalculate(Point(car.posx, car.posy), pathPoints[pointGoal]);
            //std::cout<<distCarGoal<< " ";
             
            currInput.steerAngle = - car.angle*180/M_PI + angleToGoal;
            currInput.velocity = 5;
            std::cout<<currInput.steerAngle<< " " << car.angle<<endl;
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

    DynamicInput currInput = {0};
    // AckermanModel useAckerman;

    Car car(50,50,0.0f);
    // drawPath(car, "Kinematic Monocycle Model");
    KinematicCar kincar(50,50,0.0f,0.5f);

    drawPath(kincar, "Kinematic Bicycle Model");

    // int control = 0;
//     while(true)
//     {
// //        circle(m, Point(mx, my), 20, Scalar(0, 0, 255), 2);
// //        line(m, Point(50, 50), Point(mx, my), Scalar(0, 255, 0), 2);
        
        
//         circle(m, Point(car.posx, car.posy), 20, Scalar(0, 0, 255), 2);

//         m *= 0.95f;
//         imshow("cntr", m);
//         char c = waitKey(10);
//         if(c == 27) break;
        
//         // if(c == 'a') {
//         //     currInput.steerAngle += 2;
//         //     useAckerman.ackSteering(car, currInput);
//         //     std::cout<<"left"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;
//         // }
//         // if(c == 's') {
//         //     currInput.velocity = -10;
//         //     useAckerman.ackSteering(car, currInput);
//         //     std::cout<<"down"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;

//         // }

//         // if(c == 'd') {
//         //     currInput.steerAngle -= 2;
//         //     useAckerman.ackSteering(car, currInput);
//         //     std::cout<<"right"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;

//         // }
//         // if(c == 'w') {
//         //     currInput.velocity = 10;
//         //     useAckerman.ackSteering(car, currInput);
//         //     std::cout<<"up"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;

//         // }
//         // if(c== 'x'){
//         //     currInput.velocity = 0;
//         //     useAckerman.ackSteering(car, currInput);
//         //     std::cout<<"stop"<<car.posx<<" "<<car.posy<<" "<<car.angle<<std::endl;
//         // }
        
//     }
//     //  for(int i = 0; i< pathPoints.size();i++ ){
//     //     std::cout<<pathPoints[i].x<<" "<<pathPoints[i].y<<" ";
//     // }
    std::cout<<"ENDDDDDDDDDDDDDDDDDDDDD";
}