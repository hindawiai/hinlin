<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support Intel/AMD RAPL energy consumption counters
 * Copyright (C) 2013 Google, Inc., Stephane Eranian
 *
 * Intel RAPL पूर्णांकerface is specअगरied in the IA-32 Manual Vol3b
 * section 14.7.1 (September 2013)
 *
 * AMD RAPL पूर्णांकerface क्रम Fam17h is described in the खुला PPR:
 * https://bugzilla.kernel.org/show_bug.cgi?id=206537
 *
 * RAPL provides more controls than just reporting energy consumption
 * however here we only expose the 3 energy consumption मुक्त running
 * counters (pp0, pkg, dram).
 *
 * Each of those counters increments in a घातer unit defined by the
 * RAPL_POWER_UNIT MSR. On SandyBridge, this unit is 1/(2^16) Joules
 * but it can vary.
 *
 * Counter to rapl events mappings:
 *
 *  pp0 counter: consumption of all physical cores (घातer plane 0)
 * 	  event: rapl_energy_cores
 *    perf code: 0x1
 *
 *  pkg counter: consumption of the whole processor package
 *	  event: rapl_energy_pkg
 *    perf code: 0x2
 *
 * dram counter: consumption of the dram करोमुख्य (servers only)
 *	  event: rapl_energy_dram
 *    perf code: 0x3
 *
 * gpu counter: consumption of the builtin-gpu करोमुख्य (client only)
 *	  event: rapl_energy_gpu
 *    perf code: 0x4
 *
 *  psys counter: consumption of the builtin-psys करोमुख्य (client only)
 *	  event: rapl_energy_psys
 *    perf code: 0x5
 *
 * We manage those counters as मुक्त running (पढ़ो-only). They may be
 * use simultaneously by other tools, such as turbostat.
 *
 * The events only support प्रणाली-wide mode counting. There is no
 * sampling support because it करोes not make sense and is not
 * supported by the RAPL hardware.
 *
 * Because we want to aव्योम भग्नing-poपूर्णांक operations in the kernel,
 * the events are all reported in fixed poपूर्णांक arithmetic (32.32).
 * Tools must adjust the counts to convert them to Watts using
 * the duration of the measurement. Tools may use a function such as
 * ldexp(raw_count, -32);
 */

#घोषणा pr_fmt(fmt) "RAPL PMU: " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/nospec.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश "perf_event.h"
#समावेश "probe.h"

MODULE_LICENSE("GPL");

/*
 * RAPL energy status counters
 */
क्रमागत perf_rapl_events अणु
	PERF_RAPL_PP0 = 0,		/* all cores */
	PERF_RAPL_PKG,			/* entire package */
	PERF_RAPL_RAM,			/* DRAM */
	PERF_RAPL_PP1,			/* gpu */
	PERF_RAPL_PSYS,			/* psys */

	PERF_RAPL_MAX,
	NR_RAPL_DOMAINS = PERF_RAPL_MAX,
पूर्ण;

अटल स्थिर अक्षर *स्थिर rapl_करोमुख्य_names[NR_RAPL_DOMAINS] __initस्थिर = अणु
	"pp0-core",
	"package",
	"dram",
	"pp1-gpu",
	"psys",
पूर्ण;

/*
 * event code: LSB 8 bits, passed in attr->config
 * any other bit is reserved
 */
#घोषणा RAPL_EVENT_MASK	0xFFULL
#घोषणा RAPL_CNTR_WIDTH 32

#घोषणा RAPL_EVENT_ATTR_STR(_name, v, str)					\
अटल काष्ठा perf_pmu_events_attr event_attr_##v = अणु				\
	.attr		= __ATTR(_name, 0444, perf_event_sysfs_show, शून्य),	\
	.id		= 0,							\
	.event_str	= str,							\
पूर्ण;

काष्ठा rapl_pmu अणु
	raw_spinlock_t		lock;
	पूर्णांक			n_active;
	पूर्णांक			cpu;
	काष्ठा list_head	active_list;
	काष्ठा pmu		*pmu;
	kसमय_प्रकार			समयr_पूर्णांकerval;
	काष्ठा hrसमयr		hrसमयr;
