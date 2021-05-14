#include "algorithm.hh"


namespace detail
{

std::vector<int> AlgoHandler::dijikstra_algo()
{
    std::vector<int> min_dists(vec_size);
    std::vector<int> visited(vec_size);

    int temp = 0, minindex = 0, min = 0;
    int begin_index = 0;


    //Инициализация вершин и расстояний
    for (size_t i = 0; i<vec_size; i++)
    {
        min_dists[i] = VERY_BIG_VALUE;
        visited[i] = NOT_VISITED;
    }

    min_dists[begin_index] = 0;

    // Шаг алгоритма
    do 
    {
        
        minindex = VERY_BIG_VALUE;
        min = VERY_BIG_VALUE;
        
        for (size_t i = 0; i<vec_size; i++)
        { 
            // Если вершину ещё не обошли и вес меньше min
            if ((visited[i] == NOT_VISITED) && (min_dists[i]<min))
            { 
                // Переприсваиваем значения
                min = min_dists[i];
                minindex = i;
            }
        }

        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины

        if (minindex != VERY_BIG_VALUE)
        {
            for (size_t i = 0; i<vec_size; i++)
            {
                if (weights[minindex][i] > 0)
                {
                    temp = min + weights[minindex][i];

                    if (temp < min_dists[i])
                        min_dists[i] = temp;  
                }
            }

            visited[minindex] = 0;
        }
    } while (minindex < VERY_BIG_VALUE);

    // Вывод кратчайших расстояний до вершин
    std::cout << "\nКратчайшие расстояния до вершин: \n";

    for (auto&& elem : min_dists)
        std::cout << elem << " ";

    return min_dists;
}

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


void AlgoHandler::print_optim_way(size_t src_ind, size_t dest_ind, int dist)
{
    std::cout << "optimal back way is:" << std::endl; 
    std::cout << src_ind << " ---> " << dest_ind << std::endl;
    std::cout << "distance_between = " << dist;
}


void AlgoHandler::find_optim_back_way(size_t src_ind)
{
    std::vector<int> min_dists = dijikstra_algo();
    size_t dest_ind = 0;
    int cur_dist = weights[src_ind][dest_ind];
    int min_dist = min_dists[1];
    std::pair<int, size_t> min_pair{min_dists[1], 1};

    if (cur_dist != 0)
    {
        for (size_t i = 1; i < vec_size; ++i)
        {
            int tmp = min_dists[i];

            if (tmp < min_dist)
            {
                min_pair.first = tmp;
                min_pair.second = i;
            }   
        }

        if (min_pair.first < cur_dist)
        {
            if (min_pair.first + weights[src_ind][min_pair.second] < cur_dist)
            {
                print_optim_way(src_ind, min_pair.second, weights[src_ind][min_pair.second]);
                print_optim_way(min_pair.second, dest_ind, min_pair.first);
            }
            else  
                print_optim_way(src_ind, dest_ind, cur_dist);
        }

        else if (min_pair.first > cur_dist)
            print_optim_way(src_ind, dest_ind, cur_dist);
        
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

    find_optim_back_way(cur_index);
}



void AlgoHandler::solve()
{
    optim_way();
}

}
