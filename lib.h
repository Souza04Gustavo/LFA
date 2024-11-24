#include <string.h>
#include <stdio.h>

#define max_estados 10
#define max_transicoes 100
#define max_alfabeto 5
#define max_carros 10 // qnt de carros andando ao mesmo tempo

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

typedef struct{
    int estado1; // 0 == vermelho,  1 == verde (fluxo unico)
    int estado2; // 0 == vermelho,  1 == verde (fluxo duplo)
    int pilha[max_carros];
    int topo;
} Semaforo;

int eh_estado_aceito(Automaton *afd, int estado);
int pegar_prox_estado(Automaton *afd, int estado_atual, char simbolo);
int simulate_afd(Automaton *afd, char *palavra);
int gerar_caminho(int max, int min);
void iniciar_semaforo(Semaforo *semaforo);
void adicionar_veiculo(Semaforo *semaforo, int fluxo);
void desempilhar_carro(Semaforo * semaforo);
void alterar_estado(Semaforo * semaforo);
void definir_caminhos_eficientes(char *palavra_a, char *palavra_b, char *palavra_c, char *palavra_d);
void criarFluxoComSemaforo_BC(Automaton *afd_b, Automaton *afd_c, char *palavra_b, char *palavra_c, char *carros, Semaforo *semaforo);
void criarFluxoComSemaforo_AD(Automaton *afd_a, Automaton *afd_d, char *palavra_a, char *palavra_d, char *carros, Semaforo *semaforo);