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
  virtual void draw() = 0;
  virtual ~Shape();
};

Shape::~Shape() {

}

class Point : public Shape {
public:
  Point(int x=0, int y=0, Colors color = Colors::RED);
  virtual void draw();
};

Point::Point(int x, int y, Colors color){
  _position = Position(x,y);
  _color = color;
}

void Point::draw(){
  ansiConsole.printText(_position.x,_position.y,"*", _color);
}

class Circle : public Shape {
protected:
  int       _radius;
public:
  Circle(int x=0, int y=0, int radius=0, Colors color = Colors::RED);
  virtual void draw();
};

Circle::Circle(int x, int y, int radius, Colors color){
  _position = Position(x,y);
  _color = color;
  _radius=radius;
}

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
  Rectangle(int x=0, int y=0, int height=0, int width=0, Colors color = Colors::RED);
  virtual void draw();
};

Rectangle::Rectangle(int x, int y, int height, int width, Colors color) {
  _position = Position(x,y);
  _height = height;
  _width = width;
  _color = color;
}

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
  // x=0 and y=0 is the upper left corner
  // x and y are more like column and row
  /*ansiConsole.printText(5,5,"Hello, World!");

  Point* p = new Point(10,10);
  p->draw();

  Point* p2 = new Point(2,10);
  p2->draw();


  Circle* c = new Circle(30, 15, 10);
  c->draw();

  Point* p3= new Point(30,15);
  p3->draw();


  delete p;
  delete p2;
  delete p3;
  delete c;*/

  AnsiConsole consol;
  consol.clearScreen();

  Scene test;
  test.addShape(new Circle(10, 8, 10, Colors::BLUE));
  test.addShape(new Circle(10,20, 15, Colors::BLUE));
  test.addShape(new Point(8, 6, Colors::BLACK));
  test.addShape(new Point(12, 6, Colors::BLACK));
  test.addShape(new Point(10, 8, Colors::RED));
  test.addShape(new Point(10, 10, Colors::BLACK));
  test.addShape(new Point(11, 10, Colors::BLACK));
  test.addShape(new Point(12, 9, Colors::BLACK));
  test.addShape(new Point(9, 10, Colors::BLACK));
  test.addShape(new Point(8, 9, Colors::BLACK));
  test.addShape(new Point(10, 16, Colors::BLACK));
  test.addShape(new Point(10, 18, Colors::BLACK));
  test.addShape(new Point(10, 20, Colors::BLACK));
  test.addShape(new Point(10, 22, Colors::BLACK));
  test.addShape(new Rectangle(25, 20, 5, 10, Colors::YELLOW));
  test.addShape(new Point(25, 7, Colors::BLUE));
  test.addShape(new Point(30, 14, Colors::BLUE));
  test.addShape(new Point(22, 11, Colors::BLUE));
  test.addShape(new Point(35, 8, Colors::BLUE));
  test.draw();

  return 0;
}
