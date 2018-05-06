#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"

int main(void)
{
    lista *memoria = cria_lista();
    //imprime(memoria);
    Processo p1;
    strcpy(p1.nome, "Processo de teste");
    p1.tamanho = 64;
    p1.tempo = 10;
    alocar_processo(memoria, &p1, worst_fit);
    return 1;
}
