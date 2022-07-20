#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

typedef struct _no_{
    void *item;
    struct _no_ *proximo;
}SLLNo;

typedef struct _lista_{
    SLLNo *first;
    SLLNo *last;
    int tam;
}lista;

lista *addCreat(){
    lista *l = (lista*)malloc(sizeof(lista));
    if(l!=NULL){
        l->first = NULL;
        l->last =  NULL;
        l->tam=0;
        return l;
    }

    return NULL;
}

int inserir(lista *l,void *item){
    SLLNo *novoNo;
    if(l!=NULL){
        novoNo = (SLLNo*)malloc(sizeof(SLLNo));
        if(novoNo!=NULL){
            novoNo->item = item;
            novoNo->proximo = l->first;
            l->first = novoNo;
            l->tam++;

            if (l->tam == 1) {
                l->last = novoNo;
            }

            return 1;
        }
    }
    return 0;
}

void imprimir(lista* l, void (*allLista)(void*)){

    if(l == NULL){
        return;
    }

    SLLNo *aux = l->first;
    while(aux!=NULL){
        allLista(aux->item);
        aux = aux->proximo;
    }
}

void concatenarListas(lista *l1, lista *l2) {

    if (l1->first == NULL){
        l1->first = l2->first;
        l1->tam = l2->tam;
        l1->last = l2->last;
        return;
    }

    if (l2->first == NULL) return;

    SLLNo* temp = l1->last;

    temp->proximo = l2->first;
    l1->last = l2->last;
    l1->tam = l1->tam + l2->tam;

}

void desalocarLista(lista *l) {

    while(l->first != NULL) {
        SLLNo *temp = l->first->proximo;
        free(l->first);
        l->first = temp;
    }

    free(l);
}
