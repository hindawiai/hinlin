<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xtensa Perक्रमmance Monitor Module driver
 * See Tensilica Debug User's Guide क्रम PMU रेजिस्टरs करोcumentation.
 *
 * Copyright (C) 2015 Cadence Design Systems Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/stacktrace.h>

/* Global control/status क्रम all perf counters */
#घोषणा XTENSA_PMU_PMG			0x1000
/* Perf counter values */
#घोषणा XTENSA_PMU_PM(i)		(0x1080 + (i) * 4)
/* Perf counter control रेजिस्टरs */
#घोषणा XTENSA_PMU_PMCTRL(i)		(0x1100 + (i) * 4)
/* Perf counter status रेजिस्टरs */
#घोषणा XTENSA_PMU_PMSTAT(i)		(0x1180 + (i) * 4)

#घोषणा XTENSA_PMU_PMG_PMEN		0x1

#घोषणा XTENSA_PMU_COUNTER_MASK		0xffffffffULL
#घोषणा XTENSA_PMU_COUNTER_MAX		0x7fffffff

#घोषणा XTENSA_PMU_PMCTRL_INTEN		0x00000001
#घोषणा XTENSA_PMU_PMCTRL_KRNLCNT	0x00000008
#घोषणा XTENSA_PMU_PMCTRL_TRACELEVEL	0x000000f0
#घोषणा XTENSA_PMU_PMCTRL_SELECT_SHIFT	8
#घोषणा XTENSA_PMU_PMCTRL_SELECT	0x00001f00
#घोषणा XTENSA_PMU_PMCTRL_MASK_SHIFT	16
#घोषणा XTENSA_PMU_PMCTRL_MASK		0xffff0000

#घोषणा XTENSA_PMU_MASK(select, mask) \
	(((select) << XTENSA_PMU_PMCTRL_SELECT_SHIFT) | \
	 ((mask) << XTENSA_PMU_PMCTRL_MASK_SHIFT) | \
	 XTENSA_PMU_PMCTRL_TRACELEVEL | \
	 XTENSA_PMU_PMCTRL_INTEN)

#घोषणा XTENSA_PMU_PMSTAT_OVFL		0x00000001
#घोषणा XTENSA_PMU_PMSTAT_INTASRT	0x00000010

काष्ठा xtensa_pmu_events अणु
	/* Array of events currently on this core */
	काष्ठा perf_event *event[XCHAL_NUM_PERF_COUNTERS];
	/* Biपंचांगap of used hardware counters */
	अचिन्हित दीर्घ used_mask[BITS_TO_LONGS(XCHAL_NUM_PERF_COUNTERS)];
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा xtensa_pmu_events, xtensa_pmu_events);

अटल स्थिर u32 xtensa_hw_ctl[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= XTENSA_PMU_MASK(0, 0x1),
	[PERF_COUNT_HW_INSTRUCTIONS]		= XTENSA_PMU_MASK(2, 0xffff),
	[PERF_COUNT_HW_CACHE_REFERENCES]	= XTENSA_PMU_MASK(10, 0x1),
	[PERF_COUNT_HW_CACHE_MISSES]		= XTENSA_PMU_MASK(12, 0x1),
	/* Taken and non-taken branches + taken loop ends */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= XTENSA_PMU_MASK(2, 0x490),
	/* Inकाष्ठाion-related + other global stall cycles */
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= XTENSA_PMU_MASK(4, 0x1ff),
	/* Data-related global stall cycles */
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND]	= XTENSA_PMU_MASK(3, 0x1ff),
पूर्ण;

#घोषणा C(_x) PERF_COUNT_HW_CACHE_##_x

