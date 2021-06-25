<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Steffen Trumtrar, Pengutronix
 *
 * based on imx27-dt.c
 */

#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश "common.h"
#समावेश "mx35.h"

अटल स्थिर अक्षर * स्थिर imx35_dt_board_compat[] __initस्थिर = अणु
	"fsl,imx35",
	शून्य
पूर्ण;

DT_MACHINE_START(IMX35_DT, "Freescale i.MX35 (Device Tree Support)")
	.l2c_aux_val 	= 0,
	.l2c_aux_mask	= ~0,
	.map_io		= mx35_map_io,
	.init_early	= imx35_init_early,
	.dt_compat	= imx35_dt_board_compat,
MACHINE_END
