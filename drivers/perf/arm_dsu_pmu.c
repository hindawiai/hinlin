<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM DynamIQ Shared Unit (DSU) PMU driver
 *
 * Copyright (C) ARM Limited, 2017.
 *
 * Based on ARM CCI-PMU, ARMv8 PMU-v3 drivers.
 */

#घोषणा PMUNAME		"arm_dsu"
#घोषणा DRVNAME		PMUNAME "_pmu"
#घोषणा pr_fmt(fmt)	DRVNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/arm_dsu_pmu.h>
#समावेश <यंत्र/local64.h>

/* PMU event codes */
#घोषणा DSU_PMU_EVT_CYCLES		0x11
#घोषणा DSU_PMU_EVT_CHAIN		0x1e

#घोषणा DSU_PMU_MAX_COMMON_EVENTS	0x40

#घोषणा DSU_PMU_MAX_HW_CNTRS		32
#घोषणा DSU_PMU_HW_COUNTER_MASK		(DSU_PMU_MAX_HW_CNTRS - 1)

#घोषणा CLUSTERPMCR_E			BIT(0)
#घोषणा CLUSTERPMCR_P			BIT(1)
#घोषणा CLUSTERPMCR_C			BIT(2)
#घोषणा CLUSTERPMCR_N_SHIFT		11
#घोषणा CLUSTERPMCR_N_MASK		0x1f
#घोषणा CLUSTERPMCR_IDCODE_SHIFT	16
#घोषणा CLUSTERPMCR_IDCODE_MASK		0xff
#घोषणा CLUSTERPMCR_IMP_SHIFT		24
#घोषणा CLUSTERPMCR_IMP_MASK		0xff
#घोषणा CLUSTERPMCR_RES_MASK		0x7e8
#घोषणा CLUSTERPMCR_RES_VAL		0x40

#घोषणा DSU_ACTIVE_CPU_MASK		0x0
#घोषणा DSU_ASSOCIATED_CPU_MASK		0x1

/*
 * We use the index of the counters as they appear in the counter
 * bit maps in the PMU रेजिस्टरs (e.g CLUSTERPMSELR).
 * i.e,
 *	counter 0	- Bit 0
 *	counter 1	- Bit 1
 *	...
 *	Cycle counter	- Bit 31
 */
#घोषणा DSU_PMU_IDX_CYCLE_COUNTER	31

/* All event counters are 32bit, with a 64bit Cycle counter */
#घोषणा DSU_PMU_COUNTER_WIDTH(idx)	\
	(((idx) == DSU_PMU_IDX_CYCLE_COUNTER) ? 64 : 32)

#घोषणा DSU_PMU_COUNTER_MASK(idx)	\
	GENMASK_ULL((DSU_PMU_COUNTER_WIDTH((idx)) - 1), 0)

#घोषणा DSU_EXT_ATTR(_name, _func, _config)		\
	(&((काष्ठा dev_ext_attribute[]) अणु				\
		अणु							\
			.attr = __ATTR(_name, 0444, _func, शून्य),	\
			.var = (व्योम *)_config				\
		पूर्ण							\
	पूर्ण)[0].attr.attr)

#घोषणा DSU_EVENT_ATTR(_name, _config)		\
	DSU_EXT_ATTR(_name, dsu_pmu_sysfs_event_show, (अचिन्हित दीर्घ)_config)

#घोषणा DSU_FORMAT_ATTR(_name, _config)		\
	DSU_EXT_ATTR(_name, dsu_pmu_sysfs_क्रमmat_show, (अक्षर *)_config)

#घोषणा DSU_CPUMASK_ATTR(_name, _config)	\
	DSU_EXT_ATTR(_name, dsu_pmu_cpumask_show, (अचिन्हित दीर्घ)_config)

काष्ठा dsu_hw_events अणु
	DECLARE_BITMAP(used_mask, DSU_PMU_MAX_HW_CNTRS);
	काष्ठा perf_event	*events[DSU_PMU_MAX_HW_CNTRS];
