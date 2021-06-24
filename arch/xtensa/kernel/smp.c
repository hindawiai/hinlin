<शैली गुरु>
/*
 * Xtensa SMP support functions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 - 2013 Tensilica Inc.
 *
 * Chris Zankel <chris@zankel.net>
 * Joe Taylor <joe@tensilica.com>
 * Pete Delaney <piet@tensilica.com
 */

#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/reboot.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/kdebug.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mxregs.h>
#समावेश <यंत्र/platक्रमm.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/traps.h>

#अगर_घोषित CONFIG_SMP
# अगर XCHAL_HAVE_S32C1I == 0
#  error "The S32C1I option is required for SMP."
# endअगर
#पूर्ण_अगर

अटल व्योम प्रणाली_invalidate_dcache_range(अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ size);
अटल व्योम प्रणाली_flush_invalidate_dcache_range(अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ size);

/* IPI (Inter Process Interrupt) */

#घोषणा IPI_IRQ	0

अटल irqवापस_t ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

व्योम ipi_init(व्योम)
अणु
	अचिन्हित irq = irq_create_mapping(शून्य, IPI_IRQ);
	अगर (request_irq(irq, ipi_पूर्णांकerrupt, IRQF_PERCPU, "ipi", शून्य))
		pr_err("Failed to request irq %u (ipi)\n", irq);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_core_count(व्योम)
अणु
	/* Bits 18..21 of SYSCFGID contain the core count minus 1. */
	अचिन्हित पूर्णांक syscfgid = get_er(SYSCFGID);
	वापस ((syscfgid >> 18) & 0xf) + 1;
पूर्ण

अटल अंतरभूत पूर्णांक get_core_id(व्योम)
अणु
	/* Bits 0...18 of SYSCFGID contain the core id  */
	अचिन्हित पूर्णांक core_id = get_er(SYSCFGID);
	वापस core_id & 0x3fff;
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित i;

	क्रम_each_possible_cpu(i)
		set_cpu_present(i, true);
पूर्ण

व्योम __init smp_init_cpus(व्योम)
अणु
	अचिन्हित i;
	अचिन्हित पूर्णांक ncpus = get_core_count();
	अचिन्हित पूर्णांक core_id = get_core_id();

	pr_info("%s: Core Count = %d\n", __func__, ncpus);
	pr_info("%s: Core Id = %d\n", __func__, core_id);

	अगर (ncpus > NR_CPUS) अणु
		ncpus = NR_CPUS;
		pr_info("%s: limiting core count by %d\n", __func__, ncpus);
	पूर्ण

	क्रम (i = 0; i < ncpus; ++i)
		set_cpu_possible(i, true);
पूर्ण

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	BUG_ON(cpu != 0);
	cpu_asid_cache(cpu) = ASID_USER_FIRST;
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

अटल पूर्णांक boot_secondary_processors = 1; /* Set with xt-gdb via .xt-gdb */
अटल DECLARE_COMPLETION(cpu_running);

व्योम secondary_start_kernel(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = &init_mm;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	init_mmu();

#अगर_घोषित CONFIG_DEBUG_MISC
	अगर (boot_secondary_processors == 0) अणु
		pr_debug("%s: boot_secondary_processors:%d; Hanging cpu:%d\n",
			__func__, boot_secondary_processors, cpu);
		क्रम (;;)
			__यंत्र__ __अस्थिर__ ("waiti " __stringअगरy(LOCKLEVEL));
	पूर्ण

	pr_debug("%s: boot_secondary_processors:%d; Booting cpu:%d\n",
		__func__, boot_secondary_processors, cpu);
#पूर्ण_अगर
	/* Init EXCSAVE1 */

	secondary_trap_init();

	/* All kernel thपढ़ोs share the same mm context. */

	mmget(mm);
	mmgrab(mm);
	current->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));
	enter_lazy_tlb(mm, current);

	preempt_disable();
	trace_hardirqs_off();

	calibrate_delay();

	notअगरy_cpu_starting(cpu);

	secondary_init_irq();
	local_समयr_setup(cpu);

	set_cpu_online(cpu, true);

	local_irq_enable();

	complete(&cpu_running);

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

अटल व्योम mx_cpu_start(व्योम *p)
अणु
	अचिन्हित cpu = (अचिन्हित)p;
	अचिन्हित दीर्घ run_stall_mask = get_er(MPSCORE);

	set_er(run_stall_mask & ~(1u << cpu), MPSCORE);
	pr_debug("%s: cpu: %d, run_stall_mask: %lx ---> %lx\n",
			__func__, cpu, run_stall_mask, get_er(MPSCORE));
