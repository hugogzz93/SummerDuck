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

	void listDirectory(bool verbose = false);
	void addRecord(ProcedureRecord);

	VariableRecord* getVariableByName(string name, string scope); //throws invalid_argument exception
	ProcedureRecord* getFunctionByName(string name); //throws invalid_argument exception
	ProcedureRecord* getGlobalRecord();

private:
	vector<ProcedureRecord> procedures;
};
#endif