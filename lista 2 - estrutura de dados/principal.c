#include <stdio.h>
#include "lista_simples.h"

int main(){
    NoLista *listaEncadeada = sllCria();

    for (int i = 1; i <= 10; i++){
        listaEncadeada = sllInsere(listaEncadeada, i);
    }

    sllImprime(listaEncadeada);

    printf("\nLista %sestá vazia\n", 
        (sllVazia(listaEncadeada)) == 1 ? "" : "NÃO "
    );

    NoLista *endercoMemoria = (sllBusca(listaEncadeada, 5.0));
    printf("Elemento %.2f está no endereco de memória: %p\n", endercoMemoria->info, endercoMemoria);
    
    printf("Comprimento desta lista é: %i\n", sllComprimento(listaEncadeada));

    endercoMemoria = sllUltimo(listaEncadeada);
    printf("Ultimo Elemento [%.2f] está no endereco de memória: %p\n", endercoMemoria->info, endercoMemoria);

    //remove o primeiro elemento da lista
    listaEncadeada = sllRetira(listaEncadeada, -1.0);
    sllImprime(listaEncadeada);
    
    printf("\n");//só para quebrar linha
    
    //remove o 5
    listaEncadeada = sllRetira(listaEncadeada, 5.0);
    sllImprime(listaEncadeada);

    listaEncadeada = sllLibera(listaEncadeada);
    sllImprime(listaEncadeada); //não imprime nada
    return 0;
}