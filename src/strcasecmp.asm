bits 64

section .text
    global strcasecmp

    strcasecmp:
        jmp .strcasecmp_loop

    .strcasecmp_loop:
        mov r10b, byte [rdi]    ; r10 car registre temp (b 8bit)
        mov r11b, byte [rsi]    ; r10 car registre temp (b 8bit)
        cmp r10b, r11b          ; compare les registre
        jl .check_upper
        cmp r10b, r11b          ; compare les registre
        jg .check_lower
        cmp r10b, 0
        jz .same                ; jmp \0
        inc rsi                 ; inc string
        inc rdi                 ; inc string
        jmp .strcasecmp_loop        ; loop

    .same:
        mov rax, 0              ; if same &s \0 ret 0
        ret

    .noteq:
        sub r10b, r11b        ; r10b = rdi[i] - rsi[i]
        movsx rax, r10b       ; rax = r10b (movsx car rax > r10b)
        ret

    .r_inc:
        inc rsi                 ; inc string
        inc rdi                 ; inc string
        jmp .strcasecmp_loop

    .check_upper:
        cmp r10b, 'A'
        jl .noteq
        cmp r10b, 'Z'
        jg .noteq
        add r10b, 32
        cmp r10b, r11b
        je .r_inc
        sub r10b, 32
        jmp .noteq


    .check_lower:
        cmp r11b, 'A'
        jl .noteq
        cmp r11b, 'Z'
        jg .noteq
        add r11b, 32
        cmp r11b, r10b
        je .r_inc
        sub r11b, 32
        jmp .noteq
