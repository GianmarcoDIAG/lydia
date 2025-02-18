// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   ldlflex



#include "parser.tab.hh"


// Unqualified %code blocks.
#line 37 "include/lydia/parser/ldlf/parser.yy"

   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "lydia/parser/ldlf/scanner.hpp"
   #include "lydia/parser/ldlf/driver.hpp"

#undef yylex
#define yylex scanner.ldlflex

#line 61 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if LDLFDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !LDLFDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !LDLFDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 6 "include/lydia/parser/ldlf/parser.yy"
namespace whitemech { namespace lydia { namespace parsers { namespace ldlf {
#line 154 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"

  /// Build a parser object.
  LDLfParser::LDLfParser (LDLfScanner  &scanner_yyarg, Driver  &d_yyarg)
#if LDLFDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      d (d_yyarg)
  {}

  LDLfParser::~LDLfParser ()
  {}

  LDLfParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  LDLfParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  LDLfParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  LDLfParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  LDLfParser::symbol_kind_type
  LDLfParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  LDLfParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  LDLfParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  LDLfParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  LDLfParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  LDLfParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  LDLfParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  LDLfParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  LDLfParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  LDLfParser::symbol_kind_type
  LDLfParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  LDLfParser::symbol_kind_type
  LDLfParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  LDLfParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  LDLfParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  LDLfParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  LDLfParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  LDLfParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  LDLfParser::symbol_kind_type
  LDLfParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  LDLfParser::stack_symbol_type::stack_symbol_type ()
  {}

  LDLfParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  LDLfParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  LDLfParser::stack_symbol_type&
  LDLfParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  LDLfParser::stack_symbol_type&
  LDLfParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  LDLfParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if LDLFDEBUG
  template <typename Base>
  void
  LDLfParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  LDLfParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  LDLfParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  LDLfParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if LDLFDEBUG
  std::ostream&
  LDLfParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  LDLfParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  LDLfParser::debug_level_type
  LDLfParser::debug_level () const
  {
    return yydebug_;
  }

  void
  LDLfParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // LDLFDEBUG

  LDLfParser::state_type
  LDLfParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  LDLfParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  LDLfParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  LDLfParser::operator() ()
  {
    return parse ();
  }

  int
  LDLfParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // input: ldlf_formula
#line 92 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = (yystack_[0].value.formula);
                                                                                          d.result = (yylhs.value.formula); }
#line 629 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 3: // ldlf_formula: ldlf_formula EQUIVALENCE ldlf_formula
#line 95 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfEquivalence((yystack_[2].value.formula), (yystack_[0].value.formula)); }
#line 635 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 4: // ldlf_formula: ldlf_formula IMPLICATION ldlf_formula
#line 96 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfImplication((yystack_[2].value.formula), (yystack_[0].value.formula)); }
#line 641 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 5: // ldlf_formula: ldlf_formula OR ldlf_formula
#line 97 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfOr((yystack_[2].value.formula), (yystack_[0].value.formula)); }
#line 647 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 6: // ldlf_formula: ldlf_formula AND ldlf_formula
#line 98 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfAnd((yystack_[2].value.formula), (yystack_[0].value.formula)); }
#line 653 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 7: // ldlf_formula: BOX_LPAR regular_expression BOX_RPAR ldlf_formula
#line 99 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfBox((yystack_[2].value.regex), (yystack_[0].value.formula)); }
#line 659 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 8: // ldlf_formula: DIAMOND_LPAR regular_expression DIAMOND_RPAR ldlf_formula
#line 100 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfDiamond((yystack_[2].value.regex), (yystack_[0].value.formula)); }
#line 665 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 9: // ldlf_formula: NOT ldlf_formula
#line 101 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfNot((yystack_[0].value.formula)); }
#line 671 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 10: // ldlf_formula: TT
#line 102 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfTrue(); }
#line 677 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 11: // ldlf_formula: FF
#line 103 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfFalse(); }
#line 683 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 12: // ldlf_formula: END
#line 104 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfEnd(); }
#line 689 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 13: // ldlf_formula: LAST
#line 105 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = d.add_LDLfLast(); }
#line 695 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 14: // regular_expression: regular_expression UNION regular_expression
#line 108 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.regex) = d.add_UnionRegExp((yystack_[2].value.regex), (yystack_[0].value.regex)); }
#line 701 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 15: // regular_expression: regular_expression SEQUENCE regular_expression
#line 109 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.regex) = d.add_SequenceRegExp((yystack_[2].value.regex), (yystack_[0].value.regex)); }
#line 707 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 16: // regular_expression: regular_expression STAR
#line 110 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.regex) = d.add_StarRegExp((yystack_[1].value.regex)); }
#line 713 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 17: // regular_expression: ldlf_formula TEST
#line 111 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.regex) = d.add_TestRegExp((yystack_[1].value.formula)); }
#line 719 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 18: // regular_expression: propositional_formula
#line 112 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.regex) = d.add_PropositionalRegExp((yystack_[0].value.prop_formula)); }
#line 725 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 19: // propositional_formula: propositional_formula EQUIVALENCE propositional_formula
#line 115 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = d.add_PropositionalEquivalence((yystack_[2].value.prop_formula), (yystack_[0].value.prop_formula)); }
#line 731 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 20: // propositional_formula: propositional_formula IMPLICATION propositional_formula
#line 116 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = d.add_PropositionalImplication((yystack_[2].value.prop_formula), (yystack_[0].value.prop_formula)); }
#line 737 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 21: // propositional_formula: propositional_formula OR propositional_formula
#line 117 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = d.add_PropositionalOr((yystack_[2].value.prop_formula), (yystack_[0].value.prop_formula)); }
#line 743 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 22: // propositional_formula: propositional_formula AND propositional_formula
#line 118 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = d.add_PropositionalAnd((yystack_[2].value.prop_formula), (yystack_[0].value.prop_formula)); }
#line 749 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 23: // propositional_formula: NOT propositional_formula
#line 119 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = d.add_PropositionalNot((yystack_[0].value.prop_formula)); }
#line 755 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 24: // propositional_formula: FALSE_
#line 120 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = d.add_PropositionalBooleanAtom(false); }
#line 761 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 25: // propositional_formula: TRUE_
#line 121 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = d.add_PropositionalBooleanAtom(true); }
#line 767 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 26: // propositional_formula: SYMBOL
#line 122 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = d.add_PropositionalAtom((yystack_[0].value.symbol_name)); }
#line 773 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 27: // ldlf_formula: LPAR ldlf_formula RPAR
#line 125 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.formula) = (yystack_[1].value.formula); }
#line 779 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 28: // regular_expression: LPAR regular_expression RPAR
#line 126 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.regex) = (yystack_[1].value.regex); }
#line 785 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;

