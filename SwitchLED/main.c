/*
The program interfaces a Switch and LED.

The program starts with the LED On. While the switch pressed the LED toggles at 5 Hz frequency.
Input: PE1 - Switch
Output: PE2 - Red LED
The Switch must be wired to the ground by using the pull-down 10kOhm resistor
The Red LED wired through 220 Ohm resistor (current through is appr. 5-6 mA)

*/

#include "TM4C123GH6PM.h"

#define SW (1 << 2U)	
#define LED (1 << 1U)
#define GPIOE_DATA_BITS(PIN) (*((volatile unsigned long *)(0x40024000UL + (PIN << 2))))
#define SYSCLK_HZ 16000000U
#define CYCLES_PER_TICK \
	4U // the delay overhead (setup stack, pop stack ...) from disassembly
#define TICKS_PER_MS ((SYSCLK_HZ / 1000U / CYCLES_PER_TICK))

// prototypes
void initGPIOE(void);
void delay(uint16_t ms);
void toggleLED(void);

int main(void) {
	initGPIOE();

	while (1) {
		GPIOE -> DATA_Bits[LED] = GPIOE -> DATA_Bits[SW] >> 1;
		delay(20);
	}
	// return 0; // unreachable code
}

void initGPIOE(void) {
	// enable clocking
	SYSCTL->RCGCGPIO |= (1 << 4U);

	// dummy read to add small delay before clocking activates
	volatile unsigned long delay = SYSCTL->RCGCGPIO;

	// disable analog functions
	GPIOE->AMSEL &= ~(SW);
	GPIOE->AMSEL &= ~(LED);

	// enable direction
	GPIOE->DIR &= ~SW; // as input
	GPIOE->DIR |= LED; // as output

	// no alternate functions
	GPIOE->AFSEL &= ~SW;
	GPIOE->AFSEL &= ~LED;
	GPIOE->PCTL &= ~SW;
	GPIOE->PCTL &= ~LED;
	
	// let the LED pin pull the 8mA current
	GPIOE ->DR8R |= LED;

	// enable digital pins
	GPIOE->DEN |= SW;
	GPIOE->DEN |= LED;
}

void delay(uint16_t ms) {
	volatile uint32_t ticks = ms * TICKS_PER_MS;
	while (ticks)
		--ticks;
}


// needed for startup_TM4C123GH6PM.c
__attribute__((naked)) void assert_failed(char const *file, int line) {
	/* TBD: damage control */
	NVIC_SystemReset(); /* reset the system */
}

















