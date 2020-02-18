#pragma once

#include <Observer.hpp>
#include <CircularBuffer.hpp>

namespace example
{
class MainNode
{
public:
    using TimerIntervalUs = int;

    void receive(Message&& msg);

    static MainNode& instance() 
    {
        static MainNode node;
        return node;
    }
    void addObserver(Observer* observer) { observers.push_back(observer); }
    void notifyObservers();

    void startTimer(const TimerIntervalUs interval);
    void stopTimer(){ shouldRunTimer = false; }

private:
    bool shouldRunTimer{false};
    std::mutex m;
    std::vector<Observer*> observers; // storing references would be a better(safer) idea
    CircularBuffer<Message> notifications;
};

} // namespace example