पूर्ण;

काष्ठा rapl_pmus अणु
	काष्ठा pmu		pmu;
	अचिन्हित पूर्णांक		maxdie;
	काष्ठा rapl_pmu		*pmus[];
पूर्ण;

क्रमागत rapl_unit_quirk अणु
	RAPL_UNIT_QUIRK_NONE,
	RAPL_UNIT_QUIRK_INTEL_HSW,
	RAPL_UNIT_QUIRK_INTEL_SPR,
पूर्ण;

काष्ठा rapl_model अणु
	काष्ठा perf_msr *rapl_msrs;
	अचिन्हित दीर्घ	events;
	अचिन्हित पूर्णांक	msr_घातer_unit;
	क्रमागत rapl_unit_quirk	unit_quirk;
पूर्ण;

 /* 1/2^hw_unit Joule */
अटल पूर्णांक rapl_hw_unit[NR_RAPL_DOMAINS] __पढ़ो_mostly;
अटल काष्ठा rapl_pmus *rapl_pmus;
अटल cpumask_t rapl_cpu_mask;
अटल अचिन्हित पूर्णांक rapl_cntr_mask;
अटल u64 rapl_समयr_ms;
अटल काष्ठा perf_msr *rapl_msrs;

अटल अंतरभूत काष्ठा rapl_pmu *cpu_to_rapl_pmu(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक dieid = topology_logical_die_id(cpu);

	/*
	 * The अचिन्हित check also catches the '-1' वापस value क्रम non
	 * existent mappings in the topology map.
	 */
	वापस dieid < rapl_pmus->maxdie ? rapl_pmus->pmus[dieid] : शून्य;
पूर्ण

अटल अंतरभूत u64 rapl_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	u64 raw;
	rdmsrl(event->hw.event_base, raw);
	वापस raw;
पूर्ण

अटल अंतरभूत u64 rapl_scale(u64 v, पूर्णांक cfg)
अणु
	अगर (cfg > NR_RAPL_DOMAINS) अणु
		pr_warn("Invalid domain %d, failed to scale data\n", cfg);
		वापस v;
	पूर्ण
	/*
	 * scale delta to smallest unit (1/2^32)
	 * users must then scale back: count * 1/(1e9*2^32) to get Joules
	 * or use ldexp(count, -32).
	 * Watts = Joules/Time delta
	 */
	वापस v << (32 - rapl_hw_unit[cfg - 1]);
पूर्ण

अटल u64 rapl_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 prev_raw_count, new_raw_count;
	s64 delta, sdelta;
	पूर्णांक shअगरt = RAPL_CNTR_WIDTH;

again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	rdmsrl(event->hw.event_base, new_raw_count);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			    new_raw_count) != prev_raw_count) अणु
		cpu_relax();
		जाओ again;
	पूर्ण

	/*
	 * Now we have the new raw value and have updated the prev
	 * बारtamp alपढ़ोy. We can now calculate the elapsed delta
	 * (event-)समय and add that to the generic event.
	 *
	 * Careful, not all hw sign-extends above the physical width
	 * of the count.
	 */
	delta = (new_raw_count << shअगरt) - (prev_raw_count << shअगरt);
	delta >>= shअगरt;

	sdelta = rapl_scale(delta, event->hw.config);

	local64_add(sdelta, &event->count);

	वापस new_raw_count;
पूर्ण

अटल व्योम rapl_start_hrसमयr(काष्ठा rapl_pmu *pmu)
अणु
       hrसमयr_start(&pmu->hrसमयr, pmu->समयr_पूर्णांकerval,
		     HRTIMER_MODE_REL_PINNED);
पूर्ण

