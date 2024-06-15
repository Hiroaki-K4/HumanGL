#include "Head.hpp"


Head::Head() {}

Head::~Head() {}

void Head::store_translation_matrix(glm::mat4 trans_mat) {
    trans_mat_stack.push_back(trans_mat);
}

void Head::store_rotation_matrix(glm::mat4 rot_mat) {
    rot_mat_stack.push_back(rot_mat);
}

glm::mat4 Head::get_model_matrix(glm::vec3 torso_pos) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position + torso_pos - connect_pos);
    return model;
}
