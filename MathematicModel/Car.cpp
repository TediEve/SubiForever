#include "Car.hpp"
Car::Car(){
    this->posx  = 0;
    this->posy  = 0;
    this->angle = 0;
}
Car::Car(float posx, float posy, float angle){
	this->posx = posx;
	this->posy = posy;
	this->angle = angle;
}

Car::Car(Car& car):Car(car.posx, car.posy, car.angle){

}

void Car::drawCar(Display image, float steerAngle){
  float widthT  = width/3;
  float heightT = height/6;
  image.drawCarBody(cv::Point2f(posx,posy), cv::Size2f(width, length), angle, steerAngle);
  image.drawCarTire(cv::Point2f(posx, posy), cv::Size2f(widthT, heightT), steerAngle);
}

Car::~Car(){
    this->posx  = 0;
    this->posy  = 0;
    this->angle = 0;
}
