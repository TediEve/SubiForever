#include "Car.hpp"

void Car::step(float delta, int control)
{
    if(control & controlForward) { posy += 1; }
    if(control & controlBackward) { posy -= 1; }
    if(control & controlLeft) { posx -= 1;}
    if(control & controlRight) { posx += 1; }
}

Car::Car(float posx, float posy, float angle){
	this->posx = posx;
	this->posy = posy;
	this->angle = angle;
}