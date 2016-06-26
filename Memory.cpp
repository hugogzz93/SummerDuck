#include "Memory.h"

//MUST BE SAME AS PROC_REQ'S

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
	if (rBlock->type != Quadruple::T_NULL && rBlock->type != lBlock->type) {
		// printf("[%d]%d: %d -> [%d]%d: %d\n", bP, lO, lBlock->type, bP, rO, rBlock->type);
		ErrorHandler::invalidType();
	}

	*rBlock = *lBlock;
	// printf("Assigned - [%d] %d (%d) to [%d] %d (%d) ", bP, lO, lBlock->type, bP, rO, rBlock->type);
	// cout << "(" << *lBlock << ")" << endl;
}

void Memory::setMemory(int bP1, int lO, int bP2, int rO) {
	MemoryBlock *lBlock = getBlock(bP1, lO), *rBlock = getBlock(bP2, rO);
	if (rBlock->type != Quadruple::T_NULL && rBlock->type != lBlock->type) {
		// printf("[%d]%d: %d -> [%d]%d: %d\n", bP1, lO, lBlock->type, bP2, rO, rBlock->type);
		ErrorHandler::invalidType();
	}
	// printf("Assigned - [%d] %d (%d) to [%d]%d (%d) ", bP1, lO, lBlock->type,  bP2, rO, rBlock->type);
	// cout << "(" << *lBlock << ")" << endl;
	*rBlock = *lBlock;
}

void Memory::setMemory(int bP, int address, MemoryBlock data) {
	MemoryBlock* destination = getBlock(bP, address);
	*destination = data;
	// printf("Assigned data to [%d] %d as type %d", bP, address, data.type);
	// cout << " " << data << endl;

}

// int Memory::getAvailAddress(int bP, int address) {
	// return avail[bP]
// }

MemoryBlock* Memory::getBlock(int bP, int address) {
	if (isTemp(address)) {
		return getAvailBlock(bP, address);
	} else if (isConstant(address)) {
		return &constants[address - CONSTANT_OFFSET];
	} else if(isGlobal(address)) {
		return &memory[-1][address];
	} else if (isPointer(address)) {
		// printf("looking at address: %d\n", address);
		MemoryBlock* pRes;
		// printf("pointer %d ", address);
		address -= POINTER_OFFSET;
		address *= -1;
		MemoryBlock* pointer = getAvailBlock(bP, address);
		// cout << *pointer << endl;
		if (pointer->type == Quadruple::T_ENTERO) {
			pRes = getBlock(bP, pointer->ival);
			// printf("points to: ");
			// cout << *pRes << endl;
			return getBlock(bP, pointer->ival);
		} else if(pointer->type == Quadruple::T_REAL) {
			pRes = getBlock(bP, pointer->fval);
			// printf("points to: ");
			// cout << *pRes << endl;
			return getBlock(bP, pointer->fval);
		} else {
			ErrorHandler::InvalidPointerTargetType();
		}
	} else {
		return &memory[bP][address];
	}
}

MemoryBlock* Memory::getAvailBlock(int bP, int address) {
	return &avail[bP][address];
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
	return CONSTANT_OFFSET + constants.size()-1;
}

// void Memory::allocateSpace(int size) {
// 	memory.reserve(size);
// }

unordered_map<int, unordered_map<int, MemoryBlock>>* Memory::getMemory() {
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
	// printf("variables\n");
	// for (int i = 0; i < memory.size(); ++i) {
	// 	if (memory[i].type != Quadruple::T_ENTERO) {
	// 		printf("%d: %d\n", i, memory[i].ival);
	// 	} else if (memory[i].type != Quadruple::T_REAL) {
	// 		printf("%d: %4.2f\n", i, memory[i].fval);
	// 	} else if (memory[i].type != Quadruple::T_CHAR) {
	// 		printf("%d: %s\n", i, memory[i].sval.c_str());
	// 	} else if (memory[i].type != Quadruple::T_BOOL) {
	// 		printf("%d: %d\n", i, memory[i].bval);
	// 	}
	// }

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

	// printf("Avail\n");
	// for (auto map = avail.begin(); map != avail.end(); map++) {
	// 	printf("basePointer: %d\n", map->first);
	// 	auto mMap = map->second;
	// 	for (auto it = mMap.begin(); it != mMap.end(); it++) {
	// 		MemoryBlock block = it->second;
	// 		printf("%d\n", it->first);
	// 		switch(block.type) {
	// 			case Quadruple::T_ENTERO:
	// 				printf("%d\n", block.ival);
	// 				break;
	// 			case Quadruple::T_REAL:
	// 				printf("%f\n", block.fval);
	// 				break;
	// 			case Quadruple::T_CHAR:
	// 				printf("%s\n", block.sval.c_str());
	// 				break;
	// 			case Quadruple::T_BOOL:
	// 				printf("%d\n", block.bval);
	// 				break;
	// 		}
	// 	}
	// }
}

bool Memory::isTemp(int address) {
	return address < 0 ? true : false ;
}

bool Memory::isConstant(int address) {
	return address >= CONSTANT_OFFSET && address < POINTER_OFFSET ? true : false ;
}

bool Memory::isGlobal(int address) {
	return address < GLOBAL_LIM ? true : false ;
}

bool Memory::isPointer(int address) {
	return address >= POINTER_OFFSET ? true : false ;
}

void Memory::clearAvail(int bP) {
	avail[bP].clear();
}

void Memory::setType(int bP, int address, int type) {
	MemoryBlock* block = getBlock(bP, address);
	block->type = type;
}

void Memory::prepareBlocks(int bP, VariableRecord record) {
	int dimensions = record.getDimensions();
	// printf("\n\n\n");
	// printf("-----------------------------\n");
	// printf("dimensions %d\n", dimensions);
	if( dimensions == 1) {
		for (int i = 0; i < record.sizes[0]; ++i) {
			// printf("setting %d to type %d\n", record.getVAddress() + 1, record.getType());
			setType(bP, record.getVAddress() + i,  record.getType());
		}
		
	} else {
		for (int i = 0; i < record.sizes[0]; ++i) {
			for (int j = 0; j < record.sizes[1]; ++j) {
				// printf("setting %d to type %d\n", record.getVAddress() + (i * record.sizes[1] + j), record.getType());
				// printf("%d * %d + %d = %d\n", j, i, j, j * i + j);
				setType(bP, record.getVAddress() + (i * record.sizes[1] + j),  record.getType());
			}
		}
	}
	// printf("-----------------------------\n");
}