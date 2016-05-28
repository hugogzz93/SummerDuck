#include "ProcDirHandler.h"
#define ENTERO_MAX 1000
#define REAL_MAX 3000
#define CHAR_MAX 4000

ProcDirHandler::ProcDirHandler(ProcedureDirectory *directory) { 
	this->directory = directory;
	this->global = ProcedureRecord("principal");
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

void ProcDirHandler::setName(string name) {
	ProcedureRecord* record = scope == GLOBAL ? &global : &local ;
	record->setName(name);
}

void ProcDirHandler::setScope(int scope) {
	this->scope = scope;
}

void ProcDirHandler::setVariableType(int type) {
	this->variableType = type;
}

void ProcDirHandler::setReturnType(int type) {
	ProcedureRecord* record = scope == GLOBAL ? &global : &local ;
	record->setType(type);
}

void ProcDirHandler::addVariable(int context, string name, int dimensions, int sizes[]) {
	ProcedureRecord* procedure = scope == GLOBAL ? &global : &local;

	int virtualAddress = assignVirtualAddress(variableType, dimensions, sizes);
	VariableRecord record(name, procedure->getName(), variableType, dimensions, virtualAddress, sizes);
	if (context == PARAMETER) { procedure->addParameter(record); } 
	else { procedure->addVariable(record); }
}

void ProcDirHandler::registerProcedure() {
	ProcedureRecord* record = scope == GLOBAL ? &global : &local ;

	directory->addRecord(*record);
	cleanLocal();
	local = ProcedureRecord();
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

	int units;
	if(dimensions == 0) {
		units = 1;
	} else if (dimensions == 1) {
		units = sizes[0];
	} else {
		units = sizes[0]*sizes[1];
	}
	// for (int i = 0; i < dimensions; ++i) { units += }
	// int units = dimensions == 0 ? 1 : 0;


	int virtualAddress = (*virtualAddresses)[type];
	(*virtualAddresses)[type] += units;
	int MEM_MAX = type == VariableRecord::T_ENTERO ? ENTERO_MAX : type == VariableRecord::T_REAL ? REAL_MAX : CHAR_MAX ;
	if ((*virtualAddresses)[type] >= MEM_MAX) { ErrorHandler::memoryLimitExceeded(); }
	return virtualAddress;
}
