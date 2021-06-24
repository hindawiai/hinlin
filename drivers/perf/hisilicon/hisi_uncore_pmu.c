<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon SoC Hardware event counters support
 *
 * Copyright (C) 2017 Hisilicon Limited
 * Author: Anurup M <anurup.m@huawei.com>
 *         Shaokun Zhang <zhangshaokun@hisilicon.com>
 *
 * This code is based on the uncore PMUs like arm-cci and arm-ccn.
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/local64.h>

#समावेश "hisi_uncore_pmu.h"

#घोषणा HISI_GET_EVENTID(ev) (ev->hw.config_base & 0xff)
#घोषणा HISI_MAX_PERIOD(nr) (GENMASK_ULL((nr) - 1, 0))

/*
 * PMU क्रमmat attributes
 */
sमाप_प्रकार hisi_क्रमmat_sysfs_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);

	वापस sysfs_emit(buf, "%s\n", (अक्षर *)eattr->var);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_क्रमmat_sysfs_show);

/*
 * PMU event attributes
 */
sमाप_प्रकार hisi_event_sysfs_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा dev_ext_attribute *eattr;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);

	वापस sysfs_emit(page, "config=0x%lx\n", (अचिन्हित दीर्घ)eattr->var);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_event_sysfs_show);

/*
 * sysfs cpumask attributes. For uncore PMU, we only have a single CPU to show
 */
sमाप_प्रकार hisi_cpumask_sysfs_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(dev_get_drvdata(dev));

	वापस sysfs_emit(buf, "%d\n", hisi_pmu->on_cpu);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_cpumask_sysfs_show);

अटल bool hisi_validate_event_group(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *sibling, *leader = event->group_leader;
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	/* Include count क्रम the event */
	पूर्णांक counters = 1;

	अगर (!is_software_event(leader)) अणु
		/*
		 * We must NOT create groups containing mixed PMUs, although
		 * software events are acceptable
		 */
		अगर (leader->pmu != event->pmu)
			वापस false;

		/* Increment counter क्रम the leader */
		अगर (leader != event)
			counters++;
	पूर्ण

	क्रम_each_sibling_event(sibling, event->group_leader) अणु
		अगर (is_software_event(sibling))
			जारी;
		अगर (sibling->pmu != event->pmu)
			वापस false;
		/* Increment counter क्रम each sibling */
		counters++;
	पूर्ण

	/* The group can not count events more than the counters in the HW */
	वापस counters <= hisi_pmu->num_counters;
पूर्ण

पूर्णांक hisi_uncore_pmu_get_event_idx(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	अचिन्हित दीर्घ *used_mask = hisi_pmu->pmu_events.used_mask;
	u32 num_counters = hisi_pmu->num_counters;
	पूर्णांक idx;

	idx = find_first_zero_bit(used_mask, num_counters);
	अगर (idx == num_counters)
		वापस -EAGAIN;

	set_bit(idx, used_mask);

	वापस idx;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_get_event_idx);

sमाप_प्रकार hisi_uncore_pmu_identअगरier_attr_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *page)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(dev_get_drvdata(dev));

	वापस sysfs_emit(page, "0x%08x\n", hisi_pmu->identअगरier);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_identअगरier_attr_show);

अटल व्योम hisi_uncore_pmu_clear_event_idx(काष्ठा hisi_pmu *hisi_pmu, पूर्णांक idx)
अणु
	clear_bit(idx, hisi_pmu->pmu_events.used_mask);
पूर्ण

