<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_HARसूचीQ_H
#घोषणा _ASM_X86_HARसूचीQ_H

#समावेश <linux/thपढ़ोs.h>

प्रकार काष्ठा अणु
	u16	     __softirq_pending;
#अगर IS_ENABLED(CONFIG_KVM_INTEL)
	u8	     kvm_cpu_l1tf_flush_l1d;
#पूर्ण_अगर
	अचिन्हित पूर्णांक __nmi_count;	/* arch dependent */
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	अचिन्हित पूर्णांक apic_समयr_irqs;	/* arch dependent */
	अचिन्हित पूर्णांक irq_spurious_count;
	अचिन्हित पूर्णांक icr_पढ़ो_retry_count;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_KVM
	अचिन्हित पूर्णांक kvm_posted_पूर्णांकr_ipis;
	अचिन्हित पूर्णांक kvm_posted_पूर्णांकr_wakeup_ipis;
	अचिन्हित पूर्णांक kvm_posted_पूर्णांकr_nested_ipis;
#पूर्ण_अगर
	अचिन्हित पूर्णांक x86_platक्रमm_ipis;	/* arch dependent */
	अचिन्हित पूर्णांक apic_perf_irqs;
	अचिन्हित पूर्णांक apic_irq_work_irqs;
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक irq_resched_count;
	अचिन्हित पूर्णांक irq_call_count;
#पूर्ण_अगर
	अचिन्हित पूर्णांक irq_tlb_count;
#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
	अचिन्हित पूर्णांक irq_thermal_count;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE_THRESHOLD
	अचिन्हित पूर्णांक irq_threshold_count;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE_AMD
	अचिन्हित पूर्णांक irq_deferred_error_count;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_HV_CALLBACK_VECTOR
	अचिन्हित पूर्णांक irq_hv_callback_count;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_HYPERV)
	अचिन्हित पूर्णांक irq_hv_reenlightenment_count;
	अचिन्हित पूर्णांक hyperv_sसमयr0_count;
#पूर्ण_अगर
पूर्ण ____cacheline_aligned irq_cpustat_t;

DECLARE_PER_CPU_SHARED_ALIGNED(irq_cpustat_t, irq_stat);

#घोषणा __ARCH_IRQ_STAT

#घोषणा inc_irq_stat(member)	this_cpu_inc(irq_stat.member)

बाह्य व्योम ack_bad_irq(अचिन्हित पूर्णांक irq);

बाह्य u64 arch_irq_stat_cpu(अचिन्हित पूर्णांक cpu);
#घोषणा arch_irq_stat_cpu	arch_irq_stat_cpu

बाह्य u64 arch_irq_stat(व्योम);
#घोषणा arch_irq_stat		arch_irq_stat


#अगर IS_ENABLED(CONFIG_KVM_INTEL)
अटल अंतरभूत व्योम kvm_set_cpu_l1tf_flush_l1d(व्योम)
अणु
	__this_cpu_ग_लिखो(irq_stat.kvm_cpu_l1tf_flush_l1d, 1);
पूर्ण

अटल __always_अंतरभूत व्योम kvm_clear_cpu_l1tf_flush_l1d(व्योम)
अणु
	__this_cpu_ग_लिखो(irq_stat.kvm_cpu_l1tf_flush_l1d, 0);
पूर्ण

अटल __always_अंतरभूत bool kvm_get_cpu_l1tf_flush_l1d(व्योम)
अणु
	वापस __this_cpu_पढ़ो(irq_stat.kvm_cpu_l1tf_flush_l1d);
पूर्ण
#अन्यथा /* !IS_ENABLED(CONFIG_KVM_INTEL) */
अटल अंतरभूत व्योम kvm_set_cpu_l1tf_flush_l1d(व्योम) अणु पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_KVM_INTEL) */

#पूर्ण_अगर /* _ASM_X86_HARसूचीQ_H */
