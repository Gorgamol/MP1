#include <iostream>
#include <cmath>
#include <vector>
#include "AnsiConsole.h"

struct Position{
  int x;
  int y;
  Position(int x_=0, int y_=0){ x=x_;y=y_;}
};

class Shape{
protected:
  Position _position;
  Colors _color;
public:
  Shape(int x, int y, Colors color) : _position(Position(x,y)), _color(color) {}
  virtual void draw() = 0;
  virtual ~Shape();
};

Shape::~Shape() {

}

class Point : public Shape {
public:
  Point(int x=0, int y=0, Colors color = Colors::RED) : Shape(x, y, color) {}
  virtual void draw();
};

void Point::draw(){
  ansiConsole.printText(_position.x,_position.y,"*", _color);
}

class Circle : public Shape {
protected:
  int       _radius;
public:
  Circle(int x=0, int y=0, int radius=0, Colors color = Colors::RED) : Shape(x, y, color), _radius(radius) {}
  virtual void draw();
};

void Circle::draw(){
  /* see https://de.wikibooks.org/wiki/Formelsammlung_Mathematik:_Geometrie
   * Höhensatz des Euklid
   * */
  int x_start = _position.x - _radius/2;
  int x_stop  = _position.x + _radius/2;

  for(int i=x_start; i<=x_stop; i++){
    double x_relative = double(i) - double(x_start);
    double h = sqrt(x_relative*(x_stop-x_start-x_relative));
    ansiConsole.printText(_position.x + int(x_relative)- _radius/2,
                          _position.y +h,"#",
                          _color);
    ansiConsole.printText(_position.x + int(x_relative)- _radius/2,
                          _position.y -h,"#",
                          _color);

  }
}

class Rectangle : public Shape{
protected:
  int       _height;
  int       _width;
public:
  Rectangle(int x=0, int y=0, int height=0, int width=0, Colors color = Colors::RED) : Shape(x, y, color), _height(height), _width(width) {}
  virtual void draw();
};


void Rectangle::draw() {
  for(int i = _position.x; i <= (_position.x + _width); i++) {
    ansiConsole.printText(i, _position.y, "#", _color);
    ansiConsole.printText(i, _position.y + _height, "#", _color);
  }
  for(int i = _position.y; i <= (_position.y + _height); i++) {
    ansiConsole.printText(_position.x , i, "#", _color);
    ansiConsole.printText(_position.x + _width, i, "#", _color);
  }
}

class Scene {
private:
  std::vector<Shape*> _vecShape;
public:
  Scene();
  void addShape(Shape* s);
  void draw();
  ~Scene();
};

Scene::Scene() {

}

void Scene::addShape(Shape* s) {
  _vecShape.push_back(s);
}

void Scene::draw() {
  for(auto s : _vecShape) {
    s->draw();
  }
}

Scene::~Scene() {
  for(auto s : _vecShape) {
      delete s;
  }
  _vecShape.clear();
}

int main(int argc, char **argv)
{


  return 0;
}
