#include "Human.hpp"

Human::Human() { std::cout << "This is Human class" << std::endl; }

Human::~Human() { std::cout << "Finish Human class" << std::endl; }

Torso Human::get_torso() {
    return torso;
}

Head Human::get_head() {
    return head;
}

glm::mat4 Human::get_torso_model_matrix() {
    return torso.get_model_matrix();
}

glm::mat4 Human::get_head_model_matrix() {
    return head.get_model_matrix();
}
