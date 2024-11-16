#include "lib.h"

#define max_contagem_carros 3 // qnt de carros para fechar o semaforo

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


void iniciar_semaforo(Semaforo *semaforo){
    semaforo->estado1 = 1; // inicializa como verde
    semaforo->estado2 = 1; // inicializa como verde
    semaforo->topo = -1;
    printf("\nSemaforo inicializado com sucesso!\n");
}


void empilhar_carro(Semaforo *semaforo){
    if(semaforo->topo < max_contagem_carros - 1){
        semaforo->topo++;
        semaforo->pilha[semaforo->topo] = 1;
        printf("Veiculo detectado no sensor no sentido duplo! Total de veiculos empilhados: %d\n", semaforo->topo + 1);
    }else{
        printf("Fila cheia! Maximo de veiculos permitidos: %d\n", max_contagem_carros);
    }
}

void desempilhar_carro(Semaforo *semaforo){
    if(semaforo->topo >= 0){ // verificacao para garantir que há algo na pilha antes de desempilhar
        semaforo->topo--;
        printf("Veiculo passou no sinal! Total de veiculos empilhados: %d\n", semaforo->topo + 1);
    }else{
        printf("Não há veiculos para desempilhar!\n");
    }

}

void mudarEstado(Semaforo *semaforo){
    // CONDICOES DE MUDANCA DE ESTADO:
    // 1: (sentido unico) semaforo esta verde e contou o maximo de veiculos permitidos na via
    if(semaforo->estado1 == 1 && semaforo->topo == max_contagem_carros - 1){
        semaforo->estado1 = 0; // trocou o estado da via de verde para vermelho
        semaforo->estado2 = 1; // abre o do sentido duplo
        printf("Semaforo no fluxo unico (estado1) mudou para VERMELHO!\n");
    
    }else if(semaforo->estado2 == 1 && semaforo->topo >= max_contagem_carros){
        semaforo->estado1 = 1;
        semaforo->estado2 = 0;
        printf("Semaforo no fluxo duplo (estado2) mudou para VERMELHO!\n");
    }else{
        printf("Semaforo segue inalterado\n");
    }
        
}

void criarFluxo(Automaton *afd_a, Automaton *afd_b, Automaton *afd_c, Automaton *afd_d, Semaforo *c2, char *palavra){
    printf("\n\n--- SIMULAÇÃO DO FLUXO ---\n\n");
    printf("Palavra usada para o fluxo: %s\n", palavra);

    int tam_string = strlen(palavra);
    for(int i = 0; i < tam_string; i++){
        char simbolo = palavra[i];
    

    // Empilha um carro ao detectar o símbolo de uma via específica
        switch (simbolo) {
            case 'c':
                printf("Carro inicia no fluxo único (C).\n");
                empilhar_carro(c2);
                break;

            case 'b':
                printf("Carro inicia no fluxo duplo (B).\n");
                empilhar_carro(c2);
                break;

            default:
                printf("Símbolo '%c' não afeta os semáforos diretamente.\n", simbolo);
                break;
        }

    // Muda o estado do semáforo com base na pilha
        mudarEstado(c2);
        
        // Simula a saída de carros no fluxo (desempilhando)
        desempilhar_carro(c2);
    }

    printf("Simulação concluída.\n");

}