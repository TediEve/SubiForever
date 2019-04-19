//fix the radians some time
//used https://borrelli.me.berkeley.edu/pdfpub/IV_KinematicMPC_jason.pdf
#include "AckermanModel.hpp"
void AckermanModel::ackermanSteering(Car& car, const DynamicInput& kinem){
	car.pos.x  += kinem.velocity * std::cos(car.angle) * dt;
	car.pos.y  += kinem.velocity * std::sin(car.angle) * dt;
	car.angle += kinem.velocity * std::tan(kinem.steerAngle*pi/180) / car.length * dt;
}

void AckermanModel::ackermanSteering(KinematicCar& car, const DynamicInput& kinem){
    car.pos.x  += kinem.velocity * std::cos(car.angle + car.angleVel) * dt;
    car.pos.y  += kinem.velocity * std::sin(car.angle + car.angleVel) * dt;
    car.angle += kinem.velocity * std::sin(car.angleVel) * dt / car.lateralDist;
    //kinem.velocity += car.acceleration;
    car.angleVel = std::atan(0.5 * std::tan(kinem.steerAngle*pi/180));
}