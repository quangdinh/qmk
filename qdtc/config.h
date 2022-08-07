/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

// Select hand configuration
#define MASTER_LEFT

// Define time interval to sync oled screen
#define SPLIT_SYNC_INTERVAL 250

#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// RGB
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 10

// OLED
#define OLED_UPDATE_INTERVAL 0
#define OLED_SCROLL_TIMEOUT 0
#define OLED_FONT_H "qdtcglcdfont.c"
#define OLED_FONT_WIDTH 12
#define OLED_FONT_HEIGHT 8
#define OLED_FONT_END 191
#define OLED_FONT_START 32
#define OLED_BRIGHTNESS 150

// Sync animation
#define SYNC_ANIMATION_TIME 900
#define SYNC_ANIMATION_SPEED 15

// Tap Hold
#define TAPPING_TERM 195

// Combo
#define COMBO_TERM 35
#define EXTRA_SHORT_COMBOS
#define COMBO_ONLY_FROM_LAYER 0

// Reducing firmware size
#define NO_ACTION_ONESHOT
#define LAYER_STATE_8BIT

#define SPLIT_TRANSACTION_IDS_USER USER_SPLIT_SYNC