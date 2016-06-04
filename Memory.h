#ifndef GUARD_MEMORY
#define GUARD_MEMORY

#include <vector>
#include "SemanticCube.h"
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
};

class Memory
{
public:
	const enum {
		I_WRITE, I_READ, I_VER, I_CALL, I_RET, I_GOTO, I_GOTOF, I_GOSUB, I_ERA,
		I_AND, I_OR, I_SUMA, I_RESTA, I_MULT, I_DIV, I_MAYOR_QUE, I_MAYOR_IGUAL_QUE,
	    I_MENOR_QUE, I_MENOR_IGUAL_QUE, I_NO_IGUAL, I_IGUAL, I_DETERMINANTE, I_INVERSA
	};
	
	Memory() = default;

	int getInt(int);
	double getDouble(int);
	string getChar(int);
	bool getBool(int);
	int requestAvailMemory();
	int saveConstant(int, DataHolder);

private:
	vector<MemoryBlock> memory;
	vector<MemoryBlock> avail;
	vector<MemoryBlock> constants;

};
#endif