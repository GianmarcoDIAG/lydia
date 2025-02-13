%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.prefix {ppltl}
%define api.namespace {whitemech::lydia::parsers::ppltl}
%define api.parser.class {PPTLParser}

%code requires{
   #include "lydia/logic/ppltl/base.hpp"
   #include "lydia/parser/ppltl/parser_stype.h"

namespace whitemech::lydia::parsers::ppltl {
      class PPTLDriver;
      class PPTLScanner;
}

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { PPTLScanner  &scanner  }
%parse-param { PPTLDriver  &d  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   #include "lydia/parser/ppltl/scanner.hpp"
   #include "lydia/parser/ppltl/driver.hpp"

#undef yylex
#define yylex scanner.ppltllex
}

%define parse.assert

%define api.value.type {struct whitemech::lydia::parsers::ppltl::PPLTL_YYSTYPE}

%type<formula> input ppltl_formula
%type<symbol_name> SYMBOL

%token                  LPAR
%token                  RPAR
%token                  TRUE_
%token                  FALSE_
%token                  TT
%token                  FF
%token                  START
%token                  SYMBOL
%token                  NEWLINE
%token                  END_OF_FILE    0
%token                  YESTERDAY
%token                  WEAK_YESTERDAY
%token                  SINCE
%token                  ONCE
%token                  HISTORICALLY

%left                   EQUIVALENCE
%right                  IMPLICATION
%left                   SINCE
%left                   OR
%left                   AND
%right                  ONCE
%right                  HISTORICALLY
%right                  YESTERDAY
%right                  WEAK_YESTERDAY
%right                  NOT
%nonassoc               LPAR

%locations

%start input

%%

input: ppltl_formula {
    $$ = $1;
    d.result = $$;
};

ppltl_formula: ppltl_formula EQUIVALENCE ppltl_formula  { $$ = d.add_PPTLEquivalence($1, $3); }
             | ppltl_formula IMPLICATION ppltl_formula  { $$ = d.add_PPTLImplication($1, $3); }
             | ppltl_formula SINCE ppltl_formula        { $$ = d.add_PPTLSince($1, $3); }
             | ppltl_formula OR ppltl_formula           { $$ = d.add_PPTLOr($1, $3); }
             | ppltl_formula AND ppltl_formula          { $$ = d.add_PPTLAnd($1, $3); }
             | ONCE ppltl_formula                       { $$ = d.add_PPTLOnce($2); }
             | HISTORICALLY ppltl_formula               { $$ = d.add_PPTLHistorically($2); }
             | YESTERDAY ppltl_formula                  { $$ = d.add_PPTLYesterday($2); }
             | WEAK_YESTERDAY ppltl_formula             { $$ = d.add_PPTLWeakYesterday($2); }
             | NOT ppltl_formula                        { $$ = d.add_PPTLNot($2); }
             | TRUE_                                    { $$ = d.add_PPTLTrue(); }
             | FALSE_                                   { $$ = d.add_PPTLFalse(); }
             | START                                    { $$ = d.add_PPTLStart(); }
             | SYMBOL                                   { $$ = d.add_PPTLAtom($1); }
             ;

ppltl_formula: LPAR ppltl_formula RPAR                 { $$ = $2; };

%%

void whitemech::lydia::parsers::ppltl::PPTLParser::error(const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}