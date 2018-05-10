#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "memoria.h"

int main(void)
{

    setlocale(LC_ALL, "");
    lista *memoria = cria_lista();
    //"A main está ridícula" - Janai 09/05/2018
    //imprime(memoria);
    Processo *p1, p2, p3, p4;
    p1 = (Processo*) malloc(sizeof(Processo));
    strcpy(p1->nome, "Processo um");
    p1->tamanho = 15;
    p1->tempo = 6;
    alocar_processo(memoria, p1, worst_fit);
    strcpy(p2.nome, "Processo dois");
    p2.tamanho = 9;
    p2.tempo = 4;
    alocar_processo(memoria, &p2, worst_fit);
    strcpy(p3.nome, "Processo três");
    p3.tamanho = 3;
    p3.tempo = 4;
    alocar_processo(memoria, &p3, worst_fit);
    strcpy(p4.nome, "Processo quatro");
    p4.tamanho = 5;
    p4.tempo = 3;

    //imprime(memoria);
    //desenha_memoria(memoria);

    //system("cls");
    getchar();
    for(int i = 0; i < 25; i++) {
        desenha_memoria(memoria);
        percorre_memoria(memoria);
        //getchar();
        if(i == 5) alocar_processo(memoria, &p4, worst_fit);
        if(i==25) getchar();
        else system("cls");
    }
    return 1;
}
