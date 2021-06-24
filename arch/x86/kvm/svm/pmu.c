<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KVM PMU support क्रम AMD
 *
 * Copyright 2015, Red Hat, Inc. and/or its affiliates.
 *
 * Author:
 *   Wei Huang <wei@redhat.com>
 *
 * Implementation is based on pmu_पूर्णांकel.c file
 */
#समावेश <linux/types.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/perf_event.h>
#समावेश "x86.h"
#समावेश "cpuid.h"
#समावेश "lapic.h"
#समावेश "pmu.h"

क्रमागत pmu_type अणु
	PMU_TYPE_COUNTER = 0,
	PMU_TYPE_EVNTSEL,
पूर्ण;

क्रमागत index अणु
	INDEX_ZERO = 0,
	INDEX_ONE,
	INDEX_TWO,
	INDEX_THREE,
	INDEX_FOUR,
	INDEX_FIVE,
	INDEX_ERROR,
पूर्ण;

/* duplicated from amd_perfmon_event_map, K7 and above should work. */
अटल काष्ठा kvm_event_hw_type_mapping amd_event_mapping[] = अणु
	[0] = अणु 0x76, 0x00, PERF_COUNT_HW_CPU_CYCLES पूर्ण,
	[1] = अणु 0xc0, 0x00, PERF_COUNT_HW_INSTRUCTIONS पूर्ण,
	[2] = अणु 0x7d, 0x07, PERF_COUNT_HW_CACHE_REFERENCES पूर्ण,
	[3] = अणु 0x7e, 0x07, PERF_COUNT_HW_CACHE_MISSES पूर्ण,
	[4] = अणु 0xc2, 0x00, PERF_COUNT_HW_BRANCH_INSTRUCTIONS पूर्ण,
	[5] = अणु 0xc3, 0x00, PERF_COUNT_HW_BRANCH_MISSES पूर्ण,
	[6] = अणु 0xd0, 0x00, PERF_COUNT_HW_STALLED_CYCLES_FRONTEND पूर्ण,
	[7] = अणु 0xd1, 0x00, PERF_COUNT_HW_STALLED_CYCLES_BACKEND पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक get_msr_base(काष्ठा kvm_pmu *pmu, क्रमागत pmu_type type)
अणु
	काष्ठा kvm_vcpu *vcpu = pmu_to_vcpu(pmu);

	अगर (guest_cpuid_has(vcpu, X86_FEATURE_PERFCTR_CORE)) अणु
		अगर (type == PMU_TYPE_COUNTER)
			वापस MSR_F15H_PERF_CTR;
		अन्यथा
			वापस MSR_F15H_PERF_CTL;
	पूर्ण अन्यथा अणु
		अगर (type == PMU_TYPE_COUNTER)
			वापस MSR_K7_PERFCTR0;
		अन्यथा
			वापस MSR_K7_EVNTSEL0;
	पूर्ण
पूर्ण

अटल क्रमागत index msr_to_index(u32 msr)
अणु
	चयन (msr) अणु
	हाल MSR_F15H_PERF_CTL0:
	हाल MSR_F15H_PERF_CTR0:
	हाल MSR_K7_EVNTSEL0:
	हाल MSR_K7_PERFCTR0:
		वापस INDEX_ZERO;
	हाल MSR_F15H_PERF_CTL1:
	हाल MSR_F15H_PERF_CTR1:
	हाल MSR_K7_EVNTSEL1:
	हाल MSR_K7_PERFCTR1:
		वापस INDEX_ONE;
	हाल MSR_F15H_PERF_CTL2:
	हाल MSR_F15H_PERF_CTR2:
	हाल MSR_K7_EVNTSEL2:
	हाल MSR_K7_PERFCTR2:
		वापस INDEX_TWO;
	हाल MSR_F15H_PERF_CTL3:
	हाल MSR_F15H_PERF_CTR3:
	हाल MSR_K7_EVNTSEL3:
	हाल MSR_K7_PERFCTR3:
		वापस INDEX_THREE;
	हाल MSR_F15H_PERF_CTL4:
	हाल MSR_F15H_PERF_CTR4:
		वापस INDEX_FOUR;
	हाल MSR_F15H_PERF_CTL5:
	हाल MSR_F15H_PERF_CTR5:
		वापस INDEX_FIVE;
	शेष:
		वापस INDEX_ERROR;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा kvm_pmc *get_gp_pmc_amd(काष्ठा kvm_pmu *pmu, u32 msr,
					     क्रमागत pmu_type type)
