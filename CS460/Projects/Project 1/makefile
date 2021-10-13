P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf bjazevicP1
	mkdir bjazevicP1
	cp Project1.cpp bjazevicP1
	cp LexicalAnalyzer.h bjazevicP1
	cp LexicalAnalyzer.cpp bjazevicP1
	cp SyntacticalAnalyzer.h bjazevicP1
	cp SyntacticalAnalyzer.cpp bjazevicP1
	cp makefile bjazevicP1
	cp README.txt bjazevicP1
	tar cfvz bjazevicP1.tgz bjazevicP1
	cp bjazevicP1.tgz ~tiawatts/cs460drop
