<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Microsemi SoCs pinctrl driver
 *
 * Author: <alexandre.belloni@मुक्त-electrons.com>
 * License: Dual MIT/GPL
 * Copyright (c) 2017 Microsemi Corporation
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinmux.h"

#घोषणा ocelot_clrsetbits(addr, clear, set) \
	ग_लिखोl((पढ़ोl(addr) & ~(clear)) | (set), (addr))

/* PINCONFIG bits (sparx5 only) */
क्रमागत अणु
	PINCONF_BIAS,
	PINCONF_SCHMITT,
	PINCONF_DRIVE_STRENGTH,
पूर्ण;

#घोषणा BIAS_PD_BIT BIT(4)
#घोषणा BIAS_PU_BIT BIT(3)
#घोषणा BIAS_BITS   (BIAS_PD_BIT|BIAS_PU_BIT)
#घोषणा SCHMITT_BIT BIT(2)
#घोषणा DRIVE_BITS  GENMASK(1, 0)

/* GPIO standard रेजिस्टरs */
#घोषणा OCELOT_GPIO_OUT_SET	0x0
#घोषणा OCELOT_GPIO_OUT_CLR	0x4
#घोषणा OCELOT_GPIO_OUT		0x8
#घोषणा OCELOT_GPIO_IN		0xc
#घोषणा OCELOT_GPIO_OE		0x10
#घोषणा OCELOT_GPIO_INTR	0x14
#घोषणा OCELOT_GPIO_INTR_ENA	0x18
#घोषणा OCELOT_GPIO_INTR_IDENT	0x1c
#घोषणा OCELOT_GPIO_ALT0	0x20
#घोषणा OCELOT_GPIO_ALT1	0x24
#घोषणा OCELOT_GPIO_SD_MAP	0x28

#घोषणा OCELOT_FUNC_PER_PIN	4

क्रमागत अणु
	FUNC_NONE,
	FUNC_GPIO,
	FUNC_IRQ0,
	FUNC_IRQ0_IN,
	FUNC_IRQ0_OUT,
	FUNC_IRQ1,
	FUNC_IRQ1_IN,
	FUNC_IRQ1_OUT,
	FUNC_EXT_IRQ,
	FUNC_MIIM,
	FUNC_PHY_LED,
	FUNC_PCI_WAKE,
	FUNC_MD,
	FUNC_PTP0,
	FUNC_PTP1,
	FUNC_PTP2,
	FUNC_PTP3,
	FUNC_PWM,
	FUNC_RECO_CLK,
	FUNC_SFP,
	FUNC_SG0,
	FUNC_SG1,
	FUNC_SG2,
	FUNC_SI,
	FUNC_SI2,
	FUNC_TACHO,
	FUNC_TWI,
	FUNC_TWI2,
	FUNC_TWI3,
	FUNC_TWI_SCL_M,
	FUNC_UART,
	FUNC_UART2,
	FUNC_UART3,
	FUNC_PLL_STAT,
	FUNC_EMMC,
	FUNC_REF_CLK,
	FUNC_RCVRD_CLK,
	FUNC_MAX
पूर्ण;

अटल स्थिर अक्षर *स्थिर ocelot_function_names[] = अणु
	[FUNC_NONE]		= "none",
	[FUNC_GPIO]		= "gpio",
	[FUNC_IRQ0]		= "irq0",
	[FUNC_IRQ0_IN]		= "irq0_in",
	[FUNC_IRQ0_OUT]		= "irq0_out",
	[FUNC_IRQ1]		= "irq1",
	[FUNC_IRQ1_IN]		= "irq1_in",
	[FUNC_IRQ1_OUT]		= "irq1_out",
	[FUNC_EXT_IRQ]		= "ext_irq",
	[FUNC_MIIM]		= "miim",
	[FUNC_PHY_LED]		= "phy_led",
	[FUNC_PCI_WAKE]		= "pci_wake",
	[FUNC_MD]		= "md",
	[FUNC_PTP0]		= "ptp0",
	[FUNC_PTP1]		= "ptp1",
	[FUNC_PTP2]		= "ptp2",
	[FUNC_PTP3]		= "ptp3",
	[FUNC_PWM]		= "pwm",
	[FUNC_RECO_CLK]		= "reco_clk",
	[FUNC_SFP]		= "sfp",
	[FUNC_SG0]		= "sg0",
	[FUNC_SG1]		= "sg1",
	[FUNC_SG2]		= "sg2",
	[FUNC_SI]		= "si",
	[FUNC_SI2]		= "si2",
	[FUNC_TACHO]		= "tacho",
	[FUNC_TWI]		= "twi",
	[FUNC_TWI2]		= "twi2",
	[FUNC_TWI3]		= "twi3",
	[FUNC_TWI_SCL_M]	= "twi_scl_m",
	[FUNC_UART]		= "uart",
	[FUNC_UART2]		= "uart2",
	[FUNC_UART3]		= "uart3",
	[FUNC_PLL_STAT]		= "pll_stat",
	[FUNC_EMMC]		= "emmc",
	[FUNC_REF_CLK]		= "ref_clk",
	[FUNC_RCVRD_CLK]	= "rcvrd_clk",
पूर्ण;

काष्ठा ocelot_pmx_func अणु
	स्थिर अक्षर **groups;
	अचिन्हित पूर्णांक ngroups;
पूर्ण;

काष्ठा ocelot_pin_caps अणु
	अचिन्हित पूर्णांक pin;
	अचिन्हित अक्षर functions[OCELOT_FUNC_PER_PIN];
पूर्ण;

काष्ठा ocelot_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा regmap *map;
	व्योम __iomem *pincfg;
	काष्ठा pinctrl_desc *desc;
	काष्ठा ocelot_pmx_func func[FUNC_MAX];
	u8 stride;
पूर्ण;

#घोषणा LUTON_P(p, f0, f1)						\
अटल काष्ठा ocelot_pin_caps luton_pin_##p = अणु				\
	.pin = p,							\
	.functions = अणु							\
			FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_NONE,	\
	पूर्ण,								\
पूर्ण

