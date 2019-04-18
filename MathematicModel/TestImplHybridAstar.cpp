#include "TestImplHybridAstar.hpp"

std::ostream& operator<<(std::ostream& os, const Node& node){
  os<<node.carState.pos.x<<" : "<<node.carState.pos.y<<"\n";
  return os;
}

Planner::Planner(){
  this->currNode.carState    = Car();
  this->currNode.realCost    = 0.0;
  this->currNode.heuristic   = 0.0;
  this->currNode.parent      = &this->currNode;
  this->currNode.posDiscrMap = getDiscreteCoordinates(currNode.carState.pos);
  this->boundingBox          = currNode.carState.length * 2;
}

Planner::Planner(Car carState, float realCost, float heuristic, Node* parent){
  this->currNode.carState    = Car(carState);
  this->currNode.realCost    = realCost;
  this->currNode.heuristic   = heuristic;
  this->currNode.parent      = parent;
  this->currNode.posDiscrMap = getDiscreteCoordinates(currNode.carState.pos);
  this->boundingBox          = carState.length * 2;
}

cv::Point2i Planner::getDiscreteCoordinates(cv::Point2f pos){
  return cv::Point2i(pos.x / boundingBox, pos.y / boundingBox);
}


double Planner::eucledeanDistance(cv::Point2f from, cv::Point2f to){
  float x = from.x - to.x;
  float y = from.y - to.y;
  return sqrt(x * x + y * y);
}

void Planner::generateLegalStates(Display display, const Map& map, Node node, std::vector<Node>& legalStates){
  DynamicInput dynInput;
  AckermanModel ackermanOn;
  Car tmpCar = node.carState;
  while(dynInput.steerAngle.degrees < tmpCar.maxSteer){
    ackermanOn.ackermanSteering(tmpCar, dynInput);
    dynInput.steerAngle = Angle(dynInput.steerAngle.radians + 10);
    //check for obstacles
    if(!checkForColision(display, map, tmpCar)){
      legalStates.push_back(tmpCar);
    }

  }

}

void Planner::planPath(const Map& map, cv::Point2f start, cv::Point2f goal){

}

void Planner::updateNeighbours(const Map& map, std::vector<Node> open, std::vector<Node> closed, Node currNode){

}

double Planner::heuristic(){

}

bool Planner::ckeckForColision(Display image, const Map& map, const Car& car){
  cv::Mat carMat;

  auto carBound = cv::RotatedRect(car.pos, cv::Size2f(car.width + 10, car.length),
                                  car.angle.degrees);

  if(car.pos.x < 0 || car.pos.y < 0 || car.pos.x > image.display.rows ||
     car.pos.y > image.display.cols){
    return true;
  }

  cv::getRectSubPix(image.display, carBound.size, car.pos, carMat);

  for( int i = 0; i < carMat.rows ; ++i){
    for(int j = 0; j < carMat.cols; ++j){
      // std::cout<<"{ "<<pixelPtr[i*carMat.cols*cn + j*cn + 0]<<
      // ", "<<pixelPtr[i*carMat.cols*cn + j*cn + 1]<<", "<<
      // pixelPtr[i*carMat.cols*cn + j*cn + 2]<<" }\n";
      if(static_cast<int>(image.display.at<cv::Vec3b>(i,j)[0]) == 255 &&
         static_cast<int>(image.display.at<cv::Vec3b>(i,j)[1]) == 255 && 
         static_cast<int>(image.display.at<cv::Vec3b>(i,j)[2]) == 255){
        return true;
      }
    }
  }
  return false;
}