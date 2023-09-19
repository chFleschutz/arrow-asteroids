#include <fstream>
#include <streambuf>
#include <iostream>
#include "ShaderInterface.h"
#include "StringHelper.h"

int ShaderInterface::lastShaderUsed = -1;
int ShaderInterface::lastUsedShaderID = -1;



ShaderInterface::ShaderInterface(string name, bool useTexture, bool useBump, bool useBlinn, bool useColor) {
    this->useTexture = useTexture;
    this->useBlinn = useBlinn;
    this->useBump = useBump;
    this->useColor = useColor;
    this->name = name;
    uniformVars = unordered_map<string, UniformVariable*>();
    idToVarMap = unordered_map<int, UniformVariable*>();
    arrayVarSizes = unordered_map<string, int>();
    initUniformVarBuffers();
    unknownShaderVarMessages = unordered_set<string>();
    programCompilationFinished = false;
    programID = -1;
    fragmentShader = -1;
    vertexShader = -1;
}



ShaderInterface::~ShaderInterface() {
    glDetachShader(programID, vertexShader);
    glDetachShader(programID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(programID);
    deleteUniformVars();
}



void ShaderInterface::setPathToShaderDir(string path) {
    if (!(StringHelper::endsWith(path, "\\") || StringHelper::endsWith(path, "/")))

        path = path + "/";
    this->pathToShaderPrograms = path;
}



void ShaderInterface::registerVar(string varName, UniformVariableType type) {
    if (programCompilationFinished)
        throw runtime_error("Cannot register Variable " + varName + ", because the compilation of the shader-program has already finished.");
    if (uniformVars.find(varName) != uniformVars.end()) {
        UniformVariable* v = uniformVars[varName];
        delete v;
    }
    uniformVars[varName] = new UniformVariable(varName, -1, type);
}



void ShaderInterface::registerVar(string varName, UniformVariableType type, int arraySize) {
    if (programCompilationFinished)
        throw runtime_error("Cannot register Variable " + varName + ", because the compilation of the shader-program has already finished.");
    if (uniformVars.find(varName) != uniformVars.end()) {
        UniformVariable* v = uniformVars[varName];
        delete v;
    }
    uniformVars[varName] = new UniformVariable(varName, -1, type);
    arrayVarSizes[varName] = arraySize;
}



int ShaderInterface::getGLId() {
    return programID;
}


void ShaderInterface::useMe() {
    if (lastShaderUsed != programID) {
        glUseProgram(programID);
        lastShaderUsed = programID;
    }
}

void throwInfoLog(GLint id, void (*logFunc)(GLuint, GLsizei, GLsizei*, GLchar*)) {
    GLint logSize = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);
    const int maxErrorSize = 5000;
    GLchar error[maxErrorSize];
    (*logFunc)(id, maxErrorSize, nullptr, error);
    throw  runtime_error(error);
}



void ShaderInterface::finalizeProgramInitialization() {
    GLint success;
    glLinkProgram(programID);
    glValidateProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        throwInfoLog(programID, glGetProgramInfoLog);
    }
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE) {
        throwInfoLog(programID, glGetProgramInfoLog);
    }
    for (auto iter = uniformVars.begin(); iter != uniformVars.end(); iter++) {
        UniformVariable* v = iter->second;
        v->id = glGetUniformLocation(programID, iter->first.c_str());
        idToVarMap[v->id] = v;
    }
    programCompilationFinished = true;
}


void ShaderInterface::logUnknownShaderVar(string msg) {
    auto t = unknownShaderVarMessages.find(msg);
    if (t == unknownShaderVarMessages.end()) {
        std::cerr << msg << std::endl;
        unknownShaderVarMessages.insert(msg);
    }
}


void ShaderInterface::setFragmentShader(string code) {
    GLint success;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* s = code.c_str();
    glShaderSource(fragmentShader, 1, &s, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        throwInfoLog(fragmentShader, glGetShaderInfoLog);
    }

    if (programID == -1) {
        programID = glCreateProgram();
    }
    glAttachShader(programID, fragmentShader);
    if (vertexShader != -1) {
        finalizeProgramInitialization();
    }
}


void ShaderInterface::setVertexShader(string code) {
    GLint success;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char* s = code.c_str();
    glShaderSource(vertexShader, 1, &s, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        throwInfoLog(vertexShader, glGetShaderInfoLog);
    }

    if (programID == -1) {
        programID = glCreateProgram();
    }
    glAttachShader(programID, vertexShader);
    if (fragmentShader != -1) {
        finalizeProgramInitialization();
    }
}



int ShaderInterface::getIdForVariable(string varName) {
    return uniformVars[varName]->id;
}


void execSetUniform(int id, int value) {
    glUniform1i(id, value);
}



int ShaderInterface::checkVarExistence(string varName) {
    auto v = uniformVars.find(varName);
    if (v == uniformVars.end())
        throw runtime_error("Unknown variable: " + varName);
    return uniformVars[varName]->id;
}



