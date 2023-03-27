/**
 * @file outputCMD.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that conatins subcriber outputCMD.
 * @version 0.1
 * @date 2023-03-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef OUTPUTCMD_HPP
#define OUTPUTCMD_HPP

#include <iostream>

#include "subscriber.hpp"

/**
 * @brief subcriber outputCMD that writes messages to console output via std::cout in async mode
 * 
 */
class outputCMD : public ISubscriber {
public:
    /**
    * @brief run testAsync function for console output in async via std::async
    * 
    * @param context 
    */
    virtual void messageHandler(commandsContext& context);


    /**
    * @brief function for console output with std::cout
    * 
    * @param context 
    */
    void testAsync(commandsContext& context);

    virtual void unsubscribeHandler() {}
};

#endif //OUTPUTCMD_HPP