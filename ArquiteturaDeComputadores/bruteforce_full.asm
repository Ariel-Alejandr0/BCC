.intel_syntax noprefix
# bruteforce_full.asm - "Adivinha" o texto digitado comparando a FRASE INTEIRA
# (nao caractere por caractere). Sem limite de tamanho: se demorar, demora.
# x86-64 Linux, GNU "as"
#
# Montar e rodar:
#   as bruteforce_full.asm -o bruteforce_full.o
#   ld bruteforce_full.o -o bruteforce_full
#   ./bruteforce_full
#
# Codigos de saida (spec 09): 0 encontrado, 1 entrada vazia/EOF,
# 2 erro de leitura, 3 entrada invalida, 4 nao encontrado.
#
# Algoritmo: gera candidatos em ordem crescente de tamanho (1, 2, 3, ...).
# Para cada tamanho, percorre todas as combinacoes possiveis (como um
# odometro, incrementando o ultimo caractere e "vaiando" pro anterior
# quando estoura) ate comparar a string inteira com o que foi digitado.
# So avanca pro proximo tamanho depois de esgotar TODAS as combinacoes
# do tamanho atual. Alfabeto usado: ASCII imprimivel (bytes 32 a 126).

.equ DELAY_NS, 1000000     # pausa entre tentativas (1 ms). Use 0 para maxima velocidade
.equ MAX_LEN, 255
.equ DRAIN_LEN, 64           # buffer para descartar o excedente da linha
.equ ALPHA_MIN, 32
.equ ALPHA_MAX, 126         # ASCII imprimivel (95 simbolos); ver docs/02

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

msg_trunc:
    .ascii "Aviso: entrada maior que 255 caracteres; usando apenas os 255 primeiros.\n"
    .equ msg_trunc_len, . - msg_trunc

msg_notfound:
    .ascii "\nErro: todas as combinacoes ate o tamanho da entrada foram testadas sem sucesso.\n"
    .equ msg_notfound_len, . - msg_notfound

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
drainbuf:
    .skip DRAIN_LEN

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
