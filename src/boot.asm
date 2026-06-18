[org 0x7c00]
[bits 16]
KERNEL_LOCATION equ 0x1000

xor ax, ax
mov ds, ax
mov es, ax
mov bp, 0x8000
mov sp, bp

mov [BOOT_DISK], dl
mov ah, 2               ; BIOS read function
mov al, 10              ; load 10 sectors, idk why it errs with 20
mov ch, 0               ; cylinder 0
mov cl, 2               ; load Sector 2
mov dh, 0               ; Head 0
mov dl, [BOOT_DISK]     ; Boot drive
mov bx, KERNEL_LOCATION ; load sector at this address
int 0x13

jc DISK_ERROR

; text 80x25 (character matrix) 16-bit color mode
; clears screen
mov ah, 0x0     ; selects 'Set Video Mode' function for BIOS interrupt 0x10
mov al, 0x3     ; selects the desired video mode
int 0x10

cli
lgdt [GDT_Descriptor]

; set bit to enter into protected mode
mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:start_protected_mode

BOOT_DISK: db 0

GDT_Start:
    null_descriptor:
        dd 0
        dd 0
    code_descriptor:
        dw 0xffff
        dw 0
        db 0
        db 0b10011010
        db 0b11001111
        db 0
    data_descriptor:
        dw 0xffff
        dw 0
        db 0
        db 0b10010010
        db 0b11001111
        db 0
GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1
    dd GDT_Start

; these are offset to tell the CPU
; where does the descriptors start given the address of GDT_Start?
CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start

DISK_ERROR:
    mov al, ah
    add al, '0'
    mov ah, 0x0E
    int 0x10

    mov ah, 0x0E
    mov al, 'E'
    int 0x10

    jmp $

[bits 32]
start_protected_mode:
    ; set up stack and other segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    jmp KERNEL_LOCATION


times 510 - ($ - $$) db 0
dw 0xaa55

