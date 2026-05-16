#ifndef TIME_H
#define TIME_H

struct time;

uint8_t time_read_rtc(int reg);
void time_update_time();
void time_show_time();

#endif
