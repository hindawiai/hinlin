<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip27-irq.c: Highlevel पूर्णांकerrupt handling क्रम IP27 architecture.
 *
 * Copyright (C) 1999, 2000 Ralf Baechle (ralf@gnu.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 1999 - 2001 Kanoj Sarcar
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/पूर्णांकr.h>
#समावेश <यंत्र/sn/irq_भाग.स>

काष्ठा hub_irq_data अणु
	u64	*irq_mask[2];
	cpuid_t	cpu;
पूर्ण;

अटल DECLARE_BITMAP(hub_irq_map, IP27_HUB_IRQ_COUNT);

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ [2], irq_enable_mask);

अटल अंतरभूत पूर्णांक alloc_level(व्योम)
अणु
	पूर्णांक level;

again:
	level = find_first_zero_bit(hub_irq_map, IP27_HUB_IRQ_COUNT);
	अगर (level >= IP27_HUB_IRQ_COUNT)
		वापस -ENOSPC;

	अगर (test_and_set_bit(level, hub_irq_map))
		जाओ again;

	वापस level;
पूर्ण

अटल व्योम enable_hub_irq(काष्ठा irq_data *d)
अणु
	काष्ठा hub_irq_data *hd = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ *mask = per_cpu(irq_enable_mask, hd->cpu);

	set_bit(d->hwirq, mask);
	__raw_ग_लिखोq(mask[0], hd->irq_mask[0]);
	__raw_ग_लिखोq(mask[1], hd->irq_mask[1]);
पूर्ण

अटल व्योम disable_hub_irq(काष्ठा irq_data *d)
अणु
	काष्ठा hub_irq_data *hd = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ *mask = per_cpu(irq_enable_mask, hd->cpu);

	clear_bit(d->hwirq, mask);
	__raw_ग_लिखोq(mask[0], hd->irq_mask[0]);
	__raw_ग_लिखोq(mask[1], hd->irq_mask[1]);
पूर्ण

अटल व्योम setup_hub_mask(काष्ठा hub_irq_data *hd, स्थिर काष्ठा cpumask *mask)
अणु
	nasid_t nasid;
	पूर्णांक cpu;

	cpu = cpumask_first_and(mask, cpu_online_mask);
	अगर (cpu >= nr_cpu_ids)
		cpu = cpumask_any(cpu_online_mask);

	nasid = cpu_to_node(cpu);
	hd->cpu = cpu;
	अगर (!cputoslice(cpu)) अणु
		hd->irq_mask[0] = REMOTE_HUB_PTR(nasid, PI_INT_MASK0_A);
		hd->irq_mask[1] = REMOTE_HUB_PTR(nasid, PI_INT_MASK1_A);
	पूर्ण अन्यथा अणु
		hd->irq_mask[0] = REMOTE_HUB_PTR(nasid, PI_INT_MASK0_B);
		hd->irq_mask[1] = REMOTE_HUB_PTR(nasid, PI_INT_MASK1_B);
	पूर्ण
पूर्ण

अटल पूर्णांक set_affinity_hub_irq(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask,
				bool क्रमce)
अणु
	काष्ठा hub_irq_data *hd = irq_data_get_irq_chip_data(d);

	अगर (!hd)
		वापस -EINVAL;

	अगर (irqd_is_started(d))
		disable_hub_irq(d);

	setup_hub_mask(hd, mask);

	अगर (irqd_is_started(d))
		enable_hub_irq(d);

	irq_data_update_effective_affinity(d, cpumask_of(hd->cpu));

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip hub_irq_type = अणु
	.name		  = "HUB",
	.irq_mask	  = disable_hub_irq,
	.irq_unmask	  = enable_hub_irq,
	.irq_set_affinity = set_affinity_hub_irq,
पूर्ण;

