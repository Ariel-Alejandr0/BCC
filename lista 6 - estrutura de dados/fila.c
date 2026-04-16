#include <stdio.h>
#include "fila.h"
#include <stdlib.h>
Fila *fila_cria(int tam){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->tam = tam;
    f->n = 0;
    f->ini = 0;
    f->vet = (int*) malloc(tam *sizeof(int));
    return f;
}
void fila_enqueue(Fila *f, int v){
    if (f->n == f->tam){
        printf("fila cheia");
        abort();
    }
    int fim = (f->ini + f->n) % f->tam;
    f->vet[fim] = v;
    f->n++;
}
int fila_dequeue(Fila *f){
    int v;
    if(f->n == 0){
        printf("fila vazia");
        abort();
    }
    else{
        v = f->vet[f->ini];
        f->ini = (f->ini + 1) % f->tam;
        f->n--;
    }
    return v;
}
int fila_vazia(Fila *f){
    if(f->n == 0){
        return 1;
    }
    else{
        return 0;
    }
}
void fila_imprime(Fila *f){
    if (f->n == 0){
        printf("fila vazia");
        return;
    }
    for(int i = 0; i < f->n; i++){
        int index = (f->ini + i) % f->tam;
        printf("%d\n", f->vet[index]);
    }
}
void fila_reset(Fila *f){
    f->n = 0;
    f->ini = 0;
}
Fila *fila_concatena(Fila *f1, Fila *f2){
    Fila *f3 = fila_cria(f1->n + f2->n);
    for(int i = 0; i < f1->n; i++){
        int index = (f1->ini + i) % f1->tam;
        fila_enqueue(f3, f1->vet[index]);
    }
     for(int i = 0; i < f2->n; i++){
        int index = (f2->ini + i) % f2->tam;
        fila_enqueue(f3, f2->vet[index]);
    }
    return f3;
}
Fila *fila_merge(Fila *f1, Fila *f2){
    Fila *f3 = fila_cria(f1->n + f2->n);
    int i = 0, j = 0;
    while(i < f1->n && j < f2->n){
        int index1 = (f1->ini + i) % f1->tam;
        fila_enqueue(f3, f1->vet[index1]);
        i++;
        int index2 = (f2->ini + j) % f2->tam;
        fila_enqueue(f3, f2->vet[index2]);
        j++;
    }
    while(i < f1->n){
        int index1 = (f1->ini + i) % f1->tam;
        fila_enqueue(f3, f1->vet[index1]);
        i++;
    }
    while(j < f2->n){
        int index2 = (f2->ini + j) % f2->tam;
        fila_enqueue(f3, f2->vet[index2]);
        j++;
    }
    return f3;
}
void fila_libera(Fila *f){
    free(f->vet);
    free(f);
}