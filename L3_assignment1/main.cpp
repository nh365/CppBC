#include <iostream>
#include <string>
#include "workshop.h"

#define WS_ID 012345
/* 
    Classes needed:
    Shop
    Customer
    Services
    Records
    Parts
    ....
*/

Workshop* InitMyWorkshop(Workshop* _ws){

    //Create workshop
    _ws = new Workshop("VBTorslanda");

    std::cout << "Workshop created: " << _ws->myName << std::endl;

    // Add services
    _ws->AddService("Oilchange", 1000, 20);
    _ws->AddService("Software update", 2000, 40);
    _ws->AddService("WIndscreen change", 8000, 180);

    _ws->PrintMyServices();

    // Add a customers
    _ws->AddCustomer("Jane Dough","012345679");
    _ws->AddCustomer("Sven Svensson","01239875");

    _ws->PrintMyCustomers();

    return _ws;
}

WorkOrder* UseWorkshop(Workshop* _workshop_ptr){

    WorkOrder *work_order_ptr = nullptr;
    size_t activity = 0;
    size_t customer_index = 0;
    size_t service_index = 0;

    std::cout << "What do you want to do (New order = 1, Update order = 2): ";
    std::cin >> activity;

    if (activity == 1)
    {
        std::cout << "Select customer (index): ";
        std::cin >> customer_index;
        std::cout << "Select service (index): ";
        std::cin >> service_index;
        // Create workorder
    //    work_order = new WorkOrder();
        work_order_ptr = new WorkOrder(WS_ID, customer_index, service_index);

        std::cout << "New work order created. Name: " << work_order_ptr->customer_id_global 
            << " Service ID: " << work_order_ptr->service_id_in_progress 
            << " Order status: " << work_order_ptr->status_of_work_order << std::endl;

    } else if (activity == 2){

        // TODO
        std::cout << "Not yet implemented." << std::endl;
    }
    return work_order_ptr; // TODO
}

int main(){ 

    Workshop *VBTorslanda = nullptr;

    InitMyWorkshop(VBTorslanda);
    UseWorkshop(VBTorslanda);

    delete VBTorslanda;

    return 0;
}