#ifndef TESTIMPLHYBRIDASTAR_HPP
#define TESTIMPLHYBRIDASTAR_HPP
#include "AckermanModel.hpp"
#include "Car.hpp"
#include "Map.hpp"

class Node
{
public:
  cv::Point2i posDiscrMap;
  Car         car;
  float       cost = 0.0;
  float       heuristic = 0.0;
  Node*       parent;
  bool        isVisited = false;
  int  boundingBox;
  Node();
  Node(Car car, float cost, float heuristic, Node* parent, bool isVisited);
  cv::Point2i getDiscreteCoordinates(cv::Point2f pos);
  friend std::ostream& operator<<(std::ostream& os, const Node& node);
};

class Planner{
private:

public:
  /** initialize the curr node */
  Node currNode;
  Planner();
  Planner(Car carState, float realCost, float heuristic, Node* parent);
  void generateLegalStates(Display display, const Map& map, Node currNode, std::vector<Node>& legalStates);
  bool checkForColision(Display image, const Map& map, const Car& car);
  void planPath(const Map& map, cv::Point2f start, cv::Point2f goal);
  void updateNeighbours(const Map& map, std::vector<Node> open, std::vector<Node> closed, Node currNode);
  double heuristic();
  double eucledeanDistance(cv::Point2f from, cv::Point2f to);
};
#endif