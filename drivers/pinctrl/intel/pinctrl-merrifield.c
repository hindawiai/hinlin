<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Merrअगरield SoC pinctrl driver
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>

#समावेश "pinctrl-intel.h"

#घोषणा MRFLD_FAMILY_NR			64
#घोषणा MRFLD_FAMILY_LEN		0x400

#घोषणा SLEW_OFFSET			0x000
#घोषणा BUFCFG_OFFSET			0x100
#घोषणा MISC_OFFSET			0x300

#घोषणा BUFCFG_PINMODE_SHIFT		0
#घोषणा BUFCFG_PINMODE_MASK		GENMASK(2, 0)
#घोषणा BUFCFG_PINMODE_GPIO		0
#घोषणा BUFCFG_PUPD_VAL_SHIFT		4
#घोषणा BUFCFG_PUPD_VAL_MASK		GENMASK(5, 4)
#घोषणा BUFCFG_PUPD_VAL_2K		0
#घोषणा BUFCFG_PUPD_VAL_20K		1
#घोषणा BUFCFG_PUPD_VAL_50K		2
#घोषणा BUFCFG_PUPD_VAL_910		3
#घोषणा BUFCFG_PU_EN			BIT(8)
#घोषणा BUFCFG_PD_EN			BIT(9)
#घोषणा BUFCFG_Px_EN_MASK		GENMASK(9, 8)
#घोषणा BUFCFG_SLEWSEL			BIT(10)
#घोषणा BUFCFG_OVINEN			BIT(12)
#घोषणा BUFCFG_OVINEN_EN		BIT(13)
#घोषणा BUFCFG_OVINEN_MASK		GENMASK(13, 12)
#घोषणा BUFCFG_OVOUTEN			BIT(14)
#घोषणा BUFCFG_OVOUTEN_EN		BIT(15)
#घोषणा BUFCFG_OVOUTEN_MASK		GENMASK(15, 14)
#घोषणा BUFCFG_INDATAOV_VAL		BIT(16)
#घोषणा BUFCFG_INDATAOV_EN		BIT(17)
#घोषणा BUFCFG_INDATAOV_MASK		GENMASK(17, 16)
#घोषणा BUFCFG_OUTDATAOV_VAL		BIT(18)
#घोषणा BUFCFG_OUTDATAOV_EN		BIT(19)
#घोषणा BUFCFG_OUTDATAOV_MASK		GENMASK(19, 18)
#घोषणा BUFCFG_OD_EN			BIT(21)

/**
 * काष्ठा mrfld_family - Intel pin family description
 * @barno: MMIO BAR number where रेजिस्टरs क्रम this family reside
 * @pin_base: Starting pin of pins in this family
 * @npins: Number of pins in this family
 * @रक्षित: True अगर family is रक्षित by access
 * @regs: family specअगरic common रेजिस्टरs
 */
काष्ठा mrfld_family अणु
	अचिन्हित पूर्णांक barno;
	अचिन्हित पूर्णांक pin_base;
	माप_प्रकार npins;
	bool रक्षित;
	व्योम __iomem *regs;
पूर्ण;

#घोषणा MRFLD_FAMILY(b, s, e)				\
	अणु						\
		.barno = (b),				\
		.pin_base = (s),			\
		.npins = (e) - (s) + 1,			\
	पूर्ण

