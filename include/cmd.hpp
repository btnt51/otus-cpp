/**
 * @file cmd.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Class that implements Dispatcher in pattern Observer. Created by this article://https://habr.com/ru/post/108857/
 * @version 0.1
 * @date 2023-01-20
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>

#include <fstream>
#include <future>
#include <thread>
#include <mutex>

#include "subscriber.hpp"

using tp = std::chrono::system_clock::time_point;



/**
 * @brief Class CMD implements dispatcher in Observer pattern. Taking control over data from console or etc.
 * 
 */
class CMD {
private:

    /**
     * @brief Helper class for managing subscribers
     * 
     */
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
    commandsContext m_msg;
    bool m_isDynamicBlock = false;
    bool m_isSecondDynmicBlock = false;

public:
    /**
    * @brief Construct a new CMD object
    * 
    * @param amountOfBlocks amount of commands that used for managing output and loggers
    */
    CMD(int amountOfBlocks);

    ~CMD() = default;

    /**
    * @brief taking console control 
    * 
    */
    void takeConsoleControl();

    /**
    * @brief taking control over inputted data by const char*
    * 
    * @param data input data
    */
    void inputControlAsync(const char *data);


    /**
     * @brief sends message to subcribers
     * 
     * @param msg 
     */
    void sendMessage(commandsContext& msg);

    /**
     * @brief function that unsubcribe all subcribers from Dispatcher
     * 
     */
    void unsubscribe();

    /**
     * @brief unsubcribe single subcriber from Dispatcher
     * 
     * @param id id of Subcriber to remove from Dispatcher
     * @return true if unsubscribing was successful
     * @return false if unsubscribing was unsuccessful
     */
    bool unsubscribe(SubscriberId id);

    /**
    * @brief connect subscriber to Disaptcher
    * 
    * @param pNewSubscriber shared pointer to subscriber
    * @return SubscriberId id of Subscriber
    */
    SubscriberId subscribe(std::shared_ptr<ISubscriber> pNewSubscriber);
};

#endif //CMD_HPP