#define LCD_PORT GPIOA

#define IOAEN (1<<2)

#define RS (1<<2)
#define RW (1<<1)
#define E  (1<<0)

#define LCD_clear              0x1
#define LCD_cursor_home        0x2
#define LCD_shift_cursor_right 0x6
#define LCD_cursor_blinking    0xF
#define LCD_cursor_first_line  0x80
#define LCD_cursor_second_line 0xC0
#define LCD_8_bit_data         0x38
#define LCD_4_bit_data         0x28

void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_nibble_write(unsigned char data, unsigned char control);
void LCD_init(void);
void LCD_string(char string[]);
