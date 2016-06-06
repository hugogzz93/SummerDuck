#include "Memory.h"
#define AVAIL_OFFSET 10000

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
	printf("Constant saved: val: ");
	if(type == Quadruple::T_ENTERO) {
		block.ival = data.ival;
		printf("%d ", block.ival);
	} else if(type == Quadruple::T_REAL) {
		block.fval = data.fval;
		printf("%lf ", block.fval);
	} else if(type == Quadruple::T_CHAR){
		block.sval = data.sval;
		printf("%s ", block.sval.c_str());
	} else if(type == Quadruple::T_BOOL) {}
	constants.push_back(block);
	printf("Mem: %d\n", constants.size());
	return constants.size();
}