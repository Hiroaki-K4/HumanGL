#ifndef PERLINENOISE_HPP
#define PERLINENOISE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <random>
#include <bits/stdc++.h>

class PerlineNoise {
    public:
        PerlineNoise();
        PerlineNoise(
            const int size,
            const int octs,
            const bool random_seed
        );
        ~PerlineNoise();
        double calculate_weighted_dot_product(
            int gridX, int gridY, double x, double y, int period,
            std::vector<std::pair<double, double>> dirs,
            std::vector<int> perm
        );
        double create_noise(
            double x, double y, int period,
            std::vector<std::pair<double, double>> dirs,
            std::vector<int> perm);
        double calculate_octave_perline_noise(
            double x, double y, int period, unsigned int octs,
            std::vector<std::pair<double, double>> dirs,
            std::vector<int> perm);
        void create_perline_noise(int x_start, int z_start, std::vector<double> &noise);

    private:
        unsigned int size = 128;
        double freq = 1.0 / 32.0;
        unsigned int octs = 5;
        bool random_seed = false;
};

#endif
