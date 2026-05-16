#include <stdint.h>
#include <stddef.h>
#include <dogeio.c>
#include <dogestring.h>
#include <dogeports.h>
#include <dogemath.h>
#include <font.h>
#include <dogebool.h>
#include <consts.h>
#include <dogeio_gpu.h>
#include <dogevbe.h>
#include <fat16.h>

extern void doge_shell();
extern void such_boot_check();

int main(uint32_t magic, multiboot_info_t* mbi) {
	return 0;
}
