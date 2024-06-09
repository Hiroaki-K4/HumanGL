#ifndef LOWERLEG_HPP
#define LOWERLEG_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>


class LowerLeg {
    public:
        LowerLeg();
        LowerLeg(glm::vec3 position);
        ~LowerLeg();
        glm::mat4 get_model_matrix(glm::vec3 upper_leg_pos);
        float width = 1.2f;
        float height = 2.0f;
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
        glm::vec4 connect_pos = glm::vec4(glm::vec3(-width / 2, height / 2, 0), 1.0f);

    private:
        glm::vec3 position = glm::vec3(-0.6f, -4.0f, 0.0f);

};

#endif
