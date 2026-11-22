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
# Algoritmo: gera candidatos em ordem crescente de tamanho (1, 2, 3, ...).
# Para cada tamanho, percorre todas as combinacoes possiveis (como um
# odometro, incrementando o ultimo caractere e "vaiando" pro anterior
# quando estoura) ate comparar a string inteira com o que foi digitado.
# So avanca pro proximo tamanho depois de esgotar TODAS as combinacoes
# do tamanho atual. Alfabeto usado: bytes 32 a 255.

.equ DELAY_NS, 1000000     # pausa entre tentativas (1 ms). Use 0 para maxima velocidade
.equ MAX_LEN, 255
.equ ALPHA_MIN, 32
.equ ALPHA_MAX, 255

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

msg_len:
    .byte 10
    .ascii "Testando tamanho "
    .equ msg_len_len, . - msg_len

msg_invalid:
    .ascii "Erro: caractere fora do alfabeto na posicao "
    .equ msg_invalid_len, . - msg_invalid

nl:
    .byte 10

clrline:
    .byte 0x1b, '[', '2', 'K', 13   # ESC [ 2K <CR>  (limpa a linha e volta ao inicio)
    .equ clrline_len, . - clrline

ts:
    .quad 0, DELAY_NS

.section .bss
input:
    .skip MAX_LEN + 1
cand:
    .skip MAX_LEN + 1
numbuf:
    .skip 24

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

    mov r14, 1                      # r14 = tamanho do candidato atual (clen)
    xor r12, r12                    # r12 = total de tentativas
    lea rbx, [rip + cand]
    mov byte ptr [rbx], ALPHA_MIN    # candidato inicial: 1 byte = ALPHA_MIN

    call print_len_msg

main_loop:
    # limpa a linha e mostra o candidato atual
    mov eax, 1
    mov edi, 1
    lea rsi, [rip + clrline]
    mov edx, clrline_len
    syscall

    mov eax, 1
    mov edi, 1
    lea rsi, [rip + cand]
    mov rdx, r14
    syscall

    inc r12

.if DELAY_NS > 0
    mov eax, 35
    lea rdi, [rip + ts]
    xor esi, esi
    syscall
.endif

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
