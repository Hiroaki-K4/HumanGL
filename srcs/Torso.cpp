#include "Torso.hpp"


Torso::Torso() {}

Torso::~Torso() {}

glm::mat4 Torso::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    float timeValue = glfwGetTime();
    float y_move = 0.1 * cos(6 * timeValue);
    glm::vec3 movement = glm::vec3(0.0f, y_move, 0.0f);
    curr_position = position - movement;
    model = glm::translate(model, curr_position);
    return model;
}

glm::vec3 Torso::get_current_position() {
    return curr_position;
}
