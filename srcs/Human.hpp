#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

# include "Torso.hpp"


class Human {
    public:
        Human();
        ~Human();
        glm::mat4 get_torso_model_matrix();

    private:
        Torso torso;
};

#endif
