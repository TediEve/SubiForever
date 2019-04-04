#include "KinematicCar.hpp"

KinematicCar::KinematicCar(){
  this->inertialHeading = 0.0;
  this->angleVel        = 0.0;
  this->acceleration    = 0.0;
  this->steerAngle      = 0.0;
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

KinematicCar::~KinematicCar(){

}