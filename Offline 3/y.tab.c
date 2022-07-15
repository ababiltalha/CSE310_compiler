/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "SymbolTable.cpp"

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
FILE *fp, *logout, *errorout;
extern int lineCount;
extern int errorCount;

SymbolTable table(30);
vector<string> v;
vector<string> parameterTypeList;
vector<string> parameterNameList;
string returnTypeToMatch;

void split(const string s, char delim) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        v.push_back(item);
    }
}

string getArrayName(const string s){
	stringstream ss(s);
	string item;
	while(getline(ss, item, '['))
		return item;
}

void splitParameterTypeList(const string s, char delim) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        parameterTypeList.push_back(item);
    }
}

void extractParameterNameList(const string s, char delim) {
    bool flag;
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        flag=true;
        stringstream ss2(item);
		string paramName;
		if(getline(ss2, paramName, ' ')) {}
        if(getline(ss2, paramName, ' ')) {
            for(string str : parameterNameList){
                if(paramName==str){
                    // multiple parameter same error
					errorCount++;
					fprintf(errorout, "Error at line %d: Multiple declaration of %s in parameter\n\n", lineCount, paramName.c_str());
					fprintf(logout, "Error at line %d: Multiple declaration of %s in parameter\n\n", lineCount, paramName.c_str());
                    flag=false;
                }
            }
			// if(flag)
				parameterNameList.push_back(paramName);
		}
    }
}

void clearVector() {
	v.clear();
}

void clearParameterTypeList() {
	parameterTypeList.clear();
}

void clearParameterNameList() {
	parameterNameList.clear();
}

void yyerror(char *s)
{
	errorCount++;
	fprintf(errorout, "Error at line %d: %s\n\n", lineCount, s);
	fprintf(logout, "Error at line %d: %s\n\n", lineCount, s);
	

}



#line 161 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    WHILE = 261,                   /* WHILE  */
    INT = 262,                     /* INT  */
    FLOAT = 263,                   /* FLOAT  */
    DOUBLE = 264,                  /* DOUBLE  */
    CHAR = 265,                    /* CHAR  */
    RETURN = 266,                  /* RETURN  */
    VOID = 267,                    /* VOID  */
    PRINTLN = 268,                 /* PRINTLN  */
    DO = 269,                      /* DO  */
    BREAK = 270,                   /* BREAK  */
    SWITCH = 271,                  /* SWITCH  */
    CASE = 272,                    /* CASE  */
    DEFAULT = 273,                 /* DEFAULT  */
    CONTINUE = 274,                /* CONTINUE  */
    ASSIGNOP = 275,                /* ASSIGNOP  */
    NOT = 276,                     /* NOT  */
    SEMICOLON = 277,               /* SEMICOLON  */
    COMMA = 278,                   /* COMMA  */
    LPAREN = 279,                  /* LPAREN  */
    RPAREN = 280,                  /* RPAREN  */
    LCURL = 281,                   /* LCURL  */
    RCURL = 282,                   /* RCURL  */
    LTHIRD = 283,                  /* LTHIRD  */
    RTHIRD = 284,                  /* RTHIRD  */
    INCOP = 285,                   /* INCOP  */
    DECOP = 286,                   /* DECOP  */
    ID = 287,                      /* ID  */
    ADDOP = 288,                   /* ADDOP  */
    MULOP = 289,                   /* MULOP  */
    RELOP = 290,                   /* RELOP  */
    LOGICOP = 291,                 /* LOGICOP  */
    CONST_INT = 292,               /* CONST_INT  */
    CONST_FLOAT = 293,             /* CONST_FLOAT  */
    LOWER_THAN_ELSE = 294          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define INT 262
#define FLOAT 263
#define DOUBLE 264
#define CHAR 265
#define RETURN 266
#define VOID 267
#define PRINTLN 268
#define DO 269
#define BREAK 270
#define SWITCH 271
#define CASE 272
#define DEFAULT 273
#define CONTINUE 274
#define ASSIGNOP 275
#define NOT 276
#define SEMICOLON 277
#define COMMA 278
#define LPAREN 279
#define RPAREN 280
#define LCURL 281
#define RCURL 282
#define LTHIRD 283
#define RTHIRD 284
#define INCOP 285
#define DECOP 286
#define ID 287
#define ADDOP 288
#define MULOP 289
#define RELOP 290
#define LOGICOP 291
#define CONST_INT 292
#define CONST_FLOAT 293
#define LOWER_THAN_ELSE 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 91 "parser.y"

	SymbolInfo* symbol;

