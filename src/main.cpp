#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include "EmbeddedSystem.hpp"

bool equalsIgnoreCase(std::string a, std::string b)
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

int main()
{
    EmbeddedSystem system;
    std::string command;

    std::cout << "========================================\n";
    std::cout << "        EMBEDDED SYSTEM CLI v1.0        \n";
    std::cout << "========================================\n";
    while(true)
    {
        std::cout << "embedded> ";
        std::getline(std::cin, command);
        std::stringstream stream(command);
        std::string token;
        std::vector<std::string> tokens;

        while(stream >> token)
        {
            tokens.push_back(token);
        }

        if(tokens.empty())
        {
            continue;
        }

        // Command: exit
        if(equalsIgnoreCase(tokens[0], "exit"))
        {
            std::cout << "\nExiting Embedded System CLI...\n";
            break;
        }

        // Command: help
        else if(equalsIgnoreCase(tokens[0], "help"))
        {
            std::cout << "\nAvailable commands:\n";
            std::cout << "  help    Display this help message\n";
            std::cout << "  exit    Exit Embedded System CLI\n\n";
        }

        // Module: GPIO
        else if(equalsIgnoreCase(tokens[0], "gpio"))
        {
            if(tokens.size() == 1)
            {
                std::cout << "ERROR: Missing GPIO subcommand\n";
            }

            // Subcommand: help
            else if(equalsIgnoreCase(tokens[1], "help"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "\nGPIO commands:\n";
                    std::cout << "  mode    Set GPIO pin mode\n";
                    std::cout << "  write   Write GPIO pin state\n";
                    std::cout << "  read    Read GPIO pin state\n";
                    std::cout << "  help    Display this help message\n\n";
                }
                else if(tokens.size() > 2)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            // Subcommand: mode
            else if(equalsIgnoreCase(tokens[1], "mode"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "ERROR: Missing GPIO pin\n";
                }
                else if(tokens.size() == 3)
                {
                    std::cout << "ERROR: Missing GPIO mode\n";
                }
                else if(tokens.size() == 4)
                {
                    try
                    {
                        PinMode mode;
                        int pin = std::stoi(tokens[2]);

                        if(equalsIgnoreCase(tokens[3], "output"))
                        {
                            mode = OUTPUT;
                            system.getGPIO().setMode(pin,mode);
                        }
                        else if(equalsIgnoreCase(tokens[3], "input"))
                        {
                            mode = INPUT;
                            system.getGPIO().setMode(pin,mode);
                        }
                        else
                        {
                            std::cout << "ERROR: Invalid GPIO mode\n";
                        }
                    }
                    catch(const std::invalid_argument&)
                    {
                        std::cout << "ERROR: Invalid GPIO pin\n";
                    }
                }
                else if(tokens.size() > 4)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            // Subcommand: write
            else if(equalsIgnoreCase(tokens[1], "write"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "ERROR: Missing GPIO pin\n";
                }
                else if(tokens.size() == 3)
                {
                    std::cout << "ERROR: Missing GPIO state\n";
                }
                else if(tokens.size() == 4)
                {
                    try
                    {
                        PinState state;
                        int pin = std::stoi(tokens[2]);

                        if(equalsIgnoreCase(tokens[3], "low"))
                        {
                            state = LOW;
                            system.getGPIO().write(pin,state);
                        }
                        else if(equalsIgnoreCase(tokens[3], "high"))
                        {
                            state = HIGH;
                            system.getGPIO().write(pin,state);
                        }
                        else
                        {
                            std::cout << "ERROR: Invalid GPIO state\n";
                        }
                    }
                    catch(const std::invalid_argument&)
                    {
                        std::cout << "ERROR: Invalid GPIO pin\n";
                    }
                }
                else if(tokens.size() > 4)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            // Subcommand: read
            else if(equalsIgnoreCase(tokens[1], "read"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "ERROR: Missing GPIO pin\n";
                }
                else if(tokens.size() == 3)
                {
                    try
                    {
                        int pin = std::stoi(tokens[2]);

                        system.getGPIO().read(pin);
                    }
                    catch(const std::invalid_argument&)
                    {
                        std::cout << "ERROR: Invalid GPIO pin\n";
                    }
                }
                else if(tokens.size() > 3)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            else
            {
                std::cout << "ERROR: Unknown GPIO subcommand\n";
            }
        }

        // Module: ADC
        else if(equalsIgnoreCase(tokens[0], "adc"))
        {
            if(tokens.size() == 1)
            {
                std::cout << "ERROR: Missing ADC subcommand\n";
            }

            // Subcommand: help
            else if(equalsIgnoreCase(tokens[1], "help"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "\nADC commands:\n";
                    std::cout << "  set     Set ADC channel value\n";
                    std::cout << "  read    Read ADC channel value\n";
                    std::cout << "  help    Display this help message\n\n";
                }
                else if(tokens.size() > 2)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            // Subcommand: read
            else if(equalsIgnoreCase(tokens[1], "read"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "ERROR: Missing ADC channel\n";
                }
                else if(tokens.size() == 3)
                {
                    try
                    {
                        int channel = std::stoi(tokens[2]);

                        system.getADC().read(channel);
                    }
                    catch(const std::invalid_argument&)
                    {
                        std::cout << "ERROR: Invalid ADC channel\n";
                    }
                }
                else if(tokens.size() > 3)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            // Subcommand: set
            else if(equalsIgnoreCase(tokens[1], "set"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "ERROR: Missing ADC channel\n";
                }
                else if(tokens.size() == 3)
                {
                    std::cout << "ERROR: Missing ADC value\n";
                }
                else if(tokens.size() == 4)
                {
                    try
                    {
                        int channel = std::stoi(tokens[2]);
                        
                        try
                        {
                            int value = std::stoi(tokens[3]);

                            system.getADC().setValue(channel, value);
                        }
                        catch(const std::invalid_argument&)
                        {
                            std::cout << "ERROR: Invalid ADC value\n";
                        }
                    }
                    catch(const std::invalid_argument&)
                    {
                        std::cout << "ERROR: Invalid ADC channel\n";
                    }
                }
                else if(tokens.size() > 4)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            else
            {
                std::cout << "ERROR: Unknown ADC subcommand\n";
            }
        }

        // Module: UART
        else if(equalsIgnoreCase(tokens[0], "uart"))
        {
            if(tokens.size() == 1)
            {
                std::cout << "ERROR: Missing UART subcommand\n";
            }

            // Subcommand: help
            else if(equalsIgnoreCase(tokens[1], "help"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "\nUART commands:\n";
                    std::cout << "  begin   Initialize UART\n";
                    std::cout << "  send    Send message through UART\n";
                    std::cout << "  status  Display UART status\n";
                    std::cout << "  help    Display this help message\n\n";
                }
                else if(tokens.size() > 2)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }
            
            // Subcommand: status
            else if(equalsIgnoreCase(tokens[1], "status"))
            {
                if(tokens.size() == 2)
                {
                    UARTState state = system.getUART().status();

                    switch(state)
                    {
                        case UNINITIALIZED:
                        std::cout << "UART = UNINITIALIZED\n";
                        break;

                        case READY:
                        std::cout << "UART = READY\n";
                        break;

                        default:
                        std::cout << "ERROR: UART status not recognized\n";
                        break;
                    }
                }
                else if(tokens.size() > 2)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            // Subcommand: begin
            else if(equalsIgnoreCase(tokens[1], "begin"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "ERROR: Missing UART baud rate\n";
                }
                else if(tokens.size() == 3)
                {
                    try
                    {
                        int baudRate = std::stoi(tokens[2]);

                        system.getUART().begin(baudRate);
                    }
                    catch(const std::invalid_argument&)
                    {
                        std::cout << "ERROR: Invalid UART baud rate\n";
                    }
                }
                else if(tokens.size() > 3)
                {
                    std::cout << "ERROR: Too many arguments\n";
                }
            }

            // Subcommand: send
            else if(equalsIgnoreCase(tokens[1], "send"))
            {
                if(tokens.size() == 2)
                {
                    std::cout << "ERROR: Missing UART message\n";
                }
                
                else if(tokens.size() >= 3)
                {
                    std::string message;
                    for(int i = 2; i < tokens.size(); i++)
                    {
                        if(i != 2)
                        {
                            message += " " + tokens[i];
                        }
                        else
                        {
                            message += tokens[i];
                        }
                    }

                    system.getUART().send(message);
                }
            }
            else
            {
                std::cout << "ERROR: Unknown UART subcommand\n";
            }    
        }
        else
        {
            std::cout << "ERROR: Unknown command\n";
        }
    }

    return 0;
}