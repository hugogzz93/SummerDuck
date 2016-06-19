#include "Memory.h"
#define AVAIL_OFFSET 10

int Memory::getInt(int address) {
	return memory[address].ival;
}

double Memory::getDouble(int address) {
	return memory[address].fval;
}

string Memory::getChar(int address) {
	return memory[address].sval;
}

bool Memory::getBool(int address) {
	return memory[address].bval;
}

int Memory::requestAvailMemory() {
	MemoryBlock block;
	avail.push_back(block);
	return -1 * (AVAIL_OFFSET + avail.size());
}

int Memory::saveConstant(int type, DataHolder data) {
	MemoryBlock block;
	if(type == Quadruple::T_ENTERO) {
		block.ival = data.ival;
	} else if(type == Quadruple::T_REAL) {
		block.fval = data.fval;
	} else if(type == Quadruple::T_CHAR){
		block.sval = data.sval;
	} else if(type == Quadruple::T_BOOL) {}
	block.type = type;
	constants.push_back(block);
	return constants.size();
}

void Memory::allocateSpace(int size) {
	memory.reserve(size);
}

vector<MemoryBlock>* Memory::getMemory() {
	return &memory;
}

int Memory::setMemory(int address, int data) {
	MemoryBlock block = memory[address];
	if (block.type == Quadruple::T_NULL || block.type == Quadruple::T_ENTERO) {
		block.ival = data;
	} else {
		ErrorHandler::invalidType();
	}

}

int Memory::setMemory(int address, double data) {
	MemoryBlock block = memory[address];
	if (block.type == Quadruple::T_NULL || block.type == Quadruple::T_REAL) {
		block.fval = data;
	} else {
		ErrorHandler::invalidType();
	}
}

int Memory::setMemory(int address, string data) {
	MemoryBlock block = memory[address];
	if (block.type == Quadruple::T_NULL || block.type == Quadruple::T_CHAR) {
		block.sval = data;
	} else {
		ErrorHandler::invalidType();
	}
}

void Memory::debugMemory() {
	printf("variables\n");
	for (int i = 0; i < memory.size(); ++i) {
		if (memory[i].type != Quadruple::T_ENTERO) {
			printf("%d: %d\n", i, memory[i].ival);
		} else if (memory[i].type != Quadruple::T_REAL) {
			printf("%d: %4.2f\n", i, memory[i].fval);
		} else if (memory[i].type != Quadruple::T_CHAR) {
			printf("%d: %s\n", i, memory[i].sval.c_str());
		} else if (memory[i].type != Quadruple::T_BOOL) {
			printf("%d: %d\n", i, memory[i].bval);
		}
	}

	printf("constants\n");
	for (int i = 0; i < constants.size(); ++i) {
		if (constants[i].type == Quadruple::T_ENTERO) {
			printf("%d: int    %d\n", i, constants[i].ival);
		} else if (constants[i].type == Quadruple::T_REAL) {
			printf("%d: double %f\n", i, constants[i].fval);
		} else if (constants[i].type == Quadruple::T_CHAR) {
			printf("%d: string %s\n", i, constants[i].sval.c_str());
		} else if (constants[i].type == Quadruple::T_BOOL) {
			printf("%d: bool   %d\n", i, constants[i].bval);
		}
	}
}