<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Gemini Lake SoC pinctrl/GPIO driver
 *
 * Copyright (C) 2017 Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-intel.h"

#घोषणा GLK_PAD_OWN	0x020
#घोषणा GLK_PADCFGLOCK	0x080
#घोषणा GLK_HOSTSW_OWN	0x0b0
#घोषणा GLK_GPI_IS	0x100
#घोषणा GLK_GPI_IE	0x110

#घोषणा GLK_COMMUNITY(s, e)				\
	अणु						\
		.paकरोwn_offset = GLK_PAD_OWN,		\
		.padcfglock_offset = GLK_PADCFGLOCK,	\
		.hostown_offset = GLK_HOSTSW_OWN,	\
		.is_offset = GLK_GPI_IS,		\
		.ie_offset = GLK_GPI_IE,		\
		.gpp_size = 32,                         \
		.pin_base = (s),			\
		.npins = ((e) - (s) + 1),		\
	पूर्ण

/* GLK */
अटल स्थिर काष्ठा pinctrl_pin_desc glk_northwest_pins[] = अणु
	PINCTRL_PIN(0, "TCK"),
	PINCTRL_PIN(1, "TRST_B"),
	PINCTRL_PIN(2, "TMS"),
	PINCTRL_PIN(3, "TDI"),
	PINCTRL_PIN(4, "TDO"),
	PINCTRL_PIN(5, "JTAGX"),
	PINCTRL_PIN(6, "CX_PREQ_B"),
	PINCTRL_PIN(7, "CX_PRDY_B"),
	PINCTRL_PIN(8, "GPIO_8"),
	PINCTRL_PIN(9, "GPIO_9"),
	PINCTRL_PIN(10, "GPIO_10"),
	PINCTRL_PIN(11, "GPIO_11"),
	PINCTRL_PIN(12, "GPIO_12"),
	PINCTRL_PIN(13, "GPIO_13"),
	PINCTRL_PIN(14, "GPIO_14"),
	PINCTRL_PIN(15, "GPIO_15"),
	PINCTRL_PIN(16, "GPIO_16"),
	PINCTRL_PIN(17, "GPIO_17"),
	PINCTRL_PIN(18, "GPIO_18"),
	PINCTRL_PIN(19, "GPIO_19"),
	PINCTRL_PIN(20, "GPIO_20"),
	PINCTRL_PIN(21, "GPIO_21"),
	PINCTRL_PIN(22, "GPIO_22"),
	PINCTRL_PIN(23, "GPIO_23"),
	PINCTRL_PIN(24, "GPIO_24"),
	PINCTRL_PIN(25, "GPIO_25"),
	PINCTRL_PIN(26, "ISH_GPIO_0"),
	PINCTRL_PIN(27, "ISH_GPIO_1"),
	PINCTRL_PIN(28, "ISH_GPIO_2"),
	PINCTRL_PIN(29, "ISH_GPIO_3"),
	PINCTRL_PIN(30, "ISH_GPIO_4"),
	PINCTRL_PIN(31, "ISH_GPIO_5"),
	PINCTRL_PIN(32, "ISH_GPIO_6"),
	PINCTRL_PIN(33, "ISH_GPIO_7"),
	PINCTRL_PIN(34, "ISH_GPIO_8"),
	PINCTRL_PIN(35, "ISH_GPIO_9"),
	PINCTRL_PIN(36, "GPIO_36"),
	PINCTRL_PIN(37, "GPIO_37"),
	PINCTRL_PIN(38, "GPIO_38"),
	PINCTRL_PIN(39, "GPIO_39"),
	PINCTRL_PIN(40, "GPIO_40"),
	PINCTRL_PIN(41, "GPIO_41"),
	PINCTRL_PIN(42, "GP_INTD_DSI_TE1"),
	PINCTRL_PIN(43, "GP_INTD_DSI_TE2"),
	PINCTRL_PIN(44, "USB_OC0_B"),
	PINCTRL_PIN(45, "USB_OC1_B"),
	PINCTRL_PIN(46, "DSI_I2C_SDA"),
	PINCTRL_PIN(47, "DSI_I2C_SCL"),
	PINCTRL_PIN(48, "PMC_I2C_SDA"),
	PINCTRL_PIN(49, "PMC_I2C_SCL"),
	PINCTRL_PIN(50, "LPSS_I2C0_SDA"),
	PINCTRL_PIN(51, "LPSS_I2C0_SCL"),
	PINCTRL_PIN(52, "LPSS_I2C1_SDA"),
	PINCTRL_PIN(53, "LPSS_I2C1_SCL"),
	PINCTRL_PIN(54, "LPSS_I2C2_SDA"),
	PINCTRL_PIN(55, "LPSS_I2C2_SCL"),
	PINCTRL_PIN(56, "LPSS_I2C3_SDA"),
	PINCTRL_PIN(57, "LPSS_I2C3_SCL"),
	PINCTRL_PIN(58, "LPSS_I2C4_SDA"),
	PINCTRL_PIN(59, "LPSS_I2C4_SCL"),
	PINCTRL_PIN(60, "LPSS_UART0_RXD"),
	PINCTRL_PIN(61, "LPSS_UART0_TXD"),
	PINCTRL_PIN(62, "LPSS_UART0_RTS_B"),
	PINCTRL_PIN(63, "LPSS_UART0_CTS_B"),
	PINCTRL_PIN(64, "LPSS_UART2_RXD"),
	PINCTRL_PIN(65, "LPSS_UART2_TXD"),
	PINCTRL_PIN(66, "LPSS_UART2_RTS_B"),
	PINCTRL_PIN(67, "LPSS_UART2_CTS_B"),
	PINCTRL_PIN(68, "PMC_SPI_FS0"),
	PINCTRL_PIN(69, "PMC_SPI_FS1"),
	PINCTRL_PIN(70, "PMC_SPI_FS2"),
	PINCTRL_PIN(71, "PMC_SPI_RXD"),
	PINCTRL_PIN(72, "PMC_SPI_TXD"),
	PINCTRL_PIN(73, "PMC_SPI_CLK"),
	PINCTRL_PIN(74, "THERMTRIP_B"),
	PINCTRL_PIN(75, "PROCHOT_B"),
	PINCTRL_PIN(76, "EMMC_RST_B"),
	PINCTRL_PIN(77, "GPIO_212"),
	PINCTRL_PIN(78, "GPIO_213"),
	PINCTRL_PIN(79, "GPIO_214"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक glk_northwest_uart1_pins[] = अणु 26, 27, 28, 29 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_pwm0_pins[] = अणु 42 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_pwm1_pins[] = अणु 43 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_pwm2_pins[] = अणु 44 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_pwm3_pins[] = अणु 45 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_i2c0_pins[] = अणु 50, 51 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_i2c1_pins[] = अणु 52, 53 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_i2c2_pins[] = अणु 54, 55 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_i2c3_pins[] = अणु 56, 57 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_i2c4_pins[] = अणु 58, 59 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_uart0_pins[] = अणु 60, 61, 62, 63 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_northwest_uart2_pins[] = अणु 64, 65, 66, 67 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup glk_northwest_groups[] = अणु
	PIN_GROUP("uart1_grp", glk_northwest_uart1_pins, 2),
	PIN_GROUP("pwm0_grp", glk_northwest_pwm0_pins, 2),
	PIN_GROUP("pwm1_grp", glk_northwest_pwm1_pins, 2),
	PIN_GROUP("pwm2_grp", glk_northwest_pwm2_pins, 2),
	PIN_GROUP("pwm3_grp", glk_northwest_pwm3_pins, 2),
	PIN_GROUP("i2c0_grp", glk_northwest_i2c0_pins, 1),
	PIN_GROUP("i2c1_grp", glk_northwest_i2c1_pins, 1),
	PIN_GROUP("i2c2_grp", glk_northwest_i2c2_pins, 1),
	PIN_GROUP("i2c3_grp", glk_northwest_i2c3_pins, 1),
	PIN_GROUP("i2c4_grp", glk_northwest_i2c4_pins, 1),
	PIN_GROUP("uart0_grp", glk_northwest_uart0_pins, 1),
	PIN_GROUP("uart2_grp", glk_northwest_uart2_pins, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर glk_northwest_uart1_groups[] = अणु "uart1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_pwm0_groups[] = अणु "pwm0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_pwm1_groups[] = अणु "pwm1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_pwm2_groups[] = अणु "pwm2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_pwm3_groups[] = अणु "pwm3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_i2c0_groups[] = अणु "i2c0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_i2c1_groups[] = अणु "i2c1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_i2c2_groups[] = अणु "i2c2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_i2c3_groups[] = अणु "i2c3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_i2c4_groups[] = अणु "i2c4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_uart0_groups[] = अणु "uart0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_northwest_uart2_groups[] = अणु "uart2_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function glk_northwest_functions[] = अणु
	FUNCTION("uart1", glk_northwest_uart1_groups),
	FUNCTION("pmw0", glk_northwest_pwm0_groups),
	FUNCTION("pmw1", glk_northwest_pwm1_groups),
	FUNCTION("pmw2", glk_northwest_pwm2_groups),
	FUNCTION("pmw3", glk_northwest_pwm3_groups),
	FUNCTION("i2c0", glk_northwest_i2c0_groups),
	FUNCTION("i2c1", glk_northwest_i2c1_groups),
	FUNCTION("i2c2", glk_northwest_i2c2_groups),
	FUNCTION("i2c3", glk_northwest_i2c3_groups),
	FUNCTION("i2c4", glk_northwest_i2c4_groups),
	FUNCTION("uart0", glk_northwest_uart0_groups),
	FUNCTION("uart2", glk_northwest_uart2_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community glk_northwest_communities[] = अणु
	GLK_COMMUNITY(0, 79),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data glk_northwest_soc_data = अणु
	.uid = "1",
	.pins = glk_northwest_pins,
	.npins = ARRAY_SIZE(glk_northwest_pins),
	.groups = glk_northwest_groups,
	.ngroups = ARRAY_SIZE(glk_northwest_groups),
	.functions = glk_northwest_functions,
	.nfunctions = ARRAY_SIZE(glk_northwest_functions),
	.communities = glk_northwest_communities,
	.ncommunities = ARRAY_SIZE(glk_northwest_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc glk_north_pins[] = अणु
	PINCTRL_PIN(0, "SVID0_ALERT_B"),
	PINCTRL_PIN(1, "SVID0_DATA"),
	PINCTRL_PIN(2, "SVID0_CLK"),
	PINCTRL_PIN(3, "LPSS_SPI_0_CLK"),
	PINCTRL_PIN(4, "LPSS_SPI_0_FS0"),
	PINCTRL_PIN(5, "LPSS_SPI_0_FS1"),
	PINCTRL_PIN(6, "LPSS_SPI_0_RXD"),
	PINCTRL_PIN(7, "LPSS_SPI_0_TXD"),
	PINCTRL_PIN(8, "LPSS_SPI_2_CLK"),
	PINCTRL_PIN(9, "LPSS_SPI_2_FS0"),
	PINCTRL_PIN(10, "LPSS_SPI_2_FS1"),
	PINCTRL_PIN(11, "LPSS_SPI_2_FS2"),
	PINCTRL_PIN(12, "LPSS_SPI_2_RXD"),
	PINCTRL_PIN(13, "LPSS_SPI_2_TXD"),
	PINCTRL_PIN(14, "FST_SPI_CS0_B"),
	PINCTRL_PIN(15, "FST_SPI_CS1_B"),
	PINCTRL_PIN(16, "FST_SPI_MOSI_IO0"),
	PINCTRL_PIN(17, "FST_SPI_MISO_IO1"),
	PINCTRL_PIN(18, "FST_SPI_IO2"),
	PINCTRL_PIN(19, "FST_SPI_IO3"),
	PINCTRL_PIN(20, "FST_SPI_CLK"),
	PINCTRL_PIN(21, "FST_SPI_CLK_FB"),
	PINCTRL_PIN(22, "PMU_PLTRST_B"),
	PINCTRL_PIN(23, "PMU_PWRBTN_B"),
	PINCTRL_PIN(24, "PMU_SLP_S0_B"),
	PINCTRL_PIN(25, "PMU_SLP_S3_B"),
	PINCTRL_PIN(26, "PMU_SLP_S4_B"),
	PINCTRL_PIN(27, "SUSPWRDNACK"),
	PINCTRL_PIN(28, "EMMC_DNX_PWR_EN_B"),
	PINCTRL_PIN(29, "GPIO_105"),
	PINCTRL_PIN(30, "PMU_BATLOW_B"),
	PINCTRL_PIN(31, "PMU_RESETBUTTON_B"),
	PINCTRL_PIN(32, "PMU_SUSCLK"),
	PINCTRL_PIN(33, "SUS_STAT_B"),
	PINCTRL_PIN(34, "LPSS_I2C5_SDA"),
	PINCTRL_PIN(35, "LPSS_I2C5_SCL"),
	PINCTRL_PIN(36, "LPSS_I2C6_SDA"),
	PINCTRL_PIN(37, "LPSS_I2C6_SCL"),
	PINCTRL_PIN(38, "LPSS_I2C7_SDA"),
	PINCTRL_PIN(39, "LPSS_I2C7_SCL"),
	PINCTRL_PIN(40, "PCIE_WAKE0_B"),
	PINCTRL_PIN(41, "PCIE_WAKE1_B"),
	PINCTRL_PIN(42, "PCIE_WAKE2_B"),
	PINCTRL_PIN(43, "PCIE_WAKE3_B"),
	PINCTRL_PIN(44, "PCIE_CLKREQ0_B"),
	PINCTRL_PIN(45, "PCIE_CLKREQ1_B"),
	PINCTRL_PIN(46, "PCIE_CLKREQ2_B"),
	PINCTRL_PIN(47, "PCIE_CLKREQ3_B"),
	PINCTRL_PIN(48, "HV_DDI0_DDC_SDA"),
	PINCTRL_PIN(49, "HV_DDI0_DDC_SCL"),
	PINCTRL_PIN(50, "HV_DDI1_DDC_SDA"),
	PINCTRL_PIN(51, "HV_DDI1_DDC_SCL"),
	PINCTRL_PIN(52, "PANEL0_VDDEN"),
	PINCTRL_PIN(53, "PANEL0_BKLTEN"),
	PINCTRL_PIN(54, "PANEL0_BKLTCTL"),
	PINCTRL_PIN(55, "HV_DDI0_HPD"),
	PINCTRL_PIN(56, "HV_DDI1_HPD"),
	PINCTRL_PIN(57, "HV_EDP_HPD"),
	PINCTRL_PIN(58, "GPIO_134"),
	PINCTRL_PIN(59, "GPIO_135"),
	PINCTRL_PIN(60, "GPIO_136"),
	PINCTRL_PIN(61, "GPIO_137"),
	PINCTRL_PIN(62, "GPIO_138"),
	PINCTRL_PIN(63, "GPIO_139"),
	PINCTRL_PIN(64, "GPIO_140"),
	PINCTRL_PIN(65, "GPIO_141"),
	PINCTRL_PIN(66, "GPIO_142"),
	PINCTRL_PIN(67, "GPIO_143"),
	PINCTRL_PIN(68, "GPIO_144"),
	PINCTRL_PIN(69, "GPIO_145"),
	PINCTRL_PIN(70, "GPIO_146"),
	PINCTRL_PIN(71, "LPC_ILB_SERIRQ"),
	PINCTRL_PIN(72, "LPC_CLKOUT0"),
	PINCTRL_PIN(73, "LPC_CLKOUT1"),
	PINCTRL_PIN(74, "LPC_AD0"),
	PINCTRL_PIN(75, "LPC_AD1"),
	PINCTRL_PIN(76, "LPC_AD2"),
	PINCTRL_PIN(77, "LPC_AD3"),
	PINCTRL_PIN(78, "LPC_CLKRUNB"),
	PINCTRL_PIN(79, "LPC_FRAMEB"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक glk_north_spi0_pins[] = अणु 3, 4, 5, 6, 7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_north_spi1_pins[] = अणु 8, 9, 10, 11, 12, 13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_north_i2c5_pins[] = अणु 34, 35 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_north_i2c6_pins[] = अणु 36, 37 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_north_i2c7_pins[] = अणु 38, 39 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_north_uart0_pins[] = अणु 62, 63, 64, 65 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_north_spi0b_pins[] = अणु 66, 67, 68, 69, 70 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup glk_north_groups[] = अणु
	PIN_GROUP("spi0_grp", glk_north_spi0_pins, 1),
	PIN_GROUP("spi1_grp", glk_north_spi1_pins, 1),
	PIN_GROUP("i2c5_grp", glk_north_i2c5_pins, 1),
	PIN_GROUP("i2c6_grp", glk_north_i2c6_pins, 1),
	PIN_GROUP("i2c7_grp", glk_north_i2c7_pins, 1),
	PIN_GROUP("uart0_grp", glk_north_uart0_pins, 2),
	PIN_GROUP("spi0b_grp", glk_north_spi0b_pins, 2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर glk_north_spi0_groups[] = अणु "spi0_grp", "spi0b_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_north_spi1_groups[] = अणु "spi1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_north_i2c5_groups[] = अणु "i2c5_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_north_i2c6_groups[] = अणु "i2c6_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_north_i2c7_groups[] = अणु "i2c7_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_north_uart0_groups[] = अणु "uart0_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function glk_north_functions[] = अणु
	FUNCTION("spi0", glk_north_spi0_groups),
	FUNCTION("spi1", glk_north_spi1_groups),
	FUNCTION("i2c5", glk_north_i2c5_groups),
	FUNCTION("i2c6", glk_north_i2c6_groups),
	FUNCTION("i2c7", glk_north_i2c7_groups),
	FUNCTION("uart0", glk_north_uart0_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community glk_north_communities[] = अणु
	GLK_COMMUNITY(0, 79),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data glk_north_soc_data = अणु
	.uid = "2",
	.pins = glk_north_pins,
	.npins = ARRAY_SIZE(glk_north_pins),
	.groups = glk_north_groups,
	.ngroups = ARRAY_SIZE(glk_north_groups),
	.functions = glk_north_functions,
	.nfunctions = ARRAY_SIZE(glk_north_functions),
	.communities = glk_north_communities,
	.ncommunities = ARRAY_SIZE(glk_north_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc glk_audio_pins[] = अणु
	PINCTRL_PIN(0, "AVS_I2S0_MCLK"),
	PINCTRL_PIN(1, "AVS_I2S0_BCLK"),
	PINCTRL_PIN(2, "AVS_I2S0_WS_SYNC"),
	PINCTRL_PIN(3, "AVS_I2S0_SDI"),
	PINCTRL_PIN(4, "AVS_I2S0_SDO"),
	PINCTRL_PIN(5, "AVS_I2S1_MCLK"),
	PINCTRL_PIN(6, "AVS_I2S1_BCLK"),
	PINCTRL_PIN(7, "AVS_I2S1_WS_SYNC"),
	PINCTRL_PIN(8, "AVS_I2S1_SDI"),
	PINCTRL_PIN(9, "AVS_I2S1_SDO"),
	PINCTRL_PIN(10, "AVS_HDA_BCLK"),
	PINCTRL_PIN(11, "AVS_HDA_WS_SYNC"),
	PINCTRL_PIN(12, "AVS_HDA_SDI"),
	PINCTRL_PIN(13, "AVS_HDA_SDO"),
	PINCTRL_PIN(14, "AVS_HDA_RSTB"),
	PINCTRL_PIN(15, "AVS_M_CLK_A1"),
	PINCTRL_PIN(16, "AVS_M_CLK_B1"),
	PINCTRL_PIN(17, "AVS_M_DATA_1"),
	PINCTRL_PIN(18, "AVS_M_CLK_AB2"),
	PINCTRL_PIN(19, "AVS_M_DATA_2"),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community glk_audio_communities[] = अणु
	GLK_COMMUNITY(0, 19),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data glk_audio_soc_data = अणु
	.uid = "3",
	.pins = glk_audio_pins,
	.npins = ARRAY_SIZE(glk_audio_pins),
	.communities = glk_audio_communities,
	.ncommunities = ARRAY_SIZE(glk_audio_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc glk_scc_pins[] = अणु
	PINCTRL_PIN(0, "SMB_ALERTB"),
	PINCTRL_PIN(1, "SMB_CLK"),
	PINCTRL_PIN(2, "SMB_DATA"),
	PINCTRL_PIN(3, "SDCARD_LVL_WP"),
	PINCTRL_PIN(4, "SDCARD_CLK"),
	PINCTRL_PIN(5, "SDCARD_CLK_FB"),
	PINCTRL_PIN(6, "SDCARD_D0"),
	PINCTRL_PIN(7, "SDCARD_D1"),
	PINCTRL_PIN(8, "SDCARD_D2"),
	PINCTRL_PIN(9, "SDCARD_D3"),
	PINCTRL_PIN(10, "SDCARD_CMD"),
	PINCTRL_PIN(11, "SDCARD_CD_B"),
	PINCTRL_PIN(12, "SDCARD_PWR_DOWN_B"),
	PINCTRL_PIN(13, "GPIO_210"),
	PINCTRL_PIN(14, "OSC_CLK_OUT_0"),
	PINCTRL_PIN(15, "OSC_CLK_OUT_1"),
	PINCTRL_PIN(16, "CNV_BRI_DT"),
	PINCTRL_PIN(17, "CNV_BRI_RSP"),
	PINCTRL_PIN(18, "CNV_RGI_DT"),
	PINCTRL_PIN(19, "CNV_RGI_RSP"),
	PINCTRL_PIN(20, "CNV_RF_RESET_B"),
	PINCTRL_PIN(21, "XTAL_CLKREQ"),
	PINCTRL_PIN(22, "SDIO_CLK_FB"),
	PINCTRL_PIN(23, "EMMC0_CLK"),
	PINCTRL_PIN(24, "EMMC0_CLK_FB"),
	PINCTRL_PIN(25, "EMMC0_D0"),
	PINCTRL_PIN(26, "EMMC0_D1"),
	PINCTRL_PIN(27, "EMMC0_D2"),
	PINCTRL_PIN(28, "EMMC0_D3"),
	PINCTRL_PIN(29, "EMMC0_D4"),
	PINCTRL_PIN(30, "EMMC0_D5"),
	PINCTRL_PIN(31, "EMMC0_D6"),
	PINCTRL_PIN(32, "EMMC0_D7"),
	PINCTRL_PIN(33, "EMMC0_CMD"),
	PINCTRL_PIN(34, "EMMC0_STROBE"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक glk_scc_i2c7_pins[] = अणु 1, 2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_scc_sdcard_pins[] = अणु
	3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_scc_sdio_pins[] = अणु 16, 17, 18, 19, 20, 21, 22 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_scc_uart1_pins[] = अणु 16, 17, 18, 19 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक glk_scc_emmc_pins[] = अणु
	23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup glk_scc_groups[] = अणु
	PIN_GROUP("i2c7_grp", glk_scc_i2c7_pins, 2),
	PIN_GROUP("sdcard_grp", glk_scc_sdcard_pins, 1),
	PIN_GROUP("sdio_grp", glk_scc_sdio_pins, 2),
	PIN_GROUP("uart1_grp", glk_scc_uart1_pins, 3),
	PIN_GROUP("emmc_grp", glk_scc_emmc_pins, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर glk_scc_i2c7_groups[] = अणु "i2c7_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_scc_sdcard_groups[] = अणु "sdcard_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_scc_sdio_groups[] = अणु "sdio_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_scc_uart1_groups[] = अणु "uart1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर glk_scc_emmc_groups[] = अणु "emmc_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function glk_scc_functions[] = अणु
	FUNCTION("i2c7", glk_scc_i2c7_groups),
	FUNCTION("sdcard", glk_scc_sdcard_groups),
	FUNCTION("sdio", glk_scc_sdio_groups),
	FUNCTION("uart1", glk_scc_uart1_groups),
	FUNCTION("emmc", glk_scc_emmc_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community glk_scc_communities[] = अणु
	GLK_COMMUNITY(0, 34),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data glk_scc_soc_data = अणु
	.uid = "4",
	.pins = glk_scc_pins,
	.npins = ARRAY_SIZE(glk_scc_pins),
	.groups = glk_scc_groups,
	.ngroups = ARRAY_SIZE(glk_scc_groups),
	.functions = glk_scc_functions,
	.nfunctions = ARRAY_SIZE(glk_scc_functions),
	.communities = glk_scc_communities,
	.ncommunities = ARRAY_SIZE(glk_scc_communities),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *glk_pinctrl_soc_data[] = अणु
	&glk_northwest_soc_data,
	&glk_north_soc_data,
	&glk_audio_soc_data,
	&glk_scc_soc_data,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id glk_pinctrl_acpi_match[] = अणु
	अणु "INT3453", (kernel_uदीर्घ_t)glk_pinctrl_soc_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, glk_pinctrl_acpi_match);

अटल INTEL_PINCTRL_PM_OPS(glk_pinctrl_pm_ops);

अटल काष्ठा platक्रमm_driver glk_pinctrl_driver = अणु
	.probe = पूर्णांकel_pinctrl_probe_by_uid,
	.driver = अणु
		.name = "geminilake-pinctrl",
		.acpi_match_table = glk_pinctrl_acpi_match,
		.pm = &glk_pinctrl_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init glk_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&glk_pinctrl_driver);
पूर्ण
subsys_initcall(glk_pinctrl_init);

अटल व्योम __निकास glk_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&glk_pinctrl_driver);
पूर्ण
module_निकास(glk_pinctrl_निकास);

MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("Intel Gemini Lake SoC pinctrl/GPIO driver");
MODULE_LICENSE("GPL v2");
