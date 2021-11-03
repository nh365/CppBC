
#include "main.h"

class Workshop{
// Attributes:

public:
    std::string myName;
    std::vector<Customer*> myCustomers;
    std::vector<Services*> myServices;
//    Inventory


//Methods: 
//    Workshop(std::string _name):workshop_name(_name){};
public:
    Workshop(std::string _ws_name):myName (_ws_name) {}
//    ~Workshop();

    Customer* AddCustomer(std::string _customer_name, std::string _customer_phone);
    // RemoveCustomer(...); LATER...
    Services* AddService(std::string _service_name, size_t _cost, size_t _time);
    // RemoveService(...); LATER...

    void PrintMyCustomers();

};



