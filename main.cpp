/* Ask for an OpenGL Core Context */
#define GLFW_INCLUDE_GLCOREARB
#include "GLShader.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

int main(int argc, char** argv){
  GLFWwindow* window;

  /* Initialize the library */
  if ( !glfwInit() ){
     return -1;
  }

#ifdef __APPLE__
  /* We need to explicitly ask for a 3.2 context on OS X */
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow( 1280, 720, "Hello World", NULL, NULL );
  if (!window){
     glfwTerminate();
     return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  GLuint shaderProgram = LoadProgram("./shaders/triVert.glsl", "./shaders/triFrag.glsl");

  float verts[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)){
    /* Render here */
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}