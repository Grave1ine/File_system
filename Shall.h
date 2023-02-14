#ifndef SHALL_H
#define SHALL_H

#include <FileSystem.hpp>
#include <string>

class Shall
{
public:

    Shall(const std::string & name, size_t size_file);
    void Start();
    void Get();

private:

    std::string name;
    size_t size_file;
    Filesystem fileSystem;

    static void help();
    static void rename(const std::string &, const std::string &);


};

#endif // SHALL_H
