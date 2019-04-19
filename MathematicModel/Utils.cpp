#include "Utils.hpp"

float Angle::getDegrees() const{
  return radians2degrees(radians);
}

float Angle::getRadians() const{
  return radians;
}

void Angle::setRadians(const float radians){
  this->radians = radians;
  this->degrees = radians2degrees(radians);
}

Angle::Angle(){
  this->radians = 0.0f;
  this->degrees = 0.0f;
}

Angle::Angle(float radians){
  this->radians = radians;
  this->degrees = radians2degrees(radians);
}

Angle::Angle(const Angle& angle):Angle(angle.radians){

}

