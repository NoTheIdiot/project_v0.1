#include <stdint.h>
#include <stddef.h>
#include <dogeio.c>all
#include <dogestring.h>
#include <dogeports.h>
#include <dogemath.h>
#include <font.h>
#include <dogebool.h>
#include <consts.h>
#include <dogeio_gpu.h>
#include <dogevbe.h>
#include "fat16.h"
#include "info.h"

extern void doge_shell();
extern void such_boot_check();

int main(uint32_t magic, multiboot_info_t* mbi) {
	// booting
	dogeio_println("Booting WindogeOS");
	
	// init stuff
	dogeio_println("[Note] Init such drivers...pls wait.");
	disk_init();
	dogeio_init_vbe_mbi();
	dogeio_init_vbe();
	dogeio_println("[Wow] Init done.");

	// record boot time
	record_boot_time();
	
	dogeio_print("[Note] Such boot time is ");
	time_show();
	dogeio_println("");
	dogeio_println("[Note] Checking multiboot header, pls wait...");
	such_boot_check();
	
	dogeio_print("Welcome to WindogeOS! ");
	dogeio_println(windoge_short_version);
	doge_shell();
	
	return 0;
}
