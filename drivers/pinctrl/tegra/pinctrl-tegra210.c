<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinctrl data क्रम the NVIDIA Tegra210 pinmux
 *
 * Copyright (c) 2015, NVIDIA CORPORATION.  All rights reserved.
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
#घोषणा _GPIO(offset)				(offset)

#घोषणा TEGRA_PIN_PEX_L0_RST_N_PA0		_GPIO(0)
#घोषणा TEGRA_PIN_PEX_L0_CLKREQ_N_PA1		_GPIO(1)
#घोषणा TEGRA_PIN_PEX_WAKE_N_PA2		_GPIO(2)
#घोषणा TEGRA_PIN_PEX_L1_RST_N_PA3		_GPIO(3)
#घोषणा TEGRA_PIN_PEX_L1_CLKREQ_N_PA4		_GPIO(4)
#घोषणा TEGRA_PIN_SATA_LED_ACTIVE_PA5		_GPIO(5)
#घोषणा TEGRA_PIN_PA6				_GPIO(6)
#घोषणा TEGRA_PIN_DAP1_FS_PB0			_GPIO(8)
#घोषणा TEGRA_PIN_DAP1_DIN_PB1			_GPIO(9)
#घोषणा TEGRA_PIN_DAP1_DOUT_PB2			_GPIO(10)
#घोषणा TEGRA_PIN_DAP1_SCLK_PB3			_GPIO(11)
#घोषणा TEGRA_PIN_SPI2_MOSI_PB4			_GPIO(12)
#घोषणा TEGRA_PIN_SPI2_MISO_PB5			_GPIO(13)
#घोषणा TEGRA_PIN_SPI2_SCK_PB6			_GPIO(14)
#घोषणा TEGRA_PIN_SPI2_CS0_PB7			_GPIO(15)
#घोषणा TEGRA_PIN_SPI1_MOSI_PC0			_GPIO(16)
#घोषणा TEGRA_PIN_SPI1_MISO_PC1			_GPIO(17)
#घोषणा TEGRA_PIN_SPI1_SCK_PC2			_GPIO(18)
#घोषणा TEGRA_PIN_SPI1_CS0_PC3			_GPIO(19)
#घोषणा TEGRA_PIN_SPI1_CS1_PC4			_GPIO(20)
#घोषणा TEGRA_PIN_SPI4_SCK_PC5			_GPIO(21)
#घोषणा TEGRA_PIN_SPI4_CS0_PC6			_GPIO(22)
#घोषणा TEGRA_PIN_SPI4_MOSI_PC7			_GPIO(23)
#घोषणा TEGRA_PIN_SPI4_MISO_PD0			_GPIO(24)
#घोषणा TEGRA_PIN_UART3_TX_PD1			_GPIO(25)
#घोषणा TEGRA_PIN_UART3_RX_PD2			_GPIO(26)
#घोषणा TEGRA_PIN_UART3_RTS_PD3			_GPIO(27)
#घोषणा TEGRA_PIN_UART3_CTS_PD4			_GPIO(28)
#घोषणा TEGRA_PIN_DMIC1_CLK_PE0			_GPIO(32)
#घोषणा TEGRA_PIN_DMIC1_DAT_PE1			_GPIO(33)
#घोषणा TEGRA_PIN_DMIC2_CLK_PE2			_GPIO(34)
#घोषणा TEGRA_PIN_DMIC2_DAT_PE3			_GPIO(35)
#घोषणा TEGRA_PIN_DMIC3_CLK_PE4			_GPIO(36)
#घोषणा TEGRA_PIN_DMIC3_DAT_PE5			_GPIO(37)
#घोषणा TEGRA_PIN_PE6				_GPIO(38)
#घोषणा TEGRA_PIN_PE7				_GPIO(39)
#घोषणा TEGRA_PIN_GEN3_I2C_SCL_PF0		_GPIO(40)
#घोषणा TEGRA_PIN_GEN3_I2C_SDA_PF1		_GPIO(41)
#घोषणा TEGRA_PIN_UART2_TX_PG0			_GPIO(48)
#घोषणा TEGRA_PIN_UART2_RX_PG1			_GPIO(49)
#घोषणा TEGRA_PIN_UART2_RTS_PG2			_GPIO(50)
#घोषणा TEGRA_PIN_UART2_CTS_PG3			_GPIO(51)
#घोषणा TEGRA_PIN_WIFI_EN_PH0			_GPIO(56)
#घोषणा TEGRA_PIN_WIFI_RST_PH1			_GPIO(57)
#घोषणा TEGRA_PIN_WIFI_WAKE_AP_PH2		_GPIO(58)
#घोषणा TEGRA_PIN_AP_WAKE_BT_PH3		_GPIO(59)
#घोषणा TEGRA_PIN_BT_RST_PH4			_GPIO(60)
#घोषणा TEGRA_PIN_BT_WAKE_AP_PH5		_GPIO(61)
#घोषणा TEGRA_PIN_PH6				_GPIO(62)
#घोषणा TEGRA_PIN_AP_WAKE_NFC_PH7		_GPIO(63)
#घोषणा TEGRA_PIN_NFC_EN_PI0			_GPIO(64)
#घोषणा TEGRA_PIN_NFC_INT_PI1			_GPIO(65)
#घोषणा TEGRA_PIN_GPS_EN_PI2			_GPIO(66)
#घोषणा TEGRA_PIN_GPS_RST_PI3			_GPIO(67)
#घोषणा TEGRA_PIN_UART4_TX_PI4			_GPIO(68)
#घोषणा TEGRA_PIN_UART4_RX_PI5			_GPIO(69)
#घोषणा TEGRA_PIN_UART4_RTS_PI6			_GPIO(70)
#घोषणा TEGRA_PIN_UART4_CTS_PI7			_GPIO(71)
#घोषणा TEGRA_PIN_GEN1_I2C_SDA_PJ0		_GPIO(72)
#घोषणा TEGRA_PIN_GEN1_I2C_SCL_PJ1		_GPIO(73)
#घोषणा TEGRA_PIN_GEN2_I2C_SCL_PJ2		_GPIO(74)
#घोषणा TEGRA_PIN_GEN2_I2C_SDA_PJ3		_GPIO(75)
#घोषणा TEGRA_PIN_DAP4_FS_PJ4			_GPIO(76)
#घोषणा TEGRA_PIN_DAP4_DIN_PJ5			_GPIO(77)
#घोषणा TEGRA_PIN_DAP4_DOUT_PJ6			_GPIO(78)
#घोषणा TEGRA_PIN_DAP4_SCLK_PJ7			_GPIO(79)
#घोषणा TEGRA_PIN_PK0				_GPIO(80)
#घोषणा TEGRA_PIN_PK1				_GPIO(81)
#घोषणा TEGRA_PIN_PK2				_GPIO(82)
#घोषणा TEGRA_PIN_PK3				_GPIO(83)
#घोषणा TEGRA_PIN_PK4				_GPIO(84)
#घोषणा TEGRA_PIN_PK5				_GPIO(85)
#घोषणा TEGRA_PIN_PK6				_GPIO(86)
#घोषणा TEGRA_PIN_PK7				_GPIO(87)
#घोषणा TEGRA_PIN_PL0				_GPIO(88)
#घोषणा TEGRA_PIN_PL1				_GPIO(89)
#घोषणा TEGRA_PIN_SDMMC1_CLK_PM0		_GPIO(96)
#घोषणा TEGRA_PIN_SDMMC1_CMD_PM1		_GPIO(97)
#घोषणा TEGRA_PIN_SDMMC1_DAT3_PM2		_GPIO(98)
#घोषणा TEGRA_PIN_SDMMC1_DAT2_PM3		_GPIO(99)
#घोषणा TEGRA_PIN_SDMMC1_DAT1_PM4		_GPIO(100)
#घोषणा TEGRA_PIN_SDMMC1_DAT0_PM5		_GPIO(101)
#घोषणा TEGRA_PIN_SDMMC3_CLK_PP0		_GPIO(120)
#घोषणा TEGRA_PIN_SDMMC3_CMD_PP1		_GPIO(121)
#घोषणा TEGRA_PIN_SDMMC3_DAT3_PP2		_GPIO(122)
#घोषणा TEGRA_PIN_SDMMC3_DAT2_PP3		_GPIO(123)
#घोषणा TEGRA_PIN_SDMMC3_DAT1_PP4		_GPIO(124)
#घोषणा TEGRA_PIN_SDMMC3_DAT0_PP5		_GPIO(125)
#घोषणा TEGRA_PIN_CAM1_MCLK_PS0			_GPIO(144)
#घोषणा TEGRA_PIN_CAM2_MCLK_PS1			_GPIO(145)
#घोषणा TEGRA_PIN_CAM_I2C_SCL_PS2		_GPIO(146)
#घोषणा TEGRA_PIN_CAM_I2C_SDA_PS3		_GPIO(147)
#घोषणा TEGRA_PIN_CAM_RST_PS4			_GPIO(148)
#घोषणा TEGRA_PIN_CAM_AF_EN_PS5			_GPIO(149)
#घोषणा TEGRA_PIN_CAM_FLASH_EN_PS6		_GPIO(150)
#घोषणा TEGRA_PIN_CAM1_PWDN_PS7			_GPIO(151)
#घोषणा TEGRA_PIN_CAM2_PWDN_PT0			_GPIO(152)
#घोषणा TEGRA_PIN_CAM1_STROBE_PT1		_GPIO(153)
#घोषणा TEGRA_PIN_UART1_TX_PU0			_GPIO(160)
#घोषणा TEGRA_PIN_UART1_RX_PU1			_GPIO(161)
#घोषणा TEGRA_PIN_UART1_RTS_PU2			_GPIO(162)
#घोषणा TEGRA_PIN_UART1_CTS_PU3			_GPIO(163)
#घोषणा TEGRA_PIN_LCD_BL_PWM_PV0		_GPIO(168)
#घोषणा TEGRA_PIN_LCD_BL_EN_PV1			_GPIO(169)
#घोषणा TEGRA_PIN_LCD_RST_PV2			_GPIO(170)
#घोषणा TEGRA_PIN_LCD_GPIO1_PV3			_GPIO(171)
#घोषणा TEGRA_PIN_LCD_GPIO2_PV4			_GPIO(172)
#घोषणा TEGRA_PIN_AP_READY_PV5			_GPIO(173)
#घोषणा TEGRA_PIN_TOUCH_RST_PV6			_GPIO(174)
#घोषणा TEGRA_PIN_TOUCH_CLK_PV7			_GPIO(175)
#घोषणा TEGRA_PIN_MODEM_WAKE_AP_PX0		_GPIO(184)
#घोषणा TEGRA_PIN_TOUCH_INT_PX1			_GPIO(185)
#घोषणा TEGRA_PIN_MOTION_INT_PX2		_GPIO(186)
#घोषणा TEGRA_PIN_ALS_PROX_INT_PX3		_GPIO(187)
#घोषणा TEGRA_PIN_TEMP_ALERT_PX4		_GPIO(188)
#घोषणा TEGRA_PIN_BUTTON_POWER_ON_PX5		_GPIO(189)
#घोषणा TEGRA_PIN_BUTTON_VOL_UP_PX6		_GPIO(190)
#घोषणा TEGRA_PIN_BUTTON_VOL_DOWN_PX7		_GPIO(191)
#घोषणा TEGRA_PIN_BUTTON_SLIDE_SW_PY0		_GPIO(192)
#घोषणा TEGRA_PIN_BUTTON_HOME_PY1		_GPIO(193)
#घोषणा TEGRA_PIN_LCD_TE_PY2			_GPIO(194)
#घोषणा TEGRA_PIN_PWR_I2C_SCL_PY3		_GPIO(195)
#घोषणा TEGRA_PIN_PWR_I2C_SDA_PY4		_GPIO(196)
#घोषणा TEGRA_PIN_CLK_32K_OUT_PY5		_GPIO(197)
#घोषणा TEGRA_PIN_PZ0				_GPIO(200)
#घोषणा TEGRA_PIN_PZ1				_GPIO(201)
#घोषणा TEGRA_PIN_PZ2				_GPIO(202)
#घोषणा TEGRA_PIN_PZ3				_GPIO(203)
#घोषणा TEGRA_PIN_PZ4				_GPIO(204)
#घोषणा TEGRA_PIN_PZ5				_GPIO(205)
#घोषणा TEGRA_PIN_DAP2_FS_PAA0			_GPIO(208)
#घोषणा TEGRA_PIN_DAP2_SCLK_PAA1		_GPIO(209)
#घोषणा TEGRA_PIN_DAP2_DIN_PAA2			_GPIO(210)
#घोषणा TEGRA_PIN_DAP2_DOUT_PAA3		_GPIO(211)
#घोषणा TEGRA_PIN_AUD_MCLK_PBB0			_GPIO(216)
#घोषणा TEGRA_PIN_DVFS_PWM_PBB1			_GPIO(217)
#घोषणा TEGRA_PIN_DVFS_CLK_PBB2			_GPIO(218)
#घोषणा TEGRA_PIN_GPIO_X1_AUD_PBB3		_GPIO(219)
#घोषणा TEGRA_PIN_GPIO_X3_AUD_PBB4		_GPIO(220)
#घोषणा TEGRA_PIN_HDMI_CEC_PCC0			_GPIO(224)
#घोषणा TEGRA_PIN_HDMI_INT_DP_HPD_PCC1		_GPIO(225)
#घोषणा TEGRA_PIN_SPDIF_OUT_PCC2		_GPIO(226)
#घोषणा TEGRA_PIN_SPDIF_IN_PCC3			_GPIO(227)
#घोषणा TEGRA_PIN_USB_VBUS_EN0_PCC4		_GPIO(228)
#घोषणा TEGRA_PIN_USB_VBUS_EN1_PCC5		_GPIO(229)
#घोषणा TEGRA_PIN_DP_HPD0_PCC6			_GPIO(230)
#घोषणा TEGRA_PIN_PCC7				_GPIO(231)
#घोषणा TEGRA_PIN_SPI2_CS1_PDD0			_GPIO(232)
#घोषणा TEGRA_PIN_QSPI_SCK_PEE0			_GPIO(240)
#घोषणा TEGRA_PIN_QSPI_CS_N_PEE1		_GPIO(241)
#घोषणा TEGRA_PIN_QSPI_IO0_PEE2			_GPIO(242)
#घोषणा TEGRA_PIN_QSPI_IO1_PEE3			_GPIO(243)
#घोषणा TEGRA_PIN_QSPI_IO2_PEE4			_GPIO(244)
#घोषणा TEGRA_PIN_QSPI_IO3_PEE5			_GPIO(245)

