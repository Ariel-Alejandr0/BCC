.intel_syntax noprefix
# bruteforce_full.s - "Adivinha" o texto digitado comparando a FRASE INTEIRA
# (nao caractere por caractere). Sem limite de tamanho: se demorar, demora.
# x86-64 Linux, GNU "as"
#
# Montar e rodar:
#   as bruteforce_full.s -o bruteforce_full.o
#   ld bruteforce_full.o -o bruteforce_full
#   ./bruteforce_full
#
# Velocidade maxima (sem atraso, tela atualizada a cada 2^16 tentativas):
#   as --defsym DELAY_NS=0 bruteforce_full.s -o bruteforce_full.o
# Outros ajustes na montagem: --defsym SHOW_SHIFT=k (atualiza a cada 2^k).
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

paren_close:
    .byte ')'

msg_len:
    .byte 10
    .ascii "Testando tamanho "
    .equ msg_len_len, . - msg_len

msg_invalid:
    .ascii "Erro: caractere fora do alfabeto na posicao "
    .equ msg_invalid_len, . - msg_invalid

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

    # le a entrada
    xor eax, eax
    xor edi, edi
    lea rsi, [rip + input]
    mov edx, MAX_LEN + 1
    syscall
    test rax, rax
    jle exit_prog
    mov r13, rax

    lea rbx, [rip + input]
    cmp byte ptr [rbx + r13 - 1], 10
    jne no_newline
    dec r13
no_newline:
    cmp r13, MAX_LEN
    jbe len_ok
    mov r13, MAX_LEN
len_ok:
    test r13, r13
    jz exit_prog

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

exit_prog:
    mov eax, 60
    xor edi, edi
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

show_cand:                           # limpa a linha e mostra cand (1 write)
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + clrline]
    lea rdx, [r14 + clrline_len]
    syscall
    ret

calc_expected:                       # expected = soma_{k=1}^{n-1} A^k + pos + 1 (0 se estourar)
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

print_len_msg:
    push rax
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
    pop rax
    ret

print_number:                        # imprime o numero em rax no descritor rdi, sem quebra de linha
    push rbx
    push rcx
    push rdx
    push rsi
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
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    ret
