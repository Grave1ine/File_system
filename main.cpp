#include "Shall.h"
#include <iostream>
#include <stdio.h>
#include <memory>

const std::string DEFAULT_NAME = "default_name";
const size_t DEFAULT_SIZE = 1000;

int main(int argc, char * argv[])                      //принимает параметры с консоли кол.во аргументов/аргументы
{
    std::cout << "Start FS" << std::endl;
    std::unique_ptr<Shall> node_shall;                 //умный указатель

    for(int i = 0; i < argc; ++i)
    {
        std::cout << "argc " << i << " : " << argv[i] << std::endl;
    }

    if(argc == 3)
    {
        std::string name_file = argv[1];               //в name_fail запишет значение
        size_t size_file = std::stoi(argv[2]);         //stoi переводит из string в int
        node_shall = std::make_unique<Shall>(name_file, size_file);//присваение в умный указатель
    }
    else
    {
        std::cout << "creating a standart value file " << " name : " << DEFAULT_NAME << " size : " << DEFAULT_SIZE << std::endl;
        node_shall = std::make_unique<Shall>(DEFAULT_NAME, DEFAULT_SIZE);//присваение в умный указатель
    }

    node_shall->Start();

    return 0;
}
