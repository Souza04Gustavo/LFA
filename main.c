#include <time.h>
#include "lib.h"

#define carros 100

int main() {
    
    printf("\n--- Trabalho Final da Matéria Linguagens Formais e Autômatos ---\n");
    printf("Professor: Ricardo Ferreira Martins.\n");
    printf("Alunos: Gustavo de Souza; José Augusto Laube.\n");
    srand(time(NULL));
    
    Automaton afd_a;

    // definindo os estados (usuario pode definir como desejar)
    afd_a.num_estados = 8;
    afd_a.estado_inicial = 0;
    afd_a.estados_aceitos[0] = 7; // estado final
    afd_a.estados_de_aceitacao = 1; // quantidade de transacoes por vez

    // deefinindo o alfabeto (usuario pode definir como desejar)
    afd_a.alfabeto[0] = 'a';
    afd_a.alfabeto[1] = 'r';
    afd_a.alfabeto[2] = 'p';

    // definindo as transições (usuario pode definir como desejar)
    afd_a.num_transicoes = 9;
    afd_a.transitions[0] = (Transicao){0, 'a', 1};
    afd_a.transitions[1] = (Transicao){0, 'p', 7};
    afd_a.transitions[2] = (Transicao){1, 'a', 2};  
    afd_a.transitions[3] = (Transicao){2, 'a', 3};  
    afd_a.transitions[4] = (Transicao){3, 'r', 3};  
    afd_a.transitions[5] = (Transicao){3, 'a', 4};
    afd_a.transitions[6] = (Transicao){4, 'a', 5};
    afd_a.transitions[7] = (Transicao){5, 'a', 6};
    afd_a.transitions[8] = (Transicao){6, 'p', 7};
    

    Automaton afd_b;

    // definindo os estados (usuario pode definir como desejar)
    afd_b.num_estados = 8;
    afd_b.estado_inicial = 0;
    afd_b.estados_aceitos[0] = 7; // estado final
    afd_b.estados_de_aceitacao = 1; // quantidade de transacoes por vez

    // deefinindo o alfabeto (usuario pode definir como desejar)
    afd_b.alfabeto[0] = 'b';
    afd_b.alfabeto[1] = 'r';
    afd_b.alfabeto[2] = 'p';

    // definindo as transições (usuario pode definir como desejar)
    afd_b.num_transicoes = 9;
    afd_b.transitions[0] = (Transicao){0, 'b', 1};
    afd_b.transitions[1] = (Transicao){0, 'p', 7};
    afd_b.transitions[2] = (Transicao){1, 'b', 2};  
    afd_b.transitions[3] = (Transicao){2, 'b', 3};  
    afd_b.transitions[4] = (Transicao){3, 'r', 3};  
    afd_b.transitions[5] = (Transicao){3, 'b', 4};
    afd_b.transitions[6] = (Transicao){4, 'b', 5};
    afd_b.transitions[7] = (Transicao){5, 'b', 6};
    afd_b.transitions[8] = (Transicao){6, 'p', 7};

    Automaton afd_c;

    // definindo os estados (usuario pode definir como desejar)
    afd_c.num_estados = 5;
    afd_c.estado_inicial = 0;
    afd_c.estados_aceitos[0] = 4; // estado final
    afd_c.estados_de_aceitacao = 1; // quantidade de transacoes por vez

    // deefinindo o alfabeto (usuario pode definir como desejar)
    afd_c.alfabeto[0] = 'c';
    afd_c.alfabeto[1] = 'r';
    afd_c.alfabeto[2] = 'p';

    // definindo as transições (usuario pode definir como desejar)
    afd_c.num_transicoes = 5;
    afd_c.transitions[0] = (Transicao){0, 'c', 1};
    afd_c.transitions[1] = (Transicao){1, 'c', 2};
    afd_c.transitions[2] = (Transicao){2, 'p', 4};  
    afd_c.transitions[3] = (Transicao){2, 'c', 3};  
    afd_c.transitions[4] = (Transicao){3, 'r', 3};  

    Automaton afd_d;

    // definindo os estados (usuario pode definir como desejar)
    afd_d.num_estados = 6;
    afd_d.estado_inicial = 0;
    afd_d.estados_aceitos[0] = 4; // estado final
    afd_d.estados_aceitos[1] = 5; // estado final 2
    afd_d.estados_de_aceitacao = 2; // quantidade de transacoes por vez

    // deefinindo o alfabeto (usuario pode definir como desejar)
    afd_d.alfabeto[0] = 'd';
    afd_d.alfabeto[1] = 'r';
    afd_d.alfabeto[2] = 'p';

    // definindo as transições (usuario pode definir como desejar)
    afd_d.num_transicoes = 6;
    afd_d.transitions[0] = (Transicao){0, 'd', 1};
    afd_d.transitions[1] = (Transicao){1, 'd', 2};
    afd_d.transitions[2] = (Transicao){1, 'p', 4};
    afd_d.transitions[3] = (Transicao){2, 'd', 3};  
    afd_d.transitions[4] = (Transicao){2, 'p', 5};  
    afd_d.transitions[5] = (Transicao){3, 'r', 3};  

    char palavra_a[100];  // palavra a ser processada com inicio em A
    char palavra_b[100];  // palavra a ser processada com inicio em B
    char palavra_c[100];  // palavra a ser processada com inicio em C
    char palavra_d[100];  // palavra a ser processada com inicio em D

    /*
    // GERANDO CAMINHOS DE A
    // para o caminho A há duas possibilidades:
    // 1: iniciar e ja estacionar
    // 2: ir reto, fazer a rotatoria, e seguir ate o estacionamento

    //fazendo um rand para qual caminho sera escolhido visto que o carro DEVE chegar a um estacionamento
    int min_a = 1;
    int max_a = 2;
    int caminho_a = gera_caminho(max_a, min_a);
    printf("Caminho escolhido para A: %d\n", caminho_a); 

    //criando os caminhos possiveis para A
    if(caminho_a == 1){
        strcpy(palavra_a, "p");
    }else{
        strcpy(palavra_a, "aaaraaap");
    }
    
    printf("Palavra de A (+eficiente): %s \n", palavra_a); 
    printf("\n");


    // GERANDO CAMINHOS DE B
    // para o caminho de B há duas possibilidades (igual A):
    // 1: iniciar e ja estacionar
    // 2: ir reto, fazer a rotatoria, e seguir ate o estacionamento
    int min_b = 1;
    int max_b = 2;
    int caminho_b = gera_caminho(max_b, min_b);
    printf("Caminho escolhido para B: %d\n", caminho_b); 

    //criando os caminhos possiveis para B
    if(caminho_b == 1){
        strcpy(palavra_b, "p");
    }else{
        strcpy(palavra_b, "bbbrbbbp");
    }
    
    printf("Palavra de B (+eficiente): %s \n", palavra_b); 
    printf("\n");


    // GERANDO CAMINHOS DE C
    // para o caminho C há somente uma possibilidade:
    // 1: inicia e segue até estacionar apos C2 (primeiro semaforo)
    strcpy(palavra_c, "ccp");
    printf("Palavra de C (+eficiente): %s \n", palavra_c); 
    printf("\n");


    // GERANDO CAMINHOS DE D
    // para o caminho D há duas possibilidades:
    // 1: inicia e segue até estacionar (antes do semaforo)
    // 2: inicia e segue até passar o semaforo, ai estaciona
    int min_d = 1;
    int max_d = 2;
    int caminho_d = gera_caminho(max_d, min_d);
    printf("Caminho escolhido para D: %d\n", caminho_d); 

    //criando os caminhos possiveis para D
    if(caminho_d == 1){
        strcpy(palavra_d, "dp");
    }else{
        strcpy(palavra_d, "ddp");
    }
    
    printf("Palavra de D (+eficiente): %s \n", palavra_d); 
    printf("\n");
    */

    int menu = 1;
    int cont= 0;
    int opcao;
    char selecao;
    char palavra_teste[100];

    while(menu){
            printf("\n\n\n--- MENU DE SELEÇÃO ---\n");
            printf("(1) Simular AFDs de fluxos separadamente;\n");
            printf("(2) Simular fluxo com semaforos (SEM TROCA DE DIREÇÃO);\n");
            printf("(3) Simular fluxo com semaforos (COM TROCA DE DIREÇÃO)(NAO FUNCIONA);\n");
            printf("(0) Para finalizar o programa;\n");

            scanf("%d", &opcao);
            getchar();

            switch(opcao){

                case 0:
                menu--; // finaliza o menu
                break;    

                case 1:
                printf("\nSelecione qual AFD deseja simular (A, B, C ou D):\n");
                scanf(" %c", &selecao);
                switch(selecao){    

                    case 'A':
                    printf("Insira uma palavra para testar o AFD A:\n");
                    getchar();
                    fgets(palavra_teste, sizeof(palavra_teste), stdin);
                    palavra_teste[strcspn(palavra_teste, "\n")] = '\0'; // remover o \n do final caso tenha
    
                    simulate_afd(&afd_a, palavra_teste);
                    break;

                    case 'B':
                    printf("Insira uma palavra para testar o AFD B:\n");
                    getchar();
                    fgets(palavra_teste, sizeof(palavra_teste), stdin);
                    palavra_teste[strcspn(palavra_teste, "\n")] = '\0'; // remover o \n do final caso tenha
                    
                    simulate_afd(&afd_b, palavra_teste);
                    break;

                    case 'C':
                    printf("Insira uma palavra para testar o AFD C:\n");
                    getchar();
                    fgets(palavra_teste, sizeof(palavra_teste), stdin);
                    palavra_teste[strcspn(palavra_teste, "\n")] = '\0'; // remover o \n do final caso tenha
                    
                    simulate_afd(&afd_c, palavra_teste);
                    break;

                    case 'D':
                    printf("Insira uma palavra para testar o AFD D:\n");
                    getchar();
                    fgets(palavra_teste, sizeof(palavra_teste), stdin);
                    palavra_teste[strcspn(palavra_teste, "\n")] = '\0'; // remover o \n do final caso tenha
                    
                    simulate_afd(&afd_d, palavra_teste);
                    break;

                    default:
                    printf("AFD invalido selecionado!\n");
                    break;
                }

                break; // break do case 1 do switch opcao

                case 2: // simulação do fluxo (SEM CURVA)
                char palavra[carros];
                printf("\nInsira a palavra que deseja testar:\n");
                scanf("%s", palavra);

                Semaforo c2;
                iniciar_semaforo(&c2);
    
                // Simulação do fluxo
                printf("Iniciando simulação para os carros: %s\n", palavra);
                criarFluxoComSemaforo_BC(&afd_b, &afd_c, palavra_b, palavra_c, palavra, &c2);

                break;

                case 3: // simulação do fluxo (COM CURVA)
                definir_caminhos_eficientes(palavra_a, palavra_b, palavra_c, palavra_d);
                break;  

                default:
                printf("Digito invalido!\n");
                break;

            }
    }

    printf("\nPrograma finalizado!\n");

    return 0;
}