#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
ArvoreBinaria *ab_cria(void){
    ArvoreBinaria *a = (ArvoreBinaria *) malloc(sizeof(ArvoreBinaria));
    if (a == NULL){
        return NULL;
    }
    a->raiz = NULL;
    return a;
}
NoArvoreBinaria *ab_cria_no(char *v, NoArvoreBinaria *sae, NoArvoreBinaria *sad){
    NoArvoreBinaria *no = (NoArvoreBinaria *) malloc(sizeof(NoArvoreBinaria));
    if (no == NULL){
        return NULL;
    }
    strcpy(no->info, v);
    no->sae = sae;
    no->sad = sad;
    return no;
}
void ab_define_raiz(ArvoreBinaria *a, NoArvoreBinaria *r){
    a->raiz = r;
}
int ab_vazia(ArvoreBinaria *a){
    if(a == NULL || a->raiz == NULL){
        return 1;
    }
    else{
        return 0;
    }
}
int pertence_no(NoArvoreBinaria *no, char *v){
    if(no == NULL){
        return 0;
    }
    if (strcmp(no->info, v) == 0){
        return 1;
    }
    return pertence_no(no->sae, v) || pertence_no(no->sad, v);
}
int ab_pertence(ArvoreBinaria *a, char *v){
   if (a == NULL || a->raiz == NULL){
    return 0;
   }
    return pertence_no(a->raiz, v);
}
int folhas(NoArvoreBinaria *no){
    if (no == NULL){
        return 0;
    }
    if (no->sae == NULL && no->sad == NULL){
        return 1;
    }
    return folhas(no->sae) + folhas(no->sad);
}
int ab_folhas(ArvoreBinaria *a){
    if (a == NULL || a->raiz == NULL){
        return 0;
    } 
    return folhas(a->raiz);
}
int conta_nos(NoArvoreBinaria *no){
    if (no == NULL){
        return 0;
    }
    return 1 + conta_nos(no->sae) + conta_nos(no->sad);
}
int ab_num_nos(ArvoreBinaria *a){
    if (a == NULL || a->raiz == NULL){
        return 0;
    }
    return conta_nos(a->raiz);
}
int altura_no(NoArvoreBinaria *no){
    if (no == NULL){
        return -1;
    }
    int h_esq = altura_no(no->sae);
    int h_dir = altura_no(no->sad);
    if (h_esq > h_dir){
        return h_esq + 1;
    }
    else{
        return h_dir + 1;
    }
} 
int ab_altura(ArvoreBinaria *a){
    if (a == NULL || a->raiz == NULL){
        return -1;
    }
    return altura_no(a->raiz);
}
int no_igual(NoArvoreBinaria *n1, NoArvoreBinaria *n2){
    if (n1 == NULL && n2 == NULL){
        return 1;
    }
    if (n1 == NULL || n2 == NULL){
        return 0;
    }
    if (strcmp(n1->info, n2->info) != 0){
        return 0;
    }
    return no_igual(n1->sae, n2->sae) && no_igual(n1->sad, n2->sad);
}
int ab_igual(ArvoreBinaria *a1, ArvoreBinaria *a2){
    if (a1 == NULL && a2 == NULL){
        return 1;
    }
    if (a1 == NULL || a2 == NULL){
        return 0;
    }
    return no_igual(a1->raiz, a2->raiz);
}
void pre_imprime(NoArvoreBinaria *no){
    if (no != NULL){
        printf("%s\n", no->info);
        pre_imprime(no->sae);
        pre_imprime(no->sad);
    }
}
void ab_imprime_pre(ArvoreBinaria *a){
    if (a == NULL || a->raiz == NULL){
        return;
    }
    pre_imprime(a->raiz); 
}
void sim_imprime(NoArvoreBinaria *no){
    if (no == NULL){
        return;
    }
    sim_imprime(no->sae);
    printf("%s\n", no->info);
    sim_imprime(no->sad);
}
void ab_imprime_sim(ArvoreBinaria *a){
    if (a == NULL || a->raiz == NULL){
        return;
    }
    sim_imprime(a->raiz);
}
void pos_imprime(NoArvoreBinaria *no){
    if (no == NULL){
        return;
    }
    pos_imprime(no->sae);
    pos_imprime(no->sad);
    printf("%s\n", no->info);
}
void ab_imprime_pos(ArvoreBinaria *a){
    if (a == NULL || a->raiz == NULL){
        return;
    }
    pos_imprime(a->raiz);
}
void libera(NoArvoreBinaria *no){
    if (no == NULL){
        return;
    }
    libera(no->sae);
    libera(no->sad);
    free(no);
}
void ab_libera(ArvoreBinaria *a){
    if (a == NULL){
        return;
    }
    libera(a->raiz);
    free(a);
}