#include "ErrorHandler.h"

ErrorHandler::ErrorHandler() {}

void ErrorHandler::memoryLimitExceeded() {
	printf("Se ha superado el limite de memoria\n");
	throw bad_alloc();
}

void ErrorHandler::variableRedefinition(string name) {
	printf("Ya existe una variable bajo el nombre '%s'.\n", name.c_str());
	throw "Ya existe una variable bajo ese nombre.";
}

void ErrorHandler::moduleRedefinition(string name) {
	printf("Ya existe un modulo bajo el nombre '%s'.\n", name.c_str());
	throw "Ya existe un modulo bajo ese nombre.";
}