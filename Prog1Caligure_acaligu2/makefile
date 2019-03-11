#
# Specifiy the target
make:	prog1sorter prog1generator

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
prog1generator:		prog1generator.o
	gcc prog1generator.o -o prog1generator

prog1sorter:	prog1sorter.o timer.o
	gcc prog1sorter.o timer.o -o prog1sorter
	
# Specify how the object files should be created from source files
prog1generator.o:	prog1generator.c
	gcc -c prog1generator.c

prog1sorter.o:		prog1sorter.c
	gcc -c prog1sorter.c

timer.o:		timer.h timer.c
	gcc -c timer.c

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o prog1sorter, prog1generator timer.o
