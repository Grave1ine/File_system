#include "Shall.h"
#include "File.hpp"
#include "FileSystem.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iterator>
#include <vector>

Shall::Shall(const std::string & name, size_t size_file):name(name), size_file(size_file)
{
    std::cout << "Shell constuctor  name : " << name << "\n" << "size : " << size_file << std::endl;
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
        std::cout << "User comand " << str << std::endl;

        std::istringstream _stream(str);                  //читает из строки и пишет в поток _stream
        words_consol_v.clear();                           //отчистка вектора

        while(_stream >> words_consol)                    //пока поток передает в строку то...
        {
            words_consol_v.push_back(words_consol);       //в конец вектора добавляются слова с консоли
        }

        if(words_consol_v.empty())                        //пуста ли строка?
        {
            continue;                                     //выход из цикла
        }

        words_consol = words_consol_v[0];                 //
        std::cout << "Command is: " << words_consol << std::endl;
        words_consol_v.erase(words_consol_v.begin());     //удаляет из вектора первое слово!!!

        if(words_consol == "help")
        {
            Shall::help();
        }
        else if(words_consol == "create_file")
        {
            File file = fileSystem.CreateFile(words_consol_v[0]);    //создает файл с именем ...
            std::ifstream readStrem(words_consol_v[1]);              //читает файл из адреса
            std::vector<uint8_t> transit;
            std::copy(std::istream_iterator<uint8_t>(readStrem), std::istream_iterator<uint8_t>(), std::back_inserter(transit));//копирует все в transit
            file.Write(transit);                          //transit записывется все в file
            fileSystem.Write(file);                       //file записывается в fileSystem
        }
        else if(words_consol == "read_file")
        {
            File file(words_consol_v[1]);
            fileSystem.Read(file);
        }
        else if(words_consol == "rename")
        {
            if(words_consol_v.size() != 2)
            {
                std::cerr << " Wrong Argument number!" << std::endl;
            }
                else
                {
                    Shall::rename(words_consol_v[0], words_consol_v[1]);
                }
        }
        else
        {
            std::cout << "Unknown command " << words_consol << std::endl;
            std::cout << "Type 'help' for a list of commands " << std::endl;
        }
        }
    std::cout << "Stop function: Start()" << std::endl;
}

void Shall::help()
{
    std::cout << "help. Command list : \n";
    std::cout << "exit : Exit from shell \n";
    std::cout << "help : Show this screen \n";
    std::cout << "rename : rename file to new name \n";
    std::cout << "create_file: file name\n";
}

void Shall::rename(const std::string &src_fName, const std::string &new_fName)
{
    std::cout << " Rename command run " << std::endl;
    std::cout << "Renaming file : " << src_fName << "," << " to file : " << new_fName << std::endl;
}