पूर्ण;

/*
 * काष्ठा dsu_pmu	- DSU PMU descriptor
 *
 * @pmu_lock		: Protects accesses to DSU PMU रेजिस्टर from normal vs
 *			  पूर्णांकerrupt handler contexts.
 * @hw_events		: Holds the event counter state.
 * @associated_cpus	: CPUs attached to the DSU.
 * @active_cpu		: CPU to which the PMU is bound क्रम accesses.
 * @cpuhp_node		: Node क्रम CPU hotplug notअगरier link.
 * @num_counters	: Number of event counters implemented by the PMU,
 *			  excluding the cycle counter.
 * @irq			: Interrupt line क्रम counter overflow.
 * @cpmceid_biपंचांगap	: Biपंचांगap क्रम the availability of architected common
 *			  events (event_code < 0x40).
 */
काष्ठा dsu_pmu अणु
	काष्ठा pmu			pmu;
	काष्ठा device			*dev;
	raw_spinlock_t			pmu_lock;
	काष्ठा dsu_hw_events		hw_events;
	cpumask_t			associated_cpus;
	cpumask_t			active_cpu;
	काष्ठा hlist_node		cpuhp_node;
	s8				num_counters;
	पूर्णांक				irq;
	DECLARE_BITMAP(cpmceid_biपंचांगap, DSU_PMU_MAX_COMMON_EVENTS);
पूर्ण;

अटल अचिन्हित दीर्घ dsu_pmu_cpuhp_state;

अटल अंतरभूत काष्ठा dsu_pmu *to_dsu_pmu(काष्ठा pmu *pmu)
अणु
	वापस container_of(pmu, काष्ठा dsu_pmu, pmu);
पूर्ण

अटल sमाप_प्रकार dsu_pmu_sysfs_event_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr = container_of(attr,
					काष्ठा dev_ext_attribute, attr);
	वापस sysfs_emit(buf, "event=0x%lx\n", (अचिन्हित दीर्घ)eattr->var);
पूर्ण

अटल sमाप_प्रकार dsu_pmu_sysfs_क्रमmat_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr = container_of(attr,
					काष्ठा dev_ext_attribute, attr);
	वापस sysfs_emit(buf, "%s\n", (अक्षर *)eattr->var);
पूर्ण

अटल sमाप_प्रकार dsu_pmu_cpumask_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);
	काष्ठा dev_ext_attribute *eattr = container_of(attr,
					काष्ठा dev_ext_attribute, attr);
	अचिन्हित दीर्घ mask_id = (अचिन्हित दीर्घ)eattr->var;
	स्थिर cpumask_t *cpumask;

	चयन (mask_id) अणु
	हाल DSU_ACTIVE_CPU_MASK:
		cpumask = &dsu_pmu->active_cpu;
		अवरोध;
	हाल DSU_ASSOCIATED_CPU_MASK:
		cpumask = &dsu_pmu->associated_cpus;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask);
पूर्ण

अटल काष्ठा attribute *dsu_pmu_क्रमmat_attrs[] = अणु
	DSU_FORMAT_ATTR(event, "config:0-31"),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dsu_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = dsu_pmu_क्रमmat_attrs,
पूर्ण;

अटल काष्ठा attribute *dsu_pmu_event_attrs[] = अणु
	DSU_EVENT_ATTR(cycles, 0x11),
	DSU_EVENT_ATTR(bus_access, 0x19),
	DSU_EVENT_ATTR(memory_error, 0x1a),
	DSU_EVENT_ATTR(bus_cycles, 0x1d),
	DSU_EVENT_ATTR(l3d_cache_allocate, 0x29),
	DSU_EVENT_ATTR(l3d_cache_refill, 0x2a),
	DSU_EVENT_ATTR(l3d_cache, 0x2b),
	DSU_EVENT_ATTR(l3d_cache_wb, 0x2c),
	शून्य,
पूर्ण;

