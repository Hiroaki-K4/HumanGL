#include "Torso.hpp"


Torso::Torso() {
    std::cout << "This is torso class" << std::endl;
}

Torso::~Torso() { std::cout << "Finish torso class" << std::endl; }

glm::mat4 Torso::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    return model;
}
