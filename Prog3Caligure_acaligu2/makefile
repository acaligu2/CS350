#
# Specifiy the target
make:	prog3ipc

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
prog3ipc:		prog3ipc.o
	gcc prog3ipc.o -o prog3ipc -lrt


# Specify how the object files should be created from source files
prog3ipc.o:	prog3ipc.c
	gcc -c prog3ipc.c


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o prog3ipc
