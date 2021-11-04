
#include <vector>
#include "customer.h"
#include "workorder.h"

class Workshop{
// Attributes:

public:
    std::string myName;
    std::vector<Customer*> myCustomers;
    std::vector<Services*> myServices;
    std::vector<WorkOrder*> myWorkOrders;
//    Add parts inventory


//Methods: 
//    Workshop(std::string _name):workshop_name(_name){};
public:
    Workshop(std::string _ws_name):myName (_ws_name) {}
//    ~Workshop();

    Customer* AddCustomer(std::string _customer_name, std::string _customer_phone);
    // RemoveCustomer(...); LATER...
    Services* AddService(std::string _service_name, size_t _cost, size_t _time);
    // RemoveService(...); LATER...

    void PrintMyServices();
    void PrintMyCustomers();
    void PrintMyWorkOrders();
};



