<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hardware perक्रमmance events क्रम the Alpha.
 *
 * We implement HW counts on the EV67 and subsequent CPUs only.
 *
 * (C) 2010 Michael J. Cree
 *
 * Somewhat based on the Sparc code, and to a lesser extent the PowerPC and
 * ARM code, which are copyright by their respective authors.
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/hwrpb.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/pal.h>
#समावेश <यंत्र/wrperfmon.h>
#समावेश <यंत्र/hw_irq.h>


/* The maximum number of PMCs on any Alpha CPU whatsoever. */
#घोषणा MAX_HWEVENTS 3
#घोषणा PMC_NO_INDEX -1

/* For tracking PMCs and the hw events they monitor on each CPU. */
काष्ठा cpu_hw_events अणु
	पूर्णांक			enabled;
	/* Number of events scheduled; also number entries valid in arrays below. */
	पूर्णांक			n_events;
	/* Number events added since last hw_perf_disable(). */
	पूर्णांक			n_added;
	/* Events currently scheduled. */
	काष्ठा perf_event	*event[MAX_HWEVENTS];
	/* Event type of each scheduled event. */
	अचिन्हित दीर्घ		evtype[MAX_HWEVENTS];
	/* Current index of each scheduled event; अगर not yet determined
	 * contains PMC_NO_INDEX.
	 */
	पूर्णांक			current_idx[MAX_HWEVENTS];
	/* The active PMCs' config क्रम easy use with wrperfmon(). */
	अचिन्हित दीर्घ		config;
	/* The active counters' indices क्रम easy use with wrperfmon(). */
	अचिन्हित दीर्घ		idx_mask;
पूर्ण;
DEFINE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events);



/*
 * A काष्ठाure to hold the description of the PMCs available on a particular
 * type of Alpha CPU.
 */
काष्ठा alpha_pmu_t अणु
	/* Mapping of the perf प्रणाली hw event types to indigenous event types */
	स्थिर पूर्णांक *event_map;
	/* The number of entries in the event_map */
	पूर्णांक  max_events;
	/* The number of PMCs on this Alpha */
	पूर्णांक  num_pmcs;
	/*
	 * All PMC counters reside in the IBOX रेजिस्टर PCTR.  This is the
	 * LSB of the counter.
	 */
	पूर्णांक  pmc_count_shअगरt[MAX_HWEVENTS];
	/*
	 * The mask that isolates the PMC bits when the LSB of the counter
	 * is shअगरted to bit 0.
	 */
	अचिन्हित दीर्घ pmc_count_mask[MAX_HWEVENTS];
	/* The maximum period the PMC can count. */
	अचिन्हित दीर्घ pmc_max_period[MAX_HWEVENTS];
	/*
	 * The maximum value that may be written to the counter due to
	 * hardware restrictions is pmc_max_period - pmc_left.
	 */
	दीर्घ pmc_left[3];
	 /* Subroutine क्रम allocation of PMCs.  Enक्रमces स्थिरraपूर्णांकs. */
	पूर्णांक (*check_स्थिरraपूर्णांकs)(काष्ठा perf_event **, अचिन्हित दीर्घ *, पूर्णांक);
	/* Subroutine क्रम checking validity of a raw event क्रम this PMU. */
	पूर्णांक (*raw_event_valid)(u64 config);
पूर्ण;

/*
 * The Alpha CPU PMU description currently in operation.  This is set during
 * the boot process to the specअगरic CPU of the machine.
 */
अटल स्थिर काष्ठा alpha_pmu_t *alpha_pmu;


#घोषणा HW_OP_UNSUPPORTED -1

/*
 * The hardware description of the EV67, EV68, EV69, EV7 and EV79 PMUs
 * follow. Since they are identical we refer to them collectively as the
 * EV67 henceक्रमth.
 */

/*
 * EV67 PMC event types
 *
 * There is no one-to-one mapping of the possible hw event types to the
 * actual codes that are used to program the PMCs hence we पूर्णांकroduce our
 * own hw event type identअगरiers.
 */
क्रमागत ev67_pmc_event_type अणु
	EV67_CYCLES = 1,
	EV67_INSTRUCTIONS,
	EV67_BCACHEMISS,
	EV67_MBOXREPLAY,
	EV67_LAST_ET
पूर्ण;
#घोषणा EV67_NUM_EVENT_TYPES (EV67_LAST_ET-EV67_CYCLES)


