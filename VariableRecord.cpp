#include "VariableRecord.h"
#include <cstdio>

using namespace std;

// VariableRecord::VariableRecord(int type, string name, int vAddress, string scope):
//  type(type), name(name), vAddress(vAddress), scope(scope) {}
 
// VariableRecord::VariableRecord(int type, string name): type(type), name(name) {}

VariableRecord::VariableRecord(string name, string scope, int type, int dimensions, int vAddress, int sizes[]):
name(name), scope(scope), type(type), dimensions(dimensions), vAddress(vAddress) {
	size_t size = sizeof(sizes) / sizeof(int);
	for (size_t i = 0; i < size; ++i)
	{
		this->sizes[i] = sizes[i];
	}
}

VariableRecord::VariableRecord() {}

string VariableRecord::getName() {
	return name;
}

int VariableRecord::getType() {
	return type;
}

int VariableRecord::getVAddress() {
	return vAddress;
}

string VariableRecord::expose() {
	string message = getConstant() ? getName() : getScope() + "(" + to_string(getVAddress()) + ")";
	return message;
}

int VariableRecord::arrayAccess(int coordinates[]) {
	if (sizeof(coordinates)/sizeof(coordinates[0]) != dimensions)
	{
		string msg = name + " no tiene suficientes dimensionses.";
		ErrorHandler::invalidAccess(msg);
	} else if( dimensions == 1) {
		// vector
		if (coordinates[0] > sizes[0] || coordinates[0] < 0)
		{
			ErrorHandler::invalidAccess("Accesso fuera de limites");
		}
		return coordinates[0];
	} else {
		if (coordinates[0] > sizes[0] || coordinates[0] < 0 || coordinates[1] > sizes[1] || coordinates[1] < 0)
		{
			ErrorHandler::invalidAccess("Accesso fuera de limites");
		}
		return coordinates[0]*sizes[0] + coordinates[1];
	}
}

string VariableRecord::getTypeAsString() {
	string msg;
	if (type == SemanticCube::T_ENTERO) { msg = "ENTERO"; } 
	else if(type == SemanticCube::T_REAL) { msg =  "REAL"; }
	else if(type == SemanticCube::T_CHAR) { msg = "CHAR"; }
	else { msg = "BOOL"; }
	return msg;
}

string VariableRecord::getScope() {
	return scope;
}

bool VariableRecord::getConstant() {
	return constant;
}

void VariableRecord::setType(int type) {
	this->type = type;
}

void VariableRecord::setName(string name) {
	this->name = name;
}

void VariableRecord::setVAddress(int vAddress) {
	this->vAddress = vAddress;
}

void VariableRecord::setScope(string scope) {
	this->scope = scope;
}

void VariableRecord::setConstant(bool constant) {
	this->constant = constant;
}

void VariableRecord::getValue(int &container) {
	if (type != SemanticCube::T_ENTERO) { ErrorHandler::invalidType(); }
	container = data.ival;
}

void VariableRecord::getValue(double &container) {
	if (type != SemanticCube::T_REAL) { ErrorHandler::invalidType(); }
	container = data.fval;
}

void VariableRecord::getValue(string &container) {
	if (type != SemanticCube::T_CHAR) { ErrorHandler::invalidType(); }
	container = data.sval;
}

void VariableRecord::getValue(bool &container) {
	if (type != SemanticCube::T_BOOL) { ErrorHandler::invalidType(); }
	container = data.bval;
}

void VariableRecord::setValue(int value) {
	if (type != SemanticCube::T_ENTERO) { ErrorHandler::invalidType(); }
	data.ival = value;
}

void VariableRecord::setValue(double value) {
	if (type != SemanticCube::T_REAL) { ErrorHandler::invalidType(); }
	data.fval = value;
}

void VariableRecord::setValue(string value) {
	if (type != SemanticCube::T_CHAR) { ErrorHandler::invalidType(); }
	data.sval = value;
}

void VariableRecord::setValue(bool value) {
	if (type != SemanticCube::T_BOOL) { ErrorHandler::invalidType(); }
	data.bval = value;
}

void VariableRecord::setData(Data data) {
	this->data = data;
}

