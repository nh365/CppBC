#include <iostream>
#include "workshop.h"

Customer* Workshop::AddCustomer(std::string _customer_name, std::string _customer_phone){

    // Create a new instance
    Customer *newCustomer = new Customer(_customer_name, _customer_phone);

    // Push to list of customers.
    this->myCustomers.push_back(newCustomer);

    return newCustomer;
}

void Workshop::PrintMyCustomers(){

    for (size_t i = 0; i < this->myCustomers.size(); i++)
    {
        std::cout << "Customer: " << (i + 1) << " Name: " << this->myCustomers[i]->customer_name << std::endl; 
    }

    return;
}

Services* Workshop::AddService(std::string _serviceName, size_t _cost, size_t _time){

    // Create a new service
    Services *newService = new Services(_serviceName, _cost, _time);

    // Push to list of services
    this->myServices.push_back(newService);

    return newService;
}

void Workshop::PrintMyServices(){

    for (size_t i = 0; i < this->myServices.size(); i++)
    {
        std::cout << "Service: " << (i + 1) << " Name: " << this->myServices[i]->myService.serviceName 
            << " Time required: " << this->myServices[i]->myService.time 
            << " Cost: " << this->myServices[i]->myService.cost << std::endl; 
    }

    return;
}
