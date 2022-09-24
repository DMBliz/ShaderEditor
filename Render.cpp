#include "Render.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <map>

#include "Render.h"
#include "xmath.h"
#include "Utils.h"

std::vector<float> vertices;
std::vector<unsigned int> indices;

const char* vertexCode = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    "layout (location = 1) in vec3 a_normals;\n"
    "layout (location = 2) in vec2 a_texCoords;\n"
    "\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "\n"
    "out vec3 fragPos;\n"
    "out vec3 normal;\n"
    "out vec2 uv;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   fragPos = vec3(model * vec4(a_position, 1.0));\n"
    "   normal = mat3(transpose(inverse(model))) * a_normals;\n"
    "   uv = a_texCoords;\n"
    "   gl_Position = projection * view * vec4(fragPos, 1.0);\n"
    "}\n";

std::string defaultFragment = 
    "#version 330 core\n"
    "in vec3 fragPos;\n"
    "in vec3 normal;\n"
    "in vec2 uv;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   fragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
    "}\n";

std::string fragmentCode;

unsigned int VBO = -1, VAO = -1, EBO = -1;
unsigned int shaderProgram = -1;
unsigned int vertexShader = -1, fragmentShader = -1;

unsigned int fbo = -1;
unsigned int fboColor = -1, fboDepth = -1;

Vec3 cameraPosition(0, 0, 30);
float cameraZoom = 5;
float minZoom = 1;
float maxZoom = 10;

Render::PreviewType previewType;

int _width;
int _height;

glm::mat4 projection;
glm::mat4 model;
glm::mat4 view;

std::map<std::string, Texture*> loadedTextures;
std::map<std::string, std::string> usedTextures;
std::map<std::string, UniformParameter> currentUniforms;

bool checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            return false;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            return false;
        }
    }

    return true;
}

void checkGLError()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cout << "gl error: " << error << std::endl;
    }
}

void generateSphere(float radius, int sectorCount, int stackCount)
{
    vertices.clear();
    indices.clear();

    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);

            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }

    for(int i = 0, k1, k2; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if(i != (stackCount-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void generateCube()
{
    vertices.clear();
    indices.clear();

    vertices = {
         0.5, -0.5,  0.5,  0, -1,  0, 0, 1,
        -0.5, -0.5,  0.5,  0, -1,  0, 1, 1,
        -0.5, -0.5, -0.5,  0, -1,  0, 1, 0,
         0.5,  0.5, -0.5,  0,  1,  0, 1, 0,
        -0.5,  0.5, -0.5,  0,  1,  0, 0, 0,
        -0.5,  0.5,  0.5,  0,  1,  0, 0, 1,
         0.5,  0.5, -0.5,  1,  0,  0.000001, 1, 0,
         0.5,  0.5,  0.5,  1,  0,  0.000001, 0, 0,
         0.5, -0.5,  0.5,  1,  0,  0.000001, 0, 1,
         0.5, -0.5,  0.5,  0,  0,  1, 1, 1,
         0.5,  0.5,  0.5,  0,  0,  1, 1, 0,
        -0.5,  0.5,  0.5,  0,  0,  1, 0, 0,
        -0.5,  0.5,  0.5, -1,  0,  0, 1, 0,
        -0.5,  0.5, -0.5, -1,  0,  0, 0, 0,
        -0.5, -0.5, -0.5, -1,  0,  0, 0, 1,
         0.5,  0.5, -0.5,  0,  0, -1, 0, 0,
         0.5, -0.5, -0.5,  0,  0, -1, 0, 1,
        -0.5, -0.5, -0.5,  0,  0, -1, 1, 1,
         0.5, -0.5, -0.5,  0, -1,  0, 0, 0,
         0.5, -0.5,  0.5,  0, -1,  0, 0, 1,
        -0.5, -0.5, -0.5,  0, -1,  0, 1, 0,
         0.5,  0.5,  0.5,  0,  1,  0, 1, 1,
         0.5,  0.5, -0.5,  0,  1,  0, 1, 0,
        -0.5,  0.5,  0.5,  0,  1,  0, 0, 1,
         0.5, -0.5, -0.5,  1,  0,  0, 1, 1,
         0.5,  0.5, -0.5,  1,  0,  0, 1, 0,
         0.5, -0.5,  0.5,  1,  0,  0, 0, 1,
        -0.5, -0.5,  0.5,  0,  0,  1, 0, 1,
         0.5, -0.5,  0.5,  0,  0,  1, 1, 1,
        -0.5,  0.5,  0.5,  0,  0,  1, 0, 0,
        -0.5, -0.5,  0.5, -1,  0,  0, 1, 1,
        -0.5,  0.5,  0.5, -1,  0,  0, 1, 0,
        -0.5, -0.5, -0.5, -1,  0,  0, 0, 1,
        -0.5,  0.5, -0.5,  0,  0, -1, 1, 0,
         0.5,  0.5, -0.5,  0,  0, -1, 0, 0,
        -0.5, -0.5, -0.5,  0,  0, -1, 1, 1
    };

    indices = {
         0,  1,  2,
         3,  4,  5,
         6,  7,  8,
         9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
    };   
}

void generatePlane()
{
    vertices = {
         1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    indices = {
        0, 1, 3,
        1, 2, 3
    };
}

void createVAO()
{
    if (VAO != -1)
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void loadTextureToVRAM(Texture* texture)
{
    unsigned int id = -1;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->getWidth(), texture->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    texture->setId(id);
}

namespace Render
{
    void init(int width, int height)
    {
        setScreenSize(width, height);
        setCameraPosition(cameraPosition);
        model = glm::mat4(1.0);
        setPreviewType(PreviewType::SPHERE);

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexCode, NULL);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "VERTEX");

        setFragmentCode(defaultFragment);
    }

    void reset()
    {
        setFragmentCode(defaultFragment);
    }

    void setFragmentCode(std::string fragment)
    {
        fragmentCode = fragment;
        bool successful = true;
        unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragCode = fragmentCode.c_str();
        glShaderSource(frag, 1, &fragCode, NULL);
        glCompileShader(frag);
        successful &= checkCompileErrors(frag, "FRAGMENT");

        unsigned int prog = glCreateProgram();
        glAttachShader(prog, vertexShader);
        glAttachShader(prog, frag);
        glLinkProgram(prog);
        successful &= checkCompileErrors(prog, "PROGRAM");

        if (!successful)
        {
            glDeleteShader(frag);
            glDeleteProgram(prog);
            std::cout << fragment << std::endl;
            return;
        }

        if (fragmentShader != -1)
        {
            glDeleteShader(fragmentShader);
        }

        if (shaderProgram != -1)
        {
            glDeleteProgram(shaderProgram);
        }

        fragmentShader = frag;
        shaderProgram = prog;

        checkGLError();
    }

    void setUniforms(std::map<std::string, UniformParameter>& uniforms)
    {
        currentUniforms = uniforms;
    }

    void setCameraPosition(Vec3 position)
    {
        if (previewType == PreviewType::PLANE)
        {
            return;
        }
        cameraPosition = position;
        view = glm::lookAt(glm::vec3(position.x, position.y, position.z), glm::vec3(0, 0, 0), glm::vec3(0.0, 1.0, 0.0));
    }

    const Vec3& getCameraPosition()
    {
        return cameraPosition;
    }

    void setCameraZoom(float zoom)
    {
        cameraZoom = std::min(std::max(zoom, minZoom), maxZoom);
        projection = glm::perspective(glm::radians(cameraZoom), (float)_width / (float)_height, 0.1f, 100.0f);
    }

    float getCameraZoom()
    {
        return cameraZoom;
    }

    void setScreenSize(int width, int height)
    {
        if (width == _width && height == _height)
        {
            return;
        }

        _width = width;
        _height = height;
        projection = glm::perspective(glm::radians(cameraZoom), (float)width / (float)height, 0.1f, 100.0f);

        if (fbo != -1)
        {
            glDeleteFramebuffers(1, &fbo);
            glDeleteTextures(1, &fboColor);
            glDeleteRenderbuffers(1, &fboDepth);
        }

        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glGenTextures(1, &fboColor);
        glBindTexture(GL_TEXTURE_2D, fboColor);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboColor, 0);

        glGenRenderbuffers(1, &fboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, fboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fboDepth);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        checkGLError();
    }

    unsigned int getColorTexture()
    {
        return fboColor;
    }

    unsigned int getTexture(std::string name)
    {
        auto it = loadedTextures.find(name);

        if (it == loadedTextures.end())
        {
            Texture* tex = Utils::loadImage(name);
            loadTextureToVRAM(tex);
            loadedTextures[name] = tex;
            return tex->getId();
        }
        
        return it->second->getId();
    }

    unsigned int getFolderIcon()
    {
        Texture* folder = Utils::getFolderIcon();
        if (folder->getId() == 0)
        {
            loadTextureToVRAM(folder);
        }

        return folder->getId();
    }

    void setPreviewType(PreviewType type)
    {
        view = glm::lookAt(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z), glm::vec3(0, 0, 0), glm::vec3(0.0, 1.0, 0.0));

        previewType = type;
        switch (previewType)
        {
        case PreviewType::PLANE:
            generatePlane();
            createVAO();
            view = glm::lookAt(glm::vec3(0, 0, 23), glm::vec3(0, 0, 0), glm::vec3(0.0, 1.0, 0.0));
            break;
        case PreviewType::CUBE:
            generateCube();
            createVAO();
            break;
        case PreviewType::SPHERE:
            generateSphere(1, 36, 18);
            createVAO();
            break;
        }
    }

    PreviewType getPreviewType()
    {
        return previewType;
    }

    void renderPreview()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, _width, _height);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glBindVertexArray(VAO);

        int texId = 0;
        for (auto it = currentUniforms.begin(); it != currentUniforms.end(); ++it)
        {
            int uniformLoc = glGetUniformLocation(shaderProgram, it->first.c_str());
            switch (it->second.valueType)
            {
            case ValueType::FLOAT:
                glUniform1f(uniformLoc, it->second.floatValue);
                break;
            case ValueType::VEC2:
                glUniform2f(uniformLoc, it->second.vec2Value.x, it->second.vec2Value.y);
                break;
            case ValueType::VEC3:
                glUniform3f(uniformLoc, it->second.vec3Value.x, it->second.vec3Value.y, it->second.vec3Value.z);
                break;
            case ValueType::VEC4:
                glUniform4f(uniformLoc, it->second.vec4Value.x, it->second.vec4Value.y, it->second.vec4Value.z, it->second.vec4Value.w);
                break;
            case ValueType::SAMPLER2D:
                glActiveTexture(GL_TEXTURE0 + texId);
                glUniform1i(uniformLoc, texId++);
                glBindTexture(GL_TEXTURE_2D, getTexture(it->second.textureValue));
                break;
            }
        }

        int timeLocation = glGetUniformLocation(shaderProgram, "time");
        if (timeLocation != -1)
        {
            glUniform1f(timeLocation, glfwGetTime());
        }

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);

        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        checkGLError();
    }
}