%include "minilibasm.inc"

section .text
    global strcspn

    strcspn:
        push rcx                ; push compteur
        xor rcx, rcx            ; compteur = 0
        xor rax, rax            ; return = 0
        jmp .strcspn_loop        ; go loop

    .strcspn_loop:
        mov r10b, byte [rdi]    ; r10 car registre temp (b 8bit)
        cmp [rdi], byte 0       ; check end of string
        jz .strcspn_end          ; if \0 return NULL
        jmp .check              ; sinon go check
    
    .reset:
        sub rsi, rcx            ; remet str2 a 0
        xor rcx, rcx            ; remet compteur a 0
        inc rdi                 ; prochain char
        inc rax                 ; inc la valeur de return
        jmp .strcspn_loop        ; go loop


    .check:
        mov r11b, byte [rsi]    ; r11 car registre temp (b 8bit)
        cmp [rsi], byte 0       ; check end of string
        jz .reset               ; if \0 reset
        cmp	r10b, r11b          ; compare 2 char
        je .strcspn_end         ; return null
        inc rsi                 ; inc seconde string
        inc rcx                 ; inc compteur
        jmp .check              ; loop check
        

    .strcspn_end:
        pop rcx                 ; recup compteur
        ret                     ; return rax