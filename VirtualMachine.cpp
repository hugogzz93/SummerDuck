#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(ProcedureDirectory* directory, Memory* memory): directory(directory), memory(memory) {
	memory->allocateSpace(MEM_REQ);//allocate global space
	globalLimit = MEM_REQ;
}

void VirtualMachine::callProcedure(int id) {
	basePointer = memory->getMemory()->size();
	ProcedureRecord* record = directory->getProcedure(id);
	memory->allocateSpace(MEM_REQ);
}


void VirtualMachine::executeInstruction(Quadruple instruction) {
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
			
			break;

		case Quadruple::I_AND:
			
			break;

		case Quadruple::I_OR:
			
			break;

		case Quadruple::I_SUMA:
			
			break;

		case Quadruple::I_RESTA:
			
			break;

		case Quadruple::I_MULT:
			
			break;

		case Quadruple::I_DIV:
			
			break;

		case Quadruple::I_MAYOR_QUE:
			
			break;

		 case Quadruple::I_MAYOR_IGUAL_QUE:
		 	
		 	break;

	    case Quadruple::I_MENOR_QUE:
	    	
	    	break;

	    case Quadruple::I_MENOR_IGUAL_QUE:
	    	
	    	break;

	    case Quadruple::I_NO_IGUAL:
	    	
	    	break;

	    case Quadruple::I_IGUAL:
	    	
	    	break;

	    case Quadruple::I_ASIGN:

	    	// memory->setMemory(instruction.getResult());
	    	break;

	    case Quadruple::I_DETERMINANTE:
	    	
	    	break;

	    case Quadruple::I_INVERSA:
	    	
	    	break;

	    case Quadruple::I_PARAM:
	    	
	    	break;

	    default:
		ErrorHandler::InvalidInstruction(instruction.getOperation());
	}

}



//instruction handlers
// void Memory::assignMemory(int address, VariableRecord record) {

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