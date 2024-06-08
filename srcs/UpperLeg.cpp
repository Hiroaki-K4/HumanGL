#include "UpperLeg.hpp"


UpperLeg::UpperLeg() {
    std::cout << "This is UpperLeg class" << std::endl;
}

UpperLeg::UpperLeg(glm::vec3 position) {
    std::cout << "This is UpperLeg class" << std::endl;
    this->position = position;
}

UpperLeg::~UpperLeg() { std::cout << "Finish UpperLeg class" << std::endl; }

glm::mat4 UpperLeg::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    return model;
}
