#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#define TAM 127
struct aluno
{
    int matricula;
    char nome[81];
    char email[81];
    float mediaGeral;
    struct aluno *prox;
};
typedef struct aluno Aluno;
struct tabelaHash
{
    Aluno *vet[TAM];
};
typedef struct tabelaHash TabelaHash;

TabelaHash *hsh_cria(void);
Aluno *hsh_get(TabelaHash *tab, int matricula);
Aluno *hsh_set(TabelaHash *tab, int matricula, char *nome, char *email, float mediaGeral);
void hsh_remove(TabelaHash *tab, int matricula);
int hsh_contem(TabelaHash *tab, int matricula);
int hsh_quantidade(TabelaHash *tab);
int hsh_colisoes(TabelaHash *tab);
int hsh_maior_lista(TabelaHash *tab);
void hsh_imprime(TabelaHash *tab);
void hsh_libera(TabelaHash *tab);

#endif