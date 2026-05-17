#include <stddef.h>
#include <stdint.h>
#include <dogeio.h>
#include <dogebool.h>
#include <multiboot.h>

void such_boot_check(uint32_t magic, uint32_t addr) {

	// check if the multiboot header is correct
	if (magic != 0x2BADB002) {
		dogeio_println("[Not Wow] Multiboot Header isn't such equal to 0z2BADB002");
		while (true) { __asm__ volatile ("hlt"); }
	} else {
		dogeio_println("[Wow] Multiboot Header is many valid, wow.");
	}

	multiboot_info_t* mbi = (multiboot_info_t*) addr;

	if (mbi->flags & (1 << 6)) {
		dogeio_println("[Wow] Multiboot Header flags is such valid.");
	} else {
		dogeio_println("[Warning] Multiboot Header flags isn't much valid.");
	}
} 
