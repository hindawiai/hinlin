<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * coupled.c - helper functions to enter the same idle state on multiple cpus
 *
 * Copyright (c) 2011 Google, Inc.
 *
 * Author: Colin Cross <ccross@android.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "cpuidle.h"

/**
 * DOC: Coupled cpuidle states
 *
 * On some ARM SMP SoCs (OMAP4460, Tegra 2, and probably more), the
 * cpus cannot be independently घातered करोwn, either due to
 * sequencing restrictions (on Tegra 2, cpu 0 must be the last to
 * घातer करोwn), or due to HW bugs (on OMAP4460, a cpu घातering up
 * will corrupt the gic state unless the other cpu runs a work
 * around).  Each cpu has a घातer state that it can enter without
 * coordinating with the other cpu (usually Wait For Interrupt, or
 * WFI), and one or more "coupled" घातer states that affect blocks
 * shared between the cpus (L2 cache, पूर्णांकerrupt controller, and
 * someबार the whole SoC).  Entering a coupled घातer state must
 * be tightly controlled on both cpus.
 *
 * This file implements a solution, where each cpu will रुको in the
 * WFI state until all cpus are पढ़ोy to enter a coupled state, at
 * which poपूर्णांक the coupled state function will be called on all
 * cpus at approximately the same समय.
 *
 * Once all cpus are पढ़ोy to enter idle, they are woken by an smp
 * cross call.  At this poपूर्णांक, there is a chance that one of the
 * cpus will find work to करो, and choose not to enter idle.  A
 * final pass is needed to guarantee that all cpus will call the
 * घातer state enter function at the same समय.  During this pass,
 * each cpu will increment the पढ़ोy counter, and जारी once the
 * पढ़ोy counter matches the number of online coupled cpus.  If any
 * cpu निकासs idle, the other cpus will decrement their counter and
 * retry.
 *
 * requested_state stores the deepest coupled idle state each cpu
 * is पढ़ोy क्रम.  It is assumed that the states are indexed from
 * shallowest (highest घातer, lowest निकास latency) to deepest
 * (lowest घातer, highest निकास latency).  The requested_state
 * variable is not locked.  It is only written from the cpu that
 * it stores (or by the on/offlining cpu अगर that cpu is offline),
 * and only पढ़ो after all the cpus are पढ़ोy क्रम the coupled idle
 * state are are no दीर्घer updating it.
 *
 * Three atomic counters are used.  alive_count tracks the number
 * of cpus in the coupled set that are currently or soon will be
 * online.  रुकोing_count tracks the number of cpus that are in
 * the रुकोing loop, in the पढ़ोy loop, or in the coupled idle state.
 * पढ़ोy_count tracks the number of cpus that are in the पढ़ोy loop
 * or in the coupled idle state.
 *
 * To use coupled cpuidle states, a cpuidle driver must:
 *
 *    Set काष्ठा cpuidle_device.coupled_cpus to the mask of all
 *    coupled cpus, usually the same as cpu_possible_mask अगर all cpus
 *    are part of the same cluster.  The coupled_cpus mask must be
 *    set in the काष्ठा cpuidle_device क्रम each cpu.
 *
 *    Set काष्ठा cpuidle_device.safe_state to a state that is not a
 *    coupled state.  This is usually WFI.
 *
 *    Set CPUIDLE_FLAG_COUPLED in काष्ठा cpuidle_state.flags क्रम each
 *    state that affects multiple cpus.
 *
 *    Provide a काष्ठा cpuidle_state.enter function क्रम each state
 *    that affects multiple cpus.  This function is guaranteed to be
 *    called on all cpus at approximately the same समय.  The driver
 *    should ensure that the cpus all पात together अगर any cpu tries
 *    to पात once the function is called.  The function should वापस
 *    with पूर्णांकerrupts still disabled.
 */

