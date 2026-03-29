#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_dupla.h"
#include "funcoes_playlist.h"

// remove \n do fgets
void limparNovaLinha(char *str){
    str[strcspn(str, "\n")] = '\0';
}

void menu(){
    printf("\n===== PLAYLIST =====\n");
    printf("1 - Inserir musica no inicio\n");
    printf("2 - Inserir musica no fim\n");
    printf("3 - Inserir musica em posicao\n");
    printf("4 - Remover musica por nome\n");
    printf("5 - Remover musica por posicao\n");
    printf("6 - Mover musica\n");
    printf("7 - Imprimir playlist\n");
    printf("0 - Sair\n");
    printf("====================\n");
    printf("Escolha: ");
}

int main(){
    NoListaDupla* head = dllCria();

    char nome[100];
    char entrada[100]; // 🔥 buffer separado para números

    int opcao, pos1, pos2;

    while(1){
        menu();

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) break;
        opcao = atoi(entrada);

        switch(opcao){

            case 1:
                printf("Nome da musica: ");
                fgets(nome, sizeof(nome), stdin);
                limparNovaLinha(nome);

                head = dllInsere(head, nome);
                printf("Inserida no inicio.\n");
                break;

            case 2:
                printf("Nome da musica: ");
                fgets(nome, sizeof(nome), stdin);
                limparNovaLinha(nome);

                head = dllInsereFim(head, nome);
                printf("Inserida no fim.\n");
                break;

            case 3:
                printf("Nome da musica: ");
                fgets(nome, sizeof(nome), stdin);
                limparNovaLinha(nome);

                printf("Posicao: ");
                fgets(entrada, sizeof(entrada), stdin);
                pos1 = atoi(entrada);

                head = insereNaPosicaoPlaylist(head, nome, pos1);
                break;

            case 4:
                printf("Nome da musica: ");
                fgets(nome, sizeof(nome), stdin);
                limparNovaLinha(nome);

                head = removeMusicaPlaylistTitulo(head, nome);
                break;

            case 5:
                printf("Posicao: ");
                fgets(entrada, sizeof(entrada), stdin);
                pos1 = atoi(entrada);

                head = removePosicaoPlaylist(head, pos1);
                break;

            case 6:
                printf("Posicao origem: ");
                fgets(entrada, sizeof(entrada), stdin);
                pos1 = atoi(entrada);

                printf("Posicao destino: ");
                fgets(entrada, sizeof(entrada), stdin);
                pos2 = atoi(entrada);

                head = moverMusicaPlaylist(head, pos1, pos2);
                break;

            case 7:
                imprimePlaylist(head);
                break;

            case 0:
                printf("Saindo...\n");
                dllLibera(head);
                return 0;

            default:
                printf("Opcao invalida.\n");
        }
    }

    dllLibera(head);
    return 0;
}