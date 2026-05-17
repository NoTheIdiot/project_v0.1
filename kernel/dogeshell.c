#include <stdint.h>
#include <stddef.h>
#include <dogeio.h>
#include <dogemath.h>
#include <dogeports.h>
#include <dogestring.h>
#include <font.h>
#include <multiboot.h>
#include <time.h>

extern char* windoge_full_version;
extern char* windoge_short_version;
extern void meta_sysinfo();
extern void meta_dogescript(char* filename);

void doge_shell() {
	char command[64];

	while (true) {

		dogeio_print("windoge-/# ");
		dogeio_input(command, 64);

		if (string_startsWith(command, "print")) {
			dogeio_println(command + 6);
		} else if (string_startsWith(command, "bark")) {
			dogeio_println(command + 5);
		}

		if (string_strcmp(command, "ver")) {
			dogeio_println(windoge_full_version);
		} else if (string_strcmp(command, "sysinfo")) {
			meta_sysinfo();
		}

		if (string_strcmp(command, "time")) {
			time_update_time();
			time_show();
		}

		if (string_strcmp(command, "clear")) {
			dogeio_clear_screen();
		}

		if (string_startsWith(command, "dogescript")) {
			meta_dogescript(command + 10);
		}

		if (string_strcmp(command, "halt")) {
			dogeio_clear_screen();
			dogeio_print("Halting the many cpu, such goodbye!");
			while (true) { __asm__ volatile ("hlt"); }
		}
	}
}
