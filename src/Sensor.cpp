#include <Sensor.hpp>
#include <chrono>
#include <thread>

using namespace std::chrono;

namespace example
{
void Sensor::simulateSensorRunnig()
{
    for(int i = 0; i < 5; i++) // magic number just for example sake
    {
        using ArbitrarySleepTime = int;
        std::this_thread::sleep_for(seconds(ArbitrarySleepTime{(id * 2) + 3}));
        MainNode::instance().receive(createMessage(i));
    }
}
} // namespace 