<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Intel SMP support routines.
 *
 *	(c) 1995 Alan Cox, Building #3 <alan@lxorguk.ukuu.org.uk>
 *	(c) 1998-99, 2000, 2009 Ingo Molnar <mingo@redhat.com>
 *      (c) 2002,2003 Andi Kleen, SuSE Lअसल.
 *
 *	i386 and x86_64 पूर्णांकegration by Glauber Costa <gcosta@redhat.com>
 */

#समावेश <linux/init.h>

#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/cache.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpu.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/trace/irq_vectors.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/virtext.h>

/*
 *	Some notes on x86 processor bugs affecting SMP operation:
 *
 *	Pentium, Pentium Pro, II, III (and all CPUs) have bugs.
 *	The Linux implications क्रम SMP are handled as follows:
 *
 *	Pentium III / [Xeon]
 *		None of the E1AP-E3AP errata are visible to the user.
 *
 *	E1AP.	see PII A1AP
 *	E2AP.	see PII A2AP
 *	E3AP.	see PII A3AP
 *
 *	Pentium II / [Xeon]
 *		None of the A1AP-A3AP errata are visible to the user.
 *
 *	A1AP.	see PPro 1AP
 *	A2AP.	see PPro 2AP
 *	A3AP.	see PPro 7AP
 *
 *	Pentium Pro
 *		None of 1AP-9AP errata are visible to the normal user,
 *	except occasional delivery of 'spurious interrupt' as trap #15.
 *	This is very rare and a non-problem.
 *
 *	1AP.	Linux maps APIC as non-cacheable
 *	2AP.	worked around in hardware
 *	3AP.	fixed in C0 and above steppings microcode update.
 *		Linux करोes not use excessive STARTUP_IPIs.
 *	4AP.	worked around in hardware
 *	5AP.	symmetric IO mode (normal Linux operation) not affected.
 *		'noapic' mode has vector 0xf filled out properly.
 *	6AP.	'noapic' mode might be affected - fixed in later steppings
 *	7AP.	We करो not assume ग_लिखोs to the LVT deनिश्चितing IRQs
 *	8AP.	We करो not enable low घातer mode (deep sleep) during MP bootup
 *	9AP.	We करो not use mixed mode
 *
 *	Pentium
 *		There is a marginal हाल where REP MOVS on 100MHz SMP
 *	machines with B stepping processors can fail. XXX should provide
 *	an L1cache=Writethrough or L1cache=off option.
 *
 *		B stepping CPUs may hang. There are hardware work arounds
 *	क्रम this. We warn about it in हाल your board करोesn't have the work
 *	arounds. Basically that's so I can tell anyone with a B stepping
 *	CPU and SMP problems "tough".
 *
 *	Specअगरic items [From Pentium Processor Specअगरication Update]
 *
 *	1AP.	Linux करोesn't use remote पढ़ो
 *	2AP.	Linux करोesn't trust APIC errors
 *	3AP.	We work around this
 *	4AP.	Linux never generated 3 पूर्णांकerrupts of the same priority
 *		to cause a lost local पूर्णांकerrupt.
 *	5AP.	Remote पढ़ो is never used
 *	6AP.	not affected - worked around in hardware
 *	7AP.	not affected - worked around in hardware
 *	8AP.	worked around in hardware - we get explicit CS errors अगर not
 *	9AP.	only 'noapic' mode affected. Might generate spurious
 *		पूर्णांकerrupts, we log only the first one and count the
 *		rest silently.
 *	10AP.	not affected - worked around in hardware
 *	11AP.	Linux पढ़ोs the APIC between ग_लिखोs to aव्योम this, as per
 *		the करोcumentation. Make sure you preserve this as it affects
 *		the C stepping chips too.
 *	12AP.	not affected - worked around in hardware
 *	13AP.	not affected - worked around in hardware
 *	14AP.	we always deनिश्चित INIT during bootup
 *	15AP.	not affected - worked around in hardware
 *	16AP.	not affected - worked around in hardware
 *	17AP.	not affected - worked around in hardware
 *	18AP.	not affected - worked around in hardware
 *	19AP.	not affected - worked around in BIOS
 *
 *	If this sounds worrying believe me these bugs are either ___RARE___,
 *	or are संकेत timing bugs worked around in hardware and there's
 *	about nothing of note with C stepping upwards.
 */

अटल atomic_t stopping_cpu = ATOMIC_INIT(-1);
अटल bool smp_no_nmi_ipi = false;

अटल पूर्णांक smp_stop_nmi_callback(अचिन्हित पूर्णांक val, काष्ठा pt_regs *regs)
अणु
	/* We are रेजिस्टरed on stopping cpu too, aव्योम spurious NMI */
	अगर (raw_smp_processor_id() == atomic_पढ़ो(&stopping_cpu))
		वापस NMI_HANDLED;

	cpu_emergency_vmxoff();
	stop_this_cpu(शून्य);

	वापस NMI_HANDLED;
पूर्ण

/*
 * this function calls the 'stop' function on all other CPUs in the प्रणाली.
 */
DEFINE_IDTENTRY_SYSVEC(sysvec_reboot)
अणु
	ack_APIC_irq();
	cpu_emergency_vmxoff();
	stop_this_cpu(शून्य);
पूर्ण

