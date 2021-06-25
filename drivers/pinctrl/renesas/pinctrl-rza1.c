<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Combined GPIO and pin controller support क्रम Renesas RZ/A1 (r7s72100) SoC
 *
 * Copyright (C) 2017 Jacopo Mondi
 */

/*
 * This pin controller/gpio combined driver supports Renesas devices of RZ/A1
 * family.
 * This includes SoCs which are sub- or super- sets of this particular line,
 * as RZ/A1H (r7s721000), RZ/A1M (r7s721010) and RZ/A1L (r7s721020).
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "../devicetree.h"
#समावेश "../pinconf.h"
#समावेश "../pinmux.h"

#घोषणा DRIVER_NAME			"pinctrl-rza1"

#घोषणा RZA1_P_REG			0x0000
#घोषणा RZA1_PPR_REG			0x0200
#घोषणा RZA1_PM_REG			0x0300
#घोषणा RZA1_PMC_REG			0x0400
#घोषणा RZA1_PFC_REG			0x0500
#घोषणा RZA1_PFCE_REG			0x0600
#घोषणा RZA1_PFCEA_REG			0x0a00
#घोषणा RZA1_PIBC_REG			0x4000
#घोषणा RZA1_PBDC_REG			0x4100
#घोषणा RZA1_PIPC_REG			0x4200

#घोषणा RZA1_ADDR(mem, reg, port)	((mem) + (reg) + ((port) * 4))

#घोषणा RZA1_NPORTS			12
#घोषणा RZA1_PINS_PER_PORT		16
#घोषणा RZA1_NPINS			(RZA1_PINS_PER_PORT * RZA1_NPORTS)
#घोषणा RZA1_PIN_ID_TO_PORT(id)		((id) / RZA1_PINS_PER_PORT)
#घोषणा RZA1_PIN_ID_TO_PIN(id)		((id) % RZA1_PINS_PER_PORT)

/*
 * Use 16 lower bits [15:0] क्रम pin identअगरier
 * Use 16 higher bits [31:16] क्रम pin mux function
 */
#घोषणा MUX_PIN_ID_MASK			GENMASK(15, 0)
#घोषणा MUX_FUNC_MASK			GENMASK(31, 16)

#घोषणा MUX_FUNC_OFFS			16
#घोषणा MUX_FUNC(pinconf)		\
	((pinconf & MUX_FUNC_MASK) >> MUX_FUNC_OFFS)
#घोषणा MUX_FUNC_PFC_MASK		BIT(0)
#घोषणा MUX_FUNC_PFCE_MASK		BIT(1)
#घोषणा MUX_FUNC_PFCEA_MASK		BIT(2)

/* Pin mux flags */
#घोषणा MUX_FLAGS_BIसूची			BIT(0)
#घोषणा MUX_FLAGS_SWIO_INPUT		BIT(1)
#घोषणा MUX_FLAGS_SWIO_OUTPUT		BIT(2)

/* ----------------------------------------------------------------------------
 * RZ/A1 pinmux flags
 */

/*
 * rza1_bidir_pin - describe a single pin that needs bidir flag applied.
 */
काष्ठा rza1_bidir_pin अणु
	u8 pin: 4;
	u8 func: 4;
पूर्ण;

/*
 * rza1_bidir_entry - describe a list of pins that needs bidir flag applied.
 *		      Each काष्ठा rza1_bidir_entry describes a port.
 */
काष्ठा rza1_bidir_entry अणु
	स्थिर अचिन्हित पूर्णांक npins;
	स्थिर काष्ठा rza1_bidir_pin *pins;
पूर्ण;

/*
 * rza1_swio_pin - describe a single pin that needs swio flag applied.
 */
काष्ठा rza1_swio_pin अणु
	u16 pin: 4;
	u16 port: 4;
	u16 func: 4;
	u16 input: 1;
पूर्ण;

/*
 * rza1_swio_entry - describe a list of pins that needs swio flag applied
 */
काष्ठा rza1_swio_entry अणु
	स्थिर अचिन्हित पूर्णांक npins;
	स्थिर काष्ठा rza1_swio_pin *pins;
पूर्ण;

/*
 * rza1_pinmux_conf - group together bidir and swio pinmux flag tables
 */
काष्ठा rza1_pinmux_conf अणु
	स्थिर काष्ठा rza1_bidir_entry *bidir_entries;
	स्थिर काष्ठा rza1_swio_entry *swio_entries;
पूर्ण;

