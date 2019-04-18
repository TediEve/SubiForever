#ifndef ACKERMANMODEL_HPP
#define ACKERMANMODEL_HPP

#include <cmath>

#include "Car.hpp"
#include "KinematicCar.hpp"

struct DynamicInput
{
  /* three states
   * -1 backward
   * 0 stop
   * 1 forward
   */
  float velocity = 5;
  //in radians
  Angle steerAngle = Angle(10);
};

struct AckermanModel
{
  double dt = 0.1;
  void ackermanSteering(Car& car, const DynamicInput& kinem);
  void ackermanSteering(KinematicCar& car, const DynamicInput& kinem);
}; 
#endif