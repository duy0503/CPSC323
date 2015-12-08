default: main

main: main.o clean_up.o generator.o parser.o
	g++ main.o clean_up.o generator.o parser.o -o main

clean_up.o: clean_up.cpp clean_up.h std_types.h
	g++ -c clean_up.cpp
generator.o: generator.cpp generator.h std_types.h
	g++ -c generator.cpp
parser.o: parser.cpp parser.h std_types.h
	g++ -c parser.cpp
clean:
	rm *o main finalv2.txt final.cpp *~