/* ----------------------------------------------------------------------------
 * RZ/A1H (r7s72100) pinmux flags
 */

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p1[] = अणु
	अणु .pin = 0, .func = 1 पूर्ण,
	अणु .pin = 1, .func = 1 पूर्ण,
	अणु .pin = 2, .func = 1 पूर्ण,
	अणु .pin = 3, .func = 1 पूर्ण,
	अणु .pin = 4, .func = 1 पूर्ण,
	अणु .pin = 5, .func = 1 पूर्ण,
	अणु .pin = 6, .func = 1 पूर्ण,
	अणु .pin = 7, .func = 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p2[] = अणु
	अणु .pin = 0, .func = 1 पूर्ण,
	अणु .pin = 1, .func = 1 पूर्ण,
	अणु .pin = 2, .func = 1 पूर्ण,
	अणु .pin = 3, .func = 1 पूर्ण,
	अणु .pin = 4, .func = 1 पूर्ण,
	अणु .pin = 0, .func = 4 पूर्ण,
	अणु .pin = 1, .func = 4 पूर्ण,
	अणु .pin = 2, .func = 4 पूर्ण,
	अणु .pin = 3, .func = 4 पूर्ण,
	अणु .pin = 5, .func = 1 पूर्ण,
	अणु .pin = 6, .func = 1 पूर्ण,
	अणु .pin = 7, .func = 1 पूर्ण,
	अणु .pin = 8, .func = 1 पूर्ण,
	अणु .pin = 9, .func = 1 पूर्ण,
	अणु .pin = 10, .func = 1 पूर्ण,
	अणु .pin = 11, .func = 1 पूर्ण,
	अणु .pin = 12, .func = 1 पूर्ण,
	अणु .pin = 13, .func = 1 पूर्ण,
	अणु .pin = 14, .func = 1 पूर्ण,
	अणु .pin = 15, .func = 1 पूर्ण,
	अणु .pin = 12, .func = 4 पूर्ण,
	अणु .pin = 13, .func = 4 पूर्ण,
	अणु .pin = 14, .func = 4 पूर्ण,
	अणु .pin = 15, .func = 4 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p3[] = अणु
	अणु .pin = 3, .func = 2 पूर्ण,
	अणु .pin = 10, .func = 7 पूर्ण,
	अणु .pin = 11, .func = 7 पूर्ण,
	अणु .pin = 13, .func = 7 पूर्ण,
	अणु .pin = 14, .func = 7 पूर्ण,
	अणु .pin = 15, .func = 7 पूर्ण,
	अणु .pin = 10, .func = 8 पूर्ण,
	अणु .pin = 11, .func = 8 पूर्ण,
	अणु .pin = 13, .func = 8 पूर्ण,
	अणु .pin = 14, .func = 8 पूर्ण,
	अणु .pin = 15, .func = 8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p4[] = अणु
	अणु .pin = 0, .func = 8 पूर्ण,
	अणु .pin = 1, .func = 8 पूर्ण,
	अणु .pin = 2, .func = 8 पूर्ण,
	अणु .pin = 3, .func = 8 पूर्ण,
	अणु .pin = 10, .func = 3 पूर्ण,
	अणु .pin = 11, .func = 3 पूर्ण,
	अणु .pin = 13, .func = 3 पूर्ण,
	अणु .pin = 14, .func = 3 पूर्ण,
	अणु .pin = 15, .func = 3 पूर्ण,
	अणु .pin = 10, .func = 4 पूर्ण,
	अणु .pin = 11, .func = 4 पूर्ण,
	अणु .pin = 13, .func = 4 पूर्ण,
	अणु .pin = 14, .func = 4 पूर्ण,
	अणु .pin = 15, .func = 4 पूर्ण,
	अणु .pin = 12, .func = 5 पूर्ण,
	अणु .pin = 13, .func = 5 पूर्ण,
	अणु .pin = 14, .func = 5 पूर्ण,
	अणु .pin = 15, .func = 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p6[] = अणु
	अणु .pin = 0, .func = 1 पूर्ण,
	अणु .pin = 1, .func = 1 पूर्ण,
	अणु .pin = 2, .func = 1 पूर्ण,
	अणु .pin = 3, .func = 1 पूर्ण,
	अणु .pin = 4, .func = 1 पूर्ण,
	अणु .pin = 5, .func = 1 पूर्ण,
	अणु .pin = 6, .func = 1 पूर्ण,
	अणु .pin = 7, .func = 1 पूर्ण,
	अणु .pin = 8, .func = 1 पूर्ण,
	अणु .pin = 9, .func = 1 पूर्ण,
	अणु .pin = 10, .func = 1 पूर्ण,
	अणु .pin = 11, .func = 1 पूर्ण,
	अणु .pin = 12, .func = 1 पूर्ण,
	अणु .pin = 13, .func = 1 पूर्ण,
	अणु .pin = 14, .func = 1 पूर्ण,
	अणु .pin = 15, .func = 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p7[] = अणु
	अणु .pin = 13, .func = 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p8[] = अणु
	अणु .pin = 8, .func = 3 पूर्ण,
	अणु .pin = 9, .func = 3 पूर्ण,
	अणु .pin = 10, .func = 3 पूर्ण,
	अणु .pin = 11, .func = 3 पूर्ण,
	अणु .pin = 14, .func = 2 पूर्ण,
	अणु .pin = 15, .func = 2 पूर्ण,
	अणु .pin = 14, .func = 3 पूर्ण,
	अणु .pin = 15, .func = 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p9[] = अणु
	अणु .pin = 0, .func = 2 पूर्ण,
	अणु .pin = 1, .func = 2 पूर्ण,
	अणु .pin = 4, .func = 2 पूर्ण,
	अणु .pin = 5, .func = 2 पूर्ण,
	अणु .pin = 6, .func = 2 पूर्ण,
	अणु .pin = 7, .func = 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1h_bidir_pins_p11[] = अणु
	अणु .pin = 6, .func = 2 पूर्ण,
	अणु .pin = 7, .func = 2 पूर्ण,
	अणु .pin = 9, .func = 2 पूर्ण,
	अणु .pin = 6, .func = 4 पूर्ण,
	अणु .pin = 7, .func = 4 पूर्ण,
	अणु .pin = 9, .func = 4 पूर्ण,
	अणु .pin = 10, .func = 2 पूर्ण,
	अणु .pin = 11, .func = 2 पूर्ण,
	अणु .pin = 10, .func = 4 पूर्ण,
	अणु .pin = 11, .func = 4 पूर्ण,
	अणु .pin = 12, .func = 4 पूर्ण,
	अणु .pin = 13, .func = 4 पूर्ण,
	अणु .pin = 14, .func = 4 पूर्ण,
	अणु .pin = 15, .func = 4 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_swio_pin rza1h_swio_pins[] = अणु
	अणु .port = 2, .pin = 7, .func = 4, .input = 0 पूर्ण,
	अणु .port = 2, .pin = 11, .func = 4, .input = 0 पूर्ण,
	अणु .port = 3, .pin = 7, .func = 3, .input = 0 पूर्ण,
	अणु .port = 3, .pin = 7, .func = 8, .input = 0 पूर्ण,
	अणु .port = 4, .pin = 7, .func = 5, .input = 0 पूर्ण,
	अणु .port = 4, .pin = 7, .func = 11, .input = 0 पूर्ण,
	अणु .port = 4, .pin = 15, .func = 6, .input = 0 पूर्ण,
	अणु .port = 5, .pin = 0, .func = 1, .input = 1 पूर्ण,
	अणु .port = 5, .pin = 1, .func = 1, .input = 1 पूर्ण,
	अणु .port = 5, .pin = 2, .func = 1, .input = 1 पूर्ण,
	अणु .port = 5, .pin = 3, .func = 1, .input = 1 पूर्ण,
	अणु .port = 5, .pin = 4, .func = 1, .input = 1 पूर्ण,
	अणु .port = 5, .pin = 5, .func = 1, .input = 1 पूर्ण,
	अणु .port = 5, .pin = 6, .func = 1, .input = 1 पूर्ण,
	अणु .port = 5, .pin = 7, .func = 1, .input = 1 पूर्ण,
	अणु .port = 7, .pin = 4, .func = 6, .input = 0 पूर्ण,
	अणु .port = 7, .pin = 11, .func = 2, .input = 0 पूर्ण,
	अणु .port = 8, .pin = 10, .func = 8, .input = 0 पूर्ण,
	अणु .port = 10, .pin = 15, .func = 2, .input = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_entry rza1h_bidir_entries[RZA1_NPORTS] = अणु
	[1] = अणु ARRAY_SIZE(rza1h_bidir_pins_p1), rza1h_bidir_pins_p1 पूर्ण,
	[2] = अणु ARRAY_SIZE(rza1h_bidir_pins_p2), rza1h_bidir_pins_p2 पूर्ण,
	[3] = अणु ARRAY_SIZE(rza1h_bidir_pins_p3), rza1h_bidir_pins_p3 पूर्ण,
	[4] = अणु ARRAY_SIZE(rza1h_bidir_pins_p4), rza1h_bidir_pins_p4 पूर्ण,
	[6] = अणु ARRAY_SIZE(rza1h_bidir_pins_p6), rza1h_bidir_pins_p6 पूर्ण,
	[7] = अणु ARRAY_SIZE(rza1h_bidir_pins_p7), rza1h_bidir_pins_p7 पूर्ण,
	[8] = अणु ARRAY_SIZE(rza1h_bidir_pins_p8), rza1h_bidir_pins_p8 पूर्ण,
	[9] = अणु ARRAY_SIZE(rza1h_bidir_pins_p9), rza1h_bidir_pins_p9 पूर्ण,
	[11] = अणु ARRAY_SIZE(rza1h_bidir_pins_p11), rza1h_bidir_pins_p11 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_swio_entry rza1h_swio_entries[] = अणु
	[0] = अणु ARRAY_SIZE(rza1h_swio_pins), rza1h_swio_pins पूर्ण,
