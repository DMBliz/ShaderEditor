#pragma once

#include "Graph.h"

namespace IdProvider
{
    void reset();
    void init(const Graph& graph);

    unsigned int getNodeId();
    unsigned int getSlotId();

    std::string getUniformName();
}