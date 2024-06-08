#include "ForeArm.hpp"


ForeArm::ForeArm() {
    std::cout << "This is ForeArm class" << std::endl;
}

ForeArm::ForeArm(glm::vec3 position) {
    std::cout << "This is ForeArm class" << std::endl;
    this->position = position;
}

ForeArm::~ForeArm() { std::cout << "Finish ForeArm class" << std::endl; }

glm::mat4 ForeArm::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    return model;
}
