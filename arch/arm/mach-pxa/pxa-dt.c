<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/pxa-dt.c
 *
 *  Copyright (C) 2012 Daniel Mack
 */

#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

#अगर_घोषित CONFIG_PXA25x
अटल स्थिर अक्षर * स्थिर pxa25x_dt_board_compat[] __initस्थिर = अणु
	"marvell,pxa250",
	शून्य,
पूर्ण;

DT_MACHINE_START(PXA25X_DT, "Marvell PXA25x (Device Tree Support)")
	.map_io		= pxa25x_map_io,
	.restart	= pxa_restart,
	.dt_compat	= pxa25x_dt_board_compat,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_PXA27x
अटल स्थिर अक्षर * स्थिर pxa27x_dt_board_compat[] __initस्थिर = अणु
	"marvell,pxa270",
	शून्य,
पूर्ण;

DT_MACHINE_START(PXA27X_DT, "Marvell PXA27x (Device Tree Support)")
	.map_io		= pxa27x_map_io,
	.restart	= pxa_restart,
	.dt_compat	= pxa27x_dt_board_compat,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_PXA3xx
अटल स्थिर अक्षर *स्थिर pxa3xx_dt_board_compat[] __initस्थिर = अणु
	"marvell,pxa300",
	"marvell,pxa310",
	"marvell,pxa320",
	शून्य,
पूर्ण;

DT_MACHINE_START(PXA_DT, "Marvell PXA3xx (Device Tree Support)")
	.map_io		= pxa3xx_map_io,
	.restart	= pxa_restart,
	.dt_compat	= pxa3xx_dt_board_compat,
MACHINE_END
#पूर्ण_अगर
