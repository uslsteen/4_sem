#ifndef ALGO_H_
#define ALGO_H_

#include "../matrix/matrix.hh"
#include <map>

using namespace MX;

namespace detail
{

enum helpful_const
{
    VERY_BIG_VALUE = 10000,
    INIT_VALUE = -666,
    NOT_VISITED = 1
};


class AlgoHandler final
{
private:

    std::map<size_t, bool> check_table{};
    const Matrix<int> weights;

    size_t vec_size;

public:

    AlgoHandler(const Matrix<int>& weights__, size_t vec_size__) : weights(Matrix{weights__}), vec_size(vec_size__)
    {

    }

    ~AlgoHandler() = default;

public:

    void solve(); 

private:

    void init_table();

    bool is_final();

    std::pair<int, size_t> find_min_dist(size_t cur_index);

    void optim_way();

    void find_optim_back_way(size_t src_ind);

    std::pair<int, size_t> find_min_elem(const Row<int>& row, int min_val);

    std::vector<int> dijikstra_algo();

    void print_optim_way(size_t src_ind, size_t dest_ind, int dist);
};

}

#endif
