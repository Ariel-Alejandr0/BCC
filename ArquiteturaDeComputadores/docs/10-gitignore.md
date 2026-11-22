# 10 — Artefatos de build no repositório

**Status:** Aberto · **Prioridade:** Baixa

## Problema
`bruteforce_full` (executável) e `bruteforce_full.o` estão na pasta e entrariam no primeiro commit.

## Comportamento esperado
`.gitignore` com:
```
*.o
bruteforce_full
```
Opcional: `Makefile` com alvos `all`, `run`, `clean`.

## Critérios de aceite
- [ ] `git status` não lista binários.
