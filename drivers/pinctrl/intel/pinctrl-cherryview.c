<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cherryview/Braswell pinctrl driver
 *
 * Copyright (C) 2014, 2020 Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *
 * This driver is based on the original Cherryview GPIO driver by
 *   Ning Li <ning.li@पूर्णांकel.com>
 *   Alan Cox <alan@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "pinctrl-intel.h"

#घोषणा CHV_INTSTAT			0x300
#घोषणा CHV_INTMASK			0x380

#घोषणा FAMILY_PAD_REGS_OFF		0x4400
#घोषणा FAMILY_PAD_REGS_SIZE		0x400
#घोषणा MAX_FAMILY_PAD_GPIO_NO		15
#घोषणा GPIO_REGS_SIZE			8

#घोषणा CHV_PADCTRL0			0x000
#घोषणा CHV_PADCTRL0_INTSEL_SHIFT	28
#घोषणा CHV_PADCTRL0_INTSEL_MASK	GENMASK(31, 28)
#घोषणा CHV_PADCTRL0_TERM_UP		BIT(23)
#घोषणा CHV_PADCTRL0_TERM_SHIFT		20
#घोषणा CHV_PADCTRL0_TERM_MASK		GENMASK(22, 20)
#घोषणा CHV_PADCTRL0_TERM_20K		1
#घोषणा CHV_PADCTRL0_TERM_5K		2
#घोषणा CHV_PADCTRL0_TERM_1K		4
#घोषणा CHV_PADCTRL0_PMODE_SHIFT	16
#घोषणा CHV_PADCTRL0_PMODE_MASK		GENMASK(19, 16)
#घोषणा CHV_PADCTRL0_GPIOEN		BIT(15)
#घोषणा CHV_PADCTRL0_GPIOCFG_SHIFT	8
#घोषणा CHV_PADCTRL0_GPIOCFG_MASK	GENMASK(10, 8)
#घोषणा CHV_PADCTRL0_GPIOCFG_GPIO	0
#घोषणा CHV_PADCTRL0_GPIOCFG_GPO	1
#घोषणा CHV_PADCTRL0_GPIOCFG_GPI	2
#घोषणा CHV_PADCTRL0_GPIOCFG_HIZ	3
#घोषणा CHV_PADCTRL0_GPIOTXSTATE	BIT(1)
#घोषणा CHV_PADCTRL0_GPIORXSTATE	BIT(0)

#घोषणा CHV_PADCTRL1			0x004
#घोषणा CHV_PADCTRL1_CFGLOCK		BIT(31)
#घोषणा CHV_PADCTRL1_INVRXTX_SHIFT	4
#घोषणा CHV_PADCTRL1_INVRXTX_MASK	GENMASK(7, 4)
#घोषणा CHV_PADCTRL1_INVRXTX_TXDATA	BIT(7)
#घोषणा CHV_PADCTRL1_INVRXTX_RXDATA	BIT(6)
#घोषणा CHV_PADCTRL1_INVRXTX_TXENABLE	BIT(5)
#घोषणा CHV_PADCTRL1_ODEN		BIT(3)
#घोषणा CHV_PADCTRL1_INTWAKECFG_MASK	GENMASK(2, 0)
#घोषणा CHV_PADCTRL1_INTWAKECFG_FALLING	1
#घोषणा CHV_PADCTRL1_INTWAKECFG_RISING	2
#घोषणा CHV_PADCTRL1_INTWAKECFG_BOTH	3
#घोषणा CHV_PADCTRL1_INTWAKECFG_LEVEL	4

काष्ठा पूर्णांकel_pad_context अणु
	u32 padctrl0;
	u32 padctrl1;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_community_context - community context क्रम Cherryview
 * @पूर्णांकr_lines: Mapping between 16 HW पूर्णांकerrupt wires and GPIO offset (in GPIO number space)
 * @saved_पूर्णांकmask: Interrupt mask saved क्रम प्रणाली sleep
 */
काष्ठा पूर्णांकel_community_context अणु
	अचिन्हित पूर्णांक पूर्णांकr_lines[16];
	u32 saved_पूर्णांकmask;
पूर्ण;

#घोषणा	PINMODE_INVERT_OE	BIT(15)

#घोषणा PINMODE(m, i)		((m) | ((i) * PINMODE_INVERT_OE))

#घोषणा CHV_GPP(start, end)			\
	अणु					\
		.base = (start),		\
		.size = (end) - (start) + 1,	\
	पूर्ण

#घोषणा CHV_COMMUNITY(g, i, a)			\
	अणु					\
		.gpps = (g),			\
		.ngpps = ARRAY_SIZE(g),		\
		.nirqs = (i),			\
		.acpi_space_id = (a),		\
	पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc southwest_pins[] = अणु
	PINCTRL_PIN(0, "FST_SPI_D2"),
	PINCTRL_PIN(1, "FST_SPI_D0"),
	PINCTRL_PIN(2, "FST_SPI_CLK"),
	PINCTRL_PIN(3, "FST_SPI_D3"),
	PINCTRL_PIN(4, "FST_SPI_CS1_B"),
	PINCTRL_PIN(5, "FST_SPI_D1"),
	PINCTRL_PIN(6, "FST_SPI_CS0_B"),
	PINCTRL_PIN(7, "FST_SPI_CS2_B"),

	PINCTRL_PIN(15, "UART1_RTS_B"),
	PINCTRL_PIN(16, "UART1_RXD"),
	PINCTRL_PIN(17, "UART2_RXD"),
	PINCTRL_PIN(18, "UART1_CTS_B"),
	PINCTRL_PIN(19, "UART2_RTS_B"),
	PINCTRL_PIN(20, "UART1_TXD"),
	PINCTRL_PIN(21, "UART2_TXD"),
	PINCTRL_PIN(22, "UART2_CTS_B"),

	PINCTRL_PIN(30, "MF_HDA_CLK"),
	PINCTRL_PIN(31, "MF_HDA_RSTB"),
	PINCTRL_PIN(32, "MF_HDA_SDIO"),
	PINCTRL_PIN(33, "MF_HDA_SDO"),
	PINCTRL_PIN(34, "MF_HDA_DOCKRSTB"),
	PINCTRL_PIN(35, "MF_HDA_SYNC"),
	PINCTRL_PIN(36, "MF_HDA_SDI1"),
	PINCTRL_PIN(37, "MF_HDA_DOCKENB"),

	PINCTRL_PIN(45, "I2C5_SDA"),
	PINCTRL_PIN(46, "I2C4_SDA"),
	PINCTRL_PIN(47, "I2C6_SDA"),
	PINCTRL_PIN(48, "I2C5_SCL"),
	PINCTRL_PIN(49, "I2C_NFC_SDA"),
	PINCTRL_PIN(50, "I2C4_SCL"),
	PINCTRL_PIN(51, "I2C6_SCL"),
	PINCTRL_PIN(52, "I2C_NFC_SCL"),

	PINCTRL_PIN(60, "I2C1_SDA"),
	PINCTRL_PIN(61, "I2C0_SDA"),
	PINCTRL_PIN(62, "I2C2_SDA"),
	PINCTRL_PIN(63, "I2C1_SCL"),
	PINCTRL_PIN(64, "I2C3_SDA"),
	PINCTRL_PIN(65, "I2C0_SCL"),
	PINCTRL_PIN(66, "I2C2_SCL"),
	PINCTRL_PIN(67, "I2C3_SCL"),

	PINCTRL_PIN(75, "SATA_GP0"),
	PINCTRL_PIN(76, "SATA_GP1"),
	PINCTRL_PIN(77, "SATA_LEDN"),
	PINCTRL_PIN(78, "SATA_GP2"),
	PINCTRL_PIN(79, "MF_SMB_ALERTB"),
	PINCTRL_PIN(80, "SATA_GP3"),
	PINCTRL_PIN(81, "MF_SMB_CLK"),
	PINCTRL_PIN(82, "MF_SMB_DATA"),

	PINCTRL_PIN(90, "PCIE_CLKREQ0B"),
	PINCTRL_PIN(91, "PCIE_CLKREQ1B"),
	PINCTRL_PIN(92, "GP_SSP_2_CLK"),
	PINCTRL_PIN(93, "PCIE_CLKREQ2B"),
	PINCTRL_PIN(94, "GP_SSP_2_RXD"),
	PINCTRL_PIN(95, "PCIE_CLKREQ3B"),
	PINCTRL_PIN(96, "GP_SSP_2_FS"),
	PINCTRL_PIN(97, "GP_SSP_2_TXD"),
पूर्ण;

