<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Linaro Ltd.
 * Author: Shannon Zhao <shannon.zhao@linaro.org>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/perf/arm_pmu.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <kvm/arm_pmu.h>
#समावेश <kvm/arm_vgic.h>

अटल व्योम kvm_pmu_create_perf_event(काष्ठा kvm_vcpu *vcpu, u64 select_idx);
अटल व्योम kvm_pmu_update_pmc_chained(काष्ठा kvm_vcpu *vcpu, u64 select_idx);
अटल व्योम kvm_pmu_stop_counter(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_pmc *pmc);

#घोषणा PERF_ATTR_CFG1_KVM_PMU_CHAINED 0x1

अटल u32 kvm_pmu_event_mask(काष्ठा kvm *kvm)
अणु
	चयन (kvm->arch.pmuver) अणु
	हाल ID_AA64DFR0_PMUVER_8_0:
		वापस GENMASK(9, 0);
	हाल ID_AA64DFR0_PMUVER_8_1:
	हाल ID_AA64DFR0_PMUVER_8_4:
	हाल ID_AA64DFR0_PMUVER_8_5:
		वापस GENMASK(15, 0);
	शेष:		/* Shouldn't be here, just क्रम sanity */
		WARN_ONCE(1, "Unknown PMU version %d\n", kvm->arch.pmuver);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * kvm_pmu_idx_is_64bit - determine अगर select_idx is a 64bit counter
 * @vcpu: The vcpu poपूर्णांकer
 * @select_idx: The counter index
 */
अटल bool kvm_pmu_idx_is_64bit(काष्ठा kvm_vcpu *vcpu, u64 select_idx)
अणु
	वापस (select_idx == ARMV8_PMU_CYCLE_IDX &&
		__vcpu_sys_reg(vcpu, PMCR_EL0) & ARMV8_PMU_PMCR_LC);
पूर्ण

अटल काष्ठा kvm_vcpu *kvm_pmc_to_vcpu(काष्ठा kvm_pmc *pmc)
अणु
	काष्ठा kvm_pmu *pmu;
	काष्ठा kvm_vcpu_arch *vcpu_arch;

	pmc -= pmc->idx;
	pmu = container_of(pmc, काष्ठा kvm_pmu, pmc[0]);
	vcpu_arch = container_of(pmu, काष्ठा kvm_vcpu_arch, pmu);
	वापस container_of(vcpu_arch, काष्ठा kvm_vcpu, arch);
पूर्ण

/**
 * kvm_pmu_pmc_is_chained - determine अगर the pmc is chained
 * @pmc: The PMU counter poपूर्णांकer
 */
अटल bool kvm_pmu_pmc_is_chained(काष्ठा kvm_pmc *pmc)
अणु
	काष्ठा kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);

	वापस test_bit(pmc->idx >> 1, vcpu->arch.pmu.chained);
पूर्ण

/**
 * kvm_pmu_idx_is_high_counter - determine अगर select_idx is a high/low counter
 * @select_idx: The counter index
 */
अटल bool kvm_pmu_idx_is_high_counter(u64 select_idx)
अणु
	वापस select_idx & 0x1;
पूर्ण

/**
 * kvm_pmu_get_canonical_pmc - obtain the canonical pmc
 * @pmc: The PMU counter poपूर्णांकer
 *
 * When a pair of PMCs are chained together we use the low counter (canonical)
 * to hold the underlying perf event.
 */
अटल काष्ठा kvm_pmc *kvm_pmu_get_canonical_pmc(काष्ठा kvm_pmc *pmc)
अणु
	अगर (kvm_pmu_pmc_is_chained(pmc) &&
	    kvm_pmu_idx_is_high_counter(pmc->idx))
		वापस pmc - 1;

	वापस pmc;
पूर्ण
अटल काष्ठा kvm_pmc *kvm_pmu_get_alternate_pmc(काष्ठा kvm_pmc *pmc)
अणु
	अगर (kvm_pmu_idx_is_high_counter(pmc->idx))
		वापस pmc - 1;
	अन्यथा
		वापस pmc + 1;
पूर्ण

/**
 * kvm_pmu_idx_has_chain_evtype - determine अगर the event type is chain
 * @vcpu: The vcpu poपूर्णांकer
 * @select_idx: The counter index
 */
अटल bool kvm_pmu_idx_has_chain_evtype(काष्ठा kvm_vcpu *vcpu, u64 select_idx)
अणु
	u64 eventsel, reg;

	select_idx |= 0x1;

	अगर (select_idx == ARMV8_PMU_CYCLE_IDX)
		वापस false;

	reg = PMEVTYPER0_EL0 + select_idx;
	eventsel = __vcpu_sys_reg(vcpu, reg) & kvm_pmu_event_mask(vcpu->kvm);

	वापस eventsel == ARMV8_PMUV3_PERFCTR_CHAIN;
पूर्ण

/**
 * kvm_pmu_get_pair_counter_value - get PMU counter value
 * @vcpu: The vcpu poपूर्णांकer
 * @pmc: The PMU counter poपूर्णांकer
 */
