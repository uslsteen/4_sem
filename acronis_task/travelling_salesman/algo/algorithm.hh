#ifndef ALGO_H_
#define ALGO_H_

#include "../matrix/matrix.hh"
#include <map>

using namespace MX;

enum helpful_const
{
    VERY_BIG_VALUE = 10000
};


void init_table(std::map<size_t, bool>& check_table, size_t vec_size);

bool is_final(std::map<size_t, bool>& check_table, size_t vec_size);

std::pair<int, size_t> find_min_dist(std::map<size_t, bool>& check_table, const Matrix<int>& weights, size_t vec_size, size_t cur_index);

void optim_way(const Matrix<int>& weights, size_t vec_size);

void find_optim_back_way(const Matrix<int>& weights, size_t vec_size);

#endif
