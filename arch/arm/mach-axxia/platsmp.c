<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-axxia/platsmp.c
 *
 * Copyright (C) 2012 LSI Corporation
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/smp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/cacheflush.h>

/* Syscon रेजिस्टर offsets क्रम releasing cores from reset */
#घोषणा SC_CRIT_WRITE_KEY	0x1000
#घोषणा SC_RST_CPU_HOLD		0x1010

/*
 * Write the kernel entry poपूर्णांक क्रम secondary CPUs to the specअगरied address
 */
अटल व्योम ग_लिखो_release_addr(u32 release_phys)
अणु
	u32 *virt = (u32 *) phys_to_virt(release_phys);
	ग_लिखोl_relaxed(__pa_symbol(secondary_startup), virt);
	/* Make sure this store is visible to other CPUs */
	smp_wmb();
	__cpuc_flush_dcache_area(virt, माप(u32));
पूर्ण

अटल पूर्णांक axxia_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा device_node *syscon_np;
	व्योम __iomem *syscon;
	u32 पंचांगp;

	syscon_np = of_find_compatible_node(शून्य, शून्य, "lsi,axxia-syscon");
	अगर (!syscon_np)
		वापस -ENOENT;

	syscon = of_iomap(syscon_np, 0);
	अगर (!syscon)
		वापस -ENOMEM;

	पंचांगp = पढ़ोl(syscon + SC_RST_CPU_HOLD);
	ग_लिखोl(0xab, syscon + SC_CRIT_WRITE_KEY);
	पंचांगp &= ~(1 << cpu);
	ग_लिखोl(पंचांगp, syscon + SC_RST_CPU_HOLD);

	वापस 0;
पूर्ण

अटल व्योम __init axxia_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक cpu_count = 0;
	पूर्णांक cpu;

	/*
	 * Initialise the present map, which describes the set of CPUs actually
	 * populated at the present समय.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा device_node *np;
		u32 release_phys;

		np = of_get_cpu_node(cpu, शून्य);
		अगर (!np)
			जारी;
		अगर (of_property_पढ़ो_u32(np, "cpu-release-addr", &release_phys))
			जारी;

		अगर (cpu_count < max_cpus) अणु
			set_cpu_present(cpu, true);
			cpu_count++;
		पूर्ण

		अगर (release_phys != 0)
			ग_लिखो_release_addr(release_phys);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा smp_operations axxia_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= axxia_smp_prepare_cpus,
	.smp_boot_secondary	= axxia_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(axxia_smp, "lsi,syscon-release", &axxia_smp_ops);