अटल स्थिर अचिन्हित southwest_uart0_pins[] = अणु 16, 20 पूर्ण;
अटल स्थिर अचिन्हित southwest_uart1_pins[] = अणु 15, 16, 18, 20 पूर्ण;
अटल स्थिर अचिन्हित southwest_uart2_pins[] = अणु 17, 19, 21, 22 पूर्ण;
अटल स्थिर अचिन्हित southwest_i2c0_pins[] = अणु 61, 65 पूर्ण;
अटल स्थिर अचिन्हित southwest_hda_pins[] = अणु 30, 31, 32, 33, 34, 35, 36, 37 पूर्ण;
अटल स्थिर अचिन्हित southwest_lpe_pins[] = अणु
	30, 31, 32, 33, 34, 35, 36, 37, 92, 94, 96, 97,
पूर्ण;
अटल स्थिर अचिन्हित southwest_i2c1_pins[] = अणु 60, 63 पूर्ण;
अटल स्थिर अचिन्हित southwest_i2c2_pins[] = अणु 62, 66 पूर्ण;
अटल स्थिर अचिन्हित southwest_i2c3_pins[] = अणु 64, 67 पूर्ण;
अटल स्थिर अचिन्हित southwest_i2c4_pins[] = अणु 46, 50 पूर्ण;
अटल स्थिर अचिन्हित southwest_i2c5_pins[] = अणु 45, 48 पूर्ण;
अटल स्थिर अचिन्हित southwest_i2c6_pins[] = अणु 47, 51 पूर्ण;
अटल स्थिर अचिन्हित southwest_i2c_nfc_pins[] = अणु 49, 52 पूर्ण;
अटल स्थिर अचिन्हित southwest_spi3_pins[] = अणु 76, 79, 80, 81, 82 पूर्ण;

/* Some of LPE I2S TXD pins need to have OE inversion set */
अटल स्थिर अचिन्हित पूर्णांक southwest_lpe_altfuncs[] = अणु
	PINMODE(1, 1), PINMODE(1, 0), PINMODE(1, 0), PINMODE(1, 0), /* 30, 31, 32, 33 */
	PINMODE(1, 1), PINMODE(1, 0), PINMODE(1, 0), PINMODE(1, 0), /* 34, 35, 36, 37 */
	PINMODE(1, 0), PINMODE(1, 0), PINMODE(1, 0), PINMODE(1, 1), /* 92, 94, 96, 97 */
पूर्ण;

/*
 * Two spi3 chipselects are available in dअगरferent mode than the मुख्य spi3
 * functionality, which is using mode 2.
 */
अटल स्थिर अचिन्हित पूर्णांक southwest_spi3_altfuncs[] = अणु
	PINMODE(3, 0), PINMODE(2, 0), PINMODE(3, 0), PINMODE(2, 0), /* 76, 79, 80, 81 */
	PINMODE(2, 0),						    /* 82 */
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup southwest_groups[] = अणु
	PIN_GROUP("uart0_grp", southwest_uart0_pins, PINMODE(2, 0)),
	PIN_GROUP("uart1_grp", southwest_uart1_pins, PINMODE(1, 0)),
	PIN_GROUP("uart2_grp", southwest_uart2_pins, PINMODE(1, 0)),
	PIN_GROUP("hda_grp", southwest_hda_pins, PINMODE(2, 0)),
	PIN_GROUP("i2c0_grp", southwest_i2c0_pins, PINMODE(1, 1)),
	PIN_GROUP("i2c1_grp", southwest_i2c1_pins, PINMODE(1, 1)),
	PIN_GROUP("i2c2_grp", southwest_i2c2_pins, PINMODE(1, 1)),
	PIN_GROUP("i2c3_grp", southwest_i2c3_pins, PINMODE(1, 1)),
	PIN_GROUP("i2c4_grp", southwest_i2c4_pins, PINMODE(1, 1)),
	PIN_GROUP("i2c5_grp", southwest_i2c5_pins, PINMODE(1, 1)),
	PIN_GROUP("i2c6_grp", southwest_i2c6_pins, PINMODE(1, 1)),
	PIN_GROUP("i2c_nfc_grp", southwest_i2c_nfc_pins, PINMODE(2, 1)),
	PIN_GROUP("lpe_grp", southwest_lpe_pins, southwest_lpe_altfuncs),
	PIN_GROUP("spi3_grp", southwest_spi3_pins, southwest_spi3_altfuncs),
पूर्ण;

अटल स्थिर अक्षर * स्थिर southwest_uart0_groups[] = अणु "uart0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_uart1_groups[] = अणु "uart1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_uart2_groups[] = अणु "uart2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_hda_groups[] = अणु "hda_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_lpe_groups[] = अणु "lpe_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_i2c0_groups[] = अणु "i2c0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_i2c1_groups[] = अणु "i2c1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_i2c2_groups[] = अणु "i2c2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_i2c3_groups[] = अणु "i2c3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_i2c4_groups[] = अणु "i2c4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_i2c5_groups[] = अणु "i2c5_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_i2c6_groups[] = अणु "i2c6_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_i2c_nfc_groups[] = अणु "i2c_nfc_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southwest_spi3_groups[] = अणु "spi3_grp" पूर्ण;

/*
 * Only करो pinmuxing क्रम certain LPSS devices क्रम now. Rest of the pins are
 * enabled only as GPIOs.
 */
