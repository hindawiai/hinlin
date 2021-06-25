<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KVM PMU support क्रम Intel CPUs
 *
 * Copyright 2011 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Avi Kivity   <avi@redhat.com>
 *   Gleb Natapov <gleb@redhat.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/perf_event.h>
#समावेश "x86.h"
#समावेश "cpuid.h"
#समावेश "lapic.h"
#समावेश "nested.h"
#समावेश "pmu.h"

#घोषणा MSR_PMC_FULL_WIDTH_BIT      (MSR_IA32_PMC0 - MSR_IA32_PERFCTR0)

अटल काष्ठा kvm_event_hw_type_mapping पूर्णांकel_arch_events[] = अणु
	/* Index must match CPUID 0x0A.EBX bit vector */
	[0] = अणु 0x3c, 0x00, PERF_COUNT_HW_CPU_CYCLES पूर्ण,
	[1] = अणु 0xc0, 0x00, PERF_COUNT_HW_INSTRUCTIONS पूर्ण,
	[2] = अणु 0x3c, 0x01, PERF_COUNT_HW_BUS_CYCLES  पूर्ण,
	[3] = अणु 0x2e, 0x4f, PERF_COUNT_HW_CACHE_REFERENCES पूर्ण,
	[4] = अणु 0x2e, 0x41, PERF_COUNT_HW_CACHE_MISSES पूर्ण,
	[5] = अणु 0xc4, 0x00, PERF_COUNT_HW_BRANCH_INSTRUCTIONS पूर्ण,
	[6] = अणु 0xc5, 0x00, PERF_COUNT_HW_BRANCH_MISSES पूर्ण,
	[7] = अणु 0x00, 0x03, PERF_COUNT_HW_REF_CPU_CYCLES पूर्ण,
पूर्ण;

/* mapping between fixed pmc index and पूर्णांकel_arch_events array */
अटल पूर्णांक fixed_pmc_events[] = अणु1, 0, 7पूर्ण;

अटल व्योम reprogram_fixed_counters(काष्ठा kvm_pmu *pmu, u64 data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pmu->nr_arch_fixed_counters; i++) अणु
		u8 new_ctrl = fixed_ctrl_field(data, i);
		u8 old_ctrl = fixed_ctrl_field(pmu->fixed_ctr_ctrl, i);
		काष्ठा kvm_pmc *pmc;

		pmc = get_fixed_pmc(pmu, MSR_CORE_PERF_FIXED_CTR0 + i);

		अगर (old_ctrl == new_ctrl)
			जारी;

		__set_bit(INTEL_PMC_IDX_FIXED + i, pmu->pmc_in_use);
		reprogram_fixed_counter(pmc, new_ctrl, i);
	पूर्ण

	pmu->fixed_ctr_ctrl = data;
पूर्ण

/* function is called when global control रेजिस्टर has been updated. */
अटल व्योम global_ctrl_changed(काष्ठा kvm_pmu *pmu, u64 data)
अणु
	पूर्णांक bit;
	u64 dअगरf = pmu->global_ctrl ^ data;

	pmu->global_ctrl = data;

	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&dअगरf, X86_PMC_IDX_MAX)
		reprogram_counter(pmu, bit);
पूर्ण

अटल अचिन्हित पूर्णांकel_find_arch_event(काष्ठा kvm_pmu *pmu,
				      u8 event_select,
				      u8 unit_mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकel_arch_events); i++)
		अगर (पूर्णांकel_arch_events[i].eventsel == event_select
		    && पूर्णांकel_arch_events[i].unit_mask == unit_mask
		    && (pmu->available_event_types & (1 << i)))
			अवरोध;

	अगर (i == ARRAY_SIZE(पूर्णांकel_arch_events))
		वापस PERF_COUNT_HW_MAX;

	वापस पूर्णांकel_arch_events[i].event_type;
पूर्ण

