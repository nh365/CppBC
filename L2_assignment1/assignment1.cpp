#include <iostream>
#include <cstdlib>

// Using three dimensional array
bool Version1(size_t &_user_input,size_t &_x,size_t &_y,size_t &_z){


    // Allocate memory of the first dimension
    unsigned int ***Array = new unsigned int **[_x];

    // Allocate memory of the second dimension
    for(size_t i=0; i<_x; i++)
    {
        Array[i] = new unsigned int *[_y];

// Denna är        *(Array+i) = new unsigned int **[_y];
// samma som:        Array[i] = new unsigned int **[_y];  

        for(size_t j=0; j<_y; j++){

            // Allocate memory for the third dimension
            // These are int type
            Array[i][j] = new unsigned int[_z];

            // Enter random numbers into int array
            for(size_t k=0; k<_z; k++){

                Array[i][j][k] = rand() % _user_input;                    
                std::cout << Array[i][j][k] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;        
    }
    std::cout << std::endl;

    return true;

}

// Using four dimensional array, with pointers to _z
bool Version2(size_t &_user_input,size_t &_x,size_t &_y,size_t &_z){


    // Allocate memory of the first dimension
    unsigned int ****Array = new unsigned int ***[_x];

    // Allocate memory of the second dimension
    for(size_t i=0; i<_x; i++)
    {
        Array[i] = new unsigned int **[_y];

        for(size_t j=0; j<_y; j++){

            // Allocate memory for the third dimension
            // These are int type
            Array[i][j] = new unsigned int *[_z];

            // Enter random numbers into int array
            for(size_t k=0; k<_z; k++){

                // Allocate memory for data
                Array[i][j][k] = new unsigned int;
                
                *Array[i][j][k] = rand() % _user_input;

                std::cout << *Array[i][j][k] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;        
    }
    std::cout << std::endl;

    return true;

}


int main(){

    size_t user_input,x,y,z;

    std::cout <<"Input a positive number:" << std::endl;
    std::cin >> user_input;

// Ask the user for the dimensions and put into x,y,z.

    std::cout << "Enter the size of the first dimension: ";
    std::cin >> x;

    std::cout << "Enter the size of the second dimension: ";
    std::cin >> y;

    std::cout << "Enter the size of the third dimension: ";
    std::cin >> z;    

    std::cout << "----------------------" << std::endl;
    
    Version1(user_input,x,y,z);
    
    std::cout << "----------------------" << std::endl;
    
    Version2(user_input,x,y,z);
    
    std::cout << "----------------------" << std::endl;
    
    return 0;
}

