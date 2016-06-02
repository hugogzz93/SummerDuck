#ifndef GUARD_ERROR_HANDLER
#define GUARD_ERROR_HANDLER 
#include <iostream>

using namespace std;
class ErrorHandler
{
public:
	ErrorHandler();

	static void memoryLimitExceeded();
	static void variableRedefinition(string);
	static void moduleRedefinition(string);
	static void invalidAccess(string msg);
	static void unidentifiedId(string, string);
	static void invalidType(string);
};
#endif