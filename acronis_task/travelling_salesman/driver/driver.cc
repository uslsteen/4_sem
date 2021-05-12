#include "driver.hh"

std::vector<CTS::Edge> Edges_{};

//! Constructor for class Driver
//! \param name_of_file - the name of the file from which our program is read
yy::Driver::Driver() : plex_(new OurFlexLexer)
{
  plex_->switch_streams(ifs, std::cout);
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

  /* filling weights matrix */
  weights_ = MX::Matrix<int>{max_junc_, max_junc_};

  for (size_t i = 0; i < e_num; ++i)
  {
    size_t vert1 = juncs[Edges_[i].junc1], vert2 = juncs[Edges_[i].junc2];

    weights_.set(vert1, vert2, Edges_[i].weight);
  }

  std::cout << weights_;

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

  if (juncs.find(junc1) == juncs.end())
    juncs[junc1] = juncs.size();
  if (juncs.find(junc2) == juncs.end())
    juncs[junc2] = juncs.size();

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
    std::cout << edge.junc1 << "--" << edge.junc2 << ", " << edge.weight;
    std::cout << std::endl;
  }
}

//! Destructor for class Driver
yy::Driver::~Driver()
{
  delete plex_;
}