अटल irqवापस_t hisi_uncore_pmu_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hisi_pmu *hisi_pmu = data;
	काष्ठा perf_event *event;
	अचिन्हित दीर्घ overflown;
	पूर्णांक idx;

	overflown = hisi_pmu->ops->get_पूर्णांक_status(hisi_pmu);
	अगर (!overflown)
		वापस IRQ_NONE;

	/*
	 * Find the counter index which overflowed अगर the bit was set
	 * and handle it.
	 */
	क्रम_each_set_bit(idx, &overflown, hisi_pmu->num_counters) अणु
		/* Write 1 to clear the IRQ status flag */
		hisi_pmu->ops->clear_पूर्णांक_status(hisi_pmu, idx);
		/* Get the corresponding event काष्ठा */
		event = hisi_pmu->pmu_events.hw_events[idx];
		अगर (!event)
			जारी;

		hisi_uncore_pmu_event_update(event);
		hisi_uncore_pmu_set_event_period(event);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक hisi_uncore_pmu_init_irq(काष्ठा hisi_pmu *hisi_pmu,
			     काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, hisi_uncore_pmu_isr,
			       IRQF_NOBALANCING | IRQF_NO_THREAD,
			       dev_name(&pdev->dev), hisi_pmu);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Fail to request IRQ: %d ret: %d.\n", irq, ret);
		वापस ret;
	पूर्ण

	hisi_pmu->irq = irq;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_init_irq);

पूर्णांक hisi_uncore_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hisi_pmu *hisi_pmu;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/*
	 * We करो not support sampling as the counters are all
	 * shared by all CPU cores in a CPU die(SCCL). Also we
	 * करो not support attach to a task(per-process mode)
	 */
	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EOPNOTSUPP;

	/*
	 *  The uncore counters not specअगरic to any CPU, so cannot
	 *  support per-task
	 */
	अगर (event->cpu < 0)
		वापस -EINVAL;

	/*
	 * Validate अगर the events in group करोes not exceed the
	 * available counters in hardware.
	 */
	अगर (!hisi_validate_event_group(event))
		वापस -EINVAL;

	hisi_pmu = to_hisi_pmu(event->pmu);
	अगर (event->attr.config > hisi_pmu->check_event)
		वापस -EINVAL;

	अगर (hisi_pmu->on_cpu == -1)
		वापस -EINVAL;
	/*
	 * We करोn't assign an index until we actually place the event onto
	 * hardware. Use -1 to signअगरy that we haven't decided where to put it
	 * yet.
	 */
	hwc->idx		= -1;
	hwc->config_base	= event->attr.config;

	/* Enक्रमce to use the same CPU क्रम all events in this PMU */
	event->cpu = hisi_pmu->on_cpu;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_event_init);

/*
 * Set the counter to count the event that we're पूर्णांकerested in,
 * and enable पूर्णांकerrupt and counter.
 */
अटल व्योम hisi_uncore_pmu_enable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	hisi_pmu->ops->ग_लिखो_evtype(hisi_pmu, hwc->idx,
				    HISI_GET_EVENTID(event));

	अगर (hisi_pmu->ops->enable_filter)
		hisi_pmu->ops->enable_filter(event);

	hisi_pmu->ops->enable_counter_पूर्णांक(hisi_pmu, hwc);
	hisi_pmu->ops->enable_counter(hisi_pmu, hwc);
पूर्ण

/*
 * Disable counter and पूर्णांकerrupt.
 */
अटल व्योम hisi_uncore_pmu_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	hisi_pmu->ops->disable_counter(hisi_pmu, hwc);
	hisi_pmu->ops->disable_counter_पूर्णांक(hisi_pmu, hwc);

	अगर (hisi_pmu->ops->disable_filter)
		hisi_pmu->ops->disable_filter(event);
पूर्ण

व्योम hisi_uncore_pmu_set_event_period(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	/*
	 * The HiSilicon PMU counters support 32 bits or 48 bits, depending on
	 * the PMU. We reduce it to 2^(counter_bits - 1) to account क्रम the
	 * extreme पूर्णांकerrupt latency. So we could hopefully handle the overflow
	 * पूर्णांकerrupt beक्रमe another 2^(counter_bits - 1) events occur and the
	 * counter overtakes its previous value.
	 */
	u64 val = BIT_ULL(hisi_pmu->counter_bits - 1);

	local64_set(&hwc->prev_count, val);
	/* Write start value to the hardware event counter */
	hisi_pmu->ops->ग_लिखो_counter(hisi_pmu, hwc, val);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_set_event_period);

