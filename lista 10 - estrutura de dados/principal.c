#include <stdio.h>
#include <stdlib.h>
#include "tabela_hash.h"

int main(void)
{
    TabelaHash *tab;
    Aluno *aluno;


    printf("---- (1) Criando tabela hash\n");
    tab = hsh_cria();
    if (tab == NULL)
    {
        printf("Erro: falha ao alocar tabela.\n");
        return 1;
    }
    printf("Tabela criada com sucesso.\n\n");


    printf("---- (2) Inserindo 15 estudantes\n");

    hsh_set(tab, 1001, "Ariel Alejandro", "ariel.alejandro@email.com", 8.5f);
    hsh_set(tab, 1128, "Bruno Souza", "bruno@email.com", 7.2f);
    hsh_set(tab, 1255, "Carla Dias", "carla@email.com", 9.0f);
    hsh_set(tab, 1382, "Diego Rocha", "diego@email.com", 6.8f);

    hsh_set(tab, 2002, "Eva Martins", "eva@email.com", 7.9f);
    hsh_set(tab, 2129, "Fabio Alves", "fabio@email.com", 8.1f);
    hsh_set(tab, 2256, "Gabi Neves", "gabi@email.com", 6.5f);

    hsh_set(tab, 3003, "Hugo Melo", "hugo@email.com", 9.3f);
    hsh_set(tab, 3130, "Iris Pinto", "iris@email.com", 7.4f);

    hsh_set(tab, 4010, "Joao Costa", "joao@email.com", 8.8f);
    hsh_set(tab, 5020, "Karen Reis", "karen@email.com", 7.0f);
    hsh_set(tab, 6030, "Leticia Furquim", "leticia.furquim@email.com", 6.3f);
    hsh_set(tab, 7040, "Mara Cunha", "mara@email.com", 9.1f);
    hsh_set(tab, 8050, "Nino Faria", "nino@email.com", 7.7f);
    hsh_set(tab, 9060, "Olga Vieira", "olga@email.com", 8.4f);

    printf("15 estudantes inseridos.\n\n");


    printf("---- (3) Buscando matriculas existentes\n");

    aluno = hsh_get(tab, 1001);
    if (aluno != NULL)
        printf("  Encontrado: %d | %s | %s | %.2f\n",
               aluno->matricula, aluno->nome, aluno->email, aluno->mediaGeral);

    aluno = hsh_get(tab, 2129);
    if (aluno != NULL)
        printf("  Encontrado: %d | %s | %s | %.2f\n",
               aluno->matricula, aluno->nome, aluno->email, aluno->mediaGeral);

    aluno = hsh_get(tab, 7040);
    if (aluno != NULL)
        printf("  Encontrado: %d | %s | %s | %.2f\n",
               aluno->matricula, aluno->nome, aluno->email, aluno->mediaGeral);

    printf("\n");


    printf("---- (4) Buscando matriculas inexistentes\n");

    aluno = hsh_get(tab, 9999);
    printf("  Matricula 9999: %s\n", aluno == NULL ? "nao encontrada" : "encontrada");

    aluno = hsh_get(tab, 1111);
    printf("  Matricula 1111: %s\n", aluno == NULL ? "nao encontrada" : "encontrada");

    aluno = hsh_get(tab, 5555);
    printf("  Matricula 5555: %s\n", aluno == NULL ? "nao encontrada" : "encontrada");

    printf("\n");


    printf("---- (5) Atualizando estudante (matricula 1001)\n");

    hsh_set(tab, 1001, "Ariel Silva", "ariel.silva@email.com", 9.5f);
    aluno = hsh_get(tab, 1001);
    if (aluno != NULL)
        printf("  Apos update: %d | %s | %s | %.2f\n",
               aluno->matricula, aluno->nome, aluno->email, aluno->mediaGeral);

    printf("\n");

    printf("---- (6) Removendo primeiro da lista de colisao (matricula 1382)\n");
    printf("  Contem 1382 antes: %s\n", hsh_contem(tab, 1382) ? "sim" : "nao");

    hsh_remove(tab, 1382);

    printf("  Contem 1382 apos : %s\n", hsh_contem(tab, 1382) ? "sim" : "nao");
    printf("\n");

    
    printf("---- (7) Removendo do meio da lista de colisao (matricula 1128)\n");
    printf("  Contem 1128 antes: %s\n", hsh_contem(tab, 1128) ? "sim" : "nao");

    hsh_remove(tab, 1128);

    printf("  Contem 1128 apos : %s\n", hsh_contem(tab, 1128) ? "sim" : "nao");
    printf("\n");

    
    printf("---- (8) Tentando remover matricula inexistente (9999)\n");
    hsh_remove(tab, 9999);
    printf("  Operacao concluida sem erros.\n\n");

    
    printf("---- (9) Tabela hash completa\n");
    hsh_imprime(tab);
    printf("\n");


    printf("---- (10-12) Estatisticas finais\n");
    printf("  Total de estudantes cadastrados : %d\n", hsh_quantidade(tab));
    printf("  Elementos em posicoes de colisao: %d\n", hsh_colisoes(tab));
    printf("  Tamanho da maior lista          : %d\n", hsh_maior_lista(tab));
    printf("\n");


    hsh_libera(tab);
    printf("Memoria liberada. Fim do programa.\n");

    return 0;
}