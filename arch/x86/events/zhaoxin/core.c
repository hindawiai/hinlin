<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Zhaoxin PMU; like Intel Architectural PerfMon-v2
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/nmi.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/apic.h>

#समावेश "../perf_event.h"

/*
 * Zhaoxin PerfMon, used on zxc and later.
 */
अटल u64 zx_pmon_event_map[PERF_COUNT_HW_MAX] __पढ़ो_mostly = अणु

	[PERF_COUNT_HW_CPU_CYCLES]        = 0x0082,
	[PERF_COUNT_HW_INSTRUCTIONS]      = 0x00c0,
	[PERF_COUNT_HW_CACHE_REFERENCES]  = 0x0515,
	[PERF_COUNT_HW_CACHE_MISSES]      = 0x051a,
	[PERF_COUNT_HW_BUS_CYCLES]        = 0x0083,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक zxc_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly = अणु

	FIXED_EVENT_CONSTRAINT(0x0082, 1), /* unhalted core घड़ी cycles */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक zxd_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly = अणु

	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* retired inकाष्ठाions */
	FIXED_EVENT_CONSTRAINT(0x0082, 1), /* unhalted core घड़ी cycles */
	FIXED_EVENT_CONSTRAINT(0x0083, 2), /* unhalted bus घड़ी cycles */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल __initस्थिर स्थिर u64 zxd_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0042,
		[C(RESULT_MISS)] = 0x0538,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = 0x0043,
		[C(RESULT_MISS)] = 0x0562,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0300,
		[C(RESULT_MISS)] = 0x0301,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0x030a,
		[C(RESULT_MISS)] = 0x030b,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0042,
		[C(RESULT_MISS)] = 0x052c,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = 0x0043,
		[C(RESULT_MISS)] = 0x0530,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0x0564,
		[C(RESULT_MISS)] = 0x0565,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x00c0,
		[C(RESULT_MISS)] = 0x0534,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0700,
		[C(RESULT_MISS)] = 0x0709,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
[C(NODE)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 zxe_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0568,
		[C(RESULT_MISS)] = 0x054b,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = 0x0669,
		[C(RESULT_MISS)] = 0x0562,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0300,
		[C(RESULT_MISS)] = 0x0301,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0x030a,
		[C(RESULT_MISS)] = 0x030b,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0,
		[C(RESULT_MISS)] = 0x0,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = 0x0,
		[C(RESULT_MISS)] = 0x0,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0x0,
		[C(RESULT_MISS)] = 0x0,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0568,
		[C(RESULT_MISS)] = 0x052c,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = 0x0669,
		[C(RESULT_MISS)] = 0x0530,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0x0564,
		[C(RESULT_MISS)] = 0x0565,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x00c0,
		[C(RESULT_MISS)] = 0x0534,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0028,
		[C(RESULT_MISS)] = 0x0029,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
[C(NODE)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)] = -1,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल व्योम zhaoxin_pmu_disable_all(व्योम)
अणु
	wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL, 0);
पूर्ण

अटल व्योम zhaoxin_pmu_enable_all(पूर्णांक added)
अणु
	wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL, x86_pmu.पूर्णांकel_ctrl);
पूर्ण

अटल अंतरभूत u64 zhaoxin_pmu_get_status(व्योम)
अणु
	u64 status;

	rdmsrl(MSR_CORE_PERF_GLOBAL_STATUS, status);

	वापस status;
पूर्ण

अटल अंतरभूत व्योम zhaoxin_pmu_ack_status(u64 ack)
अणु
	wrmsrl(MSR_CORE_PERF_GLOBAL_OVF_CTRL, ack);
पूर्ण

अटल अंतरभूत व्योम zxc_pmu_ack_status(u64 ack)
अणु
	/*
	 * ZXC needs global control enabled in order to clear status bits.
	 */
	zhaoxin_pmu_enable_all(0);
	zhaoxin_pmu_ack_status(ack);
	zhaoxin_pmu_disable_all();
पूर्ण

