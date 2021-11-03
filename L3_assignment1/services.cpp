#include "services.h"

void Services::AddService(std::string _serviceName, size_t _cost, size_t _time){



}

void Services::ListAvailableServices(){

   for (size_t i = 0; i < this->AvailableServices.size(); i++)
    {
        std::cout << "Service: " << (i + 1) << " Name: " << this->AvailableServices[i]->serviceName 
            << " Time required: " << this->AvailableServices[i]->time 
            << " Cost: " << this->AvailableServices[i]->cost << std::endl; 
    }


}