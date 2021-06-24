<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinctrl data क्रम the NVIDIA Tegra30 pinmux
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 *
 * Copyright (c) 2011-2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>

#समावेश "pinctrl-tegra.h"

/*
 * Most pins affected by the pinmux can also be GPIOs. Define these first.
 * These must match how the GPIO driver names/numbers its pins.
 */
#घोषणा _GPIO(offset)			(offset)

#घोषणा TEGRA_PIN_CLK_32K_OUT_PA0	_GPIO(0)
#घोषणा TEGRA_PIN_UART3_CTS_N_PA1	_GPIO(1)
#घोषणा TEGRA_PIN_DAP2_FS_PA2		_GPIO(2)
#घोषणा TEGRA_PIN_DAP2_SCLK_PA3		_GPIO(3)
#घोषणा TEGRA_PIN_DAP2_DIN_PA4		_GPIO(4)
#घोषणा TEGRA_PIN_DAP2_DOUT_PA5		_GPIO(5)
#घोषणा TEGRA_PIN_SDMMC3_CLK_PA6	_GPIO(6)
#घोषणा TEGRA_PIN_SDMMC3_CMD_PA7	_GPIO(7)
#घोषणा TEGRA_PIN_GMI_A17_PB0		_GPIO(8)
#घोषणा TEGRA_PIN_GMI_A18_PB1		_GPIO(9)
#घोषणा TEGRA_PIN_LCD_PWR0_PB2		_GPIO(10)
#घोषणा TEGRA_PIN_LCD_PCLK_PB3		_GPIO(11)
#घोषणा TEGRA_PIN_SDMMC3_DAT3_PB4	_GPIO(12)
#घोषणा TEGRA_PIN_SDMMC3_DAT2_PB5	_GPIO(13)
#घोषणा TEGRA_PIN_SDMMC3_DAT1_PB6	_GPIO(14)
#घोषणा TEGRA_PIN_SDMMC3_DAT0_PB7	_GPIO(15)
#घोषणा TEGRA_PIN_UART3_RTS_N_PC0	_GPIO(16)
#घोषणा TEGRA_PIN_LCD_PWR1_PC1		_GPIO(17)
#घोषणा TEGRA_PIN_UART2_TXD_PC2		_GPIO(18)
#घोषणा TEGRA_PIN_UART2_RXD_PC3		_GPIO(19)
#घोषणा TEGRA_PIN_GEN1_I2C_SCL_PC4	_GPIO(20)
#घोषणा TEGRA_PIN_GEN1_I2C_SDA_PC5	_GPIO(21)
#घोषणा TEGRA_PIN_LCD_PWR2_PC6		_GPIO(22)
#घोषणा TEGRA_PIN_GMI_WP_N_PC7		_GPIO(23)
#घोषणा TEGRA_PIN_SDMMC3_DAT5_PD0	_GPIO(24)
#घोषणा TEGRA_PIN_SDMMC3_DAT4_PD1	_GPIO(25)
#घोषणा TEGRA_PIN_LCD_DC1_PD2		_GPIO(26)
#घोषणा TEGRA_PIN_SDMMC3_DAT6_PD3	_GPIO(27)
#घोषणा TEGRA_PIN_SDMMC3_DAT7_PD4	_GPIO(28)
#घोषणा TEGRA_PIN_VI_D1_PD5		_GPIO(29)
#घोषणा TEGRA_PIN_VI_VSYNC_PD6		_GPIO(30)
#घोषणा TEGRA_PIN_VI_HSYNC_PD7		_GPIO(31)
#घोषणा TEGRA_PIN_LCD_D0_PE0		_GPIO(32)
#घोषणा TEGRA_PIN_LCD_D1_PE1		_GPIO(33)
#घोषणा TEGRA_PIN_LCD_D2_PE2		_GPIO(34)
#घोषणा TEGRA_PIN_LCD_D3_PE3		_GPIO(35)
#घोषणा TEGRA_PIN_LCD_D4_PE4		_GPIO(36)
#घोषणा TEGRA_PIN_LCD_D5_PE5		_GPIO(37)
#घोषणा TEGRA_PIN_LCD_D6_PE6		_GPIO(38)
#घोषणा TEGRA_PIN_LCD_D7_PE7		_GPIO(39)
#घोषणा TEGRA_PIN_LCD_D8_PF0		_GPIO(40)
#घोषणा TEGRA_PIN_LCD_D9_PF1		_GPIO(41)
#घोषणा TEGRA_PIN_LCD_D10_PF2		_GPIO(42)
#घोषणा TEGRA_PIN_LCD_D11_PF3		_GPIO(43)
#घोषणा TEGRA_PIN_LCD_D12_PF4		_GPIO(44)
#घोषणा TEGRA_PIN_LCD_D13_PF5		_GPIO(45)
#घोषणा TEGRA_PIN_LCD_D14_PF6		_GPIO(46)
#घोषणा TEGRA_PIN_LCD_D15_PF7		_GPIO(47)
#घोषणा TEGRA_PIN_GMI_AD0_PG0		_GPIO(48)
#घोषणा TEGRA_PIN_GMI_AD1_PG1		_GPIO(49)
#घोषणा TEGRA_PIN_GMI_AD2_PG2		_GPIO(50)
#घोषणा TEGRA_PIN_GMI_AD3_PG3		_GPIO(51)
#घोषणा TEGRA_PIN_GMI_AD4_PG4		_GPIO(52)
#घोषणा TEGRA_PIN_GMI_AD5_PG5		_GPIO(53)
#घोषणा TEGRA_PIN_GMI_AD6_PG6		_GPIO(54)
#घोषणा TEGRA_PIN_GMI_AD7_PG7		_GPIO(55)
#घोषणा TEGRA_PIN_GMI_AD8_PH0		_GPIO(56)
#घोषणा TEGRA_PIN_GMI_AD9_PH1		_GPIO(57)
#घोषणा TEGRA_PIN_GMI_AD10_PH2		_GPIO(58)
#घोषणा TEGRA_PIN_GMI_AD11_PH3		_GPIO(59)
#घोषणा TEGRA_PIN_GMI_AD12_PH4		_GPIO(60)
#घोषणा TEGRA_PIN_GMI_AD13_PH5		_GPIO(61)
#घोषणा TEGRA_PIN_GMI_AD14_PH6		_GPIO(62)
#घोषणा TEGRA_PIN_GMI_AD15_PH7		_GPIO(63)
#घोषणा TEGRA_PIN_GMI_WR_N_PI0		_GPIO(64)
#घोषणा TEGRA_PIN_GMI_OE_N_PI1		_GPIO(65)
#घोषणा TEGRA_PIN_GMI_DQS_PI2		_GPIO(66)
#घोषणा TEGRA_PIN_GMI_CS6_N_PI3		_GPIO(67)
#घोषणा TEGRA_PIN_GMI_RST_N_PI4		_GPIO(68)
#घोषणा TEGRA_PIN_GMI_IORDY_PI5		_GPIO(69)
#घोषणा TEGRA_PIN_GMI_CS7_N_PI6		_GPIO(70)
#घोषणा TEGRA_PIN_GMI_WAIT_PI7		_GPIO(71)
#घोषणा TEGRA_PIN_GMI_CS0_N_PJ0		_GPIO(72)
#घोषणा TEGRA_PIN_LCD_DE_PJ1		_GPIO(73)
#घोषणा TEGRA_PIN_GMI_CS1_N_PJ2		_GPIO(74)
#घोषणा TEGRA_PIN_LCD_HSYNC_PJ3		_GPIO(75)
#घोषणा TEGRA_PIN_LCD_VSYNC_PJ4		_GPIO(76)
#घोषणा TEGRA_PIN_UART2_CTS_N_PJ5	_GPIO(77)
#घोषणा TEGRA_PIN_UART2_RTS_N_PJ6	_GPIO(78)
#घोषणा TEGRA_PIN_GMI_A16_PJ7		_GPIO(79)
#घोषणा TEGRA_PIN_GMI_ADV_N_PK0		_GPIO(80)
#घोषणा TEGRA_PIN_GMI_CLK_PK1		_GPIO(81)
#घोषणा TEGRA_PIN_GMI_CS4_N_PK2		_GPIO(82)
#घोषणा TEGRA_PIN_GMI_CS2_N_PK3		_GPIO(83)
#घोषणा TEGRA_PIN_GMI_CS3_N_PK4		_GPIO(84)
#घोषणा TEGRA_PIN_SPDIF_OUT_PK5		_GPIO(85)
#घोषणा TEGRA_PIN_SPDIF_IN_PK6		_GPIO(86)
#घोषणा TEGRA_PIN_GMI_A19_PK7		_GPIO(87)
#घोषणा TEGRA_PIN_VI_D2_PL0		_GPIO(88)
#घोषणा TEGRA_PIN_VI_D3_PL1		_GPIO(89)
#घोषणा TEGRA_PIN_VI_D4_PL2		_GPIO(90)
#घोषणा TEGRA_PIN_VI_D5_PL3		_GPIO(91)
#घोषणा TEGRA_PIN_VI_D6_PL4		_GPIO(92)
#घोषणा TEGRA_PIN_VI_D7_PL5		_GPIO(93)
#घोषणा TEGRA_PIN_VI_D8_PL6		_GPIO(94)
#घोषणा TEGRA_PIN_VI_D9_PL7		_GPIO(95)
#घोषणा TEGRA_PIN_LCD_D16_PM0		_GPIO(96)
#घोषणा TEGRA_PIN_LCD_D17_PM1		_GPIO(97)
#घोषणा TEGRA_PIN_LCD_D18_PM2		_GPIO(98)
#घोषणा TEGRA_PIN_LCD_D19_PM3		_GPIO(99)
#घोषणा TEGRA_PIN_LCD_D20_PM4		_GPIO(100)
#घोषणा TEGRA_PIN_LCD_D21_PM5		_GPIO(101)
#घोषणा TEGRA_PIN_LCD_D22_PM6		_GPIO(102)
#घोषणा TEGRA_PIN_LCD_D23_PM7		_GPIO(103)
#घोषणा TEGRA_PIN_DAP1_FS_PN0		_GPIO(104)
#घोषणा TEGRA_PIN_DAP1_DIN_PN1		_GPIO(105)
#घोषणा TEGRA_PIN_DAP1_DOUT_PN2		_GPIO(106)
#घोषणा TEGRA_PIN_DAP1_SCLK_PN3		_GPIO(107)
#घोषणा TEGRA_PIN_LCD_CS0_N_PN4		_GPIO(108)
#घोषणा TEGRA_PIN_LCD_SDOUT_PN5		_GPIO(109)
#घोषणा TEGRA_PIN_LCD_DC0_PN6		_GPIO(110)
#घोषणा TEGRA_PIN_HDMI_INT_PN7		_GPIO(111)
#घोषणा TEGRA_PIN_ULPI_DATA7_PO0	_GPIO(112)
#घोषणा TEGRA_PIN_ULPI_DATA0_PO1	_GPIO(113)
#घोषणा TEGRA_PIN_ULPI_DATA1_PO2	_GPIO(114)
#घोषणा TEGRA_PIN_ULPI_DATA2_PO3	_GPIO(115)
#घोषणा TEGRA_PIN_ULPI_DATA3_PO4	_GPIO(116)
#घोषणा TEGRA_PIN_ULPI_DATA4_PO5	_GPIO(117)
#घोषणा TEGRA_PIN_ULPI_DATA5_PO6	_GPIO(118)
#घोषणा TEGRA_PIN_ULPI_DATA6_PO7	_GPIO(119)
#घोषणा TEGRA_PIN_DAP3_FS_PP0		_GPIO(120)
#घोषणा TEGRA_PIN_DAP3_DIN_PP1		_GPIO(121)
#घोषणा TEGRA_PIN_DAP3_DOUT_PP2		_GPIO(122)
#घोषणा TEGRA_PIN_DAP3_SCLK_PP3		_GPIO(123)
#घोषणा TEGRA_PIN_DAP4_FS_PP4		_GPIO(124)
#घोषणा TEGRA_PIN_DAP4_DIN_PP5		_GPIO(125)
#घोषणा TEGRA_PIN_DAP4_DOUT_PP6		_GPIO(126)
#घोषणा TEGRA_PIN_DAP4_SCLK_PP7		_GPIO(127)
#घोषणा TEGRA_PIN_KB_COL0_PQ0		_GPIO(128)
#घोषणा TEGRA_PIN_KB_COL1_PQ1		_GPIO(129)
#घोषणा TEGRA_PIN_KB_COL2_PQ2		_GPIO(130)
#घोषणा TEGRA_PIN_KB_COL3_PQ3		_GPIO(131)
#घोषणा TEGRA_PIN_KB_COL4_PQ4		_GPIO(132)
#घोषणा TEGRA_PIN_KB_COL5_PQ5		_GPIO(133)
#घोषणा TEGRA_PIN_KB_COL6_PQ6		_GPIO(134)
#घोषणा TEGRA_PIN_KB_COL7_PQ7		_GPIO(135)
#घोषणा TEGRA_PIN_KB_ROW0_PR0		_GPIO(136)
#घोषणा TEGRA_PIN_KB_ROW1_PR1		_GPIO(137)
#घोषणा TEGRA_PIN_KB_ROW2_PR2		_GPIO(138)
#घोषणा TEGRA_PIN_KB_ROW3_PR3		_GPIO(139)
#घोषणा TEGRA_PIN_KB_ROW4_PR4		_GPIO(140)
#घोषणा TEGRA_PIN_KB_ROW5_PR5		_GPIO(141)
#घोषणा TEGRA_PIN_KB_ROW6_PR6		_GPIO(142)
#घोषणा TEGRA_PIN_KB_ROW7_PR7		_GPIO(143)
#घोषणा TEGRA_PIN_KB_ROW8_PS0		_GPIO(144)
#घोषणा TEGRA_PIN_KB_ROW9_PS1		_GPIO(145)
#घोषणा TEGRA_PIN_KB_ROW10_PS2		_GPIO(146)
#घोषणा TEGRA_PIN_KB_ROW11_PS3		_GPIO(147)
#घोषणा TEGRA_PIN_KB_ROW12_PS4		_GPIO(148)
#घोषणा TEGRA_PIN_KB_ROW13_PS5		_GPIO(149)
#घोषणा TEGRA_PIN_KB_ROW14_PS6		_GPIO(150)
#घोषणा TEGRA_PIN_KB_ROW15_PS7		_GPIO(151)
#घोषणा TEGRA_PIN_VI_PCLK_PT0		_GPIO(152)
#घोषणा TEGRA_PIN_VI_MCLK_PT1		_GPIO(153)
#घोषणा TEGRA_PIN_VI_D10_PT2		_GPIO(154)
#घोषणा TEGRA_PIN_VI_D11_PT3		_GPIO(155)
#घोषणा TEGRA_PIN_VI_D0_PT4		_GPIO(156)
#घोषणा TEGRA_PIN_GEN2_I2C_SCL_PT5	_GPIO(157)
#घोषणा TEGRA_PIN_GEN2_I2C_SDA_PT6	_GPIO(158)
#घोषणा TEGRA_PIN_SDMMC4_CMD_PT7	_GPIO(159)
#घोषणा TEGRA_PIN_PU0			_GPIO(160)
#घोषणा TEGRA_PIN_PU1			_GPIO(161)
#घोषणा TEGRA_PIN_PU2			_GPIO(162)
#घोषणा TEGRA_PIN_PU3			_GPIO(163)
#घोषणा TEGRA_PIN_PU4			_GPIO(164)
#घोषणा TEGRA_PIN_PU5			_GPIO(165)
#घोषणा TEGRA_PIN_PU6			_GPIO(166)
#घोषणा TEGRA_PIN_JTAG_RTCK_PU7		_GPIO(167)
#घोषणा TEGRA_PIN_PV0			_GPIO(168)
#घोषणा TEGRA_PIN_PV1			_GPIO(169)
#घोषणा TEGRA_PIN_PV2			_GPIO(170)
#घोषणा TEGRA_PIN_PV3			_GPIO(171)
#घोषणा TEGRA_PIN_DDC_SCL_PV4		_GPIO(172)
#घोषणा TEGRA_PIN_DDC_SDA_PV5		_GPIO(173)
#घोषणा TEGRA_PIN_CRT_HSYNC_PV6		_GPIO(174)
#घोषणा TEGRA_PIN_CRT_VSYNC_PV7		_GPIO(175)
#घोषणा TEGRA_PIN_LCD_CS1_N_PW0		_GPIO(176)
#घोषणा TEGRA_PIN_LCD_M1_PW1		_GPIO(177)
#घोषणा TEGRA_PIN_SPI2_CS1_N_PW2	_GPIO(178)
#घोषणा TEGRA_PIN_SPI2_CS2_N_PW3	_GPIO(179)
#घोषणा TEGRA_PIN_CLK1_OUT_PW4		_GPIO(180)
#घोषणा TEGRA_PIN_CLK2_OUT_PW5		_GPIO(181)
#घोषणा TEGRA_PIN_UART3_TXD_PW6		_GPIO(182)
#घोषणा TEGRA_PIN_UART3_RXD_PW7		_GPIO(183)
#घोषणा TEGRA_PIN_SPI2_MOSI_PX0		_GPIO(184)
#घोषणा TEGRA_PIN_SPI2_MISO_PX1		_GPIO(185)
#घोषणा TEGRA_PIN_SPI2_SCK_PX2		_GPIO(186)
#घोषणा TEGRA_PIN_SPI2_CS0_N_PX3	_GPIO(187)
#घोषणा TEGRA_PIN_SPI1_MOSI_PX4		_GPIO(188)
#घोषणा TEGRA_PIN_SPI1_SCK_PX5		_GPIO(189)
#घोषणा TEGRA_PIN_SPI1_CS0_N_PX6	_GPIO(190)
#घोषणा TEGRA_PIN_SPI1_MISO_PX7		_GPIO(191)
#घोषणा TEGRA_PIN_ULPI_CLK_PY0		_GPIO(192)
#घोषणा TEGRA_PIN_ULPI_सूची_PY1		_GPIO(193)
#घोषणा TEGRA_PIN_ULPI_NXT_PY2		_GPIO(194)
#घोषणा TEGRA_PIN_ULPI_STP_PY3		_GPIO(195)
#घोषणा TEGRA_PIN_SDMMC1_DAT3_PY4	_GPIO(196)
#घोषणा TEGRA_PIN_SDMMC1_DAT2_PY5	_GPIO(197)
#घोषणा TEGRA_PIN_SDMMC1_DAT1_PY6	_GPIO(198)
#घोषणा TEGRA_PIN_SDMMC1_DAT0_PY7	_GPIO(199)
#घोषणा TEGRA_PIN_SDMMC1_CLK_PZ0	_GPIO(200)
#घोषणा TEGRA_PIN_SDMMC1_CMD_PZ1	_GPIO(201)
#घोषणा TEGRA_PIN_LCD_SDIN_PZ2		_GPIO(202)
#घोषणा TEGRA_PIN_LCD_WR_N_PZ3		_GPIO(203)
#घोषणा TEGRA_PIN_LCD_SCK_PZ4		_GPIO(204)
#घोषणा TEGRA_PIN_SYS_CLK_REQ_PZ5	_GPIO(205)
#घोषणा TEGRA_PIN_PWR_I2C_SCL_PZ6	_GPIO(206)
#घोषणा TEGRA_PIN_PWR_I2C_SDA_PZ7	_GPIO(207)
#घोषणा TEGRA_PIN_SDMMC4_DAT0_PAA0	_GPIO(208)
#घोषणा TEGRA_PIN_SDMMC4_DAT1_PAA1	_GPIO(209)
#घोषणा TEGRA_PIN_SDMMC4_DAT2_PAA2	_GPIO(210)
#घोषणा TEGRA_PIN_SDMMC4_DAT3_PAA3	_GPIO(211)
#घोषणा TEGRA_PIN_SDMMC4_DAT4_PAA4	_GPIO(212)
#घोषणा TEGRA_PIN_SDMMC4_DAT5_PAA5	_GPIO(213)
#घोषणा TEGRA_PIN_SDMMC4_DAT6_PAA6	_GPIO(214)
#घोषणा TEGRA_PIN_SDMMC4_DAT7_PAA7	_GPIO(215)
#घोषणा TEGRA_PIN_PBB0			_GPIO(216)
#घोषणा TEGRA_PIN_CAM_I2C_SCL_PBB1	_GPIO(217)
#घोषणा TEGRA_PIN_CAM_I2C_SDA_PBB2	_GPIO(218)
#घोषणा TEGRA_PIN_PBB3			_GPIO(219)
#घोषणा TEGRA_PIN_PBB4			_GPIO(220)
#घोषणा TEGRA_PIN_PBB5			_GPIO(221)
#घोषणा TEGRA_PIN_PBB6			_GPIO(222)
#घोषणा TEGRA_PIN_PBB7			_GPIO(223)
#घोषणा TEGRA_PIN_CAM_MCLK_PCC0		_GPIO(224)
#घोषणा TEGRA_PIN_PCC1			_GPIO(225)
#घोषणा TEGRA_PIN_PCC2			_GPIO(226)
#घोषणा TEGRA_PIN_SDMMC4_RST_N_PCC3	_GPIO(227)
#घोषणा TEGRA_PIN_SDMMC4_CLK_PCC4	_GPIO(228)
#घोषणा TEGRA_PIN_CLK2_REQ_PCC5		_GPIO(229)
#घोषणा TEGRA_PIN_PEX_L2_RST_N_PCC6	_GPIO(230)
#घोषणा TEGRA_PIN_PEX_L2_CLKREQ_N_PCC7	_GPIO(231)
#घोषणा TEGRA_PIN_PEX_L0_PRSNT_N_PDD0	_GPIO(232)
#घोषणा TEGRA_PIN_PEX_L0_RST_N_PDD1	_GPIO(233)
#घोषणा TEGRA_PIN_PEX_L0_CLKREQ_N_PDD2	_GPIO(234)
#घोषणा TEGRA_PIN_PEX_WAKE_N_PDD3	_GPIO(235)
#घोषणा TEGRA_PIN_PEX_L1_PRSNT_N_PDD4	_GPIO(236)
#घोषणा TEGRA_PIN_PEX_L1_RST_N_PDD5	_GPIO(237)
#घोषणा TEGRA_PIN_PEX_L1_CLKREQ_N_PDD6	_GPIO(238)
#घोषणा TEGRA_PIN_PEX_L2_PRSNT_N_PDD7	_GPIO(239)
#घोषणा TEGRA_PIN_CLK3_OUT_PEE0		_GPIO(240)
#घोषणा TEGRA_PIN_CLK3_REQ_PEE1		_GPIO(241)
#घोषणा TEGRA_PIN_CLK1_REQ_PEE2		_GPIO(242)
#घोषणा TEGRA_PIN_HDMI_CEC_PEE3		_GPIO(243)
#घोषणा TEGRA_PIN_PEE4			_GPIO(244)
#घोषणा TEGRA_PIN_PEE5			_GPIO(245)
#घोषणा TEGRA_PIN_PEE6			_GPIO(246)
#घोषणा TEGRA_PIN_PEE7			_GPIO(247)