अटल पूर्णांक hub_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			    अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा hub_irq_data *hd;
	काष्ठा hub_data *hub;
	काष्ठा irq_desc *desc;
	पूर्णांक swlevel;

	अगर (nr_irqs > 1 || !info)
		वापस -EINVAL;

	hd = kzalloc(माप(*hd), GFP_KERNEL);
	अगर (!hd)
		वापस -ENOMEM;

	swlevel = alloc_level();
	अगर (unlikely(swlevel < 0)) अणु
		kमुक्त(hd);
		वापस -EAGAIN;
	पूर्ण
	irq_करोमुख्य_set_info(करोमुख्य, virq, swlevel, &hub_irq_type, hd,
			    handle_level_irq, शून्य, शून्य);

	/* use CPU connected to nearest hub */
	hub = hub_data(info->nasid);
	setup_hub_mask(hd, &hub->h_cpus);
	info->nasid = cpu_to_node(hd->cpu);

	/* Make sure it's not alपढ़ोy pending when we connect it. */
	REMOTE_HUB_CLR_INTR(info->nasid, swlevel);

	desc = irq_to_desc(virq);
	desc->irq_common_data.node = info->nasid;
	cpumask_copy(desc->irq_common_data.affinity, &hub->h_cpus);

	वापस 0;
पूर्ण

अटल व्योम hub_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
			    अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irqd;

	अगर (nr_irqs > 1)
		वापस;

	irqd = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	अगर (irqd && irqd->chip_data)
		kमुक्त(irqd->chip_data);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops hub_करोमुख्य_ops = अणु
	.alloc = hub_करोमुख्य_alloc,
	.मुक्त  = hub_करोमुख्य_मुक्त,
पूर्ण;

/*
 * This code is unnecessarily complex, because we करो
 * पूर्णांकr enabling. Basically, once we grab the set of पूर्णांकrs we need
 * to service, we must mask _all_ these पूर्णांकerrupts; firstly, to make
 * sure the same पूर्णांकr करोes not पूर्णांकr again, causing recursion that
 * can lead to stack overflow. Secondly, we can not just mask the
 * one पूर्णांकr we are करो_IRQing, because the non-masked पूर्णांकrs in the
 * first set might पूर्णांकr again, causing multiple servicings of the
 * same पूर्णांकr. This effect is mostly seen क्रम पूर्णांकercpu पूर्णांकrs.
 * Kanoj 05.13.00
 */

अटल व्योम ip27_करो_irq_mask0(काष्ठा irq_desc *desc)
अणु
	cpuid_t cpu = smp_processor_id();
	अचिन्हित दीर्घ *mask = per_cpu(irq_enable_mask, cpu);
	काष्ठा irq_करोमुख्य *करोमुख्य;
	u64 pend0;
	पूर्णांक irq;

	/* copied from Irix पूर्णांकpend0() */
	pend0 = LOCAL_HUB_L(PI_INT_PEND0);

	pend0 &= mask[0];		/* Pick पूर्णांकrs we should look at */
	अगर (!pend0)
		वापस;

#अगर_घोषित CONFIG_SMP
	अगर (pend0 & (1UL << CPU_RESCHED_A_IRQ)) अणु
		LOCAL_HUB_CLR_INTR(CPU_RESCHED_A_IRQ);
		scheduler_ipi();
	पूर्ण अन्यथा अगर (pend0 & (1UL << CPU_RESCHED_B_IRQ)) अणु
		LOCAL_HUB_CLR_INTR(CPU_RESCHED_B_IRQ);
		scheduler_ipi();
	पूर्ण अन्यथा अगर (pend0 & (1UL << CPU_CALL_A_IRQ)) अणु
		LOCAL_HUB_CLR_INTR(CPU_CALL_A_IRQ);
		generic_smp_call_function_पूर्णांकerrupt();
	पूर्ण अन्यथा अगर (pend0 & (1UL << CPU_CALL_B_IRQ)) अणु
		LOCAL_HUB_CLR_INTR(CPU_CALL_B_IRQ);
		generic_smp_call_function_पूर्णांकerrupt();
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		करोमुख्य = irq_desc_get_handler_data(desc);
		irq = irq_linear_revmap(करोमुख्य, __ffs(pend0));
		अगर (irq)
			generic_handle_irq(irq);
		अन्यथा
			spurious_पूर्णांकerrupt();
	पूर्ण

	LOCAL_HUB_L(PI_INT_PEND0);
