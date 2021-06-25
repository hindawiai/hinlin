<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "common.h"
#समावेश "hardware.h"

अटल व्योम __init imx53_init_early(व्योम)
अणु
	mxc_set_cpu_type(MXC_CPU_MX53);
पूर्ण

अटल व्योम __init imx53_dt_init(व्योम)
अणु
	imx_src_init();
	imx5_pmu_init();
	imx_aips_allow_unprivileged_access("fsl,imx53-aipstz");
पूर्ण

अटल व्योम __init imx53_init_late(व्योम)
अणु
	imx53_pm_init();
पूर्ण

अटल स्थिर अक्षर * स्थिर imx53_dt_board_compat[] __initस्थिर = अणु
	"fsl,imx53",
	शून्य
पूर्ण;

DT_MACHINE_START(IMX53_DT, "Freescale i.MX53 (Device Tree Support)")
	.init_early	= imx53_init_early,
	.init_machine	= imx53_dt_init,
	.init_late	= imx53_init_late,
	.dt_compat	= imx53_dt_board_compat,
MACHINE_END
