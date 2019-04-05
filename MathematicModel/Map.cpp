#include "Map.hpp"

Map::Map(Display image, std::vector<bool> where){
  // this -> obstacles.resize(image.displaySize.width * image.displaySize.height);
  this -> obstacles = where;
}



void Map::drawObstacle(Display image){
  int i = 0;
  // for(cv::Point3_<uint8_t> &p : cv::Mat_<cv::Point3_<uint8_t>>(image.display)){
  for( int i = 0; i < image.display.rows ; ++i){
    for(int j = 0; j < image.display.cols; ++j){
      if(obstacles[i*image.display.rows + j] == 1){
        image.display.at<cv::Vec3b>(i,j) = {255,255,255};
      }
    }
  }
}

void Map::makeBorder(Display image){
  for(int i = 0; i < image.display.rows ; ++i){
    for(int j = 0; j < image.display.cols; ++j){
      if((i == image.display.rows - 1) ||
         (j == image.display.cols - 1) ||
         (i == 0) || (j == 0)){
        obstacles[i*image.display.rows + j] = 1;
      }
    }
  }
}

Map::~Map(){

}