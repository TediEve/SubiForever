#include "Car.hpp"
Car::Car(){
    this->pos  = {0, 0};
    this->angle = 0;
}
Car::Car(cv::Point2f pos, Angle angle){
	this->pos   = pos;
	this->angle = angle;
}

Car::Car(const Car& car):Car(car.pos, car.angle){

}

Car::Car(Car&& car):pos(std::move(pos)),angle(std::move(angle)){

}

Car& Car::operator=(const Car& car) = default;

void Car::drawCar(Display image, Angle steerAngle){
  float widthT  = width/3;
  float heightT = height/6;
  image.drawCarBody(pos, cv::Size2f(width, length), angle);
  image.drawCarTire(pos, cv::Size2f(widthT, heightT), steerAngle);
}

Car::~Car(){

}