/* All non-GPIO pins follow */
#घोषणा NUM_GPIOS			(TEGRA_PIN_PEE7 + 1)
#घोषणा _PIN(offset)			(NUM_GPIOS + (offset))

/* Non-GPIO pins */
#घोषणा TEGRA_PIN_CLK_32K_IN		_PIN(0)
#घोषणा TEGRA_PIN_CORE_PWR_REQ		_PIN(1)
#घोषणा TEGRA_PIN_CPU_PWR_REQ		_PIN(2)
#घोषणा TEGRA_PIN_JTAG_TCK		_PIN(3)
#घोषणा TEGRA_PIN_JTAG_TDI		_PIN(4)
#घोषणा TEGRA_PIN_JTAG_TDO		_PIN(5)
#घोषणा TEGRA_PIN_JTAG_TMS		_PIN(6)
#घोषणा TEGRA_PIN_JTAG_TRST_N		_PIN(7)
#घोषणा TEGRA_PIN_OWR			_PIN(8)
#घोषणा TEGRA_PIN_PWR_INT_N		_PIN(9)
#घोषणा TEGRA_PIN_SYS_RESET_N		_PIN(10)
#घोषणा TEGRA_PIN_TEST_MODE_EN		_PIN(11)

अटल स्थिर काष्ठा pinctrl_pin_desc tegra30_pins[] = अणु
	PINCTRL_PIN(TEGRA_PIN_CLK_32K_OUT_PA0, "CLK_32K_OUT PA0"),
	PINCTRL_PIN(TEGRA_PIN_UART3_CTS_N_PA1, "UART3_CTS_N PA1"),
	PINCTRL_PIN(TEGRA_PIN_DAP2_FS_PA2, "DAP2_FS PA2"),
	PINCTRL_PIN(TEGRA_PIN_DAP2_SCLK_PA3, "DAP2_SCLK PA3"),
	PINCTRL_PIN(TEGRA_PIN_DAP2_DIN_PA4, "DAP2_DIN PA4"),
	PINCTRL_PIN(TEGRA_PIN_DAP2_DOUT_PA5, "DAP2_DOUT PA5"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_CLK_PA6, "SDMMC3_CLK PA6"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_CMD_PA7, "SDMMC3_CMD PA7"),
	PINCTRL_PIN(TEGRA_PIN_GMI_A17_PB0, "GMI_A17 PB0"),
	PINCTRL_PIN(TEGRA_PIN_GMI_A18_PB1, "GMI_A18 PB1"),
	PINCTRL_PIN(TEGRA_PIN_LCD_PWR0_PB2, "LCD_PWR0 PB2"),
	PINCTRL_PIN(TEGRA_PIN_LCD_PCLK_PB3, "LCD_PCLK PB3"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT3_PB4, "SDMMC3_DAT3 PB4"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT2_PB5, "SDMMC3_DAT2 PB5"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT1_PB6, "SDMMC3_DAT1 PB6"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT0_PB7, "SDMMC3_DAT0 PB7"),
	PINCTRL_PIN(TEGRA_PIN_UART3_RTS_N_PC0, "UART3_RTS_N PC0"),
	PINCTRL_PIN(TEGRA_PIN_LCD_PWR1_PC1, "LCD_PWR1 PC1"),
	PINCTRL_PIN(TEGRA_PIN_UART2_TXD_PC2, "UART2_TXD PC2"),
	PINCTRL_PIN(TEGRA_PIN_UART2_RXD_PC3, "UART2_RXD PC3"),
	PINCTRL_PIN(TEGRA_PIN_GEN1_I2C_SCL_PC4, "GEN1_I2C_SCL PC4"),
	PINCTRL_PIN(TEGRA_PIN_GEN1_I2C_SDA_PC5, "GEN1_I2C_SDA PC5"),
	PINCTRL_PIN(TEGRA_PIN_LCD_PWR2_PC6, "LCD_PWR2 PC6"),
	PINCTRL_PIN(TEGRA_PIN_GMI_WP_N_PC7, "GMI_WP_N PC7"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT5_PD0, "SDMMC3_DAT5 PD0"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT4_PD1, "SDMMC3_DAT4 PD1"),
	PINCTRL_PIN(TEGRA_PIN_LCD_DC1_PD2, "LCD_DC1 PD2"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT6_PD3, "SDMMC3_DAT6 PD3"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT7_PD4, "SDMMC3_DAT7 PD4"),
	PINCTRL_PIN(TEGRA_PIN_VI_D1_PD5, "VI_D1 PD5"),
	PINCTRL_PIN(TEGRA_PIN_VI_VSYNC_PD6, "VI_VSYNC PD6"),
	PINCTRL_PIN(TEGRA_PIN_VI_HSYNC_PD7, "VI_HSYNC PD7"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D0_PE0, "LCD_D0 PE0"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D1_PE1, "LCD_D1 PE1"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D2_PE2, "LCD_D2 PE2"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D3_PE3, "LCD_D3 PE3"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D4_PE4, "LCD_D4 PE4"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D5_PE5, "LCD_D5 PE5"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D6_PE6, "LCD_D6 PE6"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D7_PE7, "LCD_D7 PE7"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D8_PF0, "LCD_D8 PF0"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D9_PF1, "LCD_D9 PF1"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D10_PF2, "LCD_D10 PF2"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D11_PF3, "LCD_D11 PF3"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D12_PF4, "LCD_D12 PF4"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D13_PF5, "LCD_D13 PF5"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D14_PF6, "LCD_D14 PF6"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D15_PF7, "LCD_D15 PF7"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD0_PG0, "GMI_AD0 PG0"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD1_PG1, "GMI_AD1 PG1"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD2_PG2, "GMI_AD2 PG2"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD3_PG3, "GMI_AD3 PG3"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD4_PG4, "GMI_AD4 PG4"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD5_PG5, "GMI_AD5 PG5"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD6_PG6, "GMI_AD6 PG6"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD7_PG7, "GMI_AD7 PG7"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD8_PH0, "GMI_AD8 PH0"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD9_PH1, "GMI_AD9 PH1"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD10_PH2, "GMI_AD10 PH2"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD11_PH3, "GMI_AD11 PH3"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD12_PH4, "GMI_AD12 PH4"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD13_PH5, "GMI_AD13 PH5"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD14_PH6, "GMI_AD14 PH6"),
	PINCTRL_PIN(TEGRA_PIN_GMI_AD15_PH7, "GMI_AD15 PH7"),
	PINCTRL_PIN(TEGRA_PIN_GMI_WR_N_PI0, "GMI_WR_N PI0"),
	PINCTRL_PIN(TEGRA_PIN_GMI_OE_N_PI1, "GMI_OE_N PI1"),
	PINCTRL_PIN(TEGRA_PIN_GMI_DQS_PI2, "GMI_DQS PI2"),
	PINCTRL_PIN(TEGRA_PIN_GMI_CS6_N_PI3, "GMI_CS6_N PI3"),
	PINCTRL_PIN(TEGRA_PIN_GMI_RST_N_PI4, "GMI_RST_N PI4"),
	PINCTRL_PIN(TEGRA_PIN_GMI_IORDY_PI5, "GMI_IORDY PI5"),
	PINCTRL_PIN(TEGRA_PIN_GMI_CS7_N_PI6, "GMI_CS7_N PI6"),
	PINCTRL_PIN(TEGRA_PIN_GMI_WAIT_PI7, "GMI_WAIT PI7"),
	PINCTRL_PIN(TEGRA_PIN_GMI_CS0_N_PJ0, "GMI_CS0_N PJ0"),
	PINCTRL_PIN(TEGRA_PIN_LCD_DE_PJ1, "LCD_DE PJ1"),
	PINCTRL_PIN(TEGRA_PIN_GMI_CS1_N_PJ2, "GMI_CS1_N PJ2"),
	PINCTRL_PIN(TEGRA_PIN_LCD_HSYNC_PJ3, "LCD_HSYNC PJ3"),
	PINCTRL_PIN(TEGRA_PIN_LCD_VSYNC_PJ4, "LCD_VSYNC PJ4"),
	PINCTRL_PIN(TEGRA_PIN_UART2_CTS_N_PJ5, "UART2_CTS_N PJ5"),
	PINCTRL_PIN(TEGRA_PIN_UART2_RTS_N_PJ6, "UART2_RTS_N PJ6"),
	PINCTRL_PIN(TEGRA_PIN_GMI_A16_PJ7, "GMI_A16 PJ7"),
	PINCTRL_PIN(TEGRA_PIN_GMI_ADV_N_PK0, "GMI_ADV_N PK0"),
	PINCTRL_PIN(TEGRA_PIN_GMI_CLK_PK1, "GMI_CLK PK1"),
	PINCTRL_PIN(TEGRA_PIN_GMI_CS4_N_PK2, "GMI_CS4_N PK2"),
	PINCTRL_PIN(TEGRA_PIN_GMI_CS2_N_PK3, "GMI_CS2_N PK3"),
	PINCTRL_PIN(TEGRA_PIN_GMI_CS3_N_PK4, "GMI_CS3_N PK4"),
	PINCTRL_PIN(TEGRA_PIN_SPDIF_OUT_PK5, "SPDIF_OUT PK5"),
	PINCTRL_PIN(TEGRA_PIN_SPDIF_IN_PK6, "SPDIF_IN PK6"),
	PINCTRL_PIN(TEGRA_PIN_GMI_A19_PK7, "GMI_A19 PK7"),
	PINCTRL_PIN(TEGRA_PIN_VI_D2_PL0, "VI_D2 PL0"),
	PINCTRL_PIN(TEGRA_PIN_VI_D3_PL1, "VI_D3 PL1"),
	PINCTRL_PIN(TEGRA_PIN_VI_D4_PL2, "VI_D4 PL2"),
	PINCTRL_PIN(TEGRA_PIN_VI_D5_PL3, "VI_D5 PL3"),
	PINCTRL_PIN(TEGRA_PIN_VI_D6_PL4, "VI_D6 PL4"),
	PINCTRL_PIN(TEGRA_PIN_VI_D7_PL5, "VI_D7 PL5"),
	PINCTRL_PIN(TEGRA_PIN_VI_D8_PL6, "VI_D8 PL6"),
	PINCTRL_PIN(TEGRA_PIN_VI_D9_PL7, "VI_D9 PL7"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D16_PM0, "LCD_D16 PM0"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D17_PM1, "LCD_D17 PM1"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D18_PM2, "LCD_D18 PM2"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D19_PM3, "LCD_D19 PM3"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D20_PM4, "LCD_D20 PM4"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D21_PM5, "LCD_D21 PM5"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D22_PM6, "LCD_D22 PM6"),
	PINCTRL_PIN(TEGRA_PIN_LCD_D23_PM7, "LCD_D23 PM7"),
	PINCTRL_PIN(TEGRA_PIN_DAP1_FS_PN0, "DAP1_FS PN0"),
	PINCTRL_PIN(TEGRA_PIN_DAP1_DIN_PN1, "DAP1_DIN PN1"),
	PINCTRL_PIN(TEGRA_PIN_DAP1_DOUT_PN2, "DAP1_DOUT PN2"),
	PINCTRL_PIN(TEGRA_PIN_DAP1_SCLK_PN3, "DAP1_SCLK PN3"),
	PINCTRL_PIN(TEGRA_PIN_LCD_CS0_N_PN4, "LCD_CS0_N PN4"),
	PINCTRL_PIN(TEGRA_PIN_LCD_SDOUT_PN5, "LCD_SDOUT PN5"),
	PINCTRL_PIN(TEGRA_PIN_LCD_DC0_PN6, "LCD_DC0 PN6"),
	PINCTRL_PIN(TEGRA_PIN_HDMI_INT_PN7, "HDMI_INT PN7"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_DATA7_PO0, "ULPI_DATA7 PO0"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_DATA0_PO1, "ULPI_DATA0 PO1"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_DATA1_PO2, "ULPI_DATA1 PO2"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_DATA2_PO3, "ULPI_DATA2 PO3"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_DATA3_PO4, "ULPI_DATA3 PO4"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_DATA4_PO5, "ULPI_DATA4 PO5"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_DATA5_PO6, "ULPI_DATA5 PO6"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_DATA6_PO7, "ULPI_DATA6 PO7"),
	PINCTRL_PIN(TEGRA_PIN_DAP3_FS_PP0, "DAP3_FS PP0"),
	PINCTRL_PIN(TEGRA_PIN_DAP3_DIN_PP1, "DAP3_DIN PP1"),
	PINCTRL_PIN(TEGRA_PIN_DAP3_DOUT_PP2, "DAP3_DOUT PP2"),
	PINCTRL_PIN(TEGRA_PIN_DAP3_SCLK_PP3, "DAP3_SCLK PP3"),
	PINCTRL_PIN(TEGRA_PIN_DAP4_FS_PP4, "DAP4_FS PP4"),
	PINCTRL_PIN(TEGRA_PIN_DAP4_DIN_PP5, "DAP4_DIN PP5"),
	PINCTRL_PIN(TEGRA_PIN_DAP4_DOUT_PP6, "DAP4_DOUT PP6"),
	PINCTRL_PIN(TEGRA_PIN_DAP4_SCLK_PP7, "DAP4_SCLK PP7"),
	PINCTRL_PIN(TEGRA_PIN_KB_COL0_PQ0, "KB_COL0 PQ0"),
	PINCTRL_PIN(TEGRA_PIN_KB_COL1_PQ1, "KB_COL1 PQ1"),
	PINCTRL_PIN(TEGRA_PIN_KB_COL2_PQ2, "KB_COL2 PQ2"),
	PINCTRL_PIN(TEGRA_PIN_KB_COL3_PQ3, "KB_COL3 PQ3"),
	PINCTRL_PIN(TEGRA_PIN_KB_COL4_PQ4, "KB_COL4 PQ4"),
	PINCTRL_PIN(TEGRA_PIN_KB_COL5_PQ5, "KB_COL5 PQ5"),
	PINCTRL_PIN(TEGRA_PIN_KB_COL6_PQ6, "KB_COL6 PQ6"),
	PINCTRL_PIN(TEGRA_PIN_KB_COL7_PQ7, "KB_COL7 PQ7"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW0_PR0, "KB_ROW0 PR0"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW1_PR1, "KB_ROW1 PR1"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW2_PR2, "KB_ROW2 PR2"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW3_PR3, "KB_ROW3 PR3"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW4_PR4, "KB_ROW4 PR4"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW5_PR5, "KB_ROW5 PR5"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW6_PR6, "KB_ROW6 PR6"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW7_PR7, "KB_ROW7 PR7"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW8_PS0, "KB_ROW8 PS0"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW9_PS1, "KB_ROW9 PS1"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW10_PS2, "KB_ROW10 PS2"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW11_PS3, "KB_ROW11 PS3"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW12_PS4, "KB_ROW12 PS4"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW13_PS5, "KB_ROW13 PS5"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW14_PS6, "KB_ROW14 PS6"),
	PINCTRL_PIN(TEGRA_PIN_KB_ROW15_PS7, "KB_ROW15 PS7"),
	PINCTRL_PIN(TEGRA_PIN_VI_PCLK_PT0, "VI_PCLK PT0"),
	PINCTRL_PIN(TEGRA_PIN_VI_MCLK_PT1, "VI_MCLK PT1"),
	PINCTRL_PIN(TEGRA_PIN_VI_D10_PT2, "VI_D10 PT2"),
	PINCTRL_PIN(TEGRA_PIN_VI_D11_PT3, "VI_D11 PT3"),
	PINCTRL_PIN(TEGRA_PIN_VI_D0_PT4, "VI_D0 PT4"),
	PINCTRL_PIN(TEGRA_PIN_GEN2_I2C_SCL_PT5, "GEN2_I2C_SCL PT5"),
	PINCTRL_PIN(TEGRA_PIN_GEN2_I2C_SDA_PT6, "GEN2_I2C_SDA PT6"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_CMD_PT7, "SDMMC4_CMD PT7"),
	PINCTRL_PIN(TEGRA_PIN_PU0, "PU0"),
	PINCTRL_PIN(TEGRA_PIN_PU1, "PU1"),
	PINCTRL_PIN(TEGRA_PIN_PU2, "PU2"),
	PINCTRL_PIN(TEGRA_PIN_PU3, "PU3"),
	PINCTRL_PIN(TEGRA_PIN_PU4, "PU4"),
	PINCTRL_PIN(TEGRA_PIN_PU5, "PU5"),
	PINCTRL_PIN(TEGRA_PIN_PU6, "PU6"),
	PINCTRL_PIN(TEGRA_PIN_JTAG_RTCK_PU7, "JTAG_RTCK PU7"),
	PINCTRL_PIN(TEGRA_PIN_PV0, "PV0"),
	PINCTRL_PIN(TEGRA_PIN_PV1, "PV1"),
	PINCTRL_PIN(TEGRA_PIN_PV2, "PV2"),
	PINCTRL_PIN(TEGRA_PIN_PV3, "PV3"),
	PINCTRL_PIN(TEGRA_PIN_DDC_SCL_PV4, "DDC_SCL PV4"),
	PINCTRL_PIN(TEGRA_PIN_DDC_SDA_PV5, "DDC_SDA PV5"),
	PINCTRL_PIN(TEGRA_PIN_CRT_HSYNC_PV6, "CRT_HSYNC PV6"),
	PINCTRL_PIN(TEGRA_PIN_CRT_VSYNC_PV7, "CRT_VSYNC PV7"),
	PINCTRL_PIN(TEGRA_PIN_LCD_CS1_N_PW0, "LCD_CS1_N PW0"),
	PINCTRL_PIN(TEGRA_PIN_LCD_M1_PW1, "LCD_M1 PW1"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_CS1_N_PW2, "SPI2_CS1_N PW2"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_CS2_N_PW3, "SPI2_CS2_N PW3"),
	PINCTRL_PIN(TEGRA_PIN_CLK1_OUT_PW4, "CLK1_OUT PW4"),
	PINCTRL_PIN(TEGRA_PIN_CLK2_OUT_PW5, "CLK2_OUT PW5"),
	PINCTRL_PIN(TEGRA_PIN_UART3_TXD_PW6, "UART3_TXD PW6"),
	PINCTRL_PIN(TEGRA_PIN_UART3_RXD_PW7, "UART3_RXD PW7"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_MOSI_PX0, "SPI2_MOSI PX0"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_MISO_PX1, "SPI2_MISO PX1"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_SCK_PX2, "SPI2_SCK PX2"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_CS0_N_PX3, "SPI2_CS0_N PX3"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_MOSI_PX4, "SPI1_MOSI PX4"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_SCK_PX5, "SPI1_SCK PX5"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_CS0_N_PX6, "SPI1_CS0_N PX6"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_MISO_PX7, "SPI1_MISO PX7"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_CLK_PY0, "ULPI_CLK PY0"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_सूची_PY1, "ULPI_DIR PY1"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_NXT_PY2, "ULPI_NXT PY2"),
	PINCTRL_PIN(TEGRA_PIN_ULPI_STP_PY3, "ULPI_STP PY3"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_DAT3_PY4, "SDMMC1_DAT3 PY4"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_DAT2_PY5, "SDMMC1_DAT2 PY5"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_DAT1_PY6, "SDMMC1_DAT1 PY6"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_DAT0_PY7, "SDMMC1_DAT0 PY7"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_CLK_PZ0, "SDMMC1_CLK PZ0"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_CMD_PZ1, "SDMMC1_CMD PZ1"),
	PINCTRL_PIN(TEGRA_PIN_LCD_SDIN_PZ2, "LCD_SDIN PZ2"),
	PINCTRL_PIN(TEGRA_PIN_LCD_WR_N_PZ3, "LCD_WR_N PZ3"),
	PINCTRL_PIN(TEGRA_PIN_LCD_SCK_PZ4, "LCD_SCK PZ4"),
	PINCTRL_PIN(TEGRA_PIN_SYS_CLK_REQ_PZ5, "SYS_CLK_REQ PZ5"),
	PINCTRL_PIN(TEGRA_PIN_PWR_I2C_SCL_PZ6, "PWR_I2C_SCL PZ6"),
	PINCTRL_PIN(TEGRA_PIN_PWR_I2C_SDA_PZ7, "PWR_I2C_SDA PZ7"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_DAT0_PAA0, "SDMMC4_DAT0 PAA0"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_DAT1_PAA1, "SDMMC4_DAT1 PAA1"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_DAT2_PAA2, "SDMMC4_DAT2 PAA2"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_DAT3_PAA3, "SDMMC4_DAT3 PAA3"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_DAT4_PAA4, "SDMMC4_DAT4 PAA4"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_DAT5_PAA5, "SDMMC4_DAT5 PAA5"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_DAT6_PAA6, "SDMMC4_DAT6 PAA6"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_DAT7_PAA7, "SDMMC4_DAT7 PAA7"),
	PINCTRL_PIN(TEGRA_PIN_PBB0, "PBB0"),
	PINCTRL_PIN(TEGRA_PIN_CAM_I2C_SCL_PBB1, "CAM_I2C_SCL PBB1"),
	PINCTRL_PIN(TEGRA_PIN_CAM_I2C_SDA_PBB2, "CAM_I2C_SDA PBB2"),
	PINCTRL_PIN(TEGRA_PIN_PBB3, "PBB3"),
	PINCTRL_PIN(TEGRA_PIN_PBB4, "PBB4"),
	PINCTRL_PIN(TEGRA_PIN_PBB5, "PBB5"),
	PINCTRL_PIN(TEGRA_PIN_PBB6, "PBB6"),
	PINCTRL_PIN(TEGRA_PIN_PBB7, "PBB7"),
	PINCTRL_PIN(TEGRA_PIN_CAM_MCLK_PCC0, "CAM_MCLK PCC0"),
	PINCTRL_PIN(TEGRA_PIN_PCC1, "PCC1"),
	PINCTRL_PIN(TEGRA_PIN_PCC2, "PCC2"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_RST_N_PCC3, "SDMMC4_RST_N PCC3"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC4_CLK_PCC4, "SDMMC4_CLK PCC4"),
	PINCTRL_PIN(TEGRA_PIN_CLK2_REQ_PCC5, "CLK2_REQ PCC5"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L2_RST_N_PCC6, "PEX_L2_RST_N PCC6"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L2_CLKREQ_N_PCC7, "PEX_L2_CLKREQ_N PCC7"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L0_PRSNT_N_PDD0, "PEX_L0_PRSNT_N PDD0"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L0_RST_N_PDD1, "PEX_L0_RST_N PDD1"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L0_CLKREQ_N_PDD2, "PEX_L0_CLKREQ_N PDD2"),
	PINCTRL_PIN(TEGRA_PIN_PEX_WAKE_N_PDD3, "PEX_WAKE_N PDD3"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L1_PRSNT_N_PDD4, "PEX_L1_PRSNT_N PDD4"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L1_RST_N_PDD5, "PEX_L1_RST_N PDD5"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L1_CLKREQ_N_PDD6, "PEX_L1_CLKREQ_N PDD6"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L2_PRSNT_N_PDD7, "PEX_L2_PRSNT_N PDD7"),
	PINCTRL_PIN(TEGRA_PIN_CLK3_OUT_PEE0, "CLK3_OUT PEE0"),
	PINCTRL_PIN(TEGRA_PIN_CLK3_REQ_PEE1, "CLK3_REQ PEE1"),
	PINCTRL_PIN(TEGRA_PIN_CLK1_REQ_PEE2, "CLK1_REQ PEE2"),
	PINCTRL_PIN(TEGRA_PIN_HDMI_CEC_PEE3, "HDMI_CEC PEE3"),
	PINCTRL_PIN(TEGRA_PIN_PEE4, "PEE4"),
	PINCTRL_PIN(TEGRA_PIN_PEE5, "PEE5"),
	PINCTRL_PIN(TEGRA_PIN_PEE6, "PEE6"),
	PINCTRL_PIN(TEGRA_PIN_PEE7, "PEE7"),
	PINCTRL_PIN(TEGRA_PIN_CLK_32K_IN, "CLK_32K_IN"),
	PINCTRL_PIN(TEGRA_PIN_CORE_PWR_REQ, "CORE_PWR_REQ"),
	PINCTRL_PIN(TEGRA_PIN_CPU_PWR_REQ, "CPU_PWR_REQ"),
	PINCTRL_PIN(TEGRA_PIN_JTAG_TCK, "JTAG_TCK"),
	PINCTRL_PIN(TEGRA_PIN_JTAG_TDI, "JTAG_TDI"),
	PINCTRL_PIN(TEGRA_PIN_JTAG_TDO, "JTAG_TDO"),
	PINCTRL_PIN(TEGRA_PIN_JTAG_TMS, "JTAG_TMS"),
	PINCTRL_PIN(TEGRA_PIN_JTAG_TRST_N, "JTAG_TRST_N"),
	PINCTRL_PIN(TEGRA_PIN_OWR, "OWR"),
	PINCTRL_PIN(TEGRA_PIN_PWR_INT_N, "PWR_INT_N"),
	PINCTRL_PIN(TEGRA_PIN_SYS_RESET_N, "SYS_RESET_N"),
	PINCTRL_PIN(TEGRA_PIN_TEST_MODE_EN, "TEST_MODE_EN"),
