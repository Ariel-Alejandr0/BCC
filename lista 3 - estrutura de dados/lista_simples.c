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
        printf("\n");//só para quebrar linha
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
// versao lista 3
NoLista *sllInsereFim(NoLista *head, float v){
    NoLista *no = malloc(sizeof(NoLista));
    no->info = v;
    no->prox = NULL;

    if(head == NULL){
        return no;
    }

    NoLista *ultimo = sllUltimo(head);
    ultimo->prox = no;

    return head;
}
int sllIgual(NoLista *lista1, NoLista *lista2){
    if(lista1 == NULL && lista2 == NULL){
        return 1;
    }
    else{
        if(lista1 == NULL || lista2 == NULL){
            return 0;
        }
        if(lista1->info == lista2->info){
            return sllIgual(lista1->prox, lista2->prox);
        }
        else{
            return 0;
        }
    }
}
void sllImprimeRecursivo(NoLista *head){
    sllImprime(head);
}
NoLista *sllRetiraRecursivo(NoLista *head, float v){
    if(head == NULL){
        return NULL;
    }

    if(head->info == v){
        NoLista *temp = head;
        head = head->prox;
        free(temp);
        return head;
    }

    head->prox = sllRetiraRecursivo(head->prox, v);
    return head;
}
int sllComprimentoRecursivo(NoLista *head){
    if(head == NULL){
        return 0;
    }
    return 1 + sllComprimentoRecursivo(head->prox);
}
int sllIgualRecursivo(NoLista *lista1, NoLista *lista2){
    return sllIgual(lista1, lista2);
}
NoLista* clone_list(NoLista* head) {
    if (!head) return NULL;
    NoLista *new_head = NULL, *new_tail = NULL;
    for (NoLista *p = head; p != NULL; p = p->prox) {
        NoLista *n = malloc(sizeof(NoLista));
        if (!n) return NULL; // omitir tratamento de erro completo
        n->info = p->info;     // se info for struct/ponteiro, clone conforme necessário
        n->prox = NULL;
        if (!new_head) new_head = new_tail = n;
        else { new_tail->prox = n; new_tail = n; }
    }
    return new_head;
}
