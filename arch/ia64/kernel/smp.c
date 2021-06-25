<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMP Support
 *
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999, 2001, 2003 David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * Lots of stuff stolen from arch/alpha/kernel/smp.c
 *
 * 01/05/16 Rohit Seth <rohit.seth@पूर्णांकel.com>  IA64-SMP functions. Reorganized
 * the existing code (on the lines of x86 port).
 * 00/09/11 David Mosberger <davidm@hpl.hp.com> Do loops_per_jअगरfy
 * calibration on each CPU.
 * 00/08/23 Asit Mallick <asit.k.mallick@पूर्णांकel.com> fixed logical processor id
 * 00/03/31 Rohit Seth <rohit.seth@पूर्णांकel.com>	Fixes क्रम Bootstrap Processor
 * & cpu_online_map now माला_लो करोne here (instead of setup.c)
 * 99/10/05 davidm	Update to bring it in sync with new command-line processing
 *  scheme.
 * 10/13/00 Goutham Rao <goutham.rao@पूर्णांकel.com> Updated smp_call_function and
 *		smp_call_function_single to resend IPI on समयouts
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/cache.h>
#समावेश <linux/delay.h>
#समावेश <linux/efi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kexec.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/mca.h>
#समावेश <यंत्र/xtp.h>

/*
 * Note: alignment of 4 entries/cacheline was empirically determined
 * to be a good tradeoff between hot cachelines & spपढ़ोing the array
 * across too many cacheline.
 */
अटल काष्ठा local_tlb_flush_counts अणु
	अचिन्हित पूर्णांक count;
पूर्ण __attribute__((__aligned__(32))) local_tlb_flush_counts[NR_CPUS];

अटल DEFINE_PER_CPU_SHARED_ALIGNED(अचिन्हित लघु [NR_CPUS],
				     shaकरोw_flush_counts);

#घोषणा IPI_CALL_FUNC		0
#घोषणा IPI_CPU_STOP		1
#घोषणा IPI_CALL_FUNC_SINGLE	2
#घोषणा IPI_KDUMP_CPU_STOP	3

/* This needs to be cacheline aligned because it is written to by *other* CPUs.  */
अटल DEFINE_PER_CPU_SHARED_ALIGNED(अचिन्हित दीर्घ, ipi_operation);

बाह्य व्योम cpu_halt (व्योम);

अटल व्योम
stop_this_cpu(व्योम)
अणु
	/*
	 * Remove this CPU:
	 */
	set_cpu_online(smp_processor_id(), false);
	max_xtp();
	local_irq_disable();
	cpu_halt();
पूर्ण

व्योम
cpu_die(व्योम)
अणु
	max_xtp();
	local_irq_disable();
	cpu_halt();
	/* Should never be here */
	BUG();
	क्रम (;;);
पूर्ण

irqवापस_t
handle_IPI (पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक this_cpu = get_cpu();
	अचिन्हित दीर्घ *pending_ipis = &__ia64_per_cpu_var(ipi_operation);
	अचिन्हित दीर्घ ops;

	mb();	/* Order पूर्णांकerrupt and bit testing. */
	जबतक ((ops = xchg(pending_ipis, 0)) != 0) अणु
		mb();	/* Order bit clearing and data access. */
		करो अणु
			अचिन्हित दीर्घ which;

			which = ffz(~ops);
			ops &= ~(1 << which);

			चयन (which) अणु
			हाल IPI_CPU_STOP:
				stop_this_cpu();
				अवरोध;
			हाल IPI_CALL_FUNC:
				generic_smp_call_function_पूर्णांकerrupt();
				अवरोध;
			हाल IPI_CALL_FUNC_SINGLE:
				generic_smp_call_function_single_पूर्णांकerrupt();
				अवरोध;
#अगर_घोषित CONFIG_KEXEC
			हाल IPI_KDUMP_CPU_STOP:
				unw_init_running(kdump_cpu_मुक्तze, शून्य);
				अवरोध;
#पूर्ण_अगर
			शेष:
				prपूर्णांकk(KERN_CRIT "Unknown IPI on CPU %d: %lu\n",
						this_cpu, which);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (ops);
		mb();	/* Order data access and bit testing. */
	पूर्ण
	put_cpu();
	वापस IRQ_HANDLED;
पूर्ण



/*
 * Called with preemption disabled.
 */
अटल अंतरभूत व्योम
send_IPI_single (पूर्णांक dest_cpu, पूर्णांक op)
अणु
	set_bit(op, &per_cpu(ipi_operation, dest_cpu));
	ia64_send_ipi(dest_cpu, IA64_IPI_VECTOR, IA64_IPI_DM_INT, 0);
पूर्ण

/*
 * Called with preemption disabled.
 */
अटल अंतरभूत व्योम
send_IPI_allbutself (पूर्णांक op)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_online_cpu(i) अणु
		अगर (i != smp_processor_id())
			send_IPI_single(i, op);
	पूर्ण
पूर्ण

/*
 * Called with preemption disabled.
 */
अटल अंतरभूत व्योम
send_IPI_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक op)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
			send_IPI_single(cpu, op);
	पूर्ण
पूर्ण

/*
 * Called with preemption disabled.
 */
