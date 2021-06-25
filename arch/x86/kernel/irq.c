<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common पूर्णांकerrupt code क्रम 32 and 64 bit
 */
#समावेश <linux/cpu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/of.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/smp.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/irq_stack.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/thermal.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <यंत्र/trace/irq_vectors.h>

DEFINE_PER_CPU_SHARED_ALIGNED(irq_cpustat_t, irq_stat);
EXPORT_PER_CPU_SYMBOL(irq_stat);

atomic_t irq_err_count;

/*
 * 'what should we do if we get a hw irq event on an illegal vector'.
 * each architecture has to answer this themselves.
 */
व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	अगर (prपूर्णांकk_ratelimit())
		pr_err("unexpected IRQ trap at vector %02x\n", irq);

	/*
	 * Currently unexpected vectors happen only on SMP and APIC.
	 * We _must_ ack these because every local APIC has only N
	 * irq slots per priority level, and a 'hanging, unacked' IRQ
	 * holds up an irq slot - in excessive हालs (when multiple
	 * unexpected vectors occur) that might lock up the APIC
	 * completely.
	 * But only ack when the APIC is enabled -AK
	 */
	ack_APIC_irq();
पूर्ण

#घोषणा irq_stats(x)		(&per_cpu(irq_stat, x))
/*
 * /proc/पूर्णांकerrupts prपूर्णांकing क्रम arch specअगरic पूर्णांकerrupts
 */
पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	पूर्णांक j;

	seq_म_लिखो(p, "%*s: ", prec, "NMI");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->__nmi_count);
	seq_माला_दो(p, "  Non-maskable interrupts\n");
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	seq_म_लिखो(p, "%*s: ", prec, "LOC");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->apic_समयr_irqs);
	seq_माला_दो(p, "  Local timer interrupts\n");

	seq_म_लिखो(p, "%*s: ", prec, "SPU");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_spurious_count);
	seq_माला_दो(p, "  Spurious interrupts\n");
	seq_म_लिखो(p, "%*s: ", prec, "PMI");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->apic_perf_irqs);
	seq_माला_दो(p, "  Performance monitoring interrupts\n");
	seq_म_लिखो(p, "%*s: ", prec, "IWI");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->apic_irq_work_irqs);
	seq_माला_दो(p, "  IRQ work interrupts\n");
	seq_म_लिखो(p, "%*s: ", prec, "RTR");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->icr_पढ़ो_retry_count);
	seq_माला_दो(p, "  APIC ICR read retries\n");
	अगर (x86_platक्रमm_ipi_callback) अणु
		seq_म_लिखो(p, "%*s: ", prec, "PLT");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ", irq_stats(j)->x86_platक्रमm_ipis);
		seq_माला_दो(p, "  Platform interrupts\n");
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	seq_म_लिखो(p, "%*s: ", prec, "RES");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_resched_count);
	seq_माला_दो(p, "  Rescheduling interrupts\n");
	seq_म_लिखो(p, "%*s: ", prec, "CAL");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_call_count);
	seq_माला_दो(p, "  Function call interrupts\n");
	seq_म_लिखो(p, "%*s: ", prec, "TLB");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_tlb_count);
	seq_माला_दो(p, "  TLB shootdowns\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
	seq_म_लिखो(p, "%*s: ", prec, "TRM");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_thermal_count);
	seq_माला_दो(p, "  Thermal event interrupts\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE_THRESHOLD
	seq_म_लिखो(p, "%*s: ", prec, "THR");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_threshold_count);
	seq_माला_दो(p, "  Threshold APIC interrupts\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE_AMD
	seq_म_लिखो(p, "%*s: ", prec, "DFR");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->irq_deferred_error_count);
	seq_माला_दो(p, "  Deferred Error APIC interrupts\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE
	seq_म_लिखो(p, "%*s: ", prec, "MCE");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(mce_exception_count, j));
	seq_माला_दो(p, "  Machine check exceptions\n");
	seq_म_लिखो(p, "%*s: ", prec, "MCP");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(mce_poll_count, j));
	seq_माला_दो(p, "  Machine check polls\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_HV_CALLBACK_VECTOR
	अगर (test_bit(HYPERVISOR_CALLBACK_VECTOR, प्रणाली_vectors)) अणु
		seq_म_लिखो(p, "%*s: ", prec, "HYP");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ",
				   irq_stats(j)->irq_hv_callback_count);
		seq_माला_दो(p, "  Hypervisor callback interrupts\n");
	पूर्ण
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_HYPERV)
	अगर (test_bit(HYPERV_REENLIGHTENMENT_VECTOR, प्रणाली_vectors)) अणु
		seq_म_लिखो(p, "%*s: ", prec, "HRE");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ",
				   irq_stats(j)->irq_hv_reenlightenment_count);
		seq_माला_दो(p, "  Hyper-V reenlightenment interrupts\n");
	पूर्ण
	अगर (test_bit(HYPERV_STIMER0_VECTOR, प्रणाली_vectors)) अणु
		seq_म_लिखो(p, "%*s: ", prec, "HVS");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ",
				   irq_stats(j)->hyperv_sसमयr0_count);
		seq_माला_दो(p, "  Hyper-V stimer0 interrupts\n");
	पूर्ण
