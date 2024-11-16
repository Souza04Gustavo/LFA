#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para usleep()

#define RESET "\033[0m"
#define WHITE "\033[47m" // Fundo branco para os quarteirões
#define EMPTY "\033[40m" // Fundo preto para as ruas
#define CAR "\033[43m"   // Fundo amarelo para representar o carro
#define CLEAR_SCREEN "\033[H" // Move o cursor para o topo

// Dimensões do quarteirão e mapa
#define TAMANHO_QUARTEIRAO 3
#define NUMERO_QUARTEIROES 3

// Função para desenhar linhas em branco como espaçamento inicial
void adicionar_espaco_inicial(int linhas) {
    for (int i = 0; i < linhas; i++) {
        printf("\n");
    }
}

// Função para desenhar o sistema de trânsito
void desenhar_sistema(int carro_x, int carro_y) {
    int largura_total = NUMERO_QUARTEIROES * (TAMANHO_QUARTEIRAO + 1) + 1;

    printf(CLEAR_SCREEN); // Move o cursor para o topo do terminal
    adicionar_espaco_inicial(5); // Adiciona 5 linhas em branco antes do mapa
    for (int linha = 0; linha < largura_total; linha++) {
        for (int coluna = 0; coluna < largura_total; coluna++) {
            // Verifica se a posição atual é do carro
            if (linha == carro_x && coluna == carro_y) {
                printf(CAR "  " RESET); // Carro na posição atual
            }
            // Posição de rua
            else if (linha % (TAMANHO_QUARTEIRAO + 1) == 0 || coluna % (TAMANHO_QUARTEIRAO + 1) == 0) {
                printf(EMPTY "  " RESET);
            }
            // Posição de quarteirão
            else {
                printf(WHITE "  " RESET);
            }
        }
        printf("\n");
    }
}

// Função para mover o carro em linha reta (exemplo)
void mover_carro() {
    // Configuração inicial do carro (posição central de uma rua horizontal)
    int carro_x = TAMANHO_QUARTEIRAO + 1; // Rua horizontal após o primeiro quarteirão
    int carro_y = 1; // Começa na borda esquerda

    // Dimensões do mapa
    int largura_total = NUMERO_QUARTEIROES * (TAMANHO_QUARTEIRAO + 1) + 1;

    // Movimento do carro para a direita
    while (carro_y < largura_total) {
        desenhar_sistema(carro_x, carro_y); // Atualiza o mapa com a posição do carro
        usleep(2000000); // Pausa de 2s
        carro_y = carro_y + 2; // Move o carro para a direita
    }
}

int main() {
    // Mensagem inicial
    printf("Simulação de Veículo em Movimento no Sistema de Trânsito:\n\n");
    printf("Pressione Ctrl+C para sair.\n");
    adicionar_espaco_inicial(5); // Empurra o mapa para baixo
    usleep(2000000); // Pausa de 2 segundos para leitura
    mover_carro(); // Inicia o movimento do carro

    return 0;
}
