#include "d48tr.h"
//#include "action_layer.h"
//#include "eeconfig.h"
//#include <print.h>
#include "trackball.c"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _HRMNY = 0,
    _QWERTY,
    _NMB,
    _EMACS,
    _META,
    _FN,
};

//Declare custum keyCodes
enum custom_keycodes {
    INS_L = SAFE_RANGE,         //Insert Line
    KILL_L,                     //Kill Line
    SND_ID,                     //Send ID
    RST_MOD,                    //Reset Modefier Key
    MS_L,                       //MS_BOTTON1
    MS_R,                       //MS_BOTTON2
};

//Alias
#define MT_MT LT(_META,KC_TAB)    //hold:"META" tap:"tab"
#define MT_SS LSFT_T(KC_SPC)      //hold:"Shift" tap:"Space"
#define MT_NE LT(_NMB,KC_ENT)     //hold:"NMB" tap:"Enter"
#define MT_FT LT(_FN,KC_T)        //hold:"Function" tap:"T"
#define MT_FE LT(_FN,KC_E)        //hold:"Function" tap:"E"
#define MT_FK LT(_FN,KC_K)        //hold:"Function" tap:"k"
#define MT_FD LT(_FN,KC_D)        //hold:"Function" tap:"D"

#define MC_PSC G(S(KC_S))         //Print screen
#define MC_DTR G(C(KC_RIGHT))     //Desk top move right
#define MC_DTL G(C(KC_LEFT))      //Desk top move left
#define MC_LCK G(KC_L)            //Screen Lock
#define MC_MIN G(KC_M)            //Window Minimize
#define MC_SRH G(KC_S)            //Search
#define MC_MAX G(KC_UP)           //Window Maxmize

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

 [_HRMNY] = KEYMAP(
  //,-----------------------------------------------------|   |------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_D,    KC_R,    KC_G,        KC_J,    KC_U,    KC_I,    KC_V,    KC_P, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   MO(_EMACS),    KC_K,    KC_S,   MT_FT,    KC_N,    KC_M,        KC_L,    KC_A,   MT_FE,    KC_O,    KC_Y, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MT_MT,    KC_Z,    KC_X,    KC_C,    KC_H,    KC_B,     KC_MINS,    KC_F, KC_COMM,  KC_DOT, KC_SLSH, RCS_T(JP_PIPE),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LALT, KC_LCTL, KC_MHEN,   MT_SS, XXXXXXX,     XXXXXXX,   MT_NE, KC_HENK, KC_RALT, KC_RGUI, KC_RSFT
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),

 [_QWERTY] = KEYMAP(
  //,-----------------------------------------------------|   |------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   MO(_EMACS),    KC_A,    KC_S,   MT_FD,    KC_F,   KC_G,         KC_H,    KC_J,   MT_FK,    KC_L, KC_SCLN, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MT_MT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, RCS_T(JP_PIPE),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LALT, KC_LCTL, KC_MHEN,   MT_SS, XXXXXXX,     XXXXXXX,   MT_NE, KC_HENK, KC_RALT, KC_RGUI, KC_RSFT
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),


[_NMB] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       JP_GRV, KC_EXLM,   JP_AT, KC_HASH,  KC_DLR, KC_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN,  JP_EQL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, JP_PLUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, JP_UNDS, KC_MINS, JP_LPRN, JP_LCBR, JP_LBRC,     JP_RBRC, JP_LCBR, JP_RPRN,  KC_DOT, KC_JYEN, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
  //|-----------------------------------------------------|   |-----------------------------------------------------'
 ),

  [_EMACS] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       MC_SRH, C(KC_A), C(KC_X),  KC_END, KC_PGDN, KC_PGUP,     C(KC_V),S(KC_TAB), KC_TAB,   INS_L,  MC_PSC,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME,  KILL_L,  KC_DEL, C(KC_F), C(KC_H),     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_F2,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,  MC_MAX, C(KC_Y), C(KC_C),  MC_DTL,  MC_DTR,  KC_MS_BTN3,KC_ENT,S(KC_LEFT),S(KC_RGHT),C(KC_Z), MC_MIN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),

  [_META] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      SND_ID,_______,_______,C(KC_END),C(KC_PGDN),C(KC_PGUP),   C(KC_V), _______,S(KC_TAB),DF(_QWERTY),DF(_HRMNY),_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
    _______,C(KC_HOME),_______,C(KC_DEL), C(KC_F),C(KC_H), C(KC_BSPC),C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, C(KC_Y), C(KC_C),  MC_DTL,  MC_DTR,  KC_MS_BTN3,  KC_ENT, _______, _______, C(KC_Z), _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
  //|-----------------------------------------------------|   |-----------------------------------------------------'
 ),

[_FN] = KEYMAP(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   MO(_QWERTY),  KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  A(KC_LEFT), KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,A(KC_RGHT),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
    MO(_META),  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,     _______,    MS_L,KC_MS_BTN3,  MS_R, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      RST_MOD, _______, _______, _______, _______, _______,     _______, _______,_______, _______, _______, RST_MOD
  //|-----------------------------------------------------|   |-----------------------------------------------------'
  ),
};

static bool SHIFT_PRESSED = false;
static bool EXCEPTIONALY_SHIFT_PRESSED = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case MT_SS:
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

    case SND_ID:
      if(record->event.pressed){
        SEND_STRING("aaa031963"SS_TAP(X_TAB));
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

    case MS_L:
      if (record->event.pressed) {
        mouse_btn1 = true;
      } else {
        mouse_btn1 = false;
      }
      return false;
      break;

    case MS_R:
      if (record->event.pressed) {
        mouse_btn2 = true;
      } else {
        mouse_btn2 = false;
      }
      return false;
      break;

    default:
      if(SHIFT_PRESSED || EXCEPTIONALY_SHIFT_PRESSED){
        switch(keycode){
          case KC_MINS:
            if(record->event.pressed){
              register_code(KC_INT1);
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
              register_code(KC_QUOT);
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
              register_code(KC_2);
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
              register_code(KC_EQL);
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
