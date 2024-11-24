#include "lib.h"

#define max_contagem_carros 6 // quantidade de carros maxima no fluxo

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
    printf("\n - Simulação - \n");
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
    semaforo->estado1 = 0; // inicializa como vermelho
    semaforo->estado2 = 1; // inicializa como verde
    semaforo->topo = -1;
    //printf("\nSemaforo inicializado com sucesso!\n");
}

void adicionar_veiculo(Semaforo *semaforo, int fluxo) {
    if (fluxo == 1 && semaforo->topo < max_contagem_carros - 1) {
        semaforo->topo++;
        semaforo->pilha[semaforo->topo] = 1; // representa veiculo no fluxo B
        printf("Veículo adicionado ao fluxo B. Total: %d\n", semaforo->topo + 1);
    } else if (fluxo == 2 && semaforo->topo < max_contagem_carros - 1) {
        semaforo->topo++;
        semaforo->pilha[semaforo->topo] = 2; // representa veiculo no fluxo C
        printf("Veículo adicionado ao fluxo C. Total: %d\n", semaforo->topo + 1);
    } else {
        printf("Fila cheia! Fluxo %d atingiu o limite de veículos.\n", fluxo);
    }
}

void desempilhar_carro(Semaforo *semaforo){
    if(semaforo->topo >= 0){ // verificacao para garantir que ha algo na pilha antes de desempilhar
        semaforo->topo--; // desempilha 
        printf("Veiculo passou no sinal! Total de veiculos empilhados: %d\n", semaforo->topo + 1);
    }else{
        printf("Não há veiculos para desempilhar!\n");
    }

}

void alternar_estado(Semaforo *semaforo) {
    // Alterna os estados do semaforo entre os dois fluxos
    semaforo->estado1 = !semaforo->estado1; // inverte o fluxo com uma logica simples
    semaforo->estado2 = !semaforo->estado2;

    // print pra teste de fluxo
    printf("Semaforo alterado: Fluxo B agora esta %s e Fluxo C está %s.\n", 
            semaforo->estado1 ? "verde" : "vermelho", 
            semaforo->estado2 ? "verde" : "vermelho");
}

int gera_caminho(int max, int min){
    int caminho = rand() % (max - min + 1) + min;
    return caminho;
}

void definir_caminhos_eficientes(char *palavra_a, char *palavra_b, char *palavra_c, char *palavra_d) {
    // Gerar caminho para A
    if (gera_caminho(2, 1) == 1) {
        strcpy(palavra_a, "p");
    } else {
        strcpy(palavra_a, "aaaraaap");
    }

    // Gerar caminho para B
    if (gera_caminho(2, 1) == 1) {
        strcpy(palavra_b, "p");
    } else {
        strcpy(palavra_b, "bbbrbbbp");
    }

    // Gerar caminho para C (fixo)
    strcpy(palavra_c, "ccp");

    // Gerar caminho para D
    if (gera_caminho(2, 1) == 1) {
        strcpy(palavra_d, "dp");
    } else {
        strcpy(palavra_d, "ddp");
    }

    // Exibir os resultados
    printf("Caminhos definidos:\n");
    printf("Palavra A: %s\n", palavra_a);
    printf("Palavra B: %s\n", palavra_b);
    printf("Palavra C: %s\n", palavra_c);
    printf("Palavra D: %s\n", palavra_d);
    printf("\n");
}

