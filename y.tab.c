/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "projet.y"

#include "hpdf.h"
#include "hpdf_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#define T 1024
	
HPDF_Doc mon_document;
HPDF_Page page[20];
HPDF_Image image;
HPDF_Rect misenpage;
/*Variable pour avoir la position : par defaut (0,0)*/	
HPDF_Point Position;
HPDF_Point CurrentPosition;
HPDF_TextAlignment   align;
HPDF_UINT *len;

int HPDF_i = 0;
int decl = 45;
int Style = 0;

/* Les tilles pas defaut de chaque type de token */
int HPDFTailleTxt = 11, cmp_txt=0;
int HPDFTailleSec = 17, cmp_sec=0;
int HPDFTailleSsec = 13, cmp_ssec=0;
int HPDFTailleTitrEnv = 13, cmp_titenv=0;
int HPDFTailleTxtEnv = 11, cmp_txtenv=0;
int HPDF_mypage = 0;	
int HPDF_EnvTitBol = 0;

int tabmat = 0;
int HPDF_IndicS = 0;
int HPDF_IndicSs = 0;
int HPDF_titres[T];
int HPDF_Ntitre = 0;
int HPDF_NumSs = 0;
char HPDF_Npage[T][T];
int HPDF_CmptePg = 0;
char HPDF_Temp[T];
char HPDF_Temp1[T];
char HPDF_StockS[T][T];
char HPDF_StockSs[T][T];
char HPDF_ConstrEnv[T];
char HPDF_ConstTitrEnt[T];
	 

	
typedef struct HPDFSTRUCT  {
char sec[2]; 	char ssec[2]; 	char numerote[2];
char def[2];	char lem[2];	char note[2];
char page[2];
} HPDFStruct ;

	
HPDFStruct HPDFMyStruct;

	
/* Utiliser une fonction de creation de page pour pouvoir : 
*	- Changer de font une seule fois et pas a chaque fois 
*	- Chnager de direction de la page HPDF_PAGE_PORTRAIT (Normal) ou HPDF_PAGE_LANDSCAPE(Mode paysage)
*	- Chnager de taille de police 
*	- Chnager l'espacement entre caractère une seule fois (a la creationde la page) => SetTextLeading
*/
void HPDF_NouvellePage() {
/*Fermer le texte de la page précédente */
HPDF_Page_EndText (page[HPDF_mypage]);
/*Incrémenter le nombre de page*/
HPDF_mypage++;
/*Ajouter une page au document*/
page[HPDF_mypage] = HPDF_AddPage (mon_document);
if (!page[HPDF_mypage]) {
	printf("Error handler !\n");
}
/*Définir la forme de la page*/
HPDF_Page_SetSize (page[HPDF_mypage], HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
/*Définir l'espacement*/
HPDF_Page_SetTextLeading (page[HPDF_mypage], 22);
/*Définir le style de la page*/
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , 11);
/*Récuperer la position*/
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
HPDF_Page_BeginText (page[HPDF_mypage]);
HPDFMyStruct.page[0]++;
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y + 35, misenpage.right, misenpage.top,HPDFMyStruct.page, HPDF_TALIGN_CENTER, NULL);
HPDF_Page_EndText (page[HPDF_mypage]);
HPDF_Page_BeginText (page[HPDF_mypage]);
}


/*	- La fonction suivante est disponible sur le site officiel de la bibliotheque http://libharu.sourceforge.net 
*	- Création de l'objet image
*	- Chargement de l'image en (png ou jpeg) => Load
*	- Dessiner l'image dans le PDF => Draw
*/

draw_image (HPDF_Doc     pdf,const char  *filename,float x, float y, const char  *text)
{
#ifdef __WIN32__
const char* FILE_SEPARATOR = "\\";
#else
const char* FILE_SEPARATOR = "/";
#endif
char filename1[255];

HPDF_Page page = HPDF_GetCurrentPage (pdf);
HPDF_Image image;

strcpy(filename1, "projet");
strcat(filename1, FILE_SEPARATOR);
strcat(filename1, filename);

image = HPDF_LoadPngImageFromFile (pdf, filename1);

/* Draw image to the canvas. */
HPDF_Page_DrawImage (page, image, x, y, HPDF_Image_GetWidth (image),HPDF_Image_GetHeight (image));

/* Print the text. */
HPDF_Page_BeginText (page);
HPDF_Page_SetTextLeading (page, 16);
HPDF_Page_MoveTextPos (page, x, y);
HPDF_Page_ShowTextNextLine (page, filename);
HPDF_Page_ShowTextNextLine (page, text);
HPDF_Page_EndText (page);
}



