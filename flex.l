%{
	#include <iostream>
	#include <stdio.h>
	using namespace std;
	#define YY_DECL extern "C" int yylex()

	#include "bison.tab.h"
	int line_num = 1;
%}
%%

"programa" 				{ return PROGRAMA ; }
"principal" 			{ return PRINCIPAL ; }
"modulo"				{ return MODULO ; }
"regresa" 				{ return REGRESA ; }

"sino"					{ return SINO ; }
"si"					{ return SI ; }
"entonces"				{ return ENTONCES ; }

"mientraz"				{ return MIENTRAZ ; }
"haz"					{ return HAZ ; }
"repite"				{ return REPITE ; }
"hasta"					{ return HASTA ; }

">" 					{ return MAYOR_QUE ; }
"<" 					{ return MENOR_QUE ; }
"<>" 					{ return NO_IGUAL_A ; }
"==" 					{ return IGUAL_A ; }
"+" 					{ return O_SUMA ; }
"-" 					{ return O_RESTA ; }
"*" 					{ return O_MULT ; }
"/" 					{ return O_DIVISION ; }
"!" 					{ return O_NOT ; }
"$" 					{ return O_DET ; }
"?" 					{ return O_INV ; }
"&&" 					{ return O_AND ; }
"||" 					{ return O_OR ; }

":"						{ return COLON ; }
";"						{ return SEMI_COLON ; }
"{"						{ return LEFT_BRACKET ; }
"}" 					{ return RIGHT_BRACKET ; }
"[" 					{ return LEFT_SQRBRACKET ; }
"]" 					{ return RIGHT_SQRBRACKET ; }
"(" 					{ return LEFT_PAREN ; }
")" 					{ return RIGHT_PAREN ; }
"," 					{ return COMA ; }
"=" 					{ return EQUALS ; }

"entero" 				{ return ENTERO ; }
"real" 					{ return REAL ; }
"char" 					{ return CHAR ; } 



[\n]                        	{ line_num++; }
[ \t\n]							{ ; }
[0-9]+\.[0-9]+					{ yylval.fval = atof(yytext); return CTE_REAL; }
[0-9]+							{ yylval.ival = atoi(yytext); return CTE_ENTERO; }
[a-zA-Z](_?([a-zA-Z]|[0-9]))*   { yylval.sval = strdup(yytext); return ID; }
\"(\\.|[^\\"])*\"               { yylval.sval = strdup(yytext); return CTE_CHAR; }
.								{ ; }
%%

int yywrap() { return 1; }
