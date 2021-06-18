#include QMK_KEYBOARD_H
#include <stdio.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use NMBbers.

//Declare layers
enum layer_number {
    _NOBIX = 0,
    _QWERTY,
    _NMB,
    _EMACS,
    _FN,
};

//Declare custum keyCodes
enum custom_keycodes {
    INS_L = SAFE_RANGE,         //Insert Line
    KILL_L,                     //Kill Line
    RST_MOD,                    //Reset Modefier Key
};

//Alias
#define MT_SSPC LSFT_T(KC_SPC)    //hold:"Shift" tap:"Space"
#define MT_NENT LT(_NMB,KC_ENT)   //hold:"NMB" tap:"Enter"
#define MT_FK LT(_FN,KC_K)        //hold:"Function" tap:"k"
#define MT_FD LT(_FN,KC_D)        //hold:"Function" tap:"D"
#define MT_FT LT(_FN,KC_T)        //hold:"Function" tap:"T"
#define MT_FE LT(_FN,KC_E)        //hold:"Function" tap:"E"

#define MC_PSC LGUI(S(KC_S))         //Print screen
#define MC_DTR LGUI(C(KC_RIGHT))     //Desk top move right
#define MC_DTL LGUI(C(KC_LEFT))      //Desk top move left
#define MC_LCK LGUI(KC_L)            //Screen Lock
#define MC_MIN LGUI(KC_M)            //Window Minimize
#define MC_SRH LGUI(KC_S)            //Search

#define JP_AT KC_LBRC             // @
#define JP_CIRC KC_EQL            // ^, ~
#define JP_COLN KC_QUOT           // :, *
#define JP_LBRC KC_RBRC           // [
#define JP_RBRC KC_NUHS           // ]
#define JP_LCBR LSFT(JP_LBRC)     // {
#define JP_RCBR LSFT(JP_RBRC)     // }
#define JP_LPRN LSFT(KC_8)        // (
#define JP_RPRN LSFT(KC_9)        // )
#define JP_QUOT LSFT(KC_7)        //',"
#define JP_AMPR LSFT(KC_6)        // &
#define JP_UNDS LSFT(KC_INT1)     //_
#define JP_PLUS LSFT(KC_SCLN)     // +
#define JP_EQL LSFT(KC_MINS)      // =
#define JP_ASTR LSFT(JP_COLN)     // *
#define JP_GRV LSFT(JP_AT)        //`
#define JP_PIPE LSFT(KC_INT3)     //|


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NOBIX] = LAYOUT( \
  //,-----------------------------------------------------|   |------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_T,    KC_R,    KC_X,        KC_J,    KC_U,    KC_I,    KC_P,    KC_V, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   MO(_EMACS),    KC_K,    KC_S,   MT_FD,    KC_N,    KC_G,        KC_L,    KC_A,   MT_FE,    KC_O,    KC_Y, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Z,    KC_H,    KC_C,    KC_M,    KC_B,     KC_MINS,    KC_F, KC_COMM,  KC_DOT, KC_SLSH,RCS_T(JP_PIPE),
  //|--------+--------+--------+--------+--------+--------/   \--------+--------+--------+---------+--------+--------'
                        KC_LCTL, KC_MHEN, MT_SSPC, KC_LGUI,     KC_RGUI, MT_NENT, KC_HENK,  KC_RALT
  //                  `--------+--------+--------+--------'   `--------+--------+--------+---------'
  ),

  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------|   |------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   MO(_EMACS),    KC_A,    KC_S,   MT_FD,    KC_F,   KC_G,         KC_H,    KC_J,   MT_FK,    KC_L, KC_SCLN, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT,KC_SLSH,RCS_T(JP_PIPE),
  //|--------+--------+--------+--------+--------+--------/   \--------+--------+--------+---------+--------+--------'
                        KC_LCTL, KC_MHEN, MT_SSPC, KC_LGUI,     KC_RGUI, MT_NENT, KC_HENK,  KC_RALT
  //                  `--------+--------+--------+--------'   `--------+--------+--------+---------'
  ),

  [_NMB] = LAYOUT( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       JP_GRV, KC_EXLM,   JP_AT, KC_HASH,  KC_DLR, KC_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN,  JP_EQL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_PLUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, JP_UNDS, KC_MINS, JP_LPRN, JP_LCBR, JP_LBRC,     JP_RBRC, JP_RCBR, JP_RPRN,  KC_DOT, KC_SLSH, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                        _______, _______,  KC_ENT, _______,     _______, _______, _______, RST_MOD
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_EMACS] = LAYOUT( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       MC_SRH, KC_PGDN, KC_PGUP,  KC_END, C(KC_A), XXXXXXX,     C(KC_V),S(KC_TAB), KC_TAB,   INS_L,  MC_PSC,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME,  KILL_L,  KC_DEL, C(KC_F), C(KC_H),     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_F2,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       MC_LCK, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y), KC_MS_BTN3,KC_ENT,S(KC_LEFT),S(KC_RGHT),C(KC_Z),  MC_MIN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                         MC_DTL,  MC_DTR, _______, _______,     _______, _______, _______, RST_MOD
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_FN] = LAYOUT( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_TAB, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,S(KC_TAB),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  A(KC_LEFT), KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,A(KC_RIGHT),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,RGB_TOG,RGB_MOD,RGB_HUI,RGB_SAI,RGB_VAI,   _______,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,DF(_EMACS),DF(_NOBIX),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                        _______, _______, _______, _______,     _______, _______, _______, RST_MOD
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),
};


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

