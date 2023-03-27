#include "outputCMD.hpp"
#include "subscriber.hpp"



void outputCMD::messageHandler(commandsContext& context) {
    /* std::cout << "bulk: ";
    std::size_t i = 0;
    for(auto const &el : context.m_commands) {
        std::cout << el;
        if(i < context.m_commands.size() - 1)
            std::cout << ", ";
        i++;
    }
    std::cout << std::endl; */
    auto f = std::async(std::launch::async, [&](){ return this->testAsync(context);});
}

void outputCMD::testAsync(commandsContext &context) {
    std::cout << "bulk: ";
    std::size_t i = 0;
    for(auto const &el : context.m_commands) {
        std::cout << el;
        if(i < context.m_commands.size() - 1)
            std::cout << ", ";
        i++;
    }
    std::cout << std::endl;
}