LUTON_P(0,  SG0,       NONE);
LUTON_P(1,  SG0,       NONE);
LUTON_P(2,  SG0,       NONE);
LUTON_P(3,  SG0,       NONE);
LUTON_P(4,  TACHO,     NONE);
LUTON_P(5,  TWI,       PHY_LED);
LUTON_P(6,  TWI,       PHY_LED);
LUTON_P(7,  NONE,      PHY_LED);
LUTON_P(8,  EXT_IRQ,   PHY_LED);
LUTON_P(9,  EXT_IRQ,   PHY_LED);
LUTON_P(10, SFP,       PHY_LED);
LUTON_P(11, SFP,       PHY_LED);
LUTON_P(12, SFP,       PHY_LED);
LUTON_P(13, SFP,       PHY_LED);
LUTON_P(14, SI,        PHY_LED);
LUTON_P(15, SI,        PHY_LED);
LUTON_P(16, SI,        PHY_LED);
LUTON_P(17, SFP,       PHY_LED);
LUTON_P(18, SFP,       PHY_LED);
LUTON_P(19, SFP,       PHY_LED);
LUTON_P(20, SFP,       PHY_LED);
LUTON_P(21, SFP,       PHY_LED);
LUTON_P(22, SFP,       PHY_LED);
LUTON_P(23, SFP,       PHY_LED);
LUTON_P(24, SFP,       PHY_LED);
LUTON_P(25, SFP,       PHY_LED);
LUTON_P(26, SFP,       PHY_LED);
LUTON_P(27, SFP,       PHY_LED);
LUTON_P(28, SFP,       PHY_LED);
LUTON_P(29, PWM,       NONE);
LUTON_P(30, UART,      NONE);
LUTON_P(31, UART,      NONE);

#घोषणा LUTON_PIN(n) अणु						\
	.number = n,						\
	.name = "GPIO_"#n,					\
	.drv_data = &luton_pin_##n				\
पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc luton_pins[] = अणु
	LUTON_PIN(0),
	LUTON_PIN(1),
	LUTON_PIN(2),
	LUTON_PIN(3),
	LUTON_PIN(4),
	LUTON_PIN(5),
	LUTON_PIN(6),
	LUTON_PIN(7),
	LUTON_PIN(8),
	LUTON_PIN(9),
	LUTON_PIN(10),
	LUTON_PIN(11),
	LUTON_PIN(12),
	LUTON_PIN(13),
	LUTON_PIN(14),
	LUTON_PIN(15),
	LUTON_PIN(16),
	LUTON_PIN(17),
	LUTON_PIN(18),
	LUTON_PIN(19),
	LUTON_PIN(20),
	LUTON_PIN(21),
	LUTON_PIN(22),
	LUTON_PIN(23),
	LUTON_PIN(24),
	LUTON_PIN(25),
	LUTON_PIN(26),
	LUTON_PIN(27),
	LUTON_PIN(28),
	LUTON_PIN(29),
	LUTON_PIN(30),
	LUTON_PIN(31),
पूर्ण;

#घोषणा SERVAL_P(p, f0, f1, f2)						\
अटल काष्ठा ocelot_pin_caps serval_pin_##p = अणु			\
	.pin = p,							\
	.functions = अणु							\
			FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_##f2,	\
	पूर्ण,								\
पूर्ण

SERVAL_P(0,  SG0,       NONE,      NONE);
SERVAL_P(1,  SG0,       NONE,      NONE);
SERVAL_P(2,  SG0,       NONE,      NONE);
SERVAL_P(3,  SG0,       NONE,      NONE);
SERVAL_P(4,  TACHO,     NONE,      NONE);
SERVAL_P(5,  PWM,       NONE,      NONE);
SERVAL_P(6,  TWI,       NONE,      NONE);
SERVAL_P(7,  TWI,       NONE,      NONE);
SERVAL_P(8,  SI,        NONE,      NONE);
SERVAL_P(9,  SI,        MD,        NONE);
SERVAL_P(10, SI,        MD,        NONE);
SERVAL_P(11, SFP,       MD,        TWI_SCL_M);
SERVAL_P(12, SFP,       MD,        TWI_SCL_M);
SERVAL_P(13, SFP,       UART2,     TWI_SCL_M);
SERVAL_P(14, SFP,       UART2,     TWI_SCL_M);
SERVAL_P(15, SFP,       PTP0,      TWI_SCL_M);
SERVAL_P(16, SFP,       PTP0,      TWI_SCL_M);
SERVAL_P(17, SFP,       PCI_WAKE,  TWI_SCL_M);
SERVAL_P(18, SFP,       NONE,      TWI_SCL_M);
SERVAL_P(19, SFP,       NONE,      TWI_SCL_M);
SERVAL_P(20, SFP,       NONE,      TWI_SCL_M);
SERVAL_P(21, SFP,       NONE,      TWI_SCL_M);
SERVAL_P(22, NONE,      NONE,      NONE);
SERVAL_P(23, NONE,      NONE,      NONE);
SERVAL_P(24, NONE,      NONE,      NONE);
SERVAL_P(25, NONE,      NONE,      NONE);
SERVAL_P(26, UART,      NONE,      NONE);
SERVAL_P(27, UART,      NONE,      NONE);
SERVAL_P(28, IRQ0,      NONE,      NONE);
SERVAL_P(29, IRQ1,      NONE,      NONE);
SERVAL_P(30, PTP0,      NONE,      NONE);
SERVAL_P(31, PTP0,      NONE,      NONE);

#घोषणा SERVAL_PIN(n) अणु						\
	.number = n,						\
	.name = "GPIO_"#n,					\
	.drv_data = &serval_pin_##n				\
पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc serval_pins[] = अणु
	SERVAL_PIN(0),
	SERVAL_PIN(1),
	SERVAL_PIN(2),
	SERVAL_PIN(3),
	SERVAL_PIN(4),
	SERVAL_PIN(5),
	SERVAL_PIN(6),
	SERVAL_PIN(7),
	SERVAL_PIN(8),
	SERVAL_PIN(9),
	SERVAL_PIN(10),
	SERVAL_PIN(11),
	SERVAL_PIN(12),
	SERVAL_PIN(13),
	SERVAL_PIN(14),
	SERVAL_PIN(15),
	SERVAL_PIN(16),
	SERVAL_PIN(17),
	SERVAL_PIN(18),
	SERVAL_PIN(19),
	SERVAL_PIN(20),
	SERVAL_PIN(21),
	SERVAL_PIN(22),
	SERVAL_PIN(23),
	SERVAL_PIN(24),
	SERVAL_PIN(25),
	SERVAL_PIN(26),
	SERVAL_PIN(27),
	SERVAL_PIN(28),
	SERVAL_PIN(29),
	SERVAL_PIN(30),
	SERVAL_PIN(31),
