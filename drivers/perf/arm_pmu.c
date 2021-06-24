<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#अघोषित DEBUG

/*
 * ARM perक्रमmance counter support.
 *
 * Copyright (C) 2009 picoChip Designs, Ltd., Jamie Iles
 * Copyright (C) 2010 ARM Ltd., Will Deacon <will.deacon@arm.com>
 *
 * This code is based on the sparc64 perf event code, which is in turn based
 * on the x86 code.
 */
#घोषणा pr_fmt(fmt) "hw perfevents: " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/perf/arm_pmu.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqdesc.h>

#समावेश <यंत्र/irq_regs.h>

अटल पूर्णांक armpmu_count_irq_users(स्थिर पूर्णांक irq);

काष्ठा pmu_irq_ops अणु
	व्योम (*enable_pmuirq)(अचिन्हित पूर्णांक irq);
	व्योम (*disable_pmuirq)(अचिन्हित पूर्णांक irq);
	व्योम (*मुक्त_pmuirq)(अचिन्हित पूर्णांक irq, पूर्णांक cpu, व्योम __percpu *devid);
पूर्ण;

अटल व्योम armpmu_मुक्त_pmuirq(अचिन्हित पूर्णांक irq, पूर्णांक cpu, व्योम __percpu *devid)
अणु
	मुक्त_irq(irq, per_cpu_ptr(devid, cpu));
पूर्ण

अटल स्थिर काष्ठा pmu_irq_ops pmuirq_ops = अणु
	.enable_pmuirq = enable_irq,
	.disable_pmuirq = disable_irq_nosync,
	.मुक्त_pmuirq = armpmu_मुक्त_pmuirq
पूर्ण;

अटल व्योम armpmu_मुक्त_pmunmi(अचिन्हित पूर्णांक irq, पूर्णांक cpu, व्योम __percpu *devid)
अणु
	मुक्त_nmi(irq, per_cpu_ptr(devid, cpu));
पूर्ण

अटल स्थिर काष्ठा pmu_irq_ops pmunmi_ops = अणु
	.enable_pmuirq = enable_nmi,
	.disable_pmuirq = disable_nmi_nosync,
	.मुक्त_pmuirq = armpmu_मुक्त_pmunmi
पूर्ण;

अटल व्योम armpmu_enable_percpu_pmuirq(अचिन्हित पूर्णांक irq)
अणु
	enable_percpu_irq(irq, IRQ_TYPE_NONE);
पूर्ण

अटल व्योम armpmu_मुक्त_percpu_pmuirq(अचिन्हित पूर्णांक irq, पूर्णांक cpu,
				   व्योम __percpu *devid)
अणु
	अगर (armpmu_count_irq_users(irq) == 1)
		मुक्त_percpu_irq(irq, devid);
पूर्ण

अटल स्थिर काष्ठा pmu_irq_ops percpu_pmuirq_ops = अणु
	.enable_pmuirq = armpmu_enable_percpu_pmuirq,
	.disable_pmuirq = disable_percpu_irq,
	.मुक्त_pmuirq = armpmu_मुक्त_percpu_pmuirq
पूर्ण;

अटल व्योम armpmu_enable_percpu_pmunmi(अचिन्हित पूर्णांक irq)
अणु
	अगर (!prepare_percpu_nmi(irq))
		enable_percpu_nmi(irq, IRQ_TYPE_NONE);
पूर्ण

अटल व्योम armpmu_disable_percpu_pmunmi(अचिन्हित पूर्णांक irq)
अणु
	disable_percpu_nmi(irq);
	tearकरोwn_percpu_nmi(irq);
पूर्ण

अटल व्योम armpmu_मुक्त_percpu_pmunmi(अचिन्हित पूर्णांक irq, पूर्णांक cpu,
				      व्योम __percpu *devid)
अणु
	अगर (armpmu_count_irq_users(irq) == 1)
		मुक्त_percpu_nmi(irq, devid);
