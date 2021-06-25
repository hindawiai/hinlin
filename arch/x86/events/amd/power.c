<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Perक्रमmance events - AMD Processor Power Reporting Mechanism
 *
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
 *
 * Author: Huang Rui <ray.huang@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश "../perf_event.h"

/* Event code: LSB 8 bits, passed in attr->config any other bit is reserved. */
#घोषणा AMD_POWER_EVENT_MASK		0xFFULL

/*
 * Accumulated घातer status counters.
 */
#घोषणा AMD_POWER_EVENTSEL_PKG		1

/*
 * The ratio of compute unit घातer accumulator sample period to the
 * PTSC period.
 */
अटल अचिन्हित पूर्णांक cpu_pwr_sample_ratio;

/* Maximum accumulated घातer of a compute unit. */
अटल u64 max_cu_acc_घातer;

अटल काष्ठा pmu pmu_class;

/*
 * Accumulated घातer represents the sum of each compute unit's (CU) घातer
 * consumption. On any core of each CU we पढ़ो the total accumulated घातer from
 * MSR_F15H_CU_PWR_ACCUMULATOR. cpu_mask represents CPU bit map of all cores
 * which are picked to measure the घातer क्रम the CUs they beदीर्घ to.
 */
अटल cpumask_t cpu_mask;

अटल व्योम event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 prev_pwr_acc, new_pwr_acc, prev_ptsc, new_ptsc;
	u64 delta, tdelta;

	prev_pwr_acc = hwc->pwr_acc;
	prev_ptsc = hwc->ptsc;
	rdmsrl(MSR_F15H_CU_PWR_ACCUMULATOR, new_pwr_acc);
	rdmsrl(MSR_F15H_PTSC, new_ptsc);

	/*
	 * Calculate the CU घातer consumption over a समय period, the unit of
	 * final value (delta) is micro-Watts. Then add it to the event count.
	 */
	अगर (new_pwr_acc < prev_pwr_acc) अणु
		delta = max_cu_acc_घातer + new_pwr_acc;
		delta -= prev_pwr_acc;
	पूर्ण अन्यथा
		delta = new_pwr_acc - prev_pwr_acc;

	delta *= cpu_pwr_sample_ratio * 1000;
	tdelta = new_ptsc - prev_ptsc;

	करो_भाग(delta, tdelta);
	local64_add(delta, &event->count);
पूर्ण

