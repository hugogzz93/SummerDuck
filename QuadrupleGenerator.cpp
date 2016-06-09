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
			record.setType(Quadruple::T_ENTERO);
			record.setValue(data->ival);
		} else if(flag == C_REAL) {
			record.setType(Quadruple::T_REAL);
			record.setValue(data->fval);
		} else if(flag == C_CHAR){
			record.setType(Quadruple::T_CHAR);
			record.setValue(data->sval);
		}
		record.setConstant(true);
		record.setVAddress(memory->saveConstant(record.getType(), *data));
		operandStack.push(record);
	} else {
		// pending implementatino so just pushing stub to stack
		VariableRecord record;
		record.setType(Quadruple::T_ENTERO);
		record.setConstant(true);
		record.setVAddress(-1);
		operandStack.push(record);
	}
}

void QuadrupleGenerator::pushOperator(int op) {
	operatorStack.push(op);
}

void QuadrupleGenerator::testForOperation(int type) {
	if ( operatorStack.empty() || operatorStack.top() == Quadruple::I_LIMIT || operandStack.size() < 2 || operatorStack.empty()) { return ; }
	if(type == 0 && operatorStack.top() == Quadruple::I_MULT || operatorStack.top() == Quadruple::I_DIV ) {
		executeOperation();
	} else if(type == 1 && operatorStack.top() == Quadruple::I_RESTA || operatorStack.top() == Quadruple::I_SUMA) {
		executeOperation();
	} else if(type == 2 && operatorStack.top() == Quadruple::I_MENOR_QUE || operatorStack.top() == Quadruple::I_MAYOR_QUE) {
		executeOperation();
	} else if(type == 3 && operatorStack.top() == Quadruple::I_IGUAL || operatorStack.top() == Quadruple::I_NO_IGUAL) {
		executeOperation();
	} else if(type == 4 && operatorStack.top() == Quadruple::I_AND) {
		executeOperation();
	} else if(type == 5 && operatorStack.top() == Quadruple::I_OR) {
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

	int res = memory->requestAvailMemory();
	generateQuadruple(op, leftOperand.getVAddress(), rightOperand.getVAddress(), res);

	VariableRecord result;
	result.setVAddress(res);
	result.setConstant(true);
	operandStack.push(result);
}

void QuadrupleGenerator::generateQuadruple(int op, int lo, int ro, int res) {
	Quadruple instruction(op, lo, ro, res);
	ProcedureRecord* procedure = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = procedure->getQuadruples();
	quadruples->push_back(instruction);
}


void QuadrupleGenerator::addLimit() {
	operatorStack.push(Quadruple::I_LIMIT);
}

void QuadrupleGenerator::removeLimit() {
	if (operatorStack.top() == Quadruple::I_LIMIT)
	{
		operatorStack.pop();
	} else {
		ErrorHandler::badSyntax("Missing left parenthesis");
	}
}


void QuadrupleGenerator::loadFunction(string id) {
	int index = directory->getIdentifier(id);
	if (index == -1) { ErrorHandler::unidentifiedProcedure(id); }
	generateQuadruple(Quadruple::I_ERA, index, 0, 0);
}