/* All non-GPIO pins follow */
#घोषणा NUM_GPIOS				(TEGRA_PIN_QSPI_IO3_PEE5 + 1)
#घोषणा _PIN(offset)				(NUM_GPIOS + (offset))

/* Non-GPIO pins */
#घोषणा TEGRA_PIN_CORE_PWR_REQ			_PIN(0)
#घोषणा TEGRA_PIN_CPU_PWR_REQ			_PIN(1)
#घोषणा TEGRA_PIN_PWR_INT_N			_PIN(2)
#घोषणा TEGRA_PIN_CLK_32K_IN			_PIN(3)
#घोषणा TEGRA_PIN_JTAG_RTCK			_PIN(4)
#घोषणा TEGRA_PIN_BATT_BCL			_PIN(5)
#घोषणा TEGRA_PIN_CLK_REQ			_PIN(6)
#घोषणा TEGRA_PIN_SHUTDOWN			_PIN(7)

अटल स्थिर काष्ठा pinctrl_pin_desc tegra210_pins[] = अणु
	PINCTRL_PIN(TEGRA_PIN_PEX_L0_RST_N_PA0, "PEX_L0_RST_N PA0"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L0_CLKREQ_N_PA1, "PEX_L0_CLKREQ_N PA1"),
	PINCTRL_PIN(TEGRA_PIN_PEX_WAKE_N_PA2, "PEX_WAKE_N PA2"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L1_RST_N_PA3, "PEX_L1_RST_N PA3"),
	PINCTRL_PIN(TEGRA_PIN_PEX_L1_CLKREQ_N_PA4, "PEX_L1_CLKREQ_N PA4"),
	PINCTRL_PIN(TEGRA_PIN_SATA_LED_ACTIVE_PA5, "SATA_LED_ACTIVE PA5"),
	PINCTRL_PIN(TEGRA_PIN_PA6, "PA6"),
	PINCTRL_PIN(TEGRA_PIN_DAP1_FS_PB0, "DAP1_FS PB0"),
	PINCTRL_PIN(TEGRA_PIN_DAP1_DIN_PB1, "DAP1_DIN PB1"),
	PINCTRL_PIN(TEGRA_PIN_DAP1_DOUT_PB2, "DAP1_DOUT PB2"),
	PINCTRL_PIN(TEGRA_PIN_DAP1_SCLK_PB3, "DAP1_SCLK PB3"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_MOSI_PB4, "SPI2_MOSI PB4"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_MISO_PB5, "SPI2_MISO PB5"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_SCK_PB6, "SPI2_SCK PB6"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_CS0_PB7, "SPI2_CS0 PB7"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_MOSI_PC0, "SPI1_MOSI PC0"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_MISO_PC1, "SPI1_MISO PC1"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_SCK_PC2, "SPI1_SCK PC2"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_CS0_PC3, "SPI1_CS0 PC3"),
	PINCTRL_PIN(TEGRA_PIN_SPI1_CS1_PC4, "SPI1_CS1 PC4"),
	PINCTRL_PIN(TEGRA_PIN_SPI4_SCK_PC5, "SPI4_SCK PC5"),
	PINCTRL_PIN(TEGRA_PIN_SPI4_CS0_PC6, "SPI4_CS0 PC6"),
	PINCTRL_PIN(TEGRA_PIN_SPI4_MOSI_PC7, "SPI4_MOSI PC7"),
	PINCTRL_PIN(TEGRA_PIN_SPI4_MISO_PD0, "SPI4_MISO PD0"),
	PINCTRL_PIN(TEGRA_PIN_UART3_TX_PD1, "UART3_TX PD1"),
	PINCTRL_PIN(TEGRA_PIN_UART3_RX_PD2, "UART3_RX PD2"),
	PINCTRL_PIN(TEGRA_PIN_UART3_RTS_PD3, "UART3_RTS PD3"),
	PINCTRL_PIN(TEGRA_PIN_UART3_CTS_PD4, "UART3_CTS PD4"),
	PINCTRL_PIN(TEGRA_PIN_DMIC1_CLK_PE0, "DMIC1_CLK PE0"),
	PINCTRL_PIN(TEGRA_PIN_DMIC1_DAT_PE1, "DMIC1_DAT PE1"),
	PINCTRL_PIN(TEGRA_PIN_DMIC2_CLK_PE2, "DMIC2_CLK PE2"),
	PINCTRL_PIN(TEGRA_PIN_DMIC2_DAT_PE3, "DMIC2_DAT PE3"),
	PINCTRL_PIN(TEGRA_PIN_DMIC3_CLK_PE4, "DMIC3_CLK PE4"),
	PINCTRL_PIN(TEGRA_PIN_DMIC3_DAT_PE5, "DMIC3_DAT PE5"),
	PINCTRL_PIN(TEGRA_PIN_PE6, "PE6"),
	PINCTRL_PIN(TEGRA_PIN_PE7, "PE7"),
	PINCTRL_PIN(TEGRA_PIN_GEN3_I2C_SCL_PF0, "GEN3_I2C_SCL PF0"),
	PINCTRL_PIN(TEGRA_PIN_GEN3_I2C_SDA_PF1, "GEN3_I2C_SDA PF1"),
	PINCTRL_PIN(TEGRA_PIN_UART2_TX_PG0, "UART2_TX PG0"),
	PINCTRL_PIN(TEGRA_PIN_UART2_RX_PG1, "UART2_RX PG1"),
	PINCTRL_PIN(TEGRA_PIN_UART2_RTS_PG2, "UART2_RTS PG2"),
	PINCTRL_PIN(TEGRA_PIN_UART2_CTS_PG3, "UART2_CTS PG3"),
	PINCTRL_PIN(TEGRA_PIN_WIFI_EN_PH0, "WIFI_EN PH0"),
	PINCTRL_PIN(TEGRA_PIN_WIFI_RST_PH1, "WIFI_RST PH1"),
	PINCTRL_PIN(TEGRA_PIN_WIFI_WAKE_AP_PH2, "WIFI_WAKE_AP PH2"),
	PINCTRL_PIN(TEGRA_PIN_AP_WAKE_BT_PH3, "AP_WAKE_BT PH3"),
	PINCTRL_PIN(TEGRA_PIN_BT_RST_PH4, "BT_RST PH4"),
	PINCTRL_PIN(TEGRA_PIN_BT_WAKE_AP_PH5, "BT_WAKE_AP PH5"),
	PINCTRL_PIN(TEGRA_PIN_PH6, "PH6"),
	PINCTRL_PIN(TEGRA_PIN_AP_WAKE_NFC_PH7, "AP_WAKE_NFC PH7"),
	PINCTRL_PIN(TEGRA_PIN_NFC_EN_PI0, "NFC_EN PI0"),
	PINCTRL_PIN(TEGRA_PIN_NFC_INT_PI1, "NFC_INT PI1"),
	PINCTRL_PIN(TEGRA_PIN_GPS_EN_PI2, "GPS_EN PI2"),
	PINCTRL_PIN(TEGRA_PIN_GPS_RST_PI3, "GPS_RST PI3"),
	PINCTRL_PIN(TEGRA_PIN_UART4_TX_PI4, "UART4_TX PI4"),
	PINCTRL_PIN(TEGRA_PIN_UART4_RX_PI5, "UART4_RX PI5"),
	PINCTRL_PIN(TEGRA_PIN_UART4_RTS_PI6, "UART4_RTS PI6"),
	PINCTRL_PIN(TEGRA_PIN_UART4_CTS_PI7, "UART4_CTS PI7"),
	PINCTRL_PIN(TEGRA_PIN_GEN1_I2C_SDA_PJ0, "GEN1_I2C_SDA PJ0"),
	PINCTRL_PIN(TEGRA_PIN_GEN1_I2C_SCL_PJ1, "GEN1_I2C_SCL PJ1"),
	PINCTRL_PIN(TEGRA_PIN_GEN2_I2C_SCL_PJ2, "GEN2_I2C_SCL PJ2"),
	PINCTRL_PIN(TEGRA_PIN_GEN2_I2C_SDA_PJ3, "GEN2_I2C_SDA PJ3"),
	PINCTRL_PIN(TEGRA_PIN_DAP4_FS_PJ4, "DAP4_FS PJ4"),
	PINCTRL_PIN(TEGRA_PIN_DAP4_DIN_PJ5, "DAP4_DIN PJ5"),
	PINCTRL_PIN(TEGRA_PIN_DAP4_DOUT_PJ6, "DAP4_DOUT PJ6"),
	PINCTRL_PIN(TEGRA_PIN_DAP4_SCLK_PJ7, "DAP4_SCLK PJ7"),
	PINCTRL_PIN(TEGRA_PIN_PK0, "PK0"),
	PINCTRL_PIN(TEGRA_PIN_PK1, "PK1"),
	PINCTRL_PIN(TEGRA_PIN_PK2, "PK2"),
	PINCTRL_PIN(TEGRA_PIN_PK3, "PK3"),
	PINCTRL_PIN(TEGRA_PIN_PK4, "PK4"),
	PINCTRL_PIN(TEGRA_PIN_PK5, "PK5"),
	PINCTRL_PIN(TEGRA_PIN_PK6, "PK6"),
	PINCTRL_PIN(TEGRA_PIN_PK7, "PK7"),
	PINCTRL_PIN(TEGRA_PIN_PL0, "PL0"),
	PINCTRL_PIN(TEGRA_PIN_PL1, "PL1"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_CLK_PM0, "SDMMC1_CLK PM0"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_CMD_PM1, "SDMMC1_CMD PM1"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_DAT3_PM2, "SDMMC1_DAT3 PM2"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_DAT2_PM3, "SDMMC1_DAT2 PM3"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_DAT1_PM4, "SDMMC1_DAT1 PM4"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC1_DAT0_PM5, "SDMMC1_DAT0 PM5"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_CLK_PP0, "SDMMC3_CLK PP0"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_CMD_PP1, "SDMMC3_CMD PP1"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT3_PP2, "SDMMC3_DAT3 PP2"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT2_PP3, "SDMMC3_DAT2 PP3"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT1_PP4, "SDMMC3_DAT1 PP4"),
	PINCTRL_PIN(TEGRA_PIN_SDMMC3_DAT0_PP5, "SDMMC3_DAT0 PP5"),
	PINCTRL_PIN(TEGRA_PIN_CAM1_MCLK_PS0, "CAM1_MCLK PS0"),
	PINCTRL_PIN(TEGRA_PIN_CAM2_MCLK_PS1, "CAM2_MCLK PS1"),
	PINCTRL_PIN(TEGRA_PIN_CAM_I2C_SCL_PS2, "CAM_I2C_SCL PS2"),
	PINCTRL_PIN(TEGRA_PIN_CAM_I2C_SDA_PS3, "CAM_I2C_SDA PS3"),
	PINCTRL_PIN(TEGRA_PIN_CAM_RST_PS4, "CAM_RST PS4"),
	PINCTRL_PIN(TEGRA_PIN_CAM_AF_EN_PS5, "CAM_AF_EN PS5"),
	PINCTRL_PIN(TEGRA_PIN_CAM_FLASH_EN_PS6, "CAM_FLASH_EN PS6"),
	PINCTRL_PIN(TEGRA_PIN_CAM1_PWDN_PS7, "CAM1_PWDN PS7"),
	PINCTRL_PIN(TEGRA_PIN_CAM2_PWDN_PT0, "CAM2_PWDN PT0"),
	PINCTRL_PIN(TEGRA_PIN_CAM1_STROBE_PT1, "CAM1_STROBE PT1"),
	PINCTRL_PIN(TEGRA_PIN_UART1_TX_PU0, "UART1_TX PU0"),
	PINCTRL_PIN(TEGRA_PIN_UART1_RX_PU1, "UART1_RX PU1"),
	PINCTRL_PIN(TEGRA_PIN_UART1_RTS_PU2, "UART1_RTS PU2"),
	PINCTRL_PIN(TEGRA_PIN_UART1_CTS_PU3, "UART1_CTS PU3"),
	PINCTRL_PIN(TEGRA_PIN_LCD_BL_PWM_PV0, "LCD_BL_PWM PV0"),
	PINCTRL_PIN(TEGRA_PIN_LCD_BL_EN_PV1, "LCD_BL_EN PV1"),
	PINCTRL_PIN(TEGRA_PIN_LCD_RST_PV2, "LCD_RST PV2"),
	PINCTRL_PIN(TEGRA_PIN_LCD_GPIO1_PV3, "LCD_GPIO1 PV3"),
	PINCTRL_PIN(TEGRA_PIN_LCD_GPIO2_PV4, "LCD_GPIO2 PV4"),
	PINCTRL_PIN(TEGRA_PIN_AP_READY_PV5, "AP_READY PV5"),
	PINCTRL_PIN(TEGRA_PIN_TOUCH_RST_PV6, "TOUCH_RST PV6"),
	PINCTRL_PIN(TEGRA_PIN_TOUCH_CLK_PV7, "TOUCH_CLK PV7"),
	PINCTRL_PIN(TEGRA_PIN_MODEM_WAKE_AP_PX0, "MODEM_WAKE_AP PX0"),
	PINCTRL_PIN(TEGRA_PIN_TOUCH_INT_PX1, "TOUCH_INT PX1"),
	PINCTRL_PIN(TEGRA_PIN_MOTION_INT_PX2, "MOTION_INT PX2"),
	PINCTRL_PIN(TEGRA_PIN_ALS_PROX_INT_PX3, "ALS_PROX_INT PX3"),
	PINCTRL_PIN(TEGRA_PIN_TEMP_ALERT_PX4, "TEMP_ALERT PX4"),
	PINCTRL_PIN(TEGRA_PIN_BUTTON_POWER_ON_PX5, "BUTTON_POWER_ON PX5"),
	PINCTRL_PIN(TEGRA_PIN_BUTTON_VOL_UP_PX6, "BUTTON_VOL_UP PX6"),
	PINCTRL_PIN(TEGRA_PIN_BUTTON_VOL_DOWN_PX7, "BUTTON_VOL_DOWN PX7"),
	PINCTRL_PIN(TEGRA_PIN_BUTTON_SLIDE_SW_PY0, "BUTTON_SLIDE_SW PY0"),
	PINCTRL_PIN(TEGRA_PIN_BUTTON_HOME_PY1, "BUTTON_HOME PY1"),
	PINCTRL_PIN(TEGRA_PIN_LCD_TE_PY2, "LCD_TE PY2"),
	PINCTRL_PIN(TEGRA_PIN_PWR_I2C_SCL_PY3, "PWR_I2C_SCL PY3"),
	PINCTRL_PIN(TEGRA_PIN_PWR_I2C_SDA_PY4, "PWR_I2C_SDA PY4"),
	PINCTRL_PIN(TEGRA_PIN_CLK_32K_OUT_PY5, "CLK_32K_OUT PY5"),
	PINCTRL_PIN(TEGRA_PIN_PZ0, "PZ0"),
	PINCTRL_PIN(TEGRA_PIN_PZ1, "PZ1"),
	PINCTRL_PIN(TEGRA_PIN_PZ2, "PZ2"),
	PINCTRL_PIN(TEGRA_PIN_PZ3, "PZ3"),
	PINCTRL_PIN(TEGRA_PIN_PZ4, "PZ4"),
	PINCTRL_PIN(TEGRA_PIN_PZ5, "PZ5"),
	PINCTRL_PIN(TEGRA_PIN_DAP2_FS_PAA0, "DAP2_FS PAA0"),
	PINCTRL_PIN(TEGRA_PIN_DAP2_SCLK_PAA1, "DAP2_SCLK PAA1"),
	PINCTRL_PIN(TEGRA_PIN_DAP2_DIN_PAA2, "DAP2_DIN PAA2"),
	PINCTRL_PIN(TEGRA_PIN_DAP2_DOUT_PAA3, "DAP2_DOUT PAA3"),
	PINCTRL_PIN(TEGRA_PIN_AUD_MCLK_PBB0, "AUD_MCLK PBB0"),
	PINCTRL_PIN(TEGRA_PIN_DVFS_PWM_PBB1, "DVFS_PWM PBB1"),
	PINCTRL_PIN(TEGRA_PIN_DVFS_CLK_PBB2, "DVFS_CLK PBB2"),
	PINCTRL_PIN(TEGRA_PIN_GPIO_X1_AUD_PBB3, "GPIO_X1_AUD PBB3"),
	PINCTRL_PIN(TEGRA_PIN_GPIO_X3_AUD_PBB4, "GPIO_X3_AUD PBB4"),
	PINCTRL_PIN(TEGRA_PIN_HDMI_CEC_PCC0, "HDMI_CEC PCC0"),
	PINCTRL_PIN(TEGRA_PIN_HDMI_INT_DP_HPD_PCC1, "HDMI_INT_DP_HPD PCC1"),
	PINCTRL_PIN(TEGRA_PIN_SPDIF_OUT_PCC2, "SPDIF_OUT PCC2"),
	PINCTRL_PIN(TEGRA_PIN_SPDIF_IN_PCC3, "SPDIF_IN PCC3"),
	PINCTRL_PIN(TEGRA_PIN_USB_VBUS_EN0_PCC4, "USB_VBUS_EN0 PCC4"),
	PINCTRL_PIN(TEGRA_PIN_USB_VBUS_EN1_PCC5, "USB_VBUS_EN1 PCC5"),
	PINCTRL_PIN(TEGRA_PIN_DP_HPD0_PCC6, "DP_HPD0 PCC6"),
	PINCTRL_PIN(TEGRA_PIN_PCC7, "PCC7"),
	PINCTRL_PIN(TEGRA_PIN_SPI2_CS1_PDD0, "SPI2_CS1 PDD0"),
	PINCTRL_PIN(TEGRA_PIN_QSPI_SCK_PEE0, "QSPI_SCK PEE0"),
	PINCTRL_PIN(TEGRA_PIN_QSPI_CS_N_PEE1, "QSPI_CS_N PEE1"),
	PINCTRL_PIN(TEGRA_PIN_QSPI_IO0_PEE2, "QSPI_IO0 PEE2"),
	PINCTRL_PIN(TEGRA_PIN_QSPI_IO1_PEE3, "QSPI_IO1 PEE3"),
	PINCTRL_PIN(TEGRA_PIN_QSPI_IO2_PEE4, "QSPI_IO2 PEE4"),
	PINCTRL_PIN(TEGRA_PIN_QSPI_IO3_PEE5, "QSPI_IO3 PEE5"),
	PINCTRL_PIN(TEGRA_PIN_CORE_PWR_REQ, "CORE_PWR_REQ"),
	PINCTRL_PIN(TEGRA_PIN_CPU_PWR_REQ, "CPU_PWR_REQ"),
	PINCTRL_PIN(TEGRA_PIN_PWR_INT_N, "PWR_INT_N"),
	PINCTRL_PIN(TEGRA_PIN_CLK_32K_IN, "CLK_32K_IN"),
	PINCTRL_PIN(TEGRA_PIN_JTAG_RTCK, "JTAG_RTCK"),
	PINCTRL_PIN(TEGRA_PIN_BATT_BCL, "BATT_BCL"),
	PINCTRL_PIN(TEGRA_PIN_CLK_REQ, "CLK_REQ"),
	PINCTRL_PIN(TEGRA_PIN_SHUTDOWN, "SHUTDOWN"),
