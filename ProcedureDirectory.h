#ifndef GUARD_PROCEDURE_DIRECTORY
#define GUARD_PROCEDURE_DIRECTORY 

#include "ProcedureRecord.h"
// #include "Quadruple.h"

using namespace std;
class ProcedureDirectory
{
	typedef unordered_map<string, int> stringInt;
public:
	ProcedureDirectory();

	// void enterLocalScope();
	// void enterGlobalScope();
	// void addFunction(string type, string name);
	// void addParameter(string type, string name);
	// void addVariable(string type, string name);
	void listDirectory(bool verbose = false);
	void addRecord(ProcedureRecord);
	// void updateVariableRecord(VariableRecord& record);
	// void setCurrentScope(string name);

	// void setReturnTypeFlag(int retType);
	// int getReturnTypeFlag();

	// void addQuadruple(const Quadruple& quad, string scope);
	// int getCurrentInstructionIndex(string scope);
	// VariableRecord addVariableRecord(VariableRecord record);

	VariableRecord* getVariableByName(string name, string scope); //throws invalid_argument exception
	// VariableRecord* getVariableForFutureFunc(string name); //throws invalid_argument exception
	// VariableRecord* getParameterForFutureFunc(string name); //throws invalid_argument exception

	ProcedureRecord* getFunctionByName(string name); //throws invalid_argument exception
	// int getReturnType(string functionName);

	// vector<VariableRecord>& getVariableDir();
	// vector<VariableRecord>& getParameterDir();
	// string getCurrentScope();

	// Quadruple* getInsAtIndex(string scope, int index);

	// vector<VariableRecord> getParameterDirFor(string id);
	

private:
	// bool scope; //true = global
	// string currentScopeName = "main";
	vector<ProcedureRecord> procedures;
	// int returnTypeFlag;

	// temporal signature storage for functions
	// std::vector<VariableRecord> parameterDir, variableDir;

	// scope -> type -> ammount
	// ( main[int] = 12)
	// unordered_map<string, stringInt> vAddressMap;
	// unordered_map<string, vector<Quadruple> > quadrupleMap;

	// void assignVirtualAddresses(vector<VariableRecord> &vec, string name);
	// void assignVirtualAddress(VariableRecord& record);
	// int getVAddress(string scope, string type);
};
#endif