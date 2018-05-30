typedef struct processo_dados Processo;

typedef struct elementoP* fila_processos;

fila_processos* cria_fila();
int novo_processo(fila_processos* fila, char *nome, int tamanho, int tempo);
Processo* retira_processo(fila_processos* fila);
void imprimirProcessos(fila_processos* fila);
//Verifica de a fila está vazia
int filaVazia(fila_processos* fila);

