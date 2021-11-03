#include "main.h"

/* 
    Classes needed:
    Shop
    Customer
    Services
    Records
    Parts
*/


/* 



class Service{

    enum service {TBD,oil_change,sparkplug_change, fault_tracing};

    // Set service

    Service(){service = TBD}
    ~Service()
};




// Service order perhaps not needed!?
/* class ServiceOrder{
//Attributes:
public:
    int order_nr;
    int date;
    enum status {todo, progress, completed};
    int price;
    enum payment_method {cash, visa, mastercard};
// Methods:
private:
    ServiceOrder();
    ~ServiceOrder();
    GenerateOrderNumber();
public:
    AddPrice();
    AddParts();
} */
/*
class Parts{
//Attributes:
public:
    int part_number;
    std::string part_name;
    int part_price;

//Methods:
private:
    Parts(int _partnr):part_number(_partnr){};
    ~Parts();
    AddPartPrice();
    AddPartName();

};

class Derived : public Parts {




};
 */


int main(){ 

    //Create workshop
    Workshop *VBTorslanda = new Workshop("VBTorslanda");

    std::cout << "Workshop created: " << VBTorslanda->myName << std::endl;

    // Add a customer
    VBTorslanda->AddCustomer("Jane Dough","012345679");

    // Add another customer
    VBTorslanda->AddCustomer("Sven Svensson","01239875");

    VBTorslanda->PrintMyCustomers();

    delete VBTorslanda;

    return 0;
}