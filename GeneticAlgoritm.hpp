//
// Created by Денис Бурылов on 02.11.2020.
//

#ifndef MO_RK2_GENETICALGORITM_HPP
#define MO_RK2_GENETICALGORITM_HPP


#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

class Population {
    typedef std::vector<std::pair<double, double>> Populations;
    static double fit(double x, double y);
    std::vector<std::pair<double, double>> _population;

public:
    Population();

    void selection();

    void crossover();

    void mutation();

    void print_table(const size_t &iteration, std::ostream &out);

private:
    std::vector<double> _roulette_wheel();

    static size_t _wheel_spin(const std::vector<double> &wheel);

    static double _max_fit(const std::vector<double> &fits);

    double _sum_fit();
};

void genetic_algoritm(const size_t &iterations, std::ostream &out);


#endif//MO_RK2_GENETICALGORITM_HPP
