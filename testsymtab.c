/*
 * testsymtab.c
 * John Rambo
 * rambo@csd.uoc.gr
 * hy255
 * as3
 */

#include "symtable.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>




void add(const char *pcKey, void *pvValue, void *pvExtra) {
  *(int *)pvValue += *(int *)pvExtra;
}



int main(void) {
  int cc;
  void *a ="a", *b="b" ,*ll="ee", *c="c" , *d="d" , *e="e";
  void *f ="f", *g="g" , *h="h" , *i="j" , *k="k";
  SymTable_T symtable = NULL;
  symtable = SymTable_new();
  SymTable_put(symtable , a , f);
  SymTable_put(symtable , b, g);
  SymTable_put(symtable ,ll, g);
  SymTable_put(symtable , c , h);
  SymTable_put(symtable ,d, i);
  SymTable_put(symtable , e, k);
  printf("-------%d------\n" , SymTable_getLength(symtable));
  SymTable_remove(symtable , (void *)"ee");
  printf("-------%d------\n" , SymTable_getLength(symtable));
  cc=SymTable_contains(symtable, "bfdf");
  if(cc==1)
	printf("the string exists\n");
  else
	printf("the string doesnt exists\n");
  

  return EXIT_SUCCESS;
}
