#ifndef ALGO_H_
#define ALGO_H_

#include "../matrix/matrix.hh"


enum helpful_const
{
    VERY_BIG_VALUE = 10000
};


using namespace MX;

int d_algo(const Matrix<int>& weights, size_t vec_size);

void find_min_dist(const Matrix<int>& weights, size_t vec_size, std::vector<int>& min_dist,
                                                                std::vector<int>& visited);

#endif