अटल स्थिर काष्ठा पूर्णांकel_function southwest_functions[] = अणु
	FUNCTION("uart0", southwest_uart0_groups),
	FUNCTION("uart1", southwest_uart1_groups),
	FUNCTION("uart2", southwest_uart2_groups),
	FUNCTION("hda", southwest_hda_groups),
	FUNCTION("lpe", southwest_lpe_groups),
	FUNCTION("i2c0", southwest_i2c0_groups),
	FUNCTION("i2c1", southwest_i2c1_groups),
	FUNCTION("i2c2", southwest_i2c2_groups),
	FUNCTION("i2c3", southwest_i2c3_groups),
	FUNCTION("i2c4", southwest_i2c4_groups),
	FUNCTION("i2c5", southwest_i2c5_groups),
	FUNCTION("i2c6", southwest_i2c6_groups),
	FUNCTION("i2c_nfc", southwest_i2c_nfc_groups),
	FUNCTION("spi3", southwest_spi3_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_padgroup southwest_gpps[] = अणु
	CHV_GPP(0, 7),
	CHV_GPP(15, 22),
	CHV_GPP(30, 37),
	CHV_GPP(45, 52),
	CHV_GPP(60, 67),
	CHV_GPP(75, 82),
	CHV_GPP(90, 97),
पूर्ण;

/*
 * Southwest community can generate GPIO पूर्णांकerrupts only क्रम the first 8
 * पूर्णांकerrupts. The upper half (8-15) can only be used to trigger GPEs.
 */
अटल स्थिर काष्ठा पूर्णांकel_community southwest_communities[] = अणु
	CHV_COMMUNITY(southwest_gpps, 8, 0x91),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data southwest_soc_data = अणु
	.uid = "1",
	.pins = southwest_pins,
	.npins = ARRAY_SIZE(southwest_pins),
	.groups = southwest_groups,
	.ngroups = ARRAY_SIZE(southwest_groups),
	.functions = southwest_functions,
	.nfunctions = ARRAY_SIZE(southwest_functions),
	.communities = southwest_communities,
	.ncommunities = ARRAY_SIZE(southwest_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc north_pins[] = अणु
	PINCTRL_PIN(0, "GPIO_DFX_0"),
	PINCTRL_PIN(1, "GPIO_DFX_3"),
	PINCTRL_PIN(2, "GPIO_DFX_7"),
	PINCTRL_PIN(3, "GPIO_DFX_1"),
	PINCTRL_PIN(4, "GPIO_DFX_5"),
	PINCTRL_PIN(5, "GPIO_DFX_4"),
	PINCTRL_PIN(6, "GPIO_DFX_8"),
	PINCTRL_PIN(7, "GPIO_DFX_2"),
	PINCTRL_PIN(8, "GPIO_DFX_6"),

	PINCTRL_PIN(15, "GPIO_SUS0"),
	PINCTRL_PIN(16, "SEC_GPIO_SUS10"),
	PINCTRL_PIN(17, "GPIO_SUS3"),
	PINCTRL_PIN(18, "GPIO_SUS7"),
	PINCTRL_PIN(19, "GPIO_SUS1"),
	PINCTRL_PIN(20, "GPIO_SUS5"),
	PINCTRL_PIN(21, "SEC_GPIO_SUS11"),
	PINCTRL_PIN(22, "GPIO_SUS4"),
	PINCTRL_PIN(23, "SEC_GPIO_SUS8"),
	PINCTRL_PIN(24, "GPIO_SUS2"),
	PINCTRL_PIN(25, "GPIO_SUS6"),
	PINCTRL_PIN(26, "CX_PREQ_B"),
	PINCTRL_PIN(27, "SEC_GPIO_SUS9"),

	PINCTRL_PIN(30, "TRST_B"),
	PINCTRL_PIN(31, "TCK"),
	PINCTRL_PIN(32, "PROCHOT_B"),
	PINCTRL_PIN(33, "SVIDO_DATA"),
	PINCTRL_PIN(34, "TMS"),
	PINCTRL_PIN(35, "CX_PRDY_B_2"),
	PINCTRL_PIN(36, "TDO_2"),
	PINCTRL_PIN(37, "CX_PRDY_B"),
	PINCTRL_PIN(38, "SVIDO_ALERT_B"),
	PINCTRL_PIN(39, "TDO"),
	PINCTRL_PIN(40, "SVIDO_CLK"),
	PINCTRL_PIN(41, "TDI"),

	PINCTRL_PIN(45, "GP_CAMERASB_05"),
	PINCTRL_PIN(46, "GP_CAMERASB_02"),
	PINCTRL_PIN(47, "GP_CAMERASB_08"),
	PINCTRL_PIN(48, "GP_CAMERASB_00"),
	PINCTRL_PIN(49, "GP_CAMERASB_06"),
	PINCTRL_PIN(50, "GP_CAMERASB_10"),
	PINCTRL_PIN(51, "GP_CAMERASB_03"),
	PINCTRL_PIN(52, "GP_CAMERASB_09"),
	PINCTRL_PIN(53, "GP_CAMERASB_01"),
	PINCTRL_PIN(54, "GP_CAMERASB_07"),
	PINCTRL_PIN(55, "GP_CAMERASB_11"),
	PINCTRL_PIN(56, "GP_CAMERASB_04"),

	PINCTRL_PIN(60, "PANEL0_BKLTEN"),
	PINCTRL_PIN(61, "HV_DDI0_HPD"),
	PINCTRL_PIN(62, "HV_DDI2_DDC_SDA"),
	PINCTRL_PIN(63, "PANEL1_BKLTCTL"),
	PINCTRL_PIN(64, "HV_DDI1_HPD"),
	PINCTRL_PIN(65, "PANEL0_BKLTCTL"),
	PINCTRL_PIN(66, "HV_DDI0_DDC_SDA"),
	PINCTRL_PIN(67, "HV_DDI2_DDC_SCL"),
	PINCTRL_PIN(68, "HV_DDI2_HPD"),
	PINCTRL_PIN(69, "PANEL1_VDDEN"),
	PINCTRL_PIN(70, "PANEL1_BKLTEN"),
	PINCTRL_PIN(71, "HV_DDI0_DDC_SCL"),
	PINCTRL_PIN(72, "PANEL0_VDDEN"),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_padgroup north_gpps[] = अणु
	CHV_GPP(0, 8),
	CHV_GPP(15, 27),
	CHV_GPP(30, 41),
	CHV_GPP(45, 56),
	CHV_GPP(60, 72),
पूर्ण;

/*
 * North community can generate GPIO पूर्णांकerrupts only क्रम the first 8
 * पूर्णांकerrupts. The upper half (8-15) can only be used to trigger GPEs.
 */
अटल स्थिर काष्ठा पूर्णांकel_community north_communities[] = अणु
	CHV_COMMUNITY(north_gpps, 8, 0x92),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data north_soc_data = अणु
	.uid = "2",
	.pins = north_pins,
	.npins = ARRAY_SIZE(north_pins),
	.communities = north_communities,
	.ncommunities = ARRAY_SIZE(north_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc east_pins[] = अणु
	PINCTRL_PIN(0, "PMU_SLP_S3_B"),
	PINCTRL_PIN(1, "PMU_BATLOW_B"),
	PINCTRL_PIN(2, "SUS_STAT_B"),
	PINCTRL_PIN(3, "PMU_SLP_S0IX_B"),
	PINCTRL_PIN(4, "PMU_AC_PRESENT"),
	PINCTRL_PIN(5, "PMU_PLTRST_B"),
	PINCTRL_PIN(6, "PMU_SUSCLK"),
	PINCTRL_PIN(7, "PMU_SLP_LAN_B"),
	PINCTRL_PIN(8, "PMU_PWRBTN_B"),
	PINCTRL_PIN(9, "PMU_SLP_S4_B"),
	PINCTRL_PIN(10, "PMU_WAKE_B"),
	PINCTRL_PIN(11, "PMU_WAKE_LAN_B"),

	PINCTRL_PIN(15, "MF_ISH_GPIO_3"),
	PINCTRL_PIN(16, "MF_ISH_GPIO_7"),
	PINCTRL_PIN(17, "MF_ISH_I2C1_SCL"),
	PINCTRL_PIN(18, "MF_ISH_GPIO_1"),
	PINCTRL_PIN(19, "MF_ISH_GPIO_5"),
	PINCTRL_PIN(20, "MF_ISH_GPIO_9"),
	PINCTRL_PIN(21, "MF_ISH_GPIO_0"),
	PINCTRL_PIN(22, "MF_ISH_GPIO_4"),
	PINCTRL_PIN(23, "MF_ISH_GPIO_8"),
	PINCTRL_PIN(24, "MF_ISH_GPIO_2"),
	PINCTRL_PIN(25, "MF_ISH_GPIO_6"),
	PINCTRL_PIN(26, "MF_ISH_I2C1_SDA"),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_padgroup east_gpps[] = अणु
	CHV_GPP(0, 11),
	CHV_GPP(15, 26),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community east_communities[] = अणु
	CHV_COMMUNITY(east_gpps, 16, 0x93),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data east_soc_data = अणु
	.uid = "3",
	.pins = east_pins,
	.npins = ARRAY_SIZE(east_pins),
	.communities = east_communities,
	.ncommunities = ARRAY_SIZE(east_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc southeast_pins[] = अणु
	PINCTRL_PIN(0, "MF_PLT_CLK0"),
	PINCTRL_PIN(1, "PWM1"),
	PINCTRL_PIN(2, "MF_PLT_CLK1"),
	PINCTRL_PIN(3, "MF_PLT_CLK4"),
	PINCTRL_PIN(4, "MF_PLT_CLK3"),
	PINCTRL_PIN(5, "PWM0"),
	PINCTRL_PIN(6, "MF_PLT_CLK5"),
	PINCTRL_PIN(7, "MF_PLT_CLK2"),

	PINCTRL_PIN(15, "SDMMC2_D3_CD_B"),
	PINCTRL_PIN(16, "SDMMC1_CLK"),
	PINCTRL_PIN(17, "SDMMC1_D0"),
	PINCTRL_PIN(18, "SDMMC2_D1"),
	PINCTRL_PIN(19, "SDMMC2_CLK"),
	PINCTRL_PIN(20, "SDMMC1_D2"),
	PINCTRL_PIN(21, "SDMMC2_D2"),
	PINCTRL_PIN(22, "SDMMC2_CMD"),
	PINCTRL_PIN(23, "SDMMC1_CMD"),
	PINCTRL_PIN(24, "SDMMC1_D1"),
	PINCTRL_PIN(25, "SDMMC2_D0"),
	PINCTRL_PIN(26, "SDMMC1_D3_CD_B"),

	PINCTRL_PIN(30, "SDMMC3_D1"),
	PINCTRL_PIN(31, "SDMMC3_CLK"),
	PINCTRL_PIN(32, "SDMMC3_D3"),
	PINCTRL_PIN(33, "SDMMC3_D2"),
	PINCTRL_PIN(34, "SDMMC3_CMD"),
	PINCTRL_PIN(35, "SDMMC3_D0"),

	PINCTRL_PIN(45, "MF_LPC_AD2"),
	PINCTRL_PIN(46, "LPC_CLKRUNB"),
	PINCTRL_PIN(47, "MF_LPC_AD0"),
	PINCTRL_PIN(48, "LPC_FRAMEB"),
	PINCTRL_PIN(49, "MF_LPC_CLKOUT1"),
	PINCTRL_PIN(50, "MF_LPC_AD3"),
	PINCTRL_PIN(51, "MF_LPC_CLKOUT0"),
	PINCTRL_PIN(52, "MF_LPC_AD1"),

	PINCTRL_PIN(60, "SPI1_MISO"),
	PINCTRL_PIN(61, "SPI1_CSO_B"),
	PINCTRL_PIN(62, "SPI1_CLK"),
	PINCTRL_PIN(63, "MMC1_D6"),
	PINCTRL_PIN(64, "SPI1_MOSI"),
	PINCTRL_PIN(65, "MMC1_D5"),
	PINCTRL_PIN(66, "SPI1_CS1_B"),
	PINCTRL_PIN(67, "MMC1_D4_SD_WE"),
	PINCTRL_PIN(68, "MMC1_D7"),
	PINCTRL_PIN(69, "MMC1_RCLK"),

	PINCTRL_PIN(75, "USB_OC1_B"),
	PINCTRL_PIN(76, "PMU_RESETBUTTON_B"),
	PINCTRL_PIN(77, "GPIO_ALERT"),
	PINCTRL_PIN(78, "SDMMC3_PWR_EN_B"),
	PINCTRL_PIN(79, "ILB_SERIRQ"),
	PINCTRL_PIN(80, "USB_OC0_B"),
	PINCTRL_PIN(81, "SDMMC3_CD_B"),
	PINCTRL_PIN(82, "SPKR"),
	PINCTRL_PIN(83, "SUSPWRDNACK"),
	PINCTRL_PIN(84, "SPARE_PIN"),
	PINCTRL_PIN(85, "SDMMC3_1P8_EN"),
पूर्ण;

अटल स्थिर अचिन्हित southeast_pwm0_pins[] = अणु 5 पूर्ण;
अटल स्थिर अचिन्हित southeast_pwm1_pins[] = अणु 1 पूर्ण;
अटल स्थिर अचिन्हित southeast_sdmmc1_pins[] = अणु
	16, 17, 20, 23, 24, 26, 63, 65, 67, 68, 69,
पूर्ण;
अटल स्थिर अचिन्हित southeast_sdmmc2_pins[] = अणु 15, 18, 19, 21, 22, 25 पूर्ण;
अटल स्थिर अचिन्हित southeast_sdmmc3_pins[] = अणु
	30, 31, 32, 33, 34, 35, 78, 81, 85,
पूर्ण;
अटल स्थिर अचिन्हित southeast_spi1_pins[] = अणु 60, 61, 62, 64, 66 पूर्ण;
अटल स्थिर अचिन्हित southeast_spi2_pins[] = अणु 2, 3, 4, 6, 7 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup southeast_groups[] = अणु
	PIN_GROUP("pwm0_grp", southeast_pwm0_pins, PINMODE(1, 0)),
	PIN_GROUP("pwm1_grp", southeast_pwm1_pins, PINMODE(1, 0)),
	PIN_GROUP("sdmmc1_grp", southeast_sdmmc1_pins, PINMODE(1, 0)),
	PIN_GROUP("sdmmc2_grp", southeast_sdmmc2_pins, PINMODE(1, 0)),
	PIN_GROUP("sdmmc3_grp", southeast_sdmmc3_pins, PINMODE(1, 0)),
	PIN_GROUP("spi1_grp", southeast_spi1_pins, PINMODE(1, 0)),
	PIN_GROUP("spi2_grp", southeast_spi2_pins, PINMODE(4, 0)),
पूर्ण;

अटल स्थिर अक्षर * स्थिर southeast_pwm0_groups[] = अणु "pwm0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southeast_pwm1_groups[] = अणु "pwm1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southeast_sdmmc1_groups[] = अणु "sdmmc1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southeast_sdmmc2_groups[] = अणु "sdmmc2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southeast_sdmmc3_groups[] = अणु "sdmmc3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southeast_spi1_groups[] = अणु "spi1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर southeast_spi2_groups[] = अणु "spi2_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function southeast_functions[] = अणु
	FUNCTION("pwm0", southeast_pwm0_groups),
	FUNCTION("pwm1", southeast_pwm1_groups),
	FUNCTION("sdmmc1", southeast_sdmmc1_groups),
	FUNCTION("sdmmc2", southeast_sdmmc2_groups),
	FUNCTION("sdmmc3", southeast_sdmmc3_groups),
	FUNCTION("spi1", southeast_spi1_groups),
	FUNCTION("spi2", southeast_spi2_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_padgroup southeast_gpps[] = अणु
	CHV_GPP(0, 7),
	CHV_GPP(15, 26),
	CHV_GPP(30, 35),
	CHV_GPP(45, 52),
	CHV_GPP(60, 69),
	CHV_GPP(75, 85),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community southeast_communities[] = अणु
	CHV_COMMUNITY(southeast_gpps, 16, 0x94),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data southeast_soc_data = अणु
	.uid = "4",
	.pins = southeast_pins,
	.npins = ARRAY_SIZE(southeast_pins),
	.groups = southeast_groups,
	.ngroups = ARRAY_SIZE(southeast_groups),
	.functions = southeast_functions,
	.nfunctions = ARRAY_SIZE(southeast_functions),
	.communities = southeast_communities,
	.ncommunities = ARRAY_SIZE(southeast_communities),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *chv_soc_data[] = अणु
	&southwest_soc_data,
	&north_soc_data,
	&east_soc_data,
	&southeast_soc_data,
	शून्य
पूर्ण;

/*
 * Lock to serialize रेजिस्टर accesses
 *
 * Due to a silicon issue, a shared lock must be used to prevent
 * concurrent accesses across the 4 GPIO controllers.
 *
 * See Intel Atom Z8000 Processor Series Specअगरication Update (Rev. 005),
 * errata #CHT34, क्रम further inक्रमmation.
 */
अटल DEFINE_RAW_SPINLOCK(chv_lock);

अटल u32 chv_pctrl_पढ़ोl(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];

	वापस पढ़ोl(community->regs + offset);
पूर्ण

अटल व्योम chv_pctrl_ग_लिखोl(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक offset, u32 value)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];
	व्योम __iomem *reg = community->regs + offset;

	/* Write and simple पढ़ो back to confirm the bus transferring करोne */
	ग_लिखोl(value, reg);
	पढ़ोl(reg);
पूर्ण

अटल व्योम __iomem *chv_padreg(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक reg)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];
	अचिन्हित पूर्णांक family_no = offset / MAX_FAMILY_PAD_GPIO_NO;
	अचिन्हित पूर्णांक pad_no = offset % MAX_FAMILY_PAD_GPIO_NO;

	offset = FAMILY_PAD_REGS_SIZE * family_no + GPIO_REGS_SIZE * pad_no;

	वापस community->pad_regs + offset + reg;
पूर्ण

अटल u32 chv_पढ़ोl(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(chv_padreg(pctrl, pin, offset));
पूर्ण

अटल व्योम chv_ग_लिखोl(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक offset, u32 value)
अणु
	व्योम __iomem *reg = chv_padreg(pctrl, pin, offset);

	/* Write and simple पढ़ो back to confirm the bus transferring करोne */
	ग_लिखोl(value, reg);
	पढ़ोl(reg);
पूर्ण

/* When Pad Cfg is locked, driver can only change GPIOTXState or GPIORXState */
अटल bool chv_pad_locked(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक offset)
अणु
	वापस chv_पढ़ोl(pctrl, offset, CHV_PADCTRL1) & CHV_PADCTRL1_CFGLOCK;
पूर्ण

अटल पूर्णांक chv_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *chv_get_group_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक group)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->groups[group].name;
पूर्ण

अटल पूर्णांक chv_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक group,
			      स्थिर अचिन्हित पूर्णांक **pins, अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = pctrl->soc->groups[group].pins;
	*npins = pctrl->soc->groups[group].npins;
	वापस 0;
पूर्ण

अटल व्योम chv_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
			     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित दीर्घ flags;
	u32 ctrl0, ctrl1;
	bool locked;

	raw_spin_lock_irqsave(&chv_lock, flags);

	ctrl0 = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL0);
	ctrl1 = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL1);
	locked = chv_pad_locked(pctrl, offset);

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	अगर (ctrl0 & CHV_PADCTRL0_GPIOEN) अणु
		seq_माला_दो(s, "GPIO ");
	पूर्ण अन्यथा अणु
		u32 mode;

		mode = ctrl0 & CHV_PADCTRL0_PMODE_MASK;
		mode >>= CHV_PADCTRL0_PMODE_SHIFT;

		seq_म_लिखो(s, "mode %d ", mode);
	पूर्ण

	seq_म_लिखो(s, "0x%08x 0x%08x", ctrl0, ctrl1);

	अगर (locked)
		seq_माला_दो(s, " [LOCKED]");
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops chv_pinctrl_ops = अणु
	.get_groups_count = chv_get_groups_count,
	.get_group_name = chv_get_group_name,
	.get_group_pins = chv_get_group_pins,
	.pin_dbg_show = chv_pin_dbg_show,
पूर्ण;

अटल पूर्णांक chv_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *chv_get_function_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित पूर्णांक function)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->functions[function].name;
पूर्ण

