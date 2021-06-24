<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Sascha Hauer, Pengutronix
 */

#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश "common.h"
#समावेश "hardware.h"

अटल व्योम __init imx25_init_early(व्योम)
अणु
	mxc_set_cpu_type(MXC_CPU_MX25);
पूर्ण

अटल व्योम __init imx25_dt_init(व्योम)
अणु
	imx_aips_allow_unprivileged_access("fsl,imx25-aips");
पूर्ण

अटल स्थिर अक्षर * स्थिर imx25_dt_board_compat[] __initस्थिर = अणु
	"fsl,imx25",
	शून्य
पूर्ण;

DT_MACHINE_START(IMX25_DT, "Freescale i.MX25 (Device Tree Support)")
	.init_early	= imx25_init_early,
	.init_machine	= imx25_dt_init,
	.init_late      = imx25_pm_init,
	.dt_compat	= imx25_dt_board_compat,
MACHINE_END
