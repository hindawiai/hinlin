<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARMv6 Perक्रमmance counter handling code.
 *
 * Copyright (C) 2009 picoChip Designs, Ltd., Jamie Iles
 *
 * ARMv6 has 2 configurable perक्रमmance counters and a single cycle counter.
 * They all share a single reset bit but can be written to zero so we can use
 * that क्रम a reset.
 *
 * The counters can't be inभागidually enabled or disabled so when we हटाओ
 * one event and replace it with another we could get spurious counts from the
 * wrong event. However, we can take advantage of the fact that the
 * perक्रमmance counters can export events to the event bus, and the event bus
 * itself can be monitored. This requires that we *करोn't* export the events to
 * the event bus. The procedure क्रम disabling a configurable counter is:
 *	- change the counter to count the ETMEXTOUT[0] संकेत (0x20). This
 *	  effectively stops the counter from counting.
 *	- disable the counter's interrupt generation (each counter has it's
 *	  own पूर्णांकerrupt enable bit).
 * Once stopped, the counter value can be written as 0 to reset.
 *
 * To enable a counter:
 *	- enable the counter's पूर्णांकerrupt generation.
 *	- set the new event type.
 *
 * Note: the dedicated cycle counter only counts cycles and can't be
 * enabled/disabled independently of the others. When we want to disable the
 * cycle counter, we have to just disable the पूर्णांकerrupt reporting and start
 * ignoring that counter. When re-enabling, we have to reset the value and
 * enable the पूर्णांकerrupt.
 */

#अगर defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K)

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/irq_regs.h>

#समावेश <linux/of.h>
#समावेश <linux/perf/arm_pmu.h>
#समावेश <linux/platक्रमm_device.h>

क्रमागत armv6_perf_types अणु
	ARMV6_PERFCTR_ICACHE_MISS	    = 0x0,
	ARMV6_PERFCTR_IBUF_STALL	    = 0x1,
	ARMV6_PERFCTR_DDEP_STALL	    = 0x2,
	ARMV6_PERFCTR_ITLB_MISS		    = 0x3,
	ARMV6_PERFCTR_DTLB_MISS		    = 0x4,
	ARMV6_PERFCTR_BR_EXEC		    = 0x5,
	ARMV6_PERFCTR_BR_MISPREDICT	    = 0x6,
	ARMV6_PERFCTR_INSTR_EXEC	    = 0x7,
	ARMV6_PERFCTR_DCACHE_HIT	    = 0x9,
	ARMV6_PERFCTR_DCACHE_ACCESS	    = 0xA,
	ARMV6_PERFCTR_DCACHE_MISS	    = 0xB,
	ARMV6_PERFCTR_DCACHE_WBACK	    = 0xC,
	ARMV6_PERFCTR_SW_PC_CHANGE	    = 0xD,
	ARMV6_PERFCTR_MAIN_TLB_MISS	    = 0xF,
	ARMV6_PERFCTR_EXPL_D_ACCESS	    = 0x10,
	ARMV6_PERFCTR_LSU_FULL_STALL	    = 0x11,
	ARMV6_PERFCTR_WBUF_DRAINED	    = 0x12,
	ARMV6_PERFCTR_CPU_CYCLES	    = 0xFF,
	ARMV6_PERFCTR_NOP		    = 0x20,
पूर्ण;

क्रमागत armv6_counters अणु
	ARMV6_CYCLE_COUNTER = 0,
	ARMV6_COUNTER0,
	ARMV6_COUNTER1,
पूर्ण;

/*
 * The hardware events that we support. We करो support cache operations but
 * we have harvard caches and no way to combine inकाष्ठाion and data
 * accesses/misses in hardware.
 */
अटल स्थिर अचिन्हित armv6_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV6_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV6_PERFCTR_INSTR_EXEC,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV6_PERFCTR_BR_EXEC,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV6_PERFCTR_BR_MISPREDICT,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= ARMV6_PERFCTR_IBUF_STALL,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND]	= ARMV6_PERFCTR_LSU_FULL_STALL,
पूर्ण;

