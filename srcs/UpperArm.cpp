#include "UpperArm.hpp"


UpperArm::UpperArm() {
    std::cout << "This is UpperArm class" << std::endl;
}

UpperArm::UpperArm(glm::vec3 position) {
    std::cout << "This is UpperArm class" << std::endl;
    this->position = position;
}

UpperArm::~UpperArm() { std::cout << "Finish UpperArm class" << std::endl; }

glm::mat4 UpperArm::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    return model;
}
