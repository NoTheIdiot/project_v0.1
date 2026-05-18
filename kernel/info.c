#include <stddef.h>
#include <stdint.h>
#include "dogeio.h"
#include "time.h"
#include "info.h"

char* windoge_full_version = "WindogeOS v0.1";
char* windoge_short_version = "v0.1";
char* boot_time;

void record_boot_time() {
	boot_time = time_get_raw();
}
