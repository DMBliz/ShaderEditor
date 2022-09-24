#include "Generator.h"
#include "Utils.h"

#include <algorithm>


struct Variable
{
    unsigned long id;
    std::string name;

    ValueType type;
};


std::map<unsigned long, std::vector<std::string>> variables;
std::map<unsigned long, std::vector<Variable>> vars;
std::map<std::string, UniformParameter> uniforms;
unsigned long lastVarName = 0;

void replaceAll(std::string& str, const std::string& from, const std::string& to) 
{
    if(from.empty())
        return;

    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) 
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

const Link* getLinkByNodeIn(const Graph& graph, unsigned long nodeInId, unsigned long slotIn)
{
    for (int i = 0; i < graph.links.size(); i++)
    {
        if (graph.links[i].node_in == nodeInId && graph.links[i].slot_in == slotIn)
        {
            return &graph.links[i];
        }
    }
    return nullptr;
}

std::string getTypeStringFromValueType(const ValueType& type)
{
    switch (type)
    {
    case ValueType::FLOAT:
        return "float";
        break;
    case ValueType::VEC2:
        return "vec2";
        break;
    case ValueType::VEC3:
        return "vec3";
        break;
    case ValueType::VEC4:
        return "vec4";
        break;
    case ValueType::SAMPLER2D:
        return "sampler2D";
        break;
    default:
        return "";
        break;
    }
}

std::string wrapValue(std::string value, ValueType type)
{
    switch (type)
    {
    case ValueType::VEC2:
        return "vec2(" + value + ")";
    case ValueType::VEC3:
        return "vec3(" + value + ")";
    case ValueType::VEC4:
        return "vec4(" + value + ")";
    case ValueType::FLOAT:
    default:
        return value;
    }
}

struct InputVariable
{
    int id;
    std::string name;

    bool hasLink;
    ValueType inType;
    std::string inName;

    std::string value;
};

Signature findBestSignature(const std::vector<InputVariable>& inputVars, const std::vector<Signature>& signatures)
{
    int currentBestSignature = 0;
    std::vector<int> currentBestMatch;
    currentBestMatch.resize(inputVars.size());
    for (size_t i = 0; i < currentBestMatch.size(); i++)
    {
        currentBestMatch[i] = static_cast<int>(TypeMatch::NONE);
    }
    
    for (size_t i = 0; i < signatures.size(); i++)
    {
        std::vector<int> currentMatch;
        currentMatch.resize(inputVars.size());
        for (size_t j = 0; j < inputVars.size(); j++)
        {
            currentMatch[j] = static_cast<int>(getTypeMatch(static_cast<int>(inputVars[j].inType), static_cast<int>(signatures[i].inputs[j])));
        }
        
        bool isBetterMatch = true;

        for (size_t j = 0; j < inputVars.size(); j++)
        {
            if (currentMatch[j] == static_cast<int>(TypeMatch::NONE) || currentMatch[j] < currentBestMatch[j])
            {
                isBetterMatch = false;
                break;
            }
        }

        if (isBetterMatch)
        {
            currentBestMatch = currentMatch;
            currentBestSignature = i;
        }
    }
    
    return signatures[currentBestSignature];
}

std::string getCastedValue(std::string value, ValueType castType)
{
    unsigned long needComponents = 0;
    switch (castType)
    {
        case ValueType::FLOAT:
            return Utils::split(value, ",")[0];
        case ValueType::VEC2:
            needComponents = 2;
            break;
        case ValueType::VEC3:
            needComponents = 3;
            break;
        case ValueType::VEC4:
            needComponents = 4;
            break;
    }
    std::vector<std::string> values = Utils::split(value, ",");
    
    int leftComponents = needComponents - values.size();
    int valuesCount = std::min(needComponents, values.size());
    
    std::string ret = "";
    
    for (int i = 0; i < valuesCount; i++)
    {
        ret += values[i] + ",";
    }
    
    for (int i = 0; i < leftComponents; i++)
    {
        ret += "1.0,";
    }
    
    return wrapValue(ret.substr(0, ret.size() - 1), castType);
}

std::string getCastedVariable(InputVariable inVariable, ValueType castType)
{
    if (castType == inVariable.inType)
    {
        if (inVariable.hasLink)
        {
            return inVariable.inName;
        }
        else
        {
            return wrapValue(inVariable.value, castType);
        }
    }
    
    if (!inVariable.hasLink)
    {
        return getCastedValue(inVariable.value, castType);
    }

    if (castType == ValueType::FLOAT)
    {
        switch (inVariable.inType)
        {
        case ValueType::VEC2:
            return inVariable.inName + ".x";
        case ValueType::VEC3:
            return inVariable.inName + ".x";
        case ValueType::VEC4:
            return inVariable.inName + ".x";
        }
    }

    if (castType == ValueType::VEC2)
    {
        switch (inVariable.inType)
        {
        case ValueType::FLOAT:
            return "vec2(" + inVariable.inName + ")";
        case ValueType::VEC3:
        case ValueType::VEC4:
            return "vec2(" + inVariable.inName + ".x, " + inVariable.inName + ".y)";
        }
    }

    if (castType == ValueType::VEC3)
    {
        switch (inVariable.inType)
        {
        case ValueType::FLOAT:
            return "vec3(" + inVariable.inName + ")";
        case ValueType::VEC2:
            return "vec3(" + inVariable.inName + ".x, " + inVariable.inName + ".y, 1.0)";
        case ValueType::VEC4:
            return "vec3(" + inVariable.inName + ".x, " + inVariable.inName + ".y, " + inVariable.inName + ".z)";
        }
    }

    if (castType == ValueType::VEC4)
    {
        switch (inVariable.inType)
        {
        case ValueType::FLOAT:
            return "vec4(" + inVariable.inName + ")";
        case ValueType::VEC2:
            return "vec4(" + inVariable.inName + ".x, " + inVariable.inName + ".y, 1.0, 1.0)";
        case ValueType::VEC3:
            return "vec4(" + inVariable.inName + ".x, " + inVariable.inName + ".y, " + inVariable.inName + ".z, 1.0)";
        }
    }

    return "error";
}