/* Mapping of the hw event types to the perf tool पूर्णांकerface */
अटल स्थिर पूर्णांक ev67_perfmon_event_map[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]	 = EV67_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]	 = EV67_INSTRUCTIONS,
	[PERF_COUNT_HW_CACHE_REFERENCES] = HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_CACHE_MISSES]	 = EV67_BCACHEMISS,
पूर्ण;

काष्ठा ev67_mapping_t अणु
	पूर्णांक config;
	पूर्णांक idx;
पूर्ण;

/*
 * The mapping used क्रम one event only - these must be in same order as क्रमागत
 * ev67_pmc_event_type definition.
 */
अटल स्थिर काष्ठा ev67_mapping_t ev67_mapping[] = अणु
	अणुEV67_PCTR_INSTR_CYCLES, 1पूर्ण,	 /* EV67_CYCLES, */
	अणुEV67_PCTR_INSTR_CYCLES, 0पूर्ण,	 /* EV67_INSTRUCTIONS */
	अणुEV67_PCTR_INSTR_BCACHEMISS, 1पूर्ण, /* EV67_BCACHEMISS */
	अणुEV67_PCTR_CYCLES_MBOX, 1पूर्ण	 /* EV67_MBOXREPLAY */
पूर्ण;


/*
 * Check that a group of events can be simultaneously scheduled on to the
 * EV67 PMU.  Also allocate counter indices and config.
 */
अटल पूर्णांक ev67_check_स्थिरraपूर्णांकs(काष्ठा perf_event **event,
				अचिन्हित दीर्घ *evtype, पूर्णांक n_ev)
अणु
	पूर्णांक idx0;
	अचिन्हित दीर्घ config;

	idx0 = ev67_mapping[evtype[0]-1].idx;
	config = ev67_mapping[evtype[0]-1].config;
	अगर (n_ev == 1)
		जाओ success;

	BUG_ON(n_ev != 2);

	अगर (evtype[0] == EV67_MBOXREPLAY || evtype[1] == EV67_MBOXREPLAY) अणु
		/* MBOX replay traps must be on PMC 1 */
		idx0 = (evtype[0] == EV67_MBOXREPLAY) ? 1 : 0;
		/* Only cycles can accompany MBOX replay traps */
		अगर (evtype[idx0] == EV67_CYCLES) अणु
			config = EV67_PCTR_CYCLES_MBOX;
			जाओ success;
		पूर्ण
	पूर्ण

	अगर (evtype[0] == EV67_BCACHEMISS || evtype[1] == EV67_BCACHEMISS) अणु
		/* Bcache misses must be on PMC 1 */
		idx0 = (evtype[0] == EV67_BCACHEMISS) ? 1 : 0;
		/* Only inकाष्ठाions can accompany Bcache misses */
		अगर (evtype[idx0] == EV67_INSTRUCTIONS) अणु
			config = EV67_PCTR_INSTR_BCACHEMISS;
			जाओ success;
		पूर्ण
	पूर्ण

	अगर (evtype[0] == EV67_INSTRUCTIONS || evtype[1] == EV67_INSTRUCTIONS) अणु
		/* Inकाष्ठाions must be on PMC 0 */
		idx0 = (evtype[0] == EV67_INSTRUCTIONS) ? 0 : 1;
		/* By this poपूर्णांक only cycles can accompany inकाष्ठाions */
		अगर (evtype[idx0^1] == EV67_CYCLES) अणु
			config = EV67_PCTR_INSTR_CYCLES;
			जाओ success;
		पूर्ण
	पूर्ण

	/* Otherwise, darn it, there is a conflict.  */
	वापस -1;

success:
	event[0]->hw.idx = idx0;
	event[0]->hw.config_base = config;
	अगर (n_ev == 2) अणु
		event[1]->hw.idx = idx0 ^ 1;
		event[1]->hw.config_base = config;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक ev67_raw_event_valid(u64 config)
अणु
	वापस config >= EV67_CYCLES && config < EV67_LAST_ET;
पूर्ण;


