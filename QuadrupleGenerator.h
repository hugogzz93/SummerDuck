#ifndef GUARD_QUADRUPLE_GENERATOR
#define GUARD_QUADRUPLE_GENERATOR 

#include <stack>
#include "ProcedureDirectory.h"
#include "ProcDirHandler.h"
#include "Quadruple.h"
#include "SemanticCube.h"

struct DataHolder {
	string sval;
	int ival;
	double fval;
	int dimensions;
	int sizes[2];
};

using namespace std;
class QuadrupleGenerator
{
public:

	const enum {
		C_ID, C_ENTERO, C_REAL, C_CHAR, C_FUNC_CALL
	};

	QuadrupleGenerator(ProcedureDirectory* ProcedureDirectory, ProcDirHandler* handler, DataHolder* data);

	void pushOperand();
	void setFlag(int);


private:
	stack<int> jumpStack, operatorStack;
	stack<VariableRecord> operandStack;

	ProcedureDirectory* directory;
	ProcDirHandler* handler;
	SemanticCube semanticCube;

	unordered_map<string, Quadruple> instructions;

	int flag; //indicates the type of operand about to be received
	DataHolder *data;


};
#endif