<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Analog Devices ADP5589/ADP5585 I/O Expander and QWERTY Keypad Controller
 *
 * Copyright 2010-2011 Analog Devices Inc.
 */

#अगर_अघोषित _ADP5589_H
#घोषणा _ADP5589_H

/*
 * ADP5589 specअगरic GPI and Keymap defines
 */

#घोषणा ADP5589_KEYMAPSIZE	88

#घोषणा ADP5589_GPI_PIN_ROW0 97
#घोषणा ADP5589_GPI_PIN_ROW1 98
#घोषणा ADP5589_GPI_PIN_ROW2 99
#घोषणा ADP5589_GPI_PIN_ROW3 100
#घोषणा ADP5589_GPI_PIN_ROW4 101
#घोषणा ADP5589_GPI_PIN_ROW5 102
#घोषणा ADP5589_GPI_PIN_ROW6 103
#घोषणा ADP5589_GPI_PIN_ROW7 104
#घोषणा ADP5589_GPI_PIN_COL0 105
#घोषणा ADP5589_GPI_PIN_COL1 106
#घोषणा ADP5589_GPI_PIN_COL2 107
#घोषणा ADP5589_GPI_PIN_COL3 108
#घोषणा ADP5589_GPI_PIN_COL4 109
#घोषणा ADP5589_GPI_PIN_COL5 110
#घोषणा ADP5589_GPI_PIN_COL6 111
#घोषणा ADP5589_GPI_PIN_COL7 112
#घोषणा ADP5589_GPI_PIN_COL8 113
#घोषणा ADP5589_GPI_PIN_COL9 114
#घोषणा ADP5589_GPI_PIN_COL10 115
#घोषणा GPI_LOGIC1 116
#घोषणा GPI_LOGIC2 117

#घोषणा ADP5589_GPI_PIN_ROW_BASE ADP5589_GPI_PIN_ROW0
#घोषणा ADP5589_GPI_PIN_ROW_END ADP5589_GPI_PIN_ROW7
#घोषणा ADP5589_GPI_PIN_COL_BASE ADP5589_GPI_PIN_COL0
#घोषणा ADP5589_GPI_PIN_COL_END ADP5589_GPI_PIN_COL10

#घोषणा ADP5589_GPI_PIN_BASE ADP5589_GPI_PIN_ROW_BASE
#घोषणा ADP5589_GPI_PIN_END ADP5589_GPI_PIN_COL_END

#घोषणा ADP5589_GPIMAPSIZE_MAX (ADP5589_GPI_PIN_END - ADP5589_GPI_PIN_BASE + 1)

/*
 * ADP5585 specअगरic GPI and Keymap defines
 */

#घोषणा ADP5585_KEYMAPSIZE	30

#घोषणा ADP5585_GPI_PIN_ROW0 37
#घोषणा ADP5585_GPI_PIN_ROW1 38
#घोषणा ADP5585_GPI_PIN_ROW2 39
#घोषणा ADP5585_GPI_PIN_ROW3 40
#घोषणा ADP5585_GPI_PIN_ROW4 41
#घोषणा ADP5585_GPI_PIN_ROW5 42
#घोषणा ADP5585_GPI_PIN_COL0 43
#घोषणा ADP5585_GPI_PIN_COL1 44
#घोषणा ADP5585_GPI_PIN_COL2 45
#घोषणा ADP5585_GPI_PIN_COL3 46
#घोषणा ADP5585_GPI_PIN_COL4 47
#घोषणा GPI_LOGIC 48

#घोषणा ADP5585_GPI_PIN_ROW_BASE ADP5585_GPI_PIN_ROW0
#घोषणा ADP5585_GPI_PIN_ROW_END ADP5585_GPI_PIN_ROW5
#घोषणा ADP5585_GPI_PIN_COL_BASE ADP5585_GPI_PIN_COL0
#घोषणा ADP5585_GPI_PIN_COL_END ADP5585_GPI_PIN_COL4

#घोषणा ADP5585_GPI_PIN_BASE ADP5585_GPI_PIN_ROW_BASE
#घोषणा ADP5585_GPI_PIN_END ADP5585_GPI_PIN_COL_END

#घोषणा ADP5585_GPIMAPSIZE_MAX (ADP5585_GPI_PIN_END - ADP5585_GPI_PIN_BASE + 1)

काष्ठा adp5589_gpi_map अणु
	अचिन्हित लघु pin;
	अचिन्हित लघु sw_evt;
पूर्ण;

/* scan_cycle_समय */
#घोषणा ADP5589_SCAN_CYCLE_10ms		0
#घोषणा ADP5589_SCAN_CYCLE_20ms		1
#घोषणा ADP5589_SCAN_CYCLE_30ms		2
#घोषणा ADP5589_SCAN_CYCLE_40ms		3

/* RESET_CFG */
#घोषणा RESET_PULSE_WIDTH_500us		0
#घोषणा RESET_PULSE_WIDTH_1ms		1
#घोषणा RESET_PULSE_WIDTH_2ms		2
#घोषणा RESET_PULSE_WIDTH_10ms		3

