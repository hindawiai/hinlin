<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SDK7786 FPGA SRAM Support.
 *
 * Copyright (C) 2010  Paul Mundt
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/माला.स>
#समावेश <mach/fpga.h>
#समावेश <यंत्र/sram.h>
#समावेश <linux/sizes.h>

अटल पूर्णांक __init fpga_sram_init(व्योम)
अणु
	अचिन्हित दीर्घ phys;
	अचिन्हित पूर्णांक area;
	व्योम __iomem *vaddr;
	पूर्णांक ret;
	u16 data;

	/* Enable FPGA SRAM */
	data = fpga_पढ़ो_reg(LCLASR);
	data |= LCLASR_FRAMEN;
	fpga_ग_लिखो_reg(data, LCLASR);

	/*
	 * FPGA_SEL determines the area mapping
	 */
	area = (data & LCLASR_FPGA_SEL_MASK) >> LCLASR_FPGA_SEL_SHIFT;
	अगर (unlikely(area == LCLASR_AREA_MASK)) अणु
		pr_err("FPGA memory unmapped.\n");
		वापस -ENXIO;
	पूर्ण

	/*
	 * The memory itself occupies a 2KiB range at the top of the area
	 * immediately below the प्रणाली रेजिस्टरs.
	 */
	phys = (area << 26) + SZ_64M - SZ_4K;

	/*
	 * The FPGA SRAM resides in translatable physical space, so set
	 * up a mapping prior to inserting it in to the pool.
	 */
	vaddr = ioremap(phys, SZ_2K);
	अगर (unlikely(!vaddr)) अणु
		pr_err("Failed remapping FPGA memory.\n");
		वापस -ENXIO;
	पूर्ण

	pr_info("Adding %dKiB of FPGA memory at 0x%08lx-0x%08lx "
		"(area %d) to pool.\n",
		SZ_2K >> 10, phys, phys + SZ_2K - 1, area);

	ret = gen_pool_add(sram_pool, (अचिन्हित दीर्घ)vaddr, SZ_2K, -1);
	अगर (unlikely(ret < 0)) अणु
		pr_err("Failed adding memory\n");
		iounmap(vaddr);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(fpga_sram_init);
