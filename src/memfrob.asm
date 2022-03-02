%include "minilibasm.inc"

section .text
    global memfrob

    memfrob:
        push rcx                ; init compteur
        xor rcx, rcx
        mov rax, rdi            ; save rdi for return
        jmp .memfrob_loop

    .memfrob_loop:
        cmp rcx, rsi            ; check si fin
        je .memfrob_end          ; si oui go fin
        xor byte [rdi + rcx], 42    ; copy str1 ind
        inc rcx                 ; inc strings et compteur
        jmp .memfrob_loop        ; loop

    .memfrob_end:
        pop rcx
        ret                     ; return ret