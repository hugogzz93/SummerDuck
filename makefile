all: flex
	g++ -w -std=c++11 bison.tab.c lex.yy.c -o out
	./out

debug: flex_debug
	g++ -w -std=c++11 bison.tab.c lex.yy.c -o out
	./out

flex_debug: bison_debug
	flex flex.l

bison_debug:
	bison --debug bison.y

flex: bison
	flex flex.l

bison:
	bison -d bison.y