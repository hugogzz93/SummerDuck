%{
	#include <cstdio>
	#include "ProcDirHandler.h"
	#include "QuadrupleGenerator.h"
	#include "VirtualMachine.h"
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
	bool regBool = false;
	Memory memory;
	DataHolder dataHolder;
	ProcedureDirectory directory;
	ProcDirHandler procedureDirectoryHandler(&directory);
	QuadrupleGenerator quadrupleGenerator(&directory, &procedureDirectoryHandler, &dataHolder, &memory);
	VirtualMachine vm(&directory, &memory);

	// var declaration aux
	string name_aux;
	int dimensions_auxT, dimensions_aux, sizes_auxT[2], sizes_aux[2];

	stack<string> names;


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
		procedureDirectoryHandler.registerProcedure();
		// directory.listDirectory(true);
		// directory.listInstructions();
		// memory.debugMemory();
		vm.run();
	}

	inline void dataHolderSetAuxs() {
		dataHolder.sval = name_aux;
		dataHolder.dimensions = dimensions_aux;
		dataHolder.sizes[0] = sizes_aux[0];
		dataHolder.sizes[1] = sizes_aux[1];
	}

	inline void checkRegBool() {
		if (!regBool) {
			ErrorHandler::badSyntax("Faltó la expresión 'regresa' en una función.");
		} else {
			regBool = false;
		}
	}

	inline void addDefaultSub() {
		ProcedureRecord escribe("escribe");
		ProcedureRecord lee("lee");
		directory.addRecord(escribe);
		directory.addRecord(lee);
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
%token MAYOR_O_IGUAL_QUE
%token MENOR_O_IGUAL_QUE
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
%token<fval> CTE_REAL
%token<sval> CTE_CHAR



// types
%token ENTERO
%token REAL
%token CHAR 
%token NULO



%type<ival> tipo
%type<ival> var_cte

%%

	programa: 
		PROGRAMA ID SEMI_COLON vars { procedureDirectoryHandler.registerProcedure(); addDefaultSub(); } 
		programa_a PRINCIPAL { procedureDirectoryHandler.setScope(ProcDirHandler::LOCAL);  procedureDirectoryHandler.setName("principal"); procedureDirectoryHandler.setReturnType(Quadruple::T_ENTERO); }
		LEFT_PAREN RIGHT_PAREN LEFT_BRACKET vars estatutos RIGHT_BRACKET { finish(); } ;

	programa_a:
		dec_func programa_a
		| ;

	estatutos:
		estatuto estatutos
		| ;

	tipo:
		ENTERO { $$ = Quadruple::T_ENTERO;	}
		| REAL { $$ = Quadruple::T_REAL; 	}
		| CHAR { $$ = Quadruple::T_CHAR;	}
		| NULO { $$ = Quadruple::T_NULL;	} ;

	vars:
		dec_var vars
		| ;

	dec_var:
		tipo { procedureDirectoryHandler.setVariableType($1); } COLON lista_ids SEMI_COLON ;

	expresion:
		expresion_a expresion_b {  quadrupleGenerator.testForOperation(2); } ;

	expresion_a:
		O_NOT
		| ;

	expresion_b:
		comparacion_and	{quadrupleGenerator.testForOperation(5); }
		| comparacion_and	{quadrupleGenerator.testForOperation(5); } O_OR { quadrupleGenerator.pushOperator(Quadruple::I_OR); } expresion;

	comparacion_and:
		igualdad	{quadrupleGenerator.testForOperation(4); }
		| igualdad	{quadrupleGenerator.testForOperation(4); } O_AND { quadrupleGenerator.pushOperator(Quadruple::I_AND); } comparacion_and;

	igualdad: 
		relacion	{quadrupleGenerator.testForOperation(3); }
		| relacion	{quadrupleGenerator.testForOperation(3); } IGUAL_A 		{ quadrupleGenerator.pushOperator(Quadruple::I_IGUAL); 		}  	igualdad
		| relacion	{quadrupleGenerator.testForOperation(3); } NO_IGUAL_A 	{ quadrupleGenerator.pushOperator(Quadruple::I_NO_IGUAL);	}  	igualdad;

	relacion: 
		exp		{quadrupleGenerator.testForOperation(2); }
		| exp	{quadrupleGenerator.testForOperation(2); } MENOR_QUE 			{ quadrupleGenerator.pushOperator(Quadruple::I_MENOR_QUE); }  		relacion
		| exp	{quadrupleGenerator.testForOperation(2); } MAYOR_QUE 			{ quadrupleGenerator.pushOperator(Quadruple::I_MAYOR_QUE); }  		relacion
		| exp	{quadrupleGenerator.testForOperation(2); } MENOR_O_IGUAL_QUE 	{ quadrupleGenerator.pushOperator(Quadruple::I_MENOR_IGUAL_QUE); }  relacion
		| exp	{quadrupleGenerator.testForOperation(2); } MAYOR_O_IGUAL_QUE 	{ quadrupleGenerator.pushOperator(Quadruple::I_MAYOR_IGUAL_QUE); }  relacion;

	exp:
		termino		{ quadrupleGenerator.testForOperation(1); }
		| termino	{ quadrupleGenerator.testForOperation(1); } O_SUMA 	{ quadrupleGenerator.pushOperator(Quadruple::I_SUMA); }  	exp
		| termino	{ quadrupleGenerator.testForOperation(1); } O_RESTA 	{ quadrupleGenerator.pushOperator(Quadruple::I_RESTA);}  	exp;


	termino:
		factor 	 { quadrupleGenerator.testForOperation(0); }
		| factor { quadrupleGenerator.testForOperation(0); } O_MULT 	 { quadrupleGenerator.pushOperator(Quadruple::I_MULT);} termino
		| factor { quadrupleGenerator.testForOperation(0); } O_DIVISION  { quadrupleGenerator.pushOperator(Quadruple::I_DIV); } termino 

	factor:
		LEFT_PAREN { quadrupleGenerator.addLimit(); } expresion  {quadrupleGenerator.removeLimit(); } RIGHT_PAREN
		| var_cte 			{ quadrupleGenerator.pushOperand(); resetAux(); } 
		| O_SUMA var_cte 	{ quadrupleGenerator.pushOperand(); resetAux(); }
		| O_RESTA var_cte 	{ quadrupleGenerator.pushOperand(); resetAux(); } ;

	var_cte:
		dim_id			{  if(dimensions_aux > 0) { name_aux = names.top(); names.pop(); } dataHolderSetAuxs();  quadrupleGenerator.setFlag(QuadrupleGenerator::C_ID);	}
		| CTE_ENTERO	{  dataHolder.ival = $1; quadrupleGenerator.setFlag(QuadrupleGenerator::C_ENTERO); 		}
		| CTE_REAL		{  dataHolder.fval = $1; quadrupleGenerator.setFlag(QuadrupleGenerator::C_REAL); 		}
		| CTE_CHAR		{  string s($1);  s.erase(remove( s.begin(), s.end(), '\"' ), s.end() ); dataHolder.sval = s; quadrupleGenerator.setFlag(QuadrupleGenerator::C_CHAR); 		}
		| llamada_func 	{  quadrupleGenerator.setFlag(QuadrupleGenerator::C_FUNC_CALL); 	} ; /* result will be in stack */


	dec_func:
		{ procedureDirectoryHandler.setScope(ProcDirHandler::LOCAL); } 
		MODULO tipo ID { procedureDirectoryHandler.setReturnType($3); procedureDirectoryHandler.setName(string($4)); } 
		LEFT_PAREN dec_func_a RIGHT_PAREN SEMI_COLON LEFT_BRACKET vars estatutos RIGHT_BRACKET
		{ procedureDirectoryHandler.registerProcedure(); procedureDirectoryHandler.setScope(ProcDirHandler::GLOBAL); checkRegBool(); } ;

	dec_func_a:
		params
		| ;

	regresa:
		REGRESA expresion 	{ quadrupleGenerator.ret(); regBool = true; } ;
		| REGRESA 			{ quadrupleGenerator.ret(); regBool = true; } ;

	params:
		tipo ID { name_aux = string($2); dimensions_aux = 0; procedureDirectoryHandler.setVariableType($1); addVariable(ProcDirHandler::PARAMETER); } 
		params_a;
	
	params_a:
		COMA params
		| ;


	lista_ids:
		dim_id_dec { addVariable(ProcDirHandler::VARIABLE); } lista_ids_a ;

	lista_ids_a:
		COMA lista_ids
		| ;

	dim_id_dec:
		ID { name_aux = string($1); dimensions_aux = 0; }
		| vector_id_dec ;

	vector_id_dec:
		ID LEFT_SQRBRACKET CTE_ENTERO RIGHT_SQRBRACKET { name_aux = string($1);  dimensions_aux = 1; sizes_aux[0] = $3; } matriz_id_dec;

	matriz_id_dec:
		LEFT_SQRBRACKET CTE_ENTERO RIGHT_SQRBRACKET matriz_id_a { dimensions_aux = 2; sizes_aux[1] = $2; }
		| ;

	dim_id:
		ID { name_aux = string($1); dimensions_aux = 0; }
		| vector_id 
		| matriz_id ;

	vector_id:
		ID LEFT_SQRBRACKET { quadrupleGenerator.addLimit(); } expresion {quadrupleGenerator.removeLimit(); } RIGHT_SQRBRACKET { name_aux = string($1); names.push(name_aux); dimensions_aux = 1; } ;

	matriz_id:
		vector_id LEFT_SQRBRACKET { quadrupleGenerator.addLimit(); } expresion {quadrupleGenerator.removeLimit(); } RIGHT_SQRBRACKET matriz_id_a { dimensions_aux = 2; } ;

	matriz_id_a:
			O_INV
			| O_DET
			| ;		

	asignacion:
		dim_id { quadrupleGenerator.setFlag(QuadrupleGenerator::C_ID); if(dimensions_aux > 0) { name_aux = names.top(); names.pop(); } dataHolderSetAuxs(); quadrupleGenerator.pushOperand(); resetAux(); } 
		EQUALS expresion 
		{ quadrupleGenerator.assignment(); };

	llamada_func:
		ID LEFT_PAREN { quadrupleGenerator.loadFunction(string($1)); quadrupleGenerator.addLimit(); } llamada_func_a { quadrupleGenerator.removeLimit(); } RIGHT_PAREN {quadrupleGenerator.gosub(string($1)); } ;

	llamada_func_a:
		llamada_func_b 
		| ;

	llamada_func_b:
		expresion { quadrupleGenerator.setParameter(); }
		| expresion { quadrupleGenerator.setParameter(); } COMA llamada_func_a ;

	decision:
		SI LEFT_PAREN expresion { quadrupleGenerator.setGotoF(); } RIGHT_PAREN ENTONCES LEFT_BRACKET estatutos RIGHT_BRACKET decision_b { quadrupleGenerator.completeGoto(); };
	
	decision_b:
		SINO LEFT_BRACKET { quadrupleGenerator.ifElse(); } estatutos RIGHT_BRACKET 
		| ;

	ciclo_while:
		MIENTRAZ LEFT_PAREN { quadrupleGenerator.startWhile(); } expresion { quadrupleGenerator.setGotoF(); } RIGHT_PAREN HAZ LEFT_BRACKET estatutos { quadrupleGenerator.endWhile(); }RIGHT_BRACKET ;

	ciclo_do_while:
		REPITE LEFT_BRACKET { quadrupleGenerator.doWhile(); } estatutos RIGHT_BRACKET HASTA LEFT_PAREN expresion { quadrupleGenerator.endRepeat(); } RIGHT_PAREN ;

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
	FILE *myfile = fopen("file2.txt", "r");
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