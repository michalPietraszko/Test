#pragma once

#include <vector>

template<typename MessageType>
class CircularBuffer // quick curcular buffer impl, normally boost::circular_buffer would be *much* better
// NOT thread safe
{
    constexpr static unsigned maxSize{5};
    static_assert(maxSize > 0, "...");
    using Buffer = std::vector<MessageType>;

public:
    CircularBuffer()
    {
        buffer.reserve(maxSize);
    }

    void push(MessageType&& message)
    {
        if(not reachedMax)
        {
            buffer.push_back(std::forward<MessageType>(message));
        }
        else
        {
            buffer.at(insertIndex) = std::forward<MessageType>(message);
        }
        advanceInsertIdx();
    }

    typename Buffer::iterator begin()
    {
        return buffer.begin();
    }

    typename Buffer::iterator end()
    {
        return buffer.end();
    }
    
    void advanceInsertIdx()
    {
        if(insertIndex >= maxSize - 1)
        {
            insertIndex = 0;
            reachedMax = true;
        }
        else
        {
            insertIndex++;
        }
    }

    std::vector<MessageType> toVec()
    {
        return buffer;
    }

private:
    Buffer buffer;
    unsigned insertIndex {0u};
    bool reachedMax{false};

};