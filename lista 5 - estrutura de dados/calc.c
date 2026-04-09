#include "calc.h"
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

Calc* calc_cria(char *f){
    if (f == NULL) return NULL;

    Calc* c = malloc(sizeof(Calc));
    if(c != NULL){
        strncpy(c->f, f, sizeof(c->f) - 1);
        c->f[sizeof(c->f) - 1] = '\0';
        c->p = pilha_cria();

        if(c->p == NULL){
            free(c);
            return NULL;
        }
    }
    return c;
};
void calc_operando(Calc* c, float v){
    if (c == NULL) return;

    pilha_push(c->p, v);
}

void calc_operador(Calc* c, char op){
    float b = pilha_pop(c->p);
    float a = pilha_pop(c->p);
    float resultado;

    switch(op){
        case '+': resultado = a + b; break;
        case '-': resultado = a - b; break;
        case '*': resultado = a * b; break;
        case '/': resultado = a / b; break;
    }

    pilha_push(c->p, resultado);
}

void calc_libera(Calc* c){
    if (c == NULL) return;

    pilha_libera(c->p);
    free(c);
}