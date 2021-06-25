<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम BCM63268 GPIO unit (pinctrl + GPIO)
 *
 * Copyright (C) 2021 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 * Copyright (C) 2016 Jonas Gorski <jonas.gorski@gmail.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "../pinctrl-utils.h"

#समावेश "pinctrl-bcm63xx.h"

#घोषणा BCM63268_NUM_GPIOS		52
#घोषणा BCM63268_NUM_LEDS		24

#घोषणा BCM63268_LED_REG		0x10
#घोषणा BCM63268_MODE_REG		0x18
#घोषणा BCM63268_CTRL_REG		0x1c
#घोषणा BCM63268_BASEMODE_REG		0x38
#घोषणा  BCM63268_BASEMODE_न_अंकD		BIT(2) /* GPIOs 2-7, 24-31 */
#घोषणा  BCM63268_BASEMODE_GPIO35	BIT(4) /* GPIO 35 */
#घोषणा  BCM63268_BASEMODE_DECTPD	BIT(5) /* GPIOs 8/9 */
#घोषणा  BCM63268_BASEMODE_VDSL_PHY_0	BIT(6) /* GPIOs 10/11 */
#घोषणा  BCM63268_BASEMODE_VDSL_PHY_1	BIT(7) /* GPIOs 12/13 */
#घोषणा  BCM63268_BASEMODE_VDSL_PHY_2	BIT(8) /* GPIOs 24/25 */
#घोषणा  BCM63268_BASEMODE_VDSL_PHY_3	BIT(9) /* GPIOs 26/27 */

क्रमागत bcm63268_pinctrl_reg अणु
	BCM63268_LEDCTRL,
	BCM63268_MODE,
	BCM63268_CTRL,
	BCM63268_BASEMODE,
पूर्ण;

काष्ठा bcm63268_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित * स्थिर pins;
	स्थिर अचिन्हित num_pins;
पूर्ण;

काष्ठा bcm63268_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित num_groups;

	क्रमागत bcm63268_pinctrl_reg reg;
	uपूर्णांक32_t mask;
पूर्ण;

