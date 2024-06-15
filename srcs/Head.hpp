#ifndef HEAD_HPP
#define HEAD_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>


class Head {
    public:
        Head();
        ~Head();
        glm::mat4 get_model_matrix(glm::vec3 torso_pos);
        float width = 1.0f;
        float height = 1.0f;
        float depth = 1.0f;
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
        glm::vec3 position = glm::vec3(0.0f, 2.5f, 0.0f);
        glm::vec3 connect_pos = glm::vec3(position[0], position[1] - height / 2, position[2]);
};

#endif
