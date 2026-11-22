# 01 — Validação do alfabeto na entrada

**Status:** Aberto · **Prioridade:** Alta · **Local:** `bruteforce_full.asm`, após `len_ok` (~linha 92)

## Problema
Se a entrada contém um byte fora de `[ALPHA_MIN, ALPHA_MAX]` (ex.: TAB = 9), nenhum candidato jamais será igual à entrada e o programa roda para sempre.

## Comportamento esperado
Antes de iniciar a busca, percorrer `input[0..r13)` e, se algum byte estiver fora do alfabeto, imprimir uma mensagem de erro (indicando a posição) e sair com código ≠ 0 (ver [09](09-codigo-saida.md)).

## Critérios de aceite
- [ ] `printf 'a\tb\n' | ./bruteforce_full` termina imediatamente com erro.
- [ ] Entradas válidas continuam funcionando sem mudança.
