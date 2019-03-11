#Peter Golden, Anthony Caligure

# Specifiy the target
make:	prog4swap

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
prog4swap:	driver.o Loop.o Optimal.o LeastRecently.o Fifo.o RandomReplace.o ClockReplace.o EightyTwenty.o NoLocality.o
	g++ driver.o Loop.o Optimal.o LeastRecently.o Fifo.o RandomReplace.o ClockReplace.o EightyTwenty.o NoLocality.o -o prog4swap


# Specify how the object files should be created from source files
driver.o:	driver.cpp
	g++ -c driver.cpp

Loop.o:		Loop.cpp Loop.h
	g++ -c Loop.cpp

Optimal.o:	Optimal.cpp Optimal.h
	g++ -c Optimal.cpp

LeastRecently.o:	LeastRecently.cpp LeastRecently.h
	g++ -c LeastRecently.cpp

Fifo.o:		Fifo.cpp Fifo.h
	g++ -c Fifo.cpp

RandomReplace.o:	RandomReplace.cpp RandomReplace.h
	g++ -c RandomReplace.cpp

ClockReplace.o:		ClockReplace.cpp ClockReplace.h
	g++ -c ClockReplace.cpp

EightyTwenty.o:		EightyTwenty.cpp EightyTwenty.h
	g++ -c EightyTwenty.cpp

NoLocality.o:	NoLocality.cpp NoLocality.h
	g++ -c NoLocality.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o prog4swap
