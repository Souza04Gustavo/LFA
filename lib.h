#include <string.h>
#include <stdio.h>

#define max_estados 10
#define max_transicoes 100
#define max_alfabeto 5

// estrutura para transicao
typedef struct {
    int estado_atual;
    char simbolo;
    int prox_estado;
} Transicao;

// estrutura para o AFD
typedef struct {
    int num_estados;
    int estado_inicial;
    int estados_aceitos[max_estados];
    int estados_de_aceitacao;
    char alfabeto[max_alfabeto];
    Transicao transitions[max_transicoes];
    int num_transicoes;
} Automaton;

// funcao para verificar se o estado eh um estado de aceitacao
int eh_estado_aceito(Automaton *afd, int estado) {
    for (int i = 0; i < afd->estados_de_aceitacao; i++) {
        if (afd->estados_aceitos[i] == estado) {
            return 1; // estado de aceitacao
        }
    }
    return 0;
}

// funcao para avancar para o prox estado com base no simbolo atual
int pegar_prox_estado(Automaton *afd, int estado_atual, char simbolo) {
    for (int i = 0; i < afd->num_transicoes; i++) {
        if (afd->transitions[i].estado_atual == estado_atual && afd->transitions[i].simbolo == simbolo) {
            return afd->transitions[i].prox_estado; // retorna o prox estado se tiver
        }
    }
    return -1; // transicao invalida error
}

// simula o AFD com base em uma palavra de entrada
int simulate_afd(Automaton *afd, char *palavra) {
    int estado_atual = afd->estado_inicial;
    printf("Estado inicial: %d\n", estado_atual);
    
    // processa cada simbolo da palavra
    for (int i = 0; i < strlen(palavra); i++) {
        char simbolo = palavra[i];
        int prox_estado = pegar_prox_estado(afd, estado_atual, simbolo);
        
        if (prox_estado == -1) {
            printf("Erro: Transicao invalida ao ler o simbolo '%c'\n", simbolo);
            return 0; // palavra rejeitada
        }

        printf("Transicao: (%d, '%c') -> %d\n", estado_atual, simbolo, prox_estado);
        estado_atual = prox_estado;
    }

    // verifica se terminou em um estado de aceitacao
    if (eh_estado_aceito(afd, estado_atual)) {
        printf("Palavra aceita. Estado final: %d\n", estado_atual);
        return 1;
    } else {
        printf("Palavra rejeitada. Estado final: %d\n", estado_atual);
        return 0;
    }
}