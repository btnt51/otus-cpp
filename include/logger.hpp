#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <chrono>
#include <vector>
#include <string>

#include "subscriber.hpp"

class Logger : public ISubscriber {
public:
    virtual void messageHandler(commandsContext& context);

    virtual void unsubscribeHandler() {}
};


#endif //LOGGER_HPP