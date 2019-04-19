//fix the radians some time
//used https://borrelli.me.berkeley.edu/pdfpub/IV_KinematicMPC_jason.pdf
#include "AckermanModel.hpp"
void AckermanModel::ackermanSteering(Car& car, const DynamicInput& kinem){
	car.pos.x  += kinem.velocity * std::cos(car.angle.getRadians()) * dt;
	car.pos.y  += kinem.velocity * std::sin(car.angle.getRadians()) * dt;
	car.angle.setRadians(car.angle.getRadians() + kinem.velocity * std::tan(kinem.steerAngle.getRadians()) / car.length * dt);
}

void AckermanModel::ackermanSteering(KinematicCar& car, const DynamicInput& kinem){
    car.pos.x  += kinem.velocity * std::cos(car.angle.getRadians() + car.angleVel.getRadians()) * dt;
    car.pos.y  += kinem.velocity * std::sin(car.angle.getRadians() + car.angleVel.getRadians()) * dt;
    car.angle.setRadians(car.angle.getRadians() + kinem.velocity * std::sin(car.angleVel.getRadians()) * dt / car.lateralDist);
    //kinem.velocity += car.acceleration*dt;
    car.angleVel.setRadians(std::atan(0.5 * std::tan(kinem.steerAngle.getRadians())));
}