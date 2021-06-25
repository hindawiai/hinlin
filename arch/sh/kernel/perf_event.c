<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance event support framework क्रम SuperH hardware counters.
 *
 *  Copyright (C) 2009  Paul Mundt
 *
 * Heavily based on the x86 and PowerPC implementations.
 *
 * x86:
 *  Copyright (C) 2008 Thomas Gleixner <tglx@linutronix.de>
 *  Copyright (C) 2008-2009 Red Hat, Inc., Ingo Molnar
 *  Copyright (C) 2009 Jaswinder Singh Rajput
 *  Copyright (C) 2009 Advanced Micro Devices, Inc., Robert Richter
 *  Copyright (C) 2008-2009 Red Hat, Inc., Peter Zijlstra
 *  Copyright (C) 2009 Intel Corporation, <markus.t.metzger@पूर्णांकel.com>
 *
 * ppc:
 *  Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/processor.h>

काष्ठा cpu_hw_events अणु
	काष्ठा perf_event	*events[MAX_HWEVENTS];
	अचिन्हित दीर्घ		used_mask[BITS_TO_LONGS(MAX_HWEVENTS)];
	अचिन्हित दीर्घ		active_mask[BITS_TO_LONGS(MAX_HWEVENTS)];
पूर्ण;

DEFINE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events);

अटल काष्ठा sh_pmu *sh_pmu __पढ़ो_mostly;

/* Number of perf_events counting hardware events */
अटल atomic_t num_events;
/* Used to aव्योम races in calling reserve/release_pmc_hardware */
अटल DEFINE_MUTEX(pmc_reserve_mutex);

/*
 * Stub these out क्रम now, करो something more profound later.
 */
पूर्णांक reserve_pmc_hardware(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम release_pmc_hardware(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sh_pmu_initialized(व्योम)
अणु
	वापस !!sh_pmu;
पूर्ण

/*
 * Release the PMU अगर this is the last perf_event.
 */
अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	अगर (!atomic_add_unless(&num_events, -1, 1)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_dec_वापस(&num_events) == 0)
			release_pmc_hardware();
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक hw_perf_cache_event(पूर्णांक config, पूर्णांक *evp)
अणु
	अचिन्हित दीर्घ type, op, result;
	पूर्णांक ev;

	अगर (!sh_pmu->cache_events)
		वापस -EINVAL;

	/* unpack config */
	type = config & 0xff;
	op = (config >> 8) & 0xff;
	result = (config >> 16) & 0xff;

	अगर (type >= PERF_COUNT_HW_CACHE_MAX ||
	    op >= PERF_COUNT_HW_CACHE_OP_MAX ||
	    result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;

	ev = (*sh_pmu->cache_events)[type][op][result];
	अगर (ev == 0)
		वापस -EOPNOTSUPP;
	अगर (ev == -1)
		वापस -EINVAL;
	*evp = ev;
	वापस 0;
पूर्ण

अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक config = -1;
	पूर्णांक err;

	अगर (!sh_pmu_initialized())
		वापस -ENODEV;

	/*
	 * See अगर we need to reserve the counter.
	 *
	 * If no events are currently in use, then we have to take a
	 * mutex to ensure that we करोn't race with another task करोing
	 * reserve_pmc_hardware or release_pmc_hardware.
	 */
	err = 0;
	अगर (!atomic_inc_not_zero(&num_events)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_पढ़ो(&num_events) == 0 &&
		    reserve_pmc_hardware())
			err = -EBUSY;
		अन्यथा
			atomic_inc(&num_events);
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण

	अगर (err)
		वापस err;

	event->destroy = hw_perf_event_destroy;

	चयन (attr->type) अणु
	हाल PERF_TYPE_RAW:
		config = attr->config & sh_pmu->raw_event_mask;
		अवरोध;
	हाल PERF_TYPE_HW_CACHE:
		err = hw_perf_cache_event(attr->config, &config);
		अगर (err)
			वापस err;
		अवरोध;
	हाल PERF_TYPE_HARDWARE:
		अगर (attr->config >= sh_pmu->max_events)
			वापस -EINVAL;

		config = sh_pmu->event_map(attr->config);
		अवरोध;
	पूर्ण

	अगर (config == -1)
		वापस -EINVAL;

	hwc->config |= config;

	वापस 0;
पूर्ण

अटल व्योम sh_perf_event_update(काष्ठा perf_event *event,
				   काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	u64 prev_raw_count, new_raw_count;
	s64 delta;
	पूर्णांक shअगरt = 0;

	/*
	 * Depending on the counter configuration, they may or may not
	 * be chained, in which हाल the previous counter value can be
	 * updated underneath us अगर the lower-half overflows.
	 *
	 * Our tactic to handle this is to first atomically पढ़ो and
	 * exchange a new raw count - then add that new-prev delta
	 * count to the generic counter atomically.
	 *
	 * As there is no पूर्णांकerrupt associated with the overflow events,
	 * this is the simplest approach क्रम मुख्यtaining consistency.
	 */
again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	new_raw_count = sh_pmu->पढ़ो(idx);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			     new_raw_count) != prev_raw_count)
		जाओ again;

	/*
	 * Now we have the new raw value and have updated the prev
	 * बारtamp alपढ़ोy. We can now calculate the elapsed delta
	 * (counter-)समय and add that to the generic counter.
	 *
	 * Careful, not all hw sign-extends above the physical width
	 * of the count.
	 */
	delta = (new_raw_count << shअगरt) - (prev_raw_count << shअगरt);
	delta >>= shअगरt;

	local64_add(delta, &event->count);
पूर्ण

अटल व्योम sh_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (!(event->hw.state & PERF_HES_STOPPED)) अणु
		sh_pmu->disable(hwc, idx);
		cpuc->events[idx] = शून्य;
		event->hw.state |= PERF_HES_STOPPED;
	पूर्ण

	अगर ((flags & PERF_EF_UPDATE) && !(event->hw.state & PERF_HES_UPTODATE)) अणु
		sh_perf_event_update(event, &event->hw, idx);
		event->hw.state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल व्योम sh_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (WARN_ON_ONCE(idx == -1))
		वापस;

	अगर (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));

	cpuc->events[idx] = event;
	event->hw.state = 0;
	sh_pmu->enable(hwc, idx);
पूर्ण

अटल व्योम sh_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	sh_pmu_stop(event, PERF_EF_UPDATE);
	__clear_bit(event->hw.idx, cpuc->used_mask);

	perf_event_update_userpage(event);
पूर्ण

अटल पूर्णांक sh_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	पूर्णांक ret = -EAGAIN;

	perf_pmu_disable(event->pmu);

	अगर (__test_and_set_bit(idx, cpuc->used_mask)) अणु
		idx = find_first_zero_bit(cpuc->used_mask, sh_pmu->num_events);
		अगर (idx == sh_pmu->num_events)
			जाओ out;

		__set_bit(idx, cpuc->used_mask);
		hwc->idx = idx;
	पूर्ण

	sh_pmu->disable(hwc, idx);

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	अगर (flags & PERF_EF_START)
		sh_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);
	ret = 0;
