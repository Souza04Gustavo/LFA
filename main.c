#include "lib.h"

int main() {
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

    printf("Digite a palavra iniciando em A: ");
    scanf("%s", palavra_a);
    simulate_afd(&afd_a, palavra_a);
    
    printf("Digite a palavra iniciando em B: ");
    scanf("%s", palavra_b);
    simulate_afd(&afd_b, palavra_b);

    printf("Digite a palavra iniciando em C: ");
    scanf("%s", palavra_c);
    simulate_afd(&afd_c, palavra_c);

    printf("Digite a palavra iniciando em D: ");
    scanf("%s", palavra_d);
    simulate_afd(&afd_d, palavra_d);


    return 0;
}