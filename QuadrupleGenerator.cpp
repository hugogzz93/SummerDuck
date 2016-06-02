#include "QuadrupleGenerator.h"

QuadrupleGenerator::QuadrupleGenerator(ProcedureDirectory* directory, ProcDirHandler* handler, DataHolder *data): 
	directory(directory),  handler(handler), data(data) {}

void QuadrupleGenerator::setFlag(int flag) {
	this->flag = flag;
}

void QuadrupleGenerator::pushOperand() {
	// VariableRecord operand;
	if (flag == C_ID) {
		string id(data->sval);
		ProcedureRecord* procedure = handler->getRecord(handler->getScope());
		VariableRecord *record, arrayAccessRecord;
		
		try {
			record = procedure->getVariableByName(id);
		} catch(...) { 
			procedure = directory->getGlobalRecord();
			record = procedure->getVariableByName(id);
		}

		if (data->dimensions >= 1) {
			arrayAccessRecord = *record;
			arrayAccessRecord.setVAddress(arrayAccessRecord.arrayAccess(data->sizes));
			operandStack.push(arrayAccessRecord);
		} else {
			operandStack.push(*record);
		}
	} else if (flag != C_FUNC_CALL) {
		VariableRecord record;
		if (flag == C_ENTERO) {
			record.setType(VariableRecord::T_ENTERO);
			record.setValue(data->ival);
		} else if(flag == C_REAL) {
			record.setType(VariableRecord::T_REAL);
			record.setValue(data->fval);
		} else {
			record.setType(VariableRecord::T_CHAR);
			record.setValue(data->sval);
		}
		record.setConstant(true);
		operandStack.push(record);
	}


}


