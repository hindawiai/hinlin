<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "common.h"
#समावेश "hardware.h"

अटल व्योम __init imx51_init_early(व्योम)
अणु
	mxc_set_cpu_type(MXC_CPU_MX51);
पूर्ण

/*
 * The MIPI HSC unit has been हटाओd from the i.MX51 Reference Manual by
 * the Freescale marketing भागision. However this did not हटाओ the
 * hardware from the chip which still needs to be configured क्रम proper
 * IPU support.
 */
#घोषणा MX51_MIPI_HSC_BASE 0x83fdc000
अटल व्योम __init imx51_ipu_mipi_setup(व्योम)
अणु
	व्योम __iomem *hsc_addr;

	hsc_addr = ioremap(MX51_MIPI_HSC_BASE, SZ_16K);
	WARN_ON(!hsc_addr);

	/* setup MIPI module to legacy mode */
	imx_ग_लिखोl(0xf00, hsc_addr);

	/* CSI mode: reserved; DI control mode: legacy (from Freescale BSP) */
	imx_ग_लिखोl(imx_पढ़ोl(hsc_addr + 0x800) | 0x30ff, hsc_addr + 0x800);

	iounmap(hsc_addr);
पूर्ण

अटल व्योम __init imx51_m4अगर_setup(व्योम)
अणु
	व्योम __iomem *m4अगर_base;
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx51-m4if");
	अगर (!np)
		वापस;

	m4अगर_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!m4अगर_base) अणु
		pr_err("Unable to map M4IF registers\n");
		वापस;
	पूर्ण

	/*
	 * Configure VPU and IPU with higher priorities
	 * in order to aव्योम artअगरacts during video playback
	 */
	ग_लिखोl_relaxed(0x00000203, m4अगर_base + 0x40);
	ग_लिखोl_relaxed(0x00000000, m4अगर_base + 0x44);
	ग_लिखोl_relaxed(0x00120125, m4अगर_base + 0x9c);
	ग_लिखोl_relaxed(0x001901A3, m4अगर_base + 0x48);
	iounmap(m4अगर_base);
पूर्ण

अटल व्योम __init imx51_dt_init(व्योम)
अणु
	imx51_ipu_mipi_setup();
	imx_src_init();
	imx51_m4अगर_setup();
	imx5_pmu_init();
	imx_aips_allow_unprivileged_access("fsl,imx51-aipstz");
पूर्ण

अटल व्योम __init imx51_init_late(व्योम)
अणु
	mx51_neon_fixup();
	imx51_pm_init();
पूर्ण

अटल स्थिर अक्षर * स्थिर imx51_dt_board_compat[] __initस्थिर = अणु
	"fsl,imx51",
	शून्य
पूर्ण;

DT_MACHINE_START(IMX51_DT, "Freescale i.MX51 (Device Tree Support)")
	.init_early	= imx51_init_early,
	.init_machine	= imx51_dt_init,
	.init_late	= imx51_init_late,
	.dt_compat	= imx51_dt_board_compat,
MACHINE_END
