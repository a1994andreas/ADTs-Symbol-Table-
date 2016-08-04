#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "symtable.h"
#include <stddef.h>
#define HASH_MULTIPLIER 65599
void expand_function(SymTable_T oSymTable);
typedef struct element {
  char *key;
  void *value;
  struct element *next;
} *node_t;

struct symtable {
  unsigned int total;
  node_t pinakas[509];
};

/*GLOBAL VARIABLES*/
int const resize_array[8]={509 , 1021 , 2053 , 4093 , 8191 ,16381 , 32771 , 65521};
int resize_int=0;
/*----------------*/
unsigned int SymTable_hash(const char *pcKey)
{
  size_t ui;
  unsigned int uiHash = 0U;
  for (ui = 0U; pcKey[ui] != '\0'; ui++)
    uiHash = uiHash * (unsigned int)HASH_MULTIPLIER + pcKey[ui];
  return uiHash;
}
SymTable_T SymTable_new(void){
    SymTable_T newSymTable_T;
    node_t kombos;
    size_t i=0;
    newSymTable_T = malloc(sizeof(struct symtable));
    kombos = malloc(sizeof(struct element));
    kombos->key =NULL;
    kombos->value = NULL;
    kombos->next = NULL;
    newSymTable_T->total=0;
    for(i=0 ; i<resize_array[resize_int] ; i++){
        newSymTable_T->pinakas[i] = kombos;
    }
    return newSymTable_T;
}
void SymTable_free(SymTable_T oSymTable){
    node_t endiamesos , boh8;
    int i;
    for(i=0 ;i<resize_array[resize_int] ; i++){
        endiamesos=oSymTable->pinakas[i]->next;
        while(endiamesos!=NULL){
            boh8=endiamesos;
            free(endiamesos->key);
            free(endiamesos);
            endiamesos=boh8->next;
        }
    }
    free(oSymTable);
}
unsigned int SymTable_getLength(SymTable_T oSymTable){
    assert(oSymTable != NULL);
    return oSymTable->total;
}
int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
    node_t kombos , kombos2;
    unsigned int i;
    /*
     *check if we need to resize our hashtable
    */
    if(resize_array[resize_int]==oSymTable->total){
    expand_function(oSymTable);
    }

    kombos = malloc(sizeof(struct element));
    kombos->key= malloc((strlen(pcKey) + 1)*sizeof(char));
    kombos->key=(char*)pcKey;
    kombos->value=(void*)pvValue;
    i=(SymTable_hash(pcKey)%resize_array[resize_int]);
    kombos2=oSymTable->pinakas[i];
    kombos->next=kombos2;
    oSymTable->pinakas[i]=kombos;
    oSymTable->total++;
    return 1;
}
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    unsigned int i;
    node_t endiamesos , prohgoumenos;
    i=(SymTable_hash(pcKey)%resize_array[resize_int]);
    prohgoumenos=oSymTable->pinakas[i];
    endiamesos=oSymTable->pinakas[i];
    while(endiamesos!=NULL){
        prohgoumenos=endiamesos;
        if(endiamesos->key==pcKey){
            prohgoumenos->next=endiamesos->next;
            endiamesos->next=NULL;
            oSymTable->total--;
	    return 1;
        }
        endiamesos=endiamesos->next;
    }
    return 0;
}
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    unsigned int i;
    node_t endiamesos;
    i=(SymTable_hash(pcKey)%resize_array[resize_int]);
    endiamesos=oSymTable->pinakas[i];
    while(endiamesos!=NULL){
        if(endiamesos->key==pcKey) return 1;
        endiamesos=endiamesos->next;
    }
    return 0;
}
void* SymTable_get(SymTable_T oSymTable, const char *pcKey){
    unsigned int i;
    node_t endiamesos;
    i=(SymTable_hash(pcKey)%resize_array[resize_int]);
    endiamesos=oSymTable->pinakas[i]->next;
    while(endiamesos!=NULL){
        if(endiamesos->key==pcKey) return endiamesos->value;
        endiamesos=endiamesos->next;
    }
    return NULL;
}
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
    int k=0;
    node_t endiamesos;
    for( k=0 ; k<resize_array[resize_int] ; k++){
      endiamesos=oSymTable->pinakas[k]->next;
      while(endiamesos!=NULL){
	pfApply(endiamesos->key ,(void *) endiamesos->value , (void *)pvExtra);
	endiamesos=endiamesos->next;
    }
    
   }
}




/*extra function for the resize*/
void expand_function(SymTable_T oSymTable){
int k=0; 
node_t endiamesos;
SymTable_T newSymtable = SymTable_new();/*create a new one*/
resize_int+=1;/*increase the size of hashtable*/
for(k=0 ; k<resize_array[resize_int-1] ; k++){ /*copy each element to the new array*/
   endiamesos=oSymTable->pinakas[k]->next;
   while(endiamesos!=NULL){
	SymTable_put(newSymtable, endiamesos->key,endiamesos->value);
	endiamesos=endiamesos->next;
  }
  
}
oSymTable=newSymtable;

}


