[org 0x7C00]
bits 16

start:
    ; BIOS gives boot drive in DL
    mov [BOOT_DRIVE], dl

    ; set segments
    xor ax, ax
    mov ds, ax
    mov es, ax

    ; destination buffer = 0000:7E00
    mov bx, 0x7E00

    ; INT 13h / AH=02h = read sectors
    mov ah, 0x02      ; read sectors
    mov al, 0x01      ; read 1 sector

    mov ch, 0x00      ; cylinder 0
    mov cl, 0x02      ; sector 2 (starts at 1!)
    mov dh, 0x00      ; head 0

    mov dl, [BOOT_DRIVE]

    int 0x13

    jc disk_error     ; CF=1 means error

    mov si, 0x7e00
    mov al, [si]
    mov ah, 0x0e
    int 0x10

    ; success: loop forever
    jmp $

disk_error:
    mov ah, 0x0E
    mov al, 'E'
    int 0x10
    jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xAA55
times 512 db 'B'
