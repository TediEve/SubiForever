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
/** orientation of the car */
    float angle;

    static constexpr float width  = 40;
    static constexpr float height = 20;
    static constexpr float mass   = 500;
    static constexpr float length = 20;
    static constexpr float vel    = 5;

    Car();
    Car(float posx, float posy, float angle);
    Car(Car& car);
    void drawCar(Display image, float steerAngle);
    ~Car();
};

#endif