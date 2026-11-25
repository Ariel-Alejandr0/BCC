.intel_syntax noprefix
# bruteforce_full.asm - "Adivinha" o texto digitado comparando a FRASE INTEIRA
# (nao caractere por caractere). Sem limite de tamanho: se demorar, demora.
# x86-64 Linux, GNU "as"
#
# Montar e rodar:
#   make run                 (ou: as bruteforce_full.asm -o bruteforce_full.o
#                                 ld bruteforce_full.o -o bruteforce_full
#                                 ./bruteforce_full)
#
# Velocidade maxima (sem atraso, tela atualizada a cada 2^16 tentativas):
#   make DELAY_NS=0          (ou: as --defsym DELAY_NS=0 bruteforce_full.asm ...)
# Outros ajustes na montagem: --defsym SHOW_SHIFT=k (atualiza a cada 2^k).
# Codigos de saida (spec 09): 0 encontrado, 1 entrada vazia/EOF,
# 2 erro de leitura, 3 entrada invalida, 4 nao encontrado.
#
# Algoritmo: gera candidatos em ordem crescente de tamanho (1, 2, 3, ...).
# Para cada tamanho, percorre todas as combinacoes possiveis (como um
# odometro, incrementando o ultimo caractere e "vaiando" pro anterior
# quando estoura) ate comparar a string inteira com o que foi digitado.
# So avanca pro proximo tamanho depois de esgotar TODAS as combinacoes
# do tamanho atual. Alfabeto usado: ASCII imprimivel (bytes 32 a 126).
#
# Numero de tentativas (spec 06): com alfabeto de tamanho A e entrada de n
# caracteres,
#   T = soma_{k=1}^{n-1} A^k + pos(entrada) + 1
# onde pos e' a entrada lida como numero na base A (digito = byte - ALPHA_MIN).
# O programa calcula T antes da busca e mostra ao lado do contador real
# (se T nao couber em 64 bits, mostra "nao cabe em 64 bits").
#
# Tempo (spec 11): clock_gettime(CLOCK_MONOTONIC) logo antes de main_loop e
# na entrada de done_found; mostra "Tempo para encontrar: N ms". A medida
# inclui as pausas de DELAY_NS e as atualizacoes de tela (tempo percebido),
# mas nao a digitacao. Nao e' impresso no caminho "nao encontrado".

.ifndef DELAY_NS
.equ DELAY_NS, 1000000     # pausa por atualizacao de tela (1 ms); --defsym DELAY_NS=0 desliga
.endif
.ifndef SHOW_SHIFT          # tela atualizada a cada 2^SHOW_SHIFT tentativas (spec 05)
.if DELAY_NS > 0
.equ SHOW_SHIFT, 0          # com atraso: mostra toda tentativa (animacao visivel)
.else
.equ SHOW_SHIFT, 16         # sem atraso: so de vez em quando, o resto e' CPU pura
.endif
.endif
.equ SHOW_MASK, (1 << SHOW_SHIFT) - 1
.equ MAX_LEN, 255
.equ DRAIN_LEN, 64           # buffer para descartar o excedente da linha
.equ ALPHA_MIN, 32
.equ ALPHA_MAX, 126         # ASCII imprimivel (95 simbolos); ver docs/02
.equ ALPHA_SIZE, ALPHA_MAX - ALPHA_MIN + 1

.section .data
prompt:
    .ascii "Digite uma frase ou palavra (ate 255 caracteres): "
    .equ prompt_len, . - prompt

msg_found:
    .byte 10
    .ascii "Encontrado: "
    .equ msg_found_len, . - msg_found

msg_tries:
    .byte 10
    .ascii "Tentativas totais: "
    .equ msg_tries_len, . - msg_tries

msg_expected:
    .ascii " (esperado pela formula: "
    .equ msg_expected_len, . - msg_expected

msg_overflow:
    .ascii "nao cabe em 64 bits"
    .equ msg_overflow_len, . - msg_overflow

msg_time:
    .ascii "Tempo para encontrar: "
    .equ msg_time_len, . - msg_time

msg_ms:
    .ascii " ms\n"
    .equ msg_ms_len, . - msg_ms

paren_close:
    .byte ')'

msg_len:
    .byte 10
    .ascii "Testando tamanho "
    .equ msg_len_len, . - msg_len