व्योम hisi_uncore_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 delta, prev_raw_count, new_raw_count;

	करो अणु
		/* Read the count from the counter रेजिस्टर */
		new_raw_count = hisi_pmu->ops->पढ़ो_counter(hisi_pmu, hwc);
		prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
				 new_raw_count) != prev_raw_count);
	/*
	 * compute the delta
	 */
	delta = (new_raw_count - prev_raw_count) &
		HISI_MAX_PERIOD(hisi_pmu->counter_bits);
	local64_add(delta, &event->count);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_event_update);

व्योम hisi_uncore_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		वापस;

	WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));
	hwc->state = 0;
	hisi_uncore_pmu_set_event_period(event);

	अगर (flags & PERF_EF_RELOAD) अणु
		u64 prev_raw_count =  local64_पढ़ो(&hwc->prev_count);

		hisi_pmu->ops->ग_लिखो_counter(hisi_pmu, hwc, prev_raw_count);
	पूर्ण

	hisi_uncore_pmu_enable_event(event);
	perf_event_update_userpage(event);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_start);

व्योम hisi_uncore_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	hisi_uncore_pmu_disable_event(event);
	WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
	hwc->state |= PERF_HES_STOPPED;

	अगर (hwc->state & PERF_HES_UPTODATE)
		वापस;

	/* Read hardware counter and update the perf counter statistics */
	hisi_uncore_pmu_event_update(event);
	hwc->state |= PERF_HES_UPTODATE;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_stop);

पूर्णांक hisi_uncore_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;

	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;

	/* Get an available counter index क्रम counting */
	idx = hisi_pmu->ops->get_event_idx(event);
	अगर (idx < 0)
		वापस idx;

	event->hw.idx = idx;
	hisi_pmu->pmu_events.hw_events[idx] = event;

	अगर (flags & PERF_EF_START)
		hisi_uncore_pmu_start(event, PERF_EF_RELOAD);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_add);

व्योम hisi_uncore_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	hisi_uncore_pmu_stop(event, PERF_EF_UPDATE);
	hisi_uncore_pmu_clear_event_idx(hisi_pmu, hwc->idx);
	perf_event_update_userpage(event);
	hisi_pmu->pmu_events.hw_events[hwc->idx] = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_del);

व्योम hisi_uncore_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	/* Read hardware counter and update the perf counter statistics */
	hisi_uncore_pmu_event_update(event);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_पढ़ो);

व्योम hisi_uncore_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(pmu);
	पूर्णांक enabled = biपंचांगap_weight(hisi_pmu->pmu_events.used_mask,
				    hisi_pmu->num_counters);

	अगर (!enabled)
		वापस;

	hisi_pmu->ops->start_counters(hisi_pmu);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_enable);

व्योम hisi_uncore_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा hisi_pmu *hisi_pmu = to_hisi_pmu(pmu);

	hisi_pmu->ops->stop_counters(hisi_pmu);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_disable);


/*
 * The Super CPU Cluster (SCCL) and CPU Cluster (CCL) IDs can be
 * determined from the MPIDR_EL1, but the encoding varies by CPU:
 *
 * - For MT variants of TSV110:
 *   SCCL is Aff2[7:3], CCL is Aff2[2:0]
 *
 * - For other MT parts:
 *   SCCL is Aff3[7:0], CCL is Aff2[7:0]
 *
 * - For non-MT parts:
 *   SCCL is Aff2[7:0], CCL is Aff1[7:0]
 */
