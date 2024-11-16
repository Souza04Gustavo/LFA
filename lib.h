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

int eh_estado_aceito(Automaton *afd, int estado);
int pegar_prox_estado(Automaton *afd, int estado_atual, char simbolo);
int simulate_afd(Automaton *afd, char *palavra);
int gera_caminho(int max, int min);