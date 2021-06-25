<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2000, 2001 Kanoj Sarcar
 * Copyright (C) 2000, 2001 Ralf Baechle
 * Copyright (C) 2000, 2001 Silicon Graphics, Inc.
 * Copyright (C) 2000, 2001, 2003 Broadcom Corporation
 */
#समावेश <linux/cache.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/export.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/ginvt.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/r4k-समयr.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/maar.h>

पूर्णांक __cpu_number_map[CONFIG_MIPS_NR_CPU_NR_MAP];   /* Map physical to logical */
EXPORT_SYMBOL(__cpu_number_map);

पूर्णांक __cpu_logical_map[NR_CPUS];		/* Map logical to physical */
EXPORT_SYMBOL(__cpu_logical_map);

/* Number of TCs (or siblings in Intel speak) per CPU core */
पूर्णांक smp_num_siblings = 1;
EXPORT_SYMBOL(smp_num_siblings);

/* representing the TCs (or siblings in Intel speak) of each logical CPU */
cpumask_t cpu_sibling_map[NR_CPUS] __पढ़ो_mostly;
EXPORT_SYMBOL(cpu_sibling_map);

/* representing the core map of multi-core chips of each logical CPU */
cpumask_t cpu_core_map[NR_CPUS] __पढ़ो_mostly;
EXPORT_SYMBOL(cpu_core_map);

अटल DECLARE_COMPLETION(cpu_starting);
अटल DECLARE_COMPLETION(cpu_running);

/*
 * A logical cpu mask containing only one VPE per core to
 * reduce the number of IPIs on large MT प्रणालीs.
 */
cpumask_t cpu_क्रमeign_map[NR_CPUS] __पढ़ो_mostly;
EXPORT_SYMBOL(cpu_क्रमeign_map);

/* representing cpus क्रम which sibling maps can be computed */
अटल cpumask_t cpu_sibling_setup_map;

/* representing cpus क्रम which core maps can be computed */
अटल cpumask_t cpu_core_setup_map;

cpumask_t cpu_coherent_mask;

#अगर_घोषित CONFIG_GENERIC_IRQ_IPI
अटल काष्ठा irq_desc *call_desc;
अटल काष्ठा irq_desc *sched_desc;
#पूर्ण_अगर

अटल अंतरभूत व्योम set_cpu_sibling_map(पूर्णांक cpu)
अणु
	पूर्णांक i;

	cpumask_set_cpu(cpu, &cpu_sibling_setup_map);

	अगर (smp_num_siblings > 1) अणु
		क्रम_each_cpu(i, &cpu_sibling_setup_map) अणु
			अगर (cpus_are_siblings(cpu, i)) अणु
				cpumask_set_cpu(i, &cpu_sibling_map[cpu]);
				cpumask_set_cpu(cpu, &cpu_sibling_map[i]);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		cpumask_set_cpu(cpu, &cpu_sibling_map[cpu]);
पूर्ण

अटल अंतरभूत व्योम set_cpu_core_map(पूर्णांक cpu)
अणु
	पूर्णांक i;

	cpumask_set_cpu(cpu, &cpu_core_setup_map);

	क्रम_each_cpu(i, &cpu_core_setup_map) अणु
		अगर (cpu_data[cpu].package == cpu_data[i].package) अणु
			cpumask_set_cpu(i, &cpu_core_map[cpu]);
			cpumask_set_cpu(cpu, &cpu_core_map[i]);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Calculate a new cpu_क्रमeign_map mask whenever a
 * new cpu appears or disappears.
 */
व्योम calculate_cpu_क्रमeign_map(व्योम)
अणु
	पूर्णांक i, k, core_present;
	cpumask_t temp_क्रमeign_map;

	/* Re-calculate the mask */
	cpumask_clear(&temp_क्रमeign_map);
	क्रम_each_online_cpu(i) अणु
		core_present = 0;
		क्रम_each_cpu(k, &temp_क्रमeign_map)
			अगर (cpus_are_siblings(i, k))
				core_present = 1;
		अगर (!core_present)
			cpumask_set_cpu(i, &temp_क्रमeign_map);
	पूर्ण

	क्रम_each_online_cpu(i)
		cpumask_andnot(&cpu_क्रमeign_map[i],
			       &temp_क्रमeign_map, &cpu_sibling_map[i]);
पूर्ण

स्थिर काष्ठा plat_smp_ops *mp_ops;
EXPORT_SYMBOL(mp_ops);

