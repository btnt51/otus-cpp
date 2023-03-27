
#include "LoggerManager.hpp"


long long LoggerManager::t = 0;

std::mutex gMutex;


void pasteInFile(commandsContext context, long long t) {
    using namespace std::chrono_literals;
    
    if(!gMutex.try_lock()) {

    } else {
        std::vector<std::string> coms = context.m_commands;
        auto tt = context.m_firstMessageTime;
        std::string postFix;
        auto myid = std::this_thread::get_id();
        std::stringstream ss;
        ss << myid;
        std::string id = ss.str();
        if(t % 2 == 0)
            postFix = "file1_" + std::to_string(t) + "_" + id;
        else
            postFix = "file2_" + std::to_string(t) + "_" + id;

       
        std::ofstream logFile("bulk" + std::to_string(tt) + "__" + postFix+".log", std::ios_base::app);
        for(auto const & el : coms) {
    
            logFile << el << std::endl;
        }
        
        
        logFile.close();
    }
    gMutex.unlock(); 

}




void LoggerManager::messageHandler(commandsContext& context) {
    auto res = std::async(std::launch::async,&pasteInFile, context, t);
    res.get();
    ++t;
}


