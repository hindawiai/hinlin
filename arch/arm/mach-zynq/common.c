<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains common code that is पूर्णांकended to be used across
 * boards so that it's not replicated.
 *
 *  Copyright (C) 2011 Xilinx
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk/zynq.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of.h>
#समावेश <linux/memblock.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश "common.h"

#घोषणा ZYNQ_DEVCFG_MCTRL		0x80
#घोषणा ZYNQ_DEVCFG_PS_VERSION_SHIFT	28
#घोषणा ZYNQ_DEVCFG_PS_VERSION_MASK	0xF

व्योम __iomem *zynq_scu_base;

/**
 * zynq_memory_init - Initialize special memory
 *
 * We need to stop things allocating the low memory as DMA can't work in
 * the 1st 512K of memory.
 */
अटल व्योम __init zynq_memory_init(व्योम)
अणु
	अगर (!__pa(PAGE_OFFSET))
		memblock_reserve(__pa(PAGE_OFFSET), 0x80000);
पूर्ण

अटल काष्ठा platक्रमm_device zynq_cpuidle_device = अणु
	.name = "cpuidle-zynq",
पूर्ण;

/**
 * zynq_get_revision - Get Zynq silicon revision
 *
 * Return: Silicon version or -1 otherwise
 */
अटल पूर्णांक __init zynq_get_revision(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *zynq_devcfg_base;
	u32 revision;

	np = of_find_compatible_node(शून्य, शून्य, "xlnx,zynq-devcfg-1.0");
	अगर (!np) अणु
		pr_err("%s: no devcfg node found\n", __func__);
		वापस -1;
	पूर्ण

	zynq_devcfg_base = of_iomap(np, 0);
	अगर (!zynq_devcfg_base) अणु
		pr_err("%s: Unable to map I/O memory\n", __func__);
		वापस -1;
	पूर्ण

	revision = पढ़ोl(zynq_devcfg_base + ZYNQ_DEVCFG_MCTRL);
	revision >>= ZYNQ_DEVCFG_PS_VERSION_SHIFT;
	revision &= ZYNQ_DEVCFG_PS_VERSION_MASK;

	iounmap(zynq_devcfg_base);

	वापस revision;
पूर्ण

अटल व्योम __init zynq_init_late(व्योम)
अणु
	zynq_core_pm_init();
	zynq_pm_late_init();
पूर्ण

/**
 * zynq_init_machine - System specअगरic initialization, पूर्णांकended to be
 *		       called from board specअगरic initialization.
 */
अटल व्योम __init zynq_init_machine(व्योम)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा soc_device *soc_dev;
	काष्ठा device *parent = शून्य;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		जाओ out;

	प्रणाली_rev = zynq_get_revision();

	soc_dev_attr->family = kaप्र_लिखो(GFP_KERNEL, "Xilinx Zynq");
	soc_dev_attr->revision = kaप्र_लिखो(GFP_KERNEL, "0x%x", प्रणाली_rev);
	soc_dev_attr->soc_id = kaप्र_लिखो(GFP_KERNEL, "0x%x",
					 zynq_slcr_get_device_id());

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr->family);
		kमुक्त(soc_dev_attr->revision);
		kमुक्त(soc_dev_attr->soc_id);
		kमुक्त(soc_dev_attr);
		जाओ out;
	पूर्ण

	parent = soc_device_to_device(soc_dev);

out:
	/*
	 * Finished with the अटल registrations now; fill in the missing
	 * devices
	 */
	of_platक्रमm_शेष_populate(शून्य, शून्य, parent);

	platक्रमm_device_रेजिस्टर(&zynq_cpuidle_device);
पूर्ण

अटल व्योम __init zynq_समयr_init(व्योम)
अणु
	zynq_घड़ी_init();
	of_clk_init(शून्य);
	समयr_probe();
पूर्ण

अटल काष्ठा map_desc zynq_cortex_a9_scu_map __initdata = अणु
	.length	= SZ_256,
	.type	= MT_DEVICE,
पूर्ण;

अटल व्योम __init zynq_scu_map_io(व्योम)
अणु
	अचिन्हित दीर्घ base;

	base = scu_a9_get_base();
	zynq_cortex_a9_scu_map.pfn = __phys_to_pfn(base);
	/* Expected address is in vदो_स्मृति area that's why simple assign here */
	zynq_cortex_a9_scu_map.भव = base;
	iotable_init(&zynq_cortex_a9_scu_map, 1);
	zynq_scu_base = (व्योम __iomem *)base;
	BUG_ON(!zynq_scu_base);
पूर्ण

/**
 * zynq_map_io - Create memory mappings needed क्रम early I/O.
 */
अटल व्योम __init zynq_map_io(व्योम)
अणु
	debug_ll_io_init();
	zynq_scu_map_io();
पूर्ण

अटल व्योम __init zynq_irq_init(व्योम)
अणु
	zynq_early_slcr_init();
	irqchip_init();
पूर्ण

अटल स्थिर अक्षर * स्थिर zynq_dt_match[] = अणु
	"xlnx,zynq-7000",
	शून्य
पूर्ण;

DT_MACHINE_START(XILINX_EP107, "Xilinx Zynq Platform")
	/* 64KB way size, 8-way associativity, parity disabled */
	.l2c_aux_val    = 0x00400000,
	.l2c_aux_mask	= 0xffbfffff,
	.smp		= smp_ops(zynq_smp_ops),
	.map_io		= zynq_map_io,
	.init_irq	= zynq_irq_init,
	.init_machine	= zynq_init_machine,
	.init_late	= zynq_init_late,
	.init_समय	= zynq_समयr_init,
	.dt_compat	= zynq_dt_match,
	.reserve	= zynq_memory_init,
MACHINE_END
