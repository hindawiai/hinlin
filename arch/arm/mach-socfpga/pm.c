<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  arch/arm/mach-socfpga/pm.c
 *
 * Copyright (C) 2014-2015 Altera Corporation. All rights reserved.
 *
 * with code from pm-imx6.c
 * Copyright 2011-2014 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/fncpy.h>
#समावेश "core.h"

/* Poपूर्णांकer to function copied to ocram */
अटल u32 (*socfpga_sdram_self_refresh_in_ocram)(u32 sdr_base);

अटल पूर्णांक socfpga_setup_ocram_self_refresh(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	phys_addr_t ocram_pbase;
	काष्ठा device_node *np;
	काष्ठा gen_pool *ocram_pool;
	अचिन्हित दीर्घ ocram_base;
	व्योम __iomem *suspend_ocram_base;
	पूर्णांक ret = 0;

	np = of_find_compatible_node(शून्य, शून्य, "mmio-sram");
	अगर (!np) अणु
		pr_err("%s: Unable to find mmio-sram in dtb\n", __func__);
		वापस -ENODEV;
	पूर्ण

	pdev = of_find_device_by_node(np);
	अगर (!pdev) अणु
		pr_warn("%s: failed to find ocram device!\n", __func__);
		ret = -ENODEV;
		जाओ put_node;
	पूर्ण

	ocram_pool = gen_pool_get(&pdev->dev, शून्य);
	अगर (!ocram_pool) अणु
		pr_warn("%s: ocram pool unavailable!\n", __func__);
		ret = -ENODEV;
		जाओ put_device;
	पूर्ण

	ocram_base = gen_pool_alloc(ocram_pool, socfpga_sdram_self_refresh_sz);
	अगर (!ocram_base) अणु
		pr_warn("%s: unable to alloc ocram!\n", __func__);
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण

	ocram_pbase = gen_pool_virt_to_phys(ocram_pool, ocram_base);

	suspend_ocram_base = __arm_ioremap_exec(ocram_pbase,
						socfpga_sdram_self_refresh_sz,
						false);
	अगर (!suspend_ocram_base) अणु
		pr_warn("%s: __arm_ioremap_exec failed!\n", __func__);
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण

	/* Copy the code that माला_दो DDR in self refresh to ocram */
	socfpga_sdram_self_refresh_in_ocram =
		(व्योम *)fncpy(suspend_ocram_base,
			      &socfpga_sdram_self_refresh,
			      socfpga_sdram_self_refresh_sz);

	WARN(!socfpga_sdram_self_refresh_in_ocram,
	     "could not copy function to ocram");
	अगर (!socfpga_sdram_self_refresh_in_ocram)
		ret = -EFAULT;

put_device:
	put_device(&pdev->dev);
put_node:
	of_node_put(np);

	वापस ret;
पूर्ण

अटल पूर्णांक socfpga_pm_suspend(अचिन्हित दीर्घ arg)
अणु
	u32 ret;

	अगर (!sdr_ctl_base_addr)
		वापस -EFAULT;

	ret = socfpga_sdram_self_refresh_in_ocram((u32)sdr_ctl_base_addr);

	pr_debug("%s self-refresh loops request=%d exit=%d\n", __func__,
		 ret & 0xffff, (ret >> 16) & 0xffff);

	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_pm_enter(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		outer_disable();
		cpu_suspend(0, socfpga_pm_suspend);
		outer_resume();
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops socfpga_pm_ops = अणु
	.valid	= suspend_valid_only_mem,
	.enter	= socfpga_pm_enter,
पूर्ण;

अटल पूर्णांक __init socfpga_pm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = socfpga_setup_ocram_self_refresh();
	अगर (ret)
		वापस ret;

	suspend_set_ops(&socfpga_pm_ops);
	pr_info("SoCFPGA initialized for DDR self-refresh during suspend.\n");

	वापस 0;
पूर्ण
arch_initcall(socfpga_pm_init);