/**
 * काष्ठा cpuidle_coupled - data क्रम set of cpus that share a coupled idle state
 * @coupled_cpus: mask of cpus that are part of the coupled set
 * @requested_state: array of requested states क्रम cpus in the coupled set
 * @पढ़ोy_रुकोing_counts: combined count of cpus  in पढ़ोy or रुकोing loops
 * @पात_barrier: synchronisation poपूर्णांक क्रम पात हालs
 * @online_count: count of cpus that are online
 * @refcnt: reference count of cpuidle devices that are using this काष्ठा
 * @prevent: flag to prevent coupled idle जबतक a cpu is hotplugging
 */
काष्ठा cpuidle_coupled अणु
	cpumask_t coupled_cpus;
	पूर्णांक requested_state[NR_CPUS];
	atomic_t पढ़ोy_रुकोing_counts;
	atomic_t पात_barrier;
	पूर्णांक online_count;
	पूर्णांक refcnt;
	पूर्णांक prevent;
पूर्ण;

#घोषणा WAITING_BITS 16
#घोषणा MAX_WAITING_CPUS (1 << WAITING_BITS)
#घोषणा WAITING_MASK (MAX_WAITING_CPUS - 1)
#घोषणा READY_MASK (~WAITING_MASK)

#घोषणा CPUIDLE_COUPLED_NOT_IDLE	(-1)

अटल DEFINE_PER_CPU(call_single_data_t, cpuidle_coupled_poke_cb);

/*
 * The cpuidle_coupled_poke_pending mask is used to aव्योम calling
 * __smp_call_function_single with the per cpu call_single_data_t काष्ठा alपढ़ोy
 * in use.  This prevents a deadlock where two cpus are रुकोing क्रम each others
 * call_single_data_t काष्ठा to be available
 */
अटल cpumask_t cpuidle_coupled_poke_pending;

/*
 * The cpuidle_coupled_poked mask is used to ensure that each cpu has been poked
 * once to minimize entering the पढ़ोy loop with a poke pending, which would
 * require पातing and retrying.
 */
अटल cpumask_t cpuidle_coupled_poked;

/**
 * cpuidle_coupled_parallel_barrier - synchronize all online coupled cpus
 * @dev: cpuidle_device of the calling cpu
 * @a:   atomic variable to hold the barrier
 *
 * No caller to this function will वापस from this function until all online
 * cpus in the same coupled group have called this function.  Once any caller
 * has वापसed from this function, the barrier is immediately available क्रम
 * reuse.
 *
 * The atomic variable must be initialized to 0 beक्रमe any cpu calls
 * this function, will be reset to 0 beक्रमe any cpu वापसs from this function.
 *
 * Must only be called from within a coupled idle state handler
 * (state.enter when state.flags has CPUIDLE_FLAG_COUPLED set).
 *
 * Provides full smp barrier semantics beक्रमe and after calling.
 */
व्योम cpuidle_coupled_parallel_barrier(काष्ठा cpuidle_device *dev, atomic_t *a)
अणु
	पूर्णांक n = dev->coupled->online_count;

	smp_mb__beक्रमe_atomic();
	atomic_inc(a);

	जबतक (atomic_पढ़ो(a) < n)
		cpu_relax();

	अगर (atomic_inc_वापस(a) == n * 2) अणु
		atomic_set(a, 0);
		वापस;
	पूर्ण

	जबतक (atomic_पढ़ो(a) > n)
		cpu_relax();
पूर्ण

/**
 * cpuidle_state_is_coupled - check अगर a state is part of a coupled set
 * @drv: काष्ठा cpuidle_driver क्रम the platक्रमm
 * @state: index of the target state in drv->states
 *
 * Returns true अगर the target state is coupled with cpus besides this one
 */
bool cpuidle_state_is_coupled(काष्ठा cpuidle_driver *drv, पूर्णांक state)
अणु
	वापस drv->states[state].flags & CPUIDLE_FLAG_COUPLED;
पूर्ण

/**
 * cpuidle_coupled_state_verअगरy - check अगर the coupled states are correctly set.
 * @drv: काष्ठा cpuidle_driver क्रम the platक्रमm
 *
 * Returns 0 क्रम valid state values, a negative error code otherwise:
 *  * -EINVAL अगर any coupled state(safe_state_index) is wrongly set.
 */
