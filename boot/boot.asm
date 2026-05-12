; multiboot constants
MB_MAGIC            equ 0x1BADB002
MB_PAGE_ALIGN       equ 1 << 0
MB_RAM_INFO         equ 1 << 1
MB_VRAM_MODE        equ 1 << 2
MB_HEADER_FLAGS     equ MB_PAGE_ALIGN | MB_RAM_INFO
MB_CHECK            equ -(MB_MAGIC + MB_HEADER_FLAGS)

; multiboot section so it works
section .multiboot
align 4
    dd MB_MAGIC
    dd MB_HEADER_FLAGS
    dd MB_CHECK
    dd 1                    ; graphics mode (1 for VBE, 0 for VGA text)
    dd 1024                 ; 1024 width
    dd 768                  ; 768 height
    dd 32                   ; depth


section .text               ; start section
global _start               ; global _start for usability
extern windoge_os_main      ; extern the c files

; enter 32 bit mode to access registers like esp ebx eax etc
_start:
    cli
    mov esp, stack_top      ; set up the stack
    push ebx                ; push multiboot infp
    push eax                ; same thing
    call windoge_os_main    ; start WindogeOS

.halt:                      ; if boot fails
    hlt                     ; halt CPU
    jmp .halt               ; jump back to .halt to loop forever

section .bss                ; bss section
align 16                    ; align 16 bytes or bits
stack_bottom:               ; at the bottom of the stack
    resb 16384              ; reserve 16KB for the stack
stack_top:                  ; at the top of the stack, also known as NOTHING