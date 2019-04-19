#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

class Angle
{
private:
  float radians = 0.0;
  float getDegrees() const;
  Angle();
  Angle(float radians);
  Angle(const Angle& angle);
};


static constexpr float radians2degrees(float rad){
  return rad * 180 / M_PI;
}

static constexpr float degrees2radians(float deg){
  return deg * M_PI / 180;
}

#endif