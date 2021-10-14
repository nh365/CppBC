#include <iostream>



int main(){

int my_guess = 128/2;
int last_guess = 128/2;
int highest_incorrect = 128;
int lowest_incorrect = 0;
int i;
bool response;
bool correct;

    for( i=0; i<7; i++)
    {
        std::cout << "My guess is: " << my_guess << " Is that correct? (true/false)" << std::endl;    
        std::cin >> correct;
        if(correct)
        {
            std::cout << "I guessed right after " << i << " tries" << std::endl;
            i=7;
        } else {
            std::cout << "Is the number larger than:" << my_guess << std::endl;
            std::cin >> response;
            if(response)
            {
                std::cout << "Higher than " << my_guess << std::endl;
                lowest_incorrect = my_guess;
            } else
            {
                std::cout << "Lower than " << my_guess << std::endl;
                highest_incorrect = my_guess;
            }
            my_guess = ((highest_incorrect - lowest_incorrect) / 2 ) + lowest_incorrect;
        }
    }
}