पूर्ण;

अटल स्थिर अचिन्हित pex_l0_rst_n_pa0_pins[] = अणु
	TEGRA_PIN_PEX_L0_RST_N_PA0,
पूर्ण;

अटल स्थिर अचिन्हित pex_l0_clkreq_n_pa1_pins[] = अणु
	TEGRA_PIN_PEX_L0_CLKREQ_N_PA1,
पूर्ण;

अटल स्थिर अचिन्हित pex_wake_n_pa2_pins[] = अणु
	TEGRA_PIN_PEX_WAKE_N_PA2,
पूर्ण;

अटल स्थिर अचिन्हित pex_l1_rst_n_pa3_pins[] = अणु
	TEGRA_PIN_PEX_L1_RST_N_PA3,
पूर्ण;

अटल स्थिर अचिन्हित pex_l1_clkreq_n_pa4_pins[] = अणु
	TEGRA_PIN_PEX_L1_CLKREQ_N_PA4,
पूर्ण;

अटल स्थिर अचिन्हित sata_led_active_pa5_pins[] = अणु
	TEGRA_PIN_SATA_LED_ACTIVE_PA5,
पूर्ण;

अटल स्थिर अचिन्हित pa6_pins[] = अणु
	TEGRA_PIN_PA6,
पूर्ण;

अटल स्थिर अचिन्हित dap1_fs_pb0_pins[] = अणु
	TEGRA_PIN_DAP1_FS_PB0,
पूर्ण;

अटल स्थिर अचिन्हित dap1_din_pb1_pins[] = अणु
	TEGRA_PIN_DAP1_DIN_PB1,
पूर्ण;

अटल स्थिर अचिन्हित dap1_करोut_pb2_pins[] = अणु
	TEGRA_PIN_DAP1_DOUT_PB2,
पूर्ण;

अटल स्थिर अचिन्हित dap1_sclk_pb3_pins[] = अणु
	TEGRA_PIN_DAP1_SCLK_PB3,
पूर्ण;

अटल स्थिर अचिन्हित spi2_mosi_pb4_pins[] = अणु
	TEGRA_PIN_SPI2_MOSI_PB4,
पूर्ण;

अटल स्थिर अचिन्हित spi2_miso_pb5_pins[] = अणु
	TEGRA_PIN_SPI2_MISO_PB5,
पूर्ण;

अटल स्थिर अचिन्हित spi2_sck_pb6_pins[] = अणु
	TEGRA_PIN_SPI2_SCK_PB6,
पूर्ण;

अटल स्थिर अचिन्हित spi2_cs0_pb7_pins[] = अणु
	TEGRA_PIN_SPI2_CS0_PB7,