पूर्ण

अटल स्थिर काष्ठा pmu_irq_ops percpu_pmunmi_ops = अणु
	.enable_pmuirq = armpmu_enable_percpu_pmunmi,
	.disable_pmuirq = armpmu_disable_percpu_pmunmi,
	.मुक्त_pmuirq = armpmu_मुक्त_percpu_pmunmi
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा arm_pmu *, cpu_armpmu);
अटल DEFINE_PER_CPU(पूर्णांक, cpu_irq);
अटल DEFINE_PER_CPU(स्थिर काष्ठा pmu_irq_ops *, cpu_irq_ops);

अटल bool has_nmi;

अटल अंतरभूत u64 arm_pmu_event_max_period(काष्ठा perf_event *event)
अणु
	अगर (event->hw.flags & ARMPMU_EVT_64BIT)
		वापस GENMASK_ULL(63, 0);
	अन्यथा
		वापस GENMASK_ULL(31, 0);
पूर्ण

अटल पूर्णांक
armpmu_map_cache_event(स्थिर अचिन्हित (*cache_map)
				      [PERF_COUNT_HW_CACHE_MAX]
				      [PERF_COUNT_HW_CACHE_OP_MAX]
				      [PERF_COUNT_HW_CACHE_RESULT_MAX],
		       u64 config)
अणु
	अचिन्हित पूर्णांक cache_type, cache_op, cache_result, ret;

	cache_type = (config >>  0) & 0xff;
	अगर (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		वापस -EINVAL;

	cache_op = (config >>  8) & 0xff;
	अगर (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		वापस -EINVAL;

	cache_result = (config >> 16) & 0xff;
	अगर (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;

	अगर (!cache_map)
		वापस -ENOENT;

	ret = (पूर्णांक)(*cache_map)[cache_type][cache_op][cache_result];

	अगर (ret == CACHE_OP_UNSUPPORTED)
		वापस -ENOENT;

	वापस ret;
पूर्ण

अटल पूर्णांक
armpmu_map_hw_event(स्थिर अचिन्हित (*event_map)[PERF_COUNT_HW_MAX], u64 config)
अणु
	पूर्णांक mapping;

	अगर (config >= PERF_COUNT_HW_MAX)
		वापस -EINVAL;

	अगर (!event_map)
		वापस -ENOENT;

	mapping = (*event_map)[config];
	वापस mapping == HW_OP_UNSUPPORTED ? -ENOENT : mapping;
पूर्ण

अटल पूर्णांक
armpmu_map_raw_event(u32 raw_event_mask, u64 config)
अणु
	वापस (पूर्णांक)(config & raw_event_mask);
पूर्ण

पूर्णांक
armpmu_map_event(काष्ठा perf_event *event,
		 स्थिर अचिन्हित (*event_map)[PERF_COUNT_HW_MAX],
		 स्थिर अचिन्हित (*cache_map)
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX],
		 u32 raw_event_mask)
अणु
	u64 config = event->attr.config;
	पूर्णांक type = event->attr.type;

	अगर (type == event->pmu->type)
		वापस armpmu_map_raw_event(raw_event_mask, config);

	चयन (type) अणु
	हाल PERF_TYPE_HARDWARE:
		वापस armpmu_map_hw_event(event_map, config);
	हाल PERF_TYPE_HW_CACHE:
		वापस armpmu_map_cache_event(cache_map, config);
	हाल PERF_TYPE_RAW:
		वापस armpmu_map_raw_event(raw_event_mask, config);
	पूर्ण

	वापस -ENOENT;
पूर्ण

पूर्णांक armpmu_event_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	s64 left = local64_पढ़ो(&hwc->period_left);
	s64 period = hwc->sample_period;
	u64 max_period;
	पूर्णांक ret = 0;

	max_period = arm_pmu_event_max_period(event);
	अगर (unlikely(left <= -period)) अणु
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	अगर (unlikely(left <= 0)) अणु
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	/*
	 * Limit the maximum period to prevent the counter value
	 * from overtaking the one we are about to program. In
	 * effect we are reducing max_period to account क्रम
	 * पूर्णांकerrupt latency (and we are being very conservative).
	 */
	अगर (left > (max_period >> 1))
		left = (max_period >> 1);

	local64_set(&hwc->prev_count, (u64)-left);

	armpmu->ग_लिखो_counter(event, (u64)(-left) & max_period);

	perf_event_update_userpage(event);

	वापस ret;
पूर्ण

u64 armpmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 delta, prev_raw_count, new_raw_count;
	u64 max_period = arm_pmu_event_max_period(event);

again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	new_raw_count = armpmu->पढ़ो_counter(event);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			     new_raw_count) != prev_raw_count)
		जाओ again;

	delta = (new_raw_count - prev_raw_count) & max_period;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	वापस new_raw_count;