void ShaderInterface::setUniform(string varName, int value) {
    int id = checkVarExistence(varName);
    bufferedUniformIntValues[id] = value;
}



void ShaderInterface::setUniform(string varName, int len, int* value) {
    int id = checkVarExistence(varName);
    auto val = bufferedUniformIntArrayValues.find(id);
    if (val != bufferedUniformIntArrayValues.end()) {
        delete val->second;
    }
    bufferedUniformIntArrayValues[id] = value;
    arrayVarSizes[varName] = len;
}



void ShaderInterface::setUniform(string varName, float value) {
    int id = checkVarExistence(varName);
    bufferedUniformFloatValues[id] = value;
}



void ShaderInterface::setUniform(string varName, int len, float* value) {
    int id = checkVarExistence(varName);
    if (len == 3) {
        auto val = bufferedUniformVec3fValues.find(id);
        if (val != bufferedUniformVec3fValues.end()) {
            delete val->second;
        }
        bufferedUniformVec3fValues[id] = value;
    } else if (len == 4) {
        auto val = bufferedUniformVec4fValues.find(id);
        if (val != bufferedUniformVec4fValues.end()) {
            delete val->second;
        }
        bufferedUniformVec4fValues[id] = value;
    } else {
        auto val = bufferedUniformFloatArrayValues.find(id);
        if (val != bufferedUniformFloatArrayValues.end()) {
            delete val->second;
        }
        bufferedUniformFloatArrayValues[id] = value;
        arrayVarSizes[varName] = len;
    }
}



void ShaderInterface::setUniform(string varName, float v1, float v2, float v3) {
    int id = checkVarExistence(varName);
    float* v = new float[3]{ v1, v2, v3 };
    auto val = bufferedUniformVec3fValues.find(id);
    if (val != bufferedUniformVec3fValues.end()) {
        delete val->second;
    }
    bufferedUniformVec3fValues[id] = v;
}



void ShaderInterface::setUniform(string varName, float v1, float v2, float v3, float v4) {
    int id = checkVarExistence(varName);
    float* v = new float[4]{ v1, v2, v3, v4 };
    auto val = bufferedUniformVec4fValues.find(id);
    if (val != bufferedUniformVec4fValues.end()) {
        delete val->second;
    }
    bufferedUniformVec4fValues[id] = v;
}



void ShaderInterface::setUniform(string varName, double value) {
    int id = checkVarExistence(varName);
    bufferedUniformDoubleValues[id] = value;
}



void ShaderInterface::setUniform(string varName, int len, double* value) {
    int id = checkVarExistence(varName);
    if (len == 3) {
        auto val = bufferedUniformVec3dValues.find(id);
        if (val != bufferedUniformVec3dValues.end()) {
            delete val->second;
        }
        bufferedUniformVec3dValues[id] = value;
    } else if (len == 4) {
        auto val = bufferedUniformVec4dValues.find(id);
        if (val != bufferedUniformVec4dValues.end()) {
            delete val->second;
        }
        bufferedUniformVec4dValues[id] = value;
    } else {
        auto val = bufferedUniformDoubleArrayValues.find(id);
        if (val != bufferedUniformDoubleArrayValues.end()) {
            delete val->second;
        }
        bufferedUniformDoubleArrayValues[id] = value;
        arrayVarSizes[varName] = len;
    }
}



void ShaderInterface::setUniform(string varName, double v1, double v2, double v3) {
    int id = checkVarExistence(varName);
    double* v = new double[3]{ v1, v2, v3 };
    auto val = bufferedUniformVec3dValues.find(id);
    if (val != bufferedUniformVec3dValues.end()) {
        delete val->second;
    }
    bufferedUniformVec3dValues[id] = v;
}



void ShaderInterface::setUniform(string varName, double v1, double v2, double v3, double v4) {
    int id = checkVarExistence(varName);
    double* v = new double[4]{ v1, v2, v3, v4 };
    auto val = bufferedUniformVec4dValues.find(id);
    if (val != bufferedUniformVec4dValues.end()) {
        delete val->second;
    }
    bufferedUniformVec4dValues[id] = v;
}