std::string resolveNode(Graph& graph, const Node& node)
{
    if (node.code == "none")
    {
        return "";
    }
    std::string selfCode = node.code;
    std::string code = "";

    std::vector<InputVariable> inVariables;
    for (int i = 0; i < node.input_slots.size(); i++)
    {
        const Link* l = getLinkByNodeIn(graph, node.guid, i);
        if (l == nullptr)
        {
            inVariables.push_back({i, "<in" + std::to_string(i) + ">", false, node.input_slots[i].type, "", node.input_slots[i].value});
            continue;
        }
        const Link& link = *l;
        auto nodeOut = vars.find(link.node_out);
        std::string variable;
        if (nodeOut == vars.end())
        {
            code += resolveNode(graph, graph.nodes[link.node_out]);
            nodeOut = vars.find(link.node_out);
            if (nodeOut != vars.end())
            {
                inVariables.push_back({i, "<in" + std::to_string(i) + ">", true, nodeOut->second[link.slot_out].type, nodeOut->second[link.slot_out].name, ""});
            }
        }
        else
        {
            inVariables.push_back({i, "<in" + std::to_string(i) + ">", true, nodeOut->second[link.slot_out].type, nodeOut->second[link.slot_out].name, ""});
        }
    }

    Signature sig = findBestSignature(inVariables, node.signatures);

    for (size_t i = 0; i < inVariables.size(); i++)
    {
        replaceAll(selfCode, inVariables[i].name, getCastedVariable(inVariables[i], sig.inputs[i]));
    }
    
    for (int i = 0; i < node.output_slots.size(); i++)
    {
        std::string varName = "var" + std::to_string(lastVarName++);
        replaceAll(selfCode, "<out" + std::to_string(i) + ">", getTypeStringFromValueType(sig.outputs[i]) + " " + varName);
        vars[node.guid].push_back({node.guid, varName, sig.outputs[i]});
    }

    return code + selfCode;
}

std::string genHeader(Graph& graph)
{
    std::string code = "#version 330 core\n\n";
    code += "out vec4 fragColor;\n\n";
    for (int i = 0; i < graph.parameters.size(); i++)
    {
        std::string prefix = "";
        if (graph.parameters[i].isVertex)
        {
            prefix = "in ";
        }
        else
        {
            prefix = "uniform ";
            
        }

        if (!graph.parameters[i].isBuiltIn && !graph.parameters[i].isVertex)
        {
            UniformParameter param;
            param.valueType = graph.parameters[i].type;
            switch (param.valueType)
            {
            case ValueType::FLOAT:
                param.floatValue = Utils::getValueFromString<float>(graph.nodes[graph.parameters[i].guid].output_slots[0].value);
                break;
            case ValueType::VEC2:
                param.vec2Value = Utils::getValueFromString<Vec2>(graph.nodes[graph.parameters[i].guid].output_slots[0].value);
                break;
            case ValueType::VEC3:
                param.vec3Value = Utils::getValueFromString<Vec3>(graph.nodes[graph.parameters[i].guid].output_slots[0].value);
                break;
            case ValueType::VEC4:
                param.vec4Value = Utils::getValueFromString<Vec4>(graph.nodes[graph.parameters[i].guid].output_slots[0].value);
                break;
            case ValueType::SAMPLER2D:
                new((void*)&param.textureValue) std::string(graph.nodes[graph.parameters[i].guid].output_slots[0].value);
            break;
            }
            uniforms.emplace(graph.parameters[i].name, param);
        }

        code += prefix + getTypeStringFromValueType(graph.parameters[i].type) + " " + graph.parameters[i].name + ";\n";
        vars[graph.parameters[i].guid].push_back({graph.parameters[i].guid, graph.parameters[i].name, graph.parameters[i].type});
    }

    return code;
}

namespace Generator
{
    GeneratorOutput generateGLSL(Graph& graph)
    {
        lastVarName = 0;
        variables.clear();
        uniforms.clear();
        vars.clear();
        std::string header = genHeader(graph);

        auto node = graph.nodes.find(graph.masterNode);
        if (node == graph.nodes.end())
        {
            return {"", {}};
        }

        const Node& masterNode = graph.nodes[graph.masterNode];
        std::string alg = resolveNode(graph, masterNode);
        replaceAll(alg, "\n", "\n\t");
        alg = "\t" + alg;

        return { header + "\nvoid main()\n{\n" + alg + "\n}\n", uniforms };
    }
}
