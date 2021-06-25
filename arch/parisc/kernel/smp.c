<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
** SMP Support
**
** Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
** Copyright (C) 1999 David Mosberger-Tang <davidm@hpl.hp.com>
** Copyright (C) 2001,2004 Grant Grundler <grundler@parisc-linux.org>
** 
** Lots of stuff stolen from arch/alpha/kernel/smp.c
** ...and then parisc stole from arch/ia64/kernel/smp.c. Thanks David! :^)
**
** Thanks to John Curry and Ullas Ponnadi. I learned a lot from their work.
** -grant (1/12/2001)
**
*/
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/cpu.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>		/* क्रम CPU_IRQ_REGION and मित्रs */
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/cacheflush.h>

#अघोषित DEBUG_SMP
#अगर_घोषित DEBUG_SMP
अटल पूर्णांक smp_debug_lvl = 0;
#घोषणा smp_debug(lvl, prपूर्णांकargs...)		\
		अगर (lvl >= smp_debug_lvl)	\
			prपूर्णांकk(prपूर्णांकargs);
#अन्यथा
#घोषणा smp_debug(lvl, ...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर /* DEBUG_SMP */

अस्थिर काष्ठा task_काष्ठा *smp_init_current_idle_task;

/* track which CPU is booting */
अटल अस्थिर पूर्णांक cpu_now_booting;

अटल पूर्णांक parisc_max_cpus = 1;

अटल DEFINE_PER_CPU(spinlock_t, ipi_lock);

क्रमागत ipi_message_type अणु
	IPI_NOP=0,
	IPI_RESCHEDULE=1,
	IPI_CALL_FUNC,
	IPI_CPU_START,
	IPI_CPU_STOP,
	IPI_CPU_TEST
पूर्ण;


/********** SMP पूर्णांकer processor पूर्णांकerrupt and communication routines */

#अघोषित PER_CPU_IRQ_REGION
#अगर_घोषित PER_CPU_IRQ_REGION
/* XXX REVISIT Ignore क्रम now.
**    *May* need this "hook" to रेजिस्टर IPI handler
**    once we have perCPU ExtIntr चयन tables.
*/
अटल व्योम
ipi_init(पूर्णांक cpuid)
अणु
#त्रुटि verअगरy IRQ_OFFSET(IPI_IRQ) is ipi_पूर्णांकerrupt() in new IRQ region

	अगर(cpu_online(cpuid) )
	अणु
		चयन_to_idle_task(current);
	पूर्ण

	वापस;
पूर्ण
#पूर्ण_अगर


/*
** Yoink this CPU from the runnable list... 
**
*/
अटल व्योम
halt_processor(व्योम) 
अणु
	/* REVISIT : redirect I/O Interrupts to another CPU? */
	/* REVISIT : करोes PM *know* this CPU isn't available? */
	set_cpu_online(smp_processor_id(), false);
	local_irq_disable();
	__pdc_cpu_rendezvous();
	क्रम (;;)
		;
पूर्ण


irqवापस_t __irq_entry
ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id) 
अणु
	पूर्णांक this_cpu = smp_processor_id();
	काष्ठा cpuinfo_parisc *p = &per_cpu(cpu_data, this_cpu);
	अचिन्हित दीर्घ ops;
	अचिन्हित दीर्घ flags;

	क्रम (;;) अणु
		spinlock_t *lock = &per_cpu(ipi_lock, this_cpu);
		spin_lock_irqsave(lock, flags);
		ops = p->pending_ipi;
		p->pending_ipi = 0;
		spin_unlock_irqrestore(lock, flags);

		mb(); /* Order bit clearing and data access. */

		अगर (!ops)
		    अवरोध;

		जबतक (ops) अणु
			अचिन्हित दीर्घ which = ffz(~ops);

			ops &= ~(1 << which);

			चयन (which) अणु
			हाल IPI_NOP:
				smp_debug(100, KERN_DEBUG "CPU%d IPI_NOP\n", this_cpu);
				अवरोध;
				
			हाल IPI_RESCHEDULE:
				smp_debug(100, KERN_DEBUG "CPU%d IPI_RESCHEDULE\n", this_cpu);
				inc_irq_stat(irq_resched_count);
				scheduler_ipi();
				अवरोध;

			हाल IPI_CALL_FUNC:
				smp_debug(100, KERN_DEBUG "CPU%d IPI_CALL_FUNC\n", this_cpu);
				inc_irq_stat(irq_call_count);
				generic_smp_call_function_पूर्णांकerrupt();
				अवरोध;

			हाल IPI_CPU_START:
				smp_debug(100, KERN_DEBUG "CPU%d IPI_CPU_START\n", this_cpu);
				अवरोध;

			हाल IPI_CPU_STOP:
				smp_debug(100, KERN_DEBUG "CPU%d IPI_CPU_STOP\n", this_cpu);
				halt_processor();
				अवरोध;

			हाल IPI_CPU_TEST:
				smp_debug(100, KERN_DEBUG "CPU%d is alive!\n", this_cpu);
				अवरोध;

			शेष:
				prपूर्णांकk(KERN_CRIT "Unknown IPI num on CPU%d: %lu\n",
					this_cpu, which);
				वापस IRQ_NONE;
			पूर्ण /* Switch */

			/* beक्रमe करोing more, let in any pending पूर्णांकerrupts */
			अगर (ops) अणु
				local_irq_enable();
				local_irq_disable();
			पूर्ण
		पूर्ण /* जबतक (ops) */
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


