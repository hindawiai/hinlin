<शैली गुरु>
/*
 * Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 * Copyright (C) 2017 Stafक्रमd Horne <shorne@gmail.com>
 *
 * Based on arm64 and arc implementations
 * Copyright (C) 2013 ARM Ltd.
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/समय.स>

अटल व्योम (*smp_cross_call)(स्थिर काष्ठा cpumask *, अचिन्हित पूर्णांक);

अचिन्हित दीर्घ secondary_release = -1;
काष्ठा thपढ़ो_info *secondary_thपढ़ो_info;

क्रमागत ipi_msg_type अणु
	IPI_WAKEUP,
	IPI_RESCHEDULE,
	IPI_CALL_FUNC,
	IPI_CALL_FUNC_SINGLE,
पूर्ण;

अटल DEFINE_SPINLOCK(boot_lock);

अटल व्योम boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	/*
	 * set synchronisation state between this boot processor
	 * and the secondary one
	 */
	spin_lock(&boot_lock);

	secondary_release = cpu;
	smp_cross_call(cpumask_of(cpu), IPI_WAKEUP);

	/*
	 * now the secondary core is starting up let it run its
	 * calibrations, then रुको क्रम it to finish
	 */
	spin_unlock(&boot_lock);
पूर्ण

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
पूर्ण

व्योम __init smp_init_cpus(व्योम)
अणु
	काष्ठा device_node *cpu;
	u32 cpu_id;

	क्रम_each_of_cpu_node(cpu) अणु
		अगर (of_property_पढ़ो_u32(cpu, "reg", &cpu_id)) अणु
			pr_warn("%s missing reg property", cpu->full_name);
			जारी;
		पूर्ण

		अगर (cpu_id < NR_CPUS)
			set_cpu_possible(cpu_id, true);
	पूर्ण
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित पूर्णांक cpu;

	/*
	 * Initialise the present map, which describes the set of CPUs
	 * actually populated at the present समय.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu < max_cpus)
			set_cpu_present(cpu, true);
	पूर्ण
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

अटल DECLARE_COMPLETION(cpu_running);

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अगर (smp_cross_call == शून्य) अणु
		pr_warn("CPU%u: failed to start, IPI controller missing",
			cpu);
		वापस -EIO;
	पूर्ण

	secondary_thपढ़ो_info = task_thपढ़ो_info(idle);
	current_pgd[cpu] = init_mm.pgd;

	boot_secondary(cpu, idle);
	अगर (!रुको_क्रम_completion_समयout(&cpu_running,
					msecs_to_jअगरfies(1000))) अणु
		pr_crit("CPU%u: failed to start\n", cpu);
		वापस -EIO;
	पूर्ण
	synchronise_count_master(cpu);

	वापस 0;
पूर्ण

यंत्रlinkage __init व्योम secondary_start_kernel(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = &init_mm;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	/*
	 * All kernel thपढ़ोs share the same mm context; grab a
	 * reference and चयन to it.
	 */
	mmgrab(mm);
	current->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	pr_info("CPU%u: Booted secondary processor\n", cpu);

	setup_cpuinfo();
	खोलोrisc_घड़ीevent_init();

	notअगरy_cpu_starting(cpu);

	/*
	 * OK, now it's safe to let the boot CPU जारी
	 */
	complete(&cpu_running);

	synchronise_count_slave(cpu);
	set_cpu_online(cpu, true);

	local_irq_enable();

	preempt_disable();
	/*
	 * OK, it's off to the idle thपढ़ो क्रम us
	 */
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

व्योम handle_IPI(अचिन्हित पूर्णांक ipi_msg)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	चयन (ipi_msg) अणु
	हाल IPI_WAKEUP:
		अवरोध;

	हाल IPI_RESCHEDULE:
		scheduler_ipi();
		अवरोध;

	हाल IPI_CALL_FUNC:
		generic_smp_call_function_पूर्णांकerrupt();
		अवरोध;

	हाल IPI_CALL_FUNC_SINGLE:
		generic_smp_call_function_single_पूर्णांकerrupt();
		अवरोध;

	शेष:
		WARN(1, "CPU%u: Unknown IPI message 0x%x\n", cpu, ipi_msg);
		अवरोध;
	पूर्ण
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	smp_cross_call(cpumask_of(cpu), IPI_RESCHEDULE);
पूर्ण

