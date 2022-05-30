#include "GLShader.h"

#include <string>
#include <iostream>
#include <fstream>

std::string readFile(const char *filePath){
    std::ifstream fileStream(filePath, std::ios::in);
    if(!fileStream.is_open()){
        std::cerr << "Could not read file " << filePath << std::endl;
        return "";
    }

    std::string content;
    std::string line = "";
    while(!fileStream.eof()){
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint LoadProgram(const char *vertexPath, const char *fragmentPath){
    std::string vertStr = readFile(vertexPath);
    std::string fragStr = readFile(fragmentPath);
    const char *vertSource = vertStr.c_str();
    const char *fragSource = fragStr.c_str();

    int success;
    int logSize = 512;
    char infoLog[logSize];

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, NULL);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertShader, logSize, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragShader, logSize, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, logSize, NULL, infoLog);
        std::cerr << "Shader linking failed\n" << infoLog << std::endl;
    }
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}