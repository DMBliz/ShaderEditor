#pragma once

static float DEG_TO_RAD = 0.017453292519943295769236907684886f;
static float PI = 3.141592653589793238f;

class Vec2
{
public:
    float x;
    float y;

    Vec2()
        : x(0), y(0)
    {
    }

    Vec2(float x, float y)
        : x(x), y(y)
    {
    }
};

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3()
        : x(0), y(0), z(0)
    {
    }

    Vec3(float x, float y, float z)
        : x(x), y(y), z(z)
    {
    }
};

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vec4()
        : x(0), y(0), z(0), w(0)
    {
    }

    Vec4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w)
    {
    }
};

struct Texture
{
private:
    int width;
    int height;
    unsigned char* pixels;
    unsigned int id = 0;
public:

    Texture(int width, int height, unsigned char* pixels)
        : width(width), height(height), pixels(pixels)
    {
    }

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }

    const unsigned char* getPixels() const
    {
        return pixels;
    }

    void setId(unsigned int id)
    {
        this->id = id;
    }

    unsigned int getId() const
    {
        return id;
    }
};
