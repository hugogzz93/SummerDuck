#ifndef GUARD_QUADRUPLE
#define GUARD_QUADRUPLE

using namespace std; 
class Quadruple
{
public:
	Quadruple(string operation, string left_operand, string right_operand, string result);
	Quadruple() = default;

	friend ostream& operator<<(ostream& os, const Quadruple& quad);

	void setResult(string result);

	

private:
	string operation, left_operand, right_operand, result;
};
#endif