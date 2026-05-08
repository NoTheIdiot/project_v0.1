#ifndef DOGEPORTS_H
#define DOGEPORTS_H

uint8_t ports_inb(uint16_t port);
void ports_outb(uint16_t port, uint8_t val);
uint16_t ports_inw(uint16_t port);
void ports_outw(uint16_t port, uint16_t data);

#endif