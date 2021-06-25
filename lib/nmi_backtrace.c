<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  NMI backtrace support
 *
 * Gratuitously copied from arch/x86/kernel/apic/hw_nmi.c by Russell King,
 * with the following header:
 *
 *  HW NMI watchकरोg support
 *
 *  started by Don Zickus, Copyright (C) 2010 Red Hat, Inc.
 *
 *  Arch specअगरic calls to support NMI watchकरोg
 *
 *  Bits copied from original nmi.c file
 */
#समावेश <linux/cpumask.h>
#समावेश <linux/delay.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/nmi.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched/debug.h>

#अगर_घोषित arch_trigger_cpumask_backtrace
/* For reliability, we're prepared to waste bits here. */
अटल DECLARE_BITMAP(backtrace_mask, NR_CPUS) __पढ़ो_mostly;

/* "in progress" flag of arch_trigger_cpumask_backtrace */
अटल अचिन्हित दीर्घ backtrace_flag;

/*
 * When उठाओ() is called it will be passed a poपूर्णांकer to the
 * backtrace_mask. Architectures that call nmi_cpu_backtrace()
 * directly from their उठाओ() functions may rely on the mask
 * they are passed being updated as a side effect of this call.
 */
व्योम nmi_trigger_cpumask_backtrace(स्थिर cpumask_t *mask,
				   bool exclude_self,
				   व्योम (*उठाओ)(cpumask_t *mask))
अणु
	पूर्णांक i, this_cpu = get_cpu();

	अगर (test_and_set_bit(0, &backtrace_flag)) अणु
		/*
		 * If there is alपढ़ोy a trigger_all_cpu_backtrace() in progress
		 * (backtrace_flag == 1), करोn't output द्विगुन cpu dump infos.
		 */
		put_cpu();
		वापस;
	पूर्ण

	cpumask_copy(to_cpumask(backtrace_mask), mask);
	अगर (exclude_self)
		cpumask_clear_cpu(this_cpu, to_cpumask(backtrace_mask));

	/*
	 * Don't try to send an NMI to this cpu; it may work on some
	 * architectures, but on others it may not, and we'll get
	 * inक्रमmation at least as useful just by करोing a dump_stack() here.
	 * Note that nmi_cpu_backtrace(शून्य) will clear the cpu bit.
	 */
	अगर (cpumask_test_cpu(this_cpu, to_cpumask(backtrace_mask)))
		nmi_cpu_backtrace(शून्य);

	अगर (!cpumask_empty(to_cpumask(backtrace_mask))) अणु
		pr_info("Sending NMI from CPU %d to CPUs %*pbl:\n",
			this_cpu, nr_cpumask_bits, to_cpumask(backtrace_mask));
		उठाओ(to_cpumask(backtrace_mask));
	पूर्ण

	/* Wait क्रम up to 10 seconds क्रम all CPUs to करो the backtrace */
	क्रम (i = 0; i < 10 * 1000; i++) अणु
		अगर (cpumask_empty(to_cpumask(backtrace_mask)))
			अवरोध;
		mdelay(1);
		touch_softlockup_watchकरोg();
	पूर्ण

	/*
	 * Force flush any remote buffers that might be stuck in IRQ context
	 * and thereक्रमe could not run their irq_work.
	 */
	prपूर्णांकk_safe_flush();

	clear_bit_unlock(0, &backtrace_flag);
	put_cpu();
पूर्ण

// Dump stacks even क्रम idle CPUs.
अटल bool backtrace_idle;
module_param(backtrace_idle, bool, 0644);

bool nmi_cpu_backtrace(काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (cpumask_test_cpu(cpu, to_cpumask(backtrace_mask))) अणु
		अगर (!READ_ONCE(backtrace_idle) && regs && cpu_in_idle(inकाष्ठाion_poपूर्णांकer(regs))) अणु
			pr_warn("NMI backtrace for cpu %d skipped: idling at %pS\n",
				cpu, (व्योम *)inकाष्ठाion_poपूर्णांकer(regs));
		पूर्ण अन्यथा अणु
			pr_warn("NMI backtrace for cpu %d\n", cpu);
			अगर (regs)
				show_regs(regs);
			अन्यथा
				dump_stack();
		पूर्ण
		cpumask_clear_cpu(cpu, to_cpumask(backtrace_mask));
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
NOKPROBE_SYMBOL(nmi_cpu_backtrace);
#पूर्ण_अगर
