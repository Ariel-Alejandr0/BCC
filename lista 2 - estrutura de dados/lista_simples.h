#ifndef LISTA_SIMPLES_H
#define LISTA_SIMPLES_H

struct noLista {
    float info; 
    struct noLista *prox; 

};
typedef struct noLista NoLista;

NoLista *sllCria(void);
NoLista *sllInsere(NoLista *head, int v);
void sllImprime(NoLista *head);
int sllVazia(NoLista *head);
NoLista *sllBusca(NoLista *head, int v);
int sllComprimento(NoLista *head);
NoLista *sllUltimo(NoLista *head);
NoLista *sllRetira(NoLista *head, float v);
NoLista *sllLibera(NoLista *head);
#endif