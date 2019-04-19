#include "Car.hpp"
Car::Car(){
    this->pos  = {0, 0};
    this->angle = 0;
}
Car::Car(cv::Point2f pos, float angle){
	this->pos   = pos;
	this->angle = angle;
}

Car::Car(Car& car):Car(car.pos, car.angle){

}

void Car::drawCar(Display image, float steerAngle){
  float widthT  = width/3;
  float heightT = height/6;
  image.drawCarBody(pos, cv::Size2f(width, length), angle, steerAngle);
  image.drawCarTire(pos, cv::Size2f(widthT, heightT), steerAngle);
}

Car::~Car(){

}
