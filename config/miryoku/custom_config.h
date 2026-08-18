// Copyright 2024 Manna Harbour
// https://github.com/manna-harbour/miryoku
//
// Temper 36 — Miryoku config (matches Corne41):
//   QWERTY alphas, VI nav (HJKL), Mac clipboard
//   Thumbs: Media/Esc (outer), Mouse/Tab (middle), Nav/Spc (inner)
//   Sym layer: morph_euro (*/€), td_bang (!/¡), morph_enye (ñ/Ñ), RA(FSLH) (¿)

// ─────────────────────────────────────────────
// 0. Miryoku options
// ─────────────────────────────────────────────
#define MIRYOKU_ALPHAS_QWERTY
#define MIRYOKU_NAV_VI
#define MIRYOKU_CLIPBOARD_MAC
#undef MIRYOKU_KLUDGE_THUMBCOMBOS

// ─────────────────────────────────────────────
// 1. Base layer: custom thumb assignments
//    (QWERTY, non-flip — only thumb row differs from stock)
// ─────────────────────────────────────────────
#undef MIRYOKU_LAYER_BASE
#define MIRYOKU_LAYER_BASE \
&kp Q,             &kp W,             &kp E,             &kp R,             &kp T,             &kp Y,             &kp U,             &kp I,             &kp O,             &kp P,             \
&u_mt_left LGUI A,  &u_mt_left LALT S,  &u_mt_left LCTRL D, &u_mt_left LSHFT F, &kp G,             &kp H,             &u_mt_right LSHFT J,&u_mt_right LCTRL K,&u_mt_right LALT L, &u_mt_right LGUI SQT,\
U_LT(U_BUTTON, Z), &u_mt_left RALT X,  &kp C,             &kp V,             &kp B,             &kp N,             &kp M,             &kp COMMA,         &u_mt_right RALT DOT,U_LT(U_BUTTON, SLASH),\
U_NP,              U_NP,              U_LT(U_MEDIA, ESC),U_LT(U_MOUSE, TAB), U_LT(U_NAV, SPACE),U_LT(U_SYM, RET),   U_LT(U_NUM, BSPC),  U_LT(U_FUN, DEL),  U_NP,              U_NP

// ─────────────────────────────────────────────
// 2. Sym layer: custom chars (ñ, ¿, €, ¡)
//    (non-flip — adds morph_enye at K25, RA(FSLH) at K29)
// ─────────────────────────────────────────────
#undef MIRYOKU_LAYER_SYM
#define MIRYOKU_LAYER_SYM \
&kp LBRC,          &kp AMPS,          &morph_euro,       &kp LPAR,          &kp RBRC,          U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,     &u_to_U_TAP,       U_BOOT,            \
&kp COLON,         &kp DLLR,          &kp PRCNT,         &kp CARET,         &kp PLUS,          U_NA,              &kp LSHFT,         &kp LCTRL,         &kp LALT,          &kp LGUI,          \
&kp TILDE,         &td_bang,          &kp AT,            &kp HASH,          &kp PIPE,          &morph_enye,       &u_to_U_SYM,       &u_to_U_MOUSE,     &kp RALT,          &kp RA(FSLH),      \
U_NP,              U_NP,              &kp LPAR,          &kp RPAR,          &kp UNDER,         U_NA,              U_NA,              U_NA,              U_NP,              U_NP
