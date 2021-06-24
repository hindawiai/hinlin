<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Timer events oriented CPU idle governor
 *
 * Copyright (C) 2018 Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *
 * The idea of this governor is based on the observation that on many प्रणालीs
 * समयr events are two or more orders of magnitude more frequent than any
 * other पूर्णांकerrupts, so they are likely to be the most signअगरicant source of CPU
 * wakeups from idle states.  Moreover, inक्रमmation about what happened in the
 * (relatively recent) past can be used to estimate whether or not the deepest
 * idle state with target residency within the समय to the बंदst समयr is
 * likely to be suitable क्रम the upcoming idle समय of the CPU and, अगर not, then
 * which of the shallower idle states to choose.
 *
 * Of course, non-समयr wakeup sources are more important in some use हालs and
 * they can be covered by taking a few most recent idle समय पूर्णांकervals of the
 * CPU पूर्णांकo account.  However, even in that हाल it is not necessary to consider
 * idle duration values greater than the समय till the बंदst समयr, as the
 * patterns that they may beदीर्घ to produce average values बंद enough to
 * the समय till the बंदst समयr (sleep length) anyway.
 *
 * Thus this governor estimates whether or not the upcoming idle समय of the CPU
 * is likely to be signअगरicantly लघुer than the sleep length and selects an
 * idle state क्रम it in accordance with that, as follows:
 *
 * - Find an idle state on the basis of the sleep length and state statistics
 *   collected over समय:
 *
 *   o Find the deepest idle state whose target residency is less than or equal
 *     to the sleep length.
 *
 *   o Select it अगर it matched both the sleep length and the observed idle
 *     duration in the past more often than it matched the sleep length alone
 *     (i.e. the observed idle duration was signअगरicantly लघुer than the sleep
 *     length matched by it).
 *
 *   o Otherwise, select the shallower state with the greatest matched "early"
 *     wakeups metric.
 *
 * - If the majority of the most recent idle duration values are below the
 *   target residency of the idle state selected so far, use those values to
 *   compute the new expected idle duration and find an idle state matching it
 *   (which has to be shallower than the one selected so far).
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/tick.h>

/*
 * The PULSE value is added to metrics when they grow and the DECAY_SHIFT value
 * is used क्रम decreasing metrics on a regular basis.
 */
#घोषणा PULSE		1024
#घोषणा DECAY_SHIFT	3

/*
 * Number of the most recent idle duration values to take पूर्णांकo consideration क्रम
 * the detection of wakeup patterns.
 */
#घोषणा INTERVALS	8

/**
 * काष्ठा teo_idle_state - Idle state data used by the TEO cpuidle governor.
 * @early_hits: "Early" CPU wakeups "matching" this state.
 * @hits: "On time" CPU wakeups "matching" this state.
 * @misses: CPU wakeups "missing" this state.
 *
 * A CPU wakeup is "matched" by a given idle state अगर the idle duration measured
 * after the wakeup is between the target residency of that state and the target
 * residency of the next one (or अगर this is the deepest available idle state, it
 * "matches" a CPU wakeup when the measured idle duration is at least equal to
 * its target residency).
 *
 * Also, from the TEO governor perspective, a CPU wakeup from idle is "early" अगर
 * it occurs signअगरicantly earlier than the बंदst expected समयr event (that
 * is, early enough to match an idle state shallower than the one matching the
 * समय till the बंदst समयr event).  Otherwise, the wakeup is "on time", or
 * it is a "hit".
 *
 * A "miss" occurs when the given state करोesn't match the wakeup, but it matches
 * the समय till the बंदst समयr event used क्रम idle state selection.
 */
काष्ठा teo_idle_state अणु
	अचिन्हित पूर्णांक early_hits;
	अचिन्हित पूर्णांक hits;
	अचिन्हित पूर्णांक misses;
पूर्ण;

/**
 * काष्ठा teo_cpu - CPU data used by the TEO cpuidle governor.
 * @समय_span_ns: Time between idle state selection and post-wakeup update.
 * @sleep_length_ns: Time till the बंदst समयr event (at the selection समय).
 * @states: Idle states data corresponding to this CPU.
 * @पूर्णांकerval_idx: Index of the most recent saved idle पूर्णांकerval.
 * @पूर्णांकervals: Saved idle duration values.
 */
काष्ठा teo_cpu अणु
	s64 समय_span_ns;
	s64 sleep_length_ns;
	काष्ठा teo_idle_state states[CPUIDLE_STATE_MAX];
	पूर्णांक पूर्णांकerval_idx;
	u64 पूर्णांकervals[INTERVALS];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा teo_cpu, teo_cpus);

/**
 * teo_update - Update CPU data after wakeup.
 * @drv: cpuidle driver containing state data.
 * @dev: Target CPU.
 */
अटल व्योम teo_update(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev)
अणु
	काष्ठा teo_cpu *cpu_data = per_cpu_ptr(&teo_cpus, dev->cpu);
	पूर्णांक i, idx_hit = 0, idx_समयr = 0;
	अचिन्हित पूर्णांक hits, misses;
	u64 measured_ns;

	अगर (cpu_data->समय_span_ns >= cpu_data->sleep_length_ns) अणु
		/*
		 * One of the safety nets has triggered or the wakeup was बंद
		 * enough to the बंदst समयr event expected at the idle state
		 * selection समय to be discarded.
		 */
		measured_ns = U64_MAX;
	पूर्ण अन्यथा अणु
		u64 lat_ns = drv->states[dev->last_state_idx].निकास_latency_ns;

		/*
		 * The computations below are to determine whether or not the
		 * (saved) समय till the next समयr event and the measured idle
		 * duration fall पूर्णांकo the same "bin", so use last_residency_ns
		 * क्रम that instead of समय_span_ns which includes the cpuidle
		 * overhead.
		 */
		measured_ns = dev->last_residency_ns;
		/*
		 * The delay between the wakeup and the first inकाष्ठाion
		 * executed by the CPU is not likely to be worst-हाल every
		 * समय, so take 1/2 of the निकास latency as a very rough
		 * approximation of the average of it.
		 */
		अगर (measured_ns >= lat_ns)
			measured_ns -= lat_ns / 2;
		अन्यथा
			measured_ns /= 2;
	पूर्ण

	/*
	 * Decay the "early hits" metric क्रम all of the states and find the
	 * states matching the sleep length and the measured idle duration.
	 */
	क्रम (i = 0; i < drv->state_count; i++) अणु
		अचिन्हित पूर्णांक early_hits = cpu_data->states[i].early_hits;

		cpu_data->states[i].early_hits -= early_hits >> DECAY_SHIFT;

		अगर (drv->states[i].target_residency_ns <= cpu_data->sleep_length_ns) अणु
			idx_समयr = i;
			अगर (drv->states[i].target_residency_ns <= measured_ns)
				idx_hit = i;
		पूर्ण
	पूर्ण

	/*
	 * Update the "hits" and "misses" data क्रम the state matching the sleep
	 * length.  If it matches the measured idle duration too, this is a hit,
	 * so increase the "hits" metric क्रम it then.  Otherwise, this is a
	 * miss, so increase the "misses" metric क्रम it.  In the latter हाल
	 * also increase the "early hits" metric क्रम the state that actually
	 * matches the measured idle duration.
	 */
	hits = cpu_data->states[idx_समयr].hits;
	hits -= hits >> DECAY_SHIFT;

	misses = cpu_data->states[idx_समयr].misses;
	misses -= misses >> DECAY_SHIFT;

	अगर (idx_समयr == idx_hit) अणु
		hits += PULSE;
	पूर्ण अन्यथा अणु
		misses += PULSE;
		cpu_data->states[idx_hit].early_hits += PULSE;
	पूर्ण

	cpu_data->states[idx_समयr].misses = misses;
	cpu_data->states[idx_समयr].hits = hits;

	/*
	 * Save idle duration values corresponding to non-समयr wakeups क्रम
	 * pattern detection.
	 */
	cpu_data->पूर्णांकervals[cpu_data->पूर्णांकerval_idx++] = measured_ns;
	अगर (cpu_data->पूर्णांकerval_idx >= INTERVALS)
		cpu_data->पूर्णांकerval_idx = 0;
पूर्ण

अटल bool teo_समय_ok(u64 पूर्णांकerval_ns)
अणु
	वापस !tick_nohz_tick_stopped() || पूर्णांकerval_ns >= TICK_NSEC;
पूर्ण

/**
 * teo_find_shallower_state - Find shallower idle state matching given duration.
 * @drv: cpuidle driver containing state data.
 * @dev: Target CPU.
 * @state_idx: Index of the capping idle state.
 * @duration_ns: Idle duration value to match.
 */
अटल पूर्णांक teo_find_shallower_state(काष्ठा cpuidle_driver *drv,
				    काष्ठा cpuidle_device *dev, पूर्णांक state_idx,
				    s64 duration_ns)
अणु
	पूर्णांक i;

	क्रम (i = state_idx - 1; i >= 0; i--) अणु
		अगर (dev->states_usage[i].disable)
			जारी;

		state_idx = i;
		अगर (drv->states[i].target_residency_ns <= duration_ns)
			अवरोध;
	पूर्ण
	वापस state_idx;
पूर्ण

/**
 * teo_select - Selects the next idle state to enter.
 * @drv: cpuidle driver containing state data.
 * @dev: Target CPU.
 * @stop_tick: Indication on whether or not to stop the scheduler tick.
 */
अटल पूर्णांक teo_select(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev,
		      bool *stop_tick)
अणु
	काष्ठा teo_cpu *cpu_data = per_cpu_ptr(&teo_cpus, dev->cpu);
	s64 latency_req = cpuidle_governor_latency_req(dev->cpu);
	पूर्णांक max_early_idx, prev_max_early_idx, स्थिरraपूर्णांक_idx, idx0, idx, i;
	अचिन्हित पूर्णांक hits, misses, early_hits;
	kसमय_प्रकार delta_tick;
	s64 duration_ns;

	अगर (dev->last_state_idx >= 0) अणु
		teo_update(drv, dev);
		dev->last_state_idx = -1;
	पूर्ण

	cpu_data->समय_span_ns = local_घड़ी();

	duration_ns = tick_nohz_get_sleep_length(&delta_tick);
	cpu_data->sleep_length_ns = duration_ns;

	hits = 0;
	misses = 0;
	early_hits = 0;
	max_early_idx = -1;
	prev_max_early_idx = -1;
	स्थिरraपूर्णांक_idx = drv->state_count;
	idx = -1;
	idx0 = idx;

	क्रम (i = 0; i < drv->state_count; i++) अणु
		काष्ठा cpuidle_state *s = &drv->states[i];

		अगर (dev->states_usage[i].disable) अणु
			/*
			 * Ignore disabled states with target residencies beyond
			 * the anticipated idle duration.
			 */
			अगर (s->target_residency_ns > duration_ns)
				जारी;

			/*
			 * This state is disabled, so the range of idle duration
			 * values corresponding to it is covered by the current
			 * candidate state, but still the "hits" and "misses"
			 * metrics of the disabled state need to be used to
			 * decide whether or not the state covering the range in
			 * question is good enough.
			 */
			hits = cpu_data->states[i].hits;
			misses = cpu_data->states[i].misses;

			अगर (early_hits >= cpu_data->states[i].early_hits ||
			    idx < 0)
				जारी;

			/*
			 * If the current candidate state has been the one with
			 * the maximum "early hits" metric so far, the "early
			 * hits" metric of the disabled state replaces the
			 * current "early hits" count to aव्योम selecting a
			 * deeper state with lower "early hits" metric.
			 */
			अगर (max_early_idx == idx) अणु
				early_hits = cpu_data->states[i].early_hits;
				जारी;
			पूर्ण

			/*
			 * The current candidate state is बंदr to the disabled
			 * one than the current maximum "early hits" state, so
			 * replace the latter with it, but in हाल the maximum
			 * "early hits" state index has not been set so far,
			 * check अगर the current candidate state is not too
			 * shallow क्रम that role.
			 */
			अगर (teo_समय_ok(drv->states[idx].target_residency_ns)) अणु
				prev_max_early_idx = max_early_idx;
				early_hits = cpu_data->states[i].early_hits;
				max_early_idx = idx;
			पूर्ण

			जारी;
		पूर्ण

		अगर (idx < 0) अणु
			idx = i; /* first enabled state */
			hits = cpu_data->states[i].hits;
			misses = cpu_data->states[i].misses;
			idx0 = i;
		पूर्ण

		अगर (s->target_residency_ns > duration_ns)
			अवरोध;

		अगर (s->निकास_latency_ns > latency_req && स्थिरraपूर्णांक_idx > i)
			स्थिरraपूर्णांक_idx = i;

		idx = i;
		hits = cpu_data->states[i].hits;
		misses = cpu_data->states[i].misses;

		अगर (early_hits < cpu_data->states[i].early_hits &&
		    teo_समय_ok(drv->states[i].target_residency_ns)) अणु
			prev_max_early_idx = max_early_idx;
			early_hits = cpu_data->states[i].early_hits;
			max_early_idx = i;
		पूर्ण
	पूर्ण

	/*
	 * If the "hits" metric of the idle state matching the sleep length is
	 * greater than its "misses" metric, that is the one to use.  Otherwise,
	 * it is more likely that one of the shallower states will match the
	 * idle duration observed after wakeup, so take the one with the maximum
	 * "early hits" metric, but अगर that cannot be determined, just use the
	 * state selected so far.
	 */
	अगर (hits <= misses) अणु
		/*
		 * The current candidate state is not suitable, so take the one
		 * whose "early hits" metric is the maximum क्रम the range of
		 * shallower states.
		 */
		अगर (idx == max_early_idx)
			max_early_idx = prev_max_early_idx;

		अगर (max_early_idx >= 0) अणु
			idx = max_early_idx;
			duration_ns = drv->states[idx].target_residency_ns;
		पूर्ण
	पूर्ण

	/*
	 * If there is a latency स्थिरraपूर्णांक, it may be necessary to use a
	 * shallower idle state than the one selected so far.
	 */
	अगर (स्थिरraपूर्णांक_idx < idx)
		idx = स्थिरraपूर्णांक_idx;

	अगर (idx < 0) अणु
		idx = 0; /* No states enabled. Must use 0. */
	पूर्ण अन्यथा अगर (idx > idx0) अणु
		अचिन्हित पूर्णांक count = 0;
		u64 sum = 0;

		/*
		 * The target residencies of at least two dअगरferent enabled idle
		 * states are less than or equal to the current expected idle
		 * duration.  Try to refine the selection using the most recent
		 * measured idle duration values.
		 *
		 * Count and sum the most recent idle duration values less than
		 * the current expected idle duration value.
		 */
		क्रम (i = 0; i < INTERVALS; i++) अणु
			u64 val = cpu_data->पूर्णांकervals[i];

			अगर (val >= duration_ns)
				जारी;

			count++;
			sum += val;
		पूर्ण

		/*
		 * Give up unless the majority of the most recent idle duration
		 * values are in the पूर्णांकeresting range.
		 */
		अगर (count > INTERVALS / 2) अणु
			u64 avg_ns = भाग64_u64(sum, count);

			/*
			 * Aव्योम spending too much समय in an idle state that
			 * would be too shallow.
			 */
			अगर (teo_समय_ok(avg_ns)) अणु
				duration_ns = avg_ns;
				अगर (drv->states[idx].target_residency_ns > avg_ns)
					idx = teo_find_shallower_state(drv, dev,
								       idx, avg_ns);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Don't stop the tick अगर the selected state is a polling one or अगर the
	 * expected idle duration is लघुer than the tick period length.
	 */
	अगर (((drv->states[idx].flags & CPUIDLE_FLAG_POLLING) ||
	    duration_ns < TICK_NSEC) && !tick_nohz_tick_stopped()) अणु
		*stop_tick = false;

		/*
		 * The tick is not going to be stopped, so अगर the target
		 * residency of the state to be वापसed is not within the समय
		 * till the बंदst समयr including the tick, try to correct
		 * that.
		 */
		अगर (idx > idx0 &&
		    drv->states[idx].target_residency_ns > delta_tick)
			idx = teo_find_shallower_state(drv, dev, idx, delta_tick);
	पूर्ण

	वापस idx;
पूर्ण

/**
 * teo_reflect - Note that governor data क्रम the CPU need to be updated.
 * @dev: Target CPU.
 * @state: Entered state.
 */
अटल व्योम teo_reflect(काष्ठा cpuidle_device *dev, पूर्णांक state)
अणु
	काष्ठा teo_cpu *cpu_data = per_cpu_ptr(&teo_cpus, dev->cpu);

	dev->last_state_idx = state;
	/*
	 * If the wakeup was not "natural", but triggered by one of the safety
	 * nets, assume that the CPU might have been idle क्रम the entire sleep
	 * length समय.
	 */
	अगर (dev->poll_समय_limit ||
	    (tick_nohz_idle_got_tick() && cpu_data->sleep_length_ns > TICK_NSEC)) अणु
		dev->poll_समय_limit = false;
		cpu_data->समय_span_ns = cpu_data->sleep_length_ns;
	पूर्ण अन्यथा अणु
		cpu_data->समय_span_ns = local_घड़ी() - cpu_data->समय_span_ns;
	पूर्ण
पूर्ण

/**
 * teo_enable_device - Initialize the governor's data क्रम the target CPU.
 * @drv: cpuidle driver (not used).
 * @dev: Target CPU.
 */
अटल पूर्णांक teo_enable_device(काष्ठा cpuidle_driver *drv,
			     काष्ठा cpuidle_device *dev)
अणु
	काष्ठा teo_cpu *cpu_data = per_cpu_ptr(&teo_cpus, dev->cpu);
	पूर्णांक i;

	स_रखो(cpu_data, 0, माप(*cpu_data));

	क्रम (i = 0; i < INTERVALS; i++)
		cpu_data->पूर्णांकervals[i] = U64_MAX;

	वापस 0;
पूर्ण

अटल काष्ठा cpuidle_governor teo_governor = अणु
	.name =		"teo",
	.rating =	19,
	.enable =	teo_enable_device,
	.select =	teo_select,
	.reflect =	teo_reflect,
पूर्ण;

अटल पूर्णांक __init teo_governor_init(व्योम)
अणु
	वापस cpuidle_रेजिस्टर_governor(&teo_governor);
पूर्ण

postcore_initcall(teo_governor_init);
