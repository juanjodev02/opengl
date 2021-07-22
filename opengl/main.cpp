#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_s.h>

#include <iostream>
#include <filesystem>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Juan Jaramillo", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("shaders/practica_shader_class.vs", "shaders/practica_shader_class.fs");
    
    //Iniciamos los vertices
    float vertices[] = {
        //triangle 1
        // positions            // colors               // texture position
        0.0f, 0.5f, 0.0f,       0.2f, 0.6f, 1.0f,       0.5f, 1.0f,     // A
        -0.2f, 0.3f, 0.0f,      0.2f, 0.6f, 1.0f,       0.3f, 0.8f,     // B
        0.0f, 0.3f, 0.0f,       0.2f, 0.6f, 1.0f,       0.5f, 0.8f,     // C
        //triangle 2
        // positions            // colors               // texture position
        0.0f, 0.3f, 0.0f,       0.2f, 0.8f, 0.4f,       0.5f, 0.8f,     // C
        -0.2f, 0.0f, 0.0f,      0.2f, 0.8f, 0.4f,       0.3f, 0.5f,     // E
        0.0f, -0.3f, 0.0f,      0.2f, 0.8f, 0.4f,       0.5f, 0.2f,     // K
        //triangle 3
        // positions            // colors               // texture position
        0.0f, 0.2f, 0.0f,       1.0f, 0.8f, 0.0f,       0.5f, 0.7f,     // D
        0.0f, -0.25f, 0.0f,     1.0f, 0.8f, 0.0f,       0.5f, 0.25f,     // I
        0.3f, -0.25f, 0.0f,     1.0f, 0.8f, 0.0f,       0.8f, 0.25f,     // J
        //triangle 4
        // positions            // colors               // texture position
        -0.2f, 0.0f, 0.0f,      1.0f, 0.4f, 0.4f,       0.3f, 0.5f,     // E
        -0.3f, -0.15, 0.0f,     1.0f, 0.4f, 0.4f,       0.2f, 0.35f,    // F
        -0.2f, -0.3f, 0.0f,     1.0f, 0.4f, 0.4f,       0.3f, 0.2f,     // G
        //triangle 5
        // positions            // colors               // texture position
        -0.2f, 0.0f, 0.0f,      1.0f, 0.4f, 0.4f,       0.3f, 0.5f,     // E
        -0.2f, -0.3f, 0.0f,     1.0f, 0.4f, 0.4f,       0.3f, 0.2f,     // G
        -0.1f, -0.15f, 0.0f,    1.0f, 0.4f, 0.4f,       0.4f, 0.35f,    // H
        //triangle 6
        // positions            // colors               // texture position
        -0.2f, -0.3f, 0.0f,     1.0f, 0.6f, 0.2f,       0.3f, 0.2f,     // G
        -0.1f, -0.15f, 0.0f,    1.0f, 0.6f, 0.2f,       0.4f, 0.35f,    // H
        0.0f, -0.3f, 0.0f,      1.0f, 0.6f, 0.2f,       0.5f, 0.2f,     // K
        //triangle 7
        // positions             // colors              // texture position
        -0.2f, -0.3f, 0.0f,     0.6f, 0.8f, 0.2f,       0.3f, 0.2f,     // G
        -0.1f, -0.45f, 0.0f,    0.6f, 0.8f, 0.2f,       0.4f, 0.05f,    // L
        0.05f, -0.3f, 0.0f,     0.6f, 0.8f, 0.2f,       0.55f, 0.2f,     // O
        //triangle 8
        // positions            // colors               // texture position
        -0.1f, -0.45f, 0.0f,    0.4f, 0.4f, 0.8f,       0.4f, 0.05f,    // L
        0.05f, -0.3f, 0.0f,     0.4f, 0.4f, 0.8f,       0.55f, 0.2f,    // O
        0.05f, -0.45f, 0.0f,    0.4f, 0.4f, 0.8f,       0.55f, 0.05f,   // M
        //triangle 9
        // positions            // colors               // texture position
        0.05f, -0.3f, 0.0f,     0.4f, 0.4f, 0.8f,       0.55f, 0.2f,    // O
        0.05f, -0.45f, 0.0f,    0.4f, 0.4f, 0.8f,       0.55f, 0.05f,   // M
        0.2f, -0.3f, 0.0f,      0.4f, 0.4f, 0.8f,       0.7f, 0.2f,      // N
        
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    glEnableVertexAttribArray(2);

    // load texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char* data = stbi_load("textures/paisaje.jpg", &width, &height, &nrChannels, 0);
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // bind texture
        glBindTexture(GL_TEXTURE_2D, texture);

        //Define uniform value
//        float timeValue = glfwGetTime()*3;
//        float greenValue = sin(timeValue) / 2.0f + 0.5f;

        // Usamos el shader class
        ourShader.use();
        //Send uniform value
//        ourShader.setFloat("GreenValue", greenValue);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 27);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
