/*
Integrantes: Janaina Ludwig e Alessandro Gambin da Silva
Objetivo: software que simule os algoritmos de alocação de memória para processos
O jogo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <process.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include "memoria.h"
#include "processos.h"

int imprimir = 1;
lista *memoria;
fila_processos *processos;

void mgotoxy(int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}
/*
void proc() {
    while(1) {
        getchar();
        imprimir = 0;
        system("cls");
        int num;
        printf("Escreva um número: ");
        scanf("%d", &num);
        printf("TECLA DIGITADA: %d", num);
        fflush(stdin);
        mgotoxy(0, 0);
        imprimir = 1;
    }
}*/

void proc() {
    char nome[20];
    int tam, tempo;
    while(1) {
        getchar();
        imprimir = 0;
        system("cls");
        printf("Nome do processo: ");
        scanf(" %[^\n]s", nome);
        printf("Tamanho do processo; ");
        scanf("%d", &tam);
        printf("Tempo do processo: ");
        scanf("%d", &tempo);
        novo_processo(processos, nome, tam, tempo);
        fflush(stdin);
        imprimirProcessos(processos);
        getchar();
        fflush(stdin);
        mgotoxy(0, 0);
        imprimir = 1;
    }
}

void memoriap() {
    while(1) {
        if(imprimir) {
            system("cls");
            desenha_memoria(memoria);
        }
        percorre_memoria(memoria);
    }
}

int main(void)
{

    processos = cria_fila();
    /*novo_processo(processos, "Processo um", 10, 5);
    imprimirProcessos(processos);
    */
    printf("\033[22;34m");
    printf("\033[0m");
    system("cls");
    setlocale(LC_ALL, "");
    int algoritmo;
    printf("Escolha o algoritmo para o gerenciamento de memória:\n1 - First fit\n2 - Next fit\n3 - Best fit\n4 - Worst fit\n");
    scanf("%d", &algoritmo);
    struct elemento* (*algMemoria)(lista *li, int tamanho_necessario);
    switch(algoritmo) {
        case 1:
            algMemoria = first_fit;
            break;
        case 4:
            algMemoria = worst_fit;
            break;
        default:
            algMemoria = first_fit;
    }
    printf("Pressione ENTER a qualquer momento para inserir um novo processo na fila.");
    system("cls");





    memoria = cria_lista();

    Processo *p1, p2, p3, p4;
    p1 = (Processo*) malloc(sizeof(Processo));
    strcpy(p1->nome, "Processo um");
    p1->tamanho = 3;
    p1->tempo = 20;
    alocar_processo(memoria, p1, algMemoria);
    strcpy(p2.nome, "Processo dois");
    p2.tamanho = 6;
    p2.tempo = 3;
    alocar_processo(memoria, &p2, algMemoria);
    strcpy(p3.nome, "Processo três");
    p3.tamanho = 3;
    p3.tempo = 20;
    alocar_processo(memoria, &p3, algMemoria);
    strcpy(p4.nome, "Processo quatro");
    p4.tamanho = 5;
    p4.tempo = 7;

    getchar();
    _beginthread(proc,0,NULL);
    _beginthread(memoriap,0,NULL);
    sleep(4);
    alocar_processo(memoria, &p4, algMemoria);

    while(1);

    return 1;
}



