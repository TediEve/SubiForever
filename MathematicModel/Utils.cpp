#include "Utils.hpp"

float Angle::getDegrees() const{
  return radians2degrees(radians);
}

Angle::Angle(){
  this->radians = 0.0f;
}

Angle::Angle(float radians){
  this->radians = radians;
}

Angle::Angle(const Angle& angle):Angle(angle.radians){

}