पूर्ण;

अटल स्थिर अचिन्हित spi1_mosi_pc0_pins[] = अणु
	TEGRA_PIN_SPI1_MOSI_PC0,
पूर्ण;

अटल स्थिर अचिन्हित spi1_miso_pc1_pins[] = अणु
	TEGRA_PIN_SPI1_MISO_PC1,
पूर्ण;

अटल स्थिर अचिन्हित spi1_sck_pc2_pins[] = अणु
	TEGRA_PIN_SPI1_SCK_PC2,
पूर्ण;

अटल स्थिर अचिन्हित spi1_cs0_pc3_pins[] = अणु
	TEGRA_PIN_SPI1_CS0_PC3,
पूर्ण;

अटल स्थिर अचिन्हित spi1_cs1_pc4_pins[] = अणु
	TEGRA_PIN_SPI1_CS1_PC4,
पूर्ण;

अटल स्थिर अचिन्हित spi4_sck_pc5_pins[] = अणु
	TEGRA_PIN_SPI4_SCK_PC5,
पूर्ण;

अटल स्थिर अचिन्हित spi4_cs0_pc6_pins[] = अणु
	TEGRA_PIN_SPI4_CS0_PC6,
पूर्ण;

अटल स्थिर अचिन्हित spi4_mosi_pc7_pins[] = अणु
	TEGRA_PIN_SPI4_MOSI_PC7,
पूर्ण;

अटल स्थिर अचिन्हित spi4_miso_pd0_pins[] = अणु
	TEGRA_PIN_SPI4_MISO_PD0,
पूर्ण;

अटल स्थिर अचिन्हित uart3_tx_pd1_pins[] = अणु
	TEGRA_PIN_UART3_TX_PD1,
पूर्ण;

अटल स्थिर अचिन्हित uart3_rx_pd2_pins[] = अणु
	TEGRA_PIN_UART3_RX_PD2,
पूर्ण;

अटल स्थिर अचिन्हित uart3_rts_pd3_pins[] = अणु
	TEGRA_PIN_UART3_RTS_PD3,
पूर्ण;

अटल स्थिर अचिन्हित uart3_cts_pd4_pins[] = अणु
	TEGRA_PIN_UART3_CTS_PD4,
पूर्ण;

अटल स्थिर अचिन्हित dmic1_clk_pe0_pins[] = अणु
	TEGRA_PIN_DMIC1_CLK_PE0,
पूर्ण;

अटल स्थिर अचिन्हित dmic1_dat_pe1_pins[] = अणु
	TEGRA_PIN_DMIC1_DAT_PE1,
पूर्ण;

अटल स्थिर अचिन्हित dmic2_clk_pe2_pins[] = अणु
	TEGRA_PIN_DMIC2_CLK_PE2,
पूर्ण;

अटल स्थिर अचिन्हित dmic2_dat_pe3_pins[] = अणु
	TEGRA_PIN_DMIC2_DAT_PE3,
पूर्ण;

अटल स्थिर अचिन्हित dmic3_clk_pe4_pins[] = अणु
	TEGRA_PIN_DMIC3_CLK_PE4,
पूर्ण;

अटल स्थिर अचिन्हित dmic3_dat_pe5_pins[] = अणु
	TEGRA_PIN_DMIC3_DAT_PE5,
पूर्ण;

अटल स्थिर अचिन्हित pe6_pins[] = अणु
	TEGRA_PIN_PE6,
पूर्ण;

अटल स्थिर अचिन्हित pe7_pins[] = अणु
	TEGRA_PIN_PE7,
पूर्ण;

अटल स्थिर अचिन्हित gen3_i2c_scl_pf0_pins[] = अणु
	TEGRA_PIN_GEN3_I2C_SCL_PF0,
पूर्ण;

अटल स्थिर अचिन्हित gen3_i2c_sda_pf1_pins[] = अणु
	TEGRA_PIN_GEN3_I2C_SDA_PF1,
पूर्ण;

अटल स्थिर अचिन्हित uart2_tx_pg0_pins[] = अणु
	TEGRA_PIN_UART2_TX_PG0,
पूर्ण;

अटल स्थिर अचिन्हित uart2_rx_pg1_pins[] = अणु
	TEGRA_PIN_UART2_RX_PG1,
पूर्ण;

अटल स्थिर अचिन्हित uart2_rts_pg2_pins[] = अणु
	TEGRA_PIN_UART2_RTS_PG2,
पूर्ण;

अटल स्थिर अचिन्हित uart2_cts_pg3_pins[] = अणु
	TEGRA_PIN_UART2_CTS_PG3,
पूर्ण;

अटल स्थिर अचिन्हित wअगरi_en_ph0_pins[] = अणु
	TEGRA_PIN_WIFI_EN_PH0,
पूर्ण;

अटल स्थिर अचिन्हित wअगरi_rst_ph1_pins[] = अणु
	TEGRA_PIN_WIFI_RST_PH1,
पूर्ण;

अटल स्थिर अचिन्हित wअगरi_wake_ap_ph2_pins[] = अणु
	TEGRA_PIN_WIFI_WAKE_AP_PH2,
पूर्ण;

अटल स्थिर अचिन्हित ap_wake_bt_ph3_pins[] = अणु
	TEGRA_PIN_AP_WAKE_BT_PH3,
पूर्ण;

अटल स्थिर अचिन्हित bt_rst_ph4_pins[] = अणु
	TEGRA_PIN_BT_RST_PH4,
पूर्ण;

अटल स्थिर अचिन्हित bt_wake_ap_ph5_pins[] = अणु
	TEGRA_PIN_BT_WAKE_AP_PH5,
पूर्ण;

अटल स्थिर अचिन्हित ph6_pins[] = अणु
	TEGRA_PIN_PH6,
पूर्ण;

अटल स्थिर अचिन्हित ap_wake_nfc_ph7_pins[] = अणु
	TEGRA_PIN_AP_WAKE_NFC_PH7,
पूर्ण;

अटल स्थिर अचिन्हित nfc_en_pi0_pins[] = अणु
	TEGRA_PIN_NFC_EN_PI0,
पूर्ण;

अटल स्थिर अचिन्हित nfc_पूर्णांक_pi1_pins[] = अणु
	TEGRA_PIN_NFC_INT_PI1,
पूर्ण;

अटल स्थिर अचिन्हित gps_en_pi2_pins[] = अणु
	TEGRA_PIN_GPS_EN_PI2,
पूर्ण;

अटल स्थिर अचिन्हित gps_rst_pi3_pins[] = अणु
	TEGRA_PIN_GPS_RST_PI3,
पूर्ण;

अटल स्थिर अचिन्हित uart4_tx_pi4_pins[] = अणु
	TEGRA_PIN_UART4_TX_PI4,
पूर्ण;

अटल स्थिर अचिन्हित uart4_rx_pi5_pins[] = अणु
	TEGRA_PIN_UART4_RX_PI5,
पूर्ण;

अटल स्थिर अचिन्हित uart4_rts_pi6_pins[] = अणु
	TEGRA_PIN_UART4_RTS_PI6,
पूर्ण;

अटल स्थिर अचिन्हित uart4_cts_pi7_pins[] = अणु
	TEGRA_PIN_UART4_CTS_PI7,
पूर्ण;

अटल स्थिर अचिन्हित gen1_i2c_sda_pj0_pins[] = अणु
	TEGRA_PIN_GEN1_I2C_SDA_PJ0,
पूर्ण;

अटल स्थिर अचिन्हित gen1_i2c_scl_pj1_pins[] = अणु
	TEGRA_PIN_GEN1_I2C_SCL_PJ1,
पूर्ण;

अटल स्थिर अचिन्हित gen2_i2c_scl_pj2_pins[] = अणु
	TEGRA_PIN_GEN2_I2C_SCL_PJ2,
पूर्ण;

अटल स्थिर अचिन्हित gen2_i2c_sda_pj3_pins[] = अणु
	TEGRA_PIN_GEN2_I2C_SDA_PJ3,
पूर्ण;

अटल स्थिर अचिन्हित dap4_fs_pj4_pins[] = अणु
	TEGRA_PIN_DAP4_FS_PJ4,
पूर्ण;

अटल स्थिर अचिन्हित dap4_din_pj5_pins[] = अणु
	TEGRA_PIN_DAP4_DIN_PJ5,
पूर्ण;

अटल स्थिर अचिन्हित dap4_करोut_pj6_pins[] = अणु
	TEGRA_PIN_DAP4_DOUT_PJ6,
पूर्ण;

अटल स्थिर अचिन्हित dap4_sclk_pj7_pins[] = अणु
	TEGRA_PIN_DAP4_SCLK_PJ7,
पूर्ण;

अटल स्थिर अचिन्हित pk0_pins[] = अणु
	TEGRA_PIN_PK0,
पूर्ण;

अटल स्थिर अचिन्हित pk1_pins[] = अणु
	TEGRA_PIN_PK1,
पूर्ण;

अटल स्थिर अचिन्हित pk2_pins[] = अणु
	TEGRA_PIN_PK2,
पूर्ण;

अटल स्थिर अचिन्हित pk3_pins[] = अणु
	TEGRA_PIN_PK3,
पूर्ण;

अटल स्थिर अचिन्हित pk4_pins[] = अणु
	TEGRA_PIN_PK4,
पूर्ण;

अटल स्थिर अचिन्हित pk5_pins[] = अणु
	TEGRA_PIN_PK5,
पूर्ण;

अटल स्थिर अचिन्हित pk6_pins[] = अणु
	TEGRA_PIN_PK6,
पूर्ण;

अटल स्थिर अचिन्हित pk7_pins[] = अणु
	TEGRA_PIN_PK7,
पूर्ण;

अटल स्थिर अचिन्हित pl0_pins[] = अणु
	TEGRA_PIN_PL0,
पूर्ण;

अटल स्थिर अचिन्हित pl1_pins[] = अणु
	TEGRA_PIN_PL1,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_clk_pm0_pins[] = अणु
	TEGRA_PIN_SDMMC1_CLK_PM0,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_cmd_pm1_pins[] = अणु
	TEGRA_PIN_SDMMC1_CMD_PM1,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_dat3_pm2_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT3_PM2,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_dat2_pm3_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT2_PM3,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_dat1_pm4_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT1_PM4,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc1_dat0_pm5_pins[] = अणु
	TEGRA_PIN_SDMMC1_DAT0_PM5,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_clk_pp0_pins[] = अणु
	TEGRA_PIN_SDMMC3_CLK_PP0,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_cmd_pp1_pins[] = अणु
	TEGRA_PIN_SDMMC3_CMD_PP1,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat3_pp2_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT3_PP2,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat2_pp3_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT2_PP3,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat1_pp4_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT1_PP4,
पूर्ण;

अटल स्थिर अचिन्हित sdmmc3_dat0_pp5_pins[] = अणु
	TEGRA_PIN_SDMMC3_DAT0_PP5,
पूर्ण;

अटल स्थिर अचिन्हित cam1_mclk_ps0_pins[] = अणु
	TEGRA_PIN_CAM1_MCLK_PS0,
पूर्ण;

अटल स्थिर अचिन्हित cam2_mclk_ps1_pins[] = अणु
	TEGRA_PIN_CAM2_MCLK_PS1,
पूर्ण;

अटल स्थिर अचिन्हित cam_i2c_scl_ps2_pins[] = अणु
	TEGRA_PIN_CAM_I2C_SCL_PS2,
पूर्ण;

अटल स्थिर अचिन्हित cam_i2c_sda_ps3_pins[] = अणु
	TEGRA_PIN_CAM_I2C_SDA_PS3,
पूर्ण;

अटल स्थिर अचिन्हित cam_rst_ps4_pins[] = अणु
	TEGRA_PIN_CAM_RST_PS4,
पूर्ण;

अटल स्थिर अचिन्हित cam_af_en_ps5_pins[] = अणु
	TEGRA_PIN_CAM_AF_EN_PS5,
पूर्ण;

अटल स्थिर अचिन्हित cam_flash_en_ps6_pins[] = अणु
	TEGRA_PIN_CAM_FLASH_EN_PS6,
पूर्ण;

अटल स्थिर अचिन्हित cam1_pwdn_ps7_pins[] = अणु
	TEGRA_PIN_CAM1_PWDN_PS7,
