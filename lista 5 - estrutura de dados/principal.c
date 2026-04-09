#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main() {
    char entrada[50];
    Calc *c = calc_cria("%.2f\n");

    if (c == NULL) {
        printf("Erro ao criar calculadora.\n");
        return 1;
    }

    printf("Digite operandos e operadores (+ - * /). Digite 'q' para sair.\n");

    while (1) {
        scanf("%s", entrada);

        if (entrada[0] == 'q') {
            break;
        }

        char *end;
        double valor = strtod(entrada, &end);

        // Se converteu número corretamente
        if (*end == '\0') {
            calc_operando(c, valor);
            printf("%.2f\n", pilha_top(c->p));
        }
        else if (entrada[0] == '+' || entrada[0] == '-' ||
                 entrada[0] == '*' || entrada[0] == '/') {

            calc_operador(c, entrada[0]);
            printf("%.2f\n", pilha_top(c->p));
        }
        else {
            printf("Entrada inválida: %s\n", entrada);
        }
    }

    calc_libera(c);
    return 0;
}