<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम OMAP pinctrl bindings.
 *
 * Copyright (C) 2009 Nokia
 * Copyright (C) 2009-2010 Texas Instruments
 */

#अगर_अघोषित _DT_BINDINGS_PINCTRL_OMAP_H
#घोषणा _DT_BINDINGS_PINCTRL_OMAP_H

/* 34xx mux mode options क्रम each pin. See TRM क्रम options */
#घोषणा MUX_MODE0	0
#घोषणा MUX_MODE1	1
#घोषणा MUX_MODE2	2
#घोषणा MUX_MODE3	3
#घोषणा MUX_MODE4	4
#घोषणा MUX_MODE5	5
#घोषणा MUX_MODE6	6
#घोषणा MUX_MODE7	7

/* 24xx/34xx mux bit defines */
#घोषणा PULL_ENA		(1 << 3)
#घोषणा PULL_UP			(1 << 4)
#घोषणा ALTELECTRICALSEL	(1 << 5)

/* omap3/4/5 specअगरic mux bit defines */
#घोषणा INPUT_EN		(1 << 8)
#घोषणा OFF_EN			(1 << 9)
#घोषणा OFFOUT_EN		(1 << 10)
#घोषणा OFFOUT_VAL		(1 << 11)
#घोषणा OFF_PULL_EN		(1 << 12)
#घोषणा OFF_PULL_UP		(1 << 13)
#घोषणा WAKEUP_EN		(1 << 14)
#घोषणा WAKEUP_EVENT		(1 << 15)

/* Active pin states */
#घोषणा PIN_OUTPUT		0
#घोषणा PIN_OUTPUT_PULLUP	(PIN_OUTPUT | PULL_ENA | PULL_UP)
#घोषणा PIN_OUTPUT_PULLDOWN	(PIN_OUTPUT | PULL_ENA)
#घोषणा PIN_INPUT		INPUT_EN
#घोषणा PIN_INPUT_PULLUP	(PULL_ENA | INPUT_EN | PULL_UP)
#घोषणा PIN_INPUT_PULLDOWN	(PULL_ENA | INPUT_EN)

/* Off mode states */
#घोषणा PIN_OFF_NONE		0
#घोषणा PIN_OFF_OUTPUT_HIGH	(OFF_EN | OFFOUT_EN | OFFOUT_VAL)
#घोषणा PIN_OFF_OUTPUT_LOW	(OFF_EN | OFFOUT_EN)
#घोषणा PIN_OFF_INPUT_PULLUP	(OFF_EN | OFFOUT_EN | OFF_PULL_EN | OFF_PULL_UP)
#घोषणा PIN_OFF_INPUT_PULLDOWN	(OFF_EN | OFFOUT_EN | OFF_PULL_EN)
#घोषणा PIN_OFF_WAKEUPENABLE	WAKEUP_EN

/*
 * Macros to allow using the असलolute physical address instead of the
 * padconf रेजिस्टरs instead of the offset from padconf base.
 */
#घोषणा OMAP_IOPAD_OFFSET(pa, offset)	(((pa) & 0xffff) - (offset))

#घोषणा OMAP2420_CORE_IOPAD(pa, val)	OMAP_IOPAD_OFFSET((pa), 0x0030) (val)
#घोषणा OMAP2430_CORE_IOPAD(pa, val)	OMAP_IOPAD_OFFSET((pa), 0x2030) (val)
#घोषणा OMAP3_CORE1_IOPAD(pa, val)	OMAP_IOPAD_OFFSET((pa), 0x2030) (val)
#घोषणा OMAP3430_CORE2_IOPAD(pa, val)	OMAP_IOPAD_OFFSET((pa), 0x25d8) (val)
#घोषणा OMAP3630_CORE2_IOPAD(pa, val)	OMAP_IOPAD_OFFSET((pa), 0x25a0) (val)
#घोषणा OMAP3_WKUP_IOPAD(pa, val)	OMAP_IOPAD_OFFSET((pa), 0x2a00) (val)
#घोषणा DM814X_IOPAD(pa, val)		OMAP_IOPAD_OFFSET((pa), 0x0800) (val)
#घोषणा DM816X_IOPAD(pa, val)		OMAP_IOPAD_OFFSET((pa), 0x0800) (val)
#घोषणा AM33XX_IOPAD(pa, val)		OMAP_IOPAD_OFFSET((pa), 0x0800) (val) (0)
#घोषणा AM33XX_PADCONF(pa, conf, mux)	OMAP_IOPAD_OFFSET((pa), 0x0800) (conf) (mux)

/*
 * Macros to allow using the offset from the padconf physical address
 * instead  of the offset from padconf base.
 */
#घोषणा OMAP_PADCONF_OFFSET(offset, base_offset)	((offset) - (base_offset))

#घोषणा OMAP4_IOPAD(offset, val)	OMAP_PADCONF_OFFSET((offset), 0x0040) (val)
#घोषणा OMAP5_IOPAD(offset, val)	OMAP_PADCONF_OFFSET((offset), 0x0040) (val)

/*
 * Define some commonly used pins configured by the boards.
 * Note that some boards use alternative pins, so check
 * the schematics beक्रमe using these.
 */
#घोषणा OMAP3_UART1_RX		0x152
#घोषणा OMAP3_UART2_RX		0x14a
#घोषणा OMAP3_UART3_RX		0x16e
#घोषणा OMAP4_UART2_RX		0xdc
#घोषणा OMAP4_UART3_RX		0x104
#घोषणा OMAP4_UART4_RX		0x11c

#पूर्ण_अगर