void ShaderInterface::sendUniformValues() {
    //if (lastUsedShaderID != programID) lastUsedTextureUnits.clear();
    for (auto k = bufferedUniformIntValues.begin(); k != bufferedUniformIntValues.end(); k++) {
        int id = k->first;
        int val = k->second;
        glUniform1i(id, val);
    }
    for (auto k = bufferedUniformFloatValues.begin(); k != bufferedUniformFloatValues.end(); k++) {
        int id = k->first;
        float val = k->second;
        glUniform1f(id, val);
    }
    for (auto k = bufferedUniformDoubleValues.begin(); k != bufferedUniformDoubleValues.end(); k++) {
        int id = k->first;
        double val = k->second;
        glUniform1d(id, val);
    }
    for (auto k = bufferedUniformIntArrayValues.begin(); k != bufferedUniformIntArrayValues.end(); k++) {
        int id = k->first;
        int* val = k->second;
        int size = arrayVarSizes[idToVarMap[id]->name];
        glUniform1iv(id, size, val);
    }

    for (auto k = bufferedUniformFloatArrayValues.begin(); k != bufferedUniformFloatArrayValues.end(); k++) {
        int id = k->first;
        float* val = k->second;
        int size = arrayVarSizes[idToVarMap[id]->name];
        glUniform1fv(id, size, val);
    }
    for (auto k = bufferedUniformDoubleArrayValues.begin(); k != bufferedUniformDoubleArrayValues.end(); k++) {
        int id = k->first;
        double* val = k->second;
        int size = arrayVarSizes[idToVarMap[id]->name];
        glUniform1dv(id, size, val);
    }
    for (auto k = bufferedUniformVec3fValues.begin(); k != bufferedUniformVec3fValues.end(); k++) {
        int id = k->first;
        float* val = k->second;
        glUniform3fv(id, 1, val);
    }
    for (auto k = bufferedUniformVec3dValues.begin(); k != bufferedUniformVec3dValues.end(); k++) {
        int id = k->first;
        double* val = k->second;
        glUniform3dv(id, 1, val);
    }
    for (auto k = bufferedUniformVec4fValues.begin(); k != bufferedUniformVec4fValues.end(); k++) {
        int id = k->first;
        float* val = k->second;
        glUniform4fv(id, 1, val);
    }
    for (auto k = bufferedUniformVec4dValues.begin(); k != bufferedUniformVec4dValues.end(); k++) {
        int id = k->first;
        double* val = k->second;
        glUniform4dv(id, 1, val);
    }
    lastUsedShaderID = programID;
    clearUniformVarBuffers();
}



ShaderInterface::UniformVariable::UniformVariable(std::string varName, GLint id, UniformVariableType type) {
    this->name = varName;
    this->id = id;
    this->type = type;
}



void ShaderInterface::initUniformVarBuffers() {
    bufferedUniformIntValues = unordered_map<int, int>();
    bufferedUniformFloatValues = unordered_map<int, float>();
    bufferedUniformDoubleValues = unordered_map<int, double>();
    bufferedUniformFloatArrayValues = unordered_map<int, float*>();
    bufferedUniformDoubleArrayValues = unordered_map<int, double*>();
    bufferedUniformIntArrayValues = unordered_map<int, int*>();
    //unordered_map<int, TextureInterface> bufferedUniformTextureValues;
    //unordered_map<int, Matrix3f> bufferedUniformMatrix3fValues;
    //unordered_map<int, Matrix4f> bufferedUniformMatrix4fValues;
    bufferedUniformVec3fValues = unordered_map<int, float*>();
    bufferedUniformVec4fValues = unordered_map<int, float*>();
    bufferedUniformVec3dValues = unordered_map<int, double*>();
    bufferedUniformVec4dValues = unordered_map<int, double*>();
}



void ShaderInterface::clearUniformVarBuffers() {
    bufferedUniformIntValues.clear();
    bufferedUniformFloatValues.clear();
    bufferedUniformDoubleValues.clear();

    for (auto k = bufferedUniformIntArrayValues.begin(); k != bufferedUniformIntArrayValues.end(); k++) {
        delete k->second;
    }
    bufferedUniformIntArrayValues.clear();
    for (auto k = bufferedUniformFloatArrayValues.begin(); k != bufferedUniformFloatArrayValues.end(); k++) {
        delete k->second;
    }
    bufferedUniformFloatArrayValues.clear();
    for (auto k = bufferedUniformDoubleArrayValues.begin(); k != bufferedUniformDoubleArrayValues.end(); k++) {
        delete k->second;
    }
    bufferedUniformDoubleArrayValues.clear();

    //bufferedUniformTextureValues.clear();
    //bufferedUniformMatrix3fValues.clear();
    //bufferedUniformMatrix4fValues.clear();

    for (auto k = bufferedUniformVec3fValues.begin(); k != bufferedUniformVec3fValues.end(); k++) {
        delete k->second;
    }
    bufferedUniformVec3fValues.clear();

    for (auto k = bufferedUniformVec4fValues.begin(); k != bufferedUniformVec4fValues.end(); k++) {
        delete k->second;
    }
    bufferedUniformVec4fValues.clear();

    for (auto k = bufferedUniformVec3dValues.begin(); k != bufferedUniformVec3dValues.end(); k++) {
        delete k->second;
    }
    bufferedUniformVec3dValues.clear();

    for (auto k = bufferedUniformVec4dValues.begin(); k != bufferedUniformVec4dValues.end(); k++) {
        delete k->second;
    }
    bufferedUniformVec4dValues.clear();
    arrayVarSizes.clear();
}



void ShaderInterface::deleteUniformVars() {
    clearUniformVarBuffers();
    for (auto iter = uniformVars.begin(); iter != uniformVars.end(); iter++) {
        UniformVariable* v = iter->second;
        delete v;
    }
    uniformVars.clear();
    idToVarMap.clear();
    arrayVarSizes.clear();
}



string ShaderInterface::readSource(string file) {
    ifstream f(file);
    string str((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    return str;
}

