<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/perf_event.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/nospec.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश "probe.h"

क्रमागत perf_msr_id अणु
	PERF_MSR_TSC			= 0,
	PERF_MSR_APERF			= 1,
	PERF_MSR_MPERF			= 2,
	PERF_MSR_PPERF			= 3,
	PERF_MSR_SMI			= 4,
	PERF_MSR_PTSC			= 5,
	PERF_MSR_IRPERF			= 6,
	PERF_MSR_THERM			= 7,
	PERF_MSR_EVENT_MAX,
पूर्ण;

अटल bool test_aperfmperf(पूर्णांक idx, व्योम *data)
अणु
	वापस boot_cpu_has(X86_FEATURE_APERFMPERF);
पूर्ण

अटल bool test_ptsc(पूर्णांक idx, व्योम *data)
अणु
	वापस boot_cpu_has(X86_FEATURE_PTSC);
पूर्ण

अटल bool test_irperf(पूर्णांक idx, व्योम *data)
अणु
	वापस boot_cpu_has(X86_FEATURE_IRPERF);
पूर्ण

अटल bool test_therm_status(पूर्णांक idx, व्योम *data)
अणु
	वापस boot_cpu_has(X86_FEATURE_DTHERM);
पूर्ण

अटल bool test_पूर्णांकel(पूर्णांक idx, व्योम *data)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL ||
	    boot_cpu_data.x86 != 6)
		वापस false;

	चयन (boot_cpu_data.x86_model) अणु
	हाल INTEL_FAM6_NEHALEM:
	हाल INTEL_FAM6_NEHALEM_G:
	हाल INTEL_FAM6_NEHALEM_EP:
	हाल INTEL_FAM6_NEHALEM_EX:

	हाल INTEL_FAM6_WESTMERE:
	हाल INTEL_FAM6_WESTMERE_EP:
	हाल INTEL_FAM6_WESTMERE_EX:

	हाल INTEL_FAM6_SANDYBRIDGE:
	हाल INTEL_FAM6_SANDYBRIDGE_X:

	हाल INTEL_FAM6_IVYBRIDGE:
	हाल INTEL_FAM6_IVYBRIDGE_X:

	हाल INTEL_FAM6_HASWELL:
	हाल INTEL_FAM6_HASWELL_X:
	हाल INTEL_FAM6_HASWELL_L:
	हाल INTEL_FAM6_HASWELL_G:

	हाल INTEL_FAM6_BROADWELL:
	हाल INTEL_FAM6_BROADWELL_D:
	हाल INTEL_FAM6_BROADWELL_G:
	हाल INTEL_FAM6_BROADWELL_X:

	हाल INTEL_FAM6_ATOM_SILVERMONT:
	हाल INTEL_FAM6_ATOM_SILVERMONT_D:
	हाल INTEL_FAM6_ATOM_AIRMONT:

	हाल INTEL_FAM6_ATOM_GOLDMONT:
	हाल INTEL_FAM6_ATOM_GOLDMONT_D:
	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
	हाल INTEL_FAM6_ATOM_TREMONT_D:
	हाल INTEL_FAM6_ATOM_TREMONT:
	हाल INTEL_FAM6_ATOM_TREMONT_L:

	हाल INTEL_FAM6_XEON_PHI_KNL:
	हाल INTEL_FAM6_XEON_PHI_KNM:
		अगर (idx == PERF_MSR_SMI)
			वापस true;
		अवरोध;

	हाल INTEL_FAM6_SKYLAKE_L:
	हाल INTEL_FAM6_SKYLAKE:
	हाल INTEL_FAM6_SKYLAKE_X:
	हाल INTEL_FAM6_KABYLAKE_L:
	हाल INTEL_FAM6_KABYLAKE:
	हाल INTEL_FAM6_COMETLAKE_L:
	हाल INTEL_FAM6_COMETLAKE:
	हाल INTEL_FAM6_ICELAKE_L:
	हाल INTEL_FAM6_ICELAKE:
	हाल INTEL_FAM6_ICELAKE_X:
	हाल INTEL_FAM6_ICELAKE_D:
	हाल INTEL_FAM6_TIGERLAKE_L:
	हाल INTEL_FAM6_TIGERLAKE:
	हाल INTEL_FAM6_ROCKETLAKE:
	हाल INTEL_FAM6_ALDERLAKE:
	हाल INTEL_FAM6_ALDERLAKE_L:
		अगर (idx == PERF_MSR_SMI || idx == PERF_MSR_PPERF)
			वापस true;
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

PMU_EVENT_ATTR_STRING(tsc,				attr_tsc,		"event=0x00"	);
PMU_EVENT_ATTR_STRING(aperf,				attr_aperf,		"event=0x01"	);
PMU_EVENT_ATTR_STRING(mperf,				attr_mperf,		"event=0x02"	);
PMU_EVENT_ATTR_STRING(pperf,				attr_pperf,		"event=0x03"	);
PMU_EVENT_ATTR_STRING(smi,				attr_smi,		"event=0x04"	);
PMU_EVENT_ATTR_STRING(ptsc,				attr_ptsc,		"event=0x05"	);
PMU_EVENT_ATTR_STRING(irperf,				attr_irperf,		"event=0x06"	);
PMU_EVENT_ATTR_STRING(cpu_thermal_margin,		attr_therm,		"event=0x07"	);
PMU_EVENT_ATTR_STRING(cpu_thermal_margin.snapshot,	attr_therm_snap,	"1"		);
PMU_EVENT_ATTR_STRING(cpu_thermal_margin.unit,		attr_therm_unit,	"C"		);

अटल अचिन्हित दीर्घ msr_mask;

