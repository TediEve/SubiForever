#include "TestImplHybridAstar.hpp"

Planner::Planner(Car carState, float realCost, float heuristic){
  this->currNode.carState    = Car(carState);
  this->currNode.realCost    = realCost;
  this->currNode.heuristic   = heuristic;
  this->currNode.parent      = &this->currNode;
  this->currNode.posDiscrMap = getDiscreteCoordinates(cv::Point2f(currNode.carState.posx, currNode.carState.posy));
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

void Planner::generateLegalStates(const Map& map, Node currNode, std::vector<Node>& legalStates){
  
}

void Planner::planPath(const Map& map, cv::Point2f start, cv::Point2f goal){

}

void Planner::updateNeighbours(const Map& map, std::vector<Node> open, std::vector<Node> closed, Node currNode){

}

double Planner::heuristic(){

}
