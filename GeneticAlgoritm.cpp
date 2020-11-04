//
// Created by Денис Бурылов on 02.11.2020.
//

#include "GeneticAlgoritm.hpp"

Population::Population() {
    std::srand(time(0));
    for (size_t i = 0; i < 4; i++) {
        _population.push_back(std::make_pair(static_cast<double>(rand()) / static_cast<double>(RAND_MAX / 4) - 2,
                                             static_cast<double>(rand()) / static_cast<double>(RAND_MAX / 4) - 2));
    }
}

void Population::selection() {
    std::srand(time(0));
    std::vector<double> wheel = _roulette_wheel();
    Populations selection;
    for (auto i = 0; i < 3; i++) { selection.push_back(_population[_wheel_spin(wheel)]); }
    std::sort(selection.begin(), selection.end(),
              [](std::pair<double, double> pair_1, std::pair<double, double> pair_2) {
                  return (fit(pair_1.first, pair_1.second) > fit(pair_2.first, pair_2.second));
              });
    _population = selection;
}

void Population::crossover() {
    Populations crossover;
    crossover.push_back(std::make_pair(_population[0].first, _population[1].second));
    crossover.push_back(std::make_pair(_population[1].first, _population[0].second));
    crossover.push_back(std::make_pair(_population[0].first, _population[2].second));
    crossover.push_back(std::make_pair(_population[2].first, _population[0].second));
    _population = crossover;
}

void Population::mutation() {
    std::srand(time(0));
    Populations mutation;
    for (auto [x, y] : _population) {
        double new_x = x;
        double new_y = y;
        if (static_cast<double>(rand()) / static_cast<double>(RAND_MAX) <= 0.25) { new_x = 0.9 * x; }
        if (static_cast<double>(rand()) / static_cast<double>(RAND_MAX) <= 0.25) { new_y = 0.9 * x; }
        mutation.push_back(std::make_pair(new_x, new_y));
    }
    _population = mutation;
}

void Population::print_table(const size_t &iteration, std::ostream &out) {
    std::vector<double> fits;
    for (auto [x, y] : _population) { fits.push_back(fit(x, y)); }
    double max_fit = _max_fit(fits);
    double average_fit = 0;
    for (auto &fit : fits) { average_fit += fit; }
    average_fit /= fits.size();

    for (size_t i = 0; i < fits.size(); i++) {
        if (i == 0) {
            out << "| " << std::setw(12) << iteration << "|";
        } else {
            out << "| " << std::setw(13) << "|";
        }
        out << std::setw(8) << std::fixed << std::setprecision(4) << _population[i].first << " |";
        out << std::setw(8) << std::fixed << std::setprecision(4) << _population[i].second << " |";
        out << std::setw(8) << std::fixed << std::setprecision(4) << fits[i] << " |";
        if (i == 0) {
            out << std::setw(8) << std::fixed << std::setprecision(4) << max_fit << " |";
            out << std::setw(8) << std::fixed << std::setprecision(4) << average_fit << " |";
        } else {
            out << std::setw(10) << " |";
            out << std::setw(10) << " |";
        }
        if (i == fits.size() - 1) {
            out << std::endl << "|-------------|---------|---------|---------|---------|---------|" << std::endl;
        } else {
            out << std::endl << "|             |---------|---------|---------|         |         |" << std::endl;
        }
    }
}

std::vector<double> Population::_roulette_wheel() {
    std::vector<double> wheel;
    double sector = 0;
    for (auto &[x, y] : _population) {
        sector += fit(x, y) / _sum_fit();
        wheel.push_back(sector);
    }
    return wheel;
}

size_t Population::_wheel_spin(const std::vector<double> &wheel) {

    double point = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    size_t index;
    size_t i = 0;
    for (auto sector : wheel) {
        if (point <= sector) {
            index = i;
            break;
        }
        i++;
    }
    return index;
}

double Population::_max_fit(const std::vector<double> &fits) {
    double max_fit = fits[0];
    for (auto &fit : fits) {
        if (fit > max_fit) { max_fit = fit; }
    }
    return max_fit;
}

double Population::_sum_fit() {
    double sum = 0;
    for (auto &[x, y] : _population) { sum += fit(x, y); }
    return sum;
}

double Population::fit(double x, double y) { return cos(x) * cos(y) * exp(y / 2); }

void genetic_algoritm(const size_t &iterations, std::ostream &out) {
    srand(time(0));
    out << "| #generation | X       | Y       | FIT     | MAX     | AVERAGE |" << std::endl;
    out << "|-------------|---------|---------|---------|---------|---------|" << std::endl;
    Population population;
    population.print_table(0, out);
    for (size_t i = 1; i <= iterations; i++) {
        population.selection();
        population.crossover();
        population.mutation();
        population.print_table(i, out);
    }
}
