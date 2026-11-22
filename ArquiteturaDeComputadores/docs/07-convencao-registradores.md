# 07 — Convenção de registradores nas sub-rotinas

**Status:** Resolvido · **Prioridade:** Baixa · **Local:** `print_len_msg`, `print_number`

## Problema
- `print_len_msg` faz `push rax`/`pop rax` sem necessidade.
- `print_number` destrói `rax`, `rdi`, `rcx`, `r11` (syscall) sem documentar; salva `rbx` sem usá-lo.

## Comportamento esperado
Cada sub-rotina tem um comentário com entradas, saídas e registradores destruídos; push/pop apenas do que é realmente preservado.

## Critérios de aceite
- [x] Comentário de contrato em cada sub-rotina.
- [x] Sem push/pop redundantes; programa com mesmo comportamento.
