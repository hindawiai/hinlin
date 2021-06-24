<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Zynq pin controller
 *
 *  Copyright (C) 2014 Xilinx
 *
 *  Sथघren Brinkmann <soren.brinkmann@xilinx.com>
 */
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/regmap.h>
#समावेश "pinctrl-utils.h"
#समावेश "core.h"

#घोषणा ZYNQ_NUM_MIOS	54

#घोषणा ZYNQ_PCTRL_MIO_MST_TRI0	0x10c
#घोषणा ZYNQ_PCTRL_MIO_MST_TRI1	0x110

#घोषणा ZYNQ_PINMUX_MUX_SHIFT	1
#घोषणा ZYNQ_PINMUX_MUX_MASK	(0x7f << ZYNQ_PINMUX_MUX_SHIFT)

/**
 * काष्ठा zynq_pinctrl - driver data
 * @pctrl:		Pinctrl device
 * @syscon:		Syscon regmap
 * @pctrl_offset:	Offset क्रम pinctrl पूर्णांकo the @syscon space
 * @groups:		Pingroups
 * @ngroups:		Number of @groups
 * @funcs:		Pinmux functions
 * @nfuncs:		Number of @funcs
 */
काष्ठा zynq_pinctrl अणु
	काष्ठा pinctrl_dev *pctrl;
	काष्ठा regmap *syscon;
	u32 pctrl_offset;
	स्थिर काष्ठा zynq_pctrl_group *groups;
	अचिन्हित पूर्णांक ngroups;
	स्थिर काष्ठा zynq_pinmux_function *funcs;
	अचिन्हित पूर्णांक nfuncs;
पूर्ण;

काष्ठा zynq_pctrl_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक npins;
पूर्ण;

/**
 * काष्ठा zynq_pinmux_function - a pinmux function
 * @name:	Name of the pinmux function.
 * @groups:	List of pingroups क्रम this function.
 * @ngroups:	Number of entries in @groups.
 * @mux_val:	Selector क्रम this function
 * @mux:	Offset of function specअगरic mux
 * @mux_mask:	Mask क्रम function specअगरic selector
 * @mux_shअगरt:	Shअगरt क्रम function specअगरic selector
 */
काष्ठा zynq_pinmux_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
	अचिन्हित पूर्णांक mux_val;
	u32 mux;
	u32 mux_mask;
	u8 mux_shअगरt;
पूर्ण;

क्रमागत zynq_pinmux_functions अणु
	ZYNQ_PMUX_can0,
	ZYNQ_PMUX_can1,
	ZYNQ_PMUX_ethernet0,
	ZYNQ_PMUX_ethernet1,
	ZYNQ_PMUX_gpio0,
	ZYNQ_PMUX_i2c0,
	ZYNQ_PMUX_i2c1,
	ZYNQ_PMUX_mdio0,
	ZYNQ_PMUX_mdio1,
	ZYNQ_PMUX_qspi0,
	ZYNQ_PMUX_qspi1,
	ZYNQ_PMUX_qspi_fbclk,
	ZYNQ_PMUX_qspi_cs1,
	ZYNQ_PMUX_spi0,
	ZYNQ_PMUX_spi1,
	ZYNQ_PMUX_spi0_ss,
	ZYNQ_PMUX_spi1_ss,
	ZYNQ_PMUX_sdio0,
	ZYNQ_PMUX_sdio0_pc,
	ZYNQ_PMUX_sdio0_cd,
	ZYNQ_PMUX_sdio0_wp,
	ZYNQ_PMUX_sdio1,
	ZYNQ_PMUX_sdio1_pc,
	ZYNQ_PMUX_sdio1_cd,
	ZYNQ_PMUX_sdio1_wp,
	ZYNQ_PMUX_smc0_nor,
	ZYNQ_PMUX_smc0_nor_cs1,
	ZYNQ_PMUX_smc0_nor_addr25,
	ZYNQ_PMUX_smc0_nand,
	ZYNQ_PMUX_ttc0,
	ZYNQ_PMUX_ttc1,
	ZYNQ_PMUX_uart0,
	ZYNQ_PMUX_uart1,
	ZYNQ_PMUX_usb0,
	ZYNQ_PMUX_usb1,
	ZYNQ_PMUX_swdt0,
	ZYNQ_PMUX_MAX_FUNC
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc zynq_pins[] = अणु
	PINCTRL_PIN(0,  "MIO0"),
	PINCTRL_PIN(1,  "MIO1"),
	PINCTRL_PIN(2,  "MIO2"),
	PINCTRL_PIN(3,  "MIO3"),
	PINCTRL_PIN(4,  "MIO4"),
	PINCTRL_PIN(5,  "MIO5"),
	PINCTRL_PIN(6,  "MIO6"),
	PINCTRL_PIN(7,  "MIO7"),
	PINCTRL_PIN(8,  "MIO8"),
	PINCTRL_PIN(9,  "MIO9"),
	PINCTRL_PIN(10, "MIO10"),
	PINCTRL_PIN(11, "MIO11"),
	PINCTRL_PIN(12, "MIO12"),
	PINCTRL_PIN(13, "MIO13"),
	PINCTRL_PIN(14, "MIO14"),
	PINCTRL_PIN(15, "MIO15"),
	PINCTRL_PIN(16, "MIO16"),
	PINCTRL_PIN(17, "MIO17"),
	PINCTRL_PIN(18, "MIO18"),
	PINCTRL_PIN(19, "MIO19"),
	PINCTRL_PIN(20, "MIO20"),
	PINCTRL_PIN(21, "MIO21"),
	PINCTRL_PIN(22, "MIO22"),
	PINCTRL_PIN(23, "MIO23"),
	PINCTRL_PIN(24, "MIO24"),
	PINCTRL_PIN(25, "MIO25"),
	PINCTRL_PIN(26, "MIO26"),
	PINCTRL_PIN(27, "MIO27"),
	PINCTRL_PIN(28, "MIO28"),
	PINCTRL_PIN(29, "MIO29"),
	PINCTRL_PIN(30, "MIO30"),
	PINCTRL_PIN(31, "MIO31"),
	PINCTRL_PIN(32, "MIO32"),
	PINCTRL_PIN(33, "MIO33"),
	PINCTRL_PIN(34, "MIO34"),
	PINCTRL_PIN(35, "MIO35"),
	PINCTRL_PIN(36, "MIO36"),
	PINCTRL_PIN(37, "MIO37"),
	PINCTRL_PIN(38, "MIO38"),
	PINCTRL_PIN(39, "MIO39"),
	PINCTRL_PIN(40, "MIO40"),
	PINCTRL_PIN(41, "MIO41"),
	PINCTRL_PIN(42, "MIO42"),
	PINCTRL_PIN(43, "MIO43"),
	PINCTRL_PIN(44, "MIO44"),
	PINCTRL_PIN(45, "MIO45"),
	PINCTRL_PIN(46, "MIO46"),
	PINCTRL_PIN(47, "MIO47"),
	PINCTRL_PIN(48, "MIO48"),
	PINCTRL_PIN(49, "MIO49"),
	PINCTRL_PIN(50, "MIO50"),
	PINCTRL_PIN(51, "MIO51"),
	PINCTRL_PIN(52, "MIO52"),
	PINCTRL_PIN(53, "MIO53"),
	PINCTRL_PIN(54, "EMIO_SD0_WP"),
	PINCTRL_PIN(55, "EMIO_SD0_CD"),
	PINCTRL_PIN(56, "EMIO_SD1_WP"),
	PINCTRL_PIN(57, "EMIO_SD1_CD"),