अटल u64 kvm_pmu_get_pair_counter_value(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा kvm_pmc *pmc)
अणु
	u64 counter, counter_high, reg, enabled, running;

	अगर (kvm_pmu_pmc_is_chained(pmc)) अणु
		pmc = kvm_pmu_get_canonical_pmc(pmc);
		reg = PMEVCNTR0_EL0 + pmc->idx;

		counter = __vcpu_sys_reg(vcpu, reg);
		counter_high = __vcpu_sys_reg(vcpu, reg + 1);

		counter = lower_32_bits(counter) | (counter_high << 32);
	पूर्ण अन्यथा अणु
		reg = (pmc->idx == ARMV8_PMU_CYCLE_IDX)
		      ? PMCCNTR_EL0 : PMEVCNTR0_EL0 + pmc->idx;
		counter = __vcpu_sys_reg(vcpu, reg);
	पूर्ण

	/*
	 * The real counter value is equal to the value of counter रेजिस्टर plus
	 * the value perf event counts.
	 */
	अगर (pmc->perf_event)
		counter += perf_event_पढ़ो_value(pmc->perf_event, &enabled,
						 &running);

	वापस counter;
पूर्ण

/**
 * kvm_pmu_get_counter_value - get PMU counter value
 * @vcpu: The vcpu poपूर्णांकer
 * @select_idx: The counter index
 */
u64 kvm_pmu_get_counter_value(काष्ठा kvm_vcpu *vcpu, u64 select_idx)
अणु
	u64 counter;
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	काष्ठा kvm_pmc *pmc = &pmu->pmc[select_idx];

	counter = kvm_pmu_get_pair_counter_value(vcpu, pmc);

	अगर (kvm_pmu_pmc_is_chained(pmc) &&
	    kvm_pmu_idx_is_high_counter(select_idx))
		counter = upper_32_bits(counter);
	अन्यथा अगर (select_idx != ARMV8_PMU_CYCLE_IDX)
		counter = lower_32_bits(counter);

	वापस counter;
पूर्ण

/**
 * kvm_pmu_set_counter_value - set PMU counter value
 * @vcpu: The vcpu poपूर्णांकer
 * @select_idx: The counter index
 * @val: The counter value
 */
व्योम kvm_pmu_set_counter_value(काष्ठा kvm_vcpu *vcpu, u64 select_idx, u64 val)
अणु
	u64 reg;

	reg = (select_idx == ARMV8_PMU_CYCLE_IDX)
	      ? PMCCNTR_EL0 : PMEVCNTR0_EL0 + select_idx;
	__vcpu_sys_reg(vcpu, reg) += (s64)val - kvm_pmu_get_counter_value(vcpu, select_idx);

	/* Recreate the perf event to reflect the updated sample_period */
	kvm_pmu_create_perf_event(vcpu, select_idx);
पूर्ण

/**
 * kvm_pmu_release_perf_event - हटाओ the perf event
 * @pmc: The PMU counter poपूर्णांकer
 */
अटल व्योम kvm_pmu_release_perf_event(काष्ठा kvm_pmc *pmc)
अणु
	pmc = kvm_pmu_get_canonical_pmc(pmc);
	अगर (pmc->perf_event) अणु
		perf_event_disable(pmc->perf_event);
		perf_event_release_kernel(pmc->perf_event);
		pmc->perf_event = शून्य;
	पूर्ण
पूर्ण

/**
 * kvm_pmu_stop_counter - stop PMU counter
 * @pmc: The PMU counter poपूर्णांकer
 *
 * If this counter has been configured to monitor some event, release it here.
 */
अटल व्योम kvm_pmu_stop_counter(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_pmc *pmc)
अणु
	u64 counter, reg, val;

	pmc = kvm_pmu_get_canonical_pmc(pmc);
	अगर (!pmc->perf_event)
		वापस;

	counter = kvm_pmu_get_pair_counter_value(vcpu, pmc);

	अगर (pmc->idx == ARMV8_PMU_CYCLE_IDX) अणु
		reg = PMCCNTR_EL0;
		val = counter;
	पूर्ण अन्यथा अणु
		reg = PMEVCNTR0_EL0 + pmc->idx;
		val = lower_32_bits(counter);
	पूर्ण

	__vcpu_sys_reg(vcpu, reg) = val;

	अगर (kvm_pmu_pmc_is_chained(pmc))
		__vcpu_sys_reg(vcpu, reg + 1) = upper_32_bits(counter);

	kvm_pmu_release_perf_event(pmc);
पूर्ण

/**
 * kvm_pmu_vcpu_init - assign pmu counter idx क्रम cpu
 * @vcpu: The vcpu poपूर्णांकer
 *
 */