पूर्ण;

/* RZ/A1H (r7s72100x) pinmux flags table */
अटल स्थिर काष्ठा rza1_pinmux_conf rza1h_pmx_conf = अणु
	.bidir_entries	= rza1h_bidir_entries,
	.swio_entries	= rza1h_swio_entries,
पूर्ण;

/* ----------------------------------------------------------------------------
 * RZ/A1L (r7s72102) pinmux flags
 */

अटल स्थिर काष्ठा rza1_bidir_pin rza1l_bidir_pins_p1[] = अणु
	अणु .pin = 0, .func = 1 पूर्ण,
	अणु .pin = 1, .func = 1 पूर्ण,
	अणु .pin = 2, .func = 1 पूर्ण,
	अणु .pin = 3, .func = 1 पूर्ण,
	अणु .pin = 4, .func = 1 पूर्ण,
	अणु .pin = 5, .func = 1 पूर्ण,
	अणु .pin = 6, .func = 1 पूर्ण,
	अणु .pin = 7, .func = 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1l_bidir_pins_p3[] = अणु
	अणु .pin = 0, .func = 2 पूर्ण,
	अणु .pin = 1, .func = 2 पूर्ण,
	अणु .pin = 2, .func = 2 पूर्ण,
	अणु .pin = 4, .func = 2 पूर्ण,
	अणु .pin = 5, .func = 2 पूर्ण,
	अणु .pin = 10, .func = 2 पूर्ण,
	अणु .pin = 11, .func = 2 पूर्ण,
	अणु .pin = 12, .func = 2 पूर्ण,
	अणु .pin = 13, .func = 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1l_bidir_pins_p4[] = अणु
	अणु .pin = 1, .func = 4 पूर्ण,
	अणु .pin = 2, .func = 2 पूर्ण,
	अणु .pin = 3, .func = 2 पूर्ण,
	अणु .pin = 6, .func = 2 पूर्ण,
	अणु .pin = 7, .func = 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1l_bidir_pins_p5[] = अणु
	अणु .pin = 0, .func = 1 पूर्ण,
	अणु .pin = 1, .func = 1 पूर्ण,
	अणु .pin = 2, .func = 1 पूर्ण,
	अणु .pin = 3, .func = 1 पूर्ण,
	अणु .pin = 4, .func = 1 पूर्ण,
	अणु .pin = 5, .func = 1 पूर्ण,
	अणु .pin = 6, .func = 1 पूर्ण,
	अणु .pin = 7, .func = 1 पूर्ण,
	अणु .pin = 8, .func = 1 पूर्ण,
	अणु .pin = 9, .func = 1 पूर्ण,
	अणु .pin = 10, .func = 1 पूर्ण,
	अणु .pin = 11, .func = 1 पूर्ण,
	अणु .pin = 12, .func = 1 पूर्ण,
	अणु .pin = 13, .func = 1 पूर्ण,
	अणु .pin = 14, .func = 1 पूर्ण,
	अणु .pin = 15, .func = 1 पूर्ण,
	अणु .pin = 0, .func = 2 पूर्ण,
	अणु .pin = 1, .func = 2 पूर्ण,
	अणु .pin = 2, .func = 2 पूर्ण,
	अणु .pin = 3, .func = 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1l_bidir_pins_p6[] = अणु
	अणु .pin = 0, .func = 1 पूर्ण,
	अणु .pin = 1, .func = 1 पूर्ण,
	अणु .pin = 2, .func = 1 पूर्ण,
	अणु .pin = 3, .func = 1 पूर्ण,
	अणु .pin = 4, .func = 1 पूर्ण,
	अणु .pin = 5, .func = 1 पूर्ण,
	अणु .pin = 6, .func = 1 पूर्ण,
	अणु .pin = 7, .func = 1 पूर्ण,
	अणु .pin = 8, .func = 1 पूर्ण,
	अणु .pin = 9, .func = 1 पूर्ण,
	अणु .pin = 10, .func = 1 पूर्ण,
	अणु .pin = 11, .func = 1 पूर्ण,
	अणु .pin = 12, .func = 1 पूर्ण,
	अणु .pin = 13, .func = 1 पूर्ण,
	अणु .pin = 14, .func = 1 पूर्ण,
	अणु .pin = 15, .func = 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1l_bidir_pins_p7[] = अणु
	अणु .pin = 2, .func = 2 पूर्ण,
	अणु .pin = 3, .func = 2 पूर्ण,
	अणु .pin = 5, .func = 2 पूर्ण,
	अणु .pin = 6, .func = 2 पूर्ण,
	अणु .pin = 7, .func = 2 पूर्ण,
	अणु .pin = 2, .func = 3 पूर्ण,
	अणु .pin = 3, .func = 3 पूर्ण,
	अणु .pin = 5, .func = 3 पूर्ण,
	अणु .pin = 6, .func = 3 पूर्ण,
	अणु .pin = 7, .func = 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_pin rza1l_bidir_pins_p9[] = अणु
	अणु .pin = 1, .func = 2 पूर्ण,
	अणु .pin = 0, .func = 3 पूर्ण,
	अणु .pin = 1, .func = 3 पूर्ण,
	अणु .pin = 3, .func = 3 पूर्ण,
	अणु .pin = 4, .func = 3 पूर्ण,
	अणु .pin = 5, .func = 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_swio_pin rza1l_swio_pins[] = अणु
	अणु .port = 2, .pin = 8, .func = 2, .input = 0 पूर्ण,
	अणु .port = 5, .pin = 6, .func = 3, .input = 0 पूर्ण,
	अणु .port = 6, .pin = 6, .func = 3, .input = 0 पूर्ण,
	अणु .port = 6, .pin = 10, .func = 3, .input = 0 पूर्ण,
	अणु .port = 7, .pin = 10, .func = 2, .input = 0 पूर्ण,
	अणु .port = 8, .pin = 2, .func = 3, .input = 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_bidir_entry rza1l_bidir_entries[RZA1_NPORTS] = अणु
	[1] = अणु ARRAY_SIZE(rza1l_bidir_pins_p1), rza1l_bidir_pins_p1 पूर्ण,
	[3] = अणु ARRAY_SIZE(rza1l_bidir_pins_p3), rza1l_bidir_pins_p3 पूर्ण,
	[4] = अणु ARRAY_SIZE(rza1l_bidir_pins_p4), rza1l_bidir_pins_p4 पूर्ण,
	[5] = अणु ARRAY_SIZE(rza1l_bidir_pins_p4), rza1l_bidir_pins_p5 पूर्ण,
	[6] = अणु ARRAY_SIZE(rza1l_bidir_pins_p6), rza1l_bidir_pins_p6 पूर्ण,
	[7] = अणु ARRAY_SIZE(rza1l_bidir_pins_p7), rza1l_bidir_pins_p7 पूर्ण,
	[9] = अणु ARRAY_SIZE(rza1l_bidir_pins_p9), rza1l_bidir_pins_p9 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rza1_swio_entry rza1l_swio_entries[] = अणु
	[0] = अणु ARRAY_SIZE(rza1l_swio_pins), rza1l_swio_pins पूर्ण,