पूर्ण;

/* pin groups */
अटल स्थिर अचिन्हित पूर्णांक ethernet0_0_pins[] = अणु16, 17, 18, 19, 20, 21, 22, 23,
						24, 25, 26, 27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ethernet1_0_pins[] = अणु28, 29, 30, 31, 32, 33, 34, 35,
						36, 37, 38, 39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mdio0_0_pins[] = अणु52, 53पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mdio1_0_pins[] = अणु52, 53पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi0_0_pins[] = अणु1, 2, 3, 4, 5, 6पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक qspi1_0_pins[] = अणु9, 10, 11, 12, 13पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi_cs1_pins[] = अणु0पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi_fbclk_pins[] = अणु8पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_0_pins[] = अणु16, 17, 21पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_0_ss0_pins[] = अणु18पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_0_ss1_pins[] = अणु19पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_0_ss2_pins[] = अणु20,पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_1_pins[] = अणु28, 29, 33पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_1_ss0_pins[] = अणु30पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_1_ss1_pins[] = अणु31पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_1_ss2_pins[] = अणु32पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_2_pins[] = अणु40, 41, 45पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_2_ss0_pins[] = अणु42पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_2_ss1_pins[] = अणु43पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi0_2_ss2_pins[] = अणु44पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_0_pins[] = अणु10, 11, 12पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_0_ss0_pins[] = अणु13पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_0_ss1_pins[] = अणु14पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_0_ss2_pins[] = अणु15पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_1_pins[] = अणु22, 23, 24पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_1_ss0_pins[] = अणु25पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_1_ss1_pins[] = अणु26पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_1_ss2_pins[] = अणु27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_2_pins[] = अणु34, 35, 36पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_2_ss0_pins[] = अणु37पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_2_ss1_pins[] = अणु38पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_2_ss2_pins[] = अणु39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_3_pins[] = अणु46, 47, 48, 49पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_3_ss0_pins[] = अणु49पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_3_ss1_pins[] = अणु50पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi1_3_ss2_pins[] = अणु51पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sdio0_0_pins[] = अणु16, 17, 18, 19, 20, 21पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio0_1_pins[] = अणु28, 29, 30, 31, 32, 33पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio0_2_pins[] = अणु40, 41, 42, 43, 44, 45पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio1_0_pins[] = अणु10, 11, 12, 13, 14, 15पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio1_1_pins[] = अणु22, 23, 24, 25, 26, 27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio1_2_pins[] = अणु34, 35, 36, 37, 38, 39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio1_3_pins[] = अणु46, 47, 48, 49, 50, 51पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio0_emio_wp_pins[] = अणु54पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio0_emio_cd_pins[] = अणु55पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio1_emio_wp_pins[] = अणु56पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio1_emio_cd_pins[] = अणु57पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक smc0_nor_pins[] = अणु0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13,
					     15, 16, 17, 18, 19, 20, 21, 22, 23,
					     24, 25, 26, 27, 28, 29, 30, 31, 32,
					     33, 34, 35, 36, 37, 38, 39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक smc0_nor_cs1_pins[] = अणु1पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक smc0_nor_addr25_pins[] = अणु1पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक smc0_nand_pins[] = अणु0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
					      12, 13, 14, 16, 17, 18, 19, 20,
					      21, 22, 23पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक smc0_nand8_pins[] = अणु0, 2, 3,  4,  5,  6,  7,
					       8, 9, 10, 11, 12, 13, 14पूर्ण;
