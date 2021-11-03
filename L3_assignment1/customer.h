#include <string>

class Customer{
// Attributes:
public: 
    std::string customer_name;
    std::string customer_phone;

private:
    size_t total_money_spent;
// Methods:
public: 
// ???    Customer() = delete;
    Customer(std::string _name, std::string _phone):customer_name(_name),customer_phone(_phone){}
//    Customer(std::string _name, std::string _phone);
    ~Customer();

    void AddMoneySpent(size_t _amount);
    size_t ReadMoneySpent();
//    UpdateCustomerPhone(std::string _phone):customer_phone(_phone){}  //NOK???
//    AddServiceOrder();

};