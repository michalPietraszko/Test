#include <Sensor.hpp>
#include <MainNode.hpp>
#include <vector>
#include <future>

namespace example 
{
namespace
{
constexpr int exampleSensorNum{3};
constexpr std::chrono::seconds mainWaitTime{45};
constexpr unsigned nofityTimerUs{6000}; // fix me (change to chrono)
constexpr int exampleArbitraryMultiplayer{10u};
}

// design choice of using singleton for MainNode could be problematic if there's ever supposed to be 
// more than one node

class ExampleController
{
public:
    ExampleController()
    {
        for(int i = 0; i < exampleSensorNum; i++) // final version could use Sensor factory if sensor class is more complex
        {
            const int dummyId{i};
            const int dummyInfo{i * exampleArbitraryMultiplayer};
            addSensor(dummyId, dummyInfo);
        }
    }
    
    void addSensor(const int id, const int info)
    {
        sensors.emplace_back(id, info);
    }
    
    void spawnSensor(Sensor& sensor)
    {
        futures.push_back(std::async(std::launch::async, [&](Sensor* sensor){
            sensor->run();
        }, &sensor)); // could also use std::ref() and reference instead of a pointer as lambda parameter
    }

    void run()
    {
        for(Sensor& sensor : sensors)
        {
            spawnSensor(sensor);
        }
    }
  
public:
    std::vector<Sensor> sensors;
    std::vector<std::future<void>> futures;
};
}// namespace example


int main()
{
    using namespace example; 

    // not tested with different setup
    Observer o1;
    Observer o2;
    MainNode& node = MainNode::instance();
    node.addObserver(&o1);
    node.addObserver(&o2);
    node.startTimer(nofityTimerUs);

   ExampleController controller;

   controller.run();
   std::this_thread::sleep_for(std::chrono::seconds(mainWaitTime));
   node.stopTimer(); // not the best solution should be managed by raii
}