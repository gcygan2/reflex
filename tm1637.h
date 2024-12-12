#ifndef	TM1637_H
#define	TM1637_H

#include <stdint.h>

// Main Settings
#define	DIO	23
#define	CLK	22
#define	TM1637_BRIGHTNESS_MAX		7
#define	TM1637_POSITION_MAX		6

// TM1637 commands
#define	TM1637_CMD_SET_DATA		0x40
#define	TM1637_CMD_SET_ADDR		0xC0
#define	TM1637_CMD_SET_DSIPLAY		0x80

// TM1637 data settings (use bitwise OR to contruct complete command)
#define	TM1637_SET_DATA_WRITE		0x00 // write data to the display register
#define	TM1637_SET_DATA_READ		0x02 // read the key scan data
#define	TM1637_SET_DATA_A_ADDR		0x00 // automatic address increment
#define	TM1637_SET_DATA_F_ADDR		0x04 // fixed address
#define	TM1637_SET_DATA_M_NORM		0x00 // normal mode
#define	TM1637_SET_DATA_M_TEST		0x10 // test mode

// TM1637 display control command set (use bitwise OR to consruct complete command)
#define	TM1637_SET_DISPLAY_OFF		0x00 // off
#define	TM1637_SET_DISPLAY_ON		0x08 // on
extern void TM1637_init(const uint8_t enable, const uint8_t brightness);
extern void TM1637_enable(const uint8_t value);
extern void TM1637_set_brightness(const uint8_t value);
extern void TM1637_display_digit(const uint8_t position, const uint8_t digit);

#endif
