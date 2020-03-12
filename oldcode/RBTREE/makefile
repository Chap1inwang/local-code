srcfile=$(wildcard *.cpp)
objfile=$(subst .c,.o,$(srcfile))
CC=g++

exefile:$(objfile)
	$(CC) -o exefile $(objfile)



%.o:%.c
	$(CC) -c $< 
