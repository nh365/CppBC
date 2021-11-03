#include <vector>
#include <string>
#include <iostream>

typedef struct services
{
    std::string serviceName;
    size_t cost;
    size_t time;
}Service_T;


class Services{
public:

    std::vector<Service_T*> AvailableServices;

    void AddService(std::string _serviceName, size_t _cost, size_t _time);
    void ListAvailableServices();

};
