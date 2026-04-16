#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "atendimento.h"
int main() {
    Fila* f = fila_cria(5);

    for(int i = 1; i < 6; i++) {
        fila_enqueue(f, 100 + i);
    }
    printf("Fila criada:\n");
    mostrar_fila(f);

    chama(f);
    
    fila_enqueue(f, 106);
    mostrar_fila(f);
    
    reseta_fila(f);
    printf("Fila após resetar:\n");
    mostrar_fila(f);

    return 0;
}