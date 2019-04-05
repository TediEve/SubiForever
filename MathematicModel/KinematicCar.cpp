#include "KinematicCar.hpp"

KinematicCar::KinematicCar(){
  this->inertialHeading = 0.0;
  this->angleVel        = 0.0;
  this->acceleration    = 0.0;
  this->steerAngle      = 0.0;
}

KinematicCar::KinematicCar(float posx, float posy, float angle, float angleVel)
:Car(posx, posy, angle)
{
  this->angleVel = angleVel;
}


KinematicCar::KinematicCar(float posx, float posy, float angle, float inertialHeading,
                           float angleVel, float acceleration, float steerAngle)
  :Car(posx, posy,angle){
  this->inertialHeading = inertialHeading;
  this->angleVel        = angleVel;
  this->acceleration    = acceleration;
  this->steerAngle      = steerAngle;
}
KinematicCar::KinematicCar(const KinematicCar& car){

}
//quick fix

void KinematicCar::drawCar(Display image, float steerAngle){
  float widthT  = width/3;
  float lengthT = length/6;

  image.drawCarBody(cv::Point2f(posx,posy), cv::Size2f(width, length), angle, steerAngle);
  image.drawCarTire(cv::Point2f(posx - 0.5 * width + widthT * 0.5,
                                posy - 0.5 * length),
                    cv::Size2f(widthT, lengthT), angle * 180 / M_PI);
  image.drawCarTire(cv::Point2f(posx - 0.5 * width + widthT * 0.5,
                                posy + 0.5 * length),
                    cv::Size2f(widthT, lengthT), angle * 180 / M_PI);
  image.drawCarTire(cv::Point2f(posx + 0.5 * width - widthT * 0.5,
                                posy + 0.5 * length),
                    cv::Size2f(widthT, lengthT), steerAngle); 
  image.drawCarTire(cv::Point2f(posx + 0.5 * width - widthT * 0.5,
                                posy - 0.5 * length),
                    cv::Size2f(widthT, lengthT), steerAngle);
}

KinematicCar::~KinematicCar(){
}