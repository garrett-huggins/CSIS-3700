project1: fraction.o point.o project1.o
	g++ -o project1 project1.o point.o fraction.o

project1.o: project1.cc point.h fraction.h
	g++ -c project1.cc

point.o: point.cc point.h fraction.h
	g++ -c point.cc

fraction.o: fraction.cc fraction.h
	g++ -c fraction.cc