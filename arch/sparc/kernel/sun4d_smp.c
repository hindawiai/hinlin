<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Sparc SS1000/SC2000 SMP support.
 *
 * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *
 * Based on sun4m's smp.c, which is:
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
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/mmu.h>

#समावेश "kernel.h"
#समावेश "irq.h"

#घोषणा IRQ_CROSS_CALL		15

अटल अस्थिर पूर्णांक smp_processors_पढ़ोy;
अटल पूर्णांक smp_highest_cpu;

अटल अंतरभूत अचिन्हित दीर्घ sun4d_swap(अस्थिर अचिन्हित दीर्घ *ptr, अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__("swap [%1], %0\n\t" :
			     "=&r" (val), "=&r" (ptr) :
			     "0" (val), "1" (ptr));
	वापस val;
पूर्ण

अटल व्योम smp4d_ipi_init(व्योम);

अटल अचिन्हित अक्षर cpu_leds[32];

अटल अंतरभूत व्योम show_leds(पूर्णांक cpuid)
अणु
	cpuid &= 0x1e;
	__यंत्र__ __अस्थिर__ ("stba %0, [%1] %2" : :
			      "r" ((cpu_leds[cpuid] << 4) | cpu_leds[cpuid+1]),
			      "r" (ECSR_BASE(cpuid) | BB_LEDS),
			      "i" (ASI_M_CTL));
पूर्ण

व्योम sun4d_cpu_pre_starting(व्योम *arg)
अणु
	पूर्णांक cpuid = hard_smp_processor_id();

	/* Show we are alive */
	cpu_leds[cpuid] = 0x6;
	show_leds(cpuid);

	/* Enable level15 पूर्णांकerrupt, disable level14 पूर्णांकerrupt क्रम now */
	cc_set_imsk((cc_get_imsk() & ~0x8000) | 0x4000);
पूर्ण

व्योम sun4d_cpu_pre_online(व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpuid;

	cpuid = hard_smp_processor_id();

	/* Unblock the master CPU _only_ when the scheduler state
	 * of all secondary CPUs will be up-to-date, so after
	 * the SMP initialization the master will be just allowed
	 * to call the scheduler code.
	 */
	sun4d_swap((अचिन्हित दीर्घ *)&cpu_callin_map[cpuid], 1);
	local_ops->cache_all();
	local_ops->tlb_all();

	जबतक ((अचिन्हित दीर्घ)current_set[cpuid] < PAGE_OFFSET)
		barrier();

	जबतक (current_set[cpuid]->cpu != cpuid)
		barrier();

	/* Fix idle thपढ़ो fields. */
	__यंत्र__ __अस्थिर__("ld [%0], %%g6\n\t"
			     : : "r" (&current_set[cpuid])
			     : "memory" /* paranoid */);

	cpu_leds[cpuid] = 0x9;
	show_leds(cpuid);

	/* Attach to the address space of init_task. */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	local_ops->cache_all();
	local_ops->tlb_all();

	जबतक (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		barrier();

	spin_lock_irqsave(&sun4d_imsk_lock, flags);
	cc_set_imsk(cc_get_imsk() & ~0x4000); /* Allow PIL 14 as well */
	spin_unlock_irqrestore(&sun4d_imsk_lock, flags);
पूर्ण

/*
 *	Cycle through the processors asking the PROM to start each one.
 */
व्योम __init smp4d_boot_cpus(व्योम)
अणु
	smp4d_ipi_init();
	अगर (boot_cpu_id)
		current_set[0] = शून्य;
	local_ops->cache_all();
पूर्ण

पूर्णांक smp4d_boot_one_cpu(पूर्णांक i, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ *entry = &sun4d_cpu_startup;
	पूर्णांक समयout;
	पूर्णांक cpu_node;

	cpu_find_by_instance(i, &cpu_node, शून्य);
	current_set[i] = task_thपढ़ो_info(idle);
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
	prom_startcpu(cpu_node,
		      &smp_penguin_ctable, 0, (अक्षर *)entry);

	prपूर्णांकk(KERN_INFO "prom_startcpu returned :)\n");

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

व्योम __init smp4d_smp_करोne(व्योम)
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
	smp_processors_पढ़ोy = 1;
	sun4d_distribute_irqs();
पूर्ण

/* Memory काष्ठाure giving पूर्णांकerrupt handler inक्रमmation about IPI generated */
काष्ठा sun4d_ipi_work अणु
	पूर्णांक single;
	पूर्णांक msk;
	पूर्णांक resched;
पूर्ण;

अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा sun4d_ipi_work, sun4d_ipi_work);

/* Initialize IPIs on the SUN4D SMP machine */
अटल व्योम __init smp4d_ipi_init(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा sun4d_ipi_work *work;

	prपूर्णांकk(KERN_INFO "smp4d: setup IPI at IRQ %d\n", SUN4D_IPI_IRQ);

	क्रम_each_possible_cpu(cpu) अणु
		work = &per_cpu(sun4d_ipi_work, cpu);
		work->single = work->msk = work->resched = 0;
	पूर्ण
पूर्ण

व्योम sun4d_ipi_पूर्णांकerrupt(व्योम)
अणु
	काष्ठा sun4d_ipi_work *work = this_cpu_ptr(&sun4d_ipi_work);

	अगर (work->single) अणु
		work->single = 0;
		smp_call_function_single_पूर्णांकerrupt();
	पूर्ण
	अगर (work->msk) अणु
		work->msk = 0;
		smp_call_function_पूर्णांकerrupt();
	पूर्ण
	अगर (work->resched) अणु
		work->resched = 0;
		smp_resched_पूर्णांकerrupt();
	पूर्ण
पूर्ण

/* +-------+-------------+-----------+------------------------------------+
 * | bcast |  devid      |   sid     |              levels mask           |
 * +-------+-------------+-----------+------------------------------------+
 *  31      30         23 22       15 14                                 0
 */
#घोषणा IGEN_MESSAGE(bcast, devid, sid, levels) \
	(((bcast) << 31) | ((devid) << 23) | ((sid) << 15) | (levels))

अटल व्योम sun4d_send_ipi(पूर्णांक cpu, पूर्णांक level)
अणु
	cc_set_igen(IGEN_MESSAGE(0, cpu << 3, 6 + ((level >> 1) & 7), 1 << (level - 1)));
पूर्ण

अटल व्योम sun4d_ipi_single(पूर्णांक cpu)
अणु
	काष्ठा sun4d_ipi_work *work = &per_cpu(sun4d_ipi_work, cpu);

	/* Mark work */
	work->single = 1;

	/* Generate IRQ on the CPU */
	sun4d_send_ipi(cpu, SUN4D_IPI_IRQ);
पूर्ण

अटल व्योम sun4d_ipi_mask_one(पूर्णांक cpu)
अणु
	काष्ठा sun4d_ipi_work *work = &per_cpu(sun4d_ipi_work, cpu);

	/* Mark work */
	work->msk = 1;

	/* Generate IRQ on the CPU */
	sun4d_send_ipi(cpu, SUN4D_IPI_IRQ);
पूर्ण

अटल व्योम sun4d_ipi_resched(पूर्णांक cpu)
अणु
	काष्ठा sun4d_ipi_work *work = &per_cpu(sun4d_ipi_work, cpu);

	/* Mark work */
	work->resched = 1;

	/* Generate IRQ on the CPU (any IRQ will cause resched) */
	sun4d_send_ipi(cpu, SUN4D_IPI_IRQ);
पूर्ण

अटल काष्ठा smp_funcall अणु
	smpfunc_t func;
	अचिन्हित दीर्घ arg1;
	अचिन्हित दीर्घ arg2;
	अचिन्हित दीर्घ arg3;
	अचिन्हित दीर्घ arg4;
	अचिन्हित दीर्घ arg5;
	अचिन्हित अक्षर processors_in[NR_CPUS];  /* Set when ipi entered. */
	अचिन्हित अक्षर processors_out[NR_CPUS]; /* Set when ipi निकासed. */
पूर्ण ccall_info __attribute__((aligned(8)));

अटल DEFINE_SPINLOCK(cross_call_lock);

/* Cross calls must be serialized, at least currently. */
अटल व्योम sun4d_cross_call(smpfunc_t func, cpumask_t mask, अचिन्हित दीर्घ arg1,
			     अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			     अचिन्हित दीर्घ arg4)
अणु
	अगर (smp_processors_पढ़ोy) अणु
		रेजिस्टर पूर्णांक high = smp_highest_cpu;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&cross_call_lock, flags);

		अणु
			/*
			 * If you make changes here, make sure
			 * gcc generates proper code...
			 */
			रेजिस्टर smpfunc_t f यंत्र("i0") = func;
			रेजिस्टर अचिन्हित दीर्घ a1 यंत्र("i1") = arg1;
			रेजिस्टर अचिन्हित दीर्घ a2 यंत्र("i2") = arg2;
			रेजिस्टर अचिन्हित दीर्घ a3 यंत्र("i3") = arg3;
			रेजिस्टर अचिन्हित दीर्घ a4 यंत्र("i4") = arg4;
			रेजिस्टर अचिन्हित दीर्घ a5 यंत्र("i5") = 0;

			__यंत्र__ __अस्थिर__(
				"std %0, [%6]\n\t"
				"std %2, [%6 + 8]\n\t"
				"std %4, [%6 + 16]\n\t" : :
				"r"(f), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5),
				"r" (&ccall_info.func));
		पूर्ण

		/* Init receive/complete mapping, plus fire the IPI's off. */
		अणु
			रेजिस्टर पूर्णांक i;

			cpumask_clear_cpu(smp_processor_id(), &mask);
			cpumask_and(&mask, cpu_online_mask, &mask);
			क्रम (i = 0; i <= high; i++) अणु
				अगर (cpumask_test_cpu(i, &mask)) अणु
					ccall_info.processors_in[i] = 0;
					ccall_info.processors_out[i] = 0;
					sun4d_send_ipi(i, IRQ_CROSS_CALL);
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
			पूर्ण जबतक (++i <= high);

			i = 0;
			करो अणु
				अगर (!cpumask_test_cpu(i, &mask))
					जारी;
				जबतक (!ccall_info.processors_out[i])
					barrier();
			पूर्ण जबतक (++i <= high);
		पूर्ण

		spin_unlock_irqrestore(&cross_call_lock, flags);
	पूर्ण
पूर्ण

/* Running cross calls. */
व्योम smp4d_cross_call_irq(व्योम)
अणु
	पूर्णांक i = hard_smp_processor_id();

	ccall_info.processors_in[i] = 1;
	ccall_info.func(ccall_info.arg1, ccall_info.arg2, ccall_info.arg3,
			ccall_info.arg4, ccall_info.arg5);
	ccall_info.processors_out[i] = 1;
पूर्ण

व्योम smp4d_percpu_समयr_पूर्णांकerrupt(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;
	पूर्णांक cpu = hard_smp_processor_id();
	काष्ठा घड़ी_event_device *ce;
	अटल पूर्णांक cpu_tick[NR_CPUS];
	अटल अक्षर led_mask[] = अणु 0xe, 0xd, 0xb, 0x7, 0xb, 0xd पूर्ण;

	old_regs = set_irq_regs(regs);
	bw_get_prof_limit(cpu);
	bw_clear_पूर्णांकr_mask(0, 1);	/* INTR_TABLE[0] & 1 is Profile IRQ */

	cpu_tick[cpu]++;
	अगर (!(cpu_tick[cpu] & 15)) अणु
		अगर (cpu_tick[cpu] == 0x60)
			cpu_tick[cpu] = 0;
		cpu_leds[cpu] = led_mask[cpu_tick[cpu] >> 4];
		show_leds(cpu);
	पूर्ण

	ce = &per_cpu(sparc32_घड़ीevent, cpu);

	irq_enter();
	ce->event_handler(ce);
	irq_निकास();

	set_irq_regs(old_regs);
पूर्ण

अटल स्थिर काष्ठा sparc32_ipi_ops sun4d_ipi_ops = अणु
	.cross_call = sun4d_cross_call,
	.resched    = sun4d_ipi_resched,
	.single     = sun4d_ipi_single,
	.mask_one   = sun4d_ipi_mask_one,
पूर्ण;

व्योम __init sun4d_init_smp(व्योम)
अणु
	पूर्णांक i;

	/* Patch ipi15 trap table */
	t_nmi[1] = t_nmi[1] + (linux_trap_ipi15_sun4d - linux_trap_ipi15_sun4m);

	sparc32_ipi_ops = &sun4d_ipi_ops;

	क्रम (i = 0; i < NR_CPUS; i++) अणु
		ccall_info.processors_in[i] = 1;
		ccall_info.processors_out[i] = 1;
	पूर्ण
पूर्ण
