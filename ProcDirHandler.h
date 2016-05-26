#ifndef GUARD_PROC_DIR_HANDLER
#define GUARD_PROC_DIR_HANDLER

#include "ErrorHandler.h"
#include "VariableRecord.h"
#include "ProcedureRecord.h"
#include "ProcedureDirectory.h"
#include <vector>
using namespace std;
class ProcDirHandler
{
public:

	const enum {
		GLOBAL, LOCAL
	};

	const enum {
		PARAMETER, VARIABLE
	};

	ProcDirHandler(ProcedureDirectory *directory);

	void setScope(int scope);
	void setVariableType(int type);
	void setReturnType(int type);

	//context: whether parameter or variable
	void addVariable(int context, string name, int dimensions, int sizes[]); 

private:
	ProcedureDirectory *directory;
	ProcedureRecord global;
	ProcedureRecord local;

	vector<VariableRecord> parameters;

	string name, type;
	unordered_map<int, int> localVariableIndex;
	unordered_map<int, int> globalVariableIndex;

	// 
	int variableType, scope;

	void cleanLocal();
	int assignVirtualAddress(int type, int dimension, int sizes[]);
};

#endif