#ifndef CAR_HPP
#define CAR_HPP 
/**
  * class Car 
  * represents basic kinematic model of a monocycle car
  */
#include <opencv2/opencv.hpp>


#include "DrawUtils.hpp"
#include "Utils.hpp"

class Car
{
public:
    cv::Point2f pos = {0, 0};
/** orientation of the car */
    Angle angle;

    static constexpr float width  = 40;
    static constexpr float height = 20;
    static constexpr float mass   = 500;
    static constexpr float length = 20;
    static constexpr float vel    = 5;
    Angle  maxSteer               = Angle(degrees2radians(40));
    Car();
    Car(cv::Point2f pos, Angle angle);
    Car(const Car& car);
    Car(Car&& car);
    Car& operator=(const Car& car);

    void drawCar(Display image, Angle steerAngle);
    ~Car();
};

#endif