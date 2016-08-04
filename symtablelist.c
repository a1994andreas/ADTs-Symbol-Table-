#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtable.h"

typedef struct element {
  char *key;
  void *value;
  struct element *next;
} *node_t;

struct symtable {
  unsigned int total;
  node_t head;
};


SymTable_T SymTable_new(void){
    SymTable_T newSymTable_T;
    node_t kombos;
    newSymTable_T = malloc(sizeof(struct symtable));
    kombos = malloc(sizeof(struct element));
    kombos->key= NULL;
    kombos->value= NULL;
    kombos->next= NULL;
    newSymTable_T->total=0;
    newSymTable_T->head=kombos;
    return  newSymTable_T;
}


void SymTable_free(SymTable_T oSymTable){
node_t endiamesos , boh8;
if(oSymTable==NULL)return;
endiamesos=oSymTable->head->next;
while(endiamesos!=NULL){
    boh8=endiamesos;
    free(endiamesos->key);
    free(endiamesos);
    endiamesos=boh8->next;
}
free(oSymTable);
}


unsigned int SymTable_getLength(SymTable_T oSymTable){
assert(oSymTable != NULL);
return (oSymTable->total);
}


int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
    unsigned int i;
    node_t kombos ,endiamesos;
    kombos = malloc(sizeof(struct element));
    if(oSymTable== NULL) exit(EXIT_FAILURE);
    endiamesos=oSymTable->head;
    for(i=0 ; i< oSymTable->total;i++){
        endiamesos=endiamesos->next;
        if(endiamesos->key==pcKey) return 0;
    }
    kombos->key=(char*)pcKey;
    kombos->value=(void*)pvValue;
    kombos->next=oSymTable->head->next;
    oSymTable->head->next=kombos;
    oSymTable->total++;
    return 1;
}


int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    unsigned int i;
    node_t endiamesos ,boh8;
    if(oSymTable== NULL) exit(EXIT_FAILURE);
    endiamesos=oSymTable->head;
    for(i=0 ; i< oSymTable->total;i++){
        boh8=endiamesos;
        endiamesos=endiamesos->next;
        if(endiamesos->key==pcKey){
            boh8->next = endiamesos->next;
            endiamesos->next =NULL;
            oSymTable->total--;
            return 1;
        }
    }
    return 0;
}


int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    unsigned int i=0;
    node_t endiamesos;
    assert(oSymTable != NULL);
    endiamesos=oSymTable->head;
    for(i=0 ; i<oSymTable->total;i++){
        endiamesos=endiamesos->next;
        if(endiamesos->key==pcKey) return 1;
    }
    return 0;
}


void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    unsigned int i=0;
    node_t endiamesos;
    endiamesos=oSymTable->head;
    for(i=0 ; i<oSymTable->total;i++){
        endiamesos=endiamesos->next;
        if(endiamesos->key==pcKey) return endiamesos->value;
    }
    return NULL;
}


void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
unsigned int i=0;
node_t endiamesos;
assert(oSymTable != NULL);
assert(pfApply != NULL);
endiamesos=oSymTable->head;
for(i=0 ; i<oSymTable->total ; i++){
pfApply(endiamesos->key , (void *)endiamesos->value , (void *)pvExtra);
endiamesos=endiamesos->next;
}
}

