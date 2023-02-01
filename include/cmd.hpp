/**
 * @file cmd.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Class that implements Dispatcher in pattern Observer
 * @version 0.1
 * @date 2023-01-20
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

#include "subscriber.hpp"

using tp = std::chrono::system_clock::time_point;




class CMD {
private:
    class ISubscriberItem {
    public:
        ISubscriberItem(pISubscriber subscriber) : mp_ISubscriber(subscriber) {}
        
        ~ISubscriberItem() {
            mp_ISubscriber->unsubscribeHandler();
        }

        pISubscriber getISubscriber() const { return mp_ISubscriber; }

    private:
        pISubscriber mp_ISubscriber;
    };

    using pISubscriberItem = std::shared_ptr<ISubscriberItem>;
    using subscribersList = std::vector<pISubscriberItem>;
    using subscribersListPtr = std::shared_ptr<subscribersList>;

    subscribersListPtr mp_subscriberList;
    int m_amountOfBlocks;
    std::mutex m_lock;

public:
    CMD(int amountOfBlocks);

    ~CMD() = default;

    void takeConsoleControl();

    void printCommands();

    void saveToLog();

    void sendMessage(commandsContext& msg);

    bool unsubscribe(SubscriberId id);

    SubscriberId subscribe(std::shared_ptr<ISubscriber> pNewSubscriber);
};

#endif //CMD_HPP