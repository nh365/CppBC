#include <iostream>
#include <stdlib.h>

typedef struct Random{
    size_t randomized_number = 0;
    size_t counter = 0;
}RandomEntry_T;

int main(){

    RandomEntry_T RandomEntryList [34];
    RandomEntry_T temporary_entry;

    // Init array
    for (size_t i = 0; i < 34; i++)
    {
        RandomEntryList[i].randomized_number = i;
        RandomEntryList[i].counter = 0;
    }
    

    // Generate random numbers and assign values to the random entries.
    for (size_t i = 0; i < 10000; i++)
    {

        RandomEntryList[rand() % 34].counter++;
    }

    // Sort the list according to number of hits
    // Ascending order
    for(size_t i = 0; i < 34; i++)
	{		
		for(size_t j = i+1; j < 34; j++)
		{
			if(RandomEntryList[i].counter > RandomEntryList[j].counter)
			{
				temporary_entry = RandomEntryList[i];
				RandomEntryList[i] = RandomEntryList[j];
				RandomEntryList[j] = temporary_entry;
			}
		}
	}

    // Print the result.
    for (size_t i = 0; i < 34; i++)
    {
        std::cout << "Random number: " << RandomEntryList[i].randomized_number << " was counted " << RandomEntryList[i].counter << " number of times." << std::endl;
    }

    return(0);
}


