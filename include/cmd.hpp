/**
 * @file cmd.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Class that implements cmd, iterating with it and saving commands from it
 * @version 0.1
 * @date 2023-01-20
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>



class CMD {
public:
    CMD(int amountOfBlocks);
    ~CMD() = default;

    void takeConsoleControl();

    void printCommands();

    void saveToLog();

private:
    std::size_t m_lastOutput;
    std::chrono::system_clock::time_point m_firstMessageTime;
    std::vector<std::string> m_commands;
    int m_amountOfBlocks;

};

#endif //CMD_HPP