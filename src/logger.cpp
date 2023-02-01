#include "logger.hpp"


void Logger::messageHandler(commandsContext& context) {
    auto tp_sec = std::chrono::time_point_cast<std::chrono::seconds>(context.m_firstMessageTime);
    auto tt = std::chrono::system_clock::to_time_t (tp_sec);
    std::ofstream logFile("blink" + std::to_string(tt) + ".log", std::ios_base::app);
    for(auto const & el : context.m_commands) {
        logFile << el << std::endl;
    }
}