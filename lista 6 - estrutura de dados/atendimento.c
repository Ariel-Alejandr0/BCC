#include "fila.h"
#include "atendimento.h"
#include <stdio.h>
#include <stdlib.h>

void chama(Fila* f){
    if (fila_vazia(f)){
        printf("Nenhuma senha para chamar.\n");
        return;
    }
    int senha = fila_dequeue(f);
    printf("Chamando senha: %d\n", senha);
}

void mostrar_fila(Fila* f){
    if (fila_vazia(f)){
        printf("Fila vazia.\n");
        return;
    }
    printf("Senhas na fila:\n");
    for(int i = 0; i < f->n; i++){
        int index = (f->ini + i) % f->tam;
        printf("%d\n", f->vet[index]);
    }
}
void reseta_fila(Fila* f){
    f->n = 0;
    f->ini = 0;
}
