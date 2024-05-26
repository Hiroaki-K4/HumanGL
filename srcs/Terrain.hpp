#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "PerlineNoise.hpp"

class Terrain {
    public:
        Terrain();
        Terrain(std::vector<double> noise);
        ~Terrain();
        void create_perline_noise(int x_start, int z_start, unsigned int size, unsigned int octs, bool random_seed);
        void rescale_noise(unsigned int scale);
        void create_mountain(int x_start, int z_start, std::vector<glm::vec3> &positions, unsigned int size);

    private:
        std::vector<double> noise;
};

#endif