अटल अंतरभूत व्योम
ipi_send(पूर्णांक cpu, क्रमागत ipi_message_type op)
अणु
	काष्ठा cpuinfo_parisc *p = &per_cpu(cpu_data, cpu);
	spinlock_t *lock = &per_cpu(ipi_lock, cpu);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	p->pending_ipi |= 1 << op;
	gsc_ग_लिखोl(IPI_IRQ - CPU_IRQ_BASE, p->hpa);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल व्योम
send_IPI_mask(स्थिर काष्ठा cpumask *mask, क्रमागत ipi_message_type op)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		ipi_send(cpu, op);
पूर्ण

अटल अंतरभूत व्योम
send_IPI_single(पूर्णांक dest_cpu, क्रमागत ipi_message_type op)
अणु
	BUG_ON(dest_cpu == NO_PROC_ID);

	ipi_send(dest_cpu, op);
पूर्ण

अटल अंतरभूत व्योम
send_IPI_allbutself(क्रमागत ipi_message_type op)
अणु
	पूर्णांक i;
	
	क्रम_each_online_cpu(i) अणु
		अगर (i != smp_processor_id())
			send_IPI_single(i, op);
	पूर्ण
पूर्ण


अंतरभूत व्योम 
smp_send_stop(व्योम)	अणु send_IPI_allbutself(IPI_CPU_STOP); पूर्ण

व्योम 
smp_send_reschedule(पूर्णांक cpu) अणु send_IPI_single(cpu, IPI_RESCHEDULE); पूर्ण

व्योम
smp_send_all_nop(व्योम)
अणु
	send_IPI_allbutself(IPI_NOP);
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	send_IPI_mask(mask, IPI_CALL_FUNC);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	send_IPI_single(cpu, IPI_CALL_FUNC);
पूर्ण

/*
 * Called by secondaries to update state and initialize CPU रेजिस्टरs.
 */
अटल व्योम __init
smp_cpu_init(पूर्णांक cpunum)
अणु
	बाह्य व्योम init_IRQ(व्योम);    /* arch/parisc/kernel/irq.c */
	बाह्य व्योम start_cpu_iसमयr(व्योम); /* arch/parisc/kernel/समय.c */

	/* Set modes and Enable भग्नing poपूर्णांक coprocessor */
	init_per_cpu(cpunum);

	disable_sr_hashing();

	mb();

	/* Well, support 2.4 linux scheme as well. */
	अगर (cpu_online(cpunum))	अणु
		बाह्य व्योम machine_halt(व्योम); /* arch/parisc.../process.c */

		prपूर्णांकk(KERN_CRIT "CPU#%d already initialized!\n", cpunum);
		machine_halt();
	पूर्ण

	notअगरy_cpu_starting(cpunum);

	set_cpu_online(cpunum, true);

	/* Initialise the idle task क्रम this CPU */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;
	BUG_ON(current->mm);
	enter_lazy_tlb(&init_mm, current);

	init_IRQ();   /* make sure no IRQs are enabled or pending */
	start_cpu_iसमयr();
पूर्ण


/*
 * Slaves start using C here. Indirectly called from smp_slave_stext.
 * Do what start_kernel() and मुख्य() करो क्रम boot strap processor (aka monarch)
 */
व्योम __init smp_callin(अचिन्हित दीर्घ pdce_proc)
अणु
	पूर्णांक slave_id = cpu_now_booting;

#अगर_घोषित CONFIG_64BIT
	WARN_ON(((अचिन्हित दीर्घ)(PAGE0->mem_pdc_hi) << 32
			| PAGE0->mem_pdc) != pdce_proc);
#पूर्ण_अगर

	smp_cpu_init(slave_id);
	preempt_disable();

	flush_cache_all_local(); /* start with known state */
	flush_tlb_all_local(शून्य);

	local_irq_enable();  /* Interrupts have been off until now */

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);

	/* NOTREACHED */
	panic("smp_callin() AAAAaaaaahhhh....\n");
पूर्ण

/*
 * Bring one cpu online.
 */
पूर्णांक smp_boot_one_cpu(पूर्णांक cpuid, काष्ठा task_काष्ठा *idle)
अणु
	स्थिर काष्ठा cpuinfo_parisc *p = &per_cpu(cpu_data, cpuid);
	दीर्घ समयout;

	task_thपढ़ो_info(idle)->cpu = cpuid;

	/* Let _start know what logical CPU we're booting
	** (offset पूर्णांकo init_tasks[],cpu_data[])
	*/
	cpu_now_booting = cpuid;

	/* 
	** boot strap code needs to know the task address since
	** it also contains the process stack.
	*/
	smp_init_current_idle_task = idle ;
	mb();

	prपूर्णांकk(KERN_INFO "Releasing cpu %d now, hpa=%lx\n", cpuid, p->hpa);

	/*
	** This माला_लो PDC to release the CPU from a very tight loop.
	**
	** From the PA-RISC 2.0 Firmware Architecture Reference Specअगरication:
	** "The MEM_RENDEZ vector specअगरies the location of OS_RENDEZ which 
	** is executed after receiving the rendezvous संकेत (an पूर्णांकerrupt to 
	** EIRअणु0पूर्ण). MEM_RENDEZ is valid only when it is nonzero and the 
	** contents of memory are valid."
	*/
	gsc_ग_लिखोl(TIMER_IRQ - CPU_IRQ_BASE, p->hpa);
	mb();

	/* 
	 * OK, रुको a bit क्रम that CPU to finish staggering about. 
	 * Slave will set a bit when it reaches smp_cpu_init().
	 * Once the "monarch CPU" sees the bit change, it can move on.
	 */
	क्रम (समयout = 0; समयout < 10000; समयout++) अणु
		अगर(cpu_online(cpuid)) अणु
			/* Which implies Slave has started up */
			cpu_now_booting = 0;
			smp_init_current_idle_task = शून्य;
			जाओ alive ;
		पूर्ण
		udelay(100);
		barrier();
	पूर्ण
	prपूर्णांकk(KERN_CRIT "SMP: CPU:%d is stuck.\n", cpuid);
	वापस -1;

alive:
	/* Remember the Slave data */
	smp_debug(100, KERN_DEBUG "SMP: CPU:%d came alive after %ld _us\n",
		cpuid, समयout * 100);
	वापस 0;
पूर्ण

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
	पूर्णांक bootstrap_processor = per_cpu(cpu_data, 0).cpuid;

	/* Setup BSP mappings */
	prपूर्णांकk(KERN_INFO "SMP: bootstrap CPU ID is %d\n", bootstrap_processor);

	set_cpu_online(bootstrap_processor, true);
	set_cpu_present(bootstrap_processor, true);
पूर्ण



/*
** inventory.c:करो_inventory() hasn't yet been run and thus we
** करोn't 'discover' the additional CPUs until later.
*/
व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		spin_lock_init(&per_cpu(ipi_lock, cpu));

	init_cpu_present(cpumask_of(0));

	parisc_max_cpus = max_cpus;
	अगर (!max_cpus)
		prपूर्णांकk(KERN_INFO "SMP mode deactivated.\n");
पूर्ण


व्योम smp_cpus_करोne(अचिन्हित पूर्णांक cpu_max)
अणु
	वापस;
पूर्ण


पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	अगर (cpu != 0 && cpu < parisc_max_cpus && smp_boot_one_cpu(cpu, tidle))
		वापस -ENOSYS;

	वापस cpu_online(cpu) ? 0 : -ENOSYS;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर
