%include "minilibasm.inc"

section .text
    global memmove

    memmove:
        xor rcx, rcx
        mov rax, rdi
        mov r11, rdx
        jmp .memmove_loop

    .memmove_loop:
        cmp rdx, 0            ; check si fin
        je .memmove_res         ; si oui go res puis copy
        mov r10b, byte [rsi + (rdx - 1)]    ; copy str1 ind
        push r10                ; met r10 dan sla stack
        dec rdx                 ; inc strings et compteur
        jmp .memmove_loop       ; loop

    .memmove_res:
        mov rdx, r11            ; reset compteur
        jmp .memmove_copy

    .memmove_copy:
        cmp rcx, rdx
        je .memmove_end         ; si oui go fin
	    pop r10			        ; recup r10 de la stack
        mov byte [rdi + rcx], r10b    ; copy str1 ind
        inc rcx
        jmp .memmove_copy       ; loop

    .memmove_end:
        ret                     ; return rax