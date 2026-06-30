#include "arvore_busca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArvoreBusca *abb_cria(void)
{
    ArvoreBusca *a = (ArvoreBusca *)malloc(sizeof(ArvoreBusca));
    a->raiz = NULL;
    return a;
}

int abb_vazia(ArvoreBusca *a)
{
    return a->raiz == NULL;
}

NoArvoreBusca *abb_busca(ArvoreBusca *a, int v)
{
    NoArvoreBusca *no = a->raiz;
    while (no != NULL)
    {
        if (v < no->info)
            no = no->esq;
        else if (v > no->info)
            no = no->dir;
        else
            return no;
    }
    return NULL;
}

void abb_insere(ArvoreBusca *a, int v)
{
    NoArvoreBusca *novo = (NoArvoreBusca *)malloc(sizeof(NoArvoreBusca));
    novo->info = v;
    novo->esq = NULL;
    novo->dir = NULL;

    if (a->raiz == NULL)
    {
        a->raiz = novo;
        return;
    }

    NoArvoreBusca *atual = a->raiz;
    while (1)
    {
        if (v < atual->info)
        {
            if (atual->esq == NULL)
            {
                atual->esq = novo;
                return;
            }
            atual = atual->esq;
        }
        else
        {
            if (atual->dir == NULL)
            {
                atual->dir = novo;
                return;
            }
            atual = atual->dir;
        }
    }
}

void abb_retira(ArvoreBusca *a, int v)
{
    NoArvoreBusca *pai = NULL;
    NoArvoreBusca *atual = a->raiz;

    while (atual != NULL && atual->info != v)
    {
        pai = atual;
        if (v < atual->info)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    if (atual == NULL)
        return;

    /* caso 1: dois filhos */
    if (atual->esq != NULL && atual->dir != NULL)
    {
        NoArvoreBusca *pai_suc = atual;
        NoArvoreBusca *suc = atual->dir;
        while (suc->esq != NULL)
        {
            pai_suc = suc;
            suc = suc->esq;
        }
        atual->info = suc->info;
        pai = pai_suc;
        atual = suc;
    }

    /* caso 2: zero ou um filho */
    NoArvoreBusca *filho = (atual->esq != NULL) ? atual->esq : atual->dir;

    if (pai == NULL)
        a->raiz = filho;
    else if (pai->esq == atual)
        pai->esq = filho;
    else
        pai->dir = filho;

    free(atual);
}

int abb_pertence(ArvoreBusca *a, int v)
{
    return abb_busca(a, v) != NULL;
}

int abb_num_nos(ArvoreBusca *a)
{
    if (abb_vazia(a))
        return 0;

    int count = 0;
    NoArvoreBusca *fila[1000];
    int inicio = 0, fim = 0;

    fila[fim++] = a->raiz;
    while (inicio < fim)
    {
        NoArvoreBusca *no = fila[inicio++];
        count++;
        if (no->esq != NULL) fila[fim++] = no->esq;
        if (no->dir != NULL) fila[fim++] = no->dir;
    }
    return count;
}

int abb_folhas(ArvoreBusca *a)
{
    if (abb_vazia(a))
        return 0;

    int count = 0;
    NoArvoreBusca *fila[1000];
    int inicio = 0, fim = 0;

    fila[fim++] = a->raiz;
    while (inicio < fim)
    {
        NoArvoreBusca *no = fila[inicio++];
        if (no->esq == NULL && no->dir == NULL)
            count++;
        if (no->esq != NULL) fila[fim++] = no->esq;
        if (no->dir != NULL) fila[fim++] = no->dir;
    }
    return count;
}

int abb_altura(ArvoreBusca *a)
{
    if (abb_vazia(a))
        return 0;

    int altura = 0;
    NoArvoreBusca *fila[1000];
    int inicio = 0, fim = 0;

    fila[fim++] = a->raiz;
    while (inicio < fim)
    {
        int nivel = fim - inicio;
        altura++;
        while (nivel > 0)
        {
            NoArvoreBusca *no = fila[inicio++];
            if (no->esq != NULL) fila[fim++] = no->esq;
            if (no->dir != NULL) fila[fim++] = no->dir;
            nivel--;
        }
    }
    return altura;
}

void abb_imprime_crescente(ArvoreBusca *a)
{
    if (abb_vazia(a))
        return;

    NoArvoreBusca *pilha[1000];
    int topo = 0;
    NoArvoreBusca *atual = a->raiz;

    while (atual != NULL || topo > 0)
    {
        while (atual != NULL)
        {
            pilha[topo++] = atual;
            atual = atual->esq;
        }
        atual = pilha[--topo];
        printf("%d ", atual->info);
        atual = atual->dir;
    }
    printf("\n");
}

void abb_imprime_decrescente(ArvoreBusca *a)
{
    if (abb_vazia(a))
        return;

    NoArvoreBusca *pilha[1000];
    int topo = 0;
    NoArvoreBusca *atual = a->raiz;

    while (atual != NULL || topo > 0)
    {
        while (atual != NULL)
        {
            pilha[topo++] = atual;
            atual = atual->dir;
        }
        atual = pilha[--topo];
        printf("%d ", atual->info);
        atual = atual->esq;
    }
    printf("\n");
}

void abb_libera(ArvoreBusca *a)
{
    if (abb_vazia(a))
        return;

    NoArvoreBusca *pilha[1000];
    int topo = 0;
    NoArvoreBusca *atual = a->raiz;

    while (atual != NULL || topo > 0)
    {
        while (atual != NULL)
        {
            pilha[topo++] = atual;
            atual = atual->esq;
        }
        atual = pilha[--topo];
        NoArvoreBusca *dir = atual->dir;
        free(atual);
        atual = dir;
    }

    a->raiz = NULL;
    free(a);
}