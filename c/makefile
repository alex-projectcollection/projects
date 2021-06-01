assembler: MainCompiler.o filemaker.o frombinary.o database.o utilFunctions.o utils1.o utils2.o utils3.o headquarters.h
	gcc -g -Wall -ansi -pedantic MainCompiler.o filemaker.o frombinary.o database.o utilFunctions.o utils1.o utils2.o utils3.o -o assembler

database.o: database.c headquarters.h
	gcc -c -Wall -ansi -pedantic database.c -o database.o

utils3.o: utils3.c headquarters.h
	gcc -c -Wall -ansi -pedantic utils3.c -o utils3.o

utils2.o: utils2.c headquarters.h
	gcc -c -Wall -ansi -pedantic utils2.c -o utils2.o

utils1.o: utils1.c headquarters.h
	gcc -c -Wall -ansi -pedantic utils1.c -o utils1.o

utilFunctions.o: utilFunctions.c headquarters.h
	gcc -c -Wall -ansi -pedantic utilFunctions.c -o utilFunctions.o

frombinary.o: frombinary.c headquarters.h
	gcc -c -Wall -ansi -pedantic frombinary.c -o frombinary.o

filemaker.o: filemaker.c headquarters.h
	gcc -c -Wall -ansi -pedantic filemaker.c -o filemaker.o

MainCompiler.o: MainCompiler.c headquarters.h
	gcc -c -Wall -ansi -pedantic MainCompiler.c -o MainCompiler.o
