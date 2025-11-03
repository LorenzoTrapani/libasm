extern __errno_location
section .text
    global ft_read

ft_read:
    mov rax, 0
    syscall
    cmp rax, 0
    jl .error
    ret

.error:
    neg rax
    mov rdi, rax
    call __errno_location wrt ..plt
    mov [rax], rdi ; impostiamo nell'indirizzo di memoria di rax il valore dell'erno di rdi
    mov rax, -1 ; ritorniamo -1 x errore write
    ret

