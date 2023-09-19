#pragma once

#include <string>

using namespace std;


namespace ShaderLib {
    const string glVersion = "410";

    const string vertexShaderForPlain2DPixels = ""
        "#version " + glVersion + "\n"
        "layout (location = 0) in vec2 positionVec;\n"
        "layout (location = 1) in vec3 color;\n"
        "out vec3 position;\n"
        "out vec3 vertexColor;\n"
        "void main() {\n"
        "    gl_Position = vec4(positionVec, 0, 1);\n"
        "    position = gl_Position.xyz;\n"
        "    vertexColor = color;\n"
        "}\n";


    const string fragmentShaderForPlain2DPixels = ""
        "#version " + glVersion + "\n"
        "in vec3 vertexColor;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(vertexColor, 1);\n"
        "}\n";
}
