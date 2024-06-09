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
        void store_translation_matrix(glm::mat4 trans_mat);
        void store_rotation_matrix(glm::mat4 rot_mat);
        glm::mat4 get_model_matrix();
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
        std::vector<glm::mat4> trans_mat_stack;
        std::vector<glm::mat4> rot_mat_stack;
};

#endif
