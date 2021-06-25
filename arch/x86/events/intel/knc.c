<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Driver क्रम Intel Xeon Phi "Knights Corner" PMU */

#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/hardirq.h>

#समावेश "../perf_event.h"

अटल स्थिर u64 knc_perfmon_event_map[] =
अणु
  [PERF_COUNT_HW_CPU_CYCLES]		= 0x002a,
  [PERF_COUNT_HW_INSTRUCTIONS]		= 0x0016,
  [PERF_COUNT_HW_CACHE_REFERENCES]	= 0x0028,
  [PERF_COUNT_HW_CACHE_MISSES]		= 0x0029,
  [PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x0012,
  [PERF_COUNT_HW_BRANCH_MISSES]		= 0x002b,
पूर्ण;

अटल स्थिर u64 __initस्थिर knc_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		/* On Xeon Phi event "0" is a valid DATA_READ          */
		/*   (L1 Data Cache Reads) Inकाष्ठाion.                */
		/* We code this as ARCH_PERFMON_EVENTSEL_INT as this   */
		/* bit will always be set in x86_pmu_hw_config().      */
		[ C(RESULT_ACCESS) ] = ARCH_PERFMON_EVENTSEL_INT,
						/* DATA_READ           */
		[ C(RESULT_MISS)   ] = 0x0003,	/* DATA_READ_MISS      */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0001,	/* DATA_WRITE          */
		[ C(RESULT_MISS)   ] = 0x0004,	/* DATA_WRITE_MISS     */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0011,	/* L1_DATA_PF1         */
		[ C(RESULT_MISS)   ] = 0x001c,	/* L1_DATA_PF1_MISS    */
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x000c,	/* CODE_READ          */
		[ C(RESULT_MISS)   ] = 0x000e,	/* CODE_CACHE_MISS    */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0x10cb,	/* L2_READ_MISS */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x10cc,	/* L2_WRITE_HIT */
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x10fc,	/* L2_DATA_PF2      */
		[ C(RESULT_MISS)   ] = 0x10fe,	/* L2_DATA_PF2_MISS */
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = ARCH_PERFMON_EVENTSEL_INT,
						/* DATA_READ */
						/* see note on L1 OP_READ */
		[ C(RESULT_MISS)   ] = 0x0002,	/* DATA_PAGE_WALK */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0001,	/* DATA_WRITE */
		[ C(RESULT_MISS)   ] = 0x0002,	/* DATA_PAGE_WALK */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x000c,	/* CODE_READ */
		[ C(RESULT_MISS)   ] = 0x000d,	/* CODE_PAGE_WALK */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0012,	/* BRANCHES */
		[ C(RESULT_MISS)   ] = 0x002b,	/* BRANCHES_MISPREDICTED */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
पूर्ण;


अटल u64 knc_pmu_event_map(पूर्णांक hw_event)
अणु
	वापस knc_perfmon_event_map[hw_event];
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक knc_event_स्थिरraपूर्णांकs[] =
अणु
	INTEL_EVENT_CONSTRAINT(0xc3, 0x1),	/* HWP_L2HIT */
	INTEL_EVENT_CONSTRAINT(0xc4, 0x1),	/* HWP_L2MISS */
	INTEL_EVENT_CONSTRAINT(0xc8, 0x1),	/* L2_READ_HIT_E */
	INTEL_EVENT_CONSTRAINT(0xc9, 0x1),	/* L2_READ_HIT_M */
	INTEL_EVENT_CONSTRAINT(0xca, 0x1),	/* L2_READ_HIT_S */
	INTEL_EVENT_CONSTRAINT(0xcb, 0x1),	/* L2_READ_MISS */
	INTEL_EVENT_CONSTRAINT(0xcc, 0x1),	/* L2_WRITE_HIT */
	INTEL_EVENT_CONSTRAINT(0xce, 0x1),	/* L2_STRONGLY_ORDERED_STREAMING_VSTORES_MISS */
	INTEL_EVENT_CONSTRAINT(0xcf, 0x1),	/* L2_WEAKLY_ORDERED_STREAMING_VSTORE_MISS */
	INTEL_EVENT_CONSTRAINT(0xd7, 0x1),	/* L2_VICTIM_REQ_WITH_DATA */
	INTEL_EVENT_CONSTRAINT(0xe3, 0x1),	/* SNP_HITM_BUNIT */
	INTEL_EVENT_CONSTRAINT(0xe6, 0x1),	/* SNP_HIT_L2 */
	INTEL_EVENT_CONSTRAINT(0xe7, 0x1),	/* SNP_HITM_L2 */
	INTEL_EVENT_CONSTRAINT(0xf1, 0x1),	/* L2_DATA_READ_MISS_CACHE_FILL */
	INTEL_EVENT_CONSTRAINT(0xf2, 0x1),	/* L2_DATA_WRITE_MISS_CACHE_FILL */
	INTEL_EVENT_CONSTRAINT(0xf6, 0x1),	/* L2_DATA_READ_MISS_MEM_FILL */
	INTEL_EVENT_CONSTRAINT(0xf7, 0x1),	/* L2_DATA_WRITE_MISS_MEM_FILL */
	INTEL_EVENT_CONSTRAINT(0xfc, 0x1),	/* L2_DATA_PF2 */
	INTEL_EVENT_CONSTRAINT(0xfd, 0x1),	/* L2_DATA_PF2_DROP */
	INTEL_EVENT_CONSTRAINT(0xfe, 0x1),	/* L2_DATA_PF2_MISS */
	INTEL_EVENT_CONSTRAINT(0xff, 0x1),	/* L2_DATA_HIT_INFLIGHT_PF2 */
	EVENT_CONSTRAINT_END
पूर्ण;

#घोषणा MSR_KNC_IA32_PERF_GLOBAL_STATUS		0x0000002d
#घोषणा MSR_KNC_IA32_PERF_GLOBAL_OVF_CONTROL	0x0000002e
#घोषणा MSR_KNC_IA32_PERF_GLOBAL_CTRL		0x0000002f

#घोषणा KNC_ENABLE_COUNTER0			0x00000001
#घोषणा KNC_ENABLE_COUNTER1			0x00000002

अटल व्योम knc_pmu_disable_all(व्योम)
अणु
	u64 val;

	rdmsrl(MSR_KNC_IA32_PERF_GLOBAL_CTRL, val);
	val &= ~(KNC_ENABLE_COUNTER0|KNC_ENABLE_COUNTER1);
	wrmsrl(MSR_KNC_IA32_PERF_GLOBAL_CTRL, val);
पूर्ण

अटल व्योम knc_pmu_enable_all(पूर्णांक added)
अणु
	u64 val;

	rdmsrl(MSR_KNC_IA32_PERF_GLOBAL_CTRL, val);
	val |= (KNC_ENABLE_COUNTER0|KNC_ENABLE_COUNTER1);
	wrmsrl(MSR_KNC_IA32_PERF_GLOBAL_CTRL, val);
पूर्ण

अटल अंतरभूत व्योम
knc_pmu_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 val;

	val = hwc->config;
	val &= ~ARCH_PERFMON_EVENTSEL_ENABLE;

	(व्योम)wrmsrl_safe(hwc->config_base + hwc->idx, val);
पूर्ण

अटल व्योम knc_pmu_enable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 val;

	val = hwc->config;
	val |= ARCH_PERFMON_EVENTSEL_ENABLE;

	(व्योम)wrmsrl_safe(hwc->config_base + hwc->idx, val);
पूर्ण

अटल अंतरभूत u64 knc_pmu_get_status(व्योम)
अणु
	u64 status;

	rdmsrl(MSR_KNC_IA32_PERF_GLOBAL_STATUS, status);

	वापस status;
पूर्ण

अटल अंतरभूत व्योम knc_pmu_ack_status(u64 ack)
अणु
	wrmsrl(MSR_KNC_IA32_PERF_GLOBAL_OVF_CONTROL, ack);
पूर्ण

अटल पूर्णांक knc_pmu_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा cpu_hw_events *cpuc;
	पूर्णांक handled = 0;
	पूर्णांक bit, loops;
	u64 status;

	cpuc = this_cpu_ptr(&cpu_hw_events);

	knc_pmu_disable_all();

	status = knc_pmu_get_status();
	अगर (!status) अणु
		knc_pmu_enable_all(0);
		वापस handled;
	पूर्ण

	loops = 0;
again:
	knc_pmu_ack_status(status);
	अगर (++loops > 100) अणु
		WARN_ONCE(1, "perf: irq loop stuck!\n");
		perf_event_prपूर्णांक_debug();
		जाओ करोne;
	पूर्ण

	inc_irq_stat(apic_perf_irqs);

	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&status, X86_PMC_IDX_MAX) अणु
		काष्ठा perf_event *event = cpuc->events[bit];

		handled++;

		अगर (!test_bit(bit, cpuc->active_mask))
			जारी;

		अगर (!पूर्णांकel_pmu_save_and_restart(event))
			जारी;

		perf_sample_data_init(&data, 0, event->hw.last_period);

		अगर (perf_event_overflow(event, &data, regs))
			x86_pmu_stop(event, 0);
	पूर्ण

	/*
	 * Repeat अगर there is more work to be करोne:
	 */
	status = knc_pmu_get_status();
	अगर (status)
		जाओ again;

