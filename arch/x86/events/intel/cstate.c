<शैली गुरु>
/*
 * Support cstate residency counters
 *
 * Copyright (C) 2015, Intel Corp.
 * Author: Kan Liang (kan.liang@पूर्णांकel.com)
 *
 * This library is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License क्रम more details.
 *
 */

/*
 * This file export cstate related मुक्त running (पढ़ो-only) counters
 * क्रम perf. These counters may be use simultaneously by other tools,
 * such as turbostat. However, it still make sense to implement them
 * in perf. Because we can conveniently collect them together with
 * other events, and allow to use them from tools without special MSR
 * access code.
 *
 * The events only support प्रणाली-wide mode counting. There is no
 * sampling support because it is not supported by the hardware.
 *
 * According to counters' scope and category, two PMUs are रेजिस्टरed
 * with the perf_event core subप्रणाली.
 *  - 'cstate_core': The counter is available क्रम each physical core.
 *    The counters include CORE_C*_RESIDENCY.
 *  - 'cstate_pkg': The counter is available क्रम each physical package.
 *    The counters include PKG_C*_RESIDENCY.
 *
 * All of these counters are specअगरied in the Intelतऍ 64 and IA-32
 * Architectures Software Developer.s Manual Vol3b.
 *
 * Model specअगरic counters:
 *	MSR_CORE_C1_RES: CORE C1 Residency Counter
 *			 perf code: 0x00
 *			 Available model: SLM,AMT,GLM,CNL,TNT,ADL
 *			 Scope: Core (each processor core has a MSR)
 *	MSR_CORE_C3_RESIDENCY: CORE C3 Residency Counter
 *			       perf code: 0x01
 *			       Available model: NHM,WSM,SNB,IVB,HSW,BDW,SKL,GLM,
 *						CNL,KBL,CML,TNT
 *			       Scope: Core
 *	MSR_CORE_C6_RESIDENCY: CORE C6 Residency Counter
 *			       perf code: 0x02
 *			       Available model: SLM,AMT,NHM,WSM,SNB,IVB,HSW,BDW,
 *						SKL,KNL,GLM,CNL,KBL,CML,ICL,TGL,
 *						TNT,RKL,ADL
 *			       Scope: Core
 *	MSR_CORE_C7_RESIDENCY: CORE C7 Residency Counter
 *			       perf code: 0x03
 *			       Available model: SNB,IVB,HSW,BDW,SKL,CNL,KBL,CML,
 *						ICL,TGL,RKL,ADL
 *			       Scope: Core
 *	MSR_PKG_C2_RESIDENCY:  Package C2 Residency Counter.
 *			       perf code: 0x00
 *			       Available model: SNB,IVB,HSW,BDW,SKL,KNL,GLM,CNL,
 *						KBL,CML,ICL,TGL,TNT,RKL,ADL
 *			       Scope: Package (physical package)
 *	MSR_PKG_C3_RESIDENCY:  Package C3 Residency Counter.
 *			       perf code: 0x01
 *			       Available model: NHM,WSM,SNB,IVB,HSW,BDW,SKL,KNL,
 *						GLM,CNL,KBL,CML,ICL,TGL,TNT,RKL,
 *						ADL
 *			       Scope: Package (physical package)
 *	MSR_PKG_C6_RESIDENCY:  Package C6 Residency Counter.
 *			       perf code: 0x02
 *			       Available model: SLM,AMT,NHM,WSM,SNB,IVB,HSW,BDW,
 *						SKL,KNL,GLM,CNL,KBL,CML,ICL,TGL,
 *						TNT,RKL,ADL
 *			       Scope: Package (physical package)
 *	MSR_PKG_C7_RESIDENCY:  Package C7 Residency Counter.
 *			       perf code: 0x03
 *			       Available model: NHM,WSM,SNB,IVB,HSW,BDW,SKL,CNL,
 *						KBL,CML,ICL,TGL,RKL,ADL
 *			       Scope: Package (physical package)
 *	MSR_PKG_C8_RESIDENCY:  Package C8 Residency Counter.
 *			       perf code: 0x04
 *			       Available model: HSW ULT,KBL,CNL,CML,ICL,TGL,RKL,
 *						ADL
 *			       Scope: Package (physical package)
 *	MSR_PKG_C9_RESIDENCY:  Package C9 Residency Counter.
 *			       perf code: 0x05
 *			       Available model: HSW ULT,KBL,CNL,CML,ICL,TGL,RKL,
 *						ADL
 *			       Scope: Package (physical package)
 *	MSR_PKG_C10_RESIDENCY: Package C10 Residency Counter.
 *			       perf code: 0x06
 *			       Available model: HSW ULT,KBL,GLM,CNL,CML,ICL,TGL,
 *						TNT,RKL,ADL
 *			       Scope: Package (physical package)
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/nospec.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश "../perf_event.h"
#समावेश "../probe.h"

MODULE_LICENSE("GPL");

#घोषणा DEFINE_CSTATE_FORMAT_ATTR(_var, _name, _क्रमmat)		\
अटल sमाप_प्रकार __cstate_##_var##_show(काष्ठा device *dev,	\
				काष्ठा device_attribute *attr,	\
				अक्षर *page)			\
अणु								\
	BUILD_BUG_ON(माप(_क्रमmat) >= PAGE_SIZE);		\
	वापस प्र_लिखो(page, _क्रमmat "\n");			\
पूर्ण								\
अटल काष्ठा device_attribute क्रमmat_attr_##_var =		\
	__ATTR(_name, 0444, __cstate_##_var##_show, शून्य)

अटल sमाप_प्रकार cstate_get_attr_cpumask(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf);

/* Model -> events mapping */
काष्ठा cstate_model अणु
	अचिन्हित दीर्घ		core_events;
	अचिन्हित दीर्घ		pkg_events;
	अचिन्हित दीर्घ		quirks;
