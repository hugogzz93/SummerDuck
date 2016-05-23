%{
	#include <cstdio>
	#include <iostream>
	using namespace std;

	// stuff from flex that bison needs to know about:
	extern "C" int yylex();
	extern "C" int yydebug;
	extern "C" int yyparse();
	extern "C" char *yytext;
	extern "C" FILE *yyin;
	extern "C" int line_num;
	 
	void yyerror(const char *s);

%}

%union {
	int ival;
	float fval;
	char *sval;
}

// keywords
%token PROGRAMA
%token PRINCIPAL
%token MODULO
%token REGRESA
%token LEE
%token ESCRIBE

// if
%token SI
%token SINO
%token ENTONCES

// while
%token MIENTRAZ
%token HAZ
%token REPITE
%token HASTA


// special
%token SEMI_COLON
%token COLON
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_SQRBRACKET
%token RIGHT_SQRBRACKET
%token LEFT_PAREN
%token RIGHT_PAREN
%token COMA
%token EQUALS

// operators
%token MAYOR_QUE
%token MENOR_QUE
%token NO_IGUAL_A
%token IGUAL_A
%token O_SUMA
%token O_RESTA
%token O_MULT
%token O_DIVISION
%token O_NOT
%token O_DET
%token O_INV
%token O_AND
%token O_OR

// general
%token ID
%token CTE_ENTERO
%token CTE_REAL
%token CTE_CHAR



// types
%token ENTERO
%token REAL
%token CHAR 

%%

	programa: 
		PROGRAMA ID SEMI_COLON vars programa_a PRINCIPAL LEFT_PAREN RIGHT_PAREN LEFT_BRACKET vars estatutos RIGHT_BRACKET { printf("accepted!\n");} ;

	programa_a:
		dec_func programa_a
		| ;

	estatutos:
		estatuto estatutos
		| ;

	tipo:
		ENTERO
		| REAL
		| CHAR ;

	vars:
		dec_var vars
		| ;

	dec_var:
		tipo COLON lista_ids SEMI_COLON ;

	expresion: 
		expresion_a exp expresion_b
		 // exp expresion_a exp
		// | exp ;
	expresion_a:
		O_NOT
		| ;

	expresion_b:
		 IGUAL_A expresion
		| NO_IGUAL_A expresion
		| MAYOR_QUE expresion
		| MENOR_QUE expresion
		| ;

	exp:
		termino
		| termino O_SUMA exp
		| termino O_RESTA exp
		| termino O_OR exp ;


	termino:
		factor
		| factor O_MULT termino
		| factor O_DIVISION termino 
		| factor O_AND termino ;

	factor:
		LEFT_PAREN expresion RIGHT_PAREN
		| var_cte
		| O_SUMA var_cte
		| O_RESTA var_cte ;

	var_cte:
		dim_id
		| CTE_ENTERO
		| CTE_REAL
		| CTE_CHAR
		| llamada_func ;


	dec_func:
		MODULO tipo ID LEFT_PAREN dec_func_a RIGHT_PAREN SEMI_COLON LEFT_BRACKET vars estatutos REGRESA dec_func_b SEMI_COLON RIGHT_BRACKET ;

	dec_func_a:
		params
		| ;

	dec_func_b:
		expresion
		| ;


	params:
		tipo ID
		| tipo ID COMA params ;

	lista_ids:
		dim_id
		| dim_id COMA lista_ids ;

	dim_id:
		ID
		| vector_id
		| matriz_id ;

	vector_id:
		ID LEFT_SQRBRACKET CTE_ENTERO RIGHT_SQRBRACKET ;

	matriz_id:
		vector_id LEFT_SQRBRACKET CTE_ENTERO RIGHT_SQRBRACKET matriz_id_a ;

	matriz_id_a:
			O_INV
			| O_DET
			| ;		

	asignacion:
		dim_id EQUALS expresion ;

	llamada_func:
		ID LEFT_PAREN llamada_func_a RIGHT_PAREN ;

	llamada_func_a:
		llamada_func_b 
		| ;

	llamada_func_b:
		var_cte
		| var_cte COMA llamada_func_a ;

	// lectura:
	// 	LEE LEFT_PAREN lectura_a RIGHT_PAREN SEMI_COLON ;

	// lectura_a:
	// 	dim_id
	// 	| dim_id COMA lectura_a ;

	// escritura:
	// 	ESCRIBE LEFT_PAREN escritura_a RIGHT_PAREN SEMI_COLON ;

	// escritura_a:
	// 	CTE_CHAR
	// 	| expresion
	// 	| CTE_CHAR COMA escritura_a
	// 	| expresion COMA escritura_a ;

	decision:
		SI LEFT_PAREN expresion RIGHT_PAREN ENTONCES LEFT_BRACKET estatutos RIGHT_BRACKET decision_b ;
	
	decision_b:
		SINO LEFT_BRACKET estatutos RIGHT_BRACKET
		| ;

	ciclo_while:
		MIENTRAZ LEFT_PAREN expresion RIGHT_PAREN HAZ LEFT_BRACKET estatutos RIGHT_BRACKET ;

	ciclo_do_while:
		REPITE LEFT_BRACKET estatutos RIGHT_BRACKET HASTA LEFT_PAREN expresion RIGHT_PAREN ;

	estatuto:
		asignacion SEMI_COLON
		| llamada_func SEMI_COLON
		// | lectura
		// | escritura
		| ciclo_while
		| ciclo_do_while SEMI_COLON
		| decision ;


%%

int main(int, char**) {
	// open a file handle to a particular file:
	// yydebug = 1;
	FILE *myfile = fopen("file", "r");
	// make sure it is valid:
	if (!myfile) {
		cout << "I can't open file.txt!" << endl;
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;
		
	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));
	return 0;
	
}

void yyerror(const char *s) {
	printf("Syntax error (line %d): unexpected token '%s'\n", line_num, yytext);
	exit(-1);
}