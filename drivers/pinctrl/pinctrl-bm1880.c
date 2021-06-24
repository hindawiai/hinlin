<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Biपंचांगain BM1880 SoC Pinctrl driver
 *
 * Copyright (c) 2019 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "pinctrl-utils.h"

#घोषणा BM1880_REG_MUX 0x20

/**
 * काष्ठा bm1880_pinctrl - driver data
 * @base:	Pinctrl base address
 * @pctrldev:	Pinctrl device
 * @groups:	Pingroups
 * @ngroups:	Number of @groups
 * @funcs:	Pinmux functions
 * @nfuncs:	Number of @funcs
 * @pinconf:	Pinconf data
 */
काष्ठा bm1880_pinctrl अणु
	व्योम __iomem *base;
	काष्ठा pinctrl_dev *pctrldev;
	स्थिर काष्ठा bm1880_pctrl_group *groups;
	अचिन्हित पूर्णांक ngroups;
	स्थिर काष्ठा bm1880_pinmux_function *funcs;
	अचिन्हित पूर्णांक nfuncs;
	स्थिर काष्ठा bm1880_pinconf_data *pinconf;
पूर्ण;

/**
 * काष्ठा bm1880_pctrl_group - pinctrl group
 * @name:	Name of the group
 * @pins:	Array of pins beदीर्घing to this group
 * @npins:	Number of @pins
 */
काष्ठा bm1880_pctrl_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक npins;
पूर्ण;

/**
 * काष्ठा bm1880_pinmux_function - a pinmux function
 * @name:	Name of the pinmux function.
 * @groups:	List of pingroups क्रम this function.
 * @ngroups:	Number of entries in @groups.
 * @mux_val:	Selector क्रम this function
 * @mux:	Offset of function specअगरic mux
 * @mux_shअगरt:	Shअगरt क्रम function specअगरic selector
 */
काष्ठा bm1880_pinmux_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
	u32 mux_val;
	u32 mux;
	u8 mux_shअगरt;
पूर्ण;

/**
 * काष्ठा bm1880_pinconf_data - pinconf data
 * @drv_bits:	Drive strength bit width
 */
काष्ठा bm1880_pinconf_data अणु
	u32 drv_bits;
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc bm1880_pins[] = अणु
	PINCTRL_PIN(0,   "MIO0"),
	PINCTRL_PIN(1,   "MIO1"),
	PINCTRL_PIN(2,   "MIO2"),
	PINCTRL_PIN(3,   "MIO3"),
	PINCTRL_PIN(4,   "MIO4"),
	PINCTRL_PIN(5,   "MIO5"),
	PINCTRL_PIN(6,   "MIO6"),
	PINCTRL_PIN(7,   "MIO7"),
	PINCTRL_PIN(8,   "MIO8"),
	PINCTRL_PIN(9,   "MIO9"),
	PINCTRL_PIN(10,   "MIO10"),
	PINCTRL_PIN(11,   "MIO11"),
	PINCTRL_PIN(12,   "MIO12"),
	PINCTRL_PIN(13,   "MIO13"),
	PINCTRL_PIN(14,   "MIO14"),
	PINCTRL_PIN(15,   "MIO15"),
	PINCTRL_PIN(16,   "MIO16"),
	PINCTRL_PIN(17,   "MIO17"),
	PINCTRL_PIN(18,   "MIO18"),
	PINCTRL_PIN(19,   "MIO19"),
	PINCTRL_PIN(20,   "MIO20"),
	PINCTRL_PIN(21,   "MIO21"),
	PINCTRL_PIN(22,   "MIO22"),
	PINCTRL_PIN(23,   "MIO23"),
	PINCTRL_PIN(24,   "MIO24"),
	PINCTRL_PIN(25,   "MIO25"),
	PINCTRL_PIN(26,   "MIO26"),
	PINCTRL_PIN(27,   "MIO27"),
	PINCTRL_PIN(28,   "MIO28"),
	PINCTRL_PIN(29,   "MIO29"),
	PINCTRL_PIN(30,   "MIO30"),
	PINCTRL_PIN(31,   "MIO31"),
	PINCTRL_PIN(32,   "MIO32"),
	PINCTRL_PIN(33,   "MIO33"),
	PINCTRL_PIN(34,   "MIO34"),
	PINCTRL_PIN(35,   "MIO35"),
	PINCTRL_PIN(36,   "MIO36"),
	PINCTRL_PIN(37,   "MIO37"),
	PINCTRL_PIN(38,   "MIO38"),
	PINCTRL_PIN(39,   "MIO39"),
	PINCTRL_PIN(40,   "MIO40"),
	PINCTRL_PIN(41,   "MIO41"),
	PINCTRL_PIN(42,   "MIO42"),
	PINCTRL_PIN(43,   "MIO43"),
	PINCTRL_PIN(44,   "MIO44"),
	PINCTRL_PIN(45,   "MIO45"),
	PINCTRL_PIN(46,   "MIO46"),
	PINCTRL_PIN(47,   "MIO47"),
	PINCTRL_PIN(48,   "MIO48"),
	PINCTRL_PIN(49,   "MIO49"),
	PINCTRL_PIN(50,   "MIO50"),
	PINCTRL_PIN(51,   "MIO51"),
	PINCTRL_PIN(52,   "MIO52"),
	PINCTRL_PIN(53,   "MIO53"),
	PINCTRL_PIN(54,   "MIO54"),
	PINCTRL_PIN(55,   "MIO55"),
	PINCTRL_PIN(56,   "MIO56"),
	PINCTRL_PIN(57,   "MIO57"),
	PINCTRL_PIN(58,   "MIO58"),
	PINCTRL_PIN(59,   "MIO59"),
	PINCTRL_PIN(60,   "MIO60"),
	PINCTRL_PIN(61,   "MIO61"),
	PINCTRL_PIN(62,   "MIO62"),
	PINCTRL_PIN(63,   "MIO63"),
	PINCTRL_PIN(64,   "MIO64"),
	PINCTRL_PIN(65,   "MIO65"),
	PINCTRL_PIN(66,   "MIO66"),
	PINCTRL_PIN(67,   "MIO67"),
	PINCTRL_PIN(68,   "MIO68"),
	PINCTRL_PIN(69,   "MIO69"),
	PINCTRL_PIN(70,   "MIO70"),
	PINCTRL_PIN(71,   "MIO71"),
	PINCTRL_PIN(72,   "MIO72"),
	PINCTRL_PIN(73,   "MIO73"),
	PINCTRL_PIN(74,   "MIO74"),
	PINCTRL_PIN(75,   "MIO75"),
	PINCTRL_PIN(76,   "MIO76"),
	PINCTRL_PIN(77,   "MIO77"),
	PINCTRL_PIN(78,   "MIO78"),
	PINCTRL_PIN(79,   "MIO79"),
	PINCTRL_PIN(80,   "MIO80"),
	PINCTRL_PIN(81,   "MIO81"),
	PINCTRL_PIN(82,   "MIO82"),
	PINCTRL_PIN(83,   "MIO83"),
	PINCTRL_PIN(84,   "MIO84"),
	PINCTRL_PIN(85,   "MIO85"),
	PINCTRL_PIN(86,   "MIO86"),
	PINCTRL_PIN(87,   "MIO87"),
	PINCTRL_PIN(88,   "MIO88"),
	PINCTRL_PIN(89,   "MIO89"),
	PINCTRL_PIN(90,   "MIO90"),
	PINCTRL_PIN(91,   "MIO91"),
	PINCTRL_PIN(92,   "MIO92"),
	PINCTRL_PIN(93,   "MIO93"),
	PINCTRL_PIN(94,   "MIO94"),
	PINCTRL_PIN(95,   "MIO95"),
	PINCTRL_PIN(96,   "MIO96"),
	PINCTRL_PIN(97,   "MIO97"),
	PINCTRL_PIN(98,   "MIO98"),
	PINCTRL_PIN(99,   "MIO99"),
	PINCTRL_PIN(100,   "MIO100"),
	PINCTRL_PIN(101,   "MIO101"),
	PINCTRL_PIN(102,   "MIO102"),
	PINCTRL_PIN(103,   "MIO103"),
	PINCTRL_PIN(104,   "MIO104"),
	PINCTRL_PIN(105,   "MIO105"),
	PINCTRL_PIN(106,   "MIO106"),
	PINCTRL_PIN(107,   "MIO107"),
	PINCTRL_PIN(108,   "MIO108"),
	PINCTRL_PIN(109,   "MIO109"),
	PINCTRL_PIN(110,   "MIO110"),
	PINCTRL_PIN(111,   "MIO111"),
