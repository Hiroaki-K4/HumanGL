#include "Torso.hpp"


Torso::Torso() {
    std::cout << "This is torso class" << std::endl;
}

Torso::~Torso() { std::cout << "Finish torso class" << std::endl; }

glm::mat4 Torso::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 scale = glm::vec3(2.0, 2.0f, 2.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    return model;
}
