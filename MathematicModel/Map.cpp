#include "Map.hpp"

Map::Map(Display image, std::vector<bool> where){
  // this -> obstacles.resize(image.displaySize.width * image.displaySize.height);
  this -> obstacles = where;
}



void Map::drawObstacle(Display image){
  for( int i = 0; i < image.display.rows ; ++i){
    for(int j = 0; j < image.display.cols; ++j){
      if(obstacles[i*image.display.rows + j] == 1){
        image.display.at<cv::Vec3b>(i,j) = {255,255,255};
      }
    }
  }
}

void Map::makeBorder(Display image){
  fillLine<true>( true, 0                     , image.display.rows, image.display.cols);
  fillLine<true>( true, image.display.rows - 1, image.display.rows, image.display.cols);
  fillLine<false>(true, 0                     , image.display.rows, image.display.cols);
  fillLine<false>(true, image.display.cols - 1, image.display.rows, image.display.cols);
}

Map::~Map(){

}