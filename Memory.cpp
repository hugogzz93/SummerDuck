#include "Memory.h"
#define AVAIL_OFFSET 10
#define CONSTANT_OFFSET 4000

// int Memory::getInt(int address) {
// 	return memory[address].ival;
// }

// double Memory::getDouble(int address) {
// 	return memory[address].fval;
// }

// string Memory::getChar(int address) {
// 	return memory[address].sval;
// }

// bool Memory::getBool(int address) {
// 	return memory[address].bval;
// }

void Memory::setMemory(int bP, int lO, int rO) {
	MemoryBlock *lBlock = getBlock(bP, lO), *rBlock = getBlock(bP, rO);
	*rBlock = *lBlock;
	printf("Assigned - %d to %d\n", lO, rO);
}

void Memory::setMemory(int bP1, int lO, int bP2, int rO) {
	MemoryBlock *lBlock = getBlock(bP1, lO), *rBlock = getBlock(bP2, rO);
	if (rBlock->type != Quadruple::T_NULL || rBlock->type != lBlock->type) {
		ErrorHandler::invalidType();
	}
	*rBlock = *lBlock;
}

// int Memory::getAvailAddress(int bP, int address) {
	// return avail[bP]
// }

MemoryBlock* Memory::getBlock(int bP, int address) {
	if (isTemp(address)) {
		return getAvailBlock(bP, address);
	} else if (isConstant(address)) {
		return &constants[address];
	} else {
		return &memory[bP + address];
	}
}

MemoryBlock* Memory::getAvailBlock(int bP, int address) {
	// if (avail.find(bP) == avail.end()) {
	// 	unordered_map<int, MemoryBlock> availSpace;
	// 	avail[bP] = availSpace;
	// }

	// if (avail[bP].find(address) == avail.end()) {
	// 	MemoryBlock newBlock;
	// 	avail[bP][address] = newBlock;
	// }

	return &avail[bP][address];
}

int Memory::getType(int address) {
	if (isTemp(address)) {
		
	} else {
		return memory[address].type;
	}
}

int Memory::requestAvailMemory() {
	return -1 * (AVAIL_OFFSET + availIndex++);
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
	return CONSTANT_OFFSET + constants.size();
}

void Memory::allocateSpace(int size) {
	memory.reserve(size);
}

vector<MemoryBlock>* Memory::getMemory() {
	return &memory;
}

// int Memory::setMemory(int address, int data) {
// 	MemoryBlock block = memory[address];
// 	if (block.type == Quadruple::T_NULL || block.type == Quadruple::T_ENTERO) {
// 		block.ival = data;
// 	} else {
// 		ErrorHandler::invalidType();
// 	}

// }

// int Memory::setMemory(int address, double data) {
// 	MemoryBlock block = memory[address];
// 	if (block.type == Quadruple::T_NULL || block.type == Quadruple::T_REAL) {
// 		block.fval = data;
// 	} else {
// 		ErrorHandler::invalidType();
// 	}
// }

// int Memory::setMemory(int address, string data) {
// 	MemoryBlock block = memory[address];
// 	if (block.type == Quadruple::T_NULL || block.type == Quadruple::T_CHAR) {
// 		block.sval = data;
// 	} else {
// 		ErrorHandler::invalidType();
// 	}
// }

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

	printf("Avail\n");
	for (auto map = avail.begin(); map != avail.end(); map++) {
		printf("basePointer: %d\n", map->first);
		auto mMap = map->second;
		for (auto it = mMap.begin(); it != mMap.end(); it++) {
			MemoryBlock block = it->second;
			printf("%d\n", it->first);
			switch(block.type) {
				case Quadruple::T_ENTERO:
					printf("%d\n", block.ival);
					break;
				case Quadruple::T_REAL:
					printf("%f\n", block.fval);
					break;
				case Quadruple::T_CHAR:
					printf("%s\n", block.sval.c_str());
					break;
				case Quadruple::T_BOOL:
					printf("%d\n", block.bval);
					break;
			}
		}
	}
}

bool Memory::isTemp(int address) {
	return address < 0 ? true : false ;
}

bool Memory::isConstant(int address) {
	return address >= CONSTANT_OFFSET ? true : false ;
}

void Memory::clearAvail(int bP) {
	avail[bP].clear();
}