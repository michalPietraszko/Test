#pragma once
#include "Message.hpp"
#include "MainNode.hpp"

namespace example
{
class Sensor
{
public:
    Sensor() = default;
    Sensor(const int id, const int info) : id{id}, info(info) {};
    
    void simulateSensorRunnig();

    Message createMessage(const int someOtherInfo) const
    {
        return {id, info + someOtherInfo};
    }

    void run()
    {
        simulateSensorRunnig();
    }

private:
    int id {0};
    int info{0};
};

} // namespace example