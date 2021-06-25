<शैली गुरु>
/*
 * Driver क्रम the Axis ARTPEC-6 pin controller
 *
 * Author: Chris Paterson <chris.paterson@linux.pieboy.co.uk>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/slab.h>
#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

#घोषणा ARTPEC6_LAST_PIN	97	/* 97 pins in pinmux */
#घोषणा ARTPEC6_MAX_MUXABLE	35	/* Last pin with muxable function */

/* Pinmux control रेजिस्टर bit definitions */
#घोषणा ARTPEC6_PINMUX_UDC0_MASK	0x00000001
#घोषणा ARTPEC6_PINMUX_UDC0_SHIFT	0
#घोषणा ARTPEC6_PINMUX_UDC1_MASK	0x00000002
#घोषणा ARTPEC6_PINMUX_UDC1_SHIFT	1
#घोषणा ARTPEC6_PINMUX_DRV_MASK		0x00000060
#घोषणा ARTPEC6_PINMUX_DRV_SHIFT	5
#घोषणा ARTPEC6_PINMUX_SEL_MASK		0x00003000
#घोषणा ARTPEC6_PINMUX_SEL_SHIFT	12

/* Pinmux configurations */
#घोषणा ARTPEC6_CONFIG_0		0
#घोषणा ARTPEC6_CONFIG_1		1
#घोषणा ARTPEC6_CONFIG_2		2
#घोषणा ARTPEC6_CONFIG_3		3

/* Pin drive strength options */
#घोषणा ARTPEC6_DRIVE_4mA		4
#घोषणा ARTPEC6_DRIVE_4mA_SET		0
#घोषणा ARTPEC6_DRIVE_6mA		6
#घोषणा ARTPEC6_DRIVE_6mA_SET		1
#घोषणा ARTPEC6_DRIVE_8mA		8
#घोषणा ARTPEC6_DRIVE_8mA_SET		2
#घोषणा ARTPEC6_DRIVE_9mA		9
#घोषणा ARTPEC6_DRIVE_9mA_SET		3

काष्ठा artpec6_pmx अणु
	काष्ठा device			*dev;
	काष्ठा pinctrl_dev		*pctl;
	व्योम __iomem			*base;
	काष्ठा pinctrl_pin_desc		*pins;
	अचिन्हित पूर्णांक			num_pins;
	स्थिर काष्ठा artpec6_pin_group	*pin_groups;
	अचिन्हित पूर्णांक			num_pin_groups;
	स्थिर काष्ठा artpec6_pmx_func	*functions;
	अचिन्हित पूर्णांक			num_functions;
पूर्ण;

काष्ठा artpec6_pin_group अणु
	स्थिर अक्षर	   *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक num_pins;
	अचिन्हित अक्षर	   config;
पूर्ण;

काष्ठा artpec6_pmx_func अणु
	स्थिर अक्षर	   *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित पूर्णांक num_groups;
पूर्ण;