पूर्ण

अटल व्योम mx_cpu_stop(व्योम *p)
अणु
	अचिन्हित cpu = (अचिन्हित)p;
	अचिन्हित दीर्घ run_stall_mask = get_er(MPSCORE);

	set_er(run_stall_mask | (1u << cpu), MPSCORE);
	pr_debug("%s: cpu: %d, run_stall_mask: %lx ---> %lx\n",
			__func__, cpu, run_stall_mask, get_er(MPSCORE));
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अचिन्हित दीर्घ cpu_start_id __cacheline_aligned;
#पूर्ण_अगर
अचिन्हित दीर्घ cpu_start_ccount;

अटल पूर्णांक boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *ts)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
	अचिन्हित दीर्घ ccount;
	पूर्णांक i;

#अगर_घोषित CONFIG_HOTPLUG_CPU
	WRITE_ONCE(cpu_start_id, cpu);
	/* Pairs with the third memw in the cpu_restart */
	mb();
	प्रणाली_flush_invalidate_dcache_range((अचिन्हित दीर्घ)&cpu_start_id,
					     माप(cpu_start_id));
#पूर्ण_अगर
	smp_call_function_single(0, mx_cpu_start, (व्योम *)cpu, 1);

	क्रम (i = 0; i < 2; ++i) अणु
		करो
			ccount = get_ccount();
		जबतक (!ccount);

		WRITE_ONCE(cpu_start_ccount, ccount);

		करो अणु
			/*
			 * Pairs with the first two memws in the
			 * .Lboot_secondary.
			 */
			mb();
			ccount = READ_ONCE(cpu_start_ccount);
		पूर्ण जबतक (ccount && समय_beक्रमe(jअगरfies, समयout));

		अगर (ccount) अणु
			smp_call_function_single(0, mx_cpu_stop,
						 (व्योम *)cpu, 1);
			WRITE_ONCE(cpu_start_ccount, 0);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret = 0;

	अगर (cpu_asid_cache(cpu) == 0)
		cpu_asid_cache(cpu) = ASID_USER_FIRST;

	start_info.stack = (अचिन्हित दीर्घ)task_pt_regs(idle);
	wmb();

	pr_debug("%s: Calling wakeup_secondary(cpu:%d, idle:%p, sp: %08lx)\n",
			__func__, cpu, idle, start_info.stack);

	init_completion(&cpu_running);
	ret = boot_secondary(cpu, idle);
	अगर (ret == 0) अणु
		रुको_क्रम_completion_समयout(&cpu_running,
				msecs_to_jअगरfies(1000));
		अगर (!cpu_online(cpu))
			ret = -EIO;
	पूर्ण

	अगर (ret)
		pr_err("CPU %u failed to boot\n", cpu);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

/*
 * __cpu_disable runs on the processor to be shutकरोwn.
 */
पूर्णांक __cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/*
	 * Take this CPU offline.  Once we clear this, we can't वापस,
	 * and we must not schedule until we're पढ़ोy to give up the cpu.
	 */
	set_cpu_online(cpu, false);

	/*
	 * OK - migrate IRQs away from this CPU
	 */
	migrate_irqs();

	/*
	 * Flush user cache and TLB mappings, and then हटाओ this CPU
	 * from the vm mask set of all processes.
	 */
	local_flush_cache_all();
	local_flush_tlb_all();
	invalidate_page_directory();

	clear_tasks_mm_cpumask(cpu);

	वापस 0;
पूर्ण

अटल व्योम platक्रमm_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	smp_call_function_single(0, mx_cpu_stop, (व्योम *)cpu, true);
पूर्ण

/*
 * called on the thपढ़ो which is asking क्रम a CPU to be shutकरोwn -
 * रुकोs until shutकरोwn has completed, or it is समयd out.
 */
व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		प्रणाली_invalidate_dcache_range((अचिन्हित दीर्घ)&cpu_start_id,
					       माप(cpu_start_id));
		/* Pairs with the second memw in the cpu_restart */
		mb();
		अगर (READ_ONCE(cpu_start_id) == -cpu) अणु
			platक्रमm_cpu_समाप्त(cpu);
			वापस;
		पूर्ण
	पूर्ण
	pr_err("CPU%u: unable to kill\n", cpu);