PMU_EVENT_GROUP(events, aperf);
PMU_EVENT_GROUP(events, mperf);
PMU_EVENT_GROUP(events, pperf);
PMU_EVENT_GROUP(events, smi);
PMU_EVENT_GROUP(events, ptsc);
PMU_EVENT_GROUP(events, irperf);

अटल काष्ठा attribute *attrs_therm[] = अणु
	&attr_therm.attr.attr,
	&attr_therm_snap.attr.attr,
	&attr_therm_unit.attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group group_therm = अणु
	.name  = "events",
	.attrs = attrs_therm,
पूर्ण;

अटल काष्ठा perf_msr msr[] = अणु
	[PERF_MSR_TSC]		= अणु .no_check = true,								पूर्ण,
	[PERF_MSR_APERF]	= अणु MSR_IA32_APERF,		&group_aperf,		test_aperfmperf,	पूर्ण,
	[PERF_MSR_MPERF]	= अणु MSR_IA32_MPERF,		&group_mperf,		test_aperfmperf,	पूर्ण,
	[PERF_MSR_PPERF]	= अणु MSR_PPERF,			&group_pperf,		test_पूर्णांकel,		पूर्ण,
	[PERF_MSR_SMI]		= अणु MSR_SMI_COUNT,		&group_smi,		test_पूर्णांकel,		पूर्ण,
	[PERF_MSR_PTSC]		= अणु MSR_F15H_PTSC,		&group_ptsc,		test_ptsc,		पूर्ण,
	[PERF_MSR_IRPERF]	= अणु MSR_F17H_IRPERF,		&group_irperf,		test_irperf,		पूर्ण,
	[PERF_MSR_THERM]	= अणु MSR_IA32_THERM_STATUS,	&group_therm,		test_therm_status,	पूर्ण,
पूर्ण;

अटल काष्ठा attribute *events_attrs[] = अणु
	&attr_tsc.attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group events_attr_group = अणु
	.name = "events",
	.attrs = events_attrs,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-63");
अटल काष्ठा attribute *क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_groups[] = अणु
	&events_attr_group,
	&क्रमmat_attr_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_update[] = अणु
	&group_aperf,
	&group_mperf,
	&group_pperf,
	&group_smi,
	&group_ptsc,
	&group_irperf,
	&group_therm,
	शून्य,
पूर्ण;

अटल पूर्णांक msr_event_init(काष्ठा perf_event *event)
अणु
	u64 cfg = event->attr.config;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* unsupported modes and filters */
	अगर (event->attr.sample_period) /* no sampling */
		वापस -EINVAL;

	अगर (cfg >= PERF_MSR_EVENT_MAX)
		वापस -EINVAL;

	cfg = array_index_nospec((अचिन्हित दीर्घ)cfg, PERF_MSR_EVENT_MAX);

	अगर (!(msr_mask & (1 << cfg)))
		वापस -EINVAL;

	event->hw.idx		= -1;
	event->hw.event_base	= msr[cfg].msr;
	event->hw.config	= cfg;

	वापस 0;
पूर्ण

अटल अंतरभूत u64 msr_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	u64 now;

	अगर (event->hw.event_base)
		rdmsrl(event->hw.event_base, now);
	अन्यथा
		now = rdtsc_ordered();

	वापस now;
पूर्ण

अटल व्योम msr_event_update(काष्ठा perf_event *event)
अणु
	u64 prev, now;
	s64 delta;

	/* Careful, an NMI might modअगरy the previous event value: */
again:
	prev = local64_पढ़ो(&event->hw.prev_count);
	now = msr_पढ़ो_counter(event);

	अगर (local64_cmpxchg(&event->hw.prev_count, prev, now) != prev)
		जाओ again;

	delta = now - prev;
	अगर (unlikely(event->hw.event_base == MSR_SMI_COUNT)) अणु
		delta = sign_extend64(delta, 31);
		local64_add(delta, &event->count);
	पूर्ण अन्यथा अगर (unlikely(event->hw.event_base == MSR_IA32_THERM_STATUS)) अणु
		/* If valid, extract digital पढ़ोout, otherwise set to -1: */
		now = now & (1ULL << 31) ? (now >> 16) & 0x3f :  -1;
		local64_set(&event->count, now);
	पूर्ण अन्यथा अणु
		local64_add(delta, &event->count);
	पूर्ण
पूर्ण

अटल व्योम msr_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	u64 now = msr_पढ़ो_counter(event);

	local64_set(&event->hw.prev_count, now);
पूर्ण

अटल व्योम msr_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	msr_event_update(event);
पूर्ण

अटल व्योम msr_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	msr_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक msr_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_START)
		msr_event_start(event, flags);

	वापस 0;
पूर्ण

अटल काष्ठा pmu pmu_msr = अणु
	.task_ctx_nr	= perf_sw_context,
	.attr_groups	= attr_groups,
	.event_init	= msr_event_init,
	.add		= msr_event_add,
	.del		= msr_event_del,
	.start		= msr_event_start,
	.stop		= msr_event_stop,
	.पढ़ो		= msr_event_update,
	.capabilities	= PERF_PMU_CAP_NO_INTERRUPT | PERF_PMU_CAP_NO_EXCLUDE,
	.attr_update	= attr_update,
पूर्ण;

अटल पूर्णांक __init msr_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_TSC)) अणु
		pr_cont("no MSR PMU driver.\n");
		वापस 0;
	पूर्ण

	msr_mask = perf_msr_probe(msr, PERF_MSR_EVENT_MAX, true, शून्य);

	perf_pmu_रेजिस्टर(&pmu_msr, "msr", -1);

	वापस 0;
पूर्ण
device_initcall(msr_init);