व्योम रेजिस्टर_smp_ops(स्थिर काष्ठा plat_smp_ops *ops)
अणु
	अगर (mp_ops)
		prपूर्णांकk(KERN_WARNING "Overriding previously set SMP ops\n");

	mp_ops = ops;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_IPI
व्योम mips_smp_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action)
अणु
	mips_smp_send_ipi_mask(cpumask_of(cpu), action);
पूर्ण

व्योम mips_smp_send_ipi_mask(स्थिर काष्ठा cpumask *mask, अचिन्हित पूर्णांक action)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक core;
	पूर्णांक cpu;

	local_irq_save(flags);

	चयन (action) अणु
	हाल SMP_CALL_FUNCTION:
		__ipi_send_mask(call_desc, mask);
		अवरोध;

	हाल SMP_RESCHEDULE_YOURSELF:
		__ipi_send_mask(sched_desc, mask);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	अगर (mips_cpc_present()) अणु
		क्रम_each_cpu(cpu, mask) अणु
			अगर (cpus_are_siblings(cpu, smp_processor_id()))
				जारी;

			core = cpu_core(&cpu_data[cpu]);

			जबतक (!cpumask_test_cpu(cpu, &cpu_coherent_mask)) अणु
				mips_cm_lock_other_cpu(cpu, CM_GCR_Cx_OTHER_BLOCK_LOCAL);
				mips_cpc_lock_other(core);
				ग_लिखो_cpc_co_cmd(CPC_Cx_CMD_PWRUP);
				mips_cpc_unlock_other();
				mips_cm_unlock_other();
			पूर्ण
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
पूर्ण


अटल irqवापस_t ipi_resched_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	scheduler_ipi();

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ipi_call_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	generic_smp_call_function_पूर्णांकerrupt();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम smp_ipi_init_one(अचिन्हित पूर्णांक virq, स्थिर अक्षर *name,
			     irq_handler_t handler)
अणु
	पूर्णांक ret;

	irq_set_handler(virq, handle_percpu_irq);
	ret = request_irq(virq, handler, IRQF_PERCPU, name, शून्य);
	BUG_ON(ret);
पूर्ण

अटल अचिन्हित पूर्णांक call_virq, sched_virq;