अटल स्थिर काष्ठा alpha_pmu_t ev67_pmu = अणु
	.event_map = ev67_perfmon_event_map,
	.max_events = ARRAY_SIZE(ev67_perfmon_event_map),
	.num_pmcs = 2,
	.pmc_count_shअगरt = अणुEV67_PCTR_0_COUNT_SHIFT, EV67_PCTR_1_COUNT_SHIFT, 0पूर्ण,
	.pmc_count_mask = अणुEV67_PCTR_0_COUNT_MASK,  EV67_PCTR_1_COUNT_MASK,  0पूर्ण,
	.pmc_max_period = अणु(1UL<<20) - 1, (1UL<<20) - 1, 0पूर्ण,
	.pmc_left = अणु16, 4, 0पूर्ण,
	.check_स्थिरraपूर्णांकs = ev67_check_स्थिरraपूर्णांकs,
	.raw_event_valid = ev67_raw_event_valid,
पूर्ण;



/*
 * Helper routines to ensure that we पढ़ो/ग_लिखो only the correct PMC bits
 * when calling the wrperfmon PALcall.
 */
अटल अंतरभूत व्योम alpha_ग_लिखो_pmc(पूर्णांक idx, अचिन्हित दीर्घ val)
अणु
	val &= alpha_pmu->pmc_count_mask[idx];
	val <<= alpha_pmu->pmc_count_shअगरt[idx];
	val |= (1<<idx);
	wrperfmon(PERFMON_CMD_WRITE, val);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ alpha_पढ़ो_pmc(पूर्णांक idx)
अणु
	अचिन्हित दीर्घ val;

	val = wrperfmon(PERFMON_CMD_READ, 0);
	val >>= alpha_pmu->pmc_count_shअगरt[idx];
	val &= alpha_pmu->pmc_count_mask[idx];
	वापस val;
पूर्ण

/* Set a new period to sample over */
अटल पूर्णांक alpha_perf_event_set_period(काष्ठा perf_event *event,
				काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	दीर्घ left = local64_पढ़ो(&hwc->period_left);
	दीर्घ period = hwc->sample_period;
	पूर्णांक ret = 0;

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
	 * Hardware restrictions require that the counters must not be
	 * written with values that are too बंद to the maximum period.
	 */
	अगर (unlikely(left < alpha_pmu->pmc_left[idx]))
		left = alpha_pmu->pmc_left[idx];

	अगर (left > (दीर्घ)alpha_pmu->pmc_max_period[idx])
		left = alpha_pmu->pmc_max_period[idx];

	local64_set(&hwc->prev_count, (अचिन्हित दीर्घ)(-left));

	alpha_ग_लिखो_pmc(idx, (अचिन्हित दीर्घ)(-left));

	perf_event_update_userpage(event);

	वापस ret;
पूर्ण


/*
 * Calculates the count (the 'delta') since the last समय the PMC was पढ़ो.
 *
 * As the PMCs' full period can easily be exceeded within the perf प्रणाली
 * sampling period we cannot use any high order bits as a guard bit in the
 * PMCs to detect overflow as is करोne by other architectures.  The code here
 * calculates the delta on the basis that there is no overflow when ovf is
 * zero.  The value passed via ovf by the पूर्णांकerrupt handler corrects क्रम
 * overflow.
 *
 * This can be racey on rare occasions -- a call to this routine can occur
 * with an overflowed counter just beक्रमe the PMI service routine is called.
 * The check क्रम delta negative hopefully always rectअगरies this situation.
 */
अटल अचिन्हित दीर्घ alpha_perf_event_update(काष्ठा perf_event *event,
					काष्ठा hw_perf_event *hwc, पूर्णांक idx, दीर्घ ovf)
अणु
	दीर्घ prev_raw_count, new_raw_count;
	दीर्घ delta;

again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	new_raw_count = alpha_पढ़ो_pmc(idx);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			     new_raw_count) != prev_raw_count)
		जाओ again;

	delta = (new_raw_count - (prev_raw_count & alpha_pmu->pmc_count_mask[idx])) + ovf;

	/* It is possible on very rare occasions that the PMC has overflowed
	 * but the पूर्णांकerrupt is yet to come.  Detect and fix this situation.
	 */
	अगर (unlikely(delta < 0)) अणु
		delta += alpha_pmu->pmc_max_period[idx] + 1;
	पूर्ण

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	वापस new_raw_count;
पूर्ण


/*
 * Collect all HW events पूर्णांकo the array event[].
 */
अटल पूर्णांक collect_events(काष्ठा perf_event *group, पूर्णांक max_count,
			  काष्ठा perf_event *event[], अचिन्हित दीर्घ *evtype,
			  पूर्णांक *current_idx)
