#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"

/*
PROCESSO: Se o processo == NULL, significa que aquele elemnto da memória está livre
ENDER_INICIO: Indica o primeiro endereço da memória(fictícia) que o elemento pode utilizar
UNIDADES_MEMORIA: Indica quantas unidades de memória o processo utiliza (necessário quando o espaço de memória é livre-
- quando está ocupada, já é indicada no processo)
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
        //Cria o primeiro elemento da lista: memória totalmente livre (inicia em 0 e possui o tamanho máximo da memoria)
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
        printf("O processo necessita de mais memória que o total... Não poderá ser alocado!");
        return -1;
    }
    if(li == NULL) {
        return 0;
    }
    //Auxiliar receberá o elemento no qual o processo deve ser alocado
    Elemento *aux, *no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL) {
        return 0;
    }
    no->processo = process;
    no->unidades_memoria = process->tamanho;
    //Recebe o endereço de um elemento que tenha memória livre e precisará ser ajustado se aida sobrar espaço
    aux = buscar_elemento(li, no->unidades_memoria);
    if(aux == NULL) {
        printf("Não há memória suficiente... Aguarde!");
    }
    if(aux->unidades_memoria == no->unidades_memoria) {
        aux->processo = no->processo;
        printf("Processo alocado!");
        return 1;
    }
    return 0;
}

struct elemento* first_fit(lista *li, int tamanho_necessario){
    Elemento *aux = NULL, *atual = *li;
    //Percorre a lista até achar um elemento com espaço suficiente
    while(aux == NULL && atual != NULL) {
        //Se o elemento estiver livre e possuir unidades de memoria suficientes, é nessa posição que o processo deve ser alocado
        if(atual->processo == NULL && atual->unidades_memoria >= tamanho_necessario) {
            aux = atual;
        } else {
            atual = atual->proximo;
        }
    }
    return aux;
    //Se não encontrou nenhum elemento com espaço disponível, retornará NULL
}

struct elemento* worst_fit(lista *li, int tamanho_necessario) {
    //O endereço da auxiliar incia no primeiro disponível
    Elemento *aux = first_fit(li, tamanho_necessario);
    //Se não houver nem um disponível, retorna NULL
    if(aux == NULL) {
        return NULL;
    }
    //O elemento atual é o próximo da lista
    Elemento *atual = aux->proximo;
    //Percorre até chegar ao final da lista
    while(atual != NULL) {
        if(atual->processo == NULL && atual->unidades_memoria > aux->unidades_memoria) {
            aux = atual;
        }
        atual = atual->proximo;
    }
    return aux;
}



/*
int worst_fit(lista li, Processo *process) {
    if(li != NULL) {
        Elemento *no = (Elemento*) malloc(sizeof(Elemento));
        no->processo = process;
        no->unidades_memoria = process->tamanho;
        //Memória totalmente livre (só há um elemento ocupando toda a memória)
        if(li->proximo == NULL) {
            if(no->unidades_memoria >= MEMORIA_MAX)
                return -1;
            no->anterior = NULL;
            no->proximo = li;
            no->ender_inicio = 0;
            li->anterior = no;
            li->ender_inicio = no->unidades_memoria;
            li->unidades_memoria -= no->unidades_memoria;
            li = no;
            return 1;
        } else {
            while(li->proximo != NULL) {


            }
        }
    }


}

*/


/*
int worst_fit(lista li, int tamanho_processo, struct elemento *no) {
    if(li != NULL) {
        //Memória totalmente livre (só há um elemento ocupando toda a memória)
        if(li->proximo == NULL) {
            if(no->unidades_memoria < MEMORIA_MAX)
                return -1;
            no = li;
            return 1;
        } else {
            while(li->proximo)
        }
    }
}
*/

void imprime(lista *li) {
    Elemento *no = *li;
    while(no != NULL) {
        printf("Tamanho usado: %d\n", no->unidades_memoria);
        no = no->proximo;
    }
}