अटल क्रमागत hrसमयr_restart rapl_hrसमयr_handle(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा rapl_pmu *pmu = container_of(hrसमयr, काष्ठा rapl_pmu, hrसमयr);
	काष्ठा perf_event *event;
	अचिन्हित दीर्घ flags;

	अगर (!pmu->n_active)
		वापस HRTIMER_NORESTART;

	raw_spin_lock_irqsave(&pmu->lock, flags);

	list_क्रम_each_entry(event, &pmu->active_list, active_entry)
		rapl_event_update(event);

	raw_spin_unlock_irqrestore(&pmu->lock, flags);

	hrसमयr_क्रमward_now(hrसमयr, pmu->समयr_पूर्णांकerval);

	वापस HRTIMER_RESTART;
पूर्ण

अटल व्योम rapl_hrसमयr_init(काष्ठा rapl_pmu *pmu)
अणु
	काष्ठा hrसमयr *hr = &pmu->hrसमयr;

	hrसमयr_init(hr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hr->function = rapl_hrसमयr_handle;
पूर्ण

अटल व्योम __rapl_pmu_event_start(काष्ठा rapl_pmu *pmu,
				   काष्ठा perf_event *event)
अणु
	अगर (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		वापस;

	event->hw.state = 0;

	list_add_tail(&event->active_entry, &pmu->active_list);

	local64_set(&event->hw.prev_count, rapl_पढ़ो_counter(event));

	pmu->n_active++;
	अगर (pmu->n_active == 1)
		rapl_start_hrसमयr(pmu);
पूर्ण

अटल व्योम rapl_pmu_event_start(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा rapl_pmu *pmu = event->pmu_निजी;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pmu->lock, flags);
	__rapl_pmu_event_start(pmu, event);
	raw_spin_unlock_irqrestore(&pmu->lock, flags);
पूर्ण

अटल व्योम rapl_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा rapl_pmu *pmu = event->pmu_निजी;
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pmu->lock, flags);

	/* mark event as deactivated and stopped */
	अगर (!(hwc->state & PERF_HES_STOPPED)) अणु
		WARN_ON_ONCE(pmu->n_active <= 0);
		pmu->n_active--;
		अगर (pmu->n_active == 0)
			hrसमयr_cancel(&pmu->hrसमयr);

		list_del(&event->active_entry);

		WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
		hwc->state |= PERF_HES_STOPPED;
	पूर्ण

	/* check अगर update of sw counter is necessary */
	अगर ((mode & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) अणु
		/*
		 * Drain the reमुख्यing delta count out of a event
		 * that we are disabling:
		 */
		rapl_event_update(event);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण

	raw_spin_unlock_irqrestore(&pmu->lock, flags);
पूर्ण

अटल पूर्णांक rapl_pmu_event_add(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा rapl_pmu *pmu = event->pmu_निजी;
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pmu->lock, flags);

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	अगर (mode & PERF_EF_START)
		__rapl_pmu_event_start(pmu, event);

	raw_spin_unlock_irqrestore(&pmu->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम rapl_pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	rapl_pmu_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक rapl_pmu_event_init(काष्ठा perf_event *event)
अणु
	u64 cfg = event->attr.config & RAPL_EVENT_MASK;
	पूर्णांक bit, ret = 0;
	काष्ठा rapl_pmu *pmu;

	/* only look at RAPL events */
	अगर (event->attr.type != rapl_pmus->pmu.type)
		वापस -ENOENT;

	/* check only supported bits are set */
	अगर (event->attr.config & ~RAPL_EVENT_MASK)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	event->event_caps |= PERF_EV_CAP_READ_ACTIVE_PKG;

	अगर (!cfg || cfg >= NR_RAPL_DOMAINS + 1)
		वापस -EINVAL;

	cfg = array_index_nospec((दीर्घ)cfg, NR_RAPL_DOMAINS + 1);
	bit = cfg - 1;

	/* check event supported */
	अगर (!(rapl_cntr_mask & (1 << bit)))
		वापस -EINVAL;

	/* unsupported modes and filters */
	अगर (event->attr.sample_period) /* no sampling */
		वापस -EINVAL;

	/* must be करोne beक्रमe validate_group */
	pmu = cpu_to_rapl_pmu(event->cpu);
	अगर (!pmu)
		वापस -EINVAL;
	event->cpu = pmu->cpu;
	event->pmu_निजी = pmu;
	event->hw.event_base = rapl_msrs[bit].msr;
	event->hw.config = cfg;
	event->hw.idx = bit;

	वापस ret;
पूर्ण

अटल व्योम rapl_pmu_event_पढ़ो(काष्ठा perf_event *event)
अणु
	rapl_event_update(event);
पूर्ण

अटल sमाप_प्रकार rapl_get_attr_cpumask(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &rapl_cpu_mask);
पूर्ण

अटल DEVICE_ATTR(cpumask, S_IRUGO, rapl_get_attr_cpumask, शून्य);

अटल काष्ठा attribute *rapl_pmu_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rapl_pmu_attr_group = अणु
	.attrs = rapl_pmu_attrs,
पूर्ण;

RAPL_EVENT_ATTR_STR(energy-cores, rapl_cores, "event=0x01");
RAPL_EVENT_ATTR_STR(energy-pkg  ,   rapl_pkg, "event=0x02");
RAPL_EVENT_ATTR_STR(energy-ram  ,   rapl_ram, "event=0x03");
RAPL_EVENT_ATTR_STR(energy-gpu  ,   rapl_gpu, "event=0x04");
RAPL_EVENT_ATTR_STR(energy-psys,   rapl_psys, "event=0x05");

RAPL_EVENT_ATTR_STR(energy-cores.unit, rapl_cores_unit, "Joules");
RAPL_EVENT_ATTR_STR(energy-pkg.unit  ,   rapl_pkg_unit, "Joules");
RAPL_EVENT_ATTR_STR(energy-ram.unit  ,   rapl_ram_unit, "Joules");
RAPL_EVENT_ATTR_STR(energy-gpu.unit  ,   rapl_gpu_unit, "Joules");
RAPL_EVENT_ATTR_STR(energy-psys.unit,   rapl_psys_unit, "Joules");

/*
 * we compute in 0.23 nJ increments regardless of MSR
 */
RAPL_EVENT_ATTR_STR(energy-cores.scale, rapl_cores_scale, "2.3283064365386962890625e-10");
RAPL_EVENT_ATTR_STR(energy-pkg.scale,     rapl_pkg_scale, "2.3283064365386962890625e-10");
RAPL_EVENT_ATTR_STR(energy-ram.scale,     rapl_ram_scale, "2.3283064365386962890625e-10");
RAPL_EVENT_ATTR_STR(energy-gpu.scale,     rapl_gpu_scale, "2.3283064365386962890625e-10");
RAPL_EVENT_ATTR_STR(energy-psys.scale,   rapl_psys_scale, "2.3283064365386962890625e-10");

/*
 * There are no शेष events, but we need to create
 * "events" group (with empty attrs) beक्रमe updating
 * it with detected events.
 */
अटल काष्ठा attribute *attrs_empty[] = अणु
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rapl_pmu_events_group = अणु
	.name = "events",
	.attrs = attrs_empty,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-7");
अटल काष्ठा attribute *rapl_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rapl_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = rapl_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *rapl_attr_groups[] = अणु
	&rapl_pmu_attr_group,
	&rapl_pmu_क्रमmat_group,
	&rapl_pmu_events_group,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *rapl_events_cores[] = अणु
	EVENT_PTR(rapl_cores),
	EVENT_PTR(rapl_cores_unit),
	EVENT_PTR(rapl_cores_scale),
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rapl_events_cores_group = अणु
	.name  = "events",
	.attrs = rapl_events_cores,
पूर्ण;

अटल काष्ठा attribute *rapl_events_pkg[] = अणु
	EVENT_PTR(rapl_pkg),
	EVENT_PTR(rapl_pkg_unit),
	EVENT_PTR(rapl_pkg_scale),
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rapl_events_pkg_group = अणु
	.name  = "events",
	.attrs = rapl_events_pkg,
पूर्ण;

अटल काष्ठा attribute *rapl_events_ram[] = अणु
	EVENT_PTR(rapl_ram),
	EVENT_PTR(rapl_ram_unit),
	EVENT_PTR(rapl_ram_scale),
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rapl_events_ram_group = अणु
	.name  = "events",
	.attrs = rapl_events_ram,
पूर्ण;

अटल काष्ठा attribute *rapl_events_gpu[] = अणु
	EVENT_PTR(rapl_gpu),
	EVENT_PTR(rapl_gpu_unit),
	EVENT_PTR(rapl_gpu_scale),
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rapl_events_gpu_group = अणु
	.name  = "events",
	.attrs = rapl_events_gpu,
पूर्ण;

अटल काष्ठा attribute *rapl_events_psys[] = अणु
	EVENT_PTR(rapl_psys),
	EVENT_PTR(rapl_psys_unit),
	EVENT_PTR(rapl_psys_scale),
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rapl_events_psys_group = अणु
	.name  = "events",
	.attrs = rapl_events_psys,
पूर्ण;

अटल bool test_msr(पूर्णांक idx, व्योम *data)
अणु
	वापस test_bit(idx, (अचिन्हित दीर्घ *) data);
पूर्ण

/* Only lower 32bits of the MSR represents the energy counter */
#घोषणा RAPL_MSR_MASK 0xFFFFFFFF

अटल काष्ठा perf_msr पूर्णांकel_rapl_msrs[] = अणु
	[PERF_RAPL_PP0]  = अणु MSR_PP0_ENERGY_STATUS,      &rapl_events_cores_group, test_msr, false, RAPL_MSR_MASK पूर्ण,
	[PERF_RAPL_PKG]  = अणु MSR_PKG_ENERGY_STATUS,      &rapl_events_pkg_group,   test_msr, false, RAPL_MSR_MASK पूर्ण,
	[PERF_RAPL_RAM]  = अणु MSR_DRAM_ENERGY_STATUS,     &rapl_events_ram_group,   test_msr, false, RAPL_MSR_MASK पूर्ण,
	[PERF_RAPL_PP1]  = अणु MSR_PP1_ENERGY_STATUS,      &rapl_events_gpu_group,   test_msr, false, RAPL_MSR_MASK पूर्ण,
	[PERF_RAPL_PSYS] = अणु MSR_PLATFORM_ENERGY_STATUS, &rapl_events_psys_group,  test_msr, false, RAPL_MSR_MASK पूर्ण,
पूर्ण;

अटल काष्ठा perf_msr पूर्णांकel_rapl_spr_msrs[] = अणु
	[PERF_RAPL_PP0]  = अणु MSR_PP0_ENERGY_STATUS,      &rapl_events_cores_group, test_msr, false, RAPL_MSR_MASK पूर्ण,
	[PERF_RAPL_PKG]  = अणु MSR_PKG_ENERGY_STATUS,      &rapl_events_pkg_group,   test_msr, false, RAPL_MSR_MASK पूर्ण,
	[PERF_RAPL_RAM]  = अणु MSR_DRAM_ENERGY_STATUS,     &rapl_events_ram_group,   test_msr, false, RAPL_MSR_MASK पूर्ण,
	[PERF_RAPL_PP1]  = अणु MSR_PP1_ENERGY_STATUS,      &rapl_events_gpu_group,   test_msr, false, RAPL_MSR_MASK पूर्ण,
	[PERF_RAPL_PSYS] = अणु MSR_PLATFORM_ENERGY_STATUS, &rapl_events_psys_group,  test_msr, true, RAPL_MSR_MASK पूर्ण,
पूर्ण;

/*
 * Force to PERF_RAPL_MAX size due to:
 * - perf_msr_probe(PERF_RAPL_MAX)
 * - want to use same event codes across both architectures
 */
अटल काष्ठा perf_msr amd_rapl_msrs[PERF_RAPL_MAX] = अणु
	[PERF_RAPL_PKG]  = अणु MSR_AMD_PKG_ENERGY_STATUS,  &rapl_events_pkg_group,   test_msr पूर्ण,
पूर्ण;


अटल पूर्णांक rapl_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rapl_pmu *pmu = cpu_to_rapl_pmu(cpu);
	पूर्णांक target;

	/* Check अगर निकासing cpu is used क्रम collecting rapl events */
	अगर (!cpumask_test_and_clear_cpu(cpu, &rapl_cpu_mask))
		वापस 0;

	pmu->cpu = -1;
	/* Find a new cpu to collect rapl events */
	target = cpumask_any_but(topology_die_cpumask(cpu), cpu);

	/* Migrate rapl events to the new target */
	अगर (target < nr_cpu_ids) अणु
		cpumask_set_cpu(target, &rapl_cpu_mask);
		pmu->cpu = target;
		perf_pmu_migrate_context(pmu->pmu, cpu, target);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rapl_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rapl_pmu *pmu = cpu_to_rapl_pmu(cpu);
	पूर्णांक target;

	अगर (!pmu) अणु
		pmu = kzalloc_node(माप(*pmu), GFP_KERNEL, cpu_to_node(cpu));
		अगर (!pmu)
			वापस -ENOMEM;

		raw_spin_lock_init(&pmu->lock);
		INIT_LIST_HEAD(&pmu->active_list);
		pmu->pmu = &rapl_pmus->pmu;
		pmu->समयr_पूर्णांकerval = ms_to_kसमय(rapl_समयr_ms);
		rapl_hrसमयr_init(pmu);

		rapl_pmus->pmus[topology_logical_die_id(cpu)] = pmu;
	पूर्ण

	/*
	 * Check अगर there is an online cpu in the package which collects rapl
	 * events alपढ़ोy.
	 */
	target = cpumask_any_and(&rapl_cpu_mask, topology_die_cpumask(cpu));
	अगर (target < nr_cpu_ids)
		वापस 0;

	cpumask_set_cpu(cpu, &rapl_cpu_mask);
	pmu->cpu = cpu;
	वापस 0;
पूर्ण

अटल पूर्णांक rapl_check_hw_unit(काष्ठा rapl_model *rm)
अणु
	u64 msr_rapl_घातer_unit_bits;
	पूर्णांक i;

	/* protect rdmsrl() to handle भवization */
	अगर (rdmsrl_safe(rm->msr_घातer_unit, &msr_rapl_घातer_unit_bits))
		वापस -1;
	क्रम (i = 0; i < NR_RAPL_DOMAINS; i++)
		rapl_hw_unit[i] = (msr_rapl_घातer_unit_bits >> 8) & 0x1FULL;

	चयन (rm->unit_quirk) अणु
	/*
	 * DRAM करोमुख्य on HSW server and KNL has fixed energy unit which can be
	 * dअगरferent than the unit from घातer unit MSR. See
	 * "Intel Xeon Processor E5-1600 and E5-2600 v3 Product Families, V2
	 * of 2. Datasheet, September 2014, Reference Number: 330784-001 "
	 */
	हाल RAPL_UNIT_QUIRK_INTEL_HSW:
		rapl_hw_unit[PERF_RAPL_RAM] = 16;
		अवरोध;
	/*
	 * SPR shares the same DRAM करोमुख्य energy unit as HSW, plus it
	 * also has a fixed energy unit क्रम Psys करोमुख्य.
	 */
	हाल RAPL_UNIT_QUIRK_INTEL_SPR:
		rapl_hw_unit[PERF_RAPL_RAM] = 16;
		rapl_hw_unit[PERF_RAPL_PSYS] = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण


	/*
	 * Calculate the समयr rate:
	 * Use reference of 200W क्रम scaling the समयout to aव्योम counter
	 * overflows. 200W = 200 Joules/sec
	 * Divide पूर्णांकerval by 2 to aव्योम lockstep (2 * 100)
	 * अगर hw unit is 32, then we use 2 ms 1/200/2
	 */
	rapl_समयr_ms = 2;
	अगर (rapl_hw_unit[0] < 32) अणु
		rapl_समयr_ms = (1000 / (2 * 100));
		rapl_समयr_ms *= (1ULL << (32 - rapl_hw_unit[0] - 1));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init rapl_advertise(व्योम)
अणु
	पूर्णांक i;

	pr_info("API unit is 2^-32 Joules, %d fixed counters, %llu ms ovfl समयr\न",
		hweight32(rapl_cntr_mask), rapl_समयr_ms);

	क्रम (i = 0; i < NR_RAPL_DOMAINS; i++) अणु
		अगर (rapl_cntr_mask & (1 << i)) अणु
			pr_info("hw unit of करोमुख्य %s 2^-%d Joules\न",
				rapl_करोमुख्य_names[i], rapl_hw_unit[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cleanup_rapl_pmus(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rapl_pmus->maxdie; i++)
		kमुक्त(rapl_pmus->pmus[i]);
	kमुक्त(rapl_pmus);
पूर्ण

अटल स्थिर काष्ठा attribute_group *rapl_attr_update[] = अणु
	&rapl_events_cores_group,
	&rapl_events_pkg_group,
	&rapl_events_ram_group,
	&rapl_events_gpu_group,
	&rapl_events_psys_group,
	शून्य,
पूर्ण;

अटल पूर्णांक __init init_rapl_pmus(व्योम)
अणु
	पूर्णांक maxdie = topology_max_packages() * topology_max_die_per_package();
	माप_प्रकार size;

	size = माप(*rapl_pmus) + maxdie * माप(काष्ठा rapl_pmu *);
	rapl_pmus = kzalloc(size, GFP_KERNEL);
	अगर (!rapl_pmus)
		वापस -ENOMEM;

	rapl_pmus->maxdie		= maxdie;
	rapl_pmus->pmu.attr_groups	= rapl_attr_groups;
	rapl_pmus->pmu.attr_update	= rapl_attr_update;
	rapl_pmus->pmu.task_ctx_nr	= perf_invalid_context;
	rapl_pmus->pmu.event_init	= rapl_pmu_event_init;
	rapl_pmus->pmu.add		= rapl_pmu_event_add;
	rapl_pmus->pmu.del		= rapl_pmu_event_del;
	rapl_pmus->pmu.start		= rapl_pmu_event_start;
	rapl_pmus->pmu.stop		= rapl_pmu_event_stop;
	rapl_pmus->pmu.पढ़ो		= rapl_pmu_event_पढ़ो;
	rapl_pmus->pmu.module		= THIS_MODULE;
	rapl_pmus->pmu.capabilities	= PERF_PMU_CAP_NO_EXCLUDE;
	वापस 0;
पूर्ण

अटल काष्ठा rapl_model model_snb = अणु
	.events		= BIT(PERF_RAPL_PP0) |
			  BIT(PERF_RAPL_PKG) |
			  BIT(PERF_RAPL_PP1),
	.msr_घातer_unit = MSR_RAPL_POWER_UNIT,
	.rapl_msrs      = पूर्णांकel_rapl_msrs,
पूर्ण;

अटल काष्ठा rapl_model model_snbep = अणु
	.events		= BIT(PERF_RAPL_PP0) |
			  BIT(PERF_RAPL_PKG) |
			  BIT(PERF_RAPL_RAM),
	.msr_घातer_unit = MSR_RAPL_POWER_UNIT,
	.rapl_msrs      = पूर्णांकel_rapl_msrs,
पूर्ण;

अटल काष्ठा rapl_model model_hsw = अणु
	.events		= BIT(PERF_RAPL_PP0) |
			  BIT(PERF_RAPL_PKG) |
			  BIT(PERF_RAPL_RAM) |
			  BIT(PERF_RAPL_PP1),
	.msr_घातer_unit = MSR_RAPL_POWER_UNIT,
	.rapl_msrs      = पूर्णांकel_rapl_msrs,
पूर्ण;

अटल काष्ठा rapl_model model_hsx = अणु
	.events		= BIT(PERF_RAPL_PP0) |
			  BIT(PERF_RAPL_PKG) |
			  BIT(PERF_RAPL_RAM),
	.unit_quirk	= RAPL_UNIT_QUIRK_INTEL_HSW,
	.msr_घातer_unit = MSR_RAPL_POWER_UNIT,
	.rapl_msrs      = पूर्णांकel_rapl_msrs,
पूर्ण;

अटल काष्ठा rapl_model model_knl = अणु
	.events		= BIT(PERF_RAPL_PKG) |
			  BIT(PERF_RAPL_RAM),
	.unit_quirk	= RAPL_UNIT_QUIRK_INTEL_HSW,
	.msr_घातer_unit = MSR_RAPL_POWER_UNIT,
	.rapl_msrs      = पूर्णांकel_rapl_msrs,
पूर्ण;

अटल काष्ठा rapl_model model_skl = अणु
	.events		= BIT(PERF_RAPL_PP0) |
			  BIT(PERF_RAPL_PKG) |
			  BIT(PERF_RAPL_RAM) |
			  BIT(PERF_RAPL_PP1) |
			  BIT(PERF_RAPL_PSYS),
	.msr_घातer_unit = MSR_RAPL_POWER_UNIT,
	.rapl_msrs      = पूर्णांकel_rapl_msrs,
पूर्ण;

अटल काष्ठा rapl_model model_spr = अणु
	.events		= BIT(PERF_RAPL_PP0) |
			  BIT(PERF_RAPL_PKG) |
			  BIT(PERF_RAPL_RAM) |
			  BIT(PERF_RAPL_PSYS),
	.unit_quirk	= RAPL_UNIT_QUIRK_INTEL_SPR,
	.msr_घातer_unit = MSR_RAPL_POWER_UNIT,
	.rapl_msrs      = पूर्णांकel_rapl_spr_msrs,
पूर्ण;

अटल काष्ठा rapl_model model_amd_fam17h = अणु
	.events		= BIT(PERF_RAPL_PKG),
	.msr_घातer_unit = MSR_AMD_RAPL_POWER_UNIT,
	.rapl_msrs      = amd_rapl_msrs,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id rapl_model_match[] __initस्थिर = अणु
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE,		&model_snb),
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE_X,	&model_snbep),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE,		&model_snb),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE_X,		&model_snbep),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL,		&model_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_X,		&model_hsx),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_L,		&model_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_G,		&model_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL,		&model_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_G,		&model_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X,		&model_hsx),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_D,		&model_hsx),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNL,	&model_knl),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNM,	&model_knl),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_L,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_X,		&model_hsx),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE_L,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(CANNONLAKE_L,	&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT,	&model_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_D,	&model_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_PLUS,	&model_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_L,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_D,		&model_hsx),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_X,		&model_hsx),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE_L,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE_L,		&model_skl),
	X86_MATCH_INTEL_FAM6_MODEL(SAPPHIRERAPIDS_X,	&model_spr),
	X86_MATCH_VENDOR_FAM(AMD,	0x17,		&model_amd_fam17h),
	X86_MATCH_VENDOR_FAM(HYGON,	0x18,		&model_amd_fam17h),
	X86_MATCH_VENDOR_FAM(AMD,	0x19,		&model_amd_fam17h),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, rapl_model_match);

