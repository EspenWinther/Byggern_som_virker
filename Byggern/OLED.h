#ifndef oled_h_
#define oled_h_

void init_OLED();
void OLED_Reset(void);
void OLED_Home();
unsigned int get_LCD_port(unsigned char data);
int OLED_print(char *d, char font);
int OLED_print_char(char c, char font);
void OLED_gotoline(char line);
void OLED_goto(char line, char col);
void OLED_picture(void);
void OLED_menu(void);
void OLED_highscore();
void OLED_NameScreen(void);
void OLED_animation(void);
void whileplaying(char score);
void OLED_Game_Over(char score);

int p;				
int oldscore;
char Name[3];

#endif