#ifndef DOGEIO_GPU_H
#define DOGEIO_GPU_H

void dogeio_clear_screen_vbe();
void dogeio_scroll_vbe();
void dogeio_init_vbe_mbi();
void dogeio_init_vbe();
void dogeio_putchar_vbe(char c);
void dogeio_print_vbe(char* string);
void dogeio_println_vbe(char* string);
void dogeio_input_vbe(char* buffer, size_t length);

#endif