/* Note: CAN MIO घड़ी inमाला_दो are modeled in the घड़ी framework */
अटल स्थिर अचिन्हित पूर्णांक can0_0_pins[] = अणु10, 11पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_1_pins[] = अणु14, 15पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_2_pins[] = अणु18, 19पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_3_pins[] = अणु22, 23पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_4_pins[] = अणु26, 27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_5_pins[] = अणु30, 31पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_6_pins[] = अणु34, 35पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_7_pins[] = अणु38, 39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_8_pins[] = अणु42, 43पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_9_pins[] = अणु46, 47पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can0_10_pins[] = अणु50, 51पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_0_pins[] = अणु8, 9पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_1_pins[] = अणु12, 13पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_2_pins[] = अणु16, 17पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_3_pins[] = अणु20, 21पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_4_pins[] = अणु24, 25पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_5_pins[] = अणु28, 29पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_6_pins[] = अणु32, 33पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_7_pins[] = अणु36, 37पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_8_pins[] = अणु40, 41पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_9_pins[] = अणु44, 45पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_10_pins[] = अणु48, 49पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can1_11_pins[] = अणु52, 53पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_0_pins[] = अणु10, 11पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_1_pins[] = अणु14, 15पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_2_pins[] = अणु18, 19पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_3_pins[] = अणु22, 23पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_4_pins[] = अणु26, 27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_5_pins[] = अणु30, 31पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_6_pins[] = अणु34, 35पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_7_pins[] = अणु38, 39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_8_pins[] = अणु42, 43पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_9_pins[] = अणु46, 47पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart0_10_pins[] = अणु50, 51पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_0_pins[] = अणु8, 9पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_1_pins[] = अणु12, 13पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_2_pins[] = अणु16, 17पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_3_pins[] = अणु20, 21पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_4_pins[] = अणु24, 25पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_5_pins[] = अणु28, 29पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_6_pins[] = अणु32, 33पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_7_pins[] = अणु36, 37पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_8_pins[] = अणु40, 41पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_9_pins[] = अणु44, 45पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_10_pins[] = अणु48, 49पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_11_pins[] = अणु52, 53पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_0_pins[] = अणु10, 11पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_1_pins[] = अणु14, 15पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_2_pins[] = अणु18, 19पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_3_pins[] = अणु22, 23पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_4_pins[] = अणु26, 27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_5_pins[] = अणु30, 31पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_6_pins[] = अणु34, 35पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_7_pins[] = अणु38, 39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_8_pins[] = अणु42, 43पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_9_pins[] = अणु46, 47पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_10_pins[] = अणु50, 51पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_0_pins[] = अणु12, 13पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_1_pins[] = अणु16, 17पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_2_pins[] = अणु20, 21पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_3_pins[] = अणु24, 25पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_4_pins[] = अणु28, 29पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_5_pins[] = अणु32, 33पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_6_pins[] = अणु36, 37पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_7_pins[] = अणु40, 41पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_8_pins[] = अणु44, 45पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_9_pins[] = अणु48, 49पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_10_pins[] = अणु52, 53पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ttc0_0_pins[] = अणु18, 19पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ttc0_1_pins[] = अणु30, 31पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ttc0_2_pins[] = अणु42, 43पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ttc1_0_pins[] = अणु16, 17पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ttc1_1_pins[] = अणु28, 29पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ttc1_2_pins[] = अणु40, 41पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक swdt0_0_pins[] = अणु14, 15पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक swdt0_1_pins[] = अणु26, 27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक swdt0_2_pins[] = अणु38, 39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक swdt0_3_pins[] = अणु50, 51पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक swdt0_4_pins[] = अणु52, 53पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_0_pins[] = अणु0पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_1_pins[] = अणु1पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_2_pins[] = अणु2पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_3_pins[] = अणु3पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_4_pins[] = अणु4पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_5_pins[] = अणु5पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_6_pins[] = अणु6पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_7_pins[] = अणु7पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_8_pins[] = अणु8पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_9_pins[] = अणु9पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_10_pins[] = अणु10पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_11_pins[] = अणु11पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_12_pins[] = अणु12पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_13_pins[] = अणु13पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_14_pins[] = अणु14पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_15_pins[] = अणु15पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_16_pins[] = अणु16पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_17_pins[] = अणु17पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_18_pins[] = अणु18पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_19_pins[] = अणु19पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_20_pins[] = अणु20पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_21_pins[] = अणु21पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_22_pins[] = अणु22पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_23_pins[] = अणु23पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_24_pins[] = अणु24पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_25_pins[] = अणु25पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_26_pins[] = अणु26पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_27_pins[] = अणु27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_28_pins[] = अणु28पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_29_pins[] = अणु29पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_30_pins[] = अणु30पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_31_pins[] = अणु31पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_32_pins[] = अणु32पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_33_pins[] = अणु33पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_34_pins[] = अणु34पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_35_pins[] = अणु35पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_36_pins[] = अणु36पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_37_pins[] = अणु37पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_38_pins[] = अणु38पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_39_pins[] = अणु39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_40_pins[] = अणु40पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_41_pins[] = अणु41पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_42_pins[] = अणु42पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_43_pins[] = अणु43पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_44_pins[] = अणु44पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_45_pins[] = अणु45पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_46_pins[] = अणु46पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_47_pins[] = अणु47पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_48_pins[] = अणु48पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_49_pins[] = अणु49पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_50_pins[] = अणु50पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_51_pins[] = अणु51पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_52_pins[] = अणु52पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio0_53_pins[] = अणु53पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक usb0_0_pins[] = अणु28, 29, 30, 31, 32, 33, 34, 35, 36,
					   37, 38, 39पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक usb1_0_pins[] = अणु40, 41, 42, 43, 44, 45, 46, 47, 48,
					   49, 50, 51पूर्ण;

#घोषणा DEFINE_ZYNQ_PINCTRL_GRP(nm) \
	अणु \
		.name = #nm "_grp", \
		.pins = nm ## _pins, \
		.npins = ARRAY_SIZE(nm ## _pins), \
	पूर्ण

अटल स्थिर काष्ठा zynq_pctrl_group zynq_pctrl_groups[] = अणु
	DEFINE_ZYNQ_PINCTRL_GRP(ethernet0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(ethernet1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(mdio0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(mdio1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(qspi0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(qspi1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(qspi_fbclk),
	DEFINE_ZYNQ_PINCTRL_GRP(qspi_cs1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_0_ss0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_0_ss1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_0_ss2),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_1_ss0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_1_ss1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_1_ss2),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_2),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_2_ss0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_2_ss1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi0_2_ss2),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_0_ss0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_0_ss1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_0_ss2),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_1_ss0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_1_ss1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_1_ss2),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_2),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_2_ss0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_2_ss1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_2_ss2),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_3),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_3_ss0),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_3_ss1),
	DEFINE_ZYNQ_PINCTRL_GRP(spi1_3_ss2),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio0_1),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio0_2),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio1_1),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio1_2),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio1_3),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio0_emio_wp),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio0_emio_cd),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio1_emio_wp),
	DEFINE_ZYNQ_PINCTRL_GRP(sdio1_emio_cd),
	DEFINE_ZYNQ_PINCTRL_GRP(smc0_nor),
	DEFINE_ZYNQ_PINCTRL_GRP(smc0_nor_cs1),
	DEFINE_ZYNQ_PINCTRL_GRP(smc0_nor_addr25),
	DEFINE_ZYNQ_PINCTRL_GRP(smc0_nand),
	DEFINE_ZYNQ_PINCTRL_GRP(smc0_nand8),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_1),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_2),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_3),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_4),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_5),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_6),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_7),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_8),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_9),
	DEFINE_ZYNQ_PINCTRL_GRP(can0_10),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_1),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_2),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_3),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_4),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_5),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_6),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_7),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_8),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_9),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_10),
	DEFINE_ZYNQ_PINCTRL_GRP(can1_11),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_1),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_2),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_3),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_4),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_5),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_6),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_7),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_8),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_9),
	DEFINE_ZYNQ_PINCTRL_GRP(uart0_10),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_1),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_2),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_3),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_4),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_5),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_6),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_7),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_8),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_9),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_10),
	DEFINE_ZYNQ_PINCTRL_GRP(uart1_11),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_1),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_2),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_3),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_4),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_5),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_6),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_7),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_8),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_9),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c0_10),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_1),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_2),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_3),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_4),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_5),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_6),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_7),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_8),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_9),
	DEFINE_ZYNQ_PINCTRL_GRP(i2c1_10),
	DEFINE_ZYNQ_PINCTRL_GRP(ttc0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(ttc0_1),
	DEFINE_ZYNQ_PINCTRL_GRP(ttc0_2),
	DEFINE_ZYNQ_PINCTRL_GRP(ttc1_0),
	DEFINE_ZYNQ_PINCTRL_GRP(ttc1_1),
	DEFINE_ZYNQ_PINCTRL_GRP(ttc1_2),
	DEFINE_ZYNQ_PINCTRL_GRP(swdt0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(swdt0_1),
	DEFINE_ZYNQ_PINCTRL_GRP(swdt0_2),
	DEFINE_ZYNQ_PINCTRL_GRP(swdt0_3),
	DEFINE_ZYNQ_PINCTRL_GRP(swdt0_4),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_1),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_2),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_3),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_4),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_5),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_6),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_7),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_8),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_9),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_10),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_11),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_12),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_13),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_14),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_15),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_16),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_17),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_18),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_19),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_20),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_21),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_22),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_23),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_24),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_25),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_26),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_27),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_28),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_29),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_30),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_31),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_32),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_33),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_34),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_35),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_36),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_37),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_38),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_39),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_40),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_41),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_42),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_43),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_44),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_45),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_46),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_47),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_48),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_49),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_50),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_51),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_52),
	DEFINE_ZYNQ_PINCTRL_GRP(gpio0_53),
	DEFINE_ZYNQ_PINCTRL_GRP(usb0_0),
	DEFINE_ZYNQ_PINCTRL_GRP(usb1_0),
