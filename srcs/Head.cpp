#include "Head.hpp"


Head::Head() {
    std::cout << "This is head class" << std::endl;
}

Head::~Head() { std::cout << "Finish head class" << std::endl; }

void Head::store_translation_matrix(glm::mat4 trans_mat) {
    trans_mat_stack.push_back(trans_mat);
}

void Head::store_rotation_matrix(glm::mat4 rot_mat) {
    rot_mat_stack.push_back(rot_mat);
}

glm::mat4 Head::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    return model;
}
