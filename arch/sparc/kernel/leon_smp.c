<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* leon_smp.c: Sparc-Leon SMP support.
 *
 * based on sun4m_smp.c
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com) Aeroflex Gaisler AB
 * Copyright (C) 2009 Konrad Eisele (konrad@gaisler.com) Aeroflex Gaisler AB
 */

#समावेश <यंत्र/head.h>

#समावेश <linux/kernel.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/of.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/profile.h>
#समावेश <linux/pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/घड़ीchips.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/traps.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/leon_amba.h>
#समावेश <यंत्र/समयr.h>

#समावेश "kernel.h"

#समावेश "irq.h"

बाह्य ctxd_t *srmmu_ctx_table_phys;
अटल पूर्णांक smp_processors_पढ़ोy;
बाह्य अस्थिर अचिन्हित दीर्घ cpu_callin_map[NR_CPUS];
बाह्य cpumask_t smp_commenced_mask;
व्योम leon_configure_cache_smp(व्योम);
अटल व्योम leon_ipi_init(व्योम);

/* IRQ number of LEON IPIs */
पूर्णांक leon_ipi_irq = LEON3_IRQ_IPI_DEFAULT;

अटल अंतरभूत अचिन्हित दीर्घ करो_swap(अस्थिर अचिन्हित दीर्घ *ptr,
				    अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__("swapa [%2] %3, %0\n\t" : "=&r"(val)
			     : "0"(val), "r"(ptr), "i"(ASI_LEON_DCACHE_MISS)
			     : "memory");
	वापस val;
पूर्ण

व्योम leon_cpu_pre_starting(व्योम *arg)
अणु
	leon_configure_cache_smp();
पूर्ण

व्योम leon_cpu_pre_online(व्योम *arg)
अणु
	पूर्णांक cpuid = hard_smp_processor_id();

	/* Allow master to जारी. The master will then give us the
	 * go-ahead by setting the smp_commenced_mask and will रुको without
	 * समयouts until our setup is completed fully (signअगरied by
	 * our bit being set in the cpu_online_mask).
	 */
	करो_swap(&cpu_callin_map[cpuid], 1);

	local_ops->cache_all();
	local_ops->tlb_all();

	/* Fix idle thपढ़ो fields. */
	__यंत्र__ __अस्थिर__("ld [%0], %%g6\n\t" : : "r"(&current_set[cpuid])
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

बाह्य काष्ठा linux_prom_रेजिस्टरs smp_penguin_ctable;

व्योम leon_configure_cache_smp(व्योम)
अणु
	अचिन्हित दीर्घ cfg = sparc_leon3_get_dcachecfg();
	पूर्णांक me = smp_processor_id();

	अगर (ASI_LEON3_SYSCTRL_CFG_SSIZE(cfg) > 4) अणु
		prपूर्णांकk(KERN_INFO "Note: SMP with snooping only works on 4k cache, found %dk(0x%x) on cpu %d, disabling caches\n",
		     (अचिन्हित पूर्णांक)ASI_LEON3_SYSCTRL_CFG_SSIZE(cfg),
		     (अचिन्हित पूर्णांक)cfg, (अचिन्हित पूर्णांक)me);
		sparc_leon3_disable_cache();
	पूर्ण अन्यथा अणु
		अगर (cfg & ASI_LEON3_SYSCTRL_CFG_SNOOPING) अणु
			sparc_leon3_enable_snooping();
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO "Note: You have to enable snooping in the vhdl model cpu %d, disabling caches\n",
			     me);
			sparc_leon3_disable_cache();
		पूर्ण
	पूर्ण

	local_ops->cache_all();
	local_ops->tlb_all();
पूर्ण

अटल व्योम leon_smp_setbroadcast(अचिन्हित पूर्णांक mask)
अणु
	पूर्णांक broadcast =
	    ((LEON3_BYPASS_LOAD_PA(&(leon3_irqctrl_regs->mpstatus)) >>
	      LEON3_IRQMPSTATUS_BROADCAST) & 1);
	अगर (!broadcast) अणु
		prom_म_लिखो("######## !!!! The irqmp-ctrl must have broadcast enabled, smp wont work !!!!! ####### nr cpus: %d\n",
		     leon_smp_nrcpus());
		अगर (leon_smp_nrcpus() > 1) अणु
			BUG();
		पूर्ण अन्यथा अणु
			prom_म_लिखो("continue anyway\n");
			वापस;
		पूर्ण
	पूर्ण
	LEON_BYPASS_STORE_PA(&(leon3_irqctrl_regs->mpbroadcast), mask);
पूर्ण

पूर्णांक leon_smp_nrcpus(व्योम)
अणु
	पूर्णांक nrcpu =
	    ((LEON3_BYPASS_LOAD_PA(&(leon3_irqctrl_regs->mpstatus)) >>
	      LEON3_IRQMPSTATUS_CPUNR) & 0xf) + 1;
	वापस nrcpu;
पूर्ण

व्योम __init leon_boot_cpus(व्योम)
अणु
	पूर्णांक nrcpu = leon_smp_nrcpus();
	पूर्णांक me = smp_processor_id();

	/* Setup IPI */
	leon_ipi_init();

	prपूर्णांकk(KERN_INFO "%d:(%d:%d) cpus mpirq at 0x%x\n", (अचिन्हित पूर्णांक)me,
	       (अचिन्हित पूर्णांक)nrcpu, (अचिन्हित पूर्णांक)NR_CPUS,
	       (अचिन्हित पूर्णांक)&(leon3_irqctrl_regs->mpstatus));

	leon_enable_irq_cpu(LEON3_IRQ_CROSS_CALL, me);
	leon_enable_irq_cpu(LEON3_IRQ_TICKER, me);
	leon_enable_irq_cpu(leon_ipi_irq, me);

	leon_smp_setbroadcast(1 << LEON3_IRQ_TICKER);

	leon_configure_cache_smp();
	local_ops->cache_all();

पूर्ण

पूर्णांक leon_boot_one_cpu(पूर्णांक i, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक समयout;

	current_set[i] = task_thपढ़ो_info(idle);

	/* See trampoline.S:leon_smp_cpu_startup क्रम details...
	 * Initialize the contexts table
	 * Since the call to prom_startcpu() trashes the काष्ठाure,
	 * we need to re-initialize it क्रम each cpu
	 */
	smp_penguin_ctable.which_io = 0;
	smp_penguin_ctable.phys_addr = (अचिन्हित पूर्णांक)srmmu_ctx_table_phys;
	smp_penguin_ctable.reg_size = 0;

	/* whirrr, whirrr, whirrrrrrrrr... */
	prपूर्णांकk(KERN_INFO "Starting CPU %d : (irqmp: 0x%x)\n", (अचिन्हित पूर्णांक)i,
	       (अचिन्हित पूर्णांक)&leon3_irqctrl_regs->mpstatus);
	local_ops->cache_all();

	/* Make sure all IRQs are of from the start क्रम this new CPU */
	LEON_BYPASS_STORE_PA(&leon3_irqctrl_regs->mask[i], 0);

	/* Wake one CPU */
	LEON_BYPASS_STORE_PA(&(leon3_irqctrl_regs->mpstatus), 1 << i);

	/* wheee... it's going... */
	क्रम (समयout = 0; समयout < 10000; समयout++) अणु
		अगर (cpu_callin_map[i])
			अवरोध;
		udelay(200);
	पूर्ण
	prपूर्णांकk(KERN_INFO "Started CPU %d\n", (अचिन्हित पूर्णांक)i);

	अगर (!(cpu_callin_map[i])) अणु
		prपूर्णांकk(KERN_ERR "Processor %d is stuck.\n", i);
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		leon_enable_irq_cpu(LEON3_IRQ_CROSS_CALL, i);
		leon_enable_irq_cpu(LEON3_IRQ_TICKER, i);
		leon_enable_irq_cpu(leon_ipi_irq, i);
	पूर्ण

	local_ops->cache_all();
	वापस 0;
पूर्ण

व्योम __init leon_smp_करोne(व्योम)
अणु

	पूर्णांक i, first;
	पूर्णांक *prev;

	/* setup cpu list क्रम irq rotation */
	first = 0;
	prev = &first;
	क्रम (i = 0; i < NR_CPUS; i++) अणु
		अगर (cpu_online(i)) अणु
			*prev = i;
			prev = &cpu_data(i).next;
		पूर्ण
	पूर्ण
	*prev = first;
	local_ops->cache_all();

	/* Free unneeded trap tables */
	अगर (!cpu_present(1)) अणु
		मुक्त_reserved_page(virt_to_page(&trapbase_cpu1));
	पूर्ण
	अगर (!cpu_present(2)) अणु
		मुक्त_reserved_page(virt_to_page(&trapbase_cpu2));
	पूर्ण
	अगर (!cpu_present(3)) अणु
		मुक्त_reserved_page(virt_to_page(&trapbase_cpu3));
	पूर्ण
	/* Ok, they are spinning and पढ़ोy to go. */
	smp_processors_पढ़ोy = 1;

पूर्ण

काष्ठा leon_ipi_work अणु
	पूर्णांक single;
	पूर्णांक msk;
	पूर्णांक resched;
पूर्ण;

अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा leon_ipi_work, leon_ipi_work);

/* Initialize IPIs on the LEON, in order to save IRQ resources only one IRQ
 * is used क्रम all three types of IPIs.
 */
अटल व्योम __init leon_ipi_init(व्योम)
अणु
	पूर्णांक cpu, len;
	काष्ठा leon_ipi_work *work;
	काष्ठा property *pp;
	काष्ठा device_node *rootnp;
	काष्ठा tt_entry *trap_table;
	अचिन्हित दीर्घ flags;

	/* Find IPI IRQ or stick with शेष value */
	rootnp = of_find_node_by_path("/ambapp0");
	अगर (rootnp) अणु
		pp = of_find_property(rootnp, "ipi_num", &len);
		अगर (pp && (*(पूर्णांक *)pp->value))
			leon_ipi_irq = *(पूर्णांक *)pp->value;
	पूर्ण
	prपूर्णांकk(KERN_INFO "leon: SMP IPIs at IRQ %d\n", leon_ipi_irq);

	/* Adjust so that we jump directly to smpleon_ipi */
	local_irq_save(flags);
	trap_table = &sparc_ttable[SP_TRAP_IRQ1 + (leon_ipi_irq - 1)];
	trap_table->inst_three += smpleon_ipi - real_irq_entry;
	local_ops->cache_all();
	local_irq_restore(flags);

	क्रम_each_possible_cpu(cpu) अणु
		work = &per_cpu(leon_ipi_work, cpu);
		work->single = work->msk = work->resched = 0;
	पूर्ण
पूर्ण

अटल व्योम leon_send_ipi(पूर्णांक cpu, पूर्णांक level)
अणु
	अचिन्हित दीर्घ mask;
	mask = leon_get_irqmask(level);
	LEON3_BYPASS_STORE_PA(&leon3_irqctrl_regs->क्रमce[cpu], mask);
पूर्ण

अटल व्योम leon_ipi_single(पूर्णांक cpu)
अणु
	काष्ठा leon_ipi_work *work = &per_cpu(leon_ipi_work, cpu);

	/* Mark work */
	work->single = 1;

	/* Generate IRQ on the CPU */
	leon_send_ipi(cpu, leon_ipi_irq);
पूर्ण

अटल व्योम leon_ipi_mask_one(पूर्णांक cpu)
अणु
	काष्ठा leon_ipi_work *work = &per_cpu(leon_ipi_work, cpu);

	/* Mark work */
	work->msk = 1;

	/* Generate IRQ on the CPU */
	leon_send_ipi(cpu, leon_ipi_irq);
पूर्ण

अटल व्योम leon_ipi_resched(पूर्णांक cpu)
अणु
	काष्ठा leon_ipi_work *work = &per_cpu(leon_ipi_work, cpu);

	/* Mark work */
	work->resched = 1;

	/* Generate IRQ on the CPU (any IRQ will cause resched) */
	leon_send_ipi(cpu, leon_ipi_irq);
पूर्ण

व्योम leonsmp_ipi_पूर्णांकerrupt(व्योम)
अणु
	काष्ठा leon_ipi_work *work = this_cpu_ptr(&leon_ipi_work);

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

अटल काष्ठा smp_funcall अणु
	smpfunc_t func;
	अचिन्हित दीर्घ arg1;
	अचिन्हित दीर्घ arg2;
	अचिन्हित दीर्घ arg3;
	अचिन्हित दीर्घ arg4;
	अचिन्हित दीर्घ arg5;
	अचिन्हित दीर्घ processors_in[NR_CPUS];	/* Set when ipi entered. */
	अचिन्हित दीर्घ processors_out[NR_CPUS];	/* Set when ipi निकासed. */
पूर्ण ccall_info __attribute__((aligned(8)));

अटल DEFINE_SPINLOCK(cross_call_lock);

/* Cross calls must be serialized, at least currently. */
अटल व्योम leon_cross_call(smpfunc_t func, cpumask_t mask, अचिन्हित दीर्घ arg1,
			    अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			    अचिन्हित दीर्घ arg4)
अणु
	अगर (smp_processors_पढ़ोy) अणु
		रेजिस्टर पूर्णांक high = NR_CPUS - 1;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&cross_call_lock, flags);

		अणु
			/* If you make changes here, make sure gcc generates proper code... */
			रेजिस्टर smpfunc_t f यंत्र("i0") = func;
			रेजिस्टर अचिन्हित दीर्घ a1 यंत्र("i1") = arg1;
			रेजिस्टर अचिन्हित दीर्घ a2 यंत्र("i2") = arg2;
			रेजिस्टर अचिन्हित दीर्घ a3 यंत्र("i3") = arg3;
			रेजिस्टर अचिन्हित दीर्घ a4 यंत्र("i4") = arg4;
			रेजिस्टर अचिन्हित दीर्घ a5 यंत्र("i5") = 0;

			__यंत्र__ __अस्थिर__("std %0, [%6]\n\t"
					     "std %2, [%6 + 8]\n\t"
					     "std %4, [%6 + 16]\n\t" : :
					     "r"(f), "r"(a1), "r"(a2), "r"(a3),
					     "r"(a4), "r"(a5),
					     "r"(&ccall_info.func));
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
					leon_send_ipi(i, LEON3_IRQ_CROSS_CALL);

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
व्योम leon_cross_call_irq(व्योम)
अणु
	पूर्णांक i = smp_processor_id();

	ccall_info.processors_in[i] = 1;
	ccall_info.func(ccall_info.arg1, ccall_info.arg2, ccall_info.arg3,
			ccall_info.arg4, ccall_info.arg5);
	ccall_info.processors_out[i] = 1;
पूर्ण

अटल स्थिर काष्ठा sparc32_ipi_ops leon_ipi_ops = अणु
	.cross_call = leon_cross_call,
	.resched    = leon_ipi_resched,
	.single     = leon_ipi_single,
	.mask_one   = leon_ipi_mask_one,
पूर्ण;

व्योम __init leon_init_smp(व्योम)
अणु
	/* Patch ipi15 trap table */
	t_nmi[1] = t_nmi[1] + (linux_trap_ipi15_leon - linux_trap_ipi15_sun4m);

	sparc32_ipi_ops = &leon_ipi_ops;
पूर्ण
