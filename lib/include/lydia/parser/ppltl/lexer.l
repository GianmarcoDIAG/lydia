%option debug
%option prefix="ppltl"
%option yyclass="whitemech::lydia::parsers::ppltl::PPLTLScanner"
%option noyywrap
%option c++

%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexPPLTLScanner */
#include "lydia/parser/ppltl/scanner_internal.hpp"
#undef  YY_DECL
#define YY_DECL int whitemech::lydia::parsers::ppltl::PPLTLScanner::yylex( whitemech::lydia::parsers::ppltl::PPLTL_YYSTYPE * lval, whitemech::lydia::parsers::ppltl::PPLTLParser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = whitemech::lydia::parsers::ppltl::PPLTLParser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END_OF_FILE )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

"("                         { return token::LPAR; }
")"                         { return token::RPAR; }

"Y"                         { return token::YESTERDAY; }
"WY"                        { return token::WEAK_YESTERDAY; }
"S"                         { return token::SINCE; }
"O"                         { return token::ONCE; }
"H"                         { return token::HISTORICALLY; }
"T"                         { return token::TRIGGERED; }

"<=>"|"<->"                 { return token::EQUIVALENCE; }
"=>"|"->"                   { return token::IMPLICATION; }

"&&"|"&"                    { return token::AND; }
"||"|"|"                    { return token::OR; }

"!"|"~"                     { return token::NOT; }

"tt"                        { return token::TT; }
"ff"                        { return token::FF; }

"true"                      { return token::TRUE_; }
"false"                     { return token::FALSE_; }

"start"                     { return token::START; }

[a-z_][a-z0-9_]*|(\"[^\"\t\r\n]+\")|(\'[^\'\t\r\n]+\') {
                                yylval->symbol_name = yytext;
                                return token::SYMBOL;
                            }

\n                          {
                               // Update line number
                               loc->lines();
                               return token::NEWLINE;
                            }
[\t\r\n ]+                  { ; }

%%