व्योम kvm_pmu_vcpu_init(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;

	क्रम (i = 0; i < ARMV8_PMU_MAX_COUNTERS; i++)
		pmu->pmc[i].idx = i;
पूर्ण

/**
 * kvm_pmu_vcpu_reset - reset pmu state क्रम cpu
 * @vcpu: The vcpu poपूर्णांकer
 *
 */
व्योम kvm_pmu_vcpu_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ mask = kvm_pmu_valid_counter_mask(vcpu);
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	पूर्णांक i;

	क्रम_each_set_bit(i, &mask, 32)
		kvm_pmu_stop_counter(vcpu, &pmu->pmc[i]);

	biपंचांगap_zero(vcpu->arch.pmu.chained, ARMV8_PMU_MAX_COUNTER_PAIRS);
पूर्ण

/**
 * kvm_pmu_vcpu_destroy - मुक्त perf event of PMU क्रम cpu
 * @vcpu: The vcpu poपूर्णांकer
 *
 */
व्योम kvm_pmu_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;

	क्रम (i = 0; i < ARMV8_PMU_MAX_COUNTERS; i++)
		kvm_pmu_release_perf_event(&pmu->pmc[i]);
	irq_work_sync(&vcpu->arch.pmu.overflow_work);
पूर्ण

u64 kvm_pmu_valid_counter_mask(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 val = __vcpu_sys_reg(vcpu, PMCR_EL0) >> ARMV8_PMU_PMCR_N_SHIFT;

	val &= ARMV8_PMU_PMCR_N_MASK;
	अगर (val == 0)
		वापस BIT(ARMV8_PMU_CYCLE_IDX);
	अन्यथा
		वापस GENMASK(val - 1, 0) | BIT(ARMV8_PMU_CYCLE_IDX);
पूर्ण

/**
 * kvm_pmu_enable_counter_mask - enable selected PMU counters
 * @vcpu: The vcpu poपूर्णांकer
 * @val: the value guest ग_लिखोs to PMCNTENSET रेजिस्टर
 *
 * Call perf_event_enable to start counting the perf event
 */
व्योम kvm_pmu_enable_counter_mask(काष्ठा kvm_vcpu *vcpu, u64 val)
अणु
	पूर्णांक i;
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	काष्ठा kvm_pmc *pmc;

	अगर (!(__vcpu_sys_reg(vcpu, PMCR_EL0) & ARMV8_PMU_PMCR_E) || !val)
		वापस;

	क्रम (i = 0; i < ARMV8_PMU_MAX_COUNTERS; i++) अणु
		अगर (!(val & BIT(i)))
			जारी;

		pmc = &pmu->pmc[i];

		/* A change in the enable state may affect the chain state */
		kvm_pmu_update_pmc_chained(vcpu, i);
		kvm_pmu_create_perf_event(vcpu, i);

		/* At this poपूर्णांक, pmc must be the canonical */
		अगर (pmc->perf_event) अणु
			perf_event_enable(pmc->perf_event);
			अगर (pmc->perf_event->state != PERF_EVENT_STATE_ACTIVE)
				kvm_debug("fail to enable perf event\n");
		पूर्ण
	पूर्ण
पूर्ण

/**
 * kvm_pmu_disable_counter_mask - disable selected PMU counters
 * @vcpu: The vcpu poपूर्णांकer
 * @val: the value guest ग_लिखोs to PMCNTENCLR रेजिस्टर
 *
 * Call perf_event_disable to stop counting the perf event
 */
व्योम kvm_pmu_disable_counter_mask(काष्ठा kvm_vcpu *vcpu, u64 val)
अणु
	पूर्णांक i;
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	काष्ठा kvm_pmc *pmc;

	अगर (!val)
		वापस;

	क्रम (i = 0; i < ARMV8_PMU_MAX_COUNTERS; i++) अणु
		अगर (!(val & BIT(i)))
			जारी;

		pmc = &pmu->pmc[i];

		/* A change in the enable state may affect the chain state */
		kvm_pmu_update_pmc_chained(vcpu, i);
		kvm_pmu_create_perf_event(vcpu, i);

		/* At this poपूर्णांक, pmc must be the canonical */
		अगर (pmc->perf_event)
			perf_event_disable(pmc->perf_event);
	पूर्ण
पूर्ण

अटल u64 kvm_pmu_overflow_status(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 reg = 0;

	अगर ((__vcpu_sys_reg(vcpu, PMCR_EL0) & ARMV8_PMU_PMCR_E)) अणु
		reg = __vcpu_sys_reg(vcpu, PMOVSSET_EL0);
		reg &= __vcpu_sys_reg(vcpu, PMCNTENSET_EL0);
		reg &= __vcpu_sys_reg(vcpu, PMINTENSET_EL1);
		reg &= kvm_pmu_valid_counter_mask(vcpu);
	पूर्ण

	वापस reg;
पूर्ण

अटल व्योम kvm_pmu_update_state(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	bool overflow;

	अगर (!kvm_vcpu_has_pmu(vcpu))
		वापस;

	overflow = !!kvm_pmu_overflow_status(vcpu);
	अगर (pmu->irq_level == overflow)
		वापस;

	pmu->irq_level = overflow;

	अगर (likely(irqchip_in_kernel(vcpu->kvm))) अणु
		पूर्णांक ret = kvm_vgic_inject_irq(vcpu->kvm, vcpu->vcpu_id,
					      pmu->irq_num, overflow, pmu);
		WARN_ON(ret);
	पूर्ण
पूर्ण

bool kvm_pmu_should_notअगरy_user(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	काष्ठा kvm_sync_regs *sregs = &vcpu->run->s.regs;
	bool run_level = sregs->device_irq_level & KVM_ARM_DEV_PMU;

	अगर (likely(irqchip_in_kernel(vcpu->kvm)))
		वापस false;

	वापस pmu->irq_level != run_level;
पूर्ण

/*
 * Reflect the PMU overflow पूर्णांकerrupt output level पूर्णांकo the kvm_run काष्ठाure
 */
व्योम kvm_pmu_update_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_sync_regs *regs = &vcpu->run->s.regs;

	/* Populate the समयr biपंचांगap क्रम user space */
	regs->device_irq_level &= ~KVM_ARM_DEV_PMU;
	अगर (vcpu->arch.pmu.irq_level)
		regs->device_irq_level |= KVM_ARM_DEV_PMU;
पूर्ण

/**
 * kvm_pmu_flush_hwstate - flush pmu state to cpu
 * @vcpu: The vcpu poपूर्णांकer
 *
 * Check अगर the PMU has overflowed जबतक we were running in the host, and inject
 * an पूर्णांकerrupt अगर that was the हाल.
 */
व्योम kvm_pmu_flush_hwstate(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_pmu_update_state(vcpu);
पूर्ण

/**
 * kvm_pmu_sync_hwstate - sync pmu state from cpu
 * @vcpu: The vcpu poपूर्णांकer
 *
 * Check अगर the PMU has overflowed जबतक we were running in the guest, and
 * inject an पूर्णांकerrupt अगर that was the हाल.
 */
व्योम kvm_pmu_sync_hwstate(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_pmu_update_state(vcpu);
पूर्ण

/**
 * When perf पूर्णांकerrupt is an NMI, we cannot safely notअगरy the vcpu corresponding
 * to the event.
 * This is why we need a callback to करो it once outside of the NMI context.
 */
अटल व्योम kvm_pmu_perf_overflow_notअगरy_vcpu(काष्ठा irq_work *work)
अणु
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा kvm_pmu *pmu;

	pmu = container_of(work, काष्ठा kvm_pmu, overflow_work);
	vcpu = kvm_pmc_to_vcpu(pmu->pmc);

	kvm_vcpu_kick(vcpu);
पूर्ण

/**
 * When the perf event overflows, set the overflow status and inक्रमm the vcpu.
 */
अटल व्योम kvm_pmu_perf_overflow(काष्ठा perf_event *perf_event,
				  काष्ठा perf_sample_data *data,
				  काष्ठा pt_regs *regs)
अणु
	काष्ठा kvm_pmc *pmc = perf_event->overflow_handler_context;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(perf_event->pmu);
	काष्ठा kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);
	पूर्णांक idx = pmc->idx;
	u64 period;

	cpu_pmu->pmu.stop(perf_event, PERF_EF_UPDATE);

	/*
	 * Reset the sample period to the architectural limit,
	 * i.e. the poपूर्णांक where the counter overflows.
	 */
	period = -(local64_पढ़ो(&perf_event->count));

	अगर (!kvm_pmu_idx_is_64bit(vcpu, pmc->idx))
		period &= GENMASK(31, 0);

	local64_set(&perf_event->hw.period_left, 0);
	perf_event->attr.sample_period = period;
	perf_event->hw.sample_period = period;

	__vcpu_sys_reg(vcpu, PMOVSSET_EL0) |= BIT(idx);

	अगर (kvm_pmu_overflow_status(vcpu)) अणु
		kvm_make_request(KVM_REQ_IRQ_PENDING, vcpu);

		अगर (!in_nmi())
			kvm_vcpu_kick(vcpu);
		अन्यथा
			irq_work_queue(&vcpu->arch.pmu.overflow_work);
	पूर्ण

	cpu_pmu->pmu.start(perf_event, PERF_EF_RELOAD);
पूर्ण

/**
 * kvm_pmu_software_increment - करो software increment
 * @vcpu: The vcpu poपूर्णांकer
 * @val: the value guest ग_लिखोs to PMSWINC रेजिस्टर
 */
व्योम kvm_pmu_software_increment(काष्ठा kvm_vcpu *vcpu, u64 val)
अणु
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	पूर्णांक i;

	अगर (!(__vcpu_sys_reg(vcpu, PMCR_EL0) & ARMV8_PMU_PMCR_E))
		वापस;

	/* Weed out disabled counters */
	val &= __vcpu_sys_reg(vcpu, PMCNTENSET_EL0);

	क्रम (i = 0; i < ARMV8_PMU_CYCLE_IDX; i++) अणु
		u64 type, reg;

		अगर (!(val & BIT(i)))
			जारी;

		/* PMSWINC only applies to ... SW_INC! */
		type = __vcpu_sys_reg(vcpu, PMEVTYPER0_EL0 + i);
		type &= kvm_pmu_event_mask(vcpu->kvm);
		अगर (type != ARMV8_PMUV3_PERFCTR_SW_INCR)
			जारी;

		/* increment this even SW_INC counter */
		reg = __vcpu_sys_reg(vcpu, PMEVCNTR0_EL0 + i) + 1;
		reg = lower_32_bits(reg);
		__vcpu_sys_reg(vcpu, PMEVCNTR0_EL0 + i) = reg;

		अगर (reg) /* no overflow on the low part */
			जारी;

		अगर (kvm_pmu_pmc_is_chained(&pmu->pmc[i])) अणु
			/* increment the high counter */
			reg = __vcpu_sys_reg(vcpu, PMEVCNTR0_EL0 + i + 1) + 1;
			reg = lower_32_bits(reg);
			__vcpu_sys_reg(vcpu, PMEVCNTR0_EL0 + i + 1) = reg;
			अगर (!reg) /* mark overflow on the high counter */
				__vcpu_sys_reg(vcpu, PMOVSSET_EL0) |= BIT(i + 1);
		पूर्ण अन्यथा अणु
			/* mark overflow on low counter */
			__vcpu_sys_reg(vcpu, PMOVSSET_EL0) |= BIT(i);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * kvm_pmu_handle_pmcr - handle PMCR रेजिस्टर
 * @vcpu: The vcpu poपूर्णांकer
 * @val: the value guest ग_लिखोs to PMCR रेजिस्टर
 */
व्योम kvm_pmu_handle_pmcr(काष्ठा kvm_vcpu *vcpu, u64 val)
अणु
	अचिन्हित दीर्घ mask = kvm_pmu_valid_counter_mask(vcpu);
	पूर्णांक i;

	अगर (val & ARMV8_PMU_PMCR_E) अणु
		kvm_pmu_enable_counter_mask(vcpu,
		       __vcpu_sys_reg(vcpu, PMCNTENSET_EL0) & mask);
	पूर्ण अन्यथा अणु
		kvm_pmu_disable_counter_mask(vcpu, mask);
	पूर्ण

	अगर (val & ARMV8_PMU_PMCR_C)
		kvm_pmu_set_counter_value(vcpu, ARMV8_PMU_CYCLE_IDX, 0);

	अगर (val & ARMV8_PMU_PMCR_P) अणु
		क्रम_each_set_bit(i, &mask, 32)
			kvm_pmu_set_counter_value(vcpu, i, 0);
	पूर्ण
पूर्ण

अटल bool kvm_pmu_counter_is_enabled(काष्ठा kvm_vcpu *vcpu, u64 select_idx)
अणु
	वापस (__vcpu_sys_reg(vcpu, PMCR_EL0) & ARMV8_PMU_PMCR_E) &&
	       (__vcpu_sys_reg(vcpu, PMCNTENSET_EL0) & BIT(select_idx));
पूर्ण

/**
 * kvm_pmu_create_perf_event - create a perf event क्रम a counter
 * @vcpu: The vcpu poपूर्णांकer
 * @select_idx: The number of selected counter
 */
अटल व्योम kvm_pmu_create_perf_event(काष्ठा kvm_vcpu *vcpu, u64 select_idx)
अणु
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	काष्ठा kvm_pmc *pmc;
	काष्ठा perf_event *event;
	काष्ठा perf_event_attr attr;
	u64 eventsel, counter, reg, data;

	/*
	 * For chained counters the event type and filtering attributes are
	 * obtained from the low/even counter. We also use this counter to
	 * determine अगर the event is enabled/disabled.
	 */
	pmc = kvm_pmu_get_canonical_pmc(&pmu->pmc[select_idx]);

	reg = (pmc->idx == ARMV8_PMU_CYCLE_IDX)
	      ? PMCCFILTR_EL0 : PMEVTYPER0_EL0 + pmc->idx;
	data = __vcpu_sys_reg(vcpu, reg);

	kvm_pmu_stop_counter(vcpu, pmc);
	अगर (pmc->idx == ARMV8_PMU_CYCLE_IDX)
		eventsel = ARMV8_PMUV3_PERFCTR_CPU_CYCLES;
	अन्यथा
		eventsel = data & kvm_pmu_event_mask(vcpu->kvm);

	/* Software increment event करोesn't need to be backed by a perf event */
	अगर (eventsel == ARMV8_PMUV3_PERFCTR_SW_INCR)
		वापस;

	/*
	 * If we have a filter in place and that the event isn't allowed, करो
	 * not install a perf event either.
	 */
	अगर (vcpu->kvm->arch.pmu_filter &&
	    !test_bit(eventsel, vcpu->kvm->arch.pmu_filter))
		वापस;

	स_रखो(&attr, 0, माप(काष्ठा perf_event_attr));
	attr.type = PERF_TYPE_RAW;
	attr.size = माप(attr);
	attr.pinned = 1;
	attr.disabled = !kvm_pmu_counter_is_enabled(vcpu, pmc->idx);
	attr.exclude_user = data & ARMV8_PMU_EXCLUDE_EL0 ? 1 : 0;
	attr.exclude_kernel = data & ARMV8_PMU_EXCLUDE_EL1 ? 1 : 0;
	attr.exclude_hv = 1; /* Don't count EL2 events */
	attr.exclude_host = 1; /* Don't count host events */
	attr.config = eventsel;

	counter = kvm_pmu_get_pair_counter_value(vcpu, pmc);

	अगर (kvm_pmu_pmc_is_chained(pmc)) अणु
		/**
		 * The initial sample period (overflow count) of an event. For
		 * chained counters we only support overflow पूर्णांकerrupts on the
		 * high counter.
		 */
		attr.sample_period = (-counter) & GENMASK(63, 0);
		attr.config1 |= PERF_ATTR_CFG1_KVM_PMU_CHAINED;

		event = perf_event_create_kernel_counter(&attr, -1, current,
							 kvm_pmu_perf_overflow,
							 pmc + 1);
	पूर्ण अन्यथा अणु
		/* The initial sample period (overflow count) of an event. */
		अगर (kvm_pmu_idx_is_64bit(vcpu, pmc->idx))
			attr.sample_period = (-counter) & GENMASK(63, 0);
		अन्यथा
			attr.sample_period = (-counter) & GENMASK(31, 0);

		event = perf_event_create_kernel_counter(&attr, -1, current,
						 kvm_pmu_perf_overflow, pmc);
	पूर्ण

	अगर (IS_ERR(event)) अणु
		pr_err_once("kvm: pmu event creation failed %ld\n",
			    PTR_ERR(event));
		वापस;
	पूर्ण

	pmc->perf_event = event;
पूर्ण

/**
 * kvm_pmu_update_pmc_chained - update chained biपंचांगap
 * @vcpu: The vcpu poपूर्णांकer
 * @select_idx: The number of selected counter
 *
 * Update the chained biपंचांगap based on the event type written in the
 * typer रेजिस्टर and the enable state of the odd रेजिस्टर.
 */
अटल व्योम kvm_pmu_update_pmc_chained(काष्ठा kvm_vcpu *vcpu, u64 select_idx)
अणु
	काष्ठा kvm_pmu *pmu = &vcpu->arch.pmu;
	काष्ठा kvm_pmc *pmc = &pmu->pmc[select_idx], *canonical_pmc;
	bool new_state, old_state;

	old_state = kvm_pmu_pmc_is_chained(pmc);
	new_state = kvm_pmu_idx_has_chain_evtype(vcpu, pmc->idx) &&
		    kvm_pmu_counter_is_enabled(vcpu, pmc->idx | 0x1);

	अगर (old_state == new_state)
		वापस;

	canonical_pmc = kvm_pmu_get_canonical_pmc(pmc);
	kvm_pmu_stop_counter(vcpu, canonical_pmc);
	अगर (new_state) अणु
		/*
		 * During promotion from !chained to chained we must ensure
		 * the adjacent counter is stopped and its event destroyed
		 */
		kvm_pmu_stop_counter(vcpu, kvm_pmu_get_alternate_pmc(pmc));
		set_bit(pmc->idx >> 1, vcpu->arch.pmu.chained);
		वापस;
	पूर्ण
	clear_bit(pmc->idx >> 1, vcpu->arch.pmu.chained);
पूर्ण

/**
 * kvm_pmu_set_counter_event_type - set selected counter to monitor some event
 * @vcpu: The vcpu poपूर्णांकer
 * @data: The data guest ग_लिखोs to PMXEVTYPER_EL0
 * @select_idx: The number of selected counter
 *
 * When OS accesses PMXEVTYPER_EL0, that means it wants to set a PMC to count an
 * event with given hardware event number. Here we call perf_event API to
 * emulate this action and create a kernel perf event क्रम it.
 */
व्योम kvm_pmu_set_counter_event_type(काष्ठा kvm_vcpu *vcpu, u64 data,
				    u64 select_idx)
अणु
	u64 reg, mask;

	mask  =  ARMV8_PMU_EVTYPE_MASK;
	mask &= ~ARMV8_PMU_EVTYPE_EVENT;
	mask |= kvm_pmu_event_mask(vcpu->kvm);

	reg = (select_idx == ARMV8_PMU_CYCLE_IDX)
	      ? PMCCFILTR_EL0 : PMEVTYPER0_EL0 + select_idx;

	__vcpu_sys_reg(vcpu, reg) = data & mask;

	kvm_pmu_update_pmc_chained(vcpu, select_idx);
	kvm_pmu_create_perf_event(vcpu, select_idx);
पूर्ण

पूर्णांक kvm_pmu_probe_pmuver(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु पूर्ण;
	काष्ठा perf_event *event;
	काष्ठा arm_pmu *pmu;
	पूर्णांक pmuver = 0xf;

	/*
	 * Create a dummy event that only counts user cycles. As we'll never
	 * leave this function with the event being live, it will never
	 * count anything. But it allows us to probe some of the PMU
	 * details. Yes, this is terrible.
	 */
	attr.type = PERF_TYPE_RAW;
	attr.size = माप(attr);
	attr.pinned = 1;
	attr.disabled = 0;
	attr.exclude_user = 0;
	attr.exclude_kernel = 1;
	attr.exclude_hv = 1;
	attr.exclude_host = 1;
	attr.config = ARMV8_PMUV3_PERFCTR_CPU_CYCLES;
	attr.sample_period = GENMASK(63, 0);

	event = perf_event_create_kernel_counter(&attr, -1, current,
						 kvm_pmu_perf_overflow, &attr);

	अगर (IS_ERR(event)) अणु
		pr_err_once("kvm: pmu event creation failed %ld\n",
			    PTR_ERR(event));
		वापस 0xf;
	पूर्ण

	अगर (event->pmu) अणु
		pmu = to_arm_pmu(event->pmu);
		अगर (pmu->pmuver)
			pmuver = pmu->pmuver;
	पूर्ण

	perf_event_disable(event);
	perf_event_release_kernel(event);

	वापस pmuver;
पूर्ण

u64 kvm_pmu_get_pmceid(काष्ठा kvm_vcpu *vcpu, bool pmceid1)
अणु
	अचिन्हित दीर्घ *bmap = vcpu->kvm->arch.pmu_filter;
	u64 val, mask = 0;
	पूर्णांक base, i, nr_events;

	अगर (!pmceid1) अणु
		val = पढ़ो_sysreg(pmceid0_el0);
		base = 0;
	पूर्ण अन्यथा अणु
		val = पढ़ो_sysreg(pmceid1_el0);
		/*
		 * Don't advertise STALL_SLOT, as PMMIR_EL0 is handled
		 * as RAZ
		 */
		अगर (vcpu->kvm->arch.pmuver >= ID_AA64DFR0_PMUVER_8_4)
			val &= ~BIT_ULL(ARMV8_PMUV3_PERFCTR_STALL_SLOT - 32);
		base = 32;
	पूर्ण

	अगर (!bmap)
		वापस val;

	nr_events = kvm_pmu_event_mask(vcpu->kvm) + 1;

	क्रम (i = 0; i < 32; i += 8) अणु
		u64 byte;

		byte = biपंचांगap_get_value8(bmap, base + i);
		mask |= byte << i;
		अगर (nr_events >= (0x4000 + base + 32)) अणु
			byte = biपंचांगap_get_value8(bmap, 0x4000 + base + i);
			mask |= byte << (32 + i);
		पूर्ण
	पूर्ण

	वापस val & mask;
पूर्ण

पूर्णांक kvm_arm_pmu_v3_enable(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!kvm_vcpu_has_pmu(vcpu))
		वापस 0;

	अगर (!vcpu->arch.pmu.created)
		वापस -EINVAL;

	/*
	 * A valid पूर्णांकerrupt configuration क्रम the PMU is either to have a
	 * properly configured पूर्णांकerrupt number and using an in-kernel
	 * irqchip, or to not have an in-kernel GIC and not set an IRQ.
	 */
	अगर (irqchip_in_kernel(vcpu->kvm)) अणु
		पूर्णांक irq = vcpu->arch.pmu.irq_num;
		/*
		 * If we are using an in-kernel vgic, at this poपूर्णांक we know
		 * the vgic will be initialized, so we can check the PMU irq
		 * number against the dimensions of the vgic and make sure
		 * it's valid.
		 */
		अगर (!irq_is_ppi(irq) && !vgic_valid_spi(vcpu->kvm, irq))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (kvm_arm_pmu_irq_initialized(vcpu)) अणु
		   वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_arm_pmu_v3_init(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (irqchip_in_kernel(vcpu->kvm)) अणु
		पूर्णांक ret;

		/*
		 * If using the PMU with an in-kernel भव GIC
		 * implementation, we require the GIC to be alपढ़ोy
		 * initialized when initializing the PMU.
		 */
		अगर (!vgic_initialized(vcpu->kvm))
			वापस -ENODEV;

		अगर (!kvm_arm_pmu_irq_initialized(vcpu))
			वापस -ENXIO;

		ret = kvm_vgic_set_owner(vcpu, vcpu->arch.pmu.irq_num,
					 &vcpu->arch.pmu);
		अगर (ret)
			वापस ret;
	पूर्ण

	init_irq_work(&vcpu->arch.pmu.overflow_work,
		      kvm_pmu_perf_overflow_notअगरy_vcpu);

	vcpu->arch.pmu.created = true;
	वापस 0;
पूर्ण

/*
 * For one VM the पूर्णांकerrupt type must be same क्रम each vcpu.
 * As a PPI, the पूर्णांकerrupt number is the same क्रम all vcpus,
 * जबतक as an SPI it must be a separate number per vcpu.
 */
अटल bool pmu_irq_is_valid(काष्ठा kvm *kvm, पूर्णांक irq)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (!kvm_arm_pmu_irq_initialized(vcpu))
			जारी;

		अगर (irq_is_ppi(irq)) अणु
			अगर (vcpu->arch.pmu.irq_num != irq)
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (vcpu->arch.pmu.irq_num == irq)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक kvm_arm_pmu_v3_set_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr)
अणु
	अगर (!kvm_vcpu_has_pmu(vcpu))
		वापस -ENODEV;

	अगर (vcpu->arch.pmu.created)
		वापस -EBUSY;

	अगर (!vcpu->kvm->arch.pmuver)
		vcpu->kvm->arch.pmuver = kvm_pmu_probe_pmuver();

	अगर (vcpu->kvm->arch.pmuver == 0xf)
		वापस -ENODEV;

	चयन (attr->attr) अणु
	हाल KVM_ARM_VCPU_PMU_V3_IRQ: अणु
		पूर्णांक __user *uaddr = (पूर्णांक __user *)(दीर्घ)attr->addr;
		पूर्णांक irq;

		अगर (!irqchip_in_kernel(vcpu->kvm))
			वापस -EINVAL;

		अगर (get_user(irq, uaddr))
			वापस -EFAULT;

		/* The PMU overflow पूर्णांकerrupt can be a PPI or a valid SPI. */
		अगर (!(irq_is_ppi(irq) || irq_is_spi(irq)))
			वापस -EINVAL;

		अगर (!pmu_irq_is_valid(vcpu->kvm, irq))
			वापस -EINVAL;

		अगर (kvm_arm_pmu_irq_initialized(vcpu))
			वापस -EBUSY;

		kvm_debug("Set kvm ARM PMU irq: %d\n", irq);
		vcpu->arch.pmu.irq_num = irq;
		वापस 0;
	पूर्ण
	हाल KVM_ARM_VCPU_PMU_V3_FILTER: अणु
		काष्ठा kvm_pmu_event_filter __user *uaddr;
		काष्ठा kvm_pmu_event_filter filter;
		पूर्णांक nr_events;

		nr_events = kvm_pmu_event_mask(vcpu->kvm) + 1;

		uaddr = (काष्ठा kvm_pmu_event_filter __user *)(दीर्घ)attr->addr;

		अगर (copy_from_user(&filter, uaddr, माप(filter)))
			वापस -EFAULT;

		अगर (((u32)filter.base_event + filter.nevents) > nr_events ||
		    (filter.action != KVM_PMU_EVENT_ALLOW &&
		     filter.action != KVM_PMU_EVENT_DENY))
			वापस -EINVAL;

		mutex_lock(&vcpu->kvm->lock);

		अगर (!vcpu->kvm->arch.pmu_filter) अणु
			vcpu->kvm->arch.pmu_filter = biपंचांगap_alloc(nr_events, GFP_KERNEL);
			अगर (!vcpu->kvm->arch.pmu_filter) अणु
				mutex_unlock(&vcpu->kvm->lock);
				वापस -ENOMEM;
			पूर्ण

			/*
			 * The शेष depends on the first applied filter.
			 * If it allows events, the शेष is to deny.
			 * Conversely, अगर the first filter denies a set of
			 * events, the शेष is to allow.
			 */
			अगर (filter.action == KVM_PMU_EVENT_ALLOW)
				biपंचांगap_zero(vcpu->kvm->arch.pmu_filter, nr_events);
			अन्यथा
				biपंचांगap_fill(vcpu->kvm->arch.pmu_filter, nr_events);
		पूर्ण

		अगर (filter.action == KVM_PMU_EVENT_ALLOW)
			biपंचांगap_set(vcpu->kvm->arch.pmu_filter, filter.base_event, filter.nevents);
		अन्यथा
			biपंचांगap_clear(vcpu->kvm->arch.pmu_filter, filter.base_event, filter.nevents);

		mutex_unlock(&vcpu->kvm->lock);

		वापस 0;
	पूर्ण
	हाल KVM_ARM_VCPU_PMU_V3_INIT:
		वापस kvm_arm_pmu_v3_init(vcpu);
	पूर्ण

	वापस -ENXIO;
पूर्ण

पूर्णांक kvm_arm_pmu_v3_get_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->attr) अणु
	हाल KVM_ARM_VCPU_PMU_V3_IRQ: अणु
		पूर्णांक __user *uaddr = (पूर्णांक __user *)(दीर्घ)attr->addr;
		पूर्णांक irq;

		अगर (!irqchip_in_kernel(vcpu->kvm))
			वापस -EINVAL;

		अगर (!kvm_vcpu_has_pmu(vcpu))
			वापस -ENODEV;

		अगर (!kvm_arm_pmu_irq_initialized(vcpu))
			वापस -ENXIO;

		irq = vcpu->arch.pmu.irq_num;
		वापस put_user(irq, uaddr);
	पूर्ण
	पूर्ण

	वापस -ENXIO;
पूर्ण

पूर्णांक kvm_arm_pmu_v3_has_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->attr) अणु
	हाल KVM_ARM_VCPU_PMU_V3_IRQ:
	हाल KVM_ARM_VCPU_PMU_V3_INIT:
	हाल KVM_ARM_VCPU_PMU_V3_FILTER:
		अगर (kvm_vcpu_has_pmu(vcpu))
			वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण
