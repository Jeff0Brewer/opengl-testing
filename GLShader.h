#ifndef GLSHADER_H
#define GLSHADER_H
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

GLuint LoadProgram(const char *vertexPath, const char *fragmentPath);

#endif