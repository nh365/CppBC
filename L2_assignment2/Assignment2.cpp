#include <iostream>
#include <cstdlib>


typedef struct list_item{
    int content;
    struct list_item *next_item;
}Node_t;


Node_t *findLast(Node_t * const _ll){

    Node_t *current = _ll; // Create a two pointers of Node_t type assign the start of the list to "current".

    if(current==nullptr)
    {
        return(current);
    }

    while(current->next_item != nullptr){
        current = current->next_item;
    }
    return(current);
}

 Node_t* add_value(Node_t *_ll)
{
    //1) Find the last item
    //2) Create new
    //3) Assign and link
    Node_t *firstNode = _ll, *newNode, *lastNode = _ll; // Create a two pointers of Node_t type assign the start of the list to "current".

    if (firstNode == nullptr)
    {
        firstNode = new Node_t;
        firstNode->content = rand() %50;
        firstNode->next_item = nullptr;

//        std::cout << "added random value: ";
//        std::cout << firstNode->content << std::endl;
    } else {
        newNode = new Node_t;
        lastNode = findLast(_ll);
        lastNode->next_item = newNode;
        newNode->content = rand() %50;
        newNode->next_item = nullptr;
//        std::cout << "added random value: ";
//        std::cout << newNode->content << std::endl;
    }
    
    return firstNode;
}

Node_t *remove_value(Node_t *LinkedList) //Simple way when returning pointer as opposed to using a reference.
{
    if (LinkedList == nullptr)
    {
        return(LinkedList);
    } 
    // 1) Find the head of the next item and set it as new head.
    // 2) Delete previous head.
    Node_t *next = LinkedList->next_item;
    delete LinkedList;
    LinkedList = nullptr;  // Question: Unnecessary? Does it even work since I have deleted the LinkList item!?l 
    return(next);
}

 Node_t* remove_index(Node_t *LinkedList, const int &_index){

 //   Node_t *previous = LinkedList[_index-1];    // Funkar inte
 //   Node_t *next = LinkedList[_index + 1];      // Funkar inte

    Node_t *previous, *next, *to_be_removed, *ret_val = nullptr;
    
    // Init
    // There is more than one item in the list.
    // Assing the next item to next.
    // Assuming that the _index is within range...!
    if (LinkedList == nullptr) {
        // The list is empty
        ret_val = LinkedList;
    } else if (LinkedList->next_item == nullptr)
    {
        // There is only one item in the list.
        if (_index != 1)
        {
            // The index is out of range.
            // This can probably be found at an earlier stage.
            std::cout << "The index is out of range." << std::endl;
            ret_val = LinkedList;
        } else {
            // Delete instance...
            // TODO!
            ret_val = nullptr;
        }
    } else {

        // Init values
        previous = LinkedList; 
        next = LinkedList;

        if (_index == 1)
        {
            // Remove the first item
            to_be_removed = LinkedList; // remove the head
            next = to_be_removed->next_item;
            delete to_be_removed;
            // LinkedList = next;
            ret_val = next; // Return new head

        } else if (_index == 2)
        {
            // Remove the second index
            to_be_removed = LinkedList->next_item; 
            next = to_be_removed->next_item;
            delete to_be_removed;
            previous->next_item = next;
            ret_val = LinkedList;   // Return head
        } else {
            // Remove any other index


            // Find the index to remove
            for (size_t i = 0; i < (_index - 2); i++)
            {
                previous = previous->next_item; // previous now points to the one before the index to remove.
                next = next->next_item;     // next now points to the one before the index to remove. Add two...
            }
            // Now previous and next point to the item before the one to be removed.
            // previous should remain here but next should be stepped up to the one after
            to_be_removed = previous->next_item;
            next = to_be_removed->next_item;
            delete to_be_removed;
            previous->next_item = next;

            ret_val = LinkedList;   // Return head
        }
    }

    return ret_val;
}

void print_values(Node_t *LinkedList){

    if (LinkedList != nullptr)
    {
        std::cout << "Values: ";

        do{
            std::cout << LinkedList->content << " ";
            LinkedList = LinkedList->next_item;
        } while (LinkedList->next_item != nullptr);
        std::cout << LinkedList->content << " ";
        std::cout << " " << std::endl;              
    }
    else{
        std::cout << "The list is empty!" << std::endl;  
    }
    return;
}


int main(){

//    Node_t *LinkedList = new Node_t;
    Node_t *LinkedList = nullptr;
    int delete_index;

    for(size_t i = 0; i<10;i++)
    {
        // add_value returns the first initialized cell in the list
        LinkedList = add_value(LinkedList);
    }

    print_values(LinkedList);

    std::cout << "Which item do you want to remove (enter index)? ";
    std::cin >> delete_index;

    LinkedList = remove_index(LinkedList, delete_index);

    print_values(LinkedList);

    for(size_t i = 0; i<10;i++)
    {
        LinkedList = remove_value(LinkedList);
    }

    print_values(LinkedList);

    return(0);
}


/* GÖR SENARE (?) MED USER INPUT...GÖR STATISK FÖRST
int main()
{
    bool keep_going;
    struct *list_item;

    {
        new list_item ;
        std::cout << "Enter a number: " << std::endl;
        std:cin >> 

    }while (keep_going)
}
*/