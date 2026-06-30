#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"
int *cria_vetor_ordenado(int n){
    int *vet;
    int i;
    vet = (int*) malloc(n * sizeof(int));
    if(vet != NULL){
        for(i = 0; i < n; i++){
            vet[i] = i * 2;
        }
    }
    return vet;
}
void imprime_vetor(int vet[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}
ResultadoBusca busca_linear(int vet[], int n, int elem){
    ResultadoBusca r;
    int i;
    r.indice = -1;
    r.comparacoes = 0;
    for(i = 0; i < n; i++){
        r.comparacoes++;
        if(vet[i] == elem){
            r.indice = i;
            return r;
        }
    }
    return r;
}
ResultadoBusca busca_linear_ordenada(int vet[], int n, int elem){
    ResultadoBusca r;
    int i;
    r.indice = -1;
    r.comparacoes = 0;
    for(i = 0; i < n; i++){
        r.comparacoes++;
        if(vet[i] == elem){
            r.indice = i;
            return r;
        }
        if(vet[i] > elem){
            return r;
        }
    }
    return r;
}

ResultadoBusca busca_binaria(int vet[], int n, int elem){
    ResultadoBusca r;
    int ini = 0;
    int fim = n - 1;
    int meio;
    r.indice = -1;
    r.comparacoes = 0;
    while(ini <= fim){
        meio = ini + (fim - ini) / 2;
        r.comparacoes++;
        if(elem < vet[meio]){
            fim = meio - 1;
        }
        else if(elem > vet[meio]){
            ini = meio + 1;
        }
        else{
            r.indice = meio;
            return r;
        }
    }
    return r;
}
ResultadoBusca busca_binaria_recursiva_aux(int vet[], int ini, int fim, int elem, int comparacoes){
    ResultadoBusca r;
    int meio;
    if(ini > fim){
        r.indice = -1;
        r.comparacoes = comparacoes;
        return r;
    }
    meio = ini + (fim - ini) / 2;
    comparacoes++;
    if(elem == vet[meio]){
        r.indice = meio;
        r.comparacoes = comparacoes;
        return r;
    }
    if(elem < vet[meio]){
        return busca_binaria_recursiva_aux(vet, ini, meio - 1, elem, comparacoes
        );
    }
    return busca_binaria_recursiva_aux(vet, meio + 1, fim, elem, comparacoes);
}
ResultadoBusca busca_binaria_recursiva(int vet[], int n, int elem){
    return busca_binaria_recursiva_aux(vet, 0, n - 1, elem, 0);
}
void libera_vetor(int *vet){
    free(vet);
}