अटल व्योम zhaoxin_pmu_disable_fixed(काष्ठा hw_perf_event *hwc)
अणु
	पूर्णांक idx = hwc->idx - INTEL_PMC_IDX_FIXED;
	u64 ctrl_val, mask;

	mask = 0xfULL << (idx * 4);

	rdmsrl(hwc->config_base, ctrl_val);
	ctrl_val &= ~mask;
	wrmsrl(hwc->config_base, ctrl_val);
पूर्ण

अटल व्योम zhaoxin_pmu_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (unlikely(hwc->config_base == MSR_ARCH_PERFMON_FIXED_CTR_CTRL)) अणु
		zhaoxin_pmu_disable_fixed(hwc);
		वापस;
	पूर्ण

	x86_pmu_disable_event(event);
पूर्ण

अटल व्योम zhaoxin_pmu_enable_fixed(काष्ठा hw_perf_event *hwc)
अणु
	पूर्णांक idx = hwc->idx - INTEL_PMC_IDX_FIXED;
	u64 ctrl_val, bits, mask;

	/*
	 * Enable IRQ generation (0x8),
	 * and enable ring-3 counting (0x2) and ring-0 counting (0x1)
	 * अगर requested:
	 */
	bits = 0x8ULL;
	अगर (hwc->config & ARCH_PERFMON_EVENTSEL_USR)
		bits |= 0x2;
	अगर (hwc->config & ARCH_PERFMON_EVENTSEL_OS)
		bits |= 0x1;

	bits <<= (idx * 4);
	mask = 0xfULL << (idx * 4);

	rdmsrl(hwc->config_base, ctrl_val);
	ctrl_val &= ~mask;
	ctrl_val |= bits;
	wrmsrl(hwc->config_base, ctrl_val);
पूर्ण

अटल व्योम zhaoxin_pmu_enable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (unlikely(hwc->config_base == MSR_ARCH_PERFMON_FIXED_CTR_CTRL)) अणु
		zhaoxin_pmu_enable_fixed(hwc);
		वापस;
	पूर्ण

	__x86_pmu_enable_event(hwc, ARCH_PERFMON_EVENTSEL_ENABLE);
पूर्ण

/*
 * This handler is triggered by the local APIC, so the APIC IRQ handling
 * rules apply:
 */
अटल पूर्णांक zhaoxin_pmu_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा cpu_hw_events *cpuc;
	पूर्णांक handled = 0;
	u64 status;
	पूर्णांक bit;

	cpuc = this_cpu_ptr(&cpu_hw_events);
	apic_ग_लिखो(APIC_LVTPC, APIC_DM_NMI);
	zhaoxin_pmu_disable_all();
	status = zhaoxin_pmu_get_status();
	अगर (!status)
		जाओ करोne;

again:
	अगर (x86_pmu.enabled_ack)
		zxc_pmu_ack_status(status);
	अन्यथा
		zhaoxin_pmu_ack_status(status);

	inc_irq_stat(apic_perf_irqs);

	/*
	 * CondChgd bit 63 करोesn't mean any overflow status. Ignore
	 * and clear the bit.
	 */
	अगर (__test_and_clear_bit(63, (अचिन्हित दीर्घ *)&status)) अणु
		अगर (!status)
			जाओ करोne;
	पूर्ण

	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&status, X86_PMC_IDX_MAX) अणु
		काष्ठा perf_event *event = cpuc->events[bit];

		handled++;

		अगर (!test_bit(bit, cpuc->active_mask))
			जारी;

		x86_perf_event_update(event);
		perf_sample_data_init(&data, 0, event->hw.last_period);

		अगर (!x86_perf_event_set_period(event))
			जारी;

		अगर (perf_event_overflow(event, &data, regs))
			x86_pmu_stop(event, 0);
	पूर्ण

	/*
	 * Repeat अगर there is more work to be करोne:
	 */
	status = zhaoxin_pmu_get_status();
	अगर (status)
		जाओ again;

करोne:
	zhaoxin_pmu_enable_all(0);
	वापस handled;
पूर्ण