अणु
	काष्ठा kvm_vcpu *vcpu = pmu_to_vcpu(pmu);

	चयन (msr) अणु
	हाल MSR_F15H_PERF_CTL0:
	हाल MSR_F15H_PERF_CTL1:
	हाल MSR_F15H_PERF_CTL2:
	हाल MSR_F15H_PERF_CTL3:
	हाल MSR_F15H_PERF_CTL4:
	हाल MSR_F15H_PERF_CTL5:
		अगर (!guest_cpuid_has(vcpu, X86_FEATURE_PERFCTR_CORE))
			वापस शून्य;
		fallthrough;
	हाल MSR_K7_EVNTSEL0 ... MSR_K7_EVNTSEL3:
		अगर (type != PMU_TYPE_EVNTSEL)
			वापस शून्य;
		अवरोध;
	हाल MSR_F15H_PERF_CTR0:
	हाल MSR_F15H_PERF_CTR1:
	हाल MSR_F15H_PERF_CTR2:
	हाल MSR_F15H_PERF_CTR3:
	हाल MSR_F15H_PERF_CTR4:
	हाल MSR_F15H_PERF_CTR5:
		अगर (!guest_cpuid_has(vcpu, X86_FEATURE_PERFCTR_CORE))
			वापस शून्य;
		fallthrough;
	हाल MSR_K7_PERFCTR0 ... MSR_K7_PERFCTR3:
		अगर (type != PMU_TYPE_COUNTER)
			वापस शून्य;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	वापस &pmu->gp_counters[msr_to_index(msr)];
पूर्ण

अटल अचिन्हित amd_find_arch_event(काष्ठा kvm_pmu *pmu,
				    u8 event_select,
				    u8 unit_mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(amd_event_mapping); i++)
		अगर (amd_event_mapping[i].eventsel == event_select
		    && amd_event_mapping[i].unit_mask == unit_mask)
			अवरोध;

	अगर (i == ARRAY_SIZE(amd_event_mapping))
		वापस PERF_COUNT_HW_MAX;

	वापस amd_event_mapping[i].event_type;
पूर्ण

/* वापस PERF_COUNT_HW_MAX as AMD करोesn't have fixed events */
अटल अचिन्हित amd_find_fixed_event(पूर्णांक idx)
अणु
	वापस PERF_COUNT_HW_MAX;
पूर्ण

/* check अगर a PMC is enabled by comparing it against global_ctrl bits. Because
 * AMD CPU करोesn't have global_ctrl MSR, all PMCs are enabled (वापस TRUE).
 */
अटल bool amd_pmc_is_enabled(काष्ठा kvm_pmc *pmc)
अणु
	वापस true;
पूर्ण

अटल काष्ठा kvm_pmc *amd_pmc_idx_to_pmc(काष्ठा kvm_pmu *pmu, पूर्णांक pmc_idx)
अणु
	अचिन्हित पूर्णांक base = get_msr_base(pmu, PMU_TYPE_COUNTER);
	काष्ठा kvm_vcpu *vcpu = pmu_to_vcpu(pmu);

	अगर (guest_cpuid_has(vcpu, X86_FEATURE_PERFCTR_CORE)) अणु
		/*
		 * The idx is contiguous. The MSRs are not. The counter MSRs
		 * are पूर्णांकerleaved with the event select MSRs.
		 */
		pmc_idx *= 2;
	पूर्ण

	वापस get_gp_pmc_amd(pmu, base + pmc_idx, PMU_TYPE_COUNTER);
पूर्ण

