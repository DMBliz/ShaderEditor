#pragma once

#include <vector>
#include <string>

#include "xmath.h"

namespace Utils
{
    std::vector<std::string> split(std::string str, std::string separator);

    Texture* loadImage(std::string path);

    Texture* getFolderIcon();

    std::string showFileDialog();
    std::string showSaveFileDialog();

    bool isNumber(const std::string& s);

    std::string getFileName(const std::string& path);
    std::string getFolderPath(const std::string& path);

    std::string getSystemSeparator();

    void copyFile(std::string from, std::string to);

    std::string fixSeparator(std::string path);

    bool isRelativePath(std::string path);

    template<typename T>
    T getValueFromString(std::string value)
    {
        return 0;
    }

    template<>
    float getValueFromString(std::string value);

    template<>
    Vec2 getValueFromString(std::string value);

    template<>
    Vec3 getValueFromString(std::string value);

    template<>
    Vec4 getValueFromString(std::string value);

    std::string valueToString(float value);

    std::string valueToString(Vec2 value);

    std::string valueToString(Vec3 value);

    std::string valueToString(Vec4 value);
}
