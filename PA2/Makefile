GCC = gcc -std=c99 -Wall -Wshadow -Wvla -pedantic -O3 *.c -o pa2
VAL = valgrind --leak-check=full

SRCS = pa2.c huffman.c

pa2: $(OBJS)
	$(GCC) $(OBJS) -o pa2
	
.c.o:
	$(GCC) -c $*.c

testmemory: pa2
	$(VAL) --log-file=memcheck.txt ./pa2 encoded/gophers_huff.hbt gophers.tree gophers.ori gophers.count gophers.htree gophers.eval

testall: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10
	


test1: pa2
	./pa2 encoded/gophers_huff.hbt gophers.tree gophers.ori gophers.count gophers.htree gophers.eval
	diff gophers.tree tree/gophers_huff.tree
	diff gophers.ori decoded/gophers
	diff gophers.count count/gophers.count
	diff gophers.htree tree/gophers_huff.tree
	diff gophers.eval eval/gophers_huff.eval


test2: pa2
	./pa2 encoded/gophers_nonhuff.hbt gophers_nonhuff.tree gophers_nonhuff.ori gophers_nonhuff.count gophers_nonhuff.htree gophers_nonhuff.eval
	diff gophers_nonhuff.tree tree/gophers_nonhuff.tree
	diff gophers_nonhuff.ori decoded/gophers
	diff gophers_nonhuff.count count/gophers.count
	diff gophers_nonhuff.htree tree/gophers_huff.tree
	diff gophers_nonhuff.eval eval/gophers_nonhuff.eval

test3: pa2
	./pa2 encoded/lorum_huff.hbt lorum_huff.tree lorum_huff.ori lorum_huff.count lorum_huff.htree lorum_huff.eval
	diff lorum_huff.tree tree/lorum_huff.tree
	diff lorum_huff.ori decoded/lorum
	diff lorum_huff.count count/lorum.count
	diff lorum_huff.htree tree/lorum_huff.tree
	diff lorum_huff.eval eval/lorum_huff.eval

test4: pa2
	./pa2 encoded/stone_huff.hbt stone_huff.tree stone_huff.ori stone_huff.count stone_huff.htree stone_huff.eval
	diff stone_huff.tree tree/stone_huff.tree
	diff stone_huff.ori decoded/stone
	diff stone_huff.count count/stone.count
	diff stone_huff.htree tree/stone_huff.tree
	diff stone_huff.eval eval/stone_huff.eval

test5: pa2
	./pa2 encoded/woods_huff.hbt woods_huff.tree woods_huff.ori woods_huff.count woods_huff.htree woods_huff.eval
	diff woods_huff.tree tree/woods_huff.tree
	diff woods_huff.ori decoded/woods
	diff woods_huff.count count/woods.count
	diff woods_huff.htree tree/woods_huff.tree 
	diff woods_huff.eval eval/woods_huff.eval

test6: pa2
	./pa2 encoded/woods_nonhuff.hbt woods_nonhuff.tree woods_nonhuff.ori woods_nonhuff.count woods_nonhuff.htree woods_nonhuff.eval
	diff woods_nonhuff.tree tree/woods_nonhuff.tree
	diff woods_nonhuff.ori decoded/woods
	diff woods_nonhuff.count count/woods.count
	diff woods_nonhuff.htree tree/woods_huff.tree 
	diff woods_nonhuff.eval eval/woods_nonhuff.eval

test7: pa2
	./pa2 encoded/lorum_nonhuff.hbt lorum_nonhuff.tree lorum_nonhuff.ori lorum_nonhuff.count lorum_nonhuff.htree lorum_nonhuff.eval
	diff lorum_nonhuff.tree tree/lorum_nonhuff.tree
	diff lorum_nonhuff.ori decoded/lorum
	diff lorum_nonhuff.count count/lorum.count
	diff lorum_nonhuff.htree tree/lorum_huff.tree
	diff lorum_nonhuff.eval eval/lorum_nonhuff.eval

test8: pa2
	./pa2 encoded/stone_nonhuff.hbt stone_nonhuff.tree stone_nonhuff.ori stone_nonhuff.count stone_nonhuff.htree stone_nonhuff.eval
	diff stone_nonhuff.tree tree/stone_nonhuff.tree
	diff stone_nonhuff.ori decoded/stone
	diff stone_nonhuff.count count/stone.count
	diff stone_nonhuff.htree tree/stone_huff.tree
	diff stone_nonhuff.eval eval/stone_nonhuff.eval

test9: pa2
	./pa2 encoded/binary1_huff.hbt binary1_huff.tree binary1_huff.ori binary1_huff.count binary1_huff.htree binary1_huff.eval
	diff binary1_huff.tree tree/binary1_huff.tree
	diff binary1_huff.ori decoded/binary1
	diff binary1_huff.count count/binary1.count
#	diff binary1_huff.htree tree/binary1_huff.tree
	diff binary1_huff.eval eval/binary1_huff.eval

test10: pa2
	./pa2 encoded/binary1_nonhuff.hbt binary1_nonhuff.tree binary1_nonhuff.ori binary1_nonhuff.count binary1_nonhuff.htree binary1_nonhuff.eval
	diff binary1_nonhuff.tree tree/binary1_nonhuff.tree
	diff binary1_nonhuff.ori decoded/binary1
	diff binary1_nonhuff.count count/binary1.count
#	diff binary1_nonhuff.htree tree/binary1_huff.tree
	diff binary1_nonhuff.eval eval/binary1_nonhuff.eval
	
clean:
	rm -f *.o *.tree *.htree *.count *.eval *.ori *.txt
	
zip:
	zip pa2.zip *.c *.h Makefile