पूर्ण;

#घोषणा OCELOT_P(p, f0, f1, f2)						\
अटल काष्ठा ocelot_pin_caps ocelot_pin_##p = अणु			\
	.pin = p,							\
	.functions = अणु							\
			FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_##f2,	\
	पूर्ण,								\
पूर्ण

OCELOT_P(0,  SG0,       NONE,      NONE);
OCELOT_P(1,  SG0,       NONE,      NONE);
OCELOT_P(2,  SG0,       NONE,      NONE);
OCELOT_P(3,  SG0,       NONE,      NONE);
OCELOT_P(4,  IRQ0_IN,   IRQ0_OUT,  TWI_SCL_M);
OCELOT_P(5,  IRQ1_IN,   IRQ1_OUT,  PCI_WAKE);
OCELOT_P(6,  UART,      TWI_SCL_M, NONE);
OCELOT_P(7,  UART,      TWI_SCL_M, NONE);
OCELOT_P(8,  SI,        TWI_SCL_M, IRQ0_OUT);
OCELOT_P(9,  SI,        TWI_SCL_M, IRQ1_OUT);
OCELOT_P(10, PTP2,      TWI_SCL_M, SFP);
OCELOT_P(11, PTP3,      TWI_SCL_M, SFP);
OCELOT_P(12, UART2,     TWI_SCL_M, SFP);
OCELOT_P(13, UART2,     TWI_SCL_M, SFP);
OCELOT_P(14, MIIM,      TWI_SCL_M, SFP);
OCELOT_P(15, MIIM,      TWI_SCL_M, SFP);
OCELOT_P(16, TWI,       NONE,      SI);
OCELOT_P(17, TWI,       TWI_SCL_M, SI);
OCELOT_P(18, PTP0,      TWI_SCL_M, NONE);
OCELOT_P(19, PTP1,      TWI_SCL_M, NONE);
OCELOT_P(20, RECO_CLK,  TACHO,     TWI_SCL_M);
OCELOT_P(21, RECO_CLK,  PWM,       TWI_SCL_M);

#घोषणा OCELOT_PIN(n) अणु						\
	.number = n,						\
	.name = "GPIO_"#n,					\
	.drv_data = &ocelot_pin_##n				\
पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc ocelot_pins[] = अणु
	OCELOT_PIN(0),
	OCELOT_PIN(1),
	OCELOT_PIN(2),
	OCELOT_PIN(3),
	OCELOT_PIN(4),
	OCELOT_PIN(5),
	OCELOT_PIN(6),
	OCELOT_PIN(7),
	OCELOT_PIN(8),
	OCELOT_PIN(9),
	OCELOT_PIN(10),
	OCELOT_PIN(11),
	OCELOT_PIN(12),
	OCELOT_PIN(13),
	OCELOT_PIN(14),
	OCELOT_PIN(15),
	OCELOT_PIN(16),
	OCELOT_PIN(17),
	OCELOT_PIN(18),
	OCELOT_PIN(19),
	OCELOT_PIN(20),
	OCELOT_PIN(21),
पूर्ण;

#घोषणा JAGUAR2_P(p, f0, f1)						\
अटल काष्ठा ocelot_pin_caps jaguar2_pin_##p = अणु			\
	.pin = p,							\
	.functions = अणु							\
			FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_NONE	\
	पूर्ण,								\
पूर्ण

JAGUAR2_P(0,  SG0,       NONE);
JAGUAR2_P(1,  SG0,       NONE);
JAGUAR2_P(2,  SG0,       NONE);
JAGUAR2_P(3,  SG0,       NONE);
JAGUAR2_P(4,  SG1,       NONE);
JAGUAR2_P(5,  SG1,       NONE);
JAGUAR2_P(6,  IRQ0_IN,   IRQ0_OUT);
JAGUAR2_P(7,  IRQ1_IN,   IRQ1_OUT);
JAGUAR2_P(8,  PTP0,      NONE);
JAGUAR2_P(9,  PTP1,      NONE);
JAGUAR2_P(10, UART,      NONE);
JAGUAR2_P(11, UART,      NONE);
JAGUAR2_P(12, SG1,       NONE);
JAGUAR2_P(13, SG1,       NONE);
JAGUAR2_P(14, TWI,       TWI_SCL_M);
JAGUAR2_P(15, TWI,       NONE);
JAGUAR2_P(16, SI,        TWI_SCL_M);
JAGUAR2_P(17, SI,        TWI_SCL_M);
JAGUAR2_P(18, SI,        TWI_SCL_M);
JAGUAR2_P(19, PCI_WAKE,  NONE);
JAGUAR2_P(20, IRQ0_OUT,  TWI_SCL_M);
JAGUAR2_P(21, IRQ1_OUT,  TWI_SCL_M);
JAGUAR2_P(22, TACHO,     NONE);
JAGUAR2_P(23, PWM,       NONE);
JAGUAR2_P(24, UART2,     NONE);
JAGUAR2_P(25, UART2,     SI);
JAGUAR2_P(26, PTP2,      SI);
JAGUAR2_P(27, PTP3,      SI);
JAGUAR2_P(28, TWI2,      SI);
JAGUAR2_P(29, TWI2,      SI);
JAGUAR2_P(30, SG2,       SI);
JAGUAR2_P(31, SG2,       SI);
JAGUAR2_P(32, SG2,       SI);
JAGUAR2_P(33, SG2,       SI);
JAGUAR2_P(34, NONE,      TWI_SCL_M);
JAGUAR2_P(35, NONE,      TWI_SCL_M);
JAGUAR2_P(36, NONE,      TWI_SCL_M);
JAGUAR2_P(37, NONE,      TWI_SCL_M);
JAGUAR2_P(38, NONE,      TWI_SCL_M);
JAGUAR2_P(39, NONE,      TWI_SCL_M);
JAGUAR2_P(40, NONE,      TWI_SCL_M);
JAGUAR2_P(41, NONE,      TWI_SCL_M);
JAGUAR2_P(42, NONE,      TWI_SCL_M);
JAGUAR2_P(43, NONE,      TWI_SCL_M);
JAGUAR2_P(44, NONE,      SFP);
JAGUAR2_P(45, NONE,      SFP);
JAGUAR2_P(46, NONE,      SFP);
JAGUAR2_P(47, NONE,      SFP);
JAGUAR2_P(48, SFP,       NONE);
JAGUAR2_P(49, SFP,       SI);
JAGUAR2_P(50, SFP,       SI);
JAGUAR2_P(51, SFP,       SI);
JAGUAR2_P(52, SFP,       NONE);
JAGUAR2_P(53, SFP,       NONE);
JAGUAR2_P(54, SFP,       NONE);
JAGUAR2_P(55, SFP,       NONE);
JAGUAR2_P(56, MIIM,      SFP);
JAGUAR2_P(57, MIIM,      SFP);
JAGUAR2_P(58, MIIM,      SFP);
JAGUAR2_P(59, MIIM,      SFP);
JAGUAR2_P(60, NONE,      NONE);
JAGUAR2_P(61, NONE,      NONE);
JAGUAR2_P(62, NONE,      NONE);
JAGUAR2_P(63, NONE,      NONE);

