
list: list.o
	gcc symtablelist.c testsymtab.c -Wall -pedantic -ansi

hash: hash.o
	gcc symtablehash.c testsymtab.c -Wall -pedantic -ansi

list.o: symtablelist.c
	gcc symtablelist.c -c -Wall -pedantic -ansi

hash.o: symtablehash.c
	gcc symtablehash.c -c -Wall -pedantic -ansi

clean:
	rm -rf *o
	rm *out
