/**
 * @file LoggerManager.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that contatins class subscriber LoggerManager and function that logs messages in file in async mode.
 * @version 0.1
 * @date 2023-03-27
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>
#include <fstream>
#include <future>
#include <vector>
#include <string>
#include <thread>


#include "subscriber.hpp"

/**
 * @brief function that logs messages in files
 * 
 * @param context messages to save in files
 * @param t special postFix for naming files in write way
 */
void pasteInFile(commandsContext context, long long t);



/**
 * @brief class subscriber LoggerManager that runs function pasteInFile in async mode via std::async
 * 
 */
class LoggerManager : public ISubscriber {
public:
/**
 * @brief Construct a new Logger Manager object
 * 
 */
    LoggerManager() {}

/**
 * @brief message handler that runs pasteInFile via std::async
 * 
 * @param context 
 */
    virtual void messageHandler(commandsContext& context);

/**
 * @brief clear unsubscriber from Dispatcher
 * 
 */
    virtual void unsubscribeHandler() {}


    static long long t;
};


#endif //LOGGER_HPP