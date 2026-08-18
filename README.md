# Temper 36 — Miryoku ZMK (GitHub Actions)

Firmware ZMK para Temper 36 (nice!nano v2, display **nice!view**) con layout [Miryoku](https://github.com/manna-harbour/miryoku_zmk), compilado automáticamente por GitHub Actions. No necesitas descargar ZMK, Zephyr ni el toolbox: solo subes este repo y GitHub compila los `.uf2`.

## Cómo funciona

El workflow `.github/workflows/build.yml` llama al build oficial de ZMK (`build-user-config.yml@v0.3`), que corre en un contenedor con la toolchain completa. Los shields se descubren así:

- `boards/shields/temper/` — definición del teclado Temper 36 (vendida desde [raeedcho/temper-zmk-config](https://github.com/raeedcho/temper-zmk-config)), cargada como módulo vía `zephyr/module.yml`.
- `nice_view_adapter` y `nice_view` — shields integrados en el propio ZMK.
- `config/` — keymap Miryoku, Kconfig y tweaks de display (comentados al final del keymap).

Cada build combina los tres shields: `temper_left/right + nice_view_adapter + nice_view`.

## Estructura

```
zmk-config/
├── .github/workflows/build.yml   # Workflow: build-user-config.yml@v0.3
├── build.yaml                    # Matriz de builds (left + right)
├── zephyr/module.yml             # Declara el repo como módulo (board_root)
├── boards/shields/temper/        # Definición del shield Temper 36
└── config/
    ├── west.yml                  # Manifiesto: ZMK v0.3
    ├── temper.keymap             # Keymap (includes Miryoku; tweaks nice!view comentados)
    ├── temper.conf               # Kconfig nice!view
    └── miryoku/                  # Motor Miryoku + customizaciones
```

## Variaciones respecto a Miryoku por defecto

Parte del layout Miryoku estándar (36 teclas: 3×5 + 3 thumbs; capas Base, Extra, Tap, Button, Nav, Mouse, Media, Num, Sym, Fun). Cambios sobre el stock:

| Variación | Detalle | Implementación |
|-----------|---------|----------------|
| **Pulgares: Espacio ↔ Tab** | Miryoku stock: pulgar **medio** izquierdo = hold Nav, tap **SPACE**; pulgar **interior** izquierdo = hold Mouse, tap **TAB**. Aquí están intercambiados: medio = hold Mouse, tap **TAB**; interior = hold Nav, tap **SPACE**. El intercambio es consistente a todos los niveles (tap y capa del hold) | `MIRYOKU_LAYER_BASE` en `miryoku/custom_config.h` |
| **Navegación VI** | Miryoku por defecto pone las flechas en la home row (LEFT/DOWN/UP/RIGHT con caps word a la izquierda); la variante VI las coloca en las posiciones J/K/L/; (estilo vim, con caps word al final) y reordena Home/PgDn/PgUp/End/Ins en la fila inferior. También activa las variantes `_VI` de las capas Mouse y Media | `MIRYOKU_NAV_VI` |
| **Alfas QWERTY** | Miryoku por defecto usa Colemak DHm; aquí las alfas son QWERTY | `MIRYOKU_ALPHAS_QWERTY` en `miryoku/custom_config.h` |
| **Clipboard Mac** | Copiar/pegar/cortar/deshacer con ⌘ (⌘C/⌘V/⌘X/⌘Z, rehacer ⌘⇧Z). Por defecto Miryoku usa X11 (Ctrl+Insert) | `MIRYOKU_CLIPBOARD_MAC` |
| **Home row mods posicionales** | A/;→LGUI, S/L→LALT, D/K→LCTRL, F/J→LSHFT, X/.→RALT. Los mods de una mano solo se activan al pulsar teclas de la **mano opuesta** o los thumbs (same-hand prevention). Flavor `balanced`, tapping-term **280ms** (stock 200ms), prior-idle 150ms y `hold-trigger-on-release` (permite combinar mods de la misma mano, p. ej. Ctrl+Shift) | `u_mt_left` / `u_mt_right` en `miryoku/custom_behaviors.dtsi` |
| **Capa Sym con caracteres españoles** | `ñ`/`Ñ` en su tecla (K25); `€` = Shift+`*`; `¡` = doble tap de `!`; `¿` = tecla dedicada (K29). Vía US International (Right Alt + N/5/1) | `MIRYOKU_LAYER_SYM` en `custom_config.h`; `morph_enye`, `morph_euro`, `td_bang` en `custom_behaviors.dtsi` |
| **Bootloader en Sym** | Capa Sym → tecla **P** (fila superior derecha) reinicia en modo bootloader | `U_BOOT` en `MIRYOKU_LAYER_SYM` |
| **Kludge thumbcombos desactivado** | Comportamiento de combinaciones de pulgares estándar (sin el kludge) | `#undef MIRYOKU_KLUDGE_THUMBCOMBOS` |

Sin cambios respecto al stock (confirmado): pulgar exterior izquierdo (Media/Esc) y pulgares derechos (Sym/Ret, Num/Bspc, Fun/Del), capa Fun con perfiles Bluetooth (Z/X/C/V → BT 0-3, pairing con hold DEL + Shift + Z), capas Num/Mouse/Media y parámetros de mouse keys (1250/100, exponente 1, timings 1500/5000ms).

## Uso

### 1. Subir a GitHub

1. Crea un repo nuevo en GitHub (público o privado). Si lo llamas `zmk-config`, GitHub lo reconoce como repo de configuración ZMK.
2. Sube el contenido de esta carpeta (o `git init` dentro y push):

```bash
cd zmk-config
git init
git add .
git commit -m "Temper 36 Miryoku ZMK"
git branch -M main
git remote add origin git@github.com:<TU_USUARIO>/<TU_REPO>.git
git push -u origin main
```

### 2. Compilar

El push dispara el workflow automáticamente. También puedes re-ejecutarlo manualmente en **Actions → build firmware → Run workflow**.

Se compilan dos firmware en paralelo:

| Artifact | Lado |
|----------|------|
| `temper_left-nice_nano_v2-nice_view.uf2` | Izquierdo |
| `temper_right-nice_nano_v2-nice_view.uf2` | Derecho |

Baja ambos desde **Actions → run más reciente → Artifacts → `firmware`** (zip).

### 3. Flashear

1. Conecta un nice!nano por USB.
2. Doble tap rápido en RESET → aparece la unidad `NICENANO`.
3. Copia el `.uf2` correspondiente (macOS):

```bash
cp -X temper_left-nice_nano_v2-nice_view.uf2 /Volumes/NICENANO/ && sync
```

4. Repite con el otro lado.

### 4. Emparejamiento Bluetooth

1. Enciende el lado izquierdo (central).
2. **Hold DEL + Shift + Z** → limpia el vínculo y entra en pairing (LED azul parpadea).
3. Busca "Temper" en el Bluetooth del ordenador.
4. Enciende el lado derecho — se conecta al central automáticamente.

## Editar capas / comportamiento

Todo lo relevante vive en `config/miryoku/`:

| Archivo | Qué controla |
|---------|--------------|
| `config/miryoku/custom_config.h` | Capas, thumb, opciones (U_BASE, U_NAV, etc.) |
| `config/miryoku/custom_behaviors.dtsi` | Behaviors custom (tap-dance, hold-tap posicional…) |
| `config/temper.keymap` | Mapping físico (incluye `mapping/36/minidox.h`) |

Tras editar, haz push → GitHub recompila en ~10 min → descarga el nuevo `firmware` artifact.

## Notas

- ZMK está fijado a la rama `v0.3` en `config/west.yml`. Para cambiar de versión, edita `revision` ahí y en `@v0.3` del workflow.
- El shield `temper` está copiado (vendido) en este repo, no se descarga de internet en cada build. Para actualizarlo, copia de nuevo `boards/shields/temper` desde [raeedcho/temper-zmk-config](https://github.com/raeedcho/temper-zmk-config).
- Variante OLED (`nice!oled` + módulo `zmk-nice-oled`) no incluida: este repo compila solo con nice!view.
