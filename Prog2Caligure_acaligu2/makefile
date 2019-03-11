#
# Specifiy the target
make:	prog2tree

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
prog2tree:		prog2tree.o
	gcc prog2tree.o -o prog2tree


# Specify how the object files should be created from source files
prog2tree.o:	prog2tree.c
	gcc -c prog2tree.c


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o prog2tree
