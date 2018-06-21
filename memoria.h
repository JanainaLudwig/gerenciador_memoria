/**
 * Integrantes: Janaina Ludwig (1932802) e Alessandro Gambin da Silva (1930648)
 */

int MEMORIA_MAX;

typedef struct processo_dados {
    char nome[20];
    int tamanho;
    int tempo;
} Processo;

typedef struct elemento* lista;


lista* cria_lista(int tamanho);
void imprime(lista *li);
void desenha_memoria(lista *li);

//O último parâmetro é o método de gerenciamento de memória (first_fit, worst_fit...)
int alocar_processo(lista *li, Processo *process, struct elemento* (*buscar_elemento)(lista *li, int tamanho_necessario));

//Buscam o endereço adequado para alocar um elemento
struct elemento* first_fit(lista *li, int tamanho_necessario);
struct elemento* next_fit(lista *li, int tamanho_necessario);
struct elemento* best_fit(lista *li, int tamanho_necessario);
struct elemento* worst_fit(lista *li, int tamanho_necessario);

void percorre_memoria(lista *li);

int liberar_processo(struct elemento *liberar);

//Usado para unir um primeiro elemento livre ao próximo elemento (que deve ser livre)
void desfragmentar_livres(struct elemento *primeiro);




