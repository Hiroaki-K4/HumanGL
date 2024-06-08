#include "Head.hpp"


Head::Head() {
    std::cout << "This is head class" << std::endl;
}

Head::~Head() { std::cout << "Finish head class" << std::endl; }

glm::mat4 Head::get_model_matrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    return model;
}
