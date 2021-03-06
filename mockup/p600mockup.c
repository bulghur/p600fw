#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "p600.h"

////////////////////////////////////////////////////////////////////////////////
// Mockup implementation of low level interface that can be loaded in the emulator
////////////////////////////////////////////////////////////////////////////////

typedef __stdcall void (*emu_write_t)(uint8_t,uint16_t,uint8_t);
typedef __stdcall uint8_t (*emu_read_t)(uint8_t,uint16_t);
typedef __stdcall void (*emu_debug_t)(char);
typedef __stdcall void (*emu_start_t)(void);

// to emu
emu_write_t emu_write;
emu_read_t emu_read;
emu_debug_t emu_debug;

void mem_write(uint16_t address, uint8_t value)
{
	emu_write(0,address,value);
}

void io_write(uint8_t address, uint8_t value)
{
	emu_write(1,address,value);
}

uint8_t mem_read(uint16_t address)
{
	return emu_read(0,address);
}

uint8_t io_read(uint8_t address)
{
	return emu_read(1,address);
}

void print(const char *s)
{
	char c;

	while (1) {
		c = *s++;
		if (!c) break;
		if (c == '\n') emu_debug('\r');
		emu_debug(c);
	}
}

void phex1(unsigned char c)
{
	emu_debug(c + ((c < 10) ? '0' : 'A' - 10));
}

void phex(unsigned char c)
{
	phex1(c >> 4);
	phex1(c & 15);
}

void phex16(unsigned int i)
{
	phex(i >> 8);
	phex(i);
}

__declspec(dllexport) __stdcall void emu_init(emu_write_t write,emu_read_t read, emu_debug_t debug)
{
	emu_write=write;
	emu_read=read;
	emu_debug=debug;

	p600_init();
}

__declspec(dllexport) __stdcall void emu_start(void)
{
	p600_update();
	p600_fastInterrupt();
	p600_slowInterrupt();
}


static uint8_t storage[STORAGE_SIZE];

void storage_write(uint32_t pageIdx, uint8_t *buf)
{
	memcpy(&storage[pageIdx*STORAGE_PAGE_SIZE],buf,STORAGE_PAGE_SIZE);
}

void storage_read(uint32_t pageIdx, uint8_t *buf)
{
	memcpy(buf,&storage[pageIdx*STORAGE_PAGE_SIZE],STORAGE_PAGE_SIZE);
}


void wait(uint8_t cycles)
{
	// emu doesn't care about timing
}

void int_clear(void)
{
	// no ints, done in tick
}

void int_set(void)
{
	// no ints, done in tick
}	
