section .text

global inb:
inb:
    mov dx, [esp + 4]
    in al, dx 
    ret

global outb
outb:
    mov dx, [esp + 4] 
    mov al, [esp + 8] 
    ; esp is ret ad4dr 
    ; esp + 4 is value?
    out dx, al
    ret

