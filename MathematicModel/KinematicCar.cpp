#include "KinematicCar.hpp"

KinematicCar::KinematicCar(){
  this->inertialHeading = 0.0;
  this->angleVel        = 0.0;
  this->acceleration    = 0.0;
  this->steerAngle      = 0.0;
}

KinematicCar::KinematicCar(cv::Point2f pos, Angle angle, Angle angleVel)
:Car(pos, angle)
{
  this->angleVel = angleVel;
}


KinematicCar::KinematicCar(cv::Point2f pos, Angle angle, float inertialHeading,
                           Angle angleVel, float acceleration, Angle steerAngle)
  :KinematicCar(pos, angle, angleVel){
  this->inertialHeading = inertialHeading;
  this->acceleration    = acceleration;
  this->steerAngle      = steerAngle;
}
KinematicCar::KinematicCar(const KinematicCar& car){

}
//quick fix

void KinematicCar::drawCar(Display image, Angle steerAngle){
  float widthT  = width/3;
  float lengthT = length/6;

  image.drawCarBody(cv::Point2f(pos.x ,pos.y), cv::Size2f(width, length), angle);
  image.drawCarTire(cv::Point2f(pos.x - 0.5 * width + widthT * 0.5,
                                pos.y - 0.5 * length),
                    cv::Size2f(widthT, lengthT), angle);
  image.drawCarTire(cv::Point2f(pos.x - 0.5 * width + widthT * 0.5,
                                pos.y + 0.5 * length),
                    cv::Size2f(widthT, lengthT), angle);
  image.drawCarTire(cv::Point2f(pos.x + 0.5 * width - widthT * 0.5,
                                pos.y + 0.5 * length),
                    cv::Size2f(widthT, lengthT), steerAngle); 
  image.drawCarTire(cv::Point2f(pos.x + 0.5 * width - widthT * 0.5,
                                pos.y - 0.5 * length),
                    cv::Size2f(widthT, lengthT), steerAngle);
}

KinematicCar::~KinematicCar(){
}