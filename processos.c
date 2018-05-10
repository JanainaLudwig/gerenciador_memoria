#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

typedef struct elementoP {
    Processo *dados;
    struct elementoP* proximo;
} ElementoP;

fila_processos* cria_fila() {
    fila_processos *fi = (fila_processos*) malloc(sizeof(fila_processos));
    return fi;
}


int novo_processo(fila_processos* fila, char *nome, int tamanho, int tempo) {
    ElementoP *no = (ElementoP*) malloc(sizeof(ElementoP));
    ElementoP *aux = *fila;
    if(no == NULL) {
        return 0;
    }
    strcpy(no->dados->nome, nome);
    no->dados->tamanho = tamanho;
    no->dados->tempo = tempo;
    no->proximo = NULL;
    if(aux == NULL) {
        *fila = no;
        return 1;
    }
    while(aux->proximo != NULL) {
        aux = aux->proximo;
    }
    aux->proximo = no;
    return 1;
}



