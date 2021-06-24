<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants specअगरic to DM814X pinctrl bindings.
 */

#अगर_अघोषित _DT_BINDINGS_PINCTRL_DM814X_H
#घोषणा _DT_BINDINGS_PINCTRL_DM814X_H

#समावेश <dt-bindings/pinctrl/omap.h>

#अघोषित INPUT_EN
#अघोषित PULL_UP
#अघोषित PULL_ENA

/*
 * Note that dm814x silicon revision 2.1 and older require input enabled
 * (bit 18 set) क्रम all 3.3V I/Os to aव्योम cumulative hardware damage. For
 * more info, see errata advisory 2.1.87. We leave bit 18 out of
 * function-mask in dm814x.h and rely on the bootloader क्रम it.
 */
#घोषणा INPUT_EN		(1 << 18)
#घोषणा PULL_UP			(1 << 17)
#घोषणा PULL_DISABLE		(1 << 16)

/* update macro depending on INPUT_EN and PULL_ENA */
#अघोषित PIN_OUTPUT
#अघोषित PIN_OUTPUT_PULLUP
#अघोषित PIN_OUTPUT_PULLDOWN
#अघोषित PIN_INPUT
#अघोषित PIN_INPUT_PULLUP
#अघोषित PIN_INPUT_PULLDOWN

#घोषणा PIN_OUTPUT		(PULL_DISABLE)
#घोषणा PIN_OUTPUT_PULLUP	(PULL_UP)
#घोषणा PIN_OUTPUT_PULLDOWN	0
#घोषणा PIN_INPUT		(INPUT_EN | PULL_DISABLE)
#घोषणा PIN_INPUT_PULLUP	(INPUT_EN | PULL_UP)
#घोषणा PIN_INPUT_PULLDOWN	(INPUT_EN)

/* undef non-existing modes */
#अघोषित PIN_OFF_NONE
#अघोषित PIN_OFF_OUTPUT_HIGH
#अघोषित PIN_OFF_OUTPUT_LOW
#अघोषित PIN_OFF_INPUT_PULLUP
#अघोषित PIN_OFF_INPUT_PULLDOWN
#अघोषित PIN_OFF_WAKEUPENABLE

#पूर्ण_अगर

