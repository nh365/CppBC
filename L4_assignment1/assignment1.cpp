#include <iostream>



class Shape{
// Attributes:
protected:
    int width;
    int height;
    int radius;
    int perimeter;

//    int area

// ********************************************************************
// Se dessa från exemplet från lektionen...
// Shape(const int &_p, const int &_a):Perimeter(_p),Area(_a){}
// bool operator <(const Shape &s);
// bool operator >(const Shape &s);
// bool operator ==(const Shape &s);
// bool operator <(const Shape &l, const Shape &s);
// void operator =(const Shape &s);
/* 
bool Shape::operator<(const Shape &s){
    bool return_value = false;
    if( (this->Area) > s.Area) || ((this->Area == s.Area() && this->Perimeter > s.Perimeter ))
}
 */
// ********************************************************************



// Methods:
public:
    Shape(int _width, int _height):width(_width),height(_height){}  // Constructor
    Shape(int _radius):radius(_radius){}                            // Constructor
    virtual int Area() = 0;                                         // Pure virtual function, needs to be added by children.
    void PrintArea(){
        std::cout << "Area: " << this->Area() << std::endl;
    }
    void PrintPerimeter(){
        std::cout << "Area: " << this->perimeter() << std::endl;
    }
};


class Square : public Shape{
public:
    Square(int a, int b) : Shape(a,b) {}
    ~Square() = default;

private: 
    int Area() {return (width * height);}
};

class Triangle : public Shape{
public:
    Triangle(int a, int b) : Shape(a,b) {}
    ~Triangle() = default;
private: 
    int Area() {return ((width * height)/2);}
};


class Circle : public Shape{
public:
    Circle(int a) : Shape(a) {}
    ~Circle() = default;
private: 
    int Area() {return (radius*radius*3);}
};


int main(){

    Shape *shape_list[3] = { new Square (3,3) , new Triangle (4,4), new Circle (2)};

    for (size_t i = 0; i < 3; i++)
    {
        shape_list[i]->PrintArea();
    }
   for (size_t i = 0; i < 3; i++)
    {
        delete shape_list[i];
    }
     
    return 1;
}