पूर्ण;

/* Quirk flags */
#घोषणा SLM_PKG_C6_USE_C7_MSR	(1UL << 0)
#घोषणा KNL_CORE_C6_MSR		(1UL << 1)

काष्ठा perf_cstate_msr अणु
	u64	msr;
	काष्ठा	perf_pmu_events_attr *attr;
पूर्ण;


/* cstate_core PMU */
अटल काष्ठा pmu cstate_core_pmu;
अटल bool has_cstate_core;

क्रमागत perf_cstate_core_events अणु
	PERF_CSTATE_CORE_C1_RES = 0,
	PERF_CSTATE_CORE_C3_RES,
	PERF_CSTATE_CORE_C6_RES,
	PERF_CSTATE_CORE_C7_RES,

	PERF_CSTATE_CORE_EVENT_MAX,
पूर्ण;

PMU_EVENT_ATTR_STRING(c1-residency, attr_cstate_core_c1, "event=0x00");
PMU_EVENT_ATTR_STRING(c3-residency, attr_cstate_core_c3, "event=0x01");
PMU_EVENT_ATTR_STRING(c6-residency, attr_cstate_core_c6, "event=0x02");
PMU_EVENT_ATTR_STRING(c7-residency, attr_cstate_core_c7, "event=0x03");

अटल अचिन्हित दीर्घ core_msr_mask;

PMU_EVENT_GROUP(events, cstate_core_c1);
PMU_EVENT_GROUP(events, cstate_core_c3);
PMU_EVENT_GROUP(events, cstate_core_c6);
PMU_EVENT_GROUP(events, cstate_core_c7);

अटल bool test_msr(पूर्णांक idx, व्योम *data)
अणु
	वापस test_bit(idx, (अचिन्हित दीर्घ *) data);
पूर्ण

अटल काष्ठा perf_msr core_msr[] = अणु
	[PERF_CSTATE_CORE_C1_RES] = अणु MSR_CORE_C1_RES,		&group_cstate_core_c1,	test_msr पूर्ण,
	[PERF_CSTATE_CORE_C3_RES] = अणु MSR_CORE_C3_RESIDENCY,	&group_cstate_core_c3,	test_msr पूर्ण,
	[PERF_CSTATE_CORE_C6_RES] = अणु MSR_CORE_C6_RESIDENCY,	&group_cstate_core_c6,	test_msr पूर्ण,
	[PERF_CSTATE_CORE_C7_RES] = अणु MSR_CORE_C7_RESIDENCY,	&group_cstate_core_c7,	test_msr पूर्ण,
पूर्ण;

अटल काष्ठा attribute *attrs_empty[] = अणु
	शून्य,
पूर्ण;

