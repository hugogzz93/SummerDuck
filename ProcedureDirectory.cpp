#include "ProcedureDirectory.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>

	ProcedureDirectory::ProcedureDirectory() {}


	void ProcedureDirectory::listDirectory(bool verbose) {
		printf("Function Identifiers\n");
		for(auto kv : identifiers) {
		    printf("\t%d: %s\n",kv.second, kv.first.c_str());
		}

		for (std::vector<ProcedureRecord>::iterator functionRecord = procedures.begin(); 
										functionRecord != procedures.end(); ++functionRecord) {
			functionRecord->showSignature(verbose);
		}
	}

	void ProcedureDirectory::listInstructions() {
		for (std::vector<ProcedureRecord>::iterator functionRecord = procedures.begin(); 
										functionRecord != procedures.end(); ++functionRecord) {
			functionRecord->showInstructions();
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


	VariableRecord* ProcedureDirectory::getVariableByName(string name, string scope) {
			ProcedureRecord *function = getFunctionByName(scope);
			VariableRecord *record;
			try {
				record = function->getVariableByName(name);
			} catch(...) {
				function = getGlobalRecord();
				record = function->getVariableByName(name);
			}
			return record;
	}

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

	ProcedureRecord* ProcedureDirectory::getProcedure(int id) {
		for(auto kv : identifiers) {
			if (kv.second == id)
				return getFunctionByName(kv.first);
		}
		ErrorHandler::unidentifiedProcedure(id);
	}

	ProcedureRecord* ProcedureDirectory::getGlobalRecord() {
		return &procedures[0];
	}

	int ProcedureDirectory::getIdentifier(string id) {
		if (identifiers.find(id) == identifiers.end()) { identifiers[id] = identifiersIndex++; }
		return identifiers[id];
	}