अटल व्योम __pmu_event_start(काष्ठा perf_event *event)
अणु
	अगर (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		वापस;

	event->hw.state = 0;

	rdmsrl(MSR_F15H_PTSC, event->hw.ptsc);
	rdmsrl(MSR_F15H_CU_PWR_ACCUMULATOR, event->hw.pwr_acc);
पूर्ण

अटल व्योम pmu_event_start(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	__pmu_event_start(event);
पूर्ण

अटल व्योम pmu_event_stop(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	/* Mark event as deactivated and stopped. */
	अगर (!(hwc->state & PERF_HES_STOPPED))
		hwc->state |= PERF_HES_STOPPED;

	/* Check अगर software counter update is necessary. */
	अगर ((mode & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) अणु
		/*
		 * Drain the reमुख्यing delta count out of an event
		 * that we are disabling:
		 */
		event_update(event);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल पूर्णांक pmu_event_add(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	अगर (mode & PERF_EF_START)
		__pmu_event_start(event);

	वापस 0;
पूर्ण

अटल व्योम pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	pmu_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक pmu_event_init(काष्ठा perf_event *event)
अणु
	u64 cfg = event->attr.config & AMD_POWER_EVENT_MASK;

	/* Only look at AMD घातer events. */
	अगर (event->attr.type != pmu_class.type)
		वापस -ENOENT;

	/* Unsupported modes and filters. */
	अगर (event->attr.sample_period)
		वापस -EINVAL;

	अगर (cfg != AMD_POWER_EVENTSEL_PKG)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम pmu_event_पढ़ो(काष्ठा perf_event *event)
अणु
	event_update(event);
पूर्ण

अटल sमाप_प्रकार
get_attr_cpumask(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &cpu_mask);
पूर्ण

अटल DEVICE_ATTR(cpumask, S_IRUGO, get_attr_cpumask, शून्य);

अटल काष्ठा attribute *pmu_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group pmu_attr_group = अणु
	.attrs = pmu_attrs,
पूर्ण;

/*
 * Currently it only supports to report the घातer of each
 * processor/package.
 */
EVENT_ATTR_STR(घातer-pkg, घातer_pkg, "event=0x01");

EVENT_ATTR_STR(घातer-pkg.unit, घातer_pkg_unit, "mWatts");

/* Convert the count from micro-Watts to milli-Watts. */
EVENT_ATTR_STR(घातer-pkg.scale, घातer_pkg_scale, "1.000000e-3");

अटल काष्ठा attribute *events_attr[] = अणु
	EVENT_PTR(घातer_pkg),
	EVENT_PTR(घातer_pkg_unit),
	EVENT_PTR(घातer_pkg_scale),
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group pmu_events_group = अणु
	.name	= "events",
	.attrs	= events_attr,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-7");

अटल काष्ठा attribute *क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group pmu_क्रमmat_group = अणु
	.name	= "format",
	.attrs	= क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_groups[] = अणु
	&pmu_attr_group,
	&pmu_क्रमmat_group,
	&pmu_events_group,
	शून्य,
पूर्ण;

अटल काष्ठा pmu pmu_class = अणु
	.attr_groups	= attr_groups,
	/* प्रणाली-wide only */
	.task_ctx_nr	= perf_invalid_context,
	.event_init	= pmu_event_init,
	.add		= pmu_event_add,
	.del		= pmu_event_del,
	.start		= pmu_event_start,
	.stop		= pmu_event_stop,
	.पढ़ो		= pmu_event_पढ़ो,
	.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
पूर्ण;

अटल पूर्णांक घातer_cpu_निकास(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक target;

	अगर (!cpumask_test_and_clear_cpu(cpu, &cpu_mask))
		वापस 0;

	/*
	 * Find a new CPU on the same compute unit, अगर was set in cpumask
	 * and still some CPUs on compute unit. Then migrate event and
	 * context to new CPU.
	 */
	target = cpumask_any_but(topology_sibling_cpumask(cpu), cpu);
	अगर (target < nr_cpumask_bits) अणु
		cpumask_set_cpu(target, &cpu_mask);
		perf_pmu_migrate_context(&pmu_class, cpu, target);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक घातer_cpu_init(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक target;

	/*
	 * 1) If any CPU is set at cpu_mask in the same compute unit, करो
	 * nothing.
	 * 2) If no CPU is set at cpu_mask in the same compute unit,
	 * set current ONLINE CPU.
	 *
	 * Note: अगर there is a CPU aside of the new one alपढ़ोy in the
	 * sibling mask, then it is also in cpu_mask.
	 */
	target = cpumask_any_but(topology_sibling_cpumask(cpu), cpu);
	अगर (target >= nr_cpumask_bits)
		cpumask_set_cpu(cpu, &cpu_mask);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id cpu_match[] = अणु
	X86_MATCH_VENDOR_FAM(AMD, 0x15, शून्य),
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init amd_घातer_pmu_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!x86_match_cpu(cpu_match))
		वापस -ENODEV;

	अगर (!boot_cpu_has(X86_FEATURE_ACC_POWER))
		वापस -ENODEV;

	cpu_pwr_sample_ratio = cpuid_ecx(0x80000007);

	अगर (rdmsrl_safe(MSR_F15H_CU_MAX_PWR_ACCUMULATOR, &max_cu_acc_घातer)) अणु
		pr_err("Failed to read max compute unit power accumulator MSR\n");
		वापस -ENODEV;
	पूर्ण


	cpuhp_setup_state(CPUHP_AP_PERF_X86_AMD_POWER_ONLINE,
			  "perf/x86/amd/power:online",
			  घातer_cpu_init, घातer_cpu_निकास);

	ret = perf_pmu_रेजिस्टर(&pmu_class, "power", -1);
	अगर (WARN_ON(ret)) अणु
		pr_warn("AMD Power PMU registration failed\n");
		वापस ret;
	पूर्ण

	pr_info("AMD Power PMU detected\n");
	वापस ret;
पूर्ण
module_init(amd_घातer_pmu_init);

अटल व्योम __निकास amd_घातer_pmu_निकास(व्योम)
अणु
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_PERF_X86_AMD_POWER_ONLINE);
	perf_pmu_unरेजिस्टर(&pmu_class);
पूर्ण
module_निकास(amd_घातer_pmu_निकास);

MODULE_AUTHOR("Huang Rui <ray.huang@amd.com>");
MODULE_DESCRIPTION("AMD Processor Power Reporting Mechanism");
MODULE_LICENSE("GPL v2");
