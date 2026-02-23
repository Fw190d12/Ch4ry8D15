#include "tap_dance.h"

static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

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
