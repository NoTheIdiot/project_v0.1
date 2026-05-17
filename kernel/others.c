#include <dogeio.h>
#include <time.h>
#include "info.h"

// lil shortcut lol
static void p(char* string) {
	dogeio_print(string);
}

void others_sysinfo(multiboot_info_t* mbi) {

	char cpu_buffer[128];
	
	dogeio_println("Many information about your wow system: \n");
	p("Version: ");
	dogeio_println(windoge_full_version);
	p("CPU: ");
	dogeio_get_cpu_name(cpu_buffer);
	p("\n");
	p("RAM: ");
	dogeio_get_total_ram(mbi);
	p("Boot Time: ");
	dogeio_println(such_boot_time);
	p("Current Time: ");
	time_update_time();
	time_show();
	
}
