%include "minilibasm.inc"

section .text
    global strlen

    strlen:
        push rcx                ; met rcx dans la stack
        xor rcx, rcx            ; met rcx a 0
        jmp .strlen_loop

    .strlen_loop:
        cmp [rdi], byte 0       ; check end of string
        jz .str_end             ; if end jump to str_end
        inc rcx                 ; inc compteur
        inc rdi                 ; inc string
        jmp .strlen_loop        ; loop

    .str_end:
        mov rax, rcx          ; met rcx dans rax
        pop rcx               ; recupere la valeur init de rcx
        ret ;rax              ; return rax
