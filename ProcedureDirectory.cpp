#include "ProcedureDirectory.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>

	ProcedureDirectory::ProcedureDirectory() {}


	void ProcedureDirectory::listDirectory(bool verbose) {
		ProcedureRecord record;
		
		for (std::vector<ProcedureRecord>::iterator functionRecord = procedures.begin(); 
										functionRecord != procedures.end(); ++functionRecord) {
			functionRecord->showSignature(verbose);
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

	ProcedureRecord* ProcedureDirectory::getGlobalRecord() {
		return &procedures[0];
	}