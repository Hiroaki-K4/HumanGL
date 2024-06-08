#include "Human.hpp"

Human::Human() {
    std::cout << "This is Human class" << std::endl;
    UpperArm right_upper_arm(glm::vec3(-1.5f, 1.0f, 0.0f));
    this->right_upper_arm = right_upper_arm;
    UpperArm left_upper_arm(glm::vec3(1.5f, 1.0f, 0.0f));
    this->left_upper_arm = left_upper_arm;

    ForeArm right_fore_arm(glm::vec3(-1.5f, -0.5f, 0.0f));
    this->right_fore_arm = right_fore_arm;
    ForeArm left_fore_arm(glm::vec3(1.5f, -0.5f, 0.0f));
    this->left_fore_arm = left_fore_arm;

    UpperLeg right_upper_leg(glm::vec3(-0.6f, -2.0f, 0.0f));
    this->right_upper_leg = right_upper_leg;
    UpperLeg left_upper_leg(glm::vec3(0.6f, -2.0f, 0.0f));
    this->left_upper_leg = left_upper_leg;

    LowerLeg right_lower_leg(glm::vec3(-0.6f, -4.0f, 0.0f));
    this->right_upper_leg = right_upper_leg;
    LowerLeg left_lower_leg(glm::vec3(0.6f, -4.0f, 0.0f));
    this->left_lower_leg = left_lower_leg;
}

Human::~Human() { std::cout << "Finish Human class" << std::endl; }

Torso Human::get_torso() {
    return torso;
}

Head Human::get_head() {
    return head;
}

UpperArm Human::get_right_upper_arm() {
    return right_upper_arm;
}

UpperArm Human::get_left_upper_arm() {
    return left_upper_arm;
}

ForeArm Human::get_right_fore_arm() {
    return right_fore_arm;
}

ForeArm Human::get_left_fore_arm() {
    return left_fore_arm;
}

UpperLeg Human::get_right_upper_leg() {
    return right_upper_leg;
}

UpperLeg Human::get_left_upper_leg() {
    return left_upper_leg;
}

LowerLeg Human::get_right_lower_leg() {
    return right_lower_leg;
}

LowerLeg Human::get_left_lower_leg() {
    return left_lower_leg;
}

glm::mat4 Human::get_torso_model_matrix() {
    return torso.get_model_matrix();
}

glm::mat4 Human::get_head_model_matrix() {
    // TODO: Think about how to store model matrix
    return head.get_model_matrix();
}

glm::mat4 Human::get_right_upper_arm_model_matrix() {
    return right_upper_arm.get_model_matrix();
}

glm::mat4 Human::get_left_upper_arm_model_matrix() {
    return left_upper_arm.get_model_matrix();
}

glm::mat4 Human::get_right_fore_arm_model_matrix() {
    return right_fore_arm.get_model_matrix();
}

glm::mat4 Human::get_left_fore_arm_model_matrix() {
    return left_fore_arm.get_model_matrix();
}

glm::mat4 Human::get_right_upper_leg_model_matrix() {
    return right_upper_leg.get_model_matrix();
}

glm::mat4 Human::get_left_upper_leg_model_matrix() {
    return left_upper_leg.get_model_matrix();
}

glm::mat4 Human::get_right_lower_leg_model_matrix() {
    return right_lower_leg.get_model_matrix();
}

glm::mat4 Human::get_left_lower_leg_model_matrix() {
    return left_lower_leg.get_model_matrix();
}
