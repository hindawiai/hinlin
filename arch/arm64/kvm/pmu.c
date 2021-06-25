<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Arm Limited
 * Author: Andrew Murray <Andrew.Murray@arm.com>
 */
#समावेश <linux/kvm_host.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/kvm_hyp.h>

/*
 * Given the perf event attributes and प्रणाली type, determine
 * अगर we are going to need to चयन counters at guest entry/निकास.
 */
अटल bool kvm_pmu_चयन_needed(काष्ठा perf_event_attr *attr)
अणु
	/**
	 * With VHE the guest kernel runs at EL1 and the host at EL2,
	 * where user (EL0) is excluded then we have no reason to चयन
	 * counters.
	 */
	अगर (has_vhe() && attr->exclude_user)
		वापस false;

	/* Only चयन अगर attributes are dअगरferent */
	वापस (attr->exclude_host != attr->exclude_guest);
पूर्ण

/*
 * Add events to track that we may want to चयन at guest entry/निकास
 * समय.
 */
व्योम kvm_set_pmu_events(u32 set, काष्ठा perf_event_attr *attr)
अणु
	काष्ठा kvm_host_data *ctx = this_cpu_ptr_hyp_sym(kvm_host_data);

	अगर (!kvm_arm_support_pmu_v3() || !ctx || !kvm_pmu_चयन_needed(attr))
		वापस;

	अगर (!attr->exclude_host)
		ctx->pmu_events.events_host |= set;
	अगर (!attr->exclude_guest)
		ctx->pmu_events.events_guest |= set;
पूर्ण

/*
 * Stop tracking events
 */
व्योम kvm_clr_pmu_events(u32 clr)
अणु
	काष्ठा kvm_host_data *ctx = this_cpu_ptr_hyp_sym(kvm_host_data);

	अगर (!kvm_arm_support_pmu_v3() || !ctx)
		वापस;

	ctx->pmu_events.events_host &= ~clr;
	ctx->pmu_events.events_guest &= ~clr;
पूर्ण

#घोषणा PMEVTYPER_READ_CASE(idx)				\
	हाल idx:						\
		वापस पढ़ो_sysreg(pmevtyper##idx##_el0)

#घोषणा PMEVTYPER_WRITE_CASE(idx)				\
	हाल idx:						\
		ग_लिखो_sysreg(val, pmevtyper##idx##_el0);	\
		अवरोध

#घोषणा PMEVTYPER_CASES(पढ़ोग_लिखो)				\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(0);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(1);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(2);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(3);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(4);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(5);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(6);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(7);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(8);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(9);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(10);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(11);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(12);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(13);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(14);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(15);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(16);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(17);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(18);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(19);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(20);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(21);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(22);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(23);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(24);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(25);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(26);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(27);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(28);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(29);			\
	PMEVTYPER_##पढ़ोग_लिखो##_CASE(30)

/*
 * Read a value direct from PMEVTYPER<idx> where idx is 0-30
 * or PMCCFILTR_EL0 where idx is ARMV8_PMU_CYCLE_IDX (31).
 */
अटल u64 kvm_vcpu_pmu_पढ़ो_evtype_direct(पूर्णांक idx)
अणु
	चयन (idx) अणु
	PMEVTYPER_CASES(READ);
	हाल ARMV8_PMU_CYCLE_IDX:
		वापस पढ़ो_sysreg(pmccfiltr_el0);
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write a value direct to PMEVTYPER<idx> where idx is 0-30
 * or PMCCFILTR_EL0 where idx is ARMV8_PMU_CYCLE_IDX (31).
 */
अटल व्योम kvm_vcpu_pmu_ग_लिखो_evtype_direct(पूर्णांक idx, u32 val)
अणु
	चयन (idx) अणु
	PMEVTYPER_CASES(WRITE);
	हाल ARMV8_PMU_CYCLE_IDX:
		ग_लिखो_sysreg(val, pmccfiltr_el0);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * Modअगरy ARMv8 PMU events to include EL0 counting
 */
अटल व्योम kvm_vcpu_pmu_enable_el0(अचिन्हित दीर्घ events)
अणु
	u64 typer;
	u32 counter;

	क्रम_each_set_bit(counter, &events, 32) अणु
		typer = kvm_vcpu_pmu_पढ़ो_evtype_direct(counter);
		typer &= ~ARMV8_PMU_EXCLUDE_EL0;
		kvm_vcpu_pmu_ग_लिखो_evtype_direct(counter, typer);
	पूर्ण
पूर्ण

/*
 * Modअगरy ARMv8 PMU events to exclude EL0 counting
 */
अटल व्योम kvm_vcpu_pmu_disable_el0(अचिन्हित दीर्घ events)
अणु
	u64 typer;
	u32 counter;

	क्रम_each_set_bit(counter, &events, 32) अणु
		typer = kvm_vcpu_pmu_पढ़ो_evtype_direct(counter);
		typer |= ARMV8_PMU_EXCLUDE_EL0;
		kvm_vcpu_pmu_ग_लिखो_evtype_direct(counter, typer);
	पूर्ण
पूर्ण

/*
 * On VHE ensure that only guest events have EL0 counting enabled.
 * This is called from both vcpu_अणुload,putपूर्ण and the sysreg handling.
 * Since the latter is preemptible, special care must be taken to
 * disable preemption.
 */
व्योम kvm_vcpu_pmu_restore_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_host_data *host;
	u32 events_guest, events_host;

	अगर (!kvm_arm_support_pmu_v3() || !has_vhe())
		वापस;

	preempt_disable();
	host = this_cpu_ptr_hyp_sym(kvm_host_data);
	events_guest = host->pmu_events.events_guest;
	events_host = host->pmu_events.events_host;

	kvm_vcpu_pmu_enable_el0(events_guest);
	kvm_vcpu_pmu_disable_el0(events_host);
	preempt_enable();
पूर्ण

/*
 * On VHE ensure that only host events have EL0 counting enabled
 */
व्योम kvm_vcpu_pmu_restore_host(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_host_data *host;
	u32 events_guest, events_host;

	अगर (!kvm_arm_support_pmu_v3() || !has_vhe())
		वापस;

	host = this_cpu_ptr_hyp_sym(kvm_host_data);
	events_guest = host->pmu_events.events_guest;
	events_host = host->pmu_events.events_host;

	kvm_vcpu_pmu_enable_el0(events_host);
	kvm_vcpu_pmu_disable_el0(events_guest);
पूर्ण
