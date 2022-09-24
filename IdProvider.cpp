#include "IdProvider.h"
#include "Utils.h"


unsigned int nodeId = 1;
unsigned int slotId = 0;
unsigned int parameterId = 0;

std::string parameter = "parameter_";

namespace IdProvider
{
    void reset()
    {
        nodeId = 0;
        slotId = 0;
        parameterId = 0;
    }

    void init(const Graph& graph)
    {
        int largestParameter = 0;
        int largestNode = 0;
        int largestSlot = 0;
        for (size_t i = 0; i < graph.parameters.size(); i++)
        {
            int p = graph.parameters[i].name.find(parameter);
            if (p == 0)
            {
                std::string number = graph.parameters[i].name.substr(parameter.size());
                if (Utils::isNumber(number))
                {
                    int value = std::stoi(number);
                    if (value > largestParameter)
                    {
                        largestParameter = value;
                    }
                }
            }
        }

        for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
        {
            if (it->first > largestNode)
            {
                largestNode = it->first;
            }

            for (int i = 0; i < it->second.input_slots.size(); i++)
            {
                if (it->second.input_slots[i].guid > largestSlot)
                {
                    largestSlot = it->second.input_slots[i].guid;
                }
            }

            for (int i = 0; i < it->second.output_slots.size(); i++)
            {
                if (it->second.output_slots[i].guid > largestSlot)
                {
                    largestSlot = it->second.output_slots[i].guid;
                }
            }
        }

        parameterId = ++largestParameter;
        nodeId = ++largestNode;
        slotId = ++largestSlot;
    }

    unsigned int getNodeId()
    {
        return nodeId++;
    }

    unsigned int getSlotId()
    {
        return slotId++;
    }

    std::string getUniformName()
    {
        return parameter + std::to_string(parameterId++);
    }
}