#include "driver.hh"

std::vector<CTS::Edge> Edges_{};

//! Constructor for class Driver
//! \param name_of_file - the name of the file from which our program is read
yy::Driver::Driver() : plex_(new OurFlexLexer)
{
  plex_->switch_streams(std::cin, std::cout);
}

//! Functuion for calling bison yy::parser:parse()
//! \return bool in
bool yy::Driver::parse()
{
  yy::parser parser_(this);

  if (parser_.parse())
    return false;

  max_junc_ = juncs.size();

  size_t e_num = Edges_.size();

  /* filling incidence matrix */
  weights_ = MX::Matrix<int>{max_junc_, max_junc_};

  for (size_t i = 0; i < e_num; ++i)
  {
    size_t vert1 = juncs[Edges_[i].junc1], vert2 = juncs[Edges_[i].junc2];

    weights_.set(vert1 - 1, vert2 - 1, Edges_[i].weight);
  }

  return true;
}

void yy::Driver::solve()
{
  
  d_algo(weights_, max_junc_);
/*
  try
  {
    print_curs(crc.curs_calc());
  }
  catch (const MX::rank_lack &er)
  {
    std::cerr << "I CAN'T CALCULATE THIS CIRCUIT, SORRY :'(" << std::endl;
  }*/
}

void yy::Driver::print_curs(const MX::Matrix<double> &curs)
{
  for (size_t i = 0, end = curs.rows(); i < end; ++i)
    Edges_[i].cur = curs[i][0];

  for (auto &&edge : Edges_)
    std::cout << edge;
}

//! The lexical analyzer function, yylex, recognizes tokens from the input stream and returns them to the parser.
//! \param yylval
//! \param yylloc
//! \return token type
yy::parser::token_type yy::Driver::yylex(yy::parser::semantic_type *yylval, parser::location_type *yylloc)
{
  yy::parser::token_type tkn_type = static_cast<yy::parser::token_type>(plex_->yylex());

  switch (tkn_type)
  {
  case yy::parser::token_type::INT: {
    yylval->emplace<int>(std::stoi(plex_->YYText()));
    break;
  }

  case yy::parser::token_type::DOUBLE: {
    yylval->emplace<float>(std::stof(plex_->YYText()));
    break;
  }
  case yy::parser::token_type::ERR: {
    std::cerr << "UNKNOWN TOKEN:" << plex_->YYText() << std::endl;
    break;
  }

  default:
    break;
  }
  *yylloc = plex_->get_cur_location();
  return tkn_type;
}

//!
//! \param junc1
//! \param junc2
//! \param rtor
//! \param voltage
void yy::Driver::insert(size_t junc1, size_t junc2, int weight)
{
  //! Insertion new edge to structure

/*
  if (!juncs.contains(junc1))
    juncs[junc1] = juncs.size();
  if (!juncs.contains(junc2))
    juncs[junc2] = juncs.size();
*/
  juncs[junc1] = junc2;

  Edges_.emplace_back(junc1, junc2, weight);
}

//!  Function for processing syntax error during parsing
//! \param ctx - the context that is created when an error is found
void yy::Driver::report_syntax_error(const parser::context &ctx)
{
  yy::location loc = ctx.location();

  std::cerr << "syntax error in ";
  std::cerr << "line: " << loc.begin.line;
  std::cerr << ", column: " << loc.begin.column << std::endl;

  // Report the tokens expected at this point.
  parser::symbol_kind_type expectd_tokns[NUM_OF_TOKENS];
  size_t num_of_expectd_tokns = ctx.expected_tokens(expectd_tokns, NUM_OF_TOKENS);

  std::cerr << "expected:";

  for (size_t i = 0; i < num_of_expectd_tokns; ++i)
  {
    if (i != 0)
      std::cerr << " or ";

    std::cerr << " <" << parser::symbol_name(expectd_tokns[i]) << "> ";
  }

  std::cerr << std::endl;

  // Report the unexpected token.
  parser::symbol_kind_type lookahead = ctx.token();

  std::cerr << "before: "
            << "<" << parser::symbol_name(lookahead) << ">" << std::endl;
  std::cerr << loc.begin.line << "   |   " << /*lines_of_prog[loc.begin.line - 1] << */ std::endl;
  std::cerr << "    |   ";

  for (int i = 0; i < loc.end.column - 1; ++i)
  {
    if (i == (ctx.lookahead().location.begin.column - 1))
      std::cerr << "^";

    else
      std::cerr << "~";
  }

  std::cerr << std::endl;
}

void yy::Driver::dump() const
{
  for (auto &&edge : Edges_)
  {
    std::cout << edge.junc1 << "--" << edge.junc2 << ", " << edge.rtor << "; " << edge.eds << "V";
    std::cout << std::endl;
  }
}

//! Destructor for class Driver
yy::Driver::~Driver()
{
  delete plex_;
}

int yy::Driver::d_algo(const MX::Matrix<int>& weights, size_t vec_size)
{
    int min_dist[vec_size]; // минимальное расстояние
    int visited[vec_size]; // посещенные вершины

    //std::cout << vec_size << std::endl;

    int temp = 0, minindex = 0, min = 0;

    int begin_index = 0;


    //Инициализация вершин и расстояний
    for (size_t i = 0; i < vec_size ; i++)
    {
        min_dist[i] = 10000;
        visited[i] = 1;
    }

    min_dist[begin_index] = 0;

    // Шаг алгоритма
    do {
    minindex = 10000;

    min = 10000;
    for (size_t i = 0; i < vec_size; i++)
    {   
        // Если вершину ещё не обошли и вес меньше min
        if ((visited[i] == 1) && (min_dist[i]<min))
        { 
            // Переприсваиваем значения
            min = min_dist[i];
            minindex = i;
        }
    }

    // Добавляем найденный минимальный вес
    // к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины

    if (minindex != 10000)
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
    } while (minindex < 10000);

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

    getchar(); getchar();
    return 0;
}
