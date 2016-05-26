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

string VariableRecord::getTypeAsString() {
	string msg;
	if (type == T_ENTERO) { msg = "ENTERO"; } 
	else if(type == T_REAL) { msg =  "REAL"; }
	else { msg = "CHAR"; }
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