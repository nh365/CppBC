#include <string>

typedef struct services
{
    std::string serviceName;
    size_t cost;
    size_t time;
}Service_T;


class Services{
public:

    Service_T myService;
//    Services(std::string _serviceName, size_t _cost, size_t _time):myService.serviceName(_serviceName), myService.cost(_cost), myService->time(_time) {}
    Services(std::string _serviceName, size_t _cost, size_t _time);

//    std::vector<Service_T*> AvailableServices;
//    void AddService(std::string _serviceName, size_t _cost, size_t _time);
//    void ListAvailableServices();

};

