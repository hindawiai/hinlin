<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 1999,2000 Arm Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 *  Copyright (C) 2002 Shane Nay (shane@minirl.com)
 *  Copyright 2005-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 *    - add MX31 specअगरic definitions
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/pinctrl/machine.h>

#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "crmregs-imx3.h"
#समावेश "hardware.h"

व्योम __iomem *mx3_ccm_base;

अटल व्योम imx3_idle(व्योम)
अणु
	अचिन्हित दीर्घ reg = 0;

	__यंत्र__ __अस्थिर__(
		/* disable I and D cache */
		"mrc p15, 0, %0, c1, c0, 0\n"
		"bic %0, %0, #0x00001000\n"
		"bic %0, %0, #0x00000004\n"
		"mcr p15, 0, %0, c1, c0, 0\n"
		/* invalidate I cache */
		"mov %0, #0\n"
		"mcr p15, 0, %0, c7, c5, 0\n"
		/* clear and invalidate D cache */
		"mov %0, #0\n"
		"mcr p15, 0, %0, c7, c14, 0\n"
		/* WFI */
		"mov %0, #0\n"
		"mcr p15, 0, %0, c7, c0, 4\n"
		"nop\n" "nop\n" "nop\n" "nop\n"
		"nop\n" "nop\n" "nop\n"
		/* enable I and D cache */
		"mrc p15, 0, %0, c1, c0, 0\n"
		"orr %0, %0, #0x00001000\n"
		"orr %0, %0, #0x00000004\n"
		"mcr p15, 0, %0, c1, c0, 0\n"
		: "=r" (reg));
पूर्ण

अटल व्योम __iomem *imx3_ioremap_caller(phys_addr_t phys_addr, माप_प्रकार size,
					 अचिन्हित पूर्णांक mtype, व्योम *caller)
अणु
	अगर (mtype == MT_DEVICE) अणु
		/*
		 * Access all peripherals below 0x80000000 as nonshared device
		 * on mx3, but leave l2cc alone.  Otherwise cache corruptions
		 * can occur.
		 */
		अगर (phys_addr < 0x80000000 &&
				!addr_in_module(phys_addr, MX3x_L2CC))
			mtype = MT_DEVICE_NONSHARED;
	पूर्ण

	वापस __arm_ioremap_caller(phys_addr, size, mtype, caller);
पूर्ण

#अगर_घोषित CONFIG_SOC_IMX31
अटल काष्ठा map_desc mx31_io_desc[] __initdata = अणु
	imx_map_entry(MX31, X_MEMC, MT_DEVICE),
	imx_map_entry(MX31, AVIC, MT_DEVICE_NONSHARED),
	imx_map_entry(MX31, AIPS1, MT_DEVICE_NONSHARED),
	imx_map_entry(MX31, AIPS2, MT_DEVICE_NONSHARED),
	imx_map_entry(MX31, SPBA0, MT_DEVICE_NONSHARED),
पूर्ण;

/*
 * This function initializes the memory map. It is called during the
 * प्रणाली startup to create अटल physical to भव memory mappings
 * क्रम the IO modules.
 */
व्योम __init mx31_map_io(व्योम)
अणु
	iotable_init(mx31_io_desc, ARRAY_SIZE(mx31_io_desc));
पूर्ण

अटल व्योम imx31_idle(व्योम)
अणु
	पूर्णांक reg = imx_पढ़ोl(mx3_ccm_base + MXC_CCM_CCMR);
	reg &= ~MXC_CCM_CCMR_LPM_MASK;
	imx_ग_लिखोl(reg, mx3_ccm_base + MXC_CCM_CCMR);

	imx3_idle();
पूर्ण

व्योम __init imx31_init_early(व्योम)
अणु
	काष्ठा device_node *np;

	mxc_set_cpu_type(MXC_CPU_MX31);
	arch_ioremap_caller = imx3_ioremap_caller;
	arm_pm_idle = imx31_idle;
	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx31-ccm");
	mx3_ccm_base = of_iomap(np, 0);
	BUG_ON(!mx3_ccm_base);
पूर्ण
#पूर्ण_अगर /* अगरdef CONFIG_SOC_IMX31 */

#अगर_घोषित CONFIG_SOC_IMX35
अटल काष्ठा map_desc mx35_io_desc[] __initdata = अणु
	imx_map_entry(MX35, X_MEMC, MT_DEVICE),
	imx_map_entry(MX35, AVIC, MT_DEVICE_NONSHARED),
	imx_map_entry(MX35, AIPS1, MT_DEVICE_NONSHARED),
	imx_map_entry(MX35, AIPS2, MT_DEVICE_NONSHARED),
	imx_map_entry(MX35, SPBA0, MT_DEVICE_NONSHARED),
पूर्ण;

व्योम __init mx35_map_io(व्योम)
अणु
	iotable_init(mx35_io_desc, ARRAY_SIZE(mx35_io_desc));
पूर्ण

अटल व्योम imx35_idle(व्योम)
अणु
	पूर्णांक reg = imx_पढ़ोl(mx3_ccm_base + MXC_CCM_CCMR);
	reg &= ~MXC_CCM_CCMR_LPM_MASK;
	reg |= MXC_CCM_CCMR_LPM_WAIT_MX35;
	imx_ग_लिखोl(reg, mx3_ccm_base + MXC_CCM_CCMR);

	imx3_idle();
पूर्ण

व्योम __init imx35_init_early(व्योम)
अणु
	काष्ठा device_node *np;

	mxc_set_cpu_type(MXC_CPU_MX35);
	arm_pm_idle = imx35_idle;
	arch_ioremap_caller = imx3_ioremap_caller;
	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx35-ccm");
	mx3_ccm_base = of_iomap(np, 0);
	BUG_ON(!mx3_ccm_base);
पूर्ण
#पूर्ण_अगर /* अगरdef CONFIG_SOC_IMX35 */
