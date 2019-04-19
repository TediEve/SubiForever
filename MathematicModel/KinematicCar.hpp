#ifndef KINEMATICCAR_HPP
#define KINEMATICCAR_HPP

#include "Car.hpp"

class KinematicCar: public Car
{
public:
    //the angle of theviation according to the horizontal axis
    float inertialHeading = 0.0;//may be the car angle orirentation ???
    // in perfect conditions that is the distance between the front and 
    // back tires and the center of gravity
    float lateralDist     = length/2;
    // the velocity vector according to the C.G. and Ox
    Angle angleVel        = 0.0;
    // accelaration vector of C.G. - should be constant
    float acceleration    = 0.0;
    // the steer angle of the front tires in ackerman
    Angle steerAngle      = 0.0;
    KinematicCar();
    KinematicCar(cv::Point2f, Angle angle, Angle angleVel);
    KinematicCar(cv::Point2f, Angle angle, float inertialHeading,
                 Angle angleVel, float acceleration, Angle steerAngle);

    KinematicCar(const KinematicCar& car);
    void drawCar(Display image, Angle steerAngle);
    ~KinematicCar();
};

#endif