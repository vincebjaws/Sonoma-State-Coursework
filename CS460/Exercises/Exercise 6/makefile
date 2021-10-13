run: bjazevicE6.o
	./a.out input.txt

bjazevicE6.o:
	g++  bjazevicE6.cpp Real.cpp

clean : 
	rm a.out

submit : bjazevicE6.cpp Real.h Real.cpp  makefile output.txt expectedOutput.txt input.txt output.txt input2.txt expectedOutput2.txt README.txt
	rm -rf bjazevicE6
	mkdir bjazevicE6
	cp bjazevicE6.cpp bjazevicE6
	cp Real.h bjazevicE6
	cp Real.cpp bjazevicE6
	cp makefile bjazevicE6
	cp output.txt bjazevicE6
	cp expectedOutput2.txt bjazevicE6
	cp input.txt bjazevicE6
	cp input2.txt bjazevicE6
	cp expectedOutput.txt bjazevicE6
	cp README.txt bjazevicE6
	tar cfvz bjazevicE6.tgz bjazevicE6
	cp bjazevicE6.tgz -r ~tiawatts/cs460drop
