# 03 — Entrada longa truncada e vazamento no stdin

**Status:** Resolvido · **Prioridade:** Alta · **Local:** leitura da entrada (linhas 74–91)

## Problema
`read` lê no máximo 256 bytes. Com mais de 255 caracteres, o texto é truncado sem aviso e o restante permanece no buffer do terminal — ao sair, o shell executa esse resto como comando.

## Comportamento esperado
- Se a linha não terminar em `\n` dentro de 256 bytes, avisar que foi truncada (ou rejeitar).
- Descartar o restante com `read` em loop até `\n` ou EOF.
- Tratar `read` parcial (entrada via pipe pode chegar em pedaços).

## Critérios de aceite
- [x] `python3 -c 'print("a"*300)' | ./bruteforce_full` não deixa sobra no stdin e informa o truncamento.
- [x] Digitar 300 caracteres interativamente não executa nada no shell depois.

## Implementação
- A leitura agora é um loop (`read_loop`) que junta leituras parciais até encontrar `\n`, chegar ao EOF ou encher os 255 bytes.
- Quando o buffer enche sem `\n`, o `drain_rest` lê e descarta o resto da linha em blocos de 64 bytes e escreve um aviso no stderr. Uma entrada de exatamente 255 caracteres não gera aviso.
- Se o `read` falhar, o programa sai com código 2 (conforme a tabela da [spec 09](09-codigo-saida.md)).
- Testado por pipe (300 caracteres geram o aviso; 255 não geram) e num pty: depois de digitar 300 caracteres, o que sobra no stdin é apenas a linha seguinte.
