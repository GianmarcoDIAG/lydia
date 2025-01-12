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
#define yylex   ltlfpluslex



#include "parser.tab.hh"


// Unqualified %code blocks.
#line 31 "include/lydia/parser/ltlfplus/parser.yy"

    #include <iostream>
    #include <cstdlib>
    #include <fstream>

    #include "lydia/parser/ltlfplus/scanner.hpp"
    #include "lydia/parser/ltlfplus/driver.hpp"

#undef yylex
#define yylex scanner.ltlfpluslex

#line 60 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"


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
#if LTLFPLUSDEBUG

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

#else // !LTLFPLUSDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !LTLFPLUSDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 6 "include/lydia/parser/ltlfplus/parser.yy"
namespace whitemech { namespace lydia { namespace parsers { namespace ltlfplus {
#line 153 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"

  /// Build a parser object.
  LTLfPlusParser::LTLfPlusParser (LTLfPlusScanner  &scanner_yyarg, LTLfPlusDriver  &d_yyarg)
#if LTLFPLUSDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      d (d_yyarg)
  {}

  LTLfPlusParser::~LTLfPlusParser ()
  {}

  LTLfPlusParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  LTLfPlusParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  LTLfPlusParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  LTLfPlusParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  LTLfPlusParser::symbol_kind_type
  LTLfPlusParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  LTLfPlusParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  LTLfPlusParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  LTLfPlusParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  LTLfPlusParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  LTLfPlusParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  LTLfPlusParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  LTLfPlusParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  LTLfPlusParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  LTLfPlusParser::symbol_kind_type
  LTLfPlusParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  LTLfPlusParser::symbol_kind_type
  LTLfPlusParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  LTLfPlusParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  LTLfPlusParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  LTLfPlusParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  LTLfPlusParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  LTLfPlusParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  LTLfPlusParser::symbol_kind_type
  LTLfPlusParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  LTLfPlusParser::stack_symbol_type::stack_symbol_type ()
  {}

  LTLfPlusParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  LTLfPlusParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  LTLfPlusParser::stack_symbol_type&
  LTLfPlusParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  LTLfPlusParser::stack_symbol_type&
  LTLfPlusParser::stack_symbol_type::operator= (stack_symbol_type& that)
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
  LTLfPlusParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if LTLFPLUSDEBUG
  template <typename Base>
  void
  LTLfPlusParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  LTLfPlusParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  LTLfPlusParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  LTLfPlusParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if LTLFPLUSDEBUG
  std::ostream&
  LTLfPlusParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  LTLfPlusParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  LTLfPlusParser::debug_level_type
  LTLfPlusParser::debug_level () const
  {
    return yydebug_;
  }

  void
  LTLfPlusParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // LTLFPLUSDEBUG

  LTLfPlusParser::state_type
  LTLfPlusParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  LTLfPlusParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  LTLfPlusParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  LTLfPlusParser::operator() ()
  {
    return parse ();
  }

