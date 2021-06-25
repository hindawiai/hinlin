<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Spin Table SMP initialisation
 *
 * Copyright (C) 2013 ARM Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp_plat.h>

बाह्य व्योम secondary_holding_pen(व्योम);
अस्थिर अचिन्हित दीर्घ __section(".mmuoff.data.read")
secondary_holding_pen_release = INVALID_HWID;

अटल phys_addr_t cpu_release_addr[NR_CPUS];

/*
 * Write secondary_holding_pen_release in a way that is guaranteed to be
 * visible to all observers, irrespective of whether they're taking part
 * in coherency or not.  This is necessary क्रम the hotplug code to work
 * reliably.
 */
अटल व्योम ग_लिखो_pen_release(u64 val)
अणु
	व्योम *start = (व्योम *)&secondary_holding_pen_release;
	अचिन्हित दीर्घ size = माप(secondary_holding_pen_release);

	secondary_holding_pen_release = val;
	__flush_dcache_area(start, size);
पूर्ण


अटल पूर्णांक smp_spin_table_cpu_init(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device_node *dn;
	पूर्णांक ret;

	dn = of_get_cpu_node(cpu, शून्य);
	अगर (!dn)
		वापस -ENODEV;

	/*
	 * Determine the address from which the CPU is polling.
	 */
	ret = of_property_पढ़ो_u64(dn, "cpu-release-addr",
				   &cpu_release_addr[cpu]);
	अगर (ret)
		pr_err("CPU %d: missing or invalid cpu-release-addr property\n",
		       cpu);

	of_node_put(dn);

	वापस ret;
पूर्ण

अटल पूर्णांक smp_spin_table_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	__le64 __iomem *release_addr;
	phys_addr_t pa_holding_pen = __pa_symbol(function_nocfi(secondary_holding_pen));

	अगर (!cpu_release_addr[cpu])
		वापस -ENODEV;

	/*
	 * The cpu-release-addr may or may not be inside the linear mapping.
	 * As ioremap_cache will either give us a new mapping or reuse the
	 * existing linear mapping, we can use it to cover both हालs. In
	 * either हाल the memory will be MT_NORMAL.
	 */
	release_addr = ioremap_cache(cpu_release_addr[cpu],
				     माप(*release_addr));
	अगर (!release_addr)
		वापस -ENOMEM;

	/*
	 * We ग_लिखो the release address as LE regardless of the native
	 * endianness of the kernel. Thereक्रमe, any boot-loaders that
	 * पढ़ो this address need to convert this address to the
	 * boot-loader's endianness beक्रमe jumping. This is mandated by
	 * the boot protocol.
	 */
	ग_लिखोq_relaxed(pa_holding_pen, release_addr);
	__flush_dcache_area((__क्रमce व्योम *)release_addr,
			    माप(*release_addr));

	/*
	 * Send an event to wake up the secondary CPU.
	 */
	sev();

	iounmap(release_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक smp_spin_table_cpu_boot(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Update the pen release flag.
	 */
	ग_लिखो_pen_release(cpu_logical_map(cpu));

	/*
	 * Send an event, causing the secondaries to पढ़ो pen_release.
	 */
	sev();

	वापस 0;
पूर्ण

स्थिर काष्ठा cpu_operations smp_spin_table_ops = अणु
	.name		= "spin-table",
	.cpu_init	= smp_spin_table_cpu_init,
	.cpu_prepare	= smp_spin_table_cpu_prepare,
	.cpu_boot	= smp_spin_table_cpu_boot,
पूर्ण;