अटल अचिन्हित पूर्णांकel_find_fixed_event(पूर्णांक idx)
अणु
	u32 event;
	माप_प्रकार size = ARRAY_SIZE(fixed_pmc_events);

	अगर (idx >= size)
		वापस PERF_COUNT_HW_MAX;

	event = fixed_pmc_events[array_index_nospec(idx, size)];
	वापस पूर्णांकel_arch_events[event].event_type;
पूर्ण

/* check अगर a PMC is enabled by comparing it with globl_ctrl bits. */
अटल bool पूर्णांकel_pmc_is_enabled(काष्ठा kvm_pmc *pmc)
अणु
	काष्ठा kvm_pmu *pmu = pmc_to_pmu(pmc);

	वापस test_bit(pmc->idx, (अचिन्हित दीर्घ *)&pmu->global_ctrl);
पूर्ण

अटल काष्ठा kvm_pmc *पूर्णांकel_pmc_idx_to_pmc(काष्ठा kvm_pmu *pmu, पूर्णांक pmc_idx)
अणु
	अगर (pmc_idx < INTEL_PMC_IDX_FIXED)
		वापस get_gp_pmc(pmu, MSR_P6_EVNTSEL0 + pmc_idx,
				  MSR_P6_EVNTSEL0);
	अन्यथा अणु
		u32 idx = pmc_idx - INTEL_PMC_IDX_FIXED;

		वापस get_fixed_pmc(pmu, idx + MSR_CORE_PERF_FIXED_CTR0);
	पूर्ण
पूर्ण