पूर्ण;

/* RZ/A1L (r7s72102x) pinmux flags table */
अटल स्थिर काष्ठा rza1_pinmux_conf rza1l_pmx_conf = अणु
	.bidir_entries	= rza1l_bidir_entries,
	.swio_entries	= rza1l_swio_entries,
पूर्ण;

/* ----------------------------------------------------------------------------
 * RZ/A1 types
 */
/**
 * काष्ठा rza1_mux_conf - describes a pin multiplexing operation
 *
 * @id: the pin identअगरier from 0 to RZA1_NPINS
 * @port: the port where pin sits on
 * @pin: pin id
 * @mux_func: alternate function id number
 * @mux_flags: alternate function flags
 * @value: output value to set the pin to
 */
काष्ठा rza1_mux_conf अणु
	u16 id;
	u8 port;
	u8 pin;
	u8 mux_func;
	u8 mux_flags;
	u8 value;
पूर्ण;

/**
 * काष्ठा rza1_port - describes a pin port
 *
 * This is mostly useful to lock रेजिस्टर ग_लिखोs per-bank and not globally.
 *
 * @lock: protect access to HW रेजिस्टरs
 * @id: port number
 * @base: logical address base
 * @pins: pins sitting on this port
 */
काष्ठा rza1_port अणु
	spinlock_t lock;
	अचिन्हित पूर्णांक id;
	व्योम __iomem *base;
	काष्ठा pinctrl_pin_desc *pins;
पूर्ण;

/**
 * काष्ठा rza1_pinctrl - RZ pincontroller device
 *
 * @dev: parent device काष्ठाure
 * @mutex: protect [pinctrl|pinmux]_generic functions
 * @base: logical address base
 * @nport: number of pin controller ports
 * @ports: pin controller banks
 * @pins: pin array क्रम pinctrl core
 * @desc: pincontroller desc क्रम pinctrl core
 * @pctl: pinctrl device
 * @data: device specअगरic data
 */
काष्ठा rza1_pinctrl अणु
	काष्ठा device *dev;

	काष्ठा mutex mutex;

	व्योम __iomem *base;

	अचिन्हित पूर्णांक nport;
	काष्ठा rza1_port *ports;

	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा pinctrl_desc desc;
	काष्ठा pinctrl_dev *pctl;

	स्थिर व्योम *data;
पूर्ण;

/* ----------------------------------------------------------------------------
 * RZ/A1 pinmux flags
 */
अटल अंतरभूत bool rza1_pinmux_get_bidir(अचिन्हित पूर्णांक port,
					 अचिन्हित पूर्णांक pin,
					 अचिन्हित पूर्णांक func,
					 स्थिर काष्ठा rza1_bidir_entry *table)
अणु
	स्थिर काष्ठा rza1_bidir_entry *entry = &table[port];
	स्थिर काष्ठा rza1_bidir_pin *bidir_pin;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < entry->npins; ++i) अणु
		bidir_pin = &entry->pins[i];
		अगर (bidir_pin->pin == pin && bidir_pin->func == func)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक rza1_pinmux_get_swio(अचिन्हित पूर्णांक port,
				       अचिन्हित पूर्णांक pin,
				       अचिन्हित पूर्णांक func,
				       स्थिर काष्ठा rza1_swio_entry *table)
अणु
	स्थिर काष्ठा rza1_swio_pin *swio_pin;
	अचिन्हित पूर्णांक i;


	क्रम (i = 0; i < table->npins; ++i) अणु
		swio_pin = &table->pins[i];
		अगर (swio_pin->port == port && swio_pin->pin == pin &&
		    swio_pin->func == func)
			वापस swio_pin->input;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/*
 * rza1_pinmux_get_flags() - वापस pinmux flags associated to a pin
 */
अटल अचिन्हित पूर्णांक rza1_pinmux_get_flags(अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक pin,
					  अचिन्हित पूर्णांक func,
					  काष्ठा rza1_pinctrl *rza1_pctl)

अणु
	स्थिर काष्ठा rza1_pinmux_conf *pmx_conf = rza1_pctl->data;
	स्थिर काष्ठा rza1_bidir_entry *bidir_entries = pmx_conf->bidir_entries;
	स्थिर काष्ठा rza1_swio_entry *swio_entries = pmx_conf->swio_entries;
	अचिन्हित पूर्णांक pmx_flags = 0;
	पूर्णांक ret;

	अगर (rza1_pinmux_get_bidir(port, pin, func, bidir_entries))
		pmx_flags |= MUX_FLAGS_BIसूची;

	ret = rza1_pinmux_get_swio(port, pin, func, swio_entries);
	अगर (ret == 0)
		pmx_flags |= MUX_FLAGS_SWIO_OUTPUT;
	अन्यथा अगर (ret > 0)
		pmx_flags |= MUX_FLAGS_SWIO_INPUT;

	वापस pmx_flags;
पूर्ण

/* ----------------------------------------------------------------------------
 * RZ/A1 SoC operations
 */

/*
 * rza1_set_bit() - un-locked set/clear a single bit in pin configuration
 *		    रेजिस्टरs
 */
अटल अंतरभूत व्योम rza1_set_bit(काष्ठा rza1_port *port, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक bit, bool set)
अणु
	व्योम __iomem *mem = RZA1_ADDR(port->base, reg, port->id);
	u16 val = ioपढ़ो16(mem);

	अगर (set)
		val |= BIT(bit);
	अन्यथा
		val &= ~BIT(bit);

	ioग_लिखो16(val, mem);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rza1_get_bit(काष्ठा rza1_port *port,
					अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक bit)
अणु
	व्योम __iomem *mem = RZA1_ADDR(port->base, reg, port->id);

	वापस ioपढ़ो16(mem) & BIT(bit);
पूर्ण

/**
 * rza1_pin_reset() - reset a pin to शेष initial state
 *
 * Reset pin state disabling input buffer and bi-directional control,
 * and configure it as input port.
 * Note that pin is now configured with direction as input but with input
 * buffer disabled. This implies the pin value cannot be पढ़ो in this state.
 *
 * @port: port where pin sits on
 * @pin: pin offset
 */
अटल व्योम rza1_pin_reset(काष्ठा rza1_port *port, अचिन्हित पूर्णांक pin)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&port->lock, irqflags);
	rza1_set_bit(port, RZA1_PIBC_REG, pin, 0);
	rza1_set_bit(port, RZA1_PBDC_REG, pin, 0);

	rza1_set_bit(port, RZA1_PM_REG, pin, 1);
	rza1_set_bit(port, RZA1_PMC_REG, pin, 0);
	rza1_set_bit(port, RZA1_PIPC_REG, pin, 0);
	spin_unlock_irqrestore(&port->lock, irqflags);
