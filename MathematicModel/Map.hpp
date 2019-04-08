#ifndef MAP_HPP
#define MAP_HPP

#include "DrawUtils.hpp"

class Map
{
private:
  template<bool isRow> void fillLine(bool val, int ind, int rows, int cols){
    int len = isRow ? rows : cols;
    for(int i = 0; i < len; ++i){
      if(isRow){
        obstacles[ind * rows + i] = val;
      }else{
        obstacles[i * rows + ind] = val;
      }
    }
  }
public:
  std::vector<bool> obstacles;
  Map(Display image, std::vector<bool> where);
  void drawObstacle(Display image);
  void makeBorder(Display image);
  ~Map();
  
};

// struct Obstacle
// {
//   cv::Size2f obstacleSize(0,0);
//   cv::Point2f obstaclePos(0,0);
//   void drawObstacle();
// };
#endif