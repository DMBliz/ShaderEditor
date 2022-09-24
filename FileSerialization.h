#pragma once

#include "Serialization.h"
#include <iostream>
#include <fstream>

class OutputFileStream : public Stream
{
private:
    std::string path;
    std::ofstream outStream;

public:
    OutputFileStream(std::string path)
    {
        outStream.open(path, std::ios::binary);
    }
    ~OutputFileStream()
    {
        outStream.close();
    }

    virtual void write(char* buffer, unsigned int byteCount)
    {
        outStream.write(buffer, byteCount);
    }

    virtual void read(char* buffer, unsigned int byteCount)
    {
        // do nothing
    }
};

class InputFileStream : public Stream
{
private:
    std::string path;
    std::ifstream inStream;

public:
    InputFileStream(std::string path)
    {
        inStream.open(path, std::ios::binary);
    }
    ~InputFileStream()
    {
        inStream.close();
    }

    virtual void write(char* buffer, unsigned int byteCount)
    {
        // do nothing
    }

    virtual void read(char* buffer, unsigned int byteCount)
    {
        inStream.read(buffer, byteCount);
    }
};