void criarFluxoComSemaforo_BC(Automaton *afd_b, Automaton *afd_c, char *palavra_b, char *palavra_c, char *carros, Semaforo *semaforo) {
    int estados[max_contagem_carros] = {0}; // vetor para armazenar o estado atual do carro
    int indices[max_contagem_carros] = {0}; // indices para acompanhar a posicao atual na palavra de cada carro
    Automaton *automatos[max_contagem_carros] = {NULL}; // vetor de ponteiros para os automatos que representam cada carro
    char *palavras[max_contagem_carros] = {NULL}; // caminhos de cada carro
    int num_carros = strlen(carros);  // qnt de carros da simulação

    // verificação do numero de carros para nao exceder o limite
    if (num_carros > max_contagem_carros) {
        printf("Erro: Número de carros excede o máximo permitido (%d).\n", max_contagem_carros);
        return;
    }

    // configuração inicial dos carros
    for (int i = 0; i < num_carros; i++) {
        indices[i] = 0; // cada carro inicia na posição inicial do seu caminho
        if (carros[i] == 'b') {
            automatos[i] = afd_b;
            palavras[i] = palavra_b; // associa a palabra do fluxo B
            estados[i] = afd_b->estado_inicial;
        } else if (carros[i] == 'c') {
            automatos[i] = afd_c;
            palavras[i] = palavra_c;  // associa a palavra do fluxo C
            estados[i] = afd_c->estado_inicial;
        } else {
            // usuario inseriu letra invalida
            printf("Erro: Letra '%c' inválida na palavra de carros.\n", carros[i]);
            return;
        }
    }

    printf("\n\n\n ---> INICIO DA SIMULAÇÃO SEM TROCA DE SENTIDO <----\n");

    int concluidos = 0;  // Qnt de carros que concluiram o percurso
    int ciclo = 0; // contador para os ciclos "passos" da simulação

    // inicializa contadores de carros para os fluxos B e C
    int carros_b = 0;
    int carros_c = 0;

    //loop principal: so finaliza a execucao quando todos os carros finalizaram o percurso
    while (concluidos < num_carros) {
        printf("\n--- Ciclo %d ---\n", ++ciclo);
        printf("Semáforo: Fluxo B está %s, Fluxo C está %s\n",
               semaforo->estado1 ? "verde" : "vermelho",
               semaforo->estado2 ? "verde" : "vermelho");

        // reseta os contadores a cada ciclo de carros aguardando
        carros_b = 0;
        carros_c = 0;

        // contagem da quantidade de carros aguardando em cada fluxo
        for (int i = 0; i < num_carros; i++) {
            if (indices[i] < strlen(palavras[i])) {
                if (carros[i] == 'b'){
                    carros_b++;
                }
                if (carros[i] == 'c'){
                    carros_c++;
                } 
            }
        }

        printf("Carros aguardando - Fluxo B: %d, Fluxo C: %d\n", carros_b, carros_c);

        // alterna o semaforo para o fluxo com mais carros
        if (carros_b > carros_c && semaforo->estado1 == 0) {
            semaforo->estado1 = 1;  // abre o fluxo b
            semaforo->estado2 = 0;  // fecha o fluxo c
            printf("Semáforo alternado para Fluxo B (prioridade).\n");
        } else if (carros_c > carros_b && semaforo->estado2 == 0) {
            semaforo->estado1 = 0;  // fecha o fluxo b
            semaforo->estado2 = 1;  // abre o fluxo C
            printf("Semáforo alternado para Fluxo C (prioridade).\n");
        }

        // processa cada carro
        for (int i = 0; i < num_carros; i++) {
            if (indices[i] < strlen(palavras[i])) {  // se o carro ainda nao estacionou
                char simbolo = palavras[i][indices[i]];  // simbolo atual analisado é o caminho do carro

                // faz verificacao do semaforo antes de avançar
                if ((carros[i] == 'b' && semaforo->estado1 == 0) ||
                    (carros[i] == 'c' && semaforo->estado2 == 0)) {
                    printf("Carro %d está aguardando no semáforo. Fluxo bloqueado.\n", i + 1);
                    continue; // esperar ata o semaforo abrir
                }

                printf("Carro %d: estado atual = %d, simbolo = '%c'\n", i + 1, estados[i], simbolo);

                // pegar o proximo estado com base no simbolo atual
                int prox_estado = pegar_prox_estado(automatos[i], estados[i], simbolo);
                if (prox_estado == -1) {
                    printf("Erro: Transição inválida para o carro %d\n", i + 1);
                    return; // finaliza com erro
                }


                estados[i] = prox_estado;  // atualiza o estado para o proximo ja
                printf("Carro %d: novo estado = %d\n", i + 1, estados[i]);

                // avanca para o prox simbolo
                indices[i]++;
                // verifica se o carro estacionou em algum momento e se estado é de fato um estado final
                if (indices[i] == strlen(palavras[i]) && eh_estado_aceito(automatos[i], estados[i])) {
                    printf("Carro %d concluiu o percurso.\n", i + 1);
                    concluidos++;
                }
            }
        }

        printf("--- Fim do Ciclo %d ---\n", ciclo);
    }

    printf("\n ----> SIMULAÇÃO CONCLUIDA <----\n");
}