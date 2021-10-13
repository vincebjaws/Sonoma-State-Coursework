 sim : Date.o Transaction.o simulator.o
	g++ -o sim Date.o Transaction.o simulator.o

Date.o : Date.h Date.cpp
	g++ -c Date.cpp 

Transaction.o : Date.h Transaction.h Transaction.cpp
	g++ -c Transaction.cpp 

simulator.o : Transaction.h simulator.cpp
	g++ -c simulator.cpp 

simD : DateD.o TransactionD.o simulatorD.o
	g++ -o simD DateD.o TransactionD.o simulatorD.o 

DateD.o : Date.h Date.cpp
	g++ -c -DDEBUG -o DateD.o Date.cpp 

TransactionD.o : Date.h Transaction.h Transaction.cpp
	g++ -c -DDEBUG -o TransactionD.o Transaction.cpp 

simulatorD.o : Transaction.h simulator.cpp
	g++ -c -DDEBUG -o simulatorD.o simulator.cpp

clean :
	rm -rf sim simD *.o

submit : simulator.cpp Date.h Date.cpp Transaction.h Transaction.cpp makefile README.txt
	rm -rf bjazevicE2
	mkdir bjazevicE2
	cp simulator.cpp bjazevicE2
	cp Date.h bjazevicE2
	cp Date.cpp bjazevicE2
	cp Transaction.h bjazevicE2
	cp Transaction.cpp bjazevicE2
	cp makefile bjazevicE2
	cp README.txt bjazevicE2
	tar cfvz bjazevicE2.tgz bjazevicE2
	cp bjazevicE2.tgz ~tiawatts/cs460drop