#पूर्ण_अगर
	seq_म_लिखो(p, "%*s: %10u\n", prec, "ERR", atomic_पढ़ो(&irq_err_count));
#अगर defined(CONFIG_X86_IO_APIC)
	seq_म_लिखो(p, "%*s: %10u\n", prec, "MIS", atomic_पढ़ो(&irq_mis_count));
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_KVM
	seq_म_लिखो(p, "%*s: ", prec, "PIN");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", irq_stats(j)->kvm_posted_पूर्णांकr_ipis);
	seq_माला_दो(p, "  Posted-interrupt notification event\n");

	seq_म_लिखो(p, "%*s: ", prec, "NPI");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ",
			   irq_stats(j)->kvm_posted_पूर्णांकr_nested_ipis);
	seq_माला_दो(p, "  Nested posted-interrupt event\n");

	seq_म_लिखो(p, "%*s: ", prec, "PIW");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ",
			   irq_stats(j)->kvm_posted_पूर्णांकr_wakeup_ipis);
	seq_माला_दो(p, "  Posted-interrupt wakeup event\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * /proc/stat helpers
 */
u64 arch_irq_stat_cpu(अचिन्हित पूर्णांक cpu)
अणु
	u64 sum = irq_stats(cpu)->__nmi_count;

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	sum += irq_stats(cpu)->apic_समयr_irqs;
	sum += irq_stats(cpu)->irq_spurious_count;
	sum += irq_stats(cpu)->apic_perf_irqs;
	sum += irq_stats(cpu)->apic_irq_work_irqs;
	sum += irq_stats(cpu)->icr_पढ़ो_retry_count;
	अगर (x86_platक्रमm_ipi_callback)
		sum += irq_stats(cpu)->x86_platक्रमm_ipis;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	sum += irq_stats(cpu)->irq_resched_count;
	sum += irq_stats(cpu)->irq_call_count;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
	sum += irq_stats(cpu)->irq_thermal_count;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE_THRESHOLD
	sum += irq_stats(cpu)->irq_threshold_count;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE
	sum += per_cpu(mce_exception_count, cpu);
	sum += per_cpu(mce_poll_count, cpu);
#पूर्ण_अगर
	वापस sum;
पूर्ण

u64 arch_irq_stat(व्योम)
अणु
	u64 sum = atomic_पढ़ो(&irq_err_count);
	वापस sum;
पूर्ण

अटल __always_अंतरभूत व्योम handle_irq(काष्ठा irq_desc *desc,
				       काष्ठा pt_regs *regs)
अणु
	अगर (IS_ENABLED(CONFIG_X86_64))
		generic_handle_irq_desc(desc);
	अन्यथा
		__handle_irq(desc, regs);
पूर्ण

/*
 * common_पूर्णांकerrupt() handles all normal device IRQ's (the special SMP
 * cross-CPU पूर्णांकerrupts have their own entry poपूर्णांकs).
 */
DEFINE_IDTENTRY_IRQ(common_पूर्णांकerrupt)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	काष्ठा irq_desc *desc;

	/* entry code tells RCU that we're not quiescent.  Check it. */
	RCU_LOCKDEP_WARN(!rcu_is_watching(), "IRQ failed to wake up RCU");

	desc = __this_cpu_पढ़ो(vector_irq[vector]);
	अगर (likely(!IS_ERR_OR_शून्य(desc))) अणु
		handle_irq(desc, regs);
	पूर्ण अन्यथा अणु
		ack_APIC_irq();

		अगर (desc == VECTOR_UNUSED) अणु
			pr_emerg_ratelimited("%s: %d.%u No irq handler for vector\n",
					     __func__, smp_processor_id(),
					     vector);
		पूर्ण अन्यथा अणु
			__this_cpu_ग_लिखो(vector_irq[vector], VECTOR_UNUSED);
		पूर्ण
	पूर्ण

	set_irq_regs(old_regs);
पूर्ण

#अगर_घोषित CONFIG_X86_LOCAL_APIC
/* Function poपूर्णांकer क्रम generic पूर्णांकerrupt vector handling */
व्योम (*x86_platक्रमm_ipi_callback)(व्योम) = शून्य;
/*
 * Handler क्रम X86_PLATFORM_IPI_VECTOR.
 */
DEFINE_IDTENTRY_SYSVEC(sysvec_x86_platक्रमm_ipi)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	ack_APIC_irq();
	trace_x86_platक्रमm_ipi_entry(X86_PLATFORM_IPI_VECTOR);
	inc_irq_stat(x86_platक्रमm_ipis);
	अगर (x86_platक्रमm_ipi_callback)
		x86_platक्रमm_ipi_callback();
	trace_x86_platक्रमm_ipi_निकास(X86_PLATFORM_IPI_VECTOR);
	set_irq_regs(old_regs);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_KVM
अटल व्योम dummy_handler(व्योम) अणुपूर्ण
अटल व्योम (*kvm_posted_पूर्णांकr_wakeup_handler)(व्योम) = dummy_handler;

व्योम kvm_set_posted_पूर्णांकr_wakeup_handler(व्योम (*handler)(व्योम))
अणु
	अगर (handler)
		kvm_posted_पूर्णांकr_wakeup_handler = handler;
	अन्यथा
		kvm_posted_पूर्णांकr_wakeup_handler = dummy_handler;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_posted_पूर्णांकr_wakeup_handler);

