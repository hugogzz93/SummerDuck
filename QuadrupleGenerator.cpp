#include "QuadrupleGenerator.h"

QuadrupleGenerator::QuadrupleGenerator(ProcedureDirectory* directory, ProcDirHandler* handler, DataHolder *data, Memory* memory): 
	directory(directory),  handler(handler), data(data), memory(memory) {}

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
			record.setType(SemanticCube::T_ENTERO);
			record.setValue(data->ival);
		} else if(flag == C_REAL) {
			record.setType(SemanticCube::T_REAL);
			record.setValue(data->fval);
		} else if(flag == C_CHAR){
			record.setType(SemanticCube::T_CHAR);
			record.setValue(data->sval);
		}
		record.setConstant(true);
		record.setVAddress(memory.saveConstant(record.setType(), *data))
		operandStack.push(record);
	}
}

void QuadrupleGenerator::pushOperator(int op) {
	operatorStack.push(op);
}

void QuadrupleGenerator::testForOperation(int type) {
	if ( !operatorStackLimit.empty() && operatorStackLimit[-1] == operatorStack.size() || operatorStack.size() < 2) { return ; }
	if (type == 1 && operatorStack.top() == Quadruple::I_SUMA || operatorStack.top() == Quadruple::I_RESTA 
													|| operatorStack.top() == Quadruple::I_OR) {
		executeOperation();
	} else if(type == 0 && operatorStack.top() == Quadruple::I_MULT || operatorStack.top() == Quadruple::I_DIV
													|| operatorStack.top() == Quadruple::I_AND) {
		executeOperation();
	}
}

void QuadrupleGenerator::executeOperation() {
	VariableRecord leftOperand, rightOperand;

	rightOperand = operandStack.top(); operandStack.pop();
	leftOperand = operandStack.top(); operandStack.pop();
	int op = operatorStack.top(); operatorStack.pop();
	int resultType = semanticCube.getResult(op, leftOperand.getType(), rightOperand.getType());
	if (resultType == -1) { ErrorHandler::invalidType(); }

	generateQuadruple(operatorStack.top(), leftOperand.getVAddress(), rightOperand.getVAddress(), memory->requestAvailMemory());
	operatorStack.pop();
}

void QuadrupleGenerator::generateQuadruple(int op, int lo, int ro, int res) {
	Quadruple instruction(op, lo, ro, res);
	// Quadruple instruction(op, lo, ro, res);
	ProcedureRecord* procedure = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = procedure->getQuadruples();
	quadruples->push_back(instruction);
	VariableRecord result;
	result.setVAddress(res);
	result.setConstant(true);
	operandStack.push(result);
}


void QuadrupleGenerator::addLimit() {
	operatorStackLimit.push_back(operatorStack.size());
}

void QuadrupleGenerator::removeLimit() {
	operatorStackLimit.pop_back();
}
