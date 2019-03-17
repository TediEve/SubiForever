#ifndef ACKERMANMODEL_HPP
#define ACKERMANMODEL_HPP

#include <cmath>

#include "Car.hpp"

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
	double dt = 0.1;
	void ackSteering(Car& car, const DynamicInput& kinem);
}; 
#endif