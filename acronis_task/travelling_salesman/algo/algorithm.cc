#include "algorithm.hh"


void find_optim_back_way()
{

}

void init_table(std::map<size_t, bool>& check_table, size_t vec_size)
{
    for (size_t i = 0; i < vec_size; ++i)
        check_table[i] = false;       // mean not visited
}

bool is_final(std::map<size_t, bool>& check_table, size_t vec_size)
{
    bool res = true;

    for (size_t i = 0; i < vec_size; ++i)
        res &= check_table[i];

    return res;
}

std::pair<int, size_t> find_min_dist(std::map<size_t, bool>& check_table, const Matrix<int>& weights, size_t vec_size, size_t cur_index)
{
    const Row tmp_row = weights[cur_index];
    int min_val = weights[cur_index][cur_index];
    std::pair<int, size_t> optim_pair;

    for (size_t i = 0; i < vec_size; ++i)
    {
        int temp = tmp_row[i];

        if ((min_val == -666) && (temp != -666) && (temp != 0))
        {
            if (!check_table[i])
            {
                min_val = temp;
                optim_pair.first = temp;
                optim_pair.second = i;
            }
            else continue;
        }

        else if (temp == -666 || temp == 0)
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
void optim_way(const Matrix<int>& weights, size_t vec_size)
{
    std::map<size_t, bool> check_table;
    init_table(check_table, vec_size);

    int distance = 0;
    size_t cur_index = 0;
    bool checker = true;
    check_table[cur_index] = true;

    while(true)
    {
        std::pair<int, size_t> res = find_min_dist(check_table, weights, vec_size, cur_index);

        size_t prev_index = cur_index;
        cur_index = res.second;

        assert(prev_index != cur_index);

        distance += res.first;

        check_table[cur_index] = true; //visited this vect

        std::cout << prev_index << " --- >" << cur_index << ", distance_between = "
                  << weights[prev_index][cur_index] << std::endl;

        if ((checker = is_final(check_table, vec_size)))
            break;
    }

    std::cout << "final location: " << cur_index << std::endl;

    find_optim_back_way();
}



/*
void find_min_dist(const Matrix<int>& weights, size_t vec_size, std::vector<int>& min_dist,
                                                                std::vector<int>& visited )

{
    int temp = 0, minindex = 0, min = 0;

    do
    {
        minindex = VERY_BIG_VALUE;
        min = VERY_BIG_VALUE;

        for (size_t i = 0; i < vec_size; i++)
        {
            // Если вершину ещё не обошли и вес меньше min
            if ((visited[i] == 1) && (min_dist[i] < min))
            {
                // Переприсваиваем значения
                min = min_dist[i];
                minindex = i;
            }
        }

        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины

        if (minindex != VERY_BIG_VALUE)
        {
            for (size_t i = 0; i < vec_size; i++)
            {
                if (weights[minindex][i] > 0)
                {
                    temp = min + weights[minindex][i];

                    if (temp < min_dist[i])
                        min_dist[i] = temp;
                }
            }

            visited[minindex] = 0;
        }
    } while (minindex < VERY_BIG_VALUE);
}

int d_algo(const MX::Matrix<int>& weights, size_t vec_size)
{
    std::vector<int> min_dist;
    min_dist.reserve(vec_size); // минимальное расстояние

    std::vector<int> visited;
    visited.reserve(vec_size);  // посещенные вершины

    int begin_index = 0;


    //Инициализация вершин и расстояний
    for (size_t i = 0; i < vec_size ; i++)
    {
        min_dist[i] = VERY_BIG_VALUE;
        visited[i] = 1;
    }

    min_dist[begin_index] = 0;

    // Шаг алгоритма
    find_min_dist(weights, vec_size, min_dist, visited);
    // Вывод кратчайших расстояний до вершин
    printf("\nКратчайшие расстояния до вершин: \n");

    for (size_t i = 0; i < vec_size ; i++)
        printf("%5d ", min_dist[i]);

    // Восстановление пути
    int ver[vec_size]; // массив посещенных вершин
    int end = 4; // индекс конечной вершины = 5 - 1

    ver[0] = end + 1; // начальный элемент - конечная вершина

    int k = 1; // индекс предыдущей вершины
    int weight = min_dist[end]; // вес конечной вершины

    while (end != begin_index) // пока не дошли до начальной вершины
    {
        for (size_t i = 0; i < vec_size; i++) // просматриваем все вершины
        {
            if (weights[i][end] != 0)   // если связь есть
            {
                int temp = weight - weights[i][end]; // определяем вес пути из предыдущей вершины

                if (temp == min_dist[i])                   // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    end = i;       // сохраняем предыдущую вершину
                    ver[k] = i + 1; // и записываем ее в массив
                    k++;
                }
            }
        }
    }

    // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
    printf("\nВывод кратчайшего пути\n");

    for (int i = k - 1; i >= 0; i--)
        printf("%3d ", ver[i]);

    return 0;
}*/