#घोषणा JAGUAR2_PIN(n) अणु					\
	.number = n,						\
	.name = "GPIO_"#n,					\
	.drv_data = &jaguar2_pin_##n				\
पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc jaguar2_pins[] = अणु
	JAGUAR2_PIN(0),
	JAGUAR2_PIN(1),
	JAGUAR2_PIN(2),
	JAGUAR2_PIN(3),
	JAGUAR2_PIN(4),
	JAGUAR2_PIN(5),
	JAGUAR2_PIN(6),
	JAGUAR2_PIN(7),
	JAGUAR2_PIN(8),
	JAGUAR2_PIN(9),
	JAGUAR2_PIN(10),
	JAGUAR2_PIN(11),
	JAGUAR2_PIN(12),
	JAGUAR2_PIN(13),
	JAGUAR2_PIN(14),
	JAGUAR2_PIN(15),
	JAGUAR2_PIN(16),
	JAGUAR2_PIN(17),
	JAGUAR2_PIN(18),
	JAGUAR2_PIN(19),
	JAGUAR2_PIN(20),
	JAGUAR2_PIN(21),
	JAGUAR2_PIN(22),
	JAGUAR2_PIN(23),
	JAGUAR2_PIN(24),
	JAGUAR2_PIN(25),
	JAGUAR2_PIN(26),
	JAGUAR2_PIN(27),
	JAGUAR2_PIN(28),
	JAGUAR2_PIN(29),
	JAGUAR2_PIN(30),
	JAGUAR2_PIN(31),
	JAGUAR2_PIN(32),
	JAGUAR2_PIN(33),
	JAGUAR2_PIN(34),
	JAGUAR2_PIN(35),
	JAGUAR2_PIN(36),
	JAGUAR2_PIN(37),
	JAGUAR2_PIN(38),
	JAGUAR2_PIN(39),
	JAGUAR2_PIN(40),
	JAGUAR2_PIN(41),
	JAGUAR2_PIN(42),
	JAGUAR2_PIN(43),
	JAGUAR2_PIN(44),
	JAGUAR2_PIN(45),
	JAGUAR2_PIN(46),
	JAGUAR2_PIN(47),
	JAGUAR2_PIN(48),
	JAGUAR2_PIN(49),
	JAGUAR2_PIN(50),
	JAGUAR2_PIN(51),
	JAGUAR2_PIN(52),
	JAGUAR2_PIN(53),
	JAGUAR2_PIN(54),
	JAGUAR2_PIN(55),
	JAGUAR2_PIN(56),
	JAGUAR2_PIN(57),
	JAGUAR2_PIN(58),
	JAGUAR2_PIN(59),
	JAGUAR2_PIN(60),
	JAGUAR2_PIN(61),
	JAGUAR2_PIN(62),
	JAGUAR2_PIN(63),
पूर्ण;

#घोषणा SPARX5_P(p, f0, f1, f2)					\
अटल काष्ठा ocelot_pin_caps sparx5_pin_##p = अणु			\
	.pin = p,							\
	.functions = अणु							\
		FUNC_GPIO, FUNC_##f0, FUNC_##f1, FUNC_##f2		\
	पूर्ण,								\
पूर्ण