पूर्ण

अटल व्योम ip27_करो_irq_mask1(काष्ठा irq_desc *desc)
अणु
	cpuid_t cpu = smp_processor_id();
	अचिन्हित दीर्घ *mask = per_cpu(irq_enable_mask, cpu);
	काष्ठा irq_करोमुख्य *करोमुख्य;
	u64 pend1;
	पूर्णांक irq;

	/* copied from Irix पूर्णांकpend0() */
	pend1 = LOCAL_HUB_L(PI_INT_PEND1);

	pend1 &= mask[1];		/* Pick पूर्णांकrs we should look at */
	अगर (!pend1)
		वापस;

	करोमुख्य = irq_desc_get_handler_data(desc);
	irq = irq_linear_revmap(करोमुख्य, __ffs(pend1) + 64);
	अगर (irq)
		generic_handle_irq(irq);
	अन्यथा
		spurious_पूर्णांकerrupt();

	LOCAL_HUB_L(PI_INT_PEND1);
पूर्ण

व्योम install_ipi(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ *mask = per_cpu(irq_enable_mask, cpu);
	पूर्णांक slice = LOCAL_HUB_L(PI_CPU_NUM);
	पूर्णांक resched, call;

	resched = CPU_RESCHED_A_IRQ + slice;
	set_bit(resched, mask);
	LOCAL_HUB_CLR_INTR(resched);

	call = CPU_CALL_A_IRQ + slice;
	set_bit(call, mask);
	LOCAL_HUB_CLR_INTR(call);

	अगर (slice == 0) अणु
		LOCAL_HUB_S(PI_INT_MASK0_A, mask[0]);
		LOCAL_HUB_S(PI_INT_MASK1_A, mask[1]);
	पूर्ण अन्यथा अणु
		LOCAL_HUB_S(PI_INT_MASK0_B, mask[0]);
		LOCAL_HUB_S(PI_INT_MASK1_B, mask[1]);
	पूर्ण
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा fwnode_handle *fn;
	पूर्णांक i;

	mips_cpu_irq_init();

	/*
	 * Some पूर्णांकerrupts are reserved by hardware or by software convention.
	 * Mark these as reserved right away so they won't be used accidentally
	 * later.
	 */
	क्रम (i = 0; i <= CPU_CALL_B_IRQ; i++)
		set_bit(i, hub_irq_map);

	क्रम (i = NI_BRDCAST_ERR_A; i <= MSC_PANIC_INTR; i++)
		set_bit(i, hub_irq_map);

	fn = irq_करोमुख्य_alloc_named_fwnode("HUB");
	WARN_ON(fn == शून्य);
	अगर (!fn)
		वापस;
	करोमुख्य = irq_करोमुख्य_create_linear(fn, IP27_HUB_IRQ_COUNT,
					  &hub_करोमुख्य_ops, शून्य);
	WARN_ON(करोमुख्य == शून्य);
	अगर (!करोमुख्य)
		वापस;

	irq_set_शेष_host(करोमुख्य);

	irq_set_percpu_devid(IP27_HUB_PEND0_IRQ);
	irq_set_chained_handler_and_data(IP27_HUB_PEND0_IRQ, ip27_करो_irq_mask0,
					 करोमुख्य);
	irq_set_percpu_devid(IP27_HUB_PEND1_IRQ);
	irq_set_chained_handler_and_data(IP27_HUB_PEND1_IRQ, ip27_करो_irq_mask1,
					 करोमुख्य);
पूर्ण
