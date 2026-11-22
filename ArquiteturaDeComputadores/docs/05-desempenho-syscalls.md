# 05 — Custo de syscalls por tentativa

**Status:** Resolvido · **Prioridade:** Média · **Local:** `main_loop` (linhas 103–124)

## Problema
Cada tentativa faz 3 syscalls (limpar linha, escrever candidato, `nanosleep` de 1 ms). Uma palavra de 3 letras exige ~11 milhões de tentativas ≈ 3 horas só de atraso.

## Propostas
1. Atualizar a tela apenas a cada 2^k tentativas (`test r12, MASK`).
2. Montar `clrline` + candidato em um buffer único → 1 `write`.
3. Permitir definir o atraso na montagem: `as --defsym DELAY_NS=0`.

## Critérios de aceite
- [x] Com `DELAY_NS=0`, medir com `time` antes/depois e registrar o ganho aqui.
- [x] A animação continua visível no modo com atraso.

## Resultado
Implementado: `clrline` e `cand` contíguos na `.data` (1 `write` por atualização, sub-rotina `show_cand`); tela atualizada a cada 2^`SHOW_SHIFT` tentativas; `DELAY_NS` e `SHOW_SHIFT` sobrescrevíveis com `--defsym`. Com atraso, `SHOW_SHIFT` = 0 (toda tentativa aparece, como antes); sem atraso, `SHOW_SHIFT` = 16.

Medição (`printf '...\n' | ./bruteforce_full > /dev/null`, `DELAY_NS=0`):

| Entrada | Tentativas | Antes | Depois |
|---------|-----------:|------:|-------:|
| `~~~`   | 866 495    | 1,69 s | 0,02 s |
| `~~~~`  | 82 317 120 | (não medido, ~160 s estimado) | 0,80 s |
