#include "main.h"

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