#ifndef VIRTUAL_MACHINE_GUARD
#define VIRTUAL_MACHINE_GUARD 

#include "ProcedureDirectory.h"
#include "Memory.h"
#include <vector>

using namespace std;
class VirtualMachine
{
public:
	VirtualMachine(ProcedureDirectory* directory, Memory* memory);

	void executeInstruction(Quadruple);
	void era(int);
	void callProcedure(int, int);
	void param(int);
	void ret(Quadruple);
	void run();
	void gotoJ(Quadruple);

private:
	ProcedureDirectory* directory;
	ProcedureRecord* procedure;
	vector<int> parameters, callStack, retAddresses, basePointers, instructionPointers;
	Memory* memory;
	int basePointer, stackPointer, globalLimit, instructionPointer;

	void arithmetic(Quadruple, int);
	void cleanParameters();
};
#endif