/*
 * There are no शेष events, but we need to create
 * "events" group (with empty attrs) beक्रमe updating
 * it with detected events.
 */
अटल काष्ठा attribute_group core_events_attr_group = अणु
	.name = "events",
	.attrs = attrs_empty,
पूर्ण;

DEFINE_CSTATE_FORMAT_ATTR(core_event, event, "config:0-63");
अटल काष्ठा attribute *core_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_core_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group core_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = core_क्रमmat_attrs,
पूर्ण;

अटल cpumask_t cstate_core_cpu_mask;
अटल DEVICE_ATTR(cpumask, S_IRUGO, cstate_get_attr_cpumask, शून्य);

अटल काष्ठा attribute *cstate_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cpumask_attr_group = अणु
	.attrs = cstate_cpumask_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *core_attr_groups[] = अणु
	&core_events_attr_group,
	&core_क्रमmat_attr_group,
	&cpumask_attr_group,
	शून्य,
पूर्ण;

/* cstate_pkg PMU */
अटल काष्ठा pmu cstate_pkg_pmu;
अटल bool has_cstate_pkg;

क्रमागत perf_cstate_pkg_events अणु
	PERF_CSTATE_PKG_C2_RES = 0,
	PERF_CSTATE_PKG_C3_RES,
	PERF_CSTATE_PKG_C6_RES,
	PERF_CSTATE_PKG_C7_RES,
	PERF_CSTATE_PKG_C8_RES,
	PERF_CSTATE_PKG_C9_RES,
	PERF_CSTATE_PKG_C10_RES,

	PERF_CSTATE_PKG_EVENT_MAX,
पूर्ण;

PMU_EVENT_ATTR_STRING(c2-residency,  attr_cstate_pkg_c2,  "event=0x00");
PMU_EVENT_ATTR_STRING(c3-residency,  attr_cstate_pkg_c3,  "event=0x01");
PMU_EVENT_ATTR_STRING(c6-residency,  attr_cstate_pkg_c6,  "event=0x02");
PMU_EVENT_ATTR_STRING(c7-residency,  attr_cstate_pkg_c7,  "event=0x03");
PMU_EVENT_ATTR_STRING(c8-residency,  attr_cstate_pkg_c8,  "event=0x04");
PMU_EVENT_ATTR_STRING(c9-residency,  attr_cstate_pkg_c9,  "event=0x05");
PMU_EVENT_ATTR_STRING(c10-residency, attr_cstate_pkg_c10, "event=0x06");

अटल अचिन्हित दीर्घ pkg_msr_mask;

PMU_EVENT_GROUP(events, cstate_pkg_c2);
PMU_EVENT_GROUP(events, cstate_pkg_c3);
PMU_EVENT_GROUP(events, cstate_pkg_c6);
PMU_EVENT_GROUP(events, cstate_pkg_c7);
PMU_EVENT_GROUP(events, cstate_pkg_c8);
PMU_EVENT_GROUP(events, cstate_pkg_c9);
PMU_EVENT_GROUP(events, cstate_pkg_c10);

अटल काष्ठा perf_msr pkg_msr[] = अणु
	[PERF_CSTATE_PKG_C2_RES]  = अणु MSR_PKG_C2_RESIDENCY,	&group_cstate_pkg_c2,	test_msr पूर्ण,
	[PERF_CSTATE_PKG_C3_RES]  = अणु MSR_PKG_C3_RESIDENCY,	&group_cstate_pkg_c3,	test_msr पूर्ण,
	[PERF_CSTATE_PKG_C6_RES]  = अणु MSR_PKG_C6_RESIDENCY,	&group_cstate_pkg_c6,	test_msr पूर्ण,
	[PERF_CSTATE_PKG_C7_RES]  = अणु MSR_PKG_C7_RESIDENCY,	&group_cstate_pkg_c7,	test_msr पूर्ण,
	[PERF_CSTATE_PKG_C8_RES]  = अणु MSR_PKG_C8_RESIDENCY,	&group_cstate_pkg_c8,	test_msr पूर्ण,
	[PERF_CSTATE_PKG_C9_RES]  = अणु MSR_PKG_C9_RESIDENCY,	&group_cstate_pkg_c9,	test_msr पूर्ण,
	[PERF_CSTATE_PKG_C10_RES] = अणु MSR_PKG_C10_RESIDENCY,	&group_cstate_pkg_c10,	test_msr पूर्ण,
