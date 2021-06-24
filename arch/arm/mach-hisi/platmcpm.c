<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014 Linaro Ltd.
 * Copyright (c) 2013-2014 HiSilicon Limited.
 */
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/smp_plat.h>

#समावेश "core.h"

/* bits definition in SC_CPU_RESET_REQ[x]/SC_CPU_RESET_DREQ[x]
 * 1 -- unreset; 0 -- reset
 */
#घोषणा CORE_RESET_BIT(x)		(1 << x)
#घोषणा NEON_RESET_BIT(x)		(1 << (x + 4))
#घोषणा CORE_DEBUG_RESET_BIT(x)		(1 << (x + 9))
#घोषणा CLUSTER_L2_RESET_BIT		(1 << 8)
#घोषणा CLUSTER_DEBUG_RESET_BIT		(1 << 13)

/*
 * bits definition in SC_CPU_RESET_STATUS[x]
 * 1 -- reset status; 0 -- unreset status
 */
#घोषणा CORE_RESET_STATUS(x)		(1 << x)
#घोषणा NEON_RESET_STATUS(x)		(1 << (x + 4))
#घोषणा CORE_DEBUG_RESET_STATUS(x)	(1 << (x + 9))
#घोषणा CLUSTER_L2_RESET_STATUS		(1 << 8)
#घोषणा CLUSTER_DEBUG_RESET_STATUS	(1 << 13)
#घोषणा CORE_WFI_STATUS(x)		(1 << (x + 16))
#घोषणा CORE_WFE_STATUS(x)		(1 << (x + 20))
#घोषणा CORE_DEBUG_ACK(x)		(1 << (x + 24))

#घोषणा SC_CPU_RESET_REQ(x)		(0x520 + (x << 3))	/* reset */
#घोषणा SC_CPU_RESET_DREQ(x)		(0x524 + (x << 3))	/* unreset */
#घोषणा SC_CPU_RESET_STATUS(x)		(0x1520 + (x << 3))

#घोषणा FAB_SF_MODE			0x0c
#घोषणा FAB_SF_INVLD			0x10

/* bits definition in FB_SF_INVLD */
#घोषणा FB_SF_INVLD_START		(1 << 8)

#घोषणा HIP04_MAX_CLUSTERS		4
#घोषणा HIP04_MAX_CPUS_PER_CLUSTER	4

#घोषणा POLL_MSEC	10
#घोषणा TIMEOUT_MSEC	1000

अटल व्योम __iomem *sysctrl, *fabric;
अटल पूर्णांक hip04_cpu_table[HIP04_MAX_CLUSTERS][HIP04_MAX_CPUS_PER_CLUSTER];
अटल DEFINE_SPINLOCK(boot_lock);
अटल u32 fabric_phys_addr;
/*
 * [0]: bootwrapper physical address
 * [1]: bootwrapper size
 * [2]: relocation address
 * [3]: relocation size
 */
अटल u32 hip04_boot_method[4];

अटल bool hip04_cluster_is_करोwn(अचिन्हित पूर्णांक cluster)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HIP04_MAX_CPUS_PER_CLUSTER; i++)
		अगर (hip04_cpu_table[cluster][i])
			वापस false;
	वापस true;
पूर्ण

अटल व्योम hip04_set_snoop_filter(अचिन्हित पूर्णांक cluster, अचिन्हित पूर्णांक on)
अणु
	अचिन्हित दीर्घ data;

	अगर (!fabric)
		BUG();
	data = पढ़ोl_relaxed(fabric + FAB_SF_MODE);
	अगर (on)
		data |= 1 << cluster;
	अन्यथा
		data &= ~(1 << cluster);
	ग_लिखोl_relaxed(data, fabric + FAB_SF_MODE);
	करो अणु
		cpu_relax();
	पूर्ण जबतक (data != पढ़ोl_relaxed(fabric + FAB_SF_MODE));
पूर्ण

