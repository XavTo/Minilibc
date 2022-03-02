%include "minilibasm.inc"

section .text
    global rindex
    global strrchr

    rindex:
    strrchr:
        xor rax, rax                ; met rax a null de base
        xor rcx, rcx

    .rindex_len:                    ; get len of str1
        mov r10b, byte [rdi + rcx]	; r10b pour registre temporaire
        cmp r10b, 0
        jz .rindex_loop             ; quand \0 jump loop
        inc rcx
        jmp .rindex_len

    .rindex_loop:
        mov r10b, byte [rdi + rcx]
        cmp r10b, sil               ; compare rdi avec rsi (8bits)
        je .rindex_end              ; si egal go end
        cmp rcx, 0		
        je .rindex_not_found		
        dec rcx
        jmp .rindex_loop

    .rindex_end:
        mov rax, rdi		        ; set return value to str
        add rax, rcx		        ; add index to return value
        ret ;rax                    ; return rax

    .rindex_not_found:
        ret
