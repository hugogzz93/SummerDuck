#include "ErrorHandler.h"

ErrorHandler::ErrorHandler() {}

void ErrorHandler::memoryLimitExceeded() {
	printf("Se ha superado el limite de memoria\n");
	throw bad_alloc();
}