#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(ProcedureDirectory* directory, Memory* memory): directory(directory), memory(memory) {
	memory->allocateSpace(MEM_REQ);//allocate global space
	prevBasePointer = stackPointer = basePointer = globalLimit = MEM_REQ;

}

void VirtualMachine::run() {

}

void VirtualMachine::era(int id) {
	procedure = directory->getProcedure(id);
}

void VirtualMachine::param(int address) {
	parameters.push_back(address);
}

void VirtualMachine::callProcedure(int id) {
	prevBasePointer = basePointer;
	basePointer = stackPointer;
	prevInstructionPointer = instructionPointer;
	if (stackPointer + MEM_REQ > memory->getMemory()->size()) {
		memory->allocateSpace(MEM_REQ);
		stackPointer = memory->getMemory()->size();
	} else {
		stackPointer += MEM_REQ;
	}

	vector<VariableRecord> funcParameters = *procedure->getParameters();
	if (funcParameters.size() != parameters.size()) {
		ErrorHandler::MissingArguments(procedure->getName());
	}

	for (int i = 0; i < funcParameters.size(); ++i) {
		memory->setMemory(prevBasePointer, parameters[i], basePointer, funcParameters[i].getVAddress());
	}
}

void VirtualMachine::ret() {
// !!!!! Recuerda limpiar el avail, la siguiente funcion va a tener el mismo basepointer

	memory->clearAvail(basePointer);
	stackPointer = basePointer;
	basePointer = prevBasePointer;
	instructionPointer = prevInstructionPointer;
}


void VirtualMachine::executeInstruction(Quadruple instruction) {
	printf("@@@@@ %s\n", Quadruple::asString(instruction.getOperation()).c_str());
	switch(instruction.getOperation()) {
		case Quadruple::I_WRITE:
			
			break;

		case Quadruple::I_READ:
			
			break;

		case Quadruple::I_VER:
			
			break;

		case Quadruple::I_CALL:
			
			break;

		case Quadruple::I_RET:
			ret();
			break;

		case Quadruple::I_GOTO:
			
			break;

		case Quadruple::I_GOTOF:
			
			break;

		case Quadruple::I_GOTOV:
			
			break;

		case Quadruple::I_GOSUB:
			break;

		case Quadruple::I_ERA:
			era(instruction.getLeftOperand());
			break;

		case Quadruple::I_AND:
			
			break;

		case Quadruple::I_OR:
			
			break;

		case Quadruple::I_SUMA:
			arithmetic(instruction, instruction.getOperation());
			break;

		case Quadruple::I_RESTA:
			arithmetic(instruction, instruction.getOperation());
			break;

		case Quadruple::I_MULT:
			arithmetic(instruction, instruction.getOperation());
			break;

		case Quadruple::I_DIV:
			arithmetic(instruction, instruction.getOperation());
			break;

		case Quadruple::I_MAYOR_QUE:
			arithmetic(instruction, instruction.getOperation());
			break;

	    case Quadruple::I_MENOR_QUE:
	    	arithmetic(instruction, instruction.getOperation());
	    	break;

		 case Quadruple::I_MAYOR_IGUAL_QUE:
		 	
		 	break;

	    case Quadruple::I_MENOR_IGUAL_QUE:
	    	
	    	break;

	    case Quadruple::I_NO_IGUAL:
	    	
	    	break;

	    case Quadruple::I_IGUAL:
	    	
	    	break;

	    case Quadruple::I_ASIGN:
	    	memory->setMemory(basePointer, instruction.getLeftOperand(), instruction.getResult());
	    	break;

	    case Quadruple::I_DETERMINANTE:
	    	
	    	break;

	    case Quadruple::I_INVERSA:
	    	
	    	break;

	    case Quadruple::I_PARAM:
	    	param(instruction.getLeftOperand());
	    	break;

	    default:
		ErrorHandler::InvalidInstruction(instruction.getOperation());
	}

}



//instruction handlers

void VirtualMachine::arithmetic(Quadruple instruction, int operation) {
	MemoryBlock* lBlock, *rBlock, result;
	lBlock = memory->getBlock(basePointer, instruction.getLeftOperand());
	rBlock = memory->getBlock(basePointer, instruction.getRightOperand());
	if (operation =  Quadruple::I_SUMA) {
		result = *lBlock + *rBlock;
	} else if (operation =  Quadruple::I_RESTA) {
		result = *lBlock - *rBlock;
	} else if (operation =  Quadruple::I_MULT) {
		result = *lBlock * *rBlock;
	} else if (operation =  Quadruple::I_DIV) {
		result = *lBlock / *rBlock;
	} else if (operation =  Quadruple::I_MAYOR_QUE) {
		result = *lBlock > *rBlock;
	} else if (operation =  Quadruple::I_MENOR_QUE) {
		result = *lBlock < *rBlock;
	}
	memory->setMemory(basePointer, instruction.getResult(), result);
	
}
// void VirtualMachine::assignMemory(Quadruple instruction) {

// }

// void Memory::dataToMemory(VariableRecord record) {
// 	MemoryBlock block;
// 	if (record.getType() == T_ENTERO) {
// 		block.ival = record.getDa
// 	} else if (record.getType() == T_REAL) {
// 		/* code */
// 	} else if (record.getType() == T_CHAR) {
// 		/* code */
// 	} else if (record.getType() == T_BOOL) {
// 		/* code */
// 	} else if (record.getType() == T_NULL || record.getType() == T_INVALID) {
// 		ErrorHandler::invalidType();
// 	}
// }