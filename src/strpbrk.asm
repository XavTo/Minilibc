%include "minilibasm.inc"

section .text
    global strpbrk

    strpbrk:
        push rcx
        xor rcx, rcx
        jmp .strpbrk_loop

    .strpbrk_loop:
        mov r10b, byte [rdi]        ; r10 car registre temp (b 8bit)
        cmp [rdi], byte 0           ; check end of string
        jz .strpbrk_not_found       ; if \0 return NULL
        jmp .check
    
    .reset:
        sub rsi, rcx                ; remet string 2 a initial
        xor rcx, rcx                ; reset compteur
        inc rdi                     ; augment str1 + 1
        jmp .strpbrk_loop


    .check:
        mov r11b, byte [rsi]        ; r10 car registre temp (b 8bit)
        cmp [rsi], byte 0           ; check end of string
        jz .reset                   ; if \0 return NULL
        cmp	r10b, r11b              ; compare 2 char
        je .strpbrk_found           ; si trouver go found
        inc rsi                     ; inc 2eme string et compteur
        inc rcx
        jmp .check                  ; loop
        

    .strpbrk_found:
        pop rcx                     
        mov rax, rdi                ; met rax a premier char trouvé
        ret                         ; return rax

    .strpbrk_not_found:
        pop rcx
        mov rax, 0                  ; met rax a null
        ret ;rax                    ; return rax