अटल पूर्णांक chv_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक function,
				   स्थिर अक्षर * स्थिर **groups,
				   अचिन्हित पूर्णांक * स्थिर ngroups)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctrl->soc->functions[function].groups;
	*ngroups = pctrl->soc->functions[function].ngroups;
	वापस 0;
पूर्ण

अटल पूर्णांक chv_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक group)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा पूर्णांकel_pingroup *grp;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	grp = &pctrl->soc->groups[group];

	raw_spin_lock_irqsave(&chv_lock, flags);

	/* Check first that the pad is not locked */
	क्रम (i = 0; i < grp->npins; i++) अणु
		अगर (chv_pad_locked(pctrl, grp->pins[i])) अणु
			dev_warn(pctrl->dev, "unable to set mode for locked pin %u\n",
				 grp->pins[i]);
			raw_spin_unlock_irqrestore(&chv_lock, flags);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < grp->npins; i++) अणु
		पूर्णांक pin = grp->pins[i];
		अचिन्हित पूर्णांक mode;
		bool invert_oe;
		u32 value;

		/* Check अगर there is pin-specअगरic config */
		अगर (grp->modes)
			mode = grp->modes[i];
		अन्यथा
			mode = grp->mode;

		/* Extract OE inversion */
		invert_oe = mode & PINMODE_INVERT_OE;
		mode &= ~PINMODE_INVERT_OE;

		value = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL0);
		/* Disable GPIO mode */
		value &= ~CHV_PADCTRL0_GPIOEN;
		/* Set to desired mode */
		value &= ~CHV_PADCTRL0_PMODE_MASK;
		value |= mode << CHV_PADCTRL0_PMODE_SHIFT;
		chv_ग_लिखोl(pctrl, pin, CHV_PADCTRL0, value);

		/* Update क्रम invert_oe */
		value = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL1) & ~CHV_PADCTRL1_INVRXTX_MASK;
		अगर (invert_oe)
			value |= CHV_PADCTRL1_INVRXTX_TXENABLE;
		chv_ग_लिखोl(pctrl, pin, CHV_PADCTRL1, value);

		dev_dbg(pctrl->dev, "configured pin %u mode %u OE %sinverted\n",
			pin, mode, invert_oe ? "" : "not ");
	पूर्ण

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम chv_gpio_clear_triggering(काष्ठा पूर्णांकel_pinctrl *pctrl,
				      अचिन्हित पूर्णांक offset)
