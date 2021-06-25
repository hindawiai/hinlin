<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMP initialisation and IPI support
 * Based on arch/arm64/kernel/smp.c
 *
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#समावेश <linux/cpu.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/profile.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq_work.h>

#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>

क्रमागत ipi_message_type अणु
	IPI_RESCHEDULE,
	IPI_CALL_FUNC,
	IPI_CPU_STOP,
	IPI_IRQ_WORK,
	IPI_TIMER,
	IPI_MAX
पूर्ण;

अचिन्हित दीर्घ __cpuid_to_hartid_map[NR_CPUS] __ro_after_init = अणु
	[0 ... NR_CPUS-1] = INVALID_HARTID
पूर्ण;

व्योम __init smp_setup_processor_id(व्योम)
अणु
	cpuid_to_hartid_map(0) = boot_cpu_hartid;
पूर्ण

/* A collection of single bit ipi messages.  */
अटल काष्ठा अणु
	अचिन्हित दीर्घ stats[IPI_MAX] ____cacheline_aligned;
	अचिन्हित दीर्घ bits ____cacheline_aligned;
पूर्ण ipi_data[NR_CPUS] __cacheline_aligned;

पूर्णांक riscv_hartid_to_cpuid(पूर्णांक hartid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_CPUS; i++)
		अगर (cpuid_to_hartid_map(i) == hartid)
			वापस i;

	pr_err("Couldn't find cpu id for hartid [%d]\n", hartid);
	वापस -ENOENT;
पूर्ण

व्योम riscv_cpuid_to_hartid_mask(स्थिर काष्ठा cpumask *in, काष्ठा cpumask *out)
अणु
	पूर्णांक cpu;

	cpumask_clear(out);
	क्रम_each_cpu(cpu, in)
		cpumask_set_cpu(cpuid_to_hartid_map(cpu), out);
पूर्ण
EXPORT_SYMBOL_GPL(riscv_cpuid_to_hartid_mask);

bool arch_match_cpu_phys_id(पूर्णांक cpu, u64 phys_id)
अणु
	वापस phys_id == cpuid_to_hartid_map(cpu);
पूर्ण

/* Unsupported */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम ipi_stop(व्योम)
अणु
	set_cpu_online(smp_processor_id(), false);
	जबतक (1)
		रुको_क्रम_पूर्णांकerrupt();
पूर्ण

अटल स्थिर काष्ठा riscv_ipi_ops *ipi_ops __ro_after_init;

व्योम riscv_set_ipi_ops(स्थिर काष्ठा riscv_ipi_ops *ops)
अणु
	ipi_ops = ops;
पूर्ण
EXPORT_SYMBOL_GPL(riscv_set_ipi_ops);

व्योम riscv_clear_ipi(व्योम)
अणु
	अगर (ipi_ops && ipi_ops->ipi_clear)
		ipi_ops->ipi_clear();

	csr_clear(CSR_IP, IE_SIE);
पूर्ण
EXPORT_SYMBOL_GPL(riscv_clear_ipi);

अटल व्योम send_ipi_mask(स्थिर काष्ठा cpumask *mask, क्रमागत ipi_message_type op)
अणु
	पूर्णांक cpu;

	smp_mb__beक्रमe_atomic();
	क्रम_each_cpu(cpu, mask)
		set_bit(op, &ipi_data[cpu].bits);
	smp_mb__after_atomic();

	अगर (ipi_ops && ipi_ops->ipi_inject)
		ipi_ops->ipi_inject(mask);
	अन्यथा
		pr_warn("SMP: IPI inject method not available\n");
पूर्ण

अटल व्योम send_ipi_single(पूर्णांक cpu, क्रमागत ipi_message_type op)
अणु
	smp_mb__beक्रमe_atomic();
	set_bit(op, &ipi_data[cpu].bits);
	smp_mb__after_atomic();

	अगर (ipi_ops && ipi_ops->ipi_inject)
		ipi_ops->ipi_inject(cpumask_of(cpu));
	अन्यथा
		pr_warn("SMP: IPI inject method not available\n");
पूर्ण