अटल स्थिर अचिन्हित armv6_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					  [PERF_COUNT_HW_CACHE_OP_MAX]
					  [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	/*
	 * The perक्रमmance counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses so this isn't strictly correct, but it's the best we
	 * can करो. Writes and पढ़ोs get combined.
	 */
	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV6_PERFCTR_DCACHE_ACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV6_PERFCTR_DCACHE_MISS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV6_PERFCTR_DCACHE_ACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV6_PERFCTR_DCACHE_MISS,

	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV6_PERFCTR_ICACHE_MISS,

	/*
	 * The ARM perक्रमmance counters can count micro DTLB misses, micro ITLB
	 * misses and मुख्य TLB misses. There isn't an event क्रम TLB misses, so
	 * use the micro misses here and अगर users want the मुख्य TLB misses they
	 * can use a raw counter.
	 */
	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV6_PERFCTR_DTLB_MISS,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV6_PERFCTR_DTLB_MISS,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV6_PERFCTR_ITLB_MISS,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV6_PERFCTR_ITLB_MISS,
पूर्ण;

क्रमागत armv6mpcore_perf_types अणु
	ARMV6MPCORE_PERFCTR_ICACHE_MISS	    = 0x0,
	ARMV6MPCORE_PERFCTR_IBUF_STALL	    = 0x1,
	ARMV6MPCORE_PERFCTR_DDEP_STALL	    = 0x2,
	ARMV6MPCORE_PERFCTR_ITLB_MISS	    = 0x3,
	ARMV6MPCORE_PERFCTR_DTLB_MISS	    = 0x4,
	ARMV6MPCORE_PERFCTR_BR_EXEC	    = 0x5,
	ARMV6MPCORE_PERFCTR_BR_NOTPREDICT   = 0x6,
	ARMV6MPCORE_PERFCTR_BR_MISPREDICT   = 0x7,
	ARMV6MPCORE_PERFCTR_INSTR_EXEC	    = 0x8,
	ARMV6MPCORE_PERFCTR_DCACHE_RDACCESS = 0xA,
	ARMV6MPCORE_PERFCTR_DCACHE_RDMISS   = 0xB,
	ARMV6MPCORE_PERFCTR_DCACHE_WRACCESS = 0xC,
	ARMV6MPCORE_PERFCTR_DCACHE_WRMISS   = 0xD,
	ARMV6MPCORE_PERFCTR_DCACHE_EVICTION = 0xE,
	ARMV6MPCORE_PERFCTR_SW_PC_CHANGE    = 0xF,
	ARMV6MPCORE_PERFCTR_MAIN_TLB_MISS   = 0x10,
	ARMV6MPCORE_PERFCTR_EXPL_MEM_ACCESS = 0x11,
	ARMV6MPCORE_PERFCTR_LSU_FULL_STALL  = 0x12,
	ARMV6MPCORE_PERFCTR_WBUF_DRAINED    = 0x13,
	ARMV6MPCORE_PERFCTR_CPU_CYCLES	    = 0xFF,
पूर्ण;

/*
 * The hardware events that we support. We करो support cache operations but
 * we have harvard caches and no way to combine inकाष्ठाion and data
 * accesses/misses in hardware.
 */
अटल स्थिर अचिन्हित armv6mpcore_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV6MPCORE_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV6MPCORE_PERFCTR_INSTR_EXEC,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV6MPCORE_PERFCTR_BR_EXEC,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV6MPCORE_PERFCTR_BR_MISPREDICT,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= ARMV6MPCORE_PERFCTR_IBUF_STALL,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND]	= ARMV6MPCORE_PERFCTR_LSU_FULL_STALL,
पूर्ण;

