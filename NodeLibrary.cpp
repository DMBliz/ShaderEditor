#include "NodeLibrary.h"
#include "IdProvider.h"


typedef Node* (*nodeCreation)(void);
typedef std::tuple<Node*, Parameter*> (*parameterCreation)(void);
std::vector<nodeCreation> nodeCreateFuncs;
std::map<std::string, std::map<std::string, unsigned int>> nodes;

std::vector<parameterCreation> parameterCreateFuncs;
std::map<std::string, unsigned int> parameters;

std::map<std::string, unsigned int> simpleParameters;

void applyDefaultSignature(std::vector<Signature>& signatures, int inputs, int outputs)
{
    Signature sig;
    for (size_t i = 0; i < inputs; i++)
    {
        sig.inputs.push_back(ValueType::FLOAT);
    }
    for (size_t i = 0; i < outputs; i++)
    {
        sig.outputs.push_back(ValueType::FLOAT);
    }

    signatures.push_back(sig);
    sig.inputs.clear();
    sig.outputs.clear();

    for (size_t i = 0; i < inputs; i++)
    {
        sig.inputs.push_back(ValueType::VEC2);
    }
    for (size_t i = 0; i < outputs; i++)
    {
        sig.outputs.push_back(ValueType::VEC2);
    }

    signatures.push_back(sig);
    sig.inputs.clear();
    sig.outputs.clear();

    for (size_t i = 0; i < inputs; i++)
    {
        sig.inputs.push_back(ValueType::VEC3);
    }
    for (size_t i = 0; i < outputs; i++)
    {
        sig.outputs.push_back(ValueType::VEC3);
    }

    signatures.push_back(sig);
    sig.inputs.clear();
    sig.outputs.clear();

    for (size_t i = 0; i < inputs; i++)
    {
        sig.inputs.push_back(ValueType::VEC4);
    }
    for (size_t i = 0; i < outputs; i++)
    {
        sig.outputs.push_back(ValueType::VEC4);
    }

    signatures.push_back(sig);
    sig.inputs.clear();
    sig.outputs.clear();
}

Node* createColorOutput()
{
    Node* n = new Node();
    n->name = "Color output";
    n->code = "fragColor = <in0>;\n";
    n->type = NodeType::MASTER;
    Slot inputColor;
    inputColor.guid = IdProvider::getSlotId();
    inputColor.type = ValueType::VEC4;
    inputColor.value = "1.0,1.0,1.0,1.0";
    n->input_slots.push_back(inputColor);

    n->signatures.push_back({{ValueType::VEC4}, {}});

    return n;
}

Node* createMultiply()
{
    Node* n = new Node();
    n->name = "Multiply";
    n->code = "<out0> = <in0> * <in1>;\n";
    Slot inputVec1;
    inputVec1.guid = IdProvider::getSlotId();
    inputVec1.type = ValueType::VEC4;
    inputVec1.value = "1.0,1.0,1.0,1.0";
    Slot inputVec2;
    inputVec2.guid = IdProvider::getSlotId();
    inputVec2.type = ValueType::VEC4;
    inputVec2.value = "1.0,1.0,1.0,1.0";
    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->input_slots.push_back(inputVec1);
    n->input_slots.push_back(inputVec2);
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 2, 1);

    return n;
}

Node* createAdd()
{
    Node* n = new Node();
    n->name = "Add";
    n->code = "<out0> = <in0> + <in1>;\n";
    Slot inputVec1;
    inputVec1.guid = IdProvider::getSlotId();
    inputVec1.type = ValueType::VEC4;
    inputVec1.value = "1.0,1.0,1.0,1.0";
    Slot inputVec2;
    inputVec2.guid = IdProvider::getSlotId();
    inputVec2.type = ValueType::VEC4;
    inputVec2.value = "1.0,1.0,1.0,1.0";
    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->input_slots.push_back(inputVec1);
    n->input_slots.push_back(inputVec2);
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 2, 1);

    return n;
}

