// double AckermanModel::integrateTrapezoid(float speadx, float speady, float acceleration){
// 	return dt*(acceleration + acceleration)/2;
// }
#include "AckermanModel.hpp"
void AckermanModel::ackSteering(Car& car, const DynamicInput& kinem){
	car.posx += kinem.velocity * std::cos(car.angle) * dt;
	car.posy += kinem.velocity * std::sin(car.angle) * dt;
	car.angle += kinem.velocity * std::tan(kinem.steerAngle*pi/180) / car.length * dt;
}