अटल स्थिर अचिन्हित armv6mpcore_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					[PERF_COUNT_HW_CACHE_OP_MAX]
					[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV6MPCORE_PERFCTR_DCACHE_RDACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV6MPCORE_PERFCTR_DCACHE_RDMISS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV6MPCORE_PERFCTR_DCACHE_WRACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV6MPCORE_PERFCTR_DCACHE_WRMISS,

	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV6MPCORE_PERFCTR_ICACHE_MISS,

	/*
	 * The ARM perक्रमmance counters can count micro DTLB misses, micro ITLB
	 * misses and मुख्य TLB misses. There isn't an event क्रम TLB misses, so
	 * use the micro misses here and अगर users want the मुख्य TLB misses they
	 * can use a raw counter.
	 */
	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV6MPCORE_PERFCTR_DTLB_MISS,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV6MPCORE_PERFCTR_DTLB_MISS,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV6MPCORE_PERFCTR_ITLB_MISS,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV6MPCORE_PERFCTR_ITLB_MISS,
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ
armv6_pmcr_पढ़ो(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc   p15, 0, %0, c15, c12, 0" : "=r"(val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम
armv6_pmcr_ग_लिखो(अचिन्हित दीर्घ val)
अणु
	यंत्र अस्थिर("mcr   p15, 0, %0, c15, c12, 0" : : "r"(val));
पूर्ण

#घोषणा ARMV6_PMCR_ENABLE		(1 << 0)
#घोषणा ARMV6_PMCR_CTR01_RESET		(1 << 1)
#घोषणा ARMV6_PMCR_CCOUNT_RESET		(1 << 2)
#घोषणा ARMV6_PMCR_CCOUNT_DIV		(1 << 3)
#घोषणा ARMV6_PMCR_COUNT0_IEN		(1 << 4)
#घोषणा ARMV6_PMCR_COUNT1_IEN		(1 << 5)
#घोषणा ARMV6_PMCR_CCOUNT_IEN		(1 << 6)
#घोषणा ARMV6_PMCR_COUNT0_OVERFLOW	(1 << 8)
#घोषणा ARMV6_PMCR_COUNT1_OVERFLOW	(1 << 9)
#घोषणा ARMV6_PMCR_CCOUNT_OVERFLOW	(1 << 10)
#घोषणा ARMV6_PMCR_EVT_COUNT0_SHIFT	20
#घोषणा ARMV6_PMCR_EVT_COUNT0_MASK	(0xFF << ARMV6_PMCR_EVT_COUNT0_SHIFT)
#घोषणा ARMV6_PMCR_EVT_COUNT1_SHIFT	12
#घोषणा ARMV6_PMCR_EVT_COUNT1_MASK	(0xFF << ARMV6_PMCR_EVT_COUNT1_SHIFT)

#घोषणा ARMV6_PMCR_OVERFLOWED_MASK \
	(ARMV6_PMCR_COUNT0_OVERFLOW | ARMV6_PMCR_COUNT1_OVERFLOW | \
	 ARMV6_PMCR_CCOUNT_OVERFLOW)

अटल अंतरभूत पूर्णांक
armv6_pmcr_has_overflowed(अचिन्हित दीर्घ pmcr)
अणु
	वापस pmcr & ARMV6_PMCR_OVERFLOWED_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक
armv6_pmcr_counter_has_overflowed(अचिन्हित दीर्घ pmcr,
				  क्रमागत armv6_counters counter)
अणु
	पूर्णांक ret = 0;

	अगर (ARMV6_CYCLE_COUNTER == counter)
		ret = pmcr & ARMV6_PMCR_CCOUNT_OVERFLOW;
	अन्यथा अगर (ARMV6_COUNTER0 == counter)
		ret = pmcr & ARMV6_PMCR_COUNT0_OVERFLOW;
	अन्यथा अगर (ARMV6_COUNTER1 == counter)
		ret = pmcr & ARMV6_PMCR_COUNT1_OVERFLOW;
	अन्यथा
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);

	वापस ret;
पूर्ण

अटल अंतरभूत u64 armv6pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;
	अचिन्हित दीर्घ value = 0;

	अगर (ARMV6_CYCLE_COUNTER == counter)
		यंत्र अस्थिर("mrc   p15, 0, %0, c15, c12, 1" : "=r"(value));
	अन्यथा अगर (ARMV6_COUNTER0 == counter)
		यंत्र अस्थिर("mrc   p15, 0, %0, c15, c12, 2" : "=r"(value));
	अन्यथा अगर (ARMV6_COUNTER1 == counter)
		यंत्र अस्थिर("mrc   p15, 0, %0, c15, c12, 3" : "=r"(value));
	अन्यथा
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);

	वापस value;