अटल umode_t
dsu_pmu_event_attr_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				पूर्णांक unused)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(kobj_to_dev(kobj));
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);
	काष्ठा dev_ext_attribute *eattr = container_of(attr,
					काष्ठा dev_ext_attribute, attr.attr);
	अचिन्हित दीर्घ evt = (अचिन्हित दीर्घ)eattr->var;

	वापस test_bit(evt, dsu_pmu->cpmceid_biपंचांगap) ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group dsu_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = dsu_pmu_event_attrs,
	.is_visible = dsu_pmu_event_attr_is_visible,
पूर्ण;

अटल काष्ठा attribute *dsu_pmu_cpumask_attrs[] = अणु
	DSU_CPUMASK_ATTR(cpumask, DSU_ACTIVE_CPU_MASK),
	DSU_CPUMASK_ATTR(associated_cpus, DSU_ASSOCIATED_CPU_MASK),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dsu_pmu_cpumask_attr_group = अणु
	.attrs = dsu_pmu_cpumask_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dsu_pmu_attr_groups[] = अणु
	&dsu_pmu_cpumask_attr_group,
	&dsu_pmu_events_attr_group,
	&dsu_pmu_क्रमmat_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक dsu_pmu_get_online_cpu_any_but(काष्ठा dsu_pmu *dsu_pmu, पूर्णांक cpu)
अणु
	काष्ठा cpumask online_supported;

	cpumask_and(&online_supported,
			 &dsu_pmu->associated_cpus, cpu_online_mask);
	वापस cpumask_any_but(&online_supported, cpu);
पूर्ण

अटल अंतरभूत bool dsu_pmu_counter_valid(काष्ठा dsu_pmu *dsu_pmu, u32 idx)
अणु
	वापस (idx < dsu_pmu->num_counters) ||
	       (idx == DSU_PMU_IDX_CYCLE_COUNTER);
पूर्ण

अटल अंतरभूत u64 dsu_pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	u64 val;
	अचिन्हित दीर्घ flags;
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	पूर्णांक idx = event->hw.idx;

	अगर (WARN_ON(!cpumask_test_cpu(smp_processor_id(),
				 &dsu_pmu->associated_cpus)))
		वापस 0;

	अगर (!dsu_pmu_counter_valid(dsu_pmu, idx)) अणु
		dev_err(event->pmu->dev,
			"Trying reading invalid counter %d\n", idx);
		वापस 0;
	पूर्ण

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	अगर (idx == DSU_PMU_IDX_CYCLE_COUNTER)
		val = __dsu_pmu_पढ़ो_pmccntr();
	अन्यथा
		val = __dsu_pmu_पढ़ो_counter(idx);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);

	वापस val;
पूर्ण

अटल व्योम dsu_pmu_ग_लिखो_counter(काष्ठा perf_event *event, u64 val)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	पूर्णांक idx = event->hw.idx;

	अगर (WARN_ON(!cpumask_test_cpu(smp_processor_id(),
			 &dsu_pmu->associated_cpus)))
		वापस;

	अगर (!dsu_pmu_counter_valid(dsu_pmu, idx)) अणु
		dev_err(event->pmu->dev,
			"writing to invalid counter %d\n", idx);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	अगर (idx == DSU_PMU_IDX_CYCLE_COUNTER)
		__dsu_pmu_ग_लिखो_pmccntr(val);
	अन्यथा
		__dsu_pmu_ग_लिखो_counter(idx, val);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);
पूर्ण

अटल पूर्णांक dsu_pmu_get_event_idx(काष्ठा dsu_hw_events *hw_events,
				 काष्ठा perf_event *event)
