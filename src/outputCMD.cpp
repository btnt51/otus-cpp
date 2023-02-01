#include "outputCMD.hpp"


void outputCMD::messageHandler(commandsContext& context) {
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