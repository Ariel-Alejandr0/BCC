#include <stdio.h>
#include "arvore_busca.h"

int main()
{
    /* 1. Criar arvore vazia */
    ArvoreBusca *a = abb_cria();

    /* 2. Inserir 15 codigos */
    int codigos[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 55, 65, 75, 85, 10, 25};
    int n = 15, i;
    for (i = 0; i < n; i++)
        abb_insere(a, codigos[i]);

    /* 3. Imprimir em ordem crescente */
    printf("Ordem crescente:\n");
    abb_imprime_crescente(a);

    /* 4. Imprimir em ordem decrescente */
    printf("Ordem decrescente:\n");
    abb_imprime_decrescente(a);

    /* 5. Buscar tres codigos existentes */
    printf("\nBusca de codigos existentes:\n");
    printf("Busca 50: %s\n", abb_pertence(a, 50) ? "encontrado" : "nao encontrado");
    printf("Busca 35: %s\n", abb_pertence(a, 35) ? "encontrado" : "nao encontrado");
    printf("Busca 85: %s\n", abb_pertence(a, 85) ? "encontrado" : "nao encontrado");

    /* 6. Buscar tres codigos inexistentes */
    printf("\nBusca de codigos inexistentes:\n");
    printf("Busca 99: %s\n", abb_pertence(a, 99) ? "encontrado" : "nao encontrado");
    printf("Busca  1: %s\n", abb_pertence(a,  1) ? "encontrado" : "nao encontrado");
    printf("Busca 42: %s\n", abb_pertence(a, 42) ? "encontrado" : "nao encontrado");

    /* 7. Numero total de nos */
    printf("\nTotal de nos:   %d\n", abb_num_nos(a));

    /* 8. Quantidade de folhas */
    printf("Total de folhas: %d\n", abb_folhas(a));

    /* 9. Altura da arvore */
    printf("Altura:          %d\n", abb_altura(a));

    /* 10. Remover no folha (85) */
    printf("\nRemovendo no folha (85)...\n");
    abb_retira(a, 85);
    abb_imprime_crescente(a);

    /* 11. Remover no com um filho (80 agora so tem filho esquerdo 75) */
    printf("Removendo no com um filho (80)...\n");
    abb_retira(a, 80);
    abb_imprime_crescente(a);

    /* 12. Remover no com dois filhos (70 tem filhos 60 e 75) */
    printf("Removendo no com dois filhos (70)...\n");
    abb_retira(a, 70);
    abb_imprime_crescente(a);

    /* Liberar memoria */
    abb_libera(a);

    return 0;
}