  int
  LTLfPlusParser::parse ()
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
  case 2: // input: ltlf_plus_formula
#line 87 "include/lydia/parser/ltlfplus/parser.yy"
                             { (yylhs.value.formula) = (yystack_[0].value.formula); d.result = (yylhs.value.formula); }
#line 627 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 3: // ltlf_formula: ltlf_formula EQUIVALENCE ltlf_formula
#line 89 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfEquivalence((yystack_[2].value.ltlf_arg), (yystack_[0].value.ltlf_arg)); }
#line 633 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 4: // ltlf_formula: ltlf_formula IMPLICATION ltlf_formula
#line 90 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfImplication((yystack_[2].value.ltlf_arg), (yystack_[0].value.ltlf_arg)); }
#line 639 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 5: // ltlf_formula: ltlf_formula RELEASE ltlf_formula
#line 91 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfRelease((yystack_[2].value.ltlf_arg), (yystack_[0].value.ltlf_arg)); }
#line 645 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 6: // ltlf_formula: ltlf_formula UNTIL ltlf_formula
#line 92 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfUntil((yystack_[2].value.ltlf_arg), (yystack_[0].value.ltlf_arg)); }
#line 651 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 7: // ltlf_formula: ltlf_formula OR ltlf_formula
#line 93 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfOr((yystack_[2].value.ltlf_arg), (yystack_[0].value.ltlf_arg)); }
#line 657 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 8: // ltlf_formula: ltlf_formula AND ltlf_formula
#line 94 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfAnd((yystack_[2].value.ltlf_arg), (yystack_[0].value.ltlf_arg)); }
#line 663 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 9: // ltlf_formula: ALWAYS ltlf_formula
#line 95 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfAlways((yystack_[0].value.ltlf_arg)); }
#line 669 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 10: // ltlf_formula: EVENTUALLY ltlf_formula
#line 96 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfEventually((yystack_[0].value.ltlf_arg)); }
#line 675 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 11: // ltlf_formula: WEAK_NEXT ltlf_formula
#line 97 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfWeakNext((yystack_[0].value.ltlf_arg)); }
#line 681 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 12: // ltlf_formula: NEXT ltlf_formula
#line 98 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfNext((yystack_[0].value.ltlf_arg)); }
#line 687 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 13: // ltlf_formula: NOT ltlf_formula
#line 99 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfNot((yystack_[0].value.ltlf_arg)); }
#line 693 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 14: // ltlf_formula: TT
#line 100 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfTrue(); }
#line 699 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 15: // ltlf_formula: FF
#line 101 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfFalse(); }
#line 705 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 16: // ltlf_formula: SYMBOL
#line 102 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = d.add_LTLfAtom((yystack_[0].value.symbol_name)); }
#line 711 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 17: // ltlf_formula: LPAR ltlf_formula RPAR
#line 105 "include/lydia/parser/ltlfplus/parser.yy"
                                                                { (yylhs.value.ltlf_arg) = (yystack_[1].value.ltlf_arg); }
#line 717 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 18: // ltlf_plus_formula: ltlf_plus_formula EQUIVALENCE ltlf_plus_formula
#line 107 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusEquivalence((yystack_[2].value.formula), (yystack_[0].value.formula)); }
#line 723 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 19: // ltlf_plus_formula: ltlf_plus_formula IMPLICATION ltlf_plus_formula
#line 108 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusImplication((yystack_[2].value.formula), (yystack_[0].value.formula)); }
#line 729 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 20: // ltlf_plus_formula: ltlf_plus_formula AND ltlf_plus_formula
#line 109 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusAnd((yystack_[2].value.formula), (yystack_[0].value.formula)); }
#line 735 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 21: // ltlf_plus_formula: ltlf_plus_formula OR ltlf_plus_formula
#line 110 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusOr((yystack_[2].value.formula), (yystack_[0].value.formula)); }
#line 741 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 22: // ltlf_plus_formula: EXISTS ltlf_formula
#line 111 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusExists((yystack_[0].value.ltlf_arg)); }
#line 747 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 23: // ltlf_plus_formula: FORALL ltlf_formula
#line 112 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusForall((yystack_[0].value.ltlf_arg)); }
#line 753 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 24: // ltlf_plus_formula: EXISTSFORALL ltlf_formula
#line 113 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusExistsForall((yystack_[0].value.ltlf_arg)); }
#line 759 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 25: // ltlf_plus_formula: FORALLEXISTS ltlf_formula
#line 114 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusForallExists((yystack_[0].value.ltlf_arg)); }
#line 765 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 26: // ltlf_plus_formula: NOT ltlf_plus_formula
#line 115 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = d.add_LTLfPlusNot((yystack_[0].value.formula)); }
#line 771 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;

  case 27: // ltlf_plus_formula: LPAR ltlf_plus_formula RPAR
#line 118 "include/lydia/parser/ltlfplus/parser.yy"
                                                                        { (yylhs.value.formula) = (yystack_[1].value.formula); }
#line 777 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"
    break;


#line 781 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"

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
  LTLfPlusParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if LTLFPLUSDEBUG || 0
  const char *
  LTLfPlusParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if LTLFPLUSDEBUG || 0









  const signed char LTLfPlusParser::yypact_ninf_ = -13;

  const signed char LTLfPlusParser::yytable_ninf_ = -1;

  const signed char
  LTLfPlusParser::yypact_[] =
  {
      15,    15,    15,    40,    40,    40,    40,    31,    32,    51,
     -13,    40,   -13,   -13,   -13,    40,    40,    40,    40,    40,
       1,     1,     1,     1,   -13,    15,    15,    15,    15,   -13,
       6,   -13,   -13,   -13,   -13,   -13,    40,    40,    40,    40,
      40,    40,    -9,    -9,   -12,   -13,   -13,    56,    56,    36,
       8,    26,   -13
  };

