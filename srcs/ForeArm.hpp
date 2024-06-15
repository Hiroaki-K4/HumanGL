#ifndef FOREARM_HPP
#define FOREARM_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


class ForeArm {
    public:
        ForeArm();
        ForeArm(glm::vec3 position);
        ~ForeArm();
        glm::mat4 get_model_matrix(glm::vec3 upper_arm_pos);
        float width = 0.3f;
        float height = 1.5f;
        float depth = 0.3f;
        float vertices[180] = {
            // Front
            -width / 2, -height / 2,  depth / 2,
            width / 2, -height / 2,  depth / 2,
            width / 2,  height / 2,  depth / 2,
            width / 2,  height / 2,  depth / 2,
            -width / 2,  height / 2,  depth / 2,
            -width / 2, -height / 2,  depth / 2,
            // Back
            -width / 2, -height / 2, -depth / 2,
            -width / 2,  height / 2, -depth / 2,
            width / 2,  height / 2, -depth / 2,
            width / 2,  height / 2, -depth / 2,
            width / 2, -height / 2, -depth / 2,
            -width / 2, -height / 2, -depth / 2,
            // Left
            -width / 2,  height / 2,  depth / 2,
            -width / 2,  height / 2, -depth / 2,
            -width / 2, -height / 2, -depth / 2,
            -width / 2, -height / 2, -depth / 2,
            -width / 2, -height / 2,  depth / 2,
            -width / 2,  height / 2,  depth / 2,
            // Right
            width / 2,  height / 2,  depth / 2,
            width / 2, -height / 2, -depth / 2,
            width / 2,  height / 2, -depth / 2,
            width / 2, -height / 2, -depth / 2,
            width / 2,  height / 2,  depth / 2,
            width / 2, -height / 2,  depth / 2,
            // Top
            -width / 2,  height / 2, -depth / 2,
            -width / 2,  height / 2,  depth / 2,
            width / 2,  height / 2,  depth / 2,
            width / 2,  height / 2,  depth / 2,
            width / 2,  height / 2, -depth / 2,
            -width / 2,  height / 2, -depth / 2,
            // Bottom
            -width / 2, -height / 2, -depth / 2,
            width / 2, -height / 2, -depth / 2,
            width / 2, -height / 2,  depth / 2,
            width / 2, -height / 2,  depth / 2,
            -width / 2, -height / 2,  depth / 2,
            -width / 2, -height / 2, -depth / 2,
        };
        glm::vec4 connect_pos = glm::vec4(glm::vec3(-width / 2, height / 2, 0), 1.0f);

    private:
        glm::vec3 position = glm::vec3(-1.5f, -0.5f, 0.0f);
};

#endif
