#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <thread>

#include "Shader.h"
#include "Terrain.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::vector<glm::vec3> cube_positions;

glm::vec3 cameraPos = glm::vec3(32.0f, 16.0f, 32.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float yaw = -120.0f, pitch = -30.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;
float fov = 45.0f;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = 2.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraUp;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f) {
        fov = 1.0f;
    }
    if (fov > 45.0f) {
        fov = 45.0f;
    }
}

std::vector<glm::vec3> update_cube_positions(
    std::vector<glm::vec3> cube_positions, std::vector<glm::vec3> new_cube_positions, glm::mat4 *modelMatrices) {
    for (unsigned int i = 0; i < new_cube_positions.size(); i++) {
        for (unsigned int j = 0; j < cube_positions.size(); j++) {
            if (new_cube_positions[i][0] == cube_positions[j][0] && new_cube_positions[i][2] == cube_positions[j][2]) {
                new_cube_positions[i][1] = cube_positions[j][1];
                cube_positions.erase(cube_positions.begin() + j);
                break;
            }
        }
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, new_cube_positions[i]);
        modelMatrices[i] = model;
    }

    return new_cube_positions;
}

void create_new_map_with_thread(
    Terrain terrain, int x_start, int z_start, double size,
    unsigned int octs, bool random_seed, unsigned int height_max,
    std::vector<glm::vec3> new_cube_positions, glm::mat4 *modelMatrices) {
    std::cout << "Updating map..." << std::endl;

    terrain.create_perline_noise(x_start, z_start, size, octs, random_seed);
    terrain.rescale_noise(height_max);
    new_cube_positions.clear();
    terrain.create_mountain(x_start, z_start, new_cube_positions, size);
    cube_positions = update_cube_positions(cube_positions, new_cube_positions, modelMatrices);

    std::cout << "Map update completed !!" << std::endl;
}

int main() {
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Build and compile our shader program
    Shader ourShader("texture.vs", "texture.fs");

    float vertices[] = {
        // positions        // texture coords  // TexIndex
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1,

        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1,

        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1,

        // Bottom
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0,

        // Top
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0,
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    double size = 42.0;
    unsigned int height_max = 12;
    unsigned int octs = 1;
    bool random_seed = true;
    Terrain terrain;
    int x_start = 0;
    int z_start = 0;
    terrain.create_perline_noise(x_start, z_start, static_cast<unsigned int>(size), octs, random_seed);
    terrain.rescale_noise(height_max);
    terrain.create_mountain(x_start, z_start, cube_positions, static_cast<unsigned int>(size));

    unsigned int amount = cube_positions.size();
    glm::mat4 *modelMatrices;
    modelMatrices = new glm::mat4[amount];
    for (unsigned int i = 0; i < amount; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cube_positions[i]);
        modelMatrices[i] = model;
    }

    // Configure instanced array
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    // Setup VAO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind vertex array object
    glBindVertexArray(VAO);

    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture index attribute
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Model matrix attribute
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glBindVertexArray(0);

    // Create texture
    unsigned int texture1, texture2;
    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // Set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../textures/grass_top.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // Set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load and generate the texture
    data = stbi_load("../textures/grass_side.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    cameraPos = glm::vec3((size - x_start) / 2, height_max, (size - z_start) / 2);
    // Render loop
    double x_range_min = x_start + size / 3;
    double x_range_max = x_start + size / 3 * 2;
    double z_range_min = z_start + size / 3;
    double z_range_max = z_start + size / 3 * 2;
    std::vector<glm::vec3> new_cube_positions;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // std::cout << "camera x: " << cameraPos[0] << " camera z: " << cameraPos[2] << " x_range_min: " << x_range_min << " x_range_max: " << x_range_max << " z_range_min: " << z_range_min << " z_range_max: " << z_range_max << " size: " << size << std::endl;
        if (cameraPos[0] < x_range_min || cameraPos[0] > x_range_max
            || cameraPos[2] < z_range_min || cameraPos[2] > z_range_max) {
            x_start = static_cast<int>(cameraPos[0] - size / 2);
            z_start = static_cast<int>(cameraPos[2] - size / 2);

            std::thread map_thread(create_new_map_with_thread, terrain, x_start, z_start, size, octs,
                random_seed, height_max, new_cube_positions, modelMatrices);
            map_thread.join();

            x_range_min = static_cast<double>(x_start + size / 3);
            x_range_max = static_cast<double>(x_start + size / 3 * 2);
            z_range_min = static_cast<double>(z_start + size / 3);
            z_range_max = static_cast<double>(z_start + size / 3 * 2);
        }

        // Configure instanced array
        glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

        // Render
        // Clear the colorbuffer
        glClearColor(0.678f, 0.847f, 0.902f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // Camera
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // Project to 2D
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

        // Render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, amount);
        glBindVertexArray(0);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional: de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}
