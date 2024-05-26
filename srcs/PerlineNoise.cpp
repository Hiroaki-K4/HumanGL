#include "PerlineNoise.hpp"

PerlineNoise::PerlineNoise() {}

PerlineNoise::PerlineNoise(
    const int size,
    const int octs,
    const bool random_seed) {
    this->size = size;
    this->octs = octs;
    this->random_seed = random_seed;
}

PerlineNoise::~PerlineNoise() {}

double PerlineNoise::calculate_weighted_dot_product(
    int gridX, int gridY, double x, double y, int period,
    std::vector<std::pair<double, double>> dirs,
    std::vector<int> perm) {
    double distX = fabs(x - gridX);
    double distY = fabs(y - gridY);
    // The closer the distance between a point and the grid,
    // the greater the weight of that grid.
    double weightX = 1 - 6 * std::pow(distX, 5) + 15 * std::pow(distX, 4) - 10 * std::pow(distX, 3);
    double weightY = 1 - 6 * std::pow(distY, 5) + 15 * std::pow(distY, 4) - 10 * std::pow(distY, 3);
    int hashed = perm[perm[int(gridX % period)] + int(gridY % period)];
    double dot = (x - gridX) * dirs[hashed].first + (y - gridY) * dirs[hashed].second;

    return weightX * weightY * dot;
}

double PerlineNoise::create_noise(
    double x, double y, int period,
    std::vector<std::pair<double, double>> dirs,
    std::vector<int> perm) {
    int intX = int(x);
    int intY = int(y);

    return (
        calculate_weighted_dot_product(intX + 0, intY + 0, x, y, period, dirs, perm)
        + calculate_weighted_dot_product(intX + 1, intY + 0, x, y, period, dirs, perm)
        + calculate_weighted_dot_product(intX + 0, intY + 1, x, y, period, dirs, perm)
        + calculate_weighted_dot_product(intX + 1, intY + 1, x, y, period, dirs, perm)
    );
}

double PerlineNoise::calculate_octave_perline_noise(
    double x, double y, int period, unsigned int octs,
    std::vector<std::pair<double, double>> dirs,
    std::vector<int> perm) {
    double noise = 0;
    // Add noise functions
    for (unsigned int octave = 0; octave < octs; octave++) {
        double amplitude = std::pow(0.5, octave);
        unsigned int frequency = std::pow(2.0, octave);
        noise += amplitude * create_noise(
            x * frequency, y * frequency, period * frequency, dirs, perm
        );
    }

    return noise;
}

void PerlineNoise::create_perline_noise(
    int x_start, int z_start, std::vector<double> &noise) {
    unsigned int rand_num = 256;
    std::vector<int> perm(rand_num);
    std::iota(perm.begin(), perm.end(), 0);

    unsigned int seed;
    if (random_seed) {
        seed = 314;
    } else {
        std::random_device seed_gen;
        seed = seed_gen();
    }
    std::random_device seed_gen;
    std::mt19937 engine(seed);
    std::shuffle(perm.begin(), perm.end(), engine);
    perm.insert(perm.end(), perm.begin(), perm.end());

    std::vector<std::pair<double, double>> dirs;
    for (unsigned int i = 0; i < rand_num; i++) {
        std::pair<double, double> dir = std::make_pair(
            std::cos(i * 2.0 * M_PI / rand_num),
            std::sin(i * 2.0 * M_PI / rand_num));
        dirs.push_back(dir);
    }

    noise.reserve(size * size);
    for (int y = z_start; y < z_start + (int)size; y++) {
        for (int x = x_start; x < x_start + (int)size; x++) {
            noise.push_back(calculate_octave_perline_noise(
                x * freq, y * freq, int(size * freq), octs, dirs, perm));
        }
    }
}
