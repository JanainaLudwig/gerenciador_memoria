typedef struct processo_dados {
    char nome[20];
    int tamanho;
    int tempo;
} Processo;

typedef struct elementoP* fila_processos;

fila_processos* cria_fila();
int novo_processo(fila_processos* fila, char *nome, int tamanho, int tempo);