#ifndef TIME_H
#define TIME_H

struct time;

uint8_t time_read_rtc(int reg) {
	ports_outb(0x70, reg);
	return ports_inb(0x71);
}

#endif
