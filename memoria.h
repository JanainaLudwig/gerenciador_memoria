#define MEMORIA_MAX 64

typedef struct processo_dados {
    char nome[10];
    int tamanho;
    int tempo;
} Processo;

typedef struct elemento* lista;

lista* cria_lista();
void imprime(lista *li);

//O �ltimo par�metro � o m�todo de gerenciamento de mem�ria (first_fit, worst_fit...)
int alocar_processo(lista *li, Processo *process, struct elemento* (*buscar_elemento)(lista *li, int tamanho_necessario));

//Buscam o endere�o adequado para alocar um elemento
struct elemento* first_fit(lista *li, int tamanho_necessario);
struct elemento* worst_fit(lista *li, int tamanho_necessario);
/*
liberar_processo();
imprime_lista();
buscar memoria();
*/