msg_invalid:
    .ascii "Erro: caractere fora do alfabeto na posicao "
    .equ msg_invalid_len, . - msg_invalid

msg_trunc:
    .ascii "Aviso: entrada maior que 255 caracteres; usando apenas os 255 primeiros.\n"
    .equ msg_trunc_len, . - msg_trunc

msg_notfound:
    .ascii "\nErro: todas as combinacoes ate o tamanho da entrada foram testadas sem sucesso.\n"
    .equ msg_notfound_len, . - msg_notfound

nl:
    .byte 10

# clrline e cand ficam colados: um unico write(clrline, clrline_len + clen)
# limpa a linha e mostra o candidato (spec 05)
clrline:
    .byte 0x1b, '[', '2', 'K', 13   # ESC [ 2K <CR>  (limpa a linha e volta ao inicio)
    .equ clrline_len, . - clrline
cand:
    .skip MAX_LEN + 1

ts:
    .quad 0, DELAY_NS

.section .bss
input:
    .skip MAX_LEN + 1
numbuf:
    .skip 24
expected:
    .skip 8                          # T pela formula; 0 = estourou 64 bits
drainbuf:
    .skip DRAIN_LEN
    .balign 8
t_start:
    .skip 16                         # struct timespec (tv_sec, tv_nsec), spec 11
t_end:
    .skip 16
t_fail:
    .skip 1                          # 1 = algum clock_gettime falhou

.section .text
.global _start

_start:
    cld

    # imprime o prompt
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + prompt]
    mov edx, prompt_len
    syscall

    # le a entrada (spec 03): le em loop ate '\n' ou EOF, tolerando leituras
    # parciais (pipe). Guarda no maximo MAX_LEN bytes; o excedente da linha e
    # lido e descartado para nao sobrar no stdin (e ser executado pelo shell).
    xor r13, r13                    # r13 = bytes validos em input
    xor r8, r8                      # r8  = 1 se a linha foi truncada
    lea rbx, [rip + input]
read_loop:
    cmp r13, MAX_LEN
    jae drain_rest                  # buffer cheio sem '\n': descarta o resto
    xor eax, eax
    xor edi, edi
    lea rsi, [rbx + r13]
    mov edx, MAX_LEN
    sub rdx, r13
    push r8
    syscall
    pop r8
    test rax, rax
    js read_error
    jz read_done                    # EOF
    mov rcx, r13
    add r13, rax
scan_new:
    cmp rcx, r13
    jae read_loop
    cmp byte ptr [rbx + rcx], 10
    je got_newline
    inc rcx
    jmp scan_new
got_newline:
    mov r13, rcx                    # ignora o '\n' e o que vier depois dele
    jmp read_done

drain_rest:
    xor eax, eax
    xor edi, edi
    lea rsi, [rip + drainbuf]
    mov edx, DRAIN_LEN
    push r8
    syscall
    pop r8
    test rax, rax
    jle drain_done                  # EOF ou erro: nada mais a descartar
    lea rsi, [rip + drainbuf]
    xor ecx, ecx
drain_scan:
    cmp rcx, rax
    jae drain_rest
    cmp byte ptr [rsi + rcx], 10
    je drain_done
    mov r8, 1                       # havia caractere alem do limite
    inc rcx
    jmp drain_scan
drain_done:
    test r8, r8
    jz read_done
    mov eax, 1                      # avisa no stderr que a frase foi cortada
    mov edi, 2
    lea rsi, [rip + msg_trunc]
    mov edx, msg_trunc_len
    syscall

read_done:
    test r13, r13
    jz empty_input

    # valida: todo byte da entrada precisa estar no alfabeto, senao a busca
    # nunca terminaria (spec 01)
    xor r15, r15                    # r15 = indice atual (rbx = input)
validate_loop:
    cmp r15, r13
    jae validate_ok
    mov al, [rbx + r15]
    cmp al, ALPHA_MIN
    jb invalid_input
    cmp al, ALPHA_MAX
    ja invalid_input
    inc r15
    jmp validate_loop
