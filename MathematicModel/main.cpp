//fix the global mouse points vector
//see how to read from the mouse

#include <cstdlib>
#include <vector>

#include "Car.hpp"
#include "AckermanModel.hpp"
#include "DrawUtils.hpp"
#include "Map.hpp"
#include "TestImplHybridAstar.hpp"

void printMatrInd(std::vector<bool> v, int width){
  for (unsigned int i = 0; i < v.size(); ++i)
  {
    /* code */
    if(i % width == 0){
      std::cout<<std::endl;
    }
    std::cout<<i<<" ";

  }
}

// template<typename vecT>
// void printV(std::vector<vecT> v){
//   for (std::vector<vecT>::iterator i = v.begin(); i != v.end(); ++i)
//   {
//     std::cout<<*i<<" ";
//   }
//   std::cout<<std::endl;
// }

double distanceCalculate(cv::Point p1, cv::Point p2)
{
  double x = p1.x - p2.x; //calculating number to square in next step
  double y = p1.y - p2.y;
  double dist;

  dist = pow(x, 2) + pow(y, 2);     //calculating Euclidean distance
  dist = sqrt(dist);          

  return dist;
}

int mx, my;
int mc[2] = {0};
int pointsCount = 1;
std::vector<cv::Point> pathPoints;
// Mat display.display(1024, 1024, CV_8UC3, cv::Scalar(122,122,122));
Display display;



void mcb(int event, int x, int y, int flags, void* userdata)
{
  mx = x;
  my = y;
  if(event == cv::EVENT_LBUTTONDOWN) mc[0] = 1;
  if(event == cv::EVENT_LBUTTONUP) mc[0] = 0;
  if(event == cv::EVENT_RBUTTONDOWN) mc[1] = 1;
  if(event == cv::EVENT_RBUTTONUP) mc[1] = 0;
}

void onPathDrawing(int event, int x, int y, int flags, void* userdata)
{
  cv::Point p = cv::Point(x,y);
  
  if(cv::MouseEventFlags::EVENT_FLAG_LBUTTON == event)
  {
    pointsCount++;
    pathPoints.push_back(p);
    //  pathPoints.size();
    
    cv::circle(display.display, cv::Point(x,y), 0, cv::Scalar(0, 0, 255), 15);

    if(pointsCount == 1) return;
    
    cv::Point prevPoint = pathPoints[pointsCount - 2];
    
     cv::line(display.display, p, prevPoint , cv::Scalar(0,0,255), 10);

  }
}

template<typename T>
void drawPath(T& car, std::string displayName)
{
  display.displayName = displayName;
  pathPoints.push_back(car.pos);

  cv::namedWindow(displayName);
  // circle(display.display, Point(car.posx, car.posy), 20, Scalar(0, 0, 255), 2);
  cv::setMouseCallback(displayName, onPathDrawing);
   
  DynamicInput currInput = {0};
  AckermanModel useAckerman;
  // bool del = 0 ;
  unsigned int pointGoal = 1;

  while(true)
  {  
      display.show(10);
      if(display.del)
      {
      car.drawCar(display, currInput.steerAngle);
      display.del = false;
      }
      double angleToGoal = atan2((car.pos.y - pathPoints[pointGoal].y), (car.pos.x - pathPoints[pointGoal].x));
      double distCarGoal = distanceCalculate(car.pos, pathPoints[pointGoal]);
      //std::cout<<distCarGoal<< " ";
       
      currInput.steerAngle = Angle(- car.angle.getRadians() + angleToGoal);
      // currInput.velocity = 5;
      std::cout<<currInput.steerAngle.getDegrees()<< " " << car.angle.getDegrees()<<std::endl;
      useAckerman.ackermanSteering(car, currInput);
      if(distCarGoal < 10 && pathPoints.size() > pointGoal){
        pointGoal++;
        currInput.velocity = 0;
      }
      //std::cout<<car.posx<<" "<<car.posy << " ";
      // circle(display.display, Point(car.posx, car.posy), 20, Scalar(0,0,255),2);

      car.drawCar(display, currInput.steerAngle);
      display.del = true;
      //wind.drawCar(State(car.posx, car.posy, car.angle));
     
    if(display.currChar == 27 )
    {
      break;
    }
  }
}




int main(int argc, char** argv)
{
  Car car(cv::Point2f(50, 50), Angle(0.0f));
  drawPath(car, "Kinematic Monocycle Model");
  // KinematicCar kincar(cv::Point2f(50, 50), Angle(0.0f), Angle(0.5f));
  // Node* par = nullptr;
  // Planner ast(Car(cv::Point2f(10, 10), Angle(0.0f)), 0.0, 0.0, par);
  // drawPath(kincar, "Kinematic Bicycle Model");
  // std::vector<bool> v(display.display.rows * display.display.cols);
  // Map map(display, v);
  // map.makeBorder(display);
  // map.drawObstacle(display);
  // display.show(10);
  // imwrite("img.png",display.display);
  // std::cout<<ast.checkForColision(display, map, Car(cv::Point2f(10, 10), Angle(0.0f)));
  // std::vector<Node> genSt;
  // int cnt = 0;
  // ast.generateLegalStates(display, map, ast.currNode, genSt);
  // for (std::vector<Node>::iterator i = genSt.begin(); i != genSt.end(); ++i)
  // {
  //   std::cout<<cnt++<<" ";
  // }
  // std::cout<<std::endl;
  // for (int i = 0; i < v.size(); ++i)
  // {
  //   if (i > 100 && i < 200)
  //   {
  //     v[i] = 1;
  //   }
  //   else{
  //     v[i] = 0;
  //   }
  // }
  // display.displayName = "test";
  
  // Map map(display, v);
  // map.makeBorder(display);
  // map.drawObstacle(display);
  // display.show(10);
  // imwrite("img.png",display.display);
  std::cout << "\n Bye bye! Come again! :) \n";
  return 0;
}