अटल u64 zhaoxin_pmu_event_map(पूर्णांक hw_event)
अणु
	वापस zx_pmon_event_map[hw_event];
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
zhaoxin_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;

	अगर (x86_pmu.event_स्थिरraपूर्णांकs) अणु
		क्रम_each_event_स्थिरraपूर्णांक(c, x86_pmu.event_स्थिरraपूर्णांकs) अणु
			अगर ((event->hw.config & c->cmask) == c->code)
				वापस c;
		पूर्ण
	पूर्ण

	वापस &unस्थिरrained;
पूर्ण

PMU_FORMAT_ATTR(event,	"config:0-7");
PMU_FORMAT_ATTR(umask,	"config:8-15");
PMU_FORMAT_ATTR(edge,	"config:18");
PMU_FORMAT_ATTR(inv,	"config:23");
PMU_FORMAT_ATTR(cmask,	"config:24-31");

अटल काष्ठा attribute *zx_arch_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_cmask.attr,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार zhaoxin_event_sysfs_show(अक्षर *page, u64 config)
अणु
	u64 event = (config & ARCH_PERFMON_EVENTSEL_EVENT);

	वापस x86_event_sysfs_show(page, config, event);
पूर्ण

अटल स्थिर काष्ठा x86_pmu zhaoxin_pmu __initस्थिर = अणु
	.name			= "zhaoxin",
	.handle_irq		= zhaoxin_pmu_handle_irq,
	.disable_all		= zhaoxin_pmu_disable_all,
	.enable_all		= zhaoxin_pmu_enable_all,
	.enable			= zhaoxin_pmu_enable_event,
	.disable		= zhaoxin_pmu_disable_event,
	.hw_config		= x86_pmu_hw_config,
	.schedule_events	= x86_schedule_events,
	.eventsel		= MSR_ARCH_PERFMON_EVENTSEL0,
	.perfctr		= MSR_ARCH_PERFMON_PERFCTR0,
	.event_map		= zhaoxin_pmu_event_map,
	.max_events		= ARRAY_SIZE(zx_pmon_event_map),
	.apic			= 1,
	/*
	 * For zxd/zxe, पढ़ो/ग_लिखो operation क्रम PMCx MSR is 48 bits.
	 */
	.max_period		= (1ULL << 47) - 1,
	.get_event_स्थिरraपूर्णांकs	= zhaoxin_get_event_स्थिरraपूर्णांकs,

	.क्रमmat_attrs		= zx_arch_क्रमmats_attr,
	.events_sysfs_show	= zhaoxin_event_sysfs_show,
पूर्ण;

अटल स्थिर काष्ठा अणु पूर्णांक id; अक्षर *name; पूर्ण zx_arch_events_map[] __initस्थिर = अणु
	अणु PERF_COUNT_HW_CPU_CYCLES, "cpu cycles" पूर्ण,
	अणु PERF_COUNT_HW_INSTRUCTIONS, "instructions" पूर्ण,
	अणु PERF_COUNT_HW_BUS_CYCLES, "bus cycles" पूर्ण,
	अणु PERF_COUNT_HW_CACHE_REFERENCES, "cache references" पूर्ण,
	अणु PERF_COUNT_HW_CACHE_MISSES, "cache misses" पूर्ण,
	अणु PERF_COUNT_HW_BRANCH_INSTRUCTIONS, "branch instructions" पूर्ण,
	अणु PERF_COUNT_HW_BRANCH_MISSES, "branch misses" पूर्ण,
पूर्ण;

अटल __init व्योम zhaoxin_arch_events_quirk(व्योम)
अणु
	पूर्णांक bit;

	/* disable event that reported as not present by cpuid */
	क्रम_each_set_bit(bit, x86_pmu.events_mask, ARRAY_SIZE(zx_arch_events_map)) अणु
		zx_pmon_event_map[zx_arch_events_map[bit].id] = 0;
		pr_warn("CPUID marked event: \'%s\' unavailable\n",
			zx_arch_events_map[bit].name);
	पूर्ण
पूर्ण

