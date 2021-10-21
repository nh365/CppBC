// Based on previous assingment borrowed from someone.

#include "D13_assignment1.h"


template <typename T1, typename T2>
bool CompareShapes(T1 &_a, T2 &_b){

    if (*_a > *_b){
         _a->Shape::print(); 
         std::cout << " is greater than ";
         _b->Shape::print();
         std::cout << std::endl;
    } 
    if (*_a == *_b)
    {
        _a->Shape::print(); 
        std::cout << " is equal to ";
        _b->Shape::print();
        std::cout << std::endl;

    }
    if (*_a < *_b)
    {
         _a->Shape::print(); 
         std::cout << " is less than ";
         _b->Shape::print();
         std::cout << std::endl;
    }    
    return true;
}


int main(){


    Shape *circ1 = new Circle(5);
    Shape *circ2 =  new Circle(100);

    Shape *triang1 = new Triangle(2,23);
    Shape *triang2 = new Triangle(3,5);

    Shape *rectangle1 = new Rectangle(23,1);
    Shape *rectangle2 = new Rectangle(2,1);

    Shape *shapes [6] ={circ1,circ2,triang1,triang2,rectangle1,rectangle2};

    CompareShapes(shapes[2],shapes[4]);
    
    for(size_t i=0;i<6;i++)
        delete shapes[i];

    return 0;
} 