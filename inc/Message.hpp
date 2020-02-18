#pragma once

namespace example
{
template<typename Payload>
struct MessageT
{
    int senderId{};
    Payload payload{};
};

using Message = MessageT<int>;
} //namespace example