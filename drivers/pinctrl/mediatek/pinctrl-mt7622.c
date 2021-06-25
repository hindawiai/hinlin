<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017-2018 MediaTek Inc.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश "pinctrl-moore.h"

#घोषणा MT7622_PIN(_number, _name)					\
	MTK_PIN(_number, _name, 1, _number, DRV_GRP0)

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_mode_range[] = अणु
	PIN_FIELD(0, 0, 0x320, 0x10, 16, 4),
	PIN_FIELD(1, 4, 0x3a0, 0x10, 16, 4),
	PIN_FIELD(5, 5, 0x320, 0x10, 0, 4),
	PINS_FIELD(6, 7, 0x300, 0x10, 4, 4),
	PIN_FIELD(8, 9, 0x350, 0x10, 20, 4),
	PINS_FIELD(10, 13, 0x300, 0x10, 8, 4),
	PIN_FIELD(14, 15, 0x320, 0x10, 4, 4),
	PIN_FIELD(16, 17, 0x320, 0x10, 20, 4),
	PIN_FIELD(18, 21, 0x310, 0x10, 16, 4),
	PIN_FIELD(22, 22, 0x380, 0x10, 16, 4),
	PINS_FIELD(23, 24, 0x300, 0x10, 24, 4),
	PINS_FIELD(25, 36, 0x300, 0x10, 12, 4),
	PINS_FIELD(37, 50, 0x300, 0x10, 20, 4),
	PIN_FIELD(51, 70, 0x330, 0x10, 4, 4),
	PINS_FIELD(71, 72, 0x300, 0x10, 16, 4),
	PIN_FIELD(73, 76, 0x310, 0x10, 0, 4),
	PIN_FIELD(77, 77, 0x320, 0x10, 28, 4),
	PIN_FIELD(78, 78, 0x320, 0x10, 12, 4),
	PIN_FIELD(79, 82, 0x3a0, 0x10, 0, 4),
	PIN_FIELD(83, 83, 0x350, 0x10, 28, 4),
	PIN_FIELD(84, 84, 0x330, 0x10, 0, 4),
	PIN_FIELD(85, 90, 0x360, 0x10, 4, 4),
	PIN_FIELD(91, 94, 0x390, 0x10, 16, 4),
	PIN_FIELD(95, 97, 0x380, 0x10, 20, 4),
	PIN_FIELD(98, 101, 0x390, 0x10, 0, 4),
	PIN_FIELD(102, 102, 0x360, 0x10, 0, 4),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_dir_range[] = अणु
	PIN_FIELD(0, 102, 0x0, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_di_range[] = अणु
	PIN_FIELD(0, 102, 0x200, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_करो_range[] = अणु
	PIN_FIELD(0, 102, 0x100, 0x10, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_sr_range[] = अणु
	PIN_FIELD(0, 31, 0x910, 0x10, 0, 1),
	PIN_FIELD(32, 50, 0xa10, 0x10, 0, 1),
	PIN_FIELD(51, 70, 0x810, 0x10, 0, 1),
	PIN_FIELD(71, 72, 0xb10, 0x10, 0, 1),
	PIN_FIELD(73, 86, 0xb10, 0x10, 4, 1),
	PIN_FIELD(87, 90, 0xc10, 0x10, 0, 1),
	PIN_FIELD(91, 102, 0xb10, 0x10, 18, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_smt_range[] = अणु
	PIN_FIELD(0, 31, 0x920, 0x10, 0, 1),
	PIN_FIELD(32, 50, 0xa20, 0x10, 0, 1),
	PIN_FIELD(51, 70, 0x820, 0x10, 0, 1),
	PIN_FIELD(71, 72, 0xb20, 0x10, 0, 1),
	PIN_FIELD(73, 86, 0xb20, 0x10, 4, 1),
	PIN_FIELD(87, 90, 0xc20, 0x10, 0, 1),
	PIN_FIELD(91, 102, 0xb20, 0x10, 18, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_pu_range[] = अणु
	PIN_FIELD(0, 31, 0x930, 0x10, 0, 1),
	PIN_FIELD(32, 50, 0xa30, 0x10, 0, 1),
	PIN_FIELD(51, 70, 0x830, 0x10, 0, 1),
	PIN_FIELD(71, 72, 0xb30, 0x10, 0, 1),
	PIN_FIELD(73, 86, 0xb30, 0x10, 4, 1),
	PIN_FIELD(87, 90, 0xc30, 0x10, 0, 1),
	PIN_FIELD(91, 102, 0xb30, 0x10, 18, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_pd_range[] = अणु
	PIN_FIELD(0, 31, 0x940, 0x10, 0, 1),
	PIN_FIELD(32, 50, 0xa40, 0x10, 0, 1),
	PIN_FIELD(51, 70, 0x840, 0x10, 0, 1),
	PIN_FIELD(71, 72, 0xb40, 0x10, 0, 1),
	PIN_FIELD(73, 86, 0xb40, 0x10, 4, 1),
	PIN_FIELD(87, 90, 0xc40, 0x10, 0, 1),
	PIN_FIELD(91, 102, 0xb40, 0x10, 18, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_e4_range[] = अणु
	PIN_FIELD(0, 31, 0x960, 0x10, 0, 1),
	PIN_FIELD(32, 50, 0xa60, 0x10, 0, 1),
	PIN_FIELD(51, 70, 0x860, 0x10, 0, 1),
	PIN_FIELD(71, 72, 0xb60, 0x10, 0, 1),
	PIN_FIELD(73, 86, 0xb60, 0x10, 4, 1),
	PIN_FIELD(87, 90, 0xc60, 0x10, 0, 1),
	PIN_FIELD(91, 102, 0xb60, 0x10, 18, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_e8_range[] = अणु
	PIN_FIELD(0, 31, 0x970, 0x10, 0, 1),
	PIN_FIELD(32, 50, 0xa70, 0x10, 0, 1),
	PIN_FIELD(51, 70, 0x870, 0x10, 0, 1),
	PIN_FIELD(71, 72, 0xb70, 0x10, 0, 1),
	PIN_FIELD(73, 86, 0xb70, 0x10, 4, 1),
	PIN_FIELD(87, 90, 0xc70, 0x10, 0, 1),
	PIN_FIELD(91, 102, 0xb70, 0x10, 18, 1),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_tdsel_range[] = अणु
	PIN_FIELD(0, 31, 0x980, 0x4, 0, 4),
	PIN_FIELD(32, 50, 0xa80, 0x4, 0, 4),
	PIN_FIELD(51, 70, 0x880, 0x4, 0, 4),
	PIN_FIELD(71, 72, 0xb80, 0x4, 0, 4),
	PIN_FIELD(73, 86, 0xb80, 0x4, 16, 4),
	PIN_FIELD(87, 90, 0xc80, 0x4, 0, 4),
	PIN_FIELD(91, 102, 0xb88, 0x4, 8, 4),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_field_calc mt7622_pin_rdsel_range[] = अणु
	PIN_FIELD(0, 31, 0x990, 0x4, 0, 6),
	PIN_FIELD(32, 50, 0xa90, 0x4, 0, 6),
	PIN_FIELD(51, 58, 0x890, 0x4, 0, 6),
	PIN_FIELD(59, 60, 0x894, 0x4, 28, 6),
	PIN_FIELD(61, 62, 0x894, 0x4, 16, 6),
	PIN_FIELD(63, 66, 0x898, 0x4, 8, 6),
	PIN_FIELD(67, 68, 0x89c, 0x4, 12, 6),
	PIN_FIELD(69, 70, 0x89c, 0x4, 0, 6),
	PIN_FIELD(71, 72, 0xb90, 0x4, 0, 6),
	PIN_FIELD(73, 86, 0xb90, 0x4, 24, 6),
	PIN_FIELD(87, 90, 0xc90, 0x4, 0, 6),
	PIN_FIELD(91, 102, 0xb9c, 0x4, 12, 6),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_reg_calc mt7622_reg_cals[PINCTRL_PIN_REG_MAX] = अणु
	[PINCTRL_PIN_REG_MODE] = MTK_RANGE(mt7622_pin_mode_range),
	[PINCTRL_PIN_REG_सूची] = MTK_RANGE(mt7622_pin_dir_range),
	[PINCTRL_PIN_REG_DI] = MTK_RANGE(mt7622_pin_di_range),
	[PINCTRL_PIN_REG_DO] = MTK_RANGE(mt7622_pin_करो_range),
	[PINCTRL_PIN_REG_SR] = MTK_RANGE(mt7622_pin_sr_range),
	[PINCTRL_PIN_REG_SMT] = MTK_RANGE(mt7622_pin_smt_range),
	[PINCTRL_PIN_REG_PU] = MTK_RANGE(mt7622_pin_pu_range),
	[PINCTRL_PIN_REG_PD] = MTK_RANGE(mt7622_pin_pd_range),
	[PINCTRL_PIN_REG_E4] = MTK_RANGE(mt7622_pin_e4_range),
	[PINCTRL_PIN_REG_E8] = MTK_RANGE(mt7622_pin_e8_range),
	[PINCTRL_PIN_REG_TDSEL] = MTK_RANGE(mt7622_pin_tdsel_range),
	[PINCTRL_PIN_REG_RDSEL] = MTK_RANGE(mt7622_pin_rdsel_range),
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_desc mt7622_pins[] = अणु
	MT7622_PIN(0, "GPIO_A"),
	MT7622_PIN(1, "I2S1_IN"),
	MT7622_PIN(2, "I2S1_OUT"),
	MT7622_PIN(3, "I2S_BCLK"),
	MT7622_PIN(4, "I2S_WS"),
	MT7622_PIN(5, "I2S_MCLK"),
	MT7622_PIN(6, "TXD0"),
	MT7622_PIN(7, "RXD0"),
	MT7622_PIN(8, "SPI_WP"),
	MT7622_PIN(9, "SPI_HOLD"),
	MT7622_PIN(10, "SPI_CLK"),
	MT7622_PIN(11, "SPI_MOSI"),
	MT7622_PIN(12, "SPI_MISO"),
	MT7622_PIN(13, "SPI_CS"),
	MT7622_PIN(14, "I2C_SDA"),
	MT7622_PIN(15, "I2C_SCL"),
	MT7622_PIN(16, "I2S2_IN"),
	MT7622_PIN(17, "I2S3_IN"),
	MT7622_PIN(18, "I2S4_IN"),
	MT7622_PIN(19, "I2S2_OUT"),
	MT7622_PIN(20, "I2S3_OUT"),
	MT7622_PIN(21, "I2S4_OUT"),
	MT7622_PIN(22, "GPIO_B"),
	MT7622_PIN(23, "MDC"),
	MT7622_PIN(24, "MDIO"),
	MT7622_PIN(25, "G2_TXD0"),
	MT7622_PIN(26, "G2_TXD1"),
	MT7622_PIN(27, "G2_TXD2"),
	MT7622_PIN(28, "G2_TXD3"),
	MT7622_PIN(29, "G2_TXEN"),
	MT7622_PIN(30, "G2_TXC"),
	MT7622_PIN(31, "G2_RXD0"),
	MT7622_PIN(32, "G2_RXD1"),
	MT7622_PIN(33, "G2_RXD2"),
	MT7622_PIN(34, "G2_RXD3"),
	MT7622_PIN(35, "G2_RXDV"),
	MT7622_PIN(36, "G2_RXC"),
	MT7622_PIN(37, "NCEB"),
	MT7622_PIN(38, "NWEB"),
	MT7622_PIN(39, "NREB"),
	MT7622_PIN(40, "NDL4"),
	MT7622_PIN(41, "NDL5"),
	MT7622_PIN(42, "NDL6"),
	MT7622_PIN(43, "NDL7"),
	MT7622_PIN(44, "NRB"),
	MT7622_PIN(45, "NCLE"),
	MT7622_PIN(46, "NALE"),
	MT7622_PIN(47, "NDL0"),
	MT7622_PIN(48, "NDL1"),
	MT7622_PIN(49, "NDL2"),
	MT7622_PIN(50, "NDL3"),
	MT7622_PIN(51, "MDI_TP_P0"),
	MT7622_PIN(52, "MDI_TN_P0"),
	MT7622_PIN(53, "MDI_RP_P0"),
	MT7622_PIN(54, "MDI_RN_P0"),
	MT7622_PIN(55, "MDI_TP_P1"),
	MT7622_PIN(56, "MDI_TN_P1"),
	MT7622_PIN(57, "MDI_RP_P1"),
	MT7622_PIN(58, "MDI_RN_P1"),
	MT7622_PIN(59, "MDI_RP_P2"),
	MT7622_PIN(60, "MDI_RN_P2"),
	MT7622_PIN(61, "MDI_TP_P2"),
	MT7622_PIN(62, "MDI_TN_P2"),
	MT7622_PIN(63, "MDI_TP_P3"),
	MT7622_PIN(64, "MDI_TN_P3"),
	MT7622_PIN(65, "MDI_RP_P3"),
	MT7622_PIN(66, "MDI_RN_P3"),
	MT7622_PIN(67, "MDI_RP_P4"),
	MT7622_PIN(68, "MDI_RN_P4"),
	MT7622_PIN(69, "MDI_TP_P4"),
	MT7622_PIN(70, "MDI_TN_P4"),
	MT7622_PIN(71, "PMIC_SCL"),
	MT7622_PIN(72, "PMIC_SDA"),
	MT7622_PIN(73, "SPIC1_CLK"),
	MT7622_PIN(74, "SPIC1_MOSI"),
	MT7622_PIN(75, "SPIC1_MISO"),
	MT7622_PIN(76, "SPIC1_CS"),
	MT7622_PIN(77, "GPIO_D"),
	MT7622_PIN(78, "WATCHDOG"),
	MT7622_PIN(79, "RTS3_N"),
	MT7622_PIN(80, "CTS3_N"),
	MT7622_PIN(81, "TXD3"),
	MT7622_PIN(82, "RXD3"),
	MT7622_PIN(83, "PERST0_N"),
	MT7622_PIN(84, "PERST1_N"),
	MT7622_PIN(85, "WLED_N"),
	MT7622_PIN(86, "EPHY_LED0_N"),
	MT7622_PIN(87, "AUXIN0"),
	MT7622_PIN(88, "AUXIN1"),
	MT7622_PIN(89, "AUXIN2"),
	MT7622_PIN(90, "AUXIN3"),
	MT7622_PIN(91, "TXD4"),
	MT7622_PIN(92, "RXD4"),
	MT7622_PIN(93, "RTS4_N"),
	MT7622_PIN(94, "CTS4_N"),
	MT7622_PIN(95, "PWM1"),
	MT7622_PIN(96, "PWM2"),
	MT7622_PIN(97, "PWM3"),
	MT7622_PIN(98, "PWM4"),
	MT7622_PIN(99, "PWM5"),
	MT7622_PIN(100, "PWM6"),
	MT7622_PIN(101, "PWM7"),
	MT7622_PIN(102, "GPIO_E"),
पूर्ण;

/* List all groups consisting of these pins dedicated to the enablement of
 * certain hardware block and the corresponding mode क्रम all of the pins. The
 * hardware probably has multiple combinations of these pinouts.
 */

/* ANTSEL */
अटल पूर्णांक mt7622_antsel0_pins[] = अणु 91, पूर्ण;
अटल पूर्णांक mt7622_antsel0_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel1_pins[] = अणु 92, पूर्ण;
अटल पूर्णांक mt7622_antsel1_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel2_pins[] = अणु 93, पूर्ण;
अटल पूर्णांक mt7622_antsel2_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel3_pins[] = अणु 94, पूर्ण;
अटल पूर्णांक mt7622_antsel3_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel4_pins[] = अणु 95, पूर्ण;
अटल पूर्णांक mt7622_antsel4_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel5_pins[] = अणु 96, पूर्ण;
अटल पूर्णांक mt7622_antsel5_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel6_pins[] = अणु 97, पूर्ण;
अटल पूर्णांक mt7622_antsel6_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel7_pins[] = अणु 98, पूर्ण;
अटल पूर्णांक mt7622_antsel7_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel8_pins[] = अणु 99, पूर्ण;
अटल पूर्णांक mt7622_antsel8_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel9_pins[] = अणु 100, पूर्ण;
अटल पूर्णांक mt7622_antsel9_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel10_pins[] = अणु 101, पूर्ण;
अटल पूर्णांक mt7622_antsel10_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel11_pins[] = अणु 102, पूर्ण;
अटल पूर्णांक mt7622_antsel11_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel12_pins[] = अणु 73, पूर्ण;
अटल पूर्णांक mt7622_antsel12_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel13_pins[] = अणु 74, पूर्ण;
अटल पूर्णांक mt7622_antsel13_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel14_pins[] = अणु 75, पूर्ण;
अटल पूर्णांक mt7622_antsel14_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel15_pins[] = अणु 76, पूर्ण;
अटल पूर्णांक mt7622_antsel15_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel16_pins[] = अणु 77, पूर्ण;
अटल पूर्णांक mt7622_antsel16_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel17_pins[] = अणु 22, पूर्ण;
अटल पूर्णांक mt7622_antsel17_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel18_pins[] = अणु 79, पूर्ण;
अटल पूर्णांक mt7622_antsel18_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel19_pins[] = अणु 80, पूर्ण;
अटल पूर्णांक mt7622_antsel19_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel20_pins[] = अणु 81, पूर्ण;
अटल पूर्णांक mt7622_antsel20_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel21_pins[] = अणु 82, पूर्ण;
अटल पूर्णांक mt7622_antsel21_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel22_pins[] = अणु 14, पूर्ण;
अटल पूर्णांक mt7622_antsel22_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel23_pins[] = अणु 15, पूर्ण;
अटल पूर्णांक mt7622_antsel23_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel24_pins[] = अणु 16, पूर्ण;
अटल पूर्णांक mt7622_antsel24_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel25_pins[] = अणु 17, पूर्ण;
अटल पूर्णांक mt7622_antsel25_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel26_pins[] = अणु 18, पूर्ण;
अटल पूर्णांक mt7622_antsel26_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel27_pins[] = अणु 19, पूर्ण;
अटल पूर्णांक mt7622_antsel27_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel28_pins[] = अणु 20, पूर्ण;
अटल पूर्णांक mt7622_antsel28_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_antsel29_pins[] = अणु 21, पूर्ण;
अटल पूर्णांक mt7622_antsel29_funcs[] = अणु 5, पूर्ण;

/* EMMC */
अटल पूर्णांक mt7622_emmc_pins[] = अणु 40, 41, 42, 43, 44, 45, 47, 48, 49, 50, पूर्ण;
अटल पूर्णांक mt7622_emmc_funcs[] = अणु 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, पूर्ण;

अटल पूर्णांक mt7622_emmc_rst_pins[] = अणु 37, पूर्ण;
अटल पूर्णांक mt7622_emmc_rst_funcs[] = अणु 1, पूर्ण;

/* LED क्रम EPHY */
अटल पूर्णांक mt7622_ephy_leds_pins[] = अणु 86, 91, 92, 93, 94, पूर्ण;
अटल पूर्णांक mt7622_ephy_leds_funcs[] = अणु 0, 0, 0, 0, 0, पूर्ण;
अटल पूर्णांक mt7622_ephy0_led_pins[] = अणु 86, पूर्ण;
अटल पूर्णांक mt7622_ephy0_led_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_ephy1_led_pins[] = अणु 91, पूर्ण;
अटल पूर्णांक mt7622_ephy1_led_funcs[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7622_ephy2_led_pins[] = अणु 92, पूर्ण;
अटल पूर्णांक mt7622_ephy2_led_funcs[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7622_ephy3_led_pins[] = अणु 93, पूर्ण;
अटल पूर्णांक mt7622_ephy3_led_funcs[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7622_ephy4_led_pins[] = अणु 94, पूर्ण;
अटल पूर्णांक mt7622_ephy4_led_funcs[] = अणु 2, पूर्ण;

/* Embedded Switch */
अटल पूर्णांक mt7622_esw_pins[] = अणु 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
				 62, 63, 64, 65, 66, 67, 68, 69, 70, पूर्ण;
अटल पूर्णांक mt7622_esw_funcs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				  0, 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण;
अटल पूर्णांक mt7622_esw_p0_p1_pins[] = अणु 51, 52, 53, 54, 55, 56, 57, 58, पूर्ण;
अटल पूर्णांक mt7622_esw_p0_p1_funcs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण;
अटल पूर्णांक mt7622_esw_p2_p3_p4_pins[] = अणु 59, 60, 61, 62, 63, 64, 65, 66, 67,
					  68, 69, 70, पूर्ण;
अटल पूर्णांक mt7622_esw_p2_p3_p4_funcs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   0, 0, 0, पूर्ण;
/* RGMII via ESW */
अटल पूर्णांक mt7622_rgmii_via_esw_pins[] = अणु 59, 60, 61, 62, 63, 64, 65, 66,
					   67, 68, 69, 70, पूर्ण;
अटल पूर्णांक mt7622_rgmii_via_esw_funcs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					    0, पूर्ण;

/* RGMII via GMAC1 */
अटल पूर्णांक mt7622_rgmii_via_gmac1_pins[] = अणु 59, 60, 61, 62, 63, 64, 65, 66,
					     67, 68, 69, 70, पूर्ण;
अटल पूर्णांक mt7622_rgmii_via_gmac1_funcs[] = अणु 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
					      2, पूर्ण;

/* RGMII via GMAC2 */
अटल पूर्णांक mt7622_rgmii_via_gmac2_pins[] = अणु 25, 26, 27, 28, 29, 30, 31, 32,
					     33, 34, 35, 36, पूर्ण;
अटल पूर्णांक mt7622_rgmii_via_gmac2_funcs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, पूर्ण;

/* I2C */
अटल पूर्णांक mt7622_i2c0_pins[] = अणु 14, 15, पूर्ण;
अटल पूर्णांक mt7622_i2c0_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_i2c1_0_pins[] = अणु 55, 56, पूर्ण;
अटल पूर्णांक mt7622_i2c1_0_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_i2c1_1_pins[] = अणु 73, 74, पूर्ण;
अटल पूर्णांक mt7622_i2c1_1_funcs[] = अणु 3, 3, पूर्ण;
अटल पूर्णांक mt7622_i2c1_2_pins[] = अणु 87, 88, पूर्ण;
अटल पूर्णांक mt7622_i2c1_2_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_i2c2_0_pins[] = अणु 57, 58, पूर्ण;
अटल पूर्णांक mt7622_i2c2_0_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_i2c2_1_pins[] = अणु 75, 76, पूर्ण;
अटल पूर्णांक mt7622_i2c2_1_funcs[] = अणु 3, 3, पूर्ण;
अटल पूर्णांक mt7622_i2c2_2_pins[] = अणु 89, 90, पूर्ण;
अटल पूर्णांक mt7622_i2c2_2_funcs[] = अणु 0, 0, पूर्ण;

/* I2S */
अटल पूर्णांक mt7622_i2s_in_mclk_bclk_ws_pins[] = अणु 3, 4, 5, पूर्ण;
अटल पूर्णांक mt7622_i2s_in_mclk_bclk_ws_funcs[] = अणु 3, 3, 0, पूर्ण;
अटल पूर्णांक mt7622_i2s1_in_data_pins[] = अणु 1, पूर्ण;
अटल पूर्णांक mt7622_i2s1_in_data_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_i2s2_in_data_pins[] = अणु 16, पूर्ण;
अटल पूर्णांक mt7622_i2s2_in_data_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_i2s3_in_data_pins[] = अणु 17, पूर्ण;
अटल पूर्णांक mt7622_i2s3_in_data_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_i2s4_in_data_pins[] = अणु 18, पूर्ण;
अटल पूर्णांक mt7622_i2s4_in_data_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_i2s_out_mclk_bclk_ws_pins[] = अणु 3, 4, 5, पूर्ण;
अटल पूर्णांक mt7622_i2s_out_mclk_bclk_ws_funcs[] = अणु 0, 0, 0, पूर्ण;
अटल पूर्णांक mt7622_i2s1_out_data_pins[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7622_i2s1_out_data_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_i2s2_out_data_pins[] = अणु 19, पूर्ण;
अटल पूर्णांक mt7622_i2s2_out_data_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_i2s3_out_data_pins[] = अणु 20, पूर्ण;
अटल पूर्णांक mt7622_i2s3_out_data_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_i2s4_out_data_pins[] = अणु 21, पूर्ण;
अटल पूर्णांक mt7622_i2s4_out_data_funcs[] = अणु 0, पूर्ण;

/* IR */
अटल पूर्णांक mt7622_ir_0_tx_pins[] = अणु 16, पूर्ण;
अटल पूर्णांक mt7622_ir_0_tx_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_ir_1_tx_pins[] = अणु 59, पूर्ण;
अटल पूर्णांक mt7622_ir_1_tx_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_ir_2_tx_pins[] = अणु 99, पूर्ण;
अटल पूर्णांक mt7622_ir_2_tx_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_ir_0_rx_pins[] = अणु 17, पूर्ण;
अटल पूर्णांक mt7622_ir_0_rx_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_ir_1_rx_pins[] = अणु 60, पूर्ण;
अटल पूर्णांक mt7622_ir_1_rx_funcs[] = अणु 5, पूर्ण;
अटल पूर्णांक mt7622_ir_2_rx_pins[] = अणु 100, पूर्ण;
अटल पूर्णांक mt7622_ir_2_rx_funcs[] = अणु 3, पूर्ण;

/* MDIO */
अटल पूर्णांक mt7622_mdc_mdio_pins[] = अणु 23, 24, पूर्ण;
अटल पूर्णांक mt7622_mdc_mdio_funcs[] = अणु 0, 0, पूर्ण;

/* PCIE */
अटल पूर्णांक mt7622_pcie0_0_waken_pins[] = अणु 14, पूर्ण;
अटल पूर्णांक mt7622_pcie0_0_waken_funcs[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7622_pcie0_0_clkreq_pins[] = अणु 15, पूर्ण;
अटल पूर्णांक mt7622_pcie0_0_clkreq_funcs[] = अणु 2, पूर्ण;
अटल पूर्णांक mt7622_pcie0_1_waken_pins[] = अणु 79, पूर्ण;
अटल पूर्णांक mt7622_pcie0_1_waken_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pcie0_1_clkreq_pins[] = अणु 80, पूर्ण;
अटल पूर्णांक mt7622_pcie0_1_clkreq_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pcie1_0_waken_pins[] = अणु 14, पूर्ण;
अटल पूर्णांक mt7622_pcie1_0_waken_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_pcie1_0_clkreq_pins[] = अणु 15, पूर्ण;
अटल पूर्णांक mt7622_pcie1_0_clkreq_funcs[] = अणु 3, पूर्ण;

अटल पूर्णांक mt7622_pcie0_pad_perst_pins[] = अणु 83, पूर्ण;
अटल पूर्णांक mt7622_pcie0_pad_perst_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_pcie1_pad_perst_pins[] = अणु 84, पूर्ण;
अटल पूर्णांक mt7622_pcie1_pad_perst_funcs[] = अणु 0, पूर्ण;

/* PMIC bus */
अटल पूर्णांक mt7622_pmic_bus_pins[] = अणु 71, 72, पूर्ण;
अटल पूर्णांक mt7622_pmic_bus_funcs[] = अणु 0, 0, पूर्ण;

/* Parallel न_अंकD */
अटल पूर्णांक mt7622_pnand_pins[] = अणु 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
				   48, 49, 50, पूर्ण;
अटल पूर्णांक mt7622_pnand_funcs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				    0, पूर्ण;

/* PWM */
अटल पूर्णांक mt7622_pwm_ch1_0_pins[] = अणु 51, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch1_0_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch1_1_pins[] = अणु 73, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch1_1_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch1_2_pins[] = अणु 95, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch1_2_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch2_0_pins[] = अणु 52, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch2_0_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch2_1_pins[] = अणु 74, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch2_1_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch2_2_pins[] = अणु 96, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch2_2_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch3_0_pins[] = अणु 53, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch3_0_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch3_1_pins[] = अणु 75, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch3_1_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch3_2_pins[] = अणु 97, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch3_2_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch4_0_pins[] = अणु 54, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch4_0_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch4_1_pins[] = अणु 67, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch4_1_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch4_2_pins[] = अणु 76, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch4_2_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch4_3_pins[] = अणु 98, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch4_3_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch5_0_pins[] = अणु 68, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch5_0_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch5_1_pins[] = अणु 77, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch5_1_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch5_2_pins[] = अणु 99, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch5_2_funcs[] = अणु 0, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch6_0_pins[] = अणु 69, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch6_0_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch6_1_pins[] = अणु 78, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch6_1_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch6_2_pins[] = अणु 81, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch6_2_funcs[] = अणु 4, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch6_3_pins[] = अणु 100, पूर्ण;
अटल पूर्णांक mt7622_pwm_ch6_3_funcs[] = अणु 0, पूर्ण;

/* SD */
अटल पूर्णांक mt7622_sd_0_pins[] = अणु 16, 17, 18, 19, 20, 21, पूर्ण;
अटल पूर्णांक mt7622_sd_0_funcs[] = अणु 2, 2, 2, 2, 2, 2, पूर्ण;
अटल पूर्णांक mt7622_sd_1_pins[] = अणु 25, 26, 27, 28, 29, 30, पूर्ण;
अटल पूर्णांक mt7622_sd_1_funcs[] = अणु 2, 2, 2, 2, 2, 2, पूर्ण;

/* Serial न_अंकD */
अटल पूर्णांक mt7622_snfi_pins[] = अणु 8, 9, 10, 11, 12, 13, पूर्ण;
अटल पूर्णांक mt7622_snfi_funcs[] = अणु 2, 2, 2, 2, 2, 2, पूर्ण;

/* SPI NOR */
अटल पूर्णांक mt7622_spi_pins[] = अणु 8, 9, 10, 11, 12, 13 पूर्ण;
अटल पूर्णांक mt7622_spi_funcs[] = अणु 0, 0, 0, 0, 0, 0, पूर्ण;

/* SPIC */
अटल पूर्णांक mt7622_spic0_0_pins[] = अणु 63, 64, 65, 66, पूर्ण;
अटल पूर्णांक mt7622_spic0_0_funcs[] = अणु 4, 4, 4, 4, पूर्ण;
अटल पूर्णांक mt7622_spic0_1_pins[] = अणु 79, 80, 81, 82, पूर्ण;
अटल पूर्णांक mt7622_spic0_1_funcs[] = अणु 3, 3, 3, 3, पूर्ण;
अटल पूर्णांक mt7622_spic1_0_pins[] = अणु 67, 68, 69, 70, पूर्ण;
अटल पूर्णांक mt7622_spic1_0_funcs[] = अणु 4, 4, 4, 4, पूर्ण;
अटल पूर्णांक mt7622_spic1_1_pins[] = अणु 73, 74, 75, 76, पूर्ण;
अटल पूर्णांक mt7622_spic1_1_funcs[] = अणु 0, 0, 0, 0, पूर्ण;
अटल पूर्णांक mt7622_spic2_0_pins[] = अणु 10, 11, 12, 13, पूर्ण;
अटल पूर्णांक mt7622_spic2_0_funcs[] = अणु 0, 0, 0, 0, पूर्ण;
अटल पूर्णांक mt7622_spic2_0_wp_hold_pins[] = अणु 8, 9, पूर्ण;
अटल पूर्णांक mt7622_spic2_0_wp_hold_funcs[] = अणु 0, 0, पूर्ण;

/* TDM */
अटल पूर्णांक mt7622_tdm_0_out_mclk_bclk_ws_pins[] = अणु 8, 9, 10, पूर्ण;
अटल पूर्णांक mt7622_tdm_0_out_mclk_bclk_ws_funcs[] = अणु 3, 3, 3, पूर्ण;
अटल पूर्णांक mt7622_tdm_0_in_mclk_bclk_ws_pins[] = अणु 11, 12, 13, पूर्ण;
अटल पूर्णांक mt7622_tdm_0_in_mclk_bclk_ws_funcs[] = अणु 3, 3, 3, पूर्ण;
अटल पूर्णांक mt7622_tdm_0_out_data_pins[] = अणु 20, पूर्ण;
अटल पूर्णांक mt7622_tdm_0_out_data_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_tdm_0_in_data_pins[] = अणु 21, पूर्ण;
अटल पूर्णांक mt7622_tdm_0_in_data_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_tdm_1_out_mclk_bclk_ws_pins[] = अणु 57, 58, 59, पूर्ण;
अटल पूर्णांक mt7622_tdm_1_out_mclk_bclk_ws_funcs[] = अणु 3, 3, 3, पूर्ण;
अटल पूर्णांक mt7622_tdm_1_in_mclk_bclk_ws_pins[] = अणु 60, 61, 62, पूर्ण;
अटल पूर्णांक mt7622_tdm_1_in_mclk_bclk_ws_funcs[] = अणु 3, 3, 3, पूर्ण;
अटल पूर्णांक mt7622_tdm_1_out_data_pins[] = अणु 55, पूर्ण;
अटल पूर्णांक mt7622_tdm_1_out_data_funcs[] = अणु 3, पूर्ण;
अटल पूर्णांक mt7622_tdm_1_in_data_pins[] = अणु 56, पूर्ण;
अटल पूर्णांक mt7622_tdm_1_in_data_funcs[] = अणु 3, पूर्ण;

/* UART */
अटल पूर्णांक mt7622_uart0_0_tx_rx_pins[] = अणु 6, 7, पूर्ण;
अटल पूर्णांक mt7622_uart0_0_tx_rx_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_uart1_0_tx_rx_pins[] = अणु 55, 56, पूर्ण;
अटल पूर्णांक mt7622_uart1_0_tx_rx_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7622_uart1_0_rts_cts_pins[] = अणु 57, 58, पूर्ण;
अटल पूर्णांक mt7622_uart1_0_rts_cts_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7622_uart1_1_tx_rx_pins[] = अणु 73, 74, पूर्ण;
अटल पूर्णांक mt7622_uart1_1_tx_rx_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7622_uart1_1_rts_cts_pins[] = अणु 75, 76, पूर्ण;
अटल पूर्णांक mt7622_uart1_1_rts_cts_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7622_uart2_0_tx_rx_pins[] = अणु 3, 4, पूर्ण;
अटल पूर्णांक mt7622_uart2_0_tx_rx_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7622_uart2_0_rts_cts_pins[] = अणु 1, 2, पूर्ण;
अटल पूर्णांक mt7622_uart2_0_rts_cts_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7622_uart2_1_tx_rx_pins[] = अणु 51, 52, पूर्ण;
अटल पूर्णांक mt7622_uart2_1_tx_rx_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_uart2_1_rts_cts_pins[] = अणु 53, 54, पूर्ण;
अटल पूर्णांक mt7622_uart2_1_rts_cts_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_uart2_2_tx_rx_pins[] = अणु 59, 60, पूर्ण;
अटल पूर्णांक mt7622_uart2_2_tx_rx_funcs[] = अणु 4, 4, पूर्ण;
अटल पूर्णांक mt7622_uart2_2_rts_cts_pins[] = अणु 61, 62, पूर्ण;
अटल पूर्णांक mt7622_uart2_2_rts_cts_funcs[] = अणु 4, 4, पूर्ण;
अटल पूर्णांक mt7622_uart2_3_tx_rx_pins[] = अणु 95, 96, पूर्ण;
अटल पूर्णांक mt7622_uart2_3_tx_rx_funcs[] = अणु 3, 3, पूर्ण;
अटल पूर्णांक mt7622_uart3_0_tx_rx_pins[] = अणु 57, 58, पूर्ण;
अटल पूर्णांक mt7622_uart3_0_tx_rx_funcs[] = अणु 5, 5, पूर्ण;
अटल पूर्णांक mt7622_uart3_1_tx_rx_pins[] = अणु 81, 82, पूर्ण;
अटल पूर्णांक mt7622_uart3_1_tx_rx_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_uart3_1_rts_cts_pins[] = अणु 79, 80, पूर्ण;
अटल पूर्णांक mt7622_uart3_1_rts_cts_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_uart4_0_tx_rx_pins[] = अणु 61, 62, पूर्ण;
अटल पूर्णांक mt7622_uart4_0_tx_rx_funcs[] = अणु 5, 5, पूर्ण;
अटल पूर्णांक mt7622_uart4_1_tx_rx_pins[] = अणु 91, 92, पूर्ण;
अटल पूर्णांक mt7622_uart4_1_tx_rx_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_uart4_1_rts_cts_pins[] = अणु 93, 94 पूर्ण;
अटल पूर्णांक mt7622_uart4_1_rts_cts_funcs[] = अणु 0, 0, पूर्ण;
अटल पूर्णांक mt7622_uart4_2_tx_rx_pins[] = अणु 97, 98, पूर्ण;
अटल पूर्णांक mt7622_uart4_2_tx_rx_funcs[] = अणु 2, 2, पूर्ण;
अटल पूर्णांक mt7622_uart4_2_rts_cts_pins[] = अणु 95, 96 पूर्ण;
अटल पूर्णांक mt7622_uart4_2_rts_cts_funcs[] = अणु 2, 2, पूर्ण;

/* Watchकरोg */
अटल पूर्णांक mt7622_watchकरोg_pins[] = अणु 78, पूर्ण;
अटल पूर्णांक mt7622_watchकरोg_funcs[] = अणु 0, पूर्ण;

/* WLAN LED */
अटल पूर्णांक mt7622_wled_pins[] = अणु 85, पूर्ण;
अटल पूर्णांक mt7622_wled_funcs[] = अणु 0, पूर्ण;

अटल स्थिर काष्ठा group_desc mt7622_groups[] = अणु
	PINCTRL_PIN_GROUP("antsel0", mt7622_antsel0),
	PINCTRL_PIN_GROUP("antsel1", mt7622_antsel1),
	PINCTRL_PIN_GROUP("antsel2", mt7622_antsel2),
	PINCTRL_PIN_GROUP("antsel3", mt7622_antsel3),
	PINCTRL_PIN_GROUP("antsel4", mt7622_antsel4),
	PINCTRL_PIN_GROUP("antsel5", mt7622_antsel5),
	PINCTRL_PIN_GROUP("antsel6", mt7622_antsel6),
	PINCTRL_PIN_GROUP("antsel7", mt7622_antsel7),
	PINCTRL_PIN_GROUP("antsel8", mt7622_antsel8),
	PINCTRL_PIN_GROUP("antsel9", mt7622_antsel9),
	PINCTRL_PIN_GROUP("antsel10", mt7622_antsel10),
	PINCTRL_PIN_GROUP("antsel11", mt7622_antsel11),
	PINCTRL_PIN_GROUP("antsel12", mt7622_antsel12),
	PINCTRL_PIN_GROUP("antsel13", mt7622_antsel13),
	PINCTRL_PIN_GROUP("antsel14", mt7622_antsel14),
	PINCTRL_PIN_GROUP("antsel15", mt7622_antsel15),
	PINCTRL_PIN_GROUP("antsel16", mt7622_antsel16),
	PINCTRL_PIN_GROUP("antsel17", mt7622_antsel17),
	PINCTRL_PIN_GROUP("antsel18", mt7622_antsel18),
	PINCTRL_PIN_GROUP("antsel19", mt7622_antsel19),
	PINCTRL_PIN_GROUP("antsel20", mt7622_antsel20),
	PINCTRL_PIN_GROUP("antsel21", mt7622_antsel21),
	PINCTRL_PIN_GROUP("antsel22", mt7622_antsel22),
	PINCTRL_PIN_GROUP("antsel23", mt7622_antsel23),
	PINCTRL_PIN_GROUP("antsel24", mt7622_antsel24),
	PINCTRL_PIN_GROUP("antsel25", mt7622_antsel25),
	PINCTRL_PIN_GROUP("antsel26", mt7622_antsel26),
	PINCTRL_PIN_GROUP("antsel27", mt7622_antsel27),
	PINCTRL_PIN_GROUP("antsel28", mt7622_antsel28),
	PINCTRL_PIN_GROUP("antsel29", mt7622_antsel29),
	PINCTRL_PIN_GROUP("emmc", mt7622_emmc),
	PINCTRL_PIN_GROUP("emmc_rst", mt7622_emmc_rst),
	PINCTRL_PIN_GROUP("ephy_leds", mt7622_ephy_leds),
	PINCTRL_PIN_GROUP("ephy0_led", mt7622_ephy0_led),
	PINCTRL_PIN_GROUP("ephy1_led", mt7622_ephy1_led),
	PINCTRL_PIN_GROUP("ephy2_led", mt7622_ephy2_led),
	PINCTRL_PIN_GROUP("ephy3_led", mt7622_ephy3_led),
	PINCTRL_PIN_GROUP("ephy4_led", mt7622_ephy4_led),
	PINCTRL_PIN_GROUP("esw", mt7622_esw),
	PINCTRL_PIN_GROUP("esw_p0_p1", mt7622_esw_p0_p1),
	PINCTRL_PIN_GROUP("esw_p2_p3_p4", mt7622_esw_p2_p3_p4),
	PINCTRL_PIN_GROUP("rgmii_via_esw", mt7622_rgmii_via_esw),
	PINCTRL_PIN_GROUP("rgmii_via_gmac1", mt7622_rgmii_via_gmac1),
	PINCTRL_PIN_GROUP("rgmii_via_gmac2", mt7622_rgmii_via_gmac2),
	PINCTRL_PIN_GROUP("i2c0", mt7622_i2c0),
	PINCTRL_PIN_GROUP("i2c1_0", mt7622_i2c1_0),
	PINCTRL_PIN_GROUP("i2c1_1", mt7622_i2c1_1),
	PINCTRL_PIN_GROUP("i2c1_2", mt7622_i2c1_2),
	PINCTRL_PIN_GROUP("i2c2_0", mt7622_i2c2_0),
	PINCTRL_PIN_GROUP("i2c2_1", mt7622_i2c2_1),
	PINCTRL_PIN_GROUP("i2c2_2", mt7622_i2c2_2),
	PINCTRL_PIN_GROUP("i2s_out_mclk_bclk_ws", mt7622_i2s_out_mclk_bclk_ws),
	PINCTRL_PIN_GROUP("i2s_in_mclk_bclk_ws", mt7622_i2s_in_mclk_bclk_ws),
	PINCTRL_PIN_GROUP("i2s1_in_data", mt7622_i2s1_in_data),
	PINCTRL_PIN_GROUP("i2s2_in_data", mt7622_i2s2_in_data),
	PINCTRL_PIN_GROUP("i2s3_in_data", mt7622_i2s3_in_data),
	PINCTRL_PIN_GROUP("i2s4_in_data", mt7622_i2s4_in_data),
	PINCTRL_PIN_GROUP("i2s1_out_data", mt7622_i2s1_out_data),
	PINCTRL_PIN_GROUP("i2s2_out_data", mt7622_i2s2_out_data),
	PINCTRL_PIN_GROUP("i2s3_out_data", mt7622_i2s3_out_data),
	PINCTRL_PIN_GROUP("i2s4_out_data", mt7622_i2s4_out_data),
	PINCTRL_PIN_GROUP("ir_0_tx", mt7622_ir_0_tx),
	PINCTRL_PIN_GROUP("ir_1_tx", mt7622_ir_1_tx),
	PINCTRL_PIN_GROUP("ir_2_tx", mt7622_ir_2_tx),
	PINCTRL_PIN_GROUP("ir_0_rx", mt7622_ir_0_rx),
	PINCTRL_PIN_GROUP("ir_1_rx", mt7622_ir_1_rx),
	PINCTRL_PIN_GROUP("ir_2_rx", mt7622_ir_2_rx),
	PINCTRL_PIN_GROUP("mdc_mdio", mt7622_mdc_mdio),
	PINCTRL_PIN_GROUP("pcie0_0_waken", mt7622_pcie0_0_waken),
	PINCTRL_PIN_GROUP("pcie0_0_clkreq", mt7622_pcie0_0_clkreq),
	PINCTRL_PIN_GROUP("pcie0_1_waken", mt7622_pcie0_1_waken),
	PINCTRL_PIN_GROUP("pcie0_1_clkreq", mt7622_pcie0_1_clkreq),
	PINCTRL_PIN_GROUP("pcie1_0_waken", mt7622_pcie1_0_waken),
	PINCTRL_PIN_GROUP("pcie1_0_clkreq", mt7622_pcie1_0_clkreq),
	PINCTRL_PIN_GROUP("pcie0_pad_perst", mt7622_pcie0_pad_perst),
	PINCTRL_PIN_GROUP("pcie1_pad_perst", mt7622_pcie1_pad_perst),
	PINCTRL_PIN_GROUP("par_nand", mt7622_pnand),
	PINCTRL_PIN_GROUP("pmic_bus", mt7622_pmic_bus),
	PINCTRL_PIN_GROUP("pwm_ch1_0", mt7622_pwm_ch1_0),
	PINCTRL_PIN_GROUP("pwm_ch1_1", mt7622_pwm_ch1_1),
	PINCTRL_PIN_GROUP("pwm_ch1_2", mt7622_pwm_ch1_2),
	PINCTRL_PIN_GROUP("pwm_ch2_0", mt7622_pwm_ch2_0),
	PINCTRL_PIN_GROUP("pwm_ch2_1", mt7622_pwm_ch2_1),
	PINCTRL_PIN_GROUP("pwm_ch2_2", mt7622_pwm_ch2_2),
	PINCTRL_PIN_GROUP("pwm_ch3_0", mt7622_pwm_ch3_0),
	PINCTRL_PIN_GROUP("pwm_ch3_1", mt7622_pwm_ch3_1),
	PINCTRL_PIN_GROUP("pwm_ch3_2", mt7622_pwm_ch3_2),
	PINCTRL_PIN_GROUP("pwm_ch4_0", mt7622_pwm_ch4_0),
	PINCTRL_PIN_GROUP("pwm_ch4_1", mt7622_pwm_ch4_1),
	PINCTRL_PIN_GROUP("pwm_ch4_2", mt7622_pwm_ch4_2),
	PINCTRL_PIN_GROUP("pwm_ch4_3", mt7622_pwm_ch4_3),
	PINCTRL_PIN_GROUP("pwm_ch5_0", mt7622_pwm_ch5_0),
	PINCTRL_PIN_GROUP("pwm_ch5_1", mt7622_pwm_ch5_1),
	PINCTRL_PIN_GROUP("pwm_ch5_2", mt7622_pwm_ch5_2),
	PINCTRL_PIN_GROUP("pwm_ch6_0", mt7622_pwm_ch6_0),
	PINCTRL_PIN_GROUP("pwm_ch6_1", mt7622_pwm_ch6_1),
	PINCTRL_PIN_GROUP("pwm_ch6_2", mt7622_pwm_ch6_2),
	PINCTRL_PIN_GROUP("pwm_ch6_3", mt7622_pwm_ch6_3),
	PINCTRL_PIN_GROUP("sd_0", mt7622_sd_0),
	PINCTRL_PIN_GROUP("sd_1", mt7622_sd_1),
	PINCTRL_PIN_GROUP("snfi", mt7622_snfi),
	PINCTRL_PIN_GROUP("spi_nor", mt7622_spi),
	PINCTRL_PIN_GROUP("spic0_0", mt7622_spic0_0),
	PINCTRL_PIN_GROUP("spic0_1", mt7622_spic0_1),
	PINCTRL_PIN_GROUP("spic1_0", mt7622_spic1_0),
	PINCTRL_PIN_GROUP("spic1_1", mt7622_spic1_1),
	PINCTRL_PIN_GROUP("spic2_0", mt7622_spic2_0),
	PINCTRL_PIN_GROUP("spic2_0_wp_hold", mt7622_spic2_0_wp_hold),
	PINCTRL_PIN_GROUP("tdm_0_out_mclk_bclk_ws",
			  mt7622_tdm_0_out_mclk_bclk_ws),
	PINCTRL_PIN_GROUP("tdm_0_in_mclk_bclk_ws",
			  mt7622_tdm_0_in_mclk_bclk_ws),
	PINCTRL_PIN_GROUP("tdm_0_out_data",  mt7622_tdm_0_out_data),
	PINCTRL_PIN_GROUP("tdm_0_in_data", mt7622_tdm_0_in_data),
	PINCTRL_PIN_GROUP("tdm_1_out_mclk_bclk_ws",
			  mt7622_tdm_1_out_mclk_bclk_ws),
	PINCTRL_PIN_GROUP("tdm_1_in_mclk_bclk_ws",
			  mt7622_tdm_1_in_mclk_bclk_ws),
	PINCTRL_PIN_GROUP("tdm_1_out_data",  mt7622_tdm_1_out_data),
	PINCTRL_PIN_GROUP("tdm_1_in_data", mt7622_tdm_1_in_data),
	PINCTRL_PIN_GROUP("uart0_0_tx_rx", mt7622_uart0_0_tx_rx),
	PINCTRL_PIN_GROUP("uart1_0_tx_rx", mt7622_uart1_0_tx_rx),
	PINCTRL_PIN_GROUP("uart1_0_rts_cts", mt7622_uart1_0_rts_cts),
	PINCTRL_PIN_GROUP("uart1_1_tx_rx", mt7622_uart1_1_tx_rx),
	PINCTRL_PIN_GROUP("uart1_1_rts_cts", mt7622_uart1_1_rts_cts),
	PINCTRL_PIN_GROUP("uart2_0_tx_rx", mt7622_uart2_0_tx_rx),
	PINCTRL_PIN_GROUP("uart2_0_rts_cts", mt7622_uart2_0_rts_cts),
	PINCTRL_PIN_GROUP("uart2_1_tx_rx", mt7622_uart2_1_tx_rx),
	PINCTRL_PIN_GROUP("uart2_1_rts_cts", mt7622_uart2_1_rts_cts),
	PINCTRL_PIN_GROUP("uart2_2_tx_rx", mt7622_uart2_2_tx_rx),
	PINCTRL_PIN_GROUP("uart2_2_rts_cts", mt7622_uart2_2_rts_cts),
	PINCTRL_PIN_GROUP("uart2_3_tx_rx", mt7622_uart2_3_tx_rx),
	PINCTRL_PIN_GROUP("uart3_0_tx_rx", mt7622_uart3_0_tx_rx),
	PINCTRL_PIN_GROUP("uart3_1_tx_rx", mt7622_uart3_1_tx_rx),
	PINCTRL_PIN_GROUP("uart3_1_rts_cts", mt7622_uart3_1_rts_cts),
	PINCTRL_PIN_GROUP("uart4_0_tx_rx", mt7622_uart4_0_tx_rx),
	PINCTRL_PIN_GROUP("uart4_1_tx_rx", mt7622_uart4_1_tx_rx),
	PINCTRL_PIN_GROUP("uart4_1_rts_cts", mt7622_uart4_1_rts_cts),
	PINCTRL_PIN_GROUP("uart4_2_tx_rx", mt7622_uart4_2_tx_rx),
	PINCTRL_PIN_GROUP("uart4_2_rts_cts", mt7622_uart4_2_rts_cts),
	PINCTRL_PIN_GROUP("watchdog", mt7622_watchकरोg),
	PINCTRL_PIN_GROUP("wled", mt7622_wled),
पूर्ण;

/* Joपूर्णांक those groups owning the same capability in user poपूर्णांक of view which
 * allows that people tend to use through the device tree.
 */
अटल स्थिर अक्षर *mt7622_antsel_groups[] = अणु "antsel0", "antsel1", "antsel2",
					      "antsel3", "antsel4", "antsel5",
					      "antsel6", "antsel7", "antsel8",
					      "antsel9", "antsel10", "antsel11",
					      "antsel12", "antsel13", "antsel14",
					      "antsel15", "antsel16", "antsel17",
					      "antsel18", "antsel19", "antsel20",
					      "antsel21", "antsel22", "antsel23",
					      "antsel24", "antsel25", "antsel26",
					      "antsel27", "antsel28", "antsel29",पूर्ण;
अटल स्थिर अक्षर *mt7622_emmc_groups[] = अणु "emmc", "emmc_rst", पूर्ण;
अटल स्थिर अक्षर *mt7622_ethernet_groups[] = अणु "esw", "esw_p0_p1",
						"esw_p2_p3_p4", "mdc_mdio",
						"rgmii_via_gmac1",
						"rgmii_via_gmac2",
						"rgmii_via_esw", पूर्ण;
अटल स्थिर अक्षर *mt7622_i2c_groups[] = अणु "i2c0", "i2c1_0", "i2c1_1",
					   "i2c1_2", "i2c2_0", "i2c2_1",
					   "i2c2_2", पूर्ण;
अटल स्थिर अक्षर *mt7622_i2s_groups[] = अणु "i2s_out_mclk_bclk_ws",
					   "i2s_in_mclk_bclk_ws",
					   "i2s1_in_data", "i2s2_in_data",
					   "i2s3_in_data", "i2s4_in_data",
					   "i2s1_out_data", "i2s2_out_data",
					   "i2s3_out_data", "i2s4_out_data", पूर्ण;
अटल स्थिर अक्षर *mt7622_ir_groups[] = अणु "ir_0_tx", "ir_1_tx", "ir_2_tx",
					  "ir_0_rx", "ir_1_rx", "ir_2_rx"पूर्ण;
अटल स्थिर अक्षर *mt7622_led_groups[] = अणु "ephy_leds", "ephy0_led",
					   "ephy1_led", "ephy2_led",
					   "ephy3_led", "ephy4_led",
					   "wled", पूर्ण;
अटल स्थिर अक्षर *mt7622_flash_groups[] = अणु "par_nand", "snfi", "spi_nor"पूर्ण;
अटल स्थिर अक्षर *mt7622_pcie_groups[] = अणु "pcie0_0_waken", "pcie0_0_clkreq",
					    "pcie0_1_waken", "pcie0_1_clkreq",
					    "pcie1_0_waken", "pcie1_0_clkreq",
					    "pcie0_pad_perst",
					    "pcie1_pad_perst", पूर्ण;
अटल स्थिर अक्षर *mt7622_pmic_bus_groups[] = अणु "pmic_bus", पूर्ण;
अटल स्थिर अक्षर *mt7622_pwm_groups[] = अणु "pwm_ch1_0", "pwm_ch1_1",
					   "pwm_ch1_2", "pwm_ch2_0",
					   "pwm_ch2_1", "pwm_ch2_2",
					   "pwm_ch3_0", "pwm_ch3_1",
					   "pwm_ch3_2", "pwm_ch4_0",
					   "pwm_ch4_1", "pwm_ch4_2",
					   "pwm_ch4_3", "pwm_ch5_0",
					   "pwm_ch5_1", "pwm_ch5_2",
					   "pwm_ch6_0", "pwm_ch6_1",
					   "pwm_ch6_2", "pwm_ch6_3", पूर्ण;
अटल स्थिर अक्षर *mt7622_sd_groups[] = अणु "sd_0", "sd_1", पूर्ण;
अटल स्थिर अक्षर *mt7622_spic_groups[] = अणु "spic0_0", "spic0_1", "spic1_0",
					    "spic1_1", "spic2_0",
					    "spic2_0_wp_hold", पूर्ण;
अटल स्थिर अक्षर *mt7622_tdm_groups[] = अणु "tdm_0_out_mclk_bclk_ws",
					   "tdm_0_in_mclk_bclk_ws",
					   "tdm_0_out_data",
					   "tdm_0_in_data",
					   "tdm_1_out_mclk_bclk_ws",
					   "tdm_1_in_mclk_bclk_ws",
					   "tdm_1_out_data",
					   "tdm_1_in_data", पूर्ण;

अटल स्थिर अक्षर *mt7622_uart_groups[] = अणु "uart0_0_tx_rx",
					    "uart1_0_tx_rx", "uart1_0_rts_cts",
					    "uart1_1_tx_rx", "uart1_1_rts_cts",
					    "uart2_0_tx_rx", "uart2_0_rts_cts",
					    "uart2_1_tx_rx", "uart2_1_rts_cts",
					    "uart2_2_tx_rx", "uart2_2_rts_cts",
					    "uart2_3_tx_rx",
					    "uart3_0_tx_rx",
					    "uart3_1_tx_rx", "uart3_1_rts_cts",
					    "uart4_0_tx_rx",
					    "uart4_1_tx_rx", "uart4_1_rts_cts",
					    "uart4_2_tx_rx",
					    "uart4_2_rts_cts",पूर्ण;
अटल स्थिर अक्षर *mt7622_wdt_groups[] = अणु "watchdog", पूर्ण;

अटल स्थिर काष्ठा function_desc mt7622_functions[] = अणु
	अणु"antsel", mt7622_antsel_groups, ARRAY_SIZE(mt7622_antsel_groups)पूर्ण,
	अणु"emmc", mt7622_emmc_groups, ARRAY_SIZE(mt7622_emmc_groups)पूर्ण,
	अणु"eth",	mt7622_ethernet_groups, ARRAY_SIZE(mt7622_ethernet_groups)पूर्ण,
	अणु"i2c", mt7622_i2c_groups, ARRAY_SIZE(mt7622_i2c_groups)पूर्ण,
	अणु"i2s",	mt7622_i2s_groups, ARRAY_SIZE(mt7622_i2s_groups)पूर्ण,
	अणु"ir", mt7622_ir_groups, ARRAY_SIZE(mt7622_ir_groups)पूर्ण,
	अणु"led",	mt7622_led_groups, ARRAY_SIZE(mt7622_led_groups)पूर्ण,
	अणु"flash", mt7622_flash_groups, ARRAY_SIZE(mt7622_flash_groups)पूर्ण,
	अणु"pcie", mt7622_pcie_groups, ARRAY_SIZE(mt7622_pcie_groups)पूर्ण,
	अणु"pmic", mt7622_pmic_bus_groups, ARRAY_SIZE(mt7622_pmic_bus_groups)पूर्ण,
	अणु"pwm",	mt7622_pwm_groups, ARRAY_SIZE(mt7622_pwm_groups)पूर्ण,
	अणु"sd", mt7622_sd_groups, ARRAY_SIZE(mt7622_sd_groups)पूर्ण,
	अणु"spi",	mt7622_spic_groups, ARRAY_SIZE(mt7622_spic_groups)पूर्ण,
	अणु"tdm",	mt7622_tdm_groups, ARRAY_SIZE(mt7622_tdm_groups)पूर्ण,
	अणु"uart", mt7622_uart_groups, ARRAY_SIZE(mt7622_uart_groups)पूर्ण,
	अणु"watchdog", mt7622_wdt_groups, ARRAY_SIZE(mt7622_wdt_groups)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_eपूर्णांक_hw mt7622_eपूर्णांक_hw = अणु
	.port_mask = 7,
	.ports     = 7,
	.ap_num    = ARRAY_SIZE(mt7622_pins),
	.db_cnt    = 20,
पूर्ण;

अटल स्थिर काष्ठा mtk_pin_soc mt7622_data = अणु
	.reg_cal = mt7622_reg_cals,
	.pins = mt7622_pins,
	.npins = ARRAY_SIZE(mt7622_pins),
	.grps = mt7622_groups,
	.ngrps = ARRAY_SIZE(mt7622_groups),
	.funcs = mt7622_functions,
	.nfuncs = ARRAY_SIZE(mt7622_functions),
	.eपूर्णांक_hw = &mt7622_eपूर्णांक_hw,
	.gpio_m	= 1,
	.ies_present = false,
	.base_names = mtk_शेष_रेजिस्टर_base_names,
	.nbase_names = ARRAY_SIZE(mtk_शेष_रेजिस्टर_base_names),
	.bias_disable_set = mtk_pinconf_bias_disable_set,
	.bias_disable_get = mtk_pinconf_bias_disable_get,
	.bias_set = mtk_pinconf_bias_set,
	.bias_get = mtk_pinconf_bias_get,
	.drive_set = mtk_pinconf_drive_set,
	.drive_get = mtk_pinconf_drive_get,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mt7622_pinctrl_of_match[] = अणु
	अणु .compatible = "mediatek,mt7622-pinctrl", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक mt7622_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस mtk_moore_pinctrl_probe(pdev, &mt7622_data);
पूर्ण

अटल काष्ठा platक्रमm_driver mt7622_pinctrl_driver = अणु
	.driver = अणु
		.name = "mt7622-pinctrl",
		.of_match_table = mt7622_pinctrl_of_match,
	पूर्ण,
	.probe = mt7622_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init mt7622_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mt7622_pinctrl_driver);
पूर्ण
arch_initcall(mt7622_pinctrl_init);
