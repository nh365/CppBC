#include "customer.h"

/* Customer::Customer(std::string _name, std::string _phone){

    this->customer_name = _name;
    this->customer_phone = _phone;
    this->customer_total_money_spent = 0; // Not possible to access in constructor since private, use one liner constructor instead.

} */


void Customer::AddMoneySpent(size_t _amount){

    this->total_money_spent += _amount;

    return;
}

size_t Customer::ReadMoneySpent(){

    return this->total_money_spent;

}
