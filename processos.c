#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"
#include "memoria.h"

#define AMARELO "\033[35m"
#define MAGENTA "\033[33m"

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
    ElementoP *no = (ElementoP*) malloc(sizeof(ElementoP));
    no->dados = (Processo*) malloc(sizeof(Processo));
    if(no->dados == NULL) {
        return 0;
    }
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
    int cor = 0;
    while(no != NULL) {
        if(cor) {
            printf("%s", AMARELO);
            cor--;
        } else {
            printf("%s", MAGENTA);
            cor++;
        }
        printf("\n==========\nProcesso %s\nTamanho: %d\nTempo: %d\n==========", no->dados->nome, no->dados->tempo, no->dados->tamanho);
        printf("\033[0;0m");
        no = no->proximo;
    }
}

int filaVazia(fila_processos* fila) {
    if(*fila == NULL) {
        return 1;
    } else {
        return 0;
    }
}
