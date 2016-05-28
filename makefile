all: flex
	g++ -w -std=c++11 bison.tab.c lex.yy.c  ErrorHandler.o ProcDirHandler.o ProcedureDirectory.o ProcedureRecord.o VariableRecord.o -o out
	./out

debug: flex_debug
	g++ -w -std=c++11 bison.tab.c lex.yy.c  ErrorHandler.o ProcDirHandler.o ProcedureDirectory.o ProcedureRecord.o VariableRecord.o -o out
	./out

flex_debug: bison_debug
	flex flex.l

bison_debug: ProcedureDirectory
	bison --debug bison.y

flex: bison 
	flex flex.l

bison: procDirHandler
	bison -d bison.y

procDirHandler: errorHandler procedureDirectory
	g++ -w -std=c++11 -c ProcDirHandler.cpp

errorHandler:
	g++ -w -std=c++11 -c ErrorHandler.cpp

procedureDirectory: variableRecord procedureRecord
	g++ -w -std=c++11 -c ProcedureDirectory.cpp

procedureRecord: variableRecord
	g++ -w -std=c++11 -c ProcedureRecord.cpp	

variableRecord: errorHandler
	g++ -w -std=c++11 -c VariableRecord.cpp	