#अगर_घोषित CONFIG_IRQ_WORK
व्योम arch_irq_work_उठाओ(व्योम)
अणु
	send_ipi_single(smp_processor_id(), IPI_IRQ_WORK);
पूर्ण
#पूर्ण_अगर

व्योम handle_IPI(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	अचिन्हित दीर्घ *pending_ipis = &ipi_data[smp_processor_id()].bits;
	अचिन्हित दीर्घ *stats = ipi_data[smp_processor_id()].stats;

	irq_enter();

	riscv_clear_ipi();

	जबतक (true) अणु
		अचिन्हित दीर्घ ops;

		/* Order bit clearing and data access. */
		mb();

		ops = xchg(pending_ipis, 0);
		अगर (ops == 0)
			जाओ करोne;

		अगर (ops & (1 << IPI_RESCHEDULE)) अणु
			stats[IPI_RESCHEDULE]++;
			scheduler_ipi();
		पूर्ण

		अगर (ops & (1 << IPI_CALL_FUNC)) अणु
			stats[IPI_CALL_FUNC]++;
			generic_smp_call_function_पूर्णांकerrupt();
		पूर्ण

		अगर (ops & (1 << IPI_CPU_STOP)) अणु
			stats[IPI_CPU_STOP]++;
			ipi_stop();
		पूर्ण

		अगर (ops & (1 << IPI_IRQ_WORK)) अणु
			stats[IPI_IRQ_WORK]++;
			irq_work_run();
		पूर्ण

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
		अगर (ops & (1 << IPI_TIMER)) अणु
			stats[IPI_TIMER]++;
			tick_receive_broadcast();
		पूर्ण
#पूर्ण_अगर
		BUG_ON((ops >> IPI_MAX) != 0);

		/* Order data access and bit testing. */
		mb();
	पूर्ण

करोne:
	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण

अटल स्थिर अक्षर * स्थिर ipi_names[] = अणु
	[IPI_RESCHEDULE]	= "Rescheduling interrupts",
	[IPI_CALL_FUNC]		= "Function call interrupts",
	[IPI_CPU_STOP]		= "CPU stop interrupts",
	[IPI_IRQ_WORK]		= "IRQ work interrupts",
	[IPI_TIMER]		= "Timer broadcast interrupts",
पूर्ण;

व्योम show_ipi_stats(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	अचिन्हित पूर्णांक cpu, i;

	क्रम (i = 0; i < IPI_MAX; i++) अणु
		seq_म_लिखो(p, "%*s%u:%s", prec - 1, "IPI", i,
			   prec >= 4 ? " " : "");
		क्रम_each_online_cpu(cpu)
			seq_म_लिखो(p, "%10lu ", ipi_data[cpu].stats[i]);
		seq_म_लिखो(p, " %s\n", ipi_names[i]);
	पूर्ण
पूर्ण

व्योम arch_send_call_function_ipi_mask(काष्ठा cpumask *mask)
अणु
	send_ipi_mask(mask, IPI_CALL_FUNC);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	send_ipi_single(cpu, IPI_CALL_FUNC);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
व्योम tick_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
	send_ipi_mask(mask, IPI_TIMER);
पूर्ण
#पूर्ण_अगर

व्योम smp_send_stop(व्योम)
अणु
	अचिन्हित दीर्घ समयout;

	अगर (num_online_cpus() > 1) अणु
		cpumask_t mask;

		cpumask_copy(&mask, cpu_online_mask);
		cpumask_clear_cpu(smp_processor_id(), &mask);

		अगर (प्रणाली_state <= SYSTEM_RUNNING)
			pr_crit("SMP: stopping secondary CPUs\n");
		send_ipi_mask(&mask, IPI_CPU_STOP);
	पूर्ण

	/* Wait up to one second क्रम other CPUs to stop */
	समयout = USEC_PER_SEC;
	जबतक (num_online_cpus() > 1 && समयout--)
		udelay(1);

	अगर (num_online_cpus() > 1)
		pr_warn("SMP: failed to stop secondary CPUs %*pbl\n",
			   cpumask_pr_args(cpu_online_mask));
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	send_ipi_single(cpu, IPI_RESCHEDULE);
पूर्ण
EXPORT_SYMBOL_GPL(smp_send_reschedule);
