# Temper 36 — Miryoku ZMK (GitHub Actions)

Firmware ZMK para Temper 36 (nice!nano v2, display **nice!view**) con layout [Miryoku](https://github.com/manna-harbour/miryoku_zmk), compilado automáticamente por GitHub Actions. No necesitas descargar ZMK, Zephyr ni el toolbox: solo subes este repo y GitHub compila los `.uf2`.

## Cómo funciona

El workflow `.github/workflows/build.yml` llama al build oficial de ZMK (`build-user-config.yml@v0.3`), que corre en un contenedor con la toolchain completa. Los shields se descubren así:

- `boards/shields/temper/` — definición del teclado Temper 36 (vendida desde [raeedcho/temper-zmk-config](https://github.com/raeedcho/temper-zmk-config)), cargada como módulo vía `zephyr/module.yml`.
- `nice_view_adapter` y `nice_view` — shields integrados en el propio ZMK.
- `config/` — keymap Miryoku, Kconfig y tweaks de display (al final del keymap).

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
    ├── temper.keymap             # Keymap (includes Miryoku + tweaks nice!view)
    ├── temper.conf               # Kconfig nice!view
    └── miryoku/                  # Motor Miryoku + customizaciones
```

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
