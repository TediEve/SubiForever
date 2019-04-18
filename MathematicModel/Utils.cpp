#include "Utils.hpp"

Angle::Angle(){
  this->radians = 0.0;
  this->degrees = 0.0;
}

Angle::Angle(float radians){
  this->radians = radians;
  this->degrees = radians * 180 / M_PI;
}

Angle::Angle(const Angle& angle):Angle(angle.radians){

}