पूर्ण;

अटल स्थिर अचिन्हित cam2_pwdn_pt0_pins[] = अणु
	TEGRA_PIN_CAM2_PWDN_PT0,
पूर्ण;

अटल स्थिर अचिन्हित cam1_strobe_pt1_pins[] = अणु
	TEGRA_PIN_CAM1_STROBE_PT1,
पूर्ण;

अटल स्थिर अचिन्हित uart1_tx_pu0_pins[] = अणु
	TEGRA_PIN_UART1_TX_PU0,
पूर्ण;

अटल स्थिर अचिन्हित uart1_rx_pu1_pins[] = अणु
	TEGRA_PIN_UART1_RX_PU1,
पूर्ण;

अटल स्थिर अचिन्हित uart1_rts_pu2_pins[] = अणु
	TEGRA_PIN_UART1_RTS_PU2,
पूर्ण;

अटल स्थिर अचिन्हित uart1_cts_pu3_pins[] = अणु
	TEGRA_PIN_UART1_CTS_PU3,
पूर्ण;

अटल स्थिर अचिन्हित lcd_bl_pwm_pv0_pins[] = अणु
	TEGRA_PIN_LCD_BL_PWM_PV0,
पूर्ण;

अटल स्थिर अचिन्हित lcd_bl_en_pv1_pins[] = अणु
	TEGRA_PIN_LCD_BL_EN_PV1,
पूर्ण;

अटल स्थिर अचिन्हित lcd_rst_pv2_pins[] = अणु
	TEGRA_PIN_LCD_RST_PV2,
पूर्ण;

अटल स्थिर अचिन्हित lcd_gpio1_pv3_pins[] = अणु
	TEGRA_PIN_LCD_GPIO1_PV3,
पूर्ण;

अटल स्थिर अचिन्हित lcd_gpio2_pv4_pins[] = अणु
	TEGRA_PIN_LCD_GPIO2_PV4,
पूर्ण;

अटल स्थिर अचिन्हित ap_पढ़ोy_pv5_pins[] = अणु
	TEGRA_PIN_AP_READY_PV5,
पूर्ण;

अटल स्थिर अचिन्हित touch_rst_pv6_pins[] = अणु
	TEGRA_PIN_TOUCH_RST_PV6,
पूर्ण;

अटल स्थिर अचिन्हित touch_clk_pv7_pins[] = अणु
	TEGRA_PIN_TOUCH_CLK_PV7,
पूर्ण;

अटल स्थिर अचिन्हित modem_wake_ap_px0_pins[] = अणु
	TEGRA_PIN_MODEM_WAKE_AP_PX0,
पूर्ण;

अटल स्थिर अचिन्हित touch_पूर्णांक_px1_pins[] = अणु
	TEGRA_PIN_TOUCH_INT_PX1,
पूर्ण;

अटल स्थिर अचिन्हित motion_पूर्णांक_px2_pins[] = अणु
	TEGRA_PIN_MOTION_INT_PX2,
पूर्ण;

अटल स्थिर अचिन्हित als_prox_पूर्णांक_px3_pins[] = अणु
	TEGRA_PIN_ALS_PROX_INT_PX3,
पूर्ण;

अटल स्थिर अचिन्हित temp_alert_px4_pins[] = अणु
	TEGRA_PIN_TEMP_ALERT_PX4,
पूर्ण;

अटल स्थिर अचिन्हित button_घातer_on_px5_pins[] = अणु
	TEGRA_PIN_BUTTON_POWER_ON_PX5,
पूर्ण;

अटल स्थिर अचिन्हित button_vol_up_px6_pins[] = अणु
	TEGRA_PIN_BUTTON_VOL_UP_PX6,
पूर्ण;

अटल स्थिर अचिन्हित button_vol_करोwn_px7_pins[] = अणु
	TEGRA_PIN_BUTTON_VOL_DOWN_PX7,
पूर्ण;

अटल स्थिर अचिन्हित button_slide_sw_py0_pins[] = अणु
	TEGRA_PIN_BUTTON_SLIDE_SW_PY0,
पूर्ण;

अटल स्थिर अचिन्हित button_home_py1_pins[] = अणु
	TEGRA_PIN_BUTTON_HOME_PY1,
पूर्ण;

अटल स्थिर अचिन्हित lcd_te_py2_pins[] = अणु
	TEGRA_PIN_LCD_TE_PY2,
पूर्ण;

अटल स्थिर अचिन्हित pwr_i2c_scl_py3_pins[] = अणु
	TEGRA_PIN_PWR_I2C_SCL_PY3,
पूर्ण;

अटल स्थिर अचिन्हित pwr_i2c_sda_py4_pins[] = अणु
	TEGRA_PIN_PWR_I2C_SDA_PY4,
पूर्ण;

अटल स्थिर अचिन्हित clk_32k_out_py5_pins[] = अणु
	TEGRA_PIN_CLK_32K_OUT_PY5,
पूर्ण;

अटल स्थिर अचिन्हित pz0_pins[] = अणु
	TEGRA_PIN_PZ0,
पूर्ण;

अटल स्थिर अचिन्हित pz1_pins[] = अणु
	TEGRA_PIN_PZ1,
पूर्ण;

अटल स्थिर अचिन्हित pz2_pins[] = अणु
	TEGRA_PIN_PZ2,
पूर्ण;

अटल स्थिर अचिन्हित pz3_pins[] = अणु
	TEGRA_PIN_PZ3,
पूर्ण;

अटल स्थिर अचिन्हित pz4_pins[] = अणु
	TEGRA_PIN_PZ4,
पूर्ण;

अटल स्थिर अचिन्हित pz5_pins[] = अणु
	TEGRA_PIN_PZ5,
पूर्ण;

अटल स्थिर अचिन्हित dap2_fs_paa0_pins[] = अणु
	TEGRA_PIN_DAP2_FS_PAA0,
पूर्ण;

अटल स्थिर अचिन्हित dap2_sclk_paa1_pins[] = अणु
	TEGRA_PIN_DAP2_SCLK_PAA1,
पूर्ण;

अटल स्थिर अचिन्हित dap2_din_paa2_pins[] = अणु
	TEGRA_PIN_DAP2_DIN_PAA2,
पूर्ण;

अटल स्थिर अचिन्हित dap2_करोut_paa3_pins[] = अणु
	TEGRA_PIN_DAP2_DOUT_PAA3,
पूर्ण;

अटल स्थिर अचिन्हित aud_mclk_pbb0_pins[] = अणु
	TEGRA_PIN_AUD_MCLK_PBB0,
पूर्ण;

अटल स्थिर अचिन्हित dvfs_pwm_pbb1_pins[] = अणु
	TEGRA_PIN_DVFS_PWM_PBB1,
पूर्ण;

अटल स्थिर अचिन्हित dvfs_clk_pbb2_pins[] = अणु
	TEGRA_PIN_DVFS_CLK_PBB2,
पूर्ण;

अटल स्थिर अचिन्हित gpio_x1_aud_pbb3_pins[] = अणु
	TEGRA_PIN_GPIO_X1_AUD_PBB3,
पूर्ण;

अटल स्थिर अचिन्हित gpio_x3_aud_pbb4_pins[] = अणु
	TEGRA_PIN_GPIO_X3_AUD_PBB4,
पूर्ण;

अटल स्थिर अचिन्हित hdmi_cec_pcc0_pins[] = अणु
	TEGRA_PIN_HDMI_CEC_PCC0,
पूर्ण;

अटल स्थिर अचिन्हित hdmi_पूर्णांक_dp_hpd_pcc1_pins[] = अणु
	TEGRA_PIN_HDMI_INT_DP_HPD_PCC1,
पूर्ण;

अटल स्थिर अचिन्हित spdअगर_out_pcc2_pins[] = अणु
	TEGRA_PIN_SPDIF_OUT_PCC2,
पूर्ण;

अटल स्थिर अचिन्हित spdअगर_in_pcc3_pins[] = अणु
	TEGRA_PIN_SPDIF_IN_PCC3,
पूर्ण;

अटल स्थिर अचिन्हित usb_vbus_en0_pcc4_pins[] = अणु
	TEGRA_PIN_USB_VBUS_EN0_PCC4,
पूर्ण;

अटल स्थिर अचिन्हित usb_vbus_en1_pcc5_pins[] = अणु
	TEGRA_PIN_USB_VBUS_EN1_PCC5,
पूर्ण;

अटल स्थिर अचिन्हित dp_hpd0_pcc6_pins[] = अणु
	TEGRA_PIN_DP_HPD0_PCC6,
पूर्ण;

अटल स्थिर अचिन्हित pcc7_pins[] = अणु
	TEGRA_PIN_PCC7,
पूर्ण;

अटल स्थिर अचिन्हित spi2_cs1_pdd0_pins[] = अणु
	TEGRA_PIN_SPI2_CS1_PDD0,
पूर्ण;

अटल स्थिर अचिन्हित qspi_sck_pee0_pins[] = अणु
	TEGRA_PIN_QSPI_SCK_PEE0,
पूर्ण;

अटल स्थिर अचिन्हित qspi_cs_n_pee1_pins[] = अणु
	TEGRA_PIN_QSPI_CS_N_PEE1,
पूर्ण;

अटल स्थिर अचिन्हित qspi_io0_pee2_pins[] = अणु
	TEGRA_PIN_QSPI_IO0_PEE2,
पूर्ण;

अटल स्थिर अचिन्हित qspi_io1_pee3_pins[] = अणु
	TEGRA_PIN_QSPI_IO1_PEE3,
पूर्ण;

अटल स्थिर अचिन्हित qspi_io2_pee4_pins[] = अणु
	TEGRA_PIN_QSPI_IO2_PEE4,
पूर्ण;

अटल स्थिर अचिन्हित qspi_io3_pee5_pins[] = अणु
	TEGRA_PIN_QSPI_IO3_PEE5,
पूर्ण;

अटल स्थिर अचिन्हित core_pwr_req_pins[] = अणु
	TEGRA_PIN_CORE_PWR_REQ,
पूर्ण;

अटल स्थिर अचिन्हित cpu_pwr_req_pins[] = अणु
	TEGRA_PIN_CPU_PWR_REQ,
पूर्ण;

अटल स्थिर अचिन्हित pwr_पूर्णांक_n_pins[] = अणु
	TEGRA_PIN_PWR_INT_N,
पूर्ण;

अटल स्थिर अचिन्हित clk_32k_in_pins[] = अणु
	TEGRA_PIN_CLK_32K_IN,
पूर्ण;

अटल स्थिर अचिन्हित jtag_rtck_pins[] = अणु
	TEGRA_PIN_JTAG_RTCK,
पूर्ण;

अटल स्थिर अचिन्हित batt_bcl_pins[] = अणु
	TEGRA_PIN_BATT_BCL,
पूर्ण;

अटल स्थिर अचिन्हित clk_req_pins[] = अणु
	TEGRA_PIN_CLK_REQ,
पूर्ण;

अटल स्थिर अचिन्हित shutकरोwn_pins[] = अणु
	TEGRA_PIN_SHUTDOWN,
पूर्ण;

अटल स्थिर अचिन्हित drive_pa6_pins[] = अणु
	TEGRA_PIN_PA6,
पूर्ण;

अटल स्थिर अचिन्हित drive_pcc7_pins[] = अणु
	TEGRA_PIN_PCC7,
पूर्ण;

अटल स्थिर अचिन्हित drive_pe6_pins[] = अणु
	TEGRA_PIN_PE6,
पूर्ण;

अटल स्थिर अचिन्हित drive_pe7_pins[] = अणु
	TEGRA_PIN_PE7,
पूर्ण;

अटल स्थिर अचिन्हित drive_ph6_pins[] = अणु
	TEGRA_PIN_PH6,
पूर्ण;

अटल स्थिर अचिन्हित drive_pk0_pins[] = अणु
	TEGRA_PIN_PK0,
पूर्ण;

अटल स्थिर अचिन्हित drive_pk1_pins[] = अणु
	TEGRA_PIN_PK1,
पूर्ण;

अटल स्थिर अचिन्हित drive_pk2_pins[] = अणु
	TEGRA_PIN_PK2,
पूर्ण;