Node* createDivide()
{
    Node* n = new Node();
    n->name = "Divide";
    n->code = "<out0> = <in0> / <in1>;\n";
    Slot inputVec1;
    inputVec1.guid = IdProvider::getSlotId();
    inputVec1.type = ValueType::VEC4;
    inputVec1.value = "1.0,1.0,1.0,1.0";
    Slot inputVec2;
    inputVec2.guid = IdProvider::getSlotId();
    inputVec2.type = ValueType::VEC4;
    inputVec2.value = "1.0,1.0,1.0,1.0";
    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->input_slots.push_back(inputVec1);
    n->input_slots.push_back(inputVec2);
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 2, 1);

    return n;
}

Node* createSampler()
{
    Node* n = new Node();
    n->name = "Texture Sampler";
    n->code = "<out0> = texture(<in0>, <in1>);\n";
    Slot inputVec1;
    inputVec1.guid = IdProvider::getSlotId();
    inputVec1.type = ValueType::SAMPLER2D;
    inputVec1.value = "none";
    Slot inputVec2;
    inputVec2.guid = IdProvider::getSlotId();
    inputVec2.type = ValueType::VEC2;
    inputVec2.value = "1.0,1.0";
    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->input_slots.push_back(inputVec1);
    n->input_slots.push_back(inputVec2);
    n->output_slots.push_back(outputVec);

    n->signatures.push_back({{ValueType::SAMPLER2D, ValueType::VEC2}, {ValueType::VEC4}});

    return n;
}

Node* createFloatValue()
{
    Node* n = new Node();
    n->name = "Float value";
    n->code = "<out0> = <in0>;\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::FLOAT;
    inputFloat1.value = "1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputFloat;
    outputFloat.guid = IdProvider::getSlotId();
    outputFloat.type = ValueType::FLOAT;
    outputFloat.value = "1.0";
    n->output_slots.push_back(outputFloat);

    n->signatures.push_back({{ValueType::FLOAT}, {ValueType::FLOAT}});

    return n;
}

Node* createVec2Value()
{
    Node* n = new Node();
    n->name = "Vec2 value";
    n->code = "<out0> = vec2(<in0>, <in1>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::FLOAT;
    inputFloat1.value = "1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::FLOAT;
    inputFloat2.value = "1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC2;
    outputVec.value = "1.0,1.0";
    n->output_slots.push_back(outputVec);

    n->signatures.push_back({{ValueType::FLOAT, ValueType::FLOAT}, {ValueType::VEC2}});

    return n;
}

Node* createVec3Value()
{
    Node* n = new Node();
    n->name = "Vec3 value";
    n->code = "<out0> = vec3(<in0>, <in1>, <in2>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::FLOAT;
    inputFloat1.value = "1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::FLOAT;
    inputFloat2.value = "1.0";
    Slot inputFloat3;
    inputFloat3.guid = IdProvider::getSlotId();
    inputFloat3.type = ValueType::FLOAT;
    inputFloat3.value = "1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);
    n->input_slots.push_back(inputFloat3);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC3;
    outputVec.value = "1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    n->signatures.push_back({{ValueType::FLOAT, ValueType::FLOAT, ValueType::FLOAT}, {ValueType::VEC3}});

    return n;
}

Node* createVec4Value()
{
    Node* n = new Node();
    n->name = "Vec4 value";
    n->code = "<out0> = vec4(<in0>, <in1>, <in2>, <in3>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::FLOAT;
    inputFloat1.value = "1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::FLOAT;
    inputFloat2.value = "1.0";
    Slot inputFloat3;
    inputFloat3.guid = IdProvider::getSlotId();
    inputFloat3.type = ValueType::FLOAT;
    inputFloat3.value = "1.0";
    Slot inputFloat4;
    inputFloat4.guid = IdProvider::getSlotId();
    inputFloat4.type = ValueType::FLOAT;
    inputFloat4.value = "1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);
    n->input_slots.push_back(inputFloat3);
    n->input_slots.push_back(inputFloat4);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    n->signatures.push_back({{ValueType::FLOAT, ValueType::FLOAT, ValueType::FLOAT, ValueType::FLOAT}, {ValueType::VEC4}});

    return n;
}