अटल पूर्णांक __init rapl_pmu_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	काष्ठा rapl_model *rm;
	पूर्णांक ret;

	id = x86_match_cpu(rapl_model_match);
	अगर (!id)
		वापस -ENODEV;

	rm = (काष्ठा rapl_model *) id->driver_data;

	rapl_msrs = rm->rapl_msrs;

	rapl_cntr_mask = perf_msr_probe(rapl_msrs, PERF_RAPL_MAX,
					false, (व्योम *) &rm->events);

	ret = rapl_check_hw_unit(rm);
	अगर (ret)
		वापस ret;

	ret = init_rapl_pmus();
	अगर (ret)
		वापस ret;

	/*
	 * Install callbacks. Core will call them क्रम each online cpu.
	 */
	ret = cpuhp_setup_state(CPUHP_AP_PERF_X86_RAPL_ONLINE,
				"perf/x86/rapl:online",
				rapl_cpu_online, rapl_cpu_offline);
	अगर (ret)
		जाओ out;

	ret = perf_pmu_रेजिस्टर(&rapl_pmus->pmu, "power", -1);
	अगर (ret)
		जाओ out1;

	rapl_advertise();
	वापस 0;

out1:
	cpuhp_हटाओ_state(CPUHP_AP_PERF_X86_RAPL_ONLINE);
out:
	pr_warn("Initialization failed (%d), disabled\n", ret);
	cleanup_rapl_pmus();
	वापस ret;
पूर्ण
module_init(rapl_pmu_init);

अटल व्योम __निकास पूर्णांकel_rapl_निकास(व्योम)
अणु
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_PERF_X86_RAPL_ONLINE);
	perf_pmu_unरेजिस्टर(&rapl_pmus->pmu);
	cleanup_rapl_pmus();
पूर्ण
module_निकास(पूर्णांकel_rapl_निकास);
