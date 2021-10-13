P3.out : Project3.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o CodeGenerator.o
	g++ -g -o P3.out Project3.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o CodeGenerator.o

Project2.o : Project3.cpp SetLimits.h SyntacticalAnalyzer.h SyntacticalAnalyzer.h CodeGenerator.h
	g++ -g -c Project3.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

CodeGenerator.o : CodeGenerator.cpp CodeGenerator.h LexicalAnalyzer.h
	g++ -g -c CodeGenerator.cpp


clean :
	rm [SP]*.o P3.out

submit : Project3.cpp LexicalAnalyzer.h SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf bjazevicP3
	mkdir bjazevicP3
	cp CodeGenerator.cpp bjazevicP3
	cp CodeGenerator.h bjazevicP3
	cp Project3.cpp bjazevicP3
	cp SyntacticalAnalyzer.h bjazevicP3
	cp SyntacticalAnalyzer.cpp bjazevicP3
	cp makefile bjazevicP3
	cp README.txt bjazevicP3
	tar cfvz bjazevicP3.tgz bjazevicP3
	cp bjazevicP3.tgz ~tiawatts/cs460drop