पूर्ण;

अटल काष्ठा attribute_group pkg_events_attr_group = अणु
	.name = "events",
	.attrs = attrs_empty,
पूर्ण;

DEFINE_CSTATE_FORMAT_ATTR(pkg_event, event, "config:0-63");
अटल काष्ठा attribute *pkg_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_pkg_event.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group pkg_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = pkg_क्रमmat_attrs,
पूर्ण;

अटल cpumask_t cstate_pkg_cpu_mask;

अटल स्थिर काष्ठा attribute_group *pkg_attr_groups[] = अणु
	&pkg_events_attr_group,
	&pkg_क्रमmat_attr_group,
	&cpumask_attr_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार cstate_get_attr_cpumask(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);

	अगर (pmu == &cstate_core_pmu)
		वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &cstate_core_cpu_mask);
	अन्यथा अगर (pmu == &cstate_pkg_pmu)
		वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &cstate_pkg_cpu_mask);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक cstate_pmu_event_init(काष्ठा perf_event *event)
अणु
	u64 cfg = event->attr.config;
	पूर्णांक cpu;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* unsupported modes and filters */
	अगर (event->attr.sample_period) /* no sampling */
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	अगर (event->pmu == &cstate_core_pmu) अणु
		अगर (cfg >= PERF_CSTATE_CORE_EVENT_MAX)
			वापस -EINVAL;
		cfg = array_index_nospec((अचिन्हित दीर्घ)cfg, PERF_CSTATE_CORE_EVENT_MAX);
		अगर (!(core_msr_mask & (1 << cfg)))
			वापस -EINVAL;
		event->hw.event_base = core_msr[cfg].msr;
		cpu = cpumask_any_and(&cstate_core_cpu_mask,
				      topology_sibling_cpumask(event->cpu));
	पूर्ण अन्यथा अगर (event->pmu == &cstate_pkg_pmu) अणु
		अगर (cfg >= PERF_CSTATE_PKG_EVENT_MAX)
			वापस -EINVAL;
		cfg = array_index_nospec((अचिन्हित दीर्घ)cfg, PERF_CSTATE_PKG_EVENT_MAX);
		अगर (!(pkg_msr_mask & (1 << cfg)))
			वापस -EINVAL;
		event->hw.event_base = pkg_msr[cfg].msr;
		cpu = cpumask_any_and(&cstate_pkg_cpu_mask,
				      topology_die_cpumask(event->cpu));
	पूर्ण अन्यथा अणु
		वापस -ENOENT;
	पूर्ण

	अगर (cpu >= nr_cpu_ids)
		वापस -ENODEV;

	event->cpu = cpu;
	event->hw.config = cfg;
	event->hw.idx = -1;
	वापस 0;
पूर्ण

अटल अंतरभूत u64 cstate_pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	u64 val;

	rdmsrl(event->hw.event_base, val);
	वापस val;
पूर्ण

अटल व्योम cstate_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 prev_raw_count, new_raw_count;

again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	new_raw_count = cstate_pmu_पढ़ो_counter(event);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			    new_raw_count) != prev_raw_count)
		जाओ again;

	local64_add(new_raw_count - prev_raw_count, &event->count);
पूर्ण

