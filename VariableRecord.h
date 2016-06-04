#ifndef GUARD_VARIABLE_RECORD
#define GUARD_VARIABLE_RECORD 

#include "ErrorHandler.h"
#include "SemanticCube.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Data {
	string sval;
	int ival;
	double fval;
	bool bval;
};

class VariableRecord
{
public:
	
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
	void getValue(bool&);
	void setValue(int);
	void setValue(double);
	void setValue(string);
	void setValue(bool);
	void setData(Data);

	string expose();
	int arrayAccess(int coordinates[]);

	// VariableRecord operator+(VariableRecord);
	// VariableRecord operator-(VariableRecord);
	// VariableRecord operator*(VariableRecord);
	// VariableRecord operator/(VariableRecord);
	// VariableRecord operator>(VariableRecord);
	// VariableRecord operator>=(VariableRecord);
	// VariableRecord operator<(VariableRecord);
	// VariableRecord operator<=(VariableRecord);
	// VariableRecord operator!=(VariableRecord);
	// VariableRecord operator==(VariableRecord);

private:
	string name = "undefined_name", scope = "undefined_scope";
	int type = -1, vAddress = -1, dimensions = 1, sizes[2];
	bool constant = false;
	Data data;
	SemanticCube cube;

	// Data dataOperation(int, Data, Data, int, int);
	// template <typename A, typename B>
	// Data dataOperationAux(int, A, B);
	// void dataStorage(Data&, int);
	// void dataStorage(Data&, double);
	// void dataStorage(Data&, string);
	// void dataStorage(Data&, bool);
};

#endif