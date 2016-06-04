%{
	#include <cstdio>
	#include "ProcDirHandler.h"
	#include "QuadrupleGenerator.h"
	using namespace std;

	// stuff from flex that bison needs to know about:
	extern "C" int yylex();
	extern "C" int yydebug;
	extern "C" int yyparse();
	extern "C" char *yytext;
	extern "C" FILE *yyin;
	extern "C" int line_num;
	 
	void yyerror(const char *s);

	// compiler code
	Memory memory;
	DataHolder dataHolder;
	ProcedureDirectory directory;
	ProcDirHandler procedureDirectoryHandler(&directory);
	QuadrupleGenerator quadrupleGenerator(&directory, &procedureDirectoryHandler, &dataHolder, &memory);

	// var declaration aux
	string name_aux;
	int dimensions_aux, sizes_aux[2];

	// var_cte aux

	inline void resetAux() {
		name_aux = "undefined";
		dimensions_aux = 0;
		size_t size = sizeof(sizes_aux) / sizeof(int);
		for (size_t i = 0; i < size; ++i)
		{
			sizes_aux[i] = 1;
		}
	}

	inline void addVariable(int context) {
		procedureDirectoryHandler.addVariable(context, name_aux, dimensions_aux, sizes_aux);
		resetAux(); //caller must be inline for this to work
	}

	inline void finish() {
		printf("accepted\n");
		procedureDirectoryHandler.registerProcedure();
		directory.listDirectory(true);
	}

	inline void dataHolderSetAuxs() {
		dataHolder.sval = name_aux;
		dataHolder.dimensions = dimensions_aux;
		dataHolder.sizes[0] = sizes_aux[0];
		dataHolder.sizes[1] = sizes_aux[1];
		// printf("parsing %s with dimensions: %d, and sizes %d, %d\n", name_aux.c_str(), dimensions_aux, sizes_aux[0], sizes_aux[1]);
	}


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
%token<sval> ID
%token<ival> CTE_ENTERO
%token<ival> CTE_REAL
%token<sval> CTE_CHAR



// types
%token ENTERO
%token REAL
%token CHAR 



%type<ival> tipo
%type<ival> var_cte

%%

	programa: 
		PROGRAMA ID SEMI_COLON vars { procedureDirectoryHandler.registerProcedure(); } 
		programa_a PRINCIPAL { procedureDirectoryHandler.setScope(ProcDirHandler::LOCAL);  procedureDirectoryHandler.setName("principal"); }
		LEFT_PAREN RIGHT_PAREN LEFT_BRACKET vars estatutos RIGHT_BRACKET { finish(); } ;

	programa_a:
		dec_func programa_a
		| ;

	estatutos:
		estatuto estatutos
		| ;

	tipo:
		ENTERO { $$ = SemanticCube::T_ENTERO;	}
		| REAL { $$ = SemanticCube::T_REAL; 	}
		| CHAR { $$ = SemanticCube::T_CHAR;	} ;

	vars:
		dec_var vars
		| ;

	dec_var:
		tipo { procedureDirectoryHandler.setVariableType($1); } COLON lista_ids SEMI_COLON ;

	expresion: 
		expresion_a exp expresion_b ;

	expresion_a:
		O_NOT
		| ;

	expresion_b:
		 IGUAL_A 		{ quadrupleGenerator.pushOperator(Quadruple::I_IGUAL); 		} expresion
		| NO_IGUAL_A	{ quadrupleGenerator.pushOperator(Quadruple::I_NO_IGUAL); 	} expresion
		| MAYOR_QUE 	{ quadrupleGenerator.pushOperator(Quadruple::I_MAYOR_QUE);	} expresion
		| MENOR_QUE 	{ quadrupleGenerator.pushOperator(Quadruple::I_MENOR_QUE);	} expresion
		| ;

	exp:
		termino		{quadrupleGenerator.testForOperation(1); }
		| termino	{quadrupleGenerator.testForOperation(1); } O_SUMA 	{ quadrupleGenerator.pushOperator(Quadruple::I_SUMA); }  	exp
		| termino	{quadrupleGenerator.testForOperation(1); } O_RESTA 	{ quadrupleGenerator.pushOperator(Quadruple::I_RESTA);}  	exp
		| termino	{quadrupleGenerator.testForOperation(1); } O_OR 	{ quadrupleGenerator.pushOperator(Quadruple::I_OR); 	}  	exp ;


	termino:
		factor 	 { quadrupleGenerator.testForOperation(0); }
		| factor { quadrupleGenerator.testForOperation(0); } O_MULT 	 { quadrupleGenerator.pushOperator(Quadruple::I_MULT);} termino
		| factor { quadrupleGenerator.testForOperation(0); } O_DIVISION  { quadrupleGenerator.pushOperator(Quadruple::I_DIV); } termino 
		| factor { quadrupleGenerator.testForOperation(0); } O_AND 		 { quadrupleGenerator.pushOperator(Quadruple::I_AND); } termino ;

	factor:
		LEFT_PAREN { quadrupleGenerator.addLimit(); } expresion  {quadrupleGenerator.removeLimit(); } RIGHT_PAREN
		| var_cte 			{ quadrupleGenerator.pushOperand(); resetAux(); } 
		| O_SUMA var_cte 	{ quadrupleGenerator.pushOperand(); resetAux(); }
		| O_RESTA var_cte 	{ quadrupleGenerator.pushOperand(); resetAux(); } ;

	var_cte:
		dim_id			{  dataHolderSetAuxs();  quadrupleGenerator.setFlag(QuadrupleGenerator::C_ID); 			}
		| CTE_ENTERO	{  dataHolder.ival = $1; quadrupleGenerator.setFlag(QuadrupleGenerator::C_ENTERO); 		}
		| CTE_REAL		{  dataHolder.fval = $1; quadrupleGenerator.setFlag(QuadrupleGenerator::C_REAL); 		}
		| CTE_CHAR		{  dataHolder.sval = $1; quadrupleGenerator.setFlag(QuadrupleGenerator::C_CHAR); 		}
		| llamada_func 	{  						 quadrupleGenerator.setFlag(QuadrupleGenerator::C_FUNC_CALL); 	} ; /* result will be in stack */


	dec_func:
		{ procedureDirectoryHandler.setScope(ProcDirHandler::LOCAL); } 
		MODULO tipo ID { procedureDirectoryHandler.setReturnType($3); procedureDirectoryHandler.setName(string($4)); } 
		LEFT_PAREN dec_func_a RIGHT_PAREN SEMI_COLON LEFT_BRACKET vars estatutos RIGHT_BRACKET 
		{ procedureDirectoryHandler.registerProcedure(); procedureDirectoryHandler.setScope(ProcDirHandler::GLOBAL) ;} ;

	dec_func_a:
		params
		| ;

	regresa:
		REGRESA expresion
		| REGRESA ;

	params:
		tipo dim_id { procedureDirectoryHandler.setVariableType($1); addVariable(ProcDirHandler::PARAMETER); } 
		params_a;
	
	params_a:
		COMA params
		| ;


	lista_ids:
		dim_id { addVariable(ProcDirHandler::VARIABLE); } lista_ids_a ;

	lista_ids_a:
		COMA lista_ids
		| ;

	dim_id:
		ID { name_aux = string($1); }
		| vector_id
		| matriz_id ;

	vector_id:
		ID LEFT_SQRBRACKET CTE_ENTERO RIGHT_SQRBRACKET { name_aux = string($1);  dimensions_aux = 1; sizes_aux[0] = $3; } ;

	matriz_id:
		vector_id LEFT_SQRBRACKET CTE_ENTERO RIGHT_SQRBRACKET matriz_id_a { dimensions_aux = 2; sizes_aux[1] = $3; } ;

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
		expresion
		| expresion COMA llamada_func_a ;

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
		| ciclo_do_while SEMI_COLON
		| regresa SEMI_COLON 
		| ciclo_while
		| decision


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