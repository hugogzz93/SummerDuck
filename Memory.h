#ifndef GUARD_MEMORY
#define GUARD_MEMORY

#include <vector>
#include <unordered_map>
#include "SemanticCube.h"
#include "ErrorHandler.h"
using namespace std;

struct DataHolder {
	string sval;
	int ival;
	double fval;
	int dimensions;
	int sizes[2];
};

struct MemoryBlock
{
	int ival;
	double fval;
	string sval;
	bool bval;
	int type = Quadruple::T_NULL;

	MemoryBlock operator+(const MemoryBlock& rhs) const {
		MemoryBlock result;
			if (type == Quadruple::T_ENTERO) {
				if (rhs.type == Quadruple::T_ENTERO) {
					result.ival = ival + rhs.ival;
					result.type = type;
				} else if (rhs.type == Quadruple::T_REAL) {
					result.fval = ival + rhs.fval;
					result.type == rhs.type;
				} else {
					ErrorHandler::invalidType();
				}
			} else if (type == Quadruple::T_REAL) {
				if (rhs.type == Quadruple::T_ENTERO) {
					result.fval = fval + rhs.ival;
					result.type = type;
				} else if (rhs.type == Quadruple::T_REAL) {
					result.fval = fval + rhs.fval;
					result.type == rhs.type;
				} else {
					ErrorHandler::invalidType();
				}
			} else if (type == Quadruple::T_CHAR) {
				ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con chars");
			} else if (type == Quadruple::T_BOOL) {
				ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con bools");
			}
		return result;
	}

	MemoryBlock operator-(const MemoryBlock& rhs) const {
		MemoryBlock result;
			if (type == Quadruple::T_ENTERO) {
				if (rhs.type == Quadruple::T_ENTERO) {
					result.ival = ival - rhs.ival;
					result.type = type;
				} else if (rhs.type == Quadruple::T_REAL) {
					result.fval = ival - rhs.fval;
					result.type == rhs.type;
				} else {
					ErrorHandler::invalidType();
				}
			} else if (type == Quadruple::T_REAL) {
				if (rhs.type == Quadruple::T_ENTERO) {
					result.fval = fval - rhs.ival;
					result.type = type;
				} else if (rhs.type == Quadruple::T_REAL) {
					result.fval = fval - rhs.fval;
					result.type == rhs.type;
				} else {
					ErrorHandler::invalidType();
				}
			} else if (type == Quadruple::T_CHAR) {
				ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con chars");
			} else if (type == Quadruple::T_BOOL) {
				ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con bools");
			}
		return result;
	}

	MemoryBlock operator*(const MemoryBlock& rhs) const {
		MemoryBlock result;
			if (type == Quadruple::T_ENTERO) {
				if (rhs.type == Quadruple::T_ENTERO) {
					result.ival = ival * rhs.ival;
					result.type = type;
				} else if (rhs.type == Quadruple::T_REAL) {
					result.fval = ival * rhs.fval;
					result.type == rhs.type;
				} else {
					ErrorHandler::invalidType();
				}
			} else if (type == Quadruple::T_REAL) {
				if (rhs.type == Quadruple::T_ENTERO) {
					result.fval = fval * rhs.ival;
					result.type = type;
				} else if (rhs.type == Quadruple::T_REAL) {
					result.fval = fval * rhs.fval;
					result.type == rhs.type;
				} else {
					ErrorHandler::invalidType();
				}
			} else if (type == Quadruple::T_CHAR) {
				ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con chars");
			} else if (type == Quadruple::T_BOOL) {
				ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con bools");
			}
		return result;
	}