पूर्ण;

क्रमागत bm1880_pinmux_functions अणु
	F_nand, F_spi, F_emmc, F_sdio, F_eth0, F_pwm0, F_pwm1, F_pwm2,
	F_pwm3, F_pwm4, F_pwm5, F_pwm6, F_pwm7, F_pwm8, F_pwm9, F_pwm10,
	F_pwm11, F_pwm12, F_pwm13, F_pwm14, F_pwm15, F_pwm16, F_pwm17,
	F_pwm18, F_pwm19, F_pwm20, F_pwm21, F_pwm22, F_pwm23, F_pwm24,
	F_pwm25, F_pwm26, F_pwm27, F_pwm28, F_pwm29, F_pwm30, F_pwm31,
	F_pwm32, F_pwm33, F_pwm34, F_pwm35, F_pwm36, F_pwm37, F_i2c0, F_i2c1,
	F_i2c2, F_i2c3, F_i2c4, F_uart0, F_uart1, F_uart2, F_uart3, F_uart4,
	F_uart5, F_uart6, F_uart7, F_uart8, F_uart9, F_uart10, F_uart11,
	F_uart12, F_uart13, F_uart14, F_uart15, F_gpio0, F_gpio1, F_gpio2,
	F_gpio3, F_gpio4, F_gpio5, F_gpio6, F_gpio7, F_gpio8, F_gpio9, F_gpio10,
	F_gpio11, F_gpio12, F_gpio13, F_gpio14, F_gpio15, F_gpio16, F_gpio17,
	F_gpio18, F_gpio19, F_gpio20, F_gpio21, F_gpio22, F_gpio23, F_gpio24,
	F_gpio25, F_gpio26, F_gpio27, F_gpio28, F_gpio29, F_gpio30, F_gpio31,
	F_gpio32, F_gpio33, F_gpio34, F_gpio35, F_gpio36, F_gpio37, F_gpio38,
	F_gpio39, F_gpio40, F_gpio41, F_gpio42, F_gpio43, F_gpio44, F_gpio45,
	F_gpio46, F_gpio47, F_gpio48, F_gpio49, F_gpio50, F_gpio51, F_gpio52,
	F_gpio53, F_gpio54, F_gpio55, F_gpio56, F_gpio57, F_gpio58, F_gpio59,
	F_gpio60, F_gpio61, F_gpio62, F_gpio63, F_gpio64, F_gpio65, F_gpio66,
	F_gpio67, F_eth1, F_i2s0, F_i2s0_mclkin, F_i2s1, F_i2s1_mclkin, F_spi0,
	F_max
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक nand_pins[] = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
					  10, 11, 12, 13, 14, 15, 16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_pins[] = अणु 0, 1, 8, 10, 11, 12, 13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक emmc_pins[] = अणु 2, 3, 4, 5, 6, 7, 9, 14, 15, 16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_pins[] = अणु 17, 18, 19, 20, 21, 22, 23, 24,
					  25, 26 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth0_pins[] = अणु 27, 28, 29, 30, 31, 32, 33, 34, 35,
					  36, 37, 38, 39, 40, 41, 42 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm0_pins[] = अणु 29 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm1_pins[] = अणु 30 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm2_pins[] = अणु 34 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm3_pins[] = अणु 35 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm4_pins[] = अणु 43 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm5_pins[] = अणु 44 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm6_pins[] = अणु 45 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm7_pins[] = अणु 46 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm8_pins[] = अणु 47 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm9_pins[] = अणु 48 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm10_pins[] = अणु 49 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm11_pins[] = अणु 50 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm12_pins[] = अणु 51 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm13_pins[] = अणु 52 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm14_pins[] = अणु 53 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm15_pins[] = अणु 54 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm16_pins[] = अणु 55 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm17_pins[] = अणु 56 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm18_pins[] = अणु 57 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm19_pins[] = अणु 58 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm20_pins[] = अणु 59 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm21_pins[] = अणु 60 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm22_pins[] = अणु 61 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm23_pins[] = अणु 62 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm24_pins[] = अणु 97 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm25_pins[] = अणु 98 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm26_pins[] = अणु 99 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm27_pins[] = अणु 100 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm28_pins[] = अणु 101 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm29_pins[] = अणु 102 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm30_pins[] = अणु 103 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm31_pins[] = अणु 104 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm32_pins[] = अणु 105 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm33_pins[] = अणु 106 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm34_pins[] = अणु 107 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm35_pins[] = अणु 108 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm36_pins[] = अणु 109 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm37_pins[] = अणु 110 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_pins[] = अणु 63, 64 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_pins[] = अणु 65, 66 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_pins[] = अणु 67, 68 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c3_pins[] = अणु 69, 70 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c4_pins[] = अणु 71, 72 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_pins[] = अणु 73, 74 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_pins[] = अणु 75, 76 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart2_pins[] = अणु 77, 78 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart3_pins[] = अणु 79, 80 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart4_pins[] = अणु 81, 82 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart5_pins[] = अणु 83, 84 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart6_pins[] = अणु 85, 86 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart7_pins[] = अणु 87, 88 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart8_pins[] = अणु 89, 90 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart9_pins[] = अणु 91, 92 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart10_pins[] = अणु 93, 94 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart11_pins[] = अणु 95, 96 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart12_pins[] = अणु 73, 74, 75, 76 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart13_pins[] = अणु 77, 78, 83, 84 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart14_pins[] = अणु 79, 80, 85, 86 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart15_pins[] = अणु 81, 82, 87, 88 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_pins[] = अणु 97 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio1_pins[] = अणु 98 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio2_pins[] = अणु 99 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio3_pins[] = अणु 100 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio4_pins[] = अणु 101 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio5_pins[] = अणु 102 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio6_pins[] = अणु 103 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio7_pins[] = अणु 104 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio8_pins[] = अणु 105 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio9_pins[] = अणु 106 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio10_pins[] = अणु 107 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio11_pins[] = अणु 108 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio12_pins[] = अणु 109 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio13_pins[] = अणु 110 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio14_pins[] = अणु 43 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio15_pins[] = अणु 44 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio16_pins[] = अणु 45 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio17_pins[] = अणु 46 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio18_pins[] = अणु 47 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio19_pins[] = अणु 48 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio20_pins[] = अणु 49 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio21_pins[] = अणु 50 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio22_pins[] = अणु 51 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio23_pins[] = अणु 52 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio24_pins[] = अणु 53 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio25_pins[] = अणु 54 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio26_pins[] = अणु 55 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio27_pins[] = अणु 56 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio28_pins[] = अणु 57 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio29_pins[] = अणु 58 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio30_pins[] = अणु 59 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio31_pins[] = अणु 60 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio32_pins[] = अणु 61 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio33_pins[] = अणु 62 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio34_pins[] = अणु 63 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio35_pins[] = अणु 64 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio36_pins[] = अणु 65 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio37_pins[] = अणु 66 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio38_pins[] = अणु 67 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio39_pins[] = अणु 68 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio40_pins[] = अणु 69 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio41_pins[] = अणु 70 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio42_pins[] = अणु 71 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio43_pins[] = अणु 72 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio44_pins[] = अणु 73 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio45_pins[] = अणु 74 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio46_pins[] = अणु 75 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio47_pins[] = अणु 76 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio48_pins[] = अणु 77 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio49_pins[] = अणु 78 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio50_pins[] = अणु 79 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio51_pins[] = अणु 80 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio52_pins[] = अणु 81 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio53_pins[] = अणु 82 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio54_pins[] = अणु 83 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio55_pins[] = अणु 84 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio56_pins[] = अणु 85 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio57_pins[] = अणु 86 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio58_pins[] = अणु 87 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio59_pins[] = अणु 88 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio60_pins[] = अणु 89 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio61_pins[] = अणु 90 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio62_pins[] = अणु 91 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio63_pins[] = अणु 92 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio64_pins[] = अणु 93 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio65_pins[] = अणु 94 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio66_pins[] = अणु 95 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio67_pins[] = अणु 96 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth1_pins[] = अणु 43, 44, 45, 46, 47, 48, 49, 50, 51,
					  52, 53, 54, 55, 56, 57, 58 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s0_pins[] = अणु 87, 88, 89, 90, 91 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s0_mclkin_pins[] = अणु 97 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s1_pins[] = अणु 92, 93, 94, 95, 96 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s1_mclkin_pins[] = अणु 98 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_pins[] = अणु 59, 60, 61, 62 पूर्ण;

