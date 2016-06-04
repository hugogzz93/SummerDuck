#include "Memory.h"
#define AVAIL_OFFSET 4000

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
	return AVAIL_OFFSET + avail.size();
}

int Memory::saveConstant(int type, DataHolder data) {
		MemoryBlock block;
		if(type == SemanticCube::T_ENTERO) {
			block.ival = data.ival;
		} else if(type == SemanticCube::T_REAL) {
			block.fval = data.fval;
		} else if(type == SemanticCube::T_CHAR){
			block.sval = data.sval;
		} else if(type == SemanticCube::T_BOOL){}
		constants.push_back(block);
	return constants.size();
}