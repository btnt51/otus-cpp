#ifndef OUTPUTCMD_HPP
#define OUTPUTCMD_HPP

#include <iostream>

#include "subscriber.hpp"


class outputCMD : public ISubscriber {
public:
    virtual void messageHandler(commandsContext& context);

    virtual void unsubscribeHandler() {}
};

#endif //OUTPUTCMD_HPP