#line 296 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_FLOAT = 8,                      /* FLOAT  */
  YYSYMBOL_DOUBLE = 9,                     /* DOUBLE  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_VOID = 12,                      /* VOID  */
  YYSYMBOL_PRINTLN = 13,                   /* PRINTLN  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_SWITCH = 16,                    /* SWITCH  */
  YYSYMBOL_CASE = 17,                      /* CASE  */
  YYSYMBOL_DEFAULT = 18,                   /* DEFAULT  */
  YYSYMBOL_CONTINUE = 19,                  /* CONTINUE  */
  YYSYMBOL_ASSIGNOP = 20,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_SEMICOLON = 22,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_LPAREN = 24,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 25,                    /* RPAREN  */
  YYSYMBOL_LCURL = 26,                     /* LCURL  */
  YYSYMBOL_RCURL = 27,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 28,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 29,                    /* RTHIRD  */
  YYSYMBOL_INCOP = 30,                     /* INCOP  */
  YYSYMBOL_DECOP = 31,                     /* DECOP  */
  YYSYMBOL_ID = 32,                        /* ID  */
  YYSYMBOL_ADDOP = 33,                     /* ADDOP  */
  YYSYMBOL_MULOP = 34,                     /* MULOP  */
  YYSYMBOL_RELOP = 35,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 36,                   /* LOGICOP  */
  YYSYMBOL_CONST_INT = 37,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 38,               /* CONST_FLOAT  */
  YYSYMBOL_LOWER_THAN_ELSE = 39,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_start = 41,                     /* start  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_unit = 43,                      /* unit  */
  YYSYMBOL_func_declaration = 44,          /* func_declaration  */
  YYSYMBOL_func_definition = 45,           /* func_definition  */
  YYSYMBOL_46_1 = 46,                      /* $@1  */
  YYSYMBOL_47_2 = 47,                      /* $@2  */
  YYSYMBOL_parameter_list = 48,            /* parameter_list  */
  YYSYMBOL_compound_statement = 49,        /* compound_statement  */
  YYSYMBOL_enter_scope = 50,               /* enter_scope  */
  YYSYMBOL_var_declaration = 51,           /* var_declaration  */
  YYSYMBOL_type_specifier = 52,            /* type_specifier  */
  YYSYMBOL_declaration_list = 53,          /* declaration_list  */
  YYSYMBOL_statements = 54,                /* statements  */
  YYSYMBOL_statement = 55,                 /* statement  */
  YYSYMBOL_expression_statement = 56,      /* expression_statement  */
  YYSYMBOL_variable = 57,                  /* variable  */
  YYSYMBOL_expression = 58,                /* expression  */
  YYSYMBOL_logic_expression = 59,          /* logic_expression  */
  YYSYMBOL_rel_expression = 60,            /* rel_expression  */
  YYSYMBOL_simple_expression = 61,         /* simple_expression  */
  YYSYMBOL_term = 62,                      /* term  */
  YYSYMBOL_unary_expression = 63,          /* unary_expression  */
  YYSYMBOL_factor = 64,                    /* factor  */
  YYSYMBOL_argument_list = 65,             /* argument_list  */
  YYSYMBOL_arguments = 66                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   103,   103,   109,   116,   123,   128,   133,   140,   167,
     191,   190,   265,   264,   323,   328,   333,   338,   343,   347,
     358,   368,   385,   433,   438,   443,   450,   457,   471,   477,
     490,   500,   509,   519,   528,   531,   536,   543,   546,   551,
     556,   561,   570,   577,   586,   593,   607,   630,   635,   642,
     657,   688,   719,   724,   757,   762,   778,   783,   799,   804,
     826,   829,   834,   871,   882,   893,   900,   905,   963,   969,
     974,   979,   985,   993,   999,  1005,  1012
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "INT", "FLOAT", "DOUBLE", "CHAR", "RETURN", "VOID", "PRINTLN",
  "DO", "BREAK", "SWITCH", "CASE", "DEFAULT", "CONTINUE", "ASSIGNOP",
  "NOT", "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LCURL", "RCURL",
  "LTHIRD", "RTHIRD", "INCOP", "DECOP", "ID", "ADDOP", "MULOP", "RELOP",
  "LOGICOP", "CONST_INT", "CONST_FLOAT", "LOWER_THAN_ELSE", "$accept",
  "start", "program", "unit", "func_declaration", "func_definition", "$@1",
  "$@2", "parameter_list", "compound_statement", "enter_scope",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-58)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      13,   -75,   -75,   -75,    16,    13,   -75,   -75,   -75,   -75,
     -10,   -75,   -75,    18,    11,     7,     2,   -75,   -75,    -4,
      26,     1,    28,   -75,    21,    37,    52,   -75,    55,   -75,
      13,    64,   -75,   -75,   -75,    66,   -75,   -75,    58,   -75,
      55,   -75,    67,    71,    86,   -75,   -75,   -75,   -75,    77,
      78,    81,   167,    82,   167,   -75,   167,   -75,    51,   167,
     -75,   -75,   -75,   -75,    79,    50,   -75,   -75,    39,    87,
     -75,    80,   116,    88,   -75,   -75,   167,   145,   167,    92,
      83,    54,   -75,    95,   167,   152,   -75,    93,   -75,   -75,
     -75,   167,   -75,   -75,   -75,   167,   -75,   167,   167,   167,
     101,   145,   106,   -75,   107,   -75,   -75,   111,   114,   -75,
     113,   -75,   -75,    88,   139,   -75,   122,   167,   122,   125,
     -75,   167,   -75,   146,   128,   -75,   -75,   -75,   122,   122,
     -75,   -75
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,    24,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    28,     0,     0,     0,    34,    22,     0,
      12,     0,    17,    30,     0,     0,    26,     9,     0,    18,
       0,    10,    16,    29,    32,     0,    21,    13,    15,     8,
       0,    31,     0,     0,     0,    14,    11,    27,    33,     0,
       0,     0,     0,     0,     0,    47,     0,    20,    49,     0,
      69,    70,    40,    38,     0,     0,    35,    39,    66,     0,
      52,    54,     0,    58,    61,    65,     0,     0,     0,     0,
       0,    66,    64,     0,    74,     0,    63,    28,    37,    19,
      36,     0,    71,    72,    48,     0,    60,     0,     0,     0,
       0,     0,     0,    46,     0,    68,    76,     0,    73,    51,
       0,    53,    55,    59,     0,    62,     0,     0,     0,     0,
      67,     0,    50,    42,     0,    44,    45,    75,     0,     0,
      43,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   -75,   151,   -75,   -75,   -75,   -75,   -75,   -22,
     -75,    73,     8,   -75,   -75,   -64,   -66,   -54,   -49,   -74,
      62,    60,    68,   -50,   -75,   -75,   -75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    40,    28,    21,    62,
      44,    63,    64,    14,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   107,   108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      81,    90,    29,    79,    82,    81,    37,    83,    10,    86,
     106,   101,    17,    10,     1,     2,    11,   111,    46,     3,
       1,     2,    13,    22,    30,     3,    31,   100,    26,   102,
      81,    23,    20,    18,    19,   117,   110,    81,    38,    24,
      25,    81,    15,    81,    81,    81,    16,   127,    27,   115,
      33,    88,   123,    49,   125,    50,    51,     1,     2,    91,
      32,    52,     3,    53,   130,   131,    34,    81,   124,    92,
      93,    54,    55,     9,    56,    84,    36,    89,     9,    85,
      35,    36,    58,    59,    92,    93,    39,    60,    61,    49,
      45,    50,    51,     1,     2,    41,    47,    52,     3,    53,
      48,    76,    77,    42,    43,    78,    80,    54,    55,    94,
      56,    87,    36,    57,   103,   104,    95,    96,    58,    59,
     105,    16,    99,    60,    61,    49,   116,    50,    51,     1,
       2,   118,   119,    52,     3,    53,   120,   121,   -56,   -56,
      96,   -56,   122,    54,    55,   -56,    56,   126,    36,    97,
     128,    98,   -56,   129,    58,    59,    12,   112,   114,    60,
      61,   -57,   -57,     0,   -57,   113,    54,    55,   -57,    56,
       0,     0,    97,    54,     0,   -57,    56,    58,    59,     0,
       0,   109,    60,    61,    58,    59,     0,     0,    54,    60,
      61,    56,     0,     0,     0,     0,     0,     0,     0,    58,
      59,     0,     0,     0,    60,    61
};