पूर्ण;

अटल स्थिर अचिन्हित clk_32k_out_pa0_pins[] = अणु
	TEGRA_PIN_CLK_32K_OUT_PA0,
पूर्ण;

अटल स्थिर अचिन्हित uart3_cts_n_pa1_pins[] = अणु
	TEGRA_PIN_UART3_CTS_N_PA1,
पूर्ण;

अटल स्थिर अचिन्हित dap2_fs_pa2_pins[] = अणु
	TEGRA_PIN_DAP2_FS_PA2,
पूर्ण;

अटल स्थिर अचिन्हित dap2_sclk_pa3_pins[] = अणु
	TEGRA_PIN_DAP2_SCLK_PA3,
पूर्ण;

अटल स्थिर अचिन्हित dap2_din_pa4_pins[] = अणु
	TEGRA_PIN_DAP2_DIN_PA4,
पूर्ण;

अटल स्थिर अचिन्हित dap2_करोut_pa5_pins[] = अणु
	TEGRA_PIN_DAP2_DOUT_PA5,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_clk_pa6_pins[] = अणु
	TEGRA_PIN_SDMMC3_CLK_PA6,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_cmd_pa7_pins[] = अणु
	TEGRA_PIN_SDMMC3_CMD_PA7,
पूर्ण;

अटल स्थिर अचिन्हित gmi_a17_pb0_pins[] = अणु
	TEGRA_PIN_GMI_A17_PB0,
पूर्ण;

अटल स्थिर अचिन्हित gmi_a18_pb1_pins[] = अणु
	TEGRA_PIN_GMI_A18_PB1,
पूर्ण;

अटल स्थिर अचिन्हित lcd_pwr0_pb2_pins[] = अणु
	TEGRA_PIN_LCD_PWR0_PB2,
पूर्ण;

अटल स्थिर अचिन्हित lcd_pclk_pb3_pins[] = अणु
	TEGRA_PIN_LCD_PCLK_PB3,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat3_pb4_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT3_PB4,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat2_pb5_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT2_PB5,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat1_pb6_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT1_PB6,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat0_pb7_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT0_PB7,
पूर्ण;

अटल स्थिर अचिन्हित uart3_rts_n_pc0_pins[] = अणु
	TEGRA_PIN_UART3_RTS_N_PC0,
पूर्ण;

अटल स्थिर अचिन्हित lcd_pwr1_pc1_pins[] = अणु
	TEGRA_PIN_LCD_PWR1_PC1,
पूर्ण;

अटल स्थिर अचिन्हित uart2_txd_pc2_pins[] = अणु
	TEGRA_PIN_UART2_TXD_PC2,
पूर्ण;

अटल स्थिर अचिन्हित uart2_rxd_pc3_pins[] = अणु
	TEGRA_PIN_UART2_RXD_PC3,
पूर्ण;

अटल स्थिर अचिन्हित gen1_i2c_scl_pc4_pins[] = अणु
	TEGRA_PIN_GEN1_I2C_SCL_PC4,
पूर्ण;

अटल स्थिर अचिन्हित gen1_i2c_sda_pc5_pins[] = अणु
	TEGRA_PIN_GEN1_I2C_SDA_PC5,
पूर्ण;

अटल स्थिर अचिन्हित lcd_pwr2_pc6_pins[] = अणु
	TEGRA_PIN_LCD_PWR2_PC6,
पूर्ण;

अटल स्थिर अचिन्हित gmi_wp_n_pc7_pins[] = अणु
	TEGRA_PIN_GMI_WP_N_PC7,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat5_pd0_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT5_PD0,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat4_pd1_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT4_PD1,
पूर्ण;

अटल स्थिर अचिन्हित lcd_dc1_pd2_pins[] = अणु
	TEGRA_PIN_LCD_DC1_PD2,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat6_pd3_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT6_PD3,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat7_pd4_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT7_PD4,
पूर्ण;

अटल स्थिर अचिन्हित vi_d1_pd5_pins[] = अणु
	TEGRA_PIN_VI_D1_PD5,
पूर्ण;

अटल स्थिर अचिन्हित vi_vsync_pd6_pins[] = अणु
	TEGRA_PIN_VI_VSYNC_PD6,
पूर्ण;

अटल स्थिर अचिन्हित vi_hsync_pd7_pins[] = अणु
	TEGRA_PIN_VI_HSYNC_PD7,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d0_pe0_pins[] = अणु
	TEGRA_PIN_LCD_D0_PE0,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d1_pe1_pins[] = अणु
	TEGRA_PIN_LCD_D1_PE1,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d2_pe2_pins[] = अणु
	TEGRA_PIN_LCD_D2_PE2,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d3_pe3_pins[] = अणु
	TEGRA_PIN_LCD_D3_PE3,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d4_pe4_pins[] = अणु
	TEGRA_PIN_LCD_D4_PE4,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d5_pe5_pins[] = अणु
	TEGRA_PIN_LCD_D5_PE5,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d6_pe6_pins[] = अणु
	TEGRA_PIN_LCD_D6_PE6,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d7_pe7_pins[] = अणु
	TEGRA_PIN_LCD_D7_PE7,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d8_pf0_pins[] = अणु
	TEGRA_PIN_LCD_D8_PF0,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d9_pf1_pins[] = अणु
	TEGRA_PIN_LCD_D9_PF1,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d10_pf2_pins[] = अणु
	TEGRA_PIN_LCD_D10_PF2,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d11_pf3_pins[] = अणु
	TEGRA_PIN_LCD_D11_PF3,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d12_pf4_pins[] = अणु
	TEGRA_PIN_LCD_D12_PF4,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d13_pf5_pins[] = अणु
	TEGRA_PIN_LCD_D13_PF5,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d14_pf6_pins[] = अणु
	TEGRA_PIN_LCD_D14_PF6,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d15_pf7_pins[] = अणु
	TEGRA_PIN_LCD_D15_PF7,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad0_pg0_pins[] = अणु
	TEGRA_PIN_GMI_AD0_PG0,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad1_pg1_pins[] = अणु
	TEGRA_PIN_GMI_AD1_PG1,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad2_pg2_pins[] = अणु
	TEGRA_PIN_GMI_AD2_PG2,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad3_pg3_pins[] = अणु
	TEGRA_PIN_GMI_AD3_PG3,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad4_pg4_pins[] = अणु
	TEGRA_PIN_GMI_AD4_PG4,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad5_pg5_pins[] = अणु
	TEGRA_PIN_GMI_AD5_PG5,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad6_pg6_pins[] = अणु
	TEGRA_PIN_GMI_AD6_PG6,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad7_pg7_pins[] = अणु
	TEGRA_PIN_GMI_AD7_PG7,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad8_ph0_pins[] = अणु
	TEGRA_PIN_GMI_AD8_PH0,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad9_ph1_pins[] = अणु
	TEGRA_PIN_GMI_AD9_PH1,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad10_ph2_pins[] = अणु
	TEGRA_PIN_GMI_AD10_PH2,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad11_ph3_pins[] = अणु
	TEGRA_PIN_GMI_AD11_PH3,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad12_ph4_pins[] = अणु
	TEGRA_PIN_GMI_AD12_PH4,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad13_ph5_pins[] = अणु
	TEGRA_PIN_GMI_AD13_PH5,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad14_ph6_pins[] = अणु
	TEGRA_PIN_GMI_AD14_PH6,
