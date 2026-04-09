#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

Pilha* pilha_cria(void){
    Pilha* p = malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
};

void pilha_push(Pilha *p, float v){
    NoLista* novoElemento = malloc(sizeof(NoLista));
    novoElemento->info = v;
    novoElemento->prox = p->topo;
    p->topo = novoElemento;
}

int pilha_vazia(Pilha* p){
    return p->topo == NULL;
}

float pilha_pop(Pilha* p){
    if(pilha_vazia(p)){
        printf("Pilha vazia! Não é possível realizar pop.\n");
        return -1; // Retorna um valor indicativo de erro
    }
    NoLista* temp = p->topo;
    float valor = temp->info;
    p->topo = temp->prox;
    free(temp);
    return valor;
}

float pilha_top(Pilha* p){
    if(pilha_vazia(p)){
        printf("Pilha vazia! Não é possível acessar o topo.\n");
        return -1; // Retorna um valor indicativo de erro
    }
    return p->topo->info;
}

void pilha_libera(Pilha* p){
    while(!pilha_vazia(p)){
        pilha_pop(p);
    }
    free(p);
}