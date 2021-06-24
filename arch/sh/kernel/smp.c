<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/smp.c
 *
 * SMP support क्रम the SuperH processors.
 *
 * Copyright (C) 2002 - 2010 Paul Mundt
 * Copyright (C) 2006 - 2007 Akio Idehara
 */
#समावेश <linux/err.h>
#समावेश <linux/cache.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/cpu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/atomic.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>

पूर्णांक __cpu_number_map[NR_CPUS];		/* Map physical to logical */
पूर्णांक __cpu_logical_map[NR_CPUS];		/* Map logical to physical */

काष्ठा plat_smp_ops *mp_ops = शून्य;

/* State of each CPU */
DEFINE_PER_CPU(पूर्णांक, cpu_state) = अणु 0 पूर्ण;

व्योम रेजिस्टर_smp_ops(काष्ठा plat_smp_ops *ops)
अणु
	अगर (mp_ops)
		prपूर्णांकk(KERN_WARNING "Overriding previously set SMP ops\n");

	mp_ops = ops;
पूर्ण

अटल अंतरभूत व्योम smp_store_cpu_info(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा sh_cpuinfo *c = cpu_data + cpu;

	स_नकल(c, &boot_cpu_data, माप(काष्ठा sh_cpuinfo));

	c->loops_per_jअगरfy = loops_per_jअगरfy;
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	init_new_context(current, &init_mm);
	current_thपढ़ो_info()->cpu = cpu;
	mp_ops->prepare_cpus(max_cpus);

#अगर_अघोषित CONFIG_HOTPLUG_CPU
	init_cpu_present(cpu_possible_mask);
#पूर्ण_अगर
पूर्ण

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	__cpu_number_map[0] = cpu;
	__cpu_logical_map[0] = cpu;

	set_cpu_online(cpu, true);
	set_cpu_possible(cpu, true);

	per_cpu(cpu_state, cpu) = CPU_ONLINE;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम native_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		smp_rmb();
		अगर (per_cpu(cpu_state, cpu) == CPU_DEAD) अणु
			अगर (प्रणाली_state == SYSTEM_RUNNING)
				pr_info("CPU %u is now offline\n", cpu);

			वापस;
		पूर्ण

		msleep(100);
	पूर्ण

	pr_err("CPU %u didn't die...\n", cpu);
पूर्ण

पूर्णांक native_cpu_disable(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpu == 0 ? -EPERM : 0;
पूर्ण

व्योम play_dead_common(व्योम)
अणु
	idle_task_निकास();
	irq_ctx_निकास(raw_smp_processor_id());
	mb();

	__this_cpu_ग_लिखो(cpu_state, CPU_DEAD);
	local_irq_disable();
पूर्ण

व्योम native_play_dead(व्योम)
अणु
	play_dead_common();
पूर्ण

पूर्णांक __cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक ret;

	ret = mp_ops->cpu_disable(cpu);
	अगर (ret)
		वापस ret;

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
	flush_cache_all();
#अगर_घोषित CONFIG_MMU
	local_flush_tlb_all();
#पूर्ण_अगर

	clear_tasks_mm_cpumask(cpu);

	वापस 0;
पूर्ण
#अन्यथा /* ... !CONFIG_HOTPLUG_CPU */
पूर्णांक native_cpu_disable(अचिन्हित पूर्णांक cpu)
अणु
	वापस -ENOSYS;
पूर्ण

व्योम native_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	/* We said "no" in __cpu_disable */
	BUG();
पूर्ण

व्योम native_play_dead(व्योम)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर

यंत्रlinkage व्योम start_secondary(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा mm_काष्ठा *mm = &init_mm;

	enable_mmu();
	mmgrab(mm);
	mmget(mm);
	current->active_mm = mm;
#अगर_घोषित CONFIG_MMU
	enter_lazy_tlb(mm, current);
	local_flush_tlb_all();
#पूर्ण_अगर

	per_cpu_trap_init();

	preempt_disable();

	notअगरy_cpu_starting(cpu);

	local_irq_enable();

	calibrate_delay();

	smp_store_cpu_info(cpu);

	set_cpu_online(cpu, true);
	per_cpu(cpu_state, cpu) = CPU_ONLINE;

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

बाह्य काष्ठा अणु
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ bss_start;
	अचिन्हित दीर्घ bss_end;
	व्योम *start_kernel_fn;
	व्योम *cpu_init_fn;
	व्योम *thपढ़ो_info;
पूर्ण stack_start;

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ समयout;

	per_cpu(cpu_state, cpu) = CPU_UP_PREPARE;

	/* Fill in data in head.S क्रम secondary cpus */
	stack_start.sp = tsk->thपढ़ो.sp;
	stack_start.thपढ़ो_info = tsk->stack;
	stack_start.bss_start = 0; /* करोn't clear bss क्रम secondary cpus */
	stack_start.start_kernel_fn = start_secondary;

	flush_icache_range((अचिन्हित दीर्घ)&stack_start,
			   (अचिन्हित दीर्घ)&stack_start + माप(stack_start));
	wmb();

	mp_ops->start_cpu(cpu, (अचिन्हित दीर्घ)_stext);

	समयout = jअगरfies + HZ;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (cpu_online(cpu))
			अवरोध;

		udelay(10);
		barrier();
	पूर्ण

	अगर (cpu_online(cpu))
		वापस 0;

	वापस -ENOENT;
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित दीर्घ bogosum = 0;
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		bogosum += cpu_data[cpu].loops_per_jअगरfy;

	prपूर्णांकk(KERN_INFO "SMP: Total of %d processors activated "
	       "(%lu.%02lu BogoMIPS).\n", num_online_cpus(),
	       bogosum / (500000/HZ),
	       (bogosum / (5000/HZ)) % 100);
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	mp_ops->send_ipi(cpu, SMP_MSG_RESCHEDULE);
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	smp_call_function(stop_this_cpu, 0, 0);
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		mp_ops->send_ipi(cpu, SMP_MSG_FUNCTION);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	mp_ops->send_ipi(cpu, SMP_MSG_FUNCTION_SINGLE);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
व्योम tick_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		mp_ops->send_ipi(cpu, SMP_MSG_TIMER);
पूर्ण

अटल व्योम ipi_समयr(व्योम)
अणु
	irq_enter();
	tick_receive_broadcast();
	irq_निकास();
पूर्ण
#पूर्ण_अगर

व्योम smp_message_recv(अचिन्हित पूर्णांक msg)
अणु
	चयन (msg) अणु
	हाल SMP_MSG_FUNCTION:
		generic_smp_call_function_पूर्णांकerrupt();
		अवरोध;
	हाल SMP_MSG_RESCHEDULE:
		scheduler_ipi();
		अवरोध;
	हाल SMP_MSG_FUNCTION_SINGLE:
		generic_smp_call_function_single_पूर्णांकerrupt();
		अवरोध;
#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	हाल SMP_MSG_TIMER:
		ipi_समयr();
		अवरोध;
#पूर्ण_अगर
	शेष:
		prपूर्णांकk(KERN_WARNING "SMP %d: %s(): unknown IPI %d\n",
		       smp_processor_id(), __func__, msg);
		अवरोध;
	पूर्ण
पूर्ण

/* Not really SMP stuff ... */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MMU

अटल व्योम flush_tlb_all_ipi(व्योम *info)
अणु
	local_flush_tlb_all();
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	on_each_cpu(flush_tlb_all_ipi, 0, 1);
पूर्ण

अटल व्योम flush_tlb_mm_ipi(व्योम *mm)
अणु
	local_flush_tlb_mm((काष्ठा mm_काष्ठा *)mm);
पूर्ण

/*
 * The following tlb flush calls are invoked when old translations are
 * being torn करोwn, or pte attributes are changing. For single thपढ़ोed
 * address spaces, a new context is obtained on the current cpu, and tlb
 * context on other cpus are invalidated to क्रमce a new context allocation
 * at चयन_mm समय, should the mm ever be used on other cpus. For
 * multithपढ़ोed address spaces, पूर्णांकercpu पूर्णांकerrupts have to be sent.
 * Another हाल where पूर्णांकercpu पूर्णांकerrupts are required is when the target
 * mm might be active on another cpu (eg debuggers करोing the flushes on
 * behalf of debugees, kswapd stealing pages from another process etc).
 * Kanoj 07/00.
 */
व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	preempt_disable();

	अगर ((atomic_पढ़ो(&mm->mm_users) != 1) || (current->mm != mm)) अणु
		smp_call_function(flush_tlb_mm_ipi, (व्योम *)mm, 1);
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		क्रम_each_online_cpu(i)
			अगर (smp_processor_id() != i)
				cpu_context(i, mm) = 0;
	पूर्ण
	local_flush_tlb_mm(mm);

	preempt_enable();
पूर्ण

काष्ठा flush_tlb_data अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr1;
	अचिन्हित दीर्घ addr2;
पूर्ण;

अटल व्योम flush_tlb_range_ipi(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = (काष्ठा flush_tlb_data *)info;

	local_flush_tlb_range(fd->vma, fd->addr1, fd->addr2);
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	preempt_disable();
	अगर ((atomic_पढ़ो(&mm->mm_users) != 1) || (current->mm != mm)) अणु
		काष्ठा flush_tlb_data fd;

		fd.vma = vma;
		fd.addr1 = start;
		fd.addr2 = end;
		smp_call_function(flush_tlb_range_ipi, (व्योम *)&fd, 1);
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		क्रम_each_online_cpu(i)
			अगर (smp_processor_id() != i)
				cpu_context(i, mm) = 0;
	पूर्ण
	local_flush_tlb_range(vma, start, end);
	preempt_enable();
पूर्ण

अटल व्योम flush_tlb_kernel_range_ipi(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = (काष्ठा flush_tlb_data *)info;

	local_flush_tlb_kernel_range(fd->addr1, fd->addr2);
पूर्ण

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा flush_tlb_data fd;

	fd.addr1 = start;
	fd.addr2 = end;
	on_each_cpu(flush_tlb_kernel_range_ipi, (व्योम *)&fd, 1);
पूर्ण

अटल व्योम flush_tlb_page_ipi(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = (काष्ठा flush_tlb_data *)info;

	local_flush_tlb_page(fd->vma, fd->addr1);
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	preempt_disable();
	अगर ((atomic_पढ़ो(&vma->vm_mm->mm_users) != 1) ||
	    (current->mm != vma->vm_mm)) अणु
		काष्ठा flush_tlb_data fd;

		fd.vma = vma;
		fd.addr1 = page;
		smp_call_function(flush_tlb_page_ipi, (व्योम *)&fd, 1);
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		क्रम_each_online_cpu(i)
			अगर (smp_processor_id() != i)
				cpu_context(i, vma->vm_mm) = 0;
	पूर्ण
	local_flush_tlb_page(vma, page);
	preempt_enable();
पूर्ण

अटल व्योम flush_tlb_one_ipi(व्योम *info)
अणु
	काष्ठा flush_tlb_data *fd = (काष्ठा flush_tlb_data *)info;
	local_flush_tlb_one(fd->addr1, fd->addr2);
पूर्ण

व्योम flush_tlb_one(अचिन्हित दीर्घ asid, अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा flush_tlb_data fd;

	fd.addr1 = asid;
	fd.addr2 = vaddr;

	smp_call_function(flush_tlb_one_ipi, (व्योम *)&fd, 1);
	local_flush_tlb_one(asid, vaddr);
पूर्ण

#पूर्ण_अगर