अटल व्योम stop_this_cpu(व्योम *dummy)
अणु
	/* Remove this CPU */
	set_cpu_online(smp_processor_id(), false);

	local_irq_disable();
	/* CPU Doze */
	अगर (mfspr(SPR_UPR) & SPR_UPR_PMP)
		mtspr(SPR_PMR, mfspr(SPR_PMR) | SPR_PMR_DME);
	/* If that didn't work, infinite loop */
	जबतक (1)
		;
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	smp_call_function(stop_this_cpu, शून्य, 0);
पूर्ण

/* not supported, yet */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

व्योम __init set_smp_cross_call(व्योम (*fn)(स्थिर काष्ठा cpumask *, अचिन्हित पूर्णांक))
अणु
	smp_cross_call = fn;
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	smp_cross_call(cpumask_of(cpu), IPI_CALL_FUNC_SINGLE);
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	smp_cross_call(mask, IPI_CALL_FUNC);
पूर्ण

/* TLB flush operations - Perक्रमmed on each CPU*/
अटल अंतरभूत व्योम ipi_flush_tlb_all(व्योम *ignored)
अणु
	local_flush_tlb_all();
पूर्ण

अटल अंतरभूत व्योम ipi_flush_tlb_mm(व्योम *info)
अणु
	काष्ठा mm_काष्ठा *mm = (काष्ठा mm_काष्ठा *)info;

	local_flush_tlb_mm(mm);
पूर्ण

अटल व्योम smp_flush_tlb_mm(काष्ठा cpumask *cmask, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक cpuid;

	अगर (cpumask_empty(cmask))
		वापस;

	cpuid = get_cpu();

	अगर (cpumask_any_but(cmask, cpuid) >= nr_cpu_ids) अणु
		/* local cpu is the only cpu present in cpumask */
		local_flush_tlb_mm(mm);
	पूर्ण अन्यथा अणु
		on_each_cpu_mask(cmask, ipi_flush_tlb_mm, mm, 1);
	पूर्ण
	put_cpu();
पूर्ण

काष्ठा flush_tlb_data अणु
	अचिन्हित दीर्घ addr1;
	अचिन्हित दीर्घ addr2;
पूर्ण;

अटल अंतरभूत व्योम ipi_flush_tlb_page(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = (काष्ठा flush_tlb_data *)info;

	local_flush_tlb_page(शून्य, fd->addr1);
पूर्ण

अटल अंतरभूत व्योम ipi_flush_tlb_range(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = (काष्ठा flush_tlb_data *)info;

	local_flush_tlb_range(शून्य, fd->addr1, fd->addr2);
पूर्ण

अटल व्योम smp_flush_tlb_range(काष्ठा cpumask *cmask, अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ end)
अणु
	अचिन्हित पूर्णांक cpuid;

	अगर (cpumask_empty(cmask))
		वापस;

	cpuid = get_cpu();

	अगर (cpumask_any_but(cmask, cpuid) >= nr_cpu_ids) अणु
		/* local cpu is the only cpu present in cpumask */
		अगर ((end - start) <= PAGE_SIZE)
			local_flush_tlb_page(शून्य, start);
		अन्यथा
			local_flush_tlb_range(शून्य, start, end);
	पूर्ण अन्यथा अणु
		काष्ठा flush_tlb_data fd;

		fd.addr1 = start;
		fd.addr2 = end;

		अगर ((end - start) <= PAGE_SIZE)
			on_each_cpu_mask(cmask, ipi_flush_tlb_page, &fd, 1);
		अन्यथा
			on_each_cpu_mask(cmask, ipi_flush_tlb_range, &fd, 1);
	पूर्ण
	put_cpu();
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	on_each_cpu(ipi_flush_tlb_all, शून्य, 1);
पूर्ण

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	smp_flush_tlb_mm(mm_cpumask(mm), mm);
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr)
अणु
	smp_flush_tlb_range(mm_cpumask(vma->vm_mm), uaddr, uaddr + PAGE_SIZE);
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	smp_flush_tlb_range(mm_cpumask(vma->vm_mm), start, end);
पूर्ण

/* Inकाष्ठाion cache invalidate - perक्रमmed on each cpu */
अटल व्योम ipi_icache_page_inv(व्योम *arg)
अणु
	काष्ठा page *page = arg;

	local_icache_page_inv(page);
पूर्ण

व्योम smp_icache_page_inv(काष्ठा page *page)
अणु
	on_each_cpu(ipi_icache_page_inv, page, 1);
पूर्ण
EXPORT_SYMBOL(smp_icache_page_inv);
