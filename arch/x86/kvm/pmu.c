<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine -- Perक्रमmance Monitoring Unit support
 *
 * Copyright 2015 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Avi Kivity   <avi@redhat.com>
 *   Gleb Natapov <gleb@redhat.com>
 *   Wei Huang    <wei@redhat.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/perf_event.h>
#समावेश "x86.h"
#समावेश "cpuid.h"
#समावेश "lapic.h"
#समावेश "pmu.h"

/* This is enough to filter the vast majority of currently defined events. */
#घोषणा KVM_PMU_EVENT_FILTER_MAX_EVENTS 300

/* NOTE:
 * - Each perf counter is defined as "struct kvm_pmc";
 * - There are two types of perf counters: general purpose (gp) and fixed.
 *   gp counters are stored in gp_counters[] and fixed counters are stored
 *   in fixed_counters[] respectively. Both of them are part of "काष्ठा
 *   kvm_pmu";
 * - pmu.c understands the dअगरference between gp counters and fixed counters.
 *   However AMD करोesn't support fixed-counters;
 * - There are three types of index to access perf counters (PMC):
 *     1. MSR (named msr): For example Intel has MSR_IA32_PERFCTRn and AMD
 *        has MSR_K7_PERFCTRn.
 *     2. MSR Index (named idx): This normally is used by RDPMC inकाष्ठाion.
 *        For instance AMD RDPMC inकाष्ठाion uses 0000_0003h in ECX to access
 *        C001_0007h (MSR_K7_PERCTR3). Intel has a similar mechanism, except
 *        that it also supports fixed counters. idx can be used to as index to
 *        gp and fixed counters.
 *     3. Global PMC Index (named pmc): pmc is an index specअगरic to PMU
 *        code. Each pmc, stored in kvm_pmc.idx field, is unique across
 *        all perf counters (both gp and fixed). The mapping relationship
 *        between pmc and perf counters is as the following:
 *        * Intel: [0 .. INTEL_PMC_MAX_GENERIC-1] <=> gp counters
 *                 [INTEL_PMC_IDX_FIXED .. INTEL_PMC_IDX_FIXED + 2] <=> fixed
 *        * AMD:   [0 .. AMD64_NUM_COUNTERS-1] <=> gp counters
 */

अटल व्योम kvm_pmi_trigger_fn(काष्ठा irq_work *irq_work)
अणु
	काष्ठा kvm_pmu *pmu = container_of(irq_work, काष्ठा kvm_pmu, irq_work);
	काष्ठा kvm_vcpu *vcpu = pmu_to_vcpu(pmu);

	kvm_pmu_deliver_pmi(vcpu);
पूर्ण

अटल व्योम kvm_perf_overflow(काष्ठा perf_event *perf_event,
			      काष्ठा perf_sample_data *data,
			      काष्ठा pt_regs *regs)
अणु
	काष्ठा kvm_pmc *pmc = perf_event->overflow_handler_context;
	काष्ठा kvm_pmu *pmu = pmc_to_pmu(pmc);

	अगर (!test_and_set_bit(pmc->idx, pmu->reprogram_pmi)) अणु
		__set_bit(pmc->idx, (अचिन्हित दीर्घ *)&pmu->global_status);
		kvm_make_request(KVM_REQ_PMU, pmc->vcpu);
	पूर्ण
पूर्ण

अटल व्योम kvm_perf_overflow_पूर्णांकr(काष्ठा perf_event *perf_event,
				   काष्ठा perf_sample_data *data,
				   काष्ठा pt_regs *regs)
अणु
	काष्ठा kvm_pmc *pmc = perf_event->overflow_handler_context;
	काष्ठा kvm_pmu *pmu = pmc_to_pmu(pmc);

	अगर (!test_and_set_bit(pmc->idx, pmu->reprogram_pmi)) अणु
		__set_bit(pmc->idx, (अचिन्हित दीर्घ *)&pmu->global_status);
		kvm_make_request(KVM_REQ_PMU, pmc->vcpu);

		/*
		 * Inject PMI. If vcpu was in a guest mode during NMI PMI
		 * can be ejected on a guest mode re-entry. Otherwise we can't
		 * be sure that vcpu wasn't executing hlt inकाष्ठाion at the
		 * समय of vmनिकास and is not going to re-enter guest mode until
		 * woken up. So we should wake it, but this is impossible from
		 * NMI context. Do it from irq work instead.
		 */
		अगर (!kvm_is_in_guest())
			irq_work_queue(&pmc_to_pmu(pmc)->irq_work);
		अन्यथा
			kvm_make_request(KVM_REQ_PMI, pmc->vcpu);
	पूर्ण
