#include <stdint.h>
#include "../utils/ports.h"
#include "screen.h"

#define KEYBOARD_PORT 0x60

// special keys
#define ESC 0x1
#define PGUP 0x49
#define PGDN 0x51
#define BACKSPACE 0xE
#define TAB	0xF
#define ENTER 0x1C
#define CAPS_LOCK 0x3A
#define SHIFT 0x36
#define CTRL 0x1D
#define ALT 0x38
#define SUPER 0xB9
#define R_ARROW 0x4D
#define L_ARROW 0x4B
#define U_ARROW 0x48
#define D_ARROW 0x50

#define PRESS_THRESH_FAST 1100000
#define HOLD_THRESH_FAST 160000

#define PRESS_THRESH_SLOW 1200000
#define HOLD_THRESH_SLOW 350000

typedef struct {
	char keycode;
	char chr;
} kbd_keycode;

static kbd_keycode std_keycode_table[] = {
	{0x29, '`'}, {0x2, '1'}, {0x3, '2'}, {0x4, '3'}, {0x5, '4'}, {0x6, '5'}, {0x7, '6'}, {0x8, '7'}, {0x9, '8'}, {0xA, '9'}, {0xB, '0'}, {0xC, '-'}, {0xD, '='},
	{0x10, 'q'}, {0x11, 'w'}, {0x12, 'e'}, {0x13, 'r'}, {0x14, 't'}, {0x15, 'y'}, {0x16, 'u'}, {0x17, 'i'}, {0x18, 'o'}, {0x19, 'p'}, {0x1A, '['}, {0x1B, ']'},
	{0x1e, 'a'}, {0x1f, 's'}, {0x20, 'd'}, {0x21, 'f'}, {0x22, 'g'}, {0x23, 'h'}, {0x24, 'j'}, {0x25, 'k'}, {0x26, 'l'}, {0x27, ';'}, {0x28, '\''}, {0x2B, '#'},
	{0x56, '\\'}, {0x2c, 'z'}, {0x2d, 'x'}, {0x2e, 'c'}, {0x2f, 'v'}, {0x30, 'b'}, {0x31, 'n'}, {0x32, 'm'}, {0x33, ','}, {0x34, '.'}, {0x35, '/'}, {0x39, ' '},
	//{0xE, 0x8},
	{0x0, 0x0}
};

static kbd_keycode shft_keycode_table[] = {
	{0x29, '¬'}, {0x2, '!'}, {0x3, '"'}, {0x5, '$'}, {0x6, '%'}, {0x7, '^'}, {0x8, '&'}, {0x9, '*'}, {0xA, '('}, {0xB, ')'}, {0xC, '_'}, {0xD, '+'},
	{0x10, 'Q'}, {0x11, 'W'}, {0x12, 'E'}, {0x13, 'R'}, {0x14, 'T'}, {0x15, 'Y'}, {0x16, 'U'}, {0x17, 'I'}, {0x18, 'O'}, {0x19, 'P'}, {0x1A, '{'}, {0x1B, '}'},
	{0x1e, 'A'}, {0x1f, 'S'}, {0x20, 'D'}, {0x21, 'F'}, {0x22, 'G'}, {0x23, 'H'}, {0x24, 'J'}, {0x25, 'K'}, {0x26, 'L'}, {0x27, ':'}, {0x28, '@'}, {0x2B, '~'},
	{0x56, '|'}, {0x2c, 'Z'}, {0x2d, 'X'}, {0x2e, 'C'}, {0x2f, 'V'}, {0x30, 'B'}, {0x31, 'N'}, {0x32, 'M'}, {0x33, '<'}, {0x34, '>'}, {0x35, '?'}, {0x39, ' '},
	//{0xE, 0x8},
	{0x0, 0x0}
};

char get_input_keycode();
char get_printable_char(char keycode, int i, uint8_t shift);
void kbd_readline(char* buffer, int tty_calibration, int buffer_bytes);
