#pragma once

#include <map>
#include <string>
#include <tuple>
#include "Graph.h"

namespace NodeLibrary
{
    Node* createNodeForParameter(Parameter param);
    const std::map<std::string, std::map<std::string, unsigned int>>& getLibrary();
    Node* createNode(unsigned int id);
    void initNodeLibrary();

    std::tuple<Node*, Parameter*> createBuiltInParameter(unsigned int);
    std::map<std::string, unsigned int> getBuiltInParameters();

    const std::map<std::string, unsigned int>& getParameters();
    std::tuple<Node*, Parameter*> createParameter(unsigned int id);
}
