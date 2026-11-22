# 03 — Entrada longa truncada e vazamento no stdin

**Status:** Aberto · **Prioridade:** Alta · **Local:** leitura da entrada (linhas 74–91)

## Problema
`read` lê no máximo 256 bytes. Com mais de 255 caracteres, o texto é truncado sem aviso e o restante permanece no buffer do terminal — ao sair, o shell executa esse resto como comando.

## Comportamento esperado
- Se a linha não terminar em `\n` dentro de 256 bytes, avisar que foi truncada (ou rejeitar).
- Descartar o restante com `read` em loop até `\n` ou EOF.
- Tratar `read` parcial (entrada via pipe pode chegar em pedaços).

## Critérios de aceite
- [ ] `python3 -c 'print("a"*300)' | ./bruteforce_full` não deixa sobra no stdin e informa o truncamento.
- [ ] Digitar 300 caracteres interativamente não executa nada no shell depois.
