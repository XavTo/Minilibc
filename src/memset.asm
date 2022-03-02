%include "minilibasm.inc"

section .text
    global memset

    memset:
        xor rcx, rcx            ; init compteur a 0
        jmp .memset_loop

    .memset_loop:
        cmp rdx, rcx            ; check end of string
        je .memset_end          ; if end jump to memset_end
        mov [rdi], byte sil     ; set int au pointeur
        inc rcx                 ; inc compteur
        inc rdi                 ; inc string
        jmp .memset_loop        ; loop
    
    .memset_end:
        sub rdi, rcx            ; remet rdi a la valeur initial
        mov rax, rdi            ; return rax
        ret