पूर्ण;

/* function groups */
अटल स्थिर अक्षर * स्थिर ethernet0_groups[] = अणु"ethernet0_0_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर ethernet1_groups[] = अणु"ethernet1_0_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर usb0_groups[] = अणु"usb0_0_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर usb1_groups[] = अणु"usb1_0_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर mdio0_groups[] = अणु"mdio0_0_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर mdio1_groups[] = अणु"mdio1_0_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi0_groups[] = अणु"qspi0_0_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi1_groups[] = अणु"qspi1_0_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_fbclk_groups[] = अणु"qspi_fbclk_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_cs1_groups[] = अणु"qspi_cs1_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर spi0_groups[] = अणु"spi0_0_grp", "spi0_1_grp",
					   "spi0_2_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर spi1_groups[] = अणु"spi1_0_grp", "spi1_1_grp",
					   "spi1_2_grp", "spi1_3_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर spi0_ss_groups[] = अणु"spi0_0_ss0_grp",
		"spi0_0_ss1_grp", "spi0_0_ss2_grp", "spi0_1_ss0_grp",
		"spi0_1_ss1_grp", "spi0_1_ss2_grp", "spi0_2_ss0_grp",
		"spi0_2_ss1_grp", "spi0_2_ss2_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर spi1_ss_groups[] = अणु"spi1_0_ss0_grp",
		"spi1_0_ss1_grp", "spi1_0_ss2_grp", "spi1_1_ss0_grp",
		"spi1_1_ss1_grp", "spi1_1_ss2_grp", "spi1_2_ss0_grp",
		"spi1_2_ss1_grp", "spi1_2_ss2_grp", "spi1_3_ss0_grp",
		"spi1_3_ss1_grp", "spi1_3_ss2_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio0_groups[] = अणु"sdio0_0_grp", "sdio0_1_grp",
					    "sdio0_2_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio1_groups[] = अणु"sdio1_0_grp", "sdio1_1_grp",
					    "sdio1_2_grp", "sdio1_3_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio0_pc_groups[] = अणु"gpio0_0_grp",
		"gpio0_2_grp", "gpio0_4_grp", "gpio0_6_grp",
		"gpio0_8_grp", "gpio0_10_grp", "gpio0_12_grp",
		"gpio0_14_grp", "gpio0_16_grp", "gpio0_18_grp",
		"gpio0_20_grp", "gpio0_22_grp", "gpio0_24_grp",
		"gpio0_26_grp", "gpio0_28_grp", "gpio0_30_grp",
		"gpio0_32_grp", "gpio0_34_grp", "gpio0_36_grp",
		"gpio0_38_grp", "gpio0_40_grp", "gpio0_42_grp",
		"gpio0_44_grp", "gpio0_46_grp", "gpio0_48_grp",
		"gpio0_50_grp", "gpio0_52_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio1_pc_groups[] = अणु"gpio0_1_grp",
		"gpio0_3_grp", "gpio0_5_grp", "gpio0_7_grp",
		"gpio0_9_grp", "gpio0_11_grp", "gpio0_13_grp",
		"gpio0_15_grp", "gpio0_17_grp", "gpio0_19_grp",
		"gpio0_21_grp", "gpio0_23_grp", "gpio0_25_grp",
		"gpio0_27_grp", "gpio0_29_grp", "gpio0_31_grp",
		"gpio0_33_grp", "gpio0_35_grp", "gpio0_37_grp",
		"gpio0_39_grp", "gpio0_41_grp", "gpio0_43_grp",
		"gpio0_45_grp", "gpio0_47_grp", "gpio0_49_grp",
		"gpio0_51_grp", "gpio0_53_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio0_cd_groups[] = अणु"gpio0_0_grp",
		"gpio0_2_grp", "gpio0_4_grp", "gpio0_6_grp",
		"gpio0_10_grp", "gpio0_12_grp",
		"gpio0_14_grp", "gpio0_16_grp", "gpio0_18_grp",
		"gpio0_20_grp", "gpio0_22_grp", "gpio0_24_grp",
		"gpio0_26_grp", "gpio0_28_grp", "gpio0_30_grp",
		"gpio0_32_grp", "gpio0_34_grp", "gpio0_36_grp",
		"gpio0_38_grp", "gpio0_40_grp", "gpio0_42_grp",
		"gpio0_44_grp", "gpio0_46_grp", "gpio0_48_grp",
		"gpio0_50_grp", "gpio0_52_grp", "gpio0_1_grp",
		"gpio0_3_grp", "gpio0_5_grp",
		"gpio0_9_grp", "gpio0_11_grp", "gpio0_13_grp",
		"gpio0_15_grp", "gpio0_17_grp", "gpio0_19_grp",
		"gpio0_21_grp", "gpio0_23_grp", "gpio0_25_grp",
		"gpio0_27_grp", "gpio0_29_grp", "gpio0_31_grp",
		"gpio0_33_grp", "gpio0_35_grp", "gpio0_37_grp",
		"gpio0_39_grp", "gpio0_41_grp", "gpio0_43_grp",
		"gpio0_45_grp", "gpio0_47_grp", "gpio0_49_grp",
		"gpio0_51_grp", "gpio0_53_grp", "sdio0_emio_cd_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio0_wp_groups[] = अणु"gpio0_0_grp",
		"gpio0_2_grp", "gpio0_4_grp", "gpio0_6_grp",
		"gpio0_10_grp", "gpio0_12_grp",
		"gpio0_14_grp", "gpio0_16_grp", "gpio0_18_grp",
		"gpio0_20_grp", "gpio0_22_grp", "gpio0_24_grp",
		"gpio0_26_grp", "gpio0_28_grp", "gpio0_30_grp",
		"gpio0_32_grp", "gpio0_34_grp", "gpio0_36_grp",
		"gpio0_38_grp", "gpio0_40_grp", "gpio0_42_grp",
		"gpio0_44_grp", "gpio0_46_grp", "gpio0_48_grp",
		"gpio0_50_grp", "gpio0_52_grp", "gpio0_1_grp",
		"gpio0_3_grp", "gpio0_5_grp",
		"gpio0_9_grp", "gpio0_11_grp", "gpio0_13_grp",
		"gpio0_15_grp", "gpio0_17_grp", "gpio0_19_grp",
		"gpio0_21_grp", "gpio0_23_grp", "gpio0_25_grp",
		"gpio0_27_grp", "gpio0_29_grp", "gpio0_31_grp",
		"gpio0_33_grp", "gpio0_35_grp", "gpio0_37_grp",
		"gpio0_39_grp", "gpio0_41_grp", "gpio0_43_grp",
		"gpio0_45_grp", "gpio0_47_grp", "gpio0_49_grp",
		"gpio0_51_grp", "gpio0_53_grp", "sdio0_emio_wp_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio1_cd_groups[] = अणु"gpio0_0_grp",
		"gpio0_2_grp", "gpio0_4_grp", "gpio0_6_grp",
		"gpio0_10_grp", "gpio0_12_grp",
		"gpio0_14_grp", "gpio0_16_grp", "gpio0_18_grp",
		"gpio0_20_grp", "gpio0_22_grp", "gpio0_24_grp",
		"gpio0_26_grp", "gpio0_28_grp", "gpio0_30_grp",
		"gpio0_32_grp", "gpio0_34_grp", "gpio0_36_grp",
		"gpio0_38_grp", "gpio0_40_grp", "gpio0_42_grp",
		"gpio0_44_grp", "gpio0_46_grp", "gpio0_48_grp",
		"gpio0_50_grp", "gpio0_52_grp", "gpio0_1_grp",
		"gpio0_3_grp", "gpio0_5_grp",
		"gpio0_9_grp", "gpio0_11_grp", "gpio0_13_grp",
		"gpio0_15_grp", "gpio0_17_grp", "gpio0_19_grp",
		"gpio0_21_grp", "gpio0_23_grp", "gpio0_25_grp",
		"gpio0_27_grp", "gpio0_29_grp", "gpio0_31_grp",
		"gpio0_33_grp", "gpio0_35_grp", "gpio0_37_grp",
		"gpio0_39_grp", "gpio0_41_grp", "gpio0_43_grp",
		"gpio0_45_grp", "gpio0_47_grp", "gpio0_49_grp",
		"gpio0_51_grp", "gpio0_53_grp", "sdio1_emio_cd_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio1_wp_groups[] = अणु"gpio0_0_grp",
		"gpio0_2_grp", "gpio0_4_grp", "gpio0_6_grp",
		"gpio0_10_grp", "gpio0_12_grp",
		"gpio0_14_grp", "gpio0_16_grp", "gpio0_18_grp",
		"gpio0_20_grp", "gpio0_22_grp", "gpio0_24_grp",
		"gpio0_26_grp", "gpio0_28_grp", "gpio0_30_grp",
		"gpio0_32_grp", "gpio0_34_grp", "gpio0_36_grp",
		"gpio0_38_grp", "gpio0_40_grp", "gpio0_42_grp",
		"gpio0_44_grp", "gpio0_46_grp", "gpio0_48_grp",
		"gpio0_50_grp", "gpio0_52_grp", "gpio0_1_grp",
		"gpio0_3_grp", "gpio0_5_grp",
		"gpio0_9_grp", "gpio0_11_grp", "gpio0_13_grp",
		"gpio0_15_grp", "gpio0_17_grp", "gpio0_19_grp",
		"gpio0_21_grp", "gpio0_23_grp", "gpio0_25_grp",
		"gpio0_27_grp", "gpio0_29_grp", "gpio0_31_grp",
		"gpio0_33_grp", "gpio0_35_grp", "gpio0_37_grp",
		"gpio0_39_grp", "gpio0_41_grp", "gpio0_43_grp",
		"gpio0_45_grp", "gpio0_47_grp", "gpio0_49_grp",
		"gpio0_51_grp", "gpio0_53_grp", "sdio1_emio_wp_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर smc0_nor_groups[] = अणु"smc0_nor_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर smc0_nor_cs1_groups[] = अणु"smc0_nor_cs1_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर smc0_nor_addr25_groups[] = अणु"smc0_nor_addr25_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर smc0_nand_groups[] = अणु"smc0_nand_grp",
		"smc0_nand8_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर can0_groups[] = अणु"can0_0_grp", "can0_1_grp",
		"can0_2_grp", "can0_3_grp", "can0_4_grp", "can0_5_grp",
		"can0_6_grp", "can0_7_grp", "can0_8_grp", "can0_9_grp",
		"can0_10_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर can1_groups[] = अणु"can1_0_grp", "can1_1_grp",
		"can1_2_grp", "can1_3_grp", "can1_4_grp", "can1_5_grp",
		"can1_6_grp", "can1_7_grp", "can1_8_grp", "can1_9_grp",
		"can1_10_grp", "can1_11_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर uart0_groups[] = अणु"uart0_0_grp", "uart0_1_grp",
		"uart0_2_grp", "uart0_3_grp", "uart0_4_grp", "uart0_5_grp",
		"uart0_6_grp", "uart0_7_grp", "uart0_8_grp", "uart0_9_grp",
		"uart0_10_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर uart1_groups[] = अणु"uart1_0_grp", "uart1_1_grp",
		"uart1_2_grp", "uart1_3_grp", "uart1_4_grp", "uart1_5_grp",
		"uart1_6_grp", "uart1_7_grp", "uart1_8_grp", "uart1_9_grp",
		"uart1_10_grp", "uart1_11_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c0_groups[] = अणु"i2c0_0_grp", "i2c0_1_grp",
		"i2c0_2_grp", "i2c0_3_grp", "i2c0_4_grp", "i2c0_5_grp",
		"i2c0_6_grp", "i2c0_7_grp", "i2c0_8_grp", "i2c0_9_grp",
		"i2c0_10_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c1_groups[] = अणु"i2c1_0_grp", "i2c1_1_grp",
		"i2c1_2_grp", "i2c1_3_grp", "i2c1_4_grp", "i2c1_5_grp",
		"i2c1_6_grp", "i2c1_7_grp", "i2c1_8_grp", "i2c1_9_grp",
		"i2c1_10_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर ttc0_groups[] = अणु"ttc0_0_grp", "ttc0_1_grp",
					   "ttc0_2_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर ttc1_groups[] = अणु"ttc1_0_grp", "ttc1_1_grp",
					   "ttc1_2_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर swdt0_groups[] = अणु"swdt0_0_grp", "swdt0_1_grp",
		"swdt0_2_grp", "swdt0_3_grp", "swdt0_4_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio0_groups[] = अणु"gpio0_0_grp",
		"gpio0_2_grp", "gpio0_4_grp", "gpio0_6_grp",
		"gpio0_8_grp", "gpio0_10_grp", "gpio0_12_grp",
		"gpio0_14_grp", "gpio0_16_grp", "gpio0_18_grp",
		"gpio0_20_grp", "gpio0_22_grp", "gpio0_24_grp",
		"gpio0_26_grp", "gpio0_28_grp", "gpio0_30_grp",
		"gpio0_32_grp", "gpio0_34_grp", "gpio0_36_grp",
		"gpio0_38_grp", "gpio0_40_grp", "gpio0_42_grp",
		"gpio0_44_grp", "gpio0_46_grp", "gpio0_48_grp",
		"gpio0_50_grp", "gpio0_52_grp", "gpio0_1_grp",
		"gpio0_3_grp", "gpio0_5_grp", "gpio0_7_grp",
		"gpio0_9_grp", "gpio0_11_grp", "gpio0_13_grp",
		"gpio0_15_grp", "gpio0_17_grp", "gpio0_19_grp",
		"gpio0_21_grp", "gpio0_23_grp", "gpio0_25_grp",
		"gpio0_27_grp", "gpio0_29_grp", "gpio0_31_grp",
		"gpio0_33_grp", "gpio0_35_grp", "gpio0_37_grp",
		"gpio0_39_grp", "gpio0_41_grp", "gpio0_43_grp",
		"gpio0_45_grp", "gpio0_47_grp", "gpio0_49_grp",
		"gpio0_51_grp", "gpio0_53_grp"पूर्ण;

