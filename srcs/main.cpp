#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Human.hpp"


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Build and compile our shader program
    Shader ourShader("texture.vs", "texture.fs");

    float vertices[] = {
        // positions
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
    };

    Human human;

    unsigned int torso_VBO, torso_VAO;
    glGenVertexArrays(1, &torso_VAO);
    glGenBuffers(1, &torso_VBO);
    glBindVertexArray(torso_VAO);
    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, torso_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(human.get_torso().vertices), human.get_torso().vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int head_VBO, head_VAO;
    glGenVertexArrays(1, &head_VAO);
    glGenBuffers(1, &head_VBO);
    glBindVertexArray(head_VAO);
    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, head_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(human.get_head().vertices), human.get_head().vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int right_upper_arm_VBO, right_upper_arm_VAO;
    glGenVertexArrays(1, &right_upper_arm_VAO);
    glGenBuffers(1, &right_upper_arm_VBO);
    glBindVertexArray(right_upper_arm_VAO);
    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, right_upper_arm_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(human.get_right_upper_arm().vertices), human.get_right_upper_arm().vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int left_upper_arm_VBO, left_upper_arm_VAO;
    glGenVertexArrays(1, &left_upper_arm_VAO);
    glGenBuffers(1, &left_upper_arm_VBO);
    glBindVertexArray(left_upper_arm_VAO);
    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, left_upper_arm_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(human.get_left_upper_arm().vertices), human.get_left_upper_arm().vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int right_fore_arm_VBO, right_fore_arm_VAO;
    glGenVertexArrays(1, &right_fore_arm_VAO);
    glGenBuffers(1, &right_fore_arm_VBO);
    glBindVertexArray(right_fore_arm_VAO);
    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, right_fore_arm_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(human.get_right_fore_arm().vertices), human.get_right_fore_arm().vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int left_fore_arm_VBO, left_fore_arm_VAO;
    glGenVertexArrays(1, &left_fore_arm_VAO);
    glGenBuffers(1, &left_fore_arm_VBO);
    glBindVertexArray(left_fore_arm_VAO);
    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, left_fore_arm_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(human.get_left_fore_arm().vertices), human.get_left_fore_arm().vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    ourShader.use();

    glEnable(GL_DEPTH_TEST);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Render
        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(10.0f, 0.0f, 10.0f),
                            glm::vec3(0.0f, 0.0f, 0.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));

        // Project to 2D
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projLoc = glGetUniformLocation(ourShader.ID, "projection");

        ourShader.use();
        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "color");

        // Draw torso
        model = human.get_torso_model_matrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
        glUniform4f(vertexColorLocation, 0.13f, 0.54f, 0.13f, 1.0f);
        glBindVertexArray(torso_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw head
        model = human.get_head_model_matrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(vertexColorLocation, 1.0f, 0.76f, 0.64f, 1.0f);
        glBindVertexArray(head_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw right upper arm
        model = human.get_right_upper_arm_model_matrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(vertexColorLocation, 1.0f, 0.76f, 0.64f, 1.0f);
        glBindVertexArray(right_upper_arm_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw left upper arm
        model = human.get_left_upper_arm_model_matrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(vertexColorLocation, 1.0f, 0.76f, 0.64f, 1.0f);
        glBindVertexArray(left_upper_arm_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw right fore arm
        model = human.get_right_fore_arm_model_matrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(vertexColorLocation, 1.0f, 0.76f, 0.64f, 1.0f);
        glBindVertexArray(right_fore_arm_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw left fore arm
        model = human.get_left_fore_arm_model_matrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(vertexColorLocation, 1.0f, 0.76f, 0.64f, 1.0f);
        glBindVertexArray(left_fore_arm_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional: de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &torso_VAO);
    glDeleteVertexArrays(1, &head_VAO);
    glDeleteVertexArrays(1, &right_upper_arm_VAO);
    glDeleteVertexArrays(1, &left_upper_arm_VAO);
    glDeleteVertexArrays(1, &right_fore_arm_VAO);
    glDeleteVertexArrays(1, &left_fore_arm_VAO);
    glDeleteBuffers(1, &torso_VBO);
    glDeleteBuffers(1, &head_VBO);
    glDeleteBuffers(1, &right_upper_arm_VBO);
    glDeleteBuffers(1, &left_upper_arm_VBO);
    glDeleteBuffers(1, &right_fore_arm_VBO);
    glDeleteBuffers(1, &left_fore_arm_VBO);

    glfwTerminate();

    return 0;
}