अणु
	u32 invrxtx_mask = CHV_PADCTRL1_INVRXTX_MASK;
	u32 value;

	/*
	 * One some devices the GPIO should output the inverted value from what
	 * device-drivers / ACPI code expects (inverted बाह्यal buffer?). The
	 * BIOS makes this work by setting the CHV_PADCTRL1_INVRXTX_TXDATA flag,
	 * preserve this flag अगर the pin is alपढ़ोy setup as GPIO.
	 */
	value = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL0);
	अगर (value & CHV_PADCTRL0_GPIOEN)
		invrxtx_mask &= ~CHV_PADCTRL1_INVRXTX_TXDATA;

	value = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL1);
	value &= ~CHV_PADCTRL1_INTWAKECFG_MASK;
	value &= ~invrxtx_mask;
	chv_ग_लिखोl(pctrl, offset, CHV_PADCTRL1, value);
पूर्ण

अटल पूर्णांक chv_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&chv_lock, flags);

	अगर (chv_pad_locked(pctrl, offset)) अणु
		value = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL0);
		अगर (!(value & CHV_PADCTRL0_GPIOEN)) अणु
			/* Locked so cannot enable */
			raw_spin_unlock_irqrestore(&chv_lock, flags);
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा पूर्णांकel_community_context *cctx = &pctrl->context.communities[0];
		पूर्णांक i;

		/* Reset the पूर्णांकerrupt mapping */
		क्रम (i = 0; i < ARRAY_SIZE(cctx->पूर्णांकr_lines); i++) अणु
			अगर (cctx->पूर्णांकr_lines[i] == offset) अणु
				cctx->पूर्णांकr_lines[i] = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Disable पूर्णांकerrupt generation */
		chv_gpio_clear_triggering(pctrl, offset);

		value = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL0);

		/*
		 * If the pin is in HiZ mode (both TX and RX buffers are
		 * disabled) we turn it to be input now.
		 */
		अगर ((value & CHV_PADCTRL0_GPIOCFG_MASK) ==
		     (CHV_PADCTRL0_GPIOCFG_HIZ << CHV_PADCTRL0_GPIOCFG_SHIFT)) अणु
			value &= ~CHV_PADCTRL0_GPIOCFG_MASK;
			value |= CHV_PADCTRL0_GPIOCFG_GPI << CHV_PADCTRL0_GPIOCFG_SHIFT;
		पूर्ण

		/* Switch to a GPIO mode */
		value |= CHV_PADCTRL0_GPIOEN;
		chv_ग_लिखोl(pctrl, offset, CHV_PADCTRL0, value);
	पूर्ण

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम chv_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chv_lock, flags);

	अगर (!chv_pad_locked(pctrl, offset))
		chv_gpio_clear_triggering(pctrl, offset);

	raw_spin_unlock_irqrestore(&chv_lock, flags);
पूर्ण

अटल पूर्णांक chv_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित पूर्णांक offset, bool input)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित दीर्घ flags;
	u32 ctrl0;

	raw_spin_lock_irqsave(&chv_lock, flags);

	ctrl0 = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL0) & ~CHV_PADCTRL0_GPIOCFG_MASK;
	अगर (input)
		ctrl0 |= CHV_PADCTRL0_GPIOCFG_GPI << CHV_PADCTRL0_GPIOCFG_SHIFT;
	अन्यथा
		ctrl0 |= CHV_PADCTRL0_GPIOCFG_GPO << CHV_PADCTRL0_GPIOCFG_SHIFT;
	chv_ग_लिखोl(pctrl, offset, CHV_PADCTRL0, ctrl0);

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops chv_pinmux_ops = अणु
	.get_functions_count = chv_get_functions_count,
	.get_function_name = chv_get_function_name,
	.get_function_groups = chv_get_function_groups,
	.set_mux = chv_pinmux_set_mux,
	.gpio_request_enable = chv_gpio_request_enable,
	.gpio_disable_मुक्त = chv_gpio_disable_मुक्त,
	.gpio_set_direction = chv_gpio_set_direction,
पूर्ण;

अटल पूर्णांक chv_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			  अचिन्हित दीर्घ *config)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित दीर्घ flags;
	u32 ctrl0, ctrl1;
	u16 arg = 0;
	u32 term;

	raw_spin_lock_irqsave(&chv_lock, flags);
	ctrl0 = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL0);
	ctrl1 = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL1);
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	term = (ctrl0 & CHV_PADCTRL0_TERM_MASK) >> CHV_PADCTRL0_TERM_SHIFT;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (term)
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (!(ctrl0 & CHV_PADCTRL0_TERM_UP))
			वापस -EINVAL;

		चयन (term) अणु
		हाल CHV_PADCTRL0_TERM_20K:
			arg = 20000;
			अवरोध;
		हाल CHV_PADCTRL0_TERM_5K:
			arg = 5000;
			अवरोध;
		हाल CHV_PADCTRL0_TERM_1K:
			arg = 1000;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (!term || (ctrl0 & CHV_PADCTRL0_TERM_UP))
			वापस -EINVAL;

		चयन (term) अणु
		हाल CHV_PADCTRL0_TERM_20K:
			arg = 20000;
			अवरोध;
		हाल CHV_PADCTRL0_TERM_5K:
			arg = 5000;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (!(ctrl1 & CHV_PADCTRL1_ODEN))
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE: अणु
		u32 cfg;

		cfg = ctrl0 & CHV_PADCTRL0_GPIOCFG_MASK;
		cfg >>= CHV_PADCTRL0_GPIOCFG_SHIFT;
		अगर (cfg != CHV_PADCTRL0_GPIOCFG_HIZ)
			वापस -EINVAL;

		अवरोध;
	पूर्ण

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक chv_config_set_pull(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin,
			       क्रमागत pin_config_param param, u32 arg)
