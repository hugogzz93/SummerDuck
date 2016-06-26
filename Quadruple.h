#ifndef GUARD_QUADRUPLE
#define GUARD_QUADRUPLE
using namespace std; 
class Quadruple
{
public:
	const enum {
		I_WRITE, I_READ, I_RET, I_GOTO, I_GOTOF, I_GOTOV, I_GOSUB, I_ERA, I_PARAM, I_VER, I_INSERT_INT,
		I_AND, I_OR, I_SUMA, I_RESTA, I_MULT, I_DIV, I_MAYOR_QUE, I_MAYOR_IGUAL_QUE,
	    I_MENOR_QUE, I_MENOR_IGUAL_QUE, I_NO_IGUAL, I_IGUAL, I_DETERMINANTE, I_INVERSA, I_LIMIT, I_ASIGN
	};

	const enum {
	  T_ENTERO, T_REAL, T_CHAR, T_BOOL, T_INVALID, T_NULL
	};

	Quadruple(int, int, int, int);
	Quadruple() = default;

	friend ostream& operator<<(ostream& os, const Quadruple& quad);

	void setResult(int result);
	static string asString(int);

	int getOperation();
	int getLeftOperand();
	int getRightOperand();
	int getResult();

private:
	int operation, left_operand, right_operand, result;
};
#endif