पूर्ण;

अटल स्थिर अचिन्हित gmi_ad15_ph7_pins[] = अणु
	TEGRA_PIN_GMI_AD15_PH7,
पूर्ण;

अटल स्थिर अचिन्हित gmi_wr_n_pi0_pins[] = अणु
	TEGRA_PIN_GMI_WR_N_PI0,
पूर्ण;

अटल स्थिर अचिन्हित gmi_oe_n_pi1_pins[] = अणु
	TEGRA_PIN_GMI_OE_N_PI1,
पूर्ण;

अटल स्थिर अचिन्हित gmi_dqs_pi2_pins[] = अणु
	TEGRA_PIN_GMI_DQS_PI2,
पूर्ण;

अटल स्थिर अचिन्हित gmi_cs6_n_pi3_pins[] = अणु
	TEGRA_PIN_GMI_CS6_N_PI3,
पूर्ण;

अटल स्थिर अचिन्हित gmi_rst_n_pi4_pins[] = अणु
	TEGRA_PIN_GMI_RST_N_PI4,
पूर्ण;

अटल स्थिर अचिन्हित gmi_iordy_pi5_pins[] = अणु
	TEGRA_PIN_GMI_IORDY_PI5,
पूर्ण;

अटल स्थिर अचिन्हित gmi_cs7_n_pi6_pins[] = अणु
	TEGRA_PIN_GMI_CS7_N_PI6,
पूर्ण;

अटल स्थिर अचिन्हित gmi_रुको_pi7_pins[] = अणु
	TEGRA_PIN_GMI_WAIT_PI7,
पूर्ण;

अटल स्थिर अचिन्हित gmi_cs0_n_pj0_pins[] = अणु
	TEGRA_PIN_GMI_CS0_N_PJ0,
पूर्ण;

अटल स्थिर अचिन्हित lcd_de_pj1_pins[] = अणु
	TEGRA_PIN_LCD_DE_PJ1,
पूर्ण;

अटल स्थिर अचिन्हित gmi_cs1_n_pj2_pins[] = अणु
	TEGRA_PIN_GMI_CS1_N_PJ2,
पूर्ण;

अटल स्थिर अचिन्हित lcd_hsync_pj3_pins[] = अणु
	TEGRA_PIN_LCD_HSYNC_PJ3,
पूर्ण;

अटल स्थिर अचिन्हित lcd_vsync_pj4_pins[] = अणु
	TEGRA_PIN_LCD_VSYNC_PJ4,
पूर्ण;

अटल स्थिर अचिन्हित uart2_cts_n_pj5_pins[] = अणु
	TEGRA_PIN_UART2_CTS_N_PJ5,
पूर्ण;

अटल स्थिर अचिन्हित uart2_rts_n_pj6_pins[] = अणु
	TEGRA_PIN_UART2_RTS_N_PJ6,
पूर्ण;

अटल स्थिर अचिन्हित gmi_a16_pj7_pins[] = अणु
	TEGRA_PIN_GMI_A16_PJ7,
पूर्ण;

अटल स्थिर अचिन्हित gmi_adv_n_pk0_pins[] = अणु
	TEGRA_PIN_GMI_ADV_N_PK0,
पूर्ण;

अटल स्थिर अचिन्हित gmi_clk_pk1_pins[] = अणु
	TEGRA_PIN_GMI_CLK_PK1,
पूर्ण;

अटल स्थिर अचिन्हित gmi_cs4_n_pk2_pins[] = अणु
	TEGRA_PIN_GMI_CS4_N_PK2,
पूर्ण;

अटल स्थिर अचिन्हित gmi_cs2_n_pk3_pins[] = अणु
	TEGRA_PIN_GMI_CS2_N_PK3,
पूर्ण;

अटल स्थिर अचिन्हित gmi_cs3_n_pk4_pins[] = अणु
	TEGRA_PIN_GMI_CS3_N_PK4,
पूर्ण;

अटल स्थिर अचिन्हित spdअगर_out_pk5_pins[] = अणु
	TEGRA_PIN_SPDIF_OUT_PK5,
पूर्ण;

अटल स्थिर अचिन्हित spdअगर_in_pk6_pins[] = अणु
	TEGRA_PIN_SPDIF_IN_PK6,
पूर्ण;

अटल स्थिर अचिन्हित gmi_a19_pk7_pins[] = अणु
	TEGRA_PIN_GMI_A19_PK7,
पूर्ण;

अटल स्थिर अचिन्हित vi_d2_pl0_pins[] = अणु
	TEGRA_PIN_VI_D2_PL0,
पूर्ण;

अटल स्थिर अचिन्हित vi_d3_pl1_pins[] = अणु
	TEGRA_PIN_VI_D3_PL1,
पूर्ण;

अटल स्थिर अचिन्हित vi_d4_pl2_pins[] = अणु
	TEGRA_PIN_VI_D4_PL2,
पूर्ण;

अटल स्थिर अचिन्हित vi_d5_pl3_pins[] = अणु
	TEGRA_PIN_VI_D5_PL3,
पूर्ण;

अटल स्थिर अचिन्हित vi_d6_pl4_pins[] = अणु
	TEGRA_PIN_VI_D6_PL4,
पूर्ण;

अटल स्थिर अचिन्हित vi_d7_pl5_pins[] = अणु
	TEGRA_PIN_VI_D7_PL5,
पूर्ण;

अटल स्थिर अचिन्हित vi_d8_pl6_pins[] = अणु
	TEGRA_PIN_VI_D8_PL6,
पूर्ण;

अटल स्थिर अचिन्हित vi_d9_pl7_pins[] = अणु
	TEGRA_PIN_VI_D9_PL7,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d16_pm0_pins[] = अणु
	TEGRA_PIN_LCD_D16_PM0,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d17_pm1_pins[] = अणु
	TEGRA_PIN_LCD_D17_PM1,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d18_pm2_pins[] = अणु
	TEGRA_PIN_LCD_D18_PM2,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d19_pm3_pins[] = अणु
	TEGRA_PIN_LCD_D19_PM3,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d20_pm4_pins[] = अणु
	TEGRA_PIN_LCD_D20_PM4,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d21_pm5_pins[] = अणु
	TEGRA_PIN_LCD_D21_PM5,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d22_pm6_pins[] = अणु
	TEGRA_PIN_LCD_D22_PM6,
पूर्ण;

अटल स्थिर अचिन्हित lcd_d23_pm7_pins[] = अणु
	TEGRA_PIN_LCD_D23_PM7,
पूर्ण;

अटल स्थिर अचिन्हित dap1_fs_pn0_pins[] = अणु
	TEGRA_PIN_DAP1_FS_PN0,
पूर्ण;

अटल स्थिर अचिन्हित dap1_din_pn1_pins[] = अणु
	TEGRA_PIN_DAP1_DIN_PN1,
पूर्ण;

अटल स्थिर अचिन्हित dap1_करोut_pn2_pins[] = अणु
	TEGRA_PIN_DAP1_DOUT_PN2,
पूर्ण;

अटल स्थिर अचिन्हित dap1_sclk_pn3_pins[] = अणु
	TEGRA_PIN_DAP1_SCLK_PN3,
पूर्ण;

अटल स्थिर अचिन्हित lcd_cs0_n_pn4_pins[] = अणु
	TEGRA_PIN_LCD_CS0_N_PN4,
पूर्ण;

अटल स्थिर अचिन्हित lcd_sकरोut_pn5_pins[] = अणु
	TEGRA_PIN_LCD_SDOUT_PN5,
पूर्ण;

अटल स्थिर अचिन्हित lcd_dc0_pn6_pins[] = अणु
	TEGRA_PIN_LCD_DC0_PN6,
पूर्ण;

अटल स्थिर अचिन्हित hdmi_पूर्णांक_pn7_pins[] = अणु
	TEGRA_PIN_HDMI_INT_PN7,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_data7_po0_pins[] = अणु
	TEGRA_PIN_ULPI_DATA7_PO0,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_data0_po1_pins[] = अणु
	TEGRA_PIN_ULPI_DATA0_PO1,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_data1_po2_pins[] = अणु
	TEGRA_PIN_ULPI_DATA1_PO2,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_data2_po3_pins[] = अणु
	TEGRA_PIN_ULPI_DATA2_PO3,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_data3_po4_pins[] = अणु
	TEGRA_PIN_ULPI_DATA3_PO4,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_data4_po5_pins[] = अणु
	TEGRA_PIN_ULPI_DATA4_PO5,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_data5_po6_pins[] = अणु
	TEGRA_PIN_ULPI_DATA5_PO6,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_data6_po7_pins[] = अणु
	TEGRA_PIN_ULPI_DATA6_PO7,
पूर्ण;

अटल स्थिर अचिन्हित dap3_fs_pp0_pins[] = अणु
	TEGRA_PIN_DAP3_FS_PP0,
पूर्ण;

अटल स्थिर अचिन्हित dap3_din_pp1_pins[] = अणु
	TEGRA_PIN_DAP3_DIN_PP1,
पूर्ण;

अटल स्थिर अचिन्हित dap3_करोut_pp2_pins[] = अणु
	TEGRA_PIN_DAP3_DOUT_PP2,
पूर्ण;

अटल स्थिर अचिन्हित dap3_sclk_pp3_pins[] = अणु
	TEGRA_PIN_DAP3_SCLK_PP3,
पूर्ण;

अटल स्थिर अचिन्हित dap4_fs_pp4_pins[] = अणु
	TEGRA_PIN_DAP4_FS_PP4,
पूर्ण;

अटल स्थिर अचिन्हित dap4_din_pp5_pins[] = अणु
	TEGRA_PIN_DAP4_DIN_PP5,
पूर्ण;

अटल स्थिर अचिन्हित dap4_करोut_pp6_pins[] = अणु
	TEGRA_PIN_DAP4_DOUT_PP6,
पूर्ण;

अटल स्थिर अचिन्हित dap4_sclk_pp7_pins[] = अणु
	TEGRA_PIN_DAP4_SCLK_PP7,
पूर्ण;

अटल स्थिर अचिन्हित kb_col0_pq0_pins[] = अणु
	TEGRA_PIN_KB_COL0_PQ0,
पूर्ण;

अटल स्थिर अचिन्हित kb_col1_pq1_pins[] = अणु
	TEGRA_PIN_KB_COL1_PQ1,
पूर्ण;

अटल स्थिर अचिन्हित kb_col2_pq2_pins[] = अणु
	TEGRA_PIN_KB_COL2_PQ2,
पूर्ण;

अटल स्थिर अचिन्हित kb_col3_pq3_pins[] = अणु
	TEGRA_PIN_KB_COL3_PQ3,
पूर्ण;

अटल स्थिर अचिन्हित kb_col4_pq4_pins[] = अणु
	TEGRA_PIN_KB_COL4_PQ4,
पूर्ण;

अटल स्थिर अचिन्हित kb_col5_pq5_pins[] = अणु
	TEGRA_PIN_KB_COL5_PQ5,
पूर्ण;

अटल स्थिर अचिन्हित kb_col6_pq6_pins[] = अणु
	TEGRA_PIN_KB_COL6_PQ6,
पूर्ण;

अटल स्थिर अचिन्हित kb_col7_pq7_pins[] = अणु
	TEGRA_PIN_KB_COL7_PQ7,
पूर्ण;

अटल स्थिर अचिन्हित kb_row0_pr0_pins[] = अणु
	TEGRA_PIN_KB_ROW0_PR0,
पूर्ण;

अटल स्थिर अचिन्हित kb_row1_pr1_pins[] = अणु
	TEGRA_PIN_KB_ROW1_PR1,
पूर्ण;

अटल स्थिर अचिन्हित kb_row2_pr2_pins[] = अणु
	TEGRA_PIN_KB_ROW2_PR2,
पूर्ण;

अटल स्थिर अचिन्हित kb_row3_pr3_pins[] = अणु
	TEGRA_PIN_KB_ROW3_PR3,
पूर्ण;

अटल स्थिर अचिन्हित kb_row4_pr4_pins[] = अणु
	TEGRA_PIN_KB_ROW4_PR4,
पूर्ण;

अटल स्थिर अचिन्हित kb_row5_pr5_pins[] = अणु
	TEGRA_PIN_KB_ROW5_PR5,
पूर्ण;

अटल स्थिर अचिन्हित kb_row6_pr6_pins[] = अणु
	TEGRA_PIN_KB_ROW6_PR6,
पूर्ण;

अटल स्थिर अचिन्हित kb_row7_pr7_pins[] = अणु
	TEGRA_PIN_KB_ROW7_PR7,
पूर्ण;

अटल स्थिर अचिन्हित kb_row8_ps0_pins[] = अणु
	TEGRA_PIN_KB_ROW8_PS0,
पूर्ण;

अटल स्थिर अचिन्हित kb_row9_ps1_pins[] = अणु
	TEGRA_PIN_KB_ROW9_PS1,
पूर्ण;

अटल स्थिर अचिन्हित kb_row10_ps2_pins[] = अणु
	TEGRA_PIN_KB_ROW10_PS2,
पूर्ण;

अटल स्थिर अचिन्हित kb_row11_ps3_pins[] = अणु
	TEGRA_PIN_KB_ROW11_PS3,
पूर्ण;

अटल स्थिर अचिन्हित kb_row12_ps4_pins[] = अणु
	TEGRA_PIN_KB_ROW12_PS4,
पूर्ण;

अटल स्थिर अचिन्हित kb_row13_ps5_pins[] = अणु
	TEGRA_PIN_KB_ROW13_PS5,
पूर्ण;

अटल स्थिर अचिन्हित kb_row14_ps6_pins[] = अणु
	TEGRA_PIN_KB_ROW14_PS6,
पूर्ण;

अटल स्थिर अचिन्हित kb_row15_ps7_pins[] = अणु
	TEGRA_PIN_KB_ROW15_PS7,
पूर्ण;

अटल स्थिर अचिन्हित vi_pclk_pt0_pins[] = अणु
	TEGRA_PIN_VI_PCLK_PT0,
पूर्ण;

अटल स्थिर अचिन्हित vi_mclk_pt1_pins[] = अणु
	TEGRA_PIN_VI_MCLK_PT1,
पूर्ण;

अटल स्थिर अचिन्हित vi_d10_pt2_pins[] = अणु
	TEGRA_PIN_VI_D10_PT2,
पूर्ण;

अटल स्थिर अचिन्हित vi_d11_pt3_pins[] = अणु
	TEGRA_PIN_VI_D11_PT3,
पूर्ण;

अटल स्थिर अचिन्हित vi_d0_pt4_pins[] = अणु
	TEGRA_PIN_VI_D0_PT4,
पूर्ण;

अटल स्थिर अचिन्हित gen2_i2c_scl_pt5_pins[] = अणु
	TEGRA_PIN_GEN2_I2C_SCL_PT5,
पूर्ण;

अटल स्थिर अचिन्हित gen2_i2c_sda_pt6_pins[] = अणु
	TEGRA_PIN_GEN2_I2C_SDA_PT6,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_cmd_pt7_pins[] = अणु
	TEGRA_PIN_SDMMC4_CMD_PT7,
पूर्ण;

अटल स्थिर अचिन्हित pu0_pins[] = अणु
	TEGRA_PIN_PU0,
पूर्ण;

अटल स्थिर अचिन्हित pu1_pins[] = अणु
	TEGRA_PIN_PU1,
पूर्ण;

अटल स्थिर अचिन्हित pu2_pins[] = अणु
	TEGRA_PIN_PU2,
पूर्ण;

अटल स्थिर अचिन्हित pu3_pins[] = अणु
	TEGRA_PIN_PU3,
पूर्ण;

अटल स्थिर अचिन्हित pu4_pins[] = अणु
	TEGRA_PIN_PU4,
पूर्ण;

अटल स्थिर अचिन्हित pu5_pins[] = अणु
	TEGRA_PIN_PU5,
पूर्ण;

अटल स्थिर अचिन्हित pu6_pins[] = अणु
	TEGRA_PIN_PU6,
पूर्ण;

अटल स्थिर अचिन्हित jtag_rtck_pu7_pins[] = अणु
	TEGRA_PIN_JTAG_RTCK_PU7,
पूर्ण;

अटल स्थिर अचिन्हित pv0_pins[] = अणु
	TEGRA_PIN_PV0,
पूर्ण;

अटल स्थिर अचिन्हित pv1_pins[] = अणु
	TEGRA_PIN_PV1,
पूर्ण;

अटल स्थिर अचिन्हित pv2_pins[] = अणु
	TEGRA_PIN_PV2,
पूर्ण;

अटल स्थिर अचिन्हित pv3_pins[] = अणु
	TEGRA_PIN_PV3,
पूर्ण;

अटल स्थिर अचिन्हित ddc_scl_pv4_pins[] = अणु
	TEGRA_PIN_DDC_SCL_PV4,
पूर्ण;

अटल स्थिर अचिन्हित ddc_sda_pv5_pins[] = अणु
	TEGRA_PIN_DDC_SDA_PV5,
पूर्ण;

अटल स्थिर अचिन्हित crt_hsync_pv6_pins[] = अणु
	TEGRA_PIN_CRT_HSYNC_PV6,
पूर्ण;

अटल स्थिर अचिन्हित crt_vsync_pv7_pins[] = अणु
	TEGRA_PIN_CRT_VSYNC_PV7,
पूर्ण;

अटल स्थिर अचिन्हित lcd_cs1_n_pw0_pins[] = अणु
	TEGRA_PIN_LCD_CS1_N_PW0,
पूर्ण;

अटल स्थिर अचिन्हित lcd_m1_pw1_pins[] = अणु
	TEGRA_PIN_LCD_M1_PW1,
पूर्ण;

अटल स्थिर अचिन्हित spi2_cs1_n_pw2_pins[] = अणु
	TEGRA_PIN_SPI2_CS1_N_PW2,
पूर्ण;

अटल स्थिर अचिन्हित spi2_cs2_n_pw3_pins[] = अणु
	TEGRA_PIN_SPI2_CS2_N_PW3,
पूर्ण;

अटल स्थिर अचिन्हित clk1_out_pw4_pins[] = अणु
	TEGRA_PIN_CLK1_OUT_PW4,
पूर्ण;

अटल स्थिर अचिन्हित clk2_out_pw5_pins[] = अणु
	TEGRA_PIN_CLK2_OUT_PW5,
