/* Copyright 2018 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "quantum.h"

// Layer names
enum{
  // - Base layer:
  _BASE,
  // - Symbols, numbers, and functions:
  _FN
};

#define FN MO(_FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
		KC_7, KC_8, KC_9,
		KC_4, KC_5, KC_6,
		KC_1, KC_2, KC_3,
		FN, KC_0, KC_DOT
	),
  
	[_FN] = LAYOUT(
		RGB_MOD, KC_HOME, KC_PGUP,
		RGB_HUI, KC_END, KC_PGDN,
		RGB_HUD, RGB_VAD, RGB_VAI,
		KC_TRNS, KC_TRNS, KC_ENT
	)
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
void render_logo(void) {
    static const char PROGMEM logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(logo, false);
    
}


extern bool oled_initialized;
void matrix_scan_keymap(void) {
  if(!oled_initialized) {
    wait_ms(200);
        oled_init(0);

  }
 }

uint16_t        oled_timer;
void oled_task_keyboard(void) {

    if (timer_elapsed(oled_timer) > 20000) {
        oled_off();
        return;
    }

            render_logo();
        
   }

#endif