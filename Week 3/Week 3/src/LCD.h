/*
 * LCD.h
 *
 * Created: 2/23/2017 11:20:05 AM
 *  Author: RMSjoshua
 */ 


#ifndef LCD_H_
#define LCD_H_


extern void wait (int ms);
extern void toggle_e_pin(void);
extern void init_4bit_mode(void);
extern void write_string_lcd(char *string);
extern void write_data_lcd(unsigned char byte);
extern void set_cursor(int position);
extern void scroll_text_right(void);
extern void lcd_write_command(unsigned char byte);
extern void scroll_text_left(void);
extern void clear_screen(void);



#endif /* LCD_H_ */