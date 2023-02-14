#include <FileSystem.hpp>

Filesystem::Filesystem()
{
    ReadSuperBlock();
}

bool Filesystem::Write(const File & file)
{
    if(_Fat.find(file.Name()) != _Fat.end())     //пока первый попавшийся key(_Name) не равен следующему за последним элементом (_Name)
    {
        return false;
    }

    _Fat[file.Name()] = _NextIndex;              // привсоение значения [имя файла: значение]

    size_t originBytes = file.Size();
    size_t dataBytes = originBytes + sizeof(originBytes);              //присвоение размера файла в переменную в int
    const size_t bloksCount = dataBytes / BlokSize + (dataBytes % BlokSize ? 1 : 0);//определяем кол.во блоков для записи файла

    for(size_t i = 0; i < bloksCount; ++i)
    {
        std::ofstream block(std::to_string(_NextIndex + i) + ".block"); //создаем блоки с именами (знаковое целое число в строку + blok)
        size_t canWriteSize = BlokSize;

        if(i == 0)
        {
            block.write(reinterpret_cast<const char*>(&originBytes), sizeof(originBytes));
            canWriteSize -= sizeof(originBytes);
        }

        block.write(reinterpret_cast<const char *>(file.Data()) + i + BlokSize,   //запись в блоки (указатель на первый элемент _Data + ...)
                    std::min(canWriteSize, originBytes));                               //и размер файла
        originBytes -= canWriteSize;
    }

    _NextIndex += bloksCount;
    return true;
}

File Filesystem::CreateFile(std::string NameFile)
{
    return File(std::move(NameFile));
}

void Filesystem::WriteSuperBlock()
{
    std::ofstream block("0.block");
    block.write(reinterpret_cast<const char *>(&MagicNumber), sizeof (MagicNumber));
    block.write(reinterpret_cast<const char *>(&_NextIndex), sizeof (_NextIndex));
    size_t fatZise = _Fat.size();
    block.write(reinterpret_cast<const char*>(&fatZise), sizeof(fatZise));
    for(const auto&[key, value]: _Fat)
    {
        size_t strSize = key.size();
        block.write(reinterpret_cast<const char*>(&strSize), sizeof(strSize));
        block.write(reinterpret_cast<const char*>(key.data()), key.size());
        block.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
}

bool Filesystem::ReadSuperBlock()
{
    std::ifstream block("0.block");
    uint64_t magicNumber;
    block.read(reinterpret_cast<char *>(&magicNumber), sizeof(magicNumber));

    if(magicNumber != MagicNumber)
    {
        return false;
    }

    block.read(reinterpret_cast<char *>(&_NextIndex), sizeof(_NextIndex));
    size_t fatSize;
    block.read(reinterpret_cast<char *>(&fatSize), sizeof(fatSize));
    for(size_t i = 0; i < fatSize; ++i)
    {
        size_t strSize;
        block.read(reinterpret_cast<char *>(&strSize), sizeof(strSize));
        std::string key;
        key.resize(strSize);
        block.read(reinterpret_cast<char *>(key.data()), strSize);
        size_t value;
        block.read(reinterpret_cast<char *>(&value), sizeof (value));
        _Fat[key] = value;
    }
    return true;
}

bool Filesystem::Read(File& file)
{
    if (_Fat.find(file.Name()) == _Fat.end())
    {
        return false;
    }

    const size_t firstIndex = _Fat[file.Name()];

    size_t originBytes;
    {
    std::ifstream block(std::to_string(firstIndex) + ".block");
    block.read(reinterpret_cast<char *>(&originBytes), sizeof (originBytes));
    }

    const size_t dataBytes = originBytes + sizeof(originBytes);
    const size_t bloksCount = dataBytes / BlokSize + (dataBytes % BlokSize ? 1 : 0);

    for(size_t i = 0; i < bloksCount; ++i)
    {
        std::ifstream block(std::to_string(firstIndex + i) + ".block");
        std::vector<uint8_t> data(BlokSize);
        block.read(reinterpret_cast<char *>(data.data()), i == 0
                   ? BlokSize - sizeof(originBytes)
                   : BlokSize);
        file.Write(data);
    }
    return true;
}


