%include "minilibasm.inc"

section .text
    global strchr

    strchr:
        jmp .strchr_loop

    .strchr_loop:
        cmp	[rdi], byte sil	    ; check if char are same. sil = rsi 8 bits (int)
	    jz	.strchr_end		    ; if same ret found
        cmp [rdi], byte 0       ; check end of string
        jz .strchr_not_found    ; if \0 return NULL
        inc rdi                 ; inc string
        jmp .strchr_loop        ; loop

    .strchr_end:
        mov rax, rdi            ; met rdi dans rax
        ret ;rax                ; return rax

    .strchr_not_found:
        xor rax, rax            ; met rax a NULL
        ret ;rax                ; return rax