अटल स्थिर अचिन्हित drive_pk3_pins[] = अणु
	TEGRA_PIN_PK3,
पूर्ण;

अटल स्थिर अचिन्हित drive_pk4_pins[] = अणु
	TEGRA_PIN_PK4,
पूर्ण;

अटल स्थिर अचिन्हित drive_pk5_pins[] = अणु
	TEGRA_PIN_PK5,
पूर्ण;

अटल स्थिर अचिन्हित drive_pk6_pins[] = अणु
	TEGRA_PIN_PK6,
पूर्ण;

अटल स्थिर अचिन्हित drive_pk7_pins[] = अणु
	TEGRA_PIN_PK7,
पूर्ण;

अटल स्थिर अचिन्हित drive_pl0_pins[] = अणु
	TEGRA_PIN_PL0,
पूर्ण;

अटल स्थिर अचिन्हित drive_pl1_pins[] = अणु
	TEGRA_PIN_PL1,
पूर्ण;

अटल स्थिर अचिन्हित drive_pz0_pins[] = अणु
	TEGRA_PIN_PZ0,
पूर्ण;

अटल स्थिर अचिन्हित drive_pz1_pins[] = अणु
	TEGRA_PIN_PZ1,
पूर्ण;

अटल स्थिर अचिन्हित drive_pz2_pins[] = अणु
	TEGRA_PIN_PZ2,
पूर्ण;

अटल स्थिर अचिन्हित drive_pz3_pins[] = अणु
	TEGRA_PIN_PZ3,
पूर्ण;

अटल स्थिर अचिन्हित drive_pz4_pins[] = अणु
	TEGRA_PIN_PZ4,
पूर्ण;

अटल स्थिर अचिन्हित drive_pz5_pins[] = अणु
	TEGRA_PIN_PZ5,
पूर्ण;

अटल स्थिर अचिन्हित drive_sdmmc1_pins[] = अणु
	TEGRA_PIN_SDMMC1_CLK_PM0,
	TEGRA_PIN_SDMMC1_CMD_PM1,
	TEGRA_PIN_SDMMC1_DAT3_PM2,
	TEGRA_PIN_SDMMC1_DAT2_PM3,
	TEGRA_PIN_SDMMC1_DAT1_PM4,
	TEGRA_PIN_SDMMC1_DAT0_PM5,
पूर्ण;

अटल स्थिर अचिन्हित drive_sdmmc2_pins[] = अणु
पूर्ण;

अटल स्थिर अचिन्हित drive_sdmmc3_pins[] = अणु
	TEGRA_PIN_SDMMC3_CLK_PP0,
	TEGRA_PIN_SDMMC3_CMD_PP1,
	TEGRA_PIN_SDMMC3_DAT3_PP2,
	TEGRA_PIN_SDMMC3_DAT2_PP3,
	TEGRA_PIN_SDMMC3_DAT1_PP4,
	TEGRA_PIN_SDMMC3_DAT0_PP5,
पूर्ण;

अटल स्थिर अचिन्हित drive_sdmmc4_pins[] = अणु
पूर्ण;

क्रमागत tegra_mux अणु
	TEGRA_MUX_AUD,
	TEGRA_MUX_BCL,
	TEGRA_MUX_BLINK,
	TEGRA_MUX_CCLA,
	TEGRA_MUX_CEC,
	TEGRA_MUX_CLDVFS,
	TEGRA_MUX_CLK,
	TEGRA_MUX_CORE,
	TEGRA_MUX_CPU,
	TEGRA_MUX_DISPLAYA,
	TEGRA_MUX_DISPLAYB,
	TEGRA_MUX_DMIC1,
	TEGRA_MUX_DMIC2,
	TEGRA_MUX_DMIC3,
	TEGRA_MUX_DP,
	TEGRA_MUX_DTV,
	TEGRA_MUX_EXTPERIPH3,
	TEGRA_MUX_I2C1,
	TEGRA_MUX_I2C2,
	TEGRA_MUX_I2C3,
	TEGRA_MUX_I2CPMU,
	TEGRA_MUX_I2CVI,
	TEGRA_MUX_I2S1,
	TEGRA_MUX_I2S2,
	TEGRA_MUX_I2S3,
	TEGRA_MUX_I2S4A,
	TEGRA_MUX_I2S4B,
	TEGRA_MUX_I2S5A,
	TEGRA_MUX_I2S5B,
	TEGRA_MUX_IQC0,
	TEGRA_MUX_IQC1,
	TEGRA_MUX_JTAG,
	TEGRA_MUX_PE,
	TEGRA_MUX_PE0,
	TEGRA_MUX_PE1,
	TEGRA_MUX_PMI,
	TEGRA_MUX_PWM0,
	TEGRA_MUX_PWM1,
	TEGRA_MUX_PWM2,
	TEGRA_MUX_PWM3,
	TEGRA_MUX_QSPI,
	TEGRA_MUX_RSVD0,
	TEGRA_MUX_RSVD1,
	TEGRA_MUX_RSVD2,
	TEGRA_MUX_RSVD3,
	TEGRA_MUX_SATA,
	TEGRA_MUX_SDMMC1,
	TEGRA_MUX_SDMMC3,
	TEGRA_MUX_SHUTDOWN,
	TEGRA_MUX_SOC,
	TEGRA_MUX_SOR0,
	TEGRA_MUX_SOR1,
	TEGRA_MUX_SPDIF,
	TEGRA_MUX_SPI1,
	TEGRA_MUX_SPI2,
	TEGRA_MUX_SPI3,
	TEGRA_MUX_SPI4,
	TEGRA_MUX_SYS,
	TEGRA_MUX_TOUCH,
	TEGRA_MUX_UART,
	TEGRA_MUX_UARTA,
	TEGRA_MUX_UARTB,
	TEGRA_MUX_UARTC,
	TEGRA_MUX_UARTD,
	TEGRA_MUX_USB,
	TEGRA_MUX_VGP1,
	TEGRA_MUX_VGP2,
	TEGRA_MUX_VGP3,
	TEGRA_MUX_VGP4,
	TEGRA_MUX_VGP5,
	TEGRA_MUX_VGP6,
	TEGRA_MUX_VIMCLK,
	TEGRA_MUX_VIMCLK2,
पूर्ण;

#घोषणा FUNCTION(fname)					\
	अणु						\
		.name = #fname,				\
	पूर्ण

अटल काष्ठा tegra_function tegra210_functions[] = अणु
	FUNCTION(aud),
	FUNCTION(bcl),
	FUNCTION(blink),
	FUNCTION(ccla),
	FUNCTION(cec),
	FUNCTION(cldvfs),
	FUNCTION(clk),
	FUNCTION(core),
	FUNCTION(cpu),
	FUNCTION(displaya),
	FUNCTION(displayb),
	FUNCTION(dmic1),
	FUNCTION(dmic2),
	FUNCTION(dmic3),
	FUNCTION(dp),
	FUNCTION(dtv),
	FUNCTION(extperiph3),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(i2cpmu),
	FUNCTION(i2cvi),
	FUNCTION(i2s1),
	FUNCTION(i2s2),
	FUNCTION(i2s3),
	FUNCTION(i2s4a),
	FUNCTION(i2s4b),
	FUNCTION(i2s5a),
	FUNCTION(i2s5b),
	FUNCTION(iqc0),
	FUNCTION(iqc1),
	FUNCTION(jtag),
	FUNCTION(pe),
	FUNCTION(pe0),
	FUNCTION(pe1),
	FUNCTION(pmi),
	FUNCTION(pwm0),
	FUNCTION(pwm1),
	FUNCTION(pwm2),
	FUNCTION(pwm3),
	FUNCTION(qspi),
	FUNCTION(rsvd0),
	FUNCTION(rsvd1),
	FUNCTION(rsvd2),
	FUNCTION(rsvd3),
	FUNCTION(sata),
	FUNCTION(sdmmc1),
	FUNCTION(sdmmc3),
	FUNCTION(shutकरोwn),
	FUNCTION(soc),
	FUNCTION(sor0),
	FUNCTION(sor1),
	FUNCTION(spdअगर),
	FUNCTION(spi1),
	FUNCTION(spi2),
	FUNCTION(spi3),
	FUNCTION(spi4),
	FUNCTION(sys),
	FUNCTION(touch),
	FUNCTION(uart),
	FUNCTION(uarta),
	FUNCTION(uartb),
	FUNCTION(uartc),
	FUNCTION(uartd),
	FUNCTION(usb),
	FUNCTION(vgp1),
	FUNCTION(vgp2),
	FUNCTION(vgp3),
	FUNCTION(vgp4),
	FUNCTION(vgp5),
	FUNCTION(vgp6),
	FUNCTION(vimclk),
	FUNCTION(vimclk2),
पूर्ण;

#घोषणा DRV_PINGROUP_REG_A		0x8d4	/* bank 0 */
#घोषणा PINGROUP_REG_A			0x3000	/* bank 1 */

#घोषणा DRV_PINGROUP_REG(r)		((r) - DRV_PINGROUP_REG_A)
#घोषणा PINGROUP_REG(r)			((r) - PINGROUP_REG_A)

#घोषणा PINGROUP_BIT_Y(b)		(b)
#घोषणा PINGROUP_BIT_N(b)		(-1)

#घोषणा PINGROUP(pg_name, f0, f1, f2, f3, r, hsm, drvtype, e_io_hv,	\
		 rdrv, drvdn_b, drvdn_w, drvup_b, drvup_w, slwr_b,	\
		 slwr_w, slwf_b, slwf_w)				\
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
		.einput_bit = 6,					\
		.odrain_bit = 11,					\
		.lock_bit = 7,						\
		.ioreset_bit = -1,					\
		.rcv_sel_bit = PINGROUP_BIT_##e_io_hv(10),		\
		.hsm_bit = PINGROUP_BIT_##hsm(9),			\
		.schmitt_bit = 12,					\
		.drvtype_bit = PINGROUP_BIT_##drvtype(13),		\
		.drv_reg = DRV_PINGROUP_REG(rdrv),			\
		.drv_bank = 0,						\
		.lpmd_bit = -1,						\
		.drvdn_bit = drvdn_b,					\
		.drvdn_width = drvdn_w,					\
		.drvup_bit = drvup_b,					\
		.drvup_width = drvup_w,					\
		.slwr_bit = slwr_b,					\
		.slwr_width = slwr_w,					\
		.slwf_bit = slwf_b,					\
		.slwf_width = slwf_w,					\
		.parked_biपंचांगask = BIT(5),				\
	पूर्ण

#घोषणा DRV_PINGROUP(pg_name, r, prk_mask, drvdn_b, drvdn_w, drvup_b,	\
		     drvup_w, slwr_b, slwr_w, slwf_b, slwf_w)		\
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
		.hsm_bit = -1,						\
		.schmitt_bit = -1,					\
		.lpmd_bit = -1,						\
		.drvdn_bit = drvdn_b,					\
		.drvdn_width = drvdn_w,					\
		.drvup_bit = drvup_b,					\
		.drvup_width = drvup_w,					\
		.slwr_bit = slwr_b,					\
		.slwr_width = slwr_w,					\
		.slwf_bit = slwf_b,					\
		.slwf_width = slwf_w,					\
		.drvtype_bit = -1,					\
		.parked_biपंचांगask = prk_mask,				\
	पूर्ण

