#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

# include "Torso.hpp"
# include "Head.hpp"
# include "UpperArm.hpp"
# include "ForeArm.hpp"
# include "UpperLeg.hpp"
# include "LowerLeg.hpp"


class Human {
    public:
        Human();
        ~Human();
        Torso get_torso();
        Head get_head();
        UpperArm get_right_upper_arm();
        UpperArm get_left_upper_arm();
        ForeArm get_right_fore_arm();
        ForeArm get_left_fore_arm();
        UpperLeg get_right_upper_leg();
        UpperLeg get_left_upper_leg();
        LowerLeg get_right_lower_leg();
        LowerLeg get_left_lower_leg();
        glm::mat4 get_torso_model_matrix();
        glm::mat4 get_head_model_matrix();
        glm::mat4 get_right_upper_arm_model_matrix();
        glm::mat4 get_left_upper_arm_model_matrix();
        glm::mat4 get_right_fore_arm_model_matrix();
        glm::mat4 get_left_fore_arm_model_matrix();
        glm::mat4 get_right_upper_leg_model_matrix();
        glm::mat4 get_left_upper_leg_model_matrix();
        glm::mat4 get_right_lower_leg_model_matrix();
        glm::mat4 get_left_lower_leg_model_matrix();

    private:
        Torso torso;
        Head head;
        UpperArm right_upper_arm;
        UpperArm left_upper_arm;
        ForeArm right_fore_arm;
        ForeArm left_fore_arm;
        UpperLeg right_upper_leg;
        UpperLeg left_upper_leg;
        LowerLeg right_lower_leg;
        LowerLeg left_lower_leg;
};

#endif