#घोषणा MRFLD_FAMILY_PROTECTED(b, s, e)			\
	अणु						\
		.barno = (b),				\
		.pin_base = (s),			\
		.npins = (e) - (s) + 1,			\
		.रक्षित = true,			\
	पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc mrfld_pins[] = अणु
	/* Family 0: OCP2SSC (0 pins) */
	/* Family 1: ULPI (13 pins) */
	PINCTRL_PIN(0, "ULPI_CLK"),
	PINCTRL_PIN(1, "ULPI_D0"),
	PINCTRL_PIN(2, "ULPI_D1"),
	PINCTRL_PIN(3, "ULPI_D2"),
	PINCTRL_PIN(4, "ULPI_D3"),
	PINCTRL_PIN(5, "ULPI_D4"),
	PINCTRL_PIN(6, "ULPI_D5"),
	PINCTRL_PIN(7, "ULPI_D6"),
	PINCTRL_PIN(8, "ULPI_D7"),
	PINCTRL_PIN(9, "ULPI_DIR"),
	PINCTRL_PIN(10, "ULPI_NXT"),
	PINCTRL_PIN(11, "ULPI_REFCLK"),
	PINCTRL_PIN(12, "ULPI_STP"),
	/* Family 2: eMMC (24 pins) */
	PINCTRL_PIN(13, "EMMC_CLK"),
	PINCTRL_PIN(14, "EMMC_CMD"),
	PINCTRL_PIN(15, "EMMC_D0"),
	PINCTRL_PIN(16, "EMMC_D1"),
	PINCTRL_PIN(17, "EMMC_D2"),
	PINCTRL_PIN(18, "EMMC_D3"),
	PINCTRL_PIN(19, "EMMC_D4"),
	PINCTRL_PIN(20, "EMMC_D5"),
	PINCTRL_PIN(21, "EMMC_D6"),
	PINCTRL_PIN(22, "EMMC_D7"),
	PINCTRL_PIN(23, "EMMC_RST_N"),
	PINCTRL_PIN(24, "GP154"),
	PINCTRL_PIN(25, "GP155"),
	PINCTRL_PIN(26, "GP156"),
	PINCTRL_PIN(27, "GP157"),
	PINCTRL_PIN(28, "GP158"),
	PINCTRL_PIN(29, "GP159"),
	PINCTRL_PIN(30, "GP160"),
	PINCTRL_PIN(31, "GP161"),
	PINCTRL_PIN(32, "GP162"),
	PINCTRL_PIN(33, "GP163"),
	PINCTRL_PIN(34, "GP97"),
	PINCTRL_PIN(35, "GP14"),
	PINCTRL_PIN(36, "GP15"),
	/* Family 3: SDIO (20 pins) */
	PINCTRL_PIN(37, "GP77_SD_CD"),
	PINCTRL_PIN(38, "GP78_SD_CLK"),
	PINCTRL_PIN(39, "GP79_SD_CMD"),
	PINCTRL_PIN(40, "GP80_SD_D0"),
	PINCTRL_PIN(41, "GP81_SD_D1"),
	PINCTRL_PIN(42, "GP82_SD_D2"),
	PINCTRL_PIN(43, "GP83_SD_D3"),
	PINCTRL_PIN(44, "GP84_SD_LS_CLK_FB"),
	PINCTRL_PIN(45, "GP85_SD_LS_CMD_DIR"),
	PINCTRL_PIN(46, "GP86_SD_LS_D_DIR"),
	PINCTRL_PIN(47, "GP88_SD_LS_SEL"),
	PINCTRL_PIN(48, "GP87_SD_PD"),
	PINCTRL_PIN(49, "GP89_SD_WP"),
	PINCTRL_PIN(50, "GP90_SDIO_CLK"),
	PINCTRL_PIN(51, "GP91_SDIO_CMD"),
	PINCTRL_PIN(52, "GP92_SDIO_D0"),
	PINCTRL_PIN(53, "GP93_SDIO_D1"),
	PINCTRL_PIN(54, "GP94_SDIO_D2"),
	PINCTRL_PIN(55, "GP95_SDIO_D3"),
	PINCTRL_PIN(56, "GP96_SDIO_PD"),
	/* Family 4: HSI (8 pins) */
	PINCTRL_PIN(57, "HSI_ACDATA"),
	PINCTRL_PIN(58, "HSI_ACFLAG"),
	PINCTRL_PIN(59, "HSI_ACREADY"),
	PINCTRL_PIN(60, "HSI_ACWAKE"),
	PINCTRL_PIN(61, "HSI_CADATA"),
	PINCTRL_PIN(62, "HSI_CAFLAG"),
	PINCTRL_PIN(63, "HSI_CAREADY"),
	PINCTRL_PIN(64, "HSI_CAWAKE"),
	/* Family 5: SSP Audio (14 pins) */
	PINCTRL_PIN(65, "GP70"),
	PINCTRL_PIN(66, "GP71"),
	PINCTRL_PIN(67, "GP32_I2S_0_CLK"),
	PINCTRL_PIN(68, "GP33_I2S_0_FS"),
	PINCTRL_PIN(69, "GP34_I2S_0_RXD"),
	PINCTRL_PIN(70, "GP35_I2S_0_TXD"),
	PINCTRL_PIN(71, "GP36_I2S_1_CLK"),
	PINCTRL_PIN(72, "GP37_I2S_1_FS"),
	PINCTRL_PIN(73, "GP38_I2S_1_RXD"),
	PINCTRL_PIN(74, "GP39_I2S_1_TXD"),
	PINCTRL_PIN(75, "GP40_I2S_2_CLK"),
	PINCTRL_PIN(76, "GP41_I2S_2_FS"),
	PINCTRL_PIN(77, "GP42_I2S_2_RXD"),
	PINCTRL_PIN(78, "GP43_I2S_2_TXD"),
	/* Family 6: GP SSP (22 pins) */
	PINCTRL_PIN(79, "GP120_SPI_0_CLK"),
	PINCTRL_PIN(80, "GP121_SPI_0_SS"),
	PINCTRL_PIN(81, "GP122_SPI_0_RXD"),
	PINCTRL_PIN(82, "GP123_SPI_0_TXD"),
	PINCTRL_PIN(83, "GP102_SPI_1_CLK"),
	PINCTRL_PIN(84, "GP103_SPI_1_SS0"),
	PINCTRL_PIN(85, "GP104_SPI_1_SS1"),
	PINCTRL_PIN(86, "GP105_SPI_1_SS2"),
	PINCTRL_PIN(87, "GP106_SPI_1_SS3"),
	PINCTRL_PIN(88, "GP107_SPI_1_RXD"),
	PINCTRL_PIN(89, "GP108_SPI_1_TXD"),
	PINCTRL_PIN(90, "GP109_SPI_2_CLK"),
	PINCTRL_PIN(91, "GP110_SPI_2_SS0"),
	PINCTRL_PIN(92, "GP111_SPI_2_SS1"),
	PINCTRL_PIN(93, "GP112_SPI_2_SS2"),
	PINCTRL_PIN(94, "GP113_SPI_2_SS3"),
	PINCTRL_PIN(95, "GP114_SPI_2_RXD"),
	PINCTRL_PIN(96, "GP115_SPI_2_TXD"),
	PINCTRL_PIN(97, "GP116_SPI_3_CLK"),
	PINCTRL_PIN(98, "GP117_SPI_3_SS"),
	PINCTRL_PIN(99, "GP118_SPI_3_RXD"),
	PINCTRL_PIN(100, "GP119_SPI_3_TXD"),
	/* Family 7: I2C (14 pins) */
	PINCTRL_PIN(101, "GP19_I2C_1_SCL"),
	PINCTRL_PIN(102, "GP20_I2C_1_SDA"),
	PINCTRL_PIN(103, "GP21_I2C_2_SCL"),
	PINCTRL_PIN(104, "GP22_I2C_2_SDA"),
	PINCTRL_PIN(105, "GP17_I2C_3_SCL_HDMI"),
	PINCTRL_PIN(106, "GP18_I2C_3_SDA_HDMI"),
	PINCTRL_PIN(107, "GP23_I2C_4_SCL"),
	PINCTRL_PIN(108, "GP24_I2C_4_SDA"),
	PINCTRL_PIN(109, "GP25_I2C_5_SCL"),
	PINCTRL_PIN(110, "GP26_I2C_5_SDA"),
	PINCTRL_PIN(111, "GP27_I2C_6_SCL"),
	PINCTRL_PIN(112, "GP28_I2C_6_SDA"),
	PINCTRL_PIN(113, "GP29_I2C_7_SCL"),
	PINCTRL_PIN(114, "GP30_I2C_7_SDA"),
	/* Family 8: UART (12 pins) */
	PINCTRL_PIN(115, "GP124_UART_0_CTS"),
	PINCTRL_PIN(116, "GP125_UART_0_RTS"),
	PINCTRL_PIN(117, "GP126_UART_0_RX"),
	PINCTRL_PIN(118, "GP127_UART_0_TX"),
	PINCTRL_PIN(119, "GP128_UART_1_CTS"),
	PINCTRL_PIN(120, "GP129_UART_1_RTS"),
	PINCTRL_PIN(121, "GP130_UART_1_RX"),
	PINCTRL_PIN(122, "GP131_UART_1_TX"),
	PINCTRL_PIN(123, "GP132_UART_2_CTS"),
	PINCTRL_PIN(124, "GP133_UART_2_RTS"),
	PINCTRL_PIN(125, "GP134_UART_2_RX"),
	PINCTRL_PIN(126, "GP135_UART_2_TX"),
	/* Family 9: GPIO South (19 pins) */
	PINCTRL_PIN(127, "GP177"),
	PINCTRL_PIN(128, "GP178"),
	PINCTRL_PIN(129, "GP179"),
	PINCTRL_PIN(130, "GP180"),
	PINCTRL_PIN(131, "GP181"),
	PINCTRL_PIN(132, "GP182_PWM2"),
	PINCTRL_PIN(133, "GP183_PWM3"),
	PINCTRL_PIN(134, "GP184"),
	PINCTRL_PIN(135, "GP185"),
	PINCTRL_PIN(136, "GP186"),
	PINCTRL_PIN(137, "GP187"),
	PINCTRL_PIN(138, "GP188"),
	PINCTRL_PIN(139, "GP189"),
	PINCTRL_PIN(140, "GP64_FAST_INT0"),
	PINCTRL_PIN(141, "GP65_FAST_INT1"),
	PINCTRL_PIN(142, "GP66_FAST_INT2"),
	PINCTRL_PIN(143, "GP67_FAST_INT3"),
	PINCTRL_PIN(144, "GP12_PWM0"),
	PINCTRL_PIN(145, "GP13_PWM1"),
	/* Family 10: Camera Sideband (12 pins) */
	PINCTRL_PIN(146, "GP0"),
	PINCTRL_PIN(147, "GP1"),
	PINCTRL_PIN(148, "GP2"),
	PINCTRL_PIN(149, "GP3"),
	PINCTRL_PIN(150, "GP4"),
	PINCTRL_PIN(151, "GP5"),
	PINCTRL_PIN(152, "GP6"),
	PINCTRL_PIN(153, "GP7"),
	PINCTRL_PIN(154, "GP8"),
	PINCTRL_PIN(155, "GP9"),
	PINCTRL_PIN(156, "GP10"),
	PINCTRL_PIN(157, "GP11"),
	/* Family 11: Clock (22 pins) */
	PINCTRL_PIN(158, "GP137"),
	PINCTRL_PIN(159, "GP138"),
	PINCTRL_PIN(160, "GP139"),
	PINCTRL_PIN(161, "GP140"),
	PINCTRL_PIN(162, "GP141"),
	PINCTRL_PIN(163, "GP142"),
	PINCTRL_PIN(164, "GP16_HDMI_HPD"),
	PINCTRL_PIN(165, "GP68_DSI_A_TE"),
	PINCTRL_PIN(166, "GP69_DSI_C_TE"),
	PINCTRL_PIN(167, "OSC_CLK_CTRL0"),
	PINCTRL_PIN(168, "OSC_CLK_CTRL1"),
	PINCTRL_PIN(169, "OSC_CLK0"),
	PINCTRL_PIN(170, "OSC_CLK1"),
	PINCTRL_PIN(171, "OSC_CLK2"),
	PINCTRL_PIN(172, "OSC_CLK3"),
	PINCTRL_PIN(173, "OSC_CLK4"),
	PINCTRL_PIN(174, "RESETOUT"),
	PINCTRL_PIN(175, "PMODE"),
	PINCTRL_PIN(176, "PRDY"),
	PINCTRL_PIN(177, "PREQ"),
	PINCTRL_PIN(178, "GP190"),
	PINCTRL_PIN(179, "GP191"),
	/* Family 12: MSIC (15 pins) */
	PINCTRL_PIN(180, "I2C_0_SCL"),
	PINCTRL_PIN(181, "I2C_0_SDA"),
	PINCTRL_PIN(182, "IERR"),
	PINCTRL_PIN(183, "JTAG_TCK"),
	PINCTRL_PIN(184, "JTAG_TDI"),
	PINCTRL_PIN(185, "JTAG_TDO"),
	PINCTRL_PIN(186, "JTAG_TMS"),
	PINCTRL_PIN(187, "JTAG_TRST"),
	PINCTRL_PIN(188, "PROCHOT"),
	PINCTRL_PIN(189, "RTC_CLK"),
	PINCTRL_PIN(190, "SVID_ALERT"),
	PINCTRL_PIN(191, "SVID_CLK"),
	PINCTRL_PIN(192, "SVID_D"),
	PINCTRL_PIN(193, "THERMTRIP"),
	PINCTRL_PIN(194, "STANDBY"),
	/* Family 13: Keyboard (20 pins) */
	PINCTRL_PIN(195, "GP44"),
	PINCTRL_PIN(196, "GP45"),
	PINCTRL_PIN(197, "GP46"),
	PINCTRL_PIN(198, "GP47"),
	PINCTRL_PIN(199, "GP48"),
	PINCTRL_PIN(200, "GP49"),
	PINCTRL_PIN(201, "GP50"),
	PINCTRL_PIN(202, "GP51"),
	PINCTRL_PIN(203, "GP52"),
	PINCTRL_PIN(204, "GP53"),
	PINCTRL_PIN(205, "GP54"),
	PINCTRL_PIN(206, "GP55"),
	PINCTRL_PIN(207, "GP56"),
	PINCTRL_PIN(208, "GP57"),
	PINCTRL_PIN(209, "GP58"),
	PINCTRL_PIN(210, "GP59"),
	PINCTRL_PIN(211, "GP60"),
	PINCTRL_PIN(212, "GP61"),
	PINCTRL_PIN(213, "GP62"),
	PINCTRL_PIN(214, "GP63"),
	/* Family 14: GPIO North (13 pins) */
	PINCTRL_PIN(215, "GP164"),
	PINCTRL_PIN(216, "GP165"),
	PINCTRL_PIN(217, "GP166"),
	PINCTRL_PIN(218, "GP167"),
	PINCTRL_PIN(219, "GP168_MJTAG_TCK"),
	PINCTRL_PIN(220, "GP169_MJTAG_TDI"),
	PINCTRL_PIN(221, "GP170_MJTAG_TDO"),
	PINCTRL_PIN(222, "GP171_MJTAG_TMS"),
	PINCTRL_PIN(223, "GP172_MJTAG_TRST"),
	PINCTRL_PIN(224, "GP173"),
	PINCTRL_PIN(225, "GP174"),
	PINCTRL_PIN(226, "GP175"),
	PINCTRL_PIN(227, "GP176"),
	/* Family 15: PTI (5 pins) */
	PINCTRL_PIN(228, "GP72_PTI_CLK"),
	PINCTRL_PIN(229, "GP73_PTI_D0"),
	PINCTRL_PIN(230, "GP74_PTI_D1"),
	PINCTRL_PIN(231, "GP75_PTI_D2"),
	PINCTRL_PIN(232, "GP76_PTI_D3"),
	/* Family 16: USB3 (0 pins) */
	/* Family 17: HSIC (0 pins) */
	/* Family 18: Broadcast (0 pins) */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mrfld_sdio_pins[] = अणु 50, 51, 52, 53, 54, 55, 56 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_i2s2_pins[] = अणु 75, 76, 77, 78 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_spi5_pins[] = अणु 90, 91, 92, 93, 94, 95, 96 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_uart0_pins[] = अणु 115, 116, 117, 118 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_uart1_pins[] = अणु 119, 120, 121, 122 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_uart2_pins[] = अणु 123, 124, 125, 126 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_pwm0_pins[] = अणु 144 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_pwm1_pins[] = अणु 145 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_pwm2_pins[] = अणु 132 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mrfld_pwm3_pins[] = अणु 133 पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pingroup mrfld_groups[] = अणु
	PIN_GROUP("sdio_grp", mrfld_sdio_pins, 1),
	PIN_GROUP("i2s2_grp", mrfld_i2s2_pins, 1),
	PIN_GROUP("spi5_grp", mrfld_spi5_pins, 1),
	PIN_GROUP("uart0_grp", mrfld_uart0_pins, 1),
	PIN_GROUP("uart1_grp", mrfld_uart1_pins, 1),
	PIN_GROUP("uart2_grp", mrfld_uart2_pins, 1),
	PIN_GROUP("pwm0_grp", mrfld_pwm0_pins, 1),
	PIN_GROUP("pwm1_grp", mrfld_pwm1_pins, 1),
	PIN_GROUP("pwm2_grp", mrfld_pwm2_pins, 1),
	PIN_GROUP("pwm3_grp", mrfld_pwm3_pins, 1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर mrfld_sdio_groups[] = अणु "sdio_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_i2s2_groups[] = अणु "i2s2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_spi5_groups[] = अणु "spi5_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_uart0_groups[] = अणु "uart0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_uart1_groups[] = अणु "uart1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_uart2_groups[] = अणु "uart2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_pwm0_groups[] = अणु "pwm0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_pwm1_groups[] = अणु "pwm1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_pwm2_groups[] = अणु "pwm2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर mrfld_pwm3_groups[] = अणु "pwm3_grp" पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_function mrfld_functions[] = अणु
	FUNCTION("sdio", mrfld_sdio_groups),
	FUNCTION("i2s2", mrfld_i2s2_groups),
	FUNCTION("spi5", mrfld_spi5_groups),
	FUNCTION("uart0", mrfld_uart0_groups),
	FUNCTION("uart1", mrfld_uart1_groups),
	FUNCTION("uart2", mrfld_uart2_groups),
	FUNCTION("pwm0", mrfld_pwm0_groups),
	FUNCTION("pwm1", mrfld_pwm1_groups),
	FUNCTION("pwm2", mrfld_pwm2_groups),
	FUNCTION("pwm3", mrfld_pwm3_groups),
पूर्ण;

अटल स्थिर काष्ठा mrfld_family mrfld_families[] = अणु
	MRFLD_FAMILY(1, 0, 12),
	MRFLD_FAMILY(2, 13, 36),
	MRFLD_FAMILY(3, 37, 56),
	MRFLD_FAMILY(4, 57, 64),
	MRFLD_FAMILY(5, 65, 78),
	MRFLD_FAMILY(6, 79, 100),
	MRFLD_FAMILY_PROTECTED(7, 101, 114),
	MRFLD_FAMILY(8, 115, 126),
	MRFLD_FAMILY(9, 127, 145),
	MRFLD_FAMILY(10, 146, 157),
	MRFLD_FAMILY(11, 158, 179),
	MRFLD_FAMILY_PROTECTED(12, 180, 194),
	MRFLD_FAMILY(13, 195, 214),
	MRFLD_FAMILY(14, 215, 227),
	MRFLD_FAMILY(15, 228, 232),
पूर्ण;

/**
 * काष्ठा mrfld_pinctrl - Intel Merrअगरield pinctrl निजी काष्ठाure
 * @dev: Poपूर्णांकer to the device काष्ठाure
 * @lock: Lock to serialize रेजिस्टर access
 * @pctldesc: Pin controller description
 * @pctldev: Poपूर्णांकer to the pin controller device
 * @families: Array of families this pinctrl handles
 * @nfamilies: Number of families in the array
 * @functions: Array of functions
 * @nfunctions: Number of functions in the array
 * @groups: Array of pin groups
 * @ngroups: Number of groups in the array
 * @pins: Array of pins this pinctrl controls
 * @npins: Number of pins in the array
 */
काष्ठा mrfld_pinctrl अणु
	काष्ठा device *dev;
	raw_spinlock_t lock;
	काष्ठा pinctrl_desc pctldesc;
	काष्ठा pinctrl_dev *pctldev;

	/* Pin controller configuration */
	स्थिर काष्ठा mrfld_family *families;
	माप_प्रकार nfamilies;
	स्थिर काष्ठा पूर्णांकel_function *functions;
	माप_प्रकार nfunctions;
	स्थिर काष्ठा पूर्णांकel_pingroup *groups;
	माप_प्रकार ngroups;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	माप_प्रकार npins;
पूर्ण;

#घोषणा pin_to_bufno(f, p)		((p) - (f)->pin_base)

अटल स्थिर काष्ठा mrfld_family *mrfld_get_family(काष्ठा mrfld_pinctrl *mp,
						   अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा mrfld_family *family;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mp->nfamilies; i++) अणु
		family = &mp->families[i];
		अगर (pin >= family->pin_base &&
		    pin < family->pin_base + family->npins)
			वापस family;
	पूर्ण

	dev_warn(mp->dev, "failed to find family for pin %u\n", pin);
	वापस शून्य;
पूर्ण

अटल bool mrfld_buf_available(काष्ठा mrfld_pinctrl *mp, अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा mrfld_family *family;

	family = mrfld_get_family(mp, pin);
	अगर (!family)
		वापस false;

	वापस !family->रक्षित;
पूर्ण

अटल व्योम __iomem *mrfld_get_bufcfg(काष्ठा mrfld_pinctrl *mp, अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा mrfld_family *family;
	अचिन्हित पूर्णांक bufno;

	family = mrfld_get_family(mp, pin);
	अगर (!family)
		वापस शून्य;

	bufno = pin_to_bufno(family, pin);
	वापस family->regs + BUFCFG_OFFSET + bufno * 4;
पूर्ण

अटल पूर्णांक mrfld_पढ़ो_bufcfg(काष्ठा mrfld_pinctrl *mp, अचिन्हित पूर्णांक pin, u32 *value)
अणु
	व्योम __iomem *bufcfg;

	अगर (!mrfld_buf_available(mp, pin))
		वापस -EBUSY;

	bufcfg = mrfld_get_bufcfg(mp, pin);
	*value = पढ़ोl(bufcfg);

	वापस 0;
पूर्ण

अटल व्योम mrfld_update_bufcfg(काष्ठा mrfld_pinctrl *mp, अचिन्हित पूर्णांक pin,
				u32 bits, u32 mask)
अणु
	व्योम __iomem *bufcfg;
	u32 value;

	bufcfg = mrfld_get_bufcfg(mp, pin);
	value = पढ़ोl(bufcfg);

	value &= ~mask;
	value |= bits & mask;

	ग_लिखोl(value, bufcfg);
पूर्ण

अटल पूर्णांक mrfld_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);

	वापस mp->ngroups;
पूर्ण

अटल स्थिर अक्षर *mrfld_get_group_name(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक group)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);

	वापस mp->groups[group].name;
पूर्ण

अटल पूर्णांक mrfld_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक group,
				स्थिर अचिन्हित पूर्णांक **pins, अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);

	*pins = mp->groups[group].pins;
	*npins = mp->groups[group].npins;
	वापस 0;
