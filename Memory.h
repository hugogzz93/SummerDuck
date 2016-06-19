#ifndef GUARD_MEMORY
#define GUARD_MEMORY

#include <vector>
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
};

class Memory
{
public:

	Memory() = default;

	int getInt(int);
	bool getBool(int);
	string getChar(int);
	double getDouble(int);
	vector<MemoryBlock>* getMemory();

	void allocateSpace(int);
	int requestAvailMemory();
	int saveConstant(int, DataHolder);

	int setMemory(int, int);
	int setMemory(int, double);
	int setMemory(int, string);
	int setMemory(int, bool);

	// debug
	void debugMemory();


private:
	vector<MemoryBlock> memory;
	vector<MemoryBlock> avail;
	vector<MemoryBlock> constants;

};
#endif