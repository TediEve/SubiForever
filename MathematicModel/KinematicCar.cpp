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
extern void drawTire(cv::Mat image, cv::Point2f center, cv::Size2f scale, float angle);

void KinematicCar::drawCar(cv::Mat image, float steerAngle, bool del){
  float widthT  = width/3;
  float heightT = height/6;
  cv::Scalar carColor[2] = {cv::Scalar(255, 0, 0), cv::Scalar(255, 255, 255)};
  if(del)
  { 
    carColor[0] = cv::Scalar(122, 122, 122);
    carColor[1] = cv::Scalar(122, 122, 122);
  }

  cv::Point2f vertices2f[4];
  cv::Point vertices[4];
//delete make new function drawBody
  cv::RotatedRect(cv::Point2f(posx, posy), cv::Size2f(width + 10, height), angle).points(vertices2f);

  for(int i = 0; i < 4; ++i)
  {
    vertices[i] = vertices2f[i];
  }
  cv::fillConvexPoly(image, vertices, 4, carColor[0]);
  cv::putText(image, "SUBI", cv::Point2f(posx - 0.4 * width, posy + 0.3 * height), 1, 1, carColor[1],3);
  drawTire(image, cv::Point2f(posx - 0.5 * width + widthT * 0.5,posy - 0.5 * height), cv::Size2f(widthT, heightT), 0);
  drawTire(image, cv::Point2f(posx - 0.5 * width + widthT * 0.5,posy + 0.5 * height), cv::Size2f(widthT, heightT), 0);
  drawTire(image, cv::Point2f(posx + 0.5 * width - widthT * 0.5,posy + 0.5 * height), cv::Size2f(widthT, heightT), steerAngle); 
  drawTire(image, cv::Point2f(posx + 0.5 * width - widthT * 0.5,posy - 0.5 * height), cv::Size2f(widthT, heightT), steerAngle);
}

KinematicCar::~KinematicCar(){

}