अटल स्थिर काष्ठा tegra_pingroup tegra210_groups[] = अणु
	/*       pg_name,              f0,         f1,     f2,    f3,    r,      hsm, drvtype, e_io_hv, rdrv,  drvdn_b, drvdn_w, drvup_b, drvup_w, slwr_b, slwr_w, slwf_b, slwf_w */
	PINGROUP(sdmmc1_clk_pm0,       SDMMC1,     RSVD1,  RSVD2, RSVD3, 0x3000, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc1_cmd_pm1,       SDMMC1,     SPI3,   RSVD2, RSVD3, 0x3004, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc1_dat3_pm2,      SDMMC1,     SPI3,   RSVD2, RSVD3, 0x3008, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc1_dat2_pm3,      SDMMC1,     SPI3,   RSVD2, RSVD3, 0x300c, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc1_dat1_pm4,      SDMMC1,     SPI3,   RSVD2, RSVD3, 0x3010, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc1_dat0_pm5,      SDMMC1,     RSVD1,  RSVD2, RSVD3, 0x3014, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc3_clk_pp0,       SDMMC3,     RSVD1,  RSVD2, RSVD3, 0x301c, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc3_cmd_pp1,       SDMMC3,     RSVD1,  RSVD2, RSVD3, 0x3020, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc3_dat0_pp5,      SDMMC3,     RSVD1,  RSVD2, RSVD3, 0x3024, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc3_dat1_pp4,      SDMMC3,     RSVD1,  RSVD2, RSVD3, 0x3028, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc3_dat2_pp3,      SDMMC3,     RSVD1,  RSVD2, RSVD3, 0x302c, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(sdmmc3_dat3_pp2,      SDMMC3,     RSVD1,  RSVD2, RSVD3, 0x3030, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pex_l0_rst_n_pa0,     PE0,        RSVD1,  RSVD2, RSVD3, 0x3038, N,   N,       Y,       0xa5c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pex_l0_clkreq_n_pa1,  PE0,        RSVD1,  RSVD2, RSVD3, 0x303c, N,   N,       Y,       0xa58, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pex_wake_n_pa2,       PE,         RSVD1,  RSVD2, RSVD3, 0x3040, N,   N,       Y,       0xa68, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pex_l1_rst_n_pa3,     PE1,        RSVD1,  RSVD2, RSVD3, 0x3044, N,   N,       Y,       0xa64, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pex_l1_clkreq_n_pa4,  PE1,        RSVD1,  RSVD2, RSVD3, 0x3048, N,   N,       Y,       0xa60, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(sata_led_active_pa5,  SATA,       RSVD1,  RSVD2, RSVD3, 0x304c, N,   N,       N,       0xa94, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(spi1_mosi_pc0,        SPI1,       RSVD1,  RSVD2, RSVD3, 0x3050, Y,   Y,       N,       0xae0, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi1_miso_pc1,        SPI1,       RSVD1,  RSVD2, RSVD3, 0x3054, Y,   Y,       N,       0xadc, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi1_sck_pc2,         SPI1,       RSVD1,  RSVD2, RSVD3, 0x3058, Y,   Y,       N,       0xae4, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi1_cs0_pc3,         SPI1,       RSVD1,  RSVD2, RSVD3, 0x305c, Y,   Y,       N,       0xad4, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi1_cs1_pc4,         SPI1,       RSVD1,  RSVD2, RSVD3, 0x3060, Y,   Y,       N,       0xad8, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi2_mosi_pb4,        SPI2,       DTV,    RSVD2, RSVD3, 0x3064, Y,   Y,       N,       0xaf4, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi2_miso_pb5,        SPI2,       DTV,    RSVD2, RSVD3, 0x3068, Y,   Y,       N,       0xaf0, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi2_sck_pb6,         SPI2,       DTV,    RSVD2, RSVD3, 0x306c, Y,   Y,       N,       0xaf8, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi2_cs0_pb7,         SPI2,       DTV,    RSVD2, RSVD3, 0x3070, Y,   Y,       N,       0xae8, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi2_cs1_pdd0,        SPI2,       RSVD1,  RSVD2, RSVD3, 0x3074, Y,   Y,       N,       0xaec, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi4_mosi_pc7,        SPI4,       RSVD1,  RSVD2, RSVD3, 0x3078, Y,   Y,       N,       0xb04, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi4_miso_pd0,        SPI4,       RSVD1,  RSVD2, RSVD3, 0x307c, Y,   Y,       N,       0xb00, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi4_sck_pc5,         SPI4,       RSVD1,  RSVD2, RSVD3, 0x3080, Y,   Y,       N,       0xb08, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(spi4_cs0_pc6,         SPI4,       RSVD1,  RSVD2, RSVD3, 0x3084, Y,   Y,       N,       0xafc, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(qspi_sck_pee0,        QSPI,       RSVD1,  RSVD2, RSVD3, 0x3088, Y,   Y,       N,       0xa90, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(qspi_cs_n_pee1,       QSPI,       RSVD1,  RSVD2, RSVD3, 0x308c, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(qspi_io0_pee2,        QSPI,       RSVD1,  RSVD2, RSVD3, 0x3090, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(qspi_io1_pee3,        QSPI,       RSVD1,  RSVD2, RSVD3, 0x3094, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(qspi_io2_pee4,        QSPI,       RSVD1,  RSVD2, RSVD3, 0x3098, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(qspi_io3_pee5,        QSPI,       RSVD1,  RSVD2, RSVD3, 0x309c, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(dmic1_clk_pe0,        DMIC1,      I2S3,   RSVD2, RSVD3, 0x30a4, N,   N,       N,       0x984, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dmic1_dat_pe1,        DMIC1,      I2S3,   RSVD2, RSVD3, 0x30a8, N,   N,       N,       0x988, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dmic2_clk_pe2,        DMIC2,      I2S3,   RSVD2, RSVD3, 0x30ac, N,   N,       N,       0x98c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dmic2_dat_pe3,        DMIC2,      I2S3,   RSVD2, RSVD3, 0x30b0, N,   N,       N,       0x990, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dmic3_clk_pe4,        DMIC3,      I2S5A,  RSVD2, RSVD3, 0x30b4, N,   N,       N,       0x994, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dmic3_dat_pe5,        DMIC3,      I2S5A,  RSVD2, RSVD3, 0x30b8, N,   N,       N,       0x998, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gen1_i2c_scl_pj1,     I2C1,       RSVD1,  RSVD2, RSVD3, 0x30bc, N,   N,       Y,       0x9a8, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gen1_i2c_sda_pj0,     I2C1,       RSVD1,  RSVD2, RSVD3, 0x30c0, N,   N,       Y,       0x9ac, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gen2_i2c_scl_pj2,     I2C2,       RSVD1,  RSVD2, RSVD3, 0x30c4, N,   N,       Y,       0x9b0, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gen2_i2c_sda_pj3,     I2C2,       RSVD1,  RSVD2, RSVD3, 0x30c8, N,   N,       Y,       0x9b4, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gen3_i2c_scl_pf0,     I2C3,       RSVD1,  RSVD2, RSVD3, 0x30cc, N,   N,       Y,       0x9b8, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gen3_i2c_sda_pf1,     I2C3,       RSVD1,  RSVD2, RSVD3, 0x30d0, N,   N,       Y,       0x9bc, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam_i2c_scl_ps2,      I2C3,       I2CVI,  RSVD2, RSVD3, 0x30d4, N,   N,       Y,       0x934, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam_i2c_sda_ps3,      I2C3,       I2CVI,  RSVD2, RSVD3, 0x30d8, N,   N,       Y,       0x938, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pwr_i2c_scl_py3,      I2CPMU,     RSVD1,  RSVD2, RSVD3, 0x30dc, N,   N,       Y,       0xa6c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pwr_i2c_sda_py4,      I2CPMU,     RSVD1,  RSVD2, RSVD3, 0x30e0, N,   N,       Y,       0xa70, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart1_tx_pu0,         UARTA,      RSVD1,  RSVD2, RSVD3, 0x30e4, N,   N,       N,       0xb28, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart1_rx_pu1,         UARTA,      RSVD1,  RSVD2, RSVD3, 0x30e8, N,   N,       N,       0xb24, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart1_rts_pu2,        UARTA,      RSVD1,  RSVD2, RSVD3, 0x30ec, N,   N,       N,       0xb20, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart1_cts_pu3,        UARTA,      RSVD1,  RSVD2, RSVD3, 0x30f0, N,   N,       N,       0xb1c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart2_tx_pg0,         UARTB,      I2S4A,  SPDIF, UART,  0x30f4, N,   N,       N,       0xb38, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart2_rx_pg1,         UARTB,      I2S4A,  SPDIF, UART,  0x30f8, N,   N,       N,       0xb34, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart2_rts_pg2,        UARTB,      I2S4A,  RSVD2, UART,  0x30fc, N,   N,       N,       0xb30, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart2_cts_pg3,        UARTB,      I2S4A,  RSVD2, UART,  0x3100, N,   N,       N,       0xb2c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart3_tx_pd1,         UARTC,      SPI4,   RSVD2, RSVD3, 0x3104, N,   N,       N,       0xb48, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart3_rx_pd2,         UARTC,      SPI4,   RSVD2, RSVD3, 0x3108, N,   N,       N,       0xb44, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart3_rts_pd3,        UARTC,      SPI4,   RSVD2, RSVD3, 0x310c, N,   N,       N,       0xb40, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart3_cts_pd4,        UARTC,      SPI4,   RSVD2, RSVD3, 0x3110, N,   N,       N,       0xb3c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart4_tx_pi4,         UARTD,      UART,   RSVD2, RSVD3, 0x3114, N,   N,       N,       0xb58, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart4_rx_pi5,         UARTD,      UART,   RSVD2, RSVD3, 0x3118, N,   N,       N,       0xb54, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart4_rts_pi6,        UARTD,      UART,   RSVD2, RSVD3, 0x311c, N,   N,       N,       0xb50, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(uart4_cts_pi7,        UARTD,      UART,   RSVD2, RSVD3, 0x3120, N,   N,       N,       0xb4c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dap1_fs_pb0,          I2S1,       RSVD1,  RSVD2, RSVD3, 0x3124, Y,   Y,       N,       0x95c, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(dap1_din_pb1,         I2S1,       RSVD1,  RSVD2, RSVD3, 0x3128, Y,   Y,       N,       0x954, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(dap1_करोut_pb2,        I2S1,       RSVD1,  RSVD2, RSVD3, 0x312c, Y,   Y,       N,       0x958, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(dap1_sclk_pb3,        I2S1,       RSVD1,  RSVD2, RSVD3, 0x3130, Y,   Y,       N,       0x960, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(dap2_fs_paa0,         I2S2,       RSVD1,  RSVD2, RSVD3, 0x3134, Y,   Y,       N,       0x96c, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(dap2_din_paa2,        I2S2,       RSVD1,  RSVD2, RSVD3, 0x3138, Y,   Y,       N,       0x964, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(dap2_करोut_paa3,       I2S2,       RSVD1,  RSVD2, RSVD3, 0x313c, Y,   Y,       N,       0x968, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(dap2_sclk_paa1,       I2S2,       RSVD1,  RSVD2, RSVD3, 0x3140, Y,   Y,       N,       0x970, -1,      -1,      -1,      -1,      28,     2,      30,     2),
	PINGROUP(dap4_fs_pj4,          I2S4B,      RSVD1,  RSVD2, RSVD3, 0x3144, N,   N,       N,       0x97c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dap4_din_pj5,         I2S4B,      RSVD1,  RSVD2, RSVD3, 0x3148, N,   N,       N,       0x974, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dap4_करोut_pj6,        I2S4B,      RSVD1,  RSVD2, RSVD3, 0x314c, N,   N,       N,       0x978, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dap4_sclk_pj7,        I2S4B,      RSVD1,  RSVD2, RSVD3, 0x3150, N,   N,       N,       0x980, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam1_mclk_ps0,        EXTPERIPH3, RSVD1,  RSVD2, RSVD3, 0x3154, N,   N,       N,       0x918, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam2_mclk_ps1,        EXTPERIPH3, RSVD1,  RSVD2, RSVD3, 0x3158, N,   N,       N,       0x924, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(jtag_rtck,            JTAG,       RSVD1,  RSVD2, RSVD3, 0x315c, N,   N,       N,       0xa2c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(clk_32k_in,           CLK,        RSVD1,  RSVD2, RSVD3, 0x3160, N,   N,       N,       0x940, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(clk_32k_out_py5,      SOC,        BLINK,  RSVD2, RSVD3, 0x3164, N,   N,       N,       0x944, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(batt_bcl,             BCL,        RSVD1,  RSVD2, RSVD3, 0x3168, N,   N,       Y,       0x8f8, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(clk_req,              SYS,        RSVD1,  RSVD2, RSVD3, 0x316c, N,   N,       N,       0x948, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cpu_pwr_req,          CPU,        RSVD1,  RSVD2, RSVD3, 0x3170, N,   N,       N,       0x950, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pwr_पूर्णांक_n,            PMI,        RSVD1,  RSVD2, RSVD3, 0x3174, N,   N,       N,       0xa74, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(shutकरोwn,             SHUTDOWN,   RSVD1,  RSVD2, RSVD3, 0x3178, N,   N,       N,       0xac8, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(core_pwr_req,         CORE,       RSVD1,  RSVD2, RSVD3, 0x317c, N,   N,       N,       0x94c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(aud_mclk_pbb0,        AUD,        RSVD1,  RSVD2, RSVD3, 0x3180, N,   N,       N,       0x8f4, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dvfs_pwm_pbb1,        RSVD0,      CLDVFS, SPI3,  RSVD3, 0x3184, N,   N,       N,       0x9a4, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dvfs_clk_pbb2,        RSVD0,      CLDVFS, SPI3,  RSVD3, 0x3188, N,   N,       N,       0x9a0, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gpio_x1_aud_pbb3,     RSVD0,      RSVD1,  SPI3,  RSVD3, 0x318c, N,   N,       N,       0xa14, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gpio_x3_aud_pbb4,     RSVD0,      RSVD1,  SPI3,  RSVD3, 0x3190, N,   N,       N,       0xa18, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pcc7,                 RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3194, N,   N,       Y,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(hdmi_cec_pcc0,        CEC,        RSVD1,  RSVD2, RSVD3, 0x3198, N,   N,       Y,       0xa24, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(hdmi_पूर्णांक_dp_hpd_pcc1, DP,         RSVD1,  RSVD2, RSVD3, 0x319c, N,   N,       Y,       0xa28, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(spdअगर_out_pcc2,       SPDIF,      RSVD1,  RSVD2, RSVD3, 0x31a0, N,   N,       N,       0xad0, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(spdअगर_in_pcc3,        SPDIF,      RSVD1,  RSVD2, RSVD3, 0x31a4, N,   N,       N,       0xacc, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(usb_vbus_en0_pcc4,    USB,        RSVD1,  RSVD2, RSVD3, 0x31a8, N,   N,       Y,       0xb5c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(usb_vbus_en1_pcc5,    USB,        RSVD1,  RSVD2, RSVD3, 0x31ac, N,   N,       Y,       0xb60, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(dp_hpd0_pcc6,         DP,         RSVD1,  RSVD2, RSVD3, 0x31b0, N,   N,       N,       0x99c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(wअगरi_en_ph0,          RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31b4, N,   N,       N,       0xb64, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(wअगरi_rst_ph1,         RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31b8, N,   N,       N,       0xb68, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(wअगरi_wake_ap_ph2,     RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31bc, N,   N,       N,       0xb6c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(ap_wake_bt_ph3,       RSVD0,      UARTB,  SPDIF, RSVD3, 0x31c0, N,   N,       N,       0x8ec, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(bt_rst_ph4,           RSVD0,      UARTB,  SPDIF, RSVD3, 0x31c4, N,   N,       N,       0x8fc, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(bt_wake_ap_ph5,       RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31c8, N,   N,       N,       0x900, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(ap_wake_nfc_ph7,      RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31cc, N,   N,       N,       0x8f0, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(nfc_en_pi0,           RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31d0, N,   N,       N,       0xa50, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(nfc_पूर्णांक_pi1,          RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31d4, N,   N,       N,       0xa54, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gps_en_pi2,           RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31d8, N,   N,       N,       0xa1c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(gps_rst_pi3,          RSVD0,      RSVD1,  RSVD2, RSVD3, 0x31dc, N,   N,       N,       0xa20, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam_rst_ps4,          VGP1,       RSVD1,  RSVD2, RSVD3, 0x31e0, N,   N,       N,       0x93c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam_af_en_ps5,        VIMCLK,     VGP2,   RSVD2, RSVD3, 0x31e4, N,   N,       N,       0x92c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam_flash_en_ps6,     VIMCLK,     VGP3,   RSVD2, RSVD3, 0x31e8, N,   N,       N,       0x930, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam1_pwdn_ps7,        VGP4,       RSVD1,  RSVD2, RSVD3, 0x31ec, N,   N,       N,       0x91c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam2_pwdn_pt0,        VGP5,       RSVD1,  RSVD2, RSVD3, 0x31f0, N,   N,       N,       0x928, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(cam1_strobe_pt1,      VGP6,       RSVD1,  RSVD2, RSVD3, 0x31f4, N,   N,       N,       0x920, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(lcd_te_py2,           DISPLAYA,   RSVD1,  RSVD2, RSVD3, 0x31f8, N,   N,       N,       0xa44, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(lcd_bl_pwm_pv0,       DISPLAYA,   PWM0,   SOR0,  RSVD3, 0x31fc, N,   N,       N,       0xa34, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(lcd_bl_en_pv1,        RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3200, N,   N,       N,       0xa30, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(lcd_rst_pv2,          RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3204, N,   N,       N,       0xa40, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(lcd_gpio1_pv3,        DISPLAYB,   RSVD1,  RSVD2, RSVD3, 0x3208, N,   N,       N,       0xa38, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(lcd_gpio2_pv4,        DISPLAYB,   PWM1,   RSVD2, SOR1,  0x320c, N,   N,       N,       0xa3c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(ap_पढ़ोy_pv5,         RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3210, N,   N,       N,       0x8e8, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(touch_rst_pv6,        RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3214, N,   N,       N,       0xb18, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(touch_clk_pv7,        TOUCH,      RSVD1,  RSVD2, RSVD3, 0x3218, N,   N,       N,       0xb10, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(modem_wake_ap_px0,    RSVD0,      RSVD1,  RSVD2, RSVD3, 0x321c, N,   N,       N,       0xa48, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(touch_पूर्णांक_px1,        RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3220, N,   N,       N,       0xb14, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(motion_पूर्णांक_px2,       RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3224, N,   N,       N,       0xa4c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(als_prox_पूर्णांक_px3,     RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3228, N,   N,       N,       0x8e4, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(temp_alert_px4,       RSVD0,      RSVD1,  RSVD2, RSVD3, 0x322c, N,   N,       N,       0xb0c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(button_घातer_on_px5,  RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3230, N,   N,       N,       0x908, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(button_vol_up_px6,    RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3234, N,   N,       N,       0x914, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(button_vol_करोwn_px7,  RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3238, N,   N,       N,       0x910, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(button_slide_sw_py0,  RSVD0,      RSVD1,  RSVD2, RSVD3, 0x323c, N,   N,       N,       0x90c, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(button_home_py1,      RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3240, N,   N,       N,       0x904, 12,      5,       20,      5,       -1,     -1,     -1,     -1),
	PINGROUP(pa6,                  SATA,       RSVD1,  RSVD2, RSVD3, 0x3244, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pe6,                  RSVD0,      I2S5A,  PWM2,  RSVD3, 0x3248, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pe7,                  RSVD0,      I2S5A,  PWM3,  RSVD3, 0x324c, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(ph6,                  RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3250, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pk0,                  IQC0,       I2S5B,  RSVD2, RSVD3, 0x3254, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pk1,                  IQC0,       I2S5B,  RSVD2, RSVD3, 0x3258, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pk2,                  IQC0,       I2S5B,  RSVD2, RSVD3, 0x325c, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pk3,                  IQC0,       I2S5B,  RSVD2, RSVD3, 0x3260, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pk4,                  IQC1,       RSVD1,  RSVD2, RSVD3, 0x3264, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pk5,                  IQC1,       RSVD1,  RSVD2, RSVD3, 0x3268, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pk6,                  IQC1,       RSVD1,  RSVD2, RSVD3, 0x326c, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pk7,                  IQC1,       RSVD1,  RSVD2, RSVD3, 0x3270, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pl0,                  RSVD0,      RSVD1,  RSVD2, RSVD3, 0x3274, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pl1,                  SOC,        RSVD1,  RSVD2, RSVD3, 0x3278, Y,   Y,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pz0,                  VIMCLK2,    RSVD1,  RSVD2, RSVD3, 0x327c, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pz1,                  VIMCLK2,    SDMMC1, RSVD2, RSVD3, 0x3280, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pz2,                  SDMMC3,     CCLA,   RSVD2, RSVD3, 0x3284, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pz3,                  SDMMC3,     RSVD1,  RSVD2, RSVD3, 0x3288, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pz4,                  SDMMC1,     RSVD1,  RSVD2, RSVD3, 0x328c, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),
	PINGROUP(pz5,                  SOC,        RSVD1,  RSVD2, RSVD3, 0x3290, N,   N,       N,       -1,    -1,      -1,      -1,      -1,      -1,     -1,     -1,     -1),

	/* pg_name, r, prk_mask, drvdn_b, drvdn_w, drvup_b, drvup_w, slwr_b, slwr_w, slwf_b, slwf_w */
	DRV_PINGROUP(pa6,    0x9c0, 0x0,       12, 5,  20, 5,  -1, -1, -1, -1),
	DRV_PINGROUP(pcc7,   0x9c4, 0x0,       12, 5,  20, 5,  -1, -1, -1, -1),
	DRV_PINGROUP(pe6,    0x9c8, 0x0,       12, 5,  20, 5,  -1, -1, -1, -1),
	DRV_PINGROUP(pe7,    0x9cc, 0x0,       12, 5,  20, 5,  -1, -1, -1, -1),
	DRV_PINGROUP(ph6,    0x9d0, 0x0,       12, 5,  20, 5,  -1, -1, -1, -1),
	DRV_PINGROUP(pk0,    0x9d4, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pk1,    0x9d8, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pk2,    0x9dc, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pk3,    0x9e0, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pk4,    0x9e4, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pk5,    0x9e8, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pk6,    0x9ec, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pk7,    0x9f0, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pl0,    0x9f4, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pl1,    0x9f8, 0x0,       -1, -1, -1, -1, 28, 2,  30, 2),
	DRV_PINGROUP(pz0,    0x9fc, 0x0,       12, 7,  20, 7,  -1, -1, -1, -1),
	DRV_PINGROUP(pz1,    0xa00, 0x0,       12, 7,  20, 7,  -1, -1, -1, -1),
	DRV_PINGROUP(pz2,    0xa04, 0x0,       12, 7,  20, 7,  -1, -1, -1, -1),
	DRV_PINGROUP(pz3,    0xa08, 0x0,       12, 7,  20, 7,  -1, -1, -1, -1),
	DRV_PINGROUP(pz4,    0xa0c, 0x0,       12, 7,  20, 7,  -1, -1, -1, -1),
	DRV_PINGROUP(pz5,    0xa10, 0x0,       12, 7,  20, 7,  -1, -1, -1, -1),
	DRV_PINGROUP(sdmmc1, 0xa98, 0x0,       12, 7,  20, 7,  28, 2,  30, 2),
	DRV_PINGROUP(sdmmc2, 0xa9c, 0x7ffc000, 2,  6,  8,  6,  28, 2,  30, 2),
	DRV_PINGROUP(sdmmc3, 0xab0, 0x0,       12, 7,  20, 7,  28, 2,  30, 2),
	DRV_PINGROUP(sdmmc4, 0xab4, 0x7ffc000, 2,  6,  8,  6,  28, 2,  30, 2),
पूर्ण;

अटल स्थिर काष्ठा tegra_pinctrl_soc_data tegra210_pinctrl = अणु
	.ngpios = NUM_GPIOS,
	.gpio_compatible = "nvidia,tegra210-gpio",
	.pins = tegra210_pins,
	.npins = ARRAY_SIZE(tegra210_pins),
	.functions = tegra210_functions,
	.nfunctions = ARRAY_SIZE(tegra210_functions),
	.groups = tegra210_groups,
	.ngroups = ARRAY_SIZE(tegra210_groups),
	.hsm_in_mux = true,
	.schmitt_in_mux = true,
	.drvtype_in_mux = true,
पूर्ण;

अटल पूर्णांक tegra210_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस tegra_pinctrl_probe(pdev, &tegra210_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra210_pinctrl_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-pinmux", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra210_pinctrl_driver = अणु
	.driver = अणु
		.name = "tegra210-pinctrl",
		.of_match_table = tegra210_pinctrl_of_match,
		.pm = &tegra_pinctrl_pm,
	पूर्ण,
	.probe = tegra210_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init tegra210_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tegra210_pinctrl_driver);
पूर्ण
arch_initcall(tegra210_pinctrl_init);