अणु
	पूर्णांक idx;
	अचिन्हित दीर्घ evtype = event->attr.config;
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	अचिन्हित दीर्घ *used_mask = hw_events->used_mask;

	अगर (evtype == DSU_PMU_EVT_CYCLES) अणु
		अगर (test_and_set_bit(DSU_PMU_IDX_CYCLE_COUNTER, used_mask))
			वापस -EAGAIN;
		वापस DSU_PMU_IDX_CYCLE_COUNTER;
	पूर्ण

	idx = find_first_zero_bit(used_mask, dsu_pmu->num_counters);
	अगर (idx >= dsu_pmu->num_counters)
		वापस -EAGAIN;
	set_bit(idx, hw_events->used_mask);
	वापस idx;
पूर्ण

अटल व्योम dsu_pmu_enable_counter(काष्ठा dsu_pmu *dsu_pmu, पूर्णांक idx)
अणु
	__dsu_pmu_counter_पूर्णांकerrupt_enable(idx);
	__dsu_pmu_enable_counter(idx);
पूर्ण

अटल व्योम dsu_pmu_disable_counter(काष्ठा dsu_pmu *dsu_pmu, पूर्णांक idx)
अणु
	__dsu_pmu_disable_counter(idx);
	__dsu_pmu_counter_पूर्णांकerrupt_disable(idx);
पूर्ण

अटल अंतरभूत व्योम dsu_pmu_set_event(काष्ठा dsu_pmu *dsu_pmu,
					काष्ठा perf_event *event)
अणु
	पूर्णांक idx = event->hw.idx;
	अचिन्हित दीर्घ flags;

	अगर (!dsu_pmu_counter_valid(dsu_pmu, idx)) अणु
		dev_err(event->pmu->dev,
			"Trying to set invalid counter %d\n", idx);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	__dsu_pmu_set_event(idx, event->hw.config_base);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);
पूर्ण

अटल व्योम dsu_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 delta, prev_count, new_count;

	करो अणु
		/* We may also be called from the irq handler */
		prev_count = local64_पढ़ो(&hwc->prev_count);
		new_count = dsu_pmu_पढ़ो_counter(event);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev_count, new_count) !=
			prev_count);
	delta = (new_count - prev_count) & DSU_PMU_COUNTER_MASK(hwc->idx);
	local64_add(delta, &event->count);
पूर्ण

अटल व्योम dsu_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	dsu_pmu_event_update(event);
पूर्ण

अटल अंतरभूत u32 dsu_pmu_get_reset_overflow(व्योम)
अणु
	वापस __dsu_pmu_get_reset_overflow();
पूर्ण

/**
 * dsu_pmu_set_event_period: Set the period क्रम the counter.
 *
 * All DSU PMU event counters, except the cycle counter are 32bit
 * counters. To handle हालs of extreme पूर्णांकerrupt latency, we program
 * the counter with half of the max count क्रम the counters.
 */
अटल व्योम dsu_pmu_set_event_period(काष्ठा perf_event *event)
अणु
	पूर्णांक idx = event->hw.idx;
	u64 val = DSU_PMU_COUNTER_MASK(idx) >> 1;

	local64_set(&event->hw.prev_count, val);
	dsu_pmu_ग_लिखो_counter(event, val);
पूर्ण

अटल irqवापस_t dsu_pmu_handle_irq(पूर्णांक irq_num, व्योम *dev)
अणु
	पूर्णांक i;
	bool handled = false;
	काष्ठा dsu_pmu *dsu_pmu = dev;
	काष्ठा dsu_hw_events *hw_events = &dsu_pmu->hw_events;
	अचिन्हित दीर्घ overflow;

	overflow = dsu_pmu_get_reset_overflow();
	अगर (!overflow)
		वापस IRQ_NONE;

	क्रम_each_set_bit(i, &overflow, DSU_PMU_MAX_HW_CNTRS) अणु
		काष्ठा perf_event *event = hw_events->events[i];

		अगर (!event)
			जारी;
		dsu_pmu_event_update(event);
		dsu_pmu_set_event_period(event);
		handled = true;
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम dsu_pmu_start(काष्ठा perf_event *event, पूर्णांक pmu_flags)
अणु
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);

	/* We always reprogram the counter */
	अगर (pmu_flags & PERF_EF_RELOAD)
		WARN_ON(!(event->hw.state & PERF_HES_UPTODATE));
	dsu_pmu_set_event_period(event);
	अगर (event->hw.idx != DSU_PMU_IDX_CYCLE_COUNTER)
		dsu_pmu_set_event(dsu_pmu, event);
	event->hw.state = 0;
	dsu_pmu_enable_counter(dsu_pmu, event->hw.idx);