अटल स्थिर u32 xtensa_cache_ctl[][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= XTENSA_PMU_MASK(10, 0x1),
			[C(RESULT_MISS)]	= XTENSA_PMU_MASK(10, 0x2),
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= XTENSA_PMU_MASK(11, 0x1),
			[C(RESULT_MISS)]	= XTENSA_PMU_MASK(11, 0x2),
		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= XTENSA_PMU_MASK(8, 0x1),
			[C(RESULT_MISS)]	= XTENSA_PMU_MASK(8, 0x2),
		पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= XTENSA_PMU_MASK(9, 0x1),
			[C(RESULT_MISS)]	= XTENSA_PMU_MASK(9, 0x8),
		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= XTENSA_PMU_MASK(7, 0x1),
			[C(RESULT_MISS)]	= XTENSA_PMU_MASK(7, 0x8),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक xtensa_pmu_cache_event(u64 config)
अणु
	अचिन्हित पूर्णांक cache_type, cache_op, cache_result;
	पूर्णांक ret;

	cache_type = (config >>  0) & 0xff;
	cache_op = (config >>  8) & 0xff;
	cache_result = (config >> 16) & 0xff;

	अगर (cache_type >= ARRAY_SIZE(xtensa_cache_ctl) ||
	    cache_op >= C(OP_MAX) ||
	    cache_result >= C(RESULT_MAX))
		वापस -EINVAL;

	ret = xtensa_cache_ctl[cache_type][cache_op][cache_result];

	अगर (ret == 0)
		वापस -EINVAL;

	वापस ret;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t xtensa_pmu_पढ़ो_counter(पूर्णांक idx)
अणु
	वापस get_er(XTENSA_PMU_PM(idx));
पूर्ण

अटल अंतरभूत व्योम xtensa_pmu_ग_लिखो_counter(पूर्णांक idx, uपूर्णांक32_t v)
अणु
	set_er(v, XTENSA_PMU_PM(idx));
पूर्ण

अटल व्योम xtensa_perf_event_update(काष्ठा perf_event *event,
				     काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	uपूर्णांक64_t prev_raw_count, new_raw_count;
	पूर्णांक64_t delta;

	करो अणु
		prev_raw_count = local64_पढ़ो(&hwc->prev_count);
		new_raw_count = xtensa_pmu_पढ़ो_counter(event->hw.idx);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
				 new_raw_count) != prev_raw_count);

	delta = (new_raw_count - prev_raw_count) & XTENSA_PMU_COUNTER_MASK;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);
पूर्ण

अटल bool xtensa_perf_event_set_period(काष्ठा perf_event *event,
					 काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	bool rc = false;
	s64 left;

	अगर (!is_sampling_event(event)) अणु
		left = XTENSA_PMU_COUNTER_MAX;
	पूर्ण अन्यथा अणु
		s64 period = hwc->sample_period;

		left = local64_पढ़ो(&hwc->period_left);
		अगर (left <= -period) अणु
			left = period;
			local64_set(&hwc->period_left, left);
			hwc->last_period = period;
			rc = true;
		पूर्ण अन्यथा अगर (left <= 0) अणु
			left += period;
			local64_set(&hwc->period_left, left);
			hwc->last_period = period;
			rc = true;
		पूर्ण
		अगर (left > XTENSA_PMU_COUNTER_MAX)
			left = XTENSA_PMU_COUNTER_MAX;
	पूर्ण

	local64_set(&hwc->prev_count, -left);
	xtensa_pmu_ग_लिखो_counter(idx, -left);
	perf_event_update_userpage(event);

	वापस rc;
पूर्ण

अटल व्योम xtensa_pmu_enable(काष्ठा pmu *pmu)
अणु
	set_er(get_er(XTENSA_PMU_PMG) | XTENSA_PMU_PMG_PMEN, XTENSA_PMU_PMG);
पूर्ण

अटल व्योम xtensa_pmu_disable(काष्ठा pmu *pmu)
अणु
	set_er(get_er(XTENSA_PMU_PMG) & ~XTENSA_PMU_PMG_PMEN, XTENSA_PMU_PMG);
पूर्ण

अटल पूर्णांक xtensa_pmu_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक ret;

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		अगर (event->attr.config >= ARRAY_SIZE(xtensa_hw_ctl) ||
		    xtensa_hw_ctl[event->attr.config] == 0)
			वापस -EINVAL;
		event->hw.config = xtensa_hw_ctl[event->attr.config];
		वापस 0;

	हाल PERF_TYPE_HW_CACHE:
		ret = xtensa_pmu_cache_event(event->attr.config);
		अगर (ret < 0)
			वापस ret;
		event->hw.config = ret;
		वापस 0;

	हाल PERF_TYPE_RAW:
		/* Not 'previous counter' select */
		अगर ((event->attr.config & XTENSA_PMU_PMCTRL_SELECT) ==
		    (1 << XTENSA_PMU_PMCTRL_SELECT_SHIFT))
			वापस -EINVAL;
		event->hw.config = (event->attr.config &
				    (XTENSA_PMU_PMCTRL_KRNLCNT |
				     XTENSA_PMU_PMCTRL_TRACELEVEL |
				     XTENSA_PMU_PMCTRL_SELECT |
				     XTENSA_PMU_PMCTRL_MASK)) |
			XTENSA_PMU_PMCTRL_INTEN;
		वापस 0;

	शेष:
		वापस -ENOENT;
	पूर्ण
पूर्ण

/*
 * Starts/Stops a counter present on the PMU. The PMI handler
 * should stop the counter when perf_event_overflow() वापसs
 * !0. ->start() will be used to जारी.
 */
अटल व्योम xtensa_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (WARN_ON_ONCE(idx == -1))
		वापस;

	अगर (flags & PERF_EF_RELOAD) अणु
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));
		xtensa_perf_event_set_period(event, hwc, idx);
	पूर्ण

	hwc->state = 0;

	set_er(hwc->config, XTENSA_PMU_PMCTRL(idx));
