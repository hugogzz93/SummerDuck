#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(ProcedureDirectory* directory, Memory* memory): directory(directory), memory(memory) {
	// memory->allocateSpace(MEM_REQ);//allocate global space
	stackPointer = basePointer = globalLimit = MEM_REQ;

}

void VirtualMachine::run() {
	// printf("Starting Virtual Machine...\n");
	Quadruple instruction;
	procedure = directory->getFunctionByName("principal");

	vector<VariableRecord> funcVariables = *procedure->getVariables();
	for (int i = 0; i < funcVariables.size(); ++i) {
		memory->prepareBlocks(basePointer, funcVariables[i]);
	}

	instructionPointer = 0;
	stackPointer += MEM_REQ;
	while(!(procedure->getName() == "principal" && instructionPointer >= procedure->getQuadruples()->size())) {
		instruction = procedure->getQuadruples()->operator[](instructionPointer);
		// printf("Executing: %d of %s: %s\n", instructionPointer, procedure->getName().c_str(), Quadruple::asString(instruction.getOperation()).c_str());
		executeInstruction(instruction);
		instructionPointer++;
	}
	// printf("Finished Executing\n");
}

void VirtualMachine::era(int id) {
}

void VirtualMachine::param(int address) {
	parameters.push_back(address);
}

void VirtualMachine::callProcedure(int id, int retAddress) {
	callStack.push_back(directory->getIdentifier(procedure->getName()));
	procedure = directory->getProcedure(id);
	if (procedure->getName() == "lee") {
		for (int i = 0; i < parameters.size(); ++i) {
			MemoryBlock *block = memory->getBlock(basePointer, parameters[i]);
			// cout << *block << endl;
			cin >> *block;
		}
		parameters.clear();
		procedure = directory->getProcedure(callStack.back()); callStack.pop_back();
		return;
	} else if (procedure->getName() == "escribe") {
		for (int i = 0; i < parameters.size(); ++i) {
			MemoryBlock *block = memory->getBlock(basePointer, parameters[i]);
				switch(block->type) {
		    	case Quadruple::T_ENTERO:
		    		printf("%d", block->ival);
		    		break;
		    	case Quadruple::T_REAL:
		    		printf("%f", block->fval);
		    		break;
		    	case Quadruple::T_CHAR:
		    		printf("%s", block->sval.c_str());
		    		break;
		    	case Quadruple::T_BOOL:
		    		printf("%d", block->bval);
		    		break;
		    	case Quadruple::T_NULL:
		    		printf("null" );
		    		break;
		    	default:
		    		printf("invalid" );
		    }
		    if (i == parameters.size() - 1)
		    {
		    	printf("\n");
		    }
		}
		parameters.clear();
		procedure = directory->getProcedure(callStack.back()); callStack.pop_back();
		return;
	}
	
	int prevBasePointer = basePointer;
	basePointers.push_back(basePointer);
	basePointer = stackPointer;
	instructionPointers.push_back(instructionPointer);


	if (procedure->getType() != Quadruple::T_NULL) {
		retAddresses.push_back(retAddress);
	}
	stackPointer += MEM_REQ;

	vector<VariableRecord> funcParameters = *procedure->getParameters();
	vector<VariableRecord> funcVariables = *procedure->getVariables();
	if (funcParameters.size() != parameters.size()) {
		ErrorHandler::MissingArguments(procedure->getName(), parameters.size(), funcParameters.size());
	}

	// set type of variable in memory
	for (int i = 0; i < funcVariables.size(); ++i)
	{
		memory->prepareBlocks(basePointer, funcVariables[i]);
	}

	// set type of parameters in memory
	for (int i = 0; i < funcParameters.size(); ++i) {
		memory->prepareBlocks(basePointer, funcParameters[i]);
		memory->setMemory(prevBasePointer, parameters[i], basePointer, funcParameters[i].getVAddress());
	}

	parameters.clear();
	instructionPointer = -1;
}

void VirtualMachine::ret(Quadruple instruction) {
	int prevBasePointer = basePointers.back();
	if (procedure->getType() != Quadruple::T_NULL ) {
		memory->setMemory(basePointer, instruction.getResult(), prevBasePointer, retAddresses.back());
		retAddresses.pop_back();
	}

	//Recuerda limpiar el avail, la siguiente funcion va a tener el mismo basepointer
	memory->clearAvail(basePointer);
	stackPointer = basePointer;
	basePointer = basePointers.back();
	basePointers.pop_back();
	instructionPointer = instructionPointers.back();
	instructionPointers.pop_back();
	procedure = directory->getProcedure(callStack.back()); 
	callStack.pop_back();
}


