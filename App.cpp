#include "App.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <imnodes.h>
#include <type_traits>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>

#include "NodeLibrary.h"
#include "Generator.h"
#include "Render.h"
#include "FileSerialization.h"
#include "IdProvider.h"
#include "Utils.h"

Vec2 cameraScale;
Vec2 previewSize = Vec2(300, 300);
Graph graph;
std::vector<std::string> textures;
bool isPreviewFocused = false;

float rotation = 0;
float rotation2 = 0;
bool isMousePressed = false;
Vec2 lastMousePosition = Vec2(0, 0);

bool needPreviewUpdate = false;

std::string currentCode = "";
bool needCopyCode = false;

char* inputTextBuffer = new char[64];

std::map<unsigned long, Signature> nodeSigntures;

void configDock()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    bool showDock = true;
    ImGui::Begin("MainDockspace", &showDock, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    if (ImGui::DockBuilderGetNode(ImGui::GetID("MainDockspace")) == NULL)
	{
		ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
		ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add empty node
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

		ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
		ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
        ImGuiID dock_id_left_down = ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.50f, NULL, &dock_id_left);

		ImGui::DockBuilderDockWindow("NodeEditor", dock_main_id);
		ImGui::DockBuilderDockWindow("Preview", dock_id_left);
        ImGui::DockBuilderDockWindow("Code", dock_id_left_down);
		ImGui::DockBuilderFinish(dockspace_id);
	}
    ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), 0);
    ImGui::End();
}

Parameter* getParameterByNode(Graph& graph, const Node& node)
{
    for (int i = 0; i < graph.parameters.size(); i++)
    {
        if (graph.parameters[i].guid == node.guid)
        {
            return &graph.parameters[i];
        }
    }

    return nullptr;
}

void drawTextByType(ValueType type, bool alignRight = false, int width = 0)
{
    std::string text = "";
    switch (type)
    {
        case ValueType::FLOAT:
            text = "float";
            break;
        case ValueType::VEC2:
            text = "Vec2";
            break;
        case ValueType::VEC3:
            text = "Vec3";
            break;
        case ValueType::VEC4:
            text = "Vec4";
            break;
        case ValueType::SAMPLER2D:
            text = "Sampler";
            break;
    }
    
    if (alignRight)
    {
        int textWidth = ImGui::CalcTextSize(text.c_str()).x;
        ImGui::Indent(width - textWidth);
    }
    ImGui::Text(text.c_str());
}

int getLinkId(Graph& graph, const Node& node, unsigned int slotID, bool isInput)
{
    for (int i = 0; i < graph.links.size(); i++)
    {
        Link& l = graph.links[i];
        if (l.node_in == node.guid && l.slot_in == slotID && isInput)
        {
            return i;
        }
        if (l.node_out == node.guid && l.slot_out == slotID && !isInput)
        {
            return i;
        }
    }
    return -1;
}

bool drawSlot(Slot& s, ValueType type)
{
    bool isValueChanged = false;
    switch (type)
    {
    case ValueType::FLOAT:
    {
        float v = Utils::getValueFromString<float>(s.value);
        bool changed = ImGui::DragFloat("##x", &v, 0.1f);
        if (changed)
        {
            s.value = Utils::valueToString(v);
            isValueChanged = true;
        }
        break;
    }
    case ValueType::VEC2:
    {
        Vec2 v = Utils::getValueFromString<Vec2>(s.value);
        bool changed = ImGui::DragFloat("##x", &v.x, 0.1f);
        changed |= ImGui::DragFloat("##y", &v.y, 0.1f);
        if (changed)
        {
            s.value = Utils::valueToString(v);
            isValueChanged = true;
        }
        break;
    }
    case ValueType::VEC3:
    {
        Vec3 v = Utils::getValueFromString<Vec3>(s.value);
        bool changed = ImGui::DragFloat("##x", &v.x, 0.1f);
        changed |= ImGui::DragFloat("##y", &v.y, 0.1f);
        changed |= ImGui::DragFloat("##z", &v.z, 0.1f);
        if (changed)
        {
            s.value = Utils::valueToString(v);
            isValueChanged = true;
        }
        break;
    }
    case ValueType::VEC4:
    {
        Vec4 v = Utils::getValueFromString<Vec4>(s.value);
        bool changed = ImGui::DragFloat("##x", &v.x, 0.1f);
        changed |= ImGui::DragFloat("##y", &v.y, 0.1f);
        changed |= ImGui::DragFloat("##z", &v.z, 0.1f);
        changed |= ImGui::DragFloat("##w", &v.w, 0.1f);
        if (changed)
        {
            s.value = Utils::valueToString(v);
            isValueChanged = true;
        }
        break;
    }
    case ValueType::SAMPLER2D:
    {
        drawTextByType(s.type);
    }
    default:
        break;
    }

    return isValueChanged;
}

