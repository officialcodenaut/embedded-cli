#include <iostream>
#include "CLI.hpp"

static bool equalsIgnoreCase(std::string a, std::string b)
{
    if(a.size() != b.size())
    {
        return false;
    }

    for(int i = 0; i < a.size(); i++)
    {
        if(tolower(a[i]) != tolower(b[i]))
        {
            return false;
        }
    }

    return true;
}

bool CLI::handleCommand(const std::vector<std::string>& tokens, EmbeddedSystem& system)
{
    if(equalsIgnoreCase(tokens[0], "exit"))
    {
        std::cout << "\nExiting Embedded System CLI...\n";
        return false;
    }
    return true;
}