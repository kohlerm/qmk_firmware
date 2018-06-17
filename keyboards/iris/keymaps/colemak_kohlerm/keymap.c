#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_SPCCTL CTL_T(KC_SPACE)
#define KC_TAB3 LT(1,KC_TAB)
#define KC_SFT_GRAVE SFT_T(KC_GRAVE)
#define KC_SFT_T SFT_T(KC_NO)
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,MINUS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J , L  , U  , Y  , SCOLON  ,BSLASH ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RASE, A  , R  , S  , T  , D  ,                H  , N  , E  , I  ,O,ENTER,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  SFT_T, Z  , X  , C  , V  , B  , APP ,     LGUI , K  , M  ,COMM,DOT ,SLSH,QUOTE,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LOWR,SPCCTL ,         SPCCTL ,SFT_T,RALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RST ,    ,    ,    ,    ,LPRN,               RPRN ,    , MS_UP   ,    ,   ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     DEL ,    ,MS_BTN3,MS_BTN2, MS_BTN1 ,LBRC,               RBRC, MS_LEFT , MS_DOWN , MS_RIGHT ,PLUS,PIPE,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,DOWN,LCBR,    ,         ,RCBR, P1 , P2 , P3 ,MINS,SFT_GRAVE    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,  ,         DEL ,    , P0
  //                  `----+----+----'        `----+----+----'
  ),
 [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.                   ,----+----+----+----+----+----.
     RST , F1 , F2 , F3 , F4 , F5 ,                    F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|                   |----+----+----+----+----+----|
         ,ESC, MS_WH_UP ,WWW_BACK,WWW_FORWARD ,MS_UP,    PGUP,HOME,UP,END,DELETE,    ,
  //|----+----+----+----+----+----|                   |----+----+----+----+----+----|
         ,LALT, MS_WH_DOWN ,LSHIFT,LCTL,MS_DOWN,          PGDOWN ,LEFT,DOWN ,RIGHT    , BSPC, ,
  //|----+----+----+----+----+----+----.              ,----|----+----+----+----+----+----|
     MUTE,MSTP,MPLY,VOLD,PGDN,MINS,    ,                    ,PLUS,END ,    ,    , QUOTE , EQUAL   ,
  //`----+----+----+--+-+----+----+----/               \----+----+----+----+----+----+----'
                           ,    ,    ,                   ,    ,
  //                  `----+----+----'                 `----+----+----'
  ),

 

  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RTOG,RMOD,RHUI,RSAI,RVAI,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,DBUG,RHUD,RSAD,RVAD,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     BL_S,RST ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
