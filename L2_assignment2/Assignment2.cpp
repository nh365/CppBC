#include <iostream>
#include <cstdlib>


typedef struct list_item{
    int content;
    struct list_item *next_item;
}Node_t;


Node_t *findLast(Node_t *LinkedList){
    if(LinkedList==nullptr)
    {
        return(LinkedList);
    }
    Node_t *current = LinkedList; // Create a two pointers of Node_t type assign the start of the list to "current".
    while(current->next_item != nullptr){
        current = current->next_item;
    }
    return(current);
}

 void add_value(Node_t *LinkedList)
{
    //1) Find the last item
    //2) Create new
    //3) Assign and link
    Node_t *newNode, *lastNode = LinkedList; // Create a two pointers of Node_t type assign the start of the list to "current".

    if (LinkedList == nullptr)
    {
        LinkedList = new Node_t;
        LinkedList->content = rand() %50;
//        std::cout << "added random value: ";
//        std::cout << LinkedList->content << std::endl;
        LinkedList->next_item = nullptr;
    } else 
    {
        newNode = new Node_t;
        lastNode = findLast(LinkedList);
        lastNode->next_item = newNode;
        newNode->content = rand() %50;
//        std::cout << "added random value: ";
//        std::cout << newNode->content << std::endl;

    }
    
    return;
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

 void remove_index(Node_t *LinkedList, const int &_index){

 //   Node_t *previous = LinkedList[_index-1];    // Funkar inte
 //   Node_t *next = LinkedList[_index + 1];      // Funkar inte

    Node_t *previous, *next;
    
    size_t i = 0;
    // Init
    // There is more than one item in the list.
    // Assing the next item to next.
    // Assuming that the _index is within range...!
    if (LinkedList != nullptr && LinkedList->next_item != nullptr )
    {
        next = LinkedList->next_item;
    }

    while(( LinkedList != nullptr) && (i < _index))
    {
        previous = LinkedList->next_item; // previous now points to the one before the index to remove.
        next = LinkedList->next_item;     // next now points to the one before the index to remove. Add two...

        i++;
    }

    while(( LinkedList != nullptr) && (i < (_index + 2)))
    {

        next = LinkedList->next_item;

        i++;
    }

    if (LinkedList[_index] != nullptr)
    {
        previous->next_item = next;

        delete LinkedList;
    }
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

    Node_t *LinkedList = nullptr;
    int delete_index;

    for(size_t i = 0; i<10;i++)
    {
        add_value(LinkedList);
    }

    print_values(LinkedList);

    std::cout << "Which item do you want to remove (enter index)? ";
    std::cin >> delete_index;

    remove_index(LinkedList, delete_index);

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