<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Sascha Hauer, Pengutronix
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "common.h"
#समावेश "hardware.h"
#समावेश "mx27.h"

/* MX27 memory map definition */
अटल काष्ठा map_desc imx27_io_desc[] __initdata = अणु
	/*
	 * this fixed mapping covers:
	 * - AIPI1
	 * - AIPI2
	 * - AITC
	 * - ROM Patch
	 * - and some reserved space
	 */
	imx_map_entry(MX27, AIPI, MT_DEVICE),
	/*
	 * this fixed mapping covers:
	 * - CSI
	 * - ATA
	 */
	imx_map_entry(MX27, SAHB1, MT_DEVICE),
	/*
	 * this fixed mapping covers:
	 * - EMI
	 */
	imx_map_entry(MX27, X_MEMC, MT_DEVICE),
पूर्ण;

/*
 * Initialize the memory map. It is called during the
 * प्रणाली startup to create अटल physical to भव
 * memory map क्रम the IO modules.
 */
अटल व्योम __init mx27_map_io(व्योम)
अणु
	iotable_init(imx27_io_desc, ARRAY_SIZE(imx27_io_desc));
पूर्ण

अटल व्योम __init imx27_init_early(व्योम)
अणु
	mxc_set_cpu_type(MXC_CPU_MX27);
पूर्ण

अटल स्थिर अक्षर * स्थिर imx27_dt_board_compat[] __initस्थिर = अणु
	"fsl,imx27",
	शून्य
पूर्ण;

DT_MACHINE_START(IMX27_DT, "Freescale i.MX27 (Device Tree Support)")
	.map_io		= mx27_map_io,
	.init_early	= imx27_init_early,
	.init_late	= imx27_pm_init,
	.dt_compat	= imx27_dt_board_compat,
MACHINE_END
