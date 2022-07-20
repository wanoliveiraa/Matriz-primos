/**
 * @file main.c
 * @author Walderney Oliveira Azevedo
 * @brief
 * @version 0.1
 * @date 2022-06-16
 *
 * @copyright Copyright (c) 2022
 *
 * Trabalho de Sistema Operacional
 * Calcular a quantidade de números primos em uma determinada matriz de forma sequencial e paralela depois inserir em uma lista os numeros primos e suas posições.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "lista.h"
#include<locale.h>

//Macros
//Características da Matriz
#define n 20000
#define m 20000
//#define SEED 7
//Numeros de threads e valor para percorrer a subMatriz
#define Qthreads 4
#define valorExploracao 625

//Definindo variaveis globais
int **mat;
int totalPrimos = 0;
int totalPrimosSeq = 0;
int xAtual = 0;
int yAtual = 0;
int contadorCheck = 0;

//Definindo Threads e Mutex
pthread_t threads[Qthreads];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Lista
typedef struct _coordenadaPrimo_{
    int valor;
    int x;
    int y;
}coordenadaPrimo;

coordenadaPrimo *aux;
lista *primos = NULL;

void allLista(void* all){
    coordenadaPrimo* aux = (coordenadaPrimo*) all;
    printf("----------------------------------\n");
    printf("primo:%d, (x:%d, y:%d)\n" , aux->valor, aux->x, aux->y);
}


void pause(){
    #ifdef WIN64
        system("pause");
    #else
        system("read -p \"presione uma tela\"saindo");
    #endif
}
/**
 *  Cria e retorna uma matriz
 *
 * @param ln Numeros de linhas da matriz
 * @param cl Numeros de colunas da matriz
 * @return int**
 */
int **alocaMatriz(int ln,int cl){

    int **mat;
    int i,j;

    //srand(time(NULL));

    if(mat == NULL){
        return NULL;
    }

    mat = (int**)malloc(ln*sizeof(int*));

    for (i = 0; i < ln; i++){
        mat[i]=(int*)malloc(cl*sizeof(int));
    }

   // int contador = 1;

    for (i = 0; i < ln; i++){
        for(j = 0;j < cl; j++ ){
            mat[i][j]= rand() % 30000;
        }
    }

    return mat;

}
/**
 * Libera o espaço alocado da matriz.
 *
 * @param mat Matriz
 */
void liberaMatriz(int **mat){
    int i;

    for (i = 0; i < n; i++){
        free(mat[i]);
    }
    free(mat);
}
/**
 * Verifica se o numero é primo
 *
 * @param num numero a ser verificado
 * @return int
 */
int isPrimo(int num) {
	double limit;
	int i = 3, control = 1;

	if (num == 2) {
		return 1;
	}

	else if (num < 2 || num % 2 == 0) {
		return 0;
	}

	else {
		limit = sqrt(num) + 1;
		while (i < limit && control) {
			if (num % i == 0) {
				control = 0;
			}
			i += 2;
		}
		return control;
	}
}

/**
 * Realiza a busca sequencial pela Matriz
 *
 */
void  verificarPrimoSeq(){

    int i,j,number;
    for(i = 0; i < n; i++){
        for(j = 0; j<m; j++){
            number=mat[i][j];
            totalPrimosSeq+=isPrimo(number);
            if(isPrimo(number)==1){
                coordenadaPrimo *aux = (coordenadaPrimo*)malloc(sizeof(coordenadaPrimo));
                aux->valor=number;
                aux->x=i;
                aux->y=j;
                inserir(primos,aux);
            }

        }
    }

}
/**
 * Imprime os elementos da Matriz
 *
 * @param mat Matriz
 */
void exibirMatriz(int **mat){
    int i,j;
    for (i = 0; i < n; i++){
        for(j = 0;j < m; j++ ){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}
/**
 * Execução da thread.
 * Quando a thread é criada e iniciada ela irá thread executará esse método.
 *
 * @param arg Dados não globais
 * @return void*
 */
//rotina da threads
void* contarPrimosParalelo(void* arg){

    while(1) {

        pthread_mutex_lock(&mutex);
        int inicioX = xAtual;
        int inicioY = yAtual;

        xAtual += valorExploracao;

        if (xAtual >= m) {
            xAtual = 0;
            yAtual += valorExploracao;
        }
        pthread_mutex_unlock(&mutex);

        if (inicioY >= m) {
            pthread_exit(NULL);
        }

        int totalPrimosLocal = 0;
        lista *listaLocal = addCreat();

        for (int x = inicioX; x < inicioX + valorExploracao; x++) {
            for (int y = inicioY; y < inicioY + valorExploracao; y++) {
                if (isPrimo(mat[y][x])) {
                    totalPrimosLocal++;
                    coordenadaPrimo* numP = (coordenadaPrimo*) malloc(sizeof(coordenadaPrimo));
                    numP->valor = mat[y][x];
                    numP->x = y;
                    numP->y = x;
                    inserir(listaLocal, numP);
                }
            }
        }


        //imprimir(listaLocal, allLista);

        pthread_mutex_lock(&mutex);
        totalPrimos += totalPrimosLocal;
        concatenarListas(primos, listaLocal);
        pthread_mutex_unlock(&mutex);
    }
}
/**
 * Realiza a busca de forma paralela pela Matriz
 *
 */
void processarMatriz(){
    pthread_t threads_id[Qthreads];

    int k=0;
    for(k=0;k<Qthreads;k++){
        pthread_create(&(threads_id[k]), NULL, contarPrimosParalelo, NULL);
    }
    for(k=0;k<Qthreads;k++){
        pthread_join(threads_id[k], NULL);
    }

   // printf("\nQuantidade de Primos: %d\n", totalPrimos);
}

void  main(){
    clock_t inicioSeq;
	clock_t fimSeq;
	clock_t inicioPll;
	clock_t fimPll;
    primos = addCreat();
    mat=alocaMatriz(n,m);
    //exibirMatriz(mat);


    /*
    inicioSeq=clock();
    verificarPrimoSeq();
    fimSeq=clock();
    printf("\nExistem %d Primos\n", totalPrimosSeq);
    printf("Time: %.3f\n", (double)(fimSeq - inicioSeq)/CLOCKS_PER_SEC);
   // pause();
    */


    inicioPll=clock();
    processarMatriz();
    fimPll=clock();
    printf("Existem %d Primos\n", totalPrimos);
    printf("Time: %.3f\n", (double)(fimPll - inicioPll)/CLOCKS_PER_SEC);
    pause();


    //imprimir(primos,allLista);

   // printf("Tamaho da lista: %d\n", primos->tam);

    liberaMatriz(mat);

    desalocarLista(primos);

}
