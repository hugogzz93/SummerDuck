#include <stdexcept>
#include "iostream"
#include "ProcedureRecord.h"
#include "VariableRecord.h"

using namespace std;

// ProcedureRecord::ProcedureRecord(string type, string name, vector<VariableRecord> parameters): type(type), name(name), parameters(parameters) {}
ProcedureRecord::ProcedureRecord(int type, string name, vector<VariableRecord> parameters, vector<VariableRecord> variables): 
	type(type), name(name), parameters(parameters), variables(variables) {}
	
ProcedureRecord::ProcedureRecord(string name): name(name) {}
ProcedureRecord::ProcedureRecord() {}



void ProcedureRecord::showSignature(bool verbose) {
	printf("%d %s (", type, name.c_str());
	for (std::vector<VariableRecord>::iterator i = parameters.begin(); i != parameters.end(); ++i)
	{
		if (verbose)
		{
			printf("%s %s (%d), ", i->getTypeAsString().c_str(), i->getName().c_str(), i->getVAddress());
		} else {
			printf("%s %s, ", i->getTypeAsString().c_str(), i->getName().c_str());
		}
	}
	printf(")\n");

	for (std::vector<VariableRecord>::iterator varRecord = variables.begin(); varRecord != variables.end(); ++varRecord)
	{
		if (verbose)
		{
			printf("\t%s %s (%d)\n", varRecord->getTypeAsString().c_str(), varRecord->getName().c_str(), varRecord->getVAddress());
		} else {
			printf("\t%s %s\n", varRecord->getTypeAsString().c_str(), varRecord->getName().c_str());
		}
	}
}

void ProcedureRecord::showInstructions() {
	printf("Instructions: %s\n", name.c_str() );
	int x = 0;
	for (std::vector<Quadruple>::iterator i = quadruples.begin(); i != quadruples.end(); ++i)
	{
		cout << x << " ";
		x++;
		cout << *i << endl;;
	}
}


void ProcedureRecord::addVariable(VariableRecord record) {
	// check for redeclaration
	try {
		VariableRecord variable = *getVariableByName(record.getName());
		ErrorHandler::variableRedefinition(record.getName());
	} catch(exception e) {	}

	variables.push_back(record);
}

void ProcedureRecord::addParameter(VariableRecord record) {
	// check for redeclaration
	try {
		VariableRecord variable = *getVariableByName(record.getName());
		ErrorHandler::variableRedefinition(record.getName());
	} catch(exception e) {}
	parameters.push_back(record);
}

void ProcedureRecord::setName(string name) {
	this->name = name;
}

void ProcedureRecord::setType(int type) {
	this->type = type;
}

VariableRecord *ProcedureRecord::getVariableByName(string name) {

	// printf("getting %s by name for func %s\n", name.c_str(), this->name.c_str());
	// printf("parameters size %d\n", parameters.size());
	for (std::vector<VariableRecord>::iterator record = parameters.begin(); record != parameters.end(); ++record)
	{
		// printf("looking at %s == %s, %d\n", record->getName().c_str(), name.c_str(), name == record->getName());
		if (record->getName() == name)
		{
			return &(*record);
		}
	}
	for (std::vector<VariableRecord>::iterator record = variables.begin(); record != variables.end(); ++record)
	{
		// printf("looking at %s\n", record->getName().c_str());
		if (record->getName() == name)
		{
			return &(*record);
		}
	}
	throw invalid_argument("No variable with the name " + name + " found.");
}

string ProcedureRecord::getName() {
	return name;
}

int ProcedureRecord::getType() {
	return type;
}

vector<Quadruple>* ProcedureRecord::getQuadruples() {
	return &this->quadruples;
}

vector<VariableRecord>* ProcedureRecord::getParameters() {
	return &this->parameters;
}

vector<VariableRecord>* ProcedureRecord::getVariables() {
	return &this->variables;
}

// int ProcedureRecord::getMemSize() {
// 	int size = 0;
// 	if (!variables.empty()) {
// 		size = variables[-1].getVAddress();
// 	} else if(!parameters.empty()) {
// 		size = parameters[-1].getVAddress();
// 	}

// 	return size;

// }

unordered_map<int, int> ProcedureRecord::getMemoryRequirements() {
	int maxInt = 0, maxFloat = 0, maxChar = 0;
	for (std::vector<VariableRecord>::iterator i = parameters.begin(); i != parameters.end(); ++i)
	{
		switch(i->getType()) {
			case Quadruple::T_ENTERO:
				maxInt = maxInt < i->getVAddress() ? i->getVAddress() : maxInt;
				break;
			case Quadruple::T_REAL:
				maxFloat = maxFloat < i->getVAddress() ? i->getVAddress() : maxFloat;
				break;
			case Quadruple::T_CHAR:
				maxChar = maxChar < i->getVAddress() ? i->getVAddress() : maxChar;
				break;
		}
	}

	for (std::vector<VariableRecord>::iterator i = variables.begin(); i != variables.end(); ++i)
	{
		switch(i->getType()) {
			case Quadruple::T_ENTERO:
				maxInt = maxInt < i->getVAddress() ? i->getVAddress() : maxInt;
				break;
			case Quadruple::T_REAL:
				maxFloat = maxFloat < i->getVAddress() ? i->getVAddress() : maxFloat;
				break;
			case Quadruple::T_CHAR:
				maxChar = maxChar < i->getVAddress() ? i->getVAddress() : maxChar;
				break;
		}
	}	

	unordered_map<int, int> requirements = { 
		{ Quadruple::T_ENTERO, maxInt }, 
		{ Quadruple::T_REAL, maxFloat }, 
		{ Quadruple::T_CHAR, maxChar}
	};

	return requirements;


}