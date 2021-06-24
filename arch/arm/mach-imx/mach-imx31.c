<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Sascha Hauer, Pengutronix
 */

#समावेश <यंत्र/mach/arch.h>
#समावेश "common.h"

अटल स्थिर अक्षर * स्थिर imx31_dt_board_compat[] __initस्थिर = अणु
	"fsl,imx31",
	शून्य
पूर्ण;

DT_MACHINE_START(IMX31_DT, "Freescale i.MX31 (Device Tree Support)")
	.map_io		= mx31_map_io,
	.init_early	= imx31_init_early,
	.dt_compat	= imx31_dt_board_compat,
MACHINE_END