  case 29: // propositional_formula: LPAR propositional_formula RPAR
#line 127 "include/lydia/parser/ldlf/parser.yy"
                                                                                        { (yylhs.value.prop_formula) = (yystack_[1].value.prop_formula); }
#line 791 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"
    break;


#line 795 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  LDLfParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if LDLFDEBUG || 0
  const char *
  LDLfParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if LDLFDEBUG || 0









  const signed char LDLfParser::yypact_ninf_ = -12;

  const signed char LDLfParser::yytable_ninf_ = -1;

  const signed char
  LDLfParser::yypact_[] =
  {
      74,    74,   -12,   -12,   -12,   -12,    44,    44,    74,     3,
     106,    84,    44,   -12,   -12,   -12,    65,   104,    93,   114,
     -11,   -12,   -12,    74,    74,    74,    74,   -12,    14,    98,
      87,    65,   -12,   -12,    44,    44,   -12,    74,    53,    53,
      53,    53,    74,    21,    21,    -9,   -12,   -12,   -12,    87,
      -7,    -3,   -12,    53,    53,   116,   116,    -1,   -12,   -12
  };

  const signed char
  LDLfParser::yydefact_[] =
  {
       0,     0,    10,    11,    12,    13,     0,     0,     0,     0,
       2,     0,     0,    25,    24,    26,     0,     0,     0,    18,
       0,     9,     1,     0,     0,     0,     0,    27,     0,     0,
      18,     0,    23,    17,     0,     0,    16,     0,     0,     0,
       0,     0,     0,     3,     4,     5,     6,    28,    29,     0,
      14,    15,     8,     0,     0,    19,    20,    21,    22,     7
  };

  const signed char
  LDLfParser::yypgoto_[] =
  {
     -12,   -12,     0,    -5,     5
  };

  const signed char
  LDLfParser::yydefgoto_[] =
  {
       0,     9,    17,    18,    19
  };

