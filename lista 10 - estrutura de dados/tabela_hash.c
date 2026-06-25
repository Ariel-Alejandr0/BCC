#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"

static int hsh_hash(int matricula)
{
    return matricula % TAM;
}

TabelaHash *hsh_cria(void)
{
    TabelaHash *tab = (TabelaHash *)malloc(sizeof(TabelaHash));
    if (tab == NULL)
        return NULL;

    int i;
    for (i = 0; i < TAM; i++)
        tab->vet[i] = NULL;

    return tab;
}

Aluno *hsh_get(TabelaHash *tab, int matricula)
{
    int indice = hsh_hash(matricula);
    Aluno *atual = tab->vet[indice];

    while (atual != NULL) {
        if (atual->matricula == matricula)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

Aluno *hsh_set(TabelaHash *tab, int matricula, char *nome,
               char *email, float mediaGeral)
{
    /* Se já existe, apenas atualiza os dados */
    Aluno *existente = hsh_get(tab, matricula);
    if (existente != NULL) {
        strcpy(existente->nome, nome);
        strcpy(existente->email, email);
        existente->mediaGeral = mediaGeral;
        return existente;
    }

    /* Cria novo nó */
    Aluno *novo = (Aluno *)malloc(sizeof(Aluno));
    if (novo == NULL)
        return NULL;

    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    novo->mediaGeral = mediaGeral;

    /* Insere no início da lista do bucket */
    int indice = hsh_hash(matricula);
    novo->prox = tab->vet[indice];
    tab->vet[indice] = novo;

    return novo;
}

void hsh_remove(TabelaHash *tab, int matricula)
{
    int indice = hsh_hash(matricula);
    Aluno *atual = tab->vet[indice];
    Aluno *anterior = NULL;

    while (atual != NULL) {
        if (atual->matricula == matricula) {
            if (anterior == NULL)           /* primeiro elemento */
                tab->vet[indice] = atual->prox;
            else                            /* meio ou fim da lista */
                anterior->prox = atual->prox;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    /* matrícula não encontrada: nenhuma ação */
}

int hsh_contem(TabelaHash *tab, int matricula)
{
    return hsh_get(tab, matricula) != NULL ? 1 : 0;
}

int hsh_quantidade(TabelaHash *tab)
{
    int total = 0;
    int i;
    for (i = 0; i < TAM; i++) {
        Aluno *atual = tab->vet[i];
        while (atual != NULL) {
            total++;
            atual = atual->prox;
        }
    }
    return total;
}

int hsh_colisoes(TabelaHash *tab)
{
    int colisoes = 0;
    int i;
    for (i = 0; i < TAM; i++) {
        if (tab->vet[i] != NULL && tab->vet[i]->prox != NULL) {
            Aluno *atual = tab->vet[i]->prox;
            while (atual != NULL) {
                colisoes++;
                atual = atual->prox;
            }
        }
    }
    return colisoes;
}

int hsh_maior_lista(TabelaHash *tab)
{
    int maior = 0;
    int i;
    for (i = 0; i < TAM; i++) {
        int tamanho = 0;
        Aluno *atual = tab->vet[i];
        while (atual != NULL) {
            tamanho++;
            atual = atual->prox;
        }
        if (tamanho > maior)
            maior = tamanho;
    }
    return maior;
}

void hsh_imprime(TabelaHash *tab)
{
    int i;
    for (i = 0; i < TAM; i++) {
        if (tab->vet[i] != NULL) {
            printf("[%d]", i);
            Aluno *atual = tab->vet[i];
            while (atual != NULL) {
                printf(" -> (Mat: %d | %s | %s | Media: %.2f)",
                       atual->matricula,
                       atual->nome,
                       atual->email,
                       atual->mediaGeral);
                atual = atual->prox;
            }
            printf("\n");
        }
    }
}

void hsh_libera(TabelaHash *tab)
{
    int i;
    for (i = 0; i < TAM; i++) {
        Aluno *atual = tab->vet[i];
        while (atual != NULL) {
            Aluno *prox = atual->prox;
            free(atual);
            atual = prox;
        }
        tab->vet[i] = NULL;
    }
    free(tab);
}