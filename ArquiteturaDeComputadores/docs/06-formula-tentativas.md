# 06 — Verificação teórica do número de tentativas

**Status:** Resolvido · **Prioridade:** Baixa (didático)

## Ideia
Para alfabeto de tamanho A e entrada de tamanho n, o número de tentativas é:

T = Σ_{k=1}^{n-1} A^k + pos(entrada) + 1

onde `pos` é o índice da entrada na ordem lexicográfica (dígitos em base A, cada um = byte − ALPHA_MIN).

## Comportamento esperado
Documentar a fórmula (no README ou cabeçalho) e, opcionalmente, imprimir o valor esperado ao lado do contador real.

## Critérios de aceite
- [x] Para 3 entradas de teste, contador real = valor da fórmula.

## Resultado
Fórmula documentada no cabeçalho do `.asm`; `calc_expected` calcula T antes da busca (com detecção de estouro de 64 bits via CF de `mul`/`add`) e a saída final fica `Tentativas totais: X (esperado pela formula: Y)`.

| Entrada | Real | Fórmula |
|---------|-----:|--------:|
| ` `     | 1 | 1 |
| `a`     | 66 | 66 |
| `ab`    | 6 337 | 6 337 |
| `Oi!`   | 440 232 | 440 232 |
| `~~~~`  | 82 317 120 | 82 317 120 |

O ramo "nao cabe em 64 bits" (n ≥ 10) não foi exercitado em execução: a busca não termina em tempo útil.
