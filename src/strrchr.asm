%include "minilibasm.inc"

global strrchr
extern rindex

section .text

    strrchr:
        xor rax, rax                ; met rax a null de base
        xor rcx, rcx

    .strrchr_len:                   ; get len of str1
        mov r10b, byte [rdi + rcx]	; r10b pour registre temporaire
        cmp r10b, 0
        jz .strrchr_loop            ; quand \0 jump loop
        inc rcx
        jmp .strrchr_len

    .strrchr_loop:
        mov r10b, byte [rdi + rcx]
        cmp r10b, sil               ; compare rdi avec rsi (8bits)
        je .strrchr_end             ; si egal go end	
        cmp rcx, 0		            ; check if rcx null (si on le fait avant marche pas
        je .strrchr_not_found	
        dec rcx
        jmp .strrchr_loop

    .strrchr_end:
        mov rax, rdi		        ; set return value to str
        add rax, rcx		        ; add index to return value
        ret ;rax                    ; return rax

    .strrchr_not_found:
        xor rax, rax                ; met rax a null de base
        ret