पूर्ण;

अटल स्थिर अचिन्हित uart3_txd_pw6_pins[] = अणु
	TEGRA_PIN_UART3_TXD_PW6,
पूर्ण;

अटल स्थिर अचिन्हित uart3_rxd_pw7_pins[] = अणु
	TEGRA_PIN_UART3_RXD_PW7,
पूर्ण;

अटल स्थिर अचिन्हित spi2_mosi_px0_pins[] = अणु
	TEGRA_PIN_SPI2_MOSI_PX0,
पूर्ण;

अटल स्थिर अचिन्हित spi2_miso_px1_pins[] = अणु
	TEGRA_PIN_SPI2_MISO_PX1,
पूर्ण;

अटल स्थिर अचिन्हित spi2_sck_px2_pins[] = अणु
	TEGRA_PIN_SPI2_SCK_PX2,
पूर्ण;

अटल स्थिर अचिन्हित spi2_cs0_n_px3_pins[] = अणु
	TEGRA_PIN_SPI2_CS0_N_PX3,
पूर्ण;

अटल स्थिर अचिन्हित spi1_mosi_px4_pins[] = अणु
	TEGRA_PIN_SPI1_MOSI_PX4,
पूर्ण;

अटल स्थिर अचिन्हित spi1_sck_px5_pins[] = अणु
	TEGRA_PIN_SPI1_SCK_PX5,
पूर्ण;

अटल स्थिर अचिन्हित spi1_cs0_n_px6_pins[] = अणु
	TEGRA_PIN_SPI1_CS0_N_PX6,
पूर्ण;

अटल स्थिर अचिन्हित spi1_miso_px7_pins[] = अणु
	TEGRA_PIN_SPI1_MISO_PX7,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_clk_py0_pins[] = अणु
	TEGRA_PIN_ULPI_CLK_PY0,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_dir_py1_pins[] = अणु
	TEGRA_PIN_ULPI_सूची_PY1,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_nxt_py2_pins[] = अणु
	TEGRA_PIN_ULPI_NXT_PY2,
पूर्ण;

अटल स्थिर अचिन्हित ulpi_stp_py3_pins[] = अणु
	TEGRA_PIN_ULPI_STP_PY3,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_dat3_py4_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT3_PY4,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_dat2_py5_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT2_PY5,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_dat1_py6_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT1_PY6,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_dat0_py7_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT0_PY7,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_clk_pz0_pins[] = अणु
	TEGRA_PIN_SDMMC1_CLK_PZ0,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_cmd_pz1_pins[] = अणु
	TEGRA_PIN_SDMMC1_CMD_PZ1,
पूर्ण;

अटल स्थिर अचिन्हित lcd_sdin_pz2_pins[] = अणु
	TEGRA_PIN_LCD_SDIN_PZ2,
पूर्ण;

अटल स्थिर अचिन्हित lcd_wr_n_pz3_pins[] = अणु
	TEGRA_PIN_LCD_WR_N_PZ3,
पूर्ण;

अटल स्थिर अचिन्हित lcd_sck_pz4_pins[] = अणु
	TEGRA_PIN_LCD_SCK_PZ4,
पूर्ण;

अटल स्थिर अचिन्हित sys_clk_req_pz5_pins[] = अणु
	TEGRA_PIN_SYS_CLK_REQ_PZ5,
पूर्ण;

अटल स्थिर अचिन्हित pwr_i2c_scl_pz6_pins[] = अणु
	TEGRA_PIN_PWR_I2C_SCL_PZ6,
पूर्ण;

अटल स्थिर अचिन्हित pwr_i2c_sda_pz7_pins[] = अणु
	TEGRA_PIN_PWR_I2C_SDA_PZ7,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_dat0_paa0_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT0_PAA0,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_dat1_paa1_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT1_PAA1,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_dat2_paa2_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT2_PAA2,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_dat3_paa3_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT3_PAA3,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_dat4_paa4_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT4_PAA4,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_dat5_paa5_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT5_PAA5,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_dat6_paa6_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT6_PAA6,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_dat7_paa7_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT7_PAA7,
पूर्ण;

अटल स्थिर अचिन्हित pbb0_pins[] = अणु
	TEGRA_PIN_PBB0,
पूर्ण;

अटल स्थिर अचिन्हित cam_i2c_scl_pbb1_pins[] = अणु
	TEGRA_PIN_CAM_I2C_SCL_PBB1,
पूर्ण;

अटल स्थिर अचिन्हित cam_i2c_sda_pbb2_pins[] = अणु
	TEGRA_PIN_CAM_I2C_SDA_PBB2,
पूर्ण;

अटल स्थिर अचिन्हित pbb3_pins[] = अणु
	TEGRA_PIN_PBB3,
पूर्ण;

अटल स्थिर अचिन्हित pbb4_pins[] = अणु
	TEGRA_PIN_PBB4,
पूर्ण;

अटल स्थिर अचिन्हित pbb5_pins[] = अणु
	TEGRA_PIN_PBB5,
पूर्ण;

अटल स्थिर अचिन्हित pbb6_pins[] = अणु
	TEGRA_PIN_PBB6,
पूर्ण;

अटल स्थिर अचिन्हित pbb7_pins[] = अणु
	TEGRA_PIN_PBB7,
पूर्ण;

अटल स्थिर अचिन्हित cam_mclk_pcc0_pins[] = अणु
	TEGRA_PIN_CAM_MCLK_PCC0,
पूर्ण;

अटल स्थिर अचिन्हित pcc1_pins[] = अणु
	TEGRA_PIN_PCC1,
पूर्ण;

अटल स्थिर अचिन्हित pcc2_pins[] = अणु
	TEGRA_PIN_PCC2,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_rst_n_pcc3_pins[] = अणु
	TEGRA_PIN_SDMMC4_RST_N_PCC3,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc4_clk_pcc4_pins[] = अणु
	TEGRA_PIN_SDMMC4_CLK_PCC4,
पूर्ण;

अटल स्थिर अचिन्हित clk2_req_pcc5_pins[] = अणु
	TEGRA_PIN_CLK2_REQ_PCC5,
पूर्ण;

अटल स्थिर अचिन्हित pex_l2_rst_n_pcc6_pins[] = अणु
	TEGRA_PIN_PEX_L2_RST_N_PCC6,
पूर्ण;

अटल स्थिर अचिन्हित pex_l2_clkreq_n_pcc7_pins[] = अणु
	TEGRA_PIN_PEX_L2_CLKREQ_N_PCC7,
पूर्ण;

अटल स्थिर अचिन्हित pex_l0_prsnt_n_pdd0_pins[] = अणु
	TEGRA_PIN_PEX_L0_PRSNT_N_PDD0,
पूर्ण;

अटल स्थिर अचिन्हित pex_l0_rst_n_pdd1_pins[] = अणु
	TEGRA_PIN_PEX_L0_RST_N_PDD1,
पूर्ण;

अटल स्थिर अचिन्हित pex_l0_clkreq_n_pdd2_pins[] = अणु
	TEGRA_PIN_PEX_L0_CLKREQ_N_PDD2,
पूर्ण;

अटल स्थिर अचिन्हित pex_wake_n_pdd3_pins[] = अणु
	TEGRA_PIN_PEX_WAKE_N_PDD3,
पूर्ण;

अटल स्थिर अचिन्हित pex_l1_prsnt_n_pdd4_pins[] = अणु
	TEGRA_PIN_PEX_L1_PRSNT_N_PDD4,
पूर्ण;

अटल स्थिर अचिन्हित pex_l1_rst_n_pdd5_pins[] = अणु
	TEGRA_PIN_PEX_L1_RST_N_PDD5,
पूर्ण;

अटल स्थिर अचिन्हित pex_l1_clkreq_n_pdd6_pins[] = अणु
	TEGRA_PIN_PEX_L1_CLKREQ_N_PDD6,
पूर्ण;

अटल स्थिर अचिन्हित pex_l2_prsnt_n_pdd7_pins[] = अणु
	TEGRA_PIN_PEX_L2_PRSNT_N_PDD7,
पूर्ण;

अटल स्थिर अचिन्हित clk3_out_pee0_pins[] = अणु
	TEGRA_PIN_CLK3_OUT_PEE0,
पूर्ण;

अटल स्थिर अचिन्हित clk3_req_pee1_pins[] = अणु
	TEGRA_PIN_CLK3_REQ_PEE1,
पूर्ण;

अटल स्थिर अचिन्हित clk1_req_pee2_pins[] = अणु
	TEGRA_PIN_CLK1_REQ_PEE2,
पूर्ण;

अटल स्थिर अचिन्हित hdmi_cec_pee3_pins[] = अणु
	TEGRA_PIN_HDMI_CEC_PEE3,
पूर्ण;

अटल स्थिर अचिन्हित clk_32k_in_pins[] = अणु
	TEGRA_PIN_CLK_32K_IN,
पूर्ण;

अटल स्थिर अचिन्हित core_pwr_req_pins[] = अणु
	TEGRA_PIN_CORE_PWR_REQ,
पूर्ण;

अटल स्थिर अचिन्हित cpu_pwr_req_pins[] = अणु
	TEGRA_PIN_CPU_PWR_REQ,
पूर्ण;

अटल स्थिर अचिन्हित owr_pins[] = अणु
	TEGRA_PIN_OWR,
पूर्ण;

अटल स्थिर अचिन्हित pwr_पूर्णांक_n_pins[] = अणु
	TEGRA_PIN_PWR_INT_N,
पूर्ण;

अटल स्थिर अचिन्हित drive_ao1_pins[] = अणु
	TEGRA_PIN_KB_ROW0_PR0,
	TEGRA_PIN_KB_ROW1_PR1,
	TEGRA_PIN_KB_ROW2_PR2,
	TEGRA_PIN_KB_ROW3_PR3,
	TEGRA_PIN_KB_ROW4_PR4,
	TEGRA_PIN_KB_ROW5_PR5,
	TEGRA_PIN_KB_ROW6_PR6,
	TEGRA_PIN_KB_ROW7_PR7,
	TEGRA_PIN_PWR_I2C_SCL_PZ6,
	TEGRA_PIN_PWR_I2C_SDA_PZ7,
	TEGRA_PIN_SYS_RESET_N,
पूर्ण;

अटल स्थिर अचिन्हित drive_ao2_pins[] = अणु
	TEGRA_PIN_CLK_32K_OUT_PA0,
	TEGRA_PIN_KB_COL0_PQ0,
	TEGRA_PIN_KB_COL1_PQ1,
	TEGRA_PIN_KB_COL2_PQ2,
	TEGRA_PIN_KB_COL3_PQ3,
	TEGRA_PIN_KB_COL4_PQ4,
	TEGRA_PIN_KB_COL5_PQ5,
	TEGRA_PIN_KB_COL6_PQ6,
	TEGRA_PIN_KB_COL7_PQ7,
	TEGRA_PIN_KB_ROW8_PS0,
	TEGRA_PIN_KB_ROW9_PS1,
	TEGRA_PIN_KB_ROW10_PS2,
	TEGRA_PIN_KB_ROW11_PS3,
	TEGRA_PIN_KB_ROW12_PS4,
	TEGRA_PIN_KB_ROW13_PS5,
	TEGRA_PIN_KB_ROW14_PS6,
	TEGRA_PIN_KB_ROW15_PS7,
	TEGRA_PIN_SYS_CLK_REQ_PZ5,
	TEGRA_PIN_CLK_32K_IN,
	TEGRA_PIN_CORE_PWR_REQ,
	TEGRA_PIN_CPU_PWR_REQ,
	TEGRA_PIN_PWR_INT_N,
पूर्ण;

अटल स्थिर अचिन्हित drive_at1_pins[] = अणु
	TEGRA_PIN_GMI_AD8_PH0,
	TEGRA_PIN_GMI_AD9_PH1,
	TEGRA_PIN_GMI_AD10_PH2,
	TEGRA_PIN_GMI_AD11_PH3,
	TEGRA_PIN_GMI_AD12_PH4,
	TEGRA_PIN_GMI_AD13_PH5,
	TEGRA_PIN_GMI_AD14_PH6,
	TEGRA_PIN_GMI_AD15_PH7,
	TEGRA_PIN_GMI_IORDY_PI5,
	TEGRA_PIN_GMI_CS7_N_PI6,
पूर्ण;

अटल स्थिर अचिन्हित drive_at2_pins[] = अणु
	TEGRA_PIN_GMI_AD0_PG0,
	TEGRA_PIN_GMI_AD1_PG1,
	TEGRA_PIN_GMI_AD2_PG2,
	TEGRA_PIN_GMI_AD3_PG3,
	TEGRA_PIN_GMI_AD4_PG4,
	TEGRA_PIN_GMI_AD5_PG5,
	TEGRA_PIN_GMI_AD6_PG6,
	TEGRA_PIN_GMI_AD7_PG7,
	TEGRA_PIN_GMI_WR_N_PI0,
	TEGRA_PIN_GMI_OE_N_PI1,
	TEGRA_PIN_GMI_DQS_PI2,
	TEGRA_PIN_GMI_CS6_N_PI3,
	TEGRA_PIN_GMI_RST_N_PI4,
	TEGRA_PIN_GMI_WAIT_PI7,
	TEGRA_PIN_GMI_ADV_N_PK0,
	TEGRA_PIN_GMI_CLK_PK1,
	TEGRA_PIN_GMI_CS4_N_PK2,
	TEGRA_PIN_GMI_CS2_N_PK3,
	TEGRA_PIN_GMI_CS3_N_PK4,
पूर्ण;

अटल स्थिर अचिन्हित drive_at3_pins[] = अणु
	TEGRA_PIN_GMI_WP_N_PC7,
	TEGRA_PIN_GMI_CS0_N_PJ0,
पूर्ण;

अटल स्थिर अचिन्हित drive_at4_pins[] = अणु
	TEGRA_PIN_GMI_A17_PB0,
	TEGRA_PIN_GMI_A18_PB1,
	TEGRA_PIN_GMI_CS1_N_PJ2,
	TEGRA_PIN_GMI_A16_PJ7,
	TEGRA_PIN_GMI_A19_PK7,
पूर्ण;

अटल स्थिर अचिन्हित drive_at5_pins[] = अणु
	TEGRA_PIN_GEN2_I2C_SCL_PT5,
	TEGRA_PIN_GEN2_I2C_SDA_PT6,
पूर्ण;

अटल स्थिर अचिन्हित drive_cdev1_pins[] = अणु
	TEGRA_PIN_CLK1_OUT_PW4,
	TEGRA_PIN_CLK1_REQ_PEE2,
पूर्ण;

अटल स्थिर अचिन्हित drive_cdev2_pins[] = अणु
	TEGRA_PIN_CLK2_OUT_PW5,
	TEGRA_PIN_CLK2_REQ_PCC5,
पूर्ण;

अटल स्थिर अचिन्हित drive_cec_pins[] = अणु
	TEGRA_PIN_HDMI_CEC_PEE3,
पूर्ण;

अटल स्थिर अचिन्हित drive_crt_pins[] = अणु
	TEGRA_PIN_CRT_HSYNC_PV6,
	TEGRA_PIN_CRT_VSYNC_PV7,
पूर्ण;

अटल स्थिर अचिन्हित drive_csus_pins[] = अणु
	TEGRA_PIN_VI_MCLK_PT1,
पूर्ण;

अटल स्थिर अचिन्हित drive_dap1_pins[] = अणु
	TEGRA_PIN_SPDIF_OUT_PK5,
	TEGRA_PIN_SPDIF_IN_PK6,
	TEGRA_PIN_DAP1_FS_PN0,
	TEGRA_PIN_DAP1_DIN_PN1,
	TEGRA_PIN_DAP1_DOUT_PN2,
	TEGRA_PIN_DAP1_SCLK_PN3,
पूर्ण;

अटल स्थिर अचिन्हित drive_dap2_pins[] = अणु
	TEGRA_PIN_DAP2_FS_PA2,
	TEGRA_PIN_DAP2_SCLK_PA3,
	TEGRA_PIN_DAP2_DIN_PA4,
	TEGRA_PIN_DAP2_DOUT_PA5,
पूर्ण;

अटल स्थिर अचिन्हित drive_dap3_pins[] = अणु
	TEGRA_PIN_DAP3_FS_PP0,
	TEGRA_PIN_DAP3_DIN_PP1,
	TEGRA_PIN_DAP3_DOUT_PP2,
	TEGRA_PIN_DAP3_SCLK_PP3,
पूर्ण;

अटल स्थिर अचिन्हित drive_dap4_pins[] = अणु
	TEGRA_PIN_DAP4_FS_PP4,
	TEGRA_PIN_DAP4_DIN_PP5,
	TEGRA_PIN_DAP4_DOUT_PP6,
	TEGRA_PIN_DAP4_SCLK_PP7,
पूर्ण;

अटल स्थिर अचिन्हित drive_dbg_pins[] = अणु
	TEGRA_PIN_GEN1_I2C_SCL_PC4,
	TEGRA_PIN_GEN1_I2C_SDA_PC5,
	TEGRA_PIN_PU0,
	TEGRA_PIN_PU1,
	TEGRA_PIN_PU2,
	TEGRA_PIN_PU3,
	TEGRA_PIN_PU4,
	TEGRA_PIN_PU5,
	TEGRA_PIN_PU6,
	TEGRA_PIN_JTAG_RTCK_PU7,
	TEGRA_PIN_JTAG_TCK,
	TEGRA_PIN_JTAG_TDI,
	TEGRA_PIN_JTAG_TDO,
	TEGRA_PIN_JTAG_TMS,
	TEGRA_PIN_JTAG_TRST_N,
	TEGRA_PIN_TEST_MODE_EN,
पूर्ण;

अटल स्थिर अचिन्हित drive_ddc_pins[] = अणु
	TEGRA_PIN_DDC_SCL_PV4,
	TEGRA_PIN_DDC_SDA_PV5,
पूर्ण;

अटल स्थिर अचिन्हित drive_dev3_pins[] = अणु
	TEGRA_PIN_CLK3_OUT_PEE0,
	TEGRA_PIN_CLK3_REQ_PEE1,
पूर्ण;

अटल स्थिर अचिन्हित drive_gma_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT0_PAA0,
	TEGRA_PIN_SDMMC4_DAT1_PAA1,
	TEGRA_PIN_SDMMC4_DAT2_PAA2,
	TEGRA_PIN_SDMMC4_DAT3_PAA3,
	TEGRA_PIN_SDMMC4_RST_N_PCC3,
पूर्ण;

