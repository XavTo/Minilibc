%include "minilibasm.inc"

section .text
    global strstr

    strstr:
        push r12                ; init registre
        push rcx
        xor rcx, rcx
        xor r12, r12
        cmp [rsi], byte 0       ; check if rsi empty
        je .strstr_found        ; si empty return rdi
        jmp .strstr_loop

    .strstr_loop:
        mov r10b, byte [rdi]    ; r10 car registre temp (b 8bit)
        mov r11b, byte [rsi]    ; r11 car registre temp (b 8bit) 
        cmp	r10b, r11b          ; check if char are same.
	    je	.check		        ; if same go check
        cmp [rdi], byte 0       ; check end of string
        jz .strstr_not_found    ; if \0 return NULL
        inc rdi                 ; inc string
        jmp .strstr_loop        ; loop
    
    .reset_val:
        sub rsi, rcx            ; reset valeur puis on contnue a +1
        sub rdi, rcx
        xor rcx, rcx
        inc rdi
        mov r10b, byte [rdi]    ; r10 car registre temp (b 8bit)
        cmp [rdi], byte 0
        jz .strstr_not_found
        jmp .strstr_loop

    .check:
        mov r10b, byte [rdi]    ; r10 car registre temp (b 8bit)
        mov r11b, byte [rsi]    ; r11 car registre temp (b 8bit) 
        cmp [rsi], byte 0       ; check fin 2eme string donc valid
        jz .strstr_found
        cmp [rdi], byte 0       ; check fin 1ere string donc pas valid
        jz .strstr_not_found
        cmp	r10b, r11b          ; compare char
        jne .reset_val          ; si pas egale on recommence a str1 + 1
        inc rsi                 ; sinon on contnue a check
        inc rdi
        inc rcx
        jmp .check              ; loop
        

    .strstr_found:
        sub rdi, rcx            ; si ca found on return premier occurence str1
        mov rax, rdi
        pop r12                 ; reset valeur
        pop rcx
        ret

    .strstr_not_found:
        pop r12
        pop rcx
        mov rax, 0              ; return NULL
        ret ;rax                ; return rax