पूर्ण

व्योम arch_cpu_idle_dead(व्योम)
अणु
	cpu_die();
पूर्ण
/*
 * Called from the idle thपढ़ो क्रम the CPU which has been shutकरोwn.
 *
 * Note that we disable IRQs here, but करो not re-enable them
 * beक्रमe वापसing to the caller. This is also the behaviour
 * of the other hotplug-cpu capable cores, so presumably coming
 * out of idle fixes this.
 */
व्योम __ref cpu_die(व्योम)
अणु
	idle_task_निकास();
	local_irq_disable();
	__यंत्र__ __अस्थिर__(
			"	movi	a2, cpu_restart\n"
			"	jx	a2\n");
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

क्रमागत ipi_msg_type अणु
	IPI_RESCHEDULE = 0,
	IPI_CALL_FUNC,
	IPI_CPU_STOP,
	IPI_MAX
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *लघु_text;
	स्थिर अक्षर *दीर्घ_text;
पूर्ण ipi_text[] = अणु
	अणु .लघु_text = "RES", .दीर्घ_text = "Rescheduling interrupts" पूर्ण,
	अणु .लघु_text = "CAL", .दीर्घ_text = "Function call interrupts" पूर्ण,
	अणु .लघु_text = "DIE", .दीर्घ_text = "CPU shutdown interrupts" पूर्ण,
पूर्ण;

काष्ठा ipi_data अणु
	अचिन्हित दीर्घ ipi_count[IPI_MAX];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा ipi_data, ipi_data);

अटल व्योम send_ipi_message(स्थिर काष्ठा cpumask *callmask,
		क्रमागत ipi_msg_type msg_id)
अणु
	पूर्णांक index;
	अचिन्हित दीर्घ mask = 0;

	क्रम_each_cpu(index, callmask)
		mask |= 1 << index;

	set_er(mask, MIPISET(msg_id));
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	send_ipi_message(mask, IPI_CALL_FUNC);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	send_ipi_message(cpumask_of(cpu), IPI_CALL_FUNC);
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	send_ipi_message(cpumask_of(cpu), IPI_RESCHEDULE);
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	काष्ठा cpumask tarमाला_लो;

	cpumask_copy(&tarमाला_लो, cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), &tarमाला_लो);
	send_ipi_message(&tarमाला_लो, IPI_CPU_STOP);
पूर्ण

अटल व्योम ipi_cpu_stop(अचिन्हित पूर्णांक cpu)
अणु
	set_cpu_online(cpu, false);
	machine_halt();
पूर्ण

irqवापस_t ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा ipi_data *ipi = &per_cpu(ipi_data, cpu);

	क्रम (;;) अणु
		अचिन्हित पूर्णांक msg;

		msg = get_er(MIPICAUSE(cpu));
		set_er(msg, MIPICAUSE(cpu));

		अगर (!msg)
			अवरोध;

		अगर (msg & (1 << IPI_CALL_FUNC)) अणु
			++ipi->ipi_count[IPI_CALL_FUNC];
			generic_smp_call_function_पूर्णांकerrupt();
		पूर्ण

		अगर (msg & (1 << IPI_RESCHEDULE)) अणु
			++ipi->ipi_count[IPI_RESCHEDULE];
			scheduler_ipi();
		पूर्ण

		अगर (msg & (1 << IPI_CPU_STOP)) अणु
			++ipi->ipi_count[IPI_CPU_STOP];
			ipi_cpu_stop(cpu);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