पूर्ण

अटल अंतरभूत व्योम armv6pmu_ग_लिखो_counter(काष्ठा perf_event *event, u64 value)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;

	अगर (ARMV6_CYCLE_COUNTER == counter)
		यंत्र अस्थिर("mcr   p15, 0, %0, c15, c12, 1" : : "r"(value));
	अन्यथा अगर (ARMV6_COUNTER0 == counter)
		यंत्र अस्थिर("mcr   p15, 0, %0, c15, c12, 2" : : "r"(value));
	अन्यथा अगर (ARMV6_COUNTER1 == counter)
		यंत्र अस्थिर("mcr   p15, 0, %0, c15, c12, 3" : : "r"(value));
	अन्यथा
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);
पूर्ण

अटल व्योम armv6pmu_enable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ val, mask, evt, flags;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	अगर (ARMV6_CYCLE_COUNTER == idx) अणु
		mask	= 0;
		evt	= ARMV6_PMCR_CCOUNT_IEN;
	पूर्ण अन्यथा अगर (ARMV6_COUNTER0 == idx) अणु
		mask	= ARMV6_PMCR_EVT_COUNT0_MASK;
		evt	= (hwc->config_base << ARMV6_PMCR_EVT_COUNT0_SHIFT) |
			  ARMV6_PMCR_COUNT0_IEN;
	पूर्ण अन्यथा अगर (ARMV6_COUNTER1 == idx) अणु
		mask	= ARMV6_PMCR_EVT_COUNT1_MASK;
		evt	= (hwc->config_base << ARMV6_PMCR_EVT_COUNT1_SHIFT) |
			  ARMV6_PMCR_COUNT1_IEN;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		वापस;
	पूर्ण

	/*
	 * Mask out the current event and set the counter to count the event
	 * that we're पूर्णांकerested in.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = armv6_pmcr_पढ़ो();
	val &= ~mask;
	val |= evt;
	armv6_pmcr_ग_लिखो(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल irqवापस_t
armv6pmu_handle_irq(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ pmcr = armv6_pmcr_पढ़ो();
	काष्ठा perf_sample_data data;
	काष्ठा pmu_hw_events *cpuc = this_cpu_ptr(cpu_pmu->hw_events);
	काष्ठा pt_regs *regs;
	पूर्णांक idx;

	अगर (!armv6_pmcr_has_overflowed(pmcr))
		वापस IRQ_NONE;

	regs = get_irq_regs();

	/*
	 * The पूर्णांकerrupts are cleared by writing the overflow flags back to
	 * the control रेजिस्टर. All of the other bits करोn't have any effect
	 * अगर they are rewritten, so ग_लिखो the whole value back.
	 */
	armv6_pmcr_ग_लिखो(pmcr);

	क्रम (idx = 0; idx < cpu_pmu->num_events; ++idx) अणु
		काष्ठा perf_event *event = cpuc->events[idx];
		काष्ठा hw_perf_event *hwc;

		/* Ignore अगर we करोn't have an event. */
		अगर (!event)
			जारी;

		/*
		 * We have a single पूर्णांकerrupt क्रम all counters. Check that
		 * each counter has overflowed beक्रमe we process it.
		 */
		अगर (!armv6_pmcr_counter_has_overflowed(pmcr, idx))
			जारी;

		hwc = &event->hw;
		armpmu_event_update(event);
		perf_sample_data_init(&data, 0, hwc->last_period);
		अगर (!armpmu_event_set_period(event))
			जारी;

		अगर (perf_event_overflow(event, &data, regs))
			cpu_pmu->disable(event);
	पूर्ण

	/*
	 * Handle the pending perf events.
	 *
	 * Note: this call *must* be run with पूर्णांकerrupts disabled. For
	 * platक्रमms that can have the PMU पूर्णांकerrupts उठाओd as an NMI, this
	 * will not work.
	 */
	irq_work_run();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम armv6pmu_start(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags, val;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = armv6_pmcr_पढ़ो();
	val |= ARMV6_PMCR_ENABLE;
	armv6_pmcr_ग_लिखो(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम armv6pmu_stop(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags, val;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = armv6_pmcr_पढ़ो();
	val &= ~ARMV6_PMCR_ENABLE;
	armv6_pmcr_ग_लिखो(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल पूर्णांक
armv6pmu_get_event_idx(काष्ठा pmu_hw_events *cpuc,
				काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	/* Always place a cycle counter पूर्णांकo the cycle counter. */
	अगर (ARMV6_PERFCTR_CPU_CYCLES == hwc->config_base) अणु
		अगर (test_and_set_bit(ARMV6_CYCLE_COUNTER, cpuc->used_mask))
			वापस -EAGAIN;

		वापस ARMV6_CYCLE_COUNTER;
	पूर्ण अन्यथा अणु
		/*
		 * For anything other than a cycle counter, try and use
		 * counter0 and counter1.
		 */
		अगर (!test_and_set_bit(ARMV6_COUNTER1, cpuc->used_mask))
			वापस ARMV6_COUNTER1;

		अगर (!test_and_set_bit(ARMV6_COUNTER0, cpuc->used_mask))
			वापस ARMV6_COUNTER0;

		/* The counters are all in use. */
		वापस -EAGAIN;
	पूर्ण
पूर्ण

अटल व्योम armv6pmu_clear_event_idx(काष्ठा pmu_hw_events *cpuc,
				     काष्ठा perf_event *event)
अणु
	clear_bit(event->hw.idx, cpuc->used_mask);
पूर्ण

अटल व्योम armv6pmu_disable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ val, mask, evt, flags;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	अगर (ARMV6_CYCLE_COUNTER == idx) अणु
		mask	= ARMV6_PMCR_CCOUNT_IEN;
		evt	= 0;
	पूर्ण अन्यथा अगर (ARMV6_COUNTER0 == idx) अणु
		mask	= ARMV6_PMCR_COUNT0_IEN | ARMV6_PMCR_EVT_COUNT0_MASK;
		evt	= ARMV6_PERFCTR_NOP << ARMV6_PMCR_EVT_COUNT0_SHIFT;
	पूर्ण अन्यथा अगर (ARMV6_COUNTER1 == idx) अणु
		mask	= ARMV6_PMCR_COUNT1_IEN | ARMV6_PMCR_EVT_COUNT1_MASK;
		evt	= ARMV6_PERFCTR_NOP << ARMV6_PMCR_EVT_COUNT1_SHIFT;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		वापस;
	पूर्ण

	/*
	 * Mask out the current event and set the counter to count the number
	 * of ETM bus संकेत निश्चितion cycles. The बाह्यal reporting should
	 * be disabled and so this should never increment.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = armv6_pmcr_पढ़ो();
	val &= ~mask;
	val |= evt;
	armv6_pmcr_ग_लिखो(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम armv6mpcore_pmu_disable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ val, mask, flags, evt = 0;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	अगर (ARMV6_CYCLE_COUNTER == idx) अणु
		mask	= ARMV6_PMCR_CCOUNT_IEN;
	पूर्ण अन्यथा अगर (ARMV6_COUNTER0 == idx) अणु
		mask	= ARMV6_PMCR_COUNT0_IEN;
	पूर्ण अन्यथा अगर (ARMV6_COUNTER1 == idx) अणु
		mask	= ARMV6_PMCR_COUNT1_IEN;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		वापस;
	पूर्ण

	/*
	 * Unlike UP ARMv6, we करोn't have a way of stopping the counters. We
	 * simply disable the पूर्णांकerrupt reporting.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = armv6_pmcr_पढ़ो();
	val &= ~mask;
	val |= evt;
	armv6_pmcr_ग_लिखो(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल पूर्णांक armv6_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &armv6_perf_map,
				&armv6_perf_cache_map, 0xFF);
पूर्ण

अटल व्योम armv6pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	cpu_pmu->handle_irq	= armv6pmu_handle_irq;
	cpu_pmu->enable		= armv6pmu_enable_event;
	cpu_pmu->disable	= armv6pmu_disable_event;
	cpu_pmu->पढ़ो_counter	= armv6pmu_पढ़ो_counter;
	cpu_pmu->ग_लिखो_counter	= armv6pmu_ग_लिखो_counter;
	cpu_pmu->get_event_idx	= armv6pmu_get_event_idx;
	cpu_pmu->clear_event_idx = armv6pmu_clear_event_idx;
	cpu_pmu->start		= armv6pmu_start;
	cpu_pmu->stop		= armv6pmu_stop;
	cpu_pmu->map_event	= armv6_map_event;
	cpu_pmu->num_events	= 3;
पूर्ण

अटल पूर्णांक armv6_1136_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv6pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv6_1136";
	वापस 0;
पूर्ण

अटल पूर्णांक armv6_1156_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv6pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv6_1156";
	वापस 0;
पूर्ण

अटल पूर्णांक armv6_1176_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv6pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv6_1176";
	वापस 0;
पूर्ण

/*
 * ARMv6mpcore is almost identical to single core ARMv6 with the exception
 * that some of the events have dअगरferent क्रमागतerations and that there is no
 * *hack* to stop the programmable counters. To stop the counters we simply
 * disable the पूर्णांकerrupt reporting and update the event. When unthrottling we
 * reset the period and enable the पूर्णांकerrupt reporting.
 */

अटल पूर्णांक armv6mpcore_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &armv6mpcore_perf_map,
				&armv6mpcore_perf_cache_map, 0xFF);
पूर्ण

अटल पूर्णांक armv6mpcore_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	cpu_pmu->name		= "armv6_11mpcore";
	cpu_pmu->handle_irq	= armv6pmu_handle_irq;
	cpu_pmu->enable		= armv6pmu_enable_event;
	cpu_pmu->disable	= armv6mpcore_pmu_disable_event;
	cpu_pmu->पढ़ो_counter	= armv6pmu_पढ़ो_counter;
	cpu_pmu->ग_लिखो_counter	= armv6pmu_ग_लिखो_counter;
	cpu_pmu->get_event_idx	= armv6pmu_get_event_idx;
	cpu_pmu->clear_event_idx = armv6pmu_clear_event_idx;
	cpu_pmu->start		= armv6pmu_start;
	cpu_pmu->stop		= armv6pmu_stop;
	cpu_pmu->map_event	= armv6mpcore_map_event;
	cpu_pmu->num_events	= 3;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id armv6_pmu_of_device_ids[] = अणु
	अणु.compatible = "arm,arm11mpcore-pmu",	.data = armv6mpcore_pmu_initपूर्ण,
	अणु.compatible = "arm,arm1176-pmu",	.data = armv6_1176_pmu_initपूर्ण,
	अणु.compatible = "arm,arm1136-pmu",	.data = armv6_1136_pmu_initपूर्ण,
	अणु /* sentinel value */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmu_probe_info armv6_pmu_probe_table[] = अणु
	ARM_PMU_PROBE(ARM_CPU_PART_ARM1136, armv6_1136_pmu_init),
	ARM_PMU_PROBE(ARM_CPU_PART_ARM1156, armv6_1156_pmu_init),
	ARM_PMU_PROBE(ARM_CPU_PART_ARM1176, armv6_1176_pmu_init),
	ARM_PMU_PROBE(ARM_CPU_PART_ARM11MPCORE, armv6mpcore_pmu_init),
	अणु /* sentinel value */ पूर्ण
पूर्ण;

अटल पूर्णांक armv6_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस arm_pmu_device_probe(pdev, armv6_pmu_of_device_ids,
				    armv6_pmu_probe_table);
पूर्ण

अटल काष्ठा platक्रमm_driver armv6_pmu_driver = अणु
	.driver		= अणु
		.name	= "armv6-pmu",
		.of_match_table = armv6_pmu_of_device_ids,
	पूर्ण,
	.probe		= armv6_pmu_device_probe,
पूर्ण;

builtin_platक्रमm_driver(armv6_pmu_driver);
#पूर्ण_अगर	/* CONFIG_CPU_V6 || CONFIG_CPU_V6K */
