#include "Human.hpp"

Human::Human() { std::cout << "This is Human class" << std::endl; }

Human::~Human() { std::cout << "Finish Human class" << std::endl; }

glm::mat4 Human::get_torso_model_matrix() {
    return torso.get_model_matrix();
}
