#ifndef GUARD_QUADRUPLE
#define GUARD_QUADRUPLE
#include "Memory.h"
using namespace std; 
class Quadruple
{
public:
	const enum {
		I_WRITE, I_READ, I_VER, I_CALL, I_RET, I_GOTO, I_GOTOF, I_GOSUB, I_ERA,
		I_AND, I_OR, I_SUMA, I_RESTA, I_MULT, I_DIV, I_MAYOR_QUE, I_MAYOR_IGUAL_QUE,
	    I_MENOR_QUE, I_MENOR_IGUAL_QUE, I_NO_IGUAL, I_IGUAL, I_DETERMINANTE, I_INVERSA
	};

	Quadruple(int, int, int, int);
	Quadruple() = default;

	friend ostream& operator<<(ostream& os, const Quadruple& quad);

	void setResult(int result);
	static string asString(int);

	

private:
	int operation, left_operand, right_operand, result;
};
#endif