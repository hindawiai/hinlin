<शैली गुरु>
/*
 * ladder.c - the residency ladder algorithm
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2004, 2005 Dominik Broकरोwski <linux@broकरो.de>
 *
 * (C) 2006-2007 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *               Shaohua Li <shaohua.li@पूर्णांकel.com>
 *               Adam Belay <abelay@novell.com>
 *
 * This code is licenced under the GPL.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/tick.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#घोषणा PROMOTION_COUNT 4
#घोषणा DEMOTION_COUNT 1

काष्ठा ladder_device_state अणु
	काष्ठा अणु
		u32 promotion_count;
		u32 demotion_count;
		u64 promotion_समय_ns;
		u64 demotion_समय_ns;
	पूर्ण threshold;
	काष्ठा अणु
		पूर्णांक promotion_count;
		पूर्णांक demotion_count;
	पूर्ण stats;
पूर्ण;

काष्ठा ladder_device अणु
	काष्ठा ladder_device_state states[CPUIDLE_STATE_MAX];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा ladder_device, ladder_devices);

/**
 * ladder_करो_selection - prepares निजी data क्रम a state change
 * @ldev: the ladder device
 * @old_idx: the current state index
 * @new_idx: the new target state index
 */
अटल अंतरभूत व्योम ladder_करो_selection(काष्ठा cpuidle_device *dev,
				       काष्ठा ladder_device *ldev,
				       पूर्णांक old_idx, पूर्णांक new_idx)
अणु
	ldev->states[old_idx].stats.promotion_count = 0;
	ldev->states[old_idx].stats.demotion_count = 0;
	dev->last_state_idx = new_idx;
पूर्ण

/**
 * ladder_select_state - selects the next state to enter
 * @drv: cpuidle driver
 * @dev: the CPU
 * @dummy: not used
 */
अटल पूर्णांक ladder_select_state(काष्ठा cpuidle_driver *drv,
			       काष्ठा cpuidle_device *dev, bool *dummy)
अणु
	काष्ठा ladder_device *ldev = this_cpu_ptr(&ladder_devices);
	काष्ठा ladder_device_state *last_state;
	पूर्णांक last_idx = dev->last_state_idx;
	पूर्णांक first_idx = drv->states[0].flags & CPUIDLE_FLAG_POLLING ? 1 : 0;
	s64 latency_req = cpuidle_governor_latency_req(dev->cpu);
	s64 last_residency;

	/* Special हाल when user has set very strict latency requirement */
	अगर (unlikely(latency_req == 0)) अणु
		ladder_करो_selection(dev, ldev, last_idx, 0);
		वापस 0;
	पूर्ण

	last_state = &ldev->states[last_idx];

	last_residency = dev->last_residency_ns - drv->states[last_idx].निकास_latency_ns;

	/* consider promotion */
	अगर (last_idx < drv->state_count - 1 &&
	    !dev->states_usage[last_idx + 1].disable &&
	    last_residency > last_state->threshold.promotion_समय_ns &&
	    drv->states[last_idx + 1].निकास_latency_ns <= latency_req) अणु
		last_state->stats.promotion_count++;
		last_state->stats.demotion_count = 0;
		अगर (last_state->stats.promotion_count >= last_state->threshold.promotion_count) अणु
			ladder_करो_selection(dev, ldev, last_idx, last_idx + 1);
			वापस last_idx + 1;
		पूर्ण
	पूर्ण

	/* consider demotion */
	अगर (last_idx > first_idx &&
	    (dev->states_usage[last_idx].disable ||
	    drv->states[last_idx].निकास_latency_ns > latency_req)) अणु
		पूर्णांक i;

		क्रम (i = last_idx - 1; i > first_idx; i--) अणु
			अगर (drv->states[i].निकास_latency_ns <= latency_req)
				अवरोध;
		पूर्ण
		ladder_करो_selection(dev, ldev, last_idx, i);
		वापस i;
	पूर्ण

	अगर (last_idx > first_idx &&
	    last_residency < last_state->threshold.demotion_समय_ns) अणु
		last_state->stats.demotion_count++;
		last_state->stats.promotion_count = 0;
		अगर (last_state->stats.demotion_count >= last_state->threshold.demotion_count) अणु
			ladder_करो_selection(dev, ldev, last_idx, last_idx - 1);
			वापस last_idx - 1;
		पूर्ण
	पूर्ण

	/* otherwise reमुख्य at the current state */
	वापस last_idx;
पूर्ण

/**
 * ladder_enable_device - setup क्रम the governor
 * @drv: cpuidle driver
 * @dev: the CPU
 */
अटल पूर्णांक ladder_enable_device(काष्ठा cpuidle_driver *drv,
				काष्ठा cpuidle_device *dev)
अणु
	पूर्णांक i;
	पूर्णांक first_idx = drv->states[0].flags & CPUIDLE_FLAG_POLLING ? 1 : 0;
	काष्ठा ladder_device *ldev = &per_cpu(ladder_devices, dev->cpu);
	काष्ठा ladder_device_state *lstate;
	काष्ठा cpuidle_state *state;

	dev->last_state_idx = first_idx;

	क्रम (i = first_idx; i < drv->state_count; i++) अणु
		state = &drv->states[i];
		lstate = &ldev->states[i];

		lstate->stats.promotion_count = 0;
		lstate->stats.demotion_count = 0;

		lstate->threshold.promotion_count = PROMOTION_COUNT;
		lstate->threshold.demotion_count = DEMOTION_COUNT;

		अगर (i < drv->state_count - 1)
			lstate->threshold.promotion_समय_ns = state->निकास_latency_ns;
		अगर (i > first_idx)
			lstate->threshold.demotion_समय_ns = state->निकास_latency_ns;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ladder_reflect - update the correct last_state_idx
 * @dev: the CPU
 * @index: the index of actual state entered
 */
अटल व्योम ladder_reflect(काष्ठा cpuidle_device *dev, पूर्णांक index)
अणु
	अगर (index > 0)
		dev->last_state_idx = index;
पूर्ण

अटल काष्ठा cpuidle_governor ladder_governor = अणु
	.name =		"ladder",
	.rating =	10,
	.enable =	ladder_enable_device,
	.select =	ladder_select_state,
	.reflect =	ladder_reflect,
पूर्ण;

/**
 * init_ladder - initializes the governor
 */
अटल पूर्णांक __init init_ladder(व्योम)
अणु
	/*
	 * When NO_HZ is disabled, or when booting with nohz=off, the ladder
	 * governor is better so give it a higher rating than the menu
	 * governor.
	 */
	अगर (!tick_nohz_enabled)
		ladder_governor.rating = 25;

	वापस cpuidle_रेजिस्टर_governor(&ladder_governor);
पूर्ण

postcore_initcall(init_ladder);