अटल व्योम cstate_pmu_event_start(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	local64_set(&event->hw.prev_count, cstate_pmu_पढ़ो_counter(event));
पूर्ण

अटल व्योम cstate_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	cstate_pmu_event_update(event);
पूर्ण

अटल व्योम cstate_pmu_event_del(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	cstate_pmu_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक cstate_pmu_event_add(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	अगर (mode & PERF_EF_START)
		cstate_pmu_event_start(event, mode);

	वापस 0;
पूर्ण

/*
 * Check अगर निकासing cpu is the designated पढ़ोer. If so migrate the
 * events when there is a valid target available
 */
अटल पूर्णांक cstate_cpu_निकास(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक target;

	अगर (has_cstate_core &&
	    cpumask_test_and_clear_cpu(cpu, &cstate_core_cpu_mask)) अणु

		target = cpumask_any_but(topology_sibling_cpumask(cpu), cpu);
		/* Migrate events अगर there is a valid target */
		अगर (target < nr_cpu_ids) अणु
			cpumask_set_cpu(target, &cstate_core_cpu_mask);
			perf_pmu_migrate_context(&cstate_core_pmu, cpu, target);
		पूर्ण
	पूर्ण

	अगर (has_cstate_pkg &&
	    cpumask_test_and_clear_cpu(cpu, &cstate_pkg_cpu_mask)) अणु

		target = cpumask_any_but(topology_die_cpumask(cpu), cpu);
		/* Migrate events अगर there is a valid target */
		अगर (target < nr_cpu_ids) अणु
			cpumask_set_cpu(target, &cstate_pkg_cpu_mask);
			perf_pmu_migrate_context(&cstate_pkg_pmu, cpu, target);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cstate_cpu_init(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक target;

	/*
	 * If this is the first online thपढ़ो of that core, set it in
	 * the core cpu mask as the designated पढ़ोer.
	 */
	target = cpumask_any_and(&cstate_core_cpu_mask,
				 topology_sibling_cpumask(cpu));

	अगर (has_cstate_core && target >= nr_cpu_ids)
		cpumask_set_cpu(cpu, &cstate_core_cpu_mask);

	/*
	 * If this is the first online thपढ़ो of that package, set it
	 * in the package cpu mask as the designated पढ़ोer.
	 */
	target = cpumask_any_and(&cstate_pkg_cpu_mask,
				 topology_die_cpumask(cpu));
	अगर (has_cstate_pkg && target >= nr_cpu_ids)
		cpumask_set_cpu(cpu, &cstate_pkg_cpu_mask);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group *core_attr_update[] = अणु
	&group_cstate_core_c1,
	&group_cstate_core_c3,
	&group_cstate_core_c6,
	&group_cstate_core_c7,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pkg_attr_update[] = अणु
	&group_cstate_pkg_c2,
	&group_cstate_pkg_c3,
	&group_cstate_pkg_c6,
	&group_cstate_pkg_c7,
	&group_cstate_pkg_c8,
	&group_cstate_pkg_c9,
	&group_cstate_pkg_c10,
	शून्य,
पूर्ण;

अटल काष्ठा pmu cstate_core_pmu = अणु
	.attr_groups	= core_attr_groups,
	.attr_update	= core_attr_update,
	.name		= "cstate_core",
	.task_ctx_nr	= perf_invalid_context,
	.event_init	= cstate_pmu_event_init,
	.add		= cstate_pmu_event_add,
	.del		= cstate_pmu_event_del,
	.start		= cstate_pmu_event_start,
	.stop		= cstate_pmu_event_stop,
	.पढ़ो		= cstate_pmu_event_update,
	.capabilities	= PERF_PMU_CAP_NO_INTERRUPT | PERF_PMU_CAP_NO_EXCLUDE,
	.module		= THIS_MODULE,
पूर्ण;

अटल काष्ठा pmu cstate_pkg_pmu = अणु
	.attr_groups	= pkg_attr_groups,
	.attr_update	= pkg_attr_update,
	.name		= "cstate_pkg",
	.task_ctx_nr	= perf_invalid_context,
	.event_init	= cstate_pmu_event_init,
	.add		= cstate_pmu_event_add,
	.del		= cstate_pmu_event_del,
	.start		= cstate_pmu_event_start,
	.stop		= cstate_pmu_event_stop,
	.पढ़ो		= cstate_pmu_event_update,
	.capabilities	= PERF_PMU_CAP_NO_INTERRUPT | PERF_PMU_CAP_NO_EXCLUDE,
	.module		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा cstate_model nhm_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C3_RES) |
				  BIT(PERF_CSTATE_CORE_C6_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C3_RES) |
				  BIT(PERF_CSTATE_PKG_C6_RES) |
				  BIT(PERF_CSTATE_PKG_C7_RES),
पूर्ण;

अटल स्थिर काष्ठा cstate_model snb_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C3_RES) |
				  BIT(PERF_CSTATE_CORE_C6_RES) |
				  BIT(PERF_CSTATE_CORE_C7_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C2_RES) |
				  BIT(PERF_CSTATE_PKG_C3_RES) |
				  BIT(PERF_CSTATE_PKG_C6_RES) |
				  BIT(PERF_CSTATE_PKG_C7_RES),
पूर्ण;

अटल स्थिर काष्ठा cstate_model hswult_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C3_RES) |
				  BIT(PERF_CSTATE_CORE_C6_RES) |
				  BIT(PERF_CSTATE_CORE_C7_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C2_RES) |
				  BIT(PERF_CSTATE_PKG_C3_RES) |
				  BIT(PERF_CSTATE_PKG_C6_RES) |
				  BIT(PERF_CSTATE_PKG_C7_RES) |
				  BIT(PERF_CSTATE_PKG_C8_RES) |
				  BIT(PERF_CSTATE_PKG_C9_RES) |
				  BIT(PERF_CSTATE_PKG_C10_RES),
पूर्ण;

अटल स्थिर काष्ठा cstate_model cnl_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C1_RES) |
				  BIT(PERF_CSTATE_CORE_C3_RES) |
				  BIT(PERF_CSTATE_CORE_C6_RES) |
				  BIT(PERF_CSTATE_CORE_C7_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C2_RES) |
				  BIT(PERF_CSTATE_PKG_C3_RES) |
				  BIT(PERF_CSTATE_PKG_C6_RES) |
				  BIT(PERF_CSTATE_PKG_C7_RES) |
				  BIT(PERF_CSTATE_PKG_C8_RES) |
				  BIT(PERF_CSTATE_PKG_C9_RES) |
				  BIT(PERF_CSTATE_PKG_C10_RES),
पूर्ण;

अटल स्थिर काष्ठा cstate_model icl_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C6_RES) |
				  BIT(PERF_CSTATE_CORE_C7_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C2_RES) |
				  BIT(PERF_CSTATE_PKG_C3_RES) |
				  BIT(PERF_CSTATE_PKG_C6_RES) |
				  BIT(PERF_CSTATE_PKG_C7_RES) |
				  BIT(PERF_CSTATE_PKG_C8_RES) |
				  BIT(PERF_CSTATE_PKG_C9_RES) |
				  BIT(PERF_CSTATE_PKG_C10_RES),