Node* createSin()
{
    Node* n = new Node();
    n->name = "Sin";
    n->code = "<out0> = sin(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createCos()
{
    Node* n = new Node();
    n->name = "Cos";
    n->code = "<out0> = cos(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createTan()
{
    Node* n = new Node();
    n->name = "Tan";
    n->code = "<out0> = tan(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createAsin()
{
    Node* n = new Node();
    n->name = "Asin";
    n->code = "<out0> = asin(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);
    
    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createAcos()
{
    Node* n = new Node();
    n->name = "Acos";
    n->code = "<out0> = acos(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createAtan()
{
    Node* n = new Node();
    n->name = "Atan";
    n->code = "<out0> = atan(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createPow()
{
    Node* n = new Node();
    n->name = "Pow";
    n->code = "<out0> = pow(<in0>, <in1>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC4;
    inputFloat2.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 2, 1);
    n->signatures.push_back({{ValueType::VEC2, ValueType::FLOAT}, {ValueType::VEC2}});
    n->signatures.push_back({{ValueType::VEC3, ValueType::FLOAT}, {ValueType::VEC3}});
    n->signatures.push_back({{ValueType::VEC4, ValueType::FLOAT}, {ValueType::VEC4}});

    return n;
}

Node* createExp()
{
    Node* n = new Node();
    n->name = "Exp";
    n->code = "<out0> = exp(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createLog()
{
    Node* n = new Node();
    n->name = "Log";
    n->code = "<out0> = log(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createSqrt()
{
    Node* n = new Node();
    n->name = "Sqrt";
    n->code = "<out0> = sqrt(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createAbs()
{
    Node* n = new Node();
    n->name = "Abs";
    n->code = "<out0> = abs(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createSign()
{
    Node* n = new Node();
    n->name = "Sign";
    n->code = "<out0> = sign(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createFloor()
{
    Node* n = new Node();
    n->name = "Floor";
    n->code = "<out0> = floor(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createRound()
{
    Node* n = new Node();
    n->name = "Round";
    n->code = "<out0> = round(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createCeil()
{
    Node* n = new Node();
    n->name = "Ceil";
    n->code = "<out0> = ceil(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

Node* createMin()
{
    Node* n = new Node();
    n->name = "Min";
    n->code = "<out0> = min(<in0>, <in1>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC4;
    inputFloat2.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 2, 1);
    n->signatures.push_back({{ValueType::VEC2, ValueType::FLOAT}, {ValueType::VEC2}});
    n->signatures.push_back({{ValueType::VEC3, ValueType::FLOAT}, {ValueType::VEC3}});
    n->signatures.push_back({{ValueType::VEC4, ValueType::FLOAT}, {ValueType::VEC4}});

    return n;
}

Node* createMax()
{
    Node* n = new Node();
    n->name = "Max";
    n->code = "<out0> = max(<in0>, <in1>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC4;
    inputFloat2.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 2, 1);
    n->signatures.push_back({{ValueType::VEC2, ValueType::FLOAT}, {ValueType::VEC2}});
    n->signatures.push_back({{ValueType::VEC3, ValueType::FLOAT}, {ValueType::VEC3}});
    n->signatures.push_back({{ValueType::VEC4, ValueType::FLOAT}, {ValueType::VEC4}});

    return n;
}

Node* createClamp()
{
    Node* n = new Node();
    n->name = "Clamp";
    n->code = "<out0> = clamp(<in0>, <in1>, <in2>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::FLOAT;
    inputFloat2.value = "1.0";
    Slot inputFloat3;
    inputFloat3.guid = IdProvider::getSlotId();
    inputFloat3.type = ValueType::FLOAT;
    inputFloat3.value = "1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);
    n->input_slots.push_back(inputFloat3);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 3, 1);
    n->signatures.push_back({{ValueType::VEC2, ValueType::FLOAT, ValueType::FLOAT}, {ValueType::VEC2}});
    n->signatures.push_back({{ValueType::VEC3, ValueType::FLOAT, ValueType::FLOAT}, {ValueType::VEC3}});
    n->signatures.push_back({{ValueType::VEC4, ValueType::FLOAT, ValueType::FLOAT}, {ValueType::VEC4}});

    return n;
}

Node* createMix()
{
    Node* n = new Node();
    n->name = "Mix";
    n->code = "<out0> = mix(<in0>, <in1>, <in2>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC4;
    inputFloat2.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat3;
    inputFloat3.guid = IdProvider::getSlotId();
    inputFloat3.type = ValueType::VEC4;
    inputFloat3.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);
    n->input_slots.push_back(inputFloat3);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 3, 1);
    n->signatures.push_back({{ValueType::VEC2, ValueType::VEC2, ValueType::FLOAT}, {ValueType::VEC2}});
    n->signatures.push_back({{ValueType::VEC3, ValueType::VEC3, ValueType::FLOAT}, {ValueType::VEC3}});
    n->signatures.push_back({{ValueType::VEC4, ValueType::VEC4, ValueType::FLOAT}, {ValueType::VEC4}});

    return n;
}

Node* createStep()
{
    Node* n = new Node();
    n->name = "Step";
    n->code = "<out0> = step(<in0>, <in1>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC4;
    inputFloat2.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 2, 1);
    n->signatures.push_back({{ValueType::FLOAT, ValueType::VEC2}, {ValueType::VEC2}});
    n->signatures.push_back({{ValueType::FLOAT, ValueType::VEC3}, {ValueType::VEC3}});
    n->signatures.push_back({{ValueType::FLOAT, ValueType::VEC4}, {ValueType::VEC4}});

    return n;
}

Node* createSmoothStep()
{
    Node* n = new Node();
    n->name = "Smooth step";
    n->code = "<out0> = smoothstep(<in0>, <in1>, <in2>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC4;
    inputFloat2.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat3;
    inputFloat3.guid = IdProvider::getSlotId();
    inputFloat3.type = ValueType::VEC4;
    inputFloat3.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);
    n->input_slots.push_back(inputFloat3);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 3, 1);
    n->signatures.push_back({{ValueType::FLOAT, ValueType::FLOAT, ValueType::VEC2}, {ValueType::VEC2}});
    n->signatures.push_back({{ValueType::FLOAT, ValueType::FLOAT, ValueType::VEC3}, {ValueType::VEC3}});
    n->signatures.push_back({{ValueType::FLOAT, ValueType::FLOAT, ValueType::VEC4}, {ValueType::VEC4}});

    return n;
}

Node* createLength()
{
    Node* n = new Node();
    n->name = "Length";
    n->code = "<out0> = length(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::FLOAT;
    outputVec.value = "1.0";
    n->output_slots.push_back(outputVec);

    n->signatures.push_back({{ValueType::FLOAT}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC2}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC3}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC4}, {ValueType::FLOAT}});

    return n;
}

Node* createDistance()
{
    Node* n = new Node();
    n->name = "Distance";
    n->code = "<out0> = distance(<in0>, <in1>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC4;
    inputFloat2.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    n->signatures.push_back({{ValueType::FLOAT, ValueType::FLOAT}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC2, ValueType::VEC2}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC3, ValueType::VEC3}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC4, ValueType::VEC4}, {ValueType::FLOAT}});

    return n;
}

