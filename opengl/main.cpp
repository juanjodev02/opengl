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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1722951165 - Juan Jaramillo", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("shaders/practica_shader_class.vs", "shaders/practica_shader_class.fs");
    Shader ourShader_2("shaders/practica_shader_class-2.vs", "shaders/practica_shader_class-2.fs");
    
    //Iniciamos los vertices
    float vertices_1[] = {
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
    };
    
    float vertices_2[] = {
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

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    
    //setup group 1
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    glEnableVertexAttribArray(2);
    
    //setup group 2
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    glEnableVertexAttribArray(2);

    // texture 1
    unsigned int texture_1;
    glGenTextures(1, &texture_1);
    glBindTexture(GL_TEXTURE_2D, texture_1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("textures/texture1.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 1" << std::endl;
    }
    stbi_image_free(data);
    
    // texture 2
    unsigned int texture_2;
    glGenTextures(1, &texture_2);
    glBindTexture(GL_TEXTURE_2D, texture_2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width_2, height_2, nrChannels_2;
    unsigned char* data_2 = stbi_load("textures/texture2.jpg", &width_2, &height_2, &nrChannels_2, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 2" << std::endl;
    }
    stbi_image_free(data_2);
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // bind texture 1
        glBindTexture(GL_TEXTURE_2D, texture_1);

        // use shaders_1
        ourShader.use();
        //Define uniform value
        float timeValue = glfwGetTime()*3;
        float dinamicValue = sin(timeValue) / 2.0f + 0.5f;
        //Send uniform value
        ourShader.setFloat("dinamicValue", dinamicValue);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 27);
        
        //bind texture 2
        glBindTexture(GL_TEXTURE_2D, texture_2);
        //use shaders_2
        ourShader_2.use();
        //Send uniform value
        ourShader.setFloat("dinamicValue", dinamicValue);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 27);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);

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