पूर्ण

अटल व्योम dsu_pmu_stop(काष्ठा perf_event *event, पूर्णांक pmu_flags)
अणु
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);

	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस;
	dsu_pmu_disable_counter(dsu_pmu, event->hw.idx);
	dsu_pmu_event_update(event);
	event->hw.state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
पूर्ण

अटल पूर्णांक dsu_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	काष्ठा dsu_hw_events *hw_events = &dsu_pmu->hw_events;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;

	अगर (WARN_ON_ONCE(!cpumask_test_cpu(smp_processor_id(),
					   &dsu_pmu->associated_cpus)))
		वापस -ENOENT;

	idx = dsu_pmu_get_event_idx(hw_events, event);
	अगर (idx < 0)
		वापस idx;

	hwc->idx = idx;
	hw_events->events[idx] = event;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;

	अगर (flags & PERF_EF_START)
		dsu_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);
	वापस 0;
पूर्ण

अटल व्योम dsu_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	काष्ठा dsu_hw_events *hw_events = &dsu_pmu->hw_events;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	dsu_pmu_stop(event, PERF_EF_UPDATE);
	hw_events->events[idx] = शून्य;
	clear_bit(idx, hw_events->used_mask);
	perf_event_update_userpage(event);
पूर्ण

अटल व्योम dsu_pmu_enable(काष्ठा pmu *pmu)
अणु
	u32 pmcr;
	अचिन्हित दीर्घ flags;
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);

	/* If no counters are added, skip enabling the PMU */
	अगर (biपंचांगap_empty(dsu_pmu->hw_events.used_mask, DSU_PMU_MAX_HW_CNTRS))
		वापस;

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	pmcr = __dsu_pmu_पढ़ो_pmcr();
	pmcr |= CLUSTERPMCR_E;
	__dsu_pmu_ग_लिखो_pmcr(pmcr);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);
पूर्ण

अटल व्योम dsu_pmu_disable(काष्ठा pmu *pmu)
अणु
	u32 pmcr;
	अचिन्हित दीर्घ flags;
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	pmcr = __dsu_pmu_पढ़ो_pmcr();
	pmcr &= ~CLUSTERPMCR_E;
	__dsu_pmu_ग_लिखो_pmcr(pmcr);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);
पूर्ण

अटल bool dsu_pmu_validate_event(काष्ठा pmu *pmu,
				  काष्ठा dsu_hw_events *hw_events,
				  काष्ठा perf_event *event)
अणु
	अगर (is_software_event(event))
		वापस true;
	/* Reject groups spanning multiple HW PMUs. */
	अगर (event->pmu != pmu)
		वापस false;
	वापस dsu_pmu_get_event_idx(hw_events, event) >= 0;
पूर्ण

/*
 * Make sure the group of events can be scheduled at once
 * on the PMU.
 */