पूर्ण

अटल व्योम xtensa_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (!(hwc->state & PERF_HES_STOPPED)) अणु
		set_er(0, XTENSA_PMU_PMCTRL(idx));
		set_er(get_er(XTENSA_PMU_PMSTAT(idx)),
		       XTENSA_PMU_PMSTAT(idx));
		hwc->state |= PERF_HES_STOPPED;
	पूर्ण

	अगर ((flags & PERF_EF_UPDATE) &&
	    !(event->hw.state & PERF_HES_UPTODATE)) अणु
		xtensa_perf_event_update(event, &event->hw, idx);
		event->hw.state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

/*
 * Adds/Removes a counter to/from the PMU, can be करोne inside
 * a transaction, see the ->*_txn() methods.
 */
अटल पूर्णांक xtensa_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा xtensa_pmu_events *ev = this_cpu_ptr(&xtensa_pmu_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (__test_and_set_bit(idx, ev->used_mask)) अणु
		idx = find_first_zero_bit(ev->used_mask,
					  XCHAL_NUM_PERF_COUNTERS);
		अगर (idx == XCHAL_NUM_PERF_COUNTERS)
			वापस -EAGAIN;

		__set_bit(idx, ev->used_mask);
		hwc->idx = idx;
	पूर्ण
	ev->event[idx] = event;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	अगर (flags & PERF_EF_START)
		xtensa_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);
	वापस 0;
पूर्ण

अटल व्योम xtensa_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा xtensa_pmu_events *ev = this_cpu_ptr(&xtensa_pmu_events);

	xtensa_pmu_stop(event, PERF_EF_UPDATE);
	__clear_bit(event->hw.idx, ev->used_mask);
	perf_event_update_userpage(event);
पूर्ण

अटल व्योम xtensa_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	xtensa_perf_event_update(event, &event->hw, event->hw.idx);
पूर्ण

अटल पूर्णांक callchain_trace(काष्ठा stackframe *frame, व्योम *data)
अणु
	काष्ठा perf_callchain_entry_ctx *entry = data;

	perf_callchain_store(entry, frame->pc);
	वापस 0;
पूर्ण

व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
			   काष्ठा pt_regs *regs)
अणु
	xtensa_backtrace_kernel(regs, entry->max_stack,
				callchain_trace, शून्य, entry);
पूर्ण

व्योम perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry,
			 काष्ठा pt_regs *regs)
