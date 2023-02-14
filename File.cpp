# include <File.hpp>
#include <string>


File::File(std::string Name)
    : _Name(std::move(Name))                           //move с одним передаваемым параметром делает его временным
    {}


bool File::Write(const std::vector<uint8_t> & a)       //ссылка не вектор
{
    _Data.insert(_Data.end(), a.begin(), a.end());     //вставляет диапазон элементов в конец вектора
    return true;
}

/*
bool File::Write(const std::vector<uint8_t> &data)
{
    return Write(data.data(), data.size());
}
*/

bool File::Write(const void * data, size_t size)
{
    _Data.reserve(_Data.size() + size);                //резервирует память для элементов массива
    for(size_t i = 0; i < size; ++i)
    {
        _Data.push_back(*(static_cast<const uint8_t *>(data) + i));//приведение указателя к определенному типу данных и разыменование
    }
    return true;
}

bool File::Read(std::vector<uint8_t> &data)
{
    data = _Data;
    return true;
}

bool File::Read(void *data, size_t size)
{
    if(size > _Data.size())
    {
        return false;
    }

    for(size_t i = 0; i < size; ++i)
    {
        *(static_cast<uint8_t *>(data) + i) = _Data[i];
    }
    return true;
}

const void * File::Data() const
{
    return _Data.data();                               //возвращаяет указатель на первый элемент
}

size_t File::Size() const
{
    return _Data.size();                              //возвращаяет размер элементов в байтах
}

std::string File::Name() const
{
    return _Name;
}