अटल bool dsu_pmu_validate_group(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *sibling, *leader = event->group_leader;
	काष्ठा dsu_hw_events fake_hw;

	अगर (event->group_leader == event)
		वापस true;

	स_रखो(fake_hw.used_mask, 0, माप(fake_hw.used_mask));
	अगर (!dsu_pmu_validate_event(event->pmu, &fake_hw, leader))
		वापस false;
	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (!dsu_pmu_validate_event(event->pmu, &fake_hw, sibling))
			वापस false;
	पूर्ण
	वापस dsu_pmu_validate_event(event->pmu, &fake_hw, event);
पूर्ण

अटल पूर्णांक dsu_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* We करोn't support sampling */
	अगर (is_sampling_event(event)) अणु
		dev_dbg(dsu_pmu->pmu.dev, "Can't support sampling events\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* We cannot support task bound events */
	अगर (event->cpu < 0 || event->attach_state & PERF_ATTACH_TASK) अणु
		dev_dbg(dsu_pmu->pmu.dev, "Can't support per-task counters\n");
		वापस -EINVAL;
	पूर्ण

	अगर (has_branch_stack(event)) अणु
		dev_dbg(dsu_pmu->pmu.dev, "Can't support filtering\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cpumask_test_cpu(event->cpu, &dsu_pmu->associated_cpus)) अणु
		dev_dbg(dsu_pmu->pmu.dev,
			 "Requested cpu is not associated with the DSU\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * Choose the current active CPU to पढ़ो the events. We करोn't want
	 * to migrate the event contexts, irq handling etc to the requested
	 * CPU. As दीर्घ as the requested CPU is within the same DSU, we
	 * are fine.
	 */
	event->cpu = cpumask_first(&dsu_pmu->active_cpu);
	अगर (event->cpu >= nr_cpu_ids)
		वापस -EINVAL;
	अगर (!dsu_pmu_validate_group(event))
		वापस -EINVAL;

	event->hw.config_base = event->attr.config;
	वापस 0;
पूर्ण

अटल काष्ठा dsu_pmu *dsu_pmu_alloc(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dsu_pmu *dsu_pmu;

	dsu_pmu = devm_kzalloc(&pdev->dev, माप(*dsu_pmu), GFP_KERNEL);
	अगर (!dsu_pmu)
		वापस ERR_PTR(-ENOMEM);

	raw_spin_lock_init(&dsu_pmu->pmu_lock);
	/*
	 * Initialise the number of counters to -1, until we probe
	 * the real number on a connected CPU.
	 */
	dsu_pmu->num_counters = -1;
	वापस dsu_pmu;
पूर्ण

/**
 * dsu_pmu_dt_get_cpus: Get the list of CPUs in the cluster
 * from device tree.
 */
अटल पूर्णांक dsu_pmu_dt_get_cpus(काष्ठा device *dev, cpumask_t *mask)
अणु
	पूर्णांक i = 0, n, cpu;
	काष्ठा device_node *cpu_node;

	n = of_count_phandle_with_args(dev->of_node, "cpus", शून्य);
	अगर (n <= 0)
		वापस -ENODEV;
	क्रम (; i < n; i++) अणु
		cpu_node = of_parse_phandle(dev->of_node, "cpus", i);
		अगर (!cpu_node)
			अवरोध;
		cpu = of_cpu_node_to_id(cpu_node);
		of_node_put(cpu_node);
		/*
		 * We have to ignore the failures here and जारी scanning
		 * the list to handle हालs where the nr_cpus could be capped
		 * in the running kernel.
		 */
		अगर (cpu < 0)
			जारी;
		cpumask_set_cpu(cpu, mask);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dsu_pmu_acpi_get_cpus: Get the list of CPUs in the cluster
 * from ACPI.
 */
अटल पूर्णांक dsu_pmu_acpi_get_cpus(काष्ठा device *dev, cpumask_t *mask)
अणु
#अगर_घोषित CONFIG_ACPI
	पूर्णांक cpu;

	/*
	 * A dsu pmu node is inside a cluster parent node aदीर्घ with cpu nodes.
	 * We need to find out all cpus that have the same parent with this pmu.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा acpi_device *acpi_dev;
		काष्ठा device *cpu_dev = get_cpu_device(cpu);

		अगर (!cpu_dev)
			जारी;

		acpi_dev = ACPI_COMPANION(cpu_dev);
		अगर (acpi_dev &&
			acpi_dev->parent == ACPI_COMPANION(dev)->parent)
			cpumask_set_cpu(cpu, mask);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * dsu_pmu_probe_pmu: Probe the PMU details on a CPU in the cluster.
 */
अटल व्योम dsu_pmu_probe_pmu(काष्ठा dsu_pmu *dsu_pmu)
अणु
	u64 num_counters;
	u32 cpmceid[2];

	num_counters = (__dsu_pmu_पढ़ो_pmcr() >> CLUSTERPMCR_N_SHIFT) &
						CLUSTERPMCR_N_MASK;
	/* We can only support up to 31 independent counters */
	अगर (WARN_ON(num_counters > 31))
		num_counters = 31;
	dsu_pmu->num_counters = num_counters;
	अगर (!dsu_pmu->num_counters)
		वापस;
	cpmceid[0] = __dsu_pmu_पढ़ो_pmceid(0);
	cpmceid[1] = __dsu_pmu_पढ़ो_pmceid(1);
	biपंचांगap_from_arr32(dsu_pmu->cpmceid_biपंचांगap, cpmceid,
			  DSU_PMU_MAX_COMMON_EVENTS);
पूर्ण

अटल व्योम dsu_pmu_set_active_cpu(पूर्णांक cpu, काष्ठा dsu_pmu *dsu_pmu)
अणु
	cpumask_set_cpu(cpu, &dsu_pmu->active_cpu);
	अगर (irq_set_affinity_hपूर्णांक(dsu_pmu->irq, &dsu_pmu->active_cpu))
		pr_warn("Failed to set irq affinity to %d\n", cpu);
पूर्ण

/*
 * dsu_pmu_init_pmu: Initialise the DSU PMU configurations अगर
 * we haven't करोne it alपढ़ोy.
 */
अटल व्योम dsu_pmu_init_pmu(काष्ठा dsu_pmu *dsu_pmu)
अणु
	अगर (dsu_pmu->num_counters == -1)
		dsu_pmu_probe_pmu(dsu_pmu);
	/* Reset the पूर्णांकerrupt overflow mask */
	dsu_pmu_get_reset_overflow();
पूर्ण

अटल पूर्णांक dsu_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq, rc;
	काष्ठा dsu_pmu *dsu_pmu;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(&pdev->dev);
	अक्षर *name;
	अटल atomic_t pmu_idx = ATOMIC_INIT(-1);

	dsu_pmu = dsu_pmu_alloc(pdev);
	अगर (IS_ERR(dsu_pmu))
		वापस PTR_ERR(dsu_pmu);

	अगर (is_of_node(fwnode))
		rc = dsu_pmu_dt_get_cpus(&pdev->dev, &dsu_pmu->associated_cpus);
	अन्यथा अगर (is_acpi_device_node(fwnode))
		rc = dsu_pmu_acpi_get_cpus(&pdev->dev, &dsu_pmu->associated_cpus);
	अन्यथा
		वापस -ENOENT;

	अगर (rc) अणु
		dev_warn(&pdev->dev, "Failed to parse the CPUs\n");
		वापस rc;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%s_%d",
				PMUNAME, atomic_inc_वापस(&pmu_idx));
	अगर (!name)
		वापस -ENOMEM;
	rc = devm_request_irq(&pdev->dev, irq, dsu_pmu_handle_irq,
			      IRQF_NOBALANCING, name, dsu_pmu);
	अगर (rc) अणु
		dev_warn(&pdev->dev, "Failed to request IRQ %d\n", irq);
		वापस rc;
	पूर्ण

	dsu_pmu->irq = irq;
	platक्रमm_set_drvdata(pdev, dsu_pmu);
	rc = cpuhp_state_add_instance(dsu_pmu_cpuhp_state,
						&dsu_pmu->cpuhp_node);
	अगर (rc)
		वापस rc;

	dsu_pmu->pmu = (काष्ठा pmu) अणु
		.task_ctx_nr	= perf_invalid_context,
		.module		= THIS_MODULE,
		.pmu_enable	= dsu_pmu_enable,
		.pmu_disable	= dsu_pmu_disable,
		.event_init	= dsu_pmu_event_init,
		.add		= dsu_pmu_add,
		.del		= dsu_pmu_del,
		.start		= dsu_pmu_start,
		.stop		= dsu_pmu_stop,
		.पढ़ो		= dsu_pmu_पढ़ो,

		.attr_groups	= dsu_pmu_attr_groups,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	rc = perf_pmu_रेजिस्टर(&dsu_pmu->pmu, name, -1);
	अगर (rc) अणु
		cpuhp_state_हटाओ_instance(dsu_pmu_cpuhp_state,
						 &dsu_pmu->cpuhp_node);
		irq_set_affinity_hपूर्णांक(dsu_pmu->irq, शून्य);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक dsu_pmu_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dsu_pmu *dsu_pmu = platक्रमm_get_drvdata(pdev);

	perf_pmu_unरेजिस्टर(&dsu_pmu->pmu);
	cpuhp_state_हटाओ_instance(dsu_pmu_cpuhp_state, &dsu_pmu->cpuhp_node);
	irq_set_affinity_hपूर्णांक(dsu_pmu->irq, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dsu_pmu_of_match[] = अणु
	अणु .compatible = "arm,dsu-pmu", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dsu_pmu_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id dsu_pmu_acpi_match[] = अणु
	अणु "ARMHD500", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dsu_pmu_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver dsu_pmu_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
		.of_match_table = of_match_ptr(dsu_pmu_of_match),
		.acpi_match_table = ACPI_PTR(dsu_pmu_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = dsu_pmu_device_probe,
	.हटाओ = dsu_pmu_device_हटाओ,
पूर्ण;

अटल पूर्णांक dsu_pmu_cpu_online(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा dsu_pmu *dsu_pmu = hlist_entry_safe(node, काष्ठा dsu_pmu,
						   cpuhp_node);

	अगर (!cpumask_test_cpu(cpu, &dsu_pmu->associated_cpus))
		वापस 0;

	/* If the PMU is alपढ़ोy managed, there is nothing to करो */
	अगर (!cpumask_empty(&dsu_pmu->active_cpu))
		वापस 0;

	dsu_pmu_init_pmu(dsu_pmu);
	dsu_pmu_set_active_cpu(cpu, dsu_pmu);

	वापस 0;
पूर्ण

अटल पूर्णांक dsu_pmu_cpu_tearकरोwn(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	पूर्णांक dst;
	काष्ठा dsu_pmu *dsu_pmu = hlist_entry_safe(node, काष्ठा dsu_pmu,
						   cpuhp_node);

	अगर (!cpumask_test_and_clear_cpu(cpu, &dsu_pmu->active_cpu))
		वापस 0;

	dst = dsu_pmu_get_online_cpu_any_but(dsu_pmu, cpu);
	/* If there are no active CPUs in the DSU, leave IRQ disabled */
	अगर (dst >= nr_cpu_ids) अणु
		irq_set_affinity_hपूर्णांक(dsu_pmu->irq, शून्य);
		वापस 0;
	पूर्ण

	perf_pmu_migrate_context(&dsu_pmu->pmu, cpu, dst);
	dsu_pmu_set_active_cpu(dst, dsu_pmu);

	वापस 0;
पूर्ण

अटल पूर्णांक __init dsu_pmu_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
					DRVNAME,
					dsu_pmu_cpu_online,
					dsu_pmu_cpu_tearकरोwn);
	अगर (ret < 0)
		वापस ret;
	dsu_pmu_cpuhp_state = ret;
	वापस platक्रमm_driver_रेजिस्टर(&dsu_pmu_driver);
पूर्ण

अटल व्योम __निकास dsu_pmu_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&dsu_pmu_driver);
	cpuhp_हटाओ_multi_state(dsu_pmu_cpuhp_state);
पूर्ण

module_init(dsu_pmu_init);
module_निकास(dsu_pmu_निकास);

MODULE_DESCRIPTION("Perf driver for ARM DynamIQ Shared Unit");
MODULE_AUTHOR("Suzuki K Poulose <suzuki.poulose@arm.com>");
MODULE_LICENSE("GPL v2");
