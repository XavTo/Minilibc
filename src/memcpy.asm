%include "minilibasm.inc"

section .text
    global memcpy

    memcpy:
        push rcx                ; init compteur
        xor rcx, rcx
        mov rax, rdi            ; save rdi for return
        jmp .memcpy_loop

    .memcpy_loop:
        cmp rcx, rdx            ; check si fin
        je .memcpy_end          ; si oui go fin
        mov r10b, byte [rsi]    ; copy str1 ind
        mov byte [rdi], r10b    ; vers str2 ind en passant par un registre temp (b 8bit)
        inc rcx                 ; inc strings et compteur
        inc rdi
        inc rsi
        jmp .memcpy_loop        ; loop

    .memcpy_end:
        pop rcx
        ret                     ; return ret