पूर्ण

/**
 * rza1_pin_set_direction() - set I/O direction on a pin in port mode
 *
 * When running in output port mode keep PBDC enabled to allow पढ़ोing the
 * pin value from PPR.
 *
 * @port: port where pin sits on
 * @pin: pin offset
 * @input: input enable/disable flag
 */
अटल अंतरभूत व्योम rza1_pin_set_direction(काष्ठा rza1_port *port,
					  अचिन्हित पूर्णांक pin, bool input)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&port->lock, irqflags);

	rza1_set_bit(port, RZA1_PIBC_REG, pin, 1);
	अगर (input) अणु
		rza1_set_bit(port, RZA1_PM_REG, pin, 1);
		rza1_set_bit(port, RZA1_PBDC_REG, pin, 0);
	पूर्ण अन्यथा अणु
		rza1_set_bit(port, RZA1_PM_REG, pin, 0);
		rza1_set_bit(port, RZA1_PBDC_REG, pin, 1);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, irqflags);
पूर्ण

अटल अंतरभूत व्योम rza1_pin_set(काष्ठा rza1_port *port, अचिन्हित पूर्णांक pin,
				अचिन्हित पूर्णांक value)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&port->lock, irqflags);
	rza1_set_bit(port, RZA1_P_REG, pin, !!value);
	spin_unlock_irqrestore(&port->lock, irqflags);
पूर्ण

अटल अंतरभूत पूर्णांक rza1_pin_get(काष्ठा rza1_port *port, अचिन्हित पूर्णांक pin)
अणु
	वापस rza1_get_bit(port, RZA1_PPR_REG, pin);
पूर्ण

/**
 * rza1_pin_mux_single() - configure pin multiplexing on a single pin
 *
 * @rza1_pctl: RZ/A1 pin controller device
 * @mux_conf: pin multiplexing descriptor
 */
अटल पूर्णांक rza1_pin_mux_single(काष्ठा rza1_pinctrl *rza1_pctl,
			       काष्ठा rza1_mux_conf *mux_conf)
अणु
	काष्ठा rza1_port *port = &rza1_pctl->ports[mux_conf->port];
	अचिन्हित पूर्णांक pin = mux_conf->pin;
	u8 mux_func = mux_conf->mux_func;
	u8 mux_flags = mux_conf->mux_flags;
	u8 mux_flags_from_table;

	rza1_pin_reset(port, pin);

	/* SWIO pinmux flags coming from DT are high precedence */
	mux_flags_from_table = rza1_pinmux_get_flags(port->id, pin, mux_func,
						     rza1_pctl);
	अगर (mux_flags)
		mux_flags |= (mux_flags_from_table & MUX_FLAGS_BIसूची);
	अन्यथा
		mux_flags = mux_flags_from_table;

	अगर (mux_flags & MUX_FLAGS_BIसूची)
		rza1_set_bit(port, RZA1_PBDC_REG, pin, 1);

	/*
	 * Enable alternate function mode and select it.
	 *
	 * Be careful here: the pin mux sub-nodes in device tree
	 * क्रमागतerate alternate functions from 1 to 8;
	 * subtract 1 beक्रमe using macros to match रेजिस्टरs configuration
	 * which expects numbers from 0 to 7 instead.
	 *
	 * ----------------------------------------------------
	 * Alternate mode selection table:
	 *
	 * PMC	PFC	PFCE	PFCAE	(mux_func - 1)
	 * 1	0	0	0	0
	 * 1	1	0	0	1
	 * 1	0	1	0	2
	 * 1	1	1	0	3
	 * 1	0	0	1	4
	 * 1	1	0	1	5
	 * 1	0	1	1	6
	 * 1	1	1	1	7
	 * ----------------------------------------------------
	 */
	mux_func -= 1;
	rza1_set_bit(port, RZA1_PFC_REG, pin, mux_func & MUX_FUNC_PFC_MASK);
	rza1_set_bit(port, RZA1_PFCE_REG, pin, mux_func & MUX_FUNC_PFCE_MASK);
	rza1_set_bit(port, RZA1_PFCEA_REG, pin, mux_func & MUX_FUNC_PFCEA_MASK);

	/*
	 * All alternate functions except a few need PIPCn = 1.
	 * If PIPCn has to stay disabled (SW IO mode), configure PMn according
	 * to I/O direction specअगरied by pin configuration -after- PMC has been
	 * set to one.
	 */
	अगर (mux_flags & (MUX_FLAGS_SWIO_INPUT | MUX_FLAGS_SWIO_OUTPUT))
		rza1_set_bit(port, RZA1_PM_REG, pin,
			     mux_flags & MUX_FLAGS_SWIO_INPUT);
	अन्यथा
		rza1_set_bit(port, RZA1_PIPC_REG, pin, 1);

	rza1_set_bit(port, RZA1_PMC_REG, pin, 1);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------------
 * gpio operations
 */

/**
 * rza1_gpio_request() - configure pin in port mode
 *
 * Configure a pin as gpio (port mode).
 * After reset, the pin is in input mode with input buffer disabled.
 * To use the pin as input or output, set_direction shall be called first
 *
 * @chip: gpio chip where the gpio sits on
 * @gpio: gpio offset
 */
अटल पूर्णांक rza1_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा rza1_port *port = gpiochip_get_data(chip);

	rza1_pin_reset(port, gpio);

	वापस 0;
पूर्ण

/**
 * rza1_gpio_disable_मुक्त() - reset a pin
 *
 * Surprisingly, disable_मुक्त a gpio, is equivalent to request it.
 * Reset pin to port mode, with input buffer disabled. This overग_लिखोs all
 * port direction settings applied with set_direction
 *
 * @chip: gpio chip where the gpio sits on
 * @gpio: gpio offset
 */
अटल व्योम rza1_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा rza1_port *port = gpiochip_get_data(chip);

	rza1_pin_reset(port, gpio);
पूर्ण

अटल पूर्णांक rza1_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा rza1_port *port = gpiochip_get_data(chip);

	अगर (rza1_get_bit(port, RZA1_PM_REG, gpio))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक rza1_gpio_direction_input(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा rza1_port *port = gpiochip_get_data(chip);

	rza1_pin_set_direction(port, gpio, true);

	वापस 0;
पूर्ण

अटल पूर्णांक rza1_gpio_direction_output(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक gpio,
				      पूर्णांक value)
अणु
	काष्ठा rza1_port *port = gpiochip_get_data(chip);

	/* Set value beक्रमe driving pin direction */
	rza1_pin_set(port, gpio, value);
	rza1_pin_set_direction(port, gpio, false);

	वापस 0;
पूर्ण

/**
 * rza1_gpio_get() - पढ़ो a gpio pin value
 *
 * Read gpio pin value through PPR रेजिस्टर.
 * Requires bi-directional mode to work when पढ़ोing the value of a pin
 * in output mode
 *
 * @chip: gpio chip where the gpio sits on
 * @gpio: gpio offset
 */
अटल पूर्णांक rza1_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा rza1_port *port = gpiochip_get_data(chip);

	वापस rza1_pin_get(port, gpio);
पूर्ण

अटल व्योम rza1_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio,
			  पूर्णांक value)
