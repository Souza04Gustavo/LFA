#include "lib.h"

#define max_contagem_carros 6 // qnt de carros para fechar o semaforo

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
    semaforo->estado1 = 0; // inicializa como verde
    semaforo->estado2 = 1; // inicializa como verde
    semaforo->topo = -1;
    printf("\nSemaforo inicializado com sucesso!\n");
}


void adicionar_veiculo(Semaforo *semaforo, int fluxo) {
    if (fluxo == 1 && semaforo->topo < max_contagem_carros - 1) {
        semaforo->topo++;
        semaforo->pilha[semaforo->topo] = 1; // Representa veículo no fluxo B
        printf("Veículo adicionado ao fluxo B. Total: %d\n", semaforo->topo + 1);
    } else if (fluxo == 2 && semaforo->topo < max_contagem_carros - 1) {
        semaforo->topo++;
        semaforo->pilha[semaforo->topo] = 2; // Representa veículo no fluxo C
        printf("Veículo adicionado ao fluxo C. Total: %d\n", semaforo->topo + 1);
    } else {
        printf("Fila cheia! Fluxo %d atingiu o limite de veículos.\n", fluxo);
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

void alternar_estado(Semaforo *semaforo) {
    // Alterna os estados do semáforo entre os dois fluxos
    semaforo->estado1 = !semaforo->estado1;
    semaforo->estado2 = !semaforo->estado2;

    printf("Semáforo alterado: Fluxo B agora está %s e Fluxo C está %s.\n",
           semaforo->estado1 ? "verde" : "vermelho",
           semaforo->estado2 ? "verde" : "vermelho");
}

void criarFluxoComSemaforo(Automaton *afd_b, Automaton *afd_c, char *palavra_b, char *palavra_c, char *carros, Semaforo *semaforo) {
    int estados[max_contagem_carros] = {0};
    int indices[max_contagem_carros] = {0};
    Automaton *automatos[max_contagem_carros] = {NULL};
    char *palavras[max_contagem_carros] = {NULL};
    int num_carros = strlen(carros);

    if (num_carros > max_contagem_carros) {
        printf("Erro: Número de carros excede o máximo permitido (%d).\n", max_contagem_carros);
        return;
    }

    // Configuração inicial dos carros
    for (int i = 0; i < num_carros; i++) {
        indices[i] = 0; // Cada carro começa na posição inicial do seu caminho
        if (carros[i] == 'b') {
            automatos[i] = afd_b;
            palavras[i] = palavra_b;
            estados[i] = afd_b->estado_inicial;
        } else if (carros[i] == 'c') {
            automatos[i] = afd_c;
            palavras[i] = palavra_c;
            estados[i] = afd_c->estado_inicial;
        } else {
            printf("Erro: Letra '%c' inválida na palavra de carros.\n", carros[i]);
            return;
        }
    }

    printf("\n--- Iniciando Simulação com Semáforo ---\n");

    int concluidos = 0;
    int ciclo = 0;

    // Inicializa contadores de carros para os fluxos B e C
    int carros_b = 0;
    int carros_c = 0;

    while (concluidos < num_carros) {
        printf("\n--- Ciclo %d ---\n", ++ciclo);
        printf("Semáforo: Fluxo B está %s, Fluxo C está %s\n",
               semaforo->estado1 ? "verde" : "vermelho",
               semaforo->estado2 ? "verde" : "vermelho");

        // Atualiza contadores para cada ciclo
        carros_b = 0;
        carros_c = 0;

        for (int i = 0; i < num_carros; i++) {
            if (indices[i] < strlen(palavras[i])) {
                if (carros[i] == 'b') carros_b++;
                if (carros[i] == 'c') carros_c++;
            }
        }

        printf("Carros aguardando - Fluxo B: %d, Fluxo C: %d\n", carros_b, carros_c);

        // Alterna o semáforo para o fluxo com mais carros
        if (carros_b > carros_c && semaforo->estado1 == 0) {
            semaforo->estado1 = 1;
            semaforo->estado2 = 0;
            printf("Semáforo alternado para Fluxo B (prioridade).\n");
        } else if (carros_c > carros_b && semaforo->estado2 == 0) {
            semaforo->estado1 = 0;
            semaforo->estado2 = 1;
            printf("Semáforo alternado para Fluxo C (prioridade).\n");
        }

        // Processa os carros
        for (int i = 0; i < num_carros; i++) {
            if (indices[i] < strlen(palavras[i])) {
                char simbolo = palavras[i][indices[i]];

                // Verifica o semáforo antes de avançar
                if ((carros[i] == 'b' && semaforo->estado1 == 0) ||
                    (carros[i] == 'c' && semaforo->estado2 == 0)) {
                    printf("Carro %d está aguardando no semáforo. Fluxo bloqueado.\n", i + 1);
                    continue; // Espera até o semáforo abrir
                }

                printf("Carro %d: estado atual = %d, simbolo = '%c'\n", i + 1, estados[i], simbolo);

                int prox_estado = pegar_prox_estado(automatos[i], estados[i], simbolo);
                if (prox_estado == -1) {
                    printf("Erro: Transição inválida para o carro %d\n", i + 1);
                    return;
                }

                estados[i] = prox_estado;
                printf("Carro %d: novo estado = %d\n", i + 1, estados[i]);

                indices[i]++;
                if (indices[i] == strlen(palavras[i]) && eh_estado_aceito(automatos[i], estados[i])) {
                    printf("Carro %d concluiu o percurso.\n", i + 1);
                    concluidos++;
                }
            }
        }

        // Adiciona uma pausa visual na simulação para entender o ciclo
        printf("--- Fim do Ciclo %d ---\n", ciclo);
    }

    printf("\n--- Simulação Concluída ---\n");
}

