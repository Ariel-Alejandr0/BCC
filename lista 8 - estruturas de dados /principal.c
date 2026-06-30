#include <stdio.h>
#include <stdlib.h>
#include "arvore_naria.h"

int main(){
    ArvoreNaria *a1 = an_cria();
    NoArvoreNaria *ifc = an_cria_no("IFC");
    an_define_raiz(a1, ifc);
    NoArvoreNaria *blumenau = an_cria_no("Campus Blumenau");
    NoArvoreNaria *camboriu = an_cria_no("Campus Camboriu");
    NoArvoreNaria *araquari = an_cria_no("Campus Araquari");
    an_insere_filho(ifc, blumenau);
    an_insere_filho(ifc, camboriu);
    an_insere_filho(ifc, araquari);
    NoArvoreNaria *bcc = an_cria_no("BCC");
    NoArvoreNaria *pedagogia = an_cria_no("Pedagogia");
    an_insere_filho(blumenau, bcc);
    an_insere_filho(blumenau, pedagogia);
    NoArvoreNaria *ed1 = an_cria_no("Estruturas de Dados I");
    NoArvoreNaria *prog2 = an_cria_no("Programacao II");
    NoArvoreNaria *bd = an_cria_no("Banco de Dados");
    an_insere_filho(bcc, ed1);
    an_insere_filho(bcc, prog2);
    an_insere_filho(bcc, bd);
    NoArvoreNaria *coord = an_cria_no("Coordenacao de Ensino");
    NoArvoreNaria *biblioteca = an_cria_no("Biblioteca");
    an_insere_filho(camboriu, coord);
    an_insere_filho(camboriu, biblioteca);
    NoArvoreNaria *adm = an_cria_no("Administracao");
    NoArvoreNaria *agro = an_cria_no("Agronomia");
    an_insere_filho(araquari, adm);
    an_insere_filho(araquari, agro);
    printf("\nprimeira arvore\n\n");
    an_imprime(a1);
    printf("\nNumero total de nos: %d\n", an_num_nos(a1));
    printf("Quantidade de folhas: %d\n", an_folhas(a1));
    printf("Altura da arvore: %d\n", an_altura(a1));
    printf("\n teste de pertencimento\n");
    printf("BCC pertence? %d\n", an_pertence(a1, "BCC"));
    printf("Biblioteca pertence? %d\n", an_pertence(a1, "Biblioteca"));
    printf("Medicina pertence? %d\n", an_pertence(a1, "Medicina"));
    ArvoreNaria *a2 = an_cria();
    NoArvoreNaria *ifc2 = an_cria_no("IFC");
    an_define_raiz(a2, ifc2);
    NoArvoreNaria *blumenau2 = an_cria_no("Campus Blumenau");
    NoArvoreNaria *camboriu2 = an_cria_no("Campus Camboriu");
    NoArvoreNaria *araquari2 = an_cria_no("Campus Araquari");
    an_insere_filho(ifc2, blumenau2);
    an_insere_filho(ifc2, camboriu2);
    an_insere_filho(ifc2, araquari2);
    NoArvoreNaria *bcc2 = an_cria_no("BCC");
    NoArvoreNaria *pedagogia2 = an_cria_no("Pedagogia");
    an_insere_filho(blumenau2, bcc2);
    an_insere_filho(blumenau2, pedagogia2);
    NoArvoreNaria *ed12 = an_cria_no("Estruturas de Dados I");
    NoArvoreNaria *prog22 = an_cria_no("Programacao II");
    NoArvoreNaria *bd2 = an_cria_no("Banco de Dados");
    an_insere_filho(bcc2, ed12);
    an_insere_filho(bcc2, prog22);
    an_insere_filho(bcc2, bd2);
    NoArvoreNaria *coord2 = an_cria_no("Coordenacao de Ensino");
    NoArvoreNaria *biblioteca2 = an_cria_no("Biblioteca");
    an_insere_filho(camboriu2, coord2);
    an_insere_filho(camboriu2, biblioteca2);
    NoArvoreNaria *adm2 = an_cria_no("Administracao");
    NoArvoreNaria *agro2 = an_cria_no("Agronomia");
    an_insere_filho(araquari2, adm2);
    an_insere_filho(araquari2, agro2);
    if(an_igual(a1, a2)){
        printf("As arvores sao iguais.\n");
    }
    else{
        printf("As arvores sao diferentes.\n");
    }
    NoArvoreNaria *novo = an_cria_no("Engenharia");
    an_insere_filho(araquari2, novo);
    if(an_igual(a1, a2)){
        printf("As arvores continuam iguais.\n");
    }
    else{
        printf("As arvores agora sao diferentes.\n");
    }
    an_libera(a1);
    an_libera(a2);
    return 0;
}