अणु
	काष्ठा rza1_port *port = gpiochip_get_data(chip);

	rza1_pin_set(port, gpio, value);
पूर्ण

अटल स्थिर काष्ठा gpio_chip rza1_gpiochip_ढाँचा = अणु
	.request		= rza1_gpio_request,
	.मुक्त			= rza1_gpio_मुक्त,
	.get_direction		= rza1_gpio_get_direction,
	.direction_input	= rza1_gpio_direction_input,
	.direction_output	= rza1_gpio_direction_output,
	.get			= rza1_gpio_get,
	.set			= rza1_gpio_set,
पूर्ण;
/* ----------------------------------------------------------------------------
 * pinctrl operations
 */

/**
 * rza1_dt_node_pin_count() - Count number of pins in a dt node or in all its
 *			      children sub-nodes
 *
 * @np: device tree node to parse
 */
अटल पूर्णांक rza1_dt_node_pin_count(काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	काष्ठा property *of_pins;
	अचिन्हित पूर्णांक npins;

	of_pins = of_find_property(np, "pinmux", शून्य);
	अगर (of_pins)
		वापस of_pins->length / माप(u32);

	npins = 0;
	क्रम_each_child_of_node(np, child) अणु
		of_pins = of_find_property(child, "pinmux", शून्य);
		अगर (!of_pins) अणु
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण

		npins += of_pins->length / माप(u32);
	पूर्ण

	वापस npins;
पूर्ण

/**
 * rza1_parse_pmx_function() - parse a pin mux sub-node
 *
 * @rza1_pctl: RZ/A1 pin controller device
 * @np: of pmx sub-node
 * @mux_confs: array of pin mux configurations to fill with parsed info
 * @grpins: array of pin ids to mux
 */
अटल पूर्णांक rza1_parse_pinmux_node(काष्ठा rza1_pinctrl *rza1_pctl,
				  काष्ठा device_node *np,
				  काष्ठा rza1_mux_conf *mux_confs,
				  अचिन्हित पूर्णांक *grpins)
अणु
	काष्ठा pinctrl_dev *pctldev = rza1_pctl->pctl;
	अक्षर स्थिर *prop_name = "pinmux";
	अचिन्हित दीर्घ *pin_configs;
	अचिन्हित पूर्णांक npin_configs;
	काष्ठा property *of_pins;
	अचिन्हित पूर्णांक npins;
	u8 pinmux_flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	of_pins = of_find_property(np, prop_name, शून्य);
	अगर (!of_pins) अणु
		dev_dbg(rza1_pctl->dev, "Missing %s property\n", prop_name);
		वापस -ENOENT;
	पूर्ण
	npins = of_pins->length / माप(u32);

	/*
	 * Collect pin configuration properties: they apply to all pins in
	 * this sub-node
	 */
	ret = pinconf_generic_parse_dt_config(np, pctldev, &pin_configs,
					      &npin_configs);
	अगर (ret) अणु
		dev_err(rza1_pctl->dev,
			"Unable to parse pin configuration options for %pOFn\n",
			np);
		वापस ret;
	पूर्ण

	/*
	 * Create a mask with pinmux flags from pin configuration;
	 * very few pins (TIOC[0-4][A|B|C|D] require SWIO direction
	 * specअगरied in device tree.
	 */
	pinmux_flags = 0;
	क्रम (i = 0; i < npin_configs && pinmux_flags == 0; i++)
		चयन (pinconf_to_config_param(pin_configs[i])) अणु
		हाल PIN_CONFIG_INPUT_ENABLE:
			pinmux_flags |= MUX_FLAGS_SWIO_INPUT;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:	/* क्रम DT backwards compatibility */
		हाल PIN_CONFIG_OUTPUT_ENABLE:
			pinmux_flags |= MUX_FLAGS_SWIO_OUTPUT;
			अवरोध;
		शेष:
			अवरोध;

		पूर्ण

	kमुक्त(pin_configs);

	/* Collect pin positions and their mux settings. */
	क्रम (i = 0; i < npins; ++i) अणु
		u32 of_pinconf;
		काष्ठा rza1_mux_conf *mux_conf = &mux_confs[i];

		ret = of_property_पढ़ो_u32_index(np, prop_name, i, &of_pinconf);
		अगर (ret)
			वापस ret;

		mux_conf->id		= of_pinconf & MUX_PIN_ID_MASK;
		mux_conf->port		= RZA1_PIN_ID_TO_PORT(mux_conf->id);
		mux_conf->pin		= RZA1_PIN_ID_TO_PIN(mux_conf->id);
		mux_conf->mux_func	= MUX_FUNC(of_pinconf);
		mux_conf->mux_flags	= pinmux_flags;

		अगर (mux_conf->port >= RZA1_NPORTS ||
		    mux_conf->pin >= RZA1_PINS_PER_PORT) अणु
			dev_err(rza1_pctl->dev,
				"Wrong port %u pin %u for %s property\n",
				mux_conf->port, mux_conf->pin, prop_name);
			वापस -EINVAL;
		पूर्ण

		grpins[i] = mux_conf->id;
	पूर्ण

	वापस npins;
पूर्ण

/**
 * rza1_dt_node_to_map() - map a pin mux node to a function/group
 *
 * Parse and रेजिस्टर a pin mux function.
 *
 * @pctldev: pin controller device
 * @np: device tree node to parse
 * @map: poपूर्णांकer to pin map (output)
 * @num_maps: number of collected maps (output)
 */
अटल पूर्णांक rza1_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा device_node *np,
			       काष्ठा pinctrl_map **map,
			       अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा rza1_pinctrl *rza1_pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा rza1_mux_conf *mux_confs, *mux_conf;
	अचिन्हित पूर्णांक *grpins, *grpin;
	काष्ठा device_node *child;
	स्थिर अक्षर *grpname;
	स्थिर अक्षर **fngrps;
	पूर्णांक ret, npins;
	पूर्णांक gsel, fsel;

	npins = rza1_dt_node_pin_count(np);
	अगर (npins < 0) अणु
		dev_err(rza1_pctl->dev, "invalid pinmux node structure\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Functions are made of 1 group only;
	 * in fact, functions and groups are identical क्रम this pin controller
	 * except that functions carry an array of per-pin mux configuration
	 * settings.
	 */
	mux_confs = devm_kसुस्मृति(rza1_pctl->dev, npins, माप(*mux_confs),
				 GFP_KERNEL);
	grpins = devm_kसुस्मृति(rza1_pctl->dev, npins, माप(*grpins),
			      GFP_KERNEL);
	fngrps = devm_kzalloc(rza1_pctl->dev, माप(*fngrps), GFP_KERNEL);

	अगर (!mux_confs || !grpins || !fngrps)
		वापस -ENOMEM;

	/*
	 * Parse the pinmux node.
	 * If the node करोes not contain "pinmux" property (-ENOENT)
	 * that property shall be specअगरied in all its children sub-nodes.
	 */
	mux_conf = &mux_confs[0];
	grpin = &grpins[0];

	ret = rza1_parse_pinmux_node(rza1_pctl, np, mux_conf, grpin);
	अगर (ret == -ENOENT)
		क्रम_each_child_of_node(np, child) अणु
			ret = rza1_parse_pinmux_node(rza1_pctl, child, mux_conf,
						     grpin);
			अगर (ret < 0) अणु
				of_node_put(child);
				वापस ret;
			पूर्ण

			grpin += ret;
			mux_conf += ret;
		पूर्ण
	अन्यथा अगर (ret < 0)
		वापस ret;

	/* Register pin group and function name to pinctrl_generic */
	grpname	= np->name;
	fngrps[0] = grpname;

	mutex_lock(&rza1_pctl->mutex);
	gsel = pinctrl_generic_add_group(pctldev, grpname, grpins, npins,
					 शून्य);
	अगर (gsel < 0) अणु
		mutex_unlock(&rza1_pctl->mutex);
		वापस gsel;
	पूर्ण

	fsel = pinmux_generic_add_function(pctldev, grpname, fngrps, 1,
					   mux_confs);
	अगर (fsel < 0) अणु
		ret = fsel;
		जाओ हटाओ_group;
	पूर्ण

	dev_info(rza1_pctl->dev, "Parsed function and group %s with %d pins\n",
				 grpname, npins);

	/* Create map where to retrieve function and mux settings from */
	*num_maps = 0;
	*map = kzalloc(माप(**map), GFP_KERNEL);
	अगर (!*map) अणु
		ret = -ENOMEM;
		जाओ हटाओ_function;
	पूर्ण

	(*map)->type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)->data.mux.group = np->name;
	(*map)->data.mux.function = np->name;
	*num_maps = 1;
	mutex_unlock(&rza1_pctl->mutex);

	वापस 0;

हटाओ_function:
	pinmux_generic_हटाओ_function(pctldev, fsel);

हटाओ_group:
	pinctrl_generic_हटाओ_group(pctldev, gsel);
	mutex_unlock(&rza1_pctl->mutex);

	dev_info(rza1_pctl->dev, "Unable to parse function and group %s\n",
				 grpname);

	वापस ret;
पूर्ण

अटल व्योम rza1_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
			     काष्ठा pinctrl_map *map, अचिन्हित पूर्णांक num_maps)