पूर्ण;

अटल स्थिर काष्ठा cstate_model adl_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C1_RES) |
				  BIT(PERF_CSTATE_CORE_C6_RES) |
				  BIT(PERF_CSTATE_CORE_C7_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C2_RES) |
				  BIT(PERF_CSTATE_PKG_C3_RES) |
				  BIT(PERF_CSTATE_PKG_C6_RES) |
				  BIT(PERF_CSTATE_PKG_C7_RES) |
				  BIT(PERF_CSTATE_PKG_C8_RES) |
				  BIT(PERF_CSTATE_PKG_C9_RES) |
				  BIT(PERF_CSTATE_PKG_C10_RES),
पूर्ण;

अटल स्थिर काष्ठा cstate_model slm_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C1_RES) |
				  BIT(PERF_CSTATE_CORE_C6_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C6_RES),
	.quirks			= SLM_PKG_C6_USE_C7_MSR,
पूर्ण;


अटल स्थिर काष्ठा cstate_model knl_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C6_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C2_RES) |
				  BIT(PERF_CSTATE_PKG_C3_RES) |
				  BIT(PERF_CSTATE_PKG_C6_RES),
	.quirks			= KNL_CORE_C6_MSR,
पूर्ण;


अटल स्थिर काष्ठा cstate_model glm_cstates __initस्थिर = अणु
	.core_events		= BIT(PERF_CSTATE_CORE_C1_RES) |
				  BIT(PERF_CSTATE_CORE_C3_RES) |
				  BIT(PERF_CSTATE_CORE_C6_RES),

	.pkg_events		= BIT(PERF_CSTATE_PKG_C2_RES) |
				  BIT(PERF_CSTATE_PKG_C3_RES) |
				  BIT(PERF_CSTATE_PKG_C6_RES) |
				  BIT(PERF_CSTATE_PKG_C10_RES),
पूर्ण;


अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_cstates_match[] __initस्थिर = अणु
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM,		&nhm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM_EP,		&nhm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM_EX,		&nhm_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE,		&nhm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE_EP,		&nhm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE_EX,		&nhm_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE_X,	&snb_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE_X,		&snb_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(HASWELL,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_X,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_G,		&snb_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_L,		&hswult_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT,	&slm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT_D,	&slm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT,	&slm_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_D,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_G,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X,		&snb_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_L,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE,		&snb_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_X,		&snb_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE_L,		&hswult_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE,		&hswult_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE_L,		&hswult_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE,		&hswult_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(CANNONLAKE_L,	&cnl_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNL,	&knl_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNM,	&knl_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT,	&glm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_D,	&glm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_PLUS,	&glm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_D,	&glm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT,	&glm_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_L,	&glm_cstates),

	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_L,		&icl_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE,		&icl_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE_L,		&icl_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE,		&icl_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ROCKETLAKE,		&icl_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE,		&adl_cstates),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE_L,		&adl_cstates),
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, पूर्णांकel_cstates_match);

अटल पूर्णांक __init cstate_probe(स्थिर काष्ठा cstate_model *cm)
अणु
	/* SLM has dअगरferent MSR क्रम PKG C6 */
	अगर (cm->quirks & SLM_PKG_C6_USE_C7_MSR)
		pkg_msr[PERF_CSTATE_PKG_C6_RES].msr = MSR_PKG_C7_RESIDENCY;

	/* KNL has dअगरferent MSR क्रम CORE C6 */
	अगर (cm->quirks & KNL_CORE_C6_MSR)
		pkg_msr[PERF_CSTATE_CORE_C6_RES].msr = MSR_KNL_CORE_C6_RESIDENCY;


	core_msr_mask = perf_msr_probe(core_msr, PERF_CSTATE_CORE_EVENT_MAX,
				       true, (व्योम *) &cm->core_events);

	pkg_msr_mask = perf_msr_probe(pkg_msr, PERF_CSTATE_PKG_EVENT_MAX,
				      true, (व्योम *) &cm->pkg_events);

	has_cstate_core = !!core_msr_mask;
	has_cstate_pkg  = !!pkg_msr_mask;

	वापस (has_cstate_core || has_cstate_pkg) ? 0 : -ENODEV;
पूर्ण

अटल अंतरभूत व्योम cstate_cleanup(व्योम)
अणु
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_PERF_X86_CSTATE_ONLINE);
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_PERF_X86_CSTATE_STARTING);

	अगर (has_cstate_core)
		perf_pmu_unरेजिस्टर(&cstate_core_pmu);

	अगर (has_cstate_pkg)
		perf_pmu_unरेजिस्टर(&cstate_pkg_pmu);
पूर्ण

अटल पूर्णांक __init cstate_init(व्योम)
अणु
	पूर्णांक err;

	cpuhp_setup_state(CPUHP_AP_PERF_X86_CSTATE_STARTING,
			  "perf/x86/cstate:starting", cstate_cpu_init, शून्य);
	cpuhp_setup_state(CPUHP_AP_PERF_X86_CSTATE_ONLINE,
			  "perf/x86/cstate:online", शून्य, cstate_cpu_निकास);

	अगर (has_cstate_core) अणु
		err = perf_pmu_रेजिस्टर(&cstate_core_pmu, cstate_core_pmu.name, -1);
		अगर (err) अणु
			has_cstate_core = false;
			pr_info("Failed to register cstate core pmu\n");
			cstate_cleanup();
			वापस err;
		पूर्ण
	पूर्ण

	अगर (has_cstate_pkg) अणु
		अगर (topology_max_die_per_package() > 1) अणु
			err = perf_pmu_रेजिस्टर(&cstate_pkg_pmu,
						"cstate_die", -1);
		पूर्ण अन्यथा अणु
			err = perf_pmu_रेजिस्टर(&cstate_pkg_pmu,
						cstate_pkg_pmu.name, -1);
		पूर्ण
		अगर (err) अणु
			has_cstate_pkg = false;
			pr_info("Failed to register cstate pkg pmu\n");
			cstate_cleanup();
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init cstate_pmu_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	पूर्णांक err;

	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस -ENODEV;

	id = x86_match_cpu(पूर्णांकel_cstates_match);
	अगर (!id)
		वापस -ENODEV;

	err = cstate_probe((स्थिर काष्ठा cstate_model *) id->driver_data);
	अगर (err)
		वापस err;

	वापस cstate_init();
पूर्ण
module_init(cstate_pmu_init);

अटल व्योम __निकास cstate_pmu_निकास(व्योम)
अणु
	cstate_cleanup();
पूर्ण
module_निकास(cstate_pmu_निकास);
