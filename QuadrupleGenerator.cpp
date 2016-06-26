#include "QuadrupleGenerator.h"

QuadrupleGenerator::QuadrupleGenerator(ProcedureDirectory* directory, ProcDirHandler* handler, DataHolder *data, Memory* memory): 
	directory(directory),  handler(handler), data(data), memory(memory) {}

void QuadrupleGenerator::setFlag(int flag) {
	this->flag = flag;
}

void QuadrupleGenerator::pushOperand() {
	// VariableRecord operand;
	ProcedureRecord* procedure = handler->getRecord(handler->getScope());
	if (flag == C_ID) {
		string id(data->sval);
		VariableRecord *record;
		try {
			record = procedure->getVariableByName(id);
		} catch(...) { 
			procedure = directory->getGlobalRecord();
			record = procedure->getVariableByName(id);
		}

		if (data->dimensions >= 1) {
			VariableRecord arrayAccessRecord = arrayAccess(record, data->dimensions);
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
	} else if(type == 2 && operatorStack.top() == Quadruple::I_MENOR_QUE ||operatorStack.top() == Quadruple::I_MENOR_IGUAL_QUE ||
				 operatorStack.top() == Quadruple::I_MAYOR_QUE || operatorStack.top() == Quadruple::I_MAYOR_IGUAL_QUE) {
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
	if (operatorStack.top() == Quadruple::I_LIMIT) {
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

void QuadrupleGenerator::setParameter() {
	VariableRecord parameter = operandStack.top(); operandStack.pop();
	generateQuadruple(Quadruple::I_PARAM, parameter.getVAddress(), 0, 0);
}

void QuadrupleGenerator::gosub(string id) {
	int index = directory->getIdentifier(id);
	if (index == -1) { ErrorHandler::unidentifiedProcedure(id); }
	ProcedureRecord* procedure = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = procedure->getQuadruples();

	VariableRecord record;
	record.setType(procedure->getType());
	record.setVAddress(memory->requestAvailMemory());
	operandStack.push(record);

	generateQuadruple(Quadruple::I_GOSUB, index, 0, record.getVAddress());
}

void QuadrupleGenerator::setGotoF() {
	ProcedureRecord* record = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = record->getQuadruples();
	VariableRecord condition = operandStack.top(); operandStack.pop();
	generateQuadruple(Quadruple::I_GOTOF, condition.getVAddress(), 0, -1);
	jumpStack.push(quadruples->size() - 1);
}

void QuadrupleGenerator::completeGoto() {
	ProcedureRecord* record = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = record->getQuadruples();
	int instructionIndex = jumpStack.top(); jumpStack.pop();
	Quadruple jump = (*quadruples)[instructionIndex];
	jump.setResult(quadruples->size());
	(*quadruples)[instructionIndex] = jump;

}

void QuadrupleGenerator::ifElse() {
	ProcedureRecord* record = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = record->getQuadruples();
	generateQuadruple(Quadruple::I_GOTO, 0,0,-1);
	
	// completa el GotoF inicial del if
	int instructionIndex = jumpStack.top(); jumpStack.pop();
	Quadruple jump = (*quadruples)[instructionIndex];
	jump.setResult(quadruples->size());
	(*quadruples)[instructionIndex] = jump;

	// push new goto to jumpstack
	jumpStack.push(quadruples->size() - 1);
}

void QuadrupleGenerator::startWhile() {
	ProcedureRecord* record = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = record->getQuadruples();
	jumpStack.push(quadruples->size());
}

void QuadrupleGenerator::endWhile() {
	ProcedureRecord* record = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = record->getQuadruples();
	int gotoFJump = jumpStack.top(); jumpStack.pop();
	
	generateQuadruple(Quadruple::I_GOTO,0,0,jumpStack.top());
	jumpStack.pop();

	Quadruple jump = (*quadruples)[gotoFJump];
	jump.setResult(quadruples->size());
	(*quadruples)[gotoFJump] = jump;
}

void QuadrupleGenerator::setGotoV() {
	ProcedureRecord* record = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = record->getQuadruples();
	VariableRecord condition = operandStack.top(); operandStack.pop();
	generateQuadruple(Quadruple::I_GOTOV, condition.getVAddress(), 0, jumpStack.top());
	jumpStack.pop();
}

void QuadrupleGenerator::doWhile() {
	ProcedureRecord* record = handler->getRecord(ProcDirHandler::LOCAL);
	vector<Quadruple>* quadruples = record->getQuadruples();
	jumpStack.push(quadruples->size());
}

void QuadrupleGenerator::assignment() {
	// VariableRecord variable = handler->getVariable(data->sval), arrayAccessRecord;
	// VariableRecord operand = operandStack.top(); operandStack.pop();

	// VariableRecord result = arrayAccess(&variable, data->dimensions);

	VariableRecord assigner, assignee;
	assigner = operandStack.top(); operandStack.pop();
	assignee = operandStack.top(); operandStack.pop();

// ///////
	// if (data->dimensions >= 1) {
	// 	// printf("[%d][%d]\n", data->sizes[0], data->sizes[1]);
	// 	variable.setVAddress(variable.arrayAccess(data->sizes) + variable.getVAddress());
	// 	// printf("address for %s is %d\n", variable.getName().c_str(), variable.getVAddress());
	// }
// ///////
	generateQuadruple(Quadruple::I_ASIGN, assigner.getVAddress(), 0, assignee.getVAddress() );
}

void QuadrupleGenerator::ret() {
	ProcedureRecord* procedure = handler->getRecord(handler->getScope());
	if (procedure->getType() != Quadruple::T_NULL) {
		VariableRecord record = operandStack.top(); operandStack.pop();
		generateQuadruple(Quadruple::I_RET, 0,0,record.getVAddress());
	} else {
		generateQuadruple(Quadruple::I_RET, 0,0,0);
	}
}

VariableRecord QuadrupleGenerator::arrayAccess(VariableRecord* record, int dimensions) {
	VariableRecord arrayAccessRecord;
	if (dimensions == 1) {
		VariableRecord dimOneAccess = operandStack.top(); operandStack.pop();
		VariableRecord targetAddressContainer;

		generateQuadruple(Quadruple::I_VER, dimOneAccess.getVAddress(),record->sizes[0],-1);
			
		targetAddressContainer.setVAddress(memory->requestAvailMemory());
		targetAddressContainer.setConstant(true);
		targetAddressContainer.setType(Quadruple::T_ENTERO);
		targetAddressContainer.setValue(record->getVAddress());
		generateQuadruple(Quadruple::I_INSERT_INT, record->getVAddress(), 0, targetAddressContainer.getVAddress());

		arrayAccessRecord.setVAddress(memory->requestAvailMemory());
		arrayAccessRecord.setConstant(true);
		generateQuadruple(Quadruple::I_SUMA, dimOneAccess.getVAddress(), targetAddressContainer.getVAddress(), arrayAccessRecord.getVAddress());
		int resultAddress = arrayAccessRecord.getVAddress();
		arrayAccessRecord.setVAddress((-1 * arrayAccessRecord.getVAddress()) + POINTER_OFFSET);
	} else if(dimensions == 2 ){
		VariableRecord dimTwoAccess = operandStack.top(); operandStack.pop();
		VariableRecord dimOneAccess = operandStack.top(); operandStack.pop();
		VariableRecord targetDOneAddressContainer, targetDTwoAddressContainer, targetAddressContainer, dimOneMult;
		generateQuadruple(Quadruple::I_VER, dimOneAccess.getVAddress(),record->sizes[0],-1);
		generateQuadruple(Quadruple::I_VER, dimTwoAccess.getVAddress(),record->sizes[1],-1);
			
		targetAddressContainer.setVAddress(memory->requestAvailMemory());
		targetAddressContainer.setConstant(true);
		targetAddressContainer.setType(Quadruple::T_ENTERO);
		targetAddressContainer.setValue(record->getVAddress());
		generateQuadruple(Quadruple::I_INSERT_INT, record->getVAddress(), 0, targetAddressContainer.getVAddress());

		targetDOneAddressContainer.setVAddress(memory->requestAvailMemory());
		targetDOneAddressContainer.setType(Quadruple::T_ENTERO);
		dimOneMult.setVAddress(memory->requestAvailMemory());
		dimOneMult.setType(Quadruple::T_ENTERO);
		generateQuadruple(Quadruple::I_INSERT_INT, record->sizes[1], 0, dimOneMult.getVAddress());

		generateQuadruple(Quadruple::I_MULT, dimOneMult.getVAddress(), dimOneAccess.getVAddress(), targetDOneAddressContainer.getVAddress());

		targetDTwoAddressContainer.setVAddress(memory->requestAvailMemory());
		targetDTwoAddressContainer.setConstant(true);
		targetDTwoAddressContainer.setType(Quadruple::T_ENTERO);
		generateQuadruple(Quadruple::I_SUMA, targetDOneAddressContainer.getVAddress(), dimTwoAccess.getVAddress(), targetDTwoAddressContainer.getVAddress());
		
		arrayAccessRecord.setVAddress(memory->requestAvailMemory());
		arrayAccessRecord.setConstant(true);
		generateQuadruple(Quadruple::I_SUMA, targetDTwoAddressContainer.getVAddress(), targetAddressContainer.getVAddress(), arrayAccessRecord.getVAddress());
		arrayAccessRecord.setVAddress((-1 * arrayAccessRecord.getVAddress()) + POINTER_OFFSET);
	} 
	return arrayAccessRecord;
}