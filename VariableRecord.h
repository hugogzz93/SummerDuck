#ifndef GUARD_VARIABLE_RECORD
#define GUARD_VARIABLE_RECORD 

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class VariableRecord
{
public:

	const enum {
		T_ENTERO, T_REAL, T_CHAR
	};
	
	VariableRecord(int type, string name);
	VariableRecord(int type, string name, int vAddress, string scope);
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

	string expose();

private:
	string name = "undefined_name", scope = "undefined_scope";
	int type = -1, vAddress = -1;
	bool constant = false;
};

#endif