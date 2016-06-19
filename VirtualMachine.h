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
	void callProcedure(int id);
	void param(int);
	void ret();
	void run();

private:
	ProcedureDirectory* directory;
	ProcedureRecord* procedure;
	vector<int> parameters;
	Memory* memory;
	int prevBasePointer, basePointer, stackPointer, globalLimit, instructionPointer, prevInstructionPointer;

};
#endif