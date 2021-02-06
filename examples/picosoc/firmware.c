#include <stdint.h>
#include <stdbool.h>
#include "animate.h"

// a pointer to this is a null pointer, but the compiler does not
// know that because "sram" is a linker symbol from sections.lds.
extern uint32_t sram;

#define reg_spictrl (*(volatile uint32_t*)0x02000000)
#define reg_uart_clkdiv (*(volatile uint32_t*)0x02000004)
#define reg_uart_data (*(volatile uint32_t*)0x02000008)
#define reg_leds (*(volatile uint32_t*)0x03000000)

extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss,_heap_start;

uint32_t set_irq_mask(uint32_t mask); asm (
    ".global set_irq_mask\n"
    "set_irq_mask:\n"
    ".word 0x0605650b\n"
    "ret\n"
);

bool animate = false;

void putchar(char c)
{
	if (c == '\n')
		putchar('\r');
	reg_uart_data = c;
}

void print(const char *p)
{
	while (*p)
		putchar(*(p++));
}

void print_hex(uint32_t v, int digits)
{
	for (int i = 7; i >= 0; i--) {
		char c = "0123456789abcdef"[(v >> (4*i)) & 15];
		if (c == '0' && i >= digits) continue;
		putchar(c);
		digits = i;
	}
}

void print_dec(uint32_t v)
{
	if (v >= 100) {
		print(">=100");
		return;
	}

	if      (v >= 90) { putchar('9'); v -= 90; }
	else if (v >= 80) { putchar('8'); v -= 80; }
	else if (v >= 70) { putchar('7'); v -= 70; }
	else if (v >= 60) { putchar('6'); v -= 60; }
	else if (v >= 50) { putchar('5'); v -= 50; }
	else if (v >= 40) { putchar('4'); v -= 40; }
	else if (v >= 30) { putchar('3'); v -= 30; }
	else if (v >= 20) { putchar('2'); v -= 20; }
	else if (v >= 10) { putchar('1'); v -= 10; }

	if      (v >= 9) { putchar('9'); v -= 9; }
	else if (v >= 8) { putchar('8'); v -= 8; }
	else if (v >= 7) { putchar('7'); v -= 7; }
	else if (v >= 6) { putchar('6'); v -= 6; }
	else if (v >= 5) { putchar('5'); v -= 5; }
	else if (v >= 4) { putchar('4'); v -= 4; }
	else if (v >= 3) { putchar('3'); v -= 3; }
	else if (v >= 2) { putchar('2'); v -= 2; }
	else if (v >= 1) { putchar('1'); v -= 1; }
	else putchar('0');
}


uint8_t dir = 1;
char getchar_prompt(char *prompt)
{
	int32_t c = -1;

	uint32_t cycles_begin, cycles_now, cycles, anim_cycles, anim_cycles_begin;
	__asm__ volatile ("rdcycle %0" : "=r"(cycles_begin));
    anim_cycles_begin = cycles_begin;


	if (prompt)
		print(prompt);

	while (c == -1) {
		__asm__ volatile ("rdcycle %0" : "=r"(cycles_now));
		cycles = cycles_now - cycles_begin;
		if (cycles > 12000000) {
			if (prompt)
				print(prompt);
			cycles_begin = cycles_now;
        }
        anim_cycles = cycles_now - anim_cycles_begin;
        if (animate && anim_cycles > 500000) {
            anim_cycles_begin = cycles_now;
            LEDRainbowWaveEffect();
		}
		c = reg_uart_data;
	}

	return c;
}

char getchar()
{
	return getchar_prompt(0);
}


void main()
{
    // correct divider for 16mhz clock 115200 baud
	reg_uart_clkdiv = 139;
	print("Booting..\n");
    
    reg_leds = 1; // turn on led

    cRGB color;
    color.r = 0;
    color.g = 40;
    color.b = 0;
    set_ws2812(color, 2); // this just to see in simulation
    color.g = 0;

/*///////////// These were removed on commit 2d17db3c935110d21783097e9f0c5828ace5e30b and 29fc73eb1ff4295e17a93779d055bde8b5ab2b19, added back as comments for merge if non-sim
//     set_irq_mask(0xff);
//    //Removed init globals and bss in start.S 
//	//zero out .bss section
//     for (uint32_t *dest = &_sbss; dest < &_ebss;) {
//         *dest++ = 0;
//     }
//
//     // switch to dual IO mode
//     reg_spictrl = (reg_spictrl & ~0x007F0000) | 0x00400000;
//////////////////// */	
	
	while (getchar_prompt("Press ENTER to continue..\n") != '\r') { /* wait */ }


	print("\n");
	print("  ____  _          ____         ____\n");
	print(" |  _ \\(_) ___ ___/ ___|  ___  / ___|\n");
	print(" | |_) | |/ __/ _ \\___ \\ / _ \\| |\n");
	print(" |  __/| | (_| (_) |__) | (_) | |___\n");
	print(" |_|   |_|\\___\\___/____/ \\___/ \\____|\n");

	while (1)
	{
		print("\n");
		print("\n");
		print("SPI State:\n");

		print("  LATENCY ");
		print_dec((reg_spictrl >> 16) & 15);
		print("\n");

		print("  DDR ");
		if ((reg_spictrl & (1 << 22)) != 0)
			print("ON\n");
		else
			print("OFF\n");

		print("  QSPI ");
		if ((reg_spictrl & (1 << 21)) != 0)
			print("ON\n");
		else
			print("OFF\n");

		print("  CRM ");
		if ((reg_spictrl & (1 << 20)) != 0)
			print("ON\n");
		else
			print("OFF\n");

		print("\n");
		print("Select an action:\n");
		print("\n");
		print("   [1] Increment LED 0 Red\n");
		print("   [2] Increment LED 0 Green\n");
		print("   [3] Increment LED 0 Blue\n");
		print("   [4] Start animation\n");
		print("   [5] Stop animation\n");
		print("   [6] Increment GPIO LED reg\n");
		print("   [0] Set LED 0 off\n");
		print("\n");

		for (int rep = 10; rep > 0; rep--)
		{
			print("Command> ");
			char cmd = getchar();
			if (cmd > 32 && cmd < 127)
				putchar(cmd);
			print("\n");

			switch (cmd)
			{
			case '1':
                color.r ++;
                set_ws2812(color,0);
                break;
			case '2':
                color.g ++;
                set_ws2812(color,0);
                break;
			case '3':
                color.b ++;
                set_ws2812(color,0);
                break;
            case '4':
                animate = true;
                break;
            case '5':
                animate = false;
                break;
            case '6':
                reg_leds += 1;
                break;
            case '0':
                color.r = 0;
                color.g = 0;
                color.b = 0;
                set_ws2812(color,0);
                break;
			default:
				continue;
			}

			break;
		}
	}
}
