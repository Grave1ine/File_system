#include "Shall.h"

#include <sstream>
#include <string>
#include <iostream>
#include <vector>

Shall::Shall(const std::string & name, size_t size_file):name(name), size_file(size_file)
{
    std::cout << "Shell constuctor  name : " << name << " size : " << size_file << std::endl;
    Shall::Get();
}

void Shall::Get()
{
    std::cout << "appropriated name : " << name << " size : " << size_file << std::endl;
}

void Shall::Start()
{
    std::cout << "function: Start()" << std::endl;
    std::string words_consol, str;
    std::vector<std::string> words_consol_v;

    while(words_consol != "exit")
    {
        std::cout << "> ";
        std::getline(std::cin, str);
        std::cout << "User comand" << str << std::endl;

        std::istringstream _stream(str);
        while(_stream >> words_consol)
        {
            words_consol_v.push_back(words_consol);
        }

        if(words_consol_v.empty())                        //пуста ли строка?
        {
            continue;                                     //выход из уикла
        }

        words_consol = words_consol_v[0];
        std::cout << "Command is: " << words_consol << std::endl;
        words_consol_v.erase(words_consol_v.begin(), words_consol_v.end());     //удаляет из строки символы от начала и до конца

        if(words_consol == "help")
        {
            Shall::help();
        }
        else if(words_consol == "rename")
        {
            Shall::rename();
        }
        else
        {
            std::cout << "Unknown command " << words_consol << std::endl;
        }
    }
    std::cout << "Stop function: Start()" << std::endl;
}

void Shall::help()
{
    std::cout << " Help. Command list : \n";
    std::cout << "exit : Exit from shell \n";
    std::cout << "help : Show this screen \n";
    std::cout << "rename : rename file \n";
}

void Shall::rename()
{
    std::cout << " Rename command run " << std::endl;
}
