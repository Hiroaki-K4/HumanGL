#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

# include "Torso.hpp"
# include "Head.hpp"


class Human {
    public:
        Human();
        ~Human();
        Torso get_torso();
        Head get_head();
        glm::mat4 get_torso_model_matrix();
        glm::mat4 get_head_model_matrix();

    private:
        Torso torso;
        Head head;
};

#endif
