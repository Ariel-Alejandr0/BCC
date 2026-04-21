#ifndef ARVORE_H
#define ARVORE_H
struct noArvoreBinaria {
    char info[50];
    struct noArvoreBinaria *sae;
    struct noArvoreBinaria *sad;
};
typedef struct noArvoreBinaria NoArvoreBinaria;
struct arvoreBinaria {
    NoArvoreBinaria *raiz;
};
typedef struct arvoreBinaria ArvoreBinaria;
ArvoreBinaria *ab_cria(void);
NoArvoreBinaria *ab_cria_no(char *v, NoArvoreBinaria *sae, NoArvoreBinaria *sad);
void ab_define_raiz(ArvoreBinaria *a, NoArvoreBinaria *r);
int ab_vazia(ArvoreBinaria *a);
int ab_pertence(ArvoreBinaria *a, char *v);
int ab_folhas(ArvoreBinaria *a);
int ab_num_nos(ArvoreBinaria *a);
int ab_altura(ArvoreBinaria *a);
int ab_igual(ArvoreBinaria *a1, ArvoreBinaria *a2);
void ab_imprime_pre(ArvoreBinaria *a);
void ab_imprime_sim(ArvoreBinaria *a);
void ab_imprime_pos(ArvoreBinaria *a);
void ab_libera(ArvoreBinaria *a);
#endif