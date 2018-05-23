#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"
#include "memoria.h"

typedef struct elementoP {
    Processo *dados;
    struct elementoP* proximo;
} ElementoP;

fila_processos* cria_fila() {
    fila_processos *fi = (fila_processos*) malloc(sizeof(fila_processos));
    *fi = NULL;
    return fi;
}

int novo_processo(fila_processos* fila, char *nome, int tamanho, int tempo) {
    if(fila == NULL) {
        return 0;
    }
    printf("1");
    ElementoP *no = (ElementoP*) malloc(sizeof(ElementoP));
    no->dados = (Processo*) malloc(sizeof(Processo));
    if(no->dados == NULL) {
        return 0;
    }
    printf("a");
    ElementoP *aux = *fila;
    printf("b");
    if(no == NULL) {
        return 0;
    }
    printf("2");
    strcpy(no->dados->nome, nome);
    printf("3");
    no->dados->tamanho = tamanho;
    no->dados->tempo = tempo;
    no->proximo = NULL;
    printf("if");
    if(aux == NULL) {
        *fila = no;
        return 1;
    }
    printf("while");
    while(aux->proximo != NULL) {
        aux = aux->proximo;
    }
    printf("o jogo");
    aux->proximo = no;
    printf("4");
    return 1;
}

Processo* retira_processo(fila_processos* fila) {
    ElementoP *no = malloc(sizeof(ElementoP));
    if(*fila == NULL) {
        return NULL;
    }
    no = *fila;
    *fila = no->proximo;
    return no->dados;
}

void imprimirProcessos(fila_processos* fila) {
    ElementoP *no = malloc(sizeof(ElementoP));
    no = *fila;
    while(no->proximo != NULL) {

        printf("Processo %s\nTempo: %d\nTamanho: %d\n", no->dados->nome, no->dados->tempo, no->dados->tamanho);
    }
}