  const signed char
  LDLfParser::yytable_[] =
  {
      10,    11,    20,    22,    34,    35,    36,    29,    21,    35,
      36,    26,    28,    42,    36,     0,    21,    30,    27,    41,
       0,    32,     0,    43,    44,    45,    46,    23,    24,    50,
      51,    11,    33,    25,    26,    24,    49,    52,     0,     0,
      25,    26,    59,    55,    56,    57,    58,    12,     0,     2,
       3,     4,     5,    13,    14,    15,    53,     0,    49,    32,
       0,     0,    13,    14,    15,     6,     7,     0,    31,    16,
       2,     3,     4,     5,    13,    14,    15,     1,    54,     2,
       3,     4,     5,     0,     0,     0,     6,     7,    27,     0,
      16,    48,     0,     0,     0,     6,     7,    23,    24,     8,
      38,    39,    47,    25,    26,     0,    40,    41,    34,    35,
      36,     0,     0,    34,    35,    36,    37,    23,    24,    23,
      24,     0,    33,    25,    26,    25,    26,    38,    39,     0,
      39,     0,     0,    40,    41,    40,    41
  };

  const signed char
  LDLfParser::yycheck_[] =
  {
       0,     1,     7,     0,    15,    16,    17,    12,     8,    16,
      17,    20,    12,    24,    17,    -1,    16,    12,     4,    20,
      -1,    16,    -1,    23,    24,    25,    26,    13,    14,    34,
      35,    31,    18,    19,    20,    14,    31,    37,    -1,    -1,
      19,    20,    42,    38,    39,    40,    41,     3,    -1,     5,
       6,     7,     8,     9,    10,    11,     3,    -1,    53,    54,
      -1,    -1,     9,    10,    11,    21,    22,    -1,     3,    25,
       5,     6,     7,     8,     9,    10,    11,     3,    25,     5,
       6,     7,     8,    -1,    -1,    -1,    21,    22,     4,    -1,
      25,     4,    -1,    -1,    -1,    21,    22,    13,    14,    25,
      13,    14,     4,    19,    20,    -1,    19,    20,    15,    16,
      17,    -1,    -1,    15,    16,    17,    23,    13,    14,    13,
      14,    -1,    18,    19,    20,    19,    20,    13,    14,    -1,
      14,    -1,    -1,    19,    20,    19,    20
  };

  const signed char
  LDLfParser::yystos_[] =
  {
       0,     3,     5,     6,     7,     8,    21,    22,    25,    27,
      28,    28,     3,     9,    10,    11,    25,    28,    29,    30,
      29,    28,     0,    13,    14,    19,    20,     4,    28,    29,
      30,     3,    30,    18,    15,    16,    17,    23,    13,    14,
      19,    20,    24,    28,    28,    28,    28,     4,     4,    30,
      29,    29,    28,     3,    25,    30,    30,    30,    30,    28
  };

  const signed char
  LDLfParser::yyr1_[] =
  {
       0,    26,    27,    28,    28,    28,    28,    28,    28,    28,
      28,    28,    28,    28,    29,    29,    29,    29,    29,    30,
      30,    30,    30,    30,    30,    30,    30,    28,    29,    30
  };

  const signed char
  LDLfParser::yyr2_[] =
  {
       0,     2,     1,     3,     3,     3,     3,     4,     4,     2,
       1,     1,     1,     1,     3,     3,     2,     2,     1,     3,
       3,     3,     3,     2,     1,     1,     1,     3,     3,     3
  };


#if LDLFDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const LDLfParser::yytname_[] =
  {
  "END_OF_FILE", "error", "\"invalid token\"", "LPAR", "RPAR", "TT", "FF",
  "END", "LAST", "TRUE_", "FALSE_", "SYMBOL", "NEWLINE", "EQUIVALENCE",
  "IMPLICATION", "UNION", "SEQUENCE", "STAR", "TEST", "OR", "AND",
  "DIAMOND_LPAR", "BOX_LPAR", "DIAMOND_RPAR", "BOX_RPAR", "NOT", "$accept",
  "input", "ldlf_formula", "regular_expression", "propositional_formula", YY_NULLPTR
  };
#endif


#if LDLFDEBUG
  const signed char
  LDLfParser::yyrline_[] =
  {
       0,    92,    92,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   108,   109,   110,   111,   112,   115,
     116,   117,   118,   119,   120,   121,   122,   125,   126,   127
  };

  void
  LDLfParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  LDLfParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // LDLFDEBUG

  LDLfParser::symbol_kind_type
  LDLfParser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
    };
    // Last valid token kind.
    const int code_max = 280;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 6 "include/lydia/parser/ldlf/parser.yy"
} } } } // whitemech::lydia::parsers::ldlf
#line 1195 "/home/chrber/dev/lydia/lib/include/lydia/parser/ldlf/parser.tab.cc"

#line 129 "include/lydia/parser/ldlf/parser.yy"


void whitemech::lydia::parsers::ldlf::LDLfParser::error(const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