पूर्ण

अटल व्योम mrfld_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
			       अचिन्हित पूर्णांक pin)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);
	u32 value, mode;
	पूर्णांक ret;

	ret = mrfld_पढ़ो_bufcfg(mp, pin, &value);
	अगर (ret) अणु
		seq_माला_दो(s, "not available");
		वापस;
	पूर्ण

	mode = (value & BUFCFG_PINMODE_MASK) >> BUFCFG_PINMODE_SHIFT;
	अगर (!mode)
		seq_माला_दो(s, "GPIO ");
	अन्यथा
		seq_म_लिखो(s, "mode %d ", mode);

	seq_म_लिखो(s, "0x%08x", value);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops mrfld_pinctrl_ops = अणु
	.get_groups_count = mrfld_get_groups_count,
	.get_group_name = mrfld_get_group_name,
	.get_group_pins = mrfld_get_group_pins,
	.pin_dbg_show = mrfld_pin_dbg_show,
पूर्ण;

अटल पूर्णांक mrfld_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);

	वापस mp->nfunctions;
पूर्ण

अटल स्थिर अक्षर *mrfld_get_function_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक function)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);

	वापस mp->functions[function].name;
पूर्ण

अटल पूर्णांक mrfld_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक function,
				     स्थिर अक्षर * स्थिर **groups,
				     अचिन्हित पूर्णांक * स्थिर ngroups)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);

	*groups = mp->functions[function].groups;
	*ngroups = mp->functions[function].ngroups;
	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक function,
				अचिन्हित पूर्णांक group)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा पूर्णांकel_pingroup *grp = &mp->groups[group];
	u32 bits = grp->mode << BUFCFG_PINMODE_SHIFT;
	u32 mask = BUFCFG_PINMODE_MASK;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/*
	 * All pins in the groups needs to be accessible and writable
	 * beक्रमe we can enable the mux क्रम this group.
	 */
	क्रम (i = 0; i < grp->npins; i++) अणु
		अगर (!mrfld_buf_available(mp, grp->pins[i]))
			वापस -EBUSY;
	पूर्ण

	/* Now enable the mux setting क्रम each pin in the group */
	raw_spin_lock_irqsave(&mp->lock, flags);
	क्रम (i = 0; i < grp->npins; i++)
		mrfld_update_bufcfg(mp, grp->pins[i], bits, mask);
	raw_spin_unlock_irqrestore(&mp->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित पूर्णांक pin)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);
	u32 bits = BUFCFG_PINMODE_GPIO << BUFCFG_PINMODE_SHIFT;
	u32 mask = BUFCFG_PINMODE_MASK;
	अचिन्हित दीर्घ flags;

	अगर (!mrfld_buf_available(mp, pin))
		वापस -EBUSY;

	raw_spin_lock_irqsave(&mp->lock, flags);
	mrfld_update_bufcfg(mp, pin, bits, mask);
	raw_spin_unlock_irqrestore(&mp->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops mrfld_pinmux_ops = अणु
	.get_functions_count = mrfld_get_functions_count,
	.get_function_name = mrfld_get_function_name,
	.get_function_groups = mrfld_get_function_groups,
	.set_mux = mrfld_pinmux_set_mux,
	.gpio_request_enable = mrfld_gpio_request_enable,
पूर्ण;

अटल पूर्णांक mrfld_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			    अचिन्हित दीर्घ *config)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	u32 value, term;
	u16 arg = 0;
	पूर्णांक ret;

	ret = mrfld_पढ़ो_bufcfg(mp, pin, &value);
	अगर (ret)
		वापस -ENOTSUPP;

	term = (value & BUFCFG_PUPD_VAL_MASK) >> BUFCFG_PUPD_VAL_SHIFT;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (value & BUFCFG_Px_EN_MASK)
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर ((value & BUFCFG_Px_EN_MASK) != BUFCFG_PU_EN)
			वापस -EINVAL;

		चयन (term) अणु
		हाल BUFCFG_PUPD_VAL_910:
			arg = 910;
			अवरोध;
		हाल BUFCFG_PUPD_VAL_2K:
			arg = 2000;
			अवरोध;
		हाल BUFCFG_PUPD_VAL_20K:
			arg = 20000;
			अवरोध;
		हाल BUFCFG_PUPD_VAL_50K:
			arg = 50000;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर ((value & BUFCFG_Px_EN_MASK) != BUFCFG_PD_EN)
			वापस -EINVAL;

		चयन (term) अणु
		हाल BUFCFG_PUPD_VAL_910:
			arg = 910;
			अवरोध;
		हाल BUFCFG_PUPD_VAL_2K:
			arg = 2000;
			अवरोध;
		हाल BUFCFG_PUPD_VAL_20K:
			arg = 20000;
			अवरोध;
		हाल BUFCFG_PUPD_VAL_50K:
			arg = 50000;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (!(value & BUFCFG_OD_EN))
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_SLEW_RATE:
		अगर (!(value & BUFCFG_SLEWSEL))
			arg = 0;
		अन्यथा
			arg = 1;
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_config_set_pin(काष्ठा mrfld_pinctrl *mp, अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ config)
अणु
	अचिन्हित पूर्णांक param = pinconf_to_config_param(config);
	अचिन्हित पूर्णांक arg = pinconf_to_config_argument(config);
	u32 bits = 0, mask = 0;
	अचिन्हित दीर्घ flags;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		mask |= BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAL_MASK;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		mask |= BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAL_MASK;
		bits |= BUFCFG_PU_EN;

		/* Set शेष strength value in हाल none is given */
		अगर (arg == 1)
			arg = 20000;

		चयन (arg) अणु
		हाल 50000:
			bits |= BUFCFG_PUPD_VAL_50K << BUFCFG_PUPD_VAL_SHIFT;
			अवरोध;
		हाल 20000:
			bits |= BUFCFG_PUPD_VAL_20K << BUFCFG_PUPD_VAL_SHIFT;
			अवरोध;
		हाल 2000:
			bits |= BUFCFG_PUPD_VAL_2K << BUFCFG_PUPD_VAL_SHIFT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		mask |= BUFCFG_Px_EN_MASK | BUFCFG_PUPD_VAL_MASK;
		bits |= BUFCFG_PD_EN;

		/* Set शेष strength value in हाल none is given */
		अगर (arg == 1)
			arg = 20000;

		चयन (arg) अणु
		हाल 50000:
			bits |= BUFCFG_PUPD_VAL_50K << BUFCFG_PUPD_VAL_SHIFT;
			अवरोध;
		हाल 20000:
			bits |= BUFCFG_PUPD_VAL_20K << BUFCFG_PUPD_VAL_SHIFT;
			अवरोध;
		हाल 2000:
			bits |= BUFCFG_PUPD_VAL_2K << BUFCFG_PUPD_VAL_SHIFT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अवरोध;

	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		mask |= BUFCFG_OD_EN;
		अगर (arg)
			bits |= BUFCFG_OD_EN;
		अवरोध;

	हाल PIN_CONFIG_SLEW_RATE:
		mask |= BUFCFG_SLEWSEL;
		अगर (arg)
			bits |= BUFCFG_SLEWSEL;
		अवरोध;
	पूर्ण

	raw_spin_lock_irqsave(&mp->lock, flags);
	mrfld_update_bufcfg(mp, pin, bits, mask);
	raw_spin_unlock_irqrestore(&mp->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			    अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक nconfigs)
