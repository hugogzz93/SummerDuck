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