अटल पूर्णांक रेजिस्टर_stop_handler(व्योम)
अणु
	वापस रेजिस्टर_nmi_handler(NMI_LOCAL, smp_stop_nmi_callback,
				    NMI_FLAG_FIRST, "smp_stop");
पूर्ण

अटल व्योम native_stop_other_cpus(पूर्णांक रुको)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयout;

	अगर (reboot_क्रमce)
		वापस;

	/*
	 * Use an own vector here because smp_call_function
	 * करोes lots of things not suitable in a panic situation.
	 */

	/*
	 * We start by using the REBOOT_VECTOR irq.
	 * The irq is treated as a sync poपूर्णांक to allow critical
	 * regions of code on other cpus to release their spin locks
	 * and re-enable irqs.  Jumping straight to an NMI might
	 * accidentally cause deadlocks with further shutकरोwn/panic
	 * code.  By syncing, we give the cpus up to one second to
	 * finish their work beक्रमe we क्रमce them off with the NMI.
	 */
	अगर (num_online_cpus() > 1) अणु
		/* did someone beat us here? */
		अगर (atomic_cmpxchg(&stopping_cpu, -1, safe_smp_processor_id()) != -1)
			वापस;

		/* sync above data beक्रमe sending IRQ */
		wmb();

		apic_send_IPI_allbutself(REBOOT_VECTOR);

		/*
		 * Don't रुको दीर्घer than a second क्रम IPI completion. The
		 * रुको request is not checked here because that would
		 * prevent an NMI shutकरोwn attempt in हाल that not all
		 * CPUs reach shutकरोwn state.
		 */
		समयout = USEC_PER_SEC;
		जबतक (num_online_cpus() > 1 && समयout--)
			udelay(1);
	पूर्ण

	/* अगर the REBOOT_VECTOR didn't work, try with the NMI */
	अगर (num_online_cpus() > 1) अणु
		/*
		 * If NMI IPI is enabled, try to रेजिस्टर the stop handler
		 * and send the IPI. In any हाल try to रुको क्रम the other
		 * CPUs to stop.
		 */
		अगर (!smp_no_nmi_ipi && !रेजिस्टर_stop_handler()) अणु
			/* Sync above data beक्रमe sending IRQ */
			wmb();

			pr_emerg("Shutting down cpus with NMI\n");

			apic_send_IPI_allbutself(NMI_VECTOR);
		पूर्ण
		/*
		 * Don't wait longer than 10 ms if the caller didn't
		 * request it. If रुको is true, the machine hangs here अगर
		 * one or more CPUs करो not reach shutकरोwn state.
		 */
		समयout = USEC_PER_MSEC * 10;
		जबतक (num_online_cpus() > 1 && (रुको || समयout--))
			udelay(1);
	पूर्ण

	local_irq_save(flags);
	disable_local_APIC();
	mcheck_cpu_clear(this_cpu_ptr(&cpu_info));
	local_irq_restore(flags);
पूर्ण

/*
 * Reschedule call back. KVM uses this पूर्णांकerrupt to क्रमce a cpu out of
 * guest mode.
 */
DEFINE_IDTENTRY_SYSVEC_SIMPLE(sysvec_reschedule_ipi)
अणु
	ack_APIC_irq();
	trace_reschedule_entry(RESCHEDULE_VECTOR);
	inc_irq_stat(irq_resched_count);
	scheduler_ipi();
	trace_reschedule_निकास(RESCHEDULE_VECTOR);
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_call_function)
अणु
	ack_APIC_irq();
	trace_call_function_entry(CALL_FUNCTION_VECTOR);
	inc_irq_stat(irq_call_count);
	generic_smp_call_function_पूर्णांकerrupt();
	trace_call_function_निकास(CALL_FUNCTION_VECTOR);
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_call_function_single)
अणु
	ack_APIC_irq();
	trace_call_function_single_entry(CALL_FUNCTION_SINGLE_VECTOR);
	inc_irq_stat(irq_call_count);
	generic_smp_call_function_single_पूर्णांकerrupt();
	trace_call_function_single_निकास(CALL_FUNCTION_SINGLE_VECTOR);
पूर्ण

अटल पूर्णांक __init nonmi_ipi_setup(अक्षर *str)
अणु
	smp_no_nmi_ipi = true;
	वापस 1;
पूर्ण

__setup("nonmi_ipi", nonmi_ipi_setup);

काष्ठा smp_ops smp_ops = अणु
	.smp_prepare_boot_cpu	= native_smp_prepare_boot_cpu,
	.smp_prepare_cpus	= native_smp_prepare_cpus,
	.smp_cpus_करोne		= native_smp_cpus_करोne,

	.stop_other_cpus	= native_stop_other_cpus,
#अगर defined(CONFIG_KEXEC_CORE)
	.crash_stop_other_cpus	= kdump_nmi_shootकरोwn_cpus,
#पूर्ण_अगर
	.smp_send_reschedule	= native_smp_send_reschedule,

	.cpu_up			= native_cpu_up,
	.cpu_die		= native_cpu_die,
	.cpu_disable		= native_cpu_disable,
	.play_dead		= native_play_dead,

	.send_call_func_ipi	= native_send_call_func_ipi,
	.send_call_func_single_ipi = native_send_call_func_single_ipi,
पूर्ण;
EXPORT_SYMBOL_GPL(smp_ops);
