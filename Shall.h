#ifndef SHALL_H
#define SHALL_H

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

    void help();
    void rename();

};

#endif // SHALL_H
