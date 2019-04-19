#include "KinematicCar.hpp"

KinematicCar::KinematicCar(){
  this->inertialHeading = 0.0;
  this->angleVel        = Angle(0.0f);
  this->acceleration    = 0.0;
  this->steerAngle      = Angle(0.0f);
}

KinematicCar::KinematicCar(cv::Point2f pos, Angle angle, Angle angleVel)
:Car(pos, angle)
{
  this->angleVel = Angle(angleVel);
}


KinematicCar::KinematicCar(cv::Point2f pos, Angle angle, Angle angleVel,
                           float inertialHeading, float acceleration, Angle steerAngle)
  :KinematicCar(pos, angle, angleVel){
  this->inertialHeading = inertialHeading;
  this->acceleration    = acceleration;
  this->steerAngle      = Angle(steerAngle);
}
KinematicCar::KinematicCar(const KinematicCar& car){

}


void KinematicCar::drawCar(Display image, Angle steerAngle){
  float widthT        = width/3;
  float lengthT       = length/6;

  image.drawCarBody(pos, cv::Size2f(width, length), Angle(angle));
  image.drawCarTire(cv::Point2f(pos.x - 0.5 * width + widthT * 0.5,
                                pos.y - 0.5 * length),
                    cv::Size2f(widthT, lengthT), Angle(angle));
  image.drawCarTire(cv::Point2f(pos.x - 0.5 * width + widthT * 0.5,
                                pos.y + 0.5 * length),
                    cv::Size2f(widthT, lengthT), Angle(angle));
  image.drawCarTire(cv::Point2f(pos.x + 0.5 * width - widthT * 0.5,
                                pos.y + 0.5 * length),
                    cv::Size2f(widthT, lengthT), Angle(steerAngle)); 
  image.drawCarTire(cv::Point2f(pos.x + 0.5 * width - widthT * 0.5,
                                pos.y - 0.5 * length),
                    cv::Size2f(widthT, lengthT), Angle(steerAngle));
}

KinematicCar::~KinematicCar(){
}