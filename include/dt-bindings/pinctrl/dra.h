<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This header provides स्थिरants क्रम DRA pinctrl bindings.
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * Author: Rajendra Nayak <rnayak@ti.com>
 */

#अगर_अघोषित _DT_BINDINGS_PINCTRL_DRA_H
#घोषणा _DT_BINDINGS_PINCTRL_DRA_H

/* DRA7 mux mode options क्रम each pin. See TRM क्रम options */
#घोषणा MUX_MODE0	0x0
#घोषणा MUX_MODE1	0x1
#घोषणा MUX_MODE2	0x2
#घोषणा MUX_MODE3	0x3
#घोषणा MUX_MODE4	0x4
#घोषणा MUX_MODE5	0x5
#घोषणा MUX_MODE6	0x6
#घोषणा MUX_MODE7	0x7
#घोषणा MUX_MODE8	0x8
#घोषणा MUX_MODE9	0x9
#घोषणा MUX_MODE10	0xa
#घोषणा MUX_MODE11	0xb
#घोषणा MUX_MODE12	0xc
#घोषणा MUX_MODE13	0xd
#घोषणा MUX_MODE14	0xe
#घोषणा MUX_MODE15	0xf

/* Certain pins need भव mode, but note: they may glitch */
#घोषणा MUX_VIRTUAL_MODE0	(MODE_SELECT | (0x0 << 4))
#घोषणा MUX_VIRTUAL_MODE1	(MODE_SELECT | (0x1 << 4))
#घोषणा MUX_VIRTUAL_MODE2	(MODE_SELECT | (0x2 << 4))
#घोषणा MUX_VIRTUAL_MODE3	(MODE_SELECT | (0x3 << 4))
#घोषणा MUX_VIRTUAL_MODE4	(MODE_SELECT | (0x4 << 4))
#घोषणा MUX_VIRTUAL_MODE5	(MODE_SELECT | (0x5 << 4))
#घोषणा MUX_VIRTUAL_MODE6	(MODE_SELECT | (0x6 << 4))
#घोषणा MUX_VIRTUAL_MODE7	(MODE_SELECT | (0x7 << 4))
#घोषणा MUX_VIRTUAL_MODE8	(MODE_SELECT | (0x8 << 4))
#घोषणा MUX_VIRTUAL_MODE9	(MODE_SELECT | (0x9 << 4))
#घोषणा MUX_VIRTUAL_MODE10	(MODE_SELECT | (0xa << 4))
#घोषणा MUX_VIRTUAL_MODE11	(MODE_SELECT | (0xb << 4))
#घोषणा MUX_VIRTUAL_MODE12	(MODE_SELECT | (0xc << 4))
#घोषणा MUX_VIRTUAL_MODE13	(MODE_SELECT | (0xd << 4))
#घोषणा MUX_VIRTUAL_MODE14	(MODE_SELECT | (0xe << 4))
#घोषणा MUX_VIRTUAL_MODE15	(MODE_SELECT | (0xf << 4))

#घोषणा MODE_SELECT		(1 << 8)

#घोषणा PULL_ENA		(0 << 16)
#घोषणा PULL_DIS		(1 << 16)
#घोषणा PULL_UP			(1 << 17)
#घोषणा INPUT_EN		(1 << 18)
#घोषणा SLEWCONTROL		(1 << 19)
#घोषणा WAKEUP_EN		(1 << 24)
#घोषणा WAKEUP_EVENT		(1 << 25)

/* Active pin states */
#घोषणा PIN_OUTPUT		(0 | PULL_DIS)
#घोषणा PIN_OUTPUT_PULLUP	(PULL_UP)
#घोषणा PIN_OUTPUT_PULLDOWN	(0)
#घोषणा PIN_INPUT		(INPUT_EN | PULL_DIS)
#घोषणा PIN_INPUT_SLEW		(INPUT_EN | SLEWCONTROL)
#घोषणा PIN_INPUT_PULLUP	(PULL_ENA | INPUT_EN | PULL_UP)
#घोषणा PIN_INPUT_PULLDOWN	(PULL_ENA | INPUT_EN)

/*
 * Macro to allow using the असलolute physical address instead of the
 * padconf रेजिस्टरs instead of the offset from padconf base.
 */
#घोषणा DRA7XX_CORE_IOPAD(pa, val)	(((pa) & 0xffff) - 0x3400) (val)

/* DRA7 IODELAY configuration parameters */
#घोषणा A_DELAY_PS(val)			((val) & 0xffff)
#घोषणा G_DELAY_PS(val)			((val) & 0xffff)
#पूर्ण_अगर