पूर्णांक cpuidle_coupled_state_verअगरy(काष्ठा cpuidle_driver *drv)
अणु
	पूर्णांक i;

	क्रम (i = drv->state_count - 1; i >= 0; i--) अणु
		अगर (cpuidle_state_is_coupled(drv, i) &&
		    (drv->safe_state_index == i ||
		     drv->safe_state_index < 0 ||
		     drv->safe_state_index >= drv->state_count))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cpuidle_coupled_set_पढ़ोy - mark a cpu as पढ़ोy
 * @coupled: the काष्ठा coupled that contains the current cpu
 */
अटल अंतरभूत व्योम cpuidle_coupled_set_पढ़ोy(काष्ठा cpuidle_coupled *coupled)
अणु
	atomic_add(MAX_WAITING_CPUS, &coupled->पढ़ोy_रुकोing_counts);
पूर्ण

/**
 * cpuidle_coupled_set_not_पढ़ोy - mark a cpu as not पढ़ोy
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Decrements the पढ़ोy counter, unless the पढ़ोy (and thus the रुकोing) counter
 * is equal to the number of online cpus.  Prevents a race where one cpu
 * decrements the रुकोing counter and then re-increments it just beक्रमe another
 * cpu has decremented its पढ़ोy counter, leading to the पढ़ोy counter going
 * करोwn from the number of online cpus without going through the coupled idle
 * state.
 *
 * Returns 0 अगर the counter was decremented successfully, -EINVAL अगर the पढ़ोy
 * counter was equal to the number of online cpus.
 */
