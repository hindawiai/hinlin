<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>

#समावेश "../perf_event.h"

/*
 * Not sure about some of these
 */
अटल स्थिर u64 p6_perfmon_event_map[] =
अणु
  [PERF_COUNT_HW_CPU_CYCLES]		= 0x0079,	/* CPU_CLK_UNHALTED */
  [PERF_COUNT_HW_INSTRUCTIONS]		= 0x00c0,	/* INST_RETIRED     */
  [PERF_COUNT_HW_CACHE_REFERENCES]	= 0x0f2e,	/* L2_RQSTS:M:E:S:I */
  [PERF_COUNT_HW_CACHE_MISSES]		= 0x012e,	/* L2_RQSTS:I       */
  [PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x00c4,	/* BR_INST_RETIRED  */
  [PERF_COUNT_HW_BRANCH_MISSES]		= 0x00c5,	/* BR_MISS_PRED_RETIRED */
  [PERF_COUNT_HW_BUS_CYCLES]		= 0x0062,	/* BUS_DRDY_CLOCKS  */
  [PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] = 0x00a2,	/* RESOURCE_STALLS  */

पूर्ण;

अटल स्थिर u64 __initस्थिर p6_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0043,	/* DATA_MEM_REFS       */
                [ C(RESULT_MISS)   ] = 0x0045,	/* DCU_LINES_IN        */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0x0f29,	/* L2_LD:M:E:S:I       */
	पूर्ण,
        [ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
        पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0080,	/* IFU_IFETCH         */
		[ C(RESULT_MISS)   ] = 0x0f28,	/* L2_IFETCH:M:E:S:I  */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0x0025,	/* L2_M_LINES_INM     */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0043,	/* DATA_MEM_REFS      */
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0080,	/* IFU_IFETCH         */
		[ C(RESULT_MISS)   ] = 0x0085,	/* ITLB_MISS          */
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
		[ C(RESULT_ACCESS) ] = 0x00c4,	/* BR_INST_RETIRED      */
		[ C(RESULT_MISS)   ] = 0x00c5,	/* BR_MISS_PRED_RETIRED */
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

अटल u64 p6_pmu_event_map(पूर्णांक hw_event)
अणु
	वापस p6_perfmon_event_map[hw_event];
पूर्ण

/*
 * Event setting that is specअगरied not to count anything.
 * We use this to effectively disable a counter.
 *
 * L2_RQSTS with 0 MESI unit mask.
 */
#घोषणा P6_NOP_EVENT			0x0000002EULL

अटल काष्ठा event_स्थिरraपूर्णांक p6_event_स्थिरraपूर्णांकs[] =
अणु
	INTEL_EVENT_CONSTRAINT(0xc1, 0x1),	/* FLOPS */
	INTEL_EVENT_CONSTRAINT(0x10, 0x1),	/* FP_COMP_OPS_EXE */
	INTEL_EVENT_CONSTRAINT(0x11, 0x2),	/* FP_ASSIST */
	INTEL_EVENT_CONSTRAINT(0x12, 0x2),	/* MUL */
	INTEL_EVENT_CONSTRAINT(0x13, 0x2),	/* DIV */
	INTEL_EVENT_CONSTRAINT(0x14, 0x1),	/* CYCLES_DIV_BUSY */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल व्योम p6_pmu_disable_all(व्योम)
अणु
	u64 val;

	/* p6 only has one enable रेजिस्टर */
	rdmsrl(MSR_P6_EVNTSEL0, val);
	val &= ~ARCH_PERFMON_EVENTSEL_ENABLE;
	wrmsrl(MSR_P6_EVNTSEL0, val);
पूर्ण

अटल व्योम p6_pmu_enable_all(पूर्णांक added)
अणु
	अचिन्हित दीर्घ val;

	/* p6 only has one enable रेजिस्टर */
	rdmsrl(MSR_P6_EVNTSEL0, val);
	val |= ARCH_PERFMON_EVENTSEL_ENABLE;
	wrmsrl(MSR_P6_EVNTSEL0, val);
पूर्ण

अटल अंतरभूत व्योम
p6_pmu_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 val = P6_NOP_EVENT;

	(व्योम)wrmsrl_safe(hwc->config_base, val);
पूर्ण

अटल व्योम p6_pmu_enable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 val;

	val = hwc->config;

	/*
	 * p6 only has a global event enable, set on PerfEvtSel0
	 * We "disable" events by programming P6_NOP_EVENT
	 * and we rely on p6_pmu_enable_all() being called
	 * to actually enable the events.
	 */

	(व्योम)wrmsrl_safe(hwc->config_base, val);
पूर्ण

PMU_FORMAT_ATTR(event,	"config:0-7"	);
PMU_FORMAT_ATTR(umask,	"config:8-15"	);
PMU_FORMAT_ATTR(edge,	"config:18"	);
PMU_FORMAT_ATTR(pc,	"config:19"	);
PMU_FORMAT_ATTR(inv,	"config:23"	);
PMU_FORMAT_ATTR(cmask,	"config:24-31"	);

अटल काष्ठा attribute *पूर्णांकel_p6_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_pc.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_cmask.attr,
	शून्य,
पूर्ण;

अटल __initस्थिर स्थिर काष्ठा x86_pmu p6_pmu = अणु
	.name			= "p6",
	.handle_irq		= x86_pmu_handle_irq,
	.disable_all		= p6_pmu_disable_all,
	.enable_all		= p6_pmu_enable_all,
	.enable			= p6_pmu_enable_event,
	.disable		= p6_pmu_disable_event,
	.hw_config		= x86_pmu_hw_config,
	.schedule_events	= x86_schedule_events,
	.eventsel		= MSR_P6_EVNTSEL0,
	.perfctr		= MSR_P6_PERFCTR0,
	.event_map		= p6_pmu_event_map,
	.max_events		= ARRAY_SIZE(p6_perfmon_event_map),
	.apic			= 1,
	.max_period		= (1ULL << 31) - 1,
	.version		= 0,
	.num_counters		= 2,
	/*
	 * Events have 40 bits implemented. However they are deचिन्हित such
	 * that bits [32-39] are sign extensions of bit 31. As such the
	 * effective width of a event क्रम P6-like PMU is 32 bits only.
	 *
	 * See IA-32 Intel Architecture Software developer manual Vol 3B
	 */
	.cntval_bits		= 32,
	.cntval_mask		= (1ULL << 32) - 1,
	.get_event_स्थिरraपूर्णांकs	= x86_get_event_स्थिरraपूर्णांकs,
	.event_स्थिरraपूर्णांकs	= p6_event_स्थिरraपूर्णांकs,

	.क्रमmat_attrs		= पूर्णांकel_p6_क्रमmats_attr,
	.events_sysfs_show	= पूर्णांकel_event_sysfs_show,

पूर्ण;

अटल __init व्योम p6_pmu_rdpmc_quirk(व्योम)
अणु
	अगर (boot_cpu_data.x86_stepping < 9) अणु
		/*
		 * PPro erratum 26; fixed in stepping 9 and above.
		 */
		pr_warn("Userspace RDPMC support disabled due to a CPU erratum\n");
		x86_pmu.attr_rdpmc_broken = 1;
		x86_pmu.attr_rdpmc = 0;
	पूर्ण
पूर्ण

__init पूर्णांक p6_pmu_init(व्योम)
अणु
	x86_pmu = p6_pmu;

	चयन (boot_cpu_data.x86_model) अणु
	हाल  1: /* Pentium Pro */
		x86_add_quirk(p6_pmu_rdpmc_quirk);
		अवरोध;

	हाल  3: /* Pentium II - Klamath */
	हाल  5: /* Pentium II - Deschutes */
	हाल  6: /* Pentium II - Menकरोcino */
		अवरोध;

	हाल  7: /* Pentium III - Kaपंचांगai */
	हाल  8: /* Pentium III - Coppermine */
	हाल 10: /* Pentium III Xeon */
	हाल 11: /* Pentium III - Tualatin */
		अवरोध;

	हाल  9: /* Pentium M - Banias */
	हाल 13: /* Pentium M - Dothan */
		अवरोध;

	शेष:
		pr_cont("unsupported p6 CPU model %d ", boot_cpu_data.x86_model);
		वापस -ENODEV;
	पूर्ण

	स_नकल(hw_cache_event_ids, p6_hw_cache_event_ids,
		माप(hw_cache_event_ids));

	वापस 0;
पूर्ण
