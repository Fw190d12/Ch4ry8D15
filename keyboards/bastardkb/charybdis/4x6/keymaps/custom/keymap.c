/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#define TAPPING_TERM 200
// qmk compile -c -kb bastardkb/charybdis/4x6 -km custom

// Combos
const uint16_t PROGMEM test_combo1[] = {KC_DOWN, KC_RIGHT, COMBO_END};

combo_t key_combos[] = {
    COMBO(test_combo1, LSFT(KC_DEL)) // keycodes with modifiers are possible too!
};

// Tap Dance declarations
enum {
    TD_ESC_TILDA,
    TD_SLSH_BSLS,
    TD_CTRL_MO3
};
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD
} td_state_t;
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_TILDA] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
    [TD_SLSH_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
    [TD_CTRL_MO3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────╮
        TD(TD_ESC_TILDA),KC_1,  KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,
  // ├─────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,
  // ├─────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_RBRC,
  // ├─────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        KC_LCTL,    LT(3,KC_Z), KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     TD(TD_SLSH_BSLS),LT(3,KC_QUOT),
  // ╰─────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────╯
                                        KC_SPC,     KC_LSFT,    KC_LGUI,        KC_ENT,     KC_BSPC,
                                                    KC_LALT,    MO(1),          MO(2)
  //                                     ╰─────────────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────╮
        KC_F12,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,          KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        KC_GRV,     XXXXXXX,    XXXXXXX,    KC_UP,      XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_VOLU,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        KC_TRNS,    XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_RGHT,    XXXXXXX,        KC_LEFT,    KC_UP,      KC_DOWN,    KC_RGHT,    XXXXXXX,    KC_MUTE,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_VOLD,
  // ╰───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────╯
                                        XXXXXXX,    KC_TRNS,    XXXXXXX,            KC_TRNS,    KC_DEL,
                                                    XXXXXXX,    KC_TRNS,            XXXXXXX
  //                                     ╰───────────────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────╮
        KC_F12,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,          KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        KC_MNXT,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_EQL,     KC_P7,      KC_P8,      KC_P9,      KC_PDOT,    KC_VOLU,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        KC_MPLY,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_PPLS,    KC_P4,      KC_P5,      KC_P6,      KC_PMNS,    KC_MUTE,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
        KC_MPRV,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_PAST,    KC_P1,      KC_P2,      KC_P3,      KC_PSLS,    KC_VOLD,
  // ╰───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────╯
                                            KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    XXXXXXX,
                                                        KC_TRNS,    XXXXXXX,        KC_P0
  //                                       ╰─────────────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────╮ ╭────────────────────────────────────────────────────────────────────────╮
       EE_CLR,      QK_BOOT,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        DT_UP,      DT_DOWN,    DT_PRNT,    XXXXXXX,    QK_BOOT,    EE_CLR,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
       XXXXXXX,     XXXXXXX,    KC_P7,      KC_P8,      KC_P9,      S_D_MOD,        S_D_MOD,    DPI_MOD,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
       XXXXXXX,     KC_LGUI,    KC_P4,      KC_P5,      KC_P6,      XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    LGUI(KC_L), XXXXXXX,    XXXXXXX,
  // ├───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────┤
       KC_TRNS,     KC_TRNS,   KC_P1,      KC_P2,      KC_P3,       XXXXXXX,        XXXXXXX,    XXXXXXX,    SNIPING,    DRGSCRL,    XXXXXXX,    XXXXXXX,
  // ╰───────────────────────────────────────────────────────────────────────┤ ├────────────────────────────────────────────────────────────────────────╯
                                            KC_TRNS,    KC_TRNS,    KC_TRNS,        XXXXXXX,    XXXXXXX,
                                                        KC_TRNS,    KC_TRNS,        XXXXXXX
  //                                       ╰─────────────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on



#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif


td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed){
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else {
    return TD_UNKNOWN;
    }
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: layer_move(3); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;

        default: break;
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: layer_move(0); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;

        default: break;
    }
    xtap_state.state = TD_NONE;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_ESC_TILDA):
            return TAPPING_TERM + 500;
        case TD(TD_CTRL_MO3):
            return TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}