Node* createDot()
{
    Node* n = new Node();
    n->name = "Dot";
    n->code = "<out0> = dot(<in0>, <in1>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC4;
    inputFloat2.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    n->signatures.push_back({{ValueType::FLOAT, ValueType::FLOAT}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC2, ValueType::VEC2}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC3, ValueType::VEC3}, {ValueType::FLOAT}});
    n->signatures.push_back({{ValueType::VEC4, ValueType::VEC4}, {ValueType::FLOAT}});

    return n;
}

Node* createCross()
{
    Node* n = new Node();
    n->name = "Cross";
    n->code = "<out0> = cross(<in0>, <in1>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC3;
    inputFloat1.value = "1.0,1.0,1.0";
    Slot inputFloat2;
    inputFloat2.guid = IdProvider::getSlotId();
    inputFloat2.type = ValueType::VEC3;
    inputFloat2.value = "1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);
    n->input_slots.push_back(inputFloat2);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC3;
    outputVec.value = "1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    n->signatures.push_back({{ValueType::VEC3, ValueType::VEC3}, {ValueType::VEC3}});

    return n;
}

Node* createNormalize()
{
    Node* n = new Node();
    n->name = "Normalize";
    n->code = "<out0> = normalize(<in0>);\n";
    Slot inputFloat1;
    inputFloat1.guid = IdProvider::getSlotId();
    inputFloat1.type = ValueType::VEC4;
    inputFloat1.value = "1.0,1.0,1.0,1.0";

    n->input_slots.push_back(inputFloat1);

    Slot outputVec;
    outputVec.guid = IdProvider::getSlotId();
    outputVec.type = ValueType::VEC4;
    outputVec.value = "1.0,1.0,1.0,1.0";
    n->output_slots.push_back(outputVec);

    applyDefaultSignature(n->signatures, 1, 1);

    return n;
}

