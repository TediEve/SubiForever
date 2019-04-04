#ifndef CAR_HPP
#define CAR_HPP 
/**
  * class Car 
  * represents basic kinematic model of a monocycle car
  */

class Car
{
public:
    float posx;
    float posy;
    float angle;

    const float width  = 32;
    const float height = 40;
    const float mass   = 500;
    const float length = 40;
    const float vel    = 5;

    Car();
    Car(float posx, float posy, float angle);
    ~Car();
};

#endif