अटल पूर्णांक hip04_boot_secondary(अचिन्हित पूर्णांक l_cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	अचिन्हित दीर्घ data;
	व्योम __iomem *sys_dreq, *sys_status;

	mpidr = cpu_logical_map(l_cpu);
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	अगर (!sysctrl)
		वापस -ENODEV;
	अगर (cluster >= HIP04_MAX_CLUSTERS || cpu >= HIP04_MAX_CPUS_PER_CLUSTER)
		वापस -EINVAL;

	spin_lock_irq(&boot_lock);

	अगर (hip04_cpu_table[cluster][cpu])
		जाओ out;

	sys_dreq = sysctrl + SC_CPU_RESET_DREQ(cluster);
	sys_status = sysctrl + SC_CPU_RESET_STATUS(cluster);
	अगर (hip04_cluster_is_करोwn(cluster)) अणु
		data = CLUSTER_DEBUG_RESET_BIT;
		ग_लिखोl_relaxed(data, sys_dreq);
		करो अणु
			cpu_relax();
			data = पढ़ोl_relaxed(sys_status);
		पूर्ण जबतक (data & CLUSTER_DEBUG_RESET_STATUS);
		hip04_set_snoop_filter(cluster, 1);
	पूर्ण

	data = CORE_RESET_BIT(cpu) | NEON_RESET_BIT(cpu) | \
	       CORE_DEBUG_RESET_BIT(cpu);
	ग_लिखोl_relaxed(data, sys_dreq);
	करो अणु
		cpu_relax();
	पूर्ण जबतक (data == पढ़ोl_relaxed(sys_status));

	/*
	 * We may fail to घातer up core again without this delay.
	 * It's not mentioned in document. It's found by test.
	 */
	udelay(20);

	arch_send_wakeup_ipi_mask(cpumask_of(l_cpu));

out:
	hip04_cpu_table[cluster][cpu]++;
	spin_unlock_irq(&boot_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम hip04_cpu_die(अचिन्हित पूर्णांक l_cpu)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	bool last_man;

	mpidr = cpu_logical_map(l_cpu);
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	spin_lock(&boot_lock);
	hip04_cpu_table[cluster][cpu]--;
	अगर (hip04_cpu_table[cluster][cpu] == 1) अणु
		/* A घातer_up request went ahead of us. */
		spin_unlock(&boot_lock);
		वापस;
	पूर्ण अन्यथा अगर (hip04_cpu_table[cluster][cpu] > 1) अणु
		pr_err("Cluster %d CPU%d boots multiple times\n", cluster, cpu);
		BUG();
	पूर्ण

	last_man = hip04_cluster_is_करोwn(cluster);
	spin_unlock(&boot_lock);
	अगर (last_man) अणु
		/* Since it's Cortex A15, disable L2 prefetching. */
		यंत्र अस्थिर(
		"mcr	p15, 1, %0, c15, c0, 3 \n\t"
		"isb	\n\t"
		"dsb	"
		: : "r" (0x400) );
		v7_निकास_coherency_flush(all);
	पूर्ण अन्यथा अणु
		v7_निकास_coherency_flush(louis);
	पूर्ण

	क्रम (;;)
		wfi();
पूर्ण

अटल पूर्णांक hip04_cpu_समाप्त(अचिन्हित पूर्णांक l_cpu)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	अचिन्हित पूर्णांक data, tries, count;

	mpidr = cpu_logical_map(l_cpu);
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	BUG_ON(cluster >= HIP04_MAX_CLUSTERS ||
	       cpu >= HIP04_MAX_CPUS_PER_CLUSTER);

	count = TIMEOUT_MSEC / POLL_MSEC;
	spin_lock_irq(&boot_lock);
	क्रम (tries = 0; tries < count; tries++) अणु
		अगर (hip04_cpu_table[cluster][cpu])
			जाओ err;
		cpu_relax();
		data = पढ़ोl_relaxed(sysctrl + SC_CPU_RESET_STATUS(cluster));
		अगर (data & CORE_WFI_STATUS(cpu))
			अवरोध;
		spin_unlock_irq(&boot_lock);
		/* Wait क्रम clean L2 when the whole cluster is करोwn. */
		msleep(POLL_MSEC);
		spin_lock_irq(&boot_lock);
	पूर्ण
	अगर (tries >= count)
		जाओ err;
	data = CORE_RESET_BIT(cpu) | NEON_RESET_BIT(cpu) | \
	       CORE_DEBUG_RESET_BIT(cpu);
	ग_लिखोl_relaxed(data, sysctrl + SC_CPU_RESET_REQ(cluster));
	क्रम (tries = 0; tries < count; tries++) अणु
		cpu_relax();
		data = पढ़ोl_relaxed(sysctrl + SC_CPU_RESET_STATUS(cluster));
		अगर (data & CORE_RESET_STATUS(cpu))
			अवरोध;
	पूर्ण
	अगर (tries >= count)
		जाओ err;
	अगर (hip04_cluster_is_करोwn(cluster))
		hip04_set_snoop_filter(cluster, 0);
	spin_unlock_irq(&boot_lock);
	वापस 1;
err:
	spin_unlock_irq(&boot_lock);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations hip04_smp_ops __initस्थिर = अणु
	.smp_boot_secondary	= hip04_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= hip04_cpu_die,
	.cpu_समाप्त		= hip04_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

अटल bool __init hip04_cpu_table_init(व्योम)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;

	mpidr = पढ़ो_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	अगर (cluster >= HIP04_MAX_CLUSTERS ||
	    cpu >= HIP04_MAX_CPUS_PER_CLUSTER) अणु
		pr_err("%s: boot CPU is out of bound!\n", __func__);
		वापस false;
	पूर्ण
	hip04_set_snoop_filter(cluster, 1);
	hip04_cpu_table[cluster][cpu] = 1;
	वापस true;
पूर्ण

अटल पूर्णांक __init hip04_smp_init(व्योम)
अणु
	काष्ठा device_node *np, *np_sctl, *np_fab;
	काष्ठा resource fab_res;
	व्योम __iomem *relocation;
	पूर्णांक ret = -ENODEV;

	np = of_find_compatible_node(शून्य, शून्य, "hisilicon,hip04-bootwrapper");
	अगर (!np)
		जाओ err;
	ret = of_property_पढ़ो_u32_array(np, "boot-method",
					 &hip04_boot_method[0], 4);
	अगर (ret)
		जाओ err;

	ret = -ENODEV;
	np_sctl = of_find_compatible_node(शून्य, शून्य, "hisilicon,sysctrl");
	अगर (!np_sctl)
		जाओ err;
	np_fab = of_find_compatible_node(शून्य, शून्य, "hisilicon,hip04-fabric");
	अगर (!np_fab)
		जाओ err;

	ret = memblock_reserve(hip04_boot_method[0], hip04_boot_method[1]);
	अगर (ret)
		जाओ err;

	relocation = ioremap(hip04_boot_method[2], hip04_boot_method[3]);
	अगर (!relocation) अणु
		pr_err("failed to map relocation space\n");
		ret = -ENOMEM;
		जाओ err_reloc;
	पूर्ण
	sysctrl = of_iomap(np_sctl, 0);
	अगर (!sysctrl) अणु
		pr_err("failed to get sysctrl base\n");
		ret = -ENOMEM;
		जाओ err_sysctrl;
	पूर्ण
	ret = of_address_to_resource(np_fab, 0, &fab_res);
	अगर (ret) अणु
		pr_err("failed to get fabric base phys\n");
		जाओ err_fabric;
	पूर्ण
	fabric_phys_addr = fab_res.start;
	sync_cache_w(&fabric_phys_addr);
	fabric = of_iomap(np_fab, 0);
	अगर (!fabric) अणु
		pr_err("failed to get fabric base\n");
		ret = -ENOMEM;
		जाओ err_fabric;
	पूर्ण

	अगर (!hip04_cpu_table_init()) अणु
		ret = -EINVAL;
		जाओ err_table;
	पूर्ण

	/*
	 * Fill the inकाष्ठाion address that is used after secondary core
	 * out of reset.
	 */
	ग_लिखोl_relaxed(hip04_boot_method[0], relocation);
	ग_लिखोl_relaxed(0xa5a5a5a5, relocation + 4);	/* magic number */
	ग_लिखोl_relaxed(__pa_symbol(secondary_startup), relocation + 8);
	ग_लिखोl_relaxed(0, relocation + 12);
	iounmap(relocation);

	smp_set_ops(&hip04_smp_ops);
	वापस ret;
err_table:
	iounmap(fabric);
err_fabric:
	iounmap(sysctrl);
err_sysctrl:
	iounmap(relocation);
err_reloc:
	memblock_मुक्त(hip04_boot_method[0], hip04_boot_method[1]);
err:
	वापस ret;
पूर्ण
early_initcall(hip04_smp_init);
