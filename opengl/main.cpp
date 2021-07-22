#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_s.h>

#include <iostream>
#include <filesystem>
#include <math.h>

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
        // positions         // colors
        0.0f, 0.5f, 0.0f,  0.2f, 0.6f, 1.0f,  // bottom right
        -0.2f, 0.3f, 0.0f,  0.2f, 0.6f, 1.0f,  // bottom left
        0.0f, 0.3f, 0.0f,  0.2f, 0.6f, 1.0f,   // top
        //triangle 2
        // positions         // colors
        0.0f, 0.3f, 0.0f,  0.2f, 0.8f, 0.4f,  // bottom right
        -0.2f, 0.0f, 0.0f,  0.2f, 0.8f, 0.4f,  // bottom left
        0.0f, -0.3f, 0.0f,  0.2f, 0.8f, 0.4f,   // top
        //triangle 3
        // positions         // colors
        0.0f, 0.2f, 0.0f,  1.0f, 0.8f, 0.0f,  // bottom right
        0.0f, -0.25f, 0.0f,  1.0f, 0.8f, 0.0f,  // bottom left
        0.3f, -0.25f, 0.0f,  1.0f, 0.8f, 0.0f,   // top
        //triangle 4
        // positions         // colors
        -0.2f, 0.0f, 0.0f,  1.0f, 0.4f, 0.4f,  // bottom right
        -0.3f, -0.15, 0.0f,  1.0f, 0.4f, 0.4f,  // bottom left
        -0.2f, -0.3f, 0.0f,  1.0f, 0.4f, 0.4f,   // top
        //triangle 5
        // positions         // colors
        -0.2f, 0.0f, 0.0f,  1.0f, 0.4f, 0.4f, // bottom right
        -0.2f, -0.3f, 0.0f,  1.0f, 0.4f, 0.4f,  // bottom left
        -0.1f, -0.15f, 0.0f,  1.0f, 0.4f, 0.4f,  // top
        //triangle 6
        // positions         // colors
        -0.2f, -0.3f, 0.0f,   1.0f, 0.6f, 0.2f,  // bottom right
        -0.1f, -0.15f, 0.0f,  1.0f, 0.6f, 0.2f,  // bottom left
        0.0f, -0.3f, 0.0f,  1.0f, 0.6f, 0.2f,   // top
        //triangle 7
        // positions         // colors
        -0.2f, -0.3f, 0.0f,  0.6f, 0.8f, 0.2f,  // bottom right
        -0.1f, -0.45f, 0.0f,  0.6f, 0.8f, 0.2f,  // bottom left
        0.05f, -0.3f, 0.0f,  0.6f, 0.8f, 0.2f,   // top
        //triangle 8
        // positions         // colors
        -0.1f, -0.45f, 0.0f,  0.4f, 0.4f, 0.8f,  // bottom right
        0.05f, -0.3f, 0.0f,  0.4f, 0.4f, 0.8f,  // bottom left
        0.05f, -0.45f, 0.0f,  0.4f, 0.4f, 0.8f,   // top
        //triangle 9
        // positions         // colors
        0.05f, -0.3f, 0.0f,  0.4f, 0.4f, 0.8f,  // bottom right
        0.05f, -0.45f, 0.0f,  0.4f, 0.4f, 0.8f,  // bottom left
        0.2f, -0.3f, 0.0f,  0.4f, 0.4f, 0.8f,   // top
        
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

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
