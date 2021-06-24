<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/percpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mmu_context.h>
#अगर_घोषित CONFIG_CPU_HAS_FPU
#समावेश <abi/fpu.h>
#पूर्ण_अगर

क्रमागत ipi_message_type अणु
	IPI_EMPTY,
	IPI_RESCHEDULE,
	IPI_CALL_FUNC,
	IPI_IRQ_WORK,
	IPI_MAX
पूर्ण;

काष्ठा ipi_data_काष्ठा अणु
	अचिन्हित दीर्घ bits ____cacheline_aligned;
	अचिन्हित दीर्घ stats[IPI_MAX] ____cacheline_aligned;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा ipi_data_काष्ठा, ipi_data);

अटल irqवापस_t handle_ipi(पूर्णांक irq, व्योम *dev)
अणु
	अचिन्हित दीर्घ *stats = this_cpu_ptr(&ipi_data)->stats;

	जबतक (true) अणु
		अचिन्हित दीर्घ ops;

		ops = xchg(&this_cpu_ptr(&ipi_data)->bits, 0);
		अगर (ops == 0)
			वापस IRQ_HANDLED;

		अगर (ops & (1 << IPI_RESCHEDULE)) अणु
			stats[IPI_RESCHEDULE]++;
			scheduler_ipi();
		पूर्ण

		अगर (ops & (1 << IPI_CALL_FUNC)) अणु
			stats[IPI_CALL_FUNC]++;
			generic_smp_call_function_पूर्णांकerrupt();
		पूर्ण

		अगर (ops & (1 << IPI_IRQ_WORK)) अणु
			stats[IPI_IRQ_WORK]++;
			irq_work_run();
		पूर्ण

		BUG_ON((ops >> IPI_MAX) != 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम (*send_arch_ipi)(स्थिर काष्ठा cpumask *mask);

अटल पूर्णांक ipi_irq;
व्योम __init set_send_ipi(व्योम (*func)(स्थिर काष्ठा cpumask *mask), पूर्णांक irq)
अणु
	अगर (send_arch_ipi)
		वापस;

	send_arch_ipi = func;
	ipi_irq = irq;
पूर्ण

अटल व्योम
send_ipi_message(स्थिर काष्ठा cpumask *to_whom, क्रमागत ipi_message_type operation)
अणु
	पूर्णांक i;

	क्रम_each_cpu(i, to_whom)
		set_bit(operation, &per_cpu_ptr(&ipi_data, i)->bits);

	smp_mb();
	send_arch_ipi(to_whom);
पूर्ण

अटल स्थिर अक्षर * स्थिर ipi_names[] = अणु
	[IPI_EMPTY]		= "Empty interrupts",
	[IPI_RESCHEDULE]	= "Rescheduling interrupts",
	[IPI_CALL_FUNC]		= "Function call interrupts",
	[IPI_IRQ_WORK]		= "Irq work interrupts",
पूर्ण;

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	अचिन्हित पूर्णांक cpu, i;

	क्रम (i = 0; i < IPI_MAX; i++) अणु
		seq_म_लिखो(p, "%*s%u:%s", prec - 1, "IPI", i,
			   prec >= 4 ? " " : "");
		क्रम_each_online_cpu(cpu)
			seq_म_लिखो(p, "%10lu ",
				per_cpu_ptr(&ipi_data, cpu)->stats[i]);
		seq_म_लिखो(p, " %s\n", ipi_names[i]);
	पूर्ण

	वापस 0;
पूर्ण

व्योम arch_send_call_function_ipi_mask(काष्ठा cpumask *mask)
अणु
	send_ipi_message(mask, IPI_CALL_FUNC);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	send_ipi_message(cpumask_of(cpu), IPI_CALL_FUNC);
पूर्ण

अटल व्योम ipi_stop(व्योम *unused)
अणु
	जबतक (1);
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	on_each_cpu(ipi_stop, शून्य, 1);
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	send_ipi_message(cpumask_of(cpu), IPI_RESCHEDULE);
पूर्ण

#अगर_घोषित CONFIG_IRQ_WORK
व्योम arch_irq_work_उठाओ(व्योम)
अणु
	send_ipi_message(cpumask_of(smp_processor_id()), IPI_IRQ_WORK);
पूर्ण
#पूर्ण_अगर

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

अटल पूर्णांक ipi_dummy_dev;

व्योम __init setup_smp_ipi(व्योम)
अणु
	पूर्णांक rc;

	अगर (ipi_irq == 0)
		वापस;

	rc = request_percpu_irq(ipi_irq, handle_ipi, "IPI Interrupt",
				&ipi_dummy_dev);
	अगर (rc)
		panic("%s IRQ request failed\n", __func__);

	enable_percpu_irq(ipi_irq, 0);
पूर्ण

व्योम __init setup_smp(व्योम)
अणु
	काष्ठा device_node *node = शून्य;
	पूर्णांक cpu;

	क्रम_each_of_cpu_node(node) अणु
		अगर (!of_device_is_available(node))
			जारी;

		अगर (of_property_पढ़ो_u32(node, "reg", &cpu))
			जारी;

		अगर (cpu >= NR_CPUS)
			जारी;

		set_cpu_possible(cpu, true);
		set_cpu_present(cpu, true);
	पूर्ण
पूर्ण

बाह्य व्योम _start_smp_secondary(व्योम);

अस्थिर अचिन्हित पूर्णांक secondary_hपूर्णांक;
अस्थिर अचिन्हित पूर्णांक secondary_hपूर्णांक2;
अस्थिर अचिन्हित पूर्णांक secondary_ccr;
अस्थिर अचिन्हित पूर्णांक secondary_stack;
अस्थिर अचिन्हित पूर्णांक secondary_msa1;
अस्थिर अचिन्हित पूर्णांक secondary_pgd;

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	अचिन्हित दीर्घ mask = 1 << cpu;

	secondary_stack =
		(अचिन्हित पूर्णांक) task_stack_page(tidle) + THREAD_SIZE - 8;
	secondary_hपूर्णांक = mfcr("cr31");
	secondary_hपूर्णांक2 = mfcr("cr<21, 1>");
	secondary_ccr  = mfcr("cr18");
	secondary_msa1 = पढ़ो_mmu_msa1();
	secondary_pgd = mfcr("cr<29, 15>");

	/*
	 * Because other CPUs are in reset status, we must flush data
	 * from cache to out and secondary CPUs use them in
	 * csky_start_secondary(व्योम)
	 */
	mtcr("cr17", 0x22);

	अगर (mask & mfcr("cr<29, 0>")) अणु
		send_arch_ipi(cpumask_of(cpu));
	पूर्ण अन्यथा अणु
		/* Enable cpu in SMP reset ctrl reg */
		mask |= mfcr("cr<29, 0>");
		mtcr("cr<29, 0>", mask);
	पूर्ण

	/* Wait क्रम the cpu online */
	जबतक (!cpu_online(cpu));

	secondary_stack = 0;

	वापस 0;
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

व्योम csky_start_secondary(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = &init_mm;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	mtcr("cr31", secondary_hपूर्णांक);
	mtcr("cr<21, 1>", secondary_hपूर्णांक2);
	mtcr("cr18", secondary_ccr);

	mtcr("vbr", vec_base);

	flush_tlb_all();
	ग_लिखो_mmu_pagemask(0);

#अगर_घोषित CONFIG_CPU_HAS_FPU
	init_fpu();
#पूर्ण_अगर

	enable_percpu_irq(ipi_irq, 0);

	mmget(mm);
	mmgrab(mm);
	current->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	notअगरy_cpu_starting(cpu);
	set_cpu_online(cpu, true);

	pr_info("CPU%u Online: %s...\n", cpu, __func__);

	local_irq_enable();
	preempt_disable();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक __cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	set_cpu_online(cpu, false);

	irq_migrate_all_off_this_cpu();

	clear_tasks_mm_cpumask(cpu);

	वापस 0;
पूर्ण

व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!cpu_रुको_death(cpu, 5)) अणु
		pr_crit("CPU%u: shutdown failed\n", cpu);
		वापस;
	पूर्ण
	pr_notice("CPU%u: shutdown\n", cpu);
पूर्ण

व्योम arch_cpu_idle_dead(व्योम)
अणु
	idle_task_निकास();

	cpu_report_death();

	जबतक (!secondary_stack)
		arch_cpu_idle();

	local_irq_disable();

	यंत्र अस्थिर(
		"mov	sp, %0\n"
		"mov	r8, %0\n"
		"jmpi	csky_start_secondary"
		:
		: "r" (secondary_stack));
पूर्ण
#पूर्ण_अगर