SPARX5_P(0,  SG0,       PLL_STAT,  NONE);
SPARX5_P(1,  SG0,       NONE,      NONE);
SPARX5_P(2,  SG0,       NONE,      NONE);
SPARX5_P(3,  SG0,       NONE,      NONE);
SPARX5_P(4,  SG1,       NONE,      NONE);
SPARX5_P(5,  SG1,       NONE,      NONE);
SPARX5_P(6,  IRQ0_IN,   IRQ0_OUT,  SFP);
SPARX5_P(7,  IRQ1_IN,   IRQ1_OUT,  SFP);
SPARX5_P(8,  PTP0,      NONE,      SFP);
SPARX5_P(9,  PTP1,      SFP,       TWI_SCL_M);
SPARX5_P(10, UART,      NONE,      NONE);
SPARX5_P(11, UART,      NONE,      NONE);
SPARX5_P(12, SG1,       NONE,      NONE);
SPARX5_P(13, SG1,       NONE,      NONE);
SPARX5_P(14, TWI,       TWI_SCL_M, NONE);
SPARX5_P(15, TWI,       NONE,      NONE);
SPARX5_P(16, SI,        TWI_SCL_M, SFP);
SPARX5_P(17, SI,        TWI_SCL_M, SFP);
SPARX5_P(18, SI,        TWI_SCL_M, SFP);
SPARX5_P(19, PCI_WAKE,  TWI_SCL_M, SFP);
SPARX5_P(20, IRQ0_OUT,  TWI_SCL_M, SFP);
SPARX5_P(21, IRQ1_OUT,  TACHO,     SFP);
SPARX5_P(22, TACHO,     IRQ0_OUT,  TWI_SCL_M);
SPARX5_P(23, PWM,       UART3,     TWI_SCL_M);
SPARX5_P(24, PTP2,      UART3,     TWI_SCL_M);
SPARX5_P(25, PTP3,      SI,        TWI_SCL_M);
SPARX5_P(26, UART2,     SI,        TWI_SCL_M);
SPARX5_P(27, UART2,     SI,        TWI_SCL_M);
SPARX5_P(28, TWI2,      SI,        SFP);
SPARX5_P(29, TWI2,      SI,        SFP);
SPARX5_P(30, SG2,       SI,        PWM);
SPARX5_P(31, SG2,       SI,        TWI_SCL_M);
SPARX5_P(32, SG2,       SI,        TWI_SCL_M);
SPARX5_P(33, SG2,       SI,        SFP);
SPARX5_P(34, NONE,      TWI_SCL_M, EMMC);
SPARX5_P(35, SFP,       TWI_SCL_M, EMMC);
SPARX5_P(36, SFP,       TWI_SCL_M, EMMC);
SPARX5_P(37, SFP,       NONE,      EMMC);
SPARX5_P(38, NONE,      TWI_SCL_M, EMMC);
SPARX5_P(39, SI2,       TWI_SCL_M, EMMC);
SPARX5_P(40, SI2,       TWI_SCL_M, EMMC);
SPARX5_P(41, SI2,       TWI_SCL_M, EMMC);
SPARX5_P(42, SI2,       TWI_SCL_M, EMMC);
SPARX5_P(43, SI2,       TWI_SCL_M, EMMC);
SPARX5_P(44, SI,        SFP,       EMMC);
SPARX5_P(45, SI,        SFP,       EMMC);
SPARX5_P(46, NONE,      SFP,       EMMC);
SPARX5_P(47, NONE,      SFP,       EMMC);
SPARX5_P(48, TWI3,      SI,        SFP);
SPARX5_P(49, TWI3,      NONE,      SFP);
SPARX5_P(50, SFP,       NONE,      TWI_SCL_M);
SPARX5_P(51, SFP,       SI,        TWI_SCL_M);
SPARX5_P(52, SFP,       MIIM,      TWI_SCL_M);
SPARX5_P(53, SFP,       MIIM,      TWI_SCL_M);
SPARX5_P(54, SFP,       PTP2,      TWI_SCL_M);
SPARX5_P(55, SFP,       PTP3,      PCI_WAKE);
SPARX5_P(56, MIIM,      SFP,       TWI_SCL_M);
SPARX5_P(57, MIIM,      SFP,       TWI_SCL_M);
SPARX5_P(58, MIIM,      SFP,       TWI_SCL_M);
SPARX5_P(59, MIIM,      SFP,       NONE);
SPARX5_P(60, RECO_CLK,  NONE,      NONE);
SPARX5_P(61, RECO_CLK,  NONE,      NONE);
SPARX5_P(62, RECO_CLK,  PLL_STAT,  NONE);
SPARX5_P(63, RECO_CLK,  NONE,      NONE);

#घोषणा SPARX5_PIN(n) अणु					\
	.number = n,						\
	.name = "GPIO_"#n,					\
	.drv_data = &sparx5_pin_##n				\
पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc sparx5_pins[] = अणु
	SPARX5_PIN(0),
	SPARX5_PIN(1),
	SPARX5_PIN(2),
	SPARX5_PIN(3),
	SPARX5_PIN(4),
	SPARX5_PIN(5),
	SPARX5_PIN(6),
	SPARX5_PIN(7),
	SPARX5_PIN(8),
	SPARX5_PIN(9),
	SPARX5_PIN(10),
	SPARX5_PIN(11),
	SPARX5_PIN(12),
	SPARX5_PIN(13),
	SPARX5_PIN(14),
	SPARX5_PIN(15),
	SPARX5_PIN(16),
	SPARX5_PIN(17),
	SPARX5_PIN(18),
	SPARX5_PIN(19),
	SPARX5_PIN(20),
	SPARX5_PIN(21),
	SPARX5_PIN(22),
	SPARX5_PIN(23),
	SPARX5_PIN(24),
	SPARX5_PIN(25),
	SPARX5_PIN(26),
	SPARX5_PIN(27),
	SPARX5_PIN(28),
	SPARX5_PIN(29),
	SPARX5_PIN(30),
	SPARX5_PIN(31),
	SPARX5_PIN(32),
	SPARX5_PIN(33),
	SPARX5_PIN(34),
	SPARX5_PIN(35),
	SPARX5_PIN(36),
	SPARX5_PIN(37),
	SPARX5_PIN(38),
	SPARX5_PIN(39),
	SPARX5_PIN(40),
	SPARX5_PIN(41),
	SPARX5_PIN(42),
	SPARX5_PIN(43),
	SPARX5_PIN(44),
	SPARX5_PIN(45),
	SPARX5_PIN(46),
	SPARX5_PIN(47),
	SPARX5_PIN(48),
	SPARX5_PIN(49),
	SPARX5_PIN(50),
	SPARX5_PIN(51),
	SPARX5_PIN(52),
	SPARX5_PIN(53),
	SPARX5_PIN(54),
	SPARX5_PIN(55),
	SPARX5_PIN(56),
	SPARX5_PIN(57),
	SPARX5_PIN(58),
	SPARX5_PIN(59),
	SPARX5_PIN(60),
	SPARX5_PIN(61),
	SPARX5_PIN(62),
	SPARX5_PIN(63),
पूर्ण;

अटल पूर्णांक ocelot_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(ocelot_function_names);
पूर्ण

अटल स्थिर अक्षर *ocelot_get_function_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित पूर्णांक function)
अणु
	वापस ocelot_function_names[function];
पूर्ण

अटल पूर्णांक ocelot_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक function,
				      स्थिर अक्षर *स्थिर **groups,
				      अचिन्हित *स्थिर num_groups)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	*groups  = info->func[function].groups;
	*num_groups = info->func[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_pin_function_idx(काष्ठा ocelot_pinctrl *info,
				   अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक function)
अणु
	काष्ठा ocelot_pin_caps *p = info->desc->pins[pin].drv_data;
	पूर्णांक i;

	क्रम (i = 0; i < OCELOT_FUNC_PER_PIN; i++) अणु
		अगर (function == p->functions[i])
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

#घोषणा REG_ALT(msb, info, p) (OCELOT_GPIO_ALT0 * (info)->stride + 4 * ((msb) + ((info)->stride * ((p) / 32))))

अटल पूर्णांक ocelot_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक selector, अचिन्हित पूर्णांक group)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा ocelot_pin_caps *pin = info->desc->pins[group].drv_data;
	अचिन्हित पूर्णांक p = pin->pin % 32;
	पूर्णांक f;

	f = ocelot_pin_function_idx(info, group, selector);
	अगर (f < 0)
		वापस -EINVAL;

	/*
	 * f is encoded on two bits.
	 * bit 0 of f goes in BIT(pin) of ALT[0], bit 1 of f goes in BIT(pin) of
	 * ALT[1]
	 * This is racy because both रेजिस्टरs can't be updated at the same समय
	 * but it करोesn't matter much क्रम now.
	 * Note: ALT0/ALT1 are organized specially क्रम 64 gpio tarमाला_लो
	 */
	regmap_update_bits(info->map, REG_ALT(0, info, pin->pin),
			   BIT(p), f << p);
	regmap_update_bits(info->map, REG_ALT(1, info, pin->pin),
			   BIT(p), f << (p - 1));

	वापस 0;
