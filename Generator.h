#pragma once

#include <string>
#include <vector>
#include <map>
#include "Graph.h"

namespace Generator
{
    struct GeneratorOutput
    {
        std::string glslCode;
        std::map<std::string, UniformParameter> uniforms;
    };
    GeneratorOutput generateGLSL(Graph& graph);
}
