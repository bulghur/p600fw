////////////////////////////////////////////////////////////////////////////////
// DAC chip
////////////////////////////////////////////////////////////////////////////////

#include "dac.h"

void inline dac_write(uint16_t value)
{
	mem_write(0x4001,value>>10);
	mem_write(0x4000,value>>2);
}