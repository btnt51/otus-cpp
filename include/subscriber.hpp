#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <chrono>

using SubscriberId = std::uint64_t;



struct commandsContext {
    std::chrono::system_clock::time_point m_firstMessageTime;
    std::vector<std::string> m_commands;
};


class ISubscriber {
public:
    virtual ~ISubscriber(){}

    virtual void    messageHandler(commandsContext& context) = 0;

    virtual void unsubscribeHandler() = 0;

    SubscriberId    getSubscriberId()   {return (SubscriberId)this;}
};

using pISubscriber = std::shared_ptr<ISubscriber>;

#endif //SUBSCRIBER_HPP