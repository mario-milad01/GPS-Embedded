
#include <stdint.h>
static void delay(volatile uint32_t d);
static void Printdata(uint8_t data);
static void lcd_pulse_en(void);
static void lcd_cmd(uint8_t cmd);
static void lcd_data(uint8_t data);
static void lcd_string(const char *str, uint8_t len);
static void lcd_init(void);
void Lcd_display(char min_index);


