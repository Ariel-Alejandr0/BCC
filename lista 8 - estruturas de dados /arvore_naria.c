#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_naria.h"
ArvoreNaria *an_cria(void){
    ArvoreNaria *a;
    a = (ArvoreNaria*) malloc(sizeof(ArvoreNaria));
    if (a!= NULL){
        a->raiz = NULL;
    }
    return a;
}
NoArvoreNaria *an_cria_no(char *v){
    NoArvoreNaria *novo;
    novo = (NoArvoreNaria*) malloc(sizeof(NoArvoreNaria));
    if(novo != NULL){
        strncpy(novo->info, v, sizeof(novo->info)-1);
        novo->info[sizeof(novo->info)-1] = '\0';
        novo->prim = NULL;
        novo->prox = NULL;
    }
    return novo;
}
void an_define_raiz(ArvoreNaria *a, NoArvoreNaria *r){
    a->raiz = r;
}
void an_insere_filho(NoArvoreNaria *pai, NoArvoreNaria *filho){
    NoArvoreNaria *aux;
    if (pai->prim == NULL){
        pai->prim = filho;
    }
    else{
        aux = pai->prim;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = filho;
    }
}
int an_vazia(ArvoreNaria *a){
    if(a->raiz == NULL){
        return 1;
    }
    return 0;
}
int pertence_no(NoArvoreNaria *no, char *v){
    if(no == NULL){
        return 0;
    }
    if(strcmp(no->info, v) == 0){
        return 1;
    }
    if(pertence_no(no->prim, v)){
        return 1;
    }
    return pertence_no(no->prox, v);
}
int an_pertence(ArvoreNaria *a, char *v){
    return pertence_no(a->raiz, v);
}
int conta_nos(NoArvoreNaria *no){
    if(no == NULL){
        return 0;
    }
    return 1 + conta_nos(no->prim) + conta_nos(no->prox);
}
int an_num_nos(ArvoreNaria *a){
    return conta_nos(a->raiz);
}
int conta_folhas(NoArvoreNaria *no){
    if(no == NULL){
        return 0;
    }
    if(no->prim == NULL){
        return 1 + conta_folhas(no->prox);
    }
    return conta_folhas(no->prim) + conta_folhas(no->prox);
}
int an_folhas(ArvoreNaria *a){
    return conta_folhas(a->raiz);
}
int altura_no(NoArvoreNaria *no){
    int maior = 0;
    int h;
    NoArvoreNaria *aux;
    if(no == NULL){
        return 0;
    }
    aux = no->prim;
    while(aux != NULL){
        h = altura_no(aux);
        if(h > maior){
            maior = h;
        }
        aux = aux->prox;
    }
    return maior + 1;
}
int an_altura(ArvoreNaria *a){
    return altura_no(a->raiz);
}
int iguais_no(NoArvoreNaria *n1, NoArvoreNaria *n2){
    if(n1 == NULL && n2 == NULL){
        return 1;
    }
    if(n1 == NULL || n2 == NULL){
        return 0;
    }
    if(strcmp(n1->info, n2->info) != 0){
        return 0;
    }
    return iguais_no(n1->prim, n2->prim) && iguais_no(n1->prox, n2->prox);
}
int an_igual(ArvoreNaria *a1, ArvoreNaria *a2){
    return iguais_no(a1->raiz, a2->raiz);
}
void imprime_no(NoArvoreNaria *no, int nivel){
    int i;
    if(no == NULL){
        return;
    }
    for(i = 0; i < nivel; i++){
       printf(" ");
    }
    printf("%s\n", no->info);
    imprime_no(no->prim, nivel + 1);
    imprime_no(no->prox, nivel);
}
void an_imprime(ArvoreNaria *a){
    imprime_no(a->raiz, 0);
}
void libera_no(NoArvoreNaria *no){
    if(no == NULL){
        return;
    }
    libera_no(no->prim);
    libera_no(no->prox);
    free(no);
}
void an_libera(ArvoreNaria *a){
    libera_no(a->raiz);
    free(a);
}
