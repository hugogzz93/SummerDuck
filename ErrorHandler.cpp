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

void ErrorHandler::invalidType() {
	// printf("%s se le ha asignado el tipo equivocado\n", name.c_str());
	printf("Datos incompatibles.\n");
	throw "";
}

void ErrorHandler::badSyntax(string msg) {
	printf("%s\n", msg.c_str());
	throw msg;
}

void ErrorHandler::unidentifiedProcedure(string id) {
	printf("No se pudo encontrar el procedimiento %s\n", id.c_str());
	throw "";
}

void ErrorHandler::unidentifiedProcedure(int id) {
	printf("No se pudo encontrar el procedimiento %d\n", id);
	throw "";
}

void ErrorHandler::InvalidInstruction(int instruction) {
	printf("No existe la funcion con el codigo %d\n", instruction);
	throw "";
}

void ErrorHandler::MissingArguments(string name, int given, int needed) {
	printf("Cantidad de parametros incorrecto para %s, %d de %d\n", name.c_str(), given, needed);
	throw "";
}

void ErrorHandler::InvalidOperation(string msg) {
	printf("%s\n", msg.c_str());
	throw "";
}