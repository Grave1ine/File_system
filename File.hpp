#ifndef FILE_HPP
#define FILE_HPP

#include <cstdlib>
#include <vector>
#include <string>

class File
{
private:

    std::string _Name;
    std::vector<uint8_t> _Data;

public:

    explicit File(std::string NameFaile);

    bool Write(const std::vector<uint8_t> & data);

    bool Write(const void * data, size_t size);

    bool Read(std::vector<uint8_t> & data);    //ссыдка на вектор?

    bool Read(void * data, size_t size);  //data указатель на неизвестный тип данных, такой указател не разыменовываеьтся

    const void * Data() const;

    size_t Size() const;

    std::string Name() const;



};
#endif // FILE_HPP
