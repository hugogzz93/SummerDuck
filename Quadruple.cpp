#include <iostream>
#include "Quadruple.h"

using namespace std;

Quadruple::Quadruple(string operation, string left_operand, string right_operand, string result):
	operation(operation), left_operand(left_operand), right_operand(right_operand), result(result) {}

ostream& operator<<(ostream& os, const Quadruple& quad)
{
    os << "[ " << quad.operation << ", " << quad.left_operand << ", " << quad.right_operand << ", " << quad.result << " ]";
    return os;
}

void Quadruple::setResult(string result) {
	this->result = result;
}