#घोषणा BCM63268_PIN(a, b, basemode)			\
	अणु						\
		.number = a,				\
		.name = b,				\
		.drv_data = (व्योम *)(basemode)		\
	पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc bcm63268_pins[] = अणु
	PINCTRL_PIN(0, "gpio0"),
	PINCTRL_PIN(1, "gpio1"),
	BCM63268_PIN(2, "gpio2", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(3, "gpio3", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(4, "gpio4", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(5, "gpio5", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(6, "gpio6", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(7, "gpio7", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(8, "gpio8", BCM63268_BASEMODE_DECTPD),
	BCM63268_PIN(9, "gpio9", BCM63268_BASEMODE_DECTPD),
	BCM63268_PIN(10, "gpio10", BCM63268_BASEMODE_VDSL_PHY_0),
	BCM63268_PIN(11, "gpio11", BCM63268_BASEMODE_VDSL_PHY_0),
	BCM63268_PIN(12, "gpio12", BCM63268_BASEMODE_VDSL_PHY_1),
	BCM63268_PIN(13, "gpio13", BCM63268_BASEMODE_VDSL_PHY_1),
	PINCTRL_PIN(14, "gpio14"),
	PINCTRL_PIN(15, "gpio15"),
	PINCTRL_PIN(16, "gpio16"),
	PINCTRL_PIN(17, "gpio17"),
	PINCTRL_PIN(18, "gpio18"),
	PINCTRL_PIN(19, "gpio19"),
	PINCTRL_PIN(20, "gpio20"),
	PINCTRL_PIN(21, "gpio21"),
	PINCTRL_PIN(22, "gpio22"),
	PINCTRL_PIN(23, "gpio23"),
	BCM63268_PIN(24, "gpio24",
		     BCM63268_BASEMODE_न_अंकD | BCM63268_BASEMODE_VDSL_PHY_2),
	BCM63268_PIN(25, "gpio25",
		     BCM63268_BASEMODE_न_अंकD | BCM63268_BASEMODE_VDSL_PHY_2),
	BCM63268_PIN(26, "gpio26",
		     BCM63268_BASEMODE_न_अंकD | BCM63268_BASEMODE_VDSL_PHY_3),
	BCM63268_PIN(27, "gpio27",
		     BCM63268_BASEMODE_न_अंकD | BCM63268_BASEMODE_VDSL_PHY_3),
	BCM63268_PIN(28, "gpio28", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(29, "gpio29", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(30, "gpio30", BCM63268_BASEMODE_न_अंकD),
	BCM63268_PIN(31, "gpio31", BCM63268_BASEMODE_न_अंकD),
	PINCTRL_PIN(32, "gpio32"),
	PINCTRL_PIN(33, "gpio33"),
	PINCTRL_PIN(34, "gpio34"),
	PINCTRL_PIN(35, "gpio35"),
	PINCTRL_PIN(36, "gpio36"),
	PINCTRL_PIN(37, "gpio37"),
	PINCTRL_PIN(38, "gpio38"),
	PINCTRL_PIN(39, "gpio39"),
	PINCTRL_PIN(40, "gpio40"),
	PINCTRL_PIN(41, "gpio41"),
	PINCTRL_PIN(42, "gpio42"),
	PINCTRL_PIN(43, "gpio43"),
	PINCTRL_PIN(44, "gpio44"),
	PINCTRL_PIN(45, "gpio45"),
	PINCTRL_PIN(46, "gpio46"),
	PINCTRL_PIN(47, "gpio47"),
	PINCTRL_PIN(48, "gpio48"),
	PINCTRL_PIN(49, "gpio49"),
	PINCTRL_PIN(50, "gpio50"),
	PINCTRL_PIN(51, "gpio51"),
पूर्ण;

अटल अचिन्हित gpio0_pins[] = अणु 0 पूर्ण;
अटल अचिन्हित gpio1_pins[] = अणु 1 पूर्ण;
अटल अचिन्हित gpio2_pins[] = अणु 2 पूर्ण;
अटल अचिन्हित gpio3_pins[] = अणु 3 पूर्ण;
अटल अचिन्हित gpio4_pins[] = अणु 4 पूर्ण;
अटल अचिन्हित gpio5_pins[] = अणु 5 पूर्ण;
अटल अचिन्हित gpio6_pins[] = अणु 6 पूर्ण;
अटल अचिन्हित gpio7_pins[] = अणु 7 पूर्ण;
अटल अचिन्हित gpio8_pins[] = अणु 8 पूर्ण;
अटल अचिन्हित gpio9_pins[] = अणु 9 पूर्ण;
अटल अचिन्हित gpio10_pins[] = अणु 10 पूर्ण;
अटल अचिन्हित gpio11_pins[] = अणु 11 पूर्ण;
अटल अचिन्हित gpio12_pins[] = अणु 12 पूर्ण;
अटल अचिन्हित gpio13_pins[] = अणु 13 पूर्ण;
अटल अचिन्हित gpio14_pins[] = अणु 14 पूर्ण;
अटल अचिन्हित gpio15_pins[] = अणु 15 पूर्ण;
अटल अचिन्हित gpio16_pins[] = अणु 16 पूर्ण;
अटल अचिन्हित gpio17_pins[] = अणु 17 पूर्ण;
अटल अचिन्हित gpio18_pins[] = अणु 18 पूर्ण;
अटल अचिन्हित gpio19_pins[] = अणु 19 पूर्ण;
अटल अचिन्हित gpio20_pins[] = अणु 20 पूर्ण;
अटल अचिन्हित gpio21_pins[] = अणु 21 पूर्ण;
अटल अचिन्हित gpio22_pins[] = अणु 22 पूर्ण;
अटल अचिन्हित gpio23_pins[] = अणु 23 पूर्ण;
अटल अचिन्हित gpio24_pins[] = अणु 24 पूर्ण;
अटल अचिन्हित gpio25_pins[] = अणु 25 पूर्ण;
अटल अचिन्हित gpio26_pins[] = अणु 26 पूर्ण;
अटल अचिन्हित gpio27_pins[] = अणु 27 पूर्ण;
अटल अचिन्हित gpio28_pins[] = अणु 28 पूर्ण;
अटल अचिन्हित gpio29_pins[] = अणु 29 पूर्ण;
अटल अचिन्हित gpio30_pins[] = अणु 30 पूर्ण;
अटल अचिन्हित gpio31_pins[] = अणु 31 पूर्ण;
अटल अचिन्हित gpio32_pins[] = अणु 32 पूर्ण;
अटल अचिन्हित gpio33_pins[] = अणु 33 पूर्ण;
अटल अचिन्हित gpio34_pins[] = अणु 34 पूर्ण;
अटल अचिन्हित gpio35_pins[] = अणु 35 पूर्ण;
अटल अचिन्हित gpio36_pins[] = अणु 36 पूर्ण;
अटल अचिन्हित gpio37_pins[] = अणु 37 पूर्ण;
अटल अचिन्हित gpio38_pins[] = अणु 38 पूर्ण;
अटल अचिन्हित gpio39_pins[] = अणु 39 पूर्ण;
अटल अचिन्हित gpio40_pins[] = अणु 40 पूर्ण;
अटल अचिन्हित gpio41_pins[] = अणु 41 पूर्ण;
अटल अचिन्हित gpio42_pins[] = अणु 42 पूर्ण;
अटल अचिन्हित gpio43_pins[] = अणु 43 पूर्ण;
अटल अचिन्हित gpio44_pins[] = अणु 44 पूर्ण;
अटल अचिन्हित gpio45_pins[] = अणु 45 पूर्ण;
अटल अचिन्हित gpio46_pins[] = अणु 46 पूर्ण;
अटल अचिन्हित gpio47_pins[] = अणु 47 पूर्ण;
अटल अचिन्हित gpio48_pins[] = अणु 48 पूर्ण;
अटल अचिन्हित gpio49_pins[] = अणु 49 पूर्ण;
अटल अचिन्हित gpio50_pins[] = अणु 50 पूर्ण;
अटल अचिन्हित gpio51_pins[] = अणु 51 पूर्ण;

अटल अचिन्हित nand_grp_pins[] = अणु
	2, 3, 4, 5, 6, 7, 24,
	25, 26, 27, 28, 29, 30, 31,
पूर्ण;

अटल अचिन्हित dectpd_grp_pins[] = अणु 8, 9 पूर्ण;
अटल अचिन्हित vdsl_phy0_grp_pins[] = अणु 10, 11 पूर्ण;
अटल अचिन्हित vdsl_phy1_grp_pins[] = अणु 12, 13 पूर्ण;
अटल अचिन्हित vdsl_phy2_grp_pins[] = अणु 24, 25 पूर्ण;
अटल अचिन्हित vdsl_phy3_grp_pins[] = अणु 26, 27 पूर्ण;

#घोषणा BCM63268_GROUP(n)					\
	अणु							\
		.name = #n,					\
		.pins = n##_pins,				\
		.num_pins = ARRAY_SIZE(n##_pins),		\
	पूर्ण

अटल काष्ठा bcm63268_pingroup bcm63268_groups[] = अणु
	BCM63268_GROUP(gpio0),
	BCM63268_GROUP(gpio1),
	BCM63268_GROUP(gpio2),
	BCM63268_GROUP(gpio3),
	BCM63268_GROUP(gpio4),
	BCM63268_GROUP(gpio5),
	BCM63268_GROUP(gpio6),
	BCM63268_GROUP(gpio7),
	BCM63268_GROUP(gpio8),
	BCM63268_GROUP(gpio9),
	BCM63268_GROUP(gpio10),
	BCM63268_GROUP(gpio11),
	BCM63268_GROUP(gpio12),
	BCM63268_GROUP(gpio13),
	BCM63268_GROUP(gpio14),
	BCM63268_GROUP(gpio15),
	BCM63268_GROUP(gpio16),
	BCM63268_GROUP(gpio17),
	BCM63268_GROUP(gpio18),
	BCM63268_GROUP(gpio19),
	BCM63268_GROUP(gpio20),
	BCM63268_GROUP(gpio21),
	BCM63268_GROUP(gpio22),
	BCM63268_GROUP(gpio23),
	BCM63268_GROUP(gpio24),
	BCM63268_GROUP(gpio25),
	BCM63268_GROUP(gpio26),
	BCM63268_GROUP(gpio27),
	BCM63268_GROUP(gpio28),
	BCM63268_GROUP(gpio29),
	BCM63268_GROUP(gpio30),
	BCM63268_GROUP(gpio31),
	BCM63268_GROUP(gpio32),
	BCM63268_GROUP(gpio33),
	BCM63268_GROUP(gpio34),
	BCM63268_GROUP(gpio35),
	BCM63268_GROUP(gpio36),
	BCM63268_GROUP(gpio37),
	BCM63268_GROUP(gpio38),
	BCM63268_GROUP(gpio39),
	BCM63268_GROUP(gpio40),
	BCM63268_GROUP(gpio41),
	BCM63268_GROUP(gpio42),
	BCM63268_GROUP(gpio43),
	BCM63268_GROUP(gpio44),
	BCM63268_GROUP(gpio45),
	BCM63268_GROUP(gpio46),
	BCM63268_GROUP(gpio47),
	BCM63268_GROUP(gpio48),
	BCM63268_GROUP(gpio49),
	BCM63268_GROUP(gpio50),
	BCM63268_GROUP(gpio51),

	/* multi pin groups */
	BCM63268_GROUP(nand_grp),
	BCM63268_GROUP(dectpd_grp),
	BCM63268_GROUP(vdsl_phy0_grp),
	BCM63268_GROUP(vdsl_phy1_grp),
	BCM63268_GROUP(vdsl_phy2_grp),
	BCM63268_GROUP(vdsl_phy3_grp),
पूर्ण;

अटल स्थिर अक्षर * स्थिर led_groups[] = अणु
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
	"gpio16",
	"gpio17",
	"gpio18",
	"gpio19",
	"gpio20",
	"gpio21",
	"gpio22",
	"gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_clk_groups[] = अणु
	"gpio0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_data_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hsspi_cs4_groups[] = अणु
	"gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hsspi_cs5_groups[] = अणु
	"gpio17",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hsspi_cs6_groups[] = अणु
	"gpio8",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hsspi_cs7_groups[] = अणु
	"gpio9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_scts_groups[] = अणु
	"gpio10",
	"gpio24",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_srts_groups[] = अणु
	"gpio11",
	"gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_sdin_groups[] = अणु
	"gpio12",
	"gpio26",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_sकरोut_groups[] = अणु
	"gpio13",
	"gpio27",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ntr_pulse_in_groups[] = अणु
	"gpio14",
	"gpio28",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsl_ntr_pulse_out_groups[] = अणु
	"gpio15",
	"gpio29",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adsl_spi_miso_groups[] = अणु
	"gpio18",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adsl_spi_mosi_groups[] = अणु
	"gpio19",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vreg_clk_groups[] = अणु
	"gpio22",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie_clkreq_b_groups[] = अणु
	"gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर चयन_led_clk_groups[] = अणु
	"gpio30",
पूर्ण;

अटल स्थिर अक्षर * स्थिर चयन_led_data_groups[] = अणु
	"gpio31",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wअगरi_groups[] = अणु
	"gpio32",
	"gpio33",
	"gpio34",
	"gpio35",
	"gpio36",
	"gpio37",
	"gpio38",
	"gpio39",
	"gpio40",
	"gpio41",
	"gpio42",
	"gpio43",
	"gpio44",
	"gpio45",
	"gpio46",
	"gpio47",
	"gpio48",
	"gpio49",
	"gpio50",
	"gpio51",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nand_groups[] = अणु
	"nand_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dectpd_groups[] = अणु
	"dectpd_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vdsl_phy_override_0_groups[] = अणु
	"vdsl_phy_override_0_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vdsl_phy_override_1_groups[] = अणु
	"vdsl_phy_override_1_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vdsl_phy_override_2_groups[] = अणु
	"vdsl_phy_override_2_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vdsl_phy_override_3_groups[] = अणु
	"vdsl_phy_override_3_grp",
पूर्ण;

#घोषणा BCM63268_LED_FUN(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.reg = BCM63268_LEDCTRL,		\
	पूर्ण

#घोषणा BCM63268_MODE_FUN(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.reg = BCM63268_MODE,			\
	पूर्ण

#घोषणा BCM63268_CTRL_FUN(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.reg = BCM63268_CTRL,			\
	पूर्ण

#घोषणा BCM63268_BASEMODE_FUN(n, val)			\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.reg = BCM63268_BASEMODE,		\
		.mask = val,				\
	पूर्ण

अटल स्थिर काष्ठा bcm63268_function bcm63268_funcs[] = अणु
	BCM63268_LED_FUN(led),
	BCM63268_MODE_FUN(serial_led_clk),
	BCM63268_MODE_FUN(serial_led_data),
	BCM63268_MODE_FUN(hsspi_cs6),
	BCM63268_MODE_FUN(hsspi_cs7),
	BCM63268_MODE_FUN(uart1_scts),
	BCM63268_MODE_FUN(uart1_srts),
	BCM63268_MODE_FUN(uart1_sdin),
	BCM63268_MODE_FUN(uart1_sकरोut),
	BCM63268_MODE_FUN(ntr_pulse_in),
	BCM63268_MODE_FUN(dsl_ntr_pulse_out),
	BCM63268_MODE_FUN(hsspi_cs4),
	BCM63268_MODE_FUN(hsspi_cs5),
	BCM63268_MODE_FUN(adsl_spi_miso),
	BCM63268_MODE_FUN(adsl_spi_mosi),
	BCM63268_MODE_FUN(vreg_clk),
	BCM63268_MODE_FUN(pcie_clkreq_b),
	BCM63268_MODE_FUN(चयन_led_clk),
	BCM63268_MODE_FUN(चयन_led_data),
	BCM63268_CTRL_FUN(wअगरi),
	BCM63268_BASEMODE_FUN(nand, BCM63268_BASEMODE_न_अंकD),
	BCM63268_BASEMODE_FUN(dectpd, BCM63268_BASEMODE_DECTPD),
	BCM63268_BASEMODE_FUN(vdsl_phy_override_0,
			      BCM63268_BASEMODE_VDSL_PHY_0),
	BCM63268_BASEMODE_FUN(vdsl_phy_override_1,
			      BCM63268_BASEMODE_VDSL_PHY_1),
	BCM63268_BASEMODE_FUN(vdsl_phy_override_2,
			      BCM63268_BASEMODE_VDSL_PHY_2),
	BCM63268_BASEMODE_FUN(vdsl_phy_override_3,
			      BCM63268_BASEMODE_VDSL_PHY_3),
पूर्ण;

अटल पूर्णांक bcm63268_pinctrl_get_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm63268_groups);
पूर्ण

अटल स्थिर अक्षर *bcm63268_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						   अचिन्हित group)
अणु
	वापस bcm63268_groups[group].name;
पूर्ण

अटल पूर्णांक bcm63268_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित group,
					   स्थिर अचिन्हित **pins,
					   अचिन्हित *num_pins)
अणु
	*pins = bcm63268_groups[group].pins;
	*num_pins = bcm63268_groups[group].num_pins;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63268_pinctrl_get_func_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm63268_funcs);
पूर्ण

अटल स्थिर अक्षर *bcm63268_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित selector)
अणु
	वापस bcm63268_funcs[selector].name;
पूर्ण

अटल पूर्णांक bcm63268_pinctrl_get_groups(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित selector,
				       स्थिर अक्षर * स्थिर **groups,
				       अचिन्हित * स्थिर num_groups)
अणु
	*groups = bcm63268_funcs[selector].groups;
	*num_groups = bcm63268_funcs[selector].num_groups;

	वापस 0;
पूर्ण

अटल व्योम bcm63268_set_gpio(काष्ठा bcm63xx_pinctrl *pc, अचिन्हित pin)
अणु
	स्थिर काष्ठा pinctrl_pin_desc *desc = &bcm63268_pins[pin];
	अचिन्हित पूर्णांक basemode = (अचिन्हित दीर्घ) desc->drv_data;
	अचिन्हित पूर्णांक mask = BIT(bcm63xx_bank_pin(pin));

	अगर (basemode)
		regmap_update_bits(pc->regs, BCM63268_BASEMODE_REG, basemode,
				   0);

	अगर (pin < BCM63XX_BANK_GPIOS) अणु
		/* base mode: 0 => gpio, 1 => mux function */
		regmap_update_bits(pc->regs, BCM63268_MODE_REG, mask, 0);

		/* pins 0-23 might be muxed to led */
		अगर (pin < BCM63268_NUM_LEDS)
			regmap_update_bits(pc->regs, BCM63268_LED_REG, mask,
					   0);
	पूर्ण अन्यथा अगर (pin < BCM63268_NUM_GPIOS) अणु
		/* ctrl reg: 0 => wअगरi function, 1 => gpio */
		regmap_update_bits(pc->regs, BCM63268_CTRL_REG, mask, mask);
	पूर्ण
पूर्ण

अटल पूर्णांक bcm63268_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित selector, अचिन्हित group)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा bcm63268_pingroup *pg = &bcm63268_groups[group];
	स्थिर काष्ठा bcm63268_function *f = &bcm63268_funcs[selector];
	अचिन्हित i;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक val, mask;

	क्रम (i = 0; i < pg->num_pins; i++)
		bcm63268_set_gpio(pc, pg->pins[i]);

	चयन (f->reg) अणु
	हाल BCM63268_LEDCTRL:
		reg = BCM63268_LED_REG;
		mask = BIT(pg->pins[0]);
		val = BIT(pg->pins[0]);
		अवरोध;
	हाल BCM63268_MODE:
		reg = BCM63268_MODE_REG;
		mask = BIT(pg->pins[0]);
		val = BIT(pg->pins[0]);
		अवरोध;
	हाल BCM63268_CTRL:
		reg = BCM63268_CTRL_REG;
		mask = BIT(pg->pins[0]);
		val = 0;
		अवरोध;
	हाल BCM63268_BASEMODE:
		reg = BCM63268_BASEMODE_REG;
		mask = f->mask;
		val = f->mask;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(pc->regs, reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63268_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
					काष्ठा pinctrl_gpio_range *range,
					अचिन्हित offset)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);

	/* disable all functions using this pin */
	bcm63268_set_gpio(pc, offset);

	वापस 0;
पूर्ण

अटल काष्ठा pinctrl_ops bcm63268_pctl_ops = अणु
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.get_group_name = bcm63268_pinctrl_get_group_name,
	.get_group_pins = bcm63268_pinctrl_get_group_pins,
	.get_groups_count = bcm63268_pinctrl_get_group_count,
पूर्ण;

अटल काष्ठा pinmux_ops bcm63268_pmx_ops = अणु
	.get_function_groups = bcm63268_pinctrl_get_groups,
	.get_function_name = bcm63268_pinctrl_get_func_name,
	.get_functions_count = bcm63268_pinctrl_get_func_count,
	.gpio_request_enable = bcm63268_gpio_request_enable,
	.set_mux = bcm63268_pinctrl_set_mux,
	.strict = true,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_pinctrl_soc bcm63268_soc = अणु
	.ngpios = BCM63268_NUM_GPIOS,
	.npins = ARRAY_SIZE(bcm63268_pins),
	.pctl_ops = &bcm63268_pctl_ops,
	.pins = bcm63268_pins,
	.pmx_ops = &bcm63268_pmx_ops,
पूर्ण;

अटल पूर्णांक bcm63268_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस bcm63xx_pinctrl_probe(pdev, &bcm63268_soc, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm63268_pinctrl_match[] = अणु
	अणु .compatible = "brcm,bcm63268-pinctrl", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm63268_pinctrl_driver = अणु
	.probe = bcm63268_pinctrl_probe,
	.driver = अणु
		.name = "bcm63268-pinctrl",
		.of_match_table = bcm63268_pinctrl_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(bcm63268_pinctrl_driver);