void VirtualMachine::executeInstruction(Quadruple instruction) {
	switch(instruction.getOperation()) {
		case Quadruple::I_VER:
			ver(instruction);
			break;

		case Quadruple::I_INSERT_INT:
			insrt(instruction);
			break;

		case Quadruple::I_RET:
			ret(instruction);
			break;

		case Quadruple::I_GOTO:
			gotoJ(instruction);
			break;

		case Quadruple::I_GOTOF:
			gotoJ(instruction);
			break;

		case Quadruple::I_GOTOV:
			gotoJ(instruction);
			break;

		case Quadruple::I_GOSUB:
			callProcedure(instruction.getLeftOperand(), instruction.getResult());
			break;

		case Quadruple::I_ERA:
			era(instruction.getLeftOperand());
			break;

		case Quadruple::I_AND:
			arithmetic(instruction, instruction.getOperation());
			break;

		case Quadruple::I_OR:
			arithmetic(instruction, instruction.getOperation());
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
		 	arithmetic(instruction, instruction.getOperation());
		 	break;

	    case Quadruple::I_MENOR_IGUAL_QUE:
	    	arithmetic(instruction, instruction.getOperation());
	    	break;

	    case Quadruple::I_NO_IGUAL:
	    	arithmetic(instruction, instruction.getOperation());
	    	break;

	    case Quadruple::I_IGUAL:
	    	arithmetic(instruction, instruction.getOperation());
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

void VirtualMachine::gotoJ(Quadruple instruction) {
	MemoryBlock* condition;
	
	if (instruction.getOperation() ==  Quadruple::I_GOTOV) {
		condition = memory->getBlock(basePointer, instruction.getLeftOperand());
		// cout << "GOTOV checking: ";
		// cout << *condition;
		if (condition->type != Quadruple::T_BOOL) { ErrorHandler::invalidType(); }
		if (condition->bval) { instructionPointer = instruction.getResult() - 1; }
	} else if (instruction.getOperation() == Quadruple::I_GOTOF) {
		condition = memory->getBlock(basePointer, instruction.getLeftOperand());
		// cout << "GOTOF checking: " << *condition << endl;
		if (condition->type != Quadruple::T_BOOL) { ErrorHandler::invalidType(); }
		if (!condition->bval) { instructionPointer = instruction.getResult() - 1; }
	} else if (instruction.getOperation() == Quadruple::I_GOTO) { 
		instructionPointer = instruction.getResult() - 1;
	}
}

void VirtualMachine::arithmetic(Quadruple instruction, int operation) {
	MemoryBlock* lBlock, *rBlock, result;
	lBlock = memory->getBlock(basePointer, instruction.getLeftOperand());
	rBlock = memory->getBlock(basePointer, instruction.getRightOperand());
	if (operation ==  Quadruple::I_SUMA) {
		result = *lBlock + *rBlock;
		// cout << result << " = " << *lBlock << " + " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_RESTA) {
		result = *lBlock - *rBlock;
		// cout << result << " = " << *lBlock << " - " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_MULT) {
		result = *lBlock * *rBlock;
		// cout << result << " = " << *lBlock << " (" << instruction.getLeftOperand() << ") "<< " * " << *rBlock << " (" << instruction.getRightOperand() << ") "<< endl;
	} else if (operation ==  Quadruple::I_DIV) {
		result = *lBlock / *rBlock;
		// cout << result << " = " << *lBlock << " / " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_MAYOR_QUE) {
		result = *lBlock > *rBlock;
		// cout << result << " = " << *lBlock << " > " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_MENOR_QUE) {
		result = *lBlock < *rBlock;
		// cout << result << " = " << *lBlock << " < " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_MENOR_IGUAL_QUE) {
		result = *lBlock <= *rBlock;
		// cout << result << " = " << *lBlock << " <= " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_MAYOR_IGUAL_QUE) {
		result = *lBlock >= *rBlock;
		// cout << result << " = " << *lBlock << " >= " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_NO_IGUAL) {
		result = *lBlock != *rBlock;
		// cout << result << " = " << *lBlock << " != " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_IGUAL) {
		result = *lBlock == *rBlock;
		// cout << result << " = " << *lBlock << " == " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_OR) {
		result = *lBlock || *rBlock;
		// cout << result << " = " << *lBlock << " || " << *rBlock << endl;
	} else if (operation ==  Quadruple::I_AND) {
		result = *lBlock && *rBlock;
		// cout << result << " = " << *lBlock << " && " << *rBlock << endl;
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


void VirtualMachine::ver(Quadruple instruction) {
	MemoryBlock* block = memory->getBlock(basePointer, instruction.getLeftOperand());
	// printf("verifying that %d < %d\n", block->ival, instruction.getRightOperand());
	if (block->type != Quadruple::T_ENTERO && block->type != Quadruple::T_REAL)
	{
		printf("on VER instruction ");
		ErrorHandler::invalidType();
	}
	if (block->type == Quadruple::T_ENTERO && block->ival >= instruction.getRightOperand() || block->fval >= instruction.getRightOperand()) {
		// printf("%d >= %f = %d\n", block->ival, instruction.getRightOperand(), block->ival >= instruction.getRightOperand());
		printf("on VER instruction ");
		ErrorHandler::invalidAccess("Accesso fuera de limites");
	}
}

void VirtualMachine::insrt(Quadruple instruction) {
	MemoryBlock data;
	data.type = Quadruple::T_ENTERO;
	data.ival = instruction.getLeftOperand();
	memory->setMemory(basePointer, instruction.getResult(), data);
}