#घोषणा DEFINE_ZYNQ_PINMUX_FUNCTION(fname, mval)	\
	[ZYNQ_PMUX_##fname] = अणु				\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
		.mux_val = mval,			\
	पूर्ण

#घोषणा DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(fname, mval, offset, mask, shअगरt)\
	[ZYNQ_PMUX_##fname] = अणु				\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
		.mux_val = mval,			\
		.mux = offset,				\
		.mux_mask = mask,			\
		.mux_shअगरt = shअगरt,			\
	पूर्ण

#घोषणा ZYNQ_SDIO_WP_SHIFT	0
#घोषणा ZYNQ_SDIO_WP_MASK	(0x3f << ZYNQ_SDIO_WP_SHIFT)
#घोषणा ZYNQ_SDIO_CD_SHIFT	16
#घोषणा ZYNQ_SDIO_CD_MASK	(0x3f << ZYNQ_SDIO_CD_SHIFT)

अटल स्थिर काष्ठा zynq_pinmux_function zynq_pmux_functions[] = अणु
	DEFINE_ZYNQ_PINMUX_FUNCTION(ethernet0, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(ethernet1, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(usb0, 2),
	DEFINE_ZYNQ_PINMUX_FUNCTION(usb1, 2),
	DEFINE_ZYNQ_PINMUX_FUNCTION(mdio0, 0x40),
	DEFINE_ZYNQ_PINMUX_FUNCTION(mdio1, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(qspi0, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(qspi1, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(qspi_fbclk, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(qspi_cs1, 1),
	DEFINE_ZYNQ_PINMUX_FUNCTION(spi0, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(spi1, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(spi0_ss, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(spi1_ss, 0x50),
	DEFINE_ZYNQ_PINMUX_FUNCTION(sdio0, 0x40),
	DEFINE_ZYNQ_PINMUX_FUNCTION(sdio0_pc, 0xc),
	DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(sdio0_wp, 0, 0x130, ZYNQ_SDIO_WP_MASK,
					ZYNQ_SDIO_WP_SHIFT),
	DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(sdio0_cd, 0, 0x130, ZYNQ_SDIO_CD_MASK,
					ZYNQ_SDIO_CD_SHIFT),
	DEFINE_ZYNQ_PINMUX_FUNCTION(sdio1, 0x40),
	DEFINE_ZYNQ_PINMUX_FUNCTION(sdio1_pc, 0xc),
	DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(sdio1_wp, 0, 0x134, ZYNQ_SDIO_WP_MASK,
					ZYNQ_SDIO_WP_SHIFT),
	DEFINE_ZYNQ_PINMUX_FUNCTION_MUX(sdio1_cd, 0, 0x134, ZYNQ_SDIO_CD_MASK,
					ZYNQ_SDIO_CD_SHIFT),
	DEFINE_ZYNQ_PINMUX_FUNCTION(smc0_nor, 4),
	DEFINE_ZYNQ_PINMUX_FUNCTION(smc0_nor_cs1, 8),
	DEFINE_ZYNQ_PINMUX_FUNCTION(smc0_nor_addr25, 4),
	DEFINE_ZYNQ_PINMUX_FUNCTION(smc0_nand, 8),
	DEFINE_ZYNQ_PINMUX_FUNCTION(can0, 0x10),
	DEFINE_ZYNQ_PINMUX_FUNCTION(can1, 0x10),
	DEFINE_ZYNQ_PINMUX_FUNCTION(uart0, 0x70),
	DEFINE_ZYNQ_PINMUX_FUNCTION(uart1, 0x70),
	DEFINE_ZYNQ_PINMUX_FUNCTION(i2c0, 0x20),
	DEFINE_ZYNQ_PINMUX_FUNCTION(i2c1, 0x20),
	DEFINE_ZYNQ_PINMUX_FUNCTION(ttc0, 0x60),
	DEFINE_ZYNQ_PINMUX_FUNCTION(ttc1, 0x60),
	DEFINE_ZYNQ_PINMUX_FUNCTION(swdt0, 0x30),
	DEFINE_ZYNQ_PINMUX_FUNCTION(gpio0, 0),
पूर्ण;


/* pinctrl */
अटल पूर्णांक zynq_pctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->ngroups;
पूर्ण

अटल स्थिर अक्षर *zynq_pctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित पूर्णांक selector)
अणु
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->groups[selector].name;
पूर्ण

अटल पूर्णांक zynq_pctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक selector,
				     स्थिर अचिन्हित पूर्णांक **pins,
				     अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = pctrl->groups[selector].pins;
	*num_pins = pctrl->groups[selector].npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops zynq_pctrl_ops = अणु
	.get_groups_count = zynq_pctrl_get_groups_count,
	.get_group_name = zynq_pctrl_get_group_name,
	.get_group_pins = zynq_pctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

/* pinmux */
अटल पूर्णांक zynq_pmux_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->nfuncs;
पूर्ण

अटल स्थिर अक्षर *zynq_pmux_get_function_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित पूर्णांक selector)
अणु
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->funcs[selector].name;
पूर्ण

अटल पूर्णांक zynq_pmux_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित पूर्णांक selector,
					 स्थिर अक्षर * स्थिर **groups,
					 अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctrl->funcs[selector].groups;
	*num_groups = pctrl->funcs[selector].ngroups;
	वापस 0;
पूर्ण

अटल पूर्णांक zynq_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित पूर्णांक function,
			       अचिन्हित पूर्णांक  group)
अणु
	पूर्णांक i, ret;
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा zynq_pctrl_group *pgrp = &pctrl->groups[group];
	स्थिर काष्ठा zynq_pinmux_function *func = &pctrl->funcs[function];

	/*
	 * SD WP & CD are special. They have dedicated रेजिस्टरs
	 * to mux them in
	 */
	अगर (function == ZYNQ_PMUX_sdio0_cd || function == ZYNQ_PMUX_sdio0_wp ||
			function == ZYNQ_PMUX_sdio1_cd ||
			function == ZYNQ_PMUX_sdio1_wp) अणु
		u32 reg;

		ret = regmap_पढ़ो(pctrl->syscon,
				  pctrl->pctrl_offset + func->mux, &reg);
		अगर (ret)
			वापस ret;

		reg &= ~func->mux_mask;
		reg |= pgrp->pins[0] << func->mux_shअगरt;
		ret = regmap_ग_लिखो(pctrl->syscon,
				   pctrl->pctrl_offset + func->mux, reg);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < pgrp->npins; i++) अणु
			अचिन्हित पूर्णांक pin = pgrp->pins[i];
			u32 reg, addr = pctrl->pctrl_offset + (4 * pin);

			ret = regmap_पढ़ो(pctrl->syscon, addr, &reg);
			अगर (ret)
				वापस ret;

			reg &= ~ZYNQ_PINMUX_MUX_MASK;
			reg |= func->mux_val << ZYNQ_PINMUX_MUX_SHIFT;
			ret = regmap_ग_लिखो(pctrl->syscon, addr, reg);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops zynq_pinmux_ops = अणु
	.get_functions_count = zynq_pmux_get_functions_count,
	.get_function_name = zynq_pmux_get_function_name,
	.get_function_groups = zynq_pmux_get_function_groups,
	.set_mux = zynq_pinmux_set_mux,
पूर्ण;

/* pinconfig */
#घोषणा ZYNQ_PINCONF_TRISTATE		BIT(0)
#घोषणा ZYNQ_PINCONF_SPEED		BIT(8)
#घोषणा ZYNQ_PINCONF_PULLUP		BIT(12)
#घोषणा ZYNQ_PINCONF_DISABLE_RECVR	BIT(13)

#घोषणा ZYNQ_PINCONF_IOTYPE_SHIFT	9
#घोषणा ZYNQ_PINCONF_IOTYPE_MASK	(7 << ZYNQ_PINCONF_IOTYPE_SHIFT)

क्रमागत zynq_io_standards अणु
	zynq_iostd_min,
	zynq_iostd_lvcmos18,
	zynq_iostd_lvcmos25,
	zynq_iostd_lvcmos33,
	zynq_iostd_hstl,
	zynq_iostd_max
पूर्ण;

/*
 * PIN_CONFIG_IOSTANDARD: अगर the pin can select an IO standard, the argument to
 *	this parameter (on a custom क्रमmat) tells the driver which alternative
 *	IO standard to use.
 */
#घोषणा PIN_CONFIG_IOSTANDARD		(PIN_CONFIG_END + 1)

अटल स्थिर काष्ठा pinconf_generic_params zynq_dt_params[] = अणु
	अणु"io-standard", PIN_CONFIG_IOSTANDARD, zynq_iostd_lvcmos18पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item zynq_conf_items[ARRAY_SIZE(zynq_dt_params)]
	= अणु PCONFDUMP(PIN_CONFIG_IOSTANDARD, "IO-standard", शून्य, true),
पूर्ण;
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक zynq_pinconf_iostd_get(u32 reg)
अणु
	वापस (reg & ZYNQ_PINCONF_IOTYPE_MASK) >> ZYNQ_PINCONF_IOTYPE_SHIFT;
पूर्ण

अटल पूर्णांक zynq_pinconf_cfg_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *config)
अणु
	u32 reg;
	पूर्णांक ret;
	अचिन्हित पूर्णांक arg = 0;
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	अगर (pin >= ZYNQ_NUM_MIOS)
		वापस -ENOTSUPP;

	ret = regmap_पढ़ो(pctrl->syscon, pctrl->pctrl_offset + (4 * pin), &reg);
	अगर (ret)
		वापस -EIO;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (!(reg & ZYNQ_PINCONF_PULLUP))
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		अगर (!(reg & ZYNQ_PINCONF_TRISTATE))
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (reg & ZYNQ_PINCONF_PULLUP || reg & ZYNQ_PINCONF_TRISTATE)
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		arg = !!(reg & ZYNQ_PINCONF_SPEED);
		अवरोध;
	हाल PIN_CONFIG_MODE_LOW_POWER:
	अणु
		क्रमागत zynq_io_standards iostd = zynq_pinconf_iostd_get(reg);

		अगर (iostd != zynq_iostd_hstl)
			वापस -EINVAL;
		अगर (!(reg & ZYNQ_PINCONF_DISABLE_RECVR))
			वापस -EINVAL;
		arg = !!(reg & ZYNQ_PINCONF_DISABLE_RECVR);
		अवरोध;
	पूर्ण
	हाल PIN_CONFIG_IOSTANDARD:
		arg = zynq_pinconf_iostd_get(reg);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक zynq_pinconf_cfg_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *configs,
				अचिन्हित पूर्णांक num_configs)
अणु
	पूर्णांक i, ret;
	u32 reg;
	u32 pullup = 0;
	u32 tristate = 0;
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	अगर (pin >= ZYNQ_NUM_MIOS)
		वापस -ENOTSUPP;

	ret = regmap_पढ़ो(pctrl->syscon, pctrl->pctrl_offset + (4 * pin), &reg);
	अगर (ret)
		वापस -EIO;

	क्रम (i = 0; i < num_configs; i++) अणु
		अचिन्हित पूर्णांक param = pinconf_to_config_param(configs[i]);
		अचिन्हित पूर्णांक arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			pullup = ZYNQ_PINCONF_PULLUP;
			अवरोध;
		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			tristate = ZYNQ_PINCONF_TRISTATE;
			अवरोध;
		हाल PIN_CONFIG_BIAS_DISABLE:
			reg &= ~(ZYNQ_PINCONF_PULLUP | ZYNQ_PINCONF_TRISTATE);
			अवरोध;
		हाल PIN_CONFIG_SLEW_RATE:
			अगर (arg)
				reg |= ZYNQ_PINCONF_SPEED;
			अन्यथा
				reg &= ~ZYNQ_PINCONF_SPEED;

			अवरोध;
		हाल PIN_CONFIG_IOSTANDARD:
			अगर (arg <= zynq_iostd_min || arg >= zynq_iostd_max) अणु
				dev_warn(pctldev->dev,
					 "unsupported IO standard '%u'\n",
					 param);
				अवरोध;
			पूर्ण
			reg &= ~ZYNQ_PINCONF_IOTYPE_MASK;
			reg |= arg << ZYNQ_PINCONF_IOTYPE_SHIFT;
			अवरोध;
		हाल PIN_CONFIG_MODE_LOW_POWER:
			अगर (arg)
				reg |= ZYNQ_PINCONF_DISABLE_RECVR;
			अन्यथा
				reg &= ~ZYNQ_PINCONF_DISABLE_RECVR;

			अवरोध;
		शेष:
			dev_warn(pctldev->dev,
				 "unsupported configuration parameter '%u'\n",
				 param);
			जारी;
		पूर्ण
	पूर्ण

	अगर (tristate || pullup) अणु
		reg &= ~(ZYNQ_PINCONF_PULLUP | ZYNQ_PINCONF_TRISTATE);
		reg |= tristate | pullup;
	पूर्ण

	ret = regmap_ग_लिखो(pctrl->syscon, pctrl->pctrl_offset + (4 * pin), reg);
	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक zynq_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector,
				  अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक  num_configs)
अणु
	पूर्णांक i, ret;
	काष्ठा zynq_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा zynq_pctrl_group *pgrp = &pctrl->groups[selector];

	क्रम (i = 0; i < pgrp->npins; i++) अणु
		ret = zynq_pinconf_cfg_set(pctldev, pgrp->pins[i], configs,
					   num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops zynq_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = zynq_pinconf_cfg_get,
	.pin_config_set = zynq_pinconf_cfg_set,
	.pin_config_group_set = zynq_pinconf_group_set,
पूर्ण;

अटल काष्ठा pinctrl_desc zynq_desc = अणु
	.name = "zynq_pinctrl",
	.pins = zynq_pins,
	.npins = ARRAY_SIZE(zynq_pins),
	.pctlops = &zynq_pctrl_ops,
	.pmxops = &zynq_pinmux_ops,
	.confops = &zynq_pinconf_ops,
	.num_custom_params = ARRAY_SIZE(zynq_dt_params),
	.custom_params = zynq_dt_params,
#अगर_घोषित CONFIG_DEBUG_FS
	.custom_conf_items = zynq_conf_items,
#पूर्ण_अगर
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक zynq_pinctrl_probe(काष्ठा platक्रमm_device *pdev)

अणु
	काष्ठा resource *res;
	काष्ठा zynq_pinctrl *pctrl;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->syscon = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							"syscon");
	अगर (IS_ERR(pctrl->syscon)) अणु
		dev_err(&pdev->dev, "unable to get syscon\n");
		वापस PTR_ERR(pctrl->syscon);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "missing IO resource\n");
		वापस -ENODEV;
	पूर्ण
	pctrl->pctrl_offset = res->start;

	pctrl->groups = zynq_pctrl_groups;
	pctrl->ngroups = ARRAY_SIZE(zynq_pctrl_groups);
	pctrl->funcs = zynq_pmux_functions;
	pctrl->nfuncs = ARRAY_SIZE(zynq_pmux_functions);

	pctrl->pctrl = devm_pinctrl_रेजिस्टर(&pdev->dev, &zynq_desc, pctrl);
	अगर (IS_ERR(pctrl->pctrl))
		वापस PTR_ERR(pctrl->pctrl);

	platक्रमm_set_drvdata(pdev, pctrl);

	dev_info(&pdev->dev, "zynq pinctrl initialized\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynq_pinctrl_of_match[] = अणु
	अणु .compatible = "xlnx,pinctrl-zynq" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver zynq_pinctrl_driver = अणु
	.driver = अणु
		.name = "zynq-pinctrl",
		.of_match_table = zynq_pinctrl_of_match,
	पूर्ण,
	.probe = zynq_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init zynq_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&zynq_pinctrl_driver);
पूर्ण
arch_initcall(zynq_pinctrl_init);
