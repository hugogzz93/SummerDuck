#include "ProcedureDirectory.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>

	ProcedureDirectory::ProcedureDirectory() {
		// unordered_map<string, unordered_map<string, int>> map;
		// vAddressMap = map;
		// addFunction("int", "main");
		// scope = true;
	}

	// void ProcedureDirectory::enterLocalScope() {
	// 	scope = false;
	// }

	// void ProcedureDirectory::enterGlobalScope() {
	// 	scope = true; 
	// }

	// void ProcedureDirectory::addFunction(string type, string name) {

	// 	ProcedureRecord newRecord(type, name, parameterDir, variableDir);
	// 	procedures.push_back(newRecord);

		
	// 	parameterDir.clear();
	// 	variableDir.clear();
	// }

	// void ProcedureDirectory::addParameter(string type, string name) {
	// 	VariableRecord newRecord(type, name);
	// 	newRecord.setScope(getCurrentScope());
	// 	assignVirtualAddress(newRecord);
	// 	parameterDir.push_back(newRecord); 
	// }

	// void ProcedureDirectory::addVariable(string type, string name) {
	// 	if (this->scope)
	// 	{
	// 		int vAddress = getVAddress("main", type);
	// 		procedures.front().addVariable(type, name, vAddress, "main");
	// 	} else {
	// 		VariableRecord newRecord(type, name);
	// 		newRecord.setScope(getCurrentScope());
	// 		assignVirtualAddress(newRecord);
	// 		variableDir.push_back(newRecord);
	// 	}
	// }

	// VariableRecord ProcedureDirectory::addVariableRecord(VariableRecord record) {
	// 	assignVirtualAddress(record);
		
	// 	if (scope) {
	// 		procedures.front().addVariable(record);
			
	// 	} else {
	// 		variableDir.push_back(record);
	// 	}

	// 	return record;
	// }

	void ProcedureDirectory::listDirectory(bool verbose) {
		ProcedureRecord record;
		// vector<Quadruple> functionQuadruples;
		
		for (std::vector<ProcedureRecord>::iterator functionRecord = procedures.begin(); 
										functionRecord != procedures.end(); ++functionRecord)
		{
			functionRecord->showSignature(verbose);
			// cout << "Instructions: " << endl;
			// functionQuadruples = quadrupleMap[functionRecord->getName()];
			// int index = 0;
			// for (std::vector<Quadruple>::iterator quadruple = functionQuadruples.begin(); quadruple != functionQuadruples.end(); ++quadruple)
			// {
			// 	cout << index++ << ": " << *quadruple << endl;
			// }
			// cout << endl;
		}
	}

	void ProcedureDirectory::addRecord(ProcedureRecord record) {
		// check for redefinition
		try {
			ProcedureRecord oldRecord = *getFunctionByName(record.getName());
			ErrorHandler::moduleRedefinition(record.getName());
		} catch(exception e) {}

		procedures.push_back(record);
	}


	// void ProcedureDirectory::assignVirtualAddresses(vector<VariableRecord> &vec, string name) {
	// 	int vAddress;

	// 	for (std::vector<VariableRecord>::iterator varRecord = vec.begin(); varRecord != vec.end(); ++varRecord)
	// 	{
	// 		// vAddress = vAddressMap[name][varRecord->getType()]++;
	// 		vAddress = getVAddress(name, varRecord->getType());
	// 		varRecord->setVAddress(vAddress);
	// 		varRecord->setScope(name);	
	// 	}
	// }

	// void ProcedureDirectory::assignVirtualAddress(VariableRecord& record) {
	// 	string scopeName = scope? "main":"local";
	// 	// int vAddress = vAddressMap[record.getScope()][record.getType()]++;
	// 	int vAddress = getVAddress(record.getScope(), record.getType());
	// 	record.setVAddress(vAddress);

	// }

	VariableRecord* ProcedureDirectory::getVariableByName(string name, string scope) {
			ProcedureRecord *function = getFunctionByName(scope);
			VariableRecord *varRecord = function->getVariableByName(name);
			return varRecord;
	}

	// void ProcedureDirectory::addQuadruple(const Quadruple& quad, string scope) {
	// 	quadrupleMap[scope].push_back(quad);
	// }

	// int ProcedureDirectory::getCurrentInstructionIndex(string scope) {
	// 	return quadrupleMap[scope].size();
	// }

	// VariableRecord* ProcedureDirectory::getVariableForFutureFunc(string name) {

	// 	if (scope)
	// 	{
	// 		VariableRecord *record =  procedures.front().getVariableByName(name);
	// 		return record;

	// 	}
	// 	for (std::vector<VariableRecord>::iterator record = variableDir.begin(); record != variableDir.end(); ++record)
	// 	{	
	// 		if (record->getName() == name)
	// 		{
	// 			return &(*record);
	// 		}
	// 	}
	// 	for (std::vector<VariableRecord>::iterator record = parameterDir.begin(); record != parameterDir.end(); ++record)
	// 	{	
	// 		if (record->getName() == name)
	// 		{
	// 			return &(*record);
	// 		}
	// 	}

	// 	throw invalid_argument("Variable " + name + " not found ProcedureDirectory::getVariableForFutureFunc - ");
	// }

	// VariableRecord* ProcedureDirectory::getParameterForFutureFunc(string name) {
	// 	for (std::vector<VariableRecord>::iterator record = parameterDir.begin(); record != parameterDir.end(); ++record)
	// 	{
	// 		if (record->getName() == name)
	// 		{
	// 			return &(*record);
	// 		}
	// 	}

	// 	throw invalid_argument("Variable" + name + " not found");

	// }

	ProcedureRecord* ProcedureDirectory::getFunctionByName(string name) {
		for (std::vector<ProcedureRecord>::iterator function = procedures.begin(); function != procedures.end(); ++function)
		{
			if (function->getName() == name)
			{
				return &(*function);
			}
		}

		throw invalid_argument("Function " + name + " not found");
	}

	// vector<VariableRecord>& ProcedureDirectory::getVariableDir() {
	// 	return variableDir;
	// }

	// vector<VariableRecord>& ProcedureDirectory::getParameterDir() {
	// 	return parameterDir;
	// }

	// int ProcedureDirectory::getVAddress(string scope, string type) {
	// 	unordered_map<string, unordered_map<string, int>>::const_iterator got = vAddressMap.find(scope);
	// 	if (got == vAddressMap.end())
	// 	{
	// 		vAddressMap[scope] = { {"INT", 0}, {"FLOAT", 1000}, {"STRING", 2000}, {"BOOL", 3000} };
	// 	}
	// 	int vAddress = vAddressMap[scope][type]++;	
	// 	return vAddress;
	// }

	// int ProcedureDirectory::getReturnType(string functionName) {
	// 	getFunctionByName(functionName)->getType();
	// }

	// void  ProcedureDirectory::updateVariableRecord(VariableRecord& record) {
	// 	bool found = false;
	// 	if (scope)
	// 	{
	// 		found = true;
	// 		record = *getVariableByName(record.getName(), "main");
	// 	} else {
	// 		found = true;
	// 		record = *getVariableForFutureFunc(record.getName());
	// 	}

	// 	if (!found)
	// 	{
	// 		throw invalid_argument("Variable " + record.getName() + " could not be updated, not found\n");
	// 	}
	// }


	// void ProcedureDirectory::setCurrentScope(string name) {
	// 	currentScopeName = name;
	// }

	// string ProcedureDirectory::getCurrentScope() {
	// 	return currentScopeName;
	// }

	// Quadruple* ProcedureDirectory::getInsAtIndex(string scope, int index) {
	// 	return &quadrupleMap[scope][index];
	// }

	// void ProcedureDirectory::setReturnTypeFlag(int retType) {
	// 	returnTypeFlag = retType;
	// }
	// int ProcedureDirectory::getReturnTypeFlag() {
	// 	return returnTypeFlag;
	// }

	// vector<VariableRecord> ProcedureDirectory::getParameterDirFor(string id) {
	// 	ProcedureRecord *functionRecord = getFunctionByName(id);
	// 	return functionRecord->getParameterDir();
	// }