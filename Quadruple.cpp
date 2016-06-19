#include <iostream>
#include "Quadruple.h"

using namespace std;

Quadruple::Quadruple(int operation, int left_operand, int right_operand, int result):
	operation(operation), left_operand(left_operand), right_operand(right_operand), result(result) {}

ostream& operator<<(ostream& os, const Quadruple& quad)
{
    os << "[ " << Quadruple::asString(quad.operation) << ", " << to_string(quad.left_operand) << ", " << to_string(quad.right_operand) << ", " << to_string(quad.result) << " ]";
    return os;
}

void Quadruple::setResult(int result) {
	this->result = result;
}

string Quadruple::asString(int op) {
	switch(op) {
		case I_WRITE:
			return "WRITE";
			break;

		case I_READ:
			return "READ";
			break;

		case I_VER:
			return "VER";
			break;

		case I_CALL:
			return "CALL";
			break;

		case I_RET:
			return "RET";
			break;

		case I_GOTO:
			return "GOTO";
			break;

		case I_GOTOF:
			return "GOTOF";
			break;

		case I_GOTOV:
			return "GOTOV";
			break;

		case I_GOSUB:
			return "GOSUB";
			break;

		case I_ERA:
			return "ERA";
			break;

		case I_AND:
			return "AND";
			break;

		case  I_OR:
			return "OR";
			break;

		case  I_SUMA:
			return "+";
			break;

		case  I_RESTA:
			return "-";
			break;

		case  I_MULT:
			return "*";
			break;

		case  I_DIV:
			return "/";
			break;

		case  I_MAYOR_QUE:
			return ">";
			break;

		 case I_MAYOR_IGUAL_QUE:
		 	return ">=";
		 	break;

	    case I_MENOR_QUE:
	    	return "<";
	    	break;

	    case  I_MENOR_IGUAL_QUE:
	    	return "<=";
	    	break;

	    case  I_NO_IGUAL:
	    	return "!=";
	    	break;

	    case  I_IGUAL:
	    	return "==";
	    	break;

	    case I_ASIGN:
	    	return "=";
	    	break;

	    case  I_DETERMINANTE:
	    	return "?";
	    	break;

	    case  I_INVERSA:
	    	return "&";
	    	break;

	    case I_PARAM:
	    	return "PARAM";
	    	break;
	}

	    return "invalid";
}

int Quadruple::getOperation() {
	return this->operation;
}
int Quadruple::getLeftOperand() {
	return this->left_operand;
}
int Quadruple::getRightOperand() {
	return this->right_operand;
}
int Quadruple::getResult() {
	return this->result;
}