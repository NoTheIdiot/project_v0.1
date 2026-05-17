#include <stdint.h>
#include <stddef.h>
#include <dogeio.h>
#include <dogemath.h>
#include <dogeports.h>
#include <dogestring.h>
#include <font.h>
#include <multiboot.h>
#include <time.h>

void doge_shell() {

	char command[64];

	while (true) {

		dogeio_print("windoge-/# ");
		dogeio_input(command, 64);

	}
}