validate_ok:
    call calc_expected

    mov r14, 1                      # r14 = tamanho do candidato atual (clen)
    xor r12, r12                    # r12 = total de tentativas
    lea rbx, [rip + cand]
    mov byte ptr [rbx], ALPHA_MIN    # candidato inicial: 1 byte = ALPHA_MIN

    call print_len_msg

    # spec 11: cronometro comeca aqui (depois da leitura/validacao/calc_expected)
    mov eax, 228                     # clock_gettime
    mov edi, 1                       # CLOCK_MONOTONIC
    lea rsi, [rip + t_start]
    syscall
    test rax, rax
    jns main_loop
    mov byte ptr [rip + t_fail], 1

main_loop:
    inc r12
.if SHOW_MASK > 0
    test r12, SHOW_MASK              # so atualiza a tela a cada 2^SHOW_SHIFT
    jnz skip_show
.endif
    call show_cand

.if DELAY_NS > 0
    mov eax, 35
    lea rdi, [rip + ts]
    xor esi, esi
    syscall
.endif
skip_show:

    cmp r14, r13                     # so pode bater se o tamanho for igual
    jne no_match

    lea rsi, [rip + cand]
    lea rdi, [rip + input]
    mov rcx, r13
    repe cmpsb
    je done_found

no_match:
    mov r15, r14
    dec r15                          # r15 = ultimo indice do candidato
    lea rbx, [rip + cand]

inc_loop:
    cmp r15, -1
    je grow_length                   # estourou todas as posicoes: aumenta o tamanho
    mov al, [rbx + r15]
    cmp al, ALPHA_MAX
    je wrap_this
    inc al
    mov [rbx + r15], al
    jmp main_loop
wrap_this:
    mov byte ptr [rbx + r15], ALPHA_MIN
    dec r15
    jmp inc_loop

grow_length:
    # spec 08: nunca passa do tamanho da entrada (<= MAX_LEN), evitando
    # escrever alem de cand e testar tamanhos que nao podem bater
    cmp r14, r13
    jae not_found
    inc r14
    xor r15, r15
reset_loop:
    cmp r15, r14
    jae len_grown_done
    mov byte ptr [rbx + r15], ALPHA_MIN
    inc r15
    jmp reset_loop
len_grown_done:
    call print_len_msg
    jmp main_loop

done_found:
    # spec 11: para o cronometro antes de qualquer write do relatorio
    mov eax, 228
    mov edi, 1
    lea rsi, [rip + t_end]
    syscall
    test rax, rax
    jns df_report
    mov byte ptr [rip + t_fail], 1
df_report:
    call show_cand                   # garante que o candidato final aparece
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + msg_found]
    mov edx, msg_found_len
    syscall

    mov eax, 1
    mov edi, 1
    lea rsi, [rip + input]
    mov rdx, r13
    syscall

    mov eax, 1
    mov edi, 1
    lea rsi, [rip + msg_tries]
    mov edx, msg_tries_len
    syscall

    mov rax, r12
    call print_number

    mov eax, 1
    mov edi, 1
    lea rsi, [rip + msg_expected]
    mov edx, msg_expected_len
    syscall

    mov rax, [rip + expected]
    test rax, rax
    jz exp_overflow
    call print_number                # edi = 1 (do write acima)
    jmp exp_close
exp_overflow:
    mov eax, 1
    lea rsi, [rip + msg_overflow]
    mov edx, msg_overflow_len
    syscall
exp_close:
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + paren_close]
    mov edx, 1
    syscall

    mov eax, 1
    mov edi, 1
    lea rsi, [rip + nl]
    mov edx, 1
    syscall

    # spec 11: ms = (fim.sec - ini.sec)*1000 + (fim.nsec - ini.nsec)/1e6
    cmp byte ptr [rip + t_fail], 0
    jne exit_prog                    # relogio falhou: omite a linha
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + msg_time]
    mov edx, msg_time_len
    syscall
    mov rax, [rip + t_end]
    sub rax, [rip + t_start]
    imul rax, rax, 1000              # rax = diferenca de segundos em ms
    mov rcx, rax
    mov rax, [rip + t_end + 8]
    sub rax, [rip + t_start + 8]     # pode ser negativo
    cqo
    mov r8, 1000000
    idiv r8                          # trunca em direcao a zero
    add rax, rcx                     # total >= 0 (relogio monotonico)
    mov edi, 1
    call print_number
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + msg_ms]
    mov edx, msg_ms_len
    syscall

exit_prog:
    mov eax, 60
    xor edi, edi                     # codigo 0 = encontrado
    syscall

