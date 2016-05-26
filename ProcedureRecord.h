#ifndef GUARD_PROCEDURE_RECORD
#define GUARD_PROCEDURE_RECORD 

#include "VariableRecord.h"

using namespace std;
class ProcedureRecord
{
public:
	// ProcedureRecord(string type, string name, vector<VariableRecord> parameters);
	ProcedureRecord(string type, string name, vector<VariableRecord> parameters, vector<VariableRecord> variables);
	ProcedureRecord(string name);
	ProcedureRecord();

	// void setReturnType(string type);

	// void addParameter(string type, string name);
	// void addVariable(string type, string name);
	// void addVariable(string type, string name, int vAddress, string scope);
	// void addVariable(VariableRecord record);
	void showSignature(bool verbose = false);

	void addVariable(VariableRecord);
	void addParameter(VariableRecord);
	
	// setters
	void setName(string name);
	void setType(int type);

	//  getters
	string getName();
	string getType();
	vector<VariableRecord> getParameters();
	vector<VariableRecord> getVariables();
	VariableRecord *getVariableByName(string name);

private:
	string name, type;
	vector<VariableRecord> parameters;
	vector<VariableRecord> variables;
};
#endif