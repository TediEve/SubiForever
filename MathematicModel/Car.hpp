#ifndef CAR_HPP
#define CAR_HPP 
class Car
{
public:
    float posx, posy;
    float angle;
    
    float speedx = 0;
    float speedy = 0;

    
    const float width  = 16;
    const float height = 20;
    const float mass   = 500;
    const float length = 20;
    
    const float acceleration = 2.2;
    const float damping = 1;
    
    const float maxTurningRadius = 40;
    
    static const int controlForward = 1;
    static const int controlBackward = 2;
    static const int controlLeft = 4;
    static const int controlRight = 8;
    
    void step(float delta, int control);
    Car(float posx, float posy, float angle);
};

#endif