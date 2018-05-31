/*
Integrantes: Janaina Ludwig e Alessandro Gambin da Silva
Objetivo: software que simule os algoritmos de alocação de memória para processos
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

//Controle da impressao da memória
int imprimir = 1;

//Listas de processos e memória
lista *memoria;
fila_processos *processos;

//Ponteiro para algoritmo de alocação
struct elemento* (*algMemoria)(lista *li, int tamanho_necessario);

//Verifica de a fila de processos não está vazia e aloca os processos
void percorreFilaProcessos();
//Insere os processos na fila antes de iniciar a execução
void iniciarFilaProcessos();
//Insere um novo processo na fila durante a execução
void novoProcessoFila();

//Percorre a memória, desalocando processos e printando a memória
void percorreMemoria();

void mgotoxy(int x, int y);

int main(void)
{
    //Gambiarra para usar cores
    printf("\033[22;34m");
    printf("\033[0m");
    system("cls");

    //Tela cheia
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);

    setlocale(LC_ALL, "");

    int tam;
    printf("Defina o tamanho da memória: ");
    scanf("%d", &tam);
    //Inicialização das listas
    processos = cria_fila();
    memoria = cria_lista(tam);


    //Instruções e preparações para iniciar
    char aux;
    fflush(stdin);
    printf("Escolha o algoritmo para o gerenciamento de memória:\n1 - First fit\n2 - Next fit\n3 - Best fit\n4 - Worst fit\n");
    aux = getch();
    switch(aux) {
        case '1':
            algMemoria = first_fit;
            break;
        case '2':
            algMemoria = next_fit;
            break;
        case '3':
            algMemoria = best_fit;
            break;
        case '4':
            algMemoria = worst_fit;
            break;
        default:
            algMemoria = first_fit;
    }

    do {
        imprimirProcessos(processos);
        printf("\n\nDeseja inserir um processo na fila?\n1-Sim\t2-Não\n");
        fflush(stdin);
        aux = getch();
        if(aux == '1') {
            iniciarFilaProcessos();
        }
    } while(aux != '2');


    system("cls");

    printf("Pressione ENTER a qualquer momento durante a execução para inserir um novo processo na fila.\n");
    printf("Se quiser que um processo tenha tempo infinito, o tempo deve ser negativo.\n\n");

    system("pause");
    system("cls");

    //Inicialização dos threads
    _beginthread(novoProcessoFila, 0, NULL);
    _beginthread(percorreMemoria, 0, NULL);
    _beginthread(percorreFilaProcessos, 0, NULL);

    while(1);

    return 1;
}

void mgotoxy(int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void novoProcessoFila() {
    char nome[20];
    int tam, tempo;
    while(1) {
        getchar();
        imprimir = 0;
        system("cls");
        printf("Nome do processo: ");
        scanf(" %[^\n]s", nome);
        printf("Tamanho do processo: ");
        scanf("%d", &tam);
        printf("Tempo do processo: ");
        scanf("%d", &tempo);
        novo_processo(processos, nome, tam, tempo);
        fflush(stdin);
        //mgotoxy(0, 0);
        imprimir = 1;
    }
}

void iniciarFilaProcessos() {
    char nome[20];
    int tam, tempo;

    printf("\nNome do processo: ");
    scanf(" %[^\n]s", nome);
    printf("Tamanho do processo: ");
    scanf("%d", &tam);
    printf("Tempo do processo: ");
    scanf("%d", &tempo);

    novo_processo(processos, nome, tam, tempo);
}

void percorreMemoria() {
    while(1) {
        if(imprimir) {
            system("cls");
            desenha_memoria(memoria);
        }
        percorre_memoria(memoria);
    }
}

void percorreFilaProcessos() {
    int aux;
    while(1) {
        if(!filaVazia(processos)) {
            Processo *processoRetirado = retira_processo(processos);
            do {
                aux = alocar_processo(memoria, processoRetirado, algMemoria);
                if(aux == 0) {
                    sleep(1);
                }
            } while(aux == 0);
        }
    }
}
