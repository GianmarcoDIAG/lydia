%option debug
%option prefix="ltlfPlus"
%option yyclass="whitemech::lydia::parsers::ltlfplus::LTLfPlusScanner"
%option noyywrap
%option c++

%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexLTLfPlusScanner */
#include "lydia/parser/ltlfplus/scanner_internal.hpp"
#undef  YY_DECL
#define YY_DECL int whitemech::lydia::parsers::ltlfplus::LTLfPlusScanner::yylex( whitemech::lydia::parsers::ltlfplus::LTLfPlus_YYSTYPE * lval, whitemech::lydia::parsers::ltlfplus::LTLfPlusParser::location_type *loc )

using token = whitemech::lydia::parsers::ltlfplus::LTLfPlusParser::token;

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

"X[!]"                      { return token::NEXT; }
"X"                         { return token::WEAK_NEXT; }
"U"                         { return token::UNTIL; }
"R"|"V"                     { return token::RELEASE; }
"F"                         { return token::EVENTUALLY; }
"G"                         { return token::ALWAYS; }

"<=>"|"<->"                 { return token::EQUIVALENCE; }
"=>"|"->"                   { return token::IMPLICATION; }

"&&"|"&"                    { return token::AND; }
"||"|"|"                    { return token::OR; }

"!"|"~"                     { return token::NOT; }

"tt"                        { return token::TT; }
"ff"                        { return token::FF; }

"true"                      { return token::TRUE_; }
"false"                     { return token::FALSE_; }

"last"                      { return token::LAST; }
"end"                       { return token::END; }

"E"                         { return token::EXISTS; }
"A"                         { return token::FORALL; }
"EA"                        { return token::EXISTSFORALL; }
"AE"                        { return token::FORALLEXISTS; }

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