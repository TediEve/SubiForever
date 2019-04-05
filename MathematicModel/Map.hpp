#ifndef MAP_HPP
#define MAP_HPP

#include "DrawUtils.hpp"

class Map
{
public:
    std::vector<bool> obstacles;
    Map(Display image, std::vector<bool> where);
    void drawObstacle(Display image);
    void makeBorder(Display image);
    ~Map();
    
};

// struct Obstacle
// {
//     cv::Size2f obstacleSize(0,0);
//     cv::Point2f obstaclePos(0,0);
//     void drawObstacle();
// };
#endif