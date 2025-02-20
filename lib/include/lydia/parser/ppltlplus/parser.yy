%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.prefix {ppltlPlus}
%define api.namespace {whitemech::lydia::parsers::ppltlplus}
%define api.parser.class {PPLTLPlusParser}

%code requires {
    #include "lydia/logic/ppltlplus/base.hpp"
    #include "lydia/parser/ppltlplus/parser_stype.h"
    namespace whitemech::lydia::parsers::ppltlplus {
        class PPLTLPlusDriver;
        class PPLTLPlusScanner;
    }

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif
}

%parse-param { PPLTLPlusScanner  &scanner  }
%parse-param { PPLTLPlusDriver  &d  }

%code {
    #include <iostream>
    #include <cstdlib>
    #include <fstream>

    #include "lydia/parser/ppltlplus/scanner.hpp"
    #include "lydia/parser/ppltlplus/driver.hpp"

#undef yylex
#define yylex scanner.ppltlPluslex
}

%define parse.assert

%define api.value.type {struct whitemech::lydia::parsers::ppltlplus::PPLTLPlus_YYSTYPE}

%type<formula> input ppltlplus_formula
%type<ppltl_arg> ppltl_formula
%type<symbol_name> SYMBOL

%token              LPAR
%token              RPAR
%token              TRUE_
%token              FALSE_
%token              TT
%token              FF
%token              START
%token              SYMBOL
%token              NEWLINE
%token              END_OF_FILE    0

%left               EQUIVALENCE
%right              IMPLICATION
%left               SINCE
%left               OR
%left               AND
%right              ONCE
%right              HISTORICALLY
%right              YESTERDAY
%right              WEAK_YESTERDAY
%right              NOT
%nonassoc           LPAR

%right              EXISTS
%right              FORALL
%right              EXISTSFORALL
%right              FORALLEXISTS

%locations

%start input

%%

input: ppltlplus_formula     { $$ = $1; d.result = $$; };

ppltl_formula :  ppltl_formula EQUIVALENCE ppltl_formula           { $$ = d.add_PPLTLEquivalence($1, $3); }
                | ppltl_formula IMPLICATION ppltl_formula         { $$ = d.add_PPLTLImplication($1, $3); }
                | ppltl_formula SINCE ppltl_formula               { $$ = d.add_PPLTLSince($1, $3); }
                | ppltl_formula OR ppltl_formula                  { $$ = d.add_PPLTLOr($1, $3); }
                | ppltl_formula AND ppltl_formula                 { $$ = d.add_PPLTLAnd($1, $3); }
                | ONCE ppltl_formula                              { $$ = d.add_PPLTLOnce($2); }
                | HISTORICALLY ppltl_formula                      { $$ = d.add_PPLTLHistorically($2); }
                | YESTERDAY ppltl_formula                         { $$ = d.add_PPLTLYesterday($2); }
                | WEAK_YESTERDAY ppltl_formula                    { $$ = d.add_PPLTLWeakYesterday($2); }
                | NOT ppltl_formula                              { $$ = d.add_PPLTLNot($2); }
                | TRUE_                                          { $$ = d.add_PPLTLTrue(); }
                | FALSE_                                         { $$ = d.add_PPLTLFalse(); }
                | START                                          { $$ = d.add_PPLTLStart(); }
                | SYMBOL                                         { $$ = d.add_PPLTLAtom($1); }
                ;

ppltl_formula: LPAR ppltl_formula RPAR                            { $$ = $2; };

ppltlplus_formula : ppltlplus_formula EQUIVALENCE ppltlplus_formula     { $$ = d.add_PPLTLPlusEquivalence($1, $3); }
                    | ppltlplus_formula IMPLICATION ppltlplus_formula   { $$ = d.add_PPLTLPlusImplication($1, $3); }
                    | ppltlplus_formula AND ppltlplus_formula           { $$ = d.add_PPLTLPlusAnd($1, $3); }
                    | ppltlplus_formula OR ppltlplus_formula            { $$ = d.add_PPLTLPlusOr($1, $3); }
                    | EXISTS ppltl_formula                              { $$ = d.add_PPLTLPlusExists($2); }
                    | FORALL ppltl_formula                              { $$ = d.add_PPLTLPlusForall($2); }
                    | EXISTSFORALL ppltl_formula                        { $$ = d.add_PPLTLPlusExistsForall($2); }
                    | FORALLEXISTS ppltl_formula                        { $$ = d.add_PPLTLPlusForallExists($2); }
                    | NOT ppltlplus_formula                             { $$ = d.add_PPLTLPlusNot($2); }
                    ;

ppltlplus_formula : LPAR ppltlplus_formula RPAR                         { $$ = $2; };

%%

void whitemech::lydia::parsers::ppltlplus::PPLTLPlusParser::error(const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}