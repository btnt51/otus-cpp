#include "cmd.hpp"


CMD::CMD(int amountOfBlocks) {
    this->m_amountOfBlocks = amountOfBlocks;
    this->m_lastOutput = 0;
}

CMD::~CMD(){

}


void CMD::takeConsoleControl() {
    std::string command;
    int k = 1;

    bool isDynamicBlock = false;
    bool isSecondDynmicBlock = false;
    while(std::getline(std::cin, command)) {
        if(command == "" || command == " ")
            break;

        if(command == "{" && !isDynamicBlock) {
            if(this->m_commands.size() > 0 && k > 1) {
                this->printCommands();
                this->saveToLog();
                k = 1;
            }
            isDynamicBlock = true;
        } else if(command == "{" && isDynamicBlock) {
            isSecondDynmicBlock = true;
            continue;
        }

        if(command == "}" && isDynamicBlock  && isSecondDynmicBlock) {
            isSecondDynmicBlock = false;
            continue;
        } else if(command == "}" && isDynamicBlock && !isSecondDynmicBlock) {
            this->printCommands();
            this->saveToLog();
            isDynamicBlock = false;
        }

        if(command == "{")
            continue;

        if(command == "}")
            continue; 

        if(k == 1)
            m_firstMessageTime = std::chrono::system_clock::now();

        this->m_commands.push_back(command);

        if(k == this->m_amountOfBlocks && !isDynamicBlock) {
            this->printCommands();
            this->saveToLog();
            k = 1;
        } else if(k < this->m_amountOfBlocks && !isDynamicBlock) {
            k++;
        }
    }
}


void CMD::printCommands() {
    std::cout << "bulk: ";
    std::size_t i = 0;
    for(auto const &el : this->m_commands) {
        std::cout << el;
        if(i < this->m_commands.size() - 1)
            std::cout << ", ";
        i++;
    }
    std::cout << std::endl;
}


void CMD::saveToLog() {
    auto tp_sec = std::chrono::time_point_cast<std::chrono::seconds>(m_firstMessageTime);
    auto tt = std::chrono::system_clock::to_time_t (tp_sec);
    std::ofstream logFile("blink" + std::to_string(tt) + ".log", std::ios_base::app);
    for(auto const & el : this->m_commands) {
        logFile << el << std::endl;
    }
    m_commands.clear();
}