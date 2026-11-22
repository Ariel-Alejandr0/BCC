# 02 — Alfabeto inclui bytes não imprimíveis

**Status:** Resolvido · **Prioridade:** Alta · **Local:** `.equ ALPHA_MAX` (linha 21)

## Problema
O alfabeto vai de 32 a 255. Inclui DEL (127), controles C1 (128–159) e bytes que isolados não são UTF-8 válido (160–255). A exibição do candidato corrompe o terminal, e caracteres acentuados em UTF-8 (2 bytes) tornam a busca confusa.

## Comportamento esperado
`ALPHA_MAX = 126` (ASCII imprimível, 95 símbolos). Busca cai de 224ⁿ para 95ⁿ combinações por tamanho.

## Decisões em aberto
- Suportar UTF-8? Se sim, seria um alfabeto de *code points*, mudança grande — tratar como spec separada.

## Critérios de aceite
- [x] Nenhum byte fora de 32–126 é escrito no terminal.
- [x] Atualizar o comentário do cabeçalho ("Alfabeto usado").
- [x] Combinar com [01](01-validacao-alfabeto.md): entrada com acento é rejeitada com mensagem clara.