/* Line 268 of yacc.c  */
#line 200 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AUTRES = 258,
     SEC = 259,
     SSEC = 260,
     ENV = 261,
     ENDENV = 262,
     MATAILLE = 263,
     TABMAT = 264,
     FINLIGNE = 265,
     BLANCS = 266,
     COMMENTAIRE = 267,
     ECHAPPER = 268,
     BOOLEAN = 269,
     STRONG = 270,
     ENTIER = 271,
     IMAGE = 272
   };
#endif
/* Tokens.  */
#define AUTRES 258
#define SEC 259
#define SSEC 260
#define ENV 261
#define ENDENV 262
#define MATAILLE 263
#define TABMAT 264
#define FINLIGNE 265
#define BLANCS 266
#define COMMENTAIRE 267
#define ECHAPPER 268
#define BOOLEAN 269
#define STRONG 270
#define ENTIER 271
#define IMAGE 272




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 129 "projet.y"

char	        *CHAINE;



/* Line 293 of yacc.c  */
#line 276 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 288 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  21
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  107

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   272

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      18,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,    19,     2,    20,     2,     2,     2,     2,
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
      15,    16,    17
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    15,    18,    21,
      24,    27,    30,    33,    34,    38,    39,    43,    44,    48,
      51,    52,    54,    58,    59,    60,    68,    70,    73,    76,
      79,    81,    83,    85,    87,    90,    92,    93,    97,    98,
      99,   103,   107,   109,   110,   114,   118,   120,   122,   124,
     125,   129,   131,   132,   133,   137,   138,   142,   146,   148,
     150,   152,   154,   157,   158,   162,   165,   168,   170,   171
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      22,     0,    -1,    23,    -1,    -1,    10,    23,    -1,    12,
      23,    -1,    24,    22,    -1,    29,    24,    -1,    30,    24,
      -1,    58,    24,    -1,    28,    24,    -1,    12,    24,    -1,
      11,    24,    -1,    -1,    33,    25,    24,    -1,    -1,    38,
      26,    24,    -1,    -1,    41,    27,    24,    -1,    48,    24,
      -1,    -1,    18,    -1,     9,    19,    33,    -1,    -1,    -1,
       8,    31,    19,    16,    32,    20,    10,    -1,    34,    -1,
      45,    34,    -1,    11,    34,    -1,    35,    36,    -1,    10,
      -1,    20,    -1,     3,    -1,    34,    -1,    45,    34,    -1,
      12,    -1,    -1,    11,    37,    34,    -1,    -1,    -1,     4,
      39,    40,    -1,    19,    33,    44,    -1,    44,    -1,    -1,
       5,    42,    43,    -1,    19,    33,    44,    -1,    44,    -1,
      10,    -1,    12,    -1,    -1,    13,    46,    47,    -1,    45,
      -1,    -1,    -1,    50,    49,    54,    -1,    -1,     6,    51,
      52,    -1,    19,    33,    53,    -1,    10,    -1,    12,    -1,
      10,    -1,    12,    -1,    55,     7,    -1,    -1,    33,    56,
      57,    -1,    12,    55,    -1,    10,    55,    -1,    55,    -1,
      -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   154,   154,   155,   158,   159,   160,   163,   164,   165,
     166,   167,   168,   169,   169,   189,   189,   209,   209,   232,
     233,   236,   243,   250,   264,   250,   284,   285,   286,   289,
     290,   291,   294,   297,   298,   299,   300,   300,   301,   304,
     304,   312,   313,   316,   316,   333,   334,   337,   338,   342,
     342,   345,   346,   351,   351,   386,   386,   406,   407,   408,
     411,   412,   414,   430,   430,   452,   455,   456,   457,   460
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AUTRES", "SEC", "SSEC", "ENV", "ENDENV",
  "MATAILLE", "TABMAT", "FINLIGNE", "BLANCS", "COMMENTAIRE", "ECHAPPER",
  "BOOLEAN", "STRONG", "ENTIER", "IMAGE", "'\\n'", "'{'", "'}'", "$accept",
  "Entree", "prog", "corp", "$@1", "$@2", "$@3", "nouvelleLigne", "tabmat",
  "taille", "$@4", "$@5", "ligne", "lettre", "debLettre", "finLettre",
  "$@6", "section", "$@7", "sectionend", "ssection", "$@8", "ssectionend",
  "reste", "echapper", "$@9", "echapperend", "envir", "$@10", "debutenv",
  "$@11", "findenv", "reste2", "txtEnv", "corpenv", "$@12", "finenv",
  "image", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    10,   123,
     125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    21,    22,    22,    23,    23,    23,    24,    24,    24,
      24,    24,    24,    25,    24,    26,    24,    27,    24,    24,
      24,    28,    29,    31,    32,    30,    33,    33,    33,    34,
      34,    34,    35,    36,    36,    36,    37,    36,    36,    39,
      38,    40,    40,    42,    41,    43,    43,    44,    44,    46,
      45,    47,    47,    49,    48,    51,    50,    52,    52,    52,
      53,    53,    54,    56,    55,    55,    57,    57,    57,    58
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     0,     3,     0,     3,     0,     3,     2,
       0,     1,     3,     0,     0,     7,     1,     2,     2,     2,
       1,     1,     1,     1,     2,     1,     0,     3,     0,     0,
       3,     3,     1,     0,     3,     3,     1,     1,     1,     0,
       3,     1,     0,     0,     3,     0,     3,     3,     1,     1,
       1,     1,     2,     0,     3,     2,     2,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    32,    39,    43,    55,    23,     0,    20,    20,    20,
      49,    69,    21,    31,     0,     2,     3,    20,    20,    20,
      13,    26,    38,    15,    17,     0,    20,    53,    20,     0,
       0,     0,     0,     0,     4,    30,    20,    12,    26,     5,
      11,    52,     1,     6,    10,     7,     8,    20,    36,    35,
      33,    29,     0,    20,    20,    27,    19,     0,     9,    47,
      48,     0,    40,    42,     0,    44,    46,    58,    59,     0,
      56,     0,     0,    22,    11,    51,    50,    14,     0,    34,
      16,    18,     0,    63,    54,     0,     0,     0,     0,    24,
      28,    37,    65,    68,    62,    41,    45,    60,    61,    57,
       0,    30,    67,    64,     0,    66,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    43,    15,    16,    47,    53,    54,    17,    18,    19,
      32,   100,    20,    21,    22,    51,    78,    23,    29,    62,
      24,    30,    65,    63,    25,    41,    76,    26,    57,    27,
      31,    70,    99,    84,    85,    93,   103,    28
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -79
static const yytype_int16 yypact[] =
{
      85,   -79,   -79,   -79,   -79,   -79,   -14,   138,   103,    85,
     -79,   -79,   -79,   -79,    12,   -79,    85,   103,   103,   103,
     -79,   -79,    23,   -79,   -79,    21,   103,   -79,   103,    -3,
      35,    41,    -6,   125,   -79,   -79,   103,   -79,   -79,   -79,
      67,     5,   -79,   -79,   -79,   -79,   -79,   103,   -79,   -79,
     -79,   -79,    21,   103,   103,   -79,   -79,   114,   -79,   -79,
     -79,   125,   -79,   -79,   125,   -79,   -79,   -79,   -79,   125,
     -79,    11,    21,   -79,   -79,   -79,   -79,   -79,    21,   -79,
     -79,   -79,   114,   -79,   -79,    32,    -4,    -4,    30,   -79,
     -79,   -79,   -79,   119,   -79,   -79,   -79,   -79,   -79,   -79,
      37,    42,   -79,   -79,    53,   -79,   -79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -79,    52,    39,     2,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -32,    -8,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -28,   -19,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -78,   -79,   -79,   -79
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const yytype_int8 yytable[] =
{
      38,    73,    66,    52,    92,    33,    59,    59,    60,    60,
      37,    40,    42,    71,    50,   102,    61,    55,    10,    44,
      45,    46,    75,   105,     1,    83,     1,    89,    56,    86,
      58,    35,    87,    35,    48,    49,    10,    88,    74,    94,
      97,    13,    98,    13,    79,    59,    34,    60,    39,    77,
      83,    67,    14,    68,    64,    80,    81,   104,    95,    96,
      69,    83,    13,   106,    90,     0,     0,    -3,     0,    83,
      91,     2,     3,     4,     0,     5,     6,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,    13,     1,     2,
       3,     4,     0,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,    12,     0,    13,     1,     2,     3,     4,
       0,     5,     6,    35,     8,    36,    10,     1,     0,     0,
      11,    12,     1,    13,    35,    72,    82,    10,     1,   101,
      72,    82,    10,     0,    13,    35,    72,     0,    10,    13,
       0,     0,     2,     3,     4,    13,     5,     6,     0,     0,
       0,     0,     0,     0,     0,     0,    12,     0,    13
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-79))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       8,    33,    30,    22,    82,    19,    10,    10,    12,    12,
       8,     9,     0,    19,    22,    93,    19,    25,    13,    17,
      18,    19,    41,   101,     3,    57,     3,    16,    26,    61,
      28,    10,    64,    10,    11,    12,    13,    69,    36,     7,
      10,    20,    12,    20,    52,    10,     7,    12,     9,    47,
      82,    10,     0,    12,    19,    53,    54,    20,    86,    87,
      19,    93,    20,    10,    72,    -1,    -1,     0,    -1,   101,
      78,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    -1,    20,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    18,    -1,    20,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    13,     3,    -1,    -1,
      17,    18,     3,    20,    10,    11,    12,    13,     3,    10,
      11,    12,    13,    -1,    20,    10,    11,    -1,    13,    20,
      -1,    -1,     4,     5,     6,    20,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      13,    17,    18,    20,    22,    23,    24,    28,    29,    30,
      33,    34,    35,    38,    41,    45,    48,    50,    58,    39,
      42,    51,    31,    19,    23,    10,    12,    24,    34,    23,
      24,    46,     0,    22,    24,    24,    24,    25,    11,    12,
      34,    36,    45,    26,    27,    34,    24,    49,    24,    10,
      12,    19,    40,    44,    19,    43,    44,    10,    12,    19,
      52,    19,    11,    33,    24,    45,    47,    24,    37,    34,
      24,    24,    12,    33,    54,    55,    33,    33,    33,    16,
      34,    34,    55,    56,     7,    44,    44,    10,    12,    53,
      32,    10,    55,    57,    20,    55,    10
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 13:

