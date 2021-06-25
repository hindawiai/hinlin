<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car Generation 2 Power management support
 *
 * Copyright (C) 2013 - 2015  Renesas Electronics Corporation
 * Copyright (C) 2011  Renesas Solutions Corp.
 * Copyright (C) 2011  Magnus Damm
 */

#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cputype.h>
#समावेश "common.h"
#समावेश "rcar-gen2.h"

/* RST */
#घोषणा RST		0xe6160000

#घोषणा CA15BAR		0x0020		/* CA15 Boot Address Register */
#घोषणा CA7BAR		0x0030		/* CA7 Boot Address Register */
#घोषणा CA15RESCNT	0x0040		/* CA15 Reset Control Register */
#घोषणा CA7RESCNT	0x0044		/* CA7 Reset Control Register */

/* SYS Boot Address Register */
#घोषणा SBAR_BAREN	BIT(4)		/* SBAR is valid */

/* Reset Control Registers */
#घोषणा CA15RESCNT_CODE	0xa5a50000
#घोषणा CA15RESCNT_CPUS	0xf		/* CPU0-3 */
#घोषणा CA7RESCNT_CODE	0x5a5a0000
#घोषणा CA7RESCNT_CPUS	0xf		/* CPU0-3 */

/* On-chip RAM */
#घोषणा ICRAM1		0xe63c0000	/* Inter Connect RAM1 (4 KiB) */

अटल अंतरभूत u32 phys_to_sbar(phys_addr_t addr)
अणु
	वापस (addr >> 8) & 0xfffffc00;
पूर्ण

व्योम __init rcar_gen2_pm_init(व्योम)
अणु
	व्योम __iomem *p;
	u32 bar;
	अटल पूर्णांक once;
	काष्ठा device_node *np;
	bool has_a7 = false;
	bool has_a15 = false;
	काष्ठा resource res;
	पूर्णांक error;

	अगर (once++)
		वापस;

	क्रम_each_of_cpu_node(np) अणु
		अगर (of_device_is_compatible(np, "arm,cortex-a15"))
			has_a15 = true;
		अन्यथा अगर (of_device_is_compatible(np, "arm,cortex-a7"))
			has_a7 = true;
	पूर्ण

	np = of_find_compatible_node(शून्य, शून्य, "renesas,smp-sram");
	अगर (!np) अणु
		/* No smp-sram in DT, fall back to hardcoded address */
		res = (काष्ठा resource)DEFINE_RES_MEM(ICRAM1,
						      shmobile_boot_size);
		जाओ map;
	पूर्ण

	error = of_address_to_resource(np, 0, &res);
	of_node_put(np);
	अगर (error) अणु
		pr_err("Failed to get smp-sram address: %d\n", error);
		वापस;
	पूर्ण

map:
	/* RAM क्रम jump stub, because BAR requires 256KB aligned address */
	अगर (res.start & (256 * 1024 - 1) ||
	    resource_size(&res) < shmobile_boot_size) अणु
		pr_err("Invalid smp-sram region\n");
		वापस;
	पूर्ण

	p = ioremap(res.start, resource_size(&res));
	अगर (!p)
		वापस;
	/*
	 * install the reset vector, use the largest version अगर we have enough
	 * memory available
	 */
	अगर (resource_size(&res) >= shmobile_boot_size_gen2) अणु
		shmobile_boot_cpu_gen2 = पढ़ो_cpuid_mpidr();
		स_नकल_toio(p, shmobile_boot_vector_gen2,
			    shmobile_boot_size_gen2);
	पूर्ण अन्यथा अणु
		स_नकल_toio(p, shmobile_boot_vector, shmobile_boot_size);
	पूर्ण
	iounmap(p);

	/* setup reset vectors */
	p = ioremap(RST, 0x63);
	bar = phys_to_sbar(res.start);
	अगर (has_a15) अणु
		ग_लिखोl_relaxed(bar, p + CA15BAR);
		ग_लिखोl_relaxed(bar | SBAR_BAREN, p + CA15BAR);

		/* de-निश्चित reset क्रम CA15 CPUs */
		ग_लिखोl_relaxed((पढ़ोl_relaxed(p + CA15RESCNT) &
				~CA15RESCNT_CPUS) | CA15RESCNT_CODE,
			       p + CA15RESCNT);
	पूर्ण
	अगर (has_a7) अणु
		ग_लिखोl_relaxed(bar, p + CA7BAR);
		ग_लिखोl_relaxed(bar | SBAR_BAREN, p + CA7BAR);

		/* de-निश्चित reset क्रम CA7 CPUs */
		ग_लिखोl_relaxed((पढ़ोl_relaxed(p + CA7RESCNT) &
				~CA7RESCNT_CPUS) | CA7RESCNT_CODE,
			       p + CA7RESCNT);
	पूर्ण
	iounmap(p);

	shmobile_smp_apmu_suspend_init();
पूर्ण