void render_layer_state(void) {
  switch (get_highest_layer(layer_state)) {
    case _NOBIX:
      oled_write_ln_P(PSTR("Layer: NOBIX"), false);
      break;
    case _QWERTY:
      oled_write_ln_P(PSTR("Layer: QWERTY"),false);
      break;
    case _NMB:
      oled_write_ln_P(PSTR("Layer: Number"), false);
      break;
    case _EMACS:
      oled_write_ln_P(PSTR("Layer: Emacs"), false);
      break;
    case _FN:
      oled_write_ln_P(PSTR("Layer: Function"),false);
      break;
    default:
      oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }
}
/*
void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(logo, false);
}
*/
char keylog_str[24]  = {};
char keylogs_str[21] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // update keylogs
    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;
        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;
    keylogs_str_idx++;
}

const char *read_keylog(void) { return keylog_str; }
const char *read_keylogs(void) { return keylogs_str; }

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
    } else {
        //render_logo();
    }
}
#endif


static bool SHIFT_PRESSED = false;
static bool EXCEPTIONALY_SHIFT_PRESSED = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    #ifdef OLED_DRIVER_ENABLE
        set_keylog(keycode, record);
    #endif
  }

  switch (keycode) {
    case MT_SSPC:
      if(record->event.pressed){
        SHIFT_PRESSED = true;
      }else{
        SHIFT_PRESSED = false;
      }
    break;

    case KILL_L:
      if(record->event.pressed){
        SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT) SS_TAP(X_DEL));
      }
      return false;
      break;

    case INS_L:
      if(record->event.pressed){
        SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_ENT));
      }
      return false;
      break;

    case RST_MOD:
      if(record->event.pressed){
          clear_keyboard();
          layer_move(_QWERTY);
        }
      return false;
      break;

    default:
      if(SHIFT_PRESSED || EXCEPTIONALY_SHIFT_PRESSED){
        switch(keycode){
          case KC_MINS:
            if(record->event.pressed){
              register_code(KC_INT1);                 //If pressed "SHIFT" then "_"
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case KC_SCLN:
            if(record->event.pressed){
              unregister_code(KC_LSFT);
              register_code(KC_QUOT);               //If pressed "SHIFT" then ":"
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case JP_QUOT:
            if(record->event.pressed){
              register_code(KC_2);                //If pressed "SHIFT" then " " "
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case KC_ESC:
            if(record->event.pressed){
              register_code(KC_EQL);            //
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
            EXCEPTIONALY_SHIFT_PRESSED = false;
            }
            return false;
            break;

        }
      }
    }
  return true;
}