/* Line 1806 of yacc.c  */
#line 169 "projet.y"
    {	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100 ){	
HPDF_NouvellePage();
}

											
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleTxt);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
											
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top, HPDF_Temp, HPDF_TALIGN_JUSTIFY, NULL);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
}else {
	if(HPDF_Temp[0] != 0){
	HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 18, misenpage.right, misenpage.top,
	HPDF_Temp, HPDF_TALIGN_JUSTIFY, NULL);
}}memset (HPDF_Temp, 0, T);HPDF_i = 0;}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 189 "projet.y"
    { 	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
	HPDF_NouvellePage();
}

												
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Bold", "WinAnsiEncoding") , HPDFTailleSec);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);	
if (Position.y == 0) {
	HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,HPDF_Temp, HPDF_TALIGN_LEFT, NULL);
}else {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 28, misenpage.right, misenpage.top,HPDF_Temp, HPDF_TALIGN_LEFT, NULL);
}
strcpy(HPDF_StockS[HPDF_IndicS], HPDF_Temp);
memset (HPDF_Temp, 0, T);HPDF_IndicS++;HPDF_i = 0;
sprintf(HPDF_Npage[HPDF_CmptePg], "%d", HPDF_mypage);
HPDF_CmptePg++;
}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 209 "projet.y"
    { 
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
HPDF_NouvellePage();
}

												
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Italic", "WinAnsiEncoding") , HPDFTailleSsec);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
												
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,HPDF_Temp, HPDF_TALIGN_LEFT, NULL);
}else {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 30, misenpage.right, misenpage.top,HPDF_Temp, HPDF_TALIGN_LEFT, NULL);
}
strcpy(HPDF_StockSs[HPDF_IndicSs], HPDF_Temp);
memset (HPDF_Temp, 0, T);
HPDF_IndicSs++;
HPDF_i = 0;

