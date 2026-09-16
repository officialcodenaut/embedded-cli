#ifndef CLI_HPP
#define CLI_HPP
#include <vector>
#include <string>
#include "EmbeddedSystem.hpp"

class CLI
{
    public:
    bool handleCommand(const std::vector<std::string>& tokens, EmbeddedSystem& system);
};

#endif