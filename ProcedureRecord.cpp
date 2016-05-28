#include <stdexcept>
#include "iostream"
#include "ProcedureRecord.h"
#include "VariableRecord.h"

using namespace std;

// ProcedureRecord::ProcedureRecord(string type, string name, vector<VariableRecord> parameters): type(type), name(name), parameters(parameters) {}
ProcedureRecord::ProcedureRecord(string type, string name, vector<VariableRecord> parameters, vector<VariableRecord> variables): 
	type(type), name(name), parameters(parameters), variables(variables) {}
	
ProcedureRecord::ProcedureRecord(string name): name(name) {}
ProcedureRecord::ProcedureRecord() {}



void ProcedureRecord::showSignature(bool verbose) {
	printf("%s %s (", type.c_str(), name.c_str());
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

	for (std::vector<VariableRecord>::iterator record = parameters.begin(); record != parameters.end(); ++record)
	{
		if (record->getName() == name)
		{
			return &(*record);
		}
	}

	for (std::vector<VariableRecord>::iterator record = variables.begin(); record != variables.end(); ++record)
	{
		if (record->getName() == name)
		{
			return &(*record);
		}
	}

	throw invalid_argument("No variable with the name " + name + " found for function " + this->name + ".");
}

string ProcedureRecord::getName() {
	return name;
}

string ProcedureRecord::getType() {
	return type;
}

vector<VariableRecord> ProcedureRecord::getParameters() {
	return parameters;
}

vector<VariableRecord> ProcedureRecord::getVariables() {
	return variables;
}