पूर्ण

अटल व्योम pmc_reprogram_counter(काष्ठा kvm_pmc *pmc, u32 type,
				  अचिन्हित config, bool exclude_user,
				  bool exclude_kernel, bool पूर्णांकr,
				  bool in_tx, bool in_tx_cp)
अणु
	काष्ठा perf_event *event;
	काष्ठा perf_event_attr attr = अणु
		.type = type,
		.size = माप(attr),
		.pinned = true,
		.exclude_idle = true,
		.exclude_host = 1,
		.exclude_user = exclude_user,
		.exclude_kernel = exclude_kernel,
		.config = config,
	पूर्ण;

	attr.sample_period = get_sample_period(pmc, pmc->counter);

	अगर (in_tx)
		attr.config |= HSW_IN_TX;
	अगर (in_tx_cp) अणु
		/*
		 * HSW_IN_TX_CHECKPOINTED is not supported with nonzero
		 * period. Just clear the sample period so at least
		 * allocating the counter करोesn't fail.
		 */
		attr.sample_period = 0;
		attr.config |= HSW_IN_TX_CHECKPOINTED;
	पूर्ण

	event = perf_event_create_kernel_counter(&attr, -1, current,
						 पूर्णांकr ? kvm_perf_overflow_पूर्णांकr :
						 kvm_perf_overflow, pmc);
	अगर (IS_ERR(event)) अणु
		pr_debug_ratelimited("kvm_pmu: event creation failed %ld for pmc->idx = %d\n",
			    PTR_ERR(event), pmc->idx);
		वापस;
	पूर्ण

	pmc->perf_event = event;
	pmc_to_pmu(pmc)->event_count++;
	clear_bit(pmc->idx, pmc_to_pmu(pmc)->reprogram_pmi);
पूर्ण

अटल व्योम pmc_छोड़ो_counter(काष्ठा kvm_pmc *pmc)
अणु
	u64 counter = pmc->counter;

	अगर (!pmc->perf_event)
		वापस;

	/* update counter, reset event value to aव्योम redundant accumulation */
	counter += perf_event_छोड़ो(pmc->perf_event, true);
	pmc->counter = counter & pmc_biपंचांगask(pmc);
पूर्ण

अटल bool pmc_resume_counter(काष्ठा kvm_pmc *pmc)
अणु
	अगर (!pmc->perf_event)
		वापस false;

	/* recalibrate sample period and check अगर it's accepted by perf core */
	अगर (perf_event_period(pmc->perf_event,
			      get_sample_period(pmc, pmc->counter)))
		वापस false;

	/* reuse perf_event to serve as pmc_reprogram_counter() करोes*/
	perf_event_enable(pmc->perf_event);

	clear_bit(pmc->idx, (अचिन्हित दीर्घ *)&pmc_to_pmu(pmc)->reprogram_pmi);
	वापस true;
पूर्ण

