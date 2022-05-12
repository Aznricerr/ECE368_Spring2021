GCC = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic *.c -o pa3
VAL = valgrind --leak-check=full

SRCS = pa3.c packed.c

pa3: $(OBJS)
	$(GCC) $(OBJS) -o pa3
	
.c.o:
	$(GCC) -c $*.c

testmemory: pa3
	$(VAL) --log-file=memcheck.txt ./pa3 examples/3.po 3.pr 3.dim 3.pck

testmemory1: pa3
	$(VAL) --log-file=memcheck1.txt ./pa3 examples/100.po 100.pr 100.dim 100.pck

testmemory2: pa3
	$(VAL) --log-file=memcheck2.txt ./pa3 examples/1K.po 1K.pr 1K.dim 1K.pck

testall: test1 test2 test3 test4 test5
	

test1: pa3
	./pa3 examples/3.po 3.pr 3.dim 3.pck
	diff 3.pr examples/3.pr
	diff 3.dim examples/3.dim
	diff 3.pck examples/3.pck



test2: pa3
	./pa3 examples/8.po 8.pr 8.dim 8.pck
	diff 8.pr examples/8.pr
	diff 8.dim examples/8.dim
	diff 8.pck examples/8.pck

test3: pa3
	./pa3 examples/100.po 100.pr 100.dim 100.pck

test4: pa3
	./pa3 examples/500.po 500.pr 500.dim 500.pck

test5: pa3
	./pa3 examples/1K.po 1K.pr 1K.dim 1K.pck
	
clean:
	rm -f *.o *.pck *.pr *.dim *.txt
	
zip:
	zip pa3.zip *.c *.h Makefile