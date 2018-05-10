#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <conio.h>
#include "memoria.h"

/*
PROCESSO: Se o processo == NULL, significa que aquele elemnto da mem�ria est� livre
ENDER_INICIO: Indica o primeiro endere�o da mem�ria(fict�cia) que o elemento pode utilizar
UNIDADES_MEMORIA: Indica quantas unidades de mem�ria o processo utiliza (necess�rio quando o espa�o de mem�ria � livre-
- quando est� ocupada, j� � indicada no processo)
*/
typedef struct elemento {
    struct elemento     *anterior;
    Processo            *processo;
    int                  ender_inicio;
    int                  unidades_memoria;
    struct elemento     *proximo;
} Elemento;

lista* cria_lista() {
    lista* li = (lista*) malloc(sizeof(lista));
    if(li != NULL) {
        //Cria o primeiro elemento da lista: mem�ria totalmente livre (inicia em 0 e possui o tamanho m�ximo da memoria)
        Elemento *no = (Elemento*) malloc(sizeof(Elemento));
        no->proximo = NULL;
        no->anterior = NULL;
        no->ender_inicio = 0;
        no->processo = NULL;
        no->unidades_memoria = MEMORIA_MAX;
        *li = no;
    }
    return li;
}

int alocar_processo(lista *li, Processo *process, struct elemento* (*buscar_elemento)(lista *li, int tamanho_necessario)) {
    if(process->tamanho > MEMORIA_MAX) {
        printf("O processo necessita de mais mem�ria que o total... N�o poder� ser alocado!\n");
        return -1;
    }
    if(li == NULL) {
        return 0;
    }
    //Auxiliar receber� o elemento no qual o processo deve ser alocado
    Elemento *aux = buscar_elemento(li, process->tamanho);
    if(aux == NULL) {
        printf("N�o h� mem�ria suficiente... Aguarde!\n");
        return 0;
    }
    //Se o processo utilizar menos quantidade de mem�ria do que est� livre, o elemento � "quebrado", mantendo parte da mem�ria livre
    if(aux->unidades_memoria != process->tamanho) {
        //Novo espa�o livre de mem�ria
        Elemento *no = (Elemento*) malloc(sizeof(Elemento));
        if(no == NULL) {
            return 0;
        }
        no->processo = NULL;
        no->unidades_memoria = aux->unidades_memoria - process->tamanho;
        no->ender_inicio = aux->ender_inicio + process->tamanho;
        aux->unidades_memoria = process->tamanho;
        //Ajusta os endere�os (anteriores, pr�ximos...)
        if(aux->proximo != NULL) {
            aux->proximo->anterior = no;
        }
        no->proximo = aux->proximo;
        no->anterior = aux;
        aux->proximo = no;
    }
    aux->processo = process;
    //printf("Processo alocado!\n");
    return 1;
}

struct elemento* first_fit(lista *li, int tamanho_necessario){
    Elemento *aux = NULL, *atual = *li;
    //Percorre a lista at� achar um elemento com espa�o suficiente
    while(aux == NULL && atual != NULL) {
        //Se o elemento estiver livre e possuir unidades de memoria suficientes, � nessa posi��o que o processo deve ser alocado
        if(atual->processo == NULL && atual->unidades_memoria >= tamanho_necessario) {
            aux = atual;
        } else {
            atual = atual->proximo;
        }
    }
    return aux;
    //Se n�o encontrou nenhum elemento com espa�o dispon�vel, retornar� NULL
}

struct elemento* worst_fit(lista *li, int tamanho_necessario) {
    //O endere�o da auxiliar incia no primeiro dispon�vel
    Elemento *aux = first_fit(li, tamanho_necessario);
    //Se n�o houver nem um dispon�vel, retorna NULL
    if(aux == NULL) {
        return NULL;
    }
    //O elemento atual � o pr�ximo da lista
    Elemento *atual = aux->proximo;
    //Percorre at� chegar ao final da lista
    while(atual != NULL) {
        if(atual->processo == NULL && atual->unidades_memoria > aux->unidades_memoria) {
            aux = atual;
        }
        atual = atual->proximo;
    }
    return aux;
}