अणु
	काष्ठा mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!mrfld_buf_available(mp, pin))
		वापस -ENOTSUPP;

	क्रम (i = 0; i < nconfigs; i++) अणु
		चयन (pinconf_to_config_param(configs[i])) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		हाल PIN_CONFIG_SLEW_RATE:
			ret = mrfld_config_set_pin(mp, pin, configs[i]);
			अगर (ret)
				वापस ret;
			अवरोध;

		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_config_group_get(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *config)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक npins;
	पूर्णांक ret;

	ret = mrfld_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	ret = mrfld_config_get(pctldev, pins[0], config);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_config_group_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक npins;
	पूर्णांक i, ret;

	ret = mrfld_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < npins; i++) अणु
		ret = mrfld_config_set(pctldev, pins[i], configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops mrfld_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = mrfld_config_get,
	.pin_config_set = mrfld_config_set,
	.pin_config_group_get = mrfld_config_group_get,
	.pin_config_group_set = mrfld_config_group_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc mrfld_pinctrl_desc = अणु
	.pctlops = &mrfld_pinctrl_ops,
	.pmxops = &mrfld_pinmux_ops,
	.confops = &mrfld_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक mrfld_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mrfld_family *families;
	काष्ठा mrfld_pinctrl *mp;
	व्योम __iomem *regs;
	माप_प्रकार nfamilies;
	अचिन्हित पूर्णांक i;

	mp = devm_kzalloc(&pdev->dev, माप(*mp), GFP_KERNEL);
	अगर (!mp)
		वापस -ENOMEM;

	mp->dev = &pdev->dev;
	raw_spin_lock_init(&mp->lock);

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	/*
	 * Make a copy of the families which we can use to hold poपूर्णांकers
	 * to the रेजिस्टरs.
	 */
	nfamilies = ARRAY_SIZE(mrfld_families),
	families = devm_kmemdup(&pdev->dev, mrfld_families,
					    माप(mrfld_families),
					    GFP_KERNEL);
	अगर (!families)
		वापस -ENOMEM;

	/* Splice memory resource by chunk per family */
	क्रम (i = 0; i < nfamilies; i++) अणु
		काष्ठा mrfld_family *family = &families[i];

		family->regs = regs + family->barno * MRFLD_FAMILY_LEN;
	पूर्ण

	mp->families = families;
	mp->nfamilies = nfamilies;
	mp->functions = mrfld_functions;
	mp->nfunctions = ARRAY_SIZE(mrfld_functions);
	mp->groups = mrfld_groups;
	mp->ngroups = ARRAY_SIZE(mrfld_groups);
	mp->pctldesc = mrfld_pinctrl_desc;
	mp->pctldesc.name = dev_name(&pdev->dev);
	mp->pctldesc.pins = mrfld_pins;
	mp->pctldesc.npins = ARRAY_SIZE(mrfld_pins);

	mp->pctldev = devm_pinctrl_रेजिस्टर(&pdev->dev, &mp->pctldesc, mp);
	अगर (IS_ERR(mp->pctldev)) अणु
		dev_err(&pdev->dev, "failed to register pinctrl driver\n");
		वापस PTR_ERR(mp->pctldev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, mp);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id mrfld_acpi_table[] = अणु
	अणु "INTC1002" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mrfld_acpi_table);

अटल काष्ठा platक्रमm_driver mrfld_pinctrl_driver = अणु
	.probe = mrfld_pinctrl_probe,
	.driver = अणु
		.name = "pinctrl-merrifield",
		.acpi_match_table = mrfld_acpi_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mrfld_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mrfld_pinctrl_driver);
पूर्ण
subsys_initcall(mrfld_pinctrl_init);

अटल व्योम __निकास mrfld_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mrfld_pinctrl_driver);
पूर्ण
module_निकास(mrfld_pinctrl_निकास);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_DESCRIPTION("Intel Merrifield SoC pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:pinctrl-merrifield");
