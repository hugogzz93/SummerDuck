all: flex
	g++ -w -std=c++11 bison.tab.c lex.yy.c  Memory.o Quadruple.o ErrorHandler.o QuadrupleGenerator.o ProcDirHandler.o ProcedureDirectory.o ProcedureRecord.o VariableRecord.o SemanticCube.o -o out
	./out

flex: bison 
	flex flex.l

bison: procDirHandler quadrupleGenerator
	bison -d bison.y

procDirHandler: errorHandler procedureDirectory
	g++ -w -std=c++11 -c ProcDirHandler.cpp

errorHandler:
	g++ -w -std=c++11 -c ErrorHandler.cpp

quadrupleGenerator: procedureDirectory quadruple semanticCube procDirHandler quadruple memory
	g++ -w -std=c++11 -c QuadrupleGenerator.cpp	

procedureDirectory: variableRecord procedureRecord
	g++ -w -std=c++11 -c ProcedureDirectory.cpp

procedureRecord: variableRecord quadruple
	g++ -w -std=c++11 -c ProcedureRecord.cpp	

variableRecord: errorHandler
	g++ -w -std=c++11 -c VariableRecord.cpp	

semanticCube: quadruple
	g++ -w -std=c++11 -c SemanticCube.cpp
	
quadruple:
	g++ -w -std=c++11 -c Quadruple.cpp	

memory: semanticCube
	g++ -w -std=c++11 -c Memory.cpp	
