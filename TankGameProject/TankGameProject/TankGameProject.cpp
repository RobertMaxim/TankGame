//// Lab 9 - Blending.cpp : Defines the entry point for the console application.
////
//#include "Mesh.h"
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//Camera* pCamera = nullptr;
//
//void Cleanup()
//{
//    delete pCamera;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//// timing
//double deltaTime = 0.0f;    // time between current frame and last frame
//double lastFrame = 0.0f;
//
//int main(int argc, char** argv)
//{
//    std::string strFullExeFileName = argv[0];
//    std::string strExePath;
//    const size_t last_slash_idx = strFullExeFileName.rfind('\\');
//    if (std::string::npos != last_slash_idx) {
//        strExePath = strFullExeFileName.substr(0, last_slash_idx);
//    }
//
//
//    // glfw: initialize and configure
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // glfw window creation
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab 9", NULL, NULL);
//    if (window == NULL) {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    glewInit();
//
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    // Floor vertices
//    float floorVertices[] = {
//        // positions          // texture Coords 
//             25.0f, -0.5f,  25.0f,    25.0f,  0.0f,
//            -25.0f, -0.5f,  25.0f,    0.0f,  0.0f,
//            -25.0f, -0.5f, -25.0f,    0.0f, 25.0f,
//
//            25.0f, -0.5f,  25.0f,     25.0f,  0.0f,
//            -25.0f, -0.5f, -25.0f,    0.0f, 25.0f,
//            25.0f, -0.5f, -25.0f,     25.0f, 25.0f
//    };
//    // Cloud vertices
//    float cloudVertices[]{
//        0.8f, 0.8f,  0.0f,  1.0f, 0.0f,
//        -0.8f, 0.8f, 0.0f, 0.0f, 0.0f,
//        -0.8f, -0.8f, 0.0f,  0.0f, 1.0f,
//
//        0.8f, 0.8f,  0.0f,  1.0f, 0.0f,
//        -0.8f, -0.8f, 0.0f,  0.0f, 1.0f,
//        0.8f, -0.8f, 0.0f,  1.0f, 1.0f,
//
//        -0.8f, -0.8f,  0.0f,  1.0f, 0.0f,
//        0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
//        0.8f, 0.8f, 0.0f,  0.0f, 1.0f,
//
//        -0.8f, -0.8f,  0.0f,  1.0f, 0.0f,
//        0.8f, 0.8f, 0.0f,  0.0f, 1.0f,
//        -0.8f, 0.8f, 0.0f,  1.0f, 1.0f
//    };
//
//    float mountainVertices[]{
//        0.5f, 0.5f,  0.0f,  1.0f, 0.0f,
//        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
//        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,
//
//        0.5f, 0.5f,  0.0f,  1.0f, 0.0f,
//        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,
//        0.5f, -0.5f, 0.0f,  1.0f, 1.0f,
//
//        -0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
//        0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
//        0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
//
//        -0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
//        0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
//        -0.5f, 0.5f, 0.0f,  1.0f, 1.0f
//    };
//
//
//    //Grass VAO si VBO
//    unsigned int cloudVAO, cloudVBO;
//    glGenVertexArrays(1, &cloudVAO);
//    glGenBuffers(1, &cloudVBO);
//    glBindVertexArray(cloudVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cloudVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cloudVertices), &cloudVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//
//    // Floor VAO si VBO
//    unsigned int floorVAO, floorVBO;
//    glGenVertexArrays(1, &floorVAO);
//    glGenBuffers(1, &floorVBO);
//    glBindVertexArray(floorVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), &floorVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//
//
//    /*Texture textures[] = {
//        Texture((strExePath + "\\grass.jpg").c_str(),"diffuse",0,GL_RGB,GL_UNSIGNED_BYTE),
//        Texture((strExePath + "\\cloud.png").c_str(),"specular", 0,GL_RGB,GL_UNSIGNED_BYTE)
//    };
//    */
//
//    Texture grass,cloud;
//    unsigned int floorTexture = grass.CreateTexture(strExePath+"\\grass.jpg");
//    unsigned int cloudTexture = cloud.CreateTexture(strExePath+"\\cloud.png");
//    // Create camera
//    
//    pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));
//
//    Shader shaderFloor("Floor.vs", "Floor.fs");
//    Shader shaderBlending("blending.vs", "blending.fs");
//    shaderBlending.SetInt("texture1", 0);
//
//    // render loop
//    while (!glfwWindowShouldClose(window)) {
//        // per-frame time logic
//        double currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        processInput(window);
//        glClearColor(0.1f, 0.1f, 1.0f, 1.0f);
//
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        glm::mat4 model = glm::mat4(1.0);
//
//        shaderFloor.Use();
//        glm::mat4 projection = pCamera->GetProjectionMatrix();
//        glm::mat4 view = pCamera->GetViewMatrix();
//        shaderFloor.SetMat4("projection", projection);
//        shaderFloor.SetMat4("view", view);
//
//        // Draw floor
//        shaderBlending.Use();
//        shaderBlending.SetMat4("projection", projection);
//        shaderBlending.SetMat4("view", view);
//
//
//
//        /*glBindVertexArray(cloudVAO);
//        glBindTexture(GL_TEXTURE_2D, grassTexture);
//        model = glm::mat4();
//        shaderBlending.SetMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 6);*/
//
//        glBindVertexArray(floorVAO);
//        glBindTexture(GL_TEXTURE_2D, floorTexture);
//        model = glm::mat4();
//        shaderFloor.SetMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
//        shaderBlending.Use();
//        shaderBlending.SetMat4("projection", projection);
//        shaderBlending.SetMat4("view", view);
//        //add clouds
//        std::vector<glm::vec3> clouds;
//        clouds.push_back(glm::vec3(4.0f, 2.0f, -4.0f));
//        clouds.push_back(glm::vec3(-2.8f, 2.0f, -2.0f));
//        clouds.push_back(glm::vec3(3.5f, 2.0f, -1.25f));
//        clouds.push_back(glm::vec3(-4.5f, 2.5f, -1.5f));
//        clouds.push_back(glm::vec3(2.0f, 2.0f, 0.0f));
//        clouds.push_back(glm::vec3(1.5f, 2.9f, 0.0f));
//        clouds.push_back(glm::vec3(-1.5f, 2.5f, 1.0f));
//        clouds.push_back(glm::vec3(4.5f, 2.0f, 2.0f));
//        clouds.push_back(glm::vec3(-3.5f, 2.0f, 1.0f));
//        clouds.push_back(glm::vec3(1.5f, 2.0f, 1.25f));
//        clouds.push_back(glm::vec3(-0.0f, 2.5f, 0.5f));
//        clouds.push_back(glm::vec3(0.0f, 2.0f, -3.0f));
//
//        clouds.push_back(glm::vec3(2.0f, 1.0f, 1.5f));
//        clouds.push_back(glm::vec3(-1.0f, 1.0f, 1.25f));
//        clouds.push_back(glm::vec3(1.5f, 2.0f, 4.0f));
//        // Draw vegetation
//        glBindVertexArray(cloudVAO);
//        glBindTexture(GL_TEXTURE_2D, cloudTexture);
//        for (unsigned int i = 0; i < clouds.size(); i++)
//        {
//            model = glm::mat4();
//            model = glm::translate(model, clouds[i]);
//            shaderBlending.SetMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 6);
//        }
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//
//    }
//
//    Cleanup();
//
//    // Clear floor VAO
//
//    // Clear grass VAO
//
//    // glfw: terminate, clearing all previously allocated GLFW resources
//    glfwTerminate();
//    return 0;
//}
//
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//        pCamera->ProcessKeyboard(FORWARD, (float)deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//        pCamera->ProcessKeyboard(BACKWARD, (float)deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//        pCamera->ProcessKeyboard(LEFT, (float)deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//        pCamera->ProcessKeyboard(RIGHT, (float)deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
//        pCamera->ProcessKeyboard(UP, (float)deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
//        pCamera->ProcessKeyboard(DOWN, (float)deltaTime);
//
//    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
//        int width, height;
//        glfwGetWindowSize(window, &width, &height);
//        pCamera->Reset(width, height);
//
//    }
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    pCamera->Reshape(width, height);
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    pCamera->MouseControl((float)xpos, (float)ypos);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)
//{
//    pCamera->ProcessMouseScroll((float)yOffset);
//}

