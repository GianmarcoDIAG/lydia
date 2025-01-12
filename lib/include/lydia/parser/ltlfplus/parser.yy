%skeleton "lalr1.cc" /* -*- C++ -*- */
%require  "3.0"
%debug 
%defines 
%define api.prefix {ltlfplus}
%define api.namespace {whitemech::lydia::parsers::ltlfplus}

%define api.parser.class {LTLfPlusParser}

%code requires {
    #include "lydia/logic/ltlfplus/base.hpp"
    #include "lydia/parser/ltlfplus/parser_stype.h"
    namespace whitemech::lydia::parsers::ltlfplus {
        class LTLfPlusDriver;
        class LTLfPlusScanner;
    }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif
}

%parse-param { LTLfPlusScanner  &scanner  }
%parse-param { LTLfPlusDriver  &d  }

%code {
    #include <iostream>
    #include <cstdlib>
    #include <fstream>

    #include "lydia/parser/ltlfplus/scanner.hpp"
    #include "lydia/parser/ltlfplus/driver.hpp"

#undef yylex
#define yylex scanner.ltlfpluslex
}

%define parse.assert

%define api.value.type {struct whitemech::lydia::parsers::ltlfplus::LTLfPlus_YYSTYPE}

%type<formula> input ltlf_plus_formula 
%type<ltlf_arg> ltlf_formula
%type<symbol_name> SYMBOL

%token              LPAR
%token              RPAR
%token              TRUE_
%token              FALSE_
%token              TT
%token              FF
%token              END
%token              LAST
%token              SYMBOL
%token              NEWLINE
%token              END_OF_FILE    0

%left               EQUIVALENCE
%right              IMPLICATION
%left               UNTIL
%left               RELEASE
%left               OR
%left               AND
%right              EVENTUALLY
%right              ALWAYS
%right              NEXT
%right              WEAK_NEXT
%right              NOT
%nonassoc           LPAR

%right              EXISTS
%right              FORALL
%right              EXISTSFORALL
%right              FORALLEXISTS 

%locations

%start input

%%

input: ltlf_plus_formula     { $$ = $1; d.result = $$; };

ltlf_formula :  ltlf_formula EQUIVALENCE ltlf_formula           { $$ = d.add_LTLfEquivalence($1, $3); }
                | ltlf_formula IMPLICATION ltlf_formula         { $$ = d.add_LTLfImplication($1, $3); }
                | ltlf_formula RELEASE ltlf_formula             { $$ = d.add_LTLfRelease($1, $3); }
                | ltlf_formula UNTIL ltlf_formula               { $$ = d.add_LTLfUntil($1, $3); }
                | ltlf_formula OR ltlf_formula                  { $$ = d.add_LTLfOr($1, $3); }
                | ltlf_formula AND ltlf_formula                 { $$ = d.add_LTLfAnd($1, $3); }
                | ALWAYS ltlf_formula                           { $$ = d.add_LTLfAlways($2); }
                | EVENTUALLY ltlf_formula                       { $$ = d.add_LTLfEventually($2); }      
                | WEAK_NEXT ltlf_formula                        { $$ = d.add_LTLfWeakNext($2); }
                | NEXT ltlf_formula                             { $$ = d.add_LTLfNext($2); }
                | NOT ltlf_formula                              { $$ = d.add_LTLfNot($2); }
                | TT                                            { $$ = d.add_LTLfTrue(); }
                | FF                                            { $$ = d.add_LTLfFalse(); }
                | SYMBOL                                        { $$ = d.add_LTLfAtom($1); }
                ;

ltlf_formula: LPAR ltlf_formula RPAR                            { $$ = $2; };

ltlf_plus_formula : ltlf_plus_formula EQUIVALENCE ltlf_plus_formula     { $$ = d.add_LTLfPlusEquivalence($1, $3); }
                    | ltlf_plus_formula IMPLICATION ltlf_plus_formula   { $$ = d.add_LTLfPlusImplication($1, $3); }
                    | ltlf_plus_formula AND ltlf_plus_formula           { $$ = d.add_LTLfPlusAnd($1, $3); }
                    | ltlf_plus_formula OR ltlf_plus_formula            { $$ = d.add_LTLfPlusOr($1, $3); }
                    | EXISTS ltlf_formula                               { $$ = d.add_LTLfPlusExists($2); }
                    | FORALL ltlf_formula                               { $$ = d.add_LTLfPlusForall($2); }    
                    | EXISTSFORALL ltlf_formula                         { $$ = d.add_LTLfPlusExistsForall($2); }
                    | FORALLEXISTS ltlf_formula                         { $$ = d.add_LTLfPlusForallExists($2); }
                    | NOT ltlf_plus_formula                             { $$ = d.add_LTLfPlusNot($2); }
                    ;

ltlf_plus_formula : LPAR ltlf_plus_formula RPAR                         { $$ = $2; };

%%

void whitemech::lydia::parsers::ltlfplus::LTLfPlusParser::error(const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}