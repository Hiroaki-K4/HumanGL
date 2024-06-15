#include "Head.hpp"


Head::Head() {}

Head::~Head() {}

glm::mat4 Head::get_model_matrix(glm::vec3 torso_pos) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position + torso_pos - connect_pos);
    return model;
}
