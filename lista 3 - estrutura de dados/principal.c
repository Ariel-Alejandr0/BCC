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
    printf("\n");//só para quebrar linha

    listaEncadeada = sllInsereFim(listaEncadeada, 0.0);
    sllImprime(listaEncadeada);
    printf("\n");//só para quebrar linha

    
    //criando a lista cópia;
    NoLista *copiaListaEncadeada = clone_list(listaEncadeada);
    printf("Imprimindo a cópia:\n");//só para quebrar linha
    sllImprime(copiaListaEncadeada);
    
    sllIgual(listaEncadeada, copiaListaEncadeada) == 1 ? printf("As listas são iguais\n") : printf("As listas são diferentes\n");
    listaEncadeada = sllInsereFim(listaEncadeada, -1.0);
    printf("Após operção de inserir ao final de uma lista Encadeada Original: \n");
    sllIgual(listaEncadeada, copiaListaEncadeada) == 1 ? printf("As listas são iguais\n") : printf("As listas são diferentes\n");
    sllImprimeRecursivo(listaEncadeada);
    sllImprimeRecursivo(copiaListaEncadeada);

    printf("retirando o elemento -1.0 da lista original: \n");
    listaEncadeada = sllRetiraRecursivo(listaEncadeada, -1.0);
    sllImprimeRecursivo(listaEncadeada);
    sllImprimeRecursivo(copiaListaEncadeada);

    printf("Imprimindo comprimento das listas:\n");
    printf("Comprimento da lista original: %i\n", sllComprimentoRecursivo(listaEncadeada));
    printf("Comprimento da lista cópia: %i\n", sllComprimentoRecursivo(copiaListaEncadeada));

    listaEncadeada = sllLibera(listaEncadeada);
    sllImprime(listaEncadeada); //não imprime nada
    return 0;
}