#घोषणा RESET_TRIG_TIME_0ms		(0 << 2)
#घोषणा RESET_TRIG_TIME_1000ms		(1 << 2)
#घोषणा RESET_TRIG_TIME_1500ms		(2 << 2)
#घोषणा RESET_TRIG_TIME_2000ms		(3 << 2)
#घोषणा RESET_TRIG_TIME_2500ms		(4 << 2)
#घोषणा RESET_TRIG_TIME_3000ms		(5 << 2)
#घोषणा RESET_TRIG_TIME_3500ms		(6 << 2)
#घोषणा RESET_TRIG_TIME_4000ms		(7 << 2)

#घोषणा RESET_PASSTHRU_EN		(1 << 5)
#घोषणा RESET1_POL_HIGH			(1 << 6)
#घोषणा RESET1_POL_LOW			(0 << 6)
#घोषणा RESET2_POL_HIGH			(1 << 7)
#घोषणा RESET2_POL_LOW			(0 << 7)

/* ADP5589 Mask Bits:
 * C C C C C C C C C C C | R R R R R R R R
 * 1 9 8 7 6 5 4 3 2 1 0 | 7 6 5 4 3 2 1 0
 * 0
 * ---------------- BIT ------------------
 * 1 1 1 1 1 1 1 1 1 0 0 | 0 0 0 0 0 0 0 0
 * 8 7 6 5 4 3 2 1 0 9 8 | 7 6 5 4 3 2 1 0
 */

#घोषणा ADP_ROW(x)	(1 << (x))
#घोषणा ADP_COL(x)	(1 << (x + 8))
#घोषणा ADP5589_ROW_MASK		0xFF
#घोषणा ADP5589_COL_MASK		0xFF
#घोषणा ADP5589_COL_SHIFT		8
#घोषणा ADP5589_MAX_ROW_NUM		7
#घोषणा ADP5589_MAX_COL_NUM		10

/* ADP5585 Mask Bits:
 * C C C C C | R R R R R R
 * 4 3 2 1 0 | 5 4 3 2 1 0
 *
 * ---- BIT -- -----------
 * 1 0 0 0 0 | 0 0 0 0 0 0
 * 0 9 8 7 6 | 5 4 3 2 1 0
 */

#घोषणा ADP5585_ROW_MASK		0x3F
#घोषणा ADP5585_COL_MASK		0x1F
#घोषणा ADP5585_ROW_SHIFT		0
#घोषणा ADP5585_COL_SHIFT		6
#घोषणा ADP5585_MAX_ROW_NUM		5
#घोषणा ADP5585_MAX_COL_NUM		4

#घोषणा ADP5585_ROW(x)	(1 << ((x) & ADP5585_ROW_MASK))
#घोषणा ADP5585_COL(x)	(1 << (((x) & ADP5585_COL_MASK) + ADP5585_COL_SHIFT))

/* Put one of these काष्ठाures in i2c_board_info platक्रमm_data */

काष्ठा adp5589_kpad_platक्रमm_data अणु
	अचिन्हित keypad_en_mask;	/* Keypad (Rows/Columns) enable mask */
	स्थिर अचिन्हित लघु *keymap;	/* Poपूर्णांकer to keymap */
	अचिन्हित लघु keymapsize;	/* Keymap size */
	bool repeat;			/* Enable key repeat */
	bool en_keylock;		/* Enable key lock feature (ADP5589 only)*/
	अचिन्हित अक्षर unlock_key1;	/* Unlock Key 1 (ADP5589 only) */
	अचिन्हित अक्षर unlock_key2;	/* Unlock Key 2 (ADP5589 only) */
	अचिन्हित अक्षर unlock_समयr;	/* Time in seconds [0..7] between the two unlock keys 0=disable (ADP5589 only) */
	अचिन्हित अक्षर scan_cycle_समय;	/* Time between consecutive scan cycles */
	अचिन्हित अक्षर reset_cfg;	/* Reset config */
	अचिन्हित लघु reset1_key_1;	/* Reset Key 1 */
	अचिन्हित लघु reset1_key_2;	/* Reset Key 2 */
	अचिन्हित लघु reset1_key_3;	/* Reset Key 3 */
	अचिन्हित लघु reset2_key_1;	/* Reset Key 1 */
	अचिन्हित लघु reset2_key_2;	/* Reset Key 2 */
	अचिन्हित debounce_dis_mask;	/* Disable debounce mask */
	अचिन्हित pull_dis_mask;		/* Disable all pull resistors mask */
	अचिन्हित pullup_en_100k;	/* Pull-Up 100k Enable Mask */
	अचिन्हित pullup_en_300k;	/* Pull-Up 300k Enable Mask */
	अचिन्हित pullकरोwn_en_300k;	/* Pull-Down 300k Enable Mask */
	स्थिर काष्ठा adp5589_gpi_map *gpimap;
	अचिन्हित लघु gpimapsize;
	स्थिर काष्ठा adp5589_gpio_platक्रमm_data *gpio_data;
पूर्ण;

काष्ठा i2c_client; /* क्रमward declaration */

काष्ठा adp5589_gpio_platक्रमm_data अणु
	पूर्णांक	gpio_start;	/* GPIO Chip base # */
पूर्ण;

#पूर्ण_अगर
