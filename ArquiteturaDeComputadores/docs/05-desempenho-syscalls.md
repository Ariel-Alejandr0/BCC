# 05 — Custo de syscalls por tentativa

**Status:** Aberto · **Prioridade:** Média · **Local:** `main_loop` (linhas 103–124)

## Problema
Cada tentativa faz 3 syscalls (limpar linha, escrever candidato, `nanosleep` de 1 ms). Uma palavra de 3 letras exige ~11 milhões de tentativas ≈ 3 horas só de atraso.

## Propostas
1. Atualizar a tela apenas a cada 2^k tentativas (`test r12, MASK`).
2. Montar `clrline` + candidato em um buffer único → 1 `write`.
3. Permitir definir o atraso na montagem: `as --defsym DELAY_NS=0`.

## Critérios de aceite
- [ ] Com `DELAY_NS=0`, medir com `time` antes/depois e registrar o ganho aqui.
- [ ] A animação continua visível no modo com atraso.
