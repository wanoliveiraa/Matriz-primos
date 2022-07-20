#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED


typedef struct _lista_ lista;
lista *addCreat();
int inserir(lista *l,void *item);
void imprimir(lista *l, void (*allLista)(void*));
void concatenarListas(lista *l1, lista *l2);
void desalocarLista(lista *l);

#endif // LISTA_H_INCLUDED
