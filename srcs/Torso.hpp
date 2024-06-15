#ifndef TORSO_HPP
#define TORSO_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>


class Torso {
    public:
        Torso();
        ~Torso();
        glm::mat4 get_model_matrix();
        glm::vec3 get_current_position();
        float width = 2.4f;
        float height = 3.0f;
        float depth = 0.6f;
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

    private:
        glm::vec3 position = glm::vec3(0.0f, 0.5f, 0.0f);
        glm::vec3 curr_position = position;

};

#endif
