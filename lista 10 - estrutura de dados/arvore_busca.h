#ifndef ARVORE_BUSCA_H
#define ARVORE_BUSCA_H

struct noArvoreBusca
{
    int info;
    struct noArvoreBusca *esq;
    struct noArvoreBusca *dir;
};
typedef struct noArvoreBusca NoArvoreBusca;

struct arvoreBusca
{
    NoArvoreBusca *raiz;
};
typedef struct arvoreBusca ArvoreBusca;

ArvoreBusca *abb_cria(void);
int abb_vazia(ArvoreBusca *a);
NoArvoreBusca *abb_busca(ArvoreBusca *a, int v);
void abb_insere(ArvoreBusca *a, int v);
void abb_retira(ArvoreBusca *a, int v);
int abb_pertence(ArvoreBusca *a, int v);
int abb_num_nos(ArvoreBusca *a);
int abb_folhas(ArvoreBusca *a);
int abb_altura(ArvoreBusca *a);
void abb_imprime_crescente(ArvoreBusca *a);
void abb_imprime_decrescente(ArvoreBusca *a);
void abb_libera(ArvoreBusca *a);

#endif