/**
 * @file subscriber.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that contatins commandsContext and interface-class Subscriber for pattern Observer.
 * @version 0.1
 * @date 2023-03-27
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <mutex>
#include <future>
#include <mutex>
#include <thread>

using SubscriberId = std::uint64_t;


/**
 * @brief structure that sends as message to subscribers.
 * 
 */
struct commandsContext {
    time_t m_firstMessageTime;
    std::vector<std::string> m_commands;
};

/**
 * @brief class that provides interface for subscribers.
 * 
 */
class ISubscriber {
public:
    /**
     * @brief Destroy the ISubscriber object
     * 
     */
    virtual ~ISubscriber(){}

    /**
    * @brief functions for handling commands context
    * 
    * @param context message from Dispatcher
    */
    virtual void messageHandler(commandsContext& context) = 0;

    /**
     * @brief function that provides interface for function that used when subscriber was unsubscribed from Dispatcher 
     * 
     */
    virtual void unsubscribeHandler() = 0;


    /**
     * @brief Get the Subscriber Id object
     * 
     * @return SubscriberId std::uint64_t
     */
    SubscriberId getSubscriberId()   {return (SubscriberId)this;}
};

using pISubscriber = std::shared_ptr<ISubscriber>;

#endif //SUBSCRIBER_HPP