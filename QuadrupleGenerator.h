#ifndef GUARD_QUADRUPLE_GENERATOR
#define GUARD_QUADRUPLE_GENERATOR 

#include <stack>
#include "ProcedureDirectory.h"
#include "ProcDirHandler.h"
#include "SemanticCube.h"

using namespace std;
class QuadrupleGenerator
{
public:

	const enum {
		C_ID, C_ENTERO, C_REAL, C_CHAR, C_FUNC_CALL
	};

	QuadrupleGenerator(ProcedureDirectory* ProcedureDirectory, ProcDirHandler* handler, DataHolder* data, Memory* memory);

	void pushOperand();
	void pushOperator(int);
	void testForOperation(int);
	void setFlag(int);

	void addLimit();
	void removeLimit();



private:
	vector<int> operatorStackLimit; //fondo falso
	stack<int> jumpStack, operatorStack;
	stack<VariableRecord> operandStack;

	Memory* memory;
	ProcDirHandler* handler;
	SemanticCube semanticCube;
	ProcedureDirectory* directory;

	unordered_map<string, Quadruple> instructions;

	int flag; //indicates the type of operand about to be received
	DataHolder *data;

	void generateQuadruple(int, int, int, int);
	void executeOperation();
};
#endif