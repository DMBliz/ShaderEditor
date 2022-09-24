#pragma once
#include <string>
#include <map>
#include "xmath.h"
#include "Graph.h"

namespace Render
{
    enum class PreviewType
    {
        SPHERE = 0,
        CUBE,
        PLANE
    };

    void init(int width, int height);
    void reset();

    void setFragmentCode(std::string fragmentCode);

    void setCameraPosition(Vec3 position);
    const Vec3& getCameraPosition();
    void setScreenSize(int width, int height);
    void setCameraZoom(float zoom);
    float getCameraZoom();

    unsigned int getColorTexture();

    unsigned int getTexture(std::string id);
    unsigned int getFolderIcon();

    void setUniforms(std::map<std::string, UniformParameter>& uniforms);

    void setPreviewType(PreviewType type);
    PreviewType getPreviewType();

    void renderPreview();
}