  const signed char
  LTLfPlusParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     2,     0,
      26,     0,    14,    15,    16,     0,     0,     0,     0,     0,
      22,    23,    24,    25,     1,     0,     0,     0,     0,    27,
       0,    10,     9,    12,    11,    13,     0,     0,     0,     0,
       0,     0,    18,    19,    21,    20,    17,     3,     4,     6,
       5,     7,     8
  };

  const signed char
  LTLfPlusParser::yypgoto_[] =
  {
     -13,   -13,    -4,     2
  };

  const signed char
  LTLfPlusParser::yydefgoto_[] =
  {
       0,     7,    20,     8
  };

  const signed char
  LTLfPlusParser::yytable_[] =
  {
      21,    22,    23,     9,    10,    26,    28,    30,    27,    28,
      46,    31,    32,    33,    34,    35,    38,    39,     1,    36,
      37,    38,    39,    40,    41,    40,    41,    42,    43,    44,
      45,    24,    47,    48,    49,    50,    51,    52,     2,     3,
       4,     5,     6,    11,    41,    25,    26,    12,    13,    27,
      28,    14,    39,    40,    41,    29,     0,     0,     0,    15,
      16,    17,    18,    19,    25,    26,     0,     0,    27,    28,
      37,    38,    39,    40,    41
  };

  const signed char
  LTLfPlusParser::yycheck_[] =
  {
       4,     5,     6,     1,     2,    14,    18,    11,    17,    18,
       4,    15,    16,    17,    18,    19,    15,    16,     3,    13,
      14,    15,    16,    17,    18,    17,    18,    25,    26,    27,
      28,     0,    36,    37,    38,    39,    40,    41,    23,    24,
      25,    26,    27,     3,    18,    13,    14,     7,     8,    17,
      18,    11,    16,    17,    18,     4,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    13,    14,    -1,    -1,    17,    18,
      14,    15,    16,    17,    18
  };

  const signed char
  LTLfPlusParser::yystos_[] =
  {
       0,     3,    23,    24,    25,    26,    27,    29,    31,    31,
      31,     3,     7,     8,    11,    19,    20,    21,    22,    23,
      30,    30,    30,    30,     0,    13,    14,    17,    18,     4,
      30,    30,    30,    30,    30,    30,    13,    14,    15,    16,
      17,    18,    31,    31,    31,    31,     4,    30,    30,    30,
      30,    30,    30
  };

  const signed char
  LTLfPlusParser::yyr1_[] =
  {
       0,    28,    29,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31
  };

  const signed char
  LTLfPlusParser::yyr2_[] =
  {
       0,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     1,     1,     1,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     3
  };


#if LTLFPLUSDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const LTLfPlusParser::yytname_[] =
  {
  "END_OF_FILE", "error", "\"invalid token\"", "LPAR", "RPAR", "TRUE_",
  "FALSE_", "TT", "FF", "END", "LAST", "SYMBOL", "NEWLINE", "EQUIVALENCE",
  "IMPLICATION", "UNTIL", "RELEASE", "OR", "AND", "EVENTUALLY", "ALWAYS",
  "NEXT", "WEAK_NEXT", "NOT", "EXISTS", "FORALL", "EXISTSFORALL",
  "FORALLEXISTS", "$accept", "input", "ltlf_formula", "ltlf_plus_formula", YY_NULLPTR
  };
#endif


#if LTLFPLUSDEBUG
  const signed char
  LTLfPlusParser::yyrline_[] =
  {
       0,    87,    87,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   105,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   118
  };

  void
  LTLfPlusParser::yy_stack_print_ () const
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
  LTLfPlusParser::yy_reduce_print_ (int yyrule) const
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
#endif // LTLFPLUSDEBUG

  LTLfPlusParser::symbol_kind_type
  LTLfPlusParser::yytranslate_ (int t) YY_NOEXCEPT
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
      25,    26,    27
    };
    // Last valid token kind.
    const int code_max = 282;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 6 "include/lydia/parser/ltlfplus/parser.yy"
} } } } // whitemech::lydia::parsers::ltlfplus
#line 1169 "/home/gianmarco/Progetti/LydiaSyft/submodules/lydia/lib/include/lydia/parser/ltlfplus/parser.tab.cc"

#line 120 "include/lydia/parser/ltlfplus/parser.yy"


void whitemech::lydia::parsers::ltlfplus::LTLfPlusParser::error(const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