अणु
	xtensa_backtrace_user(regs, entry->max_stack,
			      callchain_trace, entry);
पूर्ण

व्योम perf_event_prपूर्णांक_debug(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित i;

	local_irq_save(flags);
	pr_info("CPU#%d: PMG: 0x%08lx\n", smp_processor_id(),
		get_er(XTENSA_PMU_PMG));
	क्रम (i = 0; i < XCHAL_NUM_PERF_COUNTERS; ++i)
		pr_info("PM%d: 0x%08lx, PMCTRL%d: 0x%08lx, PMSTAT%d: 0x%08lx\n",
			i, get_er(XTENSA_PMU_PM(i)),
			i, get_er(XTENSA_PMU_PMCTRL(i)),
			i, get_er(XTENSA_PMU_PMSTAT(i)));
	local_irq_restore(flags);
पूर्ण

irqवापस_t xtensa_pmu_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t rc = IRQ_NONE;
	काष्ठा xtensa_pmu_events *ev = this_cpu_ptr(&xtensa_pmu_events);
	अचिन्हित i;

	क्रम_each_set_bit(i, ev->used_mask, XCHAL_NUM_PERF_COUNTERS) अणु
		uपूर्णांक32_t v = get_er(XTENSA_PMU_PMSTAT(i));
		काष्ठा perf_event *event = ev->event[i];
		काष्ठा hw_perf_event *hwc = &event->hw;
		u64 last_period;

		अगर (!(v & XTENSA_PMU_PMSTAT_OVFL))
			जारी;

		set_er(v, XTENSA_PMU_PMSTAT(i));
		xtensa_perf_event_update(event, hwc, i);
		last_period = hwc->last_period;
		अगर (xtensa_perf_event_set_period(event, hwc, i)) अणु
			काष्ठा perf_sample_data data;
			काष्ठा pt_regs *regs = get_irq_regs();

			perf_sample_data_init(&data, 0, last_period);
			अगर (perf_event_overflow(event, &data, regs))
				xtensa_pmu_stop(event, 0);
		पूर्ण

		rc = IRQ_HANDLED;
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा pmu xtensa_pmu = अणु
	.pmu_enable = xtensa_pmu_enable,
	.pmu_disable = xtensa_pmu_disable,
	.event_init = xtensa_pmu_event_init,
	.add = xtensa_pmu_add,
	.del = xtensa_pmu_del,
	.start = xtensa_pmu_start,
	.stop = xtensa_pmu_stop,
	.पढ़ो = xtensa_pmu_पढ़ो,
पूर्ण;

अटल पूर्णांक xtensa_pmu_setup(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित i;

	set_er(0, XTENSA_PMU_PMG);
	क्रम (i = 0; i < XCHAL_NUM_PERF_COUNTERS; ++i) अणु
		set_er(0, XTENSA_PMU_PMCTRL(i));
		set_er(get_er(XTENSA_PMU_PMSTAT(i)), XTENSA_PMU_PMSTAT(i));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init xtensa_pmu_init(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक irq = irq_create_mapping(शून्य, XCHAL_PROFILING_INTERRUPT);

	ret = cpuhp_setup_state(CPUHP_AP_PERF_XTENSA_STARTING,
				"perf/xtensa:starting", xtensa_pmu_setup,
				शून्य);
	अगर (ret) अणु
		pr_err("xtensa_pmu: failed to register CPU-hotplug.\n");
		वापस ret;
	पूर्ण
#अगर XTENSA_FAKE_NMI
	enable_irq(irq);
#अन्यथा
	ret = request_irq(irq, xtensa_pmu_irq_handler, IRQF_PERCPU,
			  "pmu", शून्य);
	अगर (ret < 0)
		वापस ret;
#पूर्ण_अगर

	ret = perf_pmu_रेजिस्टर(&xtensa_pmu, "cpu", PERF_TYPE_RAW);
	अगर (ret)
		मुक्त_irq(irq, शून्य);

	वापस ret;
पूर्ण
early_initcall(xtensa_pmu_init);
