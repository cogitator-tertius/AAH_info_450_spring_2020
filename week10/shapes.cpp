#include <iostream>
using namespace std;
const int PI = 3; // for simplicity, we'll pretend PI is 3
class shape{
  public:
    virtual int get_perimeter_length(){ return -1; }
    virtual int get_area(){             return -1; }
};
class circle : public shape{
  private:
    int circle_radius;
    int circ_circumference;
    int circle_area;

  public:
    circle(int radius){ circle_radius = radius; }
    int get_perimeter_length()
    {
        circ_circumference = 2 * PI * (circle_radius);
        return circ_circumference; 
    }
    int get_area()
    {
        circle_area = PI * circle_radius * circle_radius;
        return circle_area; 
    }
};

class rectangle : public shape{
  private:
    int rectangle_width;
    int rectangle_height;
    int rectangle_perimeter;
    int rectangle_area;

  public:
    rectangle(int height, int width){ rectangle_height = height, rectangle_width = width; }
    int get_perimeter_length()
    {
        rectangle_perimeter = 2 * (rectangle_height + rectangle_width);
        return rectangle_perimeter; 
    }
    int get_area()
    {
        rectangle_area = rectangle_height * rectangle_width;
        return rectangle_area; 
    }
};

class square : public shape{
  private:
    int square_side;
    int square_perimeter;
    int square_area;

  public:
    square(int side) { square_side = side; }
    int get_perimeter_length()
    {
        square_perimeter = 4 * square_side;
        return square_perimeter; 
    }
    int get_area()
    {
        square_area = square_side * square_side;
        return square_area; 
    }
};

int main(){
  shape *s1;
  circle c(3);
  s1 = &c;
  cout << "Perimeter: " << s1->get_perimeter_length() << " : Area " << s1->get_area() << endl;
  square s(3);
  s1 = &s;
  cout << "Perimeter: " << s1->get_perimeter_length() << " : Area " << s1->get_area() << endl;
  rectangle r(4,5);
  s1 = &r;
  cout << "Perimeter: " << s1->get_perimeter_length() << " : Area " << s1->get_area() << endl;
  return 0;
}