#घोषणा BM1880_PINCTRL_GRP(nm) \
	अणु \
		.name = #nm "_grp", \
		.pins = nm ## _pins, \
		.npins = ARRAY_SIZE(nm ## _pins), \
	पूर्ण

अटल स्थिर काष्ठा bm1880_pctrl_group bm1880_pctrl_groups[] = अणु
	BM1880_PINCTRL_GRP(nand),
	BM1880_PINCTRL_GRP(spi),
	BM1880_PINCTRL_GRP(emmc),
	BM1880_PINCTRL_GRP(sdio),
	BM1880_PINCTRL_GRP(eth0),
	BM1880_PINCTRL_GRP(pwm0),
	BM1880_PINCTRL_GRP(pwm1),
	BM1880_PINCTRL_GRP(pwm2),
	BM1880_PINCTRL_GRP(pwm3),
	BM1880_PINCTRL_GRP(pwm4),
	BM1880_PINCTRL_GRP(pwm5),
	BM1880_PINCTRL_GRP(pwm6),
	BM1880_PINCTRL_GRP(pwm7),
	BM1880_PINCTRL_GRP(pwm8),
	BM1880_PINCTRL_GRP(pwm9),
	BM1880_PINCTRL_GRP(pwm10),
	BM1880_PINCTRL_GRP(pwm11),
	BM1880_PINCTRL_GRP(pwm12),
	BM1880_PINCTRL_GRP(pwm13),
	BM1880_PINCTRL_GRP(pwm14),
	BM1880_PINCTRL_GRP(pwm15),
	BM1880_PINCTRL_GRP(pwm16),
	BM1880_PINCTRL_GRP(pwm17),
	BM1880_PINCTRL_GRP(pwm18),
	BM1880_PINCTRL_GRP(pwm19),
	BM1880_PINCTRL_GRP(pwm20),
	BM1880_PINCTRL_GRP(pwm21),
	BM1880_PINCTRL_GRP(pwm22),
	BM1880_PINCTRL_GRP(pwm23),
	BM1880_PINCTRL_GRP(pwm24),
	BM1880_PINCTRL_GRP(pwm25),
	BM1880_PINCTRL_GRP(pwm26),
	BM1880_PINCTRL_GRP(pwm27),
	BM1880_PINCTRL_GRP(pwm28),
	BM1880_PINCTRL_GRP(pwm29),
	BM1880_PINCTRL_GRP(pwm30),
	BM1880_PINCTRL_GRP(pwm31),
	BM1880_PINCTRL_GRP(pwm32),
	BM1880_PINCTRL_GRP(pwm33),
	BM1880_PINCTRL_GRP(pwm34),
	BM1880_PINCTRL_GRP(pwm35),
	BM1880_PINCTRL_GRP(pwm36),
	BM1880_PINCTRL_GRP(pwm37),
	BM1880_PINCTRL_GRP(i2c0),
	BM1880_PINCTRL_GRP(i2c1),
	BM1880_PINCTRL_GRP(i2c2),
	BM1880_PINCTRL_GRP(i2c3),
	BM1880_PINCTRL_GRP(i2c4),
	BM1880_PINCTRL_GRP(uart0),
	BM1880_PINCTRL_GRP(uart1),
	BM1880_PINCTRL_GRP(uart2),
	BM1880_PINCTRL_GRP(uart3),
	BM1880_PINCTRL_GRP(uart4),
	BM1880_PINCTRL_GRP(uart5),
	BM1880_PINCTRL_GRP(uart6),
	BM1880_PINCTRL_GRP(uart7),
	BM1880_PINCTRL_GRP(uart8),
	BM1880_PINCTRL_GRP(uart9),
	BM1880_PINCTRL_GRP(uart10),
	BM1880_PINCTRL_GRP(uart11),
	BM1880_PINCTRL_GRP(uart12),
	BM1880_PINCTRL_GRP(uart13),
	BM1880_PINCTRL_GRP(uart14),
	BM1880_PINCTRL_GRP(uart15),
	BM1880_PINCTRL_GRP(gpio0),
	BM1880_PINCTRL_GRP(gpio1),
	BM1880_PINCTRL_GRP(gpio2),
	BM1880_PINCTRL_GRP(gpio3),
	BM1880_PINCTRL_GRP(gpio4),
	BM1880_PINCTRL_GRP(gpio5),
	BM1880_PINCTRL_GRP(gpio6),
	BM1880_PINCTRL_GRP(gpio7),
	BM1880_PINCTRL_GRP(gpio8),
	BM1880_PINCTRL_GRP(gpio9),
	BM1880_PINCTRL_GRP(gpio10),
	BM1880_PINCTRL_GRP(gpio11),
	BM1880_PINCTRL_GRP(gpio12),
	BM1880_PINCTRL_GRP(gpio13),
	BM1880_PINCTRL_GRP(gpio14),
	BM1880_PINCTRL_GRP(gpio15),
	BM1880_PINCTRL_GRP(gpio16),
	BM1880_PINCTRL_GRP(gpio17),
	BM1880_PINCTRL_GRP(gpio18),
	BM1880_PINCTRL_GRP(gpio19),
	BM1880_PINCTRL_GRP(gpio20),
	BM1880_PINCTRL_GRP(gpio21),
	BM1880_PINCTRL_GRP(gpio22),
	BM1880_PINCTRL_GRP(gpio23),
	BM1880_PINCTRL_GRP(gpio24),
	BM1880_PINCTRL_GRP(gpio25),
	BM1880_PINCTRL_GRP(gpio26),
	BM1880_PINCTRL_GRP(gpio27),
	BM1880_PINCTRL_GRP(gpio28),
	BM1880_PINCTRL_GRP(gpio29),
	BM1880_PINCTRL_GRP(gpio30),
	BM1880_PINCTRL_GRP(gpio31),
	BM1880_PINCTRL_GRP(gpio32),
	BM1880_PINCTRL_GRP(gpio33),
	BM1880_PINCTRL_GRP(gpio34),
	BM1880_PINCTRL_GRP(gpio35),
	BM1880_PINCTRL_GRP(gpio36),
	BM1880_PINCTRL_GRP(gpio37),
	BM1880_PINCTRL_GRP(gpio38),
	BM1880_PINCTRL_GRP(gpio39),
	BM1880_PINCTRL_GRP(gpio40),
	BM1880_PINCTRL_GRP(gpio41),
	BM1880_PINCTRL_GRP(gpio42),
	BM1880_PINCTRL_GRP(gpio43),
	BM1880_PINCTRL_GRP(gpio44),
	BM1880_PINCTRL_GRP(gpio45),
	BM1880_PINCTRL_GRP(gpio46),
	BM1880_PINCTRL_GRP(gpio47),
	BM1880_PINCTRL_GRP(gpio48),
	BM1880_PINCTRL_GRP(gpio49),
	BM1880_PINCTRL_GRP(gpio50),
	BM1880_PINCTRL_GRP(gpio51),
	BM1880_PINCTRL_GRP(gpio52),
	BM1880_PINCTRL_GRP(gpio53),
	BM1880_PINCTRL_GRP(gpio54),
	BM1880_PINCTRL_GRP(gpio55),
	BM1880_PINCTRL_GRP(gpio56),
	BM1880_PINCTRL_GRP(gpio57),
	BM1880_PINCTRL_GRP(gpio58),
	BM1880_PINCTRL_GRP(gpio59),
	BM1880_PINCTRL_GRP(gpio60),
	BM1880_PINCTRL_GRP(gpio61),
	BM1880_PINCTRL_GRP(gpio62),
	BM1880_PINCTRL_GRP(gpio63),
	BM1880_PINCTRL_GRP(gpio64),
	BM1880_PINCTRL_GRP(gpio65),
	BM1880_PINCTRL_GRP(gpio66),
	BM1880_PINCTRL_GRP(gpio67),
	BM1880_PINCTRL_GRP(eth1),
	BM1880_PINCTRL_GRP(i2s0),
	BM1880_PINCTRL_GRP(i2s0_mclkin),
	BM1880_PINCTRL_GRP(i2s1),
	BM1880_PINCTRL_GRP(i2s1_mclkin),
	BM1880_PINCTRL_GRP(spi0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर nand_group[] = अणु "nand_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi_group[] = अणु "spi_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर emmc_group[] = अणु "emmc_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio_group[] = अणु "sdio_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर eth0_group[] = अणु "eth0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm0_group[] = अणु "pwm0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm1_group[] = अणु "pwm1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm2_group[] = अणु "pwm2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm3_group[] = अणु "pwm3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm4_group[] = अणु "pwm4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm5_group[] = अणु "pwm5_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm6_group[] = अणु "pwm6_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm7_group[] = अणु "pwm7_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm8_group[] = अणु "pwm8_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm9_group[] = अणु "pwm9_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm10_group[] = अणु "pwm10_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm11_group[] = अणु "pwm11_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm12_group[] = अणु "pwm12_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm13_group[] = अणु "pwm13_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm14_group[] = अणु "pwm14_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm15_group[] = अणु "pwm15_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm16_group[] = अणु "pwm16_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm17_group[] = अणु "pwm17_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm18_group[] = अणु "pwm18_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm19_group[] = अणु "pwm19_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm20_group[] = अणु "pwm20_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm21_group[] = अणु "pwm21_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm22_group[] = अणु "pwm22_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm23_group[] = अणु "pwm23_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm24_group[] = अणु "pwm24_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm25_group[] = अणु "pwm25_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm26_group[] = अणु "pwm26_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm27_group[] = अणु "pwm27_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm28_group[] = अणु "pwm28_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm29_group[] = अणु "pwm29_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm30_group[] = अणु "pwm30_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm31_group[] = अणु "pwm31_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm32_group[] = अणु "pwm32_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm33_group[] = अणु "pwm33_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm34_group[] = अणु "pwm34_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm35_group[] = अणु "pwm35_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm36_group[] = अणु "pwm36_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm37_group[] = अणु "pwm37_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c0_group[] = अणु "i2c0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c1_group[] = अणु "i2c1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c2_group[] = अणु "i2c2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c3_group[] = अणु "i2c3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c4_group[] = अणु "i2c4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart0_group[] = अणु "uart0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart1_group[] = अणु "uart1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart2_group[] = अणु "uart2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart3_group[] = अणु "uart3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart4_group[] = अणु "uart4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart5_group[] = अणु "uart5_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart6_group[] = अणु "uart6_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart7_group[] = अणु "uart7_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart8_group[] = अणु "uart8_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart9_group[] = अणु "uart9_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart10_group[] = अणु "uart10_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart11_group[] = अणु "uart11_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart12_group[] = अणु "uart12_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart13_group[] = अणु "uart13_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart14_group[] = अणु "uart14_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर uart15_group[] = अणु "uart15_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio0_group[] = अणु "gpio0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio1_group[] = अणु "gpio1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio2_group[] = अणु "gpio2_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio3_group[] = अणु "gpio3_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio4_group[] = अणु "gpio4_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio5_group[] = अणु "gpio5_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio6_group[] = अणु "gpio6_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio7_group[] = अणु "gpio7_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio8_group[] = अणु "gpio8_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio9_group[] = अणु "gpio9_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio10_group[] = अणु "gpio10_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio11_group[] = अणु "gpio11_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio12_group[] = अणु "gpio12_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio13_group[] = अणु "gpio13_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio14_group[] = अणु "gpio14_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio15_group[] = अणु "gpio15_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio16_group[] = अणु "gpio16_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio17_group[] = अणु "gpio17_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio18_group[] = अणु "gpio18_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio19_group[] = अणु "gpio19_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio20_group[] = अणु "gpio20_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio21_group[] = अणु "gpio21_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio22_group[] = अणु "gpio22_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio23_group[] = अणु "gpio23_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio24_group[] = अणु "gpio24_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio25_group[] = अणु "gpio25_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio26_group[] = अणु "gpio26_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio27_group[] = अणु "gpio27_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio28_group[] = अणु "gpio28_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio29_group[] = अणु "gpio29_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio30_group[] = अणु "gpio30_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio31_group[] = अणु "gpio31_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio32_group[] = अणु "gpio32_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio33_group[] = अणु "gpio33_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio34_group[] = अणु "gpio34_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio35_group[] = अणु "gpio35_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio36_group[] = अणु "gpio36_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio37_group[] = अणु "gpio37_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio38_group[] = अणु "gpio38_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio39_group[] = अणु "gpio39_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio40_group[] = अणु "gpio40_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio41_group[] = अणु "gpio41_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio42_group[] = अणु "gpio42_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio43_group[] = अणु "gpio43_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio44_group[] = अणु "gpio44_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio45_group[] = अणु "gpio45_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio46_group[] = अणु "gpio46_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio47_group[] = अणु "gpio47_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio48_group[] = अणु "gpio48_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio49_group[] = अणु "gpio49_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio50_group[] = अणु "gpio50_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio51_group[] = अणु "gpio51_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio52_group[] = अणु "gpio52_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio53_group[] = अणु "gpio53_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio54_group[] = अणु "gpio54_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio55_group[] = अणु "gpio55_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio56_group[] = अणु "gpio56_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio57_group[] = अणु "gpio57_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio58_group[] = अणु "gpio58_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio59_group[] = अणु "gpio59_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio60_group[] = अणु "gpio60_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio61_group[] = अणु "gpio61_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio62_group[] = अणु "gpio62_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio63_group[] = अणु "gpio63_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio64_group[] = अणु "gpio64_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio65_group[] = अणु "gpio65_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio66_group[] = अणु "gpio66_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio67_group[] = अणु "gpio67_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर eth1_group[] = अणु "eth1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s0_group[] = अणु "i2s0_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s0_mclkin_group[] = अणु "i2s0_mclkin_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s1_group[] = अणु "i2s1_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s1_mclkin_group[] = अणु "i2s1_mclkin_grp" पूर्ण;
अटल स्थिर अक्षर * स्थिर spi0_group[] = अणु "spi0_grp" पूर्ण;

#घोषणा BM1880_PINMUX_FUNCTION(fname, mval)		\
	[F_##fname] = अणु					\
		.name = #fname,				\
		.groups = fname##_group,		\
		.ngroups = ARRAY_SIZE(fname##_group),	\
		.mux_val = mval,			\
	पूर्ण

अटल स्थिर काष्ठा bm1880_pinmux_function bm1880_pmux_functions[] = अणु
	BM1880_PINMUX_FUNCTION(nand, 2),
	BM1880_PINMUX_FUNCTION(spi, 0),
	BM1880_PINMUX_FUNCTION(emmc, 1),
	BM1880_PINMUX_FUNCTION(sdio, 0),
	BM1880_PINMUX_FUNCTION(eth0, 0),
	BM1880_PINMUX_FUNCTION(pwm0, 2),
	BM1880_PINMUX_FUNCTION(pwm1, 2),
	BM1880_PINMUX_FUNCTION(pwm2, 2),
	BM1880_PINMUX_FUNCTION(pwm3, 2),
	BM1880_PINMUX_FUNCTION(pwm4, 2),
	BM1880_PINMUX_FUNCTION(pwm5, 2),
	BM1880_PINMUX_FUNCTION(pwm6, 2),
	BM1880_PINMUX_FUNCTION(pwm7, 2),
	BM1880_PINMUX_FUNCTION(pwm8, 2),
	BM1880_PINMUX_FUNCTION(pwm9, 2),
	BM1880_PINMUX_FUNCTION(pwm10, 2),
	BM1880_PINMUX_FUNCTION(pwm11, 2),
	BM1880_PINMUX_FUNCTION(pwm12, 2),
	BM1880_PINMUX_FUNCTION(pwm13, 2),
	BM1880_PINMUX_FUNCTION(pwm14, 2),
	BM1880_PINMUX_FUNCTION(pwm15, 2),
	BM1880_PINMUX_FUNCTION(pwm16, 2),
	BM1880_PINMUX_FUNCTION(pwm17, 2),
	BM1880_PINMUX_FUNCTION(pwm18, 2),
	BM1880_PINMUX_FUNCTION(pwm19, 2),
	BM1880_PINMUX_FUNCTION(pwm20, 2),
	BM1880_PINMUX_FUNCTION(pwm21, 2),
	BM1880_PINMUX_FUNCTION(pwm22, 2),
	BM1880_PINMUX_FUNCTION(pwm23, 2),
	BM1880_PINMUX_FUNCTION(pwm24, 2),
	BM1880_PINMUX_FUNCTION(pwm25, 2),
	BM1880_PINMUX_FUNCTION(pwm26, 2),
	BM1880_PINMUX_FUNCTION(pwm27, 2),
	BM1880_PINMUX_FUNCTION(pwm28, 2),
	BM1880_PINMUX_FUNCTION(pwm29, 2),
	BM1880_PINMUX_FUNCTION(pwm30, 2),
	BM1880_PINMUX_FUNCTION(pwm31, 2),
	BM1880_PINMUX_FUNCTION(pwm32, 2),
	BM1880_PINMUX_FUNCTION(pwm33, 2),
	BM1880_PINMUX_FUNCTION(pwm34, 2),
	BM1880_PINMUX_FUNCTION(pwm35, 2),
	BM1880_PINMUX_FUNCTION(pwm36, 2),
	BM1880_PINMUX_FUNCTION(pwm37, 2),
	BM1880_PINMUX_FUNCTION(i2c0, 1),
	BM1880_PINMUX_FUNCTION(i2c1, 1),
	BM1880_PINMUX_FUNCTION(i2c2, 1),
	BM1880_PINMUX_FUNCTION(i2c3, 1),
	BM1880_PINMUX_FUNCTION(i2c4, 1),
	BM1880_PINMUX_FUNCTION(uart0, 3),
	BM1880_PINMUX_FUNCTION(uart1, 3),
	BM1880_PINMUX_FUNCTION(uart2, 3),
	BM1880_PINMUX_FUNCTION(uart3, 3),
	BM1880_PINMUX_FUNCTION(uart4, 1),
	BM1880_PINMUX_FUNCTION(uart5, 1),
	BM1880_PINMUX_FUNCTION(uart6, 1),
	BM1880_PINMUX_FUNCTION(uart7, 1),
	BM1880_PINMUX_FUNCTION(uart8, 1),
	BM1880_PINMUX_FUNCTION(uart9, 1),
	BM1880_PINMUX_FUNCTION(uart10, 1),
	BM1880_PINMUX_FUNCTION(uart11, 1),
	BM1880_PINMUX_FUNCTION(uart12, 3),
	BM1880_PINMUX_FUNCTION(uart13, 3),
	BM1880_PINMUX_FUNCTION(uart14, 3),
	BM1880_PINMUX_FUNCTION(uart15, 3),
	BM1880_PINMUX_FUNCTION(gpio0, 0),
	BM1880_PINMUX_FUNCTION(gpio1, 0),
	BM1880_PINMUX_FUNCTION(gpio2, 0),
	BM1880_PINMUX_FUNCTION(gpio3, 0),
	BM1880_PINMUX_FUNCTION(gpio4, 0),
	BM1880_PINMUX_FUNCTION(gpio5, 0),
	BM1880_PINMUX_FUNCTION(gpio6, 0),
	BM1880_PINMUX_FUNCTION(gpio7, 0),
	BM1880_PINMUX_FUNCTION(gpio8, 0),
	BM1880_PINMUX_FUNCTION(gpio9, 0),
	BM1880_PINMUX_FUNCTION(gpio10, 0),
	BM1880_PINMUX_FUNCTION(gpio11, 0),
	BM1880_PINMUX_FUNCTION(gpio12, 1),
	BM1880_PINMUX_FUNCTION(gpio13, 1),
	BM1880_PINMUX_FUNCTION(gpio14, 0),
	BM1880_PINMUX_FUNCTION(gpio15, 0),
	BM1880_PINMUX_FUNCTION(gpio16, 0),
	BM1880_PINMUX_FUNCTION(gpio17, 0),
	BM1880_PINMUX_FUNCTION(gpio18, 0),
	BM1880_PINMUX_FUNCTION(gpio19, 0),
	BM1880_PINMUX_FUNCTION(gpio20, 0),
	BM1880_PINMUX_FUNCTION(gpio21, 0),
	BM1880_PINMUX_FUNCTION(gpio22, 0),
	BM1880_PINMUX_FUNCTION(gpio23, 0),
	BM1880_PINMUX_FUNCTION(gpio24, 0),
	BM1880_PINMUX_FUNCTION(gpio25, 0),
	BM1880_PINMUX_FUNCTION(gpio26, 0),
	BM1880_PINMUX_FUNCTION(gpio27, 0),
	BM1880_PINMUX_FUNCTION(gpio28, 0),
	BM1880_PINMUX_FUNCTION(gpio29, 0),
	BM1880_PINMUX_FUNCTION(gpio30, 0),
	BM1880_PINMUX_FUNCTION(gpio31, 0),
	BM1880_PINMUX_FUNCTION(gpio32, 0),
	BM1880_PINMUX_FUNCTION(gpio33, 0),
	BM1880_PINMUX_FUNCTION(gpio34, 0),
	BM1880_PINMUX_FUNCTION(gpio35, 0),
	BM1880_PINMUX_FUNCTION(gpio36, 0),
	BM1880_PINMUX_FUNCTION(gpio37, 0),
	BM1880_PINMUX_FUNCTION(gpio38, 0),
	BM1880_PINMUX_FUNCTION(gpio39, 0),
	BM1880_PINMUX_FUNCTION(gpio40, 0),
	BM1880_PINMUX_FUNCTION(gpio41, 0),
	BM1880_PINMUX_FUNCTION(gpio42, 0),
	BM1880_PINMUX_FUNCTION(gpio43, 0),
	BM1880_PINMUX_FUNCTION(gpio44, 0),
	BM1880_PINMUX_FUNCTION(gpio45, 0),
	BM1880_PINMUX_FUNCTION(gpio46, 0),
	BM1880_PINMUX_FUNCTION(gpio47, 0),
	BM1880_PINMUX_FUNCTION(gpio48, 0),
	BM1880_PINMUX_FUNCTION(gpio49, 0),
	BM1880_PINMUX_FUNCTION(gpio50, 0),
	BM1880_PINMUX_FUNCTION(gpio51, 0),
	BM1880_PINMUX_FUNCTION(gpio52, 0),
	BM1880_PINMUX_FUNCTION(gpio53, 0),
	BM1880_PINMUX_FUNCTION(gpio54, 0),
	BM1880_PINMUX_FUNCTION(gpio55, 0),
	BM1880_PINMUX_FUNCTION(gpio56, 0),
	BM1880_PINMUX_FUNCTION(gpio57, 0),
	BM1880_PINMUX_FUNCTION(gpio58, 0),
	BM1880_PINMUX_FUNCTION(gpio59, 0),
	BM1880_PINMUX_FUNCTION(gpio60, 0),
	BM1880_PINMUX_FUNCTION(gpio61, 0),
	BM1880_PINMUX_FUNCTION(gpio62, 0),
	BM1880_PINMUX_FUNCTION(gpio63, 0),
	BM1880_PINMUX_FUNCTION(gpio64, 0),
	BM1880_PINMUX_FUNCTION(gpio65, 0),
	BM1880_PINMUX_FUNCTION(gpio66, 0),
	BM1880_PINMUX_FUNCTION(gpio67, 0),
	BM1880_PINMUX_FUNCTION(eth1, 1),
	BM1880_PINMUX_FUNCTION(i2s0, 2),
	BM1880_PINMUX_FUNCTION(i2s0_mclkin, 1),
	BM1880_PINMUX_FUNCTION(i2s1, 2),
	BM1880_PINMUX_FUNCTION(i2s1_mclkin, 1),
	BM1880_PINMUX_FUNCTION(spi0, 1),
पूर्ण;

#घोषणा BM1880_PINCONF_DAT(_width)		\
	अणु					\
		.drv_bits = _width,		\
	पूर्ण

अटल स्थिर काष्ठा bm1880_pinconf_data bm1880_pinconf[] = अणु
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x03),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
	BM1880_PINCONF_DAT(0x02),
पूर्ण;

अटल पूर्णांक bm1880_pctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->ngroups;
पूर्ण

अटल स्थिर अक्षर *bm1880_pctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित पूर्णांक selector)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->groups[selector].name;
पूर्ण

अटल पूर्णांक bm1880_pctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक selector,
				       स्थिर अचिन्हित पूर्णांक **pins,
				       अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = pctrl->groups[selector].pins;
	*num_pins = pctrl->groups[selector].npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops bm1880_pctrl_ops = अणु
	.get_groups_count = bm1880_pctrl_get_groups_count,
	.get_group_name = bm1880_pctrl_get_group_name,
	.get_group_pins = bm1880_pctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

/* pinmux */
अटल पूर्णांक bm1880_pmux_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->nfuncs;
पूर्ण

अटल स्थिर अक्षर *bm1880_pmux_get_function_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->funcs[selector].name;
पूर्ण

अटल पूर्णांक bm1880_pmux_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक selector,
					   स्थिर अक्षर * स्थिर **groups,
					   अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctrl->funcs[selector].groups;
	*num_groups = pctrl->funcs[selector].ngroups;
	वापस 0;
पूर्ण

अटल पूर्णांक bm1880_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक function,
				 अचिन्हित पूर्णांक  group)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा bm1880_pctrl_group *pgrp = &pctrl->groups[group];
	स्थिर काष्ठा bm1880_pinmux_function *func = &pctrl->funcs[function];
	पूर्णांक i;

	क्रम (i = 0; i < pgrp->npins; i++) अणु
		अचिन्हित पूर्णांक pin = pgrp->pins[i];
		u32 offset = (pin >> 1) << 2;
		u32 mux_offset = ((!((pin + 1) & 1) << 4) + 4);
		u32 regval = पढ़ोl_relaxed(pctrl->base + BM1880_REG_MUX +
					   offset);

		regval &= ~(0x03 << mux_offset);
		regval |= func->mux_val << mux_offset;

		ग_लिखोl_relaxed(regval, pctrl->base + BM1880_REG_MUX + offset);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा BM1880_PINCONF(pin, idx) ((!((pin + 1) & 1) << 4) + idx)
#घोषणा BM1880_PINCONF_PULLCTRL(pin)	BM1880_PINCONF(pin, 0)
#घोषणा BM1880_PINCONF_PULLUP(pin)	BM1880_PINCONF(pin, 1)
#घोषणा BM1880_PINCONF_PULLDOWN(pin)	BM1880_PINCONF(pin, 2)
#घोषणा BM1880_PINCONF_DRV(pin)		BM1880_PINCONF(pin, 6)
#घोषणा BM1880_PINCONF_SCHMITT(pin)	BM1880_PINCONF(pin, 9)
#घोषणा BM1880_PINCONF_SLEW(pin)	BM1880_PINCONF(pin, 10)

अटल पूर्णांक bm1880_pinconf_drv_set(अचिन्हित पूर्णांक mA, u32 width,
				  u32 *regval, u32 bit_offset)
अणु
	u32 _regval;

	_regval = *regval;

	/*
	 * There are two sets of drive strength bit width exposed by the
	 * SoC at 4mA step, hence we need to handle them separately.
	 */
	अगर (width == 0x03) अणु
		चयन (mA) अणु
		हाल 4:
			_regval &= ~(width << bit_offset);
			_regval |= (0 << bit_offset);
			अवरोध;
		हाल 8:
			_regval &= ~(width << bit_offset);
			_regval |= (1 << bit_offset);
			अवरोध;
		हाल 12:
			_regval &= ~(width << bit_offset);
			_regval |= (2 << bit_offset);
			अवरोध;
		हाल 16:
			_regval &= ~(width << bit_offset);
			_regval |= (3 << bit_offset);
			अवरोध;
		हाल 20:
			_regval &= ~(width << bit_offset);
			_regval |= (4 << bit_offset);
			अवरोध;
		हाल 24:
			_regval &= ~(width << bit_offset);
			_regval |= (5 << bit_offset);
			अवरोध;
		हाल 28:
			_regval &= ~(width << bit_offset);
			_regval |= (6 << bit_offset);
			अवरोध;
		हाल 32:
			_regval &= ~(width << bit_offset);
			_regval |= (7 << bit_offset);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (mA) अणु
		हाल 4:
			_regval &= ~(width << bit_offset);
			_regval |= (0 << bit_offset);
			अवरोध;
		हाल 8:
			_regval &= ~(width << bit_offset);
			_regval |= (1 << bit_offset);
			अवरोध;
		हाल 12:
			_regval &= ~(width << bit_offset);
			_regval |= (2 << bit_offset);
			अवरोध;
		हाल 16:
			_regval &= ~(width << bit_offset);
			_regval |= (3 << bit_offset);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	*regval = _regval;

	वापस 0;
पूर्ण

अटल पूर्णांक bm1880_pinconf_drv_get(u32 width, u32 drv)
अणु
	पूर्णांक ret = -ENOTSUPP;

	/*
	 * There are two sets of drive strength bit width exposed by the
	 * SoC at 4mA step, hence we need to handle them separately.
	 */
	अगर (width == 0x03) अणु
		चयन (drv) अणु
		हाल 0:
			ret  = 4;
			अवरोध;
		हाल 1:
			ret  = 8;
			अवरोध;
		हाल 2:
			ret  = 12;
			अवरोध;
		हाल 3:
			ret  = 16;
			अवरोध;
		हाल 4:
			ret  = 20;
			अवरोध;
		हाल 5:
			ret  = 24;
			अवरोध;
		हाल 6:
			ret  = 28;
			अवरोध;
		हाल 7:
			ret  = 32;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (drv) अणु
		हाल 0:
			ret  = 4;
			अवरोध;
		हाल 1:
			ret  = 8;
			अवरोध;
		हाल 2:
			ret  = 12;
			अवरोध;
		हाल 3:
			ret  = 16;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bm1880_pinconf_cfg_get(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक pin,
				  अचिन्हित दीर्घ *config)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक arg = 0;
	u32 regval, offset, bit_offset;
	पूर्णांक ret;

	offset = (pin >> 1) << 2;
	regval = पढ़ोl_relaxed(pctrl->base + BM1880_REG_MUX + offset);

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		bit_offset = BM1880_PINCONF_PULLUP(pin);
		arg = !!(regval & BIT(bit_offset));
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		bit_offset = BM1880_PINCONF_PULLDOWN(pin);
		arg = !!(regval & BIT(bit_offset));
		अवरोध;
	हाल PIN_CONFIG_BIAS_DISABLE:
		bit_offset = BM1880_PINCONF_PULLCTRL(pin);
		arg = !!(regval & BIT(bit_offset));
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		bit_offset = BM1880_PINCONF_SCHMITT(pin);
		arg = !!(regval & BIT(bit_offset));
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		bit_offset = BM1880_PINCONF_SLEW(pin);
		arg = !!(regval & BIT(bit_offset));
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		bit_offset = BM1880_PINCONF_DRV(pin);
		ret = bm1880_pinconf_drv_get(pctrl->pinconf[pin].drv_bits,
					     !!(regval & BIT(bit_offset)));
		अगर (ret < 0)
			वापस ret;

		arg = ret;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक bm1880_pinconf_cfg_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक pin,
				  अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	u32 regval, offset, bit_offset;
	पूर्णांक i, ret;

	offset = (pin >> 1) << 2;
	regval = पढ़ोl_relaxed(pctrl->base + BM1880_REG_MUX + offset);

	क्रम (i = 0; i < num_configs; i++) अणु
		अचिन्हित पूर्णांक param = pinconf_to_config_param(configs[i]);
		अचिन्हित पूर्णांक arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			bit_offset = BM1880_PINCONF_PULLUP(pin);
			regval |= BIT(bit_offset);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			bit_offset = BM1880_PINCONF_PULLDOWN(pin);
			regval |= BIT(bit_offset);
			अवरोध;
		हाल PIN_CONFIG_BIAS_DISABLE:
			bit_offset = BM1880_PINCONF_PULLCTRL(pin);
			regval |= BIT(bit_offset);
			अवरोध;
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			bit_offset = BM1880_PINCONF_SCHMITT(pin);
			अगर (arg)
				regval |= BIT(bit_offset);
			अन्यथा
				regval &= ~BIT(bit_offset);
			अवरोध;
		हाल PIN_CONFIG_SLEW_RATE:
			bit_offset = BM1880_PINCONF_SLEW(pin);
			अगर (arg)
				regval |= BIT(bit_offset);
			अन्यथा
				regval &= ~BIT(bit_offset);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			bit_offset = BM1880_PINCONF_DRV(pin);
			ret = bm1880_pinconf_drv_set(arg,
						pctrl->pinconf[pin].drv_bits,
						&regval, bit_offset);
			अगर (ret < 0)
				वापस ret;

			अवरोध;
		शेष:
			dev_warn(pctldev->dev,
				 "unsupported configuration parameter '%u'\n",
				 param);
			जारी;
		पूर्ण

		ग_लिखोl_relaxed(regval, pctrl->base + BM1880_REG_MUX + offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bm1880_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित पूर्णांक selector,
				    अचिन्हित दीर्घ *configs,
				    अचिन्हित पूर्णांक  num_configs)
अणु
	पूर्णांक i, ret;
	काष्ठा bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा bm1880_pctrl_group *pgrp = &pctrl->groups[selector];

	क्रम (i = 0; i < pgrp->npins; i++) अणु
		ret = bm1880_pinconf_cfg_set(pctldev, pgrp->pins[i], configs,
					     num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops bm1880_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = bm1880_pinconf_cfg_get,
	.pin_config_set = bm1880_pinconf_cfg_set,
	.pin_config_group_set = bm1880_pinconf_group_set,
पूर्ण;

अटल स्थिर काष्ठा pinmux_ops bm1880_pinmux_ops = अणु
	.get_functions_count = bm1880_pmux_get_functions_count,
	.get_function_name = bm1880_pmux_get_function_name,
	.get_function_groups = bm1880_pmux_get_function_groups,
	.set_mux = bm1880_pinmux_set_mux,
पूर्ण;

अटल काष्ठा pinctrl_desc bm1880_desc = अणु
	.name = "bm1880_pinctrl",
	.pins = bm1880_pins,
	.npins = ARRAY_SIZE(bm1880_pins),
	.pctlops = &bm1880_pctrl_ops,
	.pmxops = &bm1880_pinmux_ops,
	.confops = &bm1880_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक bm1880_pinctrl_probe(काष्ठा platक्रमm_device *pdev)

अणु
	काष्ठा bm1880_pinctrl *pctrl;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pctrl->base))
		वापस PTR_ERR(pctrl->base);

	pctrl->groups = bm1880_pctrl_groups;
	pctrl->ngroups = ARRAY_SIZE(bm1880_pctrl_groups);
	pctrl->funcs = bm1880_pmux_functions;
	pctrl->nfuncs = ARRAY_SIZE(bm1880_pmux_functions);
	pctrl->pinconf = bm1880_pinconf;

	pctrl->pctrldev = devm_pinctrl_रेजिस्टर(&pdev->dev, &bm1880_desc,
						pctrl);
	अगर (IS_ERR(pctrl->pctrldev))
		वापस PTR_ERR(pctrl->pctrldev);

	platक्रमm_set_drvdata(pdev, pctrl);

	dev_info(&pdev->dev, "BM1880 pinctrl driver initialized\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bm1880_pinctrl_of_match[] = अणु
	अणु .compatible = "bitmain,bm1880-pinctrl" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bm1880_pinctrl_driver = अणु
	.driver = अणु
		.name = "pinctrl-bm1880",
		.of_match_table = of_match_ptr(bm1880_pinctrl_of_match),
	पूर्ण,
	.probe = bm1880_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init bm1880_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&bm1880_pinctrl_driver);
पूर्ण
arch_initcall(bm1880_pinctrl_init);
