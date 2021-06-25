<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_PMU_H
#घोषणा __KVM_X86_PMU_H

#समावेश <linux/nospec.h>

#घोषणा vcpu_to_pmu(vcpu) (&(vcpu)->arch.pmu)
#घोषणा pmu_to_vcpu(pmu)  (container_of((pmu), काष्ठा kvm_vcpu, arch.pmu))
#घोषणा pmc_to_pmu(pmc)   (&(pmc)->vcpu->arch.pmu)

/* retrieve the 4 bits क्रम EN and PMI out of IA32_FIXED_CTR_CTRL */
#घोषणा fixed_ctrl_field(ctrl_reg, idx) (((ctrl_reg) >> ((idx)*4)) & 0xf)

#घोषणा VMWARE_BACKDOOR_PMC_HOST_TSC		0x10000
#घोषणा VMWARE_BACKDOOR_PMC_REAL_TIME		0x10001
#घोषणा VMWARE_BACKDOOR_PMC_APPARENT_TIME	0x10002

#घोषणा MAX_FIXED_COUNTERS	3

काष्ठा kvm_event_hw_type_mapping अणु
	u8 eventsel;
	u8 unit_mask;
	अचिन्हित event_type;
पूर्ण;

काष्ठा kvm_pmu_ops अणु
	अचिन्हित (*find_arch_event)(काष्ठा kvm_pmu *pmu, u8 event_select,
				    u8 unit_mask);
	अचिन्हित (*find_fixed_event)(पूर्णांक idx);
	bool (*pmc_is_enabled)(काष्ठा kvm_pmc *pmc);
	काष्ठा kvm_pmc *(*pmc_idx_to_pmc)(काष्ठा kvm_pmu *pmu, पूर्णांक pmc_idx);
	काष्ठा kvm_pmc *(*rdpmc_ecx_to_pmc)(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित पूर्णांक idx, u64 *mask);
	काष्ठा kvm_pmc *(*msr_idx_to_pmc)(काष्ठा kvm_vcpu *vcpu, u32 msr);
	पूर्णांक (*is_valid_rdpmc_ecx)(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक idx);
	bool (*is_valid_msr)(काष्ठा kvm_vcpu *vcpu, u32 msr);
	पूर्णांक (*get_msr)(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info);
	पूर्णांक (*set_msr)(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info);
	व्योम (*refresh)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*init)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*reset)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*deliver_pmi)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*cleanup)(काष्ठा kvm_vcpu *vcpu);
पूर्ण;

अटल अंतरभूत u64 pmc_biपंचांगask(काष्ठा kvm_pmc *pmc)
अणु
	काष्ठा kvm_pmu *pmu = pmc_to_pmu(pmc);

	वापस pmu->counter_biपंचांगask[pmc->type];
पूर्ण

अटल अंतरभूत u64 pmc_पढ़ो_counter(काष्ठा kvm_pmc *pmc)
अणु
	u64 counter, enabled, running;

	counter = pmc->counter;
	अगर (pmc->perf_event)
		counter += perf_event_पढ़ो_value(pmc->perf_event,
						 &enabled, &running);
	/* FIXME: Scaling needed? */
	वापस counter & pmc_biपंचांगask(pmc);
पूर्ण

अटल अंतरभूत व्योम pmc_release_perf_event(काष्ठा kvm_pmc *pmc)
अणु
	अगर (pmc->perf_event) अणु
		perf_event_release_kernel(pmc->perf_event);
		pmc->perf_event = शून्य;
		pmc->current_config = 0;
		pmc_to_pmu(pmc)->event_count--;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pmc_stop_counter(काष्ठा kvm_pmc *pmc)
अणु
	अगर (pmc->perf_event) अणु
		pmc->counter = pmc_पढ़ो_counter(pmc);
		pmc_release_perf_event(pmc);
	पूर्ण
पूर्ण

अटल अंतरभूत bool pmc_is_gp(काष्ठा kvm_pmc *pmc)
अणु
	वापस pmc->type == KVM_PMC_GP;
पूर्ण

अटल अंतरभूत bool pmc_is_fixed(काष्ठा kvm_pmc *pmc)
अणु
	वापस pmc->type == KVM_PMC_FIXED;
पूर्ण

अटल अंतरभूत bool pmc_is_enabled(काष्ठा kvm_pmc *pmc)
अणु
	वापस kvm_x86_ops.pmu_ops->pmc_is_enabled(pmc);
पूर्ण

अटल अंतरभूत bool kvm_valid_perf_global_ctrl(काष्ठा kvm_pmu *pmu,
						 u64 data)
अणु
	वापस !(pmu->global_ctrl_mask & data);
पूर्ण

/* वापसs general purpose PMC with the specअगरied MSR. Note that it can be
 * used क्रम both PERFCTRn and EVNTSELn; that is why it accepts base as a
 * parameter to tell them apart.
 */
अटल अंतरभूत काष्ठा kvm_pmc *get_gp_pmc(काष्ठा kvm_pmu *pmu, u32 msr,
					 u32 base)
अणु
	अगर (msr >= base && msr < base + pmu->nr_arch_gp_counters) अणु
		u32 index = array_index_nospec(msr - base,
					       pmu->nr_arch_gp_counters);

		वापस &pmu->gp_counters[index];
	पूर्ण

	वापस शून्य;
पूर्ण

/* वापसs fixed PMC with the specअगरied MSR */
अटल अंतरभूत काष्ठा kvm_pmc *get_fixed_pmc(काष्ठा kvm_pmu *pmu, u32 msr)
अणु
	पूर्णांक base = MSR_CORE_PERF_FIXED_CTR0;

	अगर (msr >= base && msr < base + pmu->nr_arch_fixed_counters) अणु
		u32 index = array_index_nospec(msr - base,
					       pmu->nr_arch_fixed_counters);

		वापस &pmu->fixed_counters[index];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत u64 get_sample_period(काष्ठा kvm_pmc *pmc, u64 counter_value)
अणु
	u64 sample_period = (-counter_value) & pmc_biपंचांगask(pmc);

	अगर (!sample_period)
		sample_period = pmc_biपंचांगask(pmc) + 1;
	वापस sample_period;
पूर्ण

व्योम reprogram_gp_counter(काष्ठा kvm_pmc *pmc, u64 eventsel);
व्योम reprogram_fixed_counter(काष्ठा kvm_pmc *pmc, u8 ctrl, पूर्णांक fixed_idx);
व्योम reprogram_counter(काष्ठा kvm_pmu *pmu, पूर्णांक pmc_idx);

व्योम kvm_pmu_deliver_pmi(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_handle_event(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_pmu_rdpmc(काष्ठा kvm_vcpu *vcpu, अचिन्हित pmc, u64 *data);
पूर्णांक kvm_pmu_is_valid_rdpmc_ecx(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक idx);
bool kvm_pmu_is_valid_msr(काष्ठा kvm_vcpu *vcpu, u32 msr);
पूर्णांक kvm_pmu_get_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info);
पूर्णांक kvm_pmu_set_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info);
व्योम kvm_pmu_refresh(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_reset(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_init(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_cleanup(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_destroy(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_vm_ioctl_set_pmu_event_filter(काष्ठा kvm *kvm, व्योम __user *argp);

bool is_vmware_backकरोor_pmc(u32 pmc_idx);

बाह्य काष्ठा kvm_pmu_ops पूर्णांकel_pmu_ops;
बाह्य काष्ठा kvm_pmu_ops amd_pmu_ops;
#पूर्ण_अगर /* __KVM_X86_PMU_H */
