# 06 — Verificação teórica do número de tentativas

**Status:** Aberto · **Prioridade:** Baixa (didático)

## Ideia
Para alfabeto de tamanho A e entrada de tamanho n, o número de tentativas é:

T = Σ_{k=1}^{n-1} A^k + pos(entrada) + 1

onde `pos` é o índice da entrada na ordem lexicográfica (dígitos em base A, cada um = byte − ALPHA_MIN).

## Comportamento esperado
Documentar a fórmula (no README ou cabeçalho) e, opcionalmente, imprimir o valor esperado ao lado do contador real.

## Critérios de aceite
- [ ] Para 3 entradas de teste, contador real = valor da fórmula.
