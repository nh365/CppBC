#include <iostream>
#include <cstdlib>



int main(){

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

}