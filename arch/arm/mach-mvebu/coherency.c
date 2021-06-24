<शैली गुरु>
/*
 * Coherency fabric (Aurora) support क्रम Armada 370, 375, 38x and XP
 * platक्रमms.
 *
 * Copyright (C) 2012 Marvell
 *
 * Yehuda Yitschak <yehuday@marvell.com>
 * Gregory Clement <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * The Armada 370, 375, 38x and XP SOCs have a coherency fabric which is
 * responsible क्रम ensuring hardware coherency between all CPUs and between
 * CPUs and I/O masters. This file initializes the coherency fabric and
 * supplies basic routines क्रम configuring and controlling hardware coherency
 */

#घोषणा pr_fmt(fmt) "mvebu-coherency: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/smp.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mbus.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/dma-mapping.h>
#समावेश "coherency.h"
#समावेश "mvebu-soc-id.h"

अचिन्हित दीर्घ coherency_phys_base;
व्योम __iomem *coherency_base;
अटल व्योम __iomem *coherency_cpu_base;
अटल व्योम __iomem *cpu_config_base;

/* Coherency fabric रेजिस्टरs */
#घोषणा IO_SYNC_BARRIER_CTL_OFFSET		   0x0

क्रमागत अणु
	COHERENCY_FABRIC_TYPE_NONE,
	COHERENCY_FABRIC_TYPE_ARMADA_370_XP,
	COHERENCY_FABRIC_TYPE_ARMADA_375,
	COHERENCY_FABRIC_TYPE_ARMADA_380,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_coherency_table[] = अणु
	अणु.compatible = "marvell,coherency-fabric",
	 .data = (व्योम *) COHERENCY_FABRIC_TYPE_ARMADA_370_XP पूर्ण,
	अणु.compatible = "marvell,armada-375-coherency-fabric",
	 .data = (व्योम *) COHERENCY_FABRIC_TYPE_ARMADA_375 पूर्ण,
	अणु.compatible = "marvell,armada-380-coherency-fabric",
	 .data = (व्योम *) COHERENCY_FABRIC_TYPE_ARMADA_380 पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

/* Functions defined in coherency_ll.S */
पूर्णांक ll_enable_coherency(व्योम);
व्योम ll_add_cpu_to_smp_group(व्योम);

#घोषणा CPU_CONFIG_SHARED_L2 BIT(16)

/*
 * Disable the "Shared L2 Present" bit in CPU Configuration रेजिस्टर
 * on Armada XP.
 *
 * The "Shared L2 Present" bit affects the "level of coherence" value
 * in the clidr CP15 रेजिस्टर.  Cache operation functions such as
 * "flush all" and "invalidate all" operate on all the cache levels
 * that included in the defined level of coherence. When HW I/O
 * coherency is used, this bit causes unnecessary flushes of the L2
 * cache.
 */
अटल व्योम armada_xp_clear_shared_l2(व्योम)
अणु
	u32 reg;

	अगर (!cpu_config_base)
		वापस;

	reg = पढ़ोl(cpu_config_base);
	reg &= ~CPU_CONFIG_SHARED_L2;
	ग_लिखोl(reg, cpu_config_base);
पूर्ण

अटल पूर्णांक mvebu_hwcc_notअगरier(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event, व्योम *__dev)
अणु
	काष्ठा device *dev = __dev;

	अगर (event != BUS_NOTIFY_ADD_DEVICE)
		वापस NOTIFY_DONE;
	set_dma_ops(dev, &arm_coherent_dma_ops);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mvebu_hwcc_nb = अणु
	.notअगरier_call = mvebu_hwcc_notअगरier,
पूर्ण;

अटल काष्ठा notअगरier_block mvebu_hwcc_pci_nb __maybe_unused = अणु
	.notअगरier_call = mvebu_hwcc_notअगरier,
पूर्ण;

अटल पूर्णांक armada_xp_clear_l2_starting(अचिन्हित पूर्णांक cpu)
अणु
	armada_xp_clear_shared_l2();
	वापस 0;
पूर्ण

अटल व्योम __init armada_370_coherency_init(काष्ठा device_node *np)
अणु
	काष्ठा resource res;
	काष्ठा device_node *cpu_config_np;

	of_address_to_resource(np, 0, &res);
	coherency_phys_base = res.start;
	/*
	 * Ensure secondary CPUs will see the updated value,
	 * which they पढ़ो beक्रमe they join the coherency
	 * fabric, and thereक्रमe beक्रमe they are coherent with
	 * the boot CPU cache.
	 */
	sync_cache_w(&coherency_phys_base);
	coherency_base = of_iomap(np, 0);
	coherency_cpu_base = of_iomap(np, 1);

	cpu_config_np = of_find_compatible_node(शून्य, शून्य,
						"marvell,armada-xp-cpu-config");
	अगर (!cpu_config_np)
		जाओ निकास;

	cpu_config_base = of_iomap(cpu_config_np, 0);
	अगर (!cpu_config_base) अणु
		of_node_put(cpu_config_np);
		जाओ निकास;
	पूर्ण

	of_node_put(cpu_config_np);

	cpuhp_setup_state_nocalls(CPUHP_AP_ARM_MVEBU_COHERENCY,
				  "arm/mvebu/coherency:starting",
				  armada_xp_clear_l2_starting, शून्य);