static const yytype_int16 yycheck[] =
{
      54,    65,     1,    52,    54,    59,    28,    56,     0,    59,
      84,    77,     1,     5,     7,     8,     0,    91,    40,    12,
       7,     8,    32,    15,    23,    12,    25,    76,    32,    78,
      84,    29,    25,    22,    23,   101,    85,    91,    30,    37,
      38,    95,    24,    97,    98,    99,    28,   121,    22,    99,
      29,     1,   116,     3,   118,     5,     6,     7,     8,    20,
      32,    11,    12,    13,   128,   129,    29,   121,   117,    30,
      31,    21,    22,     0,    24,    24,    26,    27,     5,    28,
      28,    26,    32,    33,    30,    31,    22,    37,    38,     3,
      32,     5,     6,     7,     8,    29,    29,    11,    12,    13,
      29,    24,    24,    37,    38,    24,    24,    21,    22,    22,
      24,    32,    26,    27,    22,    32,    36,     1,    32,    33,
      25,    28,    34,    37,    38,     3,    25,     5,     6,     7,
       8,    25,    25,    11,    12,    13,    25,    23,    22,    23,
       1,    25,    29,    21,    22,    29,    24,    22,    26,    33,
       4,    35,    36,    25,    32,    33,     5,    95,    98,    37,
      38,    22,    23,    -1,    25,    97,    21,    22,    29,    24,
      -1,    -1,    33,    21,    -1,    36,    24,    32,    33,    -1,
      -1,    29,    37,    38,    32,    33,    -1,    -1,    21,    37,
      38,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,    -1,    -1,    37,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    12,    41,    42,    43,    44,    45,    51,
      52,     0,    43,    32,    53,    24,    28,     1,    22,    23,
      25,    48,    52,    29,    37,    38,    32,    22,    47,     1,
      23,    25,    32,    29,    29,    28,    26,    49,    52,    22,
      46,    29,    37,    38,    50,    32,    49,    29,    29,     3,
       5,     6,    11,    13,    21,    22,    24,    27,    32,    33,
      37,    38,    49,    51,    52,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    24,    24,    24,    58,
      24,    57,    63,    58,    24,    28,    63,    32,     1,    27,
      55,    20,    30,    31,    22,    36,     1,    33,    35,    34,
      58,    56,    58,    22,    32,    25,    59,    65,    66,    29,
      58,    59,    60,    62,    61,    63,    25,    56,    25,    25,
      25,    23,    29,    55,    58,    55,    22,    59,     4,    25,
      55,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    44,    44,
      46,    45,    47,    45,    48,    48,    48,    48,    48,    49,
      49,    50,    51,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    54,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    56,    56,    57,
      57,    57,    58,    58,    59,    59,    60,    60,    61,    61,
      61,    62,    62,    63,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    65,    65,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     2,     4,
       3,     0,     3,     1,     1,     1,     3,     6,     1,     4,
       3,     5,     4,     6,     2,     1,     2,     2,     1,     1,
       1,     7,     5,     7,     5,     5,     3,     1,     2,     1,
       4,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       2,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 104 "parser.y"
        {
		fprintf(logout, "Line %d: start : program\n\n", lineCount);
	}
#line 1447 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 110 "parser.y"
        {
		(yyval.symbol) = new SymbolInfo((yyvsp[-1].symbol)->getName()+"\n"+(yyvsp[0].symbol)->getName(),"program");
		fprintf(logout, "Line %d: program : program unit\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $1;
		// deleete $2;
	}
#line 1458 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 117 "parser.y"
        {
		(yyval.symbol) = (yyvsp[0].symbol);
		fprintf(logout, "Line %d: program : unit\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
	}
#line 1467 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 124 "parser.y"
        {
		(yyval.symbol) = (yyvsp[0].symbol);
		fprintf(logout, "Line %d: unit : var_declaration\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
	}
#line 1476 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 129 "parser.y"
        {
		(yyval.symbol) = (yyvsp[0].symbol);
		fprintf(logout, "Line %d: unit : func_declaration\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
	}
#line 1485 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 134 "parser.y"
        {
		(yyval.symbol) = (yyvsp[0].symbol);
		fprintf(logout, "Line %d: unit : func_definition\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
	}
#line 1494 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 141 "parser.y"
                {
			string returnType = (yyvsp[-5].symbol)->getName();
			string funcName = (yyvsp[-4].symbol)->getName();
			SymbolInfo* temp = table.lookUpSymbol(funcName);
			if (temp!=nullptr)
			{
				errorCount++;
				fprintf(errorout, "Error at line %d: Multiple declaration of function %s\n\n", lineCount, funcName.c_str());
				fprintf(logout, "Error at line %d: Multiple declaration of function %s\n\n", lineCount, funcName.c_str());
			}
			else {
				splitParameterTypeList((yyvsp[-2].symbol)->getType(), ',');


				FunctionInfo* f= new FunctionInfo(funcName, returnType);
				for(string parameterType : parameterTypeList)
					f->addParameter(parameterType);
				table.insertSymbolInfo(f);
				clearParameterTypeList();
			}
			table.enterScope();table.exitScope(); // dummy scope for declaration
			(yyval.symbol) = new SymbolInfo((yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+"("+(yyvsp[-2].symbol)->getName()+");","func_declaration");
			fprintf(logout, "Line %d: func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
		}
#line 1525 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 168 "parser.y"
                {
			string returnType = (yyvsp[-4].symbol)->getName();
			string funcName = (yyvsp[-3].symbol)->getName();
			SymbolInfo* temp = table.lookUpSymbol(funcName);
			if (temp!=nullptr)
			{
				errorCount++;
				fprintf(errorout, "Error at line %d: Multiple declaration of function %s\n\n", lineCount, funcName.c_str());
				fprintf(logout, "Error at line %d: Multiple declaration of function %s\n\n", lineCount, funcName.c_str());
			}
			else {
				FunctionInfo* f= new FunctionInfo(funcName, returnType);
				table.insertSymbolInfo(f);
			}
			table.enterScope();table.exitScope(); // dummy scope for declaration
			(yyval.symbol) = new SymbolInfo((yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+"();","func_declaration");
			fprintf(logout, "Line %d: func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
		}
#line 1550 "y.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 191 "parser.y"
                {
			string returnType = (yyvsp[-4].symbol)->getName();
			returnTypeToMatch= returnType;
			string funcName = (yyvsp[-3].symbol)->getName();
			splitParameterTypeList((yyvsp[-1].symbol)->getType(), ',');
			// for (int i = 0; i < parameterTypeList.size(); i++)
        		// cout<<parameterTypeList[i]<<endl;
			extractParameterNameList((yyvsp[-1].symbol)->getName(),',');
			// for (int i = 0; i < parameterNameList.size(); i++)
        		// cout<<parameterNameList[i]<<endl;
			SymbolInfo* temp = table.lookUpSymbol(funcName);
			if (temp!=nullptr) // exists in symboltable, may or may not be func, decl or defn
			{
				// cout<<temp->getType()<<endl;
				
				if (temp->getType()=="FUNCTION"){
					FunctionInfo* ftemp=(FunctionInfo*) temp;
					if(ftemp->getDefined()){
						errorCount++;
						fprintf(errorout, "Error at line %d: Multiple definition of function %s\n\n", lineCount, funcName.c_str());
						fprintf(logout, "Error at line %d: Multiple definition of function %s\n\n", lineCount, funcName.c_str());
					}
					else { // decl but not defn, working case
						// return type matching
						if (ftemp->getReturnType() != returnType) {
							errorCount++;
							fprintf(errorout, "Error at line %d: Return type mismatch with function declaration in function %s\n\n", lineCount, funcName.c_str());
							fprintf(logout, "Error at line %d: Return type mismatch with function declaration in function %s\n\n", lineCount, funcName.c_str());
						}
						// total number of arguments mismatch
						if ((ftemp->getParameterTypeList().size() != parameterTypeList.size())) {
							
							errorCount++;
							fprintf(errorout, "Error at line %d: Total number of arguments mismatch with declaration in function %s\n\n", lineCount, funcName.c_str());
							fprintf(logout, "Error at line %d: Total number of arguments mismatch with declaration in function %s\n\n", lineCount, funcName.c_str());
						}
						else {
							for(int i=0; i<ftemp->getParameterTypeList().size(); i++){
								if (ftemp->getParameterTypeList()[i] != parameterTypeList[i]){
									errorCount++;
									fprintf(errorout, "Error at line %d: %dth parameter mismatch with declaration in function %s\n\n", lineCount, i+1, funcName.c_str());
									fprintf(logout, "Error at line %d: %dth parameter mismatch with declaration in function %s\n\n", lineCount, i+1, funcName.c_str());
									break;
								}
							}

						}
						ftemp->setDefined(true);
						
					}
				}
				else { // not a function 
					errorCount++;
					fprintf(errorout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, funcName.c_str());
					fprintf(logout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, funcName.c_str());
				}
			}
			else { // not in symboltable
				FunctionInfo* f= new FunctionInfo(funcName, returnType);
				for(string parameterType : parameterTypeList)
					f->addParameter(parameterType);
				f->setDefined(true);
				table.insertSymbolInfo(f);
			}
			;
		}
#line 1621 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 256 "parser.y"
                                     {
			(yyval.symbol) = new SymbolInfo((yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+"("+(yyvsp[-3].symbol)->getName()+")"+(yyvsp[0].symbol)->getName()+"\n","func_definition");
			fprintf(logout, "Line %d: func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $4;
			// deleete $7;
		}
#line 1634 "y.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 265 "parser.y"
                {
			string returnType = (yyvsp[-3].symbol)->getName();
			returnTypeToMatch= returnType;
			string funcName = (yyvsp[-2].symbol)->getName();
			
			SymbolInfo* temp = table.lookUpSymbol(funcName);
			if (temp!=nullptr) // exists in symboltable, may or may not be func, decl or defn
			{
				// cout<<temp->getType()<<endl;
				
				if (temp->getType()=="FUNCTION"){
					FunctionInfo* ftemp=(FunctionInfo*) temp;
					if(ftemp->getDefined()){
						errorCount++;
						fprintf(errorout, "Error at line %d: Multiple definition of function %s\n\n", lineCount, funcName.c_str());
						fprintf(logout, "Error at line %d: Multiple definition of function %s\n\n", lineCount, funcName.c_str());
					}
					else { // decl but not defn, working case
						// return type matching

						if (ftemp->getReturnType() != returnType) {
							errorCount++;
							fprintf(errorout, "Error at line %d: Return type mismatch with function declaration in function %s\n\n", lineCount, funcName.c_str());
							fprintf(logout, "Error at line %d: Return type mismatch with function declaration in function %s\n\n", lineCount, funcName.c_str());
						}
						// total number of arguments mismatch
						if ((ftemp->getParameterTypeList().size() != 0)) {
							errorCount++;
							fprintf(errorout, "Error at line %d: Total number of arguments mismatch with declaration in function %s\n\n", lineCount, funcName.c_str());
							fprintf(logout, "Error at line %d: Total number of arguments mismatch with declaration in function %s\n\n", lineCount, funcName.c_str());
						}
						
						ftemp->setDefined(true);
						
					}
				}
				else { // not a function 
					errorCount++;
					fprintf(errorout, "Error at line %d: %s not a function\n\n", lineCount, funcName.c_str());
					fprintf(logout, "Error at line %d: %s not a function\n\n", lineCount, funcName.c_str());
				}
			}
			else { // not in symboltable
				FunctionInfo* f= new FunctionInfo(funcName, returnType);
				f->setDefined(true);
				table.insertSymbolInfo(f);
			}
			
		}
#line 1688 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN RPAREN $@2 compound_statement  */
#line 313 "parser.y"
                                     {
			(yyval.symbol) = new SymbolInfo((yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+"()"+(yyvsp[0].symbol)->getName()+"\n","func_definition");
			fprintf(logout, "Line %d: func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n%s\n\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $6;
		}
#line 1700 "y.tab.c"
    break;

  case 14: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 324 "parser.y"
                {
			(yyval.symbol) = new SymbolInfo((yyvsp[-3].symbol)->getName() + "," + (yyvsp[-1].symbol)->getName() + " " + (yyvsp[0].symbol)->getName(), (yyvsp[-3].symbol)->getType() + "," + (yyvsp[-1].symbol)->getType());
			fprintf(logout, "Line %d: parameter_list : parameter_list COMMA type_specifier ID\n\n%s\n\n",  lineCount, (yyval.symbol)->getName().c_str());
		}
#line 1709 "y.tab.c"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier  */
#line 329 "parser.y"
                {
			(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName() + "," + (yyvsp[0].symbol)->getName(), (yyvsp[-2].symbol)->getType() + "," + (yyvsp[0].symbol)->getType());
			fprintf(logout, "Line %d: parameter_list : parameter_list COMMA type_specifier\n\n%s\n\n",  lineCount, (yyval.symbol)->getName().c_str());
		}
#line 1718 "y.tab.c"
    break;

  case 16: /* parameter_list: type_specifier ID  */
#line 334 "parser.y"
                {
			(yyval.symbol) = new SymbolInfo((yyvsp[-1].symbol)->getName() + " " + (yyvsp[0].symbol)->getName(), (yyvsp[-1].symbol)->getType());
			fprintf(logout, "Line %d: parameter_list : type_specifier ID\n\n%s\n\n",  lineCount, (yyval.symbol)->getName().c_str());
		}
#line 1727 "y.tab.c"
    break;

  case 17: /* parameter_list: type_specifier  */
#line 339 "parser.y"
                {
			(yyval.symbol) = (yyvsp[0].symbol);
			fprintf(logout, "Line %d: parameter_list : type_specifier\n\n%s\n\n",  lineCount, (yyval.symbol)->getName().c_str());
		}
#line 1736 "y.tab.c"
    break;

  case 18: /* parameter_list: parameter_list error  */
#line 343 "parser.y"
                                       {}
#line 1742 "y.tab.c"
    break;

  case 19: /* compound_statement: LCURL enter_scope statements RCURL  */
#line 348 "parser.y"
                        {
				

				(yyval.symbol) = new SymbolInfo("{\n"+(yyvsp[-1].symbol)->getName()+"\n}\n","compound_statement");
				fprintf(logout, "Line %d: compound_statement : LCURL statements RCURL\n\n%s\n\n",  lineCount, (yyval.symbol)->getName().c_str());

				fprintf(logout, "\n\n%s\n\n", table.printAllScope().c_str());
				table.exitScope();
				
			}
#line 1757 "y.tab.c"
    break;

  case 20: /* compound_statement: LCURL enter_scope RCURL  */
#line 359 "parser.y"
                        {
				(yyval.symbol) = new SymbolInfo("{\n}\n","compound_statement");
				fprintf(logout, "Line %d: compound_statement : LCURL RCURL\n\n%s\n\n",  lineCount, (yyval.symbol)->getName().c_str());

				fprintf(logout, "\n\n%s\n\n", table.printAllScope().c_str());
				table.exitScope();
			}
#line 1769 "y.tab.c"
    break;

  case 21: /* enter_scope: %empty  */
#line 368 "parser.y"
                        {
				table.enterScope();
				if ((parameterNameList.size() != parameterTypeList.size())) {
					errorCount++;
					fprintf(errorout, "Error at line %d: Parameters name not given in function definition\n\n", lineCount);
					fprintf(logout, "Error at line %d: Parameters name not given in function definition\n\n", lineCount);
				}
				else if(parameterTypeList.size()>0){
					for(int i=0; i<parameterTypeList.size(); i++){
						table.insertSymbol(parameterNameList[i], parameterTypeList[i]);
					}
				}
				clearParameterNameList();
				clearParameterTypeList();
			}
#line 1789 "y.tab.c"
    break;

  case 22: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 386 "parser.y"
                {
			string varType = (yyvsp[-2].symbol)->getName();
			string varList = (yyvsp[-1].symbol)->getName();
			if ((yyvsp[-2].symbol)->getName()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Variable type cannot be void \n\n", lineCount);
				fprintf(logout, "Error at line %d: Variable type cannot be void \n\n", lineCount);
			}
			
			else {
				split(varList,',');
				for (string var : v){
					
					// printf("%s ",iter.c_str());

					if ((var.find("[") != string::npos) || (var.find("]") != string::npos)) {
						// printf("array");
						string arrayName = getArrayName(var);
						bool newSymbol = table.insertSymbol(arrayName, varType+"[]");
						if(!newSymbol){
							errorCount++;
							fprintf(errorout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, arrayName.c_str());
							fprintf(logout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, arrayName.c_str());
						}
					}

					else {
						bool newSymbol = table.insertSymbol(var, varType);
						if(!newSymbol){
							errorCount++;
							fprintf(errorout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, var.c_str());
							fprintf(logout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, var.c_str());
						}
					}


				}
				clearVector();
			}

			(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+";", "var_declaration");
			fprintf(logout, "Line %d: var_declaration : type_specifier declaration_list SEMICOLON\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
		}
#line 1839 "y.tab.c"
    break;

  case 23: /* type_specifier: INT  */
#line 434 "parser.y"
                {
			(yyval.symbol)= new SymbolInfo("int","int");
			fprintf(logout, "Line %d: type_specifier : INT\n\nint\n\n", lineCount);
		}
#line 1848 "y.tab.c"
    break;

  case 24: /* type_specifier: FLOAT  */
#line 439 "parser.y"
                {
			(yyval.symbol)= new SymbolInfo("float","float");
			fprintf(logout, "Line %d: type_specifier : FLOAT\n\nfloat\n\n", lineCount);
		}
#line 1857 "y.tab.c"
    break;

  case 25: /* type_specifier: VOID  */
#line 444 "parser.y"
                {
			(yyval.symbol)= new SymbolInfo("void","void");
			fprintf(logout, "Line %d: type_specifier : VOID\n\nvoid\n\n", lineCount);
		}
#line 1866 "y.tab.c"
    break;

  case 26: /* declaration_list: declaration_list COMMA ID  */
#line 451 "parser.y"
                  {
			(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+","+(yyvsp[0].symbol)->getName(), "declaration_list");
			fprintf(logout, "Line %d: declaration_list : declaration_list COMMA ID\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $3;
		  }
#line 1877 "y.tab.c"
    break;

  case 27: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 458 "parser.y"
                  {
			if((yyvsp[-1].symbol)->getName()=="0"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Array size cannot be zero\n\n", lineCount);
				fprintf(logout, "Error at line %d: Array size cannot be zero\n\n", lineCount);
			}
			
			(yyval.symbol) = new SymbolInfo((yyvsp[-5].symbol)->getName()+","+(yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $3;
			// deleete $5;
		  }
#line 1895 "y.tab.c"
    break;

  case 28: /* declaration_list: ID  */
#line 472 "parser.y"
                  {
			(yyval.symbol) = new SymbolInfo((yyvsp[0].symbol)->getName(), "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
		  }
#line 1905 "y.tab.c"
    break;

  case 29: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 478 "parser.y"
                  {
			if((yyvsp[-1].symbol)->getName()=="0"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Array size cannot be zero\n\n", lineCount);
				fprintf(logout, "Error at line %d: Array size cannot be zero\n\n", lineCount);
			}
			
			(yyval.symbol) = new SymbolInfo((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $3;
		  }
#line 1922 "y.tab.c"
    break;

  case 30: /* declaration_list: ID LTHIRD RTHIRD  */
#line 491 "parser.y"
                  {
			errorCount++;
			fprintf(errorout, "Error at line %d: Array size undefined\n\n", lineCount);
			fprintf(logout, "Error at line %d: Array size undefined\n\n", lineCount);

			(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+"[]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID LTHIRD RTHIRD\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			
		  }
#line 1936 "y.tab.c"
    break;

  case 31: /* declaration_list: declaration_list COMMA ID LTHIRD RTHIRD  */
#line 501 "parser.y"
                  {
			errorCount++;
			fprintf(errorout, "Error at line %d: Array size undefined\n\n", lineCount);
			fprintf(logout, "Error at line %d: Array size undefined\n\n", lineCount);

			(yyval.symbol) = new SymbolInfo((yyvsp[-4].symbol)->getName()+","+(yyvsp[-2].symbol)->getName()+"[]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : declaration_list COMMA ID LTHIRD RTHIRD\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		  }
#line 1949 "y.tab.c"
    break;

  case 32: /* declaration_list: ID LTHIRD CONST_FLOAT RTHIRD  */
#line 510 "parser.y"
                  {
			errorCount++;
			fprintf(errorout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);
			fprintf(logout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);

			(yyval.symbol) = new SymbolInfo((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID LTHIRD CONST_FLOAT RTHIRD\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			
		  }
#line 1963 "y.tab.c"
    break;

  case 33: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_FLOAT RTHIRD  */
#line 520 "parser.y"
                  {
			errorCount++;
			fprintf(errorout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);
			fprintf(logout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);

			(yyval.symbol) = new SymbolInfo((yyvsp[-5].symbol)->getName()+","+(yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list COMMA ID LTHIRD CONST_FLOAT RTHIRD\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		  }
#line 1976 "y.tab.c"
    break;

  case 34: /* declaration_list: declaration_list error  */
#line 528 "parser.y"
                                           {}
#line 1982 "y.tab.c"
    break;

  case 35: /* statements: statement  */
#line 532 "parser.y"
                {
			(yyval.symbol)=(yyvsp[0].symbol);
			fprintf(logout, "Line %d: statements : statement\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		}
#line 1991 "y.tab.c"
    break;

  case 36: /* statements: statements statement  */
#line 537 "parser.y"
            {
			(yyval.symbol) = new SymbolInfo((yyvsp[-1].symbol)->getName()+"\n"+(yyvsp[0].symbol)->getName(), "statements");
			fprintf(logout, "Line %d: statements : statements statement\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
	    }
#line 2002 "y.tab.c"
    break;

  case 37: /* statements: statements error  */
#line 543 "parser.y"
                              {}
#line 2008 "y.tab.c"
    break;

  case 38: /* statement: var_declaration  */
#line 547 "parser.y"
          {
		(yyval.symbol)=(yyvsp[0].symbol);
		fprintf(logout, "Line %d: statement : var_declaration\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
	  }
#line 2017 "y.tab.c"
    break;

  case 39: /* statement: expression_statement  */
#line 552 "parser.y"
          {
		(yyval.symbol)=(yyvsp[0].symbol);
		fprintf(logout, "Line %d: statement : expression_statement\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
	  }
#line 2026 "y.tab.c"
    break;

  case 40: /* statement: compound_statement  */
#line 557 "parser.y"
          {
		(yyval.symbol)=(yyvsp[0].symbol);
		fprintf(logout, "Line %d: statement : compound_statement\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
	  }
#line 2035 "y.tab.c"
    break;

  case 41: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 562 "parser.y"
          {
		(yyval.symbol) = new SymbolInfo("for("+(yyvsp[-4].symbol)->getName()+(yyvsp[-3].symbol)->getName()+(yyvsp[-2].symbol)->getName()+")"+(yyvsp[0].symbol)->getName(), "statement");
		fprintf(logout, "Line %d: statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $3;
		// deleete $4;
		// deleete $5;
		// deleete $7;
	  }
#line 2048 "y.tab.c"
    break;

  case 42: /* statement: IF LPAREN expression RPAREN statement  */
#line 571 "parser.y"
          {
		(yyval.symbol) = new SymbolInfo("if("+(yyvsp[-2].symbol)->getName()+")"+(yyvsp[0].symbol)->getName(), "statement");
		fprintf(logout, "Line %d: statement : IF LPAREN expression RPAREN statement\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $3;
		// deleete $5;
	  }
#line 2059 "y.tab.c"
    break;

  case 43: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 578 "parser.y"
          {
		(yyval.symbol) = new SymbolInfo("if("+(yyvsp[-4].symbol)->getName()+")"+(yyvsp[-2].symbol)->getName()+ "else\n"+(yyvsp[0].symbol)->getName(), "statement");
		fprintf(logout, "Line %d: statement : IF LPAREN expression RPAREN statement ELSE statement\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $3;
		// deleete $5;
		// deleete $7;
	  }
#line 2071 "y.tab.c"
    break;

  case 44: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 587 "parser.y"
          {
		(yyval.symbol) = new SymbolInfo("while("+(yyvsp[-2].symbol)->getName()+")"+(yyvsp[0].symbol)->getName(), "statement");
		fprintf(logout, "Line %d: statement : WHILE LPAREN expression RPAREN statement\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $3;
		// deleete $5;
	  }
#line 2082 "y.tab.c"
    break;

  case 45: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 594 "parser.y"
          {
		SymbolInfo *temp = table.lookUpSymbol((yyvsp[-2].symbol)->getName());
		//handle undeclared variable error
		if(temp==nullptr){
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared variable %s\n\n", lineCount, (yyvsp[-2].symbol)->getName().c_str());
			fprintf(logout, "Error at line %d: Undeclared variable %s\n\n", lineCount, (yyvsp[-2].symbol)->getName().c_str());
		}
		else (yyval.symbol) = new SymbolInfo("printf("+(yyvsp[-2].symbol)->getName()+");", "statement");
		fprintf(logout, "Line %d: statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $3;
		// deleete temp;
	  }
#line 2100 "y.tab.c"
    break;

  case 46: /* statement: RETURN expression SEMICOLON  */
#line 608 "parser.y"
          {
		// check return type in func_defn and decl
		if((yyvsp[-1].symbol)->getType()=="expression") {
			errorCount++;
			fprintf(errorout, "Error at line %d: Assignment expression does not have a return type\n\n", lineCount);
			fprintf(logout, "Error at line %d: Assignment expression does not have a return type\n\n", lineCount);
		}

		else if(returnTypeToMatch=="void");

		else if((yyvsp[-1].symbol)->getType()!=returnTypeToMatch){
			errorCount++;
			fprintf(errorout, "Error at line %d: Return type mismatch\n\n", lineCount);
			fprintf(logout, "Error at line %d: Return type mismatch\n\n", lineCount);
		}
		
		(yyval.symbol) = new SymbolInfo("return "+(yyvsp[-1].symbol)->getName()+";", "statement");
		fprintf(logout, "Line %d: statement : RETURN expression SEMICOLON\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $2;
	  }
#line 2125 "y.tab.c"
    break;

  case 47: /* expression_statement: SEMICOLON  */
#line 631 "parser.y"
                        {
				(yyval.symbol) = new SymbolInfo(";", "expression_statement");
				fprintf(logout, "Line %d: expression_statement : SEMICOLON\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			}
#line 2134 "y.tab.c"
    break;

  case 48: /* expression_statement: expression SEMICOLON  */
#line 636 "parser.y"
                        {
				(yyval.symbol) = new SymbolInfo((yyvsp[-1].symbol)->getName()+";", "expression_statement");
				fprintf(logout, "Line %d: expression_statement : expression SEMICOLON\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			}
#line 2143 "y.tab.c"
    break;

  case 49: /* variable: ID  */
#line 643 "parser.y"
         {
		SymbolInfo *temp = table.lookUpSymbol((yyvsp[0].symbol)->getName());
		//handle undeclared variable error
		if(temp==nullptr){
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared variable %s\n\n", lineCount, (yyvsp[0].symbol)->getName().c_str());
			fprintf(logout, "Error at line %d: Undeclared variable %s\n\n", lineCount, (yyvsp[0].symbol)->getName().c_str());
			(yyval.symbol) = new SymbolInfo((yyvsp[0].symbol)->getName(),"variable");
		}
		else (yyval.symbol) = new SymbolInfo(temp->getName(), temp->getType());
		// // cout<<lineCount<<$$->getType()<<endl;;
		fprintf(logout, "Line %d: variable : ID\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $1;
	 }
#line 2162 "y.tab.c"
    break;

  case 50: /* variable: ID LTHIRD expression RTHIRD  */
#line 658 "parser.y"
         {
		SymbolInfo *temp = table.lookUpSymbol((yyvsp[-3].symbol)->getName());
		if(temp==nullptr){
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared variable %s\n\n", lineCount, (yyvsp[-3].symbol)->getName().c_str());
			fprintf(logout, "Error at line %d: Undeclared variable %s\n\n", lineCount, (yyvsp[-3].symbol)->getName().c_str());
			(yyval.symbol) = new SymbolInfo((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]","variable");
		}
		else {
			string varType = temp->getType();
			if ((varType.find("[") != string::npos) || (varType.find("]") != string::npos)) { // is an array
				// handle [float] error
				if ((yyvsp[-1].symbol)->getType()!="int"){
					errorCount++;
					fprintf(errorout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);
					fprintf(logout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);
				}
				(yyval.symbol) = new SymbolInfo((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]", getArrayName(varType));
			} 
			else { 
				errorCount++;
				fprintf(errorout, "Error at line %d: %s not an array\n\n", lineCount, (yyvsp[-3].symbol)->getName().c_str());
				fprintf(logout, "Error at line %d: %s not an array\n\n", lineCount, (yyvsp[-3].symbol)->getName().c_str());
				(yyval.symbol) = new SymbolInfo((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]","variable");
			}
		}
		fprintf(logout, "Line %d: variable : ID LTHIRD expression RTHIRD\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $1;
		// deleete $3;
	 }
#line 2197 "y.tab.c"
    break;

  case 51: /* variable: ID LTHIRD RTHIRD  */
#line 689 "parser.y"
         {
		SymbolInfo *temp = table.lookUpSymbol((yyvsp[-2].symbol)->getName());
		if(temp==nullptr){
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared variable %s\n\n", lineCount, (yyvsp[-2].symbol)->getName().c_str());
			fprintf(logout, "Error at line %d: Undeclared variable %s\n\n", lineCount, (yyvsp[-2].symbol)->getName().c_str());
			(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+"[]","variable");
		}
		else {
			string varType = temp->getType();
			if ((varType.find("[") != string::npos) || (varType.find("]") != string::npos)) { // is an array
				// handle [] error
				errorCount++;
				fprintf(errorout, "Error at line %d: Array size undefined\n\n", lineCount);
				fprintf(logout, "Error at line %d: Array size undefined\n\n", lineCount);
				(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+"[]", getArrayName(varType));
			} 
			else { 
				errorCount++;
				fprintf(errorout, "Error at line %d: %s not an array\n\n", lineCount, (yyvsp[-2].symbol)->getName().c_str());
				fprintf(logout, "Error at line %d: %s not an array\n\n", lineCount, (yyvsp[-2].symbol)->getName().c_str());
				(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+"[]","variable");
			}
		}
		fprintf(logout, "Line %d: variable : ID LTHIRD expression RTHIRD\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $1;
		// deleete $3;
	 }
#line 2230 "y.tab.c"
    break;

  case 52: /* expression: logic_expression  */
#line 720 "parser.y"
                {
			(yyval.symbol)=(yyvsp[0].symbol);
			fprintf(logout, "Line %d: expression : logic_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		}
#line 2239 "y.tab.c"
    break;

  case 53: /* expression: variable ASSIGNOP logic_expression  */
#line 725 "parser.y"
                {
			// bunch of type mismatch handling (but int in float is allowed (added))
			// cout<<$1->getType()<<" "<<$3->getType()<<endl;
			if ((yyvsp[-2].symbol)->getType()=="void" || (yyvsp[0].symbol)->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			else if ((yyvsp[-2].symbol)->getType()!=(yyvsp[0].symbol)->getType()){
				string varType= (yyvsp[-2].symbol)->getType();
				string exprType= (yyvsp[0].symbol)->getType();
				if ((varType.find("[") != string::npos) || (exprType.find("[") != string::npos)) { // either an array
					errorCount++;
					fprintf(errorout, "Error at line %d: Type mismatch, %s is an array\n\n", lineCount, (yyvsp[-2].symbol)->getName().c_str());
					fprintf(logout, "Error at line %d: Type mismatch, %s is an array\n\n", lineCount, (yyvsp[-2].symbol)->getName().c_str());
				}
				else if (varType=="float" && exprType=="int") ;
				else if (varType=="variable" || exprType=="factor") ;
				else {
					errorCount++;
					// cout<<varType<<" "<<exprType<<endl;
					fprintf(errorout, "Error at line %d: Type Mismatch\n\n", lineCount);
					fprintf(logout, "Error at line %d: Type Mismatch\n\n", lineCount);
				}
			}
			(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+"="+(yyvsp[0].symbol)->getName(), "expression");
			fprintf(logout, "Line %d: expression : variable ASSIGNOP logic_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $3;
	   	}
#line 2274 "y.tab.c"
    break;

  case 54: /* logic_expression: rel_expression  */
#line 758 "parser.y"
                {
			(yyval.symbol)=(yyvsp[0].symbol);
			fprintf(logout, "Line %d: logic_expression : rel_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		}
#line 2283 "y.tab.c"
    break;

  case 55: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 763 "parser.y"
                {
			if ((yyvsp[-2].symbol)->getType()=="void" || (yyvsp[0].symbol)->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			(yyval.symbol) = new SymbolInfo("", "int");
			(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName());
			fprintf(logout, "Line %d: logic_expression : rel_expression LOGICOP rel_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $3;
		}
#line 2301 "y.tab.c"
    break;

  case 56: /* rel_expression: simple_expression  */
#line 779 "parser.y"
                {
			(yyval.symbol)=(yyvsp[0].symbol);
			fprintf(logout, "Line %d: rel_expression : simple_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		}
#line 2310 "y.tab.c"
    break;

  case 57: /* rel_expression: simple_expression RELOP simple_expression  */
#line 784 "parser.y"
                {
			if ((yyvsp[-2].symbol)->getType()=="void" || (yyvsp[0].symbol)->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			(yyval.symbol) = new SymbolInfo("", "int");
			(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName());
			fprintf(logout, "Line %d: rel_expression : simple_expression RELOP simple_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $3;
		}
#line 2328 "y.tab.c"
    break;

  case 58: /* simple_expression: term  */
#line 800 "parser.y"
                {
			(yyval.symbol)=(yyvsp[0].symbol);
			fprintf(logout, "Line %d: simple_expression : term\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		}
#line 2337 "y.tab.c"
    break;

  case 59: /* simple_expression: simple_expression ADDOP term  */
#line 805 "parser.y"
                {
			//handle int addition and float addition
			string exprType;
			// // cout<<lineCount<<$1->getType()<<endl;
			// // cout<<lineCount<<$3->getType()<<endl;
			if(((yyvsp[-2].symbol)->getType()=="int") && ((yyvsp[0].symbol)->getType()=="int")) exprType= "int"; 
			else exprType= "float";
			if ((yyvsp[-2].symbol)->getType()=="void" || (yyvsp[0].symbol)->getType()=="void"){
				// errorCount++;
				// fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				// fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
				exprType= "void";
			}

			(yyval.symbol) = new SymbolInfo("", exprType);
			(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName());
			// // cout<<lineCount<<$$->getType()<<endl;
			fprintf(logout, "Line %d: simple_expression : simple_expression ADDOP term\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $3;
		}
#line 2364 "y.tab.c"
    break;

  case 60: /* simple_expression: simple_expression error  */
#line 826 "parser.y"
                                            {}
#line 2370 "y.tab.c"
    break;

  case 61: /* term: unary_expression  */
#line 830 "parser.y"
         {
		(yyval.symbol)=(yyvsp[0].symbol);
		fprintf(logout, "Line %d: term : unary_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
	 }
#line 2379 "y.tab.c"
    break;

  case 62: /* term: term MULOP unary_expression  */
#line 835 "parser.y"
         {
		//handle errors
		if ((yyvsp[-2].symbol)->getType()=="void" || (yyvsp[0].symbol)->getType()=="void"){
			// errorCount++;
			// fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
			// fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"void");
		}
		else if((yyvsp[-1].symbol)->getName()=="%"){ // modulus cases
			if(((yyvsp[-2].symbol)->getType()=="int") && ((yyvsp[0].symbol)->getType()=="int")){
				if((yyvsp[0].symbol)->getName()=="0"){
					errorCount++;
					fprintf(errorout, "Error at line %d: Modulus by Zero\n\n", lineCount);
					fprintf(logout, "Error at line %d: Modulus by Zero\n\n", lineCount);
				}
			}
			else { // non int operand
				errorCount++;
				fprintf(errorout, "Error at line %d: Non-Integer operand on modulus operator\n\n", lineCount);
				fprintf(logout, "Error at line %d: Non-Integer operand on modulus operator\n\n", lineCount);
			}
			(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"int");
		}
		else {
			if(((yyvsp[-2].symbol)->getType()=="int")&&((yyvsp[0].symbol)->getType()=="int"))
				(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"int");
			else (yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"float");
		}
		fprintf(logout, "Line %d: term : term MULOP unary_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $1;
		// deleete $2;
		// deleete $3;

	 }
#line 2418 "y.tab.c"
    break;

  case 63: /* unary_expression: ADDOP unary_expression  */
#line 872 "parser.y"
                 {
			if ((yyvsp[0].symbol)->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			(yyval.symbol) = new SymbolInfo((yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
			fprintf(logout, "Line %d: unary_expression : ADDOP unary_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $2;
		 }
#line 2433 "y.tab.c"
    break;

  case 64: /* unary_expression: NOT unary_expression  */
#line 883 "parser.y"
                 {
			if ((yyvsp[0].symbol)->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			(yyval.symbol) = new SymbolInfo("!"+(yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
			fprintf(logout, "Line %d: unary_expression : NOT unary_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			// deleete $2;
		 }
#line 2448 "y.tab.c"
    break;

  case 65: /* unary_expression: factor  */
#line 894 "parser.y"
                 {
			(yyval.symbol)=(yyvsp[0].symbol);
			fprintf(logout, "Line %d: unary_expression : factor\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		 }
#line 2457 "y.tab.c"
    break;

  case 66: /* factor: variable  */
#line 901 "parser.y"
        {
		(yyval.symbol)=(yyvsp[0].symbol);
		fprintf(logout, "Line %d: factor : variable\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
	}
#line 2466 "y.tab.c"
    break;

  case 67: /* factor: ID LPAREN argument_list RPAREN  */
#line 906 "parser.y"
        {
		string returnType= "factor";
		string funcName = (yyvsp[-3].symbol)->getName();
		SymbolInfo* temp = table.lookUpSymbol(funcName);
		if (temp==nullptr)
		{
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared function %s\n\n", lineCount, funcName.c_str());
			fprintf(logout, "Error at line %d: Undeclared function %s\n\n", lineCount, funcName.c_str());
		}
		else {
			if(temp->getType()=="FUNCTION"){
				FunctionInfo* ftemp= (FunctionInfo*) temp;
				returnType= ftemp->getReturnType();
				splitParameterTypeList((yyvsp[-1].symbol)->getType(),',');
				// if(ftemp->getReturnType()=="void"){
				// 	errorCount++;
				// 	fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				// 	fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
				// }
				// else 
				if(parameterTypeList.size()!=ftemp->getParameterTypeList().size()){
					errorCount++;
					fprintf(errorout, "Error at line %d: Total number of arguments mismatch in function %s\n\n", lineCount, funcName.c_str());
					fprintf(logout, "Error at line %d: Total number of arguments mismatch in function %s\n\n", lineCount, funcName.c_str());
				}
				else {
					for(int i=0; i<ftemp->getParameterTypeList().size(); i++){
						if (parameterTypeList[i].find("[") != string::npos){ // array check
							errorCount++;
							fprintf(errorout, "Error at line %d: Type mismatch, argument is an array\n\n", lineCount);
							fprintf(logout, "Error at line %d: Type mismatch, argument is an array\n\n", lineCount);
							break;
						}
						if (ftemp->getParameterTypeList()[i] != parameterTypeList[i]){
							errorCount++;
							fprintf(errorout, "Error at line %d: %dth argument mismatch in function %s\n\n", lineCount, i+1, funcName.c_str());
							fprintf(logout, "Error at line %d: %dth argument mismatch in function %s\n\n", lineCount, i+1, funcName.c_str());
							break;
						}
					}

				}

				clearParameterTypeList();
			}
			else {
				errorCount++;
				fprintf(errorout, "Error at line %d: %s not a function\n\n", lineCount, funcName.c_str());
				fprintf(logout, "Error at line %d: %s not function\n\n", lineCount, funcName.c_str());	
			}
		}
		(yyval.symbol) = new SymbolInfo((yyvsp[-3].symbol)->getName()+"("+(yyvsp[-1].symbol)->getName()+")", returnType);
		fprintf(logout, "Line %d: factor : ID LPAREN argument_list RPAREN\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $1;
		// deleete $3;
	}
#line 2528 "y.tab.c"
    break;

  case 68: /* factor: LPAREN expression RPAREN  */
#line 964 "parser.y"
        {
		(yyval.symbol) = new SymbolInfo("("+(yyvsp[-1].symbol)->getName()+")", (yyvsp[-1].symbol)->getType());
		fprintf(logout, "Line %d: factor : LPAREN expression RPAREN\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $2;
	}
#line 2538 "y.tab.c"
    break;

  case 69: /* factor: CONST_INT  */
#line 970 "parser.y"
        {
		(yyval.symbol) = (yyvsp[0].symbol);
		fprintf(logout, "Line %d: factor : CONST_INT\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
	}
#line 2547 "y.tab.c"
    break;

  case 70: /* factor: CONST_FLOAT  */
#line 975 "parser.y"
        {
		(yyval.symbol) = (yyvsp[0].symbol);
		fprintf(logout, "Line %d: factor : CONST_FLOAT\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
	}
#line 2556 "y.tab.c"
    break;

  case 71: /* factor: variable INCOP  */
#line 980 "parser.y"
        {
		(yyval.symbol) = new SymbolInfo((yyvsp[-1].symbol)->getName()+"++",(yyvsp[-1].symbol)->getType());
		fprintf(logout, "Line %d: factor : variable INCOP\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $1;
	}
#line 2566 "y.tab.c"
    break;

  case 72: /* factor: variable DECOP  */
#line 986 "parser.y"
        {
		(yyval.symbol) = new SymbolInfo((yyvsp[-1].symbol)->getName()+"--",(yyvsp[-1].symbol)->getType());
		fprintf(logout, "Line %d: factor : variable DECOP\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
		// deleete $1;
	}
#line 2576 "y.tab.c"
    break;

  case 73: /* argument_list: arguments  */
#line 994 "parser.y"
                        {
				(yyval.symbol)=(yyvsp[0].symbol);
				fprintf(logout, "Line %d: argument_list : arguments\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			}
#line 2585 "y.tab.c"
    break;

  case 74: /* argument_list: %empty  */
#line 999 "parser.y"
                        {
				(yyval.symbol)=new SymbolInfo("", "void");
				fprintf(logout, "Line %d: argument_list : \n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
			}
#line 2594 "y.tab.c"
    break;

  case 75: /* arguments: arguments COMMA logic_expression  */
#line 1006 "parser.y"
                        {
				(yyval.symbol) = new SymbolInfo((yyvsp[-2].symbol)->getName()+","+(yyvsp[0].symbol)->getName(),(yyvsp[-2].symbol)->getType()+","+(yyvsp[0].symbol)->getType());
				fprintf(logout, "Line %d: arguments : arguments COMMA logic_expression\n\n%s\n\n", lineCount, (yyval.symbol)->getName().c_str());
				// deleete $1;
				// deleete $3;
			}
#line 2605 "y.tab.c"
    break;

  case 76: /* arguments: logic_expression  */
#line 1013 "parser.y"
                        {
				(yyval.symbol)=(yyvsp[0].symbol);
				fprintf(logout, "Line %d: arguments : logic_expression\n\n%s\n\n", lineCount, (yyvsp[0].symbol)->getName().c_str());
			}
#line 2614 "y.tab.c"
    break;


#line 2618 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1019 "parser.y"

int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	logout= fopen(argv[2],"w");
	fclose(logout);
	errorout= fopen(argv[3],"w");
	fclose(errorout);
	
	logout= fopen(argv[2],"a");
	errorout= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	
	fprintf(logout, "\n%s\n",table.printAllScope().c_str());
	fprintf(logout, "Total lines: %d\n", lineCount);
	fprintf(logout, "Total errors: %d\n", errorCount);

	fclose(logout);
	fclose(errorout);
	
	return 0;
}