पूर्ण

#घोषणा REG(r, info, p) ((r) * (info)->stride + (4 * ((p) / 32)))

अटल पूर्णांक ocelot_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित पूर्णांक pin, bool input)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक p = pin % 32;

	regmap_update_bits(info->map, REG(OCELOT_GPIO_OE, info, pin), BIT(p),
			   input ? 0 : BIT(p));

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_gpio_range *range,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक p = offset % 32;

	regmap_update_bits(info->map, REG_ALT(0, info, offset),
			   BIT(p), 0);
	regmap_update_bits(info->map, REG_ALT(1, info, offset),
			   BIT(p), 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops ocelot_pmx_ops = अणु
	.get_functions_count = ocelot_get_functions_count,
	.get_function_name = ocelot_get_function_name,
	.get_function_groups = ocelot_get_function_groups,
	.set_mux = ocelot_pinmux_set_mux,
	.gpio_set_direction = ocelot_gpio_set_direction,
	.gpio_request_enable = ocelot_gpio_request_enable,
पूर्ण;

अटल पूर्णांक ocelot_pctl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->desc->npins;
पूर्ण

अटल स्थिर अक्षर *ocelot_pctl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित पूर्णांक group)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->desc->pins[group].name;
पूर्ण

अटल पूर्णांक ocelot_pctl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक group,
				      स्थिर अचिन्हित पूर्णांक **pins,
				      अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	*pins = &info->desc->pins[group].number;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_hw_get_value(काष्ठा ocelot_pinctrl *info,
			       अचिन्हित पूर्णांक pin,
			       अचिन्हित पूर्णांक reg,
			       पूर्णांक *val)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (info->pincfg) अणु
		u32 regcfg = पढ़ोl(info->pincfg + (pin * माप(u32)));

		ret = 0;
		चयन (reg) अणु
		हाल PINCONF_BIAS:
			*val = regcfg & BIAS_BITS;
			अवरोध;

		हाल PINCONF_SCHMITT:
			*val = regcfg & SCHMITT_BIT;
			अवरोध;

		हाल PINCONF_DRIVE_STRENGTH:
			*val = regcfg & DRIVE_BITS;
			अवरोध;

		शेष:
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ocelot_hw_set_value(काष्ठा ocelot_pinctrl *info,
			       अचिन्हित पूर्णांक pin,
			       अचिन्हित पूर्णांक reg,
			       पूर्णांक val)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (info->pincfg) अणु
		व्योम __iomem *regaddr = info->pincfg + (pin * माप(u32));

		ret = 0;
		चयन (reg) अणु
		हाल PINCONF_BIAS:
			ocelot_clrsetbits(regaddr, BIAS_BITS, val);
			अवरोध;

		हाल PINCONF_SCHMITT:
			ocelot_clrsetbits(regaddr, SCHMITT_BIT, val);
			अवरोध;

		हाल PINCONF_DRIVE_STRENGTH:
			अगर (val <= 3)
				ocelot_clrsetbits(regaddr, DRIVE_BITS, val);
			अन्यथा
				ret = -EINVAL;
			अवरोध;

		शेष:
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ocelot_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	u32 param = pinconf_to_config_param(*config);
	पूर्णांक val, err;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		err = ocelot_hw_get_value(info, pin, PINCONF_BIAS, &val);
		अगर (err)
			वापस err;
		अगर (param == PIN_CONFIG_BIAS_DISABLE)
			val = (val == 0);
		अन्यथा अगर (param == PIN_CONFIG_BIAS_PULL_DOWN)
			val = (val & BIAS_PD_BIT ? true : false);
		अन्यथा    /* PIN_CONFIG_BIAS_PULL_UP */
			val = (val & BIAS_PU_BIT ? true : false);
		अवरोध;

	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		err = ocelot_hw_get_value(info, pin, PINCONF_SCHMITT, &val);
		अगर (err)
			वापस err;

		val = (val & SCHMITT_BIT ? true : false);
		अवरोध;

	हाल PIN_CONFIG_DRIVE_STRENGTH:
		err = ocelot_hw_get_value(info, pin, PINCONF_DRIVE_STRENGTH,
					  &val);
		अगर (err)
			वापस err;
		अवरोध;

	हाल PIN_CONFIG_OUTPUT:
		err = regmap_पढ़ो(info->map, REG(OCELOT_GPIO_OUT, info, pin),
				  &val);
		अगर (err)
			वापस err;
		val = !!(val & BIT(pin % 32));
		अवरोध;

	हाल PIN_CONFIG_INPUT_ENABLE:
	हाल PIN_CONFIG_OUTPUT_ENABLE:
		err = regmap_पढ़ो(info->map, REG(OCELOT_GPIO_OE, info, pin),
				  &val);
		अगर (err)
			वापस err;
		val = val & BIT(pin % 32);
		अगर (param == PIN_CONFIG_OUTPUT_ENABLE)
			val = !!val;
		अन्यथा
			val = !val;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			      अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	u32 param, arg, p;
	पूर्णांक cfg, err = 0;

	क्रम (cfg = 0; cfg < num_configs; cfg++) अणु
		param = pinconf_to_config_param(configs[cfg]);
		arg = pinconf_to_config_argument(configs[cfg]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			arg = (param == PIN_CONFIG_BIAS_DISABLE) ? 0 :
			(param == PIN_CONFIG_BIAS_PULL_UP) ? BIAS_PU_BIT :
			BIAS_PD_BIT;

			err = ocelot_hw_set_value(info, pin, PINCONF_BIAS, arg);
			अगर (err)
				जाओ err;

			अवरोध;

		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			arg = arg ? SCHMITT_BIT : 0;
			err = ocelot_hw_set_value(info, pin, PINCONF_SCHMITT,
						  arg);
			अगर (err)
				जाओ err;

			अवरोध;

		हाल PIN_CONFIG_DRIVE_STRENGTH:
			err = ocelot_hw_set_value(info, pin,
						  PINCONF_DRIVE_STRENGTH,
						  arg);
			अगर (err)
				जाओ err;

			अवरोध;

		हाल PIN_CONFIG_OUTPUT_ENABLE:
		हाल PIN_CONFIG_INPUT_ENABLE:
		हाल PIN_CONFIG_OUTPUT:
			p = pin % 32;
			अगर (arg)
				regmap_ग_लिखो(info->map,
					     REG(OCELOT_GPIO_OUT_SET, info,
						 pin),
					     BIT(p));
			अन्यथा
				regmap_ग_लिखो(info->map,
					     REG(OCELOT_GPIO_OUT_CLR, info,
						 pin),
					     BIT(p));
			regmap_update_bits(info->map,
					   REG(OCELOT_GPIO_OE, info, pin),
					   BIT(p),
					   param == PIN_CONFIG_INPUT_ENABLE ?
					   0 : BIT(p));
			अवरोध;

		शेष:
			err = -EOPNOTSUPP;
		पूर्ण
	पूर्ण
err:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops ocelot_confops = अणु
	.is_generic = true,
	.pin_config_get = ocelot_pinconf_get,
	.pin_config_set = ocelot_pinconf_set,
	.pin_config_config_dbg_show = pinconf_generic_dump_config,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_ops ocelot_pctl_ops = अणु
	.get_groups_count = ocelot_pctl_get_groups_count,
	.get_group_name = ocelot_pctl_get_group_name,
	.get_group_pins = ocelot_pctl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल काष्ठा pinctrl_desc luton_desc = अणु
	.name = "luton-pinctrl",
	.pins = luton_pins,
	.npins = ARRAY_SIZE(luton_pins),
	.pctlops = &ocelot_pctl_ops,
	.pmxops = &ocelot_pmx_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा pinctrl_desc serval_desc = अणु
	.name = "serval-pinctrl",
	.pins = serval_pins,
	.npins = ARRAY_SIZE(serval_pins),
	.pctlops = &ocelot_pctl_ops,
	.pmxops = &ocelot_pmx_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा pinctrl_desc ocelot_desc = अणु
	.name = "ocelot-pinctrl",
	.pins = ocelot_pins,
	.npins = ARRAY_SIZE(ocelot_pins),
	.pctlops = &ocelot_pctl_ops,
	.pmxops = &ocelot_pmx_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा pinctrl_desc jaguar2_desc = अणु
	.name = "jaguar2-pinctrl",
	.pins = jaguar2_pins,
	.npins = ARRAY_SIZE(jaguar2_pins),
	.pctlops = &ocelot_pctl_ops,
	.pmxops = &ocelot_pmx_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा pinctrl_desc sparx5_desc = अणु
	.name = "sparx5-pinctrl",
	.pins = sparx5_pins,
	.npins = ARRAY_SIZE(sparx5_pins),
	.pctlops = &ocelot_pctl_ops,
	.pmxops = &ocelot_pmx_ops,
	.confops = &ocelot_confops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक ocelot_create_group_func_map(काष्ठा device *dev,
					काष्ठा ocelot_pinctrl *info)
अणु
	पूर्णांक f, npins, i;
	u8 *pins = kसुस्मृति(info->desc->npins, माप(u8), GFP_KERNEL);

	अगर (!pins)
		वापस -ENOMEM;

	क्रम (f = 0; f < FUNC_MAX; f++) अणु
		क्रम (npins = 0, i = 0; i < info->desc->npins; i++) अणु
			अगर (ocelot_pin_function_idx(info, i, f) >= 0)
				pins[npins++] = i;
		पूर्ण

		अगर (!npins)
			जारी;

		info->func[f].ngroups = npins;
		info->func[f].groups = devm_kसुस्मृति(dev, npins, माप(अक्षर *),
						    GFP_KERNEL);
		अगर (!info->func[f].groups) अणु
			kमुक्त(pins);
			वापस -ENOMEM;
		पूर्ण

		क्रम (i = 0; i < npins; i++)
			info->func[f].groups[i] =
				info->desc->pins[pins[i]].name;
	पूर्ण

	kमुक्त(pins);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_pinctrl_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				   काष्ठा ocelot_pinctrl *info)
