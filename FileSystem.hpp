#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <File.hpp>

#include <fstream>
#include <cuchar>
#include <unordered_map>
#include <string>

class Filesystem
{
private:

    static constexpr size_t BlokSize = 4096;
    static constexpr uint64_t MagicNumber = 754968864301887519;
    size_t _NextIndex = 1;
    std::unordered_map<std::string, size_t> _Fat;  //fat table?

    void WriteSuperBlock();

public:

    Filesystem();

    bool Write(const File & file);

    File CreateFile(std::string NameFile);

    bool ReadSuperBlock();

    bool Read(File& file);

};

#endif // FILESYSTEM_HPP
