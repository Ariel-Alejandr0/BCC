# 08 — Guarda de tamanho máximo em grow_length

**Status:** Aberto · **Prioridade:** Baixa · **Local:** `grow_length` (linha 154)

## Problema
`r14` é incrementado sem checar `MAX_LEN`. Inalcançável na prática, mas com outro alfabeto/limite escreveria além de `cand`.

## Comportamento esperado
Se `r14 > r13` (ou `> MAX_LEN`), encerrar com mensagem "não encontrado" e código ≠ 0. Também é a forma natural de evitar buscar tamanhos inúteis.

## Critérios de aceite
- [ ] Nunca há escrita fora de `cand`.
