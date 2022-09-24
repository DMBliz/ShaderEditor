#pragma once

#include <string>
#include "xmath.h"

namespace App
{
    void init(int width, int height);
    void drawUI();
    void drawScene();

    void buttonPressed(int keyCode, int action, int modKey);
    void mouseButtonAction(int id, int action);
    void mouseMoved(float x, float y);
    void mouseScroll(int amount);

    bool needCopy();
    std::string getShaderCode();
}