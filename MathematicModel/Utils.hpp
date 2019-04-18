#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

class Angle
{
public:
  float degrees = 0.0;
  float radians = 0.0;
  Angle();
  Angle(float radians);
  Angle(const Angle& angle);
};
#endif