अणु
	अचिन्हित दीर्घ flags;
	u32 ctrl0, pull;

	raw_spin_lock_irqsave(&chv_lock, flags);
	ctrl0 = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL0);

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		ctrl0 &= ~(CHV_PADCTRL0_TERM_MASK | CHV_PADCTRL0_TERM_UP);
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		ctrl0 &= ~(CHV_PADCTRL0_TERM_MASK | CHV_PADCTRL0_TERM_UP);

		चयन (arg) अणु
		हाल 1000:
			/* For 1k there is only pull up */
			pull = CHV_PADCTRL0_TERM_1K << CHV_PADCTRL0_TERM_SHIFT;
			अवरोध;
		हाल 5000:
			pull = CHV_PADCTRL0_TERM_5K << CHV_PADCTRL0_TERM_SHIFT;
			अवरोध;
		हाल 20000:
			pull = CHV_PADCTRL0_TERM_20K << CHV_PADCTRL0_TERM_SHIFT;
			अवरोध;
		शेष:
			raw_spin_unlock_irqrestore(&chv_lock, flags);
			वापस -EINVAL;
		पूर्ण

		ctrl0 |= CHV_PADCTRL0_TERM_UP | pull;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ctrl0 &= ~(CHV_PADCTRL0_TERM_MASK | CHV_PADCTRL0_TERM_UP);

		चयन (arg) अणु
		हाल 5000:
			pull = CHV_PADCTRL0_TERM_5K << CHV_PADCTRL0_TERM_SHIFT;
			अवरोध;
		हाल 20000:
			pull = CHV_PADCTRL0_TERM_20K << CHV_PADCTRL0_TERM_SHIFT;
			अवरोध;
		शेष:
			raw_spin_unlock_irqrestore(&chv_lock, flags);
			वापस -EINVAL;
		पूर्ण

		ctrl0 |= pull;
		अवरोध;

	शेष:
		raw_spin_unlock_irqrestore(&chv_lock, flags);
		वापस -EINVAL;
	पूर्ण

	chv_ग_लिखोl(pctrl, pin, CHV_PADCTRL0, ctrl0);
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक chv_config_set_oden(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin,
			       bool enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 ctrl1;

	raw_spin_lock_irqsave(&chv_lock, flags);
	ctrl1 = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL1);

	अगर (enable)
		ctrl1 |= CHV_PADCTRL1_ODEN;
	अन्यथा
		ctrl1 &= ~CHV_PADCTRL1_ODEN;

	chv_ग_लिखोl(pctrl, pin, CHV_PADCTRL1, ctrl1);
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक chv_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			  अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक nconfigs)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	पूर्णांक i, ret;
	u32 arg;

	अगर (chv_pad_locked(pctrl, pin))
		वापस -EBUSY;

	क्रम (i = 0; i < nconfigs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = chv_config_set_pull(pctrl, pin, param, arg);
			अगर (ret)
				वापस ret;
			अवरोध;

		हाल PIN_CONFIG_DRIVE_PUSH_PULL:
			ret = chv_config_set_oden(pctrl, pin, false);
			अगर (ret)
				वापस ret;
			अवरोध;

		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			ret = chv_config_set_oden(pctrl, pin, true);
			अगर (ret)
				वापस ret;
			अवरोध;

		शेष:
			वापस -ENOTSUPP;
		पूर्ण

		dev_dbg(pctrl->dev, "pin %d set config %d arg %u\n", pin,
			param, arg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक chv_config_group_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक group,
				अचिन्हित दीर्घ *config)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक npins;
	पूर्णांक ret;

	ret = chv_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	ret = chv_config_get(pctldev, pins[0], config);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक chv_config_group_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *configs,
				अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक npins;
	पूर्णांक i, ret;

	ret = chv_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < npins; i++) अणु
		ret = chv_config_set(pctldev, pins[i], configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops chv_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_set = chv_config_set,
	.pin_config_get = chv_config_get,
	.pin_config_group_get = chv_config_group_get,
	.pin_config_group_set = chv_config_group_set,
पूर्ण;

अटल काष्ठा pinctrl_desc chv_pinctrl_desc = अणु
	.pctlops = &chv_pinctrl_ops,
	.pmxops = &chv_pinmux_ops,
	.confops = &chv_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक chv_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u32 ctrl0, cfg;

	raw_spin_lock_irqsave(&chv_lock, flags);
	ctrl0 = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL0);
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	cfg = ctrl0 & CHV_PADCTRL0_GPIOCFG_MASK;
	cfg >>= CHV_PADCTRL0_GPIOCFG_SHIFT;

	अगर (cfg == CHV_PADCTRL0_GPIOCFG_GPO)
		वापस !!(ctrl0 & CHV_PADCTRL0_GPIOTXSTATE);
	वापस !!(ctrl0 & CHV_PADCTRL0_GPIORXSTATE);
पूर्ण

अटल व्योम chv_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u32 ctrl0;

	raw_spin_lock_irqsave(&chv_lock, flags);

	ctrl0 = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL0);

	अगर (value)
		ctrl0 |= CHV_PADCTRL0_GPIOTXSTATE;
	अन्यथा
		ctrl0 &= ~CHV_PADCTRL0_GPIOTXSTATE;

	chv_ग_लिखोl(pctrl, offset, CHV_PADCTRL0, ctrl0);

	raw_spin_unlock_irqrestore(&chv_lock, flags);
पूर्ण

अटल पूर्णांक chv_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	u32 ctrl0, direction;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chv_lock, flags);
	ctrl0 = chv_पढ़ोl(pctrl, offset, CHV_PADCTRL0);
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	direction = ctrl0 & CHV_PADCTRL0_GPIOCFG_MASK;
	direction >>= CHV_PADCTRL0_GPIOCFG_SHIFT;

	अगर (direction == CHV_PADCTRL0_GPIOCFG_GPO)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक chv_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक chv_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				     पूर्णांक value)
अणु
	chv_gpio_set(chip, offset, value);
	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip chv_gpio_chip = अणु
	.owner = THIS_MODULE,
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.get_direction = chv_gpio_get_direction,
	.direction_input = chv_gpio_direction_input,
	.direction_output = chv_gpio_direction_output,
	.get = chv_gpio_get,
	.set = chv_gpio_set,
पूर्ण;

अटल व्योम chv_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	पूर्णांक pin = irqd_to_hwirq(d);
	u32 पूर्णांकr_line;

	raw_spin_lock(&chv_lock);

	पूर्णांकr_line = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL0);
	पूर्णांकr_line &= CHV_PADCTRL0_INTSEL_MASK;
	पूर्णांकr_line >>= CHV_PADCTRL0_INTSEL_SHIFT;
	chv_pctrl_ग_लिखोl(pctrl, CHV_INTSTAT, BIT(पूर्णांकr_line));

	raw_spin_unlock(&chv_lock);
पूर्ण

अटल व्योम chv_gpio_irq_mask_unmask(काष्ठा irq_data *d, bool mask)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	पूर्णांक pin = irqd_to_hwirq(d);
	u32 value, पूर्णांकr_line;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&chv_lock, flags);

	पूर्णांकr_line = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL0);
	पूर्णांकr_line &= CHV_PADCTRL0_INTSEL_MASK;
	पूर्णांकr_line >>= CHV_PADCTRL0_INTSEL_SHIFT;

	value = chv_pctrl_पढ़ोl(pctrl, CHV_INTMASK);
	अगर (mask)
		value &= ~BIT(पूर्णांकr_line);
	अन्यथा
		value |= BIT(पूर्णांकr_line);
	chv_pctrl_ग_लिखोl(pctrl, CHV_INTMASK, value);

	raw_spin_unlock_irqrestore(&chv_lock, flags);
पूर्ण

अटल व्योम chv_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	chv_gpio_irq_mask_unmask(d, true);
पूर्ण

अटल व्योम chv_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	chv_gpio_irq_mask_unmask(d, false);
पूर्ण

अटल अचिन्हित chv_gpio_irq_startup(काष्ठा irq_data *d)
अणु
	/*
	 * Check अगर the पूर्णांकerrupt has been requested with 0 as triggering
	 * type. In that हाल it is assumed that the current values
	 * programmed to the hardware are used (e.g BIOS configured
	 * शेषs).
	 *
	 * In that हाल ->irq_set_type() will never be called so we need to
	 * पढ़ो back the values from hardware now, set correct flow handler
	 * and update mappings beक्रमe the पूर्णांकerrupt is being used.
	 */
	अगर (irqd_get_trigger_type(d) == IRQ_TYPE_NONE) अणु
		काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
		काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
		काष्ठा पूर्णांकel_community_context *cctx = &pctrl->context.communities[0];
		अचिन्हित पूर्णांक pin = irqd_to_hwirq(d);
		irq_flow_handler_t handler;
		अचिन्हित दीर्घ flags;
		u32 पूर्णांकsel, value;

		raw_spin_lock_irqsave(&chv_lock, flags);
		पूर्णांकsel = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL0);
		पूर्णांकsel &= CHV_PADCTRL0_INTSEL_MASK;
		पूर्णांकsel >>= CHV_PADCTRL0_INTSEL_SHIFT;

		value = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL1);
		अगर (value & CHV_PADCTRL1_INTWAKECFG_LEVEL)
			handler = handle_level_irq;
		अन्यथा
			handler = handle_edge_irq;

		अगर (!cctx->पूर्णांकr_lines[पूर्णांकsel]) अणु
			irq_set_handler_locked(d, handler);
			cctx->पूर्णांकr_lines[पूर्णांकsel] = pin;
		पूर्ण
		raw_spin_unlock_irqrestore(&chv_lock, flags);
	पूर्ण

	chv_gpio_irq_unmask(d);
	वापस 0;