std::tuple<Node*, Parameter*> createUV()
{
    Parameter* param = new Parameter();
    param->default_value = "1.0,1.0";
    param->name = "uv";
    param->type = ValueType::VEC2;
    param->isVertex = true;
    param->isBuiltIn = true;

    Node* n = new Node();
    n->code = "none";
    n->name = "UV";
    n->type = NodeType::PARAMETER;
        
    Slot s;
    s.guid = IdProvider::getSlotId();
    s.type = param->type;
    s.value = param->default_value;
    n->output_slots.push_back(s);
    
    n->signatures.push_back({{}, {ValueType::VEC2}});

    return { n, param };
}

std::tuple<Node*, Parameter*> createTime()
{
    Parameter* param = new Parameter();
    param->default_value = "1.0";
    param->name = "time";
    param->type = ValueType::FLOAT;
    param->isBuiltIn = true;

    Node* n = new Node();
    n->code = "none";
    n->name = "Time";
    n->type = NodeType::PARAMETER;
        
    Slot s;
    s.guid = IdProvider::getSlotId();
    s.type = param->type;
    s.value = param->default_value;
    n->output_slots.push_back(s);
    
    n->signatures.push_back({{}, {ValueType::FLOAT}});

    return { n, param };
}

void addNode(std::string category, std::string name, nodeCreation func)
{
    int size = nodeCreateFuncs.size();
    nodeCreateFuncs.push_back(func);
    nodes[category].emplace(name, size);
}

void addBuiltInParameter(std::string name, parameterCreation func)
{
    parameters.emplace(name, parameterCreateFuncs.size());
    parameterCreateFuncs.push_back(func);
}

namespace NodeLibrary
{
    Node* createNodeForParameter(Parameter param)
    {
        Node* n = new Node();
        n->code = "none";
        n->name = "Parameter";
        n->guid = param.guid;
        n->type = NodeType::PARAMETER;
        
        Slot s;
        s.guid = IdProvider::getSlotId();
        s.type = param.type;
        s.value = param.default_value;
        n->output_slots.push_back(s);
        return n;
    }

    const std::map<std::string, std::map<std::string, unsigned int>>& getLibrary()
    {
        return nodes;
    }

    Node* createNode(unsigned int id)
    {
        return (*nodeCreateFuncs[id])();
    }

