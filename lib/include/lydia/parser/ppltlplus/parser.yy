%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.prefix {ppltlplus}
%define api.namespace {whitemech::lydia::parsers::ppltlplus}
%define api.parser.class {PPTLPlusParser}

%code requires {
    #include "lydia/logic/ppltlplus/base.hpp"
    #include "lydia/parser/ppltlplus/parser_stype.h"
    namespace whitemech::lydia::parsers::ppltlplus {
        class PPTLPlusDriver;
        class PPTLPlusScanner;
    }

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif
}

%parse-param { PPTLPlusScanner  &scanner  }
%parse-param { PPTLPlusDriver  &d  }

%code {
    #include <iostream>
    #include <cstdlib>
    #include <fstream>

    #include "lydia/parser/ppltlplus/scanner.hpp"
    #include "lydia/parser/ppltlplus/driver.hpp"

#undef yylex
#define yylex scanner.ppltlpluslex
}

%define parse.assert

%define api.value.type {struct whitemech::lydia::parsers::ppltlplus::PPTLPlus_YYSTYPE}

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

ppltl_formula :  ppltl_formula EQUIVALENCE ppltl_formula           { $$ = d.add_PPTLEquivalence($1, $3); }
                | ppltl_formula IMPLICATION ppltl_formula         { $$ = d.add_PPTLImplication($1, $3); }
                | ppltl_formula SINCE ppltl_formula               { $$ = d.add_PPTLSince($1, $3); }
                | ppltl_formula OR ppltl_formula                  { $$ = d.add_PPTLOr($1, $3); }
                | ppltl_formula AND ppltl_formula                 { $$ = d.add_PPTLAnd($1, $3); }
                | ONCE ppltl_formula                              { $$ = d.add_PPTLOnce($2); }
                | HISTORICALLY ppltl_formula                      { $$ = d.add_PPTLHistorically($2); }
                | YESTERDAY ppltl_formula                         { $$ = d.add_PPTLYesterday($2); }
                | WEAK_YESTERDAY ppltl_formula                    { $$ = d.add_PPTLWeakYesterday($2); }
                | NOT ppltl_formula                              { $$ = d.add_PPTLNot($2); }
                | TRUE_                                          { $$ = d.add_PPTLTrue(); }
                | FALSE_                                         { $$ = d.add_PPTLFalse(); }
                | START                                          { $$ = d.add_PPTLStart(); }
                | SYMBOL                                         { $$ = d.add_PPTLAtom($1); }
                ;

ppltl_formula: LPAR ppltl_formula RPAR                            { $$ = $2; };

ppltlplus_formula : ppltlplus_formula EQUIVALENCE ppltlplus_formula     { $$ = d.add_PPTLPlusEquivalence($1, $3); }
                    | ppltlplus_formula IMPLICATION ppltlplus_formula   { $$ = d.add_PPTLPlusImplication($1, $3); }
                    | ppltlplus_formula AND ppltlplus_formula           { $$ = d.add_PPTLPlusAnd($1, $3); }
                    | ppltlplus_formula OR ppltlplus_formula            { $$ = d.add_PPTLPlusOr($1, $3); }
                    | EXISTS ppltl_formula                              { $$ = d.add_PPTLPlusExists($2); }
                    | FORALL ppltl_formula                              { $$ = d.add_PPTLPlusForall($2); }
                    | EXISTSFORALL ppltl_formula                        { $$ = d.add_PPTLPlusExistsForall($2); }
                    | FORALLEXISTS ppltl_formula                        { $$ = d.add_PPTLPlusForallExists($2); }
                    | NOT ppltlplus_formula                             { $$ = d.add_PPTLPlusNot($2); }
                    ;

ppltlplus_formula : LPAR ppltlplus_formula RPAR                         { $$ = $2; };

%%

void whitemech::lydia::parsers::ppltlplus::PPTLPlusParser::error(const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}