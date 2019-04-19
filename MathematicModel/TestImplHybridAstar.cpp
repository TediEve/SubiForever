#include "TestImplHybridAstar.hpp"

Node::Node(){
  this->car         = Car();
  this->cost        = 0.0;
  this->heuristic   = 0.0;
  this->parent      = nullptr;
  this->isVisited   = false;
  this->posDiscrMap = getDiscreteCoordinates(car.pos);
  this->boundingBox = car.length * 2;
}

Node::Node(Node&& node):car(std::move(node.car)),
                        cost(node.cost),
                        heuristic(node.heuristic),
                        parent(std::move(node.parent)),
                        isVisited(node.isVisited),
                        posDiscrMap(std::move(node.posDiscrMap)),
                        boundingBox(node.boundingBox){
}

Node::Node(Car car, float cost, float heuristic, Node* parent, bool isVisited){
  this->car         = car;
  this->cost        = cost;
  this->heuristic   = heuristic;
  this->parent      = parent;
  this->isVisited   = isVisited;
  this->posDiscrMap = getDiscreteCoordinates(car.pos);
  this->boundingBox = car.length * 2;
}

Node& Node::operator=(const Node& node) = default;


cv::Point2i Node::getDiscreteCoordinates(cv::Point2f pos){
  return cv::Point2i(pos.x / boundingBox, pos.y / boundingBox);
}

std::ostream& operator<<(std::ostream& os, const Node& node){
  os<<node.car.pos.x<<" : "<<node.car.pos.y<<"\n";
  return os;
}

Planner::Planner(){
  this->currNode    = Node();
}

Planner::Planner(Car carState, float realCost, float heuristic, Node* parent){
  this->currNode    = Node(carState, realCost, heuristic, parent, false);
}

double Planner::eucledeanDistance(cv::Point2f from, cv::Point2f to){
  float x = from.x - to.x;
  float y = from.y - to.y;
  return sqrt(x * x + y * y);
}

void Planner::generateLegalStates(Display display, const Map& map, Node node, std::vector<Node>& legalStates){
  DynamicInput dynInput;
  AckermanModel ackermanOn;
  Car tmpCar = node.car;
  float cost = 0.0;
  float heuristic = 0.0;
  float steerStep = 10 * M_PI / 180;

  std::cout<<dynInput.steerAngle.radians<<std::endl;
  std::cout<<tmpCar.maxSteer.radians<<std::endl;
  while(dynInput.steerAngle.radians < tmpCar.maxSteer.radians){
    ackermanOn.ackermanSteering(tmpCar, dynInput);
    dynInput.steerAngle = Angle(dynInput.steerAngle.radians+ steerStep);

    if(!checkForColision(display, map, tmpCar)){
      legalStates.push_back(Node(tmpCar, cost, heuristic, &node, false));
      std::cout<<"found legal\n";
    }
    std::cout<<"not legal\n";
  }

}

void Planner::planPath(const Map& map, cv::Point2f start, cv::Point2f goal){

}

void Planner::updateNeighbours(const Map& map, std::vector<Node> open, std::vector<Node> closed, Node currNode){

}

double Planner::heuristic(){
  return 0.0;
}

bool Planner::checkForColision(Display image, const Map& map, const Car& car){
  cv::Mat carMat;

  auto carBound = cv::RotatedRect(car.pos, cv::Size2f(car.width + 10, car.length),
                                  car.angle.getDegrees());

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