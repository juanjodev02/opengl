#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>



#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


unsigned int loadTexture(const char *path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(2.7f, -0.3f, 1.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Juan Jaramillo | Lesly Tipanluiza", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

        // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/shaders/shader_exercise15t5_casters.vs", "C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/shaders/shader_exercise15t5_casters.fs");
    Shader lightCubeShader("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/shaders/shader_exercise15_lightcube.vs", "C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/shaders/shader_exercise15_lightcube.fs");
    Shader modelShader("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/shaders/shader_exercise16_mloading.vs", "C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/shaders/shader_exercise16_mloading.fs");
 //   Shader lightMoon("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/shaders/shader_exercise14t3_materials.vs", "C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/shaders/shader_exercise14t3_materials.fs");




    Model sidewalk("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/model/sidewalk/sidewalk.obj");
    Model lamppost("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/model/lamp/lamp.obj");
    Model building_1("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/model/building/building.obj");
    Model forest("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/model/forest/forest.obj");
    Model ruinas("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/model/pestkapelle/pestkapelle.obj");
    Model house("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/model/house/house.obj");
    Model moon("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/model/moon/moon.obj");
   Model cart("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/model/cart/cart.obj");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

 float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.0f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.0f, -0.5f, 0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.0f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    };
 //CUBES
 float cubos[] = {
     // positions          // normals           // texture coords
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
 };

 glm::vec3 cubePositions[] = {
     glm::vec3(4.0f, -0.3f,3.0f),
     glm::vec3(6.0f, -0.3f,6.0f),
     glm::vec3(-1.5f, -0.3f, 3.5f),
     glm::vec3(-5.8f, -0.3f, 3.3f),
 };


//Exercise 15 Task 5
// positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(2.6f,  1.2f,  -10.0f), //PRIMERA 
        glm::vec3(2.6f,  1.2f,  1.0f),//final
        glm::vec3(2.6f,  1.2f,  -6.0f),
        glm::vec3(2.6f,  1.2f,  -3.0f),
        glm::vec3(-3.0f, 20.0f, -25.0f)
        
    };
    
 // first, configure the cube's VAO (and VBO)
 unsigned int VBO, cubeVAO;
 glGenVertexArrays(1, &cubeVAO);
 glGenBuffers(1, &VBO);

 glBindBuffer(GL_ARRAY_BUFFER, VBO);
 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

 glBindVertexArray(cubeVAO);
 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
 glEnableVertexAttribArray(0);
 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
 glEnableVertexAttribArray(1);
 glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
 glEnableVertexAttribArray(2);

 //draw cubes
 unsigned int VAO1, VBO1;
 glGenVertexArrays(1, &VAO1);
 glGenBuffers(1, &VBO1);

 glBindBuffer(GL_ARRAY_BUFFER, VBO1);
 glBufferData(GL_ARRAY_BUFFER, sizeof(cubos), cubos, GL_STATIC_DRAW);
 glBindVertexArray(VAO1);
 // position attribute
 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
 glEnableVertexAttribArray(0);
 // normal attribute
 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
 glEnableVertexAttribArray(1);
 //texture attribute
 glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
 glEnableVertexAttribArray(2);
 




 // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
 unsigned int lightCubeVAO;
 glGenVertexArrays(1, &lightCubeVAO);
 glBindVertexArray(lightCubeVAO);
 glBindBuffer(GL_ARRAY_BUFFER, VBO);
 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
 glEnableVertexAttribArray(0);

 // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
 unsigned int diffuseMap = loadTexture("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/textures/street.jpg");
 unsigned int specularMap = loadTexture("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/textures/street.png");
 
 //Give texture diffuse
    unsigned int diffuseMap1 = loadTexture("C:/Users/Lesly/Desktop/C++/OpenGL/OpenGL_class/textures/container2.png");



    // shader configuration
    // --------------------
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
   // lightingShader.setInt("material.diffuse", 2);

    glm::vec3 pointLightColors[] = {
  glm::vec3(0.3f, 0.1f, 0.1f),
  glm::vec3(0.3f, 0.1f, 0.1f),
  glm::vec3(0.3f, 0.1f, 0.1f),
  glm::vec3(0.3f, 0.1f, 0.1f),
  glm::vec3(0.0f, 0.5f, 0.6f)
    };


 // render loop
 // -----------
 while (!glfwWindowShouldClose(window))
 {
     // per-frame time logic
     // --------------------
     float currentFrame = glfwGetTime();
     deltaTime = currentFrame - lastFrame;
     lastFrame = currentFrame;

     // input
     // -----
     processInput(window);

     // render
     // ------
  //   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
     // be sure to activate shader when setting uniforms/drawing objects

     lightingShader.use();




     lightingShader.setVec3("viewPos", camera.Position);
     lightingShader.setFloat("material.shininess", 32.0f);


     //directional light
     lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
     lightingShader.setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);
     lightingShader.setVec3("dirLight.diffuse", 0.05f, 0.05f, 0.05);
     lightingShader.setVec3("dirLight.specular", 0.8f, 0.8f, 0.8f);
     // point light 1
     lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
     lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.008, pointLightColors[0].y * 0.008, pointLightColors[0].z * 0.008);
     lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
     lightingShader.setVec3("pointLights[0].specular", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
     lightingShader.setFloat("pointLights[0].constant", 1.0f);
     lightingShader.setFloat("pointLights[0].linear", 0.09);
     lightingShader.setFloat("pointLights[0].quadratic", 0.032);
     // point light 2
     lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
     lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.08, pointLightColors[1].y * 0.08, pointLightColors[1].z * 0.08);
     lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
     lightingShader.setVec3("pointLights[1].specular", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
     lightingShader.setFloat("pointLights[1].constant", 1.0f);
     lightingShader.setFloat("pointLights[1].linear", 0.09);
     lightingShader.setFloat("pointLights[1].quadratic", 0.032);
     // point light 3
     lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
     lightingShader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.08, pointLightColors[2].y * 0.08, pointLightColors[2].z * 0.08);
     lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
     lightingShader.setVec3("pointLights[2].specular", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
     lightingShader.setFloat("pointLights[2].constant", 1.0f);
     lightingShader.setFloat("pointLights[2].linear", 0.09);
     lightingShader.setFloat("pointLights[2].quadratic", 0.032);
     //point light 4
     lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
     lightingShader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.08, pointLightColors[3].y * 0.08, pointLightColors[3].z * 0.08);
     lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
     lightingShader.setVec3("pointLights[3].specular", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
     lightingShader.setFloat("pointLights[3].constant", 1.0f);
     lightingShader.setFloat("pointLights[3].linear", 0.09);
     lightingShader.setFloat("pointLights[3].quadratic", 0.032);
     //point light 5
     lightingShader.setVec3("pointLights[3].position", pointLightPositions[4]);
     lightingShader.setVec3("pointLights[3].ambient", pointLightColors[4].x * 0.1, pointLightColors[4].y * 0.1, pointLightColors[4].z * 0.1);
     lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[4].x, pointLightColors[4].y, pointLightColors[4].z);
     lightingShader.setVec3("pointLights[3].specular", pointLightColors[4].x, pointLightColors[4].y, pointLightColors[4].z);
     lightingShader.setFloat("pointLights[3].constant", 1.0f);
     lightingShader.setFloat("pointLights[3].linear", 0.014);
     lightingShader.setFloat("pointLights[3].quadratic", 0.0007);
     // spotLight
     lightingShader.setVec3("spotLight.position", camera.Position.x, camera.Position.y, camera.Position.z);
     lightingShader.setVec3("spotLight.direction", camera.Front.x, camera.Front.y, camera.Front.z);
     lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
     lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
     lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
     lightingShader.setFloat("spotLight.constant", 1.0f);
     lightingShader.setFloat("spotLight.linear", 0.09);
     lightingShader.setFloat("spotLight.quadratic", 0.032);
     lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
     lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


     // view/projection transformations
     glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
     glm::mat4 view = camera.GetViewMatrix();
     lightingShader.setMat4("projection", projection);
     lightingShader.setMat4("view", view);


     // world transformation
     glm::mat4 model = glm::mat4(1.0f);
     lightingShader.setMat4("model", model);

     // bind diffuse map
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, diffuseMap);
     
    
     // bind specular map
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, specularMap);
     glBindVertexArray(cubeVAO);



  



     //DRAW CUBES
     for (unsigned int i = 0; i < 4; i++)
     {
         // calculate the model matrix for each object and pass it to shader before drawing
         glm::mat4 modelA= glm::mat4(1.0f);
        
         modelA= glm::translate(modelA, cubePositions[i]);
         float angle = 20.0f * i;
         modelA = glm::rotate(modelA, glm::radians(angle), glm::vec3(0.0f, 0.1f, 0.0f));
         modelA = glm::scale(modelA, glm::vec3(0.3));
         lightingShader.setMat4("model", modelA);

        // glActiveTexture(GL_TEXTURE2);
       //  glBindTexture(GL_TEXTURE_2D, diffuseMap1);
         // render the cube
         glBindVertexArray(VAO1);
     // render the cube
         glDrawArrays(GL_TRIANGLES, 0, 36);
     }




     
     int streetRepeat = 40;

     // RENDER STREET
     float initalStreetPosition = 4.0f;
     
     for (unsigned int i = 0; i < streetRepeat; i++){
        glm::mat4 model2 = glm::mat4(1.0f);
        model = glm::translate(model2, glm::vec3( 0.0f,  -0.8f, initalStreetPosition));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setMat4("model", model);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
         model2 = glm::mat4(1.0f);
         model = glm::translate(model2, glm::vec3( 1.0f,  -0.8f, initalStreetPosition));
         model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
         lightingShader.setMat4("model", model);
         glDrawArrays(GL_TRIANGLES, 0, 6);
         
         model2 = glm::mat4(1.0f);
         model = glm::translate(model2, glm::vec3( 2.0f,  -0.8f, initalStreetPosition));
         model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
          initalStreetPosition -= 0.5f;
         lightingShader.setMat4("model", model);
         glDrawArrays(GL_TRIANGLES, 0, 6);
     }



     /*

        //RENDER SIDEWALKS
         modelShader.use();
         modelShader.setMat4("projection", projection);
         modelShader.setMat4("view", view);
     float inital = 3.1f;

     for (unsigned int i = 0; i < streetRepeat / 2; i++){
        //calculate the model matrix for each object and pass it to the shader before drawing
         glm::mat4 model3 = glm::mat4(1.0f);
         model3 = glm::translate(model3, glm::vec3(2.5f,  -0.3f, inital));
         inital -= 1.0f;
         model3 = glm::rotate(model3, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
         model3 = glm::scale(model3, glm::vec3(0.04f, 0.04f, 0.04f));
         modelShader.setMat4("model", model3);
         sidewalk.Draw(modelShader);
     }
     
     inital = 4.0f;
     
     for (unsigned int i = 0; i < streetRepeat / 2; i++){
         glm::mat4 model3 = glm::mat4(1.0f);
        //calculate the model matrix for each object and pass it to the shader before drawing
         model3 = glm::translate(model3, glm::vec3(-0.5f,  -0.3f, inital));
         inital -= 1.0f;
         model3 = glm::rotate(model3, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model3 = glm::scale(model3, glm::vec3(0.04f, 0.04f, 0.04f));
         modelShader.setMat4("model", model3);
         sidewalk.Draw(modelShader);
     }
     */


     
     // RENDER LAMPPOST 1
     
     glm::mat4 model3 = glm::mat4(1.0f);
     model3 = glm::translate(model3, glm::vec3(2.7f,  -0.3f, 1.0f));
     model3 = glm::scale(model3, glm::vec3(0.04f, 0.04f, 0.04f));
     modelShader.setMat4("model", model3);
     lightingShader.setMat4("model", model3);
     lamppost.Draw(modelShader);
     
     // RENDER LAMPPOST 2
     
     glm::mat4 model7 = glm::mat4(1.0f);
     model7 = glm::translate(model7, glm::vec3(2.7f,  -0.3f, (-streetRepeat * 0.5f) + 17.0f));
     model7 = glm::scale(model7, glm::vec3(0.04f, 0.04f, 0.04f));
     modelShader.setMat4("model", model7);
     lightingShader.setMat4("model", model7);
     lamppost.Draw(modelShader);
     
     // RENDER LAMPPOST 3
     
     glm::mat4 model8 = glm::mat4(1.0f);
     model8 = glm::translate(model8, glm::vec3(2.7f,  -0.3f, (-streetRepeat * 0.5f) + 10.0f));
     model8 = glm::scale(model8, glm::vec3(0.04f, 0.04f, 0.04f));
     modelShader.setMat4("model", model8);
     lightingShader.setMat4("model", model8);
     lamppost.Draw(modelShader);

     
     //lapppost 4
     glm::mat4 modelC = glm::mat4(1.0f);
     modelC = glm::translate(modelC, glm::vec3(2.7f, -0.3f, (-streetRepeat * 0.5f) + 14.0f));
     modelC = glm::scale(modelC, glm::vec3(0.04f, 0.04f, 0.04f));
     modelShader.setMat4("model", modelC);
     lightingShader.setMat4("model", modelC);
     lamppost.Draw(modelShader);
     
     
     
     // RENDER BUILD
     glm::mat4 model4 = glm::mat4(1.0f);
     model4 = glm::translate(model4, glm::vec3(-1.5f, -0.5f, 1.0f));
     //model4 = glm::rotate(model4, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 0.0f));
     model4 = glm::scale(model4, glm::vec3(0.2f, 0.2f, 0.2f));
     lightingShader.setMat4("model", model4);
     building_1.Draw(modelShader);
     
     
     
     // RENDER FOREST
     glm::mat4 model5 = glm::mat4(1.0f);
     model5 = glm::translate(model5, glm::vec3(-1.0f,  -0.5f, 1.0f));
     model5 = glm::scale(model5, glm::vec3(0.5f, 0.5f, 0.5f));
     model5 = glm::rotate(model5, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
     modelShader.setMat4("model", model5);
     lightingShader.setMat4("model", model5);
     forest.Draw(modelShader);
     
     
     // RENDER RUINAS
     glm::mat4 model6 = glm::mat4(1.0f);
     model6 = glm::translate(model6, glm::vec3(0.6f,  -0.7f, (-streetRepeat * 0.5f) + 5.0f));
     model6 = glm::scale(model6, glm::vec3(0.7f, 0.7f, 0.7f));
     model6 = glm::rotate(model6, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
     modelShader.setMat4("model", model6);
     lightingShader.setMat4("model", model6);
     ruinas.Draw(modelShader);
     
     
     // RENDER HOUSE
     
     glm::mat4 model9 = glm::mat4(1.0f);
     model9 = glm::translate(model9, glm::vec3(-2.0f,  -0.3f, (-streetRepeat * 0.5f) + 18.0f));
     model9 = glm::scale(model9, glm::vec3(0.2f, 0.2f, 0.2f));
     model9 = glm::rotate(model9, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
     modelShader.setMat4("model", model9);
     lightingShader.setMat4("model", model9);
     house.Draw(modelShader);
     
     
     // RENDER MOON
    
     glm::mat4 model10 = glm::mat4(1.0f);
     model10 = glm::translate(model10, glm::vec3(-3.0f, 20.0f, -40.0f));
     model10 = glm::scale(model10, glm::vec3(0.1f, 0.1f, 0.1f));
     modelShader.setMat4("model", model10);
     lightingShader.setMat4("model", model10);
     moon.Draw(modelShader);
     
     // RENDER CART
     
     glm::mat4 model11 = glm::mat4(1.0f);
     model11 = glm::translate(model11, glm::vec3(2.0f,  -0.17f, (-streetRepeat * 0.5f) + 18.0f));
     model11 = glm::scale(model11, glm::vec3(0.3f, 0.3f, 0.3f));
     model11 = glm::rotate(model11, glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
     modelShader.setMat4("model", model11);
     lightingShader.setMat4("model", model11);
     cart.Draw(modelShader);
    
     
     
     //Light Position Moon
     glm::mat4 modeln = glm::mat4(1.0f);
     modeln = glm::mat4(1.0f);
     modeln = glm::translate(modeln, lightPos);
     modeln = glm::scale(modeln, glm::vec3(0.5f)); // a smaller cube


     // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
     // -------------------------------------------------------------------------------
     //Exercise 15 Task 5
         // also draw the lamp object(s)
     /*
     lightCubeShader.use();
     lightCubeShader.setMat4("projection", projection);
     lightCubeShader.setMat4("view", view);

     // we now draw as many light bulbs as we have point lights.
     
     glBindVertexArray(lightCubeVAO);
     for (unsigned int i = 0; i < 4; i++)
     {
         model = glm::mat4(1.0f);
         model = glm::translate(model, pointLightPositions[i]);
         model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
         lightCubeShader.setMat4("model", model);
         glDrawArrays(GL_TRIANGLES, 0, 36);
     }*/


     glfwSwapBuffers(window);
     glfwPollEvents();
 }

 // optional: de-allocate all resources once they've outlived their purpose:
 // ------------------------------------------------------------------------
 glDeleteVertexArrays(1, &cubeVAO);
 glDeleteVertexArrays(1, &VAO1);
 glDeleteVertexArrays(1, &lightCubeVAO);
 glDeleteBuffers(1, &VBO);
 glDeleteBuffers(1, &VBO1);

 // glfw: terminate, clearing all previously allocated GLFW resources.
 // ------------------------------------------------------------------
 glfwTerminate();
 return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

//Exercise 14 Task 2
// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