sprintf(HPDF_Npage[HPDF_CmptePg], "%d", HPDF_mypage);
HPDF_CmptePg++;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 236 "projet.y"
    {	Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleSsec);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
													
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 12, misenpage.right, misenpage.top," ", HPDF_TALIGN_LEFT, NULL);
}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 243 "projet.y"
    {	  
if(HPDF_Temp=="true") {tabmat = 0; } else { tabmat = 1;}
memset (HPDF_Temp, 0, T);
HPDF_i = 0;
}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 250 "projet.y"
    { 

if(!(strcmp ((yyvsp[(1) - (1)].CHAINE),"\\taillesec"))) {
	cmp_sec = 1; 
} 	else if (!(strcmp ((yyvsp[(1) - (1)].CHAINE),"\\taillessec"))) {
	cmp_ssec = 1;
} 	else if (!(strcmp ((yyvsp[(1) - (1)].CHAINE),"\\tailletxt"))) {
	cmp_txt = 1;
} else if (!(strcmp ((yyvsp[(1) - (1)].CHAINE),"\\tailleenvi"))) {
	cmp_titenv = 1;
} else if (!(strcmp ((yyvsp[(1) - (1)].CHAINE),"\\tailleenvicont"))) {
	cmp_txtenv = 1;

}
}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 264 "projet.y"
    {   int curr= 0; 
if(cmp_sec==1) { 
	sscanf((yyvsp[(1) - (4)].CHAINE),"%d",&curr); 
	HPDFTailleSec = curr; cmp_sec=0;
} 	else if (cmp_ssec==1) {
		sscanf((yyvsp[(1) - (4)].CHAINE),"%d",&curr);
	HPDFTailleSsec = curr; cmp_ssec=0;;
} 		else if (cmp_txt==1) {
sscanf((yyvsp[(1) - (4)].CHAINE),"%d",&curr);
	HPDFTailleTxt = curr; cmp_txt=0;
} else if (cmp_titenv==1) {
sscanf((yyvsp[(1) - (4)].CHAINE),"%d",&curr);
	HPDFTailleTitrEnv = curr; cmp_titenv=0;
} else if (cmp_txtenv==1) {
sscanf((yyvsp[(1) - (4)].CHAINE),"%d",&curr);
	HPDFTailleTxtEnv = curr; cmp_txtenv=0;
} 
 }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 294 "projet.y"
    { /*Récuperer la valuer de la chaine insérer */  HPDF_Temp[HPDF_i] = *(yyvsp[(1) - (1)].CHAINE); HPDF_i++; }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 300 "projet.y"
    {strcat(HPDF_Temp," ");HPDF_i++;}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 304 "projet.y"
    {	
HPDFMyStruct.sec[0]++;						
strcat(HPDF_Temp, HPDFMyStruct.sec);
strcat(HPDF_Temp, ". : ");
HPDF_i = strlen(HPDF_Temp);
}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 316 "projet.y"
    {	
if(HPDFMyStruct.numerote[0] != HPDFMyStruct.sec[0]){
HPDFMyStruct.ssec[0] = '0';
}
HPDFMyStruct.ssec[0]++;
strcat(HPDF_Temp, HPDFMyStruct.sec);
strcat(HPDF_Temp, ". ");
strcat(HPDF_Temp, HPDFMyStruct.ssec);
strcat(HPDF_Temp, ". : ");
HPDF_i = strlen(HPDF_Temp);
HPDFMyStruct.numerote[0] = HPDFMyStruct.sec[0];
HPDF_Ntitre = atof(HPDFMyStruct.sec);
HPDF_NumSs = atof(HPDFMyStruct.ssec);
HPDF_titres[HPDF_Ntitre] = HPDF_NumSs;
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 342 "projet.y"
    {strcat(HPDF_Temp,"%");HPDF_i++;}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 351 "projet.y"
    {	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
HPDF_NouvellePage();
}
								
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleTitrEnv);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);

