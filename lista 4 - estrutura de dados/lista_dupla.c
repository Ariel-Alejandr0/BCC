#include "lista_dupla.h"
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free
#include <string.h>  // strcpy, strncpy, strcmp

NoListaDupla* dllCria(void){
    return NULL;
};
NoListaDupla* dllInsere(NoListaDupla* head, char *v){
    NoListaDupla* no = malloc(sizeof(NoListaDupla));
    strncpy(no->info, v, sizeof(no->info) - 1);
    no->info[sizeof(no->info) - 1] = '\0';
    no->ant = NULL;
    no->prox = head; 
    if (head != NULL) {
        head->ant = no;  // Ajusta o ponteiro de volta da antiga cabeça
    }
    return no;
};
void dllImprime(NoListaDupla* head, int count){
    if(head != NULL){
        printf("%d. %s\n", count, head->info);
        dllImprime(head->prox, ++count);
    }
    
};
int dllVazia(NoListaDupla* head){
    return (head == NULL);
};

NoListaDupla* dllBusca(NoListaDupla* head, char* v){
    while(head != NULL){
        if(strcmp(head->info, v) == 0){
            return head;
        }
        head = head->prox;
    }
    return NULL;
};
int dllComprimento(NoListaDupla* head){
    int count = 0;
    while(head != NULL){
        count++;
        head = head->prox;
    }
    return count;
};
NoListaDupla* dllUltimo(NoListaDupla* head){
    if(head == NULL){
        return NULL;
    }
    while (head->prox != NULL){
        head = head->prox;
    }
    return head;
};
NoListaDupla* dllRetira(NoListaDupla *head, char* v){
    NoListaDupla* no = dllBusca(head, v);
    if(no == NULL){ 
        return head; 
    }
    if(no->ant == NULL){
        head = no->prox;
        if(head != NULL){
            head->ant = NULL;
        }   
        free(no);
        no = NULL;
        return head;
    } else if(no->prox == NULL){
        no->ant->prox = NULL;
        free(no);
        no = NULL;
        return head;
    } else {
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;
        free(no);
        no = NULL;
        return head;
    }
    return head;
};
void dllLibera(NoListaDupla* head){
    NoListaDupla* temp;
    while (head != NULL){
        temp = head;
        head = head->prox;
        free(temp);
    }
};
NoListaDupla *dllInsereFim(NoListaDupla* head, char* v){
    NoListaDupla* no = malloc(sizeof(NoListaDupla));
    strncpy(no->info, v, sizeof(no->info) - 1);
    no->info[sizeof(no->info) - 1] = '\0';

    no->ant = NULL;
    no->prox = NULL;

    if (head == NULL) {
        return no;
    }

    NoListaDupla* aux = head;

    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    aux->prox = no;
    no->ant = aux;

    return head;
}