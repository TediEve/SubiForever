#include "DrawUtils.hpp"

void Display::show(int t){
    cv::imshow(displayName, display);
    currChar = cv::waitKey(t);
}

void Display::drawCarBody(cv::Point2f posCar, cv::Size2f sizeCar, Angle angle){
  cv::Scalar carColor[2] = {cv::Scalar(255, 0, 0), cv::Scalar(255, 255, 255)};
  if(del)
  { 
    carColor[0] = cv::Scalar(122, 122, 122);
    carColor[1] = cv::Scalar(122, 122, 122);
  }

  // cv::Scalar carColorSc = carColor;
  cv::Point2f vertices2f[4];

  cv::RotatedRect(cv::Point2f(posCar.x, posCar.y), 
                  cv::Size2f(sizeCar.width + 10, sizeCar.height),
                  angle.getDegrees()).points(vertices2f);

  for(int i = 0; i < 4; ++i)
  {
    cv::line(display, vertices2f[i], vertices2f[(i+1)%4], carColor[0]);
  }
  // cv::putText(display, "S", cv::Point2f(posCar.x - 0.4 * sizeCar.width,
  //                                          posCar.y + 0.3 * sizeCar.height)
  //            , 1, 1, carColor[1],3);
}

void Display::drawCarTire(cv::Point2f center, cv::Size2f scale, Angle angle){
  cv::ellipse(display, cv::RotatedRect(center, scale, angle.getDegrees()), cv::Scalar(0,0,0), -1, 4);
}
