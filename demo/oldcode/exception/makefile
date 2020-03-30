srcfile=$(wildcard *.cpp)
objfile=$(subst .cpp,.o,$(srcfile))
CC=g++

all:exefile
exefile:$(objfile)
	$(CC) $(objfile) -g -o exefile 



%.o:%.c
	$(CC) $< -g -c -I /usr/include    

#定义伪目标，防止有歧义
.PHONY:clean

clean:
	-@rm -f *.o
	rm -f exefile