अणु
	काष्ठा perf_event *pe;
	पूर्णांक n = 0;

	अगर (!is_software_event(group)) अणु
		अगर (n >= max_count)
			वापस -1;
		event[n] = group;
		evtype[n] = group->hw.event_base;
		current_idx[n++] = PMC_NO_INDEX;
	पूर्ण
	क्रम_each_sibling_event(pe, group) अणु
		अगर (!is_software_event(pe) && pe->state != PERF_EVENT_STATE_OFF) अणु
			अगर (n >= max_count)
				वापस -1;
			event[n] = pe;
			evtype[n] = pe->hw.event_base;
			current_idx[n++] = PMC_NO_INDEX;
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण



/*
 * Check that a group of events can be simultaneously scheduled on to the PMU.
 */
अटल पूर्णांक alpha_check_स्थिरraपूर्णांकs(काष्ठा perf_event **events,
				   अचिन्हित दीर्घ *evtypes, पूर्णांक n_ev)
अणु

	/* No HW events is possible from hw_perf_group_sched_in(). */
	अगर (n_ev == 0)
		वापस 0;

	अगर (n_ev > alpha_pmu->num_pmcs)
		वापस -1;

	वापस alpha_pmu->check_स्थिरraपूर्णांकs(events, evtypes, n_ev);
पूर्ण


/*
 * If new events have been scheduled then update cpuc with the new
 * configuration.  This may involve shअगरting cycle counts from one PMC to
 * another.
 */
अटल व्योम maybe_change_configuration(काष्ठा cpu_hw_events *cpuc)
अणु
	पूर्णांक j;

	अगर (cpuc->n_added == 0)
		वापस;

	/* Find counters that are moving to another PMC and update */
	क्रम (j = 0; j < cpuc->n_events; j++) अणु
		काष्ठा perf_event *pe = cpuc->event[j];

		अगर (cpuc->current_idx[j] != PMC_NO_INDEX &&
			cpuc->current_idx[j] != pe->hw.idx) अणु
			alpha_perf_event_update(pe, &pe->hw, cpuc->current_idx[j], 0);
			cpuc->current_idx[j] = PMC_NO_INDEX;
		पूर्ण
	पूर्ण

	/* Assign to counters all unasचिन्हित events. */
	cpuc->idx_mask = 0;
	क्रम (j = 0; j < cpuc->n_events; j++) अणु
		काष्ठा perf_event *pe = cpuc->event[j];
		काष्ठा hw_perf_event *hwc = &pe->hw;
		पूर्णांक idx = hwc->idx;

		अगर (cpuc->current_idx[j] == PMC_NO_INDEX) अणु
			alpha_perf_event_set_period(pe, hwc, idx);
			cpuc->current_idx[j] = idx;
		पूर्ण

		अगर (!(hwc->state & PERF_HES_STOPPED))
			cpuc->idx_mask |= (1<<cpuc->current_idx[j]);
	पूर्ण
	cpuc->config = cpuc->event[0]->hw.config_base;
पूर्ण



/* Schedule perf HW event on to PMU.
 *  - this function is called from outside this module via the pmu काष्ठा
 *    वापसed from perf event initialisation.
 */
अटल पूर्णांक alpha_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक n0;
	पूर्णांक ret;
	अचिन्हित दीर्घ irq_flags;

	/*
	 * The Sparc code has the IRQ disable first followed by the perf
	 * disable, however this can lead to an overflowed counter with the
	 * PMI disabled on rare occasions.  The alpha_perf_event_update()
	 * routine should detect this situation by noting a negative delta,
	 * nevertheless we disable the PMCs first to enable a potential
	 * final PMI to occur beक्रमe we disable पूर्णांकerrupts.
	 */
	perf_pmu_disable(event->pmu);
	local_irq_save(irq_flags);

	/* Default to error to be वापसed */
	ret = -EAGAIN;

	/* Insert event on to PMU and अगर successful modअगरy ret to valid वापस */
	n0 = cpuc->n_events;
	अगर (n0 < alpha_pmu->num_pmcs) अणु
		cpuc->event[n0] = event;
		cpuc->evtype[n0] = event->hw.event_base;
		cpuc->current_idx[n0] = PMC_NO_INDEX;

		अगर (!alpha_check_स्थिरraपूर्णांकs(cpuc->event, cpuc->evtype, n0+1)) अणु
			cpuc->n_events++;
			cpuc->n_added++;
			ret = 0;
		पूर्ण
	पूर्ण

	hwc->state = PERF_HES_UPTODATE;
	अगर (!(flags & PERF_EF_START))
		hwc->state |= PERF_HES_STOPPED;

	local_irq_restore(irq_flags);
	perf_pmu_enable(event->pmu);

	वापस ret;
पूर्ण



/* Disable perक्रमmance monitoring unit
 *  - this function is called from outside this module via the pmu काष्ठा
 *    वापसed from perf event initialisation.
 */
अटल व्योम alpha_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक j;

	perf_pmu_disable(event->pmu);
	local_irq_save(irq_flags);

	क्रम (j = 0; j < cpuc->n_events; j++) अणु
		अगर (event == cpuc->event[j]) अणु
			पूर्णांक idx = cpuc->current_idx[j];

			/* Shअगरt reमुख्यing entries करोwn पूर्णांकo the existing
			 * slot.
			 */
			जबतक (++j < cpuc->n_events) अणु
				cpuc->event[j - 1] = cpuc->event[j];
				cpuc->evtype[j - 1] = cpuc->evtype[j];
				cpuc->current_idx[j - 1] =
					cpuc->current_idx[j];
			पूर्ण

			/* Absorb the final count and turn off the event. */
			alpha_perf_event_update(event, hwc, idx, 0);
			perf_event_update_userpage(event);

			cpuc->idx_mask &= ~(1UL<<idx);
			cpuc->n_events--;
			अवरोध;
		पूर्ण
	पूर्ण

	local_irq_restore(irq_flags);
	perf_pmu_enable(event->pmu);
पूर्ण


अटल व्योम alpha_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	alpha_perf_event_update(event, hwc, hwc->idx, 0);
पूर्ण


अटल व्योम alpha_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (!(hwc->state & PERF_HES_STOPPED)) अणु
		cpuc->idx_mask &= ~(1UL<<hwc->idx);
		hwc->state |= PERF_HES_STOPPED;
	पूर्ण

	अगर ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) अणु
		alpha_perf_event_update(event, hwc, hwc->idx, 0);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण

	अगर (cpuc->enabled)
		wrperfmon(PERFMON_CMD_DISABLE, (1UL<<hwc->idx));
पूर्ण


अटल व्योम alpha_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		वापस;

	अगर (flags & PERF_EF_RELOAD) अणु
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));
		alpha_perf_event_set_period(event, hwc, hwc->idx);
	पूर्ण

	hwc->state = 0;

	cpuc->idx_mask |= 1UL<<hwc->idx;
	अगर (cpuc->enabled)
		wrperfmon(PERFMON_CMD_ENABLE, (1UL<<hwc->idx));
पूर्ण


/*
 * Check that CPU perक्रमmance counters are supported.
 * - currently support EV67 and later CPUs.
 * - actually some later revisions of the EV6 have the same PMC model as the
 *     EV67 but we करोn't करो suffiently deep CPU detection to detect them.
 *     Bad luck to the very few people who might have one, I guess.
 */
अटल पूर्णांक supported_cpu(व्योम)
अणु
	काष्ठा percpu_काष्ठा *cpu;
	अचिन्हित दीर्घ cputype;

	/* Get cpu type from HW */
	cpu = (काष्ठा percpu_काष्ठा *)((अक्षर *)hwrpb + hwrpb->processor_offset);
	cputype = cpu->type & 0xffffffff;
	/* Include all of EV67, EV68, EV7, EV79 and EV69 as supported. */
	वापस (cputype >= EV67_CPU) && (cputype <= EV69_CPU);
पूर्ण



अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	/* Nothing to be करोne! */
	वापस;
पूर्ण



अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_event *evts[MAX_HWEVENTS];
	अचिन्हित दीर्घ evtypes[MAX_HWEVENTS];
	पूर्णांक idx_rubbish_bin[MAX_HWEVENTS];
	पूर्णांक ev;
	पूर्णांक n;

	/* We only support a limited range of HARDWARE event types with one
	 * only programmable via a RAW event type.
	 */
	अगर (attr->type == PERF_TYPE_HARDWARE) अणु
		अगर (attr->config >= alpha_pmu->max_events)
			वापस -EINVAL;
		ev = alpha_pmu->event_map[attr->config];
	पूर्ण अन्यथा अगर (attr->type == PERF_TYPE_HW_CACHE) अणु
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (attr->type == PERF_TYPE_RAW) अणु
		अगर (!alpha_pmu->raw_event_valid(attr->config))
			वापस -EINVAL;
		ev = attr->config;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ev < 0) अणु
		वापस ev;
	पूर्ण

	/*
	 * We place the event type in event_base here and leave calculation
	 * of the codes to programme the PMU क्रम alpha_pmu_enable() because
	 * it is only then we will know what HW events are actually
	 * scheduled on to the PMU.  At that poपूर्णांक the code to programme the
	 * PMU is put पूर्णांकo config_base and the PMC to use is placed पूर्णांकo
	 * idx.  We initialise idx (below) to PMC_NO_INDEX to indicate that
	 * it is yet to be determined.
	 */
	hwc->event_base = ev;

	/* Collect events in a group together suitable क्रम calling
	 * alpha_check_स्थिरraपूर्णांकs() to verअगरy that the group as a whole can
	 * be scheduled on to the PMU.
	 */
	n = 0;
	अगर (event->group_leader != event) अणु
		n = collect_events(event->group_leader,
				alpha_pmu->num_pmcs - 1,
				evts, evtypes, idx_rubbish_bin);
		अगर (n < 0)
			वापस -EINVAL;
	पूर्ण
	evtypes[n] = hwc->event_base;
	evts[n] = event;

	अगर (alpha_check_स्थिरraपूर्णांकs(evts, evtypes, n + 1))
		वापस -EINVAL;

	/* Indicate that PMU config and idx are yet to be determined. */
	hwc->config_base = 0;
	hwc->idx = PMC_NO_INDEX;

	event->destroy = hw_perf_event_destroy;

	/*
	 * Most architectures reserve the PMU क्रम their use at this poपूर्णांक.
	 * As there is no existing mechanism to arbitrate usage and there
	 * appears to be no other user of the Alpha PMU we just assume
	 * that we can just use it, hence a NO-OP here.
	 *
	 * Maybe an alpha_reserve_pmu() routine should be implemented but is
	 * anything अन्यथा ever going to use it?
	 */

	अगर (!hwc->sample_period) अणु
		hwc->sample_period = alpha_pmu->pmc_max_period[0];
		hwc->last_period = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Main entry poपूर्णांक to initialise a HW perक्रमmance event.
 */
अटल पूर्णांक alpha_pmu_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक err;

	/* करोes not support taken branch sampling */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_RAW:
	हाल PERF_TYPE_HARDWARE:
	हाल PERF_TYPE_HW_CACHE:
		अवरोध;

	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (!alpha_pmu)
		वापस -ENODEV;

	/* Do the real initialisation work. */
	err = __hw_perf_event_init(event);

	वापस err;
पूर्ण

/*
 * Main entry poपूर्णांक - enable HW perक्रमmance counters.
 */
अटल व्योम alpha_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (cpuc->enabled)
		वापस;

	cpuc->enabled = 1;
	barrier();

	अगर (cpuc->n_events > 0) अणु
		/* Update cpuc with inक्रमmation from any new scheduled events. */
		maybe_change_configuration(cpuc);

		/* Start counting the desired events. */
		wrperfmon(PERFMON_CMD_LOGGING_OPTIONS, EV67_PCTR_MODE_AGGREGATE);
		wrperfmon(PERFMON_CMD_DESIRED_EVENTS, cpuc->config);
		wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);
	पूर्ण
पूर्ण


/*
 * Main entry poपूर्णांक - disable HW perक्रमmance counters.
 */

अटल व्योम alpha_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (!cpuc->enabled)
		वापस;

	cpuc->enabled = 0;
	cpuc->n_added = 0;

	wrperfmon(PERFMON_CMD_DISABLE, cpuc->idx_mask);
पूर्ण

अटल काष्ठा pmu pmu = अणु
	.pmu_enable	= alpha_pmu_enable,
	.pmu_disable	= alpha_pmu_disable,
	.event_init	= alpha_pmu_event_init,
	.add		= alpha_pmu_add,
	.del		= alpha_pmu_del,
	.start		= alpha_pmu_start,
	.stop		= alpha_pmu_stop,
	.पढ़ो		= alpha_pmu_पढ़ो,
	.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
