# 04 — Comentário de montagem com nome errado

**Status:** Aberto · **Prioridade:** Baixa · **Local:** linhas 2 e 7

## Problema
O cabeçalho cita `bruteforce_full.s`, mas o arquivo é `bruteforce_full.asm`.

## Comportamento esperado
Comandos do cabeçalho funcionam copiando e colando:
```
as bruteforce_full.asm -o bruteforce_full.o
ld bruteforce_full.o -o bruteforce_full
```

## Critérios de aceite
- [ ] Nome no comentário igual ao nome real do arquivo.
