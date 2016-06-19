#ifndef VIRTUAL_MACHINE_GUARD
#define VIRTUAL_MACHINE_GUARD 

#include "ProcedureDirectory.h"
#include "Memory.h"

using namespace std;
class VirtualMachine
{
public:
	VirtualMachine(ProcedureDirectory* directory, Memory* memory);

	void callProcedure(int id);
	void executeInstruction(Quadruple);

private:
	ProcedureDirectory* directory;
	Memory* memory;
	int basePointer, globalLimit, instructionPointer;

};
#endif