// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// -------- //
// maple_tx //
// -------- //

#define maple_tx_wrap_target 0
#define maple_tx_wrap 28

static const uint16_t maple_tx_program_instructions[] = {
            //     .wrap_target
    0xf080, //  0: set    pindirs, 0      side 1     
    0x9ca0, //  1: pull   block           side 1 [12]
    0x7020, //  2: out    x, 32           side 1     
    0xf083, //  3: set    pindirs, 3      side 1     
    0xf043, //  4: set    y, 3            side 1     
    0xfc02, //  5: set    pins, 2         side 1 [12]
    0xac42, //  6: nop                    side 0 [12]
    0x1c86, //  7: jmp    y--, 6          side 1 [12]
    0xf603, //  8: set    pins, 3         side 1 [6] 
    0xac42, //  9: nop                    side 0 [12]
    0x6041, // 10: out    y, 1            side 0     
    0xe501, // 11: set    pins, 1         side 0 [5] 
    0x0070, // 12: jmp    !y, 16          side 0     
    0xb642, // 13: nop                    side 1 [6] 
    0xfc02, // 14: set    pins, 2         side 1 [12]
    0x1613, // 15: jmp    19              side 1 [6] 
    0xa642, // 16: nop                    side 0 [6] 
    0xec00, // 17: set    pins, 0         side 0 [12]
    0xb642, // 18: nop                    side 1 [6] 
    0x7601, // 19: out    pins, 1         side 1 [6] 
    0x0b4a, // 20: jmp    x--, 10         side 0 [11]
    0xec01, // 21: set    pins, 1         side 0 [12]
    0xbc42, // 22: nop                    side 1 [12]
    0xac42, // 23: nop                    side 0 [12]
    0xec00, // 24: set    pins, 0         side 0 [12]
    0xec01, // 25: set    pins, 1         side 0 [12]
    0xec00, // 26: set    pins, 0         side 0 [12]
    0xec01, // 27: set    pins, 1         side 0 [12]
    0xfc03, // 28: set    pins, 3         side 1 [12]
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program maple_tx_program = {
    .instructions = maple_tx_program_instructions,
    .length = 29,
    .origin = -1,
};

static inline pio_sm_config maple_tx_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + maple_tx_wrap_target, offset + maple_tx_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}

static inline void maple_tx_program_init(PIO TXPio, uint SM, uint Offset, uint Pin1, uint Pin5, float ClockDivider)
{
    pio_sm_config SMConfig = maple_tx_program_get_default_config(Offset);
	assert(Pin5 == Pin1 + 1); // Need to be consecutive for set to control both pins
    sm_config_set_out_pins(&SMConfig, Pin1, 1); // Only want to output on pin 1 (so we can shift directly)
	sm_config_set_set_pins(&SMConfig, Pin1, 2); // But we need to set direction of both pins to take control of bus
	sm_config_set_sideset_pins(&SMConfig, Pin5); // Possibly could do without on second thoughts but saves some instructions 
	sm_config_set_out_shift(&SMConfig, false, true, 32); // Autopull every 32 bits (makes DMA more efficient to do it this way)
	sm_config_set_clkdiv(&SMConfig, ClockDivider);
	sm_config_set_fifo_join(&SMConfig, PIO_FIFO_JOIN_TX); // Not using RX FIFO so double TX FIFO length
	// Set the pin direction to input at the PIO but high when used as output
	pio_sm_set_pins_with_mask(TXPio, SM, (1u << Pin1) | (1u << Pin5), (1u << Pin1) | (1u << Pin5));
    pio_sm_set_pindirs_with_mask(TXPio, SM, 0, (1u << Pin1) | (1u << Pin5));
	// Set this pin's GPIO function (connect PIO to the pad)
    pio_gpio_init(TXPio, Pin1);
    pio_gpio_init(TXPio, Pin5);
    pio_sm_init(TXPio, SM, Offset, &SMConfig); // Load our configuration, and jump to the start of the program
    pio_sm_set_enabled(TXPio, SM, true); // Set the state machine running
}

#endif

// ---------------- //
// maple_rx_triple1 //
// ---------------- //

#define maple_rx_triple1_wrap_target 0
#define maple_rx_triple1_wrap 1

static const uint16_t maple_rx_triple1_program_instructions[] = {
            //     .wrap_target
    0x20c7, //  0: wait   1 irq, 7                   
    0x4002, //  1: in     pins, 2                    
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program maple_rx_triple1_program = {
    .instructions = maple_rx_triple1_program_instructions,
    .length = 2,
    .origin = -1,
};

static inline pio_sm_config maple_rx_triple1_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + maple_rx_triple1_wrap_target, offset + maple_rx_triple1_wrap);
    return c;
}
#endif

// ---------------- //
// maple_rx_triple2 //
// ---------------- //

#define maple_rx_triple2_wrap_target 0
#define maple_rx_triple2_wrap 3

static const uint16_t maple_rx_triple2_program_instructions[] = {
            //     .wrap_target
    0x2020, //  0: wait   0 pin, 0                   
    0xc007, //  1: irq    nowait 7                   
    0x20a0, //  2: wait   1 pin, 0                   
    0xc007, //  3: irq    nowait 7                   
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program maple_rx_triple2_program = {
    .instructions = maple_rx_triple2_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config maple_rx_triple2_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + maple_rx_triple2_wrap_target, offset + maple_rx_triple2_wrap);
    return c;
}
#endif

// ---------------- //
// maple_rx_triple3 //
// ---------------- //

#define maple_rx_triple3_wrap_target 0
#define maple_rx_triple3_wrap 3

static const uint16_t maple_rx_triple3_program_instructions[] = {
            //     .wrap_target
    0x2021, //  0: wait   0 pin, 1                   
    0xc007, //  1: irq    nowait 7                   
    0x20a1, //  2: wait   1 pin, 1                   
    0xc007, //  3: irq    nowait 7                   
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program maple_rx_triple3_program = {
    .instructions = maple_rx_triple3_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config maple_rx_triple3_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + maple_rx_triple3_wrap_target, offset + maple_rx_triple3_wrap);
    return c;
}

static inline void maple_rx_triple_program_init(PIO RXPio, uint* Offset, uint Pin1, uint Pin5, float ClockDivider)
{
	assert(Pin5 == Pin1 + 1);
	for (int SM = 0; SM < 3; SM++)
	{
		// Both pins inputs
		pio_sm_set_consecutive_pindirs(RXPio, SM, Pin1, 2, false);
		pio_sm_config c = 
			(SM == 0)?maple_rx_triple1_program_get_default_config(Offset[0]):
			((SM == 1)?maple_rx_triple2_program_get_default_config(Offset[1]):
			maple_rx_triple3_program_get_default_config(Offset[2]));
		sm_config_set_in_pins(&c, Pin1);
		// autopush every 8 bits (gives possibly 3 missed transitions which is enough to still detect end of packet)
		sm_config_set_in_shift(&c, false, true, 8);
		sm_config_set_clkdiv(&c, ClockDivider);
		sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_RX); // Not using transmit FIFO so use it for recieving
		// Load our configuration, and jump to the start of the program
		pio_sm_init(RXPio, SM, Offset[SM], &c);
	}
}

#endif
