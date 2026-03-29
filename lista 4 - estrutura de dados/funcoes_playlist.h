#ifndef FUNCOES_PLAYLIST_H
#define FUNCOES_PLAYLIST_H

#include "lista_dupla.h"

NoListaDupla* insereFimPlaylist(NoListaDupla* head, char* nomeMusica);
NoListaDupla* insereNaPosicaoPlaylist(NoListaDupla* head, char* nomeMusica, int posicao);
NoListaDupla* removeMusicaPlaylistTitulo(NoListaDupla* head, char* nomeMusica);
NoListaDupla* removePosicaoPlaylist(NoListaDupla*, int);
NoListaDupla* moverMusicaPlaylist(NoListaDupla*, int, int);
void imprimePlaylist(NoListaDupla*);

#endif  