पूर्ण

अटल व्योम
armpmu_पढ़ो(काष्ठा perf_event *event)
अणु
	armpmu_event_update(event);
पूर्ण

अटल व्योम
armpmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	/*
	 * ARM pmu always has to update the counter, so ignore
	 * PERF_EF_UPDATE, see comments in armpmu_start().
	 */
	अगर (!(hwc->state & PERF_HES_STOPPED)) अणु
		armpmu->disable(event);
		armpmu_event_update(event);
		hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल व्योम armpmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	/*
	 * ARM pmu always has to reprogram the period, so ignore
	 * PERF_EF_RELOAD, see the comment below.
	 */
	अगर (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;
	/*
	 * Set the period again. Some counters can't be stopped, so when we
	 * were stopped we simply disabled the IRQ source and the counter
	 * may have been left counting. If we करोn't करो this step then we may
	 * get an पूर्णांकerrupt too soon or *way* too late अगर the overflow has
	 * happened since disabling.
	 */
	armpmu_event_set_period(event);
	armpmu->enable(event);
पूर्ण

अटल व्योम
armpmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);
	काष्ठा pmu_hw_events *hw_events = this_cpu_ptr(armpmu->hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	armpmu_stop(event, PERF_EF_UPDATE);
	hw_events->events[idx] = शून्य;
	armpmu->clear_event_idx(hw_events, event);
	perf_event_update_userpage(event);
	/* Clear the allocated counter */
	hwc->idx = -1;
पूर्ण

अटल पूर्णांक
armpmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);
	काष्ठा pmu_hw_events *hw_events = this_cpu_ptr(armpmu->hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;

	/* An event following a process won't be stopped earlier */
	अगर (!cpumask_test_cpu(smp_processor_id(), &armpmu->supported_cpus))
		वापस -ENOENT;

	/* If we करोn't have a space क्रम the counter then finish early. */
	idx = armpmu->get_event_idx(hw_events, event);
	अगर (idx < 0)
		वापस idx;

	/*
	 * If there is an event in the counter we are going to use then make
	 * sure it is disabled.
	 */
	event->hw.idx = idx;
	armpmu->disable(event);
	hw_events->events[idx] = event;

	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	अगर (flags & PERF_EF_START)
		armpmu_start(event, PERF_EF_RELOAD);

	/* Propagate our changes to the userspace mapping. */
	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_event(काष्ठा pmu *pmu, काष्ठा pmu_hw_events *hw_events,
			       काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *armpmu;

	अगर (is_software_event(event))
		वापस 1;

	/*
	 * Reject groups spanning multiple HW PMUs (e.g. CPU + CCI). The
	 * core perf code won't check that the pmu->ctx == leader->ctx
	 * until after pmu->event_init(event).
	 */
	अगर (event->pmu != pmu)
		वापस 0;

	अगर (event->state < PERF_EVENT_STATE_OFF)
		वापस 1;

	अगर (event->state == PERF_EVENT_STATE_OFF && !event->attr.enable_on_exec)
		वापस 1;

	armpmu = to_arm_pmu(event->pmu);
	वापस armpmu->get_event_idx(hw_events, event) >= 0;
पूर्ण

अटल पूर्णांक
validate_group(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *sibling, *leader = event->group_leader;
	काष्ठा pmu_hw_events fake_pmu;

	/*
	 * Initialise the fake PMU. We only need to populate the
	 * used_mask क्रम the purposes of validation.
	 */
	स_रखो(&fake_pmu.used_mask, 0, माप(fake_pmu.used_mask));

	अगर (!validate_event(event->pmu, &fake_pmu, leader))
		वापस -EINVAL;

	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (!validate_event(event->pmu, &fake_pmu, sibling))
			वापस -EINVAL;
	पूर्ण

	अगर (!validate_event(event->pmu, &fake_pmu, event))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल irqवापस_t armpmu_dispatch_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा arm_pmu *armpmu;
	पूर्णांक ret;
	u64 start_घड़ी, finish_घड़ी;

	/*
	 * we request the IRQ with a (possibly percpu) काष्ठा arm_pmu**, but
	 * the handlers expect a काष्ठा arm_pmu*. The percpu_irq framework will
	 * करो any necessary shअगरting, we just need to perक्रमm the first
	 * dereference.
	 */
	armpmu = *(व्योम **)dev;
	अगर (WARN_ON_ONCE(!armpmu))
		वापस IRQ_NONE;

	start_घड़ी = sched_घड़ी();
	ret = armpmu->handle_irq(armpmu);
	finish_घड़ी = sched_घड़ी();

	perf_sample_event_took(finish_घड़ी - start_घड़ी);
	वापस ret;
पूर्ण

अटल पूर्णांक
__hw_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक mapping;

	hwc->flags = 0;
	mapping = armpmu->map_event(event);

	अगर (mapping < 0) अणु
		pr_debug("event %x:%llx not supported\n", event->attr.type,
			 event->attr.config);
		वापस mapping;
	पूर्ण

	/*
	 * We करोn't assign an index until we actually place the event onto
	 * hardware. Use -1 to signअगरy that we haven't decided where to put it
	 * yet. For SMP प्रणालीs, each core has it's own PMU so we can't करो any
	 * clever allocation or स्थिरraपूर्णांकs checking at this poपूर्णांक.
	 */
	hwc->idx		= -1;
	hwc->config_base	= 0;
	hwc->config		= 0;
	hwc->event_base		= 0;

	/*
	 * Check whether we need to exclude the counter from certain modes.
	 */
	अगर (armpmu->set_event_filter &&
	    armpmu->set_event_filter(hwc, &event->attr)) अणु
		pr_debug("ARM performance counters do not support "
			 "mode exclusion\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * Store the event encoding पूर्णांकo the config_base field.
	 */
	hwc->config_base	    |= (अचिन्हित दीर्घ)mapping;

	अगर (!is_sampling_event(event)) अणु
		/*
		 * For non-sampling runs, limit the sample_period to half
		 * of the counter width. That way, the new counter value
		 * is far less likely to overtake the previous one unless
		 * you have some serious IRQ latency issues.
		 */
		hwc->sample_period  = arm_pmu_event_max_period(event) >> 1;
		hwc->last_period    = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	पूर्ण

	अगर (event->group_leader != event) अणु
		अगर (validate_group(event) != 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक armpmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);

	/*
	 * Reject CPU-affine events क्रम CPUs that are of a dअगरferent class to
	 * that which this PMU handles. Process-following events (where
	 * event->cpu == -1) can be migrated between CPUs, and thus we have to
	 * reject them later (in armpmu_add) अगर they're scheduled on a
	 * dअगरferent class of CPU.
	 */
	अगर (event->cpu != -1 &&
		!cpumask_test_cpu(event->cpu, &armpmu->supported_cpus))
		वापस -ENOENT;

	/* करोes not support taken branch sampling */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	अगर (armpmu->map_event(event) == -ENOENT)
		वापस -ENOENT;

	वापस __hw_perf_event_init(event);
पूर्ण

अटल व्योम armpmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(pmu);
	काष्ठा pmu_hw_events *hw_events = this_cpu_ptr(armpmu->hw_events);
	पूर्णांक enabled = biपंचांगap_weight(hw_events->used_mask, armpmu->num_events);

	/* For task-bound events we may be called on other CPUs */
	अगर (!cpumask_test_cpu(smp_processor_id(), &armpmu->supported_cpus))
		वापस;

	अगर (enabled)
		armpmu->start(armpmu);
पूर्ण

अटल व्योम armpmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(pmu);

	/* For task-bound events we may be called on other CPUs */
	अगर (!cpumask_test_cpu(smp_processor_id(), &armpmu->supported_cpus))
		वापस;

	armpmu->stop(armpmu);
पूर्ण

/*
 * In heterogeneous प्रणालीs, events are specअगरic to a particular
 * microarchitecture, and aren't suitable क्रम another. Thus, only match CPUs of
 * the same microarchitecture.
 */
अटल पूर्णांक armpmu_filter_match(काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक ret;

	ret = cpumask_test_cpu(cpu, &armpmu->supported_cpus);
	अगर (ret && armpmu->filter_match)
		वापस armpmu->filter_match(event);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार armpmu_cpumask_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arm_pmu *armpmu = to_arm_pmu(dev_get_drvdata(dev));
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &armpmu->supported_cpus);
पूर्ण

अटल DEVICE_ATTR(cpus, S_IRUGO, armpmu_cpumask_show, शून्य);

अटल काष्ठा attribute *armpmu_common_attrs[] = अणु
	&dev_attr_cpus.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group armpmu_common_attr_group = अणु
	.attrs = armpmu_common_attrs,
पूर्ण;

अटल पूर्णांक armpmu_count_irq_users(स्थिर पूर्णांक irq)
अणु
	पूर्णांक cpu, count = 0;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (per_cpu(cpu_irq, cpu) == irq)
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा pmu_irq_ops *armpmu_find_irq_ops(पूर्णांक irq)
अणु
	स्थिर काष्ठा pmu_irq_ops *ops = शून्य;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (per_cpu(cpu_irq, cpu) != irq)
			जारी;

		ops = per_cpu(cpu_irq_ops, cpu);
		अगर (ops)
			अवरोध;
	पूर्ण

	वापस ops;
पूर्ण

व्योम armpmu_मुक्त_irq(पूर्णांक irq, पूर्णांक cpu)
अणु
	अगर (per_cpu(cpu_irq, cpu) == 0)
		वापस;
	अगर (WARN_ON(irq != per_cpu(cpu_irq, cpu)))
		वापस;

	per_cpu(cpu_irq_ops, cpu)->मुक्त_pmuirq(irq, cpu, &cpu_armpmu);

	per_cpu(cpu_irq, cpu) = 0;
	per_cpu(cpu_irq_ops, cpu) = शून्य;
पूर्ण

पूर्णांक armpmu_request_irq(पूर्णांक irq, पूर्णांक cpu)
अणु
	पूर्णांक err = 0;
	स्थिर irq_handler_t handler = armpmu_dispatch_irq;
	स्थिर काष्ठा pmu_irq_ops *irq_ops;

	अगर (!irq)
		वापस 0;

	अगर (!irq_is_percpu_devid(irq)) अणु
		अचिन्हित दीर्घ irq_flags;

		err = irq_क्रमce_affinity(irq, cpumask_of(cpu));

		अगर (err && num_possible_cpus() > 1) अणु
			pr_warn("unable to set irq affinity (irq=%d, cpu=%u)\n",
				irq, cpu);
			जाओ err_out;
		पूर्ण

		irq_flags = IRQF_PERCPU |
			    IRQF_NOBALANCING |
			    IRQF_NO_THREAD;

		irq_set_status_flags(irq, IRQ_NOAUTOEN);

		err = request_nmi(irq, handler, irq_flags, "arm-pmu",
				  per_cpu_ptr(&cpu_armpmu, cpu));

		/* If cannot get an NMI, get a normal पूर्णांकerrupt */
		अगर (err) अणु
			err = request_irq(irq, handler, irq_flags, "arm-pmu",
					  per_cpu_ptr(&cpu_armpmu, cpu));
			irq_ops = &pmuirq_ops;
		पूर्ण अन्यथा अणु
			has_nmi = true;
			irq_ops = &pmunmi_ops;
		पूर्ण
	पूर्ण अन्यथा अगर (armpmu_count_irq_users(irq) == 0) अणु
		err = request_percpu_nmi(irq, handler, "arm-pmu", &cpu_armpmu);

		/* If cannot get an NMI, get a normal पूर्णांकerrupt */
		अगर (err) अणु
			err = request_percpu_irq(irq, handler, "arm-pmu",
						 &cpu_armpmu);
			irq_ops = &percpu_pmuirq_ops;
		पूर्ण अन्यथा अणु
			has_nmi= true;
			irq_ops = &percpu_pmunmi_ops;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Per cpudevid irq was alपढ़ोy requested by another CPU */
		irq_ops = armpmu_find_irq_ops(irq);

		अगर (WARN_ON(!irq_ops))
			err = -EINVAL;
	पूर्ण

	अगर (err)
		जाओ err_out;

	per_cpu(cpu_irq, cpu) = irq;
	per_cpu(cpu_irq_ops, cpu) = irq_ops;
	वापस 0;

err_out:
	pr_err("unable to request IRQ%d for ARM PMU counters\n", irq);
	वापस err;
पूर्ण

अटल पूर्णांक armpmu_get_cpu_irq(काष्ठा arm_pmu *pmu, पूर्णांक cpu)
अणु
	काष्ठा pmu_hw_events __percpu *hw_events = pmu->hw_events;
	वापस per_cpu(hw_events->irq, cpu);
पूर्ण

/*
 * PMU hardware loses all context when a CPU goes offline.
 * When a CPU is hotplugged back in, since some hardware रेजिस्टरs are
 * UNKNOWN at reset, the PMU must be explicitly reset to aव्योम पढ़ोing
 * junk values out of them.
 */
अटल पूर्णांक arm_perf_starting_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा arm_pmu *pmu = hlist_entry_safe(node, काष्ठा arm_pmu, node);
	पूर्णांक irq;

	अगर (!cpumask_test_cpu(cpu, &pmu->supported_cpus))
		वापस 0;
	अगर (pmu->reset)
		pmu->reset(pmu);

	per_cpu(cpu_armpmu, cpu) = pmu;

	irq = armpmu_get_cpu_irq(pmu, cpu);
	अगर (irq)
		per_cpu(cpu_irq_ops, cpu)->enable_pmuirq(irq);

	वापस 0;
पूर्ण

अटल पूर्णांक arm_perf_tearकरोwn_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा arm_pmu *pmu = hlist_entry_safe(node, काष्ठा arm_pmu, node);
	पूर्णांक irq;

	अगर (!cpumask_test_cpu(cpu, &pmu->supported_cpus))
		वापस 0;

	irq = armpmu_get_cpu_irq(pmu, cpu);
	अगर (irq)
		per_cpu(cpu_irq_ops, cpu)->disable_pmuirq(irq);

	per_cpu(cpu_armpmu, cpu) = शून्य;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CPU_PM
अटल व्योम cpu_pm_pmu_setup(काष्ठा arm_pmu *armpmu, अचिन्हित दीर्घ cmd)
अणु
	काष्ठा pmu_hw_events *hw_events = this_cpu_ptr(armpmu->hw_events);
	काष्ठा perf_event *event;
	पूर्णांक idx;

	क्रम (idx = 0; idx < armpmu->num_events; idx++) अणु
		event = hw_events->events[idx];
		अगर (!event)
			जारी;

		चयन (cmd) अणु
		हाल CPU_PM_ENTER:
			/*
			 * Stop and update the counter
			 */
			armpmu_stop(event, PERF_EF_UPDATE);
			अवरोध;
		हाल CPU_PM_EXIT:
		हाल CPU_PM_ENTER_FAILED:
			 /*
			  * Restore and enable the counter.
			  * armpmu_start() indirectly calls
			  *
			  * perf_event_update_userpage()
			  *
			  * that requires RCU पढ़ो locking to be functional,
			  * wrap the call within RCU_NONIDLE to make the
			  * RCU subप्रणाली aware this cpu is not idle from
			  * an RCU perspective क्रम the armpmu_start() call
			  * duration.
			  */
			RCU_NONIDLE(armpmu_start(event, PERF_EF_RELOAD));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cpu_pm_pmu_notअगरy(काष्ठा notअगरier_block *b, अचिन्हित दीर्घ cmd,
			     व्योम *v)
अणु
	काष्ठा arm_pmu *armpmu = container_of(b, काष्ठा arm_pmu, cpu_pm_nb);
	काष्ठा pmu_hw_events *hw_events = this_cpu_ptr(armpmu->hw_events);
	पूर्णांक enabled = biपंचांगap_weight(hw_events->used_mask, armpmu->num_events);

	अगर (!cpumask_test_cpu(smp_processor_id(), &armpmu->supported_cpus))
		वापस NOTIFY_DONE;

	/*
	 * Always reset the PMU रेजिस्टरs on घातer-up even अगर
	 * there are no events running.
	 */
	अगर (cmd == CPU_PM_EXIT && armpmu->reset)
		armpmu->reset(armpmu);

	अगर (!enabled)
		वापस NOTIFY_OK;

	चयन (cmd) अणु
	हाल CPU_PM_ENTER:
		armpmu->stop(armpmu);
		cpu_pm_pmu_setup(armpmu, cmd);
		अवरोध;
	हाल CPU_PM_EXIT:
	हाल CPU_PM_ENTER_FAILED:
		cpu_pm_pmu_setup(armpmu, cmd);
		armpmu->start(armpmu);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक cpu_pm_pmu_रेजिस्टर(काष्ठा arm_pmu *cpu_pmu)
अणु
	cpu_pmu->cpu_pm_nb.notअगरier_call = cpu_pm_pmu_notअगरy;
	वापस cpu_pm_रेजिस्टर_notअगरier(&cpu_pmu->cpu_pm_nb);
पूर्ण

अटल व्योम cpu_pm_pmu_unरेजिस्टर(काष्ठा arm_pmu *cpu_pmu)
अणु
	cpu_pm_unरेजिस्टर_notअगरier(&cpu_pmu->cpu_pm_nb);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक cpu_pm_pmu_रेजिस्टर(काष्ठा arm_pmu *cpu_pmu) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम cpu_pm_pmu_unरेजिस्टर(काष्ठा arm_pmu *cpu_pmu) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cpu_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	पूर्णांक err;

	err = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_STARTING,
				       &cpu_pmu->node);
	अगर (err)
		जाओ out;

	err = cpu_pm_pmu_रेजिस्टर(cpu_pmu);
	अगर (err)
		जाओ out_unरेजिस्टर;

	वापस 0;

out_unरेजिस्टर:
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_STARTING,
					    &cpu_pmu->node);
out:
	वापस err;
पूर्ण

अटल व्योम cpu_pmu_destroy(काष्ठा arm_pmu *cpu_pmu)
अणु
	cpu_pm_pmu_unरेजिस्टर(cpu_pmu);
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_STARTING,
					    &cpu_pmu->node);
पूर्ण

अटल काष्ठा arm_pmu *__armpmu_alloc(gfp_t flags)
अणु
	काष्ठा arm_pmu *pmu;
	पूर्णांक cpu;

	pmu = kzalloc(माप(*pmu), flags);
	अगर (!pmu) अणु
		pr_info("failed to allocate PMU device!\n");
		जाओ out;
	पूर्ण

	pmu->hw_events = alloc_percpu_gfp(काष्ठा pmu_hw_events, flags);
	अगर (!pmu->hw_events) अणु
		pr_info("failed to allocate per-cpu PMU data.\n");
		जाओ out_मुक्त_pmu;
	पूर्ण

	pmu->pmu = (काष्ठा pmu) अणु
		.pmu_enable	= armpmu_enable,
		.pmu_disable	= armpmu_disable,
		.event_init	= armpmu_event_init,
		.add		= armpmu_add,
		.del		= armpmu_del,
		.start		= armpmu_start,
		.stop		= armpmu_stop,
		.पढ़ो		= armpmu_पढ़ो,
		.filter_match	= armpmu_filter_match,
		.attr_groups	= pmu->attr_groups,
		/*
		 * This is a CPU PMU potentially in a heterogeneous
		 * configuration (e.g. big.LITTLE). This is not an uncore PMU,
		 * and we have taken ctx sharing पूर्णांकo account (e.g. with our
		 * pmu::filter_match callback and pmu::event_init group
		 * validation).
		 */
		.capabilities	= PERF_PMU_CAP_HETEROGENEOUS_CPUS,
	पूर्ण;

	pmu->attr_groups[ARMPMU_ATTR_GROUP_COMMON] =
		&armpmu_common_attr_group;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा pmu_hw_events *events;

		events = per_cpu_ptr(pmu->hw_events, cpu);
		raw_spin_lock_init(&events->pmu_lock);
		events->percpu_pmu = pmu;
	पूर्ण

	वापस pmu;

out_मुक्त_pmu:
	kमुक्त(pmu);
out:
	वापस शून्य;
पूर्ण

काष्ठा arm_pmu *armpmu_alloc(व्योम)
अणु
	वापस __armpmu_alloc(GFP_KERNEL);
पूर्ण

काष्ठा arm_pmu *armpmu_alloc_atomic(व्योम)
अणु
	वापस __armpmu_alloc(GFP_ATOMIC);
पूर्ण


व्योम armpmu_मुक्त(काष्ठा arm_pmu *pmu)
अणु
	मुक्त_percpu(pmu->hw_events);
	kमुक्त(pmu);
पूर्ण

पूर्णांक armpmu_रेजिस्टर(काष्ठा arm_pmu *pmu)
अणु
	पूर्णांक ret;

	ret = cpu_pmu_init(pmu);
	अगर (ret)
		वापस ret;

	अगर (!pmu->set_event_filter)
		pmu->pmu.capabilities |= PERF_PMU_CAP_NO_EXCLUDE;

	ret = perf_pmu_रेजिस्टर(&pmu->pmu, pmu->name, -1);
	अगर (ret)
		जाओ out_destroy;

	pr_info("enabled with %s PMU driver, %d counters available%s\n",
		pmu->name, pmu->num_events,
		has_nmi ? ", using NMIs" : "");

	वापस 0;

out_destroy:
	cpu_pmu_destroy(pmu);
	वापस ret;
पूर्ण

अटल पूर्णांक arm_pmu_hp_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_STARTING,
				      "perf/arm/pmu:starting",
				      arm_perf_starting_cpu,
				      arm_perf_tearकरोwn_cpu);
	अगर (ret)
		pr_err("CPU hotplug notifier for ARM PMU could not be registered: %d\n",
		       ret);
	वापस ret;
पूर्ण
subsys_initcall(arm_pmu_hp_init);
