/* notes

second = 0x00
minutes = 0x02
hour = 0x04
day = 0x07
month = 0x08
year = 0x09

*/

// include files
#include <stdint.h>
#include <stddef.h>
#include <dogeports.h>
#include <dogeio.h>
#include <dogestring.h>

// time structure for seconds, minutes, hours, etc.
struct {
	uint8_t second, minute, hour, day, month;
	uint32_t year;
} time;

// read rtc using outb0x70 and inb0x71
uint8_t time_read_rtc(int reg) {
	ports_outb(0x70, reg);
	return ports_inb(0x71);
}

// update time
void time_update_time() {
	while (time_read_rtc(0x0A) & 0x80);
	time.second 	= time_read_rtc(0x00);
	time.minute		= time_read_rtc(0x02);
	time.hour		= time_read_rtc(0x04);
	time.day		= time_read_rtc(0x07);
	time.month		= time_read_rtc(0x08);
	time.year		= time_read_rtc(0x09);

	uint8_t status_b = time_read_rtc(0x0B);

	if (!(status_b & 0x04)) {
		time.second		= (time.second & 0x0F) + ((time.second >> 4) * 10);
		time.minute	 	= (time.minute & 0x0F) + ((time.minute >> 4) * 10);
		uint8_t hour_variable3 = time.hour & 0x80;
		uint8_t hour_variable1 = (time.hour & 0x7F) & 0x0F;
		uint8_t hour_variable2 = ((time.hour & 0x7F) >> 4) * 10;
		time.hour		= (hour_variable1 + hour_variable2) | hour_variable3;
		time.day		= (time.day & 0x0F) + ((time.day >> 4) * 10);
		time.month		= (time.month & 0x0F) + ((time.month >> 4) * 10);
		time.year		= (time.year & 0x0F) + ((time.year >> 4) * 10);
	}

	if (!(status_b & 0x02)) {
		uint8_t is_pm = time.hour & 0x80;
		time.hour &= 0x7F;
		if (is_pm && time.hour != 12) {
			time.hour += 12;
		} else if (!is_pm && time.hour == 12) {
			time.hour = 0;
		}
	}
}

void time_show() {
	char buffer[16];
	time_update_time();

	if (time.hour < 10) dogeio_print("0");
	    string_itoa(time.hour, buffer, 10);
    dogeio_print(buffer);
    dogeio_print(":");

    if (time.minute < 10) dogeio_print("0");
    string_itoa(time.minute, buffer, 10);
    dogeio_print(buffer);
    dogeio_print(":");

    if (time.second < 10) dogeio_print("0");
    string_itoa(time.second, buffer, 10);
    dogeio_print(buffer);
}

char* time_get_raw() {
    time_update_time();

    static char raw_buffer[16];
    int i = 0;

    raw_buffer[i++] = (time.hour / 10) + '0';
    raw_buffer[i++] = (time.hour % 10) + '0';
    raw_buffer[i++] = ':';

    raw_buffer[i++] = (time.minute / 10) + '0';
    raw_buffer[i++] = (time.minute % 10) + '0';
    raw_buffer[i++] = ':';

    raw_buffer[i++] = (time.second / 10) + '0';
    raw_buffer[i++] = (time.second % 10) + '0';
    raw_buffer[i++] = '\0';

    return raw_buffer;
}
