#include <stdio.h>
#include <stdlib.h>
#include "busca.h"
void imprimeResultado(char *nome, ResultadoBusca r)
{
    printf("%s\n", nome);
    printf("Indice: %d\n", r.indice);
    printf("Comparacoes: %d\n\n", r.comparacoes);
}
int main()
{
    int *vet;
    int i;
    ResultadoBusca r;
    /* vetores pequenos */
    printf("vetor de 10 elementos\n\n");
    vet = cria_vetor_ordenado(10);
    printf("Vetor:\n");
    imprime_vetor(vet, 10);
    int testes[3] = {0, 10, 11};
    for (i = 0; i < 3; i++)
    {
        printf("\n");
        printf("Valor procurado: %d\n", testes[i]);
        printf("\n");
        r = busca_linear(vet, 10, testes[i]);
        imprimeResultado("Busca Linear", r);
        r = busca_linear_ordenada(vet, 10, testes[i]);
        imprimeResultado("Busca Linear Ordenada", r);
        r = busca_binaria(vet, 10, testes[i]);
        imprimeResultado("Busca Binaria Iterativa", r);
        r = busca_binaria_recursiva(vet, 10, testes[i]);
        imprimeResultado("Busca Binaria Recursiva", r);
    }
    libera_vetor(vet);
    /*vetores maiores*/
    int tamanhos[5] = {10, 100, 1000, 10000, 100000};
    printf("\n");
    printf("%-8s %-10s %-10s %-12s %-10s %-12s\n", "n", "elem", "linear", "linear_ord", "binaria", "bin_rec");
    for (i = 0; i < 5; i++)
    {
        int n = tamanhos[i];
        vet = cria_vetor_ordenado(n);
        int elem = vet[n - 1];
        ResultadoBusca l = busca_linear(vet, n, elem);
        ResultadoBusca lo = busca_linear_ordenada(vet, n, elem);
        ResultadoBusca b = busca_binaria(vet, n, elem);
        ResultadoBusca br = busca_binaria_recursiva(vet, n, elem);
        printf("%-8d %-10d %-10d %-12d %-10d %-12d\n", n, elem, l.comparacoes, lo.comparacoes, b.comparacoes, br.comparacoes);
        libera_vetor(vet);
        printf("\n");
        printf("o elemento não existe\n");
        printf("\n");
        printf("%-8s %-10s %-10s %-12s %-10s %-12s\n", "n", "elem", "linear", "linear_ord", "binaria", "bin_rec");
    }
    for (i = 0; i < 5; i++)
    {
        int n = tamanhos[i];
        vet = cria_vetor_ordenado(n);
        int elem = vet[n - 1] + 1;
        ResultadoBusca l = busca_linear(vet, n, elem);
        ResultadoBusca lo = busca_linear_ordenada(vet, n, elem);
        ResultadoBusca b = busca_binaria(vet, n, elem);
        ResultadoBusca br = busca_binaria_recursiva(vet, n, elem);
        printf("%-8d %-10d %-10d %-12d %-10d %-12d\n", n, elem, l.comparacoes, lo.comparacoes, b.comparacoes, br.comparacoes);
        libera_vetor(vet);
    }
    return 0;
}
/*
Questões:
1) Por que a busca binaria exige que o vetor esteja ordenado?
Porque ela elimina metade do vetor a cada comparacao.
2) Em quais casos a busca linear ordenada pode parar antes de chegar ao final do vetor?
Quando encontra-se um valor maior do que o que se procura. Como o vetor esta ordenado, o elemento nao aparecerá nas posicoes seguintes.
3) O que acontece com a quantidade de comparacoes da busca linear quando n aumenta?
Ela cresce proporcionalmente ao tamanho do vetor e no pior caso sao feitas n comparacoes.
4) O que acontece com a quantidade de comparacoes da busca binaria quando n aumenta?
Ela cresce muito lentamente, log2(n).
5) Para os testes realizados, a busca binaria iterativa e a busca binaria recursiva retornaram os mesmos indices?
Sim, ambas executam o mesmo algoritmo e analisam os mesmos intervalos, a diferenca esta apenas na forma de implementacao.
*/