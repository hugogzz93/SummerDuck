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
};

class Memory
{
public:

	Memory() = default;

	int getInt(int);
	bool getBool(int);
	string getChar(int);
	double getDouble(int);
	int getType(int);
	vector<MemoryBlock>* getMemory();
	

	void allocateSpace(int);
	int requestAvailMemory();
	int saveConstant(int, DataHolder);
	void clearAvail(int);

	// int setMemory(int, int);
	// int setMemory(int, double);
	// int setMemory(int, string);
	// int setMemory(int, bool);

	void setMemory(int, int, int);
	void setMemory(int, int, int, int);

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
	MemoryBlock* getBlock(int, int);
	MemoryBlock* getAvailBlock(int, int);

};
#endif