	MemoryBlock operator/(const MemoryBlock& rhs) const {
		MemoryBlock result;
			if (type == Quadruple::T_ENTERO) {
				if (rhs.type == Quadruple::T_ENTERO) {
					result.fval = ival / rhs.ival;
					result.type = Quadruple::T_REAL;
				} else if (rhs.type == Quadruple::T_REAL) {
					result.fval = ival / rhs.fval;
					result.type == rhs.type;
				} else {
					ErrorHandler::invalidType();
				}
			} else if (type == Quadruple::T_REAL) {
				if (rhs.type == Quadruple::T_ENTERO) {
					result.fval = fval / rhs.ival;
					result.type = type;
				} else if (rhs.type == Quadruple::T_REAL) {
					result.fval = fval / rhs.fval;
					result.type == rhs.type;
				} else {
					ErrorHandler::invalidType();
				}
			} else if (type == Quadruple::T_CHAR) {
				ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con chars");
			} else if (type == Quadruple::T_BOOL) {
				ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con bools");
			}
		return result;
	}

	MemoryBlock operator>(const MemoryBlock& rhs) const {
		MemoryBlock result;
		if (type == Quadruple::T_ENTERO) {
			if (rhs.type == Quadruple::T_ENTERO) {
				result.bval = ival > rhs.ival;
			} else if (rhs.type == Quadruple::T_REAL) {
				result.bval = ival > rhs.fval;
			} else {
				ErrorHandler::invalidType();
			}
		} else if (type == Quadruple::T_REAL) {
			if (rhs.type == Quadruple::T_ENTERO) {
				result.bval = fval > rhs.ival;
			} else if (rhs.type == Quadruple::T_REAL) {
				result.bval = fval > rhs.fval;
			} else {
				ErrorHandler::invalidType();
			}
		} else if (type == Quadruple::T_CHAR) {
			if (rhs.type == Quadruple::T_CHAR) {
				result.bval = sval > rhs.sval;
			} else {
				ErrorHandler::invalidType();
			}
			
		} else if (type == Quadruple::T_BOOL) {
			ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con bools");
		}
		return result;
	}

	MemoryBlock operator<(const MemoryBlock& rhs) const {
		MemoryBlock result;
		if (type == Quadruple::T_ENTERO) {
			if (rhs.type == Quadruple::T_ENTERO) {
				result.bval = ival < rhs.ival;
			} else if (rhs.type == Quadruple::T_REAL) {
				result.bval = ival < rhs.fval;
			} else {
				ErrorHandler::invalidType();
			}
		} else if (type == Quadruple::T_REAL) {
			if (rhs.type == Quadruple::T_ENTERO) {
				result.bval = fval < rhs.ival;
			} else if (rhs.type == Quadruple::T_REAL) {
				result.bval = fval < rhs.fval;
			} else {
				ErrorHandler::invalidType();
			}
		} else if (type == Quadruple::T_CHAR) {
			if (rhs.type == Quadruple::T_CHAR) {
				result.bval = sval < rhs.sval;
			} else {
				ErrorHandler::invalidType();
			}
			
		} else if (type == Quadruple::T_BOOL) {
			ErrorHandler::InvalidOperation("No se pueden hacer operaciones aritmeticas con bools");
		}
		return result;
	}
};

class Memory
{
public:

	Memory() = default;

	int getInt(int);
	int getType(int);
	bool getBool(int);
	string getChar(int);
	double getDouble(int);
	MemoryBlock* getBlock(int, int);
	vector<MemoryBlock>* getMemory();


	void clearAvail(int);
	void allocateSpace(int);
	int requestAvailMemory();
	int saveConstant(int, DataHolder);

	// int setMemory(int, int);
	// int setMemory(int, double);
	// int setMemory(int, string);
	// int setMemory(int, bool);

	void setMemory(int, int, int);
	void setMemory(int, int, int, int);
	void setMemory(int, int, MemoryBlock);

	// debug
	void debugMemory();
	bool isTemp(int);
	bool isConstant(int);


private:
	int availIndex = 0;
	vector<MemoryBlock> memory;
	vector<MemoryBlock> constants;
	unordered_map<int, unordered_map<int, MemoryBlock>> avail; //bp -> address = block

	// int getAvailAddress(int, int);
	MemoryBlock* getAvailBlock(int, int);

};
#endif