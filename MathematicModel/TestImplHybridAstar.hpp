#ifndef TESTIMPLHYBRIDASTAR_HPP
#define TESTIMPLHYBRIDASTAR_HPP

#include "Car.hpp"
#include "Map.hpp"

struct Node
{
  cv::Point2f posDiscrMap;
  Car         carState;
  float       realCost = 0.0;
  float       heuristic = 0.0;
  Node*       parent;
  int         boundingBox = carState.length * 2;
};

class Planner{
private:
  Node currNode;
public:
  Planner();
  cv::Point2i getDiscreteCoordinates(cv::Point2f pos);
  void generateLegalStates(const Map& map, std::vector<Node> legalStates);
  void planPath(const Map& map, cv::Point2f start, cv::Point2f goal);
  void updateNeighbours(const Map& map, std::vector<Node> open, std::vector<Node> closed, Node currNode);
  double heuristic();
  double eucledeanDistance(cv::Point2f from, cv::Point2f to);
};
#endif