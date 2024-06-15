#include "UpperArm.hpp"


UpperArm::UpperArm() {}

UpperArm::UpperArm(glm::vec3 position) {
    this->position = position;
}

UpperArm::~UpperArm() {}

void UpperArm::store_translation_matrix(glm::mat4 trans_mat) {
    trans_mat_stack.push_back(trans_mat);
}

void UpperArm::store_rotation_matrix(glm::mat4 rot_mat) {
    rot_mat_stack.push_back(rot_mat);
}

glm::mat4 UpperArm::get_model_matrix(glm::vec3 torso_pos) {
    float timeValue = glfwGetTime();
    float sign;
    if (position[0] < 0) {
        sign = 1.0;
    } else {
        sign = -1.0;
    }
    float rad = glm::radians(35.0 * sign * sin(3 * timeValue));
    glm::vec3 axis = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 rot_model = glm::rotate(model, rad, axis);
    glm::vec3 rotated_pos = rot_model * top_connect_pos;
    model = glm::translate(model, torso_pos - rotated_pos);
    model = glm::rotate(model, rad, axis);

    current_bottom_connect_pos = model * bottom_connect_pos;

    return model;
}