अणु
	पूर्णांक ret;

	ret = ocelot_create_group_func_map(&pdev->dev, info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to create group func map.\n");
		वापस ret;
	पूर्ण

	info->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, info->desc, info);
	अगर (IS_ERR(info->pctl)) अणु
		dev_err(&pdev->dev, "Failed to register pinctrl\n");
		वापस PTR_ERR(info->pctl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ocelot_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(info->map, REG(OCELOT_GPIO_IN, info, offset), &val);

	वापस !!(val & BIT(offset % 32));
पूर्ण

अटल व्योम ocelot_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा ocelot_pinctrl *info = gpiochip_get_data(chip);

	अगर (value)
		regmap_ग_लिखो(info->map, REG(OCELOT_GPIO_OUT_SET, info, offset),
			     BIT(offset % 32));
	अन्यथा
		regmap_ग_लिखो(info->map, REG(OCELOT_GPIO_OUT_CLR, info, offset),
			     BIT(offset % 32));
पूर्ण

अटल पूर्णांक ocelot_gpio_get_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ocelot_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(info->map, REG(OCELOT_GPIO_OE, info, offset), &val);

	अगर (val & BIT(offset % 32))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक ocelot_gpio_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक ocelot_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा ocelot_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक pin = BIT(offset % 32);

	अगर (value)
		regmap_ग_लिखो(info->map, REG(OCELOT_GPIO_OUT_SET, info, offset),
			     pin);
	अन्यथा
		regmap_ग_लिखो(info->map, REG(OCELOT_GPIO_OUT_CLR, info, offset),
			     pin);

	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ocelot_gpiolib_chip = अणु
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.set = ocelot_gpio_set,
	.get = ocelot_gpio_get,
	.get_direction = ocelot_gpio_get_direction,
	.direction_input = ocelot_gpio_direction_input,
	.direction_output = ocelot_gpio_direction_output,
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम ocelot_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा ocelot_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(data);

	regmap_update_bits(info->map, REG(OCELOT_GPIO_INTR_ENA, info, gpio),
			   BIT(gpio % 32), 0);
पूर्ण

अटल व्योम ocelot_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा ocelot_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(data);

	regmap_update_bits(info->map, REG(OCELOT_GPIO_INTR_ENA, info, gpio),
			   BIT(gpio % 32), BIT(gpio % 32));
पूर्ण

अटल व्योम ocelot_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा ocelot_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(data);

	regmap_ग_लिखो_bits(info->map, REG(OCELOT_GPIO_INTR, info, gpio),
			  BIT(gpio % 32), BIT(gpio % 32));
पूर्ण

अटल पूर्णांक ocelot_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type);