अटल स्थिर अचिन्हित drive_gmb_pins[] = अणु
	TEGRA_PIN_SDMMC4_DAT4_PAA4,
	TEGRA_PIN_SDMMC4_DAT5_PAA5,
	TEGRA_PIN_SDMMC4_DAT6_PAA6,
	TEGRA_PIN_SDMMC4_DAT7_PAA7,
पूर्ण;

अटल स्थिर अचिन्हित drive_gmc_pins[] = अणु
	TEGRA_PIN_SDMMC4_CLK_PCC4,
पूर्ण;

अटल स्थिर अचिन्हित drive_gmd_pins[] = अणु
	TEGRA_PIN_SDMMC4_CMD_PT7,
पूर्ण;

अटल स्थिर अचिन्हित drive_gme_pins[] = अणु
	TEGRA_PIN_PBB0,
	TEGRA_PIN_CAM_I2C_SCL_PBB1,
	TEGRA_PIN_CAM_I2C_SDA_PBB2,
	TEGRA_PIN_PBB3,
	TEGRA_PIN_PCC2,
पूर्ण;

अटल स्थिर अचिन्हित drive_gmf_pins[] = अणु
	TEGRA_PIN_PBB4,
	TEGRA_PIN_PBB5,
	TEGRA_PIN_PBB6,
	TEGRA_PIN_PBB7,
पूर्ण;

अटल स्थिर अचिन्हित drive_gmg_pins[] = अणु
	TEGRA_PIN_CAM_MCLK_PCC0,
पूर्ण;

अटल स्थिर अचिन्हित drive_gmh_pins[] = अणु
	TEGRA_PIN_PCC1,
पूर्ण;

अटल स्थिर अचिन्हित drive_gpv_pins[] = अणु
	TEGRA_PIN_PEX_L2_RST_N_PCC6,
	TEGRA_PIN_PEX_L2_CLKREQ_N_PCC7,
	TEGRA_PIN_PEX_L0_PRSNT_N_PDD0,
	TEGRA_PIN_PEX_L0_RST_N_PDD1,
	TEGRA_PIN_PEX_L0_CLKREQ_N_PDD2,
	TEGRA_PIN_PEX_WAKE_N_PDD3,
	TEGRA_PIN_PEX_L1_PRSNT_N_PDD4,
	TEGRA_PIN_PEX_L1_RST_N_PDD5,
	TEGRA_PIN_PEX_L1_CLKREQ_N_PDD6,
	TEGRA_PIN_PEX_L2_PRSNT_N_PDD7,
पूर्ण;

अटल स्थिर अचिन्हित drive_lcd1_pins[] = अणु
	TEGRA_PIN_LCD_PWR1_PC1,
	TEGRA_PIN_LCD_PWR2_PC6,
	TEGRA_PIN_LCD_CS0_N_PN4,
	TEGRA_PIN_LCD_SDOUT_PN5,
	TEGRA_PIN_LCD_DC0_PN6,
	TEGRA_PIN_LCD_SDIN_PZ2,
	TEGRA_PIN_LCD_WR_N_PZ3,
	TEGRA_PIN_LCD_SCK_PZ4,
पूर्ण;

अटल स्थिर अचिन्हित drive_lcd2_pins[] = अणु
	TEGRA_PIN_LCD_PWR0_PB2,
	TEGRA_PIN_LCD_PCLK_PB3,
	TEGRA_PIN_LCD_DC1_PD2,
	TEGRA_PIN_LCD_D0_PE0,
	TEGRA_PIN_LCD_D1_PE1,
	TEGRA_PIN_LCD_D2_PE2,
	TEGRA_PIN_LCD_D3_PE3,
	TEGRA_PIN_LCD_D4_PE4,
	TEGRA_PIN_LCD_D5_PE5,
	TEGRA_PIN_LCD_D6_PE6,
	TEGRA_PIN_LCD_D7_PE7,
	TEGRA_PIN_LCD_D8_PF0,
	TEGRA_PIN_LCD_D9_PF1,
	TEGRA_PIN_LCD_D10_PF2,
	TEGRA_PIN_LCD_D11_PF3,
	TEGRA_PIN_LCD_D12_PF4,
	TEGRA_PIN_LCD_D13_PF5,
	TEGRA_PIN_LCD_D14_PF6,
	TEGRA_PIN_LCD_D15_PF7,
	TEGRA_PIN_LCD_DE_PJ1,
	TEGRA_PIN_LCD_HSYNC_PJ3,
	TEGRA_PIN_LCD_VSYNC_PJ4,
	TEGRA_PIN_LCD_D16_PM0,
	TEGRA_PIN_LCD_D17_PM1,
	TEGRA_PIN_LCD_D18_PM2,
	TEGRA_PIN_LCD_D19_PM3,
	TEGRA_PIN_LCD_D20_PM4,
	TEGRA_PIN_LCD_D21_PM5,
	TEGRA_PIN_LCD_D22_PM6,
	TEGRA_PIN_LCD_D23_PM7,
	TEGRA_PIN_HDMI_INT_PN7,
	TEGRA_PIN_LCD_CS1_N_PW0,
	TEGRA_PIN_LCD_M1_PW1,
पूर्ण;

अटल स्थिर अचिन्हित drive_owr_pins[] = अणु
	TEGRA_PIN_OWR,
पूर्ण;

अटल स्थिर अचिन्हित drive_sdio1_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT3_PY4,
	TEGRA_PIN_SDMMC1_DAT2_PY5,
	TEGRA_PIN_SDMMC1_DAT1_PY6,
	TEGRA_PIN_SDMMC1_DAT0_PY7,
	TEGRA_PIN_SDMMC1_CLK_PZ0,
	TEGRA_PIN_SDMMC1_CMD_PZ1,
पूर्ण;

अटल स्थिर अचिन्हित drive_sdio2_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT5_PD0,
	TEGRA_PIN_SDMMC3_DAT4_PD1,
	TEGRA_PIN_SDMMC3_DAT6_PD3,
	TEGRA_PIN_SDMMC3_DAT7_PD4,
पूर्ण;

अटल स्थिर अचिन्हित drive_sdio3_pins[] = अणु
	TEGRA_PIN_SDMMC3_CLK_PA6,
	TEGRA_PIN_SDMMC3_CMD_PA7,
	TEGRA_PIN_SDMMC3_DAT3_PB4,
	TEGRA_PIN_SDMMC3_DAT2_PB5,
	TEGRA_PIN_SDMMC3_DAT1_PB6,
	TEGRA_PIN_SDMMC3_DAT0_PB7,
पूर्ण;

अटल स्थिर अचिन्हित drive_spi_pins[] = अणु
	TEGRA_PIN_SPI2_CS1_N_PW2,
	TEGRA_PIN_SPI2_CS2_N_PW3,
	TEGRA_PIN_SPI2_MOSI_PX0,
	TEGRA_PIN_SPI2_MISO_PX1,
	TEGRA_PIN_SPI2_SCK_PX2,
	TEGRA_PIN_SPI2_CS0_N_PX3,
	TEGRA_PIN_SPI1_MOSI_PX4,
	TEGRA_PIN_SPI1_SCK_PX5,
	TEGRA_PIN_SPI1_CS0_N_PX6,
	TEGRA_PIN_SPI1_MISO_PX7,
पूर्ण;

अटल स्थिर अचिन्हित drive_uaa_pins[] = अणु
	TEGRA_PIN_ULPI_DATA0_PO1,
	TEGRA_PIN_ULPI_DATA1_PO2,
	TEGRA_PIN_ULPI_DATA2_PO3,
	TEGRA_PIN_ULPI_DATA3_PO4,
पूर्ण;

अटल स्थिर अचिन्हित drive_uab_pins[] = अणु
	TEGRA_PIN_ULPI_DATA7_PO0,
	TEGRA_PIN_ULPI_DATA4_PO5,
	TEGRA_PIN_ULPI_DATA5_PO6,
	TEGRA_PIN_ULPI_DATA6_PO7,
	TEGRA_PIN_PV0,
	TEGRA_PIN_PV1,
	TEGRA_PIN_PV2,
	TEGRA_PIN_PV3,
पूर्ण;

अटल स्थिर अचिन्हित drive_uart2_pins[] = अणु
	TEGRA_PIN_UART2_TXD_PC2,
	TEGRA_PIN_UART2_RXD_PC3,
	TEGRA_PIN_UART2_CTS_N_PJ5,
	TEGRA_PIN_UART2_RTS_N_PJ6,
पूर्ण;

अटल स्थिर अचिन्हित drive_uart3_pins[] = अणु
	TEGRA_PIN_UART3_CTS_N_PA1,
	TEGRA_PIN_UART3_RTS_N_PC0,
	TEGRA_PIN_UART3_TXD_PW6,
	TEGRA_PIN_UART3_RXD_PW7,
पूर्ण;

अटल स्थिर अचिन्हित drive_uda_pins[] = अणु
	TEGRA_PIN_ULPI_CLK_PY0,
	TEGRA_PIN_ULPI_सूची_PY1,
	TEGRA_PIN_ULPI_NXT_PY2,
	TEGRA_PIN_ULPI_STP_PY3,
पूर्ण;

अटल स्थिर अचिन्हित drive_vi1_pins[] = अणु
	TEGRA_PIN_VI_D1_PD5,
	TEGRA_PIN_VI_VSYNC_PD6,
	TEGRA_PIN_VI_HSYNC_PD7,
	TEGRA_PIN_VI_D2_PL0,
	TEGRA_PIN_VI_D3_PL1,
	TEGRA_PIN_VI_D4_PL2,
	TEGRA_PIN_VI_D5_PL3,
	TEGRA_PIN_VI_D6_PL4,
	TEGRA_PIN_VI_D7_PL5,
	TEGRA_PIN_VI_D8_PL6,
	TEGRA_PIN_VI_D9_PL7,
	TEGRA_PIN_VI_PCLK_PT0,
	TEGRA_PIN_VI_D10_PT2,
	TEGRA_PIN_VI_D11_PT3,
	TEGRA_PIN_VI_D0_PT4,
पूर्ण;

क्रमागत tegra_mux अणु
	TEGRA_MUX_BLINK,
	TEGRA_MUX_CEC,
	TEGRA_MUX_CLK_12M_OUT,
	TEGRA_MUX_CLK_32K_IN,
	TEGRA_MUX_CORE_PWR_REQ,
	TEGRA_MUX_CPU_PWR_REQ,
	TEGRA_MUX_CRT,
	TEGRA_MUX_DAP,
	TEGRA_MUX_DDR,
	TEGRA_MUX_DEV3,
	TEGRA_MUX_DISPLAYA,
	TEGRA_MUX_DISPLAYB,
	TEGRA_MUX_DTV,
	TEGRA_MUX_EXTPERIPH1,
	TEGRA_MUX_EXTPERIPH2,
	TEGRA_MUX_EXTPERIPH3,
	TEGRA_MUX_GMI,
	TEGRA_MUX_GMI_ALT,
	TEGRA_MUX_HDA,
	TEGRA_MUX_HDCP,
	TEGRA_MUX_HDMI,
	TEGRA_MUX_HSI,
	TEGRA_MUX_I2C1,
	TEGRA_MUX_I2C2,
	TEGRA_MUX_I2C3,
	TEGRA_MUX_I2C4,
	TEGRA_MUX_I2CPWR,
	TEGRA_MUX_I2S0,
	TEGRA_MUX_I2S1,
	TEGRA_MUX_I2S2,
	TEGRA_MUX_I2S3,
	TEGRA_MUX_I2S4,
	TEGRA_MUX_INVALID,
	TEGRA_MUX_KBC,
	TEGRA_MUX_MIO,
	TEGRA_MUX_न_अंकD,
	TEGRA_MUX_न_अंकD_ALT,
	TEGRA_MUX_OWR,
	TEGRA_MUX_PCIE,
	TEGRA_MUX_PWM0,
	TEGRA_MUX_PWM1,
	TEGRA_MUX_PWM2,
	TEGRA_MUX_PWM3,
	TEGRA_MUX_PWR_INT_N,
	TEGRA_MUX_RSVD1,
	TEGRA_MUX_RSVD2,
	TEGRA_MUX_RSVD3,
	TEGRA_MUX_RSVD4,
	TEGRA_MUX_RTCK,
	TEGRA_MUX_SATA,
	TEGRA_MUX_SDMMC1,
	TEGRA_MUX_SDMMC2,
	TEGRA_MUX_SDMMC3,
	TEGRA_MUX_SDMMC4,
	TEGRA_MUX_SPDIF,
	TEGRA_MUX_SPI1,
	TEGRA_MUX_SPI2,
	TEGRA_MUX_SPI2_ALT,
	TEGRA_MUX_SPI3,
	TEGRA_MUX_SPI4,
	TEGRA_MUX_SPI5,
	TEGRA_MUX_SPI6,
	TEGRA_MUX_SYSCLK,
	TEGRA_MUX_TEST,
	TEGRA_MUX_TRACE,
	TEGRA_MUX_UARTA,
	TEGRA_MUX_UARTB,
	TEGRA_MUX_UARTC,
	TEGRA_MUX_UARTD,
	TEGRA_MUX_UARTE,
	TEGRA_MUX_ULPI,
	TEGRA_MUX_VGP1,
	TEGRA_MUX_VGP2,
	TEGRA_MUX_VGP3,
	TEGRA_MUX_VGP4,
	TEGRA_MUX_VGP5,
	TEGRA_MUX_VGP6,
	TEGRA_MUX_VI,
	TEGRA_MUX_VI_ALT1,
	TEGRA_MUX_VI_ALT2,
	TEGRA_MUX_VI_ALT3,
पूर्ण;

#घोषणा FUNCTION(fname)					\
	अणु						\
		.name = #fname,				\
	पूर्ण

अटल काष्ठा tegra_function tegra30_functions[] = अणु
	FUNCTION(blink),
	FUNCTION(cec),
	FUNCTION(clk_12m_out),
	FUNCTION(clk_32k_in),
	FUNCTION(core_pwr_req),
	FUNCTION(cpu_pwr_req),
	FUNCTION(crt),
	FUNCTION(dap),
	FUNCTION(ddr),
	FUNCTION(dev3),
	FUNCTION(displaya),
	FUNCTION(displayb),
	FUNCTION(dtv),
	FUNCTION(extperiph1),
	FUNCTION(extperiph2),
	FUNCTION(extperiph3),
	FUNCTION(gmi),
	FUNCTION(gmi_alt),
	FUNCTION(hda),
	FUNCTION(hdcp),
	FUNCTION(hdmi),
	FUNCTION(hsi),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(i2c4),
	FUNCTION(i2cpwr),
	FUNCTION(i2s0),
	FUNCTION(i2s1),
	FUNCTION(i2s2),
	FUNCTION(i2s3),
	FUNCTION(i2s4),
	FUNCTION(invalid),
	FUNCTION(kbc),
	FUNCTION(mio),
	FUNCTION(nand),
	FUNCTION(nand_alt),
	FUNCTION(owr),
	FUNCTION(pcie),
	FUNCTION(pwm0),
	FUNCTION(pwm1),
	FUNCTION(pwm2),
	FUNCTION(pwm3),
	FUNCTION(pwr_पूर्णांक_n),
	FUNCTION(rsvd1),
	FUNCTION(rsvd2),
	FUNCTION(rsvd3),
	FUNCTION(rsvd4),
	FUNCTION(rtck),
	FUNCTION(sata),
	FUNCTION(sdmmc1),
	FUNCTION(sdmmc2),
	FUNCTION(sdmmc3),
	FUNCTION(sdmmc4),
	FUNCTION(spdअगर),
	FUNCTION(spi1),
	FUNCTION(spi2),
	FUNCTION(spi2_alt),
	FUNCTION(spi3),
	FUNCTION(spi4),
	FUNCTION(spi5),
	FUNCTION(spi6),
	FUNCTION(sysclk),
	FUNCTION(test),
	FUNCTION(trace),
	FUNCTION(uarta),
	FUNCTION(uartb),
	FUNCTION(uartc),
	FUNCTION(uartd),
	FUNCTION(uarte),
	FUNCTION(ulpi),
	FUNCTION(vgp1),
	FUNCTION(vgp2),
	FUNCTION(vgp3),
	FUNCTION(vgp4),
	FUNCTION(vgp5),
	FUNCTION(vgp6),
	FUNCTION(vi),
	FUNCTION(vi_alt1),
	FUNCTION(vi_alt2),
	FUNCTION(vi_alt3),
पूर्ण;

#घोषणा DRV_PINGROUP_REG_A		0x868	/* bank 0 */
#घोषणा PINGROUP_REG_A			0x3000	/* bank 1 */

#घोषणा DRV_PINGROUP_REG(r)		((r) - DRV_PINGROUP_REG_A)
#घोषणा PINGROUP_REG(r)			((r) - PINGROUP_REG_A)

#घोषणा PINGROUP_BIT_Y(b)		(b)
#घोषणा PINGROUP_BIT_N(b)		(-1)