पूर्ण

अटल पूर्णांक chv_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	काष्ठा पूर्णांकel_community_context *cctx = &pctrl->context.communities[0];
	अचिन्हित पूर्णांक pin = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&chv_lock, flags);

	/*
	 * Pins which can be used as shared पूर्णांकerrupt are configured in
	 * BIOS. Driver trusts BIOS configurations and assigns dअगरferent
	 * handler according to the irq type.
	 *
	 * Driver needs to save the mapping between each pin and
	 * its पूर्णांकerrupt line.
	 * 1. If the pin cfg is locked in BIOS:
	 *	Trust BIOS has programmed IntWakeCfg bits correctly,
	 *	driver just needs to save the mapping.
	 * 2. If the pin cfg is not locked in BIOS:
	 *	Driver programs the IntWakeCfg bits and save the mapping.
	 */
	अगर (!chv_pad_locked(pctrl, pin)) अणु
		value = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL1);
		value &= ~CHV_PADCTRL1_INTWAKECFG_MASK;
		value &= ~CHV_PADCTRL1_INVRXTX_MASK;

		अगर (type & IRQ_TYPE_EDGE_BOTH) अणु
			अगर ((type & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH)
				value |= CHV_PADCTRL1_INTWAKECFG_BOTH;
			अन्यथा अगर (type & IRQ_TYPE_EDGE_RISING)
				value |= CHV_PADCTRL1_INTWAKECFG_RISING;
			अन्यथा अगर (type & IRQ_TYPE_EDGE_FALLING)
				value |= CHV_PADCTRL1_INTWAKECFG_FALLING;
		पूर्ण अन्यथा अगर (type & IRQ_TYPE_LEVEL_MASK) अणु
			value |= CHV_PADCTRL1_INTWAKECFG_LEVEL;
			अगर (type & IRQ_TYPE_LEVEL_LOW)
				value |= CHV_PADCTRL1_INVRXTX_RXDATA;
		पूर्ण

		chv_ग_लिखोl(pctrl, pin, CHV_PADCTRL1, value);
	पूर्ण

	value = chv_पढ़ोl(pctrl, pin, CHV_PADCTRL0);
	value &= CHV_PADCTRL0_INTSEL_MASK;
	value >>= CHV_PADCTRL0_INTSEL_SHIFT;

	cctx->पूर्णांकr_lines[value] = pin;

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम chv_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];
	काष्ठा पूर्णांकel_community_context *cctx = &pctrl->context.communities[0];
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ pending;
	अचिन्हित दीर्घ flags;
	u32 पूर्णांकr_line;

	chained_irq_enter(chip, desc);

	raw_spin_lock_irqsave(&chv_lock, flags);
	pending = chv_pctrl_पढ़ोl(pctrl, CHV_INTSTAT);
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	क्रम_each_set_bit(पूर्णांकr_line, &pending, community->nirqs) अणु
		अचिन्हित पूर्णांक irq, offset;

		offset = cctx->पूर्णांकr_lines[पूर्णांकr_line];
		irq = irq_find_mapping(gc->irq.करोमुख्य, offset);
		generic_handle_irq(irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

/*
 * Certain machines seem to hardcode Linux IRQ numbers in their ACPI
 * tables. Since we leave GPIOs that are not capable of generating
 * पूर्णांकerrupts out of the irqकरोमुख्य the numbering will be dअगरferent and
 * cause devices using the hardcoded IRQ numbers fail. In order not to
 * अवरोध such machines we will only mask pins from irqकरोमुख्य अगर the machine
 * is not listed below.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id chv_no_valid_mask[] = अणु
	/* See https://bugzilla.kernel.org/show_bug.cgi?id=194945 */
	अणु
		.ident = "Intel_Strago based Chromebooks (All models)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_FAMILY, "Intel_Strago"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "HP Chromebook 11 G5 (Setzer)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Setzer"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Acer Chromebook R11 (Cyan)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Cyan"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Samsung Chromebook 3 (Celes)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Celes"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम chv_init_irq_valid_mask(काष्ठा gpio_chip *chip,
				    अचिन्हित दीर्घ *valid_mask,
				    अचिन्हित पूर्णांक ngpios)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];
	पूर्णांक i;

	/* Do not add GPIOs that can only generate GPEs to the IRQ करोमुख्य */
	क्रम (i = 0; i < pctrl->soc->npins; i++) अणु
		स्थिर काष्ठा pinctrl_pin_desc *desc;
		u32 पूर्णांकsel;

		desc = &pctrl->soc->pins[i];

		पूर्णांकsel = chv_पढ़ोl(pctrl, desc->number, CHV_PADCTRL0);
		पूर्णांकsel &= CHV_PADCTRL0_INTSEL_MASK;
		पूर्णांकsel >>= CHV_PADCTRL0_INTSEL_SHIFT;

		अगर (पूर्णांकsel >= community->nirqs)
			clear_bit(desc->number, valid_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक chv_gpio_irq_init_hw(काष्ठा gpio_chip *chip)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];

	/*
	 * The same set of machines in chv_no_valid_mask[] have incorrectly
	 * configured GPIOs that generate spurious पूर्णांकerrupts so we use
	 * this same list to apply another quirk क्रम them.
	 *
	 * See also https://bugzilla.kernel.org/show_bug.cgi?id=197953.
	 */
	अगर (!pctrl->chip.irq.init_valid_mask) अणु
		/*
		 * Mask all पूर्णांकerrupts the community is able to generate
		 * but leave the ones that can only generate GPEs unmasked.
		 */
		chv_pctrl_ग_लिखोl(pctrl, CHV_INTMASK, GENMASK(31, community->nirqs));
	पूर्ण

	/* Clear all पूर्णांकerrupts */
	chv_pctrl_ग_लिखोl(pctrl, CHV_INTSTAT, 0xffff);

	वापस 0;
पूर्ण

