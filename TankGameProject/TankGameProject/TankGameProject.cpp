// Lab 9 - Blending.cpp : Defines the entry point for the console application.
//
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h> 
#include <vector>

#include <GL/glew.h>

#define GLM_FORCE_CTOR_INIT 
#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Shader.h"
#include "Camera.h"
#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

// settings
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






    //Mountain texture
    unsigned int mountainTexture = CreateTexture(strExePath + "\\mountain.jpg");
    // Floor texture
    unsigned int floorTexture = CreateTexture(strExePath + "\\grass.jpg");

    // Grass texture
    unsigned int cloudTexture = CreateTexture(strExePath + "\\cloud.png");

    // Create camera
    pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0, 1.0, 3.0));

    Shader shaderFloor("Floor.vs", "Floor.fs");
    Shader shaderBlending("blending.vs", "blending.fs");
    shaderBlending.SetInt("texture1", 0);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);
        glClearColor(0.1f, 0.1f, 1.0f, 1.0f);

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

