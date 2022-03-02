%include "minilibasm.inc"

section .text
    global ffs

    ffs:
        xor rax, rax        ; put rax at 0
        cmp rdi, 0          ; check si arg == 0
        je .ffs_end         ; si oui return 0
        mov rax, 1          ; met rax a 1 car base 1
        mov r10, 1          ; init compteur a 1
        mov r11, rdi
        jmp .ffs_loop
        
    .ffs_inc:
        inc rax             ; inc ret
        imul r10, 2         ; compteur *2
        mov r11, rdi        ; save rdi dans registre temp r11
        jmp .ffs_loop       

    .ffs_loop:
        and r11, r10        ; op binaire and sur r11(rdi) et r10
        cmp r11, 0          ; check if r11(rdi) = 0
        je .ffs_inc         ; si oui on continue car bit = 0
        jmp .ffs_end        ; sinon fin

    .ffs_end:
        ret
