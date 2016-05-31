#ifndef GUARD_QUADRUPLE_GENERATOR
#define GUARD_QUADRUPLE_GENERATOR 

#include <stack>
#include "ProcedureDirectory.h"
#include "ProcDirHandler.h"
#include "Quadruple.h"
#include "SemanticCube.h"

using namespace std;
class QuadrupleGenerator
{
public:
	const enum {
		GLOBAL, LOCAL
	};
	QuadrupleGenerator(ProcedureDirectory* ProcedureDirectory, ProcDirHandler* handler);

	void setScope(int);

private:
	stack<int> jumpStack, operatorStack;
	stack<VariableRecord> operandStack;

	ProcedureDirectory* directory;
	ProcDirHandler* handler;
	SemanticCube semanticCube;

	unordered_map<string, Quadruple> instructions;


};
#endif