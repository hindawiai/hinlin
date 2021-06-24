<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Broxton SoC pinctrl/GPIO driver
 *
 * Copyright (C) 2015, 2016 Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-intel.h"

#घोषणा BXT_PAD_OWN	0x020
#घोषणा BXT_PADCFGLOCK	0x060
#घोषणा BXT_HOSTSW_OWN	0x080
#घोषणा BXT_GPI_IS	0x100
#घोषणा BXT_GPI_IE	0x110

#घोषणा BXT_COMMUNITY(s, e)				\
	अणु						\
		.paकरोwn_offset = BXT_PAD_OWN,		\
		.padcfglock_offset = BXT_PADCFGLOCK,	\
		.hostown_offset = BXT_HOSTSW_OWN,	\
		.is_offset = BXT_GPI_IS,		\
		.ie_offset = BXT_GPI_IE,		\
		.gpp_size = 32,                         \
		.pin_base = (s),			\
		.npins = ((e) - (s) + 1),		\
	पूर्ण

/* BXT */
अटल स्थिर काष्ठा pinctrl_pin_desc bxt_north_pins[] = अणु
	PINCTRL_PIN(0, "GPIO_0"),
	PINCTRL_PIN(1, "GPIO_1"),
	PINCTRL_PIN(2, "GPIO_2"),
	PINCTRL_PIN(3, "GPIO_3"),
	PINCTRL_PIN(4, "GPIO_4"),
	PINCTRL_PIN(5, "GPIO_5"),
	PINCTRL_PIN(6, "GPIO_6"),
	PINCTRL_PIN(7, "GPIO_7"),
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
	PINCTRL_PIN(26, "GPIO_26"),
	PINCTRL_PIN(27, "GPIO_27"),
	PINCTRL_PIN(28, "GPIO_28"),
	PINCTRL_PIN(29, "GPIO_29"),
	PINCTRL_PIN(30, "GPIO_30"),
	PINCTRL_PIN(31, "GPIO_31"),
	PINCTRL_PIN(32, "GPIO_32"),
	PINCTRL_PIN(33, "GPIO_33"),
	PINCTRL_PIN(34, "PWM0"),
	PINCTRL_PIN(35, "PWM1"),
	PINCTRL_PIN(36, "PWM2"),
	PINCTRL_PIN(37, "PWM3"),
	PINCTRL_PIN(38, "LPSS_UART0_RXD"),
	PINCTRL_PIN(39, "LPSS_UART0_TXD"),
	PINCTRL_PIN(40, "LPSS_UART0_RTS_B"),
	PINCTRL_PIN(41, "LPSS_UART0_CTS_B"),
	PINCTRL_PIN(42, "LPSS_UART1_RXD"),
	PINCTRL_PIN(43, "LPSS_UART1_TXD"),
	PINCTRL_PIN(44, "LPSS_UART1_RTS_B"),
	PINCTRL_PIN(45, "LPSS_UART1_CTS_B"),
	PINCTRL_PIN(46, "LPSS_UART2_RXD"),
	PINCTRL_PIN(47, "LPSS_UART2_TXD"),
	PINCTRL_PIN(48, "LPSS_UART2_RTS_B"),
	PINCTRL_PIN(49, "LPSS_UART2_CTS_B"),
	PINCTRL_PIN(50, "ISH_UART0_RXD"),
	PINCTRL_PIN(51, "ISH_UART0_TXT"),
	PINCTRL_PIN(52, "ISH_UART0_RTS_B"),
	PINCTRL_PIN(53, "ISH_UART0_CTS_B"),
	PINCTRL_PIN(54, "ISH_UART1_RXD"),
	PINCTRL_PIN(55, "ISH_UART1_TXT"),
	PINCTRL_PIN(56, "ISH_UART1_RTS_B"),
	PINCTRL_PIN(57, "ISH_UART1_CTS_B"),
	PINCTRL_PIN(58, "ISH_UART2_RXD"),
	PINCTRL_PIN(59, "ISH_UART2_TXD"),
	PINCTRL_PIN(60, "ISH_UART2_RTS_B"),
	PINCTRL_PIN(61, "ISH_UART2_CTS_B"),
	PINCTRL_PIN(62, "GP_CAMERASB00"),
	PINCTRL_PIN(63, "GP_CAMERASB01"),
	PINCTRL_PIN(64, "GP_CAMERASB02"),
	PINCTRL_PIN(65, "GP_CAMERASB03"),
	PINCTRL_PIN(66, "GP_CAMERASB04"),
	PINCTRL_PIN(67, "GP_CAMERASB05"),
	PINCTRL_PIN(68, "GP_CAMERASB06"),
	PINCTRL_PIN(69, "GP_CAMERASB07"),
	PINCTRL_PIN(70, "GP_CAMERASB08"),
	PINCTRL_PIN(71, "GP_CAMERASB09"),
	PINCTRL_PIN(72, "GP_CAMERASB10"),
	PINCTRL_PIN(73, "GP_CAMERASB11"),
	PINCTRL_PIN(74, "TCK"),
	PINCTRL_PIN(75, "TRST_B"),
	PINCTRL_PIN(76, "TMS"),
	PINCTRL_PIN(77, "TDI"),
	PINCTRL_PIN(78, "CX_PMODE"),
	PINCTRL_PIN(79, "CX_PREQ_B"),
	PINCTRL_PIN(80, "JTAGX"),
	PINCTRL_PIN(81, "CX_PRDY_B"),
	PINCTRL_PIN(82, "TDO"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bxt_north_pwm0_pins[] = अणु 34 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_pwm1_pins[] = अणु 35 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_pwm2_pins[] = अणु 36 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_pwm3_pins[] = अणु 37 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_uart0_pins[] = अणु 38, 39, 40, 41 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_uart1_pins[] = अणु 42, 43, 44, 45 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_uart2_pins[] = अणु 46, 47, 48, 49 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_uart0b_pins[] = अणु 50, 51, 52, 53 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_uart1b_pins[] = अणु 54, 55, 56, 57 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_uart2b_pins[] = अणु 58, 59, 60, 61 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_north_uart3_pins[] = अणु 58, 59, 60, 61 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup bxt_north_groups[] = अणु
	PIN_GROUP("pwm0_grp", bxt_north_pwm0_pins, 1),
	PIN_GROUP("pwm1_grp", bxt_north_pwm1_pins, 1),
	PIN_GROUP("pwm2_grp", bxt_north_pwm2_pins, 1),
	PIN_GROUP("pwm3_grp", bxt_north_pwm3_pins, 1),
	PIN_GROUP("uart0_grp", bxt_north_uart0_pins, 1),
	PIN_GROUP("uart1_grp", bxt_north_uart1_pins, 1),
	PIN_GROUP("uart2_grp", bxt_north_uart2_pins, 1),
	PIN_GROUP("uart0b_grp", bxt_north_uart0b_pins, 2),
	PIN_GROUP("uart1b_grp", bxt_north_uart1b_pins, 2),
	PIN_GROUP("uart2b_grp", bxt_north_uart2b_pins, 2),
	PIN_GROUP("uart3_grp", bxt_north_uart3_pins, 3),
पूर्ण;

अटल स्थिर अक्षर * स्थिर bxt_north_pwm0_groups[] = अणु "pwm0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_north_pwm1_groups[] = अणु "pwm1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_north_pwm2_groups[] = अणु "pwm2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_north_pwm3_groups[] = अणु "pwm3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_north_uart0_groups[] = अणु
	"uart0_grp", "uart0b_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_north_uart1_groups[] = अणु
	"uart1_grp", "uart1b_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_north_uart2_groups[] = अणु
	"uart2_grp", "uart2b_grp",
पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_north_uart3_groups[] = अणु "uart3_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function bxt_north_functions[] = अणु
	FUNCTION("pwm0", bxt_north_pwm0_groups),
	FUNCTION("pwm1", bxt_north_pwm1_groups),
	FUNCTION("pwm2", bxt_north_pwm2_groups),
	FUNCTION("pwm3", bxt_north_pwm3_groups),
	FUNCTION("uart0", bxt_north_uart0_groups),
	FUNCTION("uart1", bxt_north_uart1_groups),
	FUNCTION("uart2", bxt_north_uart2_groups),
	FUNCTION("uart3", bxt_north_uart3_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community bxt_north_communities[] = अणु
	BXT_COMMUNITY(0, 82),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data bxt_north_soc_data = अणु
	.uid = "1",
	.pins = bxt_north_pins,
	.npins = ARRAY_SIZE(bxt_north_pins),
	.groups = bxt_north_groups,
	.ngroups = ARRAY_SIZE(bxt_north_groups),
	.functions = bxt_north_functions,
	.nfunctions = ARRAY_SIZE(bxt_north_functions),
	.communities = bxt_north_communities,
	.ncommunities = ARRAY_SIZE(bxt_north_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc bxt_northwest_pins[] = अणु
	PINCTRL_PIN(0, "PMC_SPI_FS0"),
	PINCTRL_PIN(1, "PMC_SPI_FS1"),
	PINCTRL_PIN(2, "PMC_SPI_FS2"),
	PINCTRL_PIN(3, "PMC_SPI_RXD"),
	PINCTRL_PIN(4, "PMC_SPI_TXD"),
	PINCTRL_PIN(5, "PMC_SPI_CLK"),
	PINCTRL_PIN(6, "PMC_UART_RXD"),
	PINCTRL_PIN(7, "PMC_UART_TXD"),
	PINCTRL_PIN(8, "PMIC_PWRGOOD"),
	PINCTRL_PIN(9, "PMIC_RESET_B"),
	PINCTRL_PIN(10, "RTC_CLK"),
	PINCTRL_PIN(11, "PMIC_SDWN_B"),
	PINCTRL_PIN(12, "PMIC_BCUDISW2"),
	PINCTRL_PIN(13, "PMIC_BCUDISCRIT"),
	PINCTRL_PIN(14, "PMIC_THERMTRIP_B"),
	PINCTRL_PIN(15, "PMIC_STDBY"),
	PINCTRL_PIN(16, "SVID0_ALERT_B"),
	PINCTRL_PIN(17, "SVID0_DATA"),
	PINCTRL_PIN(18, "SVID0_CLK"),
	PINCTRL_PIN(19, "PMIC_I2C_SCL"),
	PINCTRL_PIN(20, "PMIC_I2C_SDA"),
	PINCTRL_PIN(21, "AVS_I2S1_MCLK"),
	PINCTRL_PIN(22, "AVS_I2S1_BCLK"),
	PINCTRL_PIN(23, "AVS_I2S1_WS_SYNC"),
	PINCTRL_PIN(24, "AVS_I2S1_SDI"),
	PINCTRL_PIN(25, "AVS_I2S1_SDO"),
	PINCTRL_PIN(26, "AVS_M_CLK_A1"),
	PINCTRL_PIN(27, "AVS_M_CLK_B1"),
	PINCTRL_PIN(28, "AVS_M_DATA_1"),
	PINCTRL_PIN(29, "AVS_M_CLK_AB2"),
	PINCTRL_PIN(30, "AVS_M_DATA_2"),
	PINCTRL_PIN(31, "AVS_I2S2_MCLK"),
	PINCTRL_PIN(32, "AVS_I2S2_BCLK"),
	PINCTRL_PIN(33, "AVS_I2S2_WS_SYNC"),
	PINCTRL_PIN(34, "AVS_I2S2_SDI"),
	PINCTRL_PIN(35, "AVS_I2S2_SDOK"),
	PINCTRL_PIN(36, "AVS_I2S3_BCLK"),
	PINCTRL_PIN(37, "AVS_I2S3_WS_SYNC"),
	PINCTRL_PIN(38, "AVS_I2S3_SDI"),
	PINCTRL_PIN(39, "AVS_I2S3_SDO"),
	PINCTRL_PIN(40, "AVS_I2S4_BCLK"),
	PINCTRL_PIN(41, "AVS_I2S4_WS_SYNC"),
	PINCTRL_PIN(42, "AVS_I2S4_SDI"),
	PINCTRL_PIN(43, "AVS_I2S4_SDO"),
	PINCTRL_PIN(44, "PROCHOT_B"),
	PINCTRL_PIN(45, "FST_SPI_CS0_B"),
	PINCTRL_PIN(46, "FST_SPI_CS1_B"),
	PINCTRL_PIN(47, "FST_SPI_MOSI_IO0"),
	PINCTRL_PIN(48, "FST_SPI_MISO_IO1"),
	PINCTRL_PIN(49, "FST_SPI_IO2"),
	PINCTRL_PIN(50, "FST_SPI_IO3"),
	PINCTRL_PIN(51, "FST_SPI_CLK"),
	PINCTRL_PIN(52, "FST_SPI_CLK_FB"),
	PINCTRL_PIN(53, "GP_SSP_0_CLK"),
	PINCTRL_PIN(54, "GP_SSP_0_FS0"),
	PINCTRL_PIN(55, "GP_SSP_0_FS1"),
	PINCTRL_PIN(56, "GP_SSP_0_FS2"),
	PINCTRL_PIN(57, "GP_SSP_0_RXD"),
	PINCTRL_PIN(58, "GP_SSP_0_TXD"),
	PINCTRL_PIN(59, "GP_SSP_1_CLK"),
	PINCTRL_PIN(60, "GP_SSP_1_FS0"),
	PINCTRL_PIN(61, "GP_SSP_1_FS1"),
	PINCTRL_PIN(62, "GP_SSP_1_FS2"),
	PINCTRL_PIN(63, "GP_SSP_1_FS3"),
	PINCTRL_PIN(64, "GP_SSP_1_RXD"),
	PINCTRL_PIN(65, "GP_SSP_1_TXD"),
	PINCTRL_PIN(66, "GP_SSP_2_CLK"),
	PINCTRL_PIN(67, "GP_SSP_2_FS0"),
	PINCTRL_PIN(68, "GP_SSP_2_FS1"),
	PINCTRL_PIN(69, "GP_SSP_2_FS2"),
	PINCTRL_PIN(70, "GP_SSP_2_RXD"),
	PINCTRL_PIN(71, "GP_SSP_2_TXD"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bxt_northwest_ssp0_pins[] = अणु 53, 54, 55, 56, 57, 58 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_northwest_ssp1_pins[] = अणु
	59, 60, 61, 62, 63, 64, 65
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_northwest_ssp2_pins[] = अणु 66, 67, 68, 69, 70, 71 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_northwest_uart3_pins[] = अणु 67, 68, 69, 70 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup bxt_northwest_groups[] = अणु
	PIN_GROUP("ssp0_grp", bxt_northwest_ssp0_pins, 1),
	PIN_GROUP("ssp1_grp", bxt_northwest_ssp1_pins, 1),
	PIN_GROUP("ssp2_grp", bxt_northwest_ssp2_pins, 1),
	PIN_GROUP("uart3_grp", bxt_northwest_uart3_pins, 2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर bxt_northwest_ssp0_groups[] = अणु "ssp0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_northwest_ssp1_groups[] = अणु "ssp1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_northwest_ssp2_groups[] = अणु "ssp2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_northwest_uart3_groups[] = अणु "uart3_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function bxt_northwest_functions[] = अणु
	FUNCTION("ssp0", bxt_northwest_ssp0_groups),
	FUNCTION("ssp1", bxt_northwest_ssp1_groups),
	FUNCTION("ssp2", bxt_northwest_ssp2_groups),
	FUNCTION("uart3", bxt_northwest_uart3_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community bxt_northwest_communities[] = अणु
	BXT_COMMUNITY(0, 71),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data bxt_northwest_soc_data = अणु
	.uid = "2",
	.pins = bxt_northwest_pins,
	.npins = ARRAY_SIZE(bxt_northwest_pins),
	.groups = bxt_northwest_groups,
	.ngroups = ARRAY_SIZE(bxt_northwest_groups),
	.functions = bxt_northwest_functions,
	.nfunctions = ARRAY_SIZE(bxt_northwest_functions),
	.communities = bxt_northwest_communities,
	.ncommunities = ARRAY_SIZE(bxt_northwest_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc bxt_west_pins[] = अणु
	PINCTRL_PIN(0, "LPSS_I2C0_SDA"),
	PINCTRL_PIN(1, "LPSS_I2C0_SCL"),
	PINCTRL_PIN(2, "LPSS_I2C1_SDA"),
	PINCTRL_PIN(3, "LPSS_I2C1_SCL"),
	PINCTRL_PIN(4, "LPSS_I2C2_SDA"),
	PINCTRL_PIN(5, "LPSS_I2C2_SCL"),
	PINCTRL_PIN(6, "LPSS_I2C3_SDA"),
	PINCTRL_PIN(7, "LPSS_I2C3_SCL"),
	PINCTRL_PIN(8, "LPSS_I2C4_SDA"),
	PINCTRL_PIN(9, "LPSS_I2C4_SCL"),
	PINCTRL_PIN(10, "LPSS_I2C5_SDA"),
	PINCTRL_PIN(11, "LPSS_I2C5_SCL"),
	PINCTRL_PIN(12, "LPSS_I2C6_SDA"),
	PINCTRL_PIN(13, "LPSS_I2C6_SCL"),
	PINCTRL_PIN(14, "LPSS_I2C7_SDA"),
	PINCTRL_PIN(15, "LPSS_I2C7_SCL"),
	PINCTRL_PIN(16, "ISH_I2C0_SDA"),
	PINCTRL_PIN(17, "ISH_I2C0_SCL"),
	PINCTRL_PIN(18, "ISH_I2C1_SDA"),
	PINCTRL_PIN(19, "ISH_I2C1_SCL"),
	PINCTRL_PIN(20, "ISH_I2C2_SDA"),
	PINCTRL_PIN(21, "ISH_I2C2_SCL"),
	PINCTRL_PIN(22, "ISH_GPIO_0"),
	PINCTRL_PIN(23, "ISH_GPIO_1"),
	PINCTRL_PIN(24, "ISH_GPIO_2"),
	PINCTRL_PIN(25, "ISH_GPIO_3"),
	PINCTRL_PIN(26, "ISH_GPIO_4"),
	PINCTRL_PIN(27, "ISH_GPIO_5"),
	PINCTRL_PIN(28, "ISH_GPIO_6"),
	PINCTRL_PIN(29, "ISH_GPIO_7"),
	PINCTRL_PIN(30, "ISH_GPIO_8"),
	PINCTRL_PIN(31, "ISH_GPIO_9"),
	PINCTRL_PIN(32, "MODEM_CLKREQ"),
	PINCTRL_PIN(33, "DGCLKDBG_PMC_0"),
	PINCTRL_PIN(34, "DGCLKDBG_PMC_1"),
	PINCTRL_PIN(35, "DGCLKDBG_PMC_2"),
	PINCTRL_PIN(36, "DGCLKDBG_ICLK_0"),
	PINCTRL_PIN(37, "DGCLKDBG_ICLK_1"),
	PINCTRL_PIN(38, "OSC_CLK_OUT_0"),
	PINCTRL_PIN(39, "OSC_CLK_OUT_1"),
	PINCTRL_PIN(40, "OSC_CLK_OUT_2"),
	PINCTRL_PIN(41, "OSC_CLK_OUT_3"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c0_pins[] = अणु 0, 1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c1_pins[] = अणु 2, 3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c2_pins[] = अणु 4, 5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c3_pins[] = अणु 6, 7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c4_pins[] = अणु 8, 9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c5_pins[] = अणु 10, 11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c6_pins[] = अणु 12, 13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c7_pins[] = अणु 14, 15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c5b_pins[] = अणु 16, 17 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c6b_pins[] = अणु 18, 19 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_west_i2c7b_pins[] = अणु 20, 21 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup bxt_west_groups[] = अणु
	PIN_GROUP("i2c0_grp", bxt_west_i2c0_pins, 1),
	PIN_GROUP("i2c1_grp", bxt_west_i2c1_pins, 1),
	PIN_GROUP("i2c2_grp", bxt_west_i2c2_pins, 1),
	PIN_GROUP("i2c3_grp", bxt_west_i2c3_pins, 1),
	PIN_GROUP("i2c4_grp", bxt_west_i2c4_pins, 1),
	PIN_GROUP("i2c5_grp", bxt_west_i2c5_pins, 1),
	PIN_GROUP("i2c6_grp", bxt_west_i2c6_pins, 1),
	PIN_GROUP("i2c7_grp", bxt_west_i2c7_pins, 1),
	PIN_GROUP("i2c5b_grp", bxt_west_i2c5b_pins, 2),
	PIN_GROUP("i2c6b_grp", bxt_west_i2c6b_pins, 2),
	PIN_GROUP("i2c7b_grp", bxt_west_i2c7b_pins, 2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर bxt_west_i2c0_groups[] = अणु "i2c0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_west_i2c1_groups[] = अणु "i2c1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_west_i2c2_groups[] = अणु "i2c2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_west_i2c3_groups[] = अणु "i2c3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_west_i2c4_groups[] = अणु "i2c4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_west_i2c5_groups[] = अणु "i2c5_grp", "i2c5b_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_west_i2c6_groups[] = अणु "i2c6_grp", "i2c6b_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_west_i2c7_groups[] = अणु "i2c7_grp", "i2c7b_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function bxt_west_functions[] = अणु
	FUNCTION("i2c0", bxt_west_i2c0_groups),
	FUNCTION("i2c1", bxt_west_i2c1_groups),
	FUNCTION("i2c2", bxt_west_i2c2_groups),
	FUNCTION("i2c3", bxt_west_i2c3_groups),
	FUNCTION("i2c4", bxt_west_i2c4_groups),
	FUNCTION("i2c5", bxt_west_i2c5_groups),
	FUNCTION("i2c6", bxt_west_i2c6_groups),
	FUNCTION("i2c7", bxt_west_i2c7_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community bxt_west_communities[] = अणु
	BXT_COMMUNITY(0, 41),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data bxt_west_soc_data = अणु
	.uid = "3",
	.pins = bxt_west_pins,
	.npins = ARRAY_SIZE(bxt_west_pins),
	.groups = bxt_west_groups,
	.ngroups = ARRAY_SIZE(bxt_west_groups),
	.functions = bxt_west_functions,
	.nfunctions = ARRAY_SIZE(bxt_west_functions),
	.communities = bxt_west_communities,
	.ncommunities = ARRAY_SIZE(bxt_west_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc bxt_southwest_pins[] = अणु
	PINCTRL_PIN(0, "EMMC0_CLK"),
	PINCTRL_PIN(1, "EMMC0_D0"),
	PINCTRL_PIN(2, "EMMC0_D1"),
	PINCTRL_PIN(3, "EMMC0_D2"),
	PINCTRL_PIN(4, "EMMC0_D3"),
	PINCTRL_PIN(5, "EMMC0_D4"),
	PINCTRL_PIN(6, "EMMC0_D5"),
	PINCTRL_PIN(7, "EMMC0_D6"),
	PINCTRL_PIN(8, "EMMC0_D7"),
	PINCTRL_PIN(9, "EMMC0_CMD"),
	PINCTRL_PIN(10, "SDIO_CLK"),
	PINCTRL_PIN(11, "SDIO_D0"),
	PINCTRL_PIN(12, "SDIO_D1"),
	PINCTRL_PIN(13, "SDIO_D2"),
	PINCTRL_PIN(14, "SDIO_D3"),
	PINCTRL_PIN(15, "SDIO_CMD"),
	PINCTRL_PIN(16, "SDCARD_CLK"),
	PINCTRL_PIN(17, "SDCARD_D0"),
	PINCTRL_PIN(18, "SDCARD_D1"),
	PINCTRL_PIN(19, "SDCARD_D2"),
	PINCTRL_PIN(20, "SDCARD_D3"),
	PINCTRL_PIN(21, "SDCARD_CD_B"),
	PINCTRL_PIN(22, "SDCARD_CMD"),
	PINCTRL_PIN(23, "SDCARD_LVL_CLK_FB"),
	PINCTRL_PIN(24, "SDCARD_LVL_CMD_DIR"),
	PINCTRL_PIN(25, "SDCARD_LVL_DAT_DIR"),
	PINCTRL_PIN(26, "EMMC0_STROBE"),
	PINCTRL_PIN(27, "SDIO_PWR_DOWN_B"),
	PINCTRL_PIN(28, "SDCARD_PWR_DOWN_B"),
	PINCTRL_PIN(29, "SDCARD_LVL_SEL"),
	PINCTRL_PIN(30, "SDCARD_LVL_WP"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bxt_southwest_emmc0_pins[] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 26,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_southwest_sdio_pins[] = अणु
	10, 11, 12, 13, 14, 15, 27,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक bxt_southwest_sdcard_pins[] = अणु
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 28, 29, 30,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup bxt_southwest_groups[] = अणु
	PIN_GROUP("emmc0_grp", bxt_southwest_emmc0_pins, 1),
	PIN_GROUP("sdio_grp", bxt_southwest_sdio_pins, 1),
	PIN_GROUP("sdcard_grp", bxt_southwest_sdcard_pins, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर bxt_southwest_emmc0_groups[] = अणु "emmc0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_southwest_sdio_groups[] = अणु "sdio_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर bxt_southwest_sdcard_groups[] = अणु "sdcard_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function bxt_southwest_functions[] = अणु
	FUNCTION("emmc0", bxt_southwest_emmc0_groups),
	FUNCTION("sdio", bxt_southwest_sdio_groups),
	FUNCTION("sdcard", bxt_southwest_sdcard_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community bxt_southwest_communities[] = अणु
	BXT_COMMUNITY(0, 30),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data bxt_southwest_soc_data = अणु
	.uid = "4",
	.pins = bxt_southwest_pins,
	.npins = ARRAY_SIZE(bxt_southwest_pins),
	.groups = bxt_southwest_groups,
	.ngroups = ARRAY_SIZE(bxt_southwest_groups),
	.functions = bxt_southwest_functions,
	.nfunctions = ARRAY_SIZE(bxt_southwest_functions),
	.communities = bxt_southwest_communities,
	.ncommunities = ARRAY_SIZE(bxt_southwest_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc bxt_south_pins[] = अणु
	PINCTRL_PIN(0, "HV_DDI0_DDC_SDA"),
	PINCTRL_PIN(1, "HV_DDI0_DDC_SCL"),
	PINCTRL_PIN(2, "HV_DDI1_DDC_SDA"),
	PINCTRL_PIN(3, "HV_DDI1_DDC_SCL"),
	PINCTRL_PIN(4, "DBI_SDA"),
	PINCTRL_PIN(5, "DBI_SCL"),
	PINCTRL_PIN(6, "PANEL0_VDDEN"),
	PINCTRL_PIN(7, "PANEL0_BKLTEN"),
	PINCTRL_PIN(8, "PANEL0_BKLTCTL"),
	PINCTRL_PIN(9, "PANEL1_VDDEN"),
	PINCTRL_PIN(10, "PANEL1_BKLTEN"),
	PINCTRL_PIN(11, "PANEL1_BKLTCTL"),
	PINCTRL_PIN(12, "DBI_CSX"),
	PINCTRL_PIN(13, "DBI_RESX"),
	PINCTRL_PIN(14, "GP_INTD_DSI_TE1"),
	PINCTRL_PIN(15, "GP_INTD_DSI_TE2"),
	PINCTRL_PIN(16, "USB_OC0_B"),
	PINCTRL_PIN(17, "USB_OC1_B"),
	PINCTRL_PIN(18, "MEX_WAKE0_B"),
	PINCTRL_PIN(19, "MEX_WAKE1_B"),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community bxt_south_communities[] = अणु
	BXT_COMMUNITY(0, 19),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data bxt_south_soc_data = अणु
	.uid = "5",
	.pins = bxt_south_pins,
	.npins = ARRAY_SIZE(bxt_south_pins),
	.communities = bxt_south_communities,
	.ncommunities = ARRAY_SIZE(bxt_south_communities),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *bxt_pinctrl_soc_data[] = अणु
	&bxt_north_soc_data,
	&bxt_northwest_soc_data,
	&bxt_west_soc_data,
	&bxt_southwest_soc_data,
	&bxt_south_soc_data,
	शून्य
पूर्ण;

/* APL */
अटल स्थिर काष्ठा pinctrl_pin_desc apl_north_pins[] = अणु
	PINCTRL_PIN(0, "GPIO_0"),
	PINCTRL_PIN(1, "GPIO_1"),
	PINCTRL_PIN(2, "GPIO_2"),
	PINCTRL_PIN(3, "GPIO_3"),
	PINCTRL_PIN(4, "GPIO_4"),
	PINCTRL_PIN(5, "GPIO_5"),
	PINCTRL_PIN(6, "GPIO_6"),
	PINCTRL_PIN(7, "GPIO_7"),
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
	PINCTRL_PIN(26, "GPIO_26"),
	PINCTRL_PIN(27, "GPIO_27"),
	PINCTRL_PIN(28, "GPIO_28"),
	PINCTRL_PIN(29, "GPIO_29"),
	PINCTRL_PIN(30, "GPIO_30"),
	PINCTRL_PIN(31, "GPIO_31"),
	PINCTRL_PIN(32, "GPIO_32"),
	PINCTRL_PIN(33, "GPIO_33"),
	PINCTRL_PIN(34, "PWM0"),
	PINCTRL_PIN(35, "PWM1"),
	PINCTRL_PIN(36, "PWM2"),
	PINCTRL_PIN(37, "PWM3"),
	PINCTRL_PIN(38, "LPSS_UART0_RXD"),
	PINCTRL_PIN(39, "LPSS_UART0_TXD"),
	PINCTRL_PIN(40, "LPSS_UART0_RTS_B"),
	PINCTRL_PIN(41, "LPSS_UART0_CTS_B"),
	PINCTRL_PIN(42, "LPSS_UART1_RXD"),
	PINCTRL_PIN(43, "LPSS_UART1_TXD"),
	PINCTRL_PIN(44, "LPSS_UART1_RTS_B"),
	PINCTRL_PIN(45, "LPSS_UART1_CTS_B"),
	PINCTRL_PIN(46, "LPSS_UART2_RXD"),
	PINCTRL_PIN(47, "LPSS_UART2_TXD"),
	PINCTRL_PIN(48, "LPSS_UART2_RTS_B"),
	PINCTRL_PIN(49, "LPSS_UART2_CTS_B"),
	PINCTRL_PIN(50, "GP_CAMERASB00"),
	PINCTRL_PIN(51, "GP_CAMERASB01"),
	PINCTRL_PIN(52, "GP_CAMERASB02"),
	PINCTRL_PIN(53, "GP_CAMERASB03"),
	PINCTRL_PIN(54, "GP_CAMERASB04"),
	PINCTRL_PIN(55, "GP_CAMERASB05"),
	PINCTRL_PIN(56, "GP_CAMERASB06"),
	PINCTRL_PIN(57, "GP_CAMERASB07"),
	PINCTRL_PIN(58, "GP_CAMERASB08"),
	PINCTRL_PIN(59, "GP_CAMERASB09"),
	PINCTRL_PIN(60, "GP_CAMERASB10"),
	PINCTRL_PIN(61, "GP_CAMERASB11"),
	PINCTRL_PIN(62, "TCK"),
	PINCTRL_PIN(63, "TRST_B"),
	PINCTRL_PIN(64, "TMS"),
	PINCTRL_PIN(65, "TDI"),
	PINCTRL_PIN(66, "CX_PMODE"),
	PINCTRL_PIN(67, "CX_PREQ_B"),
	PINCTRL_PIN(68, "JTAGX"),
	PINCTRL_PIN(69, "CX_PRDY_B"),
	PINCTRL_PIN(70, "TDO"),
	PINCTRL_PIN(71, "CNV_BRI_DT"),
	PINCTRL_PIN(72, "CNV_BRI_RSP"),
	PINCTRL_PIN(73, "CNV_RGI_DT"),
	PINCTRL_PIN(74, "CNV_RGI_RSP"),
	PINCTRL_PIN(75, "SVID0_ALERT_B"),
	PINCTRL_PIN(76, "SVID0_DATA"),
	PINCTRL_PIN(77, "SVID0_CLK"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक apl_north_pwm0_pins[] = अणु 34 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_north_pwm1_pins[] = अणु 35 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_north_pwm2_pins[] = अणु 36 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_north_pwm3_pins[] = अणु 37 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_north_uart0_pins[] = अणु 38, 39, 40, 41 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_north_uart1_pins[] = अणु 42, 43, 44, 45 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_north_uart2_pins[] = अणु 46, 47, 48, 49 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup apl_north_groups[] = अणु
	PIN_GROUP("pwm0_grp", apl_north_pwm0_pins, 1),
	PIN_GROUP("pwm1_grp", apl_north_pwm1_pins, 1),
	PIN_GROUP("pwm2_grp", apl_north_pwm2_pins, 1),
	PIN_GROUP("pwm3_grp", apl_north_pwm3_pins, 1),
	PIN_GROUP("uart0_grp", apl_north_uart0_pins, 1),
	PIN_GROUP("uart1_grp", apl_north_uart1_pins, 1),
	PIN_GROUP("uart2_grp", apl_north_uart2_pins, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर apl_north_pwm0_groups[] = अणु "pwm0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_north_pwm1_groups[] = अणु "pwm1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_north_pwm2_groups[] = अणु "pwm2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_north_pwm3_groups[] = अणु "pwm3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_north_uart0_groups[] = अणु "uart0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_north_uart1_groups[] = अणु "uart1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_north_uart2_groups[] = अणु "uart2_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function apl_north_functions[] = अणु
	FUNCTION("pwm0", apl_north_pwm0_groups),
	FUNCTION("pwm1", apl_north_pwm1_groups),
	FUNCTION("pwm2", apl_north_pwm2_groups),
	FUNCTION("pwm3", apl_north_pwm3_groups),
	FUNCTION("uart0", apl_north_uart0_groups),
	FUNCTION("uart1", apl_north_uart1_groups),
	FUNCTION("uart2", apl_north_uart2_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community apl_north_communities[] = अणु
	BXT_COMMUNITY(0, 77),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data apl_north_soc_data = अणु
	.uid = "1",
	.pins = apl_north_pins,
	.npins = ARRAY_SIZE(apl_north_pins),
	.groups = apl_north_groups,
	.ngroups = ARRAY_SIZE(apl_north_groups),
	.functions = apl_north_functions,
	.nfunctions = ARRAY_SIZE(apl_north_functions),
	.communities = apl_north_communities,
	.ncommunities = ARRAY_SIZE(apl_north_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc apl_northwest_pins[] = अणु
	PINCTRL_PIN(0, "HV_DDI0_DDC_SDA"),
	PINCTRL_PIN(1, "HV_DDI0_DDC_SCL"),
	PINCTRL_PIN(2, "HV_DDI1_DDC_SDA"),
	PINCTRL_PIN(3, "HV_DDI1_DDC_SCL"),
	PINCTRL_PIN(4, "DBI_SDA"),
	PINCTRL_PIN(5, "DBI_SCL"),
	PINCTRL_PIN(6, "PANEL0_VDDEN"),
	PINCTRL_PIN(7, "PANEL0_BKLTEN"),
	PINCTRL_PIN(8, "PANEL0_BKLTCTL"),
	PINCTRL_PIN(9, "PANEL1_VDDEN"),
	PINCTRL_PIN(10, "PANEL1_BKLTEN"),
	PINCTRL_PIN(11, "PANEL1_BKLTCTL"),
	PINCTRL_PIN(12, "DBI_CSX"),
	PINCTRL_PIN(13, "DBI_RESX"),
	PINCTRL_PIN(14, "GP_INTD_DSI_TE1"),
	PINCTRL_PIN(15, "GP_INTD_DSI_TE2"),
	PINCTRL_PIN(16, "USB_OC0_B"),
	PINCTRL_PIN(17, "USB_OC1_B"),
	PINCTRL_PIN(18, "PMC_SPI_FS0"),
	PINCTRL_PIN(19, "PMC_SPI_FS1"),
	PINCTRL_PIN(20, "PMC_SPI_FS2"),
	PINCTRL_PIN(21, "PMC_SPI_RXD"),
	PINCTRL_PIN(22, "PMC_SPI_TXD"),
	PINCTRL_PIN(23, "PMC_SPI_CLK"),
	PINCTRL_PIN(24, "PMIC_PWRGOOD"),
	PINCTRL_PIN(25, "PMIC_RESET_B"),
	PINCTRL_PIN(26, "PMIC_SDWN_B"),
	PINCTRL_PIN(27, "PMIC_BCUDISW2"),
	PINCTRL_PIN(28, "PMIC_BCUDISCRIT"),
	PINCTRL_PIN(29, "PMIC_THERMTRIP_B"),
	PINCTRL_PIN(30, "PMIC_STDBY"),
	PINCTRL_PIN(31, "PROCHOT_B"),
	PINCTRL_PIN(32, "PMIC_I2C_SCL"),
	PINCTRL_PIN(33, "PMIC_I2C_SDA"),
	PINCTRL_PIN(34, "AVS_I2S1_MCLK"),
	PINCTRL_PIN(35, "AVS_I2S1_BCLK"),
	PINCTRL_PIN(36, "AVS_I2S1_WS_SYNC"),
	PINCTRL_PIN(37, "AVS_I2S1_SDI"),
	PINCTRL_PIN(38, "AVS_I2S1_SDO"),
	PINCTRL_PIN(39, "AVS_M_CLK_A1"),
	PINCTRL_PIN(40, "AVS_M_CLK_B1"),
	PINCTRL_PIN(41, "AVS_M_DATA_1"),
	PINCTRL_PIN(42, "AVS_M_CLK_AB2"),
	PINCTRL_PIN(43, "AVS_M_DATA_2"),
	PINCTRL_PIN(44, "AVS_I2S2_MCLK"),
	PINCTRL_PIN(45, "AVS_I2S2_BCLK"),
	PINCTRL_PIN(46, "AVS_I2S2_WS_SYNC"),
	PINCTRL_PIN(47, "AVS_I2S2_SDI"),
	PINCTRL_PIN(48, "AVS_I2S2_SDO"),
	PINCTRL_PIN(49, "AVS_I2S3_BCLK"),
	PINCTRL_PIN(50, "AVS_I2S3_WS_SYNC"),
	PINCTRL_PIN(51, "AVS_I2S3_SDI"),
	PINCTRL_PIN(52, "AVS_I2S3_SDO"),
	PINCTRL_PIN(53, "FST_SPI_CS0_B"),
	PINCTRL_PIN(54, "FST_SPI_CS1_B"),
	PINCTRL_PIN(55, "FST_SPI_MOSI_IO0"),
	PINCTRL_PIN(56, "FST_SPI_MISO_IO1"),
	PINCTRL_PIN(57, "FST_SPI_IO2"),
	PINCTRL_PIN(58, "FST_SPI_IO3"),
	PINCTRL_PIN(59, "FST_SPI_CLK"),
	PINCTRL_PIN(60, "FST_SPI_CLK_FB"),
	PINCTRL_PIN(61, "GP_SSP_0_CLK"),
	PINCTRL_PIN(62, "GP_SSP_0_FS0"),
	PINCTRL_PIN(63, "GP_SSP_0_FS1"),
	PINCTRL_PIN(64, "GP_SSP_0_RXD"),
	PINCTRL_PIN(65, "GP_SSP_0_TXD"),
	PINCTRL_PIN(66, "GP_SSP_1_CLK"),
	PINCTRL_PIN(67, "GP_SSP_1_FS0"),
	PINCTRL_PIN(68, "GP_SSP_1_FS1"),
	PINCTRL_PIN(69, "GP_SSP_1_RXD"),
	PINCTRL_PIN(70, "GP_SSP_1_TXD"),
	PINCTRL_PIN(71, "GP_SSP_2_CLK"),
	PINCTRL_PIN(72, "GP_SSP_2_FS0"),
	PINCTRL_PIN(73, "GP_SSP_2_FS1"),
	PINCTRL_PIN(74, "GP_SSP_2_FS2"),
	PINCTRL_PIN(75, "GP_SSP_2_RXD"),
	PINCTRL_PIN(76, "GP_SSP_2_TXD"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक apl_northwest_ssp0_pins[] = अणु 61, 62, 63, 64, 65 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_northwest_ssp1_pins[] = अणु 66, 67, 68, 69, 70 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_northwest_ssp2_pins[] = अणु 71, 72, 73, 74, 75, 76 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_northwest_uart3_pins[] = अणु 67, 68, 69, 70 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup apl_northwest_groups[] = अणु
	PIN_GROUP("ssp0_grp", apl_northwest_ssp0_pins, 1),
	PIN_GROUP("ssp1_grp", apl_northwest_ssp1_pins, 1),
	PIN_GROUP("ssp2_grp", apl_northwest_ssp2_pins, 1),
	PIN_GROUP("uart3_grp", apl_northwest_uart3_pins, 2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर apl_northwest_ssp0_groups[] = अणु "ssp0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_northwest_ssp1_groups[] = अणु "ssp1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_northwest_ssp2_groups[] = अणु "ssp2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_northwest_uart3_groups[] = अणु "uart3_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function apl_northwest_functions[] = अणु
	FUNCTION("ssp0", apl_northwest_ssp0_groups),
	FUNCTION("ssp1", apl_northwest_ssp1_groups),
	FUNCTION("ssp2", apl_northwest_ssp2_groups),
	FUNCTION("uart3", apl_northwest_uart3_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community apl_northwest_communities[] = अणु
	BXT_COMMUNITY(0, 76),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data apl_northwest_soc_data = अणु
	.uid = "2",
	.pins = apl_northwest_pins,
	.npins = ARRAY_SIZE(apl_northwest_pins),
	.groups = apl_northwest_groups,
	.ngroups = ARRAY_SIZE(apl_northwest_groups),
	.functions = apl_northwest_functions,
	.nfunctions = ARRAY_SIZE(apl_northwest_functions),
	.communities = apl_northwest_communities,
	.ncommunities = ARRAY_SIZE(apl_northwest_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc apl_west_pins[] = अणु
	PINCTRL_PIN(0, "LPSS_I2C0_SDA"),
	PINCTRL_PIN(1, "LPSS_I2C0_SCL"),
	PINCTRL_PIN(2, "LPSS_I2C1_SDA"),
	PINCTRL_PIN(3, "LPSS_I2C1_SCL"),
	PINCTRL_PIN(4, "LPSS_I2C2_SDA"),
	PINCTRL_PIN(5, "LPSS_I2C2_SCL"),
	PINCTRL_PIN(6, "LPSS_I2C3_SDA"),
	PINCTRL_PIN(7, "LPSS_I2C3_SCL"),
	PINCTRL_PIN(8, "LPSS_I2C4_SDA"),
	PINCTRL_PIN(9, "LPSS_I2C4_SCL"),
	PINCTRL_PIN(10, "LPSS_I2C5_SDA"),
	PINCTRL_PIN(11, "LPSS_I2C5_SCL"),
	PINCTRL_PIN(12, "LPSS_I2C6_SDA"),
	PINCTRL_PIN(13, "LPSS_I2C6_SCL"),
	PINCTRL_PIN(14, "LPSS_I2C7_SDA"),
	PINCTRL_PIN(15, "LPSS_I2C7_SCL"),
	PINCTRL_PIN(16, "ISH_GPIO_0"),
	PINCTRL_PIN(17, "ISH_GPIO_1"),
	PINCTRL_PIN(18, "ISH_GPIO_2"),
	PINCTRL_PIN(19, "ISH_GPIO_3"),
	PINCTRL_PIN(20, "ISH_GPIO_4"),
	PINCTRL_PIN(21, "ISH_GPIO_5"),
	PINCTRL_PIN(22, "ISH_GPIO_6"),
	PINCTRL_PIN(23, "ISH_GPIO_7"),
	PINCTRL_PIN(24, "ISH_GPIO_8"),
	PINCTRL_PIN(25, "ISH_GPIO_9"),
	PINCTRL_PIN(26, "PCIE_CLKREQ0_B"),
	PINCTRL_PIN(27, "PCIE_CLKREQ1_B"),
	PINCTRL_PIN(28, "PCIE_CLKREQ2_B"),
	PINCTRL_PIN(29, "PCIE_CLKREQ3_B"),
	PINCTRL_PIN(30, "OSC_CLK_OUT_0"),
	PINCTRL_PIN(31, "OSC_CLK_OUT_1"),
	PINCTRL_PIN(32, "OSC_CLK_OUT_2"),
	PINCTRL_PIN(33, "OSC_CLK_OUT_3"),
	PINCTRL_PIN(34, "OSC_CLK_OUT_4"),
	PINCTRL_PIN(35, "PMU_AC_PRESENT"),
	PINCTRL_PIN(36, "PMU_BATLOW_B"),
	PINCTRL_PIN(37, "PMU_PLTRST_B"),
	PINCTRL_PIN(38, "PMU_PWRBTN_B"),
	PINCTRL_PIN(39, "PMU_RESETBUTTON_B"),
	PINCTRL_PIN(40, "PMU_SLP_S0_B"),
	PINCTRL_PIN(41, "PMU_SLP_S3_B"),
	PINCTRL_PIN(42, "PMU_SLP_S4_B"),
	PINCTRL_PIN(43, "PMU_SUSCLK"),
	PINCTRL_PIN(44, "PMU_WAKE_B"),
	PINCTRL_PIN(45, "SUS_STAT_B"),
	PINCTRL_PIN(46, "SUSPWRDNACK"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक apl_west_i2c0_pins[] = अणु 0, 1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_west_i2c1_pins[] = अणु 2, 3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_west_i2c2_pins[] = अणु 4, 5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_west_i2c3_pins[] = अणु 6, 7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_west_i2c4_pins[] = अणु 8, 9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_west_i2c5_pins[] = अणु 10, 11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_west_i2c6_pins[] = अणु 12, 13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_west_i2c7_pins[] = अणु 14, 15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_west_uart2_pins[] = अणु 20, 21, 22, 34 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup apl_west_groups[] = अणु
	PIN_GROUP("i2c0_grp", apl_west_i2c0_pins, 1),
	PIN_GROUP("i2c1_grp", apl_west_i2c1_pins, 1),
	PIN_GROUP("i2c2_grp", apl_west_i2c2_pins, 1),
	PIN_GROUP("i2c3_grp", apl_west_i2c3_pins, 1),
	PIN_GROUP("i2c4_grp", apl_west_i2c4_pins, 1),
	PIN_GROUP("i2c5_grp", apl_west_i2c5_pins, 1),
	PIN_GROUP("i2c6_grp", apl_west_i2c6_pins, 1),
	PIN_GROUP("i2c7_grp", apl_west_i2c7_pins, 1),
	PIN_GROUP("uart2_grp", apl_west_uart2_pins, 3),
पूर्ण;

अटल स्थिर अक्षर * स्थिर apl_west_i2c0_groups[] = अणु "i2c0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_west_i2c1_groups[] = अणु "i2c1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_west_i2c2_groups[] = अणु "i2c2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_west_i2c3_groups[] = अणु "i2c3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_west_i2c4_groups[] = अणु "i2c4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_west_i2c5_groups[] = अणु "i2c5_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_west_i2c6_groups[] = अणु "i2c6_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_west_i2c7_groups[] = अणु "i2c7_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_west_uart2_groups[] = अणु "uart2_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function apl_west_functions[] = अणु
	FUNCTION("i2c0", apl_west_i2c0_groups),
	FUNCTION("i2c1", apl_west_i2c1_groups),
	FUNCTION("i2c2", apl_west_i2c2_groups),
	FUNCTION("i2c3", apl_west_i2c3_groups),
	FUNCTION("i2c4", apl_west_i2c4_groups),
	FUNCTION("i2c5", apl_west_i2c5_groups),
	FUNCTION("i2c6", apl_west_i2c6_groups),
	FUNCTION("i2c7", apl_west_i2c7_groups),
	FUNCTION("uart2", apl_west_uart2_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community apl_west_communities[] = अणु
	BXT_COMMUNITY(0, 46),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data apl_west_soc_data = अणु
	.uid = "3",
	.pins = apl_west_pins,
	.npins = ARRAY_SIZE(apl_west_pins),
	.groups = apl_west_groups,
	.ngroups = ARRAY_SIZE(apl_west_groups),
	.functions = apl_west_functions,
	.nfunctions = ARRAY_SIZE(apl_west_functions),
	.communities = apl_west_communities,
	.ncommunities = ARRAY_SIZE(apl_west_communities),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc apl_southwest_pins[] = अणु
	PINCTRL_PIN(0, "PCIE_WAKE0_B"),
	PINCTRL_PIN(1, "PCIE_WAKE1_B"),
	PINCTRL_PIN(2, "PCIE_WAKE2_B"),
	PINCTRL_PIN(3, "PCIE_WAKE3_B"),
	PINCTRL_PIN(4, "EMMC0_CLK"),
	PINCTRL_PIN(5, "EMMC0_D0"),
	PINCTRL_PIN(6, "EMMC0_D1"),
	PINCTRL_PIN(7, "EMMC0_D2"),
	PINCTRL_PIN(8, "EMMC0_D3"),
	PINCTRL_PIN(9, "EMMC0_D4"),
	PINCTRL_PIN(10, "EMMC0_D5"),
	PINCTRL_PIN(11, "EMMC0_D6"),
	PINCTRL_PIN(12, "EMMC0_D7"),
	PINCTRL_PIN(13, "EMMC0_CMD"),
	PINCTRL_PIN(14, "SDIO_CLK"),
	PINCTRL_PIN(15, "SDIO_D0"),
	PINCTRL_PIN(16, "SDIO_D1"),
	PINCTRL_PIN(17, "SDIO_D2"),
	PINCTRL_PIN(18, "SDIO_D3"),
	PINCTRL_PIN(19, "SDIO_CMD"),
	PINCTRL_PIN(20, "SDCARD_CLK"),
	PINCTRL_PIN(21, "SDCARD_CLK_FB"),
	PINCTRL_PIN(22, "SDCARD_D0"),
	PINCTRL_PIN(23, "SDCARD_D1"),
	PINCTRL_PIN(24, "SDCARD_D2"),
	PINCTRL_PIN(25, "SDCARD_D3"),
	PINCTRL_PIN(26, "SDCARD_CD_B"),
	PINCTRL_PIN(27, "SDCARD_CMD"),
	PINCTRL_PIN(28, "SDCARD_LVL_WP"),
	PINCTRL_PIN(29, "EMMC0_STROBE"),
	PINCTRL_PIN(30, "SDIO_PWR_DOWN_B"),
	PINCTRL_PIN(31, "SMB_ALERTB"),
	PINCTRL_PIN(32, "SMB_CLK"),
	PINCTRL_PIN(33, "SMB_DATA"),
	PINCTRL_PIN(34, "LPC_ILB_SERIRQ"),
	PINCTRL_PIN(35, "LPC_CLKOUT0"),
	PINCTRL_PIN(36, "LPC_CLKOUT1"),
	PINCTRL_PIN(37, "LPC_AD0"),
	PINCTRL_PIN(38, "LPC_AD1"),
	PINCTRL_PIN(39, "LPC_AD2"),
	PINCTRL_PIN(40, "LPC_AD3"),
	PINCTRL_PIN(41, "LPC_CLKRUNB"),
	PINCTRL_PIN(42, "LPC_FRAMEB"),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक apl_southwest_emmc0_pins[] = अणु
	4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 29,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_southwest_sdio_pins[] = अणु
	14, 15, 16, 17, 18, 19, 30,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_southwest_sdcard_pins[] = अणु
	20, 21, 22, 23, 24, 25, 26, 27, 28,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक apl_southwest_i2c7_pins[] = अणु 32, 33 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup apl_southwest_groups[] = अणु
	PIN_GROUP("emmc0_grp", apl_southwest_emmc0_pins, 1),
	PIN_GROUP("sdio_grp", apl_southwest_sdio_pins, 1),
	PIN_GROUP("sdcard_grp", apl_southwest_sdcard_pins, 1),
	PIN_GROUP("i2c7_grp", apl_southwest_i2c7_pins, 2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर apl_southwest_emmc0_groups[] = अणु "emmc0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_southwest_sdio_groups[] = अणु "sdio_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_southwest_sdcard_groups[] = अणु "sdcard_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर apl_southwest_i2c7_groups[] = अणु "i2c7_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function apl_southwest_functions[] = अणु
	FUNCTION("emmc0", apl_southwest_emmc0_groups),
	FUNCTION("sdio", apl_southwest_sdio_groups),
	FUNCTION("sdcard", apl_southwest_sdcard_groups),
	FUNCTION("i2c7", apl_southwest_i2c7_groups),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community apl_southwest_communities[] = अणु
	BXT_COMMUNITY(0, 42),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data apl_southwest_soc_data = अणु
	.uid = "4",
	.pins = apl_southwest_pins,
	.npins = ARRAY_SIZE(apl_southwest_pins),
	.groups = apl_southwest_groups,
	.ngroups = ARRAY_SIZE(apl_southwest_groups),
	.functions = apl_southwest_functions,
	.nfunctions = ARRAY_SIZE(apl_southwest_functions),
	.communities = apl_southwest_communities,
	.ncommunities = ARRAY_SIZE(apl_southwest_communities),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *apl_pinctrl_soc_data[] = अणु
	&apl_north_soc_data,
	&apl_northwest_soc_data,
	&apl_west_soc_data,
	&apl_southwest_soc_data,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id bxt_pinctrl_acpi_match[] = अणु
	अणु "INT3452", (kernel_uदीर्घ_t)apl_pinctrl_soc_data पूर्ण,
	अणु "INT34D1", (kernel_uदीर्घ_t)bxt_pinctrl_soc_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bxt_pinctrl_acpi_match);

अटल स्थिर काष्ठा platक्रमm_device_id bxt_pinctrl_platक्रमm_ids[] = अणु
	अणु "apollolake-pinctrl", (kernel_uदीर्घ_t)apl_pinctrl_soc_data पूर्ण,
	अणु "broxton-pinctrl", (kernel_uदीर्घ_t)bxt_pinctrl_soc_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल INTEL_PINCTRL_PM_OPS(bxt_pinctrl_pm_ops);

अटल काष्ठा platक्रमm_driver bxt_pinctrl_driver = अणु
	.probe = पूर्णांकel_pinctrl_probe_by_uid,
	.driver = अणु
		.name = "broxton-pinctrl",
		.acpi_match_table = bxt_pinctrl_acpi_match,
		.pm = &bxt_pinctrl_pm_ops,
	पूर्ण,
	.id_table = bxt_pinctrl_platक्रमm_ids,
पूर्ण;

अटल पूर्णांक __init bxt_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&bxt_pinctrl_driver);
पूर्ण
subsys_initcall(bxt_pinctrl_init);

अटल व्योम __निकास bxt_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&bxt_pinctrl_driver);
पूर्ण
module_निकास(bxt_pinctrl_निकास);

MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("Intel Broxton SoC pinctrl/GPIO driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:broxton-pinctrl");
