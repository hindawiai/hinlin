<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The MT7629 driver based on Linux generic pinctrl binding.
 *
 * Copyright (C) 2018 MediaTek Inc.
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश "pinctrl-moore.h"

#घोषणा MT7629_PIN(_number, _name, _eपूर्णांक_n)				\
	MTK_PIN(_number, _name, 0, _eपूर्णांक_n, DRV_GRP1)

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_mode_range[] = अणु
	PIN_FIELD(0, 78, 0x300, 0x10, 0, 4),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_dir_range[] = अणु
	PIN_FIELD(0, 78, 0x0, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_di_range[] = अणु
	PIN_FIELD(0, 78, 0x200, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_करो_range[] = अणु
	PIN_FIELD(0, 78, 0x100, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_ies_range[] = अणु
	PIN_FIELD(0, 10, 0x1000, 0x10, 0, 1),
	PIN_FIELD(11, 18, 0x2000, 0x10, 0, 1),
	PIN_FIELD(19, 32, 0x3000, 0x10, 0, 1),
	PIN_FIELD(33, 48, 0x4000, 0x10, 0, 1),
	PIN_FIELD(49, 50, 0x5000, 0x10, 0, 1),
	PIN_FIELD(51, 69, 0x6000, 0x10, 0, 1),
	PIN_FIELD(70, 78, 0x7000, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_smt_range[] = अणु
	PIN_FIELD(0, 10, 0x1100, 0x10, 0, 1),
	PIN_FIELD(11, 18, 0x2100, 0x10, 0, 1),
	PIN_FIELD(19, 32, 0x3100, 0x10, 0, 1),
	PIN_FIELD(33, 48, 0x4100, 0x10, 0, 1),
	PIN_FIELD(49, 50, 0x5100, 0x10, 0, 1),
	PIN_FIELD(51, 69, 0x6100, 0x10, 0, 1),
	PIN_FIELD(70, 78, 0x7100, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_pullen_range[] = अणु
	PIN_FIELD(0, 10, 0x1400, 0x10, 0, 1),
	PIN_FIELD(11, 18, 0x2400, 0x10, 0, 1),
	PIN_FIELD(19, 32, 0x3400, 0x10, 0, 1),
	PIN_FIELD(33, 48, 0x4400, 0x10, 0, 1),
	PIN_FIELD(49, 50, 0x5400, 0x10, 0, 1),
	PIN_FIELD(51, 69, 0x6400, 0x10, 0, 1),
	PIN_FIELD(70, 78, 0x7400, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_pullsel_range[] = अणु
	PIN_FIELD(0, 10, 0x1500, 0x10, 0, 1),
	PIN_FIELD(11, 18, 0x2500, 0x10, 0, 1),
	PIN_FIELD(19, 32, 0x3500, 0x10, 0, 1),
	PIN_FIELD(33, 48, 0x4500, 0x10, 0, 1),
	PIN_FIELD(49, 50, 0x5500, 0x10, 0, 1),
	PIN_FIELD(51, 69, 0x6500, 0x10, 0, 1),
	PIN_FIELD(70, 78, 0x7500, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_drv_range[] = अणु
	PIN_FIELD(0, 10, 0x1600, 0x10, 0, 4),
	PIN_FIELD(11, 18, 0x2600, 0x10, 0, 4),
	PIN_FIELD(19, 32, 0x3600, 0x10, 0, 4),
	PIN_FIELD(33, 48, 0x4600, 0x10, 0, 4),
	PIN_FIELD(49, 50, 0x5600, 0x10, 0, 4),
	PIN_FIELD(51, 69, 0x6600, 0x10, 0, 4),
	PIN_FIELD(70, 78, 0x7600, 0x10, 0, 4),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_tdsel_range[] = अणु
	PIN_FIELD(0, 10, 0x1200, 0x10, 0, 4),
	PIN_FIELD(11, 18, 0x2200, 0x10, 0, 4),
	PIN_FIELD(19, 32, 0x3200, 0x10, 0, 4),
	PIN_FIELD(33, 48, 0x4200, 0x10, 0, 4),
	PIN_FIELD(49, 50, 0x5200, 0x10, 0, 4),
	PIN_FIELD(51, 69, 0x6200, 0x10, 0, 4),
	PIN_FIELD(70, 78, 0x7200, 0x10, 0, 4),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7629_pin_rdsel_range[] = अणु
	PIN_FIELD(0, 10, 0x1300, 0x10, 0, 4),
	PIN_FIELD(11, 18, 0x2300, 0x10, 0, 4),
	PIN_FIELD(19, 32, 0x3300, 0x10, 0, 4),
	PIN_FIELD(33, 48, 0x4300, 0x10, 0, 4),
	PIN_FIELD(49, 50, 0x5300, 0x10, 0, 4),
	PIN_FIELD(51, 69, 0x6300, 0x10, 0, 4),
	PIN_FIELD(70, 78, 0x7300, 0x10, 0, 4),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_reg_calc mt7629_reg_cals[] = अणु
	[PINCTRL_PIN_REG_MODE] = MTK_RANGE(mt7629_pin_mode_range),
	[PINCTRL_PIN_REG_सूची] = MTK_RANGE(mt7629_pin_dir_range),
	[PINCTRL_PIN_REG_DI] = MTK_RANGE(mt7629_pin_di_range),
	[PINCTRL_PIN_REG_DO] = MTK_RANGE(mt7629_pin_करो_range),
	[PINCTRL_PIN_REG_IES] = MTK_RANGE(mt7629_pin_ies_range),
	[PINCTRL_PIN_REG_SMT] = MTK_RANGE(mt7629_pin_smt_range),
	[PINCTRL_PIN_REG_PULLSEL] = MTK_RANGE(mt7629_pin_pullsel_range),
	[PINCTRL_PIN_REG_PULLEN] = MTK_RANGE(mt7629_pin_pullen_range),
	[PINCTRL_PIN_REG_DRV] = MTK_RANGE(mt7629_pin_drv_range),
	[PINCTRL_PIN_REG_TDSEL] = MTK_RANGE(mt7629_pin_tdsel_range),
	[PINCTRL_PIN_REG_RDSEL] = MTK_RANGE(mt7629_pin_rdsel_range),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_desc mt7629_pins[] = अणु
	MT7629_PIN(0, "TOP_5G_CLK", 53),
	MT7629_PIN(1, "TOP_5G_DATA", 54),
	MT7629_PIN(2, "WF0_5G_HB0", 55),
	MT7629_PIN(3, "WF0_5G_HB1", 56),
	MT7629_PIN(4, "WF0_5G_HB2", 57),
	MT7629_PIN(5, "WF0_5G_HB3", 58),
	MT7629_PIN(6, "WF0_5G_HB4", 59),
	MT7629_PIN(7, "WF0_5G_HB5", 60),
	MT7629_PIN(8, "WF0_5G_HB6", 61),
	MT7629_PIN(9, "XO_REQ", 9),
	MT7629_PIN(10, "TOP_RST_N", 10),
	MT7629_PIN(11, "SYS_WATCHDOG", 11),
	MT7629_PIN(12, "EPHY_LED0_N_JTDO", 12),
	MT7629_PIN(13, "EPHY_LED1_N_JTDI", 13),
	MT7629_PIN(14, "EPHY_LED2_N_JTMS", 14),
	MT7629_PIN(15, "EPHY_LED3_N_JTCLK", 15),
	MT7629_PIN(16, "EPHY_LED4_N_JTRST_N", 16),
	MT7629_PIN(17, "WF2G_LED_N", 17),
	MT7629_PIN(18, "WF5G_LED_N", 18),
	MT7629_PIN(19, "I2C_SDA", 19),
	MT7629_PIN(20, "I2C_SCL", 20),
	MT7629_PIN(21, "GPIO_9", 21),
	MT7629_PIN(22, "GPIO_10", 22),
	MT7629_PIN(23, "GPIO_11", 23),
	MT7629_PIN(24, "GPIO_12", 24),
	MT7629_PIN(25, "UART1_TXD", 25),
	MT7629_PIN(26, "UART1_RXD", 26),
	MT7629_PIN(27, "UART1_CTS", 27),
	MT7629_PIN(28, "UART1_RTS", 28),
	MT7629_PIN(29, "UART2_TXD", 29),
	MT7629_PIN(30, "UART2_RXD", 30),
	MT7629_PIN(31, "UART2_CTS", 31),
	MT7629_PIN(32, "UART2_RTS", 32),
	MT7629_PIN(33, "MDI_TP_P1", 33),
	MT7629_PIN(34, "MDI_TN_P1", 34),
	MT7629_PIN(35, "MDI_RP_P1", 35),
	MT7629_PIN(36, "MDI_RN_P1", 36),
	MT7629_PIN(37, "MDI_RP_P2", 37),
	MT7629_PIN(38, "MDI_RN_P2", 38),
	MT7629_PIN(39, "MDI_TP_P2", 39),
	MT7629_PIN(40, "MDI_TN_P2", 40),
	MT7629_PIN(41, "MDI_TP_P3", 41),
	MT7629_PIN(42, "MDI_TN_P3", 42),
	MT7629_PIN(43, "MDI_RP_P3", 43),
	MT7629_PIN(44, "MDI_RN_P3", 44),
	MT7629_PIN(45, "MDI_RP_P4", 45),
	MT7629_PIN(46, "MDI_RN_P4", 46),
	MT7629_PIN(47, "MDI_TP_P4", 47),
	MT7629_PIN(48, "MDI_TN_P4", 48),
	MT7629_PIN(49, "SMI_MDC", 49),
	MT7629_PIN(50, "SMI_MDIO", 50),
	MT7629_PIN(51, "PCIE_PERESET_N", 51),
	MT7629_PIN(52, "PWM_0", 52),
	MT7629_PIN(53, "GPIO_0", 0),
	MT7629_PIN(54, "GPIO_1", 1),
	MT7629_PIN(55, "GPIO_2", 2),
	MT7629_PIN(56, "GPIO_3", 3),
	MT7629_PIN(57, "GPIO_4", 4),
	MT7629_PIN(58, "GPIO_5", 5),
	MT7629_PIN(59, "GPIO_6", 6),
	MT7629_PIN(60, "GPIO_7", 7),
	MT7629_PIN(61, "GPIO_8", 8),
	MT7629_PIN(62, "SPI_CLK", 62),
	MT7629_PIN(63, "SPI_CS", 63),
	MT7629_PIN(64, "SPI_MOSI", 64),
	MT7629_PIN(65, "SPI_MISO", 65),
	MT7629_PIN(66, "SPI_WP", 66),
	MT7629_PIN(67, "SPI_HOLD", 67),
	MT7629_PIN(68, "UART0_TXD", 68),
	MT7629_PIN(69, "UART0_RXD", 69),
	MT7629_PIN(70, "TOP_2G_CLK", 70),
	MT7629_PIN(71, "TOP_2G_DATA", 71),
	MT7629_PIN(72, "WF0_2G_HB0", 72),
	MT7629_PIN(73, "WF0_2G_HB1", 73),
	MT7629_PIN(74, "WF0_2G_HB2", 74),
	MT7629_PIN(75, "WF0_2G_HB3", 75),
	MT7629_PIN(76, "WF0_2G_HB4", 76),
	MT7629_PIN(77, "WF0_2G_HB5", 77),
	MT7629_PIN(78, "WF0_2G_HB6", 78),
पूर्ण;

/* List all groups consisting of these pins dedicated to the enablement of
 * certain hardware block and the corresponding mode क्रम all of the pins.
 * The hardware probably has multiple combinations of these pinouts.
 */

/* LED क्रम EPHY */
अटल पूर्णांक mt7629_ephy_leds_pins[] = अणु 12, 13, 14, 15, 16, 17, 18, पूर्ण;
अटल पूर्णांक mt7629_ephy_leds_funcs[] = अणु 1, 1, 1, 1, 1, 1, 1, पूर्ण;
अटल पूर्णांक mt7629_ephy_led0_pins[] = अणु 12, पूर्ण;
अटल पूर्णांक mt7629_ephy_led0_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_ephy_led1_pins[] = अणु 13, पूर्ण;
अटल पूर्णांक mt7629_ephy_led1_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_ephy_led2_pins[] = अणु 14, पूर्ण;
अटल पूर्णांक mt7629_ephy_led2_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_ephy_led3_pins[] = अणु 15, पूर्ण;
अटल पूर्णांक mt7629_ephy_led3_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_ephy_led4_pins[] = अणु 16, पूर्ण;
अटल पूर्णांक mt7629_ephy_led4_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_wf2g_led_pins[] = अणु 17, पूर्ण;
अटल पूर्णांक mt7629_wf2g_led_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_wf5g_led_pins[] = अणु 18, पूर्ण;
अटल पूर्णांक mt7629_wf5g_led_funcs[] = अणु 1, पूर्ण;

/* Watchकरोg */
अटल पूर्णांक mt7629_watchकरोg_pins[] = अणु 11, पूर्ण;
अटल पूर्णांक mt7629_watchकरोg_funcs[] = अणु 1, पूर्ण;

/* LED क्रम GPHY */
अटल पूर्णांक mt7629_gphy_leds_0_pins[] = अणु 21, 22, 23, पूर्ण;
अटल पूर्णांक mt7629_gphy_leds_0_funcs[] = अणु 2, 2, 2, पूर्ण;
अटल पूर्णांक mt7629_gphy_led1_0_pins[] = अणु 21, पूर्ण;
अटल पूर्णांक mt7629_gphy_led1_0_funcs[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7629_gphy_led2_0_pins[] = अणु 22, पूर्ण;
अटल पूर्णांक mt7629_gphy_led2_0_funcs[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7629_gphy_led3_0_pins[] = अणु 23, पूर्ण;
अटल पूर्णांक mt7629_gphy_led3_0_funcs[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7629_gphy_leds_1_pins[] = अणु 57, 58, 59, पूर्ण;
अटल पूर्णांक mt7629_gphy_leds_1_funcs[] = अणु 1, 1, 1, पूर्ण;
अटल पूर्णांक mt7629_gphy_led1_1_pins[] = अणु 57, पूर्ण;
अटल पूर्णांक mt7629_gphy_led1_1_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_gphy_led2_1_pins[] = अणु 58, पूर्ण;
अटल पूर्णांक mt7629_gphy_led2_1_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_gphy_led3_1_pins[] = अणु 59, पूर्ण;
अटल पूर्णांक mt7629_gphy_led3_1_funcs[] = अणु 1, पूर्ण;

/* I2C */
अटल पूर्णांक mt7629_i2c_0_pins[] = अणु 19, 20, पूर्ण;
अटल पूर्णांक mt7629_i2c_0_funcs[] = अणु 1, 1, पूर्ण;
अटल पूर्णांक mt7629_i2c_1_pins[] = अणु 53, 54, पूर्ण;
अटल पूर्णांक mt7629_i2c_1_funcs[] = अणु 1, 1, पूर्ण;

/* SPI */
अटल पूर्णांक mt7629_spi_0_pins[] = अणु 21, 22, 23, 24, पूर्ण;
अटल पूर्णांक mt7629_spi_0_funcs[] = अणु 1, 1, 1, 1, पूर्ण;
अटल पूर्णांक mt7629_spi_1_pins[] = अणु 62, 63, 64, 65, पूर्ण;
अटल पूर्णांक mt7629_spi_1_funcs[] = अणु 1, 1, 1, 1, पूर्ण;
अटल पूर्णांक mt7629_spi_wp_pins[] = अणु 66, पूर्ण;
अटल पूर्णांक mt7629_spi_wp_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_spi_hold_pins[] = अणु 67, पूर्ण;
अटल पूर्णांक mt7629_spi_hold_funcs[] = अणु 1, पूर्ण;

/* UART */
अटल पूर्णांक mt7629_uart1_0_txd_rxd_pins[] = अणु 25, 26, पूर्ण;
अटल पूर्णांक mt7629_uart1_0_txd_rxd_funcs[] = अणु 1, 1, पूर्ण;
अटल पूर्णांक mt7629_uart1_1_txd_rxd_pins[] = अणु 53, 54, पूर्ण;
अटल पूर्णांक mt7629_uart1_1_txd_rxd_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7629_uart2_0_txd_rxd_pins[] = अणु 29, 30, पूर्ण;
अटल पूर्णांक mt7629_uart2_0_txd_rxd_funcs[] = अणु 1, 1, पूर्ण;
अटल पूर्णांक mt7629_uart2_1_txd_rxd_pins[] = अणु 57, 58, पूर्ण;
अटल पूर्णांक mt7629_uart2_1_txd_rxd_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7629_uart1_0_cts_rts_pins[] = अणु 27, 28, पूर्ण;
अटल पूर्णांक mt7629_uart1_0_cts_rts_funcs[] = अणु 1, 1, पूर्ण;
अटल पूर्णांक mt7629_uart1_1_cts_rts_pins[] = अणु 55, 56, पूर्ण;
अटल पूर्णांक mt7629_uart1_1_cts_rts_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7629_uart2_0_cts_rts_pins[] = अणु 31, 32, पूर्ण;
अटल पूर्णांक mt7629_uart2_0_cts_rts_funcs[] = अणु 1, 1, पूर्ण;
अटल पूर्णांक mt7629_uart2_1_cts_rts_pins[] = अणु 59, 60, पूर्ण;
अटल पूर्णांक mt7629_uart2_1_cts_rts_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7629_uart0_txd_rxd_pins[] = अणु 68, 69, पूर्ण;
अटल पूर्णांक mt7629_uart0_txd_rxd_funcs[] = अणु 1, 1, पूर्ण;

/* MDC/MDIO */
अटल पूर्णांक mt7629_mdc_mdio_pins[] = अणु 49, 50, पूर्ण;
अटल पूर्णांक mt7629_mdc_mdio_funcs[] = अणु 1, 1, पूर्ण;

/* PCIE */
अटल पूर्णांक mt7629_pcie_pereset_pins[] = अणु 51, पूर्ण;
अटल पूर्णांक mt7629_pcie_pereset_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_pcie_wake_pins[] = अणु 55, पूर्ण;
अटल पूर्णांक mt7629_pcie_wake_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_pcie_clkreq_pins[] = अणु 56, पूर्ण;
अटल पूर्णांक mt7629_pcie_clkreq_funcs[] = अणु 1, पूर्ण;

/* PWM */
अटल पूर्णांक mt7629_pwm_0_pins[] = अणु 52, पूर्ण;
अटल पूर्णांक mt7629_pwm_0_funcs[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7629_pwm_1_pins[] = अणु 61, पूर्ण;
अटल पूर्णांक mt7629_pwm_1_funcs[] = अणु 2, पूर्ण;

/* WF 2G */
अटल पूर्णांक mt7629_wf0_2g_pins[] = अणु 70, 71, 72, 73, 74, 75, 76, 77, 78, पूर्ण;
अटल पूर्णांक mt7629_wf0_2g_funcs[] = अणु 1, 1, 1, 1, 1, 1, 1, 1, पूर्ण;

/* WF 5G */
अटल पूर्णांक mt7629_wf0_5g_pins[] = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, पूर्ण;
अटल पूर्णांक mt7629_wf0_5g_funcs[] = अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, पूर्ण;

/* SNFI */
अटल पूर्णांक mt7629_snfi_pins[] = अणु 62, 63, 64, 65, 66, 67 पूर्ण;
अटल पूर्णांक mt7629_snfi_funcs[] = अणु 2, 2, 2, 2, 2, 2 पूर्ण;

/* SPI NOR */
अटल पूर्णांक mt7629_snor_pins[] = अणु 62, 63, 64, 65, 66, 67 पूर्ण;
अटल पूर्णांक mt7629_snor_funcs[] = अणु 1, 1, 1, 1, 1, 1 पूर्ण;

अटल स्थिर काष्ठा group_desc mt7629_groups[] = अणु
	PINCTRL_PIN_GROUP("ephy_leds", mt7629_ephy_leds),
	PINCTRL_PIN_GROUP("ephy_led0", mt7629_ephy_led0),
	PINCTRL_PIN_GROUP("ephy_led1", mt7629_ephy_led1),
	PINCTRL_PIN_GROUP("ephy_led2", mt7629_ephy_led2),
	PINCTRL_PIN_GROUP("ephy_led3", mt7629_ephy_led3),
	PINCTRL_PIN_GROUP("ephy_led4", mt7629_ephy_led4),
	PINCTRL_PIN_GROUP("wf2g_led", mt7629_wf2g_led),
	PINCTRL_PIN_GROUP("wf5g_led", mt7629_wf5g_led),
	PINCTRL_PIN_GROUP("watchdog", mt7629_watchकरोg),
	PINCTRL_PIN_GROUP("gphy_leds_0", mt7629_gphy_leds_0),
	PINCTRL_PIN_GROUP("gphy_led1_0", mt7629_gphy_led1_0),
	PINCTRL_PIN_GROUP("gphy_led2_0", mt7629_gphy_led2_0),
	PINCTRL_PIN_GROUP("gphy_led3_0", mt7629_gphy_led3_0),
	PINCTRL_PIN_GROUP("gphy_leds_1", mt7629_gphy_leds_1),
	PINCTRL_PIN_GROUP("gphy_led1_1", mt7629_gphy_led1_1),
	PINCTRL_PIN_GROUP("gphy_led2_1", mt7629_gphy_led2_1),
	PINCTRL_PIN_GROUP("gphy_led3_1", mt7629_gphy_led3_1),
	PINCTRL_PIN_GROUP("i2c_0", mt7629_i2c_0),
	PINCTRL_PIN_GROUP("i2c_1", mt7629_i2c_1),
	PINCTRL_PIN_GROUP("spi_0", mt7629_spi_0),
	PINCTRL_PIN_GROUP("spi_1", mt7629_spi_1),
	PINCTRL_PIN_GROUP("spi_wp", mt7629_spi_wp),
	PINCTRL_PIN_GROUP("spi_hold", mt7629_spi_hold),
	PINCTRL_PIN_GROUP("uart1_0_txd_rxd", mt7629_uart1_0_txd_rxd),
	PINCTRL_PIN_GROUP("uart1_1_txd_rxd", mt7629_uart1_1_txd_rxd),
	PINCTRL_PIN_GROUP("uart2_0_txd_rxd", mt7629_uart2_0_txd_rxd),
	PINCTRL_PIN_GROUP("uart2_1_txd_rxd", mt7629_uart2_1_txd_rxd),
	PINCTRL_PIN_GROUP("uart1_0_cts_rts", mt7629_uart1_0_cts_rts),
	PINCTRL_PIN_GROUP("uart1_1_cts_rts", mt7629_uart1_1_cts_rts),
	PINCTRL_PIN_GROUP("uart2_0_cts_rts", mt7629_uart2_0_cts_rts),
	PINCTRL_PIN_GROUP("uart2_1_cts_rts", mt7629_uart2_1_cts_rts),
	PINCTRL_PIN_GROUP("uart0_txd_rxd", mt7629_uart0_txd_rxd),
	PINCTRL_PIN_GROUP("mdc_mdio", mt7629_mdc_mdio),
	PINCTRL_PIN_GROUP("pcie_pereset", mt7629_pcie_pereset),
	PINCTRL_PIN_GROUP("pcie_wake", mt7629_pcie_wake),
	PINCTRL_PIN_GROUP("pcie_clkreq", mt7629_pcie_clkreq),
	PINCTRL_PIN_GROUP("pwm_0", mt7629_pwm_0),
	PINCTRL_PIN_GROUP("pwm_1", mt7629_pwm_1),
	PINCTRL_PIN_GROUP("wf0_5g", mt7629_wf0_5g),
	PINCTRL_PIN_GROUP("wf0_2g", mt7629_wf0_2g),
	PINCTRL_PIN_GROUP("snfi", mt7629_snfi),
	PINCTRL_PIN_GROUP("spi_nor", mt7629_snor),
पूर्ण;

/* Joपूर्णांक those groups owning the same capability in user poपूर्णांक of view which
 * allows that people tend to use through the device tree.
 */
अटल स्थिर अक्षर *mt7629_ethernet_groups[] = अणु "mdc_mdio", पूर्ण;
अटल स्थिर अक्षर *mt7629_i2c_groups[] = अणु "i2c_0", "i2c_1", पूर्ण;
अटल स्थिर अक्षर *mt7629_led_groups[] = अणु "ephy_leds", "ephy_led0",
					   "ephy_led1", "ephy_led2",
					   "ephy_led3", "ephy_led4",
					   "wf2g_led", "wf5g_led",
					   "gphy_leds_0", "gphy_led1_0",
					   "gphy_led2_0", "gphy_led3_0",
					   "gphy_leds_1", "gphy_led1_1",
					   "gphy_led2_1", "gphy_led3_1",पूर्ण;
अटल स्थिर अक्षर *mt7629_pcie_groups[] = अणु "pcie_pereset", "pcie_wake",
					    "pcie_clkreq", पूर्ण;
अटल स्थिर अक्षर *mt7629_pwm_groups[] = अणु "pwm_0", "pwm_1", पूर्ण;
अटल स्थिर अक्षर *mt7629_spi_groups[] = अणु "spi_0", "spi_1", "spi_wp",
					   "spi_hold", पूर्ण;
अटल स्थिर अक्षर *mt7629_uart_groups[] = अणु "uart1_0_txd_rxd",
					    "uart1_1_txd_rxd",
					    "uart2_0_txd_rxd",
					    "uart2_1_txd_rxd",
					    "uart1_0_cts_rts",
					    "uart1_1_cts_rts",
					    "uart2_0_cts_rts",
					    "uart2_1_cts_rts",
					    "uart0_txd_rxd", पूर्ण;
अटल स्थिर अक्षर *mt7629_wdt_groups[] = अणु "watchdog", पूर्ण;
अटल स्थिर अक्षर *mt7629_wअगरi_groups[] = अणु "wf0_5g", "wf0_2g", पूर्ण;
अटल स्थिर अक्षर *mt7629_flash_groups[] = अणु "snfi", "spi_nor" पूर्ण;

अटल स्थिर काष्ठा function_desc mt7629_functions[] = अणु
	अणु"eth",	mt7629_ethernet_groups, ARRAY_SIZE(mt7629_ethernet_groups)पूर्ण,
	अणु"i2c", mt7629_i2c_groups, ARRAY_SIZE(mt7629_i2c_groups)पूर्ण,
	अणु"led",	mt7629_led_groups, ARRAY_SIZE(mt7629_led_groups)पूर्ण,
	अणु"pcie", mt7629_pcie_groups, ARRAY_SIZE(mt7629_pcie_groups)पूर्ण,
	अणु"pwm",	mt7629_pwm_groups, ARRAY_SIZE(mt7629_pwm_groups)पूर्ण,
	अणु"spi",	mt7629_spi_groups, ARRAY_SIZE(mt7629_spi_groups)पूर्ण,
	अणु"uart", mt7629_uart_groups, ARRAY_SIZE(mt7629_uart_groups)पूर्ण,
	अणु"watchdog", mt7629_wdt_groups, ARRAY_SIZE(mt7629_wdt_groups)पूर्ण,
	अणु"wifi", mt7629_wअगरi_groups, ARRAY_SIZE(mt7629_wअगरi_groups)पूर्ण,
	अणु"flash", mt7629_flash_groups, ARRAY_SIZE(mt7629_flash_groups)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_eपूर्णांक_hw mt7629_eपूर्णांक_hw = अणु
	.port_mask = 7,
	.ports     = 7,
	.ap_num    = ARRAY_SIZE(mt7629_pins),
	.db_cnt    = 16,
पूर्ण;

अटल काष्ठा mtk_pin_soc mt7629_data = अणु
	.reg_cal = mt7629_reg_cals,
	.pins = mt7629_pins,
	.npins = ARRAY_SIZE(mt7629_pins),
	.grps = mt7629_groups,
	.ngrps = ARRAY_SIZE(mt7629_groups),
	.funcs = mt7629_functions,
	.nfuncs = ARRAY_SIZE(mt7629_functions),
	.eपूर्णांक_hw = &mt7629_eपूर्णांक_hw,
	.gpio_m = 0,
	.ies_present = true,
	.base_names = mtk_शेष_रेजिस्टर_base_names,
	.nbase_names = ARRAY_SIZE(mtk_शेष_रेजिस्टर_base_names),
	.bias_disable_set = mtk_pinconf_bias_disable_set_rev1,
	.bias_disable_get = mtk_pinconf_bias_disable_get_rev1,
	.bias_set = mtk_pinconf_bias_set_rev1,
	.bias_get = mtk_pinconf_bias_get_rev1,
	.drive_set = mtk_pinconf_drive_set_rev1,
	.drive_get = mtk_pinconf_drive_get_rev1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mt7629_pinctrl_of_match[] = अणु
	अणु .compatible = "mediatek,mt7629-pinctrl", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक mt7629_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस mtk_moore_pinctrl_probe(pdev, &mt7629_data);
पूर्ण

अटल काष्ठा platक्रमm_driver mt7629_pinctrl_driver = अणु
	.driver = अणु
		.name = "mt7629-pinctrl",
		.of_match_table = mt7629_pinctrl_of_match,
	पूर्ण,
	.probe = mt7629_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init mt7629_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mt7629_pinctrl_driver);
पूर्ण
arch_initcall(mt7629_pinctrl_init);
