<शैली गुरु>
/*
 * Driver क्रम the ST Microelectronics SPEAr310 pinmux
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "pinctrl-spear3xx.h"

#घोषणा DRIVER_NAME "spear310-pinmux"

/* addresses */
#घोषणा PMX_CONFIG_REG			0x08

/* emi_cs_0_to_5_pins */
अटल स्थिर अचिन्हित emi_cs_0_to_5_pins[] = अणु 45, 46, 47, 48, 49, 50 पूर्ण;
अटल काष्ठा spear_muxreg emi_cs_0_to_5_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK | PMX_TIMER_2_3_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux emi_cs_0_to_5_modemux[] = अणु
	अणु
		.muxregs = emi_cs_0_to_5_muxreg,
		.nmuxregs = ARRAY_SIZE(emi_cs_0_to_5_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup emi_cs_0_to_5_pingroup = अणु
	.name = "emi_cs_0_to_5_grp",
	.pins = emi_cs_0_to_5_pins,
	.npins = ARRAY_SIZE(emi_cs_0_to_5_pins),
	.modemuxs = emi_cs_0_to_5_modemux,
	.nmodemuxs = ARRAY_SIZE(emi_cs_0_to_5_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर emi_cs_0_to_5_grps[] = अणु "emi_cs_0_to_5_grp" पूर्ण;
अटल काष्ठा spear_function emi_cs_0_to_5_function = अणु
	.name = "emi",
	.groups = emi_cs_0_to_5_grps,
	.ngroups = ARRAY_SIZE(emi_cs_0_to_5_grps),
पूर्ण;

/* uart1_pins */
अटल स्थिर अचिन्हित uart1_pins[] = अणु 0, 1 पूर्ण;
अटल काष्ठा spear_muxreg uart1_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_FIRDA_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart1_modemux[] = अणु
	अणु
		.muxregs = uart1_muxreg,
		.nmuxregs = ARRAY_SIZE(uart1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart1_pingroup = अणु
	.name = "uart1_grp",
	.pins = uart1_pins,
	.npins = ARRAY_SIZE(uart1_pins),
	.modemuxs = uart1_modemux,
	.nmodemuxs = ARRAY_SIZE(uart1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart1_grps[] = अणु "uart1_grp" पूर्ण;
अटल काष्ठा spear_function uart1_function = अणु
	.name = "uart1",
	.groups = uart1_grps,
	.ngroups = ARRAY_SIZE(uart1_grps),
पूर्ण;

/* uart2_pins */
अटल स्थिर अचिन्हित uart2_pins[] = अणु 43, 44 पूर्ण;
अटल काष्ठा spear_muxreg uart2_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_TIMER_0_1_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart2_modemux[] = अणु
	अणु
		.muxregs = uart2_muxreg,
		.nmuxregs = ARRAY_SIZE(uart2_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart2_pingroup = अणु
	.name = "uart2_grp",
	.pins = uart2_pins,
	.npins = ARRAY_SIZE(uart2_pins),
	.modemuxs = uart2_modemux,
	.nmodemuxs = ARRAY_SIZE(uart2_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart2_grps[] = अणु "uart2_grp" पूर्ण;
अटल काष्ठा spear_function uart2_function = अणु
	.name = "uart2",
	.groups = uart2_grps,
	.ngroups = ARRAY_SIZE(uart2_grps),
पूर्ण;

/* uart3_pins */
अटल स्थिर अचिन्हित uart3_pins[] = अणु 37, 38 पूर्ण;
अटल काष्ठा spear_muxreg uart3_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart3_modemux[] = अणु
	अणु
		.muxregs = uart3_muxreg,
		.nmuxregs = ARRAY_SIZE(uart3_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart3_pingroup = अणु
	.name = "uart3_grp",
	.pins = uart3_pins,
	.npins = ARRAY_SIZE(uart3_pins),
	.modemuxs = uart3_modemux,
	.nmodemuxs = ARRAY_SIZE(uart3_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart3_grps[] = अणु "uart3_grp" पूर्ण;
अटल काष्ठा spear_function uart3_function = अणु
	.name = "uart3",
	.groups = uart3_grps,
	.ngroups = ARRAY_SIZE(uart3_grps),
पूर्ण;

/* uart4_pins */
अटल स्थिर अचिन्हित uart4_pins[] = अणु 39, 40 पूर्ण;
अटल काष्ठा spear_muxreg uart4_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart4_modemux[] = अणु
	अणु
		.muxregs = uart4_muxreg,
		.nmuxregs = ARRAY_SIZE(uart4_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart4_pingroup = अणु
	.name = "uart4_grp",
	.pins = uart4_pins,
	.npins = ARRAY_SIZE(uart4_pins),
	.modemuxs = uart4_modemux,
	.nmodemuxs = ARRAY_SIZE(uart4_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart4_grps[] = अणु "uart4_grp" पूर्ण;
अटल काष्ठा spear_function uart4_function = अणु
	.name = "uart4",
	.groups = uart4_grps,
	.ngroups = ARRAY_SIZE(uart4_grps),
पूर्ण;

/* uart5_pins */
अटल स्थिर अचिन्हित uart5_pins[] = अणु 41, 42 पूर्ण;
अटल काष्ठा spear_muxreg uart5_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_UART0_MODEM_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux uart5_modemux[] = अणु
	अणु
		.muxregs = uart5_muxreg,
		.nmuxregs = ARRAY_SIZE(uart5_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup uart5_pingroup = अणु
	.name = "uart5_grp",
	.pins = uart5_pins,
	.npins = ARRAY_SIZE(uart5_pins),
	.modemuxs = uart5_modemux,
	.nmodemuxs = ARRAY_SIZE(uart5_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर uart5_grps[] = अणु "uart5_grp" पूर्ण;
अटल काष्ठा spear_function uart5_function = अणु
	.name = "uart5",
	.groups = uart5_grps,
	.ngroups = ARRAY_SIZE(uart5_grps),
पूर्ण;

/* fsmc_pins */
अटल स्थिर अचिन्हित fsmc_pins[] = अणु 34, 35, 36 पूर्ण;
अटल काष्ठा spear_muxreg fsmc_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_SSP_CS_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux fsmc_modemux[] = अणु
	अणु
		.muxregs = fsmc_muxreg,
		.nmuxregs = ARRAY_SIZE(fsmc_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup fsmc_pingroup = अणु
	.name = "fsmc_grp",
	.pins = fsmc_pins,
	.npins = ARRAY_SIZE(fsmc_pins),
	.modemuxs = fsmc_modemux,
	.nmodemuxs = ARRAY_SIZE(fsmc_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर fsmc_grps[] = अणु "fsmc_grp" पूर्ण;
अटल काष्ठा spear_function fsmc_function = अणु
	.name = "fsmc",
	.groups = fsmc_grps,
	.ngroups = ARRAY_SIZE(fsmc_grps),
पूर्ण;

/* rs485_0_pins */
अटल स्थिर अचिन्हित rs485_0_pins[] = अणु 19, 20, 21, 22, 23 पूर्ण;
अटल काष्ठा spear_muxreg rs485_0_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux rs485_0_modemux[] = अणु
	अणु
		.muxregs = rs485_0_muxreg,
		.nmuxregs = ARRAY_SIZE(rs485_0_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup rs485_0_pingroup = अणु
	.name = "rs485_0_grp",
	.pins = rs485_0_pins,
	.npins = ARRAY_SIZE(rs485_0_pins),
	.modemuxs = rs485_0_modemux,
	.nmodemuxs = ARRAY_SIZE(rs485_0_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर rs485_0_grps[] = अणु "rs485_0" पूर्ण;
अटल काष्ठा spear_function rs485_0_function = अणु
	.name = "rs485_0",
	.groups = rs485_0_grps,
	.ngroups = ARRAY_SIZE(rs485_0_grps),
पूर्ण;

/* rs485_1_pins */
अटल स्थिर अचिन्हित rs485_1_pins[] = अणु 14, 15, 16, 17, 18 पूर्ण;
अटल काष्ठा spear_muxreg rs485_1_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux rs485_1_modemux[] = अणु
	अणु
		.muxregs = rs485_1_muxreg,
		.nmuxregs = ARRAY_SIZE(rs485_1_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup rs485_1_pingroup = अणु
	.name = "rs485_1_grp",
	.pins = rs485_1_pins,
	.npins = ARRAY_SIZE(rs485_1_pins),
	.modemuxs = rs485_1_modemux,
	.nmodemuxs = ARRAY_SIZE(rs485_1_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर rs485_1_grps[] = अणु "rs485_1" पूर्ण;
अटल काष्ठा spear_function rs485_1_function = अणु
	.name = "rs485_1",
	.groups = rs485_1_grps,
	.ngroups = ARRAY_SIZE(rs485_1_grps),
पूर्ण;

/* tdm_pins */
अटल स्थिर अचिन्हित tdm_pins[] = अणु 10, 11, 12, 13 पूर्ण;
अटल काष्ठा spear_muxreg tdm_muxreg[] = अणु
	अणु
		.reg = PMX_CONFIG_REG,
		.mask = PMX_MII_MASK,
		.val = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_modemux tdm_modemux[] = अणु
	अणु
		.muxregs = tdm_muxreg,
		.nmuxregs = ARRAY_SIZE(tdm_muxreg),
	पूर्ण,
पूर्ण;

अटल काष्ठा spear_pingroup tdm_pingroup = अणु
	.name = "tdm_grp",
	.pins = tdm_pins,
	.npins = ARRAY_SIZE(tdm_pins),
	.modemuxs = tdm_modemux,
	.nmodemuxs = ARRAY_SIZE(tdm_modemux),
पूर्ण;

अटल स्थिर अक्षर *स्थिर tdm_grps[] = अणु "tdm_grp" पूर्ण;
अटल काष्ठा spear_function tdm_function = अणु
	.name = "tdm",
	.groups = tdm_grps,
	.ngroups = ARRAY_SIZE(tdm_grps),
पूर्ण;

/* pingroups */
अटल काष्ठा spear_pingroup *spear310_pingroups[] = अणु
	SPEAR3XX_COMMON_PINGROUPS,
	&emi_cs_0_to_5_pingroup,
	&uart1_pingroup,
	&uart2_pingroup,
	&uart3_pingroup,
	&uart4_pingroup,
	&uart5_pingroup,
	&fsmc_pingroup,
	&rs485_0_pingroup,
	&rs485_1_pingroup,
	&tdm_pingroup,
पूर्ण;

/* functions */
अटल काष्ठा spear_function *spear310_functions[] = अणु
	SPEAR3XX_COMMON_FUNCTIONS,
	&emi_cs_0_to_5_function,
	&uart1_function,
	&uart2_function,
	&uart3_function,
	&uart4_function,
	&uart5_function,
	&fsmc_function,
	&rs485_0_function,
	&rs485_1_function,
	&tdm_function,
पूर्ण;

अटल स्थिर काष्ठा of_device_id spear310_pinctrl_of_match[] = अणु
	अणु
		.compatible = "st,spear310-pinmux",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक spear310_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	spear3xx_machdata.groups = spear310_pingroups;
	spear3xx_machdata.ngroups = ARRAY_SIZE(spear310_pingroups);
	spear3xx_machdata.functions = spear310_functions;
	spear3xx_machdata.nfunctions = ARRAY_SIZE(spear310_functions);

	pmx_init_addr(&spear3xx_machdata, PMX_CONFIG_REG);
	pmx_init_gpio_pingroup_addr(spear3xx_machdata.gpio_pingroups,
			spear3xx_machdata.ngpio_pingroups, PMX_CONFIG_REG);

	spear3xx_machdata.modes_supported = false;

	वापस spear_pinctrl_probe(pdev, &spear3xx_machdata);
पूर्ण

अटल काष्ठा platक्रमm_driver spear310_pinctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = spear310_pinctrl_of_match,
	पूर्ण,
	.probe = spear310_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init spear310_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&spear310_pinctrl_driver);
पूर्ण
arch_initcall(spear310_pinctrl_init);