अणु
	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops rza1_pinctrl_ops = अणु
	.get_groups_count	= pinctrl_generic_get_group_count,
	.get_group_name		= pinctrl_generic_get_group_name,
	.get_group_pins		= pinctrl_generic_get_group_pins,
	.dt_node_to_map		= rza1_dt_node_to_map,
	.dt_मुक्त_map		= rza1_dt_मुक्त_map,
पूर्ण;

/* ----------------------------------------------------------------------------
 * pinmux operations
 */

/**
 * rza1_set_mux() - retrieve pins from a group and apply their mux settings
 *
 * @pctldev: pin controller device
 * @selector: function selector
 * @group: group selector
 */
अटल पूर्णांक rza1_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक selector,
			   अचिन्हित पूर्णांक group)
अणु
	काष्ठा rza1_pinctrl *rza1_pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा rza1_mux_conf *mux_confs;
	काष्ठा function_desc *func;
	काष्ठा group_desc *grp;
	पूर्णांक i;

	grp = pinctrl_generic_get_group(pctldev, group);
	अगर (!grp)
		वापस -EINVAL;

	func = pinmux_generic_get_function(pctldev, selector);
	अगर (!func)
		वापस -EINVAL;

	mux_confs = (काष्ठा rza1_mux_conf *)func->data;
	क्रम (i = 0; i < grp->num_pins; ++i) अणु
		पूर्णांक ret;

		ret = rza1_pin_mux_single(rza1_pctl, &mux_confs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops rza1_pinmux_ops = अणु
	.get_functions_count	= pinmux_generic_get_function_count,
	.get_function_name	= pinmux_generic_get_function_name,
	.get_function_groups	= pinmux_generic_get_function_groups,
	.set_mux		= rza1_set_mux,
	.strict			= true,
पूर्ण;

/* ----------------------------------------------------------------------------
 * RZ/A1 pin controller driver operations
 */

अटल अचिन्हित पूर्णांक rza1_count_gpio_chips(काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक count = 0;

	क्रम_each_child_of_node(np, child) अणु
		अगर (!of_property_पढ़ो_bool(child, "gpio-controller"))
			जारी;

		count++;
	पूर्ण

	वापस count;
पूर्ण

/**
 * rza1_parse_gpiochip() - parse and रेजिस्टर a gpio chip and pin range
 *
 * The gpio controller subnode shall provide a "gpio-ranges" list property as
 * defined by gpio device tree binding करोcumentation.
 *
 * @rza1_pctl: RZ/A1 pin controller device
 * @np: of gpio-controller node
 * @chip: gpio chip to रेजिस्टर to gpiolib
 * @range: pin range to रेजिस्टर to pinctrl core
 */
अटल पूर्णांक rza1_parse_gpiochip(काष्ठा rza1_pinctrl *rza1_pctl,
			       काष्ठा device_node *np,
			       काष्ठा gpio_chip *chip,
			       काष्ठा pinctrl_gpio_range *range)
अणु
	स्थिर अक्षर *list_name = "gpio-ranges";
	काष्ठा of_phandle_args of_args;
	अचिन्हित पूर्णांक gpioport;
	u32 pinctrl_base;
	पूर्णांक ret;

	ret = of_parse_phandle_with_fixed_args(np, list_name, 3, 0, &of_args);
	अगर (ret) अणु
		dev_err(rza1_pctl->dev, "Unable to parse %s list property\n",
			list_name);
		वापस ret;
	पूर्ण

	/*
	 * Find out on which port this gpio-chip maps to by inspecting the
	 * second argument of the "gpio-ranges" property.
	 */
	pinctrl_base = of_args.args[1];
	gpioport = RZA1_PIN_ID_TO_PORT(pinctrl_base);
	अगर (gpioport >= RZA1_NPORTS) अणु
		dev_err(rza1_pctl->dev,
			"Invalid values in property %s\n", list_name);
		वापस -EINVAL;
	पूर्ण

	*chip		= rza1_gpiochip_ढाँचा;
	chip->base	= -1;
	chip->label	= devm_kaप्र_लिखो(rza1_pctl->dev, GFP_KERNEL, "%pOFn",
					 np);
	अगर (!chip->label)
		वापस -ENOMEM;

	chip->ngpio	= of_args.args[2];
	chip->of_node	= np;
	chip->parent	= rza1_pctl->dev;

	range->id	= gpioport;
	range->name	= chip->label;
	range->pin_base	= range->base = pinctrl_base;
	range->npins	= of_args.args[2];
	range->gc	= chip;

	ret = devm_gpiochip_add_data(rza1_pctl->dev, chip,
				     &rza1_pctl->ports[gpioport]);
	अगर (ret)
		वापस ret;

	pinctrl_add_gpio_range(rza1_pctl->pctl, range);

	dev_dbg(rza1_pctl->dev, "Parsed gpiochip %s with %d pins\n",
		chip->label, chip->ngpio);

	वापस 0;
पूर्ण

/**
 * rza1_gpio_रेजिस्टर() - parse DT to collect gpio-chips and gpio-ranges
 *
 * @rza1_pctl: RZ/A1 pin controller device
 */
अटल पूर्णांक rza1_gpio_रेजिस्टर(काष्ठा rza1_pinctrl *rza1_pctl)
अणु
	काष्ठा device_node *np = rza1_pctl->dev->of_node;
	काष्ठा pinctrl_gpio_range *gpio_ranges;
	काष्ठा gpio_chip *gpio_chips;
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक ngpiochips;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ngpiochips = rza1_count_gpio_chips(np);
	अगर (ngpiochips == 0) अणु
		dev_dbg(rza1_pctl->dev, "No gpiochip registered\n");
		वापस 0;
	पूर्ण

	gpio_chips = devm_kसुस्मृति(rza1_pctl->dev, ngpiochips,
				  माप(*gpio_chips), GFP_KERNEL);
	gpio_ranges = devm_kसुस्मृति(rza1_pctl->dev, ngpiochips,
				   माप(*gpio_ranges), GFP_KERNEL);
	अगर (!gpio_chips || !gpio_ranges)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_child_of_node(np, child) अणु
		अगर (!of_property_पढ़ो_bool(child, "gpio-controller"))
			जारी;

		ret = rza1_parse_gpiochip(rza1_pctl, child, &gpio_chips[i],
					  &gpio_ranges[i]);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण

		++i;
	पूर्ण

	dev_info(rza1_pctl->dev, "Registered %u gpio controllers\n", i);

	वापस 0;
पूर्ण

/**
 * rza1_pinctrl_रेजिस्टर() - Enumerate pins, ports and gpiochips; रेजिस्टर
 *			     them to pinctrl and gpio cores.
 *
 * @rza1_pctl: RZ/A1 pin controller device
 */
अटल पूर्णांक rza1_pinctrl_रेजिस्टर(काष्ठा rza1_pinctrl *rza1_pctl)
अणु
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा rza1_port *ports;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	pins = devm_kसुस्मृति(rza1_pctl->dev, RZA1_NPINS, माप(*pins),
			    GFP_KERNEL);
	ports = devm_kसुस्मृति(rza1_pctl->dev, RZA1_NPORTS, माप(*ports),
			     GFP_KERNEL);
	अगर (!pins || !ports)
		वापस -ENOMEM;

	rza1_pctl->pins		= pins;
	rza1_pctl->desc.pins	= pins;
	rza1_pctl->desc.npins	= RZA1_NPINS;
	rza1_pctl->ports	= ports;

	क्रम (i = 0; i < RZA1_NPINS; ++i) अणु
		अचिन्हित पूर्णांक pin = RZA1_PIN_ID_TO_PIN(i);
		अचिन्हित पूर्णांक port = RZA1_PIN_ID_TO_PORT(i);

		pins[i].number = i;
		pins[i].name = devm_kaप्र_लिखो(rza1_pctl->dev, GFP_KERNEL,
					      "P%u-%u", port, pin);
		अगर (!pins[i].name)
			वापस -ENOMEM;

		अगर (i % RZA1_PINS_PER_PORT == 0) अणु
			/*
			 * Setup ports;
			 * they provide per-port lock and logical base address.
			 */
			अचिन्हित पूर्णांक port_id = RZA1_PIN_ID_TO_PORT(i);

			ports[port_id].id	= port_id;
			ports[port_id].base	= rza1_pctl->base;
			ports[port_id].pins	= &pins[i];
			spin_lock_init(&ports[port_id].lock);
		पूर्ण
	पूर्ण

	ret = devm_pinctrl_रेजिस्टर_and_init(rza1_pctl->dev, &rza1_pctl->desc,
					     rza1_pctl, &rza1_pctl->pctl);
	अगर (ret) अणु
		dev_err(rza1_pctl->dev,
			"RZ/A1 pin controller registration failed\n");
		वापस ret;
	पूर्ण

	ret = pinctrl_enable(rza1_pctl->pctl);
	अगर (ret) अणु
		dev_err(rza1_pctl->dev,
			"RZ/A1 pin controller failed to start\n");
		वापस ret;
	पूर्ण

	ret = rza1_gpio_रेजिस्टर(rza1_pctl);
	अगर (ret) अणु
		dev_err(rza1_pctl->dev, "RZ/A1 GPIO registration failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rza1_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rza1_pinctrl *rza1_pctl;
	पूर्णांक ret;

	rza1_pctl = devm_kzalloc(&pdev->dev, माप(*rza1_pctl), GFP_KERNEL);
	अगर (!rza1_pctl)
		वापस -ENOMEM;

	rza1_pctl->dev = &pdev->dev;

	rza1_pctl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rza1_pctl->base))
		वापस PTR_ERR(rza1_pctl->base);

	mutex_init(&rza1_pctl->mutex);

	platक्रमm_set_drvdata(pdev, rza1_pctl);

	rza1_pctl->desc.name	= DRIVER_NAME;
	rza1_pctl->desc.pctlops	= &rza1_pinctrl_ops;
	rza1_pctl->desc.pmxops	= &rza1_pinmux_ops;
	rza1_pctl->desc.owner	= THIS_MODULE;
	rza1_pctl->data		= of_device_get_match_data(&pdev->dev);

	ret = rza1_pinctrl_रेजिस्टर(rza1_pctl);
	अगर (ret)
		वापस ret;

	dev_info(&pdev->dev,
		 "RZ/A1 pin controller and gpio successfully registered\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rza1_pinctrl_of_match[] = अणु
	अणु
		/* RZ/A1H, RZ/A1M */
		.compatible	= "renesas,r7s72100-ports",
		.data		= &rza1h_pmx_conf,
	पूर्ण,
	अणु
		/* RZ/A1L */
		.compatible	= "renesas,r7s72102-ports",
		.data		= &rza1l_pmx_conf,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver rza1_pinctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = rza1_pinctrl_of_match,
	पूर्ण,
	.probe = rza1_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init rza1_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rza1_pinctrl_driver);
पूर्ण
core_initcall(rza1_pinctrl_init);

MODULE_AUTHOR("Jacopo Mondi <jacopo+renesas@jmondi.org");
MODULE_DESCRIPTION("Pin and gpio controller driver for Reneas RZ/A1 SoC");
MODULE_LICENSE("GPL v2");
