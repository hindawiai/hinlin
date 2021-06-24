<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants specअगरic to AM43XX pinctrl bindings.
 */

#अगर_अघोषित _DT_BINDINGS_PINCTRL_AM43XX_H
#घोषणा _DT_BINDINGS_PINCTRL_AM43XX_H

#घोषणा MUX_MODE0	0
#घोषणा MUX_MODE1	1
#घोषणा MUX_MODE2	2
#घोषणा MUX_MODE3	3
#घोषणा MUX_MODE4	4
#घोषणा MUX_MODE5	5
#घोषणा MUX_MODE6	6
#घोषणा MUX_MODE7	7
#घोषणा MUX_MODE8	8
#घोषणा MUX_MODE9	9

#घोषणा PULL_DISABLE		(1 << 16)
#घोषणा PULL_UP			(1 << 17)
#घोषणा INPUT_EN		(1 << 18)
#घोषणा SLEWCTRL_SLOW		(1 << 19)
#घोषणा SLEWCTRL_FAST		0
#घोषणा DS0_FORCE_OFF_MODE	(1 << 24)
#घोषणा DS0_INPUT		(1 << 25)
#घोषणा DS0_FORCE_OUT_HIGH	(1 << 26)
#घोषणा DS0_PULL_UP_DOWN_EN	(0 << 27)
#घोषणा DS0_PULL_UP_DOWN_DIS	(1 << 27)
#घोषणा DS0_PULL_UP_SEL		(1 << 28)
#घोषणा WAKEUP_ENABLE		(1 << 29)

#घोषणा DS0_PIN_OUTPUT		(DS0_FORCE_OFF_MODE)
#घोषणा DS0_PIN_OUTPUT_HIGH	(DS0_FORCE_OFF_MODE | DS0_FORCE_OUT_HIGH)
#घोषणा DS0_PIN_OUTPUT_PULLUP	(DS0_FORCE_OFF_MODE | DS0_PULL_UP_DOWN_EN | DS0_PULL_UP_SEL)
#घोषणा DS0_PIN_OUTPUT_PULLDOWN	(DS0_FORCE_OFF_MODE | DS0_PULL_UP_DOWN_EN)
#घोषणा DS0_PIN_INPUT		(DS0_FORCE_OFF_MODE | DS0_INPUT)
#घोषणा DS0_PIN_INPUT_PULLUP	(DS0_FORCE_OFF_MODE | DS0_INPUT | DS0_PULL_UP_DOWN_EN | DS0_PULL_UP_SEL)
#घोषणा DS0_PIN_INPUT_PULLDOWN	(DS0_FORCE_OFF_MODE | DS0_INPUT | DS0_PULL_UP_DOWN_EN)

#घोषणा PIN_OUTPUT		(PULL_DISABLE)
#घोषणा PIN_OUTPUT_PULLUP	(PULL_UP)
#घोषणा PIN_OUTPUT_PULLDOWN	0
#घोषणा PIN_INPUT		(INPUT_EN | PULL_DISABLE)
#घोषणा PIN_INPUT_PULLUP	(INPUT_EN | PULL_UP)
#घोषणा PIN_INPUT_PULLDOWN	(INPUT_EN)

/*
 * Macro to allow using the असलolute physical address instead of the
 * padconf रेजिस्टरs instead of the offset from padconf base.
 */
#घोषणा AM4372_IOPAD(pa, val)	(((pa) & 0xffff) - 0x0800) (val)

#पूर्ण_अगर

