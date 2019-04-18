//fix the radians some time
//used https://borrelli.me.berkeley.edu/pdfpub/IV_KinematicMPC_jason.pdf
#include "AckermanModel.hpp"
void AckermanModel::ackermanSteering(Car& car, const DynamicInput& kinem){
	car.pos.x  += kinem.velocity * std::cos(car.angle.radians) * dt;
	car.pos.y  += kinem.velocity * std::sin(car.angle.radians) * dt;
	car.angle.radians += kinem.velocity * std::tan(kinem.steerAngle.radians) / car.length * dt;
}

void AckermanModel::ackermanSteering(KinematicCar& car, const DynamicInput& kinem){
    car.pos.x  += kinem.velocity * std::cos(car.angle.radians + car.angleVel.radians) * dt;
    car.pos.y  += kinem.velocity * std::sin(car.angle.radians + car.angleVel.radians) * dt;
    car.angle.radians += kinem.velocity * std::sin(car.angleVel.radians) * dt / car.lateralDist;
    //kinem.velocity += car.acceleration;
    car.angleVel.radians = std::atan(0.5 * std::tan(kinem.steerAngle.radians));
}