    void initNodeLibrary()
    {
        addNode("Output", "Color output", &createColorOutput);
        addNode("Math", "Multiply", &createMultiply);
        addNode("Math", "Add", &createAdd);
        addNode("Math", "Divide", &createDivide);
        addNode("Math", "Sin", &createSin);
        addNode("Math", "Cos", &createCos);
        addNode("Math", "Tan", &createTan);
        addNode("Math", "Asin", &createAsin);
        addNode("Math", "Acos", &createAcos);
        addNode("Math", "Atan", &createAtan);
        addNode("Math", "Pow", &createPow);
        addNode("Math", "Exp", &createExp);
        addNode("Math", "Log", &createLog);
        addNode("Math", "Sqrt", &createSqrt);
        addNode("Math", "Abs", &createAbs);
        addNode("Math", "Sign", &createSign);
        addNode("Math", "Floor", &createFloor);
        addNode("Math", "Round", &createRound);
        addNode("Math", "Ceil", &createCeil);
        addNode("Math", "Min", &createMin);
        addNode("Math", "Max", &createMax);
        addNode("Math", "Clamp", &createClamp);
        addNode("Math", "Mix", &createMix);
        addNode("Math", "Step", &createStep);
        addNode("Math", "Smooth step", &createSmoothStep);
        addNode("Math", "Length", &createLength);
        addNode("Math", "Distance", &createDistance);
        addNode("Math", "Dot", &createDot);
        addNode("Math", "Cross", &createCross);
        addNode("Math", "Normalize", &createNormalize);
        addNode("Textures", "Sampler", &createSampler);
        addNode("Values", "Float value", &createFloatValue);
        addNode("Values", "Vec2 value", &createVec2Value);
        addNode("Values", "Vec3 value", &createVec3Value);
        addNode("Values", "Vec4 value", &createVec4Value);

        addBuiltInParameter("uv", &createUV);
        addBuiltInParameter("Time", &createTime);
        
        simpleParameters["Float"] = 1;
        simpleParameters["Vec2"] = 2;
        simpleParameters["Vec3"] = 3;
        simpleParameters["Vec4"] = 4;
        simpleParameters["Texture"] = 5;
        
    }

    std::tuple<Node*, Parameter*> createBuiltInParameter(unsigned int id)
    {
        return (*parameterCreateFuncs[id])();
    }

    std::map<std::string, unsigned int> getBuiltInParameters()
    {
        return parameters;
    }

    const std::map<std::string, unsigned int>& getParameters()
    {
        return simpleParameters;
    }

    std::tuple<Node*, Parameter*> createParameter(unsigned int id)
    {
        Parameter* param = new Parameter();
        param->type = ValueType::INVALID;
        
        switch (id)
        {
            case 1:
                param->default_value = "1.0";
                param->isVertex = false;
                param->name = IdProvider::getUniformName();
                param->type = ValueType::FLOAT;
            break;
            case 2:
                param->default_value = "1.0,1.0";
                param->isVertex = false;
                param->name = IdProvider::getUniformName();
                param->type = ValueType::VEC2;
            break;
            case 3:
                param->default_value = "1.0,1.0,1.0";
                param->isVertex = false;
                param->name = IdProvider::getUniformName();
                param->type = ValueType::VEC3;
            break;
            case 4:
                param->default_value = "1.0,1.0,1.0,1.0";
                param->isVertex = false;
                param->name = IdProvider::getUniformName();
                param->type = ValueType::VEC4;
            break;
            case 5:
                param->default_value = "none";
                param->isVertex = false;
                param->name = IdProvider::getUniformName();
                param->type = ValueType::SAMPLER2D;
            break;
        }
        
        if (param->type != ValueType::INVALID)
        {
            Node* n = new Node();
            n->code = "none";
            n->name = "Parameter";
            n->type = NodeType::PARAMETER;
            
            Slot s;
            s.guid = IdProvider::getSlotId();
            s.type = param->type;
            s.value = param->default_value;
            n->output_slots.push_back(s);
            n->signatures.push_back({{}, {param->type}});
            
            return { n, param };
        }
        
        return { nullptr, nullptr };
    }
}