अटल अंतरभूत व्योम
send_IPI_all (पूर्णांक op)
अणु
	पूर्णांक i;

	क्रम_each_online_cpu(i) अणु
		send_IPI_single(i, op);
	पूर्ण
पूर्ण

/*
 * Called with preemption disabled.
 */
अटल अंतरभूत व्योम
send_IPI_self (पूर्णांक op)
अणु
	send_IPI_single(smp_processor_id(), op);
पूर्ण

#अगर_घोषित CONFIG_KEXEC
व्योम
kdump_smp_send_stop(व्योम)
अणु
 	send_IPI_allbutself(IPI_KDUMP_CPU_STOP);
पूर्ण

व्योम
kdump_smp_send_init(व्योम)
अणु
	अचिन्हित पूर्णांक cpu, self_cpu;
	self_cpu = smp_processor_id();
	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu != self_cpu) अणु
			अगर(kdump_status[cpu] == 0)
				ia64_send_ipi(cpu, 0, IA64_IPI_DM_INIT, 0);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर
/*
 * Called with preemption disabled.
 */
व्योम
smp_send_reschedule (पूर्णांक cpu)
अणु
	ia64_send_ipi(cpu, IA64_IPI_RESCHEDULE, IA64_IPI_DM_INT, 0);
पूर्ण
EXPORT_SYMBOL_GPL(smp_send_reschedule);

/*
 * Called with preemption disabled.
 */
अटल व्योम
smp_send_local_flush_tlb (पूर्णांक cpu)
अणु
	ia64_send_ipi(cpu, IA64_IPI_LOCAL_TLB_FLUSH, IA64_IPI_DM_INT, 0);
पूर्ण

व्योम
smp_local_flush_tlb(व्योम)
अणु
	/*
	 * Use atomic ops. Otherwise, the load/increment/store sequence from
	 * a "++" operation can have the line stolen between the load & store.
	 * The overhead of the atomic op in negligible in this हाल & offers
	 * signअगरicant benefit क्रम the brief periods where lots of cpus
	 * are simultaneously flushing TLBs.
	 */
	ia64_fetchadd(1, &local_tlb_flush_counts[smp_processor_id()].count, acq);
	local_flush_tlb_all();
पूर्ण

#घोषणा FLUSH_DELAY	5 /* Usec backoff to eliminate excessive cacheline bouncing */

व्योम
smp_flush_tlb_cpumask(cpumask_t xcpumask)
अणु
	अचिन्हित लघु *counts = __ia64_per_cpu_var(shaकरोw_flush_counts);
	cpumask_t cpumask = xcpumask;
	पूर्णांक mycpu, cpu, flush_mycpu = 0;

	preempt_disable();
	mycpu = smp_processor_id();

	क्रम_each_cpu(cpu, &cpumask)
		counts[cpu] = local_tlb_flush_counts[cpu].count & 0xffff;

	mb();
	क्रम_each_cpu(cpu, &cpumask) अणु
		अगर (cpu == mycpu)
			flush_mycpu = 1;
		अन्यथा
			smp_send_local_flush_tlb(cpu);
	पूर्ण

	अगर (flush_mycpu)
		smp_local_flush_tlb();

	क्रम_each_cpu(cpu, &cpumask)
		जबतक(counts[cpu] == (local_tlb_flush_counts[cpu].count & 0xffff))
			udelay(FLUSH_DELAY);

	preempt_enable();
पूर्ण

व्योम
smp_flush_tlb_all (व्योम)
अणु
	on_each_cpu((व्योम (*)(व्योम *))local_flush_tlb_all, शून्य, 1);
पूर्ण

व्योम
smp_flush_tlb_mm (काष्ठा mm_काष्ठा *mm)
अणु
	cpumask_var_t cpus;
	preempt_disable();
	/* this happens क्रम the common हाल of a single-thपढ़ोed विभाजन():  */
	अगर (likely(mm == current->active_mm && atomic_पढ़ो(&mm->mm_users) == 1))
	अणु
		local_finish_flush_tlb_mm(mm);
		preempt_enable();
		वापस;
	पूर्ण
	अगर (!alloc_cpumask_var(&cpus, GFP_ATOMIC)) अणु
		smp_call_function((व्योम (*)(व्योम *))local_finish_flush_tlb_mm,
			mm, 1);
	पूर्ण अन्यथा अणु
		cpumask_copy(cpus, mm_cpumask(mm));
		smp_call_function_many(cpus,
			(व्योम (*)(व्योम *))local_finish_flush_tlb_mm, mm, 1);
		मुक्त_cpumask_var(cpus);
	पूर्ण
	local_irq_disable();
	local_finish_flush_tlb_mm(mm);
	local_irq_enable();
	preempt_enable();
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	send_IPI_single(cpu, IPI_CALL_FUNC_SINGLE);
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	send_IPI_mask(mask, IPI_CALL_FUNC);
पूर्ण

/*
 * this function calls the 'stop' function on all other CPUs in the प्रणाली.
 */
व्योम
smp_send_stop (व्योम)
अणु
	send_IPI_allbutself(IPI_CPU_STOP);
पूर्ण

पूर्णांक
setup_profiling_समयr (अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण
