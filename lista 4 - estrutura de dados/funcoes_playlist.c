#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_dupla.h"
NoListaDupla* insereFimPlaylist(NoListaDupla* head, char* nomeMusica){
    if (nomeMusica == NULL){
        printf("Erro: musica invalida.\n");
        return head;
    }

    head = dllInsereFim(head, nomeMusica);

    printf("Música '%s' inserida no fim da playlist.\n", nomeMusica);
    dllImprime(head, 1);

    return head;
}
NoListaDupla* insereNaPosicaoPlaylist(NoListaDupla* head, char* nomeMusica, int posicao){
    // validações básicas
    if (nomeMusica == NULL || posicao <= 0){
        printf("Erro: parametros invalidos.\n");
        return head;
    }

    // lista vazia
    if (dllVazia(head)){
        printf("Erro: lista vazia.\n");
        return head;
    }

    // inserção no início
    if (posicao == 1){
        return dllInsere(head, nomeMusica);
    }

    NoListaDupla* aux = head;

    // andar até posição anterior
    for(int i = 1; i < posicao - 1; i++){
        if(aux == NULL){
            printf("Erro: posicao fora dos limites.\n");
            return head;
        }
        aux = aux->prox;
    }

    // se chegou no fim e não tem próxima posição válida
    if(aux == NULL){
        printf("Erro: posicao fora dos limites.\n");
        return head;
    }

    // inserção no fim
    if(aux->prox == NULL){
        dllInsereFim(head, nomeMusica);
        return head;
    }

    // inserção no meio
    NoListaDupla* no = malloc(sizeof(NoListaDupla));
    if(no == NULL){
        printf("Erro: falha de memoria.\n");
        return head;
    }

    strncpy(no->info, nomeMusica, sizeof(no->info) - 1);
    no->info[sizeof(no->info) - 1] = '\0';

    no->prox = aux->prox;
    no->ant = aux;

    aux->prox->ant = no;
    aux->prox = no;

    return head;
}
NoListaDupla* removeMusicaPlaylistTitulo(NoListaDupla* head, char* nomeMusica){
    if (nomeMusica == NULL){
        printf("Erro: nome da musica invalido.\n");
        return head;
    }

    if (dllVazia(head)){
        printf("Erro: playlist vazia.\n");
        return head;
    }

    NoListaDupla* encontrada = dllBusca(head, nomeMusica);

    if (encontrada == NULL){
        printf("Musica '%s' nao encontrada na playlist.\n", nomeMusica);
        return head;
    }

    head = dllRetira(head, nomeMusica);

    printf("Musica '%s' removida com sucesso.\n", nomeMusica);
    dllImprime(head, 1);

    return head;
} 

NoListaDupla* removePosicaoPlaylist(NoListaDupla* head, int posicao){
    if (posicao <= 0){
        printf("Erro: posicao invalida.\n");
        return head;
    }

    if (dllVazia(head)){
        printf("Erro: playlist vazia.\n");
        return head;
    }

    NoListaDupla* aux = head;

    // remover o primeiro
    if (posicao == 1){
        head = head->prox;
        if (head != NULL){
            head->ant = NULL;
        }
        printf("Musica removida da posicao %d.\n", posicao);
        free(aux);
        dllImprime(head, 1);
        return head;
    }

    // andar até a posição desejada
    for(int i = 1; i < posicao; i++){
        if (aux == NULL){
            printf("Erro: posicao fora dos limites.\n");
            return head;
        }
        aux = aux->prox;
    }

    if (aux == NULL){
        printf("Erro: posicao fora dos limites.\n");
        return head;
    }

    // remover último
    if (aux->prox == NULL){
        aux->ant->prox = NULL;
    }
    // remover do meio
    else{
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }

    printf("Musica removida da posicao %d.\n", posicao);
    free(aux);

    dllImprime(head, 1);
    return head;
}
NoListaDupla* moverMusicaPlaylist(NoListaDupla* head, int origem, int destino){
    if (origem <= 0 || destino <= 0){
        printf("Erro: posicoes invalidas.\n");
        return head;
    }

    if (dllVazia(head)){
        printf("Erro: playlist vazia.\n");
        return head;
    }

    if (origem == destino){
        printf("Nada a fazer: mesma posicao.\n");
        return head;
    }

    NoListaDupla* aux = head;

    // achar nó da posição de origem
    for(int i = 1; i < origem; i++){
        if (aux == NULL){
            printf("Erro: posicao de origem invalida.\n");
            return head;
        }
        aux = aux->prox;
    }

    if (aux == NULL){
        printf("Erro: posicao de origem invalida.\n");
        return head;
    }

    // salvar a música antes de remover
    char nome[sizeof(aux->info)];
    strncpy(nome, aux->info, sizeof(nome));
    nome[sizeof(nome) - 1] = '\0';

    // remove da posição original
    head = removePosicaoPlaylist(head, origem);

    // ajuste importante:
    // se removeu antes do destino, o índice muda
    if (origem < destino){
        destino--;
    }

    // insere na nova posição
    head = insereNaPosicaoPlaylist(head, nome, destino);

    printf("Musica movida de %d para %d.\n", origem, destino);
    dllImprime(head, 1);

    return head;
}
void imprimePlaylist(NoListaDupla* head){
    if (dllVazia(head)){
        printf("Playlist vazia.\n");
        return;
    }

    printf("\n=== PLAYLIST ===\n");
    dllImprime(head, 1);
    printf("================\n");
}