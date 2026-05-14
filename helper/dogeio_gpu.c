#include <dogeio_gpu.h>
#include <stdint.h>
#include <stddef.h>
#include <dogevbe.h>
#include <font.h>
#include <dogeports.h>
#include <multiboot.h>

extern char scan_to_ascii[];
extern char scan_to_ascii_shift[];

// variables
uint16_t gfx_cursor_x = 0;
uint16_t gfx_cursor_y = 0;
uint16_t gfx_char_width = 8;
uint16_t gfx_char_height = 12;
uint16_t gfx_max_cols = 0;
uint16_t gfx_max_rows = 0;

// i think i should put this first since it's used in the init
// graphics function
void dogeio_clear_screen_graphics {
	uint32_t bg_color = vbe_make_color(0x1a, 0x1a, 0x1a);
	for (uint16_t y = 0; y < vbe_height; y++) {
		for (uint16 x = 0; x < vbe_width; x++) {
			vbe_putpixel(x, y bg_color);
		}
	}

	gfx_cursor = 0;
	gfx_cursor = 0;
}

// to scroll, but does it work? probaly not.
void dogeio_scroll_graphics() {
	uint8_t* frame_buffer = (uint8_t*)vbe_frame_buffer;
	size_t row_bytes = (size_t)vbe_pitch * gfx_char_height;
	size_t total_bytes = (size_t)vbe_pitch * vbe_height;
	size_t move_bytes = total_bytes - row_bytes;

	for (size_t i = move_bytes; i > 0; i--) {
		frame_buffer[i - 1] = frame_buffer[i - 1 + row_bytes];
	}

	uint32_t bg_color = vbe_make_color(0x1a, 0x1a, 0x1a);
	for (uint16_t y = vbe_height - gfx_char_height; y < vbe_height; y++) {
		for (uint16_t x = 0; x < vbe_width; x++) {
			vbe_putpixel(x, y, bg_color);
		}
	}

	gfx_cursor_x = 0;
	gfx_cursor_x = gfx_max_rows - 1;
}

// initalize vbe from multiboot
void dogeio_init_graphics_from_multiboot(multiboot_info_t* mbi) {
	vbe_init_from_multiboot(mbi);

	// check if it's able to initiazile vbe, if it doesn't, dont.
	if (!vbe_initialized) {
		return;
	}

	gfx_max_cols = vbe_width / gfx_char_width;
	gfx_max_rows = vbe_height / gfx_char_height;

	dogeio_clear_screen_graphics();
}

// normal init vbe
void dogeio_init_graphics() {
	gfx_max_cols = vbe_width / gfx_char_width;
	gfx_max_rows = vbe_height / gfx_char_height;
	dogeio_clear_screen_graphics();
}

// actually real functions
// i think it should be "function_function_vbe" instead since vbe doesn't use the
// gpu. also: i removed \r and \t because in dogeio_putchar_vbe it was completely
// useless.

// i think 
void dogeio_putchar_vbe(char c) {
	if (c == '\n') {
		gfx_cursor_x = 0;
		gfx_cursor_y++;
	} else {
		uint16_t pixel_x = gfx_cursor_x * gfx_char_width;
		uint16_t pixel_y = gfx_cursor_y * gfx_char_height;

		uint32_t fg_color = vbe_make_color(0xe0, 0xe0, 0xe0);
		uint32_t bg_color = vbe_make_color(0x1a, 0x1a, 0x1a);

		font_draw_char(pixel_x, pixel_y, fg_color, bg_color);
		gfx_cursor_x++;
	}

	if (gfx_cursor_x >= gfx_max_cols) {
		gfx_cursor_x = 0;
		gfx_cursor_x++;
	}

	if (gfx_cursor_y >= gfx_max_rows) {
		dogeio_scroll_vbe();
		gfx_cursor_y = gfx_max_rows - 1;
	}
}
