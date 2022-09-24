#include "Serialization.h"


Stream& operator<<(Stream& stream, char& value)
{
    stream.write((char*)(&value), sizeof(char));
    return stream;
}

Stream& operator<<(Stream& stream, const char& value)
{
    stream.write((char*)(&value), sizeof(char));
    return stream;
}

Stream& operator<<(Stream& stream, bool& value)
{
    stream.write((char*)(&value), sizeof(bool));
    return stream;
}

Stream& operator<<(Stream& stream, short& value)
{
    stream.write((char*)(&value), sizeof(short));
    return stream;
}

Stream& operator<<(Stream& stream, unsigned short& value)
{
    stream.write((char*)(&value), sizeof(unsigned short));
    return stream;
}

Stream& operator<<(Stream& stream, int& value)
{
    stream.write((char*)(&value), sizeof(int));
    return stream;
}

Stream& operator<<(Stream& stream, const int& value)
{
    stream.write((char*)(&value), sizeof(int));
    return stream;
}

Stream& operator<<(Stream& stream, unsigned int& value)
{
    stream.write((char*)(&value), sizeof(unsigned int));
    return stream;
}

Stream& operator<<(Stream& stream, const unsigned int& value)
{
    stream.write((char*)(&value), sizeof(unsigned int));
    return stream;
}

Stream& operator<<(Stream& stream, long& value)
{
    stream.write((char*)(&value), sizeof(long));
    return stream;
}

Stream& operator<<(Stream& stream, unsigned long& value)
{
    stream.write((char*)(&value), sizeof(unsigned long));
    return stream;
}

Stream& operator<<(Stream& stream, const unsigned long& value)
{
    stream.write((char*)(&value), sizeof(unsigned long));
    return stream;
}

Stream& operator<<(Stream& stream, long long& value)
{
    stream.write((char*)(&value), sizeof(long long));
    return stream;
}

Stream& operator<<(Stream& stream, unsigned long long& value)
{
    stream.write((char*)(&value), sizeof(unsigned long long));
    return stream;
}

Stream& operator<<(Stream& stream, float& value)
{
    stream.write((char*)(&value), sizeof(float));
    return stream;
}

Stream& operator<<(Stream& stream, double& value)
{
    stream.write((char*)(&value), sizeof(double));
    return stream;
}

Stream& operator<<(Stream& stream, long double& value)
{
    stream.write((char*)(&value), sizeof(long double));
    return stream;
}


Stream& operator>>(Stream& stream, char& value)
{
    stream.read((char*)(&value), sizeof(char));
    return stream;
}

Stream& operator>>(Stream& stream, bool& value)
{
    stream.read((char*)(&value), sizeof(bool));
    return stream;
}

Stream& operator>>(Stream& stream, short& value)
{
    stream.read((char*)(&value), sizeof(short));
    return stream;
}

Stream& operator>>(Stream& stream, unsigned short& value)
{
    stream.read((char*)(&value), sizeof(unsigned short));
    return stream;
}

Stream& operator>>(Stream& stream, int& value)
{
    stream.read((char*)(&value), sizeof(int));
    return stream;
}

Stream& operator>>(Stream& stream, unsigned int& value)
{
    stream.read((char*)(&value), sizeof(unsigned int));
    return stream;
}

Stream& operator>>(Stream& stream, long& value)
{
    stream.read((char*)(&value), sizeof(long));
    return stream;
}

Stream& operator>>(Stream& stream, unsigned long& value)
{
    stream.read((char*)(&value), sizeof(unsigned long));
    return stream;
}

Stream& operator>>(Stream& stream, long long& value)
{
    stream.read((char*)(&value), sizeof(long long));
    return stream;
}

Stream& operator>>(Stream& stream, unsigned long long& value)
{
    stream.read((char*)(&value), sizeof(unsigned long long));
    return stream;
}

Stream& operator>>(Stream& stream, float& value)
{
    stream.read((char*)(&value), sizeof(float));
    return stream;
}

Stream& operator>>(Stream& stream, double& value)
{
    stream.read((char*)(&value), sizeof(double));
    return stream;
}

Stream& operator>>(Stream& stream, long double& value)
{
    stream.read((char*)(&value), sizeof(long double));
    return stream;
}

Stream& operator<<(Stream& stream, std::string& str)
{
    stream << str.size();
    for (size_t i = 0; i < str.size(); i++)
    {
        stream << str[i];
    }

    return stream;
}

Stream& operator>>(Stream& stream, std::string& str)
{
    str.clear();

    size_t contSize = 0;
    stream >> contSize;

    str.resize(contSize);
    for (size_t i = 0; i < contSize; i++)
    {
        stream >> str[i];
    }

    return stream;
}

