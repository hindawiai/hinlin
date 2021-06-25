<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम pinctrl bindings क्रम TI's K3 SoC
 * family.
 *
 * Copyright (C) 2018-2021 Texas Instruments Incorporated - https://www.ti.com/
 */
#अगर_अघोषित _DT_BINDINGS_PINCTRL_TI_K3_H
#घोषणा _DT_BINDINGS_PINCTRL_TI_K3_H

#घोषणा PULLUDEN_SHIFT		(16)
#घोषणा PULLTYPESEL_SHIFT	(17)
#घोषणा RXACTIVE_SHIFT		(18)

#घोषणा PULL_DISABLE		(1 << PULLUDEN_SHIFT)
#घोषणा PULL_ENABLE		(0 << PULLUDEN_SHIFT)

#घोषणा PULL_UP			(1 << PULLTYPESEL_SHIFT | PULL_ENABLE)
#घोषणा PULL_DOWN		(0 << PULLTYPESEL_SHIFT | PULL_ENABLE)

#घोषणा INPUT_EN		(1 << RXACTIVE_SHIFT)
#घोषणा INPUT_DISABLE		(0 << RXACTIVE_SHIFT)

/* Only these macros are expected be used directly in device tree files */
#घोषणा PIN_OUTPUT		(INPUT_DISABLE | PULL_DISABLE)
#घोषणा PIN_OUTPUT_PULLUP	(INPUT_DISABLE | PULL_UP)
#घोषणा PIN_OUTPUT_PULLDOWN	(INPUT_DISABLE | PULL_DOWN)
#घोषणा PIN_INPUT		(INPUT_EN | PULL_DISABLE)
#घोषणा PIN_INPUT_PULLUP	(INPUT_EN | PULL_UP)
#घोषणा PIN_INPUT_PULLDOWN	(INPUT_EN | PULL_DOWN)

#घोषणा AM65X_IOPAD(pa, val, muxmode)		(((pa) & 0x1fff)) ((val) | (muxmode))
#घोषणा AM65X_WKUP_IOPAD(pa, val, muxmode)	(((pa) & 0x1fff)) ((val) | (muxmode))

#घोषणा J721E_IOPAD(pa, val, muxmode)		(((pa) & 0x1fff)) ((val) | (muxmode))
#घोषणा J721E_WKUP_IOPAD(pa, val, muxmode)	(((pa) & 0x1fff)) ((val) | (muxmode))

#घोषणा AM64X_IOPAD(pa, val, muxmode)		(((pa) & 0x1fff)) ((val) | (muxmode))
#घोषणा AM64X_MCU_IOPAD(pa, val, muxmode)	(((pa) & 0x1fff)) ((val) | (muxmode))

#पूर्ण_अगर
