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

Car::~Car(){
    this->posx  = 0;
    this->posy  = 0;
    this->angle = 0;
}
