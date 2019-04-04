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
	float velocity;
	float steerAngle;
};

struct AckermanModel
{
	double const pi = 3.14159265359;
	double dt = 0.1;
	void ackSteeringMonocycle(Car& car, const DynamicInput& kinem);
	void ackSteeringBicycle(KinematicCar& car, const DynamicInput& kinem);
}; 
#endif