Signature getBestSignatureForNode(const std::vector<Signature>& signatures, const std::vector<ValueType>& currentInputs)
{
    int currentBestSignature = 0;
    std::vector<int> currentBestMatch;
    currentBestMatch.resize(currentInputs.size());
    for (size_t i = 0; i < currentBestMatch.size(); i++)
    {
        currentBestMatch[i] = static_cast<int>(TypeMatch::NONE);
    }
    
    for (size_t i = 0; i < signatures.size(); i++)
    {
        std::vector<int> currentMatch;
        currentMatch.resize(currentInputs.size());
        for (size_t j = 0; j < currentInputs.size(); j++)
        {
            currentMatch[j] = static_cast<int>(getTypeMatch(static_cast<int>(currentInputs[j]), static_cast<int>(signatures[i].inputs[j])));
        }
        
        bool isBetterMatch = true;

        for (size_t j = 0; j < currentInputs.size(); j++)
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

Signature resolveNodeSignature(Graph& graph, const Node& node)
{
    auto nodeFind = nodeSigntures.find(node.guid);
    if (nodeFind != nodeSigntures.end())
    {
        return nodeFind->second;
    }
    std::vector<ValueType> inputTypes;
    for (unsigned long i = 0; i < node.input_slots.size(); i++)
    {
        int linkId = getLinkId(graph, node, i, true);
        if (linkId == -1)
        {
            inputTypes.push_back(node.input_slots[i].type);
        }
        else
        {
            const Link& l = graph.links[linkId];
            inputTypes.push_back(resolveNodeSignature(graph, graph.nodes[l.node_out]).outputs[l.slot_out]);
        }
    }
    Signature sig = getBestSignatureForNode(node.signatures, inputTypes);
    nodeSigntures[node.guid] = sig;
    return sig;
}

void updateSignaturesForNodes(Graph& graph)
{
    nodeSigntures.clear();
    
    for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
    {
        resolveNodeSignature(graph, it->second);
    }
}

void fixNodeValue(Node& node, bool isInput)
{
    const Signature& sig = nodeSigntures[node.guid];
    
    if (isInput)
    {
        for (int i = 0; i < node.input_slots.size(); i++)
        {
            if (node.input_slots[i].type != sig.inputs[i])
            {
                int count = Utils::split(node.input_slots[i].value, ",").size();
                int componentsDiff = static_cast<int>(node.input_slots[i].type) - count;
                for (int j = 0; j < componentsDiff; j++)
                {
                    node.input_slots[i].value += ",1.0";
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < node.output_slots.size(); i++)
        {
            if (node.output_slots[i].type != sig.outputs[i])
            {
                int count = Utils::split(node.output_slots[i].value, ",").size();
                int componentsDiff = static_cast<int>(node.output_slots[i].type) - count;
                for (int j = 0; j < componentsDiff; j++)
                {
                    node.output_slots[i].value += "1.0,";
                }
            }
        }
    }
}

void fixLink(Graph& graph, unsigned long linkId)
{
    Link& l = graph.links[linkId];
    fixNodeValue(graph.nodes[l.node_in], true);
    fixNodeValue(graph.nodes[l.node_out], false);
}


void drawSlotsForNode(Graph& graph, Node& node)
{
    ImNodes::BeginNode(node.guid);
    ImVec2 pos = ImNodes::GetNodeGridSpacePos(node.guid);
    node.position.x = pos.x;
    node.position.y = pos.y;
    
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(node.name.c_str());
    ImNodes::EndNodeTitleBar();
    
    const Signature& sig = nodeSigntures[node.guid];

    for (int i = 0; i < node.input_slots.size(); i++)
    {
        Slot& s = node.input_slots[i];
        ImNodes::BeginInputAttribute(s.guid, ImNodesPinShape_Circle);
        
        ImGui::PushItemWidth(100);
        if (getLinkId(graph, node, i, true) == -1)
        {
            if (drawSlot(s, sig.inputs[i]))
            {
                needPreviewUpdate = true;
            }
        }
        else
        {
            drawTextByType(sig.inputs[i]);
        }
        ImGui::PopItemWidth();

        ImNodes::EndInputAttribute();
        ImGui::Spacing();
    }

    for (int i = 0; i < node.output_slots.size(); i++)
    {
        Slot& s = node.output_slots[i];
        
        ImGui::PushItemWidth(100);
        if (node.type == NodeType::PARAMETER)
        {
            Parameter* param = getParameterByNode(graph, node);

            if (param != nullptr && (!param->isBuiltIn) && (!param->isVertex))
            {
                memset(inputTextBuffer, 0, sizeof(inputTextBuffer));
                strcpy(inputTextBuffer, param->name.c_str());
                if (ImGui::InputText("name", inputTextBuffer, 64, ImGuiInputTextFlags_CharsNoBlank))
                {
                    param->name = inputTextBuffer;
                    needPreviewUpdate = true;
                }
            }

            if (node.output_slots[i].type == ValueType::SAMPLER2D)
            {
                unsigned int tex = Render::getTexture(s.value);
                ImGui::Image((ImTextureID)tex, ImVec2(90, 90));
                ImGui::Text(s.value.c_str());
                ImGui::SameLine();
                if (ImGui::ImageButton((ImTextureID)Render::getFolderIcon(), ImVec2(ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight())))
                {
                    std::string str = Utils::showFileDialog();
                    if (str != "canceled" && str != "failed")
                    {
                        Render::getTexture(str);
                        textures.push_back(str);
                        s.value = str;
                    }
                }
            }
            else
            {
                if (param != nullptr && (!param->isBuiltIn) && (!param->isVertex))
                {
                    if (drawSlot(s, sig.outputs[i]))
                    {
                        needPreviewUpdate = true;
                    }
                }
            }
        }
        
        ImNodes::BeginOutputAttribute(s.guid, ImNodesPinShape_Circle);
        ImGui::Dummy(ImVec2(50, 0));
        drawTextByType(sig.outputs[i], true, ImNodes::GetNodeDimensions(node.guid).x - 16);
        ImNodes::EndOutputAttribute();
        ImGui::PopItemWidth();
    }

    ImNodes::EndNode();
}

unsigned long getNodeBySlot(const Graph& graph, unsigned long slotId)
{
    for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
    {
        auto inputSlots = it->second.input_slots;
        auto outputSlots = it->second.output_slots;

        for (int i = 0; i < inputSlots.size(); i++)
        {
            if (inputSlots[i].guid == slotId)
            {
                return it->first;
            }
        }

        for (int i = 0; i < outputSlots.size(); i++)
        {
            if (outputSlots[i].guid == slotId)
            {
                return it->first;
            }
        }
    }

    return -1;
}

int getSlotIndexInNodeByGUID(const Node& node, const unsigned long slotGUID)
{
    for (int i = 0; i < node.input_slots.size(); i++)
    {
        if (node.input_slots[i].guid == slotGUID)
        {
            return i;
        }
    }

    for (int i = 0; i < node.output_slots.size(); i++)
    {
        if (node.output_slots[i].guid == slotGUID)
        {
            return i;
        }
    }

    return -1;
}

void deleteLinksWithNode(Graph& graph, unsigned long node)
{
    int id = 0;
    auto it = graph.links.begin();
    while(it != graph.links.end())
    {
        if (it->node_in == node || it->node_out == node)
        {
            fixLink(graph, id);
            it = graph.links.erase(it);
        }
        else
        {
            it++;
        }
        id++;
    }
}

void drawNodePopup(Graph& graph)
{
    const ImVec2 mousePos = ImGui::GetMousePosOnOpeningCurrentPopup();
    auto library = NodeLibrary::getLibrary();
    for (auto cat = library.begin(); cat != library.end(); ++cat)
    {
        if (ImGui::BeginMenu(cat->first.c_str()))
        {
            auto nodes = cat->second;

            for (auto it = nodes.begin(); it != nodes.end(); ++it)
            {
                if (ImGui::MenuItem(it->first.c_str()))
                {
                    Node* n = NodeLibrary::createNode(it->second);
                    if (n->type == NodeType::MASTER)
                    {
                        if (graph.masterNode != 0)
                        {
                            graph.nodes.erase(graph.masterNode);
                            n->guid = graph.masterNode;
                        }
                    }
                    else
                    {
                        n->guid = IdProvider::getNodeId();
                    }
                    ImNodes::SetNodeScreenSpacePos(n->guid, mousePos);
                    ImVec2 pos = ImNodes::GetNodeGridSpacePos(n->guid);
                    n->position = Vec2(pos.x, pos.y);
                    
                    graph.nodes.emplace(n->guid, *n);
                    delete n;
                    needPreviewUpdate = true;
                }
            }
            ImGui::EndMenu();
        }
    }

    if (ImGui::BeginMenu("Builtin parameters"))
    {
        auto params = NodeLibrary::getBuiltInParameters();
        for (auto param = params.begin(); param != params.end(); ++param)
        {
            if (ImGui::MenuItem(param->first.c_str()))
            {
                std::tuple<Node*, Parameter*> ret = NodeLibrary::createBuiltInParameter(param->second);
                Node* n = std::get<0>(ret);
                Parameter* param = std::get<1>(ret);
                n->guid = IdProvider::getNodeId();
                param->guid = n->guid;
                graph.parameters.push_back(*param);
                graph.nodes[n->guid] = *n;

                ImNodes::SetNodeScreenSpacePos(n->guid, mousePos);
                ImVec2 pos = ImNodes::GetNodeGridSpacePos(n->guid);
                n->position = Vec2(pos.x, pos.y);

                delete n;
                delete param;

                needPreviewUpdate = true;
            }
        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Add parameter"))
    {
        const std::map<std::string, unsigned int> params = NodeLibrary::getParameters();
        for (auto param = params.begin(); param != params.end(); ++param)
        {
            if (ImGui::MenuItem(param->first.c_str()))
            {
                std::tuple<Node *, Parameter *> ret = NodeLibrary::createParameter(param->second);
                Node* n = std::get<0>(ret);
                Parameter* param = std::get<1>(ret);
                n->guid = IdProvider::getNodeId();
                param->guid = n->guid;
                graph.parameters.push_back(*param);
                graph.nodes[n->guid] = *n;
                
                ImNodes::SetNodeScreenSpacePos(n->guid, mousePos);
                ImVec2 pos = ImNodes::GetNodeGridSpacePos(n->guid);
                n->position = Vec2(pos.x, pos.y);

                delete n;
                delete param;

                needPreviewUpdate = true;
            }
        }
        ImGui::EndMenu();
    }
}

void drawNodeEditor(Graph& graph)
{
    ImGui::Begin("NodeEditor", nullptr, ImGuiWindowFlags_NoDecoration);
    ImNodes::BeginNodeEditor();
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && ImGui::IsMouseReleased(1))
    {
        ImGui::OpenPopup("Node list");
    }

    if (ImGui::BeginPopup("Node list"))
    {
        drawNodePopup(graph);
        ImGui::EndPopup();
    }
    
    if (needPreviewUpdate)
    {
        updateSignaturesForNodes(graph);
    }

    for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
    {
        Node& n = it->second;
        drawSlotsForNode(graph, n);
    }

    for (int i = 0; i < graph.links.size(); i++)
    {
        Link& l = graph.links[i];
        Node& inNode = graph.nodes[l.node_in];
        Node& outNode = graph.nodes[l.node_out];
        ImNodes::Link(i, outNode.output_slots[l.slot_out].guid, inNode.input_slots[l.slot_in].guid);
    }

    ImNodes::EndNodeEditor();
    ImGui::End();

    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        Link l;
        l.node_in = getNodeBySlot(graph, end_attr);
        l.slot_in = getSlotIndexInNodeByGUID(graph.nodes[l.node_in], end_attr);

        int linkID = getLinkId(graph, graph.nodes[l.node_in], l.slot_in, true);

        if (linkID != -1)
        {
            graph.links.erase(graph.links.begin() + linkID);
        }

        l.node_out = getNodeBySlot(graph, start_attr);
        
        l.slot_out = getSlotIndexInNodeByGUID(graph.nodes[l.node_out], start_attr);
        graph.links.push_back(l);
        needPreviewUpdate = true;
    }

    int linkID = -1;
    if (ImNodes::IsLinkDestroyed(&linkID))
    {
        graph.links.erase(graph.links.begin() + linkID);
        needPreviewUpdate = true;
    }

    int selectedLinksCount = ImNodes::NumSelectedLinks();
    if (selectedLinksCount > 0 && ImGui::IsKeyReleased(GLFW_KEY_DELETE))
    {
        std::vector<int> selectedLinks;
        selectedLinks.resize(selectedLinksCount);
        ImNodes::GetSelectedLinks(selectedLinks.data());
        if (selectedLinks.size() > 0)
        {
            Link& l = graph.links[selectedLinks[0]];
            fixLink(graph, selectedLinks[0]);
            graph.links.erase(graph.links.begin() + selectedLinks[0]);
            needPreviewUpdate = true;
        }
    }
    int selectedNodesCount = ImNodes::NumSelectedNodes();
    if (selectedNodesCount > 0 && ImGui::IsKeyReleased(GLFW_KEY_DELETE))
    {
        std::vector<int> selectedNodes;
        selectedNodes.resize(selectedNodesCount);
        ImNodes::GetSelectedNodes(selectedNodes.data());
        for (int i = 0; i < selectedNodes.size(); i++)
        {
            if (graph.nodes[selectedNodes[i]].type == NodeType::PARAMETER)
            {
                for (int j = 0; j < graph.parameters.size(); j++)
                {
                    if (graph.parameters[j].guid == selectedNodes[i])
                    {
                        graph.parameters.erase(graph.parameters.begin() + j);
                        break;
                    }
                }
            }
            deleteLinksWithNode(graph, selectedNodes[i]);
            graph.nodes.erase(selectedNodes[i]);
            needPreviewUpdate = true;
        }
    }
}

std::string previewTypeToString(Render::PreviewType type)
{
    switch(type)
    {
        case Render::PreviewType::SPHERE:
            return "Sphere";
        case Render::PreviewType::CUBE:
            return "Cube";
        case Render::PreviewType::PLANE:
            return "Plane";
    }
    return "";
}

bool drawSelectableFor(Render::PreviewType type, Render::PreviewType selected)
{
    bool isSelected = type == selected;
    if (ImGui::Selectable(previewTypeToString(type).c_str(), &isSelected))
    {
        return true;
    }

    return false;
}

void copyTexturesAndUpdatePaths(Graph& graph, std::string outputPath)
{
    std::string folder = Utils::getFolderPath(outputPath);
    std::string texturesFolder = folder + Utils::getSystemSeparator() + "textures" + Utils::getSystemSeparator();

    for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
    {
        if (it->second.type != NodeType::PARAMETER)
        {
            continue;
        }
        for (size_t i = 0; i < it->second.input_slots.size(); i++)
        {
            if (it->second.input_slots[i].type == ValueType::SAMPLER2D)
            {
                std::string textureName = Utils::getFileName(it->second.input_slots[i].value);
                Utils::copyFile(it->second.input_slots[i].value, texturesFolder + textureName);
                it->second.input_slots[i].value = "textures" + Utils::getSystemSeparator() + textureName;
            }
        }

        for (size_t i = 0; i < it->second.output_slots.size(); i++)
        {
            if (it->second.output_slots[i].type == ValueType::SAMPLER2D)
            {
                std::string textureName = Utils::getFileName(it->second.output_slots[i].value);
                Utils::copyFile(it->second.output_slots[i].value, texturesFolder + textureName);
                it->second.output_slots[i].value = "textures" + Utils::getSystemSeparator() + textureName;
            }
        }
    }
}

void fixPaths(Graph& graph, std::string projectPath)
{
    std::string projectFolder = Utils::getFolderPath(projectPath);
    for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
    {
        if (it->second.type != NodeType::PARAMETER)
        {
            continue;
        }
        for (size_t i = 0; i < it->second.input_slots.size(); i++)
        {
            if (it->second.input_slots[i].type == ValueType::SAMPLER2D)
            {
                std::string fullPath = projectFolder + Utils::getSystemSeparator() + it->second.input_slots[i].value;
                it->second.input_slots[i].value = Utils::fixSeparator(fullPath);
            }
        }

        for (size_t i = 0; i < it->second.output_slots.size(); i++)
        {
            if (it->second.output_slots[i].type == ValueType::SAMPLER2D)
            {
                std::string fullPath = projectFolder + Utils::getSystemSeparator() + it->second.output_slots[i].value;
                it->second.output_slots[i].value = Utils::fixSeparator(fullPath);
            }
        }
    }
}

void menuNew()
{
    graph = Graph();
    Render::reset();
    currentCode = "";
}

void menuOpen()
{
    try
    {
        std::string path = Utils::showFileDialog();
        if (path != "canceled" && path != "failed")
        {
            InputFileStream is(path);
            Graph g;
            is >> g;
            graph = g;

            IdProvider::init(graph);
            fixPaths(graph, path);

            for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
            {
                ImNodes::SetNodeGridSpacePos(it->first, ImVec2(it->second.position.x, it->second.position.y));
            }

            Generator::GeneratorOutput res = Generator::generateGLSL(graph);
            Render::setFragmentCode(res.glslCode);
            Render::setUniforms(res.uniforms);
            currentCode = res.glslCode;
            updateSignaturesForNodes(graph);

            for (auto it = res.uniforms.begin(); it != res.uniforms.end(); ++it)
            {
                if (it->second.valueType == ValueType::SAMPLER2D)
                {
                    textures.push_back(it->second.textureValue);
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Failed to load project\n";
    }
}

void menuSave()
{
    try
    {
        std::string path = Utils::showSaveFileDialog();
        if (path != "canceled" && path != "failed")
        {
            copyTexturesAndUpdatePaths(graph, path);
            OutputFileStream ser(path);
            ser << graph;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Failed to save project\n";
    }
}

void menuExport()
{
    try
    {
        std::string path = Utils::showSaveFileDialog();
        if (path != "canceled" && path != "failed")
        {
            Generator::GeneratorOutput res = Generator::generateGLSL(graph);

            std::ofstream out(path);
            out << res.glslCode;
            out.close();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Failed to save glsl code\n";
    }
}

namespace App
{

    void init(int width, int height)
    {
        cameraScale.x = 1.0f;
        cameraScale.y = 1.0f;
        NodeLibrary::initNodeLibrary();
        Render::init(previewSize.x, previewSize.y);
    }

    void drawUI()
    {
        needCopyCode = false;
        configDock();

        ImGui::BeginMainMenuBar();

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl + N"))
            {
                menuNew();
            }
            if (ImGui::MenuItem("Open", "Ctrl + O"))
            {
                menuOpen();
            }
            if (ImGui::MenuItem("Save", "Ctrl + S"))
            {
                menuSave();
            }
            if (ImGui::MenuItem("Export", "Ctrl + E"))
            {
                menuExport();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit"))
            {
                std::terminate();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();

        drawNodeEditor(graph);

        ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        isPreviewFocused = ImGui::IsWindowFocused();
        ImVec2 size = ImGui::GetWindowSize();
        size.y = size.y - 55;
        previewSize.x = std::min(size.x, size.y);
        previewSize.y = previewSize.x;
        unsigned int texture = Render::getColorTexture();
        ImGui::Image((ImTextureID)texture, ImVec2(previewSize.x, previewSize.y));

        Render::PreviewType type = Render::getPreviewType();
        if (ImGui::BeginCombo("##comb", previewTypeToString(type).c_str()))
        {
            if (drawSelectableFor(Render::PreviewType::SPHERE, type))
            {
                Render::setPreviewType(Render::PreviewType::SPHERE);
            }
            if (drawSelectableFor(Render::PreviewType::CUBE, type))
            {
                Render::setPreviewType(Render::PreviewType::CUBE);
            }
            if (drawSelectableFor(Render::PreviewType::PLANE, type))
            {
                Render::setPreviewType(Render::PreviewType::PLANE);
            }
            ImGui::EndCombo();
        }

        ImGui::End();


        ImGui::Begin("Code");

        ImGui::BeginChild("Code window", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 25));
        ImGui::TextWrapped(currentCode.c_str());
        ImGui::EndChild();
        if (ImGui::Button("Copy"))
        {
            needCopyCode = true;
        }
        
        ImGui::End();

        if (needPreviewUpdate)
        {
            Generator::GeneratorOutput res = Generator::generateGLSL(graph);
            Render::setFragmentCode(res.glslCode);
            Render::setUniforms(res.uniforms);
            needPreviewUpdate = false;
            currentCode = res.glslCode;
            updateSignaturesForNodes(graph);
        }
    }

    void drawScene()
    {
        Render::setScreenSize(previewSize.x, previewSize.y);
        Render::renderPreview();
    }

    void buttonPressed(int keyCode, int action, int modKey)
    {
        if (keyCode == GLFW_KEY_S && action == GLFW_RELEASE && modKey & GLFW_MOD_CONTROL)
        {
            menuSave();
        }
        if (keyCode == GLFW_KEY_O && action == GLFW_RELEASE && modKey & GLFW_MOD_CONTROL)
        {
            menuOpen();
        }
        if (keyCode == GLFW_KEY_E && action == GLFW_RELEASE && modKey & GLFW_MOD_CONTROL)
        {
            menuExport();
        }
        if (keyCode == GLFW_KEY_N && action == GLFW_RELEASE && modKey & GLFW_MOD_CONTROL)
        {
            menuNew();
        }
    }

    void mouseButtonAction(int id, int action)
    {
        if (action == GLFW_PRESS && id == 0)
        {
            isMousePressed = true;
        }
        if (action == GLFW_RELEASE && id == 0)
        {
            isMousePressed = false;
        }
    }

    void mouseMoved(float x, float y)
    {
        if (isMousePressed && isPreviewFocused)
        {
            lastMousePosition.x = x;
            lastMousePosition.y = y;

            const Vec3& position = Render::getCameraPosition();
            Render::setCameraPosition(Vec3(position.x, cosf(y / 10.0f) * 30, sinf(y / 10.0f) * 30));
            const Vec3& newPosition = Render::getCameraPosition();
            Render::setCameraPosition(Vec3(sinf(x / 10.0f) * 30, newPosition.y, cosf(x / 10.0f) * 30));
        }
    }

    void mouseScroll(int amount)
    {
        if (isPreviewFocused)
        {
            Render::setCameraZoom(Render::getCameraZoom() + amount);
        }
    }

    bool needCopy()
    {
        return needCopyCode;
    }

    std::string getShaderCode()
    {
        return currentCode;
    }
}
