#include "Terrain.hpp"

Terrain::Terrain() {}

Terrain::Terrain(std::vector<double> noise) {
    this->noise = noise;
}

Terrain::~Terrain() {}

void Terrain::create_perline_noise(
    int x_start, int z_start, unsigned int size, unsigned int octs, bool random_seed) {
    PerlineNoise perline_noise(size, octs, random_seed);
    std::vector<double> noise;
    perline_noise.create_perline_noise(abs(x_start), abs(z_start), noise);
    this->noise = noise;
}

void Terrain::rescale_noise(unsigned int scale) {
    double min_noise = *std::min_element(this->noise.begin(), this->noise.end());
    transform(this->noise.begin(), this->noise.end(), this->noise.begin(), bind2nd(std::plus<double>(), -(min_noise-0.0)));
    double max_noise = *std::max_element(this->noise.begin(), this->noise.end());
    double mag = scale / max_noise;
    std::transform(this->noise.begin(), this->noise.end(), this->noise.begin(),
        std::bind1st(std::multiplies<double>(), mag));
    double min_noise_fi = *std::min_element(this->noise.begin(), this->noise.end());
    double max_noise_fi = *std::max_element(this->noise.begin(), this->noise.end());
}

void Terrain::create_mountain(
    int x_start, int z_start, std::vector<glm::vec3> &positions, unsigned int size) {
    for (int z = z_start; z < z_start + (int)size; z++) {
        for (int x = x_start; x < x_start + (int)size; x++) {
            int y = int(noise[(int)size * (z - z_start) + (x - x_start)]);
            positions.push_back(glm::vec3(x, y, z));
            for (int i = y-10; i < y; i++) {
                positions.push_back(glm::vec3(x, i, z));
            }
        }
    }
}
