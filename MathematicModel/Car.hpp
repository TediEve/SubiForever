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
    cv::Point2f  pos;
/** orientation of the car */
    Angle angle;

    static constexpr float width    = 40;
    static constexpr float height   = 20;
    static constexpr float mass     = 500;
    static constexpr float length   = 20;
    //delete
    static constexpr float vel      = 5;
    static constexpr float maxSteer = 40;

    Car();
    Car(cv::Point2f pos, Angle angle);
    Car(const Car& car);
    void drawCar(Display image, Angle steerAngle);
    ~Car();
};

#endif