अटल काष्ठा irq_chip ocelot_eoi_irqchip = अणु
	.name		= "gpio",
	.irq_mask	= ocelot_irq_mask,
	.irq_eoi	= ocelot_irq_ack,
	.irq_unmask	= ocelot_irq_unmask,
	.flags          = IRQCHIP_EOI_THREADED | IRQCHIP_EOI_IF_HANDLED,
	.irq_set_type	= ocelot_irq_set_type,
पूर्ण;

अटल काष्ठा irq_chip ocelot_irqchip = अणु
	.name		= "gpio",
	.irq_mask	= ocelot_irq_mask,
	.irq_ack	= ocelot_irq_ack,
	.irq_unmask	= ocelot_irq_unmask,
	.irq_set_type	= ocelot_irq_set_type,
पूर्ण;

अटल पूर्णांक ocelot_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	type &= IRQ_TYPE_SENSE_MASK;

	अगर (!(type & (IRQ_TYPE_EDGE_BOTH | IRQ_TYPE_LEVEL_HIGH)))
		वापस -EINVAL;

	अगर (type & IRQ_TYPE_LEVEL_HIGH)
		irq_set_chip_handler_name_locked(data, &ocelot_eoi_irqchip,
						 handle_fasteoi_irq, शून्य);
	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_chip_handler_name_locked(data, &ocelot_irqchip,
						 handle_edge_irq, शून्य);

	वापस 0;
पूर्ण

अटल व्योम ocelot_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *parent_chip = irq_desc_get_chip(desc);
	काष्ठा gpio_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा ocelot_pinctrl *info = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक id_reg = OCELOT_GPIO_INTR_IDENT * info->stride;
	अचिन्हित पूर्णांक reg = 0, irq, i;
	अचिन्हित दीर्घ irqs;

	क्रम (i = 0; i < info->stride; i++) अणु
		regmap_पढ़ो(info->map, id_reg + 4 * i, &reg);
		अगर (!reg)
			जारी;

		chained_irq_enter(parent_chip, desc);

		irqs = reg;

		क्रम_each_set_bit(irq, &irqs,
				 min(32U, info->desc->npins - 32 * i))
			generic_handle_irq(irq_linear_revmap(chip->irq.करोमुख्य,
							     irq + 32 * i));

		chained_irq_निकास(parent_chip, desc);
	पूर्ण
पूर्ण

अटल पूर्णांक ocelot_gpiochip_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				    काष्ठा ocelot_pinctrl *info)
अणु
	काष्ठा gpio_chip *gc;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक irq;

	info->gpio_chip = ocelot_gpiolib_chip;

	gc = &info->gpio_chip;
	gc->ngpio = info->desc->npins;
	gc->parent = &pdev->dev;
	gc->base = 0;
	gc->of_node = info->dev->of_node;
	gc->label = "ocelot-gpio";

	irq = irq_of_parse_and_map(gc->of_node, 0);
	अगर (irq) अणु
		girq = &gc->irq;
		girq->chip = &ocelot_irqchip;
		girq->parent_handler = ocelot_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_edge_irq;
	पूर्ण

	वापस devm_gpiochip_add_data(&pdev->dev, gc, info);
पूर्ण

अटल स्थिर काष्ठा of_device_id ocelot_pinctrl_of_match[] = अणु
	अणु .compatible = "mscc,luton-pinctrl", .data = &luton_desc पूर्ण,
	अणु .compatible = "mscc,serval-pinctrl", .data = &serval_desc पूर्ण,
	अणु .compatible = "mscc,ocelot-pinctrl", .data = &ocelot_desc पूर्ण,
	अणु .compatible = "mscc,jaguar2-pinctrl", .data = &jaguar2_desc पूर्ण,
	अणु .compatible = "microchip,sparx5-pinctrl", .data = &sparx5_desc पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक ocelot_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ocelot_pinctrl *info;
	व्योम __iomem *base;
	काष्ठा resource *res;
	पूर्णांक ret;
	काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 32,
		.val_bits = 32,
		.reg_stride = 4,
	पूर्ण;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->desc = (काष्ठा pinctrl_desc *)device_get_match_data(dev);

	base = devm_ioremap_resource(dev,
			platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0));
	अगर (IS_ERR(base)) अणु
		dev_err(dev, "Failed to ioremap registers\n");
		वापस PTR_ERR(base);
	पूर्ण

	info->stride = 1 + (info->desc->npins - 1) / 32;

	regmap_config.max_रेजिस्टर = OCELOT_GPIO_SD_MAP * info->stride + 15 * 4;

	info->map = devm_regmap_init_mmio(dev, base, &regmap_config);
	अगर (IS_ERR(info->map)) अणु
		dev_err(dev, "Failed to create regmap\n");
		वापस PTR_ERR(info->map);
	पूर्ण
	dev_set_drvdata(dev, info->map);
	info->dev = dev;

	/* Pinconf रेजिस्टरs */
	अगर (info->desc->confops) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(base))
			dev_dbg(dev, "Failed to ioremap config registers (no extended pinconf)\n");
		अन्यथा
			info->pincfg = base;
	पूर्ण

	ret = ocelot_pinctrl_रेजिस्टर(pdev, info);
	अगर (ret)
		वापस ret;

	ret = ocelot_gpiochip_रेजिस्टर(pdev, info);
	अगर (ret)
		वापस ret;

	dev_info(dev, "driver registered\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ocelot_pinctrl_driver = अणु
	.driver = अणु
		.name = "pinctrl-ocelot",
		.of_match_table = of_match_ptr(ocelot_pinctrl_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = ocelot_pinctrl_probe,
पूर्ण;
builtin_platक्रमm_driver(ocelot_pinctrl_driver);
