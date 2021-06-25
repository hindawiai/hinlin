<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARMv5 [xscale] Perक्रमmance counter handling code.
 *
 * Copyright (C) 2010, ARM Ltd., Will Deacon <will.deacon@arm.com>
 *
 * Based on the previous xscale OProfile code.
 *
 * There are two variants of the xscale PMU that we support:
 * 	- xscale1pmu: 2 event counters and a cycle counter
 * 	- xscale2pmu: 4 event counters and a cycle counter
 * The two variants share event definitions, but have dअगरferent
 * PMU काष्ठाures.
 */

#अगर_घोषित CONFIG_CPU_XSCALE

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/irq_regs.h>

#समावेश <linux/of.h>
#समावेश <linux/perf/arm_pmu.h>
#समावेश <linux/platक्रमm_device.h>

क्रमागत xscale_perf_types अणु
	XSCALE_PERFCTR_ICACHE_MISS		= 0x00,
	XSCALE_PERFCTR_ICACHE_NO_DELIVER	= 0x01,
	XSCALE_PERFCTR_DATA_STALL		= 0x02,
	XSCALE_PERFCTR_ITLB_MISS		= 0x03,
	XSCALE_PERFCTR_DTLB_MISS		= 0x04,
	XSCALE_PERFCTR_BRANCH			= 0x05,
	XSCALE_PERFCTR_BRANCH_MISS		= 0x06,
	XSCALE_PERFCTR_INSTRUCTION		= 0x07,
	XSCALE_PERFCTR_DCACHE_FULL_STALL	= 0x08,
	XSCALE_PERFCTR_DCACHE_FULL_STALL_CONTIG	= 0x09,
	XSCALE_PERFCTR_DCACHE_ACCESS		= 0x0A,
	XSCALE_PERFCTR_DCACHE_MISS		= 0x0B,
	XSCALE_PERFCTR_DCACHE_WRITE_BACK	= 0x0C,
	XSCALE_PERFCTR_PC_CHANGED		= 0x0D,
	XSCALE_PERFCTR_BCU_REQUEST		= 0x10,
	XSCALE_PERFCTR_BCU_FULL			= 0x11,
	XSCALE_PERFCTR_BCU_DRAIN		= 0x12,
	XSCALE_PERFCTR_BCU_ECC_NO_ELOG		= 0x14,
	XSCALE_PERFCTR_BCU_1_BIT_ERR		= 0x15,
	XSCALE_PERFCTR_RMW			= 0x16,
	/* XSCALE_PERFCTR_CCNT is not hardware defined */
	XSCALE_PERFCTR_CCNT			= 0xFE,
	XSCALE_PERFCTR_UNUSED			= 0xFF,
पूर्ण;

क्रमागत xscale_counters अणु
	XSCALE_CYCLE_COUNTER	= 0,
	XSCALE_COUNTER0,
	XSCALE_COUNTER1,
	XSCALE_COUNTER2,
	XSCALE_COUNTER3,
पूर्ण;

अटल स्थिर अचिन्हित xscale_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= XSCALE_PERFCTR_CCNT,
	[PERF_COUNT_HW_INSTRUCTIONS]		= XSCALE_PERFCTR_INSTRUCTION,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= XSCALE_PERFCTR_BRANCH,
	[PERF_COUNT_HW_BRANCH_MISSES]		= XSCALE_PERFCTR_BRANCH_MISS,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= XSCALE_PERFCTR_ICACHE_NO_DELIVER,
पूर्ण;

