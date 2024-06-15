#include "LowerLeg.hpp"


LowerLeg::LowerLeg() {}

LowerLeg::LowerLeg(glm::vec3 position) {
    this->position = position;
}

LowerLeg::~LowerLeg() {}

glm::mat4 LowerLeg::get_model_matrix(glm::vec3 upper_leg_pos) {
    float timeValue = glfwGetTime();
    float sign;
    if (position[0] < 0) {
        sign = -1.0;
    } else {
        sign = 1.0;
    }
    float rad = glm::radians(35.0 * sign * sin(3 * timeValue) + 10);
    glm::vec3 axis = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 rot_model = glm::rotate(model, rad, axis);
    glm::vec3 rotated_pos = rot_model * connect_pos;
    model = glm::translate(model, upper_leg_pos - rotated_pos);
    model = glm::rotate(model, rad, axis);

    return model;
}
