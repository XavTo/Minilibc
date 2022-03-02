bits 64

section .text
    global strncmp

    strncmp:
        xor rcx, rcx
        jmp .strncmp_loop

    .strncmp_loop:
        mov r10b, byte [rdi]    ; r10 car registre temp (b 8bit)
        mov r11b, byte [rsi]    ; r10 car registre temp (b 8bit)
        cmp r10b, r11b          ; compare les registre
        jne .noteq
        cmp r10b, 0
        jz .same                ; jmp \0
        inc rsi                 ; inc string
        inc rdi                 ; inc string
        inc rcx
        cmp rcx, rdx
        je .noteq
        jmp .strncmp_loop        ; loop

    .same:
        mov rax, 0              ; if same &s \0 ret 0
        ret

    .noteq:
        sub r10b, r11b        ; r10b = rdi[i] - rsi[i]
        movsx rax, r10b       ; rax = r10b (movsx car rax > r10b)
        ret