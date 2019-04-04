//fix the radians some time
//used https://borrelli.me.berkeley.edu/pdfpub/IV_KinematicMPC_jason.pdf
#include "AckermanModel.hpp"
void AckermanModel::ackSteeringMonocycle(Car& car, const DynamicInput& kinem){
	car.posx  += kinem.velocity * std::cos(car.angle) * dt;
	car.posy  += kinem.velocity * std::sin(car.angle) * dt;
	car.angle += kinem.velocity * std::tan(kinem.steerAngle*pi/180) / car.length * dt;
}

void AckermanModel::ackSteeringBicycle(KinematicCar& car, const DynamicInput& kinem){
    car.posx  += kinem.velocity * std::cos(car.angle + car.angleVel);
    car.posy  += kinem.velocity * std::sin(car.angle + car.angleVel);
    car.angle += kinem.velocity * std::sin(car.angleVel) / car.lateralDist;
    //kinem.velocity += car.acceleration;
    car.angleVel += std::atan(0.5 * std::tan(kinem.steerAngle*pi/180));
}