#घोषणा PINGROUP(pg_name, f0, f1, f2, f3, r, od, ior)			\
	अणु								\
		.name = #pg_name,					\
		.pins = pg_name##_pins,					\
		.npins = ARRAY_SIZE(pg_name##_pins),			\
		.funcs = अणु						\
			TEGRA_MUX_##f0,					\
			TEGRA_MUX_##f1,					\
			TEGRA_MUX_##f2,					\
			TEGRA_MUX_##f3,					\
		पूर्ण,							\
		.mux_reg = PINGROUP_REG(r),				\
		.mux_bank = 1,						\
		.mux_bit = 0,						\
		.pupd_reg = PINGROUP_REG(r),				\
		.pupd_bank = 1,						\
		.pupd_bit = 2,						\
		.tri_reg = PINGROUP_REG(r),				\
		.tri_bank = 1,						\
		.tri_bit = 4,						\
		.einput_bit = 5,					\
		.odrain_bit = PINGROUP_BIT_##od(6),			\
		.lock_bit = 7,						\
		.ioreset_bit = PINGROUP_BIT_##ior(8),			\
		.rcv_sel_bit = -1,					\
		.drv_reg = -1,						\
		.parked_biपंचांगask = 0,					\
	पूर्ण

#घोषणा DRV_PINGROUP(pg_name, r, hsm_b, schmitt_b, lpmd_b, drvdn_b,	\
		     drvdn_w, drvup_b, drvup_w, slwr_b, slwr_w,		\
		     slwf_b, slwf_w)					\
	अणु								\
		.name = "drive_" #pg_name,				\
		.pins = drive_##pg_name##_pins,				\
		.npins = ARRAY_SIZE(drive_##pg_name##_pins),		\
		.mux_reg = -1,						\
		.pupd_reg = -1,						\
		.tri_reg = -1,						\
		.einput_bit = -1,					\
		.odrain_bit = -1,					\
		.lock_bit = -1,						\
		.ioreset_bit = -1,					\
		.rcv_sel_bit = -1,					\
		.drv_reg = DRV_PINGROUP_REG(r),				\
		.drv_bank = 0,						\
		.hsm_bit = hsm_b,					\
		.schmitt_bit = schmitt_b,				\
		.lpmd_bit = lpmd_b,					\
		.drvdn_bit = drvdn_b,					\
		.drvdn_width = drvdn_w,					\
		.drvup_bit = drvup_b,					\
		.drvup_width = drvup_w,					\
		.slwr_bit = slwr_b,					\
		.slwr_width = slwr_w,					\
		.slwf_bit = slwf_b,					\
		.slwf_width = slwf_w,					\
		.drvtype_bit = -1,					\
		.parked_biपंचांगask = 0,					\
	पूर्ण

अटल स्थिर काष्ठा tegra_pingroup tegra30_groups[] = अणु
	/*       pg_name,              f0,           f1,           f2,           f3,           r,      od, ior */
	PINGROUP(clk_32k_out_pa0,      BLINK,        RSVD2,        RSVD3,        RSVD4,        0x331c, N, N),
	PINGROUP(uart3_cts_n_pa1,      UARTC,        RSVD2,        GMI,          RSVD4,        0x317c, N, N),
	PINGROUP(dap2_fs_pa2,          I2S1,         HDA,          RSVD3,        GMI,          0x3358, N, N),
	PINGROUP(dap2_sclk_pa3,        I2S1,         HDA,          RSVD3,        GMI,          0x3364, N, N),
	PINGROUP(dap2_din_pa4,         I2S1,         HDA,          RSVD3,        GMI,          0x335c, N, N),
	PINGROUP(dap2_करोut_pa5,        I2S1,         HDA,          RSVD3,        GMI,          0x3360, N, N),
	PINGROUP(sdmmc3_clk_pa6,       UARTA,        PWM2,         SDMMC3,       SPI3,         0x3390, N, N),
	PINGROUP(sdmmc3_cmd_pa7,       UARTA,        PWM3,         SDMMC3,       SPI2,         0x3394, N, N),
	PINGROUP(gmi_a17_pb0,          UARTD,        SPI4,         GMI,          DTV,          0x3234, N, N),
	PINGROUP(gmi_a18_pb1,          UARTD,        SPI4,         GMI,          DTV,          0x3238, N, N),
	PINGROUP(lcd_pwr0_pb2,         DISPLAYA,     DISPLAYB,     SPI5,         HDCP,         0x3090, N, N),
	PINGROUP(lcd_pclk_pb3,         DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x3094, N, N),
	PINGROUP(sdmmc3_dat3_pb4,      RSVD1,        PWM0,         SDMMC3,       SPI3,         0x33a4, N, N),
	PINGROUP(sdmmc3_dat2_pb5,      RSVD1,        PWM1,         SDMMC3,       SPI3,         0x33a0, N, N),
	PINGROUP(sdmmc3_dat1_pb6,      RSVD1,        RSVD2,        SDMMC3,       SPI3,         0x339c, N, N),
	PINGROUP(sdmmc3_dat0_pb7,      RSVD1,        RSVD2,        SDMMC3,       SPI3,         0x3398, N, N),
	PINGROUP(uart3_rts_n_pc0,      UARTC,        PWM0,         GMI,          RSVD4,        0x3180, N, N),
	PINGROUP(lcd_pwr1_pc1,         DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x3070, N, N),
	PINGROUP(uart2_txd_pc2,        UARTB,        SPDIF,        UARTA,        SPI4,         0x3168, N, N),
	PINGROUP(uart2_rxd_pc3,        UARTB,        SPDIF,        UARTA,        SPI4,         0x3164, N, N),
	PINGROUP(gen1_i2c_scl_pc4,     I2C1,         RSVD2,        RSVD3,        RSVD4,        0x31a4, Y, N),
	PINGROUP(gen1_i2c_sda_pc5,     I2C1,         RSVD2,        RSVD3,        RSVD4,        0x31a0, Y, N),
	PINGROUP(lcd_pwr2_pc6,         DISPLAYA,     DISPLAYB,     SPI5,         HDCP,         0x3074, N, N),
	PINGROUP(gmi_wp_n_pc7,         RSVD1,        न_अंकD,         GMI,          GMI_ALT,      0x31c0, N, N),
	PINGROUP(sdmmc3_dat5_pd0,      PWM0,         SPI4,         SDMMC3,       SPI2,         0x33ac, N, N),
	PINGROUP(sdmmc3_dat4_pd1,      PWM1,         SPI4,         SDMMC3,       SPI2,         0x33a8, N, N),
	PINGROUP(lcd_dc1_pd2,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x310c, N, N),
	PINGROUP(sdmmc3_dat6_pd3,      SPDIF,        SPI4,         SDMMC3,       SPI2,         0x33b0, N, N),
	PINGROUP(sdmmc3_dat7_pd4,      SPDIF,        SPI4,         SDMMC3,       SPI2,         0x33b4, N, N),
	PINGROUP(vi_d1_pd5,            DDR,          SDMMC2,       VI,           RSVD4,        0x3128, N, Y),
	PINGROUP(vi_vsync_pd6,         DDR,          RSVD2,        VI,           RSVD4,        0x315c, N, Y),
	PINGROUP(vi_hsync_pd7,         DDR,          RSVD2,        VI,           RSVD4,        0x3160, N, Y),
	PINGROUP(lcd_d0_pe0,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30a4, N, N),
	PINGROUP(lcd_d1_pe1,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30a8, N, N),
	PINGROUP(lcd_d2_pe2,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30ac, N, N),
	PINGROUP(lcd_d3_pe3,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30b0, N, N),
	PINGROUP(lcd_d4_pe4,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30b4, N, N),
	PINGROUP(lcd_d5_pe5,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30b8, N, N),
	PINGROUP(lcd_d6_pe6,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30bc, N, N),
	PINGROUP(lcd_d7_pe7,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30c0, N, N),
	PINGROUP(lcd_d8_pf0,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30c4, N, N),
	PINGROUP(lcd_d9_pf1,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30c8, N, N),
	PINGROUP(lcd_d10_pf2,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30cc, N, N),
	PINGROUP(lcd_d11_pf3,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30d0, N, N),
	PINGROUP(lcd_d12_pf4,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30d4, N, N),
	PINGROUP(lcd_d13_pf5,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30d8, N, N),
	PINGROUP(lcd_d14_pf6,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30dc, N, N),
	PINGROUP(lcd_d15_pf7,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30e0, N, N),
	PINGROUP(gmi_ad0_pg0,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31f0, N, N),
	PINGROUP(gmi_ad1_pg1,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31f4, N, N),
	PINGROUP(gmi_ad2_pg2,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31f8, N, N),
	PINGROUP(gmi_ad3_pg3,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31fc, N, N),
	PINGROUP(gmi_ad4_pg4,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3200, N, N),
	PINGROUP(gmi_ad5_pg5,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3204, N, N),
	PINGROUP(gmi_ad6_pg6,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3208, N, N),
	PINGROUP(gmi_ad7_pg7,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x320c, N, N),
	PINGROUP(gmi_ad8_ph0,          PWM0,         न_अंकD,         GMI,          RSVD4,        0x3210, N, N),
	PINGROUP(gmi_ad9_ph1,          PWM1,         न_अंकD,         GMI,          RSVD4,        0x3214, N, N),
	PINGROUP(gmi_ad10_ph2,         PWM2,         न_अंकD,         GMI,          RSVD4,        0x3218, N, N),
	PINGROUP(gmi_ad11_ph3,         PWM3,         न_अंकD,         GMI,          RSVD4,        0x321c, N, N),
	PINGROUP(gmi_ad12_ph4,         RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3220, N, N),
	PINGROUP(gmi_ad13_ph5,         RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3224, N, N),
	PINGROUP(gmi_ad14_ph6,         RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3228, N, N),
	PINGROUP(gmi_ad15_ph7,         RSVD1,        न_अंकD,         GMI,          RSVD4,        0x322c, N, N),
	PINGROUP(gmi_wr_n_pi0,         RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3240, N, N),
	PINGROUP(gmi_oe_n_pi1,         RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3244, N, N),
	PINGROUP(gmi_dqs_pi2,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x3248, N, N),
	PINGROUP(gmi_cs6_n_pi3,        न_अंकD,         न_अंकD_ALT,     GMI,          SATA,         0x31e8, N, N),
	PINGROUP(gmi_rst_n_pi4,        न_अंकD,         न_अंकD_ALT,     GMI,          RSVD4,        0x324c, N, N),
	PINGROUP(gmi_iordy_pi5,        RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31c4, N, N),
	PINGROUP(gmi_cs7_n_pi6,        न_अंकD,         न_अंकD_ALT,     GMI,          GMI_ALT,      0x31ec, N, N),
	PINGROUP(gmi_रुको_pi7,         RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31c8, N, N),
	PINGROUP(gmi_cs0_n_pj0,        RSVD1,        न_अंकD,         GMI,          DTV,          0x31d4, N, N),
	PINGROUP(lcd_de_pj1,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x3098, N, N),
	PINGROUP(gmi_cs1_n_pj2,        RSVD1,        न_अंकD,         GMI,          DTV,          0x31d8, N, N),
	PINGROUP(lcd_hsync_pj3,        DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x309c, N, N),
	PINGROUP(lcd_vsync_pj4,        DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30a0, N, N),
	PINGROUP(uart2_cts_n_pj5,      UARTA,        UARTB,        GMI,          SPI4,         0x3170, N, N),
	PINGROUP(uart2_rts_n_pj6,      UARTA,        UARTB,        GMI,          SPI4,         0x316c, N, N),
	PINGROUP(gmi_a16_pj7,          UARTD,        SPI4,         GMI,          GMI_ALT,      0x3230, N, N),
	PINGROUP(gmi_adv_n_pk0,        RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31cc, N, N),
	PINGROUP(gmi_clk_pk1,          RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31d0, N, N),
	PINGROUP(gmi_cs4_n_pk2,        RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31e4, N, N),
	PINGROUP(gmi_cs2_n_pk3,        RSVD1,        न_अंकD,         GMI,          RSVD4,        0x31dc, N, N),
	PINGROUP(gmi_cs3_n_pk4,        RSVD1,        न_अंकD,         GMI,          GMI_ALT,      0x31e0, N, N),
	PINGROUP(spdअगर_out_pk5,        SPDIF,        RSVD2,        I2C1,         SDMMC2,       0x3354, N, N),
	PINGROUP(spdअगर_in_pk6,         SPDIF,        HDA,          I2C1,         SDMMC2,       0x3350, N, N),
	PINGROUP(gmi_a19_pk7,          UARTD,        SPI4,         GMI,          RSVD4,        0x323c, N, N),
	PINGROUP(vi_d2_pl0,            DDR,          SDMMC2,       VI,           RSVD4,        0x312c, N, Y),
	PINGROUP(vi_d3_pl1,            DDR,          SDMMC2,       VI,           RSVD4,        0x3130, N, Y),
	PINGROUP(vi_d4_pl2,            DDR,          SDMMC2,       VI,           RSVD4,        0x3134, N, Y),
	PINGROUP(vi_d5_pl3,            DDR,          SDMMC2,       VI,           RSVD4,        0x3138, N, Y),
	PINGROUP(vi_d6_pl4,            DDR,          SDMMC2,       VI,           RSVD4,        0x313c, N, Y),
	PINGROUP(vi_d7_pl5,            DDR,          SDMMC2,       VI,           RSVD4,        0x3140, N, Y),
	PINGROUP(vi_d8_pl6,            DDR,          SDMMC2,       VI,           RSVD4,        0x3144, N, Y),
	PINGROUP(vi_d9_pl7,            DDR,          SDMMC2,       VI,           RSVD4,        0x3148, N, Y),
	PINGROUP(lcd_d16_pm0,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30e4, N, N),
	PINGROUP(lcd_d17_pm1,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30e8, N, N),
	PINGROUP(lcd_d18_pm2,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30ec, N, N),
	PINGROUP(lcd_d19_pm3,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30f0, N, N),
	PINGROUP(lcd_d20_pm4,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30f4, N, N),
	PINGROUP(lcd_d21_pm5,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30f8, N, N),
	PINGROUP(lcd_d22_pm6,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x30fc, N, N),
	PINGROUP(lcd_d23_pm7,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x3100, N, N),
	PINGROUP(dap1_fs_pn0,          I2S0,         HDA,          GMI,          SDMMC2,       0x3338, N, N),
	PINGROUP(dap1_din_pn1,         I2S0,         HDA,          GMI,          SDMMC2,       0x333c, N, N),
	PINGROUP(dap1_करोut_pn2,        I2S0,         HDA,          GMI,          SDMMC2,       0x3340, N, N),
	PINGROUP(dap1_sclk_pn3,        I2S0,         HDA,          GMI,          SDMMC2,       0x3344, N, N),
	PINGROUP(lcd_cs0_n_pn4,        DISPLAYA,     DISPLAYB,     SPI5,         RSVD4,        0x3084, N, N),
	PINGROUP(lcd_sकरोut_pn5,        DISPLAYA,     DISPLAYB,     SPI5,         HDCP,         0x307c, N, N),
	PINGROUP(lcd_dc0_pn6,          DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x3088, N, N),
	PINGROUP(hdmi_पूर्णांक_pn7,         HDMI,         RSVD2,        RSVD3,        RSVD4,        0x3110, N, N),
	PINGROUP(ulpi_data7_po0,       SPI2,         HSI,          UARTA,        ULPI,         0x301c, N, N),
	PINGROUP(ulpi_data0_po1,       SPI3,         HSI,          UARTA,        ULPI,         0x3000, N, N),
	PINGROUP(ulpi_data1_po2,       SPI3,         HSI,          UARTA,        ULPI,         0x3004, N, N),
	PINGROUP(ulpi_data2_po3,       SPI3,         HSI,          UARTA,        ULPI,         0x3008, N, N),
	PINGROUP(ulpi_data3_po4,       SPI3,         HSI,          UARTA,        ULPI,         0x300c, N, N),
	PINGROUP(ulpi_data4_po5,       SPI2,         HSI,          UARTA,        ULPI,         0x3010, N, N),
	PINGROUP(ulpi_data5_po6,       SPI2,         HSI,          UARTA,        ULPI,         0x3014, N, N),
	PINGROUP(ulpi_data6_po7,       SPI2,         HSI,          UARTA,        ULPI,         0x3018, N, N),
	PINGROUP(dap3_fs_pp0,          I2S2,         RSVD2,        DISPLAYA,     DISPLAYB,     0x3030, N, N),
	PINGROUP(dap3_din_pp1,         I2S2,         RSVD2,        DISPLAYA,     DISPLAYB,     0x3034, N, N),
	PINGROUP(dap3_करोut_pp2,        I2S2,         RSVD2,        DISPLAYA,     DISPLAYB,     0x3038, N, N),
	PINGROUP(dap3_sclk_pp3,        I2S2,         RSVD2,        DISPLAYA,     DISPLAYB,     0x303c, N, N),
	PINGROUP(dap4_fs_pp4,          I2S3,         RSVD2,        GMI,          RSVD4,        0x31a8, N, N),
	PINGROUP(dap4_din_pp5,         I2S3,         RSVD2,        GMI,          RSVD4,        0x31ac, N, N),
	PINGROUP(dap4_करोut_pp6,        I2S3,         RSVD2,        GMI,          RSVD4,        0x31b0, N, N),
	PINGROUP(dap4_sclk_pp7,        I2S3,         RSVD2,        GMI,          RSVD4,        0x31b4, N, N),
	PINGROUP(kb_col0_pq0,          KBC,          न_अंकD,         TRACE,        TEST,         0x32fc, N, N),
	PINGROUP(kb_col1_pq1,          KBC,          न_अंकD,         TRACE,        TEST,         0x3300, N, N),
	PINGROUP(kb_col2_pq2,          KBC,          न_अंकD,         TRACE,        RSVD4,        0x3304, N, N),
	PINGROUP(kb_col3_pq3,          KBC,          न_अंकD,         TRACE,        RSVD4,        0x3308, N, N),
	PINGROUP(kb_col4_pq4,          KBC,          न_अंकD,         TRACE,        RSVD4,        0x330c, N, N),
	PINGROUP(kb_col5_pq5,          KBC,          न_अंकD,         TRACE,        RSVD4,        0x3310, N, N),
	PINGROUP(kb_col6_pq6,          KBC,          न_अंकD,         TRACE,        MIO,          0x3314, N, N),
	PINGROUP(kb_col7_pq7,          KBC,          न_अंकD,         TRACE,        MIO,          0x3318, N, N),
	PINGROUP(kb_row0_pr0,          KBC,          न_अंकD,         RSVD3,        RSVD4,        0x32bc, N, N),
	PINGROUP(kb_row1_pr1,          KBC,          न_अंकD,         RSVD3,        RSVD4,        0x32c0, N, N),
	PINGROUP(kb_row2_pr2,          KBC,          न_अंकD,         RSVD3,        RSVD4,        0x32c4, N, N),
	PINGROUP(kb_row3_pr3,          KBC,          न_अंकD,         RSVD3,        INVALID,      0x32c8, N, N),
	PINGROUP(kb_row4_pr4,          KBC,          न_अंकD,         TRACE,        RSVD4,        0x32cc, N, N),
	PINGROUP(kb_row5_pr5,          KBC,          न_अंकD,         TRACE,        OWR,          0x32d0, N, N),
	PINGROUP(kb_row6_pr6,          KBC,          न_अंकD,         SDMMC2,       MIO,          0x32d4, N, N),
	PINGROUP(kb_row7_pr7,          KBC,          न_अंकD,         SDMMC2,       MIO,          0x32d8, N, N),
	PINGROUP(kb_row8_ps0,          KBC,          न_अंकD,         SDMMC2,       MIO,          0x32dc, N, N),
	PINGROUP(kb_row9_ps1,          KBC,          न_अंकD,         SDMMC2,       MIO,          0x32e0, N, N),
	PINGROUP(kb_row10_ps2,         KBC,          न_अंकD,         SDMMC2,       MIO,          0x32e4, N, N),
	PINGROUP(kb_row11_ps3,         KBC,          न_अंकD,         SDMMC2,       MIO,          0x32e8, N, N),
	PINGROUP(kb_row12_ps4,         KBC,          न_अंकD,         SDMMC2,       MIO,          0x32ec, N, N),
	PINGROUP(kb_row13_ps5,         KBC,          न_अंकD,         SDMMC2,       MIO,          0x32f0, N, N),
	PINGROUP(kb_row14_ps6,         KBC,          न_अंकD,         SDMMC2,       MIO,          0x32f4, N, N),
	PINGROUP(kb_row15_ps7,         KBC,          न_अंकD,         SDMMC2,       MIO,          0x32f8, N, N),
	PINGROUP(vi_pclk_pt0,          RSVD1,        SDMMC2,       VI,           RSVD4,        0x3154, N, Y),
	PINGROUP(vi_mclk_pt1,          VI,           VI_ALT1,      VI_ALT2,      VI_ALT3,      0x3158, N, Y),
	PINGROUP(vi_d10_pt2,           DDR,          RSVD2,        VI,           RSVD4,        0x314c, N, Y),
	PINGROUP(vi_d11_pt3,           DDR,          RSVD2,        VI,           RSVD4,        0x3150, N, Y),
	PINGROUP(vi_d0_pt4,            DDR,          RSVD2,        VI,           RSVD4,        0x3124, N, Y),
	PINGROUP(gen2_i2c_scl_pt5,     I2C2,         HDCP,         GMI,          RSVD4,        0x3250, Y, N),
	PINGROUP(gen2_i2c_sda_pt6,     I2C2,         HDCP,         GMI,          RSVD4,        0x3254, Y, N),
	PINGROUP(sdmmc4_cmd_pt7,       I2C3,         न_अंकD,         GMI,          SDMMC4,       0x325c, N, Y),
	PINGROUP(pu0,                  OWR,          UARTA,        GMI,          RSVD4,        0x3184, N, N),
	PINGROUP(pu1,                  RSVD1,        UARTA,        GMI,          RSVD4,        0x3188, N, N),
	PINGROUP(pu2,                  RSVD1,        UARTA,        GMI,          RSVD4,        0x318c, N, N),
	PINGROUP(pu3,                  PWM0,         UARTA,        GMI,          RSVD4,        0x3190, N, N),
	PINGROUP(pu4,                  PWM1,         UARTA,        GMI,          RSVD4,        0x3194, N, N),
	PINGROUP(pu5,                  PWM2,         UARTA,        GMI,          RSVD4,        0x3198, N, N),
	PINGROUP(pu6,                  PWM3,         UARTA,        GMI,          RSVD4,        0x319c, N, N),
	PINGROUP(jtag_rtck_pu7,        RTCK,         RSVD2,        RSVD3,        RSVD4,        0x32b0, N, N),
	PINGROUP(pv0,                  RSVD1,        RSVD2,        RSVD3,        RSVD4,        0x3040, N, N),
	PINGROUP(pv1,                  RSVD1,        RSVD2,        RSVD3,        RSVD4,        0x3044, N, N),
	PINGROUP(pv2,                  OWR,          RSVD2,        RSVD3,        RSVD4,        0x3060, N, N),
	PINGROUP(pv3,                  CLK_12M_OUT,  RSVD2,        RSVD3,        RSVD4,        0x3064, N, N),
	PINGROUP(ddc_scl_pv4,          I2C4,         RSVD2,        RSVD3,        RSVD4,        0x3114, N, N),
	PINGROUP(ddc_sda_pv5,          I2C4,         RSVD2,        RSVD3,        RSVD4,        0x3118, N, N),
	PINGROUP(crt_hsync_pv6,        CRT,          RSVD2,        RSVD3,        RSVD4,        0x311c, N, N),
	PINGROUP(crt_vsync_pv7,        CRT,          RSVD2,        RSVD3,        RSVD4,        0x3120, N, N),
	PINGROUP(lcd_cs1_n_pw0,        DISPLAYA,     DISPLAYB,     SPI5,         RSVD4,        0x3104, N, N),
	PINGROUP(lcd_m1_pw1,           DISPLAYA,     DISPLAYB,     RSVD3,        RSVD4,        0x3108, N, N),
	PINGROUP(spi2_cs1_n_pw2,       SPI3,         SPI2,         SPI2_ALT,     I2C1,         0x3388, N, N),
	PINGROUP(spi2_cs2_n_pw3,       SPI3,         SPI2,         SPI2_ALT,     I2C1,         0x338c, N, N),
	PINGROUP(clk1_out_pw4,         EXTPERIPH1,   RSVD2,        RSVD3,        RSVD4,        0x334c, N, N),
	PINGROUP(clk2_out_pw5,         EXTPERIPH2,   RSVD2,        RSVD3,        RSVD4,        0x3068, N, N),
	PINGROUP(uart3_txd_pw6,        UARTC,        RSVD2,        GMI,          RSVD4,        0x3174, N, N),
	PINGROUP(uart3_rxd_pw7,        UARTC,        RSVD2,        GMI,          RSVD4,        0x3178, N, N),
	PINGROUP(spi2_mosi_px0,        SPI6,         SPI2,         SPI3,         GMI,          0x3368, N, N),
	PINGROUP(spi2_miso_px1,        SPI6,         SPI2,         SPI3,         GMI,          0x336c, N, N),
	PINGROUP(spi2_sck_px2,         SPI6,         SPI2,         SPI3,         GMI,          0x3374, N, N),
	PINGROUP(spi2_cs0_n_px3,       SPI6,         SPI2,         SPI3,         GMI,          0x3370, N, N),
	PINGROUP(spi1_mosi_px4,        SPI2,         SPI1,         SPI2_ALT,     GMI,          0x3378, N, N),
	PINGROUP(spi1_sck_px5,         SPI2,         SPI1,         SPI2_ALT,     GMI,          0x337c, N, N),
	PINGROUP(spi1_cs0_n_px6,       SPI2,         SPI1,         SPI2_ALT,     GMI,          0x3380, N, N),
	PINGROUP(spi1_miso_px7,        SPI3,         SPI1,         SPI2_ALT,     RSVD4,        0x3384, N, N),
	PINGROUP(ulpi_clk_py0,         SPI1,         RSVD2,        UARTD,        ULPI,         0x3020, N, N),
	PINGROUP(ulpi_dir_py1,         SPI1,         RSVD2,        UARTD,        ULPI,         0x3024, N, N),
	PINGROUP(ulpi_nxt_py2,         SPI1,         RSVD2,        UARTD,        ULPI,         0x3028, N, N),
	PINGROUP(ulpi_stp_py3,         SPI1,         RSVD2,        UARTD,        ULPI,         0x302c, N, N),
	PINGROUP(sdmmc1_dat3_py4,      SDMMC1,       RSVD2,        UARTE,        UARTA,        0x3050, N, N),
	PINGROUP(sdmmc1_dat2_py5,      SDMMC1,       RSVD2,        UARTE,        UARTA,        0x3054, N, N),
	PINGROUP(sdmmc1_dat1_py6,      SDMMC1,       RSVD2,        UARTE,        UARTA,        0x3058, N, N),
	PINGROUP(sdmmc1_dat0_py7,      SDMMC1,       RSVD2,        UARTE,        UARTA,        0x305c, N, N),
	PINGROUP(sdmmc1_clk_pz0,       SDMMC1,       RSVD2,        RSVD3,        UARTA,        0x3048, N, N),
	PINGROUP(sdmmc1_cmd_pz1,       SDMMC1,       RSVD2,        RSVD3,        UARTA,        0x304c, N, N),
	PINGROUP(lcd_sdin_pz2,         DISPLAYA,     DISPLAYB,     SPI5,         RSVD4,        0x3078, N, N),
	PINGROUP(lcd_wr_n_pz3,         DISPLAYA,     DISPLAYB,     SPI5,         HDCP,         0x3080, N, N),
	PINGROUP(lcd_sck_pz4,          DISPLAYA,     DISPLAYB,     SPI5,         HDCP,         0x308c, N, N),
	PINGROUP(sys_clk_req_pz5,      SYSCLK,       RSVD2,        RSVD3,        RSVD4,        0x3320, N, N),
	PINGROUP(pwr_i2c_scl_pz6,      I2CPWR,       RSVD2,        RSVD3,        RSVD4,        0x32b4, Y, N),
	PINGROUP(pwr_i2c_sda_pz7,      I2CPWR,       RSVD2,        RSVD3,        RSVD4,        0x32b8, Y, N),
	PINGROUP(sdmmc4_dat0_paa0,     UARTE,        SPI3,         GMI,          SDMMC4,       0x3260, N, Y),
	PINGROUP(sdmmc4_dat1_paa1,     UARTE,        SPI3,         GMI,          SDMMC4,       0x3264, N, Y),
	PINGROUP(sdmmc4_dat2_paa2,     UARTE,        SPI3,         GMI,          SDMMC4,       0x3268, N, Y),
	PINGROUP(sdmmc4_dat3_paa3,     UARTE,        SPI3,         GMI,          SDMMC4,       0x326c, N, Y),
	PINGROUP(sdmmc4_dat4_paa4,     I2C3,         I2S4,         GMI,          SDMMC4,       0x3270, N, Y),
	PINGROUP(sdmmc4_dat5_paa5,     VGP3,         I2S4,         GMI,          SDMMC4,       0x3274, N, Y),
	PINGROUP(sdmmc4_dat6_paa6,     VGP4,         I2S4,         GMI,          SDMMC4,       0x3278, N, Y),
	PINGROUP(sdmmc4_dat7_paa7,     VGP5,         I2S4,         GMI,          SDMMC4,       0x327c, N, Y),
	PINGROUP(pbb0,                 I2S4,         RSVD2,        RSVD3,        SDMMC4,       0x328c, N, N),
	PINGROUP(cam_i2c_scl_pbb1,     VGP1,         I2C3,         RSVD3,        SDMMC4,       0x3290, Y, N),
	PINGROUP(cam_i2c_sda_pbb2,     VGP2,         I2C3,         RSVD3,        SDMMC4,       0x3294, Y, N),
	PINGROUP(pbb3,                 VGP3,         DISPLAYA,     DISPLAYB,     SDMMC4,       0x3298, N, N),
	PINGROUP(pbb4,                 VGP4,         DISPLAYA,     DISPLAYB,     SDMMC4,       0x329c, N, N),
	PINGROUP(pbb5,                 VGP5,         DISPLAYA,     DISPLAYB,     SDMMC4,       0x32a0, N, N),
	PINGROUP(pbb6,                 VGP6,         DISPLAYA,     DISPLAYB,     SDMMC4,       0x32a4, N, N),
	PINGROUP(pbb7,                 I2S4,         RSVD2,        RSVD3,        SDMMC4,       0x32a8, N, N),
	PINGROUP(cam_mclk_pcc0,        VI,           VI_ALT1,      VI_ALT3,      SDMMC4,       0x3284, N, N),
	PINGROUP(pcc1,                 I2S4,         RSVD2,        RSVD3,        SDMMC4,       0x3288, N, N),
	PINGROUP(pcc2,                 I2S4,         RSVD2,        RSVD3,        RSVD4,        0x32ac, N, N),
	PINGROUP(sdmmc4_rst_n_pcc3,    VGP6,         RSVD2,        RSVD3,        SDMMC4,       0x3280, N, Y),
	PINGROUP(sdmmc4_clk_pcc4,      INVALID,      न_अंकD,         GMI,          SDMMC4,       0x3258, N, Y),
	PINGROUP(clk2_req_pcc5,        DAP,          RSVD2,        RSVD3,        RSVD4,        0x306c, N, N),
	PINGROUP(pex_l2_rst_n_pcc6,    PCIE,         HDA,          RSVD3,        RSVD4,        0x33d8, N, N),
	PINGROUP(pex_l2_clkreq_n_pcc7, PCIE,         HDA,          RSVD3,        RSVD4,        0x33dc, N, N),
	PINGROUP(pex_l0_prsnt_n_pdd0,  PCIE,         HDA,          RSVD3,        RSVD4,        0x33b8, N, N),
	PINGROUP(pex_l0_rst_n_pdd1,    PCIE,         HDA,          RSVD3,        RSVD4,        0x33bc, N, N),
	PINGROUP(pex_l0_clkreq_n_pdd2, PCIE,         HDA,          RSVD3,        RSVD4,        0x33c0, N, N),
	PINGROUP(pex_wake_n_pdd3,      PCIE,         HDA,          RSVD3,        RSVD4,        0x33c4, N, N),
	PINGROUP(pex_l1_prsnt_n_pdd4,  PCIE,         HDA,          RSVD3,        RSVD4,        0x33c8, N, N),
	PINGROUP(pex_l1_rst_n_pdd5,    PCIE,         HDA,          RSVD3,        RSVD4,        0x33cc, N, N),
	PINGROUP(pex_l1_clkreq_n_pdd6, PCIE,         HDA,          RSVD3,        RSVD4,        0x33d0, N, N),
	PINGROUP(pex_l2_prsnt_n_pdd7,  PCIE,         HDA,          RSVD3,        RSVD4,        0x33d4, N, N),
	PINGROUP(clk3_out_pee0,        EXTPERIPH3,   RSVD2,        RSVD3,        RSVD4,        0x31b8, N, N),
	PINGROUP(clk3_req_pee1,        DEV3,         RSVD2,        RSVD3,        RSVD4,        0x31bc, N, N),
	PINGROUP(clk1_req_pee2,        DAP,          HDA,          RSVD3,        RSVD4,        0x3348, N, N),
	PINGROUP(hdmi_cec_pee3,        CEC,          RSVD2,        RSVD3,        RSVD4,        0x33e0, Y, N),
	PINGROUP(clk_32k_in,           CLK_32K_IN,   RSVD2,        RSVD3,        RSVD4,        0x3330, N, N),
	PINGROUP(core_pwr_req,         CORE_PWR_REQ, RSVD2,        RSVD3,        RSVD4,        0x3324, N, N),
	PINGROUP(cpu_pwr_req,          CPU_PWR_REQ,  RSVD2,        RSVD3,        RSVD4,        0x3328, N, N),
	PINGROUP(owr,                  OWR,          CEC,          RSVD3,        RSVD4,        0x3334, N, N),
	PINGROUP(pwr_पूर्णांक_n,            PWR_INT_N,    RSVD2,        RSVD3,        RSVD4,        0x332c, N, N),
	/* pg_name, r, hsm_b, schmitt_b, lpmd_b, drvdn_b, drvdn_w, drvup_b, drvup_w, slwr_b, slwr_w, slwf_b, slwf_w */
	DRV_PINGROUP(ao1,   0x868,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(ao2,   0x86c,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(at1,   0x870,  2,  3,  4,  14,  5,  19,  5,  24,  2,  28,  2),
	DRV_PINGROUP(at2,   0x874,  2,  3,  4,  14,  5,  19,  5,  24,  2,  28,  2),
	DRV_PINGROUP(at3,   0x878,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2),
	DRV_PINGROUP(at4,   0x87c,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2),
	DRV_PINGROUP(at5,   0x880,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2),
	DRV_PINGROUP(cdev1, 0x884,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(cdev2, 0x888,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(cec,   0x938,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(crt,   0x8f8,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(csus,  0x88c, -1, -1, -1,  12,  5,  19,  5,  24,  4,  28,  4),
	DRV_PINGROUP(dap1,  0x890,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(dap2,  0x894,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(dap3,  0x898,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(dap4,  0x89c,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(dbg,   0x8a0,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(ddc,   0x8fc,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(dev3,  0x92c,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(gma,   0x900, -1, -1, -1,  14,  5,  19,  5,  24,  4,  28,  4),
	DRV_PINGROUP(gmb,   0x904, -1, -1, -1,  14,  5,  19,  5,  24,  4,  28,  4),
	DRV_PINGROUP(gmc,   0x908, -1, -1, -1,  14,  5,  19,  5,  24,  4,  28,  4),
	DRV_PINGROUP(gmd,   0x90c, -1, -1, -1,  14,  5,  19,  5,  24,  4,  28,  4),
	DRV_PINGROUP(gme,   0x910,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2),
	DRV_PINGROUP(gmf,   0x914,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2),
	DRV_PINGROUP(gmg,   0x918,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2),
	DRV_PINGROUP(gmh,   0x91c,  2,  3,  4,  14,  5,  19,  5,  28,  2,  30,  2),
	DRV_PINGROUP(gpv,   0x928,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(lcd1,  0x8a4,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(lcd2,  0x8a8,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(owr,   0x920,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(sdio1, 0x8ec,  2,  3, -1,  12,  7,  20,  7,  28,  2,  30,  2),
	DRV_PINGROUP(sdio2, 0x8ac,  2,  3, -1,  12,  7,  20,  7,  28,  2,  30,  2),
	DRV_PINGROUP(sdio3, 0x8b0,  2,  3, -1,  12,  7,  20,  7,  28,  2,  30,  2),
	DRV_PINGROUP(spi,   0x8b4,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(uaa,   0x8b8,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(uab,   0x8bc,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(uart2, 0x8c0,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(uart3, 0x8c4,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(uda,   0x924,  2,  3,  4,  12,  5,  20,  5,  28,  2,  30,  2),
	DRV_PINGROUP(vi1,   0x8c8, -1, -1, -1,  14,  5,  19,  5,  24,  4,  28,  4),
पूर्ण;

अटल स्थिर काष्ठा tegra_pinctrl_soc_data tegra30_pinctrl = अणु
	.ngpios = NUM_GPIOS,
	.gpio_compatible = "nvidia,tegra30-gpio",
	.pins = tegra30_pins,
	.npins = ARRAY_SIZE(tegra30_pins),
	.functions = tegra30_functions,
	.nfunctions = ARRAY_SIZE(tegra30_functions),
	.groups = tegra30_groups,
	.ngroups = ARRAY_SIZE(tegra30_groups),
	.hsm_in_mux = false,
	.schmitt_in_mux = false,
	.drvtype_in_mux = false,
पूर्ण;

अटल पूर्णांक tegra30_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस tegra_pinctrl_probe(pdev, &tegra30_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra30_pinctrl_of_match[] = अणु
	अणु .compatible = "nvidia,tegra30-pinmux", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra30_pinctrl_driver = अणु
	.driver = अणु
		.name = "tegra30-pinctrl",
		.of_match_table = tegra30_pinctrl_of_match,
	पूर्ण,
	.probe = tegra30_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init tegra30_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tegra30_pinctrl_driver);
पूर्ण
arch_initcall(tegra30_pinctrl_init);
