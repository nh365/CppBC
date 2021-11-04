#include "services.h"

Services::Services(std::string _serviceName, size_t _cost, size_t _time){

    myService.serviceName = _serviceName;
    myService.cost = _cost;
    myService.time = _time;
}


/* void Services::ListAvailableServices(){


} */