व्योम reprogram_gp_counter(काष्ठा kvm_pmc *pmc, u64 eventsel)
अणु
	अचिन्हित config, type = PERF_TYPE_RAW;
	u8 event_select, unit_mask;
	काष्ठा kvm *kvm = pmc->vcpu->kvm;
	काष्ठा kvm_pmu_event_filter *filter;
	पूर्णांक i;
	bool allow_event = true;

	अगर (eventsel & ARCH_PERFMON_EVENTSEL_PIN_CONTROL)
		prपूर्णांकk_once("kvm pmu: pin control bit is ignored\n");

	pmc->eventsel = eventsel;

	pmc_छोड़ो_counter(pmc);

	अगर (!(eventsel & ARCH_PERFMON_EVENTSEL_ENABLE) || !pmc_is_enabled(pmc))
		वापस;

	filter = srcu_dereference(kvm->arch.pmu_event_filter, &kvm->srcu);
	अगर (filter) अणु
		क्रम (i = 0; i < filter->nevents; i++)
			अगर (filter->events[i] ==
			    (eventsel & AMD64_RAW_EVENT_MASK_NB))
				अवरोध;
		अगर (filter->action == KVM_PMU_EVENT_ALLOW &&
		    i == filter->nevents)
			allow_event = false;
		अगर (filter->action == KVM_PMU_EVENT_DENY &&
		    i < filter->nevents)
			allow_event = false;
	पूर्ण
	अगर (!allow_event)
		वापस;

	event_select = eventsel & ARCH_PERFMON_EVENTSEL_EVENT;
	unit_mask = (eventsel & ARCH_PERFMON_EVENTSEL_UMASK) >> 8;

	अगर (!(eventsel & (ARCH_PERFMON_EVENTSEL_EDGE |
			  ARCH_PERFMON_EVENTSEL_INV |
			  ARCH_PERFMON_EVENTSEL_CMASK |
			  HSW_IN_TX |
			  HSW_IN_TX_CHECKPOINTED))) अणु
		config = kvm_x86_ops.pmu_ops->find_arch_event(pmc_to_pmu(pmc),
						      event_select,
						      unit_mask);
		अगर (config != PERF_COUNT_HW_MAX)
			type = PERF_TYPE_HARDWARE;
	पूर्ण

	अगर (type == PERF_TYPE_RAW)
		config = eventsel & X86_RAW_EVENT_MASK;

	अगर (pmc->current_config == eventsel && pmc_resume_counter(pmc))
		वापस;

	pmc_release_perf_event(pmc);

	pmc->current_config = eventsel;
	pmc_reprogram_counter(pmc, type, config,
			      !(eventsel & ARCH_PERFMON_EVENTSEL_USR),
			      !(eventsel & ARCH_PERFMON_EVENTSEL_OS),
			      eventsel & ARCH_PERFMON_EVENTSEL_INT,
			      (eventsel & HSW_IN_TX),
			      (eventsel & HSW_IN_TX_CHECKPOINTED));
पूर्ण
EXPORT_SYMBOL_GPL(reprogram_gp_counter);

व्योम reprogram_fixed_counter(काष्ठा kvm_pmc *pmc, u8 ctrl, पूर्णांक idx)
अणु
	अचिन्हित en_field = ctrl & 0x3;
	bool pmi = ctrl & 0x8;
	काष्ठा kvm_pmu_event_filter *filter;
	काष्ठा kvm *kvm = pmc->vcpu->kvm;

	pmc_छोड़ो_counter(pmc);

	अगर (!en_field || !pmc_is_enabled(pmc))
		वापस;

	filter = srcu_dereference(kvm->arch.pmu_event_filter, &kvm->srcu);
	अगर (filter) अणु
		अगर (filter->action == KVM_PMU_EVENT_DENY &&
		    test_bit(idx, (uदीर्घ *)&filter->fixed_counter_biपंचांगap))
			वापस;
		अगर (filter->action == KVM_PMU_EVENT_ALLOW &&
		    !test_bit(idx, (uदीर्घ *)&filter->fixed_counter_biपंचांगap))
			वापस;
	पूर्ण

	अगर (pmc->current_config == (u64)ctrl && pmc_resume_counter(pmc))
		वापस;

	pmc_release_perf_event(pmc);

	pmc->current_config = (u64)ctrl;
	pmc_reprogram_counter(pmc, PERF_TYPE_HARDWARE,
			      kvm_x86_ops.pmu_ops->find_fixed_event(idx),
			      !(en_field & 0x2), /* exclude user */
			      !(en_field & 0x1), /* exclude kernel */
			      pmi, false, false);
पूर्ण
EXPORT_SYMBOL_GPL(reprogram_fixed_counter);

व्योम reprogram_counter(काष्ठा kvm_pmu *pmu, पूर्णांक pmc_idx)
अणु
	काष्ठा kvm_pmc *pmc = kvm_x86_ops.pmu_ops->pmc_idx_to_pmc(pmu, pmc_idx);

	अगर (!pmc)
		वापस;

	अगर (pmc_is_gp(pmc))
		reprogram_gp_counter(pmc, pmc->eventsel);
	अन्यथा अणु
		पूर्णांक idx = pmc_idx - INTEL_PMC_IDX_FIXED;
		u8 ctrl = fixed_ctrl_field(pmu->fixed_ctr_ctrl, idx);

		reprogram_fixed_counter(pmc, ctrl, idx);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(reprogram_counter);

