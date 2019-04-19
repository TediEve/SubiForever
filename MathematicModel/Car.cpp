#include "Car.hpp"
Car::Car(){
    this->pos   = {0.0, 0.0};
    this->angle = Angle(0.0f);
}
Car::Car(cv::Point2f pos, Angle angle){
	this->pos   = pos;
	this->angle = Angle(angle);
}

Car::Car(const Car& car):Car(car.pos, car.angle){

}

void Car::drawCar(Display image, Angle steerAngle){
  float widthT  = width/3;
  float heightT = height/6;

  image.drawCarBody(pos, cv::Size2f(width, length), Angle(angle));
  image.drawCarTire(pos, cv::Size2f(widthT, heightT), Angle(steerAngle));
}

Car::~Car(){

}
