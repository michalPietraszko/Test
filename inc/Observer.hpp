#pragma once

#include <Message.hpp>
#include <vector>
#include <iostream>

namespace example
{
static int observerIndentifier{0}; // fixme: ugly hack

/**
 * @Note:
 *  Every calss that should "receive" should derive from Receiver calss,
 *  class is unfinished but neat idea would to to pass unique pointers around 
 *  since once send data doesn't belong to sender anymore
 *  
 *  MainNode should also use receiver interface
 */

template<typename Msg>
class Receiver
{
public:
    virtual void receive(Msg msgs) = 0;
};

class Observer : public Receiver<std::vector<Message>> // could use alias for receiver template parameter
{
public:
    int identifier{observerIndentifier++};
    virtual void receive(std::vector<Message> msgs) override
    {
        // FIXME: cout race condition 
        std::cout<<"Observer: " << identifier << " received: "<<std::endl;
        for(const Message& m : msgs)
        {
            std::cout <<"[Id: " << m.senderId<<", payload: " << m.payload << "]; ";
        }
        std::cout<<std::endl;
        std::cout<<std::endl;
    }
};
} // example