व्योम kvm_pmu_handle_event(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	पूर्णांक bit;

	क्रम_each_set_bit(bit, pmu->reprogram_pmi, X86_PMC_IDX_MAX) अणु
		काष्ठा kvm_pmc *pmc = kvm_x86_ops.pmu_ops->pmc_idx_to_pmc(pmu, bit);

		अगर (unlikely(!pmc || !pmc->perf_event)) अणु
			clear_bit(bit, pmu->reprogram_pmi);
			जारी;
		पूर्ण

		reprogram_counter(pmu, bit);
	पूर्ण

	/*
	 * Unused perf_events are only released अगर the corresponding MSRs
	 * weren't accessed during the last vCPU समय slice. kvm_arch_sched_in
	 * triggers KVM_REQ_PMU अगर cleanup is needed.
	 */
	अगर (unlikely(pmu->need_cleanup))
		kvm_pmu_cleanup(vcpu);
पूर्ण

/* check अगर idx is a valid index to access PMU */
पूर्णांक kvm_pmu_is_valid_rdpmc_ecx(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक idx)
अणु
	वापस kvm_x86_ops.pmu_ops->is_valid_rdpmc_ecx(vcpu, idx);
पूर्ण

bool is_vmware_backकरोor_pmc(u32 pmc_idx)
अणु
	चयन (pmc_idx) अणु
	हाल VMWARE_BACKDOOR_PMC_HOST_TSC:
	हाल VMWARE_BACKDOOR_PMC_REAL_TIME:
	हाल VMWARE_BACKDOOR_PMC_APPARENT_TIME:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक kvm_pmu_rdpmc_vmware(काष्ठा kvm_vcpu *vcpu, अचिन्हित idx, u64 *data)
अणु
	u64 ctr_val;

	चयन (idx) अणु
	हाल VMWARE_BACKDOOR_PMC_HOST_TSC:
		ctr_val = rdtsc();
		अवरोध;
	हाल VMWARE_BACKDOOR_PMC_REAL_TIME:
		ctr_val = kसमय_get_bootसमय_ns();
		अवरोध;
	हाल VMWARE_BACKDOOR_PMC_APPARENT_TIME:
		ctr_val = kसमय_get_bootसमय_ns() +
			vcpu->kvm->arch.kvmघड़ी_offset;
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण

	*data = ctr_val;
	वापस 0;
पूर्ण

पूर्णांक kvm_pmu_rdpmc(काष्ठा kvm_vcpu *vcpu, अचिन्हित idx, u64 *data)
अणु
	bool fast_mode = idx & (1u << 31);
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc;
	u64 mask = fast_mode ? ~0u : ~0ull;

	अगर (!pmu->version)
		वापस 1;

	अगर (is_vmware_backकरोor_pmc(idx))
		वापस kvm_pmu_rdpmc_vmware(vcpu, idx, data);

	pmc = kvm_x86_ops.pmu_ops->rdpmc_ecx_to_pmc(vcpu, idx, &mask);
	अगर (!pmc)
		वापस 1;

	अगर (!(kvm_पढ़ो_cr4(vcpu) & X86_CR4_PCE) &&
	    (अटल_call(kvm_x86_get_cpl)(vcpu) != 0) &&
	    (kvm_पढ़ो_cr0(vcpu) & X86_CR0_PE))
		वापस 1;

	*data = pmc_पढ़ो_counter(pmc) & mask;
	वापस 0;
पूर्ण

व्योम kvm_pmu_deliver_pmi(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (lapic_in_kernel(vcpu)) अणु
		अगर (kvm_x86_ops.pmu_ops->deliver_pmi)
			kvm_x86_ops.pmu_ops->deliver_pmi(vcpu);
		kvm_apic_local_deliver(vcpu->arch.apic, APIC_LVTPC);
	पूर्ण
पूर्ण

bool kvm_pmu_is_valid_msr(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	वापस kvm_x86_ops.pmu_ops->msr_idx_to_pmc(vcpu, msr) ||
		kvm_x86_ops.pmu_ops->is_valid_msr(vcpu, msr);
पूर्ण

अटल व्योम kvm_pmu_mark_pmc_in_use(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc = kvm_x86_ops.pmu_ops->msr_idx_to_pmc(vcpu, msr);

	अगर (pmc)
		__set_bit(pmc->idx, pmu->pmc_in_use);
पूर्ण

पूर्णांक kvm_pmu_get_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	वापस kvm_x86_ops.pmu_ops->get_msr(vcpu, msr_info);
पूर्ण

पूर्णांक kvm_pmu_set_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	kvm_pmu_mark_pmc_in_use(vcpu, msr_info->index);
	वापस kvm_x86_ops.pmu_ops->set_msr(vcpu, msr_info);
पूर्ण

/* refresh PMU settings. This function generally is called when underlying
 * settings are changed (such as changes of PMU CPUID by guest VMs), which
 * should rarely happen.
 */
व्योम kvm_pmu_refresh(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_x86_ops.pmu_ops->refresh(vcpu);
पूर्ण

व्योम kvm_pmu_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	irq_work_sync(&pmu->irq_work);
	kvm_x86_ops.pmu_ops->reset(vcpu);
पूर्ण

व्योम kvm_pmu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	स_रखो(pmu, 0, माप(*pmu));
	kvm_x86_ops.pmu_ops->init(vcpu);
	init_irq_work(&pmu->irq_work, kvm_pmi_trigger_fn);
	pmu->event_count = 0;
	pmu->need_cleanup = false;
	kvm_pmu_refresh(vcpu);
पूर्ण

अटल अंतरभूत bool pmc_speculative_in_use(काष्ठा kvm_pmc *pmc)
अणु
	काष्ठा kvm_pmu *pmu = pmc_to_pmu(pmc);

	अगर (pmc_is_fixed(pmc))
		वापस fixed_ctrl_field(pmu->fixed_ctr_ctrl,
			pmc->idx - INTEL_PMC_IDX_FIXED) & 0x3;

	वापस pmc->eventsel & ARCH_PERFMON_EVENTSEL_ENABLE;
पूर्ण

/* Release perf_events क्रम vPMCs that have been unused क्रम a full समय slice.  */
व्योम kvm_pmu_cleanup(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc = शून्य;
	DECLARE_BITMAP(biपंचांगask, X86_PMC_IDX_MAX);
	पूर्णांक i;

	pmu->need_cleanup = false;

	biपंचांगap_andnot(biपंचांगask, pmu->all_valid_pmc_idx,
		      pmu->pmc_in_use, X86_PMC_IDX_MAX);

	क्रम_each_set_bit(i, biपंचांगask, X86_PMC_IDX_MAX) अणु
		pmc = kvm_x86_ops.pmu_ops->pmc_idx_to_pmc(pmu, i);

		अगर (pmc && pmc->perf_event && !pmc_speculative_in_use(pmc))
			pmc_stop_counter(pmc);
	पूर्ण

	अगर (kvm_x86_ops.pmu_ops->cleanup)
		kvm_x86_ops.pmu_ops->cleanup(vcpu);

	biपंचांगap_zero(pmu->pmc_in_use, X86_PMC_IDX_MAX);
पूर्ण

व्योम kvm_pmu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_pmu_reset(vcpu);
पूर्ण

पूर्णांक kvm_vm_ioctl_set_pmu_event_filter(काष्ठा kvm *kvm, व्योम __user *argp)
अणु
	काष्ठा kvm_pmu_event_filter पंचांगp, *filter;
	माप_प्रकार size;
	पूर्णांक r;

	अगर (copy_from_user(&पंचांगp, argp, माप(पंचांगp)))
		वापस -EFAULT;

	अगर (पंचांगp.action != KVM_PMU_EVENT_ALLOW &&
	    पंचांगp.action != KVM_PMU_EVENT_DENY)
		वापस -EINVAL;

	अगर (पंचांगp.flags != 0)
		वापस -EINVAL;

	अगर (पंचांगp.nevents > KVM_PMU_EVENT_FILTER_MAX_EVENTS)
		वापस -E2BIG;

	size = काष्ठा_size(filter, events, पंचांगp.nevents);
	filter = kदो_स्मृति(size, GFP_KERNEL_ACCOUNT);
	अगर (!filter)
		वापस -ENOMEM;

	r = -EFAULT;
	अगर (copy_from_user(filter, argp, size))
		जाओ cleanup;

	/* Ensure nevents can't be changed between the user copies. */
	*filter = पंचांगp;

	mutex_lock(&kvm->lock);
	filter = rcu_replace_poपूर्णांकer(kvm->arch.pmu_event_filter, filter,
				     mutex_is_locked(&kvm->lock));
	mutex_unlock(&kvm->lock);

	synchronize_srcu_expedited(&kvm->srcu);
	r = 0;
cleanup:
	kमुक्त(filter);
	वापस r;
पूर्ण