// Lab 9 - Blending.cpp : Defines the entry point for the console application.
//

// settings

#include "Camera.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera* pCamera = nullptr;

void Cleanup()
{
    delete pCamera;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// timing
double deltaTime = 0.0f;    // time between current frame and last frame
double lastFrame = 0.0f;

unsigned int CreateTexture(const std::string& strTexturePath);

float skyboxVertices[] =
{
    //   Coordinates
    -100.0f, -100.0f,  100.0f,//        7--------6
     100.0f, -100.0f,  100.0f,//       /|       /|
     100.0f, -100.0f, -100.0f,//      4--------5 |
    -100.0f, -100.0f, -100.0f,//      | |      | |
    -100.0f,  100.0f,  100.0f,//      | 3------|-2
     100.0f,  100.0f,  100.0f,//      |/       |/
     100.0f,  100.0f, -100.0f,//      0--------1
    -100.0f,  100.0f, -100.0f
};

unsigned int skyboxIndices[] =
{
    // Right
    1, 2, 6,
    6, 5, 1,
    // Left
    0, 4, 7,
    7, 3, 0,
    // Top
    4, 5, 6,
    6, 7, 4,
    // Bottom
    0, 3, 2,
    2, 1, 0,
    // Back
    0, 1, 5,
    5, 4, 0,
    // Front
    3, 7, 6,
    6, 2, 3
};

int main(int argc, char** argv)
{
    std::string strFullExeFileName = argv[0];
    std::string strExePath;
    const size_t last_slash_idx = strFullExeFileName.rfind('\\');
    if (std::string::npos != last_slash_idx) {
        strExePath = strFullExeFileName.substr(0, last_slash_idx);
    }


    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab 9", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Floor vertices
    float floorVertices[] = {
        // positions          // texture Coords 
             25.0f, -0.5f,  25.0f,    25.0f,  0.0f,
            -25.0f, -0.5f,  25.0f,    0.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,    0.0f, 25.0f,

            25.0f, -0.5f,  25.0f,     25.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,    0.0f, 25.0f,
            25.0f, -0.5f, -25.0f,     25.0f, 25.0f
    };
    // Cloud vertices
    float cloudVertices[]{
        0.8f, 0.8f,  0.0f,  1.0f, 0.0f,
        -0.8f, 0.8f, 0.0f, 0.0f, 0.0f,
        -0.8f, -0.8f, 0.0f,  0.0f, 1.0f,

        0.8f, 0.8f,  0.0f,  1.0f, 0.0f,
        -0.8f, -0.8f, 0.0f,  0.0f, 1.0f,
        0.8f, -0.8f, 0.0f,  1.0f, 1.0f,

        -0.8f, -0.8f,  0.0f,  1.0f, 0.0f,
        0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
        0.8f, 0.8f, 0.0f,  0.0f, 1.0f,

        -0.8f, -0.8f,  0.0f,  1.0f, 0.0f,
        0.8f, 0.8f, 0.0f,  0.0f, 1.0f,
        -0.8f, 0.8f, 0.0f,  1.0f, 1.0f
    };

    float mountainVertices[]{
        0.5f, 0.5f,  0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,

        0.5f, 0.5f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f,

        -0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
        0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f,  1.0f, 1.0f
    };


    //Grass VAO si VBO
    unsigned int cloudVAO, cloudVBO;
    glGenVertexArrays(1, &cloudVAO);
    glGenBuffers(1, &cloudVBO);
    glBindVertexArray(cloudVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cloudVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cloudVertices), &cloudVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // Floor VAO si VBO
    unsigned int floorVAO, floorVBO;
    glGenVertexArrays(1, &floorVAO);
    glGenBuffers(1, &floorVBO);
    glBindVertexArray(floorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), &floorVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    //Mountain texture
    unsigned int mountainTexture = CreateTexture(strExePath + "\\mountain.jpg");
    // Floor texture
    unsigned int floorTexture = CreateTexture(strExePath + "\\grass.jpg");

    // Grass texture
    unsigned int cloudTexture = CreateTexture(strExePath + "\\cloud.png");

    // Create camera
    pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0, 0.0, 0.0));

    Shader shaderFloor("Floor.vs", "Floor.fs");
    Shader shaderBlending("blending.vs", "blending.fs");
    Shader skyboxShader("skybox.vs", "skybox.fs");

    //shaderBlending.SetInt("texture1", 0);
    glUseProgram(shaderBlending.GetID());
    glUniform1i(glGetUniformLocation(shaderBlending.GetID(), "texture1"), 0);

    glUseProgram(skyboxShader.GetID());
    glUniform1i(glGetUniformLocation(skyboxShader.GetID(), "skybox"), 0);

    glEnable(GL_DEPTH_CLAMP);
    glEnable(GL_CULL_FACE);
    // Keeps front faces
    glCullFace(GL_FRONT);
    // Uses counter clock-wise standard
    glFrontFace(GL_CCW);


    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::string facesCubemap[6] =
    {
        strExePath + "\\right.jpg",
        strExePath + "\\left.jpg",
        strExePath + "\\top.jpg",
        strExePath + "\\bottom.jpg",
        strExePath + "\\front.jpg",
        strExePath + "\\back.jpg"
    };

    // Creates the cubemap texture object
    unsigned int cubemapTexture;
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // This might help with seams on some systems
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // Cycles through all the textures and attaches them to the cubemap object
    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
            (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }


    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 model = glm::mat4(1.0);

        shaderFloor.Use();
        glm::mat4 projection = pCamera->GetProjectionMatrix();
        glm::mat4 view = pCamera->GetViewMatrix();
        shaderFloor.SetMat4("projection", projection);
        shaderFloor.SetMat4("view", view);

        // Draw floor
        shaderBlending.Use();
        shaderBlending.SetMat4("projection", projection);
        shaderBlending.SetMat4("view", view);



        /*glBindVertexArray(cloudVAO);
        glBindTexture(GL_TEXTURE_2D, grassTexture);
        model = glm::mat4();
        shaderBlending.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);*/



        glBindVertexArray(floorVAO);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        model = glm::mat4();
        shaderFloor.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        shaderBlending.Use();
        shaderBlending.SetMat4("projection", projection);
        shaderBlending.SetMat4("view", view);
        //add clouds
        std::vector<glm::vec3> clouds;
        clouds.push_back(glm::vec3(4.0f, 2.0f, -4.0f));
        clouds.push_back(glm::vec3(-2.8f, 2.0f, -2.0f));
        clouds.push_back(glm::vec3(3.5f, 2.0f, -1.25f));
        clouds.push_back(glm::vec3(-4.5f, 2.5f, -1.5f));
        clouds.push_back(glm::vec3(2.0f, 2.0f, 0.0f));
        clouds.push_back(glm::vec3(1.5f, 2.9f, 0.0f));
        clouds.push_back(glm::vec3(-1.5f, 2.5f, 1.0f));
        clouds.push_back(glm::vec3(4.5f, 2.0f, 2.0f));
        clouds.push_back(glm::vec3(-3.5f, 2.0f, 1.0f));
        clouds.push_back(glm::vec3(1.5f, 2.0f, 1.25f));
        clouds.push_back(glm::vec3(-0.0f, 2.5f, 0.5f));
        clouds.push_back(glm::vec3(0.0f, 2.0f, -3.0f));

        clouds.push_back(glm::vec3(2.0f, 1.0f, 1.5f));
        clouds.push_back(glm::vec3(-1.0f, 1.0f, 1.25f));
        clouds.push_back(glm::vec3(1.5f, 2.0f, 4.0f));
        // Draw vegetation
        glBindVertexArray(cloudVAO);
        glBindTexture(GL_TEXTURE_2D, cloudTexture);
        for (unsigned int i = 0; i < clouds.size(); i++)
        {

            model = glm::mat4();
            model = glm::translate(model, clouds[i]);
            shaderBlending.SetMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glDepthFunc(GL_LEQUAL);

        glUseProgram(skyboxShader.GetID());

        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
        // We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
        // The last row and column affect the translation of the skybox (which we don't want to affect)
        view = pCamera->GetViewMatrix();
        projection = pCamera->GetProjectionMatrix();
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
        // where an object is present (a depth of 1.0f will always fail against any object's depth value)
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glDepthFunc(GL_LESS);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    Cleanup();

    // Clear floor VAO
    
    // Clear grass VAO

    // glfw: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        pCamera->ProcessKeyboard(FORWARD, (float)deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        pCamera->ProcessKeyboard(BACKWARD, (float)deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        pCamera->ProcessKeyboard(LEFT, (float)deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        pCamera->ProcessKeyboard(RIGHT, (float)deltaTime);
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        pCamera->ProcessKeyboard(UP, (float)deltaTime);
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        pCamera->ProcessKeyboard(DOWN, (float)deltaTime);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        pCamera->Reset(width, height);

    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    pCamera->Reshape(width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    pCamera->MouseControl((float)xpos, (float)ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)
{
    pCamera->ProcessMouseScroll((float)yOffset);
}

unsigned int CreateTexture(const std::string& strTexturePath)
{
    unsigned int textureId = -1;

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(strTexturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format{};
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "Failed to load texture: " << strTexturePath << std::endl;
    }
    stbi_image_free(data);

    return textureId;
}