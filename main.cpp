#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "casa.hpp"
#include "shaders.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

unsigned int renderMode = GL_TRIANGLES;

ogl::vector moveRight(0.1f, 0.0f, 0.0f);
ogl::vector moveLeft(-0.1f, 0.0f, 0.0f);
ogl::vector moveUp(0.0f, 0.1f, 0.0f);
ogl::vector moveDown(0.0f, -0.1f, 0.0f);

ogl::casa miCasa;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

    // Compile vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShader1Source, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

    // Compile fragment shader
  unsigned int fragmentShaderWhite = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderWhite, 1, &fragmentShader1Source, NULL);
  glCompileShader(fragmentShaderWhite);

  unsigned int fragmentShaderBlack = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderBlack, 1, &fragmentShader2Source, NULL);
  glCompileShader(fragmentShaderBlack);

  unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderRed, 1, &fragmentShader3Source, NULL);
  glCompileShader(fragmentShaderRed);

  unsigned int fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderGreen, 1, &fragmentShader4Source, NULL);
  glCompileShader(fragmentShaderGreen);

  unsigned int fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderBlue, 1, &fragmentShader5Source, NULL);
  glCompileShader(fragmentShaderBlue);

    // Link shader program
  unsigned int shaderProgramWhite = glCreateProgram();
  glAttachShader(shaderProgramWhite, vertexShader);
  glAttachShader(shaderProgramWhite, fragmentShaderWhite);
  glLinkProgram(shaderProgramWhite);

  unsigned int shaderProgramBlack = glCreateProgram();
  glAttachShader(shaderProgramBlack, vertexShader);
  glAttachShader(shaderProgramBlack, fragmentShaderBlack);
  glLinkProgram(shaderProgramBlack);

  unsigned int shaderProgramRed = glCreateProgram();
  glAttachShader(shaderProgramRed, vertexShader);
  glAttachShader(shaderProgramRed, fragmentShaderRed);
  glLinkProgram(shaderProgramRed);

  unsigned int shaderProgramGreen = glCreateProgram();
  glAttachShader(shaderProgramGreen, vertexShader);
  glAttachShader(shaderProgramGreen, fragmentShaderGreen);
  glLinkProgram(shaderProgramGreen);

  unsigned int shaderProgramBlue = glCreateProgram();
  glAttachShader(shaderProgramBlue, vertexShader);
  glAttachShader(shaderProgramBlue, fragmentShaderBlue);
  glLinkProgram(shaderProgramBlue);

  float vertices[12+12+9];
  miCasa.get_vertices(vertices);

  unsigned int indices[6+6+3];
  miCasa.get_indices(indices);

  glGenVertexArrays(3, miCasa.VAOs);
  glGenBuffers(3, miCasa.VBOs);
  glGenBuffers(3, miCasa.EBOs);

    // Pared setup
  glBindVertexArray(miCasa.VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, miCasa.VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, miCasa.pared.vertices().size() * sizeof(float), miCasa.pared.vertices().data(), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, miCasa.EBOs[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, miCasa.pared.indices().size() * sizeof(unsigned int), miCasa.pared.indices().data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

    // Techo setup
  glBindVertexArray(miCasa.VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, miCasa.VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, miCasa.techo.vertices().size() * sizeof(float), miCasa.techo.vertices().data(), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, miCasa.EBOs[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, miCasa.techo.indices().size() * sizeof(unsigned int), miCasa.techo.indices().data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

    // Puerta setup
  glBindVertexArray(miCasa.VAOs[2]);
  glBindBuffer(GL_ARRAY_BUFFER, miCasa.VBOs[2]);
  glBufferData(GL_ARRAY_BUFFER, miCasa.puerta.vertices().size() * sizeof(float), miCasa.puerta.vertices().data(), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, miCasa.EBOs[2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, miCasa.puerta.indices().size() * sizeof(unsigned int), miCasa.puerta.indices().data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

    // Render loop
  while (!glfwWindowShouldClose(window)) {
    miCasa.get_vertices(vertices);

    glBindBuffer(GL_ARRAY_BUFFER, miCasa.VBOs[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, miCasa.pared.vertices().size() * sizeof(float), miCasa.pared.vertices().data());

    glBindBuffer(GL_ARRAY_BUFFER, miCasa.VBOs[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, miCasa.techo.vertices().size() * sizeof(float), miCasa.techo.vertices().data());

    glBindBuffer(GL_ARRAY_BUFFER, miCasa.VBOs[2]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, miCasa.puerta.vertices().size() * sizeof(float), miCasa.puerta.vertices().data());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (renderMode == GL_LINES) {
      glLineWidth(50.0f);
    } else {
      glLineWidth(1.0f);
    }

    if (renderMode == GL_POINTS) {
      glPointSize(10.0f);
    } else {
      glPointSize(1.0f);
    }

    if (renderMode == GL_TRIANGLES) {
      glUseProgram(shaderProgramWhite);
    } else if (renderMode == GL_LINES) {
      glUseProgram(shaderProgramGreen);
    } else if (renderMode == GL_POINTS) {
      glUseProgram(shaderProgramRed); 
    }
    glBindVertexArray(miCasa.VAOs[0]);
    glDrawElements(renderMode, 36, GL_UNSIGNED_INT, 0);

    if (renderMode == GL_TRIANGLES) {
      glUseProgram(shaderProgramBlack);
    } else if (renderMode == GL_LINES) {
      glUseProgram(shaderProgramBlue);
    } else if (renderMode == GL_POINTS) {
      glUseProgram(shaderProgramWhite);
    }
    glBindVertexArray(miCasa.VAOs[1]);
    glDrawElements(renderMode, 36, GL_UNSIGNED_INT, 0);

    if (renderMode == GL_TRIANGLES) {
      glUseProgram(shaderProgramBlack);
    } else if (renderMode == GL_LINES) {
      glUseProgram(shaderProgramBlue);
    } else if (renderMode == GL_POINTS) {
      glUseProgram(shaderProgramWhite);
    }
    glBindVertexArray(miCasa.VAOs[2]);
    glDrawElements(renderMode, 36, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(3, miCasa.VAOs);
  glDeleteBuffers(3, miCasa.VBOs);
  glDeleteBuffers(3, miCasa.EBOs);

  glDeleteShader(vertexShader);

  glDeleteProgram(shaderProgramWhite);
  glDeleteProgram(shaderProgramBlack);
  glDeleteProgram(shaderProgramRed);
  glDeleteProgram(shaderProgramGreen);
  glDeleteProgram(shaderProgramBlue);

  glDeleteShader(fragmentShaderRed);
  glDeleteShader(fragmentShaderGreen);
  glDeleteShader(fragmentShaderBlue);
  glDeleteShader(fragmentShaderWhite);
  glDeleteShader(fragmentShaderBlack);
   
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    miCasa.move(moveRight);
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    miCasa.move(moveLeft);
  }
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    miCasa.move(moveUp);
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    miCasa.move(moveDown);
  }
  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
    renderMode = GL_TRIANGLES;
  }
  if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
    renderMode = GL_LINES;
  }
  if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
    renderMode = GL_POINTS;
  }
}
