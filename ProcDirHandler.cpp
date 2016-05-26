#include "ProcDirHandler.h"
#define ENTERO_MAX 1000
#define REAL_MAX 3000
#define CHAR_MAX 4000

ProcDirHandler::ProcDirHandler(ProcedureDirectory *directory) { 
	this->directory = directory;
	this->global = ProcedureRecord();
	this->local = ProcedureRecord();
	unordered_map<int, int> new_virtual_addresses = { 
		{ VariableRecord::T_ENTERO, 0 }, 
		{ VariableRecord::T_REAL, 1000 }, 
		{ VariableRecord::T_CHAR, 2000}
	};
	globalVariableIndex = new_virtual_addresses;
	localVariableIndex = new_virtual_addresses;
	setScope(GLOBAL);
}

void ProcDirHandler::setScope(int scope) {
	this->scope = scope;
	if (scope == GLOBAL) 
		cleanLocal();
}

void ProcDirHandler::setVariableType(int type) {
	this->variableType = type;
}

void ProcDirHandler::setReturnType(int type) {
	this->type = type;
}

void ProcDirHandler::addVariable(int context, string name, int dimensions, int sizes[]) {
	int virtualAddress = assignVirtualAddress(variableType, dimensions, sizes);
	VariableRecord record = VariableRecord(variableType, name, virtualAddress, this->name);
	ProcedureRecord* procedure = scope == GLOBAL ? &global : &local;
	if (context == PARAMETER) { procedure->addParameter(record); } 
	else { procedure->addVariable(record); }

}

void ProcDirHandler::cleanLocal() {
	parameters.clear();
	localVariableIndex = { 
		{ VariableRecord::T_ENTERO, 0 }, 
		{ VariableRecord::T_REAL, 1000 }, 
		{ VariableRecord::T_CHAR, 2000}
	};
}

int ProcDirHandler::assignVirtualAddress(int type, int dimensions, int sizes[]) {
	unordered_map<int, int> *virtualAddresses = scope == GLOBAL ? &globalVariableIndex : &localVariableIndex;

	int units = 1;
	for (int i = 0; i < dimensions; ++i) { units += sizes[i]; }

	int virtualAddress = (*virtualAddresses)[type];
	(*virtualAddresses)[type] += units;
	int MEM_MAX = type == VariableRecord::T_ENTERO ? ENTERO_MAX : type == VariableRecord::T_REAL ? REAL_MAX : CHAR_MAX ;
	if ((*virtualAddresses)[type] >= MEM_MAX) { ErrorHandler::memoryLimitExceeded(); }
	return virtualAddress;
}
