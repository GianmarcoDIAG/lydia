%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.prefix {ppltl}
%define api.namespace {whitemech::lydia::parsers::ppltl}
%define api.parser.class {PPLTLParser}

%code requires{
   #include "lydia/logic/ppltl/base.hpp"
   #include "lydia/parser/ppltl/parser_stype.h"

namespace whitemech::lydia::parsers::ppltl {
      class PPLTLDriver;
      class PPLTLScanner;
}

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { PPLTLScanner  &scanner  }
%parse-param { PPLTLDriver  &d  }

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
%token                  TRIGGERED

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

ppltl_formula: ppltl_formula EQUIVALENCE ppltl_formula  { $$ = d.add_PPLTLEquivalence($1, $3); }
             | ppltl_formula IMPLICATION ppltl_formula  { $$ = d.add_PPLTLImplication($1, $3); }
             | ppltl_formula SINCE ppltl_formula        { $$ = d.add_PPLTLSince($1, $3); }
             | ppltl_formula OR ppltl_formula           { $$ = d.add_PPLTLOr($1, $3); }
             | ppltl_formula AND ppltl_formula          { $$ = d.add_PPLTLAnd($1, $3); }
             | ONCE ppltl_formula                       { $$ = d.add_PPLTLOnce($2); }
             | HISTORICALLY ppltl_formula               { $$ = d.add_PPLTLHistorically($2); }
             | YESTERDAY ppltl_formula                  { $$ = d.add_PPLTLYesterday($2); }
             | WEAK_YESTERDAY ppltl_formula             { $$ = d.add_PPLTLWeakYesterday($2); }
             | NOT ppltl_formula                        { $$ = d.add_PPLTLNot($2); }
             | TRUE_                                    { $$ = d.add_PPLTLTrue(); }
             | FALSE_                                   { $$ = d.add_PPLTLFalse(); }
             | START                                    { $$ = d.add_PPLTLStart(); }
             | SYMBOL                                   { $$ = d.add_PPLTLAtom($1); }
             ;

ppltl_formula: LPAR ppltl_formula RPAR                 { $$ = $2; };

%%

void whitemech::lydia::parsers::ppltl::PPLTLParser::error(const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}