/* pins */
अटल काष्ठा pinctrl_pin_desc artpec6_pins[] = अणु
	PINCTRL_PIN(0, "GPIO0"),
	PINCTRL_PIN(1, "GPIO1"),
	PINCTRL_PIN(2, "GPIO2"),
	PINCTRL_PIN(3, "GPIO3"),
	PINCTRL_PIN(4, "GPIO4"),
	PINCTRL_PIN(5, "GPIO5"),
	PINCTRL_PIN(6, "GPIO6"),
	PINCTRL_PIN(7, "GPIO7"),
	PINCTRL_PIN(8, "GPIO8"),
	PINCTRL_PIN(9, "GPIO9"),
	PINCTRL_PIN(10, "GPIO10"),
	PINCTRL_PIN(11, "GPIO11"),
	PINCTRL_PIN(12, "GPIO12"),
	PINCTRL_PIN(13, "GPIO13"),
	PINCTRL_PIN(14, "GPIO14"),
	PINCTRL_PIN(15, "GPIO15"),
	PINCTRL_PIN(16, "GPIO16"),
	PINCTRL_PIN(17, "GPIO17"),
	PINCTRL_PIN(18, "GPIO18"),
	PINCTRL_PIN(19, "GPIO19"),
	PINCTRL_PIN(20, "GPIO20"),
	PINCTRL_PIN(21, "GPIO21"),
	PINCTRL_PIN(22, "GPIO22"),
	PINCTRL_PIN(23, "GPIO23"),
	PINCTRL_PIN(24, "GPIO24"),
	PINCTRL_PIN(25, "GPIO25"),
	PINCTRL_PIN(26, "GPIO26"),
	PINCTRL_PIN(27, "GPIO27"),
	PINCTRL_PIN(28, "GPIO28"),
	PINCTRL_PIN(29, "GPIO29"),
	PINCTRL_PIN(30, "GPIO30"),
	PINCTRL_PIN(31, "GPIO31"),
	PINCTRL_PIN(32, "UART3_TXD"),
	PINCTRL_PIN(33, "UART3_RXD"),
	PINCTRL_PIN(34, "UART3_RTS"),
	PINCTRL_PIN(35, "UART3_CTS"),
	PINCTRL_PIN(36, "NF_ALE"),
	PINCTRL_PIN(37, "NF_CE0_N"),
	PINCTRL_PIN(38, "NF_CE1_N"),
	PINCTRL_PIN(39, "NF_CLE"),
	PINCTRL_PIN(40, "NF_RE_N"),
	PINCTRL_PIN(41, "NF_WE_N"),
	PINCTRL_PIN(42, "NF_WP0_N"),
	PINCTRL_PIN(43, "NF_WP1_N"),
	PINCTRL_PIN(44, "NF_IO0"),
	PINCTRL_PIN(45, "NF_IO1"),
	PINCTRL_PIN(46, "NF_IO2"),
	PINCTRL_PIN(47, "NF_IO3"),
	PINCTRL_PIN(48, "NF_IO4"),
	PINCTRL_PIN(49, "NF_IO5"),
	PINCTRL_PIN(50, "NF_IO6"),
	PINCTRL_PIN(51, "NF_IO7"),
	PINCTRL_PIN(52, "NF_RB0_N"),
	PINCTRL_PIN(53, "SDIO0_CLK"),
	PINCTRL_PIN(54, "SDIO0_CMD"),
	PINCTRL_PIN(55, "SDIO0_DAT0"),
	PINCTRL_PIN(56, "SDIO0_DAT1"),
	PINCTRL_PIN(57, "SDIO0_DAT2"),
	PINCTRL_PIN(58, "SDIO0_DAT3"),
	PINCTRL_PIN(59, "SDI0_CD"),
	PINCTRL_PIN(60, "SDI0_WP"),
	PINCTRL_PIN(61, "SDIO1_CLK"),
	PINCTRL_PIN(62, "SDIO1_CMD"),
	PINCTRL_PIN(63, "SDIO1_DAT0"),
	PINCTRL_PIN(64, "SDIO1_DAT1"),
	PINCTRL_PIN(65, "SDIO1_DAT2"),
	PINCTRL_PIN(66, "SDIO1_DAT3"),
	PINCTRL_PIN(67, "SDIO1_CD"),
	PINCTRL_PIN(68, "SDIO1_WP"),
	PINCTRL_PIN(69, "GBE_REFCLk"),
	PINCTRL_PIN(70, "GBE_GTX_CLK"),
	PINCTRL_PIN(71, "GBE_TX_CLK"),
	PINCTRL_PIN(72, "GBE_TX_EN"),
	PINCTRL_PIN(73, "GBE_TX_ER"),
	PINCTRL_PIN(74, "GBE_TXD0"),
	PINCTRL_PIN(75, "GBE_TXD1"),
	PINCTRL_PIN(76, "GBE_TXD2"),
	PINCTRL_PIN(77, "GBE_TXD3"),
	PINCTRL_PIN(78, "GBE_TXD4"),
	PINCTRL_PIN(79, "GBE_TXD5"),
	PINCTRL_PIN(80, "GBE_TXD6"),
	PINCTRL_PIN(81, "GBE_TXD7"),
	PINCTRL_PIN(82, "GBE_RX_CLK"),
	PINCTRL_PIN(83, "GBE_RX_DV"),
	PINCTRL_PIN(84, "GBE_RX_ER"),
	PINCTRL_PIN(85, "GBE_RXD0"),
	PINCTRL_PIN(86, "GBE_RXD1"),
	PINCTRL_PIN(87, "GBE_RXD2"),
	PINCTRL_PIN(88, "GBE_RXD3"),
	PINCTRL_PIN(89, "GBE_RXD4"),
	PINCTRL_PIN(90, "GBE_RXD5"),
	PINCTRL_PIN(91, "GBE_RXD6"),
	PINCTRL_PIN(92, "GBE_RXD7"),
	PINCTRL_PIN(93, "GBE_CRS"),
	PINCTRL_PIN(94, "GBE_COL"),
	PINCTRL_PIN(95, "GBE_MDC"),
	PINCTRL_PIN(96, "GBE_MDIO"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक cpuclkout_pins0[] = अणु 0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक udlclkout_pins0[] = अणु 1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_pins0[] = अणु 2, 3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_pins0[] = अणु 4, 5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c3_pins0[] = अणु 6, 7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s0_pins0[] = अणु 8, 9, 10, 11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s1_pins0[] = अणु 12, 13, 14, 15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2srefclk_pins0[] = अणु 19 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_pins0[] = अणु 12, 13, 14, 15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_pins0[] = अणु 16, 17, 18, 19 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pciedebug_pins0[] = अणु 12, 13, 14, 15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_pins0[] = अणु 16, 17, 18, 19, 20,
					    21, 22, 23, 24, 25 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_pins1[] = अणु 20, 21, 22, 23 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_pins0[] = अणु 24, 25, 26, 27 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart2_pins0[] = अणु 26, 27, 28, 29, 30,
					    31, 32, 33, 34, 35 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart2_pins1[] = अणु 28, 29, 30, 31 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart3_pins0[] = अणु 32, 33, 34, 35 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart4_pins0[] = अणु 20, 21, 22, 23 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart5_pins0[] = अणु 28, 29, 30, 31 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_pins0[]  = अणु 36, 37, 38, 39, 40, 41,
					    42, 43, 44, 45, 46, 47,
					    48, 49, 50, 51, 52 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio0_pins0[] = अणु 53, 54, 55, 56, 57, 58, 59, 60 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio1_pins0[] = अणु 61, 62, 63, 64, 65, 66, 67, 68 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ethernet_pins0[]  = अणु 69, 70, 71, 72, 73, 74, 75,
						76, 77, 78, 79, 80, 81, 82,
						83, 84,	85, 86, 87, 88, 89,
						90, 91, 92, 93, 94, 95, 96 पूर्ण;

अटल स्थिर काष्ठा artpec6_pin_group artpec6_pin_groups[] = अणु
	अणु
		.name = "cpuclkoutgrp0",
		.pins = cpuclkout_pins0,
		.num_pins = ARRAY_SIZE(cpuclkout_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "udlclkoutgrp0",
		.pins = udlclkout_pins0,
		.num_pins = ARRAY_SIZE(udlclkout_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "i2c1grp0",
		.pins = i2c1_pins0,
		.num_pins = ARRAY_SIZE(i2c1_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "i2c2grp0",
		.pins = i2c2_pins0,
		.num_pins = ARRAY_SIZE(i2c2_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "i2c3grp0",
		.pins = i2c3_pins0,
		.num_pins = ARRAY_SIZE(i2c3_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "i2s0grp0",
		.pins = i2s0_pins0,
		.num_pins = ARRAY_SIZE(i2s0_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "i2s1grp0",
		.pins = i2s1_pins0,
		.num_pins = ARRAY_SIZE(i2s1_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "i2srefclkgrp0",
		.pins = i2srefclk_pins0,
		.num_pins = ARRAY_SIZE(i2srefclk_pins0),
		.config = ARTPEC6_CONFIG_3,
	पूर्ण,
	अणु
		.name = "spi0grp0",
		.pins = spi0_pins0,
		.num_pins = ARRAY_SIZE(spi0_pins0),
		.config = ARTPEC6_CONFIG_2,
	पूर्ण,
	अणु
		.name = "spi1grp0",
		.pins = spi1_pins0,
		.num_pins = ARRAY_SIZE(spi1_pins0),
		.config = ARTPEC6_CONFIG_2,
	पूर्ण,
	अणु
		.name = "pciedebuggrp0",
		.pins = pciedebug_pins0,
		.num_pins = ARRAY_SIZE(pciedebug_pins0),
		.config = ARTPEC6_CONFIG_3,
	पूर्ण,
	अणु
		.name = "uart0grp0",	/* All pins. */
		.pins = uart0_pins0,
		.num_pins = ARRAY_SIZE(uart0_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "uart0grp1",	/* RX/TX and RTS/CTS */
		.pins = uart0_pins1,
		.num_pins = ARRAY_SIZE(uart0_pins1),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "uart0grp2",	/* Only RX/TX pins. */
		.pins = uart0_pins1,
		.num_pins = ARRAY_SIZE(uart0_pins1) - 2,
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "uart1grp0",	/* RX/TX and RTS/CTS */
		.pins = uart1_pins0,
		.num_pins = ARRAY_SIZE(uart1_pins0),
		.config = ARTPEC6_CONFIG_2,
	पूर्ण,
	अणु
		.name = "uart1grp1",	/* Only RX/TX pins. */
		.pins = uart1_pins0,
		.num_pins = 2,
		.config = ARTPEC6_CONFIG_2,
	पूर्ण,
	अणु
		.name = "uart2grp0",	/* Full pinout */
		.pins = uart2_pins0,
		.num_pins = ARRAY_SIZE(uart2_pins0),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "uart2grp1",	/* RX/TX and RTS/CTS */
		.pins = uart2_pins1,
		.num_pins = ARRAY_SIZE(uart2_pins1),
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "uart2grp2",	/* Only RX/TX */
		.pins = uart2_pins1,
		.num_pins = 2,
		.config = ARTPEC6_CONFIG_1,
	पूर्ण,
	अणु
		.name = "uart3grp0",	/* RX/TX and CTS/RTS */
		.pins = uart3_pins0,
		.num_pins = ARRAY_SIZE(uart3_pins0),
		.config = ARTPEC6_CONFIG_0,
	पूर्ण,
	अणु
		.name = "uart3grp1",	/* Only RX/TX */
		.pins = uart3_pins0,
		.num_pins = ARRAY_SIZE(uart3_pins0),
		.config = ARTPEC6_CONFIG_0,
	पूर्ण,
	अणु
		.name = "uart4grp0",
		.pins = uart4_pins0,
		.num_pins = ARRAY_SIZE(uart4_pins0),
		.config = ARTPEC6_CONFIG_2,
	पूर्ण,
	अणु
		.name = "uart5grp0",	/* TX/RX and RTS/CTS */
		.pins = uart5_pins0,
		.num_pins = ARRAY_SIZE(uart5_pins0),
		.config = ARTPEC6_CONFIG_2,
	पूर्ण,
	अणु
		.name = "uart5grp1",	/* Only TX/RX */
		.pins = uart5_pins0,
		.num_pins = 2,
		.config = ARTPEC6_CONFIG_2,
	पूर्ण,
	अणु
		.name = "uart5nocts",	/* TX/RX/RTS */
		.pins = uart5_pins0,
		.num_pins = ARRAY_SIZE(uart5_pins0) - 1,
		.config = ARTPEC6_CONFIG_2,
	पूर्ण,
	अणु
		.name = "nandgrp0",
		.pins = nand_pins0,
		.num_pins = ARRAY_SIZE(nand_pins0),
		.config = ARTPEC6_CONFIG_0,
	पूर्ण,
	अणु
		.name = "sdio0grp0",
		.pins = sdio0_pins0,
		.num_pins = ARRAY_SIZE(sdio0_pins0),
		.config = ARTPEC6_CONFIG_0,
	पूर्ण,
	अणु
		.name = "sdio1grp0",
		.pins = sdio1_pins0,
		.num_pins = ARRAY_SIZE(sdio1_pins0),
		.config = ARTPEC6_CONFIG_0,
	पूर्ण,
	अणु
		.name = "ethernetgrp0",
		.pins = ethernet_pins0,
		.num_pins = ARRAY_SIZE(ethernet_pins0),
		.config = ARTPEC6_CONFIG_0,
	पूर्ण,
पूर्ण;

काष्ठा pin_रेजिस्टर अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक end;
	अचिन्हित पूर्णांक reg_base;
पूर्ण;

/*
 * The रेजिस्टर map has two holes where the pin number
 * no दीर्घer fits directly with the रेजिस्टर offset.
 * This table allows us to map this easily.
 */
अटल स्थिर काष्ठा pin_रेजिस्टर pin_रेजिस्टर[] = अणु
	अणु 0, 35, 0x0 पूर्ण,		/* 0x0 - 0x8c */
	अणु 36, 52, 0x100 पूर्ण,	/* 0x100 - 0x140 */
	अणु 53, 96, 0x180 पूर्ण,	/* 0x180 - 0x22c */
पूर्ण;

अटल अचिन्हित पूर्णांक artpec6_pmx_reg_offset(अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pin_रेजिस्टर); i++) अणु
		अगर (pin <= pin_रेजिस्टर[i].end) अणु
			वापस (pin - pin_रेजिस्टर[i].start) * 4 +
				pin_रेजिस्टर[i].reg_base;
		पूर्ण
	पूर्ण
	/*
	 * Anything we वापस here is wrong, but we can only
	 * get here अगर pin is outside रेजिस्टरed range.
	 */
	pr_err("%s: Impossible pin %d\n", __func__, pin);
	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(artpec6_pin_groups);
पूर्ण

अटल स्थिर अक्षर *artpec6_get_group_name(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित पूर्णांक group)
अणु
	वापस artpec6_pin_groups[group].name;
पूर्ण

अटल पूर्णांक artpec6_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक group,
				  स्थिर अचिन्हित पूर्णांक **pins,
				  अचिन्हित पूर्णांक *num_pins)
अणु
	*pins = (अचिन्हित पूर्णांक *)artpec6_pin_groups[group].pins;
	*num_pins = artpec6_pin_groups[group].num_pins;
	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_pconf_drive_mA_to_field(अचिन्हित पूर्णांक mA)
अणु
	चयन (mA) अणु
	हाल ARTPEC6_DRIVE_4mA:
		वापस ARTPEC6_DRIVE_4mA_SET;
	हाल ARTPEC6_DRIVE_6mA:
		वापस ARTPEC6_DRIVE_6mA_SET;
	हाल ARTPEC6_DRIVE_8mA:
		वापस ARTPEC6_DRIVE_8mA_SET;
	हाल ARTPEC6_DRIVE_9mA:
		वापस ARTPEC6_DRIVE_9mA_SET;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक artpec6_pconf_drive_field_to_mA(पूर्णांक field)
अणु
	चयन (field) अणु
	हाल ARTPEC6_DRIVE_4mA_SET:
		वापस ARTPEC6_DRIVE_4mA;
	हाल ARTPEC6_DRIVE_6mA_SET:
		वापस ARTPEC6_DRIVE_6mA;
	हाल ARTPEC6_DRIVE_8mA_SET:
		वापस ARTPEC6_DRIVE_8mA;
	हाल ARTPEC6_DRIVE_9mA_SET:
		वापस ARTPEC6_DRIVE_9mA;
	शेष:
		/* Shouldn't happen */
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops artpec6_pctrl_ops = अणु
	.get_group_pins		= artpec6_get_group_pins,
	.get_groups_count	= artpec6_get_groups_count,
	.get_group_name		= artpec6_get_group_name,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpiogrps[] = अणु
	"cpuclkoutgrp0", "udlclkoutgrp0", "i2c1grp0", "i2c2grp0",
	"i2c3grp0", "i2s0grp0", "i2s1grp0", "i2srefclkgrp0",
	"spi0grp0", "spi1grp0", "pciedebuggrp0", "uart0grp0",
	"uart0grp1", "uart0grp2", "uart1grp0", "uart1grp1",
	"uart2grp0", "uart2grp1", "uart2grp2", "uart4grp0", "uart5grp0",
	"uart5grp1", "uart5nocts",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cpuclkoutgrps[] = अणु "cpuclkoutgrp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर udlclkoutgrps[] = अणु "udlclkoutgrp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c1grps[]	  = अणु "i2c1grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c2grps[]	  = अणु "i2c2grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c3grps[]	  = अणु "i2c3grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s0grps[]	  = अणु "i2s0grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s1grps[]	  = अणु "i2s1grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2srefclkgrps[] = अणु "i2srefclkgrp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi0grps[]	  = अणु "spi0grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi1grps[]	  = अणु "spi1grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर pciedebuggrps[] = अणु "pciedebuggrp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart0grps[]	  = अणु "uart0grp0", "uart0grp1",
					      "uart0grp2" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart1grps[]	  = अणु "uart1grp0", "uart1grp1" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart2grps[]	  = अणु "uart2grp0", "uart2grp1",
					      "uart2grp2" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart3grps[]	  = अणु "uart3grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart4grps[]	  = अणु "uart4grp0", "uart4grp1" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart5grps[]	  = अणु "uart5grp0", "uart5grp1",
					      "uart5nocts" पूर्ण;
अटल स्थिर अक्षर * स्थिर nandgrps[]	  = अणु "nandgrp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio0grps[]	  = अणु "sdio0grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio1grps[]	  = अणु "sdio1grp0" पूर्ण;
अटल स्थिर अक्षर * स्थिर ethernetgrps[]  = अणु "ethernetgrp0" पूर्ण;

अटल स्थिर काष्ठा artpec6_pmx_func artpec6_pmx_functions[] = अणु
	अणु
		.name = "gpio",
		.groups = gpiogrps,
		.num_groups = ARRAY_SIZE(gpiogrps),
	पूर्ण,
	अणु
		.name = "cpuclkout",
		.groups = cpuclkoutgrps,
		.num_groups = ARRAY_SIZE(cpuclkoutgrps),
	पूर्ण,
	अणु
		.name = "udlclkout",
		.groups = udlclkoutgrps,
		.num_groups = ARRAY_SIZE(udlclkoutgrps),
	पूर्ण,
	अणु
		.name = "i2c1",
		.groups = i2c1grps,
		.num_groups = ARRAY_SIZE(i2c1grps),
	पूर्ण,
	अणु
		.name = "i2c2",
		.groups = i2c2grps,
		.num_groups = ARRAY_SIZE(i2c2grps),
	पूर्ण,
	अणु
		.name = "i2c3",
		.groups = i2c3grps,
		.num_groups = ARRAY_SIZE(i2c3grps),
	पूर्ण,
	अणु
		.name = "i2s0",
		.groups = i2s0grps,
		.num_groups = ARRAY_SIZE(i2s0grps),
	पूर्ण,
	अणु
		.name = "i2s1",
		.groups = i2s1grps,
		.num_groups = ARRAY_SIZE(i2s1grps),
	पूर्ण,
	अणु
		.name = "i2srefclk",
		.groups = i2srefclkgrps,
		.num_groups = ARRAY_SIZE(i2srefclkgrps),
	पूर्ण,
	अणु
		.name = "spi0",
		.groups = spi0grps,
		.num_groups = ARRAY_SIZE(spi0grps),
	पूर्ण,
	अणु
		.name = "spi1",
		.groups = spi1grps,
		.num_groups = ARRAY_SIZE(spi1grps),
	पूर्ण,
	अणु
		.name = "pciedebug",
		.groups = pciedebuggrps,
		.num_groups = ARRAY_SIZE(pciedebuggrps),
	पूर्ण,
	अणु
		.name = "uart0",
		.groups = uart0grps,
		.num_groups = ARRAY_SIZE(uart0grps),
	पूर्ण,
	अणु
		.name = "uart1",
		.groups = uart1grps,
		.num_groups = ARRAY_SIZE(uart1grps),
	पूर्ण,
	अणु
		.name = "uart2",
		.groups = uart2grps,
		.num_groups = ARRAY_SIZE(uart2grps),
	पूर्ण,
	अणु
		.name = "uart3",
		.groups = uart3grps,
		.num_groups = ARRAY_SIZE(uart3grps),
	पूर्ण,
	अणु
		.name = "uart4",
		.groups = uart4grps,
		.num_groups = ARRAY_SIZE(uart4grps),
	पूर्ण,
	अणु
		.name = "uart5",
		.groups = uart5grps,
		.num_groups = ARRAY_SIZE(uart5grps),
	पूर्ण,
	अणु
		.name = "nand",
		.groups = nandgrps,
		.num_groups = ARRAY_SIZE(nandgrps),
	पूर्ण,
	अणु
		.name = "sdio0",
		.groups = sdio0grps,
		.num_groups = ARRAY_SIZE(sdio0grps),
	पूर्ण,
	अणु
		.name = "sdio1",
		.groups = sdio1grps,
		.num_groups = ARRAY_SIZE(sdio1grps),
	पूर्ण,
	अणु
		.name = "ethernet",
		.groups = ethernetgrps,
		.num_groups = ARRAY_SIZE(ethernetgrps),
	पूर्ण,
पूर्ण;

अटल पूर्णांक artpec6_pmx_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(artpec6_pmx_functions);
पूर्ण

अटल स्थिर अक्षर *artpec6_pmx_get_fname(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित पूर्णांक function)
अणु
	वापस artpec6_pmx_functions[function].name;
पूर्ण

अटल पूर्णांक artpec6_pmx_get_fgroups(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक function,
				   स्थिर अक्षर * स्थिर **groups,
				   अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	*groups = artpec6_pmx_functions[function].groups;
	*num_groups = artpec6_pmx_functions[function].num_groups;
	वापस 0;
पूर्ण

अटल व्योम artpec6_pmx_select_func(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक group,
				    bool enable)
अणु
	अचिन्हित पूर्णांक regval, val;
	अचिन्हित पूर्णांक reg;
	पूर्णांक i;
	काष्ठा artpec6_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	क्रम (i = 0; i < artpec6_pin_groups[group].num_pins; i++) अणु
		/*
		 * Registers क्रम pins above a ARTPEC6_MAX_MUXABLE
		 * करो not have a SEL field and are always selected.
		 */
		अगर (artpec6_pin_groups[group].pins[i] > ARTPEC6_MAX_MUXABLE)
			जारी;

		अगर (!म_भेद(artpec6_pmx_get_fname(pctldev, function), "gpio")) अणु
			/* GPIO is always config 0 */
			val = ARTPEC6_CONFIG_0 << ARTPEC6_PINMUX_SEL_SHIFT;
		पूर्ण अन्यथा अणु
			अगर (enable)
				val = artpec6_pin_groups[group].config
					<< ARTPEC6_PINMUX_SEL_SHIFT;
			अन्यथा
				val = ARTPEC6_CONFIG_0
					<< ARTPEC6_PINMUX_SEL_SHIFT;
		पूर्ण

		reg = artpec6_pmx_reg_offset(artpec6_pin_groups[group].pins[i]);

		regval = पढ़ोl(pmx->base + reg);
		regval &= ~ARTPEC6_PINMUX_SEL_MASK;
		regval |= val;
		ग_लिखोl(regval, pmx->base + reg);
	पूर्ण
पूर्ण

अटल पूर्णांक artpec6_pmx_set(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित पूर्णांक function,
			   अचिन्हित पूर्णांक group)
अणु
	काष्ठा artpec6_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(pmx->dev, "enabling %s function for pin group %s\n",
		artpec6_pmx_get_fname(pctldev, function),
		artpec6_get_group_name(pctldev, group));

	artpec6_pmx_select_func(pctldev, function, group, true);

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_pmx_request_gpio(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_gpio_range *range,
				    अचिन्हित पूर्णांक pin)
अणु
	काष्ठा artpec6_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक reg = artpec6_pmx_reg_offset(pin);
	u32 val;

	अगर (pin >= 32)
		वापस -EINVAL;

	val = पढ़ोl_relaxed(pmx->base + reg);
	val &= ~ARTPEC6_PINMUX_SEL_MASK;
	val |= ARTPEC6_CONFIG_0 << ARTPEC6_PINMUX_SEL_SHIFT;
	ग_लिखोl_relaxed(val, pmx->base + reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops artpec6_pmx_ops = अणु
	.get_functions_count	= artpec6_pmx_get_functions_count,
	.get_function_name	= artpec6_pmx_get_fname,
	.get_function_groups	= artpec6_pmx_get_fgroups,
	.set_mux		= artpec6_pmx_set,
	.gpio_request_enable = artpec6_pmx_request_gpio,
पूर्ण;

अटल पूर्णांक artpec6_pconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			     अचिन्हित दीर्घ *config)
अणु
	काष्ठा artpec6_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक regval;

	/* Check क्रम valid pin */
	अगर (pin >= pmx->num_pins) अणु
		dev_dbg(pmx->dev, "pinconf is not supported for pin %s\n",
			pmx->pins[pin].name);
		वापस -ENOTSUPP;
	पूर्ण

	dev_dbg(pmx->dev, "getting configuration for pin %s\n",
		pmx->pins[pin].name);

	/* Read pin रेजिस्टर values */
	regval = पढ़ोl(pmx->base + artpec6_pmx_reg_offset(pin));

	/* If valid, get configuration क्रम parameter */
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (!(regval & ARTPEC6_PINMUX_UDC1_MASK))
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (regval & ARTPEC6_PINMUX_UDC1_MASK)
			वापस -EINVAL;

		regval = regval & ARTPEC6_PINMUX_UDC0_MASK;
		अगर ((param == PIN_CONFIG_BIAS_PULL_UP && !regval) ||
		    (param == PIN_CONFIG_BIAS_PULL_DOWN && regval))
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		regval = (regval & ARTPEC6_PINMUX_DRV_MASK)
			>> ARTPEC6_PINMUX_DRV_SHIFT;
		regval = artpec6_pconf_drive_field_to_mA(regval);
		*config = pinconf_to_config_packed(param, regval);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Valid combinations of param and arg:
 *
 * param		     arg
 * PIN_CONFIG_BIAS_DISABLE:   x (disable bias)
 * PIN_CONFIG_BIAS_PULL_UP:   1 (pull up bias + enable)
 * PIN_CONFIG_BIAS_PULL_DOWN: 1 (pull करोwn bias + enable)
 * PIN_CONFIG_DRIVE_STRENGTH: x (4mA, 6mA, 8mA, 9mA)
 *
 * All other args are invalid. All other params are not supported.
 */
अटल पूर्णांक artpec6_pconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			     अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा artpec6_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	अचिन्हित पूर्णांक arg;
	अचिन्हित पूर्णांक regval;
	व्योम __iomem *reg;
	पूर्णांक i;

	/* Check क्रम valid pin */
	अगर (pin >= pmx->num_pins) अणु
		dev_dbg(pmx->dev, "pinconf is not supported for pin %s\n",
			pmx->pins[pin].name);
		वापस -ENOTSUPP;
	पूर्ण

	dev_dbg(pmx->dev, "setting configuration for pin %s\n",
		pmx->pins[pin].name);

	reg = pmx->base + artpec6_pmx_reg_offset(pin);

	/* For each config */
	क्रम (i = 0; i < num_configs; i++) अणु
		पूर्णांक drive;

		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			regval = पढ़ोl(reg);
			regval |= (1 << ARTPEC6_PINMUX_UDC1_SHIFT);
			ग_लिखोl(regval, reg);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			अगर (arg != 1) अणु
				dev_dbg(pctldev->dev, "%s: arg %u out of range\n",
					__func__, arg);
				वापस -EINVAL;
			पूर्ण

			regval = पढ़ोl(reg);
			regval |= (arg << ARTPEC6_PINMUX_UDC0_SHIFT);
			regval &= ~ARTPEC6_PINMUX_UDC1_MASK; /* Enable */
			ग_लिखोl(regval, reg);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			अगर (arg != 1) अणु
				dev_dbg(pctldev->dev, "%s: arg %u out of range\n",
					__func__, arg);
				वापस -EINVAL;
			पूर्ण

			regval = पढ़ोl(reg);
			regval &= ~(arg << ARTPEC6_PINMUX_UDC0_SHIFT);
			regval &= ~ARTPEC6_PINMUX_UDC1_MASK; /* Enable */
			ग_लिखोl(regval, reg);
			अवरोध;

		हाल PIN_CONFIG_DRIVE_STRENGTH:
			drive = artpec6_pconf_drive_mA_to_field(arg);
			अगर (drive < 0) अणु
				dev_dbg(pctldev->dev, "%s: arg %u out of range\n",
					__func__, arg);
				वापस -EINVAL;
			पूर्ण

			regval = पढ़ोl(reg);
			regval &= ~ARTPEC6_PINMUX_DRV_MASK;
			regval |= (drive << ARTPEC6_PINMUX_DRV_SHIFT);
			ग_लिखोl(regval, reg);
			अवरोध;

		शेष:
			dev_dbg(pmx->dev, "parameter not supported\n");
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_pconf_group_set(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *configs,
				   अचिन्हित पूर्णांक num_configs)
अणु
	अचिन्हित पूर्णांक num_pins, current_pin;
	पूर्णांक ret;

	dev_dbg(pctldev->dev, "setting group %s configuration\n",
		artpec6_get_group_name(pctldev, group));

	num_pins = artpec6_pin_groups[group].num_pins;

	क्रम (current_pin = 0; current_pin < num_pins; current_pin++) अणु
		ret = artpec6_pconf_set(pctldev,
				artpec6_pin_groups[group].pins[current_pin],
				configs, num_configs);

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops artpec6_pconf_ops = अणु
	.is_generic		= true,
	.pin_config_get		= artpec6_pconf_get,
	.pin_config_set		= artpec6_pconf_set,
	.pin_config_group_set	= artpec6_pconf_group_set,
पूर्ण;

अटल काष्ठा pinctrl_desc artpec6_desc = अणु
	.name	 = "artpec6-pinctrl",
	.owner	 = THIS_MODULE,
	.pins	 = artpec6_pins,
	.npins	 = ARRAY_SIZE(artpec6_pins),
	.pctlops = &artpec6_pctrl_ops,
	.pmxops	 = &artpec6_pmx_ops,
	.confops = &artpec6_pconf_ops,
पूर्ण;

/* The reset values say 4mA, but we want 8mA as शेष. */
अटल व्योम artpec6_pmx_reset(काष्ठा artpec6_pmx *pmx)
अणु
	व्योम __iomem *base = pmx->base;
	पूर्णांक i;

	क्रम (i = 0; i < ARTPEC6_LAST_PIN; i++) अणु
		u32 val;

		val = पढ़ोl_relaxed(base + artpec6_pmx_reg_offset(i));
		val &= ~ARTPEC6_PINMUX_DRV_MASK;
		val |= ARTPEC6_DRIVE_8mA_SET << ARTPEC6_PINMUX_DRV_SHIFT;
		ग_लिखोl_relaxed(val, base + artpec6_pmx_reg_offset(i));
	पूर्ण
पूर्ण

अटल पूर्णांक artpec6_pmx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा artpec6_pmx *pmx;

	pmx = devm_kzalloc(&pdev->dev, माप(*pmx), GFP_KERNEL);
	अगर (!pmx)
		वापस -ENOMEM;

	pmx->dev = &pdev->dev;

	pmx->base = devm_platक्रमm_ioremap_resource(pdev, 0);

	अगर (IS_ERR(pmx->base))
		वापस PTR_ERR(pmx->base);

	artpec6_pmx_reset(pmx);

	pmx->pins	    = artpec6_pins;
	pmx->num_pins	    = ARRAY_SIZE(artpec6_pins);
	pmx->functions	    = artpec6_pmx_functions;
	pmx->num_functions  = ARRAY_SIZE(artpec6_pmx_functions);
	pmx->pin_groups	    = artpec6_pin_groups;
	pmx->num_pin_groups = ARRAY_SIZE(artpec6_pin_groups);
	pmx->pctl	    = pinctrl_रेजिस्टर(&artpec6_desc, &pdev->dev, pmx);

	अगर (IS_ERR(pmx->pctl)) अणु
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		वापस PTR_ERR(pmx->pctl);
	पूर्ण

	platक्रमm_set_drvdata(pdev, pmx);

	dev_info(&pdev->dev, "initialised Axis ARTPEC-6 pinctrl driver\n");

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_pmx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा artpec6_pmx *pmx = platक्रमm_get_drvdata(pdev);

	pinctrl_unरेजिस्टर(pmx->pctl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id artpec6_pinctrl_match[] = अणु
	अणु .compatible = "axis,artpec6-pinctrl" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver artpec6_pmx_driver = अणु
	.driver = अणु
		.name = "artpec6-pinctrl",
		.of_match_table = artpec6_pinctrl_match,
	पूर्ण,
	.probe = artpec6_pmx_probe,
	.हटाओ = artpec6_pmx_हटाओ,
पूर्ण;

अटल पूर्णांक __init artpec6_pmx_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&artpec6_pmx_driver);
पूर्ण
arch_initcall(artpec6_pmx_init);
