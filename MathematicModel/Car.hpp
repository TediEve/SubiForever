#ifndef CAR_HPP
#define CAR_HPP 
/**
  * class Car 
  * represents basic kinematic model of a monocycle car
  */
#include <opencv2/opencv.hpp>


#include "DrawUtils.hpp"

class Car
{
public:
    float posx;
    float posy;
    float angle;

    const float width  = 40;
    const float height = 20;
    const float mass   = 500;
    const float length = 20;
    const float vel    = 5;

    Car();
    Car(float posx, float posy, float angle);
    void drawCar(Display image, float steerAngle);
    ~Car();
};

#endif