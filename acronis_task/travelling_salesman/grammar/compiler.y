%language "c++"
%skeleton "lalr1.cc"

%define api.value.type variant
%define parse.error custom

%param {Driver* driver}

%locations


%code requires
{
namespace yy { class Driver; }

#include <string>
#include "graph.hh"
}

%code
{
#include "driver.hh"

namespace yy
{
parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* yylloc, Driver* driver);

};
}

%token  

SEMICOLON      ";"
EDGE           "--"
VOLT           "V"
COMMA          ","
NEW_LINE       "\n"
COLON          ":"

ERR
;

%token <int>   INT
%token <float> DOUBLE

%nterm <int>   junc
%nterm <int>   weight


%%

program:     lines                           { /* program starting */};


lines:       line			                       {};
           | lines line                      {};

line:        line NEW_LINE                   {};
           | expr                            {};

expr:        junc EDGE junc COLON weight     { driver->insert($1, $3, $5); };



junc:        INT                             { $$ = $1; };

weight:      INT                             { $$ = $1;  };


%%

namespace yy
{

  void parser::error (const parser::location_type& location, const std::string& string)
  {
      std::cerr << string << " in (line.column): "<< location << std::endl;
  }

  parser::token_type yylex(parser::semantic_type* yylval, parser::location_type* yylloc, Driver* driver)
  {
       return driver->yylex(yylval, yylloc);
  }

  void parser::report_syntax_error(parser::context const& ctx) const
  {
      driver->report_syntax_error(ctx);
  }

}
