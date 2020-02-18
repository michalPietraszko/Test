#include <MainNode.hpp>

#include <mutex>
#include <iostream>
#include <thread>

namespace example
{
void MainNode::receive(Message &&msg)
{
    std::lock_guard<std::mutex> guard(m);
    std::cout << "Main node received: " << msg.payload << " from id: " << msg.senderId << std::endl;
    std::cout << std::endl;
    notifications.push(std::move(msg)); // thread safe buffer would be better
}

void MainNode::notifyObservers()
{
    m.lock();
    std::vector<Message> copy = notifications.toVec();
    m.unlock();

    for (auto observer : observers)
    {
        observer->receive(copy);
    }
}

void MainNode::startTimer(const MainNode::TimerIntervalUs interval)
{
    shouldRunTimer = true;
    std::thread([this, interval]() {
        while (shouldRunTimer)
        {
            notifyObservers();
            std::this_thread::sleep_for(
                std::chrono::milliseconds(interval));
        }
    }).detach();
}
} // namespace example