#include "Utils.h"

#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <filesystem>
#include "nfd.h"

Texture* folderIconCache = nullptr;

namespace Utils
{
    std::vector<std::string> split(std::string str, std::string separator)
    {
        std::string strCopy = str;

        std::vector<std::string> ret{};

        int position;

        std::string token;

        while ((position = strCopy.find(separator)) != std::string::npos) 
        {
            token = strCopy.substr(0, position);
            //Remove the extra space from the front of the splitted string
            ret.push_back(token.erase(0, token.find_first_not_of(" ")));
            strCopy.erase(0, position + separator.length());
        }
        ret.push_back(strCopy);
        
        return ret;
    }

    Texture* createTexture(const unsigned char* data, unsigned int size)
    {
        int width, height, chanels;
        
        unsigned char* pixels = stbi_load_from_memory(data, size, &width, &height, &chanels, 4);

        return new Texture(width, height, pixels);
    }

    Texture* loadImage(std::string path)
    {
        std::ifstream file(path, std::ios::binary);
        std::vector<unsigned char> bytes(
            (std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));

        file.close();

        return createTexture(bytes.data(), bytes.size());
    }

    Texture* getFolderIcon()
    {
        if (folderIconCache != nullptr)
        {
            return folderIconCache;
        }

        static const unsigned char folderIconData[] = {
            0x89, 0x50, 0x4e, 0x47, 0xd, 0xa, 0x1a, 0xa, 0x0, 0x0, 
            0x0, 0xd, 0x49, 0x48, 0x44, 0x52, 0x0, 0x0, 0x0, 0x30, 
            0x0, 0x0, 0x0, 0x30, 0x8, 0x6, 0x0, 0x0, 0x0, 0x57, 0x2, 
            0xf9, 0x87, 0x0, 0x0, 0x0, 0x6, 0x62, 0x4b, 0x47, 0x44, 
            0x0, 0xff, 0x0, 0xff, 0x0, 0xff, 0xa0, 0xbd, 0xa7, 
            0x93, 0x0, 0x0, 0x1, 0x4e, 0x49, 0x44, 0x41, 0x54, 
            0x68, 0x81, 0xed, 0x98, 0x3d, 0x4a, 0xc4, 0x40, 0x18, 
            0x86, 0x1f, 0x5c, 0xb, 0x13, 0xd8, 0xd2, 0xce, 0xc6, 
            0xde, 0x56, 0xb0, 0x50, 0xbc, 0xc0, 0x5e, 0x62, 0x1b, 
            0x6f, 0xa1, 0xe2, 0xd6, 0xde, 0xc0, 0x56, 0x6f, 0xe0, 
            0x5, 0x4, 0x45, 0xab, 0x6d, 0xb6, 0xdc, 0x65, 0xb1, 
            0xde, 0x52, 0xb0, 0x10, 0xb2, 0x68, 0x31, 0x19, 0xc8, 
            0x4e, 0xc6, 0x75, 0x32, 0x99, 0x9f, 0xc2, 0xef, 0x81, 
            0xb7, 0x9, 0xe1, 0xcb, 0xf3, 0x66, 0x12, 0x42, 0x6, 0x4, 
            0x41, 0x10, 0x4, 0xa1, 0x4d, 0x9, 0x4c, 0x80, 0x5, 0x50, 
            0x1, 0xdf, 0x5b, 0xf2, 0x9, 0xbc, 0x1, 0x17, 0xc0, 0x20, 
            0x87, 0xac, 0x49, 0x9, 0xbc, 0xb2, 0x5d, 0xfa, 0xb7, 0x3c, 
            0x1, 0xfb, 0xe9, 0x95, 0x37, 0x99, 0xe0, 0x27, 0xaf, 0xb3, 
            0x4, 0x8e, 0x92, 0x5b, 0x37, 0x58, 0x58, 0xa4, 0xba, 0xe6, 
            0x3, 0x18, 0xa5, 0x16, 0xd7, 0xfc, 0xf5, 0xcc, 0xbb, 0xa6, 
            0x2, 0x8e, 0x13, 0xbb, 0x83, 0xa7, 0xac, 0x99, 0x2f, 0x60, 
            0x6c, 0xcc, 0x3d, 0x4, 0x66, 0x1d, 0xe7, 0x54, 0xa8, 0x27, 
            0xe2, 0x6, 0x28, 0x52, 0x15, 0x58, 0x1, 0x67, 0xc6, 0xcc, 
            0xd3, 0xfa, 0x78, 0x9f, 0xb9, 0x2f, 0xae, 0x25, 0xfa, 0x5c, 
            0x64, 0x86, 0xba, 0xd3, 0x4d, 0xc6, 0xa8, 0x15, 0x9, 0xb1, 
            0xb2, 0xd7, 0x31, 0xb, 0x3c, 0x2, 0xc3, 0xc6, 0x9c, 0x1, 0x70, 
            0x1b, 0x48, 0x5c, 0x67, 0x1e, 0xa3, 0xc0, 0xa, 0xb8, 0x64, 0xf3, 
            0x23, 0x36, 0xac, 0xb, 0x85, 0x94, 0xd7, 0xef, 0x44, 0x74, 0xe, 
            0x80, 0x69, 0x4, 0x79, 0x9d, 0xa8, 0x9c, 0xd3, 0xff, 0x65, 0x4d, 
            0x5e, 0xa0, 0x4, 0x4e, 0x80, 0x3b, 0x60, 0x1d, 0x59, 0xbe, 0x55, 
            0x60, 0xd7, 0x22, 0x14, 0x7d, 0x99, 0x42, 0xb2, 0x93, 0x5b, 0xa0, 
            0x2f, 0x52, 0x20, 0x37, 0x52, 0x20, 0x37, 0x52, 0x20, 0x37, 0x52, 
            0x20, 0x37, 0x52, 0x20, 0x37, 0x52, 0x20, 0x37, 0xb6, 0x2, 0xeb, 
            0xe4, 0x16, 0xee, 0xb4, 0xdc, 0x6c, 0x5, 0xde, 0x13, 0x88, 0xf8, 
            0xb2, 0x34, 0xf, 0xd8, 0xa, 0x3c, 0x24, 0x10, 0xf1, 0xe5, 0xde, 
            0xe5, 0xa4, 0x2, 0xb5, 0x7, 0x13, 0xfb, 0xcf, 0xaa, 0x6b, 0x9e, 
            0x81, 0x3d, 0xd7, 0xa6, 0x5, 0x6a, 0xf, 0x66, 0x4e, 0xb8, 0xad, 
            0x46, 0x9f, 0x54, 0xb5, 0xc3, 0x55, 0x17, 0x79, 0x41, 0x10, 0x4, 
            0xe1, 0xff, 0xf0, 0x3, 0xf2, 0x55, 0x91, 0xfe, 0xd4, 0x22, 0x60, 
            0xa6, 0x0, 0x0, 0x0, 0x0, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

        folderIconCache = createTexture(folderIconData, sizeof(folderIconData) / sizeof(folderIconData[0]));

        return folderIconCache;
    }

    std::string showFileDialog()
    {
        char* path = NULL;
        nfdresult_t res = NFD_OpenDialog(NULL, NULL, &path);

        if (res == NFD_OKAY)
        {
            return std::string(path);
        }
        else if (res == NFD_CANCEL)
        {
            return "canceled";
        }
        
        return "failed";
    }

    std::string showSaveFileDialog()
    {
        char* path = NULL;
        nfdresult_t res = NFD_SaveDialog(NULL, NULL, &path);

        if (res == NFD_OKAY)
        {
            return std::string(path);
        }
        else if (res == NFD_CANCEL)
        {
            return "canceled";
        }
        
        return "failed";
    }

    bool isNumber(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), 
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }

    std::string getFileName(const std::string& path)
    {
        return path.substr(path.find_last_of("/\\") + 1);
    }

    std::string getFolderPath(const std::string& path)
    {
        int id = path.find_last_of("/\\");
        if (id == path.size())
        {
            return path;
        }

        return path.substr(0, id);
    }

    std::string getSystemSeparator()
    {
#ifdef _WIN32
        return "\\";
#else
        return "/";
#endif
    }

    void copyFile(std::string from, std::string to)
    {
        if (from == to)
        {
            return;
        }
        std::filesystem::create_directories(getFolderPath(to));
        std::filesystem::copy(from, to, std::filesystem::copy_options::update_existing);
    }

    std::string fixSeparator(std::string path)
    {
        if (getSystemSeparator() == std::string("/"))
        {
            std::replace(path.begin(), path.end(), '\\', '/');
        }
        if (getSystemSeparator() == std::string("\\"))
        {
            std::replace(path.begin(), path.end(), '/', '\\');
        }

        return path;
    }

    bool isRelativePath(std::string path)
    {
        if (path.empty())
        {
            return false;
        }

        if (path[0] == '/')
        {
            return false;
        }

        if (path.size() > 1 && path[1] == ':')
        {
            return false;
        }

        return true;
    }

    template<>
    float getValueFromString(std::string value)
    {
        return std::stof(value);
    }

    template<>
    Vec2 getValueFromString(std::string value)
    {
        Vec2 ret;
        std::vector<std::string> values = Utils::split(value, ",");
        ret.x = std::stof(values[0]);
        ret.y = std::stof(values[1]);
        return ret;
    }

    template<>
    Vec3 getValueFromString(std::string value)
    {
        Vec3 ret;
        std::vector<std::string> values = Utils::split(value, ",");
        ret.x = std::stof(values[0]);
        ret.y = std::stof(values[1]);
        ret.z = std::stof(values[2]);
        return ret;
    }

    template<>
    Vec4 getValueFromString(std::string value)
    {
        Vec4 ret;
        std::vector<std::string> values = Utils::split(value, ",");
        ret.x = std::stof(values[0]);
        ret.y = std::stof(values[1]);
        ret.z = std::stof(values[2]);
        ret.w = std::stof(values[3]);
        return ret;
    }

    std::string valueToString(float value)
    {
        return std::to_string(value);
    }

    std::string valueToString(Vec2 value)
    {
        return std::to_string(value.x) + "," + std::to_string(value.y);
    }

    std::string valueToString(Vec3 value)
    {
        return std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z);
    }

    std::string valueToString(Vec4 value)
    {
        return std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + "," + std::to_string(value.w);
    }

}
