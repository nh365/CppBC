#include <iostream>

/* 
    Classes needed:
    Shop
    Customer
    Services
    Records
    Parts
*/


class Workshop{
// Attributes:
    //Array of customers
    std::string workshop_name;
    Services
    Customers
    Inventory

       int row = 0, column = 0;
        
        for (row = 0; row < 9; row++)
        {
            for (column = 0; column < 9; column++)
            {
                indata >> sudoku_table [row] [column].value;
    //            std::cout << "Added cell value:" << sudoku_table [row] [column].value << std::endl;
            }
        }
    
        indata.close();
//Methods: 
//    Workshop(std::string _name):workshop_name(_name){};
    Workshop();
    ~Workshop();
    AddUser();
    RemoveUser();
}

class Customer{
// Attributes:
public: 
    std::string customer_name;
    std::string customer_phone;
    int customer_added_date;
    ServiceOrder *service_order_list = new ServiceOrder

// Methods:
public: 
    Customer() = delete;
    Customer(std::string _name, std::string _phone):customer_name(_name),customer_phone(_phone){}
    ~Customer();
    UpdateCustomerPhone(std::string _phone):customer_phone(_phone){}  //NOK???
    AddServiceOrder();

};

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

}

class Derived : public Parts {




}



int main(){

    //Create workshop
    Workshop VBTorslanda();


    



}