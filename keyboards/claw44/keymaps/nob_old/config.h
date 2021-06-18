/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define TAPPING_FORCE_HOLD
#define PERMISSIVE_HOLD
#define TAPPING_TERM 180
#define TAPPING_TOGGLE 1

/* WS2812B RGB LED */
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
//#define RGBLIGHT_EFFECT_STATIC_GRANDIENT
//#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLED_NUM 12
#define RGBLIGHT_SPRIT
#define RGBLED_SPLIT {6,6} //Number of LEDs
#define RGBLIGHT_SLEEP

// The LEDs on the slave half go in reverse order
#define RGBLIGHT_LED_MAP {0,1,2,3,4,5,11,10,9,8,7,6}

#define OLED_FONT_H "keyboards/claw44/lib/glcdfont.c"

#define ROMAJI_TERM 75