/* वापसs 0 अगर idx's corresponding MSR exists; otherwise वापसs 1. */
अटल पूर्णांक पूर्णांकel_is_valid_rdpmc_ecx(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	bool fixed = idx & (1u << 30);

	idx &= ~(3u << 30);

	वापस (!fixed && idx >= pmu->nr_arch_gp_counters) ||
		(fixed && idx >= pmu->nr_arch_fixed_counters);
पूर्ण

अटल काष्ठा kvm_pmc *पूर्णांकel_rdpmc_ecx_to_pmc(काष्ठा kvm_vcpu *vcpu,
					    अचिन्हित पूर्णांक idx, u64 *mask)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	bool fixed = idx & (1u << 30);
	काष्ठा kvm_pmc *counters;
	अचिन्हित पूर्णांक num_counters;

	idx &= ~(3u << 30);
	अगर (fixed) अणु
		counters = pmu->fixed_counters;
		num_counters = pmu->nr_arch_fixed_counters;
	पूर्ण अन्यथा अणु
		counters = pmu->gp_counters;
		num_counters = pmu->nr_arch_gp_counters;
	पूर्ण
	अगर (idx >= num_counters)
		वापस शून्य;
	*mask &= pmu->counter_biपंचांगask[fixed ? KVM_PMC_FIXED : KVM_PMC_GP];
	वापस &counters[array_index_nospec(idx, num_counters)];
पूर्ण

अटल अंतरभूत u64 vcpu_get_perf_capabilities(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!guest_cpuid_has(vcpu, X86_FEATURE_PDCM))
		वापस 0;

	वापस vcpu->arch.perf_capabilities;
पूर्ण

अटल अंतरभूत bool fw_ग_लिखोs_is_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (vcpu_get_perf_capabilities(vcpu) & PMU_CAP_FW_WRITES) != 0;
पूर्ण

अटल अंतरभूत काष्ठा kvm_pmc *get_fw_gp_pmc(काष्ठा kvm_pmu *pmu, u32 msr)
अणु
	अगर (!fw_ग_लिखोs_is_enabled(pmu_to_vcpu(pmu)))
		वापस शून्य;

	वापस get_gp_pmc(pmu, msr, MSR_IA32_PMC0);
पूर्ण

bool पूर्णांकel_pmu_lbr_is_compatible(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * As a first step, a guest could only enable LBR feature अगर its
	 * cpu model is the same as the host because the LBR रेजिस्टरs
	 * would be pass-through to the guest and they're model specअगरic.
	 */
	वापस boot_cpu_data.x86_model == guest_cpuid_model(vcpu);
पूर्ण

bool पूर्णांकel_pmu_lbr_is_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा x86_pmu_lbr *lbr = vcpu_to_lbr_records(vcpu);

	वापस lbr->nr && (vcpu_get_perf_capabilities(vcpu) & PMU_CAP_LBR_FMT);
पूर्ण

अटल bool पूर्णांकel_pmu_is_valid_lbr_msr(काष्ठा kvm_vcpu *vcpu, u32 index)
अणु
	काष्ठा x86_pmu_lbr *records = vcpu_to_lbr_records(vcpu);
	bool ret = false;

	अगर (!पूर्णांकel_pmu_lbr_is_enabled(vcpu))
		वापस ret;

	ret = (index == MSR_LBR_SELECT) || (index == MSR_LBR_TOS) ||
		(index >= records->from && index < records->from + records->nr) ||
		(index >= records->to && index < records->to + records->nr);

	अगर (!ret && records->info)
		ret = (index >= records->info && index < records->info + records->nr);

	वापस ret;
पूर्ण

अटल bool पूर्णांकel_is_valid_msr(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	पूर्णांक ret;

	चयन (msr) अणु
	हाल MSR_CORE_PERF_FIXED_CTR_CTRL:
	हाल MSR_CORE_PERF_GLOBAL_STATUS:
	हाल MSR_CORE_PERF_GLOBAL_CTRL:
	हाल MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		ret = pmu->version > 1;
		अवरोध;
	शेष:
		ret = get_gp_pmc(pmu, msr, MSR_IA32_PERFCTR0) ||
			get_gp_pmc(pmu, msr, MSR_P6_EVNTSEL0) ||
			get_fixed_pmc(pmu, msr) || get_fw_gp_pmc(pmu, msr) ||
			पूर्णांकel_pmu_is_valid_lbr_msr(vcpu, msr);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा kvm_pmc *पूर्णांकel_msr_idx_to_pmc(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc;

	pmc = get_fixed_pmc(pmu, msr);
	pmc = pmc ? pmc : get_gp_pmc(pmu, msr, MSR_P6_EVNTSEL0);
	pmc = pmc ? pmc : get_gp_pmc(pmu, msr, MSR_IA32_PERFCTR0);

	वापस pmc;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pmu_release_guest_lbr_event(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा lbr_desc *lbr_desc = vcpu_to_lbr_desc(vcpu);

	अगर (lbr_desc->event) अणु
		perf_event_release_kernel(lbr_desc->event);
		lbr_desc->event = शून्य;
		vcpu_to_pmu(vcpu)->event_count--;
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_pmu_create_guest_lbr_event(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा lbr_desc *lbr_desc = vcpu_to_lbr_desc(vcpu);
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा perf_event *event;

	/*
	 * The perf_event_attr is स्थिरructed in the minimum efficient way:
	 * - set 'pinned = true' to make it task pinned so that अगर another
	 *   cpu pinned event reclaims LBR, the event->oncpu will be set to -1;
	 * - set '.exclude_host = true' to record guest branches behavior;
	 *
	 * - set '.config = INTEL_FIXED_VLBR_EVENT' to indicates host perf
	 *   schedule the event without a real HW counter but a fake one;
	 *   check is_guest_lbr_event() and __पूर्णांकel_get_event_स्थिरraपूर्णांकs();
	 *
	 * - set 'sample_type = PERF_SAMPLE_BRANCH_STACK' and
	 *   'branch_sample_type = PERF_SAMPLE_BRANCH_CALL_STACK |
	 *   PERF_SAMPLE_BRANCH_USER' to configure it as a LBR callstack
	 *   event, which helps KVM to save/restore guest LBR records
	 *   during host context चयनes and reduces quite a lot overhead,
	 *   check branch_user_callstack() and पूर्णांकel_pmu_lbr_sched_task();
	 */
	काष्ठा perf_event_attr attr = अणु
		.type = PERF_TYPE_RAW,
		.size = माप(attr),
		.config = INTEL_FIXED_VLBR_EVENT,
		.sample_type = PERF_SAMPLE_BRANCH_STACK,
		.pinned = true,
		.exclude_host = true,
		.branch_sample_type = PERF_SAMPLE_BRANCH_CALL_STACK |
					PERF_SAMPLE_BRANCH_USER,
	पूर्ण;

	अगर (unlikely(lbr_desc->event)) अणु
		__set_bit(INTEL_PMC_IDX_FIXED_VLBR, pmu->pmc_in_use);
		वापस 0;
	पूर्ण

	event = perf_event_create_kernel_counter(&attr, -1,
						current, शून्य, शून्य);
	अगर (IS_ERR(event)) अणु
		pr_debug_ratelimited("%s: failed %ld\n",
					__func__, PTR_ERR(event));
		वापस PTR_ERR(event);
	पूर्ण
	lbr_desc->event = event;
	pmu->event_count++;
	__set_bit(INTEL_PMC_IDX_FIXED_VLBR, pmu->pmc_in_use);
	वापस 0;
पूर्ण

/*
 * It's safe to access LBR msrs from guest when they have not
 * been passthrough since the host would help restore or reset
 * the LBR msrs records when the guest LBR event is scheduled in.
 */
अटल bool पूर्णांकel_pmu_handle_lbr_msrs_access(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा msr_data *msr_info, bool पढ़ो)
अणु
	काष्ठा lbr_desc *lbr_desc = vcpu_to_lbr_desc(vcpu);
	u32 index = msr_info->index;

	अगर (!पूर्णांकel_pmu_is_valid_lbr_msr(vcpu, index))
		वापस false;

	अगर (!lbr_desc->event && पूर्णांकel_pmu_create_guest_lbr_event(vcpu) < 0)
		जाओ dummy;

	/*
	 * Disable irq to ensure the LBR feature करोesn't get reclaimed by the
	 * host at the समय the value is पढ़ो from the msr, and this aव्योमs the
	 * host LBR value to be leaked to the guest. If LBR has been reclaimed,
	 * वापस 0 on guest पढ़ोs.
	 */
	local_irq_disable();
	अगर (lbr_desc->event->state == PERF_EVENT_STATE_ACTIVE) अणु
		अगर (पढ़ो)
			rdmsrl(index, msr_info->data);
		अन्यथा
			wrmsrl(index, msr_info->data);
		__set_bit(INTEL_PMC_IDX_FIXED_VLBR, vcpu_to_pmu(vcpu)->pmc_in_use);
		local_irq_enable();
		वापस true;
	पूर्ण
	clear_bit(INTEL_PMC_IDX_FIXED_VLBR, vcpu_to_pmu(vcpu)->pmc_in_use);
	local_irq_enable();

dummy:
	अगर (पढ़ो)
		msr_info->data = 0;
	वापस true;
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_get_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc;
	u32 msr = msr_info->index;

	चयन (msr) अणु
	हाल MSR_CORE_PERF_FIXED_CTR_CTRL:
		msr_info->data = pmu->fixed_ctr_ctrl;
		वापस 0;
	हाल MSR_CORE_PERF_GLOBAL_STATUS:
		msr_info->data = pmu->global_status;
		वापस 0;
	हाल MSR_CORE_PERF_GLOBAL_CTRL:
		msr_info->data = pmu->global_ctrl;
		वापस 0;
	हाल MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		msr_info->data = pmu->global_ovf_ctrl;
		वापस 0;
	शेष:
		अगर ((pmc = get_gp_pmc(pmu, msr, MSR_IA32_PERFCTR0)) ||
		    (pmc = get_gp_pmc(pmu, msr, MSR_IA32_PMC0))) अणु
			u64 val = pmc_पढ़ो_counter(pmc);
			msr_info->data =
				val & pmu->counter_biपंचांगask[KVM_PMC_GP];
			वापस 0;
		पूर्ण अन्यथा अगर ((pmc = get_fixed_pmc(pmu, msr))) अणु
			u64 val = pmc_पढ़ो_counter(pmc);
			msr_info->data =
				val & pmu->counter_biपंचांगask[KVM_PMC_FIXED];
			वापस 0;
		पूर्ण अन्यथा अगर ((pmc = get_gp_pmc(pmu, msr, MSR_P6_EVNTSEL0))) अणु
			msr_info->data = pmc->eventsel;
			वापस 0;
		पूर्ण अन्यथा अगर (पूर्णांकel_pmu_handle_lbr_msrs_access(vcpu, msr_info, true))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_set_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc;
	u32 msr = msr_info->index;
	u64 data = msr_info->data;

	चयन (msr) अणु
	हाल MSR_CORE_PERF_FIXED_CTR_CTRL:
		अगर (pmu->fixed_ctr_ctrl == data)
			वापस 0;
		अगर (!(data & 0xfffffffffffff444ull)) अणु
			reprogram_fixed_counters(pmu, data);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल MSR_CORE_PERF_GLOBAL_STATUS:
		अगर (msr_info->host_initiated) अणु
			pmu->global_status = data;
			वापस 0;
		पूर्ण
		अवरोध; /* RO MSR */
	हाल MSR_CORE_PERF_GLOBAL_CTRL:
		अगर (pmu->global_ctrl == data)
			वापस 0;
		अगर (kvm_valid_perf_global_ctrl(pmu, data)) अणु
			global_ctrl_changed(pmu, data);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		अगर (!(data & pmu->global_ovf_ctrl_mask)) अणु
			अगर (!msr_info->host_initiated)
				pmu->global_status &= ~data;
			pmu->global_ovf_ctrl = data;
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		अगर ((pmc = get_gp_pmc(pmu, msr, MSR_IA32_PERFCTR0)) ||
		    (pmc = get_gp_pmc(pmu, msr, MSR_IA32_PMC0))) अणु
			अगर ((msr & MSR_PMC_FULL_WIDTH_BIT) &&
			    (data & ~pmu->counter_biपंचांगask[KVM_PMC_GP]))
				वापस 1;
			अगर (!msr_info->host_initiated &&
			    !(msr & MSR_PMC_FULL_WIDTH_BIT))
				data = (s64)(s32)data;
			pmc->counter += data - pmc_पढ़ो_counter(pmc);
			अगर (pmc->perf_event)
				perf_event_period(pmc->perf_event,
						  get_sample_period(pmc, data));
			वापस 0;
		पूर्ण अन्यथा अगर ((pmc = get_fixed_pmc(pmu, msr))) अणु
			pmc->counter += data - pmc_पढ़ो_counter(pmc);
			अगर (pmc->perf_event)
				perf_event_period(pmc->perf_event,
						  get_sample_period(pmc, data));
			वापस 0;
		पूर्ण अन्यथा अगर ((pmc = get_gp_pmc(pmu, msr, MSR_P6_EVNTSEL0))) अणु
			अगर (data == pmc->eventsel)
				वापस 0;
			अगर (!(data & pmu->reserved_bits)) अणु
				reprogram_gp_counter(pmc, data);
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अगर (पूर्णांकel_pmu_handle_lbr_msrs_access(vcpu, msr_info, false))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम पूर्णांकel_pmu_refresh(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा lbr_desc *lbr_desc = vcpu_to_lbr_desc(vcpu);

	काष्ठा x86_pmu_capability x86_pmu;
	काष्ठा kvm_cpuid_entry2 *entry;
	जोड़ cpuid10_eax eax;
	जोड़ cpuid10_edx edx;

	pmu->nr_arch_gp_counters = 0;
	pmu->nr_arch_fixed_counters = 0;
	pmu->counter_biपंचांगask[KVM_PMC_GP] = 0;
	pmu->counter_biपंचांगask[KVM_PMC_FIXED] = 0;
	pmu->version = 0;
	pmu->reserved_bits = 0xffffffff00200000ull;

	entry = kvm_find_cpuid_entry(vcpu, 0xa, 0);
	अगर (!entry)
		वापस;
	eax.full = entry->eax;
	edx.full = entry->edx;

	pmu->version = eax.split.version_id;
	अगर (!pmu->version)
		वापस;

	perf_get_x86_pmu_capability(&x86_pmu);

	pmu->nr_arch_gp_counters = min_t(पूर्णांक, eax.split.num_counters,
					 x86_pmu.num_counters_gp);
	eax.split.bit_width = min_t(पूर्णांक, eax.split.bit_width, x86_pmu.bit_width_gp);
	pmu->counter_biपंचांगask[KVM_PMC_GP] = ((u64)1 << eax.split.bit_width) - 1;
	eax.split.mask_length = min_t(पूर्णांक, eax.split.mask_length, x86_pmu.events_mask_len);
	pmu->available_event_types = ~entry->ebx &
					((1ull << eax.split.mask_length) - 1);

	अगर (pmu->version == 1) अणु
		pmu->nr_arch_fixed_counters = 0;
	पूर्ण अन्यथा अणु
		pmu->nr_arch_fixed_counters =
			min_t(पूर्णांक, edx.split.num_counters_fixed,
			      x86_pmu.num_counters_fixed);
		edx.split.bit_width_fixed = min_t(पूर्णांक,
			edx.split.bit_width_fixed, x86_pmu.bit_width_fixed);
		pmu->counter_biपंचांगask[KVM_PMC_FIXED] =
			((u64)1 << edx.split.bit_width_fixed) - 1;
	पूर्ण

	pmu->global_ctrl = ((1ull << pmu->nr_arch_gp_counters) - 1) |
		(((1ull << pmu->nr_arch_fixed_counters) - 1) << INTEL_PMC_IDX_FIXED);
	pmu->global_ctrl_mask = ~pmu->global_ctrl;
	pmu->global_ovf_ctrl_mask = pmu->global_ctrl_mask
			& ~(MSR_CORE_PERF_GLOBAL_OVF_CTRL_OVF_BUF |
			    MSR_CORE_PERF_GLOBAL_OVF_CTRL_COND_CHGD);
	अगर (vmx_pt_mode_is_host_guest())
		pmu->global_ovf_ctrl_mask &=
				~MSR_CORE_PERF_GLOBAL_OVF_CTRL_TRACE_TOPA_PMI;

	entry = kvm_find_cpuid_entry(vcpu, 7, 0);
	अगर (entry &&
	    (boot_cpu_has(X86_FEATURE_HLE) || boot_cpu_has(X86_FEATURE_RTM)) &&
	    (entry->ebx & (X86_FEATURE_HLE|X86_FEATURE_RTM)))
		pmu->reserved_bits ^= HSW_IN_TX|HSW_IN_TX_CHECKPOINTED;

	biपंचांगap_set(pmu->all_valid_pmc_idx,
		0, pmu->nr_arch_gp_counters);
	biपंचांगap_set(pmu->all_valid_pmc_idx,
		INTEL_PMC_MAX_GENERIC, pmu->nr_arch_fixed_counters);

	nested_vmx_pmu_entry_निकास_ctls_update(vcpu);

	अगर (पूर्णांकel_pmu_lbr_is_compatible(vcpu))
		x86_perf_get_lbr(&lbr_desc->records);
	अन्यथा
		lbr_desc->records.nr = 0;

	अगर (lbr_desc->records.nr)
		biपंचांगap_set(pmu->all_valid_pmc_idx, INTEL_PMC_IDX_FIXED_VLBR, 1);
पूर्ण

अटल व्योम पूर्णांकel_pmu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा lbr_desc *lbr_desc = vcpu_to_lbr_desc(vcpu);

	क्रम (i = 0; i < INTEL_PMC_MAX_GENERIC; i++) अणु
		pmu->gp_counters[i].type = KVM_PMC_GP;
		pmu->gp_counters[i].vcpu = vcpu;
		pmu->gp_counters[i].idx = i;
		pmu->gp_counters[i].current_config = 0;
	पूर्ण

	क्रम (i = 0; i < INTEL_PMC_MAX_FIXED; i++) अणु
		pmu->fixed_counters[i].type = KVM_PMC_FIXED;
		pmu->fixed_counters[i].vcpu = vcpu;
		pmu->fixed_counters[i].idx = i + INTEL_PMC_IDX_FIXED;
		pmu->fixed_counters[i].current_config = 0;
	पूर्ण

	vcpu->arch.perf_capabilities = vmx_get_perf_capabilities();
	lbr_desc->records.nr = 0;
	lbr_desc->event = शून्य;
	lbr_desc->msr_passthrough = false;
पूर्ण

अटल व्योम पूर्णांकel_pmu_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < INTEL_PMC_MAX_GENERIC; i++) अणु
		pmc = &pmu->gp_counters[i];

		pmc_stop_counter(pmc);
		pmc->counter = pmc->eventsel = 0;
	पूर्ण

	क्रम (i = 0; i < INTEL_PMC_MAX_FIXED; i++) अणु
		pmc = &pmu->fixed_counters[i];

		pmc_stop_counter(pmc);
		pmc->counter = 0;
	पूर्ण

	pmu->fixed_ctr_ctrl = pmu->global_ctrl = pmu->global_status =
		pmu->global_ovf_ctrl = 0;

	पूर्णांकel_pmu_release_guest_lbr_event(vcpu);
पूर्ण

/*
 * Emulate LBR_On_PMI behavior क्रम 1 < pmu.version < 4.
 *
 * If Freeze_LBR_On_PMI = 1, the LBR is frozen on PMI and
 * the KVM emulates to clear the LBR bit (bit 0) in IA32_DEBUGCTL.
 *
 * Guest needs to re-enable LBR to resume branches recording.
 */
अटल व्योम पूर्णांकel_pmu_legacy_मुक्तzing_lbrs_on_pmi(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 data = vmcs_पढ़ो64(GUEST_IA32_DEBUGCTL);

	अगर (data & DEBUGCTLMSR_FREEZE_LBRS_ON_PMI) अणु
		data &= ~DEBUGCTLMSR_LBR;
		vmcs_ग_लिखो64(GUEST_IA32_DEBUGCTL, data);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_deliver_pmi(काष्ठा kvm_vcpu *vcpu)
अणु
	u8 version = vcpu_to_pmu(vcpu)->version;

	अगर (!पूर्णांकel_pmu_lbr_is_enabled(vcpu))
		वापस;

	अगर (version > 1 && version < 4)
		पूर्णांकel_pmu_legacy_मुक्तzing_lbrs_on_pmi(vcpu);
पूर्ण

अटल व्योम vmx_update_पूर्णांकercept_क्रम_lbr_msrs(काष्ठा kvm_vcpu *vcpu, bool set)
अणु
	काष्ठा x86_pmu_lbr *lbr = vcpu_to_lbr_records(vcpu);
	पूर्णांक i;

	क्रम (i = 0; i < lbr->nr; i++) अणु
		vmx_set_पूर्णांकercept_क्रम_msr(vcpu, lbr->from + i, MSR_TYPE_RW, set);
		vmx_set_पूर्णांकercept_क्रम_msr(vcpu, lbr->to + i, MSR_TYPE_RW, set);
		अगर (lbr->info)
			vmx_set_पूर्णांकercept_क्रम_msr(vcpu, lbr->info + i, MSR_TYPE_RW, set);
	पूर्ण

	vmx_set_पूर्णांकercept_क्रम_msr(vcpu, MSR_LBR_SELECT, MSR_TYPE_RW, set);
	vmx_set_पूर्णांकercept_क्रम_msr(vcpu, MSR_LBR_TOS, MSR_TYPE_RW, set);
पूर्ण

अटल अंतरभूत व्योम vmx_disable_lbr_msrs_passthrough(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा lbr_desc *lbr_desc = vcpu_to_lbr_desc(vcpu);

	अगर (!lbr_desc->msr_passthrough)
		वापस;

	vmx_update_पूर्णांकercept_क्रम_lbr_msrs(vcpu, true);
	lbr_desc->msr_passthrough = false;
पूर्ण

अटल अंतरभूत व्योम vmx_enable_lbr_msrs_passthrough(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा lbr_desc *lbr_desc = vcpu_to_lbr_desc(vcpu);

	अगर (lbr_desc->msr_passthrough)
		वापस;

	vmx_update_पूर्णांकercept_क्रम_lbr_msrs(vcpu, false);
	lbr_desc->msr_passthrough = true;
पूर्ण

/*
 * Higher priority host perf events (e.g. cpu pinned) could reclaim the
 * pmu resources (e.g. LBR) that were asचिन्हित to the guest. This is
 * usually करोne via ipi calls (more details in perf_install_in_context).
 *
 * Beक्रमe entering the non-root mode (with irq disabled here), द्विगुन
 * confirm that the pmu features enabled to the guest are not reclaimed
 * by higher priority host events. Otherwise, disallow vcpu's access to
 * the reclaimed features.
 */
व्योम vmx_passthrough_lbr_msrs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा lbr_desc *lbr_desc = vcpu_to_lbr_desc(vcpu);

	अगर (!lbr_desc->event) अणु
		vmx_disable_lbr_msrs_passthrough(vcpu);
		अगर (vmcs_पढ़ो64(GUEST_IA32_DEBUGCTL) & DEBUGCTLMSR_LBR)
			जाओ warn;
		अगर (test_bit(INTEL_PMC_IDX_FIXED_VLBR, pmu->pmc_in_use))
			जाओ warn;
		वापस;
	पूर्ण

	अगर (lbr_desc->event->state < PERF_EVENT_STATE_ACTIVE) अणु
		vmx_disable_lbr_msrs_passthrough(vcpu);
		__clear_bit(INTEL_PMC_IDX_FIXED_VLBR, pmu->pmc_in_use);
		जाओ warn;
	पूर्ण अन्यथा
		vmx_enable_lbr_msrs_passthrough(vcpu);

	वापस;

warn:
	pr_warn_ratelimited("kvm: vcpu-%d: fail to passthrough LBR.\n",
		vcpu->vcpu_id);
पूर्ण

अटल व्योम पूर्णांकel_pmu_cleanup(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(vmcs_पढ़ो64(GUEST_IA32_DEBUGCTL) & DEBUGCTLMSR_LBR))
		पूर्णांकel_pmu_release_guest_lbr_event(vcpu);
पूर्ण

काष्ठा kvm_pmu_ops पूर्णांकel_pmu_ops = अणु
	.find_arch_event = पूर्णांकel_find_arch_event,
	.find_fixed_event = पूर्णांकel_find_fixed_event,
	.pmc_is_enabled = पूर्णांकel_pmc_is_enabled,
	.pmc_idx_to_pmc = पूर्णांकel_pmc_idx_to_pmc,
	.rdpmc_ecx_to_pmc = पूर्णांकel_rdpmc_ecx_to_pmc,
	.msr_idx_to_pmc = पूर्णांकel_msr_idx_to_pmc,
	.is_valid_rdpmc_ecx = पूर्णांकel_is_valid_rdpmc_ecx,
	.is_valid_msr = पूर्णांकel_is_valid_msr,
	.get_msr = पूर्णांकel_pmu_get_msr,
	.set_msr = पूर्णांकel_pmu_set_msr,
	.refresh = पूर्णांकel_pmu_refresh,
	.init = पूर्णांकel_pmu_init,
	.reset = पूर्णांकel_pmu_reset,
	.deliver_pmi = पूर्णांकel_pmu_deliver_pmi,
	.cleanup = पूर्णांकel_pmu_cleanup,
पूर्ण;
