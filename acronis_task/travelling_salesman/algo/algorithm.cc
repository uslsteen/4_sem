#include "algorithm.hh"


namespace detail
{

void AlgoHandler::init_table()
{
    for (size_t i = 0; i < vec_size; ++i)
        check_table[i] = false;       // mean not visited
}

bool AlgoHandler::is_final()
{
    bool res = true;

    for (size_t i = 0; i < vec_size; ++i)
        res &= check_table[i];

    return res;
}

std::pair<int, size_t> AlgoHandler::find_min_elem(const Row<int>& row, int min_val)
{
    std::pair<int, size_t> optim_pair;

    for (size_t i = 0; i < vec_size; ++i)
    {
        int temp = row[i];

        if ((min_val == INIT_VALUE) && (temp != INIT_VALUE) && (temp != 0))
        {
            if (!check_table[i])
            {
                min_val = temp;
                optim_pair.first = temp;
                optim_pair.second = i;
            }
            else continue;
        }

        else if (temp == INIT_VALUE || temp == 0)
            continue;

        else if ((temp < min_val))
        {
            if (!check_table[i])   // if not visited
            {
                min_val = temp;
                optim_pair.first = temp;
                optim_pair.second = i;
            }
            else continue;
        }
    }
    return optim_pair;
}




void AlgoHandler::find_optim_back_way(size_t src_ind)
{

    if (weights[src_ind][0] != 0)
    {
        init_table();
        size_t dest_index = 0;
        int min_val = weights[dest_index][dest_index];
        const Row<int> tmp_row = weights[dest_index];

        std::pair<int, size_t> res = find_min_elem(tmp_row, min_val);

        if (weights[src_ind][dest_index] == res.first)
            std::cout << src_ind << " ---> " << dest_index << ", " << "distance_between = "
                                             << weights[src_ind][dest_index];

        else if (weights[src_ind][dest_index] > res.first)
        {

            if (weights[src_ind][res.second] + res.first < weights[src_ind][dest_index])
            {
                std::cout << src_ind << " ---> " << res.first << "," << "distance_between = "
                                                 << weights[src_ind][res.second] << std::endl;

                std::cout << res.first << " ---> " << dest_index << "," << "distance_between = "
                          << weights[res.first][dest_index] << std::endl;
            }
            else
                std::cout << src_ind << " ---> " << dest_index << ", " << "distance_between = "
                          << weights[src_ind][dest_index];
        }
    }
}

std::pair<int, size_t> AlgoHandler::find_min_dist(size_t cur_index)
{
    const Row<int> tmp_row = weights[cur_index];
    int min_val = weights[cur_index][cur_index];

    return find_min_elem(tmp_row, min_val);
}


void AlgoHandler::optim_way()
{
    init_table();

    int distance = 0;
    size_t cur_index = 0;

    bool checker = true;
    check_table[cur_index] = true;

    while(true)
    {
        std::pair<int, size_t> res = find_min_dist(cur_index);

        size_t prev_index = cur_index;
        cur_index = res.second;

        assert(prev_index != cur_index);

        distance += res.first;

        check_table[cur_index] = true; //visited this vect

        std::cout << prev_index << " --- >" << cur_index << ", distance_between = "
                  << weights[prev_index][cur_index] << std::endl;

        if ((checker = is_final()))
            break;
    }

    std::cout << "final location: " << cur_index << std::endl;

    //find_optim_back_way(weights, vec_size, cur_index);
}



void AlgoHandler::solve()
{
    optim_way();
}

}