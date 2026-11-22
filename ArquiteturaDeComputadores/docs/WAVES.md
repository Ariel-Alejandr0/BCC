# Waves de execução

As specs estão agrupadas em **waves**: conjuntos de specs que mexem no mesmo trecho de código e por isso são feitas juntas, numa só branch e num só PR. As waves seguem em ordem, porque cada uma depende do código deixado pela anterior.

## Visão geral

| Wave | Tema | Specs | Branch | PR | Status |
|------|------|-------|--------|----|--------|
| 0 | Specs pontuais (antes das waves) | [01](01-validacao-alfabeto.md), [02](02-alfabeto-imprimivel.md), [03](03-entrada-longa.md) | `fix/spec-0X-…` | [#2](https://github.com/Ariel-Alejandr0/BCC/pull/2), [#3](https://github.com/Ariel-Alejandr0/BCC/pull/3), [#4](https://github.com/Ariel-Alejandr0/BCC/pull/4) | Concluída |
| 1 | Entrada e saída de erro | [04](04-comentario-montagem.md), [08](08-guarda-max-len.md), [09](09-codigo-saida.md) | `fix/wave-1-entrada-erros` | [#5](https://github.com/Ariel-Alejandr0/BCC/pull/5) | Concluída |
| 2 | Laço principal | [05](05-desempenho-syscalls.md), [06](06-formula-tentativas.md) | `fix/spec-05-…`, `fix/spec-06-…` | [#6](https://github.com/Ariel-Alejandr0/BCC/pull/6), [#7](https://github.com/Ariel-Alejandr0/BCC/pull/7) | Concluída |
| 3 | Limpeza final | [07](07-convencao-registradores.md), [10](10-gitignore.md) | `fix/wave-3-limpeza` | [#8](https://github.com/Ariel-Alejandr0/BCC/pull/8) | Concluída |

```
Wave 0 ──► Wave 1 ──► Wave 2 ──► Wave 3
(01-03)    (04,08,09)  (05,06)    (07,10)
```

## Wave 1 — Entrada e saída de erro

**Trecho:** início (cabeçalho, leitura) e fim do programa (rotinas de saída).

| Spec | Por que está aqui |
|------|-------------------|
| 09 | Define a tabela de códigos de saída usada pelas outras. |
| 08 | Encerra com "não encontrado" usando o código 4 da 09. |
| 04 | Ajuste trivial no mesmo cabeçalho onde a tabela de códigos foi documentada. |

A spec 03 era desta wave, mas foi resolvida antes, no PR #4.

**Resultado:** códigos de saída 0–4 testados (ver PR #5). O total de tentativas para `ab` (6337) confere com a fórmula da spec 06.

## Wave 2 — Laço principal

**Trecho:** `main_loop` e o relatório final (`done_found`).

| Spec | Por que está aqui |
|------|-------------------|
| 05 | Reduz syscalls por tentativa: um `write` só, tela atualizada a cada 2^k tentativas, `DELAY_NS` via `--defsym`. |
| 06 | Mostra o total esperado ao lado do contador; depende do contador que a 05 altera. |

**Ordem:** 05 → 06. Feitas em PRs separados (#6 e #7) em vez de uma branch única.

**Resultado:** total real de tentativas igual ao previsto pela fórmula.

## Wave 3 — Limpeza final

| Spec | Por que está aqui |
|------|-------------------|
| 07 | Documenta e enxuga as sub-rotinas só depois que as waves 1 e 2 terminaram de criá-las e alterá-las. |
| 10 | `.gitignore` e `Makefile`; o `Makefile` também facilita montar com `--defsym` (wave 2). |

**Resultado:** sem push/pop redundantes; `make DELAY_NS=0` monta com `--defsym`; binários ignorados pelo git (PR #8).

## Fluxo de cada wave

1. Criar a branch `fix/wave-N-…` a partir da `main` atualizada.
2. Implementar as specs na ordem indicada.
3. Rodar os critérios de aceite de cada spec.
4. Marcar as specs como **Resolvido** no arquivo da spec e no [índice](README.md), e atualizar esta página.
5. Abrir o PR e registrar o link na tabela acima.
