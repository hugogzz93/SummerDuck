#ifndef GUARD_PROCEDURE_RECORD
#define GUARD_PROCEDURE_RECORD 

#include "VariableRecord.h"
#include "Quadruple.h"
#include <unordered_map>

#define ENTERO_MAX 999
#define REAL_MAX 1999
#define CHAR_MAX 2999
#define MEM_REQ 3000

using namespace std;
class ProcedureRecord
{
public:
	// ProcedureRecord(string type, string name, vector<VariableRecord> parameters);
	ProcedureRecord(int type, string name, vector<VariableRecord> parameters, vector<VariableRecord> variables);
	ProcedureRecord(string name);
	ProcedureRecord();

	void showSignature(bool verbose = false);
	void showInstructions();

	void addVariable(VariableRecord);
	void addParameter(VariableRecord);
	
	// setters
	void setName(string name);
	void setType(int type);

	//  getters
	int getType();
	string getName();
	vector<Quadruple>* getQuadruples();
	vector<VariableRecord>* getParameters();
	vector<VariableRecord>* getVariables();
	VariableRecord *getVariableByName(string name);
	unordered_map<int, int> getMemoryRequirements();

private:
	string name;
	int type;
	vector<Quadruple> quadruples;
	vector<VariableRecord> parameters;
	vector<VariableRecord> variables;
};
#endif