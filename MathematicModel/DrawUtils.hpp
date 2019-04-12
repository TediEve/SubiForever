#ifndef DRAWUTILS_HPP
#define DRAWUTILS_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>

struct Display
{
    std::string displayName = "Display";
    // cv::Size2f  displaySize = cv::Size2f(13, 12);
    cv::Mat     display     = cv::Mat(512, 512, CV_8UC3, cv::Scalar(122, 122, 122));
    /** current pushed keyboard key */
    int         currChar    = 0;
    /** a flag to tell us if we are drawing or deleting */
    bool        del         = false;
    /** 
      * visualizes the window with the simulation 
      * param t sets the waitKey function
      */
    void show(int t);
    /** 
      * draws or deletes the rectangle which represents the car body
      * param posCar current x,y position of the car
      * param sizeCar the width and length of the car
      * param angle the angle of the velocity vector
      * param steerAngle the angle of current steering
      */
    void drawCarBody(cv::Point2f posCar, cv::Size2f sizeCar, float angle, float steerAngle);
    /**
      * draws an ellipse representing a tire of a car
      * param center the center of the elipse
      * param scale the width and length of the tire
      * param angle the angle of rotation of the tire
      */
    void drawCarTire(cv::Point2f center, cv::Size2f scale, float angle);
    /**
      * draws the obstacles of the map
      * param TODO
      */
    void drawObstacle();
};


#endif