<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Pengutronix, Oleksij Rempel <o.rempel@pengutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/v7m.h>
#समावेश <यंत्र/mach/arch.h>

अटल स्थिर अक्षर * स्थिर imx7d_cm4_dt_compat[] __initस्थिर = अणु
	"fsl,imx7d-cm4",
	शून्य,
पूर्ण;

DT_MACHINE_START(IMX7D, "Freescale i.MX7 Dual Cortex-M4 (Device Tree)")
	.dt_compat = imx7d_cm4_dt_compat,
	.restart = armv7m_restart,
MACHINE_END
