#include "ForeArm.hpp"


ForeArm::ForeArm() {}

ForeArm::ForeArm(glm::vec3 position) {
    this->position = position;
}

ForeArm::~ForeArm() {}

void ForeArm::store_translation_matrix(glm::mat4 trans_mat) {
    trans_mat_stack.push_back(trans_mat);
}

void ForeArm::store_rotation_matrix(glm::mat4 rot_mat) {
    rot_mat_stack.push_back(rot_mat);
}

glm::mat4 ForeArm::get_model_matrix(glm::vec3 upper_arm_pos) {
    float timeValue = glfwGetTime();
    float sign;
    if (position[0] < 0) {
        sign = 1.0;
    } else {
        sign = -1.0;
    }
    float rad = glm::radians(35.0 * sign * sin(3 * timeValue) - 20);
    glm::vec3 axis = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 rot_model = glm::rotate(model, rad, axis);
    glm::vec3 rotated_pos = rot_model * connect_pos;
    model = glm::translate(model, upper_arm_pos - rotated_pos);
    model = glm::rotate(model, rad, axis);
    return model;
}