अटल
अंतरभूत पूर्णांक cpuidle_coupled_set_not_पढ़ोy(काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक all;
	पूर्णांक ret;

	all = coupled->online_count | (coupled->online_count << WAITING_BITS);
	ret = atomic_add_unless(&coupled->पढ़ोy_रुकोing_counts,
		-MAX_WAITING_CPUS, all);

	वापस ret ? 0 : -EINVAL;
पूर्ण

/**
 * cpuidle_coupled_no_cpus_पढ़ोy - check अगर no cpus in a coupled set are पढ़ोy
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Returns true अगर all of the cpus in a coupled set are out of the पढ़ोy loop.
 */
अटल अंतरभूत पूर्णांक cpuidle_coupled_no_cpus_पढ़ोy(काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक r = atomic_पढ़ो(&coupled->पढ़ोy_रुकोing_counts) >> WAITING_BITS;
	वापस r == 0;
पूर्ण

/**
 * cpuidle_coupled_cpus_पढ़ोy - check अगर all cpus in a coupled set are पढ़ोy
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Returns true अगर all cpus coupled to this target state are in the पढ़ोy loop
 */
अटल अंतरभूत bool cpuidle_coupled_cpus_पढ़ोy(काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक r = atomic_पढ़ो(&coupled->पढ़ोy_रुकोing_counts) >> WAITING_BITS;
	वापस r == coupled->online_count;
पूर्ण

/**
 * cpuidle_coupled_cpus_रुकोing - check अगर all cpus in a coupled set are रुकोing
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Returns true अगर all cpus coupled to this target state are in the रुको loop
 */
अटल अंतरभूत bool cpuidle_coupled_cpus_रुकोing(काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक w = atomic_पढ़ो(&coupled->पढ़ोy_रुकोing_counts) & WAITING_MASK;
	वापस w == coupled->online_count;
पूर्ण

/**
 * cpuidle_coupled_no_cpus_रुकोing - check अगर no cpus in coupled set are रुकोing
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Returns true अगर all of the cpus in a coupled set are out of the रुकोing loop.
 */
अटल अंतरभूत पूर्णांक cpuidle_coupled_no_cpus_रुकोing(काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक w = atomic_पढ़ो(&coupled->पढ़ोy_रुकोing_counts) & WAITING_MASK;
	वापस w == 0;
पूर्ण

/**
 * cpuidle_coupled_get_state - determine the deepest idle state
 * @dev: काष्ठा cpuidle_device क्रम this cpu
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Returns the deepest idle state that all coupled cpus can enter
 */
अटल अंतरभूत पूर्णांक cpuidle_coupled_get_state(काष्ठा cpuidle_device *dev,
		काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक i;
	पूर्णांक state = पूर्णांक_उच्च;

	/*
	 * Read barrier ensures that पढ़ो of requested_state is ordered after
	 * पढ़ोs of पढ़ोy_count.  Matches the ग_लिखो barriers
	 * cpuidle_set_state_रुकोing.
	 */
	smp_rmb();

	क्रम_each_cpu(i, &coupled->coupled_cpus)
		अगर (cpu_online(i) && coupled->requested_state[i] < state)
			state = coupled->requested_state[i];

	वापस state;
पूर्ण

अटल व्योम cpuidle_coupled_handle_poke(व्योम *info)
अणु
	पूर्णांक cpu = (अचिन्हित दीर्घ)info;
	cpumask_set_cpu(cpu, &cpuidle_coupled_poked);
	cpumask_clear_cpu(cpu, &cpuidle_coupled_poke_pending);
पूर्ण

/**
 * cpuidle_coupled_poke - wake up a cpu that may be रुकोing
 * @cpu: target cpu
 *
 * Ensures that the target cpu निकासs it's रुकोing idle state (अगर it is in it)
 * and will see updates to रुकोing_count beक्रमe it re-enters it's रुकोing idle
 * state.
 *
 * If cpuidle_coupled_poked_mask is alपढ़ोy set क्रम the target cpu, that cpu
 * either has or will soon have a pending IPI that will wake it out of idle,
 * or it is currently processing the IPI and is not in idle.
 */
अटल व्योम cpuidle_coupled_poke(पूर्णांक cpu)
अणु
	call_single_data_t *csd = &per_cpu(cpuidle_coupled_poke_cb, cpu);

	अगर (!cpumask_test_and_set_cpu(cpu, &cpuidle_coupled_poke_pending))
		smp_call_function_single_async(cpu, csd);
पूर्ण

/**
 * cpuidle_coupled_poke_others - wake up all other cpus that may be रुकोing
 * @this_cpu: target cpu
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Calls cpuidle_coupled_poke on all other online cpus.
 */
अटल व्योम cpuidle_coupled_poke_others(पूर्णांक this_cpu,
		काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, &coupled->coupled_cpus)
		अगर (cpu != this_cpu && cpu_online(cpu))
			cpuidle_coupled_poke(cpu);
पूर्ण

/**
 * cpuidle_coupled_set_रुकोing - mark this cpu as in the रुको loop
 * @cpu: target cpu
 * @coupled: the काष्ठा coupled that contains the current cpu
 * @next_state: the index in drv->states of the requested state क्रम this cpu
 *
 * Updates the requested idle state क्रम the specअगरied cpuidle device.
 * Returns the number of रुकोing cpus.
 */
अटल पूर्णांक cpuidle_coupled_set_रुकोing(पूर्णांक cpu,
		काष्ठा cpuidle_coupled *coupled, पूर्णांक next_state)
अणु
	coupled->requested_state[cpu] = next_state;

	/*
	 * The atomic_inc_वापस provides a ग_लिखो barrier to order the ग_लिखो
	 * to requested_state with the later ग_लिखो that increments पढ़ोy_count.
	 */
	वापस atomic_inc_वापस(&coupled->पढ़ोy_रुकोing_counts) & WAITING_MASK;
पूर्ण

/**
 * cpuidle_coupled_set_not_रुकोing - mark this cpu as leaving the रुको loop
 * @cpu: target cpu
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Removes the requested idle state क्रम the specअगरied cpuidle device.
 */
अटल व्योम cpuidle_coupled_set_not_रुकोing(पूर्णांक cpu,
		काष्ठा cpuidle_coupled *coupled)
अणु
	/*
	 * Decrementing रुकोing count can race with incrementing it in
	 * cpuidle_coupled_set_रुकोing, but that's OK.  Worst हाल, some
	 * cpus will increment पढ़ोy_count and then spin until they
	 * notice that this cpu has cleared it's requested_state.
	 */
	atomic_dec(&coupled->पढ़ोy_रुकोing_counts);

	coupled->requested_state[cpu] = CPUIDLE_COUPLED_NOT_IDLE;
पूर्ण

/**
 * cpuidle_coupled_set_करोne - mark this cpu as leaving the पढ़ोy loop
 * @cpu: the current cpu
 * @coupled: the काष्ठा coupled that contains the current cpu
 *
 * Marks this cpu as no दीर्घer in the पढ़ोy and रुकोing loops.  Decrements
 * the रुकोing count first to prevent another cpu looping back in and seeing
 * this cpu as रुकोing just beक्रमe it निकासs idle.
 */
अटल व्योम cpuidle_coupled_set_करोne(पूर्णांक cpu, काष्ठा cpuidle_coupled *coupled)
अणु
	cpuidle_coupled_set_not_रुकोing(cpu, coupled);
	atomic_sub(MAX_WAITING_CPUS, &coupled->पढ़ोy_रुकोing_counts);
पूर्ण

/**
 * cpuidle_coupled_clear_pokes - spin until the poke पूर्णांकerrupt is processed
 * @cpu: this cpu
 *
 * Turns on पूर्णांकerrupts and spins until any outstanding poke पूर्णांकerrupts have
 * been processed and the poke bit has been cleared.
 *
 * Other पूर्णांकerrupts may also be processed जबतक पूर्णांकerrupts are enabled, so
 * need_resched() must be tested after this function वापसs to make sure
 * the पूर्णांकerrupt didn't schedule work that should take the cpu out of idle.
 *
 * Returns 0 अगर no poke was pending, 1 अगर a poke was cleared.
 */
अटल पूर्णांक cpuidle_coupled_clear_pokes(पूर्णांक cpu)
अणु
	अगर (!cpumask_test_cpu(cpu, &cpuidle_coupled_poke_pending))
		वापस 0;

	local_irq_enable();
	जबतक (cpumask_test_cpu(cpu, &cpuidle_coupled_poke_pending))
		cpu_relax();
	local_irq_disable();

	वापस 1;
पूर्ण

अटल bool cpuidle_coupled_any_pokes_pending(काष्ठा cpuidle_coupled *coupled)
अणु
	cpumask_t cpus;
	पूर्णांक ret;

	cpumask_and(&cpus, cpu_online_mask, &coupled->coupled_cpus);
	ret = cpumask_and(&cpus, &cpuidle_coupled_poke_pending, &cpus);

	वापस ret;
पूर्ण

/**
 * cpuidle_enter_state_coupled - attempt to enter a state with coupled cpus
 * @dev: काष्ठा cpuidle_device क्रम the current cpu
 * @drv: काष्ठा cpuidle_driver क्रम the platक्रमm
 * @next_state: index of the requested state in drv->states
 *
 * Coordinate with coupled cpus to enter the target state.  This is a two
 * stage process.  In the first stage, the cpus are operating independently,
 * and may call पूर्णांकo cpuidle_enter_state_coupled at completely dअगरferent बार.
 * To save as much घातer as possible, the first cpus to call this function will
 * go to an पूर्णांकermediate state (the cpuidle_device's safe state), and रुको क्रम
 * all the other cpus to call this function.  Once all coupled cpus are idle,
 * the second stage will start.  Each coupled cpu will spin until all cpus have
 * guaranteed that they will call the target_state.
 *
 * This function must be called with पूर्णांकerrupts disabled.  It may enable
 * पूर्णांकerrupts जबतक preparing क्रम idle, and it will always वापस with
 * पूर्णांकerrupts enabled.
 */
पूर्णांक cpuidle_enter_state_coupled(काष्ठा cpuidle_device *dev,
		काष्ठा cpuidle_driver *drv, पूर्णांक next_state)
अणु
	पूर्णांक entered_state = -1;
	काष्ठा cpuidle_coupled *coupled = dev->coupled;
	पूर्णांक w;

	अगर (!coupled)
		वापस -EINVAL;

	जबतक (coupled->prevent) अणु
		cpuidle_coupled_clear_pokes(dev->cpu);
		अगर (need_resched()) अणु
			local_irq_enable();
			वापस entered_state;
		पूर्ण
		entered_state = cpuidle_enter_state(dev, drv,
			drv->safe_state_index);
		local_irq_disable();
	पूर्ण

	/* Read barrier ensures online_count is पढ़ो after prevent is cleared */
	smp_rmb();

reset:
	cpumask_clear_cpu(dev->cpu, &cpuidle_coupled_poked);

	w = cpuidle_coupled_set_रुकोing(dev->cpu, coupled, next_state);
	/*
	 * If this is the last cpu to enter the रुकोing state, poke
	 * all the other cpus out of their रुकोing state so they can
	 * enter a deeper state.  This can race with one of the cpus
	 * निकासing the रुकोing state due to an पूर्णांकerrupt and
	 * decrementing रुकोing_count, see comment below.
	 */
	अगर (w == coupled->online_count) अणु
		cpumask_set_cpu(dev->cpu, &cpuidle_coupled_poked);
		cpuidle_coupled_poke_others(dev->cpu, coupled);
	पूर्ण

retry:
	/*
	 * Wait क्रम all coupled cpus to be idle, using the deepest state
	 * allowed क्रम a single cpu.  If this was not the poking cpu, रुको
	 * क्रम at least one poke beक्रमe leaving to aव्योम a race where
	 * two cpus could arrive at the रुकोing loop at the same समय,
	 * but the first of the two to arrive could skip the loop without
	 * processing the pokes from the last to arrive.
	 */
	जबतक (!cpuidle_coupled_cpus_रुकोing(coupled) ||
			!cpumask_test_cpu(dev->cpu, &cpuidle_coupled_poked)) अणु
		अगर (cpuidle_coupled_clear_pokes(dev->cpu))
			जारी;

		अगर (need_resched()) अणु
			cpuidle_coupled_set_not_रुकोing(dev->cpu, coupled);
			जाओ out;
		पूर्ण

		अगर (coupled->prevent) अणु
			cpuidle_coupled_set_not_रुकोing(dev->cpu, coupled);
			जाओ out;
		पूर्ण

		entered_state = cpuidle_enter_state(dev, drv,
			drv->safe_state_index);
		local_irq_disable();
	पूर्ण

	cpuidle_coupled_clear_pokes(dev->cpu);
	अगर (need_resched()) अणु
		cpuidle_coupled_set_not_रुकोing(dev->cpu, coupled);
		जाओ out;
	पूर्ण

	/*
	 * Make sure final poke status क्रम this cpu is visible beक्रमe setting
	 * cpu as पढ़ोy.
	 */
	smp_wmb();

	/*
	 * All coupled cpus are probably idle.  There is a small chance that
	 * one of the other cpus just became active.  Increment the पढ़ोy count,
	 * and spin until all coupled cpus have incremented the counter. Once a
	 * cpu has incremented the पढ़ोy counter, it cannot पात idle and must
	 * spin until either all cpus have incremented the पढ़ोy counter, or
	 * another cpu leaves idle and decrements the रुकोing counter.
	 */

	cpuidle_coupled_set_पढ़ोy(coupled);
	जबतक (!cpuidle_coupled_cpus_पढ़ोy(coupled)) अणु
		/* Check अगर any other cpus bailed out of idle. */
		अगर (!cpuidle_coupled_cpus_रुकोing(coupled))
			अगर (!cpuidle_coupled_set_not_पढ़ोy(coupled))
				जाओ retry;

		cpu_relax();
	पूर्ण

	/*
	 * Make sure पढ़ो of all cpus पढ़ोy is करोne beक्रमe पढ़ोing pending pokes
	 */
	smp_rmb();

	/*
	 * There is a small chance that a cpu left and reentered idle after this
	 * cpu saw that all cpus were रुकोing.  The cpu that reentered idle will
	 * have sent this cpu a poke, which will still be pending after the
	 * पढ़ोy loop.  The pending पूर्णांकerrupt may be lost by the पूर्णांकerrupt
	 * controller when entering the deep idle state.  It's not possible to
	 * clear a pending पूर्णांकerrupt without turning पूर्णांकerrupts on and handling
	 * it, and it's too late to turn on पूर्णांकerrupts here, so reset the
	 * coupled idle state of all cpus and retry.
	 */
	अगर (cpuidle_coupled_any_pokes_pending(coupled)) अणु
		cpuidle_coupled_set_करोne(dev->cpu, coupled);
		/* Wait क्रम all cpus to see the pending pokes */
		cpuidle_coupled_parallel_barrier(dev, &coupled->पात_barrier);
		जाओ reset;
	पूर्ण

	/* all cpus have acked the coupled state */
	next_state = cpuidle_coupled_get_state(dev, coupled);

	entered_state = cpuidle_enter_state(dev, drv, next_state);

	cpuidle_coupled_set_करोne(dev->cpu, coupled);

out:
	/*
	 * Normal cpuidle states are expected to वापस with irqs enabled.
	 * That leads to an inefficiency where a cpu receiving an पूर्णांकerrupt
	 * that brings it out of idle will process that पूर्णांकerrupt beक्रमe
	 * निकासing the idle enter function and decrementing पढ़ोy_count.  All
	 * other cpus will need to spin रुकोing क्रम the cpu that is processing
	 * the पूर्णांकerrupt.  If the driver वापसs with पूर्णांकerrupts disabled,
	 * all other cpus will loop back पूर्णांकo the safe idle state instead of
	 * spinning, saving घातer.
	 *
	 * Calling local_irq_enable here allows coupled states to वापस with
	 * पूर्णांकerrupts disabled, but won't cause problems क्रम drivers that
	 * निकास with पूर्णांकerrupts enabled.
	 */
	local_irq_enable();

	/*
	 * Wait until all coupled cpus have निकासed idle.  There is no risk that
	 * a cpu निकासs and re-enters the पढ़ोy state because this cpu has
	 * alपढ़ोy decremented its रुकोing_count.
	 */
	जबतक (!cpuidle_coupled_no_cpus_पढ़ोy(coupled))
		cpu_relax();

	वापस entered_state;
पूर्ण

अटल व्योम cpuidle_coupled_update_online_cpus(काष्ठा cpuidle_coupled *coupled)
अणु
	cpumask_t cpus;
	cpumask_and(&cpus, cpu_online_mask, &coupled->coupled_cpus);
	coupled->online_count = cpumask_weight(&cpus);
पूर्ण

/**
 * cpuidle_coupled_रेजिस्टर_device - रेजिस्टर a coupled cpuidle device
 * @dev: काष्ठा cpuidle_device क्रम the current cpu
 *
 * Called from cpuidle_रेजिस्टर_device to handle coupled idle init.  Finds the
 * cpuidle_coupled काष्ठा क्रम this set of coupled cpus, or creates one अगर none
 * exists yet.
 */
पूर्णांक cpuidle_coupled_रेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणु
	पूर्णांक cpu;
	काष्ठा cpuidle_device *other_dev;
	call_single_data_t *csd;
	काष्ठा cpuidle_coupled *coupled;

	अगर (cpumask_empty(&dev->coupled_cpus))
		वापस 0;

	क्रम_each_cpu(cpu, &dev->coupled_cpus) अणु
		other_dev = per_cpu(cpuidle_devices, cpu);
		अगर (other_dev && other_dev->coupled) अणु
			coupled = other_dev->coupled;
			जाओ have_coupled;
		पूर्ण
	पूर्ण

	/* No existing coupled info found, create a new one */
	coupled = kzalloc(माप(काष्ठा cpuidle_coupled), GFP_KERNEL);
	अगर (!coupled)
		वापस -ENOMEM;

	coupled->coupled_cpus = dev->coupled_cpus;

have_coupled:
	dev->coupled = coupled;
	अगर (WARN_ON(!cpumask_equal(&dev->coupled_cpus, &coupled->coupled_cpus)))
		coupled->prevent++;

	cpuidle_coupled_update_online_cpus(coupled);

	coupled->refcnt++;

	csd = &per_cpu(cpuidle_coupled_poke_cb, dev->cpu);
	INIT_CSD(csd, cpuidle_coupled_handle_poke, (व्योम *)(अचिन्हित दीर्घ)dev->cpu);

	वापस 0;
पूर्ण

/**
 * cpuidle_coupled_unरेजिस्टर_device - unरेजिस्टर a coupled cpuidle device
 * @dev: काष्ठा cpuidle_device क्रम the current cpu
 *
 * Called from cpuidle_unरेजिस्टर_device to tear करोwn coupled idle.  Removes the
 * cpu from the coupled idle set, and मुक्तs the cpuidle_coupled_info काष्ठा अगर
 * this was the last cpu in the set.
 */
व्योम cpuidle_coupled_unरेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणु
	काष्ठा cpuidle_coupled *coupled = dev->coupled;

	अगर (cpumask_empty(&dev->coupled_cpus))
		वापस;

	अगर (--coupled->refcnt)
		kमुक्त(coupled);
	dev->coupled = शून्य;
पूर्ण

/**
 * cpuidle_coupled_prevent_idle - prevent cpus from entering a coupled state
 * @coupled: the काष्ठा coupled that contains the cpu that is changing state
 *
 * Disables coupled cpuidle on a coupled set of cpus.  Used to ensure that
 * cpu_online_mask करोesn't change जबतक cpus are coordinating coupled idle.
 */
अटल व्योम cpuidle_coupled_prevent_idle(काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक cpu = get_cpu();

	/* Force all cpus out of the रुकोing loop. */
	coupled->prevent++;
	cpuidle_coupled_poke_others(cpu, coupled);
	put_cpu();
	जबतक (!cpuidle_coupled_no_cpus_रुकोing(coupled))
		cpu_relax();
पूर्ण

/**
 * cpuidle_coupled_allow_idle - allows cpus to enter a coupled state
 * @coupled: the काष्ठा coupled that contains the cpu that is changing state
 *
 * Enables coupled cpuidle on a coupled set of cpus.  Used to ensure that
 * cpu_online_mask करोesn't change जबतक cpus are coordinating coupled idle.
 */
अटल व्योम cpuidle_coupled_allow_idle(काष्ठा cpuidle_coupled *coupled)
अणु
	पूर्णांक cpu = get_cpu();

	/*
	 * Write barrier ensures पढ़ोers see the new online_count when they
	 * see prevent == 0.
	 */
	smp_wmb();
	coupled->prevent--;
	/* Force cpus out of the prevent loop. */
	cpuidle_coupled_poke_others(cpu, coupled);
	put_cpu();
पूर्ण

अटल पूर्णांक coupled_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuidle_device *dev;

	mutex_lock(&cpuidle_lock);

	dev = per_cpu(cpuidle_devices, cpu);
	अगर (dev && dev->coupled) अणु
		cpuidle_coupled_update_online_cpus(dev->coupled);
		cpuidle_coupled_allow_idle(dev->coupled);
	पूर्ण

	mutex_unlock(&cpuidle_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक coupled_cpu_up_prepare(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuidle_device *dev;

	mutex_lock(&cpuidle_lock);

	dev = per_cpu(cpuidle_devices, cpu);
	अगर (dev && dev->coupled)
		cpuidle_coupled_prevent_idle(dev->coupled);

	mutex_unlock(&cpuidle_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __init cpuidle_coupled_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_nocalls(CPUHP_CPUIDLE_COUPLED_PREPARE,
					"cpuidle/coupled:prepare",
					coupled_cpu_up_prepare,
					coupled_cpu_online);
	अगर (ret)
		वापस ret;
	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"cpuidle/coupled:online",
					coupled_cpu_online,
					coupled_cpu_up_prepare);
	अगर (ret < 0)
		cpuhp_हटाओ_state_nocalls(CPUHP_CPUIDLE_COUPLED_PREPARE);
	वापस ret;
पूर्ण
core_initcall(cpuidle_coupled_init);