अटल व्योम hisi_पढ़ो_sccl_and_ccl_id(पूर्णांक *scclp, पूर्णांक *cclp)
अणु
	u64 mpidr = पढ़ो_cpuid_mpidr();
	पूर्णांक aff3 = MPIDR_AFFINITY_LEVEL(mpidr, 3);
	पूर्णांक aff2 = MPIDR_AFFINITY_LEVEL(mpidr, 2);
	पूर्णांक aff1 = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	bool mt = mpidr & MPIDR_MT_BITMASK;
	पूर्णांक sccl, ccl;

	अगर (mt && पढ़ो_cpuid_part_number() == HISI_CPU_PART_TSV110) अणु
		sccl = aff2 >> 3;
		ccl = aff2 & 0x7;
	पूर्ण अन्यथा अगर (mt) अणु
		sccl = aff3;
		ccl = aff2;
	पूर्ण अन्यथा अणु
		sccl = aff2;
		ccl = aff1;
	पूर्ण

	अगर (scclp)
		*scclp = sccl;
	अगर (cclp)
		*cclp = ccl;
पूर्ण

/*
 * Check whether the CPU is associated with this uncore PMU
 */
अटल bool hisi_pmu_cpu_is_associated_pmu(काष्ठा hisi_pmu *hisi_pmu)
अणु
	पूर्णांक sccl_id, ccl_id;

	अगर (hisi_pmu->ccl_id == -1) अणु
		/* If CCL_ID is -1, the PMU only shares the same SCCL */
		hisi_पढ़ो_sccl_and_ccl_id(&sccl_id, शून्य);

		वापस sccl_id == hisi_pmu->sccl_id;
	पूर्ण

	hisi_पढ़ो_sccl_and_ccl_id(&sccl_id, &ccl_id);

	वापस sccl_id == hisi_pmu->sccl_id && ccl_id == hisi_pmu->ccl_id;
पूर्ण

पूर्णांक hisi_uncore_pmu_online_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा hisi_pmu *hisi_pmu = hlist_entry_safe(node, काष्ठा hisi_pmu,
						     node);

	अगर (!hisi_pmu_cpu_is_associated_pmu(hisi_pmu))
		वापस 0;

	cpumask_set_cpu(cpu, &hisi_pmu->associated_cpus);

	/* If another CPU is alपढ़ोy managing this PMU, simply वापस. */
	अगर (hisi_pmu->on_cpu != -1)
		वापस 0;

	/* Use this CPU in cpumask क्रम event counting */
	hisi_pmu->on_cpu = cpu;

	/* Overflow पूर्णांकerrupt also should use the same CPU */
	WARN_ON(irq_set_affinity_hपूर्णांक(hisi_pmu->irq, cpumask_of(cpu)));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_online_cpu);

पूर्णांक hisi_uncore_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा hisi_pmu *hisi_pmu = hlist_entry_safe(node, काष्ठा hisi_pmu,
						     node);
	cpumask_t pmu_online_cpus;
	अचिन्हित पूर्णांक target;

	अगर (!cpumask_test_and_clear_cpu(cpu, &hisi_pmu->associated_cpus))
		वापस 0;

	/* Nothing to करो अगर this CPU करोesn't own the PMU */
	अगर (hisi_pmu->on_cpu != cpu)
		वापस 0;

	/* Give up ownership of the PMU */
	hisi_pmu->on_cpu = -1;

	/* Choose a new CPU to migrate ownership of the PMU to */
	cpumask_and(&pmu_online_cpus, &hisi_pmu->associated_cpus,
		    cpu_online_mask);
	target = cpumask_any_but(&pmu_online_cpus, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	perf_pmu_migrate_context(&hisi_pmu->pmu, cpu, target);
	/* Use this CPU क्रम event counting */
	hisi_pmu->on_cpu = target;
	WARN_ON(irq_set_affinity_hपूर्णांक(hisi_pmu->irq, cpumask_of(target)));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_uncore_pmu_offline_cpu);

MODULE_LICENSE("GPL v2");
