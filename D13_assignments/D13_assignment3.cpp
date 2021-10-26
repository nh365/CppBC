#include <iostream>
#include <set>
#include <iterator>

// Uses multiset
// Can be improved/extended with own search algorithm (binary-search)

int main(){

//    std::multiset <size_t, std::greater<size_t> > randomized_number;
    std::multiset <size_t> my_multiset;
    std::multiset <size_t>::iterator low_iterator,high_iterator;

    size_t inserted_number = 0;

    for (size_t i = 0; i < 1024; i++)
    {
        my_multiset.insert(rand()%100000);
    }
    
//    std::multiset <size_t, std::greater<size_t> >::iterator iterator1;
    std::multiset <size_t>::iterator iterator1;

//    std::cout << "The multiset elements are: " << std::endl;
//    for (iterator1 = my_multiset.begin(); iterator1 != my_multiset.end(); ++iterator1)
//    {
//        std::cout << *iterator1 << std::endl;
//    }

    // Generate a random number and find its closest peers.
    inserted_number = rand() % 100000;

    high_iterator = my_multiset.lower_bound(inserted_number);

    low_iterator = high_iterator;
    low_iterator--;
    
    std::cout << "Randomized number: " << inserted_number << std::endl;
    std::cout << "Lower peer: " << *low_iterator << " Higher peer: " << *high_iterator << std::endl;

    return 0;
}



















