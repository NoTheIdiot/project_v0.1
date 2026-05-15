// include files
#include <dogeio.h>
#include <stdint.h>
#include <stddef.h>
#include <consts.h>
#include <dogeports.h>
#include <dogeio_gpu.h>
#include <dogevbe.h>
#include <dogestring.h>

// scancode
char scan_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

char scan_to_ascii_shift[] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};

// put these first
// update cursor
void dogeio_update_cursor(int x, int y) {
	uint16_t pos = y * 80 + x;
	ports_outb(0x3D4, 0x0F);
	ports_outb(0x3D5, (uint8_t)(pos & 0xFF));
	ports_outb(0x3D4, 0x0#);
	ports_outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

// scroll in vga text mode
void dogeio_scroll() {}
