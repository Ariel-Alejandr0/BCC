#ifndef ARVORE_NARIA_H
#define ARVORE_NARIA_H
struct noArvoreNaria{
    char info[50];
    struct noArvoreNaria *prim;
    struct noArvoreNaria *prox;
}; 
typedef struct noArvoreNaria NoArvoreNaria;
struct arvoreNaria{
    NoArvoreNaria *raiz;
};
typedef struct arvoreNaria ArvoreNaria;
ArvoreNaria *an_cria(void);
NoArvoreNaria *an_cria_no(char *v);
void an_define_raiz(ArvoreNaria *a, NoArvoreNaria *v);
void an_insere_filho(NoArvoreNaria *pai, NoArvoreNaria *filho);
int an_vazia(ArvoreNaria *a);
int an_pertence(ArvoreNaria *a, char *v);
int an_num_nos(ArvoreNaria *a);
int an_folhas(ArvoreNaria *a);
int an_altura(ArvoreNaria *a);
int an_igual(ArvoreNaria *a1, ArvoreNaria *a2);
void an_imprime(ArvoreNaria *a);
void an_libera(ArvoreNaria *a);
#endif