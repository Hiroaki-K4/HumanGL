#include "LowerLeg.hpp"


LowerLeg::LowerLeg() {
    std::cout << "This is LowerLeg class" << std::endl;
}

LowerLeg::LowerLeg(glm::vec3 position) {
    std::cout << "This is LowerLeg class" << std::endl;
    this->position = position;
}

LowerLeg::~LowerLeg() { std::cout << "Finish LowerLeg class" << std::endl; }

glm::mat4 LowerLeg::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    return model;
}