out:
	perf_pmu_enable(event->pmu);
	वापस ret;
पूर्ण

अटल व्योम sh_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	sh_perf_event_update(event, &event->hw, event->hw.idx);
पूर्ण

अटल पूर्णांक sh_pmu_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक err;

	/* करोes not support taken branch sampling */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_RAW:
	हाल PERF_TYPE_HW_CACHE:
	हाल PERF_TYPE_HARDWARE:
		err = __hw_perf_event_init(event);
		अवरोध;

	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (unlikely(err)) अणु
		अगर (event->destroy)
			event->destroy(event);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम sh_pmu_enable(काष्ठा pmu *pmu)
अणु
	अगर (!sh_pmu_initialized())
		वापस;

	sh_pmu->enable_all();
पूर्ण

अटल व्योम sh_pmu_disable(काष्ठा pmu *pmu)
अणु
	अगर (!sh_pmu_initialized())
		वापस;

	sh_pmu->disable_all();
पूर्ण

अटल काष्ठा pmu pmu = अणु
	.pmu_enable	= sh_pmu_enable,
	.pmu_disable	= sh_pmu_disable,
	.event_init	= sh_pmu_event_init,
	.add		= sh_pmu_add,
	.del		= sh_pmu_del,
	.start		= sh_pmu_start,
	.stop		= sh_pmu_stop,
	.पढ़ो		= sh_pmu_पढ़ो,
पूर्ण;

अटल पूर्णांक sh_pmu_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuhw = &per_cpu(cpu_hw_events, cpu);

	स_रखो(cpuhw, 0, माप(काष्ठा cpu_hw_events));
	वापस 0;
पूर्ण

पूर्णांक रेजिस्टर_sh_pmu(काष्ठा sh_pmu *_pmu)
अणु
	अगर (sh_pmu)
		वापस -EBUSY;
	sh_pmu = _pmu;

	pr_info("Performance Events: %s support registered\n", _pmu->name);

	/*
	 * All of the on-chip counters are "limited", in that they have
	 * no पूर्णांकerrupts, and are thereक्रमe unable to करो sampling without
	 * further work and समयr assistance.
	 */
	pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;

	WARN_ON(_pmu->num_events > MAX_HWEVENTS);

	perf_pmu_रेजिस्टर(&pmu, "cpu", PERF_TYPE_RAW);
	cpuhp_setup_state(CPUHP_PERF_SUPERH, "PERF_SUPERH", sh_pmu_prepare_cpu,
			  शून्य);
	वापस 0;
पूर्ण