__init पूर्णांक zhaoxin_pmu_init(व्योम)
अणु
	जोड़ cpuid10_edx edx;
	जोड़ cpuid10_eax eax;
	जोड़ cpuid10_ebx ebx;
	काष्ठा event_स्थिरraपूर्णांक *c;
	अचिन्हित पूर्णांक unused;
	पूर्णांक version;

	pr_info("Welcome to zhaoxin pmu!\n");

	/*
	 * Check whether the Architectural PerfMon supports
	 * hw_event or not.
	 */
	cpuid(10, &eax.full, &ebx.full, &unused, &edx.full);

	अगर (eax.split.mask_length < ARCH_PERFMON_EVENTS_COUNT - 1)
		वापस -ENODEV;

	version = eax.split.version_id;
	अगर (version != 2)
		वापस -ENODEV;

	x86_pmu = zhaoxin_pmu;
	pr_info("Version check pass!\n");

	x86_pmu.version			= version;
	x86_pmu.num_counters		= eax.split.num_counters;
	x86_pmu.cntval_bits		= eax.split.bit_width;
	x86_pmu.cntval_mask		= (1ULL << eax.split.bit_width) - 1;
	x86_pmu.events_maskl		= ebx.full;
	x86_pmu.events_mask_len		= eax.split.mask_length;

	x86_pmu.num_counters_fixed = edx.split.num_counters_fixed;
	x86_add_quirk(zhaoxin_arch_events_quirk);

	चयन (boot_cpu_data.x86) अणु
	हाल 0x06:
		अगर (boot_cpu_data.x86_model == 0x0f || boot_cpu_data.x86_model == 0x19) अणु

			x86_pmu.max_period = x86_pmu.cntval_mask >> 1;

			/* Clearing status works only अगर the global control is enable on zxc. */
			x86_pmu.enabled_ack = 1;

			x86_pmu.event_स्थिरraपूर्णांकs = zxc_event_स्थिरraपूर्णांकs;
			zx_pmon_event_map[PERF_COUNT_HW_INSTRUCTIONS] = 0;
			zx_pmon_event_map[PERF_COUNT_HW_CACHE_REFERENCES] = 0;
			zx_pmon_event_map[PERF_COUNT_HW_CACHE_MISSES] = 0;
			zx_pmon_event_map[PERF_COUNT_HW_BUS_CYCLES] = 0;

			pr_cont("ZXC events, ");
			अवरोध;
		पूर्ण
		वापस -ENODEV;

	हाल 0x07:
		zx_pmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] =
			X86_CONFIG(.event = 0x01, .umask = 0x01, .inv = 0x01, .cmask = 0x01);

		zx_pmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] =
			X86_CONFIG(.event = 0x0f, .umask = 0x04, .inv = 0, .cmask = 0);

		चयन (boot_cpu_data.x86_model) अणु
		हाल 0x1b:
			स_नकल(hw_cache_event_ids, zxd_hw_cache_event_ids,
			       माप(hw_cache_event_ids));

			x86_pmu.event_स्थिरraपूर्णांकs = zxd_event_स्थिरraपूर्णांकs;

			zx_pmon_event_map[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = 0x0700;
			zx_pmon_event_map[PERF_COUNT_HW_BRANCH_MISSES] = 0x0709;

			pr_cont("ZXD events, ");
			अवरोध;
		हाल 0x3b:
			स_नकल(hw_cache_event_ids, zxe_hw_cache_event_ids,
			       माप(hw_cache_event_ids));

			x86_pmu.event_स्थिरraपूर्णांकs = zxd_event_स्थिरraपूर्णांकs;

			zx_pmon_event_map[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = 0x0028;
			zx_pmon_event_map[PERF_COUNT_HW_BRANCH_MISSES] = 0x0029;

			pr_cont("ZXE events, ");
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
		अवरोध;

	शेष:
		वापस -ENODEV;
	पूर्ण

	x86_pmu.पूर्णांकel_ctrl = (1 << (x86_pmu.num_counters)) - 1;
	x86_pmu.पूर्णांकel_ctrl |= ((1LL << x86_pmu.num_counters_fixed)-1) << INTEL_PMC_IDX_FIXED;

	अगर (x86_pmu.event_स्थिरraपूर्णांकs) अणु
		क्रम_each_event_स्थिरraपूर्णांक(c, x86_pmu.event_स्थिरraपूर्णांकs) अणु
			c->idxmsk64 |= (1ULL << x86_pmu.num_counters) - 1;
			c->weight += x86_pmu.num_counters;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

