#ifndef GUARD_ERROR_HANDLER
#define GUARD_ERROR_HANDLER 
#include <iostream>

using namespace std;
class ErrorHandler
{
public:
	ErrorHandler();

	static void memoryLimitExceeded();
};
#endif