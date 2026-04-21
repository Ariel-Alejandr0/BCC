#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    //arvore 1
    NoArvoreBinaria *Brasil = ab_cria_no("Brasil", NULL, NULL);
    NoArvoreBinaria *Argentina = ab_cria_no("Argentina", NULL, NULL);
    NoArvoreBinaria *Alemanha = ab_cria_no("Alemanha", NULL, NULL);
    NoArvoreBinaria *Chile = ab_cria_no("Chile", NULL, NULL);
    NoArvoreBinaria *SemiFinal1 = ab_cria_no ("Semifinal 1", Brasil, Argentina);
    NoArvoreBinaria *SemiFinal2 = ab_cria_no ("Semifinal 2", Alemanha, Chile);
    NoArvoreBinaria *Final = ab_cria_no("Final", SemiFinal1, SemiFinal2);
    ArvoreBinaria *a = ab_cria();
    ab_define_raiz(a, Final);
    
    //cópia da arvore 1
    NoArvoreBinaria *Brasil1 = ab_cria_no("Brasil", NULL, NULL);
    NoArvoreBinaria *Argentina1 = ab_cria_no("Argentina", NULL, NULL);
    NoArvoreBinaria *Alemanha1 = ab_cria_no("Alemanha", NULL, NULL);
    NoArvoreBinaria *Chile1 = ab_cria_no("Chile", NULL, NULL);

    NoArvoreBinaria *SemiFinal1_1 = ab_cria_no("Semifinal 1", Brasil1, Argentina1);
    NoArvoreBinaria *SemiFinal2_1 = ab_cria_no("Semifinal 2", Alemanha1, Chile1);

    NoArvoreBinaria *Final1 = ab_cria_no("Final", SemiFinal1_1, SemiFinal2_1);

    ArvoreBinaria *a1 = ab_cria();
    ab_define_raiz(a1, Final1);

    //arvore a3 diferente
    NoArvoreBinaria *Brasil3 = ab_cria_no("Brasil", NULL, NULL);
    NoArvoreBinaria *Argentina3 = ab_cria_no("Argentina", NULL, NULL);
    NoArvoreBinaria *Alemanha3 = ab_cria_no("Alemanha", NULL, NULL);
    NoArvoreBinaria *Uruguai3 = ab_cria_no("Uruguai", NULL, NULL); // 🔴 mudou aqui

    NoArvoreBinaria *SemiFinal1_3 = ab_cria_no("Semifinal 1", Brasil3, Argentina3);
    NoArvoreBinaria *SemiFinal2_3 = ab_cria_no("Semifinal 2", Alemanha3, Uruguai3);

    NoArvoreBinaria *Final3 = ab_cria_no("Final", SemiFinal1_3, SemiFinal2_3);

    ArvoreBinaria *a3 = ab_cria();
    ab_define_raiz(a3, Final3);
    
    ab_imprime_pre(a);
    printf("\n");
    ab_imprime_sim(a);
    printf("\n");
    ab_imprime_pos(a);
    printf("numero total de nos: %d\n", ab_num_nos(a));
    printf("numero total de folhas: %d\n", ab_folhas(a));
    printf("altura da arvore: %d\n", ab_altura(a));

    char selecao[50];
    printf("\nDigite o nome da selecao ou partida para pesquisar: ");
    scanf("%s", selecao);
    printf("\n%s!", ab_pertence(a, selecao) == 1 ? "PERTENCE!!" : "N tá aqui");
    printf("\nÁrvore A %sÉ igual a árvore A1", ab_igual(a, a1) == 1 ? "" : "NÃO ");
    printf("\nÁrvore A %sÉ igual a árvore A3", ab_igual(a, a3) == 1 ? "" : "NÃO ");
}