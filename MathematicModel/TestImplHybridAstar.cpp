#include "TestImplHybridAstar.hpp"

Planner::Planner(){

}

cv::Point2i Planner::getDiscreteCoordinates(cv::Point2f pos){
    return cv::Point2i(pos.x / currNode.boundingBox, pos.y / currNode.boundingBox);
}


double Planner::eucledeanDistance(cv::Point2f from, cv::Point2f to){
    float x = from.x - to.x;
    float y = from.y - to.y;
    return sqrt(x * x + y * y);
}
void Planner::generateLegalStates(const Map& map, std::vector<Node> legalStates){

}
void Planner::planPath(const Map& map, cv::Point2f start, cv::Point2f goal){

}
void Planner::updateNeighbours(const Map& map, std::vector<Node> open, std::vector<Node> closed, Node currNode){

}
double Planner::heuristic(){

}