# 11 — Tempo gasto para encontrar a senha

**Status:** Aberto · **Prioridade:** Baixa (didático) · **Categoria:** Feature

## Ideia
Ao final da busca, mostrar quantos milissegundos foram gastos para encontrar a senha, ao lado do total de tentativas. Isso permite comparar o efeito de `DELAY_NS` e `SHOW_SHIFT` (spec 05) e relacionar o tempo com o total previsto pela fórmula (spec 06).

## Comportamento esperado
- O cronômetro **começa** imediatamente antes de `main_loop` (depois da leitura, da validação e de `calc_expected`) e **para** na entrada de `done_found`, antes de qualquer `write` do relatório final. Assim, o tempo de digitação do usuário não entra na medida.
- Relógio: syscall `clock_gettime` (nº 228) com `CLOCK_MONOTONIC` (1), que não sofre ajustes de horário do sistema. Os dois `struct timespec` (16 bytes: `tv_sec`, `tv_nsec`) ficam em `.bss`.
- Cálculo: `ms = (fim.sec − ini.sec) × 1000 + (fim.nsec − ini.nsec) / 1 000 000`, com aritmética de 64 bits com sinal (a diferença de `nsec` pode ser negativa; o resultado total não é). Divisão inteira: frações de ms são truncadas.
- Saída: nova linha logo após a linha de tentativas, reutilizando `print_number`:

  ```
  Tempo para encontrar: 12 ms
  ```

- O tempo inclui as pausas de `DELAY_NS` e as atualizações de tela; isso é intencional (é o tempo que o usuário percebe). O README/cabeçalho deve dizer isso.
- No caminho "não encontrado" (spec 08, código 4) o tempo **não** é impresso. Os códigos de saída da spec 09 não mudam.
- Se `clock_gettime` falhar (`rax` negativo, improvável), a linha é omitida sem alterar o código de saída.

## Fora do escopo
- Resolução em µs/ns ou casas decimais.
- Tentativas por segundo (pode virar outra spec).

## Critérios de aceite
- [ ] Com `make` padrão e entrada `ab`, a saída final traz `Tempo para encontrar: N ms`, com N > 0 e coerente com `time ./bruteforce_full` (N ≤ tempo real total).
- [ ] Com `make -B DELAY_NS=0`, o tempo para `ab` cai de forma visível em relação ao padrão.
- [ ] Entrada de 1 byte (ex.: ` `) imprime `0 ms` ou um valor pequeno, sem lixo nem número negativo.
- [ ] Contagem de tentativas e valor esperado (spec 06) continuam iguais aos da tabela da spec 06.
- [ ] Os códigos de saída 0–4 (spec 09) continuam iguais.
- [ ] Registradores preservados conforme a convenção da spec 07 (o cálculo não pode corromper `r12`/`r13` antes do relatório).

## Notas de implementação
- `r12` (tentativas) e `r13` (tamanho) são usados pelo relatório; fazer o cálculo em `rax`/`rcx`/`rdx` e chamar `print_number` com `rax = ms`.
- A divisão por 1 000 000 pode usar `cqo` + `idiv`, ou `mov rcx, 1000000` + `idiv rcx`.
