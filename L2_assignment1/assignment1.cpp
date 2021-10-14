#include <iostream>
#include <cstdlib>

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

    // Allocate memory of the first dimension
    unsigned int ***Array = new unsigned int **[x];
    // samma som unsigned int*** Array;
    // den översta är om man definierar flera på samma rad.

    // Allocate memory of the second dimension
    for(size_t i=0; i<x; i++)
    {
//        *(Array+i) = new unsigned int *[y];

        Array[i] = new unsigned int *[y];

// Denna är        *(Array+i) = new unsigned int **[y];
// samma som:        Array[i] = new unsigned int **[y];  

        for(size_t j=0; j<y; j++){

            for(size_t k=0; k<y; k++){

                *(Array+i) = rand() % user_input;    
                std::cout << *Array << std::endl;

        }


    *Array = new unsigned int 
    
    
    unsigned int *ArrDemo = new unsigned int[2];
    unsigned char *ArrDemo = new unsigned char[2];



/* 
unsigned int user_input = 0;
// unsigned int generated_array [8][9][11];
// unsigned int i,j,k;

int *arr_pointer = new int;

    std::cout <<"Input a positive number:" << std::endl;
    std::cin >> user_input;

    for(size_t i=0; i<size; i++)
    {
        *(arr_pointer+i) = rand() % user_input;    
        std::cout << *arr_pointer << std::endl;
    }

 */

    return(0);
}


// FRÅN L1 SOM VI SKULLE MODIFIERA...
/* int main(){

unsigned int user_input = 0;
unsigned int generated_array [8][9][11];
unsigned int i,j,k;


    std::cout <<"Input a positive number:" << std::endl;
    std::cin >> user_input;

    for( i=0; i<8; i++){
        for(j=0; j<9; j++){
            for(k=0; k<11; k++){

                generated_array [i][j][k]= rand() % user_input;
                std::cout << generated_array[i][j][k] << "\t";
            }    
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

} */