empty_input:
    mov eax, 60
    mov edi, 1                       # codigo 1 = entrada vazia/EOF (spec 09)
    syscall

not_found:                           # spec 08: tamanhos esgotados sem achar
    mov eax, 1
    mov edi, 2
    lea rsi, [rip + msg_notfound]
    mov edx, msg_notfound_len
    syscall
    mov eax, 60
    mov edi, 4                       # codigo 4 = nao encontrado (spec 09)
    syscall

read_error:
    mov eax, 60
    mov edi, 2                       # codigo 2 = erro de leitura (spec 09)
    syscall

invalid_input:                       # r15 = indice do byte invalido
    mov eax, 1
    mov edi, 2
    lea rsi, [rip + msg_invalid]
    mov edx, msg_invalid_len
    syscall

    lea rax, [r15 + 1]               # posicao comecando em 1
    mov edi, 2
    call print_number

    mov eax, 1
    mov edi, 2
    lea rsi, [rip + nl]
    mov edx, 1
    syscall

    mov eax, 60
    mov edi, 3                       # codigo 3 = entrada invalida (spec 09)
    syscall

# ---- sub-rotinas ----
# Contrato (spec 07): entradas, saidas e registradores destruidos de cada uma.
# Registradores de estado do laco principal (rbx, r12-r15) nunca sao destruidos.

# show_cand: limpa a linha e mostra cand com um unico write.
#   entrada: r14 = tamanho do candidato
#   saida:   nenhuma
#   destroi: rax, rdi, rsi, rdx, rcx, r11
show_cand:
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + clrline]
    lea rdx, [r14 + clrline_len]
    syscall
    ret

# calc_expected: expected = soma_{k=1}^{n-1} A^k + pos + 1 (0 se estourar 64 bits).
#   entrada: r13 = tamanho da entrada, input = bytes validados
#   saida:   [expected]
#   destroi: rax, rcx, rdx, r8, r9, r10 (preserva rbx)
calc_expected:
    push rbx
    mov ecx, ALPHA_SIZE
    xor r8, r8                       # r8 = soma das potencias
    mov r9, 1                        # r9 = A^k
    mov r10, 1                       # r10 = k
ce_pow:
    cmp r10, r13
    jae ce_pos
    mov rax, r9
    mul rcx
    jc ce_over                       # CF=1: parte alta de rdx:rax nao e' zero
    mov r9, rax
    add r8, rax
    jc ce_over
    inc r10
    jmp ce_pow
ce_pos:                              # Horner: pos = pos*A + digito
    lea rbx, [rip + input]
    xor r9, r9
    xor r10, r10
ce_digit:
    cmp r10, r13
    jae ce_sum
    mov rax, r9
    mul rcx
    jc ce_over
    movzx edx, byte ptr [rbx + r10]
    sub edx, ALPHA_MIN
    add rax, rdx
    jc ce_over
    mov r9, rax
    inc r10
    jmp ce_digit
ce_sum:
    add r8, r9
    jc ce_over
    add r8, 1
    jc ce_over
    jmp ce_store
ce_over:
    xor r8, r8
ce_store:
    mov [rip + expected], r8
    pop rbx
    ret

# print_len_msg: imprime "\nTestando tamanho <r14>\n" no stdout.
#   entrada: r14 = tamanho atual
#   saida:   nenhuma
#   destroi: rax, rdi, rsi, rdx, rcx, r11
print_len_msg:
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + msg_len]
    mov edx, msg_len_len
    syscall
    mov rax, r14
    call print_number
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + nl]
    mov edx, 1
    syscall
    ret

# print_number: imprime rax em decimal no descritor rdi, sem quebra de linha.
#   entrada: rax = numero, rdi = descritor
#   saida:   nenhuma (rdi continua igual)
#   destroi: rax, rcx, rdx, rsi, r11
print_number:
    lea rsi, [rip + numbuf]
    add rsi, 23
    mov rcx, 10
pn_digit:
    xor edx, edx
    div rcx
    add dl, '0'
    dec rsi
    mov [rsi], dl
    test rax, rax
    jnz pn_digit
    lea rdx, [rip + numbuf]
    add rdx, 23
    sub rdx, rsi
    mov eax, 1                       # rdi = descritor, definido por quem chama
    syscall
    ret
