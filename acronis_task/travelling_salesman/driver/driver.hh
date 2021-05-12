#ifndef CIRC_DRIVER_HH
#define CIRC_DRIVER_HH

#include <fstream>
#include <iostream>

#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "matrix.hh"
#include "parser.hh"

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif /* yyFlexLexer */

enum
{
  NUM_OF_TOKENS = 30
};

namespace yy
{

class Driver final
{
private:
  std::unordered_map<size_t, size_t> juncs;
  std::unordered_set<size_t> unique_juncs_with_loops;

  size_t max_junc_{0};

  OurFlexLexer *plex_; // maybe this is good name
  std::vector<std::string> lines_of_prog;

  MX::Matrix<int> incidence_;
  MX::Matrix<double> resistance_;
  MX::Matrix<double> eds_;

  MX::Matrix<int> weights_;

public:
  Driver();

  Driver(const Driver &drvr) = delete;

  Driver &operator=(const Driver &) = delete;

  bool parse();

  void solve();

  void insert(size_t junc1, size_t junc2, int weight);

  parser::token_type yylex(parser::semantic_type *yylval, parser::location_type *yylloc);

  void report_syntax_error(const parser::context &ctx);

  void dump() const;

  void print_curs(const MX::Matrix<double> &curs);

  int d_algo(const MX::Matrix<int>& weights, size_t vec_size);

  ~Driver();
};

} // namespace yy

// namespace yy

#endif // CIRC_DRIVER_HH