strcat(HPDF_ConstTitrEnt, HPDF_ConstrEnv);
if(HPDF_EnvTitBol) {
strcat(HPDF_ConstTitrEnt," [");
strcat(HPDF_ConstTitrEnt, HPDF_Temp);
}else {
strcat(HPDF_ConstTitrEnt," :");
strcat(HPDF_ConstTitrEnt, HPDF_Temp);
}
if(HPDF_EnvTitBol) {
strcat(HPDF_ConstTitrEnt,"]***");
}else {
strcat(HPDF_ConstTitrEnt,"***");
}
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,HPDF_ConstTitrEnt, HPDF_TALIGN_LEFT, NULL);
}else {

HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 20, misenpage.right, misenpage.top,HPDF_ConstTitrEnt, HPDF_TALIGN_LEFT, NULL);

}
memset (HPDF_Temp, 0, T);HPDF_i = 0;
memset (HPDF_ConstTitrEnt, 0, T); memset (HPDF_ConstrEnv, 0, T);
}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 386 "projet.y"
    {	

if(!(strcmp ((yyvsp[(1) - (1)].CHAINE),"\\def"))) {
HPDFMyStruct.def[0]++;
strcat(HPDF_ConstrEnv, "*** Definition ");
strcat(HPDF_ConstrEnv, HPDFMyStruct.def);
}else if(!(strcmp ((yyvsp[(1) - (1)].CHAINE),"\\lem"))) {
HPDFMyStruct.lem[0]++;
strcat(HPDF_ConstrEnv, "*** Lemme ");
strcat(HPDF_ConstrEnv, HPDFMyStruct.lem);
}else if(!(strcmp ((yyvsp[(1) - (1)].CHAINE),"\\note"))) {
HPDFMyStruct.note[0]++;
strcat(HPDF_ConstrEnv, "*** Note ");
strcat(HPDF_ConstrEnv, HPDFMyStruct.note);
}	
}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 407 "projet.y"
    {HPDF_EnvTitBol = 0;}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 408 "projet.y"
    {HPDF_EnvTitBol = 0;}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 411 "projet.y"
    {HPDF_EnvTitBol = 1;}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 412 "projet.y"
    {HPDF_EnvTitBol = 1;}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 414 "projet.y"
    {	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
HPDF_NouvellePage();
}
										
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleTitrEnv);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,
"*****Fin*****", HPDF_TALIGN_LEFT, NULL);
}else {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 12, misenpage.right, misenpage.top,"*****Fin*****", HPDF_TALIGN_LEFT, NULL);
}	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 430 "projet.y"
    { 	
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(Position.y > 1 && Position.y < 100){	
HPDF_NouvellePage();
}
/*Insertion de tabulation de debut de ligne*/
strcat(HPDF_Temp1,"        ");
strcat(HPDF_Temp1, HPDF_Temp);
/*Définitiondu style pour le texte de l'environnement*/							
HPDF_Page_SetFontAndSize (page[HPDF_mypage], HPDF_GetFont (mon_document, "Times-Roman", "WinAnsiEncoding") , HPDFTailleTxtEnv);
Position = HPDF_Page_GetCurrentTextPos(page[HPDF_mypage]);
if(HPDF_Temp[0] != '\0'){
if (Position.y == 0) {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, misenpage.bottom, misenpage.right, misenpage.top,
HPDF_Temp1, HPDF_TALIGN_JUSTIFY, NULL);
}else {
HPDF_Page_TextRect (page[HPDF_mypage],  misenpage.left, Position.y - 12, misenpage.right, misenpage.top,HPDF_Temp1, HPDF_TALIGN_JUSTIFY, NULL);
}
memset (HPDF_Temp, 0, T);
memset (HPDF_Temp1, 0, T);
HPDF_i = 0;
}}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 460 "projet.y"
    {
		  
/* Perment de dessiner une image */
draw_image (mon_document, "rouen.png", 400, HPDF_Page_GetHeight (page[HPDF_mypage]) - 350, "Mon univ");
/*Creation de l'objet image */
image = HPDF_LoadPngImageFromFile (mon_document , "rouen.png");
double  iw = HPDF_Image_GetWidth (image);
double  ih = HPDF_Image_GetHeight (image);
double   x = 100;
double   y = HPDF_Page_GetHeight (page[HPDF_mypage]) - 100;
/* Perment de dessiner une image */
HPDF_Page_DrawImage (page[HPDF_mypage], image, x, y,  iw, ih);
}
    break;



/* Line 1806 of yacc.c  */
#line 1969 "y.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 475 "projet.y"

#include "lex.yy.c"



