<शैली गुरु>
/*
 * Driver क्रम the ST Microelectronics SPEAr3xx pinmux
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-spear3xx.h"

/* pins */
अटल स्थिर काष्ठा pinctrl_pin_desc spear3xx_pins[] = अणु
	SPEAR_PIN_0_TO_101,
पूर्ण;

/* firda_pins */
अटल स्थिर अचिन्हित firda_pins[] = अणु 0, 1 पूर्ण;
अटल काष्ठा spear_muxreg firda_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_FIRDA_MASK,
		.val = PMX_FIRDA_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux firda_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = firda_muxreg,
		.nmuxregs = ARRAY_SIZE(firda_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_firda_pingroup = अणु
	.name = "firda_grp",
	.pins = firda_pins,
	.npins = ARRAY_SIZE(firda_pins),
	.modemuxs = firda_modemux,
	.nmodemuxs = ARRAY_SIZE(firda_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर firda_grps[] = अणु "firda_grp" पूर्ण;
काष्ठा spear_function spear3xx_firda_function = अणु
	.name = "firda",
	.groups = firda_grps,
	.ngroups = ARRAY_SIZE(firda_grps),
पूर्ण;

/* i2c_pins */
अटल स्थिर अचिन्हित i2c_pins[] = अणु 4, 5 पूर्ण;
अटल काष्ठा spear_muxreg i2c_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_I2C_MASK,
		.val = PMX_I2C_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux i2c_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = i2c_muxreg,
		.nmuxregs = ARRAY_SIZE(i2c_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_i2c_pingroup = अणु
	.name = "i2c0_grp",
	.pins = i2c_pins,
	.npins = ARRAY_SIZE(i2c_pins),
	.modemuxs = i2c_modemux,
	.nmodemuxs = ARRAY_SIZE(i2c_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर i2c_grps[] = अणु "i2c0_grp" पूर्ण;
काष्ठा spear_function spear3xx_i2c_function = अणु
	.name = "i2c0",
	.groups = i2c_grps,
	.ngroups = ARRAY_SIZE(i2c_grps),
पूर्ण;

/* ssp_cs_pins */
अटल स्थिर अचिन्हित ssp_cs_pins[] = अणु 34, 35, 36 पूर्ण;
अटल काष्ठा spear_muxreg ssp_cs_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_SSP_CS_MASK,
		.val = PMX_SSP_CS_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp_cs_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = ssp_cs_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp_cs_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_ssp_cs_pingroup = अणु
	.name = "ssp_cs_grp",
	.pins = ssp_cs_pins,
	.npins = ARRAY_SIZE(ssp_cs_pins),
	.modemuxs = ssp_cs_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp_cs_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर ssp_cs_grps[] = अणु "ssp_cs_grp" पूर्ण;
काष्ठा spear_function spear3xx_ssp_cs_function = अणु
	.name = "ssp_cs",
	.groups = ssp_cs_grps,
	.ngroups = ARRAY_SIZE(ssp_cs_grps),
पूर्ण;

/* ssp_pins */
अटल स्थिर अचिन्हित ssp_pins[] = अणु 6, 7, 8, 9 पूर्ण;
अटल काष्ठा spear_muxreg ssp_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_SSP_MASK,
		.val = PMX_SSP_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux ssp_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = ssp_muxreg,
		.nmuxregs = ARRAY_SIZE(ssp_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_ssp_pingroup = अणु
	.name = "ssp0_grp",
	.pins = ssp_pins,
	.npins = ARRAY_SIZE(ssp_pins),
	.modemuxs = ssp_modemux,
	.nmodemuxs = ARRAY_SIZE(ssp_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर ssp_grps[] = अणु "ssp0_grp" पूर्ण;
काष्ठा spear_function spear3xx_ssp_function = अणु
	.name = "ssp0",
	.groups = ssp_grps,
	.ngroups = ARRAY_SIZE(ssp_grps),
पूर्ण;

/* mii_pins */
अटल स्थिर अचिन्हित mii_pins[] = अणु 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27 पूर्ण;
अटल काष्ठा spear_muxreg mii_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_MII_MASK,
		.val = PMX_MII_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux mii_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = mii_muxreg,
		.nmuxregs = ARRAY_SIZE(mii_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_mii_pingroup = अणु
	.name = "mii0_grp",
	.pins = mii_pins,
	.npins = ARRAY_SIZE(mii_pins),
	.modemuxs = mii_modemux,
	.nmodemuxs = ARRAY_SIZE(mii_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर mii_grps[] = अणु "mii0_grp" पूर्ण;
काष्ठा spear_function spear3xx_mii_function = अणु
	.name = "mii0",
	.groups = mii_grps,
	.ngroups = ARRAY_SIZE(mii_grps),
पूर्ण;

/* gpio0_pin0_pins */
अटल स्थिर अचिन्हित gpio0_pin0_pins[] = अणु 28 पूर्ण;
अटल काष्ठा spear_muxreg gpio0_pin0_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_GPIO_PIN0_MASK,
		.val = PMX_GPIO_PIN0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpio0_pin0_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = gpio0_pin0_muxreg,
		.nmuxregs = ARRAY_SIZE(gpio0_pin0_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_gpio0_pin0_pingroup = अणु
	.name = "gpio0_pin0_grp",
	.pins = gpio0_pin0_pins,
	.npins = ARRAY_SIZE(gpio0_pin0_pins),
	.modemuxs = gpio0_pin0_modemux,
	.nmodemuxs = ARRAY_SIZE(gpio0_pin0_modemux),
पूर्ण;

/* gpio0_pin1_pins */
अटल स्थिर अचिन्हित gpio0_pin1_pins[] = अणु 29 पूर्ण;
अटल काष्ठा spear_muxreg gpio0_pin1_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_GPIO_PIN1_MASK,
		.val = PMX_GPIO_PIN1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpio0_pin1_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = gpio0_pin1_muxreg,
		.nmuxregs = ARRAY_SIZE(gpio0_pin1_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_gpio0_pin1_pingroup = अणु
	.name = "gpio0_pin1_grp",
	.pins = gpio0_pin1_pins,
	.npins = ARRAY_SIZE(gpio0_pin1_pins),
	.modemuxs = gpio0_pin1_modemux,
	.nmodemuxs = ARRAY_SIZE(gpio0_pin1_modemux),
पूर्ण;

/* gpio0_pin2_pins */
अटल स्थिर अचिन्हित gpio0_pin2_pins[] = अणु 30 पूर्ण;
अटल काष्ठा spear_muxreg gpio0_pin2_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_GPIO_PIN2_MASK,
		.val = PMX_GPIO_PIN2_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpio0_pin2_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = gpio0_pin2_muxreg,
		.nmuxregs = ARRAY_SIZE(gpio0_pin2_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_gpio0_pin2_pingroup = अणु
	.name = "gpio0_pin2_grp",
	.pins = gpio0_pin2_pins,
	.npins = ARRAY_SIZE(gpio0_pin2_pins),
	.modemuxs = gpio0_pin2_modemux,
	.nmodemuxs = ARRAY_SIZE(gpio0_pin2_modemux),
पूर्ण;

/* gpio0_pin3_pins */
अटल स्थिर अचिन्हित gpio0_pin3_pins[] = अणु 31 पूर्ण;
अटल काष्ठा spear_muxreg gpio0_pin3_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_GPIO_PIN3_MASK,
		.val = PMX_GPIO_PIN3_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpio0_pin3_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = gpio0_pin3_muxreg,
		.nmuxregs = ARRAY_SIZE(gpio0_pin3_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_gpio0_pin3_pingroup = अणु
	.name = "gpio0_pin3_grp",
	.pins = gpio0_pin3_pins,
	.npins = ARRAY_SIZE(gpio0_pin3_pins),
	.modemuxs = gpio0_pin3_modemux,
	.nmodemuxs = ARRAY_SIZE(gpio0_pin3_modemux),
पूर्ण;

/* gpio0_pin4_pins */
अटल स्थिर अचिन्हित gpio0_pin4_pins[] = अणु 32 पूर्ण;
अटल काष्ठा spear_muxreg gpio0_pin4_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_GPIO_PIN4_MASK,
		.val = PMX_GPIO_PIN4_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpio0_pin4_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = gpio0_pin4_muxreg,
		.nmuxregs = ARRAY_SIZE(gpio0_pin4_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_gpio0_pin4_pingroup = अणु
	.name = "gpio0_pin4_grp",
	.pins = gpio0_pin4_pins,
	.npins = ARRAY_SIZE(gpio0_pin4_pins),
	.modemuxs = gpio0_pin4_modemux,
	.nmodemuxs = ARRAY_SIZE(gpio0_pin4_modemux),
पूर्ण;

/* gpio0_pin5_pins */
अटल स्थिर अचिन्हित gpio0_pin5_pins[] = अणु 33 पूर्ण;
अटल काष्ठा spear_muxreg gpio0_pin5_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_GPIO_PIN5_MASK,
		.val = PMX_GPIO_PIN5_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux gpio0_pin5_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = gpio0_pin5_muxreg,
		.nmuxregs = ARRAY_SIZE(gpio0_pin5_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_gpio0_pin5_pingroup = अणु
	.name = "gpio0_pin5_grp",
	.pins = gpio0_pin5_pins,
	.npins = ARRAY_SIZE(gpio0_pin5_pins),
	.modemuxs = gpio0_pin5_modemux,
	.nmodemuxs = ARRAY_SIZE(gpio0_pin5_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर gpio0_grps[] = अणु "gpio0_pin0_grp", "gpio0_pin1_grp",
	"gpio0_pin2_grp", "gpio0_pin3_grp", "gpio0_pin4_grp", "gpio0_pin5_grp",
पूर्ण;
काष्ठा spear_function spear3xx_gpio0_function = अणु
	.name = "gpio0",
	.groups = gpio0_grps,
	.ngroups = ARRAY_SIZE(gpio0_grps),
पूर्ण;

/* uart0_ext_pins */
अटल स्थिर अचिन्हित uart0_ext_pins[] = अणु 37, 38, 39, 40, 41, 42 पूर्ण;
अटल काष्ठा spear_muxreg uart0_ext_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_UART0_MODEM_MASK,
		.val = PMX_UART0_MODEM_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart0_ext_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = uart0_ext_muxreg,
		.nmuxregs = ARRAY_SIZE(uart0_ext_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_uart0_ext_pingroup = अणु
	.name = "uart0_ext_grp",
	.pins = uart0_ext_pins,
	.npins = ARRAY_SIZE(uart0_ext_pins),
	.modemuxs = uart0_ext_modemux,
	.nmodemuxs = ARRAY_SIZE(uart0_ext_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart0_ext_grps[] = अणु "uart0_ext_grp" पूर्ण;
काष्ठा spear_function spear3xx_uart0_ext_function = अणु
	.name = "uart0_ext",
	.groups = uart0_ext_grps,
	.ngroups = ARRAY_SIZE(uart0_ext_grps),
पूर्ण;

/* uart0_pins */
अटल स्थिर अचिन्हित uart0_pins[] = अणु 2, 3 पूर्ण;
अटल काष्ठा spear_muxreg uart0_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_UART0_MASK,
		.val = PMX_UART0_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart0_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = uart0_muxreg,
		.nmuxregs = ARRAY_SIZE(uart0_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_uart0_pingroup = अणु
	.name = "uart0_grp",
	.pins = uart0_pins,
	.npins = ARRAY_SIZE(uart0_pins),
	.modemuxs = uart0_modemux,
	.nmodemuxs = ARRAY_SIZE(uart0_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart0_grps[] = अणु "uart0_grp" पूर्ण;
काष्ठा spear_function spear3xx_uart0_function = अणु
	.name = "uart0",
	.groups = uart0_grps,
	.ngroups = ARRAY_SIZE(uart0_grps),
पूर्ण;

/* समयr_0_1_pins */
अटल स्थिर अचिन्हित समयr_0_1_pins[] = अणु 43, 44, 47, 48 पूर्ण;
अटल काष्ठा spear_muxreg समयr_0_1_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_TIMER_0_1_MASK,
		.val = PMX_TIMER_0_1_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux समयr_0_1_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = समयr_0_1_muxreg,
		.nmuxregs = ARRAY_SIZE(समयr_0_1_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_समयr_0_1_pingroup = अणु
	.name = "timer_0_1_grp",
	.pins = समयr_0_1_pins,
	.npins = ARRAY_SIZE(समयr_0_1_pins),
	.modemuxs = समयr_0_1_modemux,
	.nmodemuxs = ARRAY_SIZE(समयr_0_1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर समयr_0_1_grps[] = अणु "timer_0_1_grp" पूर्ण;
काष्ठा spear_function spear3xx_समयr_0_1_function = अणु
	.name = "timer_0_1",
	.groups = समयr_0_1_grps,
	.ngroups = ARRAY_SIZE(समयr_0_1_grps),
पूर्ण;

/* समयr_2_3_pins */
अटल स्थिर अचिन्हित समयr_2_3_pins[] = अणु 45, 46, 49, 50 पूर्ण;
अटल काष्ठा spear_muxreg समयr_2_3_muxreg[] = अणु
	अणु
		.reg = -1,
		.mask = PMX_TIMER_2_3_MASK,
		.val = PMX_TIMER_2_3_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux समयr_2_3_modemux[] = अणु
	अणु
		.modes = ~0,
		.muxregs = समयr_2_3_muxreg,
		.nmuxregs = ARRAY_SIZE(समयr_2_3_muxreg),
	पूर्ण,
पूर्ण;

काष्ठा spear_pingroup spear3xx_समयr_2_3_pingroup = अणु
	.name = "timer_2_3_grp",
	.pins = समयr_2_3_pins,
	.npins = ARRAY_SIZE(समयr_2_3_pins),
	.modemuxs = समयr_2_3_modemux,
	.nmodemuxs = ARRAY_SIZE(समयr_2_3_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर समयr_2_3_grps[] = अणु "timer_2_3_grp" पूर्ण;
काष्ठा spear_function spear3xx_समयr_2_3_function = अणु
	.name = "timer_2_3",
	.groups = समयr_2_3_grps,
	.ngroups = ARRAY_SIZE(समयr_2_3_grps),
पूर्ण;

/* Define muxreg arrays */
DEFINE_MUXREG(firda_pins, 0, PMX_FIRDA_MASK, 0);
DEFINE_MUXREG(i2c_pins, 0, PMX_I2C_MASK, 0);
DEFINE_MUXREG(ssp_cs_pins, 0, PMX_SSP_CS_MASK, 0);
DEFINE_MUXREG(ssp_pins, 0, PMX_SSP_MASK, 0);
DEFINE_MUXREG(mii_pins, 0, PMX_MII_MASK, 0);
DEFINE_MUXREG(gpio0_pin0_pins, 0, PMX_GPIO_PIN0_MASK, 0);
DEFINE_MUXREG(gpio0_pin1_pins, 0, PMX_GPIO_PIN1_MASK, 0);
DEFINE_MUXREG(gpio0_pin2_pins, 0, PMX_GPIO_PIN2_MASK, 0);
DEFINE_MUXREG(gpio0_pin3_pins, 0, PMX_GPIO_PIN3_MASK, 0);
DEFINE_MUXREG(gpio0_pin4_pins, 0, PMX_GPIO_PIN4_MASK, 0);
DEFINE_MUXREG(gpio0_pin5_pins, 0, PMX_GPIO_PIN5_MASK, 0);
DEFINE_MUXREG(uart0_ext_pins, 0, PMX_UART0_MODEM_MASK, 0);
DEFINE_MUXREG(uart0_pins, 0, PMX_UART0_MASK, 0);
DEFINE_MUXREG(समयr_0_1_pins, 0, PMX_TIMER_0_1_MASK, 0);
DEFINE_MUXREG(समयr_2_3_pins, 0, PMX_TIMER_2_3_MASK, 0);

अटल काष्ठा spear_gpio_pingroup spear3xx_gpio_pingroup[] = अणु
	GPIO_PINGROUP(firda_pins),
	GPIO_PINGROUP(i2c_pins),
	GPIO_PINGROUP(ssp_cs_pins),
	GPIO_PINGROUP(ssp_pins),
	GPIO_PINGROUP(mii_pins),
	GPIO_PINGROUP(gpio0_pin0_pins),
	GPIO_PINGROUP(gpio0_pin1_pins),
	GPIO_PINGROUP(gpio0_pin2_pins),
	GPIO_PINGROUP(gpio0_pin3_pins),
	GPIO_PINGROUP(gpio0_pin4_pins),
	GPIO_PINGROUP(gpio0_pin5_pins),
	GPIO_PINGROUP(uart0_ext_pins),
	GPIO_PINGROUP(uart0_pins),
	GPIO_PINGROUP(समयr_0_1_pins),
	GPIO_PINGROUP(समयr_2_3_pins),
पूर्ण;

काष्ठा spear_pinctrl_machdata spear3xx_machdata = अणु
	.pins = spear3xx_pins,
	.npins = ARRAY_SIZE(spear3xx_pins),
	.gpio_pingroups = spear3xx_gpio_pingroup,
	.ngpio_pingroups = ARRAY_SIZE(spear3xx_gpio_pingroup),
पूर्ण;
