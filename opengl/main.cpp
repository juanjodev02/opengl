#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camara Settings
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Ligth settings
glm::vec3 lightPos1(1.2f, 1.0f, 2.0f);
glm::vec3 lightPos2(-1.2f, 1.0f, -2.0f);

glm::vec4 ligthPos1Color (1.0f); //white
glm::vec4 ligthPos2Color (1.0f, 0.0f, 0.0f, 1.0f); //red

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
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Config mouse envents
    glfwSetCursorPosCallback(window, mouse_callback);
    // Config scroll events
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // Enable z buffer
    glEnable(GL_DEPTH_TEST);
    
    // Load Shaders
    Shader ourShader("shaders/shader_exercise11.vs", "shaders/shader_exercise11.fs");
    Shader lightCubeShader("shaders/shader_exercise13_lightcube.vs", "shaders/shader_exercise13_lightcube.fs");

    
    // Setup position vectors
    float vertices[] = {
    // positions          // texture coords
    //CARA ATRÁS
    -0.5f, -0.5f, -0.5f,  0.725f, 0.326f,
     0.5f, -0.5f, -0.5f,  0.933f, 0.326f,
     0.5f,  0.5f, -0.5f,  0.933f, 0.58f,
     0.5f,  0.5f, -0.5f,  0.933f, 0.58f,
    -0.5f,  0.5f, -0.5f,  0.725f, 0.58f,
    -0.5f, -0.5f, -0.5f,  0.725f, 0.326f,

    //CARA FRONTAL
    -0.5f, -0.5f,  0.5f,  0.3f, 0.31f,
     0.5f, -0.5f,  0.5f,  0.51f, 0.31f,
     0.5f,  0.5f,  0.5f,  0.51f, 0.58f,
     0.5f,  0.5f,  0.5f,  0.51f, 0.58f,
    -0.5f,  0.5f,  0.5f,  0.3f, 0.58f,
    -0.5f, -0.5f,  0.5f,  0.3f, 0.31f,

    //CARA IZQUIERDA
    -0.5f,  0.5f,  0.5f,  0.085f, 0.58f,
    -0.5f,  0.5f, -0.5f,  0.295f, 0.58f,
    -0.5f, -0.5f, -0.5f,  0.295f, 0.33f,
    -0.5f, -0.5f, -0.5f,  0.295f, 0.33f,
    -0.5f, -0.5f,  0.5f,  0.085f, 0.33f,
    -0.5f,  0.5f,  0.5f,  0.085f, 0.58f,

    //CARA DERECHA
     0.5f,  0.5f,  0.5f,  0.51f, 0.58f,
     0.5f,  0.5f, -0.5f,  0.72f, 0.58f,
     0.5f, -0.5f, -0.5f,  0.72f, 0.326f,
     0.5f, -0.5f, -0.5f,  0.72f, 0.326f,
     0.5f, -0.5f,  0.5f,  0.51f, 0.326f,
     0.5f,  0.5f,  0.5f,  0.51f, 0.58f,


     //CARA ABAJO
    -0.5f, -0.5f, -0.5f,  0.3f, 0.32f,
     0.5f, -0.5f, -0.5f,  0.51f, 0.32f,
     0.5f, -0.5f,  0.5f,  0.51f, 0.07f,
     0.5f, -0.5f,  0.5f,  0.51f, 0.07f,
    -0.5f, -0.5f,  0.5f,  0.3f, 0.07f,
    -0.5f, -0.5f, -0.5f,  0.3f, 0.32f,

    //CARA ARRIBA
    -0.5f,  0.5f, -0.5f,  0.3f, 0.83f,
     0.5f,  0.5f, -0.5f,  0.3f, 0.57f,
     0.5f,  0.5f,  0.5f,  0.51f, 0.57f,
     0.5f,  0.5f,  0.5f,  0.51f, 0.57f,
    -0.5f,  0.5f,  0.5f,  0.51f, 0.83f,
    -0.5f,  0.5f, -0.5f,  0.3f, 0.83f
    };

    // Define world positions for each cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f)
    };

    // Define VBO and VAO
    unsigned int VBO, VAO;
    // Init VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
 
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //configure light VAO
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Load Textures
    unsigned int texture1, texture2;
    // Texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("textures/tnt.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // Change config to use .png files
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // Texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("textures/fire.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use textures
        glActiveTexture(GL_TEXTURE0);

        glActiveTexture(GL_TEXTURE1);
        

        // Activate shaders
        ourShader.use();
        
        // Define projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);
        
         // Define view matrix | Usage of camera class
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // Use VAO
        glBindVertexArray(VAO);

        // Render one cube for each position vectors using first texture
        for (unsigned int i = 0; i < 5; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 2 == 0)
                angle = glfwGetTime() * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);
            // Use first texture
            glBindTexture(GL_TEXTURE_2D, texture1);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        for (unsigned int i = 5; i < 8; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 2 == 0)
                angle = glfwGetTime() * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);
            // Use first texture
            glBindTexture(GL_TEXTURE_2D, texture2);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        
        lightCubeShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos2);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);
        lightCubeShader.setVec4("ligthColor", ligthPos2Color);
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
        // cube 2
        lightCubeShader.use();
        glm::mat4 model2 = glm::mat4(1.0f);
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, lightPos1);
        model2 = glm::scale(model2, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model2);
        lightCubeShader.setVec4("ligthColor", ligthPos1Color);
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    //If I want to stay in ground level (xz plane)
//    camera.Position.y = 0.0f;
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