करोne:
	/* Only restore PMU state when it's active. See x86_pmu_disable(). */
	अगर (cpuc->enabled)
		knc_pmu_enable_all(0);

	वापस handled;
पूर्ण


PMU_FORMAT_ATTR(event,	"config:0-7"	);
PMU_FORMAT_ATTR(umask,	"config:8-15"	);
PMU_FORMAT_ATTR(edge,	"config:18"	);
PMU_FORMAT_ATTR(inv,	"config:23"	);
PMU_FORMAT_ATTR(cmask,	"config:24-31"	);

अटल काष्ठा attribute *पूर्णांकel_knc_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_cmask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा x86_pmu knc_pmu __initस्थिर = अणु
	.name			= "knc",
	.handle_irq		= knc_pmu_handle_irq,
	.disable_all		= knc_pmu_disable_all,
	.enable_all		= knc_pmu_enable_all,
	.enable			= knc_pmu_enable_event,
	.disable		= knc_pmu_disable_event,
	.hw_config		= x86_pmu_hw_config,
	.schedule_events	= x86_schedule_events,
	.eventsel		= MSR_KNC_EVNTSEL0,
	.perfctr		= MSR_KNC_PERFCTR0,
	.event_map		= knc_pmu_event_map,
	.max_events             = ARRAY_SIZE(knc_perfmon_event_map),
	.apic			= 1,
	.max_period		= (1ULL << 39) - 1,
	.version		= 0,
	.num_counters		= 2,
	.cntval_bits		= 40,
	.cntval_mask		= (1ULL << 40) - 1,
	.get_event_स्थिरraपूर्णांकs	= x86_get_event_स्थिरraपूर्णांकs,
	.event_स्थिरraपूर्णांकs	= knc_event_स्थिरraपूर्णांकs,
	.क्रमmat_attrs		= पूर्णांकel_knc_क्रमmats_attr,
पूर्ण;

__init पूर्णांक knc_pmu_init(व्योम)
अणु
	x86_pmu = knc_pmu;

	स_नकल(hw_cache_event_ids, knc_hw_cache_event_ids, 
		माप(hw_cache_event_ids));

	वापस 0;
पूर्ण
