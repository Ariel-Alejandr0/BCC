#include <stdlib.h>
#include <stdio.h>
#include "lista_simples.h"
NoLista *sllCria(void){ 
//    NoLista *no = malloc(sizeof(NoLista));
//    if(no != NULL){
//     no->info = 0;
//     no->prox = NULL;
//    }
//   return no;
    return NULL;    
}

NoLista *sllInsere(NoLista *head, int v){
    NoLista *no = malloc(sizeof(NoLista));
    no->info = v;
    no->prox = head;
    return no;
}
void sllImprime(NoLista *head){
    if(head == NULL){
        return;
    }

    printf("[%.2f] %s", head->info, head->prox != NULL ? "-> " : "");
    sllImprime(head->prox);
}
int sllVazia(NoLista *head){
    if(head == NULL){
        return 1;
    }
    return 0;
};
NoLista *sllBusca(NoLista *head, int v){
    if(head == NULL){
        return NULL;
    }
    if(head->info != v){
       return sllBusca(head->prox, v);
    }
    return head;
};
int sllComprimento(NoLista *head){
    int count = 0;
    while(head != NULL){
        count++;
        head = head->prox;
    }
    return count;
};
NoLista *sllUltimo(NoLista *head){
    if(head == NULL){
        return NULL;

    }
    while(head->prox != NULL){
        head = head->prox;
    }
    return head;
};
NoLista *sllRetira(NoLista *head, float v){
    NoLista **ponteiro = &head;
    if (v == -1.0 && head != NULL){//remove primeiro elemento se v == -1
        NoLista *temp = head;
        head = head->prox;
        free(temp);
        return head;
    }
    while (*ponteiro != NULL && (*ponteiro)->info != v)
    {
        ponteiro = &(*ponteiro)->prox;
    }
    if(*ponteiro != NULL){
        NoLista *temp = *ponteiro;
        *ponteiro = temp->prox;
        free(temp);
        temp = NULL;
    }
    return head;
};
NoLista *sllLibera(NoLista *head){
    NoLista *temp;
    while (head != NULL){
        temp = head->prox;
        free(head);
        head = temp;
    }
    return NULL;
};
