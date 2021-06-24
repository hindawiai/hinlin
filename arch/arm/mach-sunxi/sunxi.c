<शैली गुरु>
/*
 * Device Tree support क्रम Allwinner A1X SoCs
 *
 * Copyright (C) 2012 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset/sunxi.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/secure_cntvoff.h>

अटल स्थिर अक्षर * स्थिर sunxi_board_dt_compat[] = अणु
	"allwinner,sun4i-a10",
	"allwinner,sun5i-a10s",
	"allwinner,sun5i-a13",
	"allwinner,sun5i-r8",
	"nextthing,gr8",
	शून्य,
पूर्ण;

DT_MACHINE_START(SUNXI_DT, "Allwinner sun4i/sun5i Families")
	.dt_compat	= sunxi_board_dt_compat,
MACHINE_END

अटल स्थिर अक्षर * स्थिर sun6i_board_dt_compat[] = अणु
	"allwinner,sun6i-a31",
	"allwinner,sun6i-a31s",
	शून्य,
पूर्ण;

अटल व्योम __init sun6i_समयr_init(व्योम)
अणु
	of_clk_init(शून्य);
	अगर (IS_ENABLED(CONFIG_RESET_CONTROLLER))
		sun6i_reset_init();
	समयr_probe();
पूर्ण

DT_MACHINE_START(SUN6I_DT, "Allwinner sun6i (A31) Family")
	.init_समय	= sun6i_समयr_init,
	.dt_compat	= sun6i_board_dt_compat,
MACHINE_END

अटल स्थिर अक्षर * स्थिर sun7i_board_dt_compat[] = अणु
	"allwinner,sun7i-a20",
	शून्य,
पूर्ण;

DT_MACHINE_START(SUN7I_DT, "Allwinner sun7i (A20) Family")
	.dt_compat	= sun7i_board_dt_compat,
MACHINE_END

अटल स्थिर अक्षर * स्थिर sun8i_board_dt_compat[] = अणु
	"allwinner,sun8i-a23",
	"allwinner,sun8i-a33",
	"allwinner,sun8i-h2-plus",
	"allwinner,sun8i-h3",
	"allwinner,sun8i-r40",
	"allwinner,sun8i-v3",
	"allwinner,sun8i-v3s",
	शून्य,
पूर्ण;

DT_MACHINE_START(SUN8I_DT, "Allwinner sun8i Family")
	.init_समय	= sun6i_समयr_init,
	.dt_compat	= sun8i_board_dt_compat,
MACHINE_END

अटल व्योम __init sun8i_a83t_cntvoff_init(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	secure_cntvoff_init();
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर * स्थिर sun8i_a83t_cntvoff_board_dt_compat[] = अणु
	"allwinner,sun8i-a83t",
	शून्य,
पूर्ण;

DT_MACHINE_START(SUN8I_A83T_CNTVOFF_DT, "Allwinner A83t board")
	.init_early	= sun8i_a83t_cntvoff_init,
	.init_समय	= sun6i_समयr_init,
	.dt_compat	= sun8i_a83t_cntvoff_board_dt_compat,
MACHINE_END

अटल स्थिर अक्षर * स्थिर sun9i_board_dt_compat[] = अणु
	"allwinner,sun9i-a80",
	शून्य,
पूर्ण;

DT_MACHINE_START(SUN9I_DT, "Allwinner sun9i Family")
	.dt_compat	= sun9i_board_dt_compat,
MACHINE_END

अटल स्थिर अक्षर * स्थिर suniv_board_dt_compat[] = अणु
	"allwinner,suniv-f1c100s",
	शून्य,
पूर्ण;

DT_MACHINE_START(SUNIV_DT, "Allwinner suniv Family")
	.dt_compat	= suniv_board_dt_compat,
MACHINE_END
