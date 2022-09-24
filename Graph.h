#pragma once

#include <string>
#include <vector>
#include <map>
#include "xmath.h"
#include "Serialization.h"


enum class TypeMatch
{
    NONE = 0, DOWNCAST, UPCAST, MATCH,
};

enum class ValueType
{
    FLOAT = 1, VEC2, VEC3, VEC4, SAMPLER2D, INVALID = 0
};

enum class NodeType
{
    DEFAULT, MASTER, PARAMETER
};

struct Signature
{
    std::vector<ValueType> inputs;
    std::vector<ValueType> outputs;
};

struct Slot
{
    unsigned long guid;
    ValueType type{};
    std::string value;
};

struct Node
{
    unsigned long guid;
    std::string name;
    std::string code;
    NodeType type = NodeType::DEFAULT;

    std::vector<Slot> input_slots;
    std::vector<Slot> output_slots;

    std::vector<Signature> signatures;

    Vec2 position;
};

struct Link
{
    unsigned long node_out;
    unsigned long node_in;
    int slot_out{};
    int slot_in{};
};

struct Parameter
{
    unsigned long guid;
    bool isVertex = false;
    bool isBuiltIn = false;
    std::string name;
    ValueType type{};
    std::string default_value;
};

struct Graph
{
    unsigned long masterNode = 0;
    std::map<unsigned long, Node> nodes;
    std::vector<Link> links;
    std::vector<Parameter> parameters;
};


struct UniformParameter
{
    UniformParameter()
    {}

    UniformParameter(const UniformParameter& parameter)
    {
        setValue(parameter);
    }

    ~UniformParameter()
    {}

    UniformParameter& operator=(const UniformParameter& other)
    {
        if (this == &other)
        {
            return *this;
        }

        setValue(other);

        return *this;
    }

    ValueType valueType;
    union
    {
        float floatValue;
        Vec2 vec2Value;
        Vec3 vec3Value;
        Vec4 vec4Value;
        std::string textureValue;
    };

private:
    void setValue(const UniformParameter& other)
    {
        valueType = other.valueType;
        switch(valueType)
        {
        case ValueType::FLOAT:
            floatValue = other.floatValue;
            break;
        case ValueType::VEC2:
            vec2Value = other.vec2Value;
            break;
        case ValueType::VEC3:
            vec3Value = other.vec3Value;
            break;
        case ValueType::VEC4:
            vec4Value = other.vec4Value;
            break;
        case ValueType::SAMPLER2D:
            new((void*)&textureValue) std::string(other.textureValue);
        break;
        }
    }
};



TypeMatch getTypeMatch(int t1, int t2);


Stream& operator<<(Stream& stream, Vec2& vec);

Stream& operator>>(Stream& stream, Vec2& vec);


Stream& operator<<(Stream& stream, Graph& graph);

Stream& operator>>(Stream& stream, Graph& graph);

Stream& operator<<(Stream& stream, Parameter& parameter);

Stream& operator>>(Stream& stream, Parameter& parameter);

Stream& operator<<(Stream& stream, Link& link);

Stream& operator>>(Stream& stream, Link& link);

Stream& operator<<(Stream& stream, Node& node);

Stream& operator>>(Stream& stream, Node& node);

Stream& operator<<(Stream& stream, Slot& slot);

Stream& operator>>(Stream& stream, Slot& slot);
