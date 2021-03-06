#include <string.h>

#define GI(X) _romaji_##X

enum Romaji {
    GI(_A) = 0,
    GI(_I),
    GI(_U),
    GI(_E),
    GI(_O),
    GI(_Y),
    GI(_H),

    GI(_SLASH),
    GI(_NN),
    GI(_MACRON),
    GI(_SHIFT),
    GI(_ARRAY_SIZE)
};

bool GI(mode) = false;
static bool GI(press)[GI(_ARRAY_SIZE)];
static uint16_t GI(press_cnt) = 0;
static uint16_t GI(consonants) = 0;
static uint16_t GI(time_max) = ROMAJI_TERM;
static uint16_t GI(time_start) = 0;

static int romaji_key_idx(uint16_t keycode) {
    switch(keycode) {
        case KC_A:     return GI(_A);
        case KC_I:     return GI(_I);
        case KC_U:     return GI(_U);
        case KC_E:     return GI(_E);
        case KC_O:     return GI(_O);
        case KC_Y:     return GI(_Y);
        case KC_H:     return GI(_H);
        case KC_SPACE: return GI(_NN);
        case KC_LSHIFT:  return GI(_SHIFT);
        case KC_RSHIFT:  return GI(_SHIFT);
        case KC_MINS:    return GI(_MACRON);
        case KC_SLASH:   return GI(_SLASH);
        default:       return -1;
    }
}

static bool set_flGI(uint16_t keycode) {
    static const bool pressed = true;

    int rmkidx = romaji_key_idx(keycode);
    if(rmkidx != -1) {
        GI(press)[rmkidx] |= pressed;
        return true;
    }

    if(pressed) {
        if(GI(consonants))
            return false;

        GI(consonants) = keycode;
    }
    return true;
}

static void romaji_clear(void) {
    GI(consonants) = 0;
    //memset( GI(press)     ,0,sizeof(bool)*GI(_Y) );
    memset( GI(press)     ,0,sizeof(bool)*GI(_ARRAY_SIZE) );
}

void romaji_reset(void) {
    GI(press_cnt) = 0;
    romaji_clear();
    memset( GI(press)     ,0,sizeof(bool)*GI(_ARRAY_SIZE) );
}


static inline bool check_pressed(uint16_t kidx) {
    return GI(press)[kidx];
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
static const char* GI(shifted_chrs) = "     p b  g  N b  zd      ";

static void romaji_flush(void) {
    char buf[16];
    char*p = buf;
    char ch = 0;
    bool fshift = check_pressed( GI(_SHIFT) );
    if( GI(consonants) == 0 ) {
        if( check_pressed( GI(_H) ) ) {
            GI(consonants) = KC_H;
            GI(press)[ GI(_H)  ] = false;
        }
    }
    if( GI(consonants) != 0 ) {
        if( fshift  ) {
            ch = GI(shifted_chrs)[ GI(consonants) - KC_A ];
        }
        else {
            ch = (char)( GI(consonants) - KC_A + 'a');
        }
        *p++ = to_lower(ch);
        if( ! is_lower(ch) )
            *p++ = to_lower(ch);
    }
    if( check_pressed( GI(_H) ) )    *p++ = 'h';
    if( check_pressed( GI(_Y) ) )    *p++ = 'y';
    if( check_pressed( GI(_A) ) )    *p++ = 'a';
    if( check_pressed( GI(_O) ) )    *p++ = 'o';
    if( check_pressed( GI(_U) ) )    *p++ = 'u';
    if( check_pressed( GI(_E) ) )    *p++ = 'e';
    if( check_pressed( GI(_I) ) )    *p++ = 'i';
    if( check_pressed( GI(_MACRON) ) )    *p++ = '-';
    if( check_pressed( GI(_SLASH) ) ) {
        if( fshift )
            *p++ = '?';
        else
            *p++ = '/';
    }
    if( check_pressed( GI(_NN) ) ) {
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
        set_flGI(keycode);
    }
    else {
        if( GI(press_cnt) == 0 ) {
            romaji_flush();
        }
    }
}

static void romaji_key(uint16_t keycode,bool pressed) {
    if (pressed) {
        uint16_t now = timer_read();
        if( GI(press_cnt) == 0 ) {
            GI(time_start) = now;
        }
        else {
            if( elapsed_time(now,GI(time_start)) > GI(time_max) ) {
                GI(time_start) = now;
                romaji_flush();
            }
        }

        GI(press_cnt)++;
        if( ! set_flGI(keycode) )
        {
            romaji_flush();
            set_flGI(keycode);
        }
    }
    else {
        GI(press_cnt)--;
        if( GI(press_cnt) == 0 )
            romaji_flush();
    }
}

static void romaji_change_param(uint16_t id,int16_t val) {
    int32_t v = GI(time_max);
    v += val*5;
    if(v<0)    v = 0;
    if(v>200)   v = 200;
    GI(time_max) = (uint16_t)v;
}

static void romaji_report_param(void) {
    char buf[20];
    snprintf(buf,sizeof(buf),"time:%d\n",GI(time_max));
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
                if( GI(press_cnt) != 0 )
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