/* वापसs 0 अगर idx's corresponding MSR exists; otherwise वापसs 1. */
अटल पूर्णांक amd_is_valid_rdpmc_ecx(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	idx &= ~(3u << 30);

	वापस (idx >= pmu->nr_arch_gp_counters);
पूर्ण

/* idx is the ECX रेजिस्टर of RDPMC inकाष्ठाion */
अटल काष्ठा kvm_pmc *amd_rdpmc_ecx_to_pmc(काष्ठा kvm_vcpu *vcpu,
	अचिन्हित पूर्णांक idx, u64 *mask)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *counters;

	idx &= ~(3u << 30);
	अगर (idx >= pmu->nr_arch_gp_counters)
		वापस शून्य;
	counters = pmu->gp_counters;

	वापस &counters[idx];
पूर्ण

अटल bool amd_is_valid_msr(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	/* All MSRs refer to exactly one PMC, so msr_idx_to_pmc is enough.  */
	वापस false;
पूर्ण

अटल काष्ठा kvm_pmc *amd_msr_idx_to_pmc(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc;

	pmc = get_gp_pmc_amd(pmu, msr, PMU_TYPE_COUNTER);
	pmc = pmc ? pmc : get_gp_pmc_amd(pmu, msr, PMU_TYPE_EVNTSEL);

	वापस pmc;
पूर्ण

अटल पूर्णांक amd_pmu_get_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc;
	u32 msr = msr_info->index;

	/* MSR_PERFCTRn */
	pmc = get_gp_pmc_amd(pmu, msr, PMU_TYPE_COUNTER);
	अगर (pmc) अणु
		msr_info->data = pmc_पढ़ो_counter(pmc);
		वापस 0;
	पूर्ण
	/* MSR_EVNTSELn */
	pmc = get_gp_pmc_amd(pmu, msr, PMU_TYPE_EVNTSEL);
	अगर (pmc) अणु
		msr_info->data = pmc->eventsel;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक amd_pmu_set_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	काष्ठा kvm_pmc *pmc;
	u32 msr = msr_info->index;
	u64 data = msr_info->data;

	/* MSR_PERFCTRn */
	pmc = get_gp_pmc_amd(pmu, msr, PMU_TYPE_COUNTER);
	अगर (pmc) अणु
		pmc->counter += data - pmc_पढ़ो_counter(pmc);
		वापस 0;
	पूर्ण
	/* MSR_EVNTSELn */
	pmc = get_gp_pmc_amd(pmu, msr, PMU_TYPE_EVNTSEL);
	अगर (pmc) अणु
		अगर (data == pmc->eventsel)
			वापस 0;
		अगर (!(data & pmu->reserved_bits)) अणु
			reprogram_gp_counter(pmc, data);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम amd_pmu_refresh(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	अगर (guest_cpuid_has(vcpu, X86_FEATURE_PERFCTR_CORE))
		pmu->nr_arch_gp_counters = AMD64_NUM_COUNTERS_CORE;
	अन्यथा
		pmu->nr_arch_gp_counters = AMD64_NUM_COUNTERS;

	pmu->counter_biपंचांगask[KVM_PMC_GP] = ((u64)1 << 48) - 1;
	pmu->reserved_bits = 0xffffffff00200000ull;
	pmu->version = 1;
	/* not applicable to AMD; but clean them to prevent any fall out */
	pmu->counter_biपंचांगask[KVM_PMC_FIXED] = 0;
	pmu->nr_arch_fixed_counters = 0;
	pmu->global_status = 0;
	biपंचांगap_set(pmu->all_valid_pmc_idx, 0, pmu->nr_arch_gp_counters);
पूर्ण

अटल व्योम amd_pmu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	पूर्णांक i;

	BUILD_BUG_ON(AMD64_NUM_COUNTERS_CORE > INTEL_PMC_MAX_GENERIC);

	क्रम (i = 0; i < AMD64_NUM_COUNTERS_CORE ; i++) अणु
		pmu->gp_counters[i].type = KVM_PMC_GP;
		pmu->gp_counters[i].vcpu = vcpu;
		pmu->gp_counters[i].idx = i;
		pmu->gp_counters[i].current_config = 0;
	पूर्ण
पूर्ण

अटल व्योम amd_pmu_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	पूर्णांक i;

	क्रम (i = 0; i < AMD64_NUM_COUNTERS_CORE; i++) अणु
		काष्ठा kvm_pmc *pmc = &pmu->gp_counters[i];

		pmc_stop_counter(pmc);
		pmc->counter = pmc->eventsel = 0;
	पूर्ण
पूर्ण

काष्ठा kvm_pmu_ops amd_pmu_ops = अणु
	.find_arch_event = amd_find_arch_event,
	.find_fixed_event = amd_find_fixed_event,
	.pmc_is_enabled = amd_pmc_is_enabled,
	.pmc_idx_to_pmc = amd_pmc_idx_to_pmc,
	.rdpmc_ecx_to_pmc = amd_rdpmc_ecx_to_pmc,
	.msr_idx_to_pmc = amd_msr_idx_to_pmc,
	.is_valid_rdpmc_ecx = amd_is_valid_rdpmc_ecx,
	.is_valid_msr = amd_is_valid_msr,
	.get_msr = amd_pmu_get_msr,
	.set_msr = amd_pmu_set_msr,
	.refresh = amd_pmu_refresh,
	.init = amd_pmu_init,
	.reset = amd_pmu_reset,
पूर्ण;