व्योम show_ipi_list(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	अचिन्हित पूर्णांक cpu;
	अचिन्हित i;

	क्रम (i = 0; i < IPI_MAX; ++i) अणु
		seq_म_लिखो(p, "%*s:", prec, ipi_text[i].लघु_text);
		क्रम_each_online_cpu(cpu)
			seq_म_लिखो(p, " %10lu",
					per_cpu(ipi_data, cpu).ipi_count[i]);
		seq_म_लिखो(p, "   %s\n", ipi_text[i].दीर्घ_text);
	पूर्ण
पूर्ण

पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	pr_debug("setup_profiling_timer %d\n", multiplier);
	वापस 0;
पूर्ण

/* TLB flush functions */

काष्ठा flush_data अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr1;
	अचिन्हित दीर्घ addr2;
पूर्ण;

अटल व्योम ipi_flush_tlb_all(व्योम *arg)
अणु
	local_flush_tlb_all();
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	on_each_cpu(ipi_flush_tlb_all, शून्य, 1);
पूर्ण

अटल व्योम ipi_flush_tlb_mm(व्योम *arg)
अणु
	local_flush_tlb_mm(arg);
पूर्ण

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	on_each_cpu(ipi_flush_tlb_mm, mm, 1);
पूर्ण

अटल व्योम ipi_flush_tlb_page(व्योम *arg)
अणु
	काष्ठा flush_data *fd = arg;
	local_flush_tlb_page(fd->vma, fd->addr1);
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा flush_data fd = अणु
		.vma = vma,
		.addr1 = addr,
	पूर्ण;
	on_each_cpu(ipi_flush_tlb_page, &fd, 1);
पूर्ण

अटल व्योम ipi_flush_tlb_range(व्योम *arg)
अणु
	काष्ठा flush_data *fd = arg;
	local_flush_tlb_range(fd->vma, fd->addr1, fd->addr2);
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा flush_data fd = अणु
		.vma = vma,
		.addr1 = start,
		.addr2 = end,
	पूर्ण;
	on_each_cpu(ipi_flush_tlb_range, &fd, 1);
पूर्ण

अटल व्योम ipi_flush_tlb_kernel_range(व्योम *arg)
अणु
	काष्ठा flush_data *fd = arg;
	local_flush_tlb_kernel_range(fd->addr1, fd->addr2);
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा flush_data fd = अणु
		.addr1 = start,
		.addr2 = end,
	पूर्ण;
	on_each_cpu(ipi_flush_tlb_kernel_range, &fd, 1);
पूर्ण

/* Cache flush functions */

अटल व्योम ipi_flush_cache_all(व्योम *arg)
अणु
	local_flush_cache_all();
पूर्ण

व्योम flush_cache_all(व्योम)
अणु
	on_each_cpu(ipi_flush_cache_all, शून्य, 1);
पूर्ण

अटल व्योम ipi_flush_cache_page(व्योम *arg)
अणु
	काष्ठा flush_data *fd = arg;
	local_flush_cache_page(fd->vma, fd->addr1, fd->addr2);
पूर्ण

व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ address, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा flush_data fd = अणु
		.vma = vma,
		.addr1 = address,
		.addr2 = pfn,
	पूर्ण;
	on_each_cpu(ipi_flush_cache_page, &fd, 1);
पूर्ण

अटल व्योम ipi_flush_cache_range(व्योम *arg)
अणु
	काष्ठा flush_data *fd = arg;
	local_flush_cache_range(fd->vma, fd->addr1, fd->addr2);
पूर्ण

व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा flush_data fd = अणु
		.vma = vma,
		.addr1 = start,
		.addr2 = end,
	पूर्ण;
	on_each_cpu(ipi_flush_cache_range, &fd, 1);
पूर्ण

अटल व्योम ipi_flush_icache_range(व्योम *arg)
अणु
	काष्ठा flush_data *fd = arg;
	local_flush_icache_range(fd->addr1, fd->addr2);
पूर्ण

व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा flush_data fd = अणु
		.addr1 = start,
		.addr2 = end,
	पूर्ण;
	on_each_cpu(ipi_flush_icache_range, &fd, 1);
पूर्ण
EXPORT_SYMBOL(flush_icache_range);

/* ------------------------------------------------------------------------- */

अटल व्योम ipi_invalidate_dcache_range(व्योम *arg)
अणु
	काष्ठा flush_data *fd = arg;
	__invalidate_dcache_range(fd->addr1, fd->addr2);
पूर्ण

अटल व्योम प्रणाली_invalidate_dcache_range(अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ size)
अणु
	काष्ठा flush_data fd = अणु
		.addr1 = start,
		.addr2 = size,
	पूर्ण;
	on_each_cpu(ipi_invalidate_dcache_range, &fd, 1);
पूर्ण

अटल व्योम ipi_flush_invalidate_dcache_range(व्योम *arg)
अणु
	काष्ठा flush_data *fd = arg;
	__flush_invalidate_dcache_range(fd->addr1, fd->addr2);
पूर्ण

अटल व्योम प्रणाली_flush_invalidate_dcache_range(अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ size)
अणु
	काष्ठा flush_data fd = अणु
		.addr1 = start,
		.addr2 = size,
	पूर्ण;
	on_each_cpu(ipi_flush_invalidate_dcache_range, &fd, 1);
पूर्ण
