/*
 * hid.h
 *
 *  Created on: Apr 28, 2011
 *      Author: sebastiaan
 */

#ifndef HID_H_
#define HID_H_
/* Keyboard usage values, see usb.org's HID-usage-tables document, chapter
 * 10 Keyboard/Keypad Page for more codes.
 */
#define MOD_CONTROL_LEFT    (1<<0)
#define MOD_SHIFT_LEFT      (1<<1)
#define MOD_ALT_LEFT        (1<<2)
#define MOD_GUI_LEFT        (1<<3)
#define MOD_CONTROL_RIGHT   (1<<4)
#define MOD_SHIFT_RIGHT     (1<<5)
#define MOD_ALT_RIGHT       (1<<6)
#define MOD_GUI_RIGHT       (1<<7)

#define KEY_A       4
#define KEY_B       5
#define KEY_C       6
#define KEY_D       7
#define KEY_E       8
#define KEY_F       9
#define KEY_G       10
#define KEY_H       11
#define KEY_I       12
#define KEY_J       13
#define KEY_K       14
#define KEY_L       15
#define KEY_M       16
#define KEY_N       17
#define KEY_O       18
#define KEY_P       19
#define KEY_Q       20
#define KEY_R       21
#define KEY_S       22
#define KEY_T       23
#define KEY_U       24
#define KEY_V       25
#define KEY_W       26
#define KEY_X       27
#define KEY_Y       28
#define KEY_Z       29
#define KEY_1       30
#define KEY_2       31
#define KEY_3       32
#define KEY_4       33
#define KEY_5       34
#define KEY_6       35
#define KEY_7       36
#define KEY_8       37
#define KEY_9       38
#define KEY_0       39


#define  HID_ENTER            40
#define  HID_ESCAPE           41
#define  HID_BACKSPACE        42
#define  HID_TAB              43
#define  HID_SPACEBAR         44
#define  HID_UNDERSCORE       45
#define  HID_PLUS             46
/*
#define  HID_[ {              47
#define  HID_] }              48
*/
#define  HID_BACKSLASH        49
/*
#define  HID_# ~              50
#define  HID_; :              51
#define  HID_� "              52
*/
#define  HID_TILDE            53
#define  HID_COMMA            54
#define  HID_DOT              55
#define  HID_SLASH            56
#define  HID_CAPS_LOCK        57

#define KEY_F1      58
#define KEY_F2      59
#define KEY_F3      60
#define KEY_F4      61
#define KEY_F5      62
#define KEY_F6      63
#define KEY_F7      64
#define KEY_F8      65
#define KEY_F9      66
#define KEY_F10     67
#define KEY_F11     68
#define KEY_F12     69

#endif /* HID_H_ */
