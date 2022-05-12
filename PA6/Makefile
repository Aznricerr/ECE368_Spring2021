GCC = gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -O3 *.c -o pa6
VAL = valgrind --leak-check=full

SRCS = pa6.c gridTrav.c

pa6: $(OBJS)
	$(GCC) $(OBJS) -o pa6
	
.c.o:
	$(GCC) -c $*.c

testmemory: pa6
	$(VAL) --log-file=memcheck.txt ./pa6 examples/4_5.b 4_5.t 4_5.f 4_5.p

testmemory1: pa6
	$(VAL) --log-file=memcheck1.txt ./pa6 examples/5_4.b 5_4.t 5_4.f 5_4.p



testall: test1 test2 test3 test4 
	

test1: pa6
	./pa6 examples/4_5.b 4_5.t 4_5.f 4_5.p
	diff 4_5.t examples/4_5.t
	diff 4_5.f examples/4_5.f
	diff 4_5.p examples/4_5.p



test2: pa6
	./pa6 examples/5_4.b 5_4.t 5_4.f 5_4.p
	diff 5_4.t examples/5_4.t
	diff 5_4.f examples/5_4.f
	diff 5_4.p examples/5_4.p

test3: pa6
	./pa6 examples/5_5.b 5_5.t 5_5.f 5_5.p
	diff 5_5.t examples/5_5.t
	diff 5_5.f examples/5_5.f
	diff 5_5.p examples/5_5.p

test4: pa6
	./pa6 examples/7_7.b 7_7.t 7_7.f 7_7.p
	diff 7_7.t examples/7_7.t
	diff 7_7.f examples/7_7.f
	diff 7_7.p examples/7_7.p
	
clean:
	rm -f *.t *.f *.p *.txt
	
zip:
	zip pa6.zip *.c *.h Makefile