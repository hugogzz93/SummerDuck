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

void ErrorHandler::unidentifiedId(string name, string procedure) {
	printf("No se pudo encontrar un registro de la variable '%s' para el modulo %s.\n", name.c_str(), procedure.c_str());
	throw "No se pudo encontrar un registro de la variable.";
}

void ErrorHandler::invalidAccess(string msg) {
	printf("%s\n", msg.c_str());
	throw msg;	
}

void ErrorHandler::invalidType(string name) {
	printf("%s se le ha asignado el tipo equivocado\n", name.c_str());
	throw "";
}