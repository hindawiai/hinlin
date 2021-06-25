<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  sun4m SMP support.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/profile.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/oplib.h>

#समावेश "irq.h"
#समावेश "kernel.h"

#घोषणा IRQ_IPI_SINGLE		12
#घोषणा IRQ_IPI_MASK		13
#घोषणा IRQ_IPI_RESCHED		14
#घोषणा IRQ_CROSS_CALL		15

अटल अंतरभूत अचिन्हित दीर्घ
swap_uदीर्घ(अस्थिर अचिन्हित दीर्घ *ptr, अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__("swap [%1], %0\n\t" :
			     "=&r" (val), "=&r" (ptr) :
			     "0" (val), "1" (ptr));
	वापस val;
पूर्ण

व्योम sun4m_cpu_pre_starting(व्योम *arg)
अणु
पूर्ण

व्योम sun4m_cpu_pre_online(व्योम *arg)
अणु
	पूर्णांक cpuid = hard_smp_processor_id();

	/* Allow master to जारी. The master will then give us the
	 * go-ahead by setting the smp_commenced_mask and will रुको without
	 * समयouts until our setup is completed fully (signअगरied by
	 * our bit being set in the cpu_online_mask).
	 */
	swap_uदीर्घ(&cpu_callin_map[cpuid], 1);

	/* XXX: What's up with all the flushes? */
	local_ops->cache_all();
	local_ops->tlb_all();

	/* Fix idle thपढ़ो fields. */
	__यंत्र__ __अस्थिर__("ld [%0], %%g6\n\t"
			     : : "r" (&current_set[cpuid])
			     : "memory" /* paranoid */);

	/* Attach to the address space of init_task. */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	जबतक (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		mb();
पूर्ण

/*
 *	Cycle through the processors asking the PROM to start each one.
 */
व्योम __init smp4m_boot_cpus(व्योम)
अणु
	sun4m_unmask_profile_irq();
	local_ops->cache_all();
पूर्ण

पूर्णांक smp4m_boot_one_cpu(पूर्णांक i, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ *entry = &sun4m_cpu_startup;
	पूर्णांक समयout;
	पूर्णांक cpu_node;

	cpu_find_by_mid(i, &cpu_node);
	current_set[i] = task_thपढ़ो_info(idle);

	/* See trampoline.S क्रम details... */
	entry += ((i - 1) * 3);

	/*
	 * Initialize the contexts table
	 * Since the call to prom_startcpu() trashes the काष्ठाure,
	 * we need to re-initialize it क्रम each cpu
	 */
	smp_penguin_ctable.which_io = 0;
	smp_penguin_ctable.phys_addr = (अचिन्हित पूर्णांक) srmmu_ctx_table_phys;
	smp_penguin_ctable.reg_size = 0;

	/* whirrr, whirrr, whirrrrrrrrr... */
	prपूर्णांकk(KERN_INFO "Starting CPU %d at %p\n", i, entry);
	local_ops->cache_all();
	prom_startcpu(cpu_node, &smp_penguin_ctable, 0, (अक्षर *)entry);

	/* wheee... it's going... */
	क्रम (समयout = 0; समयout < 10000; समयout++) अणु
		अगर (cpu_callin_map[i])
			अवरोध;
		udelay(200);
	पूर्ण

	अगर (!(cpu_callin_map[i])) अणु
		prपूर्णांकk(KERN_ERR "Processor %d is stuck.\n", i);
		वापस -ENODEV;
	पूर्ण

	local_ops->cache_all();
	वापस 0;
पूर्ण

व्योम __init smp4m_smp_करोne(व्योम)
अणु
	पूर्णांक i, first;
	पूर्णांक *prev;

	/* setup cpu list क्रम irq rotation */
	first = 0;
	prev = &first;
	क्रम_each_online_cpu(i) अणु
		*prev = i;
		prev = &cpu_data(i).next;
	पूर्ण
	*prev = first;
	local_ops->cache_all();

	/* Ok, they are spinning and पढ़ोy to go. */
पूर्ण

अटल व्योम sun4m_send_ipi(पूर्णांक cpu, पूर्णांक level)
अणु
	sbus_ग_लिखोl(SUN4M_SOFT_INT(level), &sun4m_irq_percpu[cpu]->set);
पूर्ण

अटल व्योम sun4m_ipi_resched(पूर्णांक cpu)
अणु
	sun4m_send_ipi(cpu, IRQ_IPI_RESCHED);
पूर्ण

अटल व्योम sun4m_ipi_single(पूर्णांक cpu)
अणु
	sun4m_send_ipi(cpu, IRQ_IPI_SINGLE);
पूर्ण

अटल व्योम sun4m_ipi_mask_one(पूर्णांक cpu)
अणु
	sun4m_send_ipi(cpu, IRQ_IPI_MASK);
पूर्ण

अटल काष्ठा smp_funcall अणु
	smpfunc_t func;
	अचिन्हित दीर्घ arg1;
	अचिन्हित दीर्घ arg2;
	अचिन्हित दीर्घ arg3;
	अचिन्हित दीर्घ arg4;
	अचिन्हित दीर्घ arg5;
	अचिन्हित दीर्घ processors_in[SUN4M_NCPUS];  /* Set when ipi entered. */
	अचिन्हित दीर्घ processors_out[SUN4M_NCPUS]; /* Set when ipi निकासed. */
पूर्ण ccall_info;

अटल DEFINE_SPINLOCK(cross_call_lock);

/* Cross calls must be serialized, at least currently. */
अटल व्योम sun4m_cross_call(smpfunc_t func, cpumask_t mask, अचिन्हित दीर्घ arg1,
			     अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			     अचिन्हित दीर्घ arg4)
अणु
		रेजिस्टर पूर्णांक ncpus = SUN4M_NCPUS;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&cross_call_lock, flags);

		/* Init function glue. */
		ccall_info.func = func;
		ccall_info.arg1 = arg1;
		ccall_info.arg2 = arg2;
		ccall_info.arg3 = arg3;
		ccall_info.arg4 = arg4;
		ccall_info.arg5 = 0;

		/* Init receive/complete mapping, plus fire the IPI's off. */
		अणु
			रेजिस्टर पूर्णांक i;

			cpumask_clear_cpu(smp_processor_id(), &mask);
			cpumask_and(&mask, cpu_online_mask, &mask);
			क्रम (i = 0; i < ncpus; i++) अणु
				अगर (cpumask_test_cpu(i, &mask)) अणु
					ccall_info.processors_in[i] = 0;
					ccall_info.processors_out[i] = 0;
					sun4m_send_ipi(i, IRQ_CROSS_CALL);
				पूर्ण अन्यथा अणु
					ccall_info.processors_in[i] = 1;
					ccall_info.processors_out[i] = 1;
				पूर्ण
			पूर्ण
		पूर्ण

		अणु
			रेजिस्टर पूर्णांक i;

			i = 0;
			करो अणु
				अगर (!cpumask_test_cpu(i, &mask))
					जारी;
				जबतक (!ccall_info.processors_in[i])
					barrier();
			पूर्ण जबतक (++i < ncpus);

			i = 0;
			करो अणु
				अगर (!cpumask_test_cpu(i, &mask))
					जारी;
				जबतक (!ccall_info.processors_out[i])
					barrier();
			पूर्ण जबतक (++i < ncpus);
		पूर्ण
		spin_unlock_irqrestore(&cross_call_lock, flags);
पूर्ण

/* Running cross calls. */
व्योम smp4m_cross_call_irq(व्योम)
अणु
	पूर्णांक i = smp_processor_id();

	ccall_info.processors_in[i] = 1;
	ccall_info.func(ccall_info.arg1, ccall_info.arg2, ccall_info.arg3,
			ccall_info.arg4, ccall_info.arg5);
	ccall_info.processors_out[i] = 1;
पूर्ण

व्योम smp4m_percpu_समयr_पूर्णांकerrupt(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;
	काष्ठा घड़ी_event_device *ce;
	पूर्णांक cpu = smp_processor_id();

	old_regs = set_irq_regs(regs);

	ce = &per_cpu(sparc32_घड़ीevent, cpu);

	अगर (घड़ीevent_state_periodic(ce))
		sun4m_clear_profile_irq(cpu);
	अन्यथा
		sparc_config.load_profile_irq(cpu, 0); /* Is this needless? */

	irq_enter();
	ce->event_handler(ce);
	irq_निकास();

	set_irq_regs(old_regs);
पूर्ण

अटल स्थिर काष्ठा sparc32_ipi_ops sun4m_ipi_ops = अणु
	.cross_call = sun4m_cross_call,
	.resched    = sun4m_ipi_resched,
	.single     = sun4m_ipi_single,
	.mask_one   = sun4m_ipi_mask_one,
पूर्ण;

व्योम __init sun4m_init_smp(व्योम)
अणु
	sparc32_ipi_ops = &sun4m_ipi_ops;
पूर्ण
