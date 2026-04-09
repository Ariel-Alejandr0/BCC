#include "pilha.h"

#ifndef CALC_H
#define CALC_H

struct calc {
    char f[21]; /* formato para impress~ao, por exemplo "%.2f\n" */
    Pilha *p; /* pilha de operandos */
};
typedef struct calc Calc;

Calc *calc_cria(char *f);
void calc_operando(Calc *c, float v);
void calc_operador(Calc *c, char op);
void calc_libera(Calc *c);

#endif