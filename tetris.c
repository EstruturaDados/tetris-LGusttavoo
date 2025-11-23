#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 10     // Capacidade máxima da fila
#define INICIAL 5       // Quantidade de opcoes 

// ---------------------------------------------------------
// ESTRUTURA DA PEÇA ;  "I", "O", "T" e"L",
// " Cada peça poussui um idenificador unico"
// ---------------------------------------------------------
typedef struct {
    char nome;
    int id;
} Peca;

// ---------------------------------------------------------
// ESTRUTURA DA FILA CIRCULAR
// ---------------------------------------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;


// --------------------- PROTÓTIPOS ------------------------
void inicializarFila(Fila *f);
Peca gerarPeca(int id);
int enqueue(Fila *f, Peca nova);
int dequeue(Fila *f);
void exibirFila(Fila f);


// ---------------------------------------------------------
// FUNÇÃO PRINCIPAL >> "Main"
// ---------------------------------------------------------
int main() {
    Fila fila;
    int opcao;
    int contador_id = 0; // id único e crescente das peças

    srand(time(NULL));  // inicializa o gerador de números aleatórios

    inicializarFila(&fila);

    // -----------------------------------------------------
    // Preenche a fila com 5 peças iniciais
    // -----------------------------------------------------
    for (int i = 0; i < INICIAL; i++) {
        enqueue(&fila, gerarPeca(contador_id++));
    }

    // -----------------------------------------------------
    // Loop principal do menu
    // -----------------------------------------------------
    do {
        printf("\n=================================\n");
        printf("        TETRIS STACK - FILA\n");
        printf("=================================\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                if (dequeue(&fila))
                    printf("Peça jogada com sucesso!\n");
                else
                    printf("A fila está vazia! Nenhuma peça para jogar.\n");
                exibirFila(fila);
                break;

            case 2: {
                Peca nova = gerarPeca(contador_id++);
                if (enqueue(&fila, nova))
                    printf("Peça adicionada com sucesso!\n");
                else
                    printf("A fila está cheia! Não é possível inserir nova peça.\n");
                exibirFila(fila);
                break;
            }

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}



// ---------------------------------------------------------
// FUNÇÕES DO PROGRAMA
// ---------------------------------------------------------

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}


// Gera automaticamente uma peça com tipo aleatório
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;

    p.nome = tipos[rand() % 4];
    p.id = id;

    return p;
}


// Insere uma nova peça no final da fila (enqueue)
int enqueue(Fila *f, Peca nova) {
    if (f->quantidade == TAM_FILA)
        return 0;

    f->itens[f->fim] = nova;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;

    return 1;
}


// Remove a peça da frente da fila (dequeue)
int dequeue(Fila *f) {
    if (f->quantidade == 0)
        return 0; 

    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    return 1;
}


// Exibe o estado atual da fila
void exibirFila(Fila f) {
    printf("\nFila de peças:\n");

    if (f.quantidade == 0) {
        printf("[vazia]\n");
        return;
    }

    int i = f.inicio;

    for (int c = 0; c < f.quantidade; c++) {
        printf("[%c %d] ", f.itens[i].nome, f.itens[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\n");
}
