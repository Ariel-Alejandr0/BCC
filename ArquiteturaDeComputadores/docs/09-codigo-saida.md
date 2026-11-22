# 09 — Código de saída em caso de erro

**Status:** Resolvido · **Prioridade:** Média · **Local:** `exit_prog` (linha 195)

## Problema
Entrada vazia, falha de `read` e (futuramente) entrada inválida saem todos com código 0.

## Comportamento esperado
| Situação | Código |
|----------|--------|
| Encontrado | 0 |
| Entrada vazia / EOF | 1 |
| Erro de leitura | 2 |
| Entrada inválida ([01](01-validacao-alfabeto.md)) | 3 |
| Não encontrado ([08](08-guarda-max-len.md)) | 4 |

## Critérios de aceite
- [x] `echo -n | ./bruteforce_full; echo $?` imprime 1.