पूर्णांक mips_smp_ipi_allocate(स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक virq;
	काष्ठा irq_करोमुख्य *ipiकरोमुख्य;
	काष्ठा device_node *node;

	node = of_irq_find_parent(of_root);
	ipiकरोमुख्य = irq_find_matching_host(node, DOMAIN_BUS_IPI);

	/*
	 * Some platक्रमms have half DT setup. So अगर we found irq node but
	 * didn't find an ipiकरोमुख्य, try to search क्रम one that is not in the
	 * DT.
	 */
	अगर (node && !ipiकरोमुख्य)
		ipiकरोमुख्य = irq_find_matching_host(शून्य, DOMAIN_BUS_IPI);

	/*
	 * There are प्रणालीs which use IPI IRQ करोमुख्यs, but only have one
	 * रेजिस्टरed when some runसमय condition is met. For example a Malta
	 * kernel may include support क्रम GIC & CPU पूर्णांकerrupt controller IPI
	 * IRQ करोमुख्यs, but अगर run on a प्रणाली with no GIC & no MT ASE then
	 * neither will be supported or रेजिस्टरed.
	 *
	 * We only have a problem अगर we're actually using multiple CPUs so fail
	 * loudly अगर that is the हाल. Otherwise simply वापस, skipping IPI
	 * setup, अगर we're running with only a single CPU.
	 */
	अगर (!ipiकरोमुख्य) अणु
		BUG_ON(num_present_cpus() > 1);
		वापस 0;
	पूर्ण

	virq = irq_reserve_ipi(ipiकरोमुख्य, mask);
	BUG_ON(!virq);
	अगर (!call_virq)
		call_virq = virq;

	virq = irq_reserve_ipi(ipiकरोमुख्य, mask);
	BUG_ON(!virq);
	अगर (!sched_virq)
		sched_virq = virq;

	अगर (irq_करोमुख्य_is_ipi_per_cpu(ipiकरोमुख्य)) अणु
		पूर्णांक cpu;

		क्रम_each_cpu(cpu, mask) अणु
			smp_ipi_init_one(call_virq + cpu, "IPI call",
					 ipi_call_पूर्णांकerrupt);
			smp_ipi_init_one(sched_virq + cpu, "IPI resched",
					 ipi_resched_पूर्णांकerrupt);
		पूर्ण
	पूर्ण अन्यथा अणु
		smp_ipi_init_one(call_virq, "IPI call", ipi_call_पूर्णांकerrupt);
		smp_ipi_init_one(sched_virq, "IPI resched",
				 ipi_resched_पूर्णांकerrupt);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mips_smp_ipi_मुक्त(स्थिर काष्ठा cpumask *mask)
अणु
	काष्ठा irq_करोमुख्य *ipiकरोमुख्य;
	काष्ठा device_node *node;

	node = of_irq_find_parent(of_root);
	ipiकरोमुख्य = irq_find_matching_host(node, DOMAIN_BUS_IPI);

	/*
	 * Some platक्रमms have half DT setup. So अगर we found irq node but
	 * didn't find an ipiकरोमुख्य, try to search क्रम one that is not in the
	 * DT.
	 */
	अगर (node && !ipiकरोमुख्य)
		ipiकरोमुख्य = irq_find_matching_host(शून्य, DOMAIN_BUS_IPI);

	BUG_ON(!ipiकरोमुख्य);

	अगर (irq_करोमुख्य_is_ipi_per_cpu(ipiकरोमुख्य)) अणु
		पूर्णांक cpu;

		क्रम_each_cpu(cpu, mask) अणु
			मुक्त_irq(call_virq + cpu, शून्य);
			मुक्त_irq(sched_virq + cpu, शून्य);
		पूर्ण
	पूर्ण
	irq_destroy_ipi(call_virq, mask);
	irq_destroy_ipi(sched_virq, mask);
	वापस 0;
पूर्ण


अटल पूर्णांक __init mips_smp_ipi_init(व्योम)
अणु
	अगर (num_possible_cpus() == 1)
		वापस 0;

	mips_smp_ipi_allocate(cpu_possible_mask);

	call_desc = irq_to_desc(call_virq);
	sched_desc = irq_to_desc(sched_virq);

	वापस 0;
पूर्ण
early_initcall(mips_smp_ipi_init);
#पूर्ण_अगर

/*
 * First C code run on the secondary CPUs after being started up by
 * the master.
 */
यंत्रlinkage व्योम start_secondary(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	cpu_probe();
	per_cpu_trap_init(false);
	mips_घड़ीevent_init();
	mp_ops->init_secondary();
	cpu_report();
	maar_init();

	/*
	 * XXX parity protection should be folded in here when it's converted
	 * to an option instead of something based on .cputype
	 */

	calibrate_delay();
	preempt_disable();
	cpu = smp_processor_id();
	cpu_data[cpu].udelay_val = loops_per_jअगरfy;

	cpumask_set_cpu(cpu, &cpu_coherent_mask);
	notअगरy_cpu_starting(cpu);

	/* Notअगरy boot CPU that we're starting & पढ़ोy to sync counters */
	complete(&cpu_starting);

	synchronise_count_slave(cpu);

	/* The CPU is running and counters synchronised, now mark it online */
	set_cpu_online(cpu, true);

	set_cpu_sibling_map(cpu);
	set_cpu_core_map(cpu);

	calculate_cpu_क्रमeign_map();

	/*
	 * Notअगरy boot CPU that we're up & online and it can safely वापस
	 * from __cpu_up
	 */
	complete(&cpu_running);

	/*
	 * irq will be enabled in ->smp_finish(), enabling it too early
	 * is dangerous.
	 */
	WARN_ON_ONCE(!irqs_disabled());
	mp_ops->smp_finish();

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

अटल व्योम stop_this_cpu(व्योम *dummy)
अणु
	/*
	 * Remove this CPU:
	 */

	set_cpu_online(smp_processor_id(), false);
	calculate_cpu_क्रमeign_map();
	local_irq_disable();
	जबतक (1);
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	smp_call_function(stop_this_cpu, शून्य, 0);
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

/* called from मुख्य beक्रमe smp_init() */
व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	init_new_context(current, &init_mm);
	current_thपढ़ो_info()->cpu = 0;
	mp_ops->prepare_cpus(max_cpus);
	set_cpu_sibling_map(0);
	set_cpu_core_map(0);
	calculate_cpu_क्रमeign_map();
#अगर_अघोषित CONFIG_HOTPLUG_CPU
	init_cpu_present(cpu_possible_mask);
#पूर्ण_अगर
	cpumask_copy(&cpu_coherent_mask, cpu_possible_mask);
पूर्ण

/* preload SMP state क्रम boot cpu */
व्योम smp_prepare_boot_cpu(व्योम)
अणु
	अगर (mp_ops->prepare_boot_cpu)
		mp_ops->prepare_boot_cpu();
	set_cpu_possible(0, true);
	set_cpu_online(0, true);
पूर्ण

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक err;

	err = mp_ops->boot_secondary(cpu, tidle);
	अगर (err)
		वापस err;

	/* Wait क्रम CPU to start and be पढ़ोy to sync counters */
	अगर (!रुको_क्रम_completion_समयout(&cpu_starting,
					 msecs_to_jअगरfies(1000))) अणु
		pr_crit("CPU%u: failed to start\n", cpu);
		वापस -EIO;
	पूर्ण

	synchronise_count_master(cpu);

	/* Wait क्रम CPU to finish startup & mark itself online beक्रमe वापस */
	रुको_क्रम_completion(&cpu_running);
	वापस 0;
पूर्ण

/* Not really SMP stuff ... */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस 0;
पूर्ण

अटल व्योम flush_tlb_all_ipi(व्योम *info)
अणु
	local_flush_tlb_all();
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	अगर (cpu_has_mmid) अणु
		htw_stop();
		ginvt_full();
		sync_ginv();
		inकाष्ठाion_hazard();
		htw_start();
		वापस;
	पूर्ण

	on_each_cpu(flush_tlb_all_ipi, शून्य, 1);
पूर्ण

अटल व्योम flush_tlb_mm_ipi(व्योम *mm)
अणु
	drop_mmu_context((काष्ठा mm_काष्ठा *)mm);
पूर्ण

/*
 * Special Variant of smp_call_function क्रम use by TLB functions:
 *
 *  o No वापस value
 *  o collapses to normal function call on UP kernels
 *  o collapses to normal function call on प्रणालीs with a single shared
 *    primary cache.
 */
अटल अंतरभूत व्योम smp_on_other_tlbs(व्योम (*func) (व्योम *info), व्योम *info)
अणु
	smp_call_function(func, info, 1);
पूर्ण

अटल अंतरभूत व्योम smp_on_each_tlb(व्योम (*func) (व्योम *info), व्योम *info)
अणु
	preempt_disable();

	smp_on_other_tlbs(func, info);
	func(info);

	preempt_enable();
पूर्ण

/*
 * The following tlb flush calls are invoked when old translations are
 * being torn करोwn, or pte attributes are changing. For single thपढ़ोed
 * address spaces, a new context is obtained on the current cpu, and tlb
 * context on other cpus are invalidated to क्रमce a new context allocation
 * at चयन_mm समय, should the mm ever be used on other cpus. For
 * multithपढ़ोed address spaces, पूर्णांकer-CPU पूर्णांकerrupts have to be sent.
 * Another हाल where पूर्णांकer-CPU पूर्णांकerrupts are required is when the target
 * mm might be active on another cpu (eg debuggers करोing the flushes on
 * behalf of debugees, kswapd stealing pages from another process etc).
 * Kanoj 07/00.
 */

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	preempt_disable();

	अगर (cpu_has_mmid) अणु
		/*
		 * No need to worry about other CPUs - the ginvt in
		 * drop_mmu_context() will be globalized.
		 */
	पूर्ण अन्यथा अगर ((atomic_पढ़ो(&mm->mm_users) != 1) || (current->mm != mm)) अणु
		smp_on_other_tlbs(flush_tlb_mm_ipi, mm);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक cpu;

		क्रम_each_online_cpu(cpu) अणु
			अगर (cpu != smp_processor_id() && cpu_context(cpu, mm))
				set_cpu_context(cpu, mm, 0);
		पूर्ण
	पूर्ण
	drop_mmu_context(mm);

	preempt_enable();
पूर्ण

काष्ठा flush_tlb_data अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr1;
	अचिन्हित दीर्घ addr2;
पूर्ण;

अटल व्योम flush_tlb_range_ipi(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = info;

	local_flush_tlb_range(fd->vma, fd->addr1, fd->addr2);
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ addr;
	u32 old_mmid;

	preempt_disable();
	अगर (cpu_has_mmid) अणु
		htw_stop();
		old_mmid = पढ़ो_c0_memorymapid();
		ग_लिखो_c0_memorymapid(cpu_asid(0, mm));
		mtc0_tlbw_hazard();
		addr = round_करोwn(start, PAGE_SIZE * 2);
		end = round_up(end, PAGE_SIZE * 2);
		करो अणु
			ginvt_va_mmid(addr);
			sync_ginv();
			addr += PAGE_SIZE * 2;
		पूर्ण जबतक (addr < end);
		ग_लिखो_c0_memorymapid(old_mmid);
		inकाष्ठाion_hazard();
		htw_start();
	पूर्ण अन्यथा अगर ((atomic_पढ़ो(&mm->mm_users) != 1) || (current->mm != mm)) अणु
		काष्ठा flush_tlb_data fd = अणु
			.vma = vma,
			.addr1 = start,
			.addr2 = end,
		पूर्ण;

		smp_on_other_tlbs(flush_tlb_range_ipi, &fd);
		local_flush_tlb_range(vma, start, end);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक cpu;
		पूर्णांक exec = vma->vm_flags & VM_EXEC;

		क्रम_each_online_cpu(cpu) अणु
			/*
			 * flush_cache_range() will only fully flush icache अगर
			 * the VMA is executable, otherwise we must invalidate
			 * ASID without it appearing to has_valid_asid() as अगर
			 * mm has been completely unused by that CPU.
			 */
			अगर (cpu != smp_processor_id() && cpu_context(cpu, mm))
				set_cpu_context(cpu, mm, !exec);
		पूर्ण
		local_flush_tlb_range(vma, start, end);
	पूर्ण
	preempt_enable();
पूर्ण

अटल व्योम flush_tlb_kernel_range_ipi(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = info;

	local_flush_tlb_kernel_range(fd->addr1, fd->addr2);
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा flush_tlb_data fd = अणु
		.addr1 = start,
		.addr2 = end,
	पूर्ण;

	on_each_cpu(flush_tlb_kernel_range_ipi, &fd, 1);
पूर्ण

अटल व्योम flush_tlb_page_ipi(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = info;

	local_flush_tlb_page(fd->vma, fd->addr1);
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	u32 old_mmid;

	preempt_disable();
	अगर (cpu_has_mmid) अणु
		htw_stop();
		old_mmid = पढ़ो_c0_memorymapid();
		ग_लिखो_c0_memorymapid(cpu_asid(0, vma->vm_mm));
		mtc0_tlbw_hazard();
		ginvt_va_mmid(page);
		sync_ginv();
		ग_लिखो_c0_memorymapid(old_mmid);
		inकाष्ठाion_hazard();
		htw_start();
	पूर्ण अन्यथा अगर ((atomic_पढ़ो(&vma->vm_mm->mm_users) != 1) ||
		   (current->mm != vma->vm_mm)) अणु
		काष्ठा flush_tlb_data fd = अणु
			.vma = vma,
			.addr1 = page,
		पूर्ण;

		smp_on_other_tlbs(flush_tlb_page_ipi, &fd);
		local_flush_tlb_page(vma, page);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक cpu;

		क्रम_each_online_cpu(cpu) अणु
			/*
			 * flush_cache_page() only करोes partial flushes, so
			 * invalidate ASID without it appearing to
			 * has_valid_asid() as अगर mm has been completely unused
			 * by that CPU.
			 */
			अगर (cpu != smp_processor_id() && cpu_context(cpu, vma->vm_mm))
				set_cpu_context(cpu, vma->vm_mm, 1);
		पूर्ण
		local_flush_tlb_page(vma, page);
	पूर्ण
	preempt_enable();
पूर्ण

अटल व्योम flush_tlb_one_ipi(व्योम *info)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ) info;

	local_flush_tlb_one(vaddr);
पूर्ण

व्योम flush_tlb_one(अचिन्हित दीर्घ vaddr)
अणु
	smp_on_each_tlb(flush_tlb_one_ipi, (व्योम *) vaddr);
पूर्ण

EXPORT_SYMBOL(flush_tlb_page);
EXPORT_SYMBOL(flush_tlb_one);

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST

अटल व्योम tick_broadcast_callee(व्योम *info)
अणु
	tick_receive_broadcast();
पूर्ण

अटल DEFINE_PER_CPU(call_single_data_t, tick_broadcast_csd) =
	CSD_INIT(tick_broadcast_callee, शून्य);

व्योम tick_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
	call_single_data_t *csd;
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
		csd = &per_cpu(tick_broadcast_csd, cpu);
		smp_call_function_single_async(cpu, csd);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_GENERIC_CLOCKEVENTS_BROADCAST */
