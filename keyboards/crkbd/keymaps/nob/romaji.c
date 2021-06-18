#include <string.h>

#define ROMA(X) _romaji_##X

enum Romaji {
    ROMA(_A) = 0,
    ROMA(_I),
    ROMA(_U),
    ROMA(_E),
    ROMA(_O),
    ROMA(_Y),
    ROMA(_H),

    ROMA(_SLASH),
    ROMA(_NN),
    ROMA(_MACRON),
    ROMA(_SHIFT),
    ROMA(_ARRAY_SIZE)
};

bool ROMA(mode) = false;
static bool ROMA(press)[ROMA(_ARRAY_SIZE)];
static uint16_t ROMA(press_cnt) = 0;
static uint16_t ROMA(consonants) = 0;
static uint16_t ROMA(time_max) = ROMAJI_TERM;
static uint16_t ROMA(time_start) = 0;

static int romaji_key_idx(uint16_t keycode) {
    switch(keycode) {
        case KC_A:     return ROMA(_A);
        case KC_I:     return ROMA(_I);
        case KC_U:     return ROMA(_U);
        case KC_E:     return ROMA(_E);
        case KC_O:     return ROMA(_O);
        case KC_Y:     return ROMA(_Y);
        case KC_H:     return ROMA(_H);
        case KC_SPACE: return ROMA(_NN);
        case KC_LSHIFT:  return ROMA(_SHIFT);
        case KC_RSHIFT:  return ROMA(_SHIFT);
        case KC_MINS:    return ROMA(_MACRON);
        case KC_SLASH:   return ROMA(_SLASH);
        default:       return -1;
    }
}

static bool set_flg(uint16_t keycode) {
    static const bool pressed = true;

    int rmkidx = romaji_key_idx(keycode);
    if(rmkidx != -1) {
        ROMA(press)[rmkidx] |= pressed;
        return true;
    }

    if(pressed) {
        if(ROMA(consonants))
            return false;

        ROMA(consonants) = keycode;
    }
    return true;
}

static void romaji_clear(void) {
    ROMA(consonants) = 0;
    //memset( ROMA(press)     ,0,sizeof(bool)*ROMA(_Y) );
    memset( ROMA(press)     ,0,sizeof(bool)*ROMA(_ARRAY_SIZE) );
}

void romaji_reset(void) {
    ROMA(press_cnt) = 0;
    romaji_clear();
    memset( ROMA(press)     ,0,sizeof(bool)*ROMA(_ARRAY_SIZE) );
}


static inline bool check_pressed(uint16_t kidx) {
    return ROMA(press)[kidx];
}
static inline bool is_lower(char ch) {
    return 'a' <= ch && ch <= 'z';
}
static inline char to_lower(char ch) {
    if( is_lower(ch) )
        return ch;
    else
        return ch - 'A' + 'a';
}
//                                   "abcdefghijklmnopqrstuvwxyz";
static const char* ROMA(shifted_chrs) = "     p b  g  N b  zd      ";

static void romaji_flush(void) {
    char buf[16];
    char*p = buf;
    char ch = 0;
    bool fshift = check_pressed( ROMA(_SHIFT) );
    if( ROMA(consonants) == 0 ) {
        if( check_pressed( ROMA(_H) ) ) {
            ROMA(consonants) = KC_H;
            ROMA(press)[ ROMA(_H)  ] = false;
        }
    }
    if( ROMA(consonants) != 0 ) {
        if( fshift  ) {
            ch = ROMA(shifted_chrs)[ ROMA(consonants) - KC_A ];
        }
        else {
            ch = (char)( ROMA(consonants) - KC_A + 'a');
        }
        *p++ = to_lower(ch);
        if( ! is_lower(ch) )
            *p++ = to_lower(ch);
    }
    if( check_pressed( ROMA(_H) ) )    *p++ = 'h';
    if( check_pressed( ROMA(_Y) ) )    *p++ = 'y';
    if( check_pressed( ROMA(_A) ) )    *p++ = 'a';
    if( check_pressed( ROMA(_O) ) )    *p++ = 'o';
    if( check_pressed( ROMA(_U) ) )    *p++ = 'u';
    if( check_pressed( ROMA(_E) ) )    *p++ = 'e';
    if( check_pressed( ROMA(_I) ) )    *p++ = 'i';
    if( check_pressed( ROMA(_MACRON) ) )    *p++ = '-';
    if( check_pressed( ROMA(_SLASH) ) ) {
        if( fshift )
            *p++ = '?';
        else
            *p++ = '/';
    }
    if( check_pressed( ROMA(_NN) ) ) {
        if( buf == p )
            *p++ = ' ';
        else {
            *p++ = 'n';
            *p++ = 'n';
        }
    }
    if( fshift && (buf == p - 1) && (buf[0] == 'n') )
        *p++ = ch;

    if(buf != p) {
        *p++ = 0;
        send_string(buf);
    }

    romaji_clear();
}

static uint16_t elapsed_time(uint16_t a,uint16_t b) {
    if( a > b )
        return a - b;
    else
        return (uint16_t)( ((uint32_t)a) + 65535 - b);
}

static void romaji_mod(uint16_t keycode,bool pressed) {
    if (pressed) {
        set_flg(keycode);
    }
    else {
        if( ROMA(press_cnt) == 0 ) {
            romaji_flush();
        }
    }
}

static void romaji_key(uint16_t keycode,bool pressed) {
    if (pressed) {
        uint16_t now = timer_read();
        if( ROMA(press_cnt) == 0 ) {
            ROMA(time_start) = now;
        }
        else {
            if( elapsed_time(now,ROMA(time_start)) > ROMA(time_max) ) {
                ROMA(time_start) = now;
                romaji_flush();
            }
        }

        ROMA(press_cnt)++;
        if( ! set_flg(keycode) )
        {
            romaji_flush();
            set_flg(keycode);
        }
    }
    else {
        ROMA(press_cnt)--;
        if( ROMA(press_cnt) == 0 )
            romaji_flush();
    }
}

static void romaji_change_param(uint16_t id,int16_t val) {
    int32_t v = ROMA(time_max);
    v += val*5;
    if(v<0)    v = 0;
    if(v>200)   v = 200;
    ROMA(time_max) = (uint16_t)v;
}

static void romaji_report_param(void) {
    char buf[20];
    snprintf(buf,sizeof(buf),"time:%d\n",ROMA(time_max));
    send_string(buf);
}


bool process_romaji(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case REPORT_PARAM:
                romaji_report_param();
                return false;
            case INC_PARAM:
              romaji_change_param(0,1);
              return false;
            case DEC_PARAM:
              romaji_change_param(0,-1);
              return false;
        }
    }


    if( _romaji_mode ) {
        bool f = (KC_A <= keycode && keycode <= KC_Z);
        bool fmod = false;
        if( !f ) {
            switch(keycode) {
                case KC_SPACE:
                case KC_MINS:
                case KC_SLASH:
                case KC_LSHIFT:
                case KC_RSHIFT:
                    f = fmod = true;
                    break;
            }
        }
        // ローマ字と関係ない文字ならフラッシュ
        if( !f ) {
            if(record->event.pressed) {
                if( ROMA(press_cnt) != 0 )
                    romaji_flush();
                romaji_clear();
            }
            return true;
        }

        if( f ) {
            if( fmod )
                romaji_mod(keycode,record->event.pressed);
            else
                romaji_key(keycode,record->event.pressed);

            return false;
        }
    }

    return true;
}


#undef G

