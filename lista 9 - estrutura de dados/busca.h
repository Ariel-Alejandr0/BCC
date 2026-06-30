#ifndef BUSCA_H
#define BUSCA_H
struct resultadoBusca {
    int indice;
    int comparacoes;
};
typedef struct resultadoBusca ResultadoBusca;
int *cria_vetor_ordenado(int n);
void imprime_vetor(int vet[], int n);
ResultadoBusca busca_linear_ordenada(int vet[], int n, int elem);
ResultadoBusca busca_binaria(int vet[], int n, int elem);
ResultadoBusca busca_binaria_recursiva(int vet[], int n, int elem);
ResultadoBusca busca_binaria_recursiva_aux(int vet[], int ini, int fim, int elem, int comparacoes);
ResultadoBusca busca_linear(int vet[], int n, int elem);
void libera_vetor(int *vet);
#endif 