#include <arduino.h>
#include "tm1637.h"

/*
#define	TM1637_DIO_HIGH()		(PORTB |= _BV(DIO))
#define	TM1637_DIO_LOW()		(PORTB &= ~_BV(DIO))
#define	TM1637_DIO_OUTPUT()		(DDRB |= _BV(DIO))
#define	TM1637_DIO_INPUT()		(DDRB &= ~_BV(DIO))
#define	TM1637_DIO_READ() 		(((PINB & _BV(DIO)) > 0) ? 1 : 0)
#define	TM1637_CLK_HIGH()		(PORTB |= _BV(CLK))
#define	TM1637_CLK_LOW()		(PORTB &= ~_BV(CLK))
*/
#define	TM1637_DIO_HIGH()		(digitalWrite (DIO, HIGH))
#define	TM1637_DIO_LOW()		(digitalWrite (DIO, LOW))
#define	TM1637_DIO_OUTPUT()		(pinMode (DIO, OUTPUT))
#define	TM1637_DIO_INPUT()		(pinMode (DIO, INPUT))
#define	TM1637_CLK_OUTPUT()		(pinMode (CLK, OUTPUT))
#define	TM1637_CLK_INPUT()		(pinMode (CLK, INPUT))
#define	TM1637_DIO_READ() 		(digitalRead (DIO))
#define	TM1637_CLK_HIGH()		(digitalWrite (CLK, HIGH))
#define	TM1637_CLK_LOW()		(digitalWrite (CLK, LOW))

#define _delay_us(x) (delayMicroseconds(x))

static void TM1637_send_config(const uint8_t enable, const uint8_t brightness);
static void TM1637_send_command(const uint8_t value);
static void TM1637_start(void);
static void TM1637_stop(void);
static uint8_t TM1637_write_byte(uint8_t value);

static uint8_t _config = TM1637_SET_DISPLAY_ON | TM1637_BRIGHTNESS_MAX;
//static uint8_t _segments = 0xff;
const uint8_t _digit2segments[] =
{
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F,  // 9
	0x00,  // blank
	0x40  // -
};

void TM1637_init(const uint8_t enable, const uint8_t brightness)
{
	/*
	DDRB |= (_BV(DIO)|_BV(CLK));
	PORTB &= ~(_BV(DIO)|_BV(CLK));
	*/
	TM1637_DIO_OUTPUT();
	TM1637_CLK_OUTPUT();
	TM1637_DIO_LOW();
	TM1637_CLK_LOW();

	TM1637_send_config(enable, brightness);
}

void TM1637_enable(const uint8_t value)
{

	TM1637_send_config(value, _config & TM1637_BRIGHTNESS_MAX);
}

void TM1637_set_brightness(const uint8_t value)
{

	TM1637_send_config(_config & TM1637_SET_DISPLAY_ON,
		value & TM1637_BRIGHTNESS_MAX);
}


void TM1637_display_digit(const uint8_t position, const uint8_t digit)
{
	uint8_t segments = (digit < 12 ? pgm_read_byte_near((uint8_t *)&_digit2segments + digit) : 0x00);

	/*if (position == 0x01) {
		segments = segments | (_segments & 0x80);
		_segments = segments;
	}*/

	//TM1637_display_segments((position + 3) % 6, segments);
	TM1637_send_command(TM1637_CMD_SET_DATA | TM1637_SET_DATA_F_ADDR);
	TM1637_start();
	//TM1637_write_byte(TM1637_CMD_SET_ADDR | (position & (TM1637_POSITION_MAX - 1)));
	TM1637_write_byte(TM1637_CMD_SET_ADDR | ((position + 3) % 6));
	TM1637_write_byte(segments);
	TM1637_stop();
}


void TM1637_send_config(const uint8_t enable, const uint8_t brightness)
{

	_config = (enable ? TM1637_SET_DISPLAY_ON : TM1637_SET_DISPLAY_OFF) |
		(brightness > TM1637_BRIGHTNESS_MAX ? TM1637_BRIGHTNESS_MAX : brightness);

	TM1637_send_command(TM1637_CMD_SET_DSIPLAY | _config);
}

void TM1637_send_command(const uint8_t value)
{

	TM1637_start();
	TM1637_write_byte(value);
	TM1637_stop();
}

void TM1637_start(void)
{

	TM1637_DIO_HIGH();
	TM1637_CLK_HIGH();
	_delay_us(5);
	TM1637_DIO_LOW();
}

void TM1637_stop(void)
{

	TM1637_CLK_LOW();
	_delay_us(5);

	TM1637_DIO_LOW();
	_delay_us(5);

	TM1637_CLK_HIGH();
	_delay_us(5);

	TM1637_DIO_HIGH();
}

uint8_t TM1637_write_byte(uint8_t value)
{
	uint8_t i, ack;

	for (i = 0; i < 8; ++i, value >>= 1) {
		TM1637_CLK_LOW();
		_delay_us(5);

		if (value & 0x01) {
			TM1637_DIO_HIGH();
		} else {
			TM1637_DIO_LOW();
		}

		TM1637_CLK_HIGH();
		_delay_us(5);
	}

	TM1637_CLK_LOW();
	TM1637_DIO_INPUT();
	TM1637_DIO_HIGH();
	_delay_us(5);

	ack = TM1637_DIO_READ();
	if (ack) {
		TM1637_DIO_OUTPUT();
		TM1637_DIO_LOW();
	}
	_delay_us(5);

	TM1637_CLK_HIGH();
	_delay_us(5);

	TM1637_CLK_LOW();
	_delay_us(5);

	TM1637_DIO_OUTPUT();

	return ack;
}
