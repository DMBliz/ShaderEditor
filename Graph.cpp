#include "Graph.h"

#include "Serialization.h"

TypeMatch getTypeMatch(int t1, int t2)
{
    if (t1 == t2)
    {
        return TypeMatch::MATCH;
    }
    
    if (t1 == static_cast<int>(ValueType::SAMPLER2D) || t2 == static_cast<int>(ValueType::SAMPLER2D))
    {
        return TypeMatch::NONE;
    }

    if (t2 < t1)
    {
        return TypeMatch::DOWNCAST;
    }

    if (t1 == static_cast<int>(ValueType::FLOAT))
    {
        return TypeMatch::UPCAST;
    }

    return TypeMatch::NONE;
}

Stream& operator<<(Stream& stream, Vec2& vec)
{
    stream << vec.x;
    stream << vec.y;

    return stream;
}

Stream& operator>>(Stream& stream, Vec2& vec)
{
    stream >> vec.x;
    stream >> vec.y;

    return stream;
}


Stream& operator<<(Stream& stream, Graph& graph)
{
    stream << graph.masterNode;
    stream << graph.nodes;
    stream << graph.links;
    stream << graph.parameters;

    return stream;
}

Stream& operator>>(Stream& stream, Graph& graph)
{
    stream >> graph.masterNode;
    stream >> graph.nodes;
    stream >> graph.links;
    stream >> graph.parameters;

    return stream;
}

Stream& operator<<(Stream& stream, Parameter& parameter)
{
    stream << parameter.guid;
    stream << parameter.isVertex;
    stream << parameter.isBuiltIn;
    stream << parameter.name;
    stream << static_cast<int>(parameter.type);
    stream << parameter.default_value;

    return stream;
}

Stream& operator>>(Stream& stream, Parameter& parameter)
{
    int paramType;
    stream >> parameter.guid;
    stream >> parameter.isVertex;
    stream >> parameter.isBuiltIn;
    stream >> parameter.name;
    stream >> paramType;
    stream >> parameter.default_value;
    parameter.type = static_cast<ValueType>(paramType);
    return stream;
}

Stream& operator<<(Stream& stream, Link& link)
{
    stream << link.node_out;
    stream << link.node_in;
    stream << link.slot_out;
    stream << link.slot_in;

    return stream;
}

Stream& operator>>(Stream& stream, Link& link)
{
    stream >> link.node_out;
    stream >> link.node_in;
    stream >> link.slot_out;
    stream >> link.slot_in;

    return stream;
}

Stream& operator<<(Stream& stream, Node& node)
{
    stream << node.guid;
    stream << node.name;
    stream << node.code;
    stream << static_cast<int>(node.type);
    stream << node.input_slots;
    stream << node.output_slots;
    stream << node.position;
    stream << node.signatures;

    return stream;
}

Stream& operator>>(Stream& stream, Node& node)
{
    int nodeType;
    stream >> node.guid;
    stream >> node.name;
    stream >> node.code;
    stream >> nodeType;
    stream >> node.input_slots;
    stream >> node.output_slots;
    stream >> node.position;
    stream >> node.signatures;

    node.type = static_cast<NodeType>(nodeType);

    return stream;
}

Stream& operator<<(Stream& stream, Slot& slot)
{
    stream << slot.guid;
    stream << static_cast<int>(slot.type);
    stream << slot.value;

    return stream;
}

Stream& operator>>(Stream& stream, Slot& slot)
{
    int slotType;
    stream >> slot.guid;
    stream >> slotType;
    stream >> slot.value;

    slot.type = static_cast<ValueType>(slotType);

    return stream;
}

Stream& operator<<(Stream& stream, ValueType& valueType)
{
    stream << static_cast<int>(valueType);

    return stream;
}

Stream& operator>>(Stream& stream, ValueType& valueType)
{
    int vt;
    stream >> vt;
    valueType = static_cast<ValueType>(vt);

    return stream;
}

Stream& operator<<(Stream& stream, Signature& signature)
{
    stream << signature.inputs;
    stream << signature.outputs;

    return stream;
}

Stream& operator>>(Stream& stream, Signature& signature)
{
    stream >> signature.inputs;
    stream >> signature.outputs;

    return stream;
}
