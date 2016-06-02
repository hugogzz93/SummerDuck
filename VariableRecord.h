#ifndef GUARD_VARIABLE_RECORD
#define GUARD_VARIABLE_RECORD 

#include "ErrorHandler.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Data {
	string sval;
	int ival;
	double fval;
};

class VariableRecord
{
public:

	const enum {
		T_ENTERO, T_REAL, T_CHAR
	};
	
	// VariableRecord(int type, string name, int dimensions, int vAddress, string scope);
	VariableRecord(string name, string scope, int type, int dimensions, int vAddress, int sizes[]);
	VariableRecord();
	
	int getType();
	int getVAddress();
	string getName();
	string getScope();
	string getTypeAsString();
	bool getConstant();

	void setType(int type);
	void setVAddress(int vAddress);
	void setName(string name);
	void setScope(string scope);
	void setConstant(bool constant);

	void getValue(int&);
	void getValue(double&);
	void getValue(string&);
	void setValue(int);
	void setValue(double);
	void setValue(string);

	string expose();
	int arrayAccess(int coordinates[]);

private:
	string name = "undefined_name", scope = "undefined_scope";
	int type = -1, vAddress = -1, dimensions = 1, sizes[2];
	bool constant = false;
	Data data;

};

#endif