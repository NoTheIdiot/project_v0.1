#include <stdint.h>
#include <stddef.h>
#include "dogestring.h"
#include "dogeports.h"
#include "dogemath.h"
#include "font.h"
#include "dogebool.h"
#include "consts.h"
#include "dogeio.h"
#include "dogeio_vbe.h"
#include "dogevbe.h"
#include "fat16.h"
#include "info.h"

extern void doge_shell();
extern void such_boot_check();

char* windoge_full_version = "WindogeOS v0.1";
char* windoge_short_version = "v0.1";
char* boot_time;
uint32_t primary_sector = 2048;

int windoge_os_main(multiboot_info_t* mbi) {
	// booting
	dogeio_println("Booting WindogeOS");
	
	// init stuff
	dogeio_println("[Note] Init such drivers...pls wait.");
	disk_init(primary_sector); // how do you even use this, WHAT IS LBA I JUST COPIED A FILE FROM A RANDOM DEAD REPO
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
	dogeio_println(windoge_short_version); // why doesn't it see it
	doge_shell();
	
	return 0;
}
