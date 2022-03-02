%include "minilibasm.inc"

section .text
    global index
    global strchr

    index:
    strchr:
        jmp .index_loop

    .index_loop:
        cmp	[rdi], byte sil	    ; check if char are same. sil = rsi 8 bits (int)
	    jz	.index_end		    ; if same ret found
        cmp [rdi], byte 0       ; check end of string
        jz .index_not_found     ; if \0 return NULL
        inc rdi                 ; inc string
        jmp .index_loop         ; loop

    .index_end:
        mov rax, rdi            ; met rdi dans rax
        ret ;rax                ; return rax

    .index_not_found:
        xor rax, rax            ; met rax a NULL
        ret ;rax                ; return rax