निकास:
	set_cpu_coherent();
पूर्ण

/*
 * This ioremap hook is used on Armada 375/38x to ensure that all MMIO
 * areas are mapped as MT_UNCACHED instead of MT_DEVICE. This is
 * needed क्रम the HW I/O coherency mechanism to work properly without
 * deadlock.
 */
अटल व्योम __iomem *
armada_wa_ioremap_caller(phys_addr_t phys_addr, माप_प्रकार size,
			 अचिन्हित पूर्णांक mtype, व्योम *caller)
अणु
	mtype = MT_UNCACHED;
	वापस __arm_ioremap_caller(phys_addr, size, mtype, caller);
पूर्ण

अटल व्योम __init armada_375_380_coherency_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *cache_dn;

	coherency_cpu_base = of_iomap(np, 0);
	arch_ioremap_caller = armada_wa_ioremap_caller;
	pci_ioremap_set_mem_type(MT_UNCACHED);

	/*
	 * We should चयन the PL310 to I/O coherency mode only अगर
	 * I/O coherency is actually enabled.
	 */
	अगर (!coherency_available())
		वापस;

	/*
	 * Add the PL310 property "arm,io-coherent". This makes sure the
	 * outer sync operation is not used, which allows to
	 * workaround the प्रणाली erratum that causes deadlocks when
	 * करोing PCIe in an SMP situation on Armada 375 and Armada
	 * 38x.
	 */
	क्रम_each_compatible_node(cache_dn, शून्य, "arm,pl310-cache") अणु
		काष्ठा property *p;

		p = kzalloc(माप(*p), GFP_KERNEL);
		p->name = kstrdup("arm,io-coherent", GFP_KERNEL);
		of_add_property(cache_dn, p);
	पूर्ण
पूर्ण

अटल पूर्णांक coherency_type(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक type;

	/*
	 * The coherency fabric is needed:
	 * - For coherency between processors on Armada XP, so only
	 *   when SMP is enabled.
	 * - For coherency between the processor and I/O devices, but
	 *   this coherency requires many pre-requisites (ग_लिखो
	 *   allocate cache policy, shareable pages, SMP bit set) that
	 *   are only meant in SMP situations.
	 *
	 * Note that this means that on Armada 370, there is currently
	 * no way to use hardware I/O coherency, because even when
	 * CONFIG_SMP is enabled, is_smp() वापसs false due to the
	 * Armada 370 being a single-core processor. To lअगरt this
	 * limitation, we would have to find a way to make the cache
	 * policy set to ग_लिखो-allocate (on all Armada SoCs), and to
	 * set the shareable attribute in page tables (on all Armada
	 * SoCs except the Armada 370). Unक्रमtunately, such decisions
	 * are taken very early in the kernel boot process, at a poपूर्णांक
	 * where we करोn't know yet on which SoC we are running.

	 */
	अगर (!is_smp())
		वापस COHERENCY_FABRIC_TYPE_NONE;

	np = of_find_matching_node_and_match(शून्य, of_coherency_table, &match);
	अगर (!np)
		वापस COHERENCY_FABRIC_TYPE_NONE;

	type = (पूर्णांक) match->data;

	of_node_put(np);

	वापस type;
पूर्ण

पूर्णांक set_cpu_coherent(व्योम)
अणु
	पूर्णांक type = coherency_type();

	अगर (type == COHERENCY_FABRIC_TYPE_ARMADA_370_XP) अणु
		अगर (!coherency_base) अणु
			pr_warn("Can't make current CPU cache coherent.\n");
			pr_warn("Coherency fabric is not initialized\n");
			वापस 1;
		पूर्ण

		armada_xp_clear_shared_l2();
		ll_add_cpu_to_smp_group();
		वापस ll_enable_coherency();
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक coherency_available(व्योम)
अणु
	वापस coherency_type() != COHERENCY_FABRIC_TYPE_NONE;
पूर्ण

पूर्णांक __init coherency_init(व्योम)
अणु
	पूर्णांक type = coherency_type();
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, of_coherency_table);

	अगर (type == COHERENCY_FABRIC_TYPE_ARMADA_370_XP)
		armada_370_coherency_init(np);
	अन्यथा अगर (type == COHERENCY_FABRIC_TYPE_ARMADA_375 ||
		 type == COHERENCY_FABRIC_TYPE_ARMADA_380)
		armada_375_380_coherency_init(np);

	of_node_put(np);

	वापस 0;
पूर्ण

अटल पूर्णांक __init coherency_late_init(व्योम)
अणु
	अगर (coherency_available())
		bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type,
				      &mvebu_hwcc_nb);
	वापस 0;
पूर्ण

postcore_initcall(coherency_late_init);

#अगर IS_ENABLED(CONFIG_PCI)
अटल पूर्णांक __init coherency_pci_init(व्योम)
अणु
	अगर (coherency_available())
		bus_रेजिस्टर_notअगरier(&pci_bus_type,
				       &mvebu_hwcc_pci_nb);
	वापस 0;
पूर्ण

arch_initcall(coherency_pci_init);
#पूर्ण_अगर
