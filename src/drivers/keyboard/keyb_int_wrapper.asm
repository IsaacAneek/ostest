global isr_keyb_wrapper
extern ISR_keyboard_handler_01
isr_keyb_wrapper:
    pusha
    call ISR_keyboard_handler_01
    popa
    iret