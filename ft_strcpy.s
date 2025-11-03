section .text
    global ft_strcpy

ft_strcpy:
    mov rax, rdi; salva dst per il return

.loop:
    mov bl, byte [rsi] ;src
    mov byte [rdi], bl ;dest
    test bl, bl
    je .finish
    inc rsi
    inc rdi
    jmp .loop

.finish:
    ret