अटल पूर्णांक chv_gpio_add_pin_ranges(काष्ठा gpio_chip *chip)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];
	स्थिर काष्ठा पूर्णांकel_padgroup *gpp;
	पूर्णांक ret, i;

	क्रम (i = 0; i < community->ngpps; i++) अणु
		gpp = &community->gpps[i];
		ret = gpiochip_add_pin_range(chip, dev_name(pctrl->dev),
					     gpp->base, gpp->base,
					     gpp->size);
		अगर (ret) अणु
			dev_err(pctrl->dev, "failed to add GPIO pin range\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक chv_gpio_probe(काष्ठा पूर्णांकel_pinctrl *pctrl, पूर्णांक irq)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];
	स्थिर काष्ठा पूर्णांकel_padgroup *gpp;
	काष्ठा gpio_chip *chip = &pctrl->chip;
	bool need_valid_mask = !dmi_check_प्रणाली(chv_no_valid_mask);
	पूर्णांक ret, i, irq_base;

	*chip = chv_gpio_chip;

	chip->ngpio = pctrl->soc->pins[pctrl->soc->npins - 1].number + 1;
	chip->label = dev_name(pctrl->dev);
	chip->add_pin_ranges = chv_gpio_add_pin_ranges;
	chip->parent = pctrl->dev;
	chip->base = -1;

	pctrl->irq = irq;
	pctrl->irqchip.name = "chv-gpio";
	pctrl->irqchip.irq_startup = chv_gpio_irq_startup;
	pctrl->irqchip.irq_ack = chv_gpio_irq_ack;
	pctrl->irqchip.irq_mask = chv_gpio_irq_mask;
	pctrl->irqchip.irq_unmask = chv_gpio_irq_unmask;
	pctrl->irqchip.irq_set_type = chv_gpio_irq_type;
	pctrl->irqchip.flags = IRQCHIP_SKIP_SET_WAKE;

	chip->irq.chip = &pctrl->irqchip;
	chip->irq.init_hw = chv_gpio_irq_init_hw;
	chip->irq.parent_handler = chv_gpio_irq_handler;
	chip->irq.num_parents = 1;
	chip->irq.parents = &pctrl->irq;
	chip->irq.शेष_type = IRQ_TYPE_NONE;
	chip->irq.handler = handle_bad_irq;
	अगर (need_valid_mask) अणु
		chip->irq.init_valid_mask = chv_init_irq_valid_mask;
	पूर्ण अन्यथा अणु
		irq_base = devm_irq_alloc_descs(pctrl->dev, -1, 0,
						pctrl->soc->npins, NUMA_NO_NODE);
		अगर (irq_base < 0) अणु
			dev_err(pctrl->dev, "Failed to allocate IRQ numbers\n");
			वापस irq_base;
		पूर्ण
	पूर्ण

	ret = devm_gpiochip_add_data(pctrl->dev, chip, pctrl);
	अगर (ret) अणु
		dev_err(pctrl->dev, "Failed to register gpiochip\n");
		वापस ret;
	पूर्ण

	अगर (!need_valid_mask) अणु
		क्रम (i = 0; i < community->ngpps; i++) अणु
			gpp = &community->gpps[i];

			irq_करोमुख्य_associate_many(chip->irq.करोमुख्य, irq_base,
						  gpp->base, gpp->size);
			irq_base += gpp->size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल acpi_status chv_pinctrl_mmio_access_handler(u32 function,
	acpi_physical_address address, u32 bits, u64 *value,
	व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = region_context;
	अचिन्हित दीर्घ flags;
	acpi_status ret = AE_OK;

	raw_spin_lock_irqsave(&chv_lock, flags);

	अगर (function == ACPI_WRITE)
		chv_pctrl_ग_लिखोl(pctrl, address, *value);
	अन्यथा अगर (function == ACPI_READ)
		*value = chv_pctrl_पढ़ोl(pctrl, address);
	अन्यथा
		ret = AE_BAD_PARAMETER;

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक chv_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *soc_data;
	काष्ठा पूर्णांकel_community *community;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	काष्ठा पूर्णांकel_pinctrl *pctrl;
	acpi_status status;
	पूर्णांक ret, irq;

	soc_data = पूर्णांकel_pinctrl_get_soc_data(pdev);
	अगर (IS_ERR(soc_data))
		वापस PTR_ERR(soc_data);

	pctrl = devm_kzalloc(dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->dev = dev;
	pctrl->soc = soc_data;

	pctrl->ncommunities = pctrl->soc->ncommunities;
	pctrl->communities = devm_kmemdup(dev, pctrl->soc->communities,
					  pctrl->ncommunities * माप(*pctrl->communities),
					  GFP_KERNEL);
	अगर (!pctrl->communities)
		वापस -ENOMEM;

	community = &pctrl->communities[0];
	community->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(community->regs))
		वापस PTR_ERR(community->regs);

	community->pad_regs = community->regs + FAMILY_PAD_REGS_OFF;

#अगर_घोषित CONFIG_PM_SLEEP
	pctrl->context.pads = devm_kसुस्मृति(dev, pctrl->soc->npins,
					   माप(*pctrl->context.pads),
					   GFP_KERNEL);
	अगर (!pctrl->context.pads)
		वापस -ENOMEM;
#पूर्ण_अगर

	pctrl->context.communities = devm_kसुस्मृति(dev, pctrl->soc->ncommunities,
						  माप(*pctrl->context.communities),
						  GFP_KERNEL);
	अगर (!pctrl->context.communities)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	pctrl->pctldesc = chv_pinctrl_desc;
	pctrl->pctldesc.name = dev_name(dev);
	pctrl->pctldesc.pins = pctrl->soc->pins;
	pctrl->pctldesc.npins = pctrl->soc->npins;

	pctrl->pctldev = devm_pinctrl_रेजिस्टर(dev, &pctrl->pctldesc, pctrl);
	अगर (IS_ERR(pctrl->pctldev)) अणु
		dev_err(dev, "failed to register pinctrl driver\n");
		वापस PTR_ERR(pctrl->pctldev);
	पूर्ण

	ret = chv_gpio_probe(pctrl, irq);
	अगर (ret)
		वापस ret;

	status = acpi_install_address_space_handler(adev->handle,
					community->acpi_space_id,
					chv_pinctrl_mmio_access_handler,
					शून्य, pctrl);
	अगर (ACPI_FAILURE(status))
		dev_err(dev, "failed to install ACPI addr space handler\n");

	platक्रमm_set_drvdata(pdev, pctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक chv_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[0];

	acpi_हटाओ_address_space_handler(ACPI_COMPANION(&pdev->dev),
					  community->acpi_space_id,
					  chv_pinctrl_mmio_access_handler);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक chv_pinctrl_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel_community_context *cctx = &pctrl->context.communities[0];
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&chv_lock, flags);

	cctx->saved_पूर्णांकmask = chv_pctrl_पढ़ोl(pctrl, CHV_INTMASK);

	क्रम (i = 0; i < pctrl->soc->npins; i++) अणु
		स्थिर काष्ठा pinctrl_pin_desc *desc;
		काष्ठा पूर्णांकel_pad_context *ctx = &pctrl->context.pads[i];

		desc = &pctrl->soc->pins[i];
		अगर (chv_pad_locked(pctrl, desc->number))
			जारी;

		ctx->padctrl0 = chv_पढ़ोl(pctrl, desc->number, CHV_PADCTRL0);
		ctx->padctrl0 &= ~CHV_PADCTRL0_GPIORXSTATE;

		ctx->padctrl1 = chv_पढ़ोl(pctrl, desc->number, CHV_PADCTRL1);
	पूर्ण

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक chv_pinctrl_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel_community_context *cctx = &pctrl->context.communities[0];
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&chv_lock, flags);

	/*
	 * Mask all पूर्णांकerrupts beक्रमe restoring per-pin configuration
	 * रेजिस्टरs because we करोn't know in which state BIOS left them
	 * upon निकासing suspend.
	 */
	chv_pctrl_ग_लिखोl(pctrl, CHV_INTMASK, 0x0000);

	क्रम (i = 0; i < pctrl->soc->npins; i++) अणु
		स्थिर काष्ठा pinctrl_pin_desc *desc;
		काष्ठा पूर्णांकel_pad_context *ctx = &pctrl->context.pads[i];
		u32 val;

		desc = &pctrl->soc->pins[i];
		अगर (chv_pad_locked(pctrl, desc->number))
			जारी;

		/* Only restore अगर our saved state dअगरfers from the current */
		val = chv_पढ़ोl(pctrl, desc->number, CHV_PADCTRL0);
		val &= ~CHV_PADCTRL0_GPIORXSTATE;
		अगर (ctx->padctrl0 != val) अणु
			chv_ग_लिखोl(pctrl, desc->number, CHV_PADCTRL0, ctx->padctrl0);
			dev_dbg(pctrl->dev, "restored pin %2u ctrl0 0x%08x\n",
				desc->number, chv_पढ़ोl(pctrl, desc->number, CHV_PADCTRL0));
		पूर्ण

		val = chv_पढ़ोl(pctrl, desc->number, CHV_PADCTRL1);
		अगर (ctx->padctrl1 != val) अणु
			chv_ग_लिखोl(pctrl, desc->number, CHV_PADCTRL1, ctx->padctrl1);
			dev_dbg(pctrl->dev, "restored pin %2u ctrl1 0x%08x\n",
				desc->number, chv_पढ़ोl(pctrl, desc->number, CHV_PADCTRL1));
		पूर्ण
	पूर्ण

	/*
	 * Now that all pins are restored to known state, we can restore
	 * the पूर्णांकerrupt mask रेजिस्टर as well.
	 */
	chv_pctrl_ग_लिखोl(pctrl, CHV_INTSTAT, 0xffff);
	chv_pctrl_ग_लिखोl(pctrl, CHV_INTMASK, cctx->saved_पूर्णांकmask);

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops chv_pinctrl_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(chv_pinctrl_suspend_noirq,
				      chv_pinctrl_resume_noirq)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id chv_pinctrl_acpi_match[] = अणु
	अणु "INT33FF", (kernel_uदीर्घ_t)chv_soc_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, chv_pinctrl_acpi_match);

अटल काष्ठा platक्रमm_driver chv_pinctrl_driver = अणु
	.probe = chv_pinctrl_probe,
	.हटाओ = chv_pinctrl_हटाओ,
	.driver = अणु
		.name = "cherryview-pinctrl",
		.pm = &chv_pinctrl_pm_ops,
		.acpi_match_table = chv_pinctrl_acpi_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init chv_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&chv_pinctrl_driver);
पूर्ण
subsys_initcall(chv_pinctrl_init);

अटल व्योम __निकास chv_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&chv_pinctrl_driver);
पूर्ण
module_निकास(chv_pinctrl_निकास);

MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("Intel Cherryview/Braswell pinctrl driver");
MODULE_LICENSE("GPL v2");
