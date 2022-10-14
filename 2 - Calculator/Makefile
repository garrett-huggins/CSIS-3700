project2: dictionary.o fraction.o project2.o
	g++ -o project2 project2.o dictionary.o fraction.o

project2.o: project2.cc dictionary.h stack.h
	g++ -c project2.cc

dictionary.o: dictionary.cc dictionary.h fraction.h
	g++ -c dictionary.cc

fraction.o: fraction.cc fraction.h
	g++ -c fraction.cc