पूर्ण;


/*
 * Main entry poपूर्णांक - करोn't know when this is called but it
 * obviously dumps debug info.
 */
व्योम perf_event_prपूर्णांक_debug(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ pcr;
	पूर्णांक pcr0, pcr1;
	पूर्णांक cpu;

	अगर (!supported_cpu())
		वापस;

	local_irq_save(flags);

	cpu = smp_processor_id();

	pcr = wrperfmon(PERFMON_CMD_READ, 0);
	pcr0 = (pcr >> alpha_pmu->pmc_count_shअगरt[0]) & alpha_pmu->pmc_count_mask[0];
	pcr1 = (pcr >> alpha_pmu->pmc_count_shअगरt[1]) & alpha_pmu->pmc_count_mask[1];

	pr_info("CPU#%d: PCTR0[%06x] PCTR1[%06x]\n", cpu, pcr0, pcr1);

	local_irq_restore(flags);
पूर्ण


/*
 * Perक्रमmance Monitoring Interrupt Service Routine called when a PMC
 * overflows.  The PMC that overflowed is passed in la_ptr.
 */
अटल व्योम alpha_perf_event_irq_handler(अचिन्हित दीर्घ la_ptr,
					काष्ठा pt_regs *regs)
अणु
	काष्ठा cpu_hw_events *cpuc;
	काष्ठा perf_sample_data data;
	काष्ठा perf_event *event;
	काष्ठा hw_perf_event *hwc;
	पूर्णांक idx, j;

	__this_cpu_inc(irq_pmi_count);
	cpuc = this_cpu_ptr(&cpu_hw_events);

	/* Completely counting through the PMC's period to trigger a new PMC
	 * overflow पूर्णांकerrupt जबतक in this पूर्णांकerrupt routine is utterly
	 * disastrous!  The EV6 and EV67 counters are sufficiently large to
	 * prevent this but to be really sure disable the PMCs.
	 */
	wrperfmon(PERFMON_CMD_DISABLE, cpuc->idx_mask);

	/* la_ptr is the counter that overflowed. */
	अगर (unlikely(la_ptr >= alpha_pmu->num_pmcs)) अणु
		/* This should never occur! */
		irq_err_count++;
		pr_warn("PMI: silly index %ld\n", la_ptr);
		wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);
		वापस;
	पूर्ण

	idx = la_ptr;

	क्रम (j = 0; j < cpuc->n_events; j++) अणु
		अगर (cpuc->current_idx[j] == idx)
			अवरोध;
	पूर्ण

	अगर (unlikely(j == cpuc->n_events)) अणु
		/* This can occur अगर the event is disabled right on a PMC overflow. */
		wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);
		वापस;
	पूर्ण

	event = cpuc->event[j];

	अगर (unlikely(!event)) अणु
		/* This should never occur! */
		irq_err_count++;
		pr_warn("PMI: No event at index %d!\n", idx);
		wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);
		वापस;
	पूर्ण

	hwc = &event->hw;
	alpha_perf_event_update(event, hwc, idx, alpha_pmu->pmc_max_period[idx]+1);
	perf_sample_data_init(&data, 0, hwc->last_period);

	अगर (alpha_perf_event_set_period(event, hwc, idx)) अणु
		अगर (perf_event_overflow(event, &data, regs)) अणु
			/* Interrupts coming too quickly; "throttle" the
			 * counter, i.e., disable it क्रम a little जबतक.
			 */
			alpha_pmu_stop(event, 0);
		पूर्ण
	पूर्ण
	wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);

	वापस;
पूर्ण



/*
 * Init call to initialise perक्रमmance events at kernel startup.
 */
पूर्णांक __init init_hw_perf_events(व्योम)
अणु
	pr_info("Performance events: ");

	अगर (!supported_cpu()) अणु
		pr_cont("No support for your CPU.\n");
		वापस 0;
	पूर्ण

	pr_cont("Supported CPU type!\n");

	/* Override perक्रमmance counter IRQ vector */

	perf_irq = alpha_perf_event_irq_handler;

	/* And set up PMU specअगरication */
	alpha_pmu = &ev67_pmu;

	perf_pmu_रेजिस्टर(&pmu, "cpu", PERF_TYPE_RAW);

	वापस 0;
पूर्ण
early_initcall(init_hw_perf_events);