void percorre_memoria(lista *li) {
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    no = *li;
    while(no != NULL) {
        if(no->processo != NULL) {
            printf("Processo: %s\tTempo: %d\n", no->processo->nome, no->processo->tempo);
            if(no->processo->tempo == 0) {
                printf("Desalocar %s\n", no->processo->nome);
                no->processo = NULL;
                liberar_processo(li, no);
            } else {
                no->processo->tempo--;
            }
        }
        no = no->proximo;
    }
    sleep(1);
    printf("-------------\n");
}

int liberar_processo(lista *li, Elemento *liberar) {
    free(liberar->processo);
    liberar->processo = NULL;
    //Se for o primeiro da lista e o pr�ximo for mem�ria livre
    /*if(liberar->anterior == NULL && liberar->proximo->processo == NULL) {
        Elemento *aux = malloc(sizeof(Elemento*));
        aux = liberar->proximo;
        liberar->unidades_memoria += aux->unidades_memoria;
        aux->proximo->anterior = liberar;
        liberar->proximo = aux->proximo;
        free(aux);
        aux = NULL;
    }*/
    //Se existir um elemento antes do que deve ser liberado e ele for livre, une os dois
    if(liberar->anterior != NULL && liberar->anterior->processo == NULL) {
        liberar = liberar->anterior;
        desfragmentar_livres(liberar);
    }
    if(liberar->proximo != NULL && liberar->proximo->processo == NULL) {
        desfragmentar_livres(liberar);
    }
    return 1;
}

void desfragmentar_livres(Elemento *primeiro) {
        Elemento *segundo = malloc(sizeof(Elemento*));
        segundo = primeiro->proximo;
        primeiro->unidades_memoria += segundo->unidades_memoria;
        if(segundo->proximo != NULL) {
            segundo->proximo->anterior = primeiro;
            primeiro->proximo = segundo->proximo;
        } else {
            primeiro->proximo = NULL;
        }
        free(segundo);
        segundo = NULL;
}

void imprime(lista *li) {
    Elemento *no = *li;
    while(no != NULL) {
        if(no->processo != NULL) {
            printf("Nome:%s\tTamanho usado: %d\n", no->processo->nome, no->unidades_memoria);
        } else {
            printf("Mem�ria livre: %d\n", no->unidades_memoria);
        }
        no = no->proximo;
    }
}

void desenha_memoria(lista *li) {
    printf("\033[22;34m");
    printf("\033[0m");
    system("cls");
    setlocale(LC_ALL, "C");
    Elemento *no = *li;
    int i, j = 0, cor = 1;
    //textcolor(4);
    //printf("\033[22;34m");
    printf(" %4c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    //printf("\033[0m");
    while(no != NULL) {
            if(cor == 1) {
                    printf("\x1b[34m"); // AZUL
                    cor--;
               } else {
                    printf("\x1b[32m"); // VERDE
                    cor++;
               }
        for(i = 0; i < no->unidades_memoria; i++) {
            setlocale(LC_ALL, "C");
            if(no->processo != NULL) {

               printf("%3d %c%c%c%c%c%c%c%c%c%c", j, 186, 178, 178, 178, 178, 178, 178, 178, 178, 186);

               if(i == (int) (no->unidades_memoria-1)/2) {
                    setlocale(LC_ALL, "");
                    printf("  %s\tTempo: %d", no->processo->nome, no->processo->tempo);
                    if(no->processo->tempo == 0) printf(" DESALOCANDO...\n");
                    else printf("\n");
               } else {
                    printf("\n");
               }
            } else {
                printf("\x1b[0m");//reset cor
                printf("%3d %c%c%c%c%c%c%c%c%c%c\n", j, 186, 176, 176, 176, 176, 176, 176, 176, 176, 186);
            }
            j++;
        }
    printf("\x1b[0m");//reset cor

   /* printf("\033[22;34m");
        printf(" %4c%c%c%c%c%c%c%c%c%c\n", 186, 196, 196, 196, 196, 196, 196, 196, 196, 186);
        printf("\033[0m");*/
        no = no->proximo;
    }
    printf(" %4c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    setlocale(LC_ALL, "");
    //textcolor(0);
}