/*
 * Handler क्रम POSTED_INTERRUPT_VECTOR.
 */
DEFINE_IDTENTRY_SYSVEC_SIMPLE(sysvec_kvm_posted_पूर्णांकr_ipi)
अणु
	ack_APIC_irq();
	inc_irq_stat(kvm_posted_पूर्णांकr_ipis);
पूर्ण

/*
 * Handler क्रम POSTED_INTERRUPT_WAKEUP_VECTOR.
 */
DEFINE_IDTENTRY_SYSVEC(sysvec_kvm_posted_पूर्णांकr_wakeup_ipi)
अणु
	ack_APIC_irq();
	inc_irq_stat(kvm_posted_पूर्णांकr_wakeup_ipis);
	kvm_posted_पूर्णांकr_wakeup_handler();
पूर्ण

/*
 * Handler क्रम POSTED_INTERRUPT_NESTED_VECTOR.
 */
DEFINE_IDTENTRY_SYSVEC_SIMPLE(sysvec_kvm_posted_पूर्णांकr_nested_ipi)
अणु
	ack_APIC_irq();
	inc_irq_stat(kvm_posted_पूर्णांकr_nested_ipis);
पूर्ण
#पूर्ण_अगर


#अगर_घोषित CONFIG_HOTPLUG_CPU
/* A cpu has been हटाओd from cpu_online_mask.  Reset irq affinities. */
व्योम fixup_irqs(व्योम)
अणु
	अचिन्हित पूर्णांक irr, vector;
	काष्ठा irq_desc *desc;
	काष्ठा irq_data *data;
	काष्ठा irq_chip *chip;

	irq_migrate_all_off_this_cpu();

	/*
	 * We can हटाओ mdelay() and then send spurious पूर्णांकerrupts to
	 * new cpu tarमाला_लो क्रम all the irqs that were handled previously by
	 * this cpu. While it works, I have seen spurious पूर्णांकerrupt messages
	 * (nothing wrong but still...).
	 *
	 * So क्रम now, retain mdelay(1) and check the IRR and then send those
	 * पूर्णांकerrupts to new tarमाला_लो as this cpu is alपढ़ोy offlined...
	 */
	mdelay(1);

	/*
	 * We can walk the vector array of this cpu without holding
	 * vector_lock because the cpu is alपढ़ोy marked !online, so
	 * nothing अन्यथा will touch it.
	 */
	क्रम (vector = FIRST_EXTERNAL_VECTOR; vector < NR_VECTORS; vector++) अणु
		अगर (IS_ERR_OR_शून्य(__this_cpu_पढ़ो(vector_irq[vector])))
			जारी;

		irr = apic_पढ़ो(APIC_IRR + (vector / 32 * 0x10));
		अगर (irr  & (1 << (vector % 32))) अणु
			desc = __this_cpu_पढ़ो(vector_irq[vector]);

			raw_spin_lock(&desc->lock);
			data = irq_desc_get_irq_data(desc);
			chip = irq_data_get_irq_chip(data);
			अगर (chip->irq_retrigger) अणु
				chip->irq_retrigger(data);
				__this_cpu_ग_लिखो(vector_irq[vector], VECTOR_RETRIGGERED);
			पूर्ण
			raw_spin_unlock(&desc->lock);
		पूर्ण
		अगर (__this_cpu_पढ़ो(vector_irq[vector]) != VECTOR_RETRIGGERED)
			__this_cpu_ग_लिखो(vector_irq[vector], VECTOR_UNUSED);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
अटल व्योम smp_thermal_vector(व्योम)
अणु
	अगर (x86_thermal_enabled())
		पूर्णांकel_thermal_पूर्णांकerrupt();
	अन्यथा
		pr_err("CPU%d: Unexpected LVT thermal interrupt!\n",
		       smp_processor_id());
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_thermal)
अणु
	trace_thermal_apic_entry(THERMAL_APIC_VECTOR);
	inc_irq_stat(irq_thermal_count);
	smp_thermal_vector();
	trace_thermal_apic_निकास(THERMAL_APIC_VECTOR);
	ack_APIC_irq();
पूर्ण
#पूर्ण_अगर
