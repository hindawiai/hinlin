<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Linaro Ltd.
 * Author: Shannon Zhao <shannon.zhao@linaro.org>
 */

#अगर_अघोषित __ASM_ARM_KVM_PMU_H
#घोषणा __ASM_ARM_KVM_PMU_H

#समावेश <linux/perf_event.h>
#समावेश <यंत्र/perf_event.h>

#घोषणा ARMV8_PMU_CYCLE_IDX		(ARMV8_PMU_MAX_COUNTERS - 1)
#घोषणा ARMV8_PMU_MAX_COUNTER_PAIRS	((ARMV8_PMU_MAX_COUNTERS + 1) >> 1)

DECLARE_STATIC_KEY_FALSE(kvm_arm_pmu_available);

अटल __always_अंतरभूत bool kvm_arm_support_pmu_v3(व्योम)
अणु
	वापस अटल_branch_likely(&kvm_arm_pmu_available);
पूर्ण

#अगर_घोषित CONFIG_HW_PERF_EVENTS

काष्ठा kvm_pmc अणु
	u8 idx;	/* index पूर्णांकo the pmu->pmc array */
	काष्ठा perf_event *perf_event;
पूर्ण;

काष्ठा kvm_pmu अणु
	पूर्णांक irq_num;
	काष्ठा kvm_pmc pmc[ARMV8_PMU_MAX_COUNTERS];
	DECLARE_BITMAP(chained, ARMV8_PMU_MAX_COUNTER_PAIRS);
	bool created;
	bool irq_level;
	काष्ठा irq_work overflow_work;
पूर्ण;

#घोषणा kvm_arm_pmu_irq_initialized(v)	((v)->arch.pmu.irq_num >= VGIC_NR_SGIS)
u64 kvm_pmu_get_counter_value(काष्ठा kvm_vcpu *vcpu, u64 select_idx);
व्योम kvm_pmu_set_counter_value(काष्ठा kvm_vcpu *vcpu, u64 select_idx, u64 val);
u64 kvm_pmu_valid_counter_mask(काष्ठा kvm_vcpu *vcpu);
u64 kvm_pmu_get_pmceid(काष्ठा kvm_vcpu *vcpu, bool pmceid1);
व्योम kvm_pmu_vcpu_init(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_vcpu_reset(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_vcpu_destroy(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_disable_counter_mask(काष्ठा kvm_vcpu *vcpu, u64 val);
व्योम kvm_pmu_enable_counter_mask(काष्ठा kvm_vcpu *vcpu, u64 val);
व्योम kvm_pmu_flush_hwstate(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_sync_hwstate(काष्ठा kvm_vcpu *vcpu);
bool kvm_pmu_should_notअगरy_user(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_update_run(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_pmu_software_increment(काष्ठा kvm_vcpu *vcpu, u64 val);
व्योम kvm_pmu_handle_pmcr(काष्ठा kvm_vcpu *vcpu, u64 val);
व्योम kvm_pmu_set_counter_event_type(काष्ठा kvm_vcpu *vcpu, u64 data,
				    u64 select_idx);
पूर्णांक kvm_arm_pmu_v3_set_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_pmu_v3_get_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_pmu_v3_has_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr);
पूर्णांक kvm_arm_pmu_v3_enable(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_pmu_probe_pmuver(व्योम);
#अन्यथा
काष्ठा kvm_pmu अणु
पूर्ण;

#घोषणा kvm_arm_pmu_irq_initialized(v)	(false)
अटल अंतरभूत u64 kvm_pmu_get_counter_value(काष्ठा kvm_vcpu *vcpu,
					    u64 select_idx)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम kvm_pmu_set_counter_value(काष्ठा kvm_vcpu *vcpu,
					     u64 select_idx, u64 val) अणुपूर्ण
अटल अंतरभूत u64 kvm_pmu_valid_counter_mask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम kvm_pmu_vcpu_init(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_vcpu_reset(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_vcpu_destroy(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_disable_counter_mask(काष्ठा kvm_vcpu *vcpu, u64 val) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_enable_counter_mask(काष्ठा kvm_vcpu *vcpu, u64 val) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_flush_hwstate(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_sync_hwstate(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत bool kvm_pmu_should_notअगरy_user(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम kvm_pmu_update_run(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_software_increment(काष्ठा kvm_vcpu *vcpu, u64 val) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_handle_pmcr(काष्ठा kvm_vcpu *vcpu, u64 val) अणुपूर्ण
अटल अंतरभूत व्योम kvm_pmu_set_counter_event_type(काष्ठा kvm_vcpu *vcpu,
						  u64 data, u64 select_idx) अणुपूर्ण
अटल अंतरभूत पूर्णांक kvm_arm_pmu_v3_set_attr(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा kvm_device_attr *attr)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत पूर्णांक kvm_arm_pmu_v3_get_attr(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा kvm_device_attr *attr)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत पूर्णांक kvm_arm_pmu_v3_has_attr(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा kvm_device_attr *attr)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत पूर्णांक kvm_arm_pmu_v3_enable(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत u64 kvm_pmu_get_pmceid(काष्ठा kvm_vcpu *vcpu, bool pmceid1)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_pmu_probe_pmuver(व्योम) अणु वापस 0xf; पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
