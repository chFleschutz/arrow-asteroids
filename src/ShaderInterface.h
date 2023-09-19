#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class ShaderInterface {


public:

    static int lastShaderUsed;

    enum class UniformVariableType {
        intT, floatT, doubleT, doubleV3T, doubleV4T, floatV3T, floatV4T,
        floatM3T, floatM4T, doubleM3T, doubleM4T, textureT, intAT, floatAT, doubleAT
    };

    bool useTexture;
    bool useBump;
    bool useBlinn;
    bool useColor;

    ShaderInterface(string name, bool useTexture, bool useBump, bool useBlinn, bool useColor);
    ~ShaderInterface();

    void setPathToShaderDir(string path);
    void registerVar(string name, UniformVariableType type);
    void registerVar(string name, UniformVariableType type, int arraySize);
    int getGLId();
    void useMe();
    void setFragmentShader(string code);
    void setVertexShader(string code);
    int getIdForVariable(string varName);
    void sendUniformValues();


private:
    const char* STANDARD_COLOR_TEXTURE_VARNAME = "text";
    const char* STANDARD_NORMALMAP_VARNAME = "normalMap";
    const char* STANDARD_SHADOWMAP_VARNAME = "shadowMap";
    const char* STANDARD_LIGHT_INTENSITY_VARNAME = "lightIntensity";
    const char* STANDARD_LIGHT_COLOR_VARNAME = "lightColor";
    const char* STANDARD_ENVIRON_LIGHT_INTENSITY_VARNAME = "environLightIntensity";
    const char* STANDARD_WORLD_TRANSFORMATION_VARNAME = "transformWorld";
    const char* STANDARD_OBJECT_TRANSFORMATION_VARNAME = "transformObject";
    const char* STANDARD_CAMERA_POS_VARNAME = "cameraPos";
    const char* STANDARD_CAMERA_PROJ_VARNAME = "cameraProjection";
    const char* STANDARD_LIGHT_POS_VARNAME = "lightPosition";
    const char* STANDARD_LIGHT_SPACE_MAT_VARNAME = "lightSpaceMatrix";

    class UniformVariable {
    public:
        string name;
        GLint id;
        UniformVariableType type;
        UniformVariable(string name, GLint id, UniformVariableType type);
    };

    GLint vertexShader, fragmentShader, programID;
    string pathToShaderPrograms;
    string name;
    bool programCompilationFinished;
    unordered_set<string> unknownShaderVarMessages;

    unordered_map<string, UniformVariable*> uniformVars;
    unordered_map<int, UniformVariable*> idToVarMap;
    unordered_map<string, int> arrayVarSizes;

    unordered_map<int, int> bufferedUniformIntValues;
    unordered_map<int, float> bufferedUniformFloatValues;
    unordered_map<int, double> bufferedUniformDoubleValues;
    unordered_map<int, float*> bufferedUniformFloatArrayValues;
    unordered_map<int, double*> bufferedUniformDoubleArrayValues;
    unordered_map<int, int*> bufferedUniformIntArrayValues;
    //unordered_map<int, TextureInterface> bufferedUniformTextureValues;
    //unordered_map<int, Matrix3f> bufferedUniformMatrix3fValues;
    //unordered_map<int, Matrix4f> bufferedUniformMatrix4fValues;
    unordered_map<int, float*> bufferedUniformVec3fValues;
    unordered_map<int, float*> bufferedUniformVec4fValues;
    unordered_map<int, double*> bufferedUniformVec3dValues;
    unordered_map<int, double*> bufferedUniformVec4dValues;

    //static unordered_map<int, TextureInterface> lastUsedTextureUnits;

    static int lastUsedShaderID;


    void initUniformVarBuffers();
    void clearUniformVarBuffers();

    string readSource(string file);
    void finalizeProgramInitialization();

    void logUnknownShaderVar(string msg);

    void deleteUniformVars();
    int checkVarExistence(string name);
    void setUniform(string name, int value);
    void setUniform(string name, int len, int* value);
    void setUniform(string name, float value);
    void setUniform(string name, int len, float* value);
    void setUniform(string name, float v1, float v2, float v3);
    void setUniform(string name, float v1, float v2, float v3, float v4);
    void setUniform(string name, double value);
    void setUniform(string name, int len, double* value);
    void setUniform(string name, double v1, double v2, double v3);
    void setUniform(string name, double v1, double v2, double v3, double v4);


};