अटल स्थिर अचिन्हित xscale_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					   [PERF_COUNT_HW_CACHE_OP_MAX]
					   [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= XSCALE_PERFCTR_DCACHE_ACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= XSCALE_PERFCTR_DCACHE_MISS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= XSCALE_PERFCTR_DCACHE_ACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= XSCALE_PERFCTR_DCACHE_MISS,

	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= XSCALE_PERFCTR_ICACHE_MISS,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= XSCALE_PERFCTR_DTLB_MISS,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= XSCALE_PERFCTR_DTLB_MISS,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= XSCALE_PERFCTR_ITLB_MISS,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= XSCALE_PERFCTR_ITLB_MISS,
पूर्ण;

#घोषणा	XSCALE_PMU_ENABLE	0x001
#घोषणा XSCALE_PMN_RESET	0x002
#घोषणा	XSCALE_CCNT_RESET	0x004
#घोषणा	XSCALE_PMU_RESET	(CCNT_RESET | PMN_RESET)
#घोषणा XSCALE_PMU_CNT64	0x008

#घोषणा XSCALE1_OVERFLOWED_MASK	0x700
#घोषणा XSCALE1_CCOUNT_OVERFLOW	0x400
#घोषणा XSCALE1_COUNT0_OVERFLOW	0x100
#घोषणा XSCALE1_COUNT1_OVERFLOW	0x200
#घोषणा XSCALE1_CCOUNT_INT_EN	0x040
#घोषणा XSCALE1_COUNT0_INT_EN	0x010
#घोषणा XSCALE1_COUNT1_INT_EN	0x020
#घोषणा XSCALE1_COUNT0_EVT_SHFT	12
#घोषणा XSCALE1_COUNT0_EVT_MASK	(0xff << XSCALE1_COUNT0_EVT_SHFT)
#घोषणा XSCALE1_COUNT1_EVT_SHFT	20
#घोषणा XSCALE1_COUNT1_EVT_MASK	(0xff << XSCALE1_COUNT1_EVT_SHFT)

अटल अंतरभूत u32
xscale1pmu_पढ़ो_pmnc(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p14, 0, %0, c0, c0, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम
xscale1pmu_ग_लिखो_pmnc(u32 val)
अणु
	/* upper 4bits and 7, 11 are ग_लिखो-as-0 */
	val &= 0xffff77f;
	यंत्र अस्थिर("mcr p14, 0, %0, c0, c0, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत पूर्णांक
xscale1_pmnc_counter_has_overflowed(अचिन्हित दीर्घ pmnc,
					क्रमागत xscale_counters counter)
अणु
	पूर्णांक ret = 0;

	चयन (counter) अणु
	हाल XSCALE_CYCLE_COUNTER:
		ret = pmnc & XSCALE1_CCOUNT_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER0:
		ret = pmnc & XSCALE1_COUNT0_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER1:
		ret = pmnc & XSCALE1_COUNT1_OVERFLOW;
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t
xscale1pmu_handle_irq(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ pmnc;
	काष्ठा perf_sample_data data;
	काष्ठा pmu_hw_events *cpuc = this_cpu_ptr(cpu_pmu->hw_events);
	काष्ठा pt_regs *regs;
	पूर्णांक idx;

	/*
	 * NOTE: there's an A stepping erratum that states अगर an overflow
	 *       bit alपढ़ोy exists and another occurs, the previous
	 *       Overflow bit माला_लो cleared. There's no workaround.
	 *	 Fixed in B stepping or later.
	 */
	pmnc = xscale1pmu_पढ़ो_pmnc();

	/*
	 * Write the value back to clear the overflow flags. Overflow
	 * flags reमुख्य in pmnc क्रम use below. We also disable the PMU
	 * जबतक we process the पूर्णांकerrupt.
	 */
	xscale1pmu_ग_लिखो_pmnc(pmnc & ~XSCALE_PMU_ENABLE);

	अगर (!(pmnc & XSCALE1_OVERFLOWED_MASK))
		वापस IRQ_NONE;

	regs = get_irq_regs();

	क्रम (idx = 0; idx < cpu_pmu->num_events; ++idx) अणु
		काष्ठा perf_event *event = cpuc->events[idx];
		काष्ठा hw_perf_event *hwc;

		अगर (!event)
			जारी;

		अगर (!xscale1_pmnc_counter_has_overflowed(pmnc, idx))
			जारी;

		hwc = &event->hw;
		armpmu_event_update(event);
		perf_sample_data_init(&data, 0, hwc->last_period);
		अगर (!armpmu_event_set_period(event))
			जारी;

		अगर (perf_event_overflow(event, &data, regs))
			cpu_pmu->disable(event);
	पूर्ण

	irq_work_run();

	/*
	 * Re-enable the PMU.
	 */
	pmnc = xscale1pmu_पढ़ो_pmnc() | XSCALE_PMU_ENABLE;
	xscale1pmu_ग_लिखो_pmnc(pmnc);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xscale1pmu_enable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ val, mask, evt, flags;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	चयन (idx) अणु
	हाल XSCALE_CYCLE_COUNTER:
		mask = 0;
		evt = XSCALE1_CCOUNT_INT_EN;
		अवरोध;
	हाल XSCALE_COUNTER0:
		mask = XSCALE1_COUNT0_EVT_MASK;
		evt = (hwc->config_base << XSCALE1_COUNT0_EVT_SHFT) |
			XSCALE1_COUNT0_INT_EN;
		अवरोध;
	हाल XSCALE_COUNTER1:
		mask = XSCALE1_COUNT1_EVT_MASK;
		evt = (hwc->config_base << XSCALE1_COUNT1_EVT_SHFT) |
			XSCALE1_COUNT1_INT_EN;
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = xscale1pmu_पढ़ो_pmnc();
	val &= ~mask;
	val |= evt;
	xscale1pmu_ग_लिखो_pmnc(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम xscale1pmu_disable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ val, mask, evt, flags;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	चयन (idx) अणु
	हाल XSCALE_CYCLE_COUNTER:
		mask = XSCALE1_CCOUNT_INT_EN;
		evt = 0;
		अवरोध;
	हाल XSCALE_COUNTER0:
		mask = XSCALE1_COUNT0_INT_EN | XSCALE1_COUNT0_EVT_MASK;
		evt = XSCALE_PERFCTR_UNUSED << XSCALE1_COUNT0_EVT_SHFT;
		अवरोध;
	हाल XSCALE_COUNTER1:
		mask = XSCALE1_COUNT1_INT_EN | XSCALE1_COUNT1_EVT_MASK;
		evt = XSCALE_PERFCTR_UNUSED << XSCALE1_COUNT1_EVT_SHFT;
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = xscale1pmu_पढ़ो_pmnc();
	val &= ~mask;
	val |= evt;
	xscale1pmu_ग_लिखो_pmnc(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल पूर्णांक
xscale1pmu_get_event_idx(काष्ठा pmu_hw_events *cpuc,
				काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	अगर (XSCALE_PERFCTR_CCNT == hwc->config_base) अणु
		अगर (test_and_set_bit(XSCALE_CYCLE_COUNTER, cpuc->used_mask))
			वापस -EAGAIN;

		वापस XSCALE_CYCLE_COUNTER;
	पूर्ण अन्यथा अणु
		अगर (!test_and_set_bit(XSCALE_COUNTER1, cpuc->used_mask))
			वापस XSCALE_COUNTER1;

		अगर (!test_and_set_bit(XSCALE_COUNTER0, cpuc->used_mask))
			वापस XSCALE_COUNTER0;

		वापस -EAGAIN;
	पूर्ण
पूर्ण

अटल व्योम xscalepmu_clear_event_idx(काष्ठा pmu_hw_events *cpuc,
				     काष्ठा perf_event *event)
अणु
	clear_bit(event->hw.idx, cpuc->used_mask);
पूर्ण

अटल व्योम xscale1pmu_start(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags, val;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = xscale1pmu_पढ़ो_pmnc();
	val |= XSCALE_PMU_ENABLE;
	xscale1pmu_ग_लिखो_pmnc(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम xscale1pmu_stop(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags, val;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = xscale1pmu_पढ़ो_pmnc();
	val &= ~XSCALE_PMU_ENABLE;
	xscale1pmu_ग_लिखो_pmnc(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल अंतरभूत u64 xscale1pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;
	u32 val = 0;

	चयन (counter) अणु
	हाल XSCALE_CYCLE_COUNTER:
		यंत्र अस्थिर("mrc p14, 0, %0, c1, c0, 0" : "=r" (val));
		अवरोध;
	हाल XSCALE_COUNTER0:
		यंत्र अस्थिर("mrc p14, 0, %0, c2, c0, 0" : "=r" (val));
		अवरोध;
	हाल XSCALE_COUNTER1:
		यंत्र अस्थिर("mrc p14, 0, %0, c3, c0, 0" : "=r" (val));
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल अंतरभूत व्योम xscale1pmu_ग_लिखो_counter(काष्ठा perf_event *event, u64 val)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;

	चयन (counter) अणु
	हाल XSCALE_CYCLE_COUNTER:
		यंत्र अस्थिर("mcr p14, 0, %0, c1, c0, 0" : : "r" (val));
		अवरोध;
	हाल XSCALE_COUNTER0:
		यंत्र अस्थिर("mcr p14, 0, %0, c2, c0, 0" : : "r" (val));
		अवरोध;
	हाल XSCALE_COUNTER1:
		यंत्र अस्थिर("mcr p14, 0, %0, c3, c0, 0" : : "r" (val));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xscale_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &xscale_perf_map,
				&xscale_perf_cache_map, 0xFF);
पूर्ण

अटल पूर्णांक xscale1pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	cpu_pmu->name		= "armv5_xscale1";
	cpu_pmu->handle_irq	= xscale1pmu_handle_irq;
	cpu_pmu->enable		= xscale1pmu_enable_event;
	cpu_pmu->disable	= xscale1pmu_disable_event;
	cpu_pmu->पढ़ो_counter	= xscale1pmu_पढ़ो_counter;
	cpu_pmu->ग_लिखो_counter	= xscale1pmu_ग_लिखो_counter;
	cpu_pmu->get_event_idx	= xscale1pmu_get_event_idx;
	cpu_pmu->clear_event_idx = xscalepmu_clear_event_idx;
	cpu_pmu->start		= xscale1pmu_start;
	cpu_pmu->stop		= xscale1pmu_stop;
	cpu_pmu->map_event	= xscale_map_event;
	cpu_pmu->num_events	= 3;

	वापस 0;
पूर्ण

#घोषणा XSCALE2_OVERFLOWED_MASK	0x01f
#घोषणा XSCALE2_CCOUNT_OVERFLOW	0x001
#घोषणा XSCALE2_COUNT0_OVERFLOW	0x002
#घोषणा XSCALE2_COUNT1_OVERFLOW	0x004
#घोषणा XSCALE2_COUNT2_OVERFLOW	0x008
#घोषणा XSCALE2_COUNT3_OVERFLOW	0x010
#घोषणा XSCALE2_CCOUNT_INT_EN	0x001
#घोषणा XSCALE2_COUNT0_INT_EN	0x002
#घोषणा XSCALE2_COUNT1_INT_EN	0x004
#घोषणा XSCALE2_COUNT2_INT_EN	0x008
#घोषणा XSCALE2_COUNT3_INT_EN	0x010
#घोषणा XSCALE2_COUNT0_EVT_SHFT	0
#घोषणा XSCALE2_COUNT0_EVT_MASK	(0xff << XSCALE2_COUNT0_EVT_SHFT)
#घोषणा XSCALE2_COUNT1_EVT_SHFT	8
#घोषणा XSCALE2_COUNT1_EVT_MASK	(0xff << XSCALE2_COUNT1_EVT_SHFT)
#घोषणा XSCALE2_COUNT2_EVT_SHFT	16
#घोषणा XSCALE2_COUNT2_EVT_MASK	(0xff << XSCALE2_COUNT2_EVT_SHFT)
#घोषणा XSCALE2_COUNT3_EVT_SHFT	24
#घोषणा XSCALE2_COUNT3_EVT_MASK	(0xff << XSCALE2_COUNT3_EVT_SHFT)

अटल अंतरभूत u32
xscale2pmu_पढ़ो_pmnc(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p14, 0, %0, c0, c1, 0" : "=r" (val));
	/* bits 1-2 and 4-23 are पढ़ो-unpredictable */
	वापस val & 0xff000009;
पूर्ण

अटल अंतरभूत व्योम
xscale2pmu_ग_लिखो_pmnc(u32 val)
अणु
	/* bits 4-23 are ग_लिखो-as-0, 24-31 are ग_लिखो ignored */
	val &= 0xf;
	यंत्र अस्थिर("mcr p14, 0, %0, c0, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत u32
xscale2pmu_पढ़ो_overflow_flags(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p14, 0, %0, c5, c1, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम
xscale2pmu_ग_लिखो_overflow_flags(u32 val)
अणु
	यंत्र अस्थिर("mcr p14, 0, %0, c5, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत u32
xscale2pmu_पढ़ो_event_select(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p14, 0, %0, c8, c1, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम
xscale2pmu_ग_लिखो_event_select(u32 val)
अणु
	यंत्र अस्थिर("mcr p14, 0, %0, c8, c1, 0" : : "r"(val));
पूर्ण

अटल अंतरभूत u32
xscale2pmu_पढ़ो_पूर्णांक_enable(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p14, 0, %0, c4, c1, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल व्योम
xscale2pmu_ग_लिखो_पूर्णांक_enable(u32 val)
अणु
	यंत्र अस्थिर("mcr p14, 0, %0, c4, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत पूर्णांक
xscale2_pmnc_counter_has_overflowed(अचिन्हित दीर्घ of_flags,
					क्रमागत xscale_counters counter)
अणु
	पूर्णांक ret = 0;

	चयन (counter) अणु
	हाल XSCALE_CYCLE_COUNTER:
		ret = of_flags & XSCALE2_CCOUNT_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER0:
		ret = of_flags & XSCALE2_COUNT0_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER1:
		ret = of_flags & XSCALE2_COUNT1_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER2:
		ret = of_flags & XSCALE2_COUNT2_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER3:
		ret = of_flags & XSCALE2_COUNT3_OVERFLOW;
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t
xscale2pmu_handle_irq(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ pmnc, of_flags;
	काष्ठा perf_sample_data data;
	काष्ठा pmu_hw_events *cpuc = this_cpu_ptr(cpu_pmu->hw_events);
	काष्ठा pt_regs *regs;
	पूर्णांक idx;

	/* Disable the PMU. */
	pmnc = xscale2pmu_पढ़ो_pmnc();
	xscale2pmu_ग_लिखो_pmnc(pmnc & ~XSCALE_PMU_ENABLE);

	/* Check the overflow flag रेजिस्टर. */
	of_flags = xscale2pmu_पढ़ो_overflow_flags();
	अगर (!(of_flags & XSCALE2_OVERFLOWED_MASK))
		वापस IRQ_NONE;

	/* Clear the overflow bits. */
	xscale2pmu_ग_लिखो_overflow_flags(of_flags);

	regs = get_irq_regs();

	क्रम (idx = 0; idx < cpu_pmu->num_events; ++idx) अणु
		काष्ठा perf_event *event = cpuc->events[idx];
		काष्ठा hw_perf_event *hwc;

		अगर (!event)
			जारी;

		अगर (!xscale2_pmnc_counter_has_overflowed(of_flags, idx))
			जारी;

		hwc = &event->hw;
		armpmu_event_update(event);
		perf_sample_data_init(&data, 0, hwc->last_period);
		अगर (!armpmu_event_set_period(event))
			जारी;

		अगर (perf_event_overflow(event, &data, regs))
			cpu_pmu->disable(event);
	पूर्ण

	irq_work_run();

	/*
	 * Re-enable the PMU.
	 */
	pmnc = xscale2pmu_पढ़ो_pmnc() | XSCALE_PMU_ENABLE;
	xscale2pmu_ग_लिखो_pmnc(pmnc);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xscale2pmu_enable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags, ien, evtsel;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	ien = xscale2pmu_पढ़ो_पूर्णांक_enable();
	evtsel = xscale2pmu_पढ़ो_event_select();

	चयन (idx) अणु
	हाल XSCALE_CYCLE_COUNTER:
		ien |= XSCALE2_CCOUNT_INT_EN;
		अवरोध;
	हाल XSCALE_COUNTER0:
		ien |= XSCALE2_COUNT0_INT_EN;
		evtsel &= ~XSCALE2_COUNT0_EVT_MASK;
		evtsel |= hwc->config_base << XSCALE2_COUNT0_EVT_SHFT;
		अवरोध;
	हाल XSCALE_COUNTER1:
		ien |= XSCALE2_COUNT1_INT_EN;
		evtsel &= ~XSCALE2_COUNT1_EVT_MASK;
		evtsel |= hwc->config_base << XSCALE2_COUNT1_EVT_SHFT;
		अवरोध;
	हाल XSCALE_COUNTER2:
		ien |= XSCALE2_COUNT2_INT_EN;
		evtsel &= ~XSCALE2_COUNT2_EVT_MASK;
		evtsel |= hwc->config_base << XSCALE2_COUNT2_EVT_SHFT;
		अवरोध;
	हाल XSCALE_COUNTER3:
		ien |= XSCALE2_COUNT3_INT_EN;
		evtsel &= ~XSCALE2_COUNT3_EVT_MASK;
		evtsel |= hwc->config_base << XSCALE2_COUNT3_EVT_SHFT;
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	xscale2pmu_ग_लिखो_event_select(evtsel);
	xscale2pmu_ग_लिखो_पूर्णांक_enable(ien);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम xscale2pmu_disable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags, ien, evtsel, of_flags;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	ien = xscale2pmu_पढ़ो_पूर्णांक_enable();
	evtsel = xscale2pmu_पढ़ो_event_select();

	चयन (idx) अणु
	हाल XSCALE_CYCLE_COUNTER:
		ien &= ~XSCALE2_CCOUNT_INT_EN;
		of_flags = XSCALE2_CCOUNT_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER0:
		ien &= ~XSCALE2_COUNT0_INT_EN;
		evtsel &= ~XSCALE2_COUNT0_EVT_MASK;
		evtsel |= XSCALE_PERFCTR_UNUSED << XSCALE2_COUNT0_EVT_SHFT;
		of_flags = XSCALE2_COUNT0_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER1:
		ien &= ~XSCALE2_COUNT1_INT_EN;
		evtsel &= ~XSCALE2_COUNT1_EVT_MASK;
		evtsel |= XSCALE_PERFCTR_UNUSED << XSCALE2_COUNT1_EVT_SHFT;
		of_flags = XSCALE2_COUNT1_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER2:
		ien &= ~XSCALE2_COUNT2_INT_EN;
		evtsel &= ~XSCALE2_COUNT2_EVT_MASK;
		evtsel |= XSCALE_PERFCTR_UNUSED << XSCALE2_COUNT2_EVT_SHFT;
		of_flags = XSCALE2_COUNT2_OVERFLOW;
		अवरोध;
	हाल XSCALE_COUNTER3:
		ien &= ~XSCALE2_COUNT3_INT_EN;
		evtsel &= ~XSCALE2_COUNT3_EVT_MASK;
		evtsel |= XSCALE_PERFCTR_UNUSED << XSCALE2_COUNT3_EVT_SHFT;
		of_flags = XSCALE2_COUNT3_OVERFLOW;
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	xscale2pmu_ग_लिखो_event_select(evtsel);
	xscale2pmu_ग_लिखो_पूर्णांक_enable(ien);
	xscale2pmu_ग_लिखो_overflow_flags(of_flags);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल पूर्णांक
xscale2pmu_get_event_idx(काष्ठा pmu_hw_events *cpuc,
				काष्ठा perf_event *event)
अणु
	पूर्णांक idx = xscale1pmu_get_event_idx(cpuc, event);
	अगर (idx >= 0)
		जाओ out;

	अगर (!test_and_set_bit(XSCALE_COUNTER3, cpuc->used_mask))
		idx = XSCALE_COUNTER3;
	अन्यथा अगर (!test_and_set_bit(XSCALE_COUNTER2, cpuc->used_mask))
		idx = XSCALE_COUNTER2;
out:
	वापस idx;
पूर्ण

अटल व्योम xscale2pmu_start(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags, val;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = xscale2pmu_पढ़ो_pmnc() & ~XSCALE_PMU_CNT64;
	val |= XSCALE_PMU_ENABLE;
	xscale2pmu_ग_लिखो_pmnc(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम xscale2pmu_stop(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags, val;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	val = xscale2pmu_पढ़ो_pmnc();
	val &= ~XSCALE_PMU_ENABLE;
	xscale2pmu_ग_लिखो_pmnc(val);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल अंतरभूत u64 xscale2pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;
	u32 val = 0;

	चयन (counter) अणु
	हाल XSCALE_CYCLE_COUNTER:
		यंत्र अस्थिर("mrc p14, 0, %0, c1, c1, 0" : "=r" (val));
		अवरोध;
	हाल XSCALE_COUNTER0:
		यंत्र अस्थिर("mrc p14, 0, %0, c0, c2, 0" : "=r" (val));
		अवरोध;
	हाल XSCALE_COUNTER1:
		यंत्र अस्थिर("mrc p14, 0, %0, c1, c2, 0" : "=r" (val));
		अवरोध;
	हाल XSCALE_COUNTER2:
		यंत्र अस्थिर("mrc p14, 0, %0, c2, c2, 0" : "=r" (val));
		अवरोध;
	हाल XSCALE_COUNTER3:
		यंत्र अस्थिर("mrc p14, 0, %0, c3, c2, 0" : "=r" (val));
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल अंतरभूत व्योम xscale2pmu_ग_लिखो_counter(काष्ठा perf_event *event, u64 val)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;

	चयन (counter) अणु
	हाल XSCALE_CYCLE_COUNTER:
		यंत्र अस्थिर("mcr p14, 0, %0, c1, c1, 0" : : "r" (val));
		अवरोध;
	हाल XSCALE_COUNTER0:
		यंत्र अस्थिर("mcr p14, 0, %0, c0, c2, 0" : : "r" (val));
		अवरोध;
	हाल XSCALE_COUNTER1:
		यंत्र अस्थिर("mcr p14, 0, %0, c1, c2, 0" : : "r" (val));
		अवरोध;
	हाल XSCALE_COUNTER2:
		यंत्र अस्थिर("mcr p14, 0, %0, c2, c2, 0" : : "r" (val));
		अवरोध;
	हाल XSCALE_COUNTER3:
		यंत्र अस्थिर("mcr p14, 0, %0, c3, c2, 0" : : "r" (val));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xscale2pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	cpu_pmu->name		= "armv5_xscale2";
	cpu_pmu->handle_irq	= xscale2pmu_handle_irq;
	cpu_pmu->enable		= xscale2pmu_enable_event;
	cpu_pmu->disable	= xscale2pmu_disable_event;
	cpu_pmu->पढ़ो_counter	= xscale2pmu_पढ़ो_counter;
	cpu_pmu->ग_लिखो_counter	= xscale2pmu_ग_लिखो_counter;
	cpu_pmu->get_event_idx	= xscale2pmu_get_event_idx;
	cpu_pmu->clear_event_idx = xscalepmu_clear_event_idx;
	cpu_pmu->start		= xscale2pmu_start;
	cpu_pmu->stop		= xscale2pmu_stop;
	cpu_pmu->map_event	= xscale_map_event;
	cpu_pmu->num_events	= 5;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pmu_probe_info xscale_pmu_probe_table[] = अणु
	XSCALE_PMU_PROBE(ARM_CPU_XSCALE_ARCH_V1, xscale1pmu_init),
	XSCALE_PMU_PROBE(ARM_CPU_XSCALE_ARCH_V2, xscale2pmu_init),
	अणु /* sentinel value */ पूर्ण
पूर्ण;

अटल पूर्णांक xscale_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस arm_pmu_device_probe(pdev, शून्य, xscale_pmu_probe_table);
पूर्ण

अटल काष्ठा platक्रमm_driver xscale_pmu_driver = अणु
	.driver		= अणु
		.name	= "xscale-pmu",
	पूर्ण,
	.probe		= xscale_pmu_device_probe,
पूर्ण;

builtin_platक्रमm_driver(xscale_pmu_driver);
#पूर्ण_अगर	/* CONFIG_CPU_XSCALE */
