<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * This file contains the CPU initialization code.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "hardware.h"
#समावेश "common.h"

अटल पूर्णांक mx5_cpu_rev = -1;

#घोषणा IIM_SREV 0x24

अटल u32 imx5_पढ़ो_srev_reg(स्थिर अक्षर *compat)
अणु
	व्योम __iomem *iim_base;
	काष्ठा device_node *np;
	u32 srev;

	np = of_find_compatible_node(शून्य, शून्य, compat);
	iim_base = of_iomap(np, 0);
	WARN_ON(!iim_base);

	srev = पढ़ोl(iim_base + IIM_SREV) & 0xff;

	iounmap(iim_base);

	वापस srev;
पूर्ण

अटल पूर्णांक get_mx51_srev(व्योम)
अणु
	u32 rev = imx5_पढ़ो_srev_reg("fsl,imx51-iim");

	चयन (rev) अणु
	हाल 0x0:
		वापस IMX_CHIP_REVISION_2_0;
	हाल 0x10:
		वापस IMX_CHIP_REVISION_3_0;
	शेष:
		वापस IMX_CHIP_REVISION_UNKNOWN;
	पूर्ण
पूर्ण

/*
 * Returns:
 *	the silicon revision of the cpu
 */
पूर्णांक mx51_revision(व्योम)
अणु
	अगर (mx5_cpu_rev == -1)
		mx5_cpu_rev = get_mx51_srev();

	वापस mx5_cpu_rev;
पूर्ण
EXPORT_SYMBOL(mx51_revision);

#अगर_घोषित CONFIG_NEON

/*
 * All versions of the silicon beक्रमe Rev. 3 have broken NEON implementations.
 * Dependent on link order - so the assumption is that vfp_init is called
 * beक्रमe us.
 */
पूर्णांक __init mx51_neon_fixup(व्योम)
अणु
	अगर (mx51_revision() < IMX_CHIP_REVISION_3_0 &&
			(elf_hwcap & HWCAP_NEON)) अणु
		elf_hwcap &= ~HWCAP_NEON;
		pr_info("Turning off NEON support, detected broken NEON implementation\n");
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक get_mx53_srev(व्योम)
अणु
	u32 rev = imx5_पढ़ो_srev_reg("fsl,imx53-iim");

	चयन (rev) अणु
	हाल 0x0:
		वापस IMX_CHIP_REVISION_1_0;
	हाल 0x2:
		वापस IMX_CHIP_REVISION_2_0;
	हाल 0x3:
		वापस IMX_CHIP_REVISION_2_1;
	शेष:
		वापस IMX_CHIP_REVISION_UNKNOWN;
	पूर्ण
पूर्ण

/*
 * Returns:
 *	the silicon revision of the cpu
 */
पूर्णांक mx53_revision(व्योम)
अणु
	अगर (mx5_cpu_rev == -1)
		mx5_cpu_rev = get_mx53_srev();

	वापस mx5_cpu_rev;
पूर्ण
EXPORT_SYMBOL(mx53_revision);

#घोषणा ARM_GPC		0x4
#घोषणा DBGEN		BIT(16)

/*
 * This enables the DBGEN bit in ARM_GPC रेजिस्टर, which is
 * required क्रम accessing some perक्रमmance counter features.
 * Technically it is only required जबतक perf is used, but to
 * keep the source code simple we just enable it all the समय
 * when the kernel configuration allows using the feature.
 */
व्योम __init imx5_pmu_init(व्योम)
अणु
	व्योम __iomem *tigerp_base;
	काष्ठा device_node *np;
	u32 gpc;

	अगर (!IS_ENABLED(CONFIG_ARM_PMU))
		वापस;

	np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a8-pmu");
	अगर (!np)
		वापस;

	अगर (!of_property_पढ़ो_bool(np, "secure-reg-access"))
		जाओ निकास;

	of_node_put(np);

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx51-tigerp");
	अगर (!np)
		वापस;

	tigerp_base = of_iomap(np, 0);
	अगर (!tigerp_base)
		जाओ निकास;

	gpc = पढ़ोl_relaxed(tigerp_base + ARM_GPC);
	gpc |= DBGEN;
	ग_लिखोl_relaxed(gpc, tigerp_base + ARM_GPC);
	iounmap(tigerp_base);
निकास:
	of_node_put(np);

पूर्ण
