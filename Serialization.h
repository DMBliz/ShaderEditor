#pragma once

#include <map>
#include <vector>
#include <string>

class Stream
{
public:
    virtual void write(char* buffer, unsigned int byteCount) = 0;
    virtual void read(char* buffer, unsigned int byteCount) = 0;
};

Stream& operator<<(Stream& stream, char& value);

Stream& operator<<(Stream& stream, const char& value);

Stream& operator<<(Stream& stream, bool& value);

Stream& operator<<(Stream& stream, short& value);

Stream& operator<<(Stream& stream, unsigned short& value);

Stream& operator<<(Stream& stream, int& value);

Stream& operator<<(Stream& stream, const int& value);

Stream& operator<<(Stream& stream, unsigned int& value);

Stream& operator<<(Stream& stream, const unsigned int& value);

Stream& operator<<(Stream& stream, long& value);

Stream& operator<<(Stream& stream, unsigned long& value);

Stream& operator<<(Stream& stream, const unsigned long& value);

Stream& operator<<(Stream& stream, long long& value);

Stream& operator<<(Stream& stream, unsigned long long& value);

Stream& operator<<(Stream& stream, float& value);

Stream& operator<<(Stream& stream, double& value);

Stream& operator<<(Stream& stream, long double& value);


Stream& operator>>(Stream& stream, char& value);

Stream& operator>>(Stream& stream, bool& value);

Stream& operator>>(Stream& stream, short& value);

Stream& operator>>(Stream& stream, unsigned short& value);

Stream& operator>>(Stream& stream, int& value);

Stream& operator>>(Stream& stream, unsigned int& value);

Stream& operator>>(Stream& stream, long& value);

Stream& operator>>(Stream& stream, unsigned long& value);

Stream& operator>>(Stream& stream, long long& value);

Stream& operator>>(Stream& stream, unsigned long long& value);

Stream& operator>>(Stream& stream, float& value);

Stream& operator>>(Stream& stream, double& value);

Stream& operator>>(Stream& stream, long double& value);

Stream& operator<<(Stream& stream, std::string& str);

Stream& operator>>(Stream& stream, std::string& str);

template <typename T>
Stream& operator<<(Stream& stream, std::vector<T>& vec)
{
    stream << vec.size();
    for (size_t i = 0; i < vec.size(); i++)
    {
        stream << vec[i];
    }

    return stream;
}

template <typename T>
Stream& operator>>(Stream& stream, std::vector<T>& vec)
{
    vec.clear();

    size_t contSize = 0;
    stream >> contSize;

    vec.resize(contSize);
    for (size_t i = 0; i < contSize; i++)
    {
        stream >> vec[i];
    }

    return stream;
}


template <typename T, typename C>
Stream& operator<<(Stream& stream, std::map<T, C>& map)
{
    stream << map.size();
    for (auto it = map.begin(); it != map.end(); it++)
    {
        stream << it->first;
        stream << it->second;
    }

    return stream;
}

template <typename T, typename C>
Stream& operator>>(Stream& stream, std::map<T, C>& map)
{
    map.clear();

    size_t contSize = 0;
    stream >> contSize;

    for (size_t i = 0; i < contSize; i++)
    {
        T key;
        C val;
        stream >> key;
        stream >> val;
        map.emplace(key, val);
    }

    return stream;
}
