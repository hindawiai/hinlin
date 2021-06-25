<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * menu.c - the menu idle governor
 *
 * Copyright (C) 2006-2007 Adam Belay <abelay@novell.com>
 * Copyright (C) 2009 Intel Corporation
 * Author:
 *        Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/समय.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/tick.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/math64.h>

#घोषणा BUCKETS 12
#घोषणा INTERVAL_SHIFT 3
#घोषणा INTERVALS (1UL << INTERVAL_SHIFT)
#घोषणा RESOLUTION 1024
#घोषणा DECAY 8
#घोषणा MAX_INTERESTING (50000 * NSEC_PER_USEC)

/*
 * Concepts and ideas behind the menu governor
 *
 * For the menu governor, there are 3 decision factors क्रम picking a C
 * state:
 * 1) Energy अवरोध even poपूर्णांक
 * 2) Perक्रमmance impact
 * 3) Latency tolerance (from pmqos infraकाष्ठाure)
 * These these three factors are treated independently.
 *
 * Energy अवरोध even poपूर्णांक
 * -----------------------
 * C state entry and निकास have an energy cost, and a certain amount of समय in
 * the  C state is required to actually अवरोध even on this cost. CPUIDLE
 * provides us this duration in the "target_residency" field. So all that we
 * need is a good prediction of how दीर्घ we'll be idle. Like the traditional
 * menu governor, we start with the actual known "next timer event" समय.
 *
 * Since there are other source of wakeups (पूर्णांकerrupts क्रम example) than
 * the next समयr event, this estimation is rather optimistic. To get a
 * more realistic estimate, a correction factor is applied to the estimate,
 * that is based on historic behavior. For example, अगर in the past the actual
 * duration always was 50% of the next समयr tick, the correction factor will
 * be 0.5.
 *
 * menu uses a running average क्रम this correction factor, however it uses a
 * set of factors, not just a single factor. This stems from the realization
 * that the ratio is dependent on the order of magnitude of the expected
 * duration; अगर we expect 500 milliseconds of idle समय the likelihood of
 * getting an पूर्णांकerrupt very early is much higher than अगर we expect 50 micro
 * seconds of idle समय. A second independent factor that has big impact on
 * the actual factor is अगर there is (disk) IO outstanding or not.
 * (as a special twist, we consider every sleep दीर्घer than 50 milliseconds
 * as perfect; there are no घातer gains क्रम sleeping दीर्घer than this)
 *
 * For these two reasons we keep an array of 12 independent factors, that माला_लो
 * indexed based on the magnitude of the expected duration as well as the
 * "is IO outstanding" property.
 *
 * Repeatable-पूर्णांकerval-detector
 * ----------------------------
 * There are some हालs where "next timer" is a completely unusable predictor:
 * Those हालs where the पूर्णांकerval is fixed, क्रम example due to hardware
 * पूर्णांकerrupt mitigation, but also due to fixed transfer rate devices such as
 * mice.
 * For this, we use a dअगरferent predictor: We track the duration of the last 8
 * पूर्णांकervals and अगर the stand deviation of these 8 पूर्णांकervals is below a
 * threshold value, we use the average of these पूर्णांकervals as prediction.
 *
 * Limiting Perक्रमmance Impact
 * ---------------------------
 * C states, especially those with large निकास latencies, can have a real
 * noticeable impact on workloads, which is not acceptable क्रम most sysadmins,
 * and in addition, less perक्रमmance has a घातer price of its own.
 *
 * As a general rule of thumb, menu assumes that the following heuristic
 * holds:
 *     The busier the प्रणाली, the less impact of C states is acceptable
 *
 * This rule-of-thumb is implemented using a perक्रमmance-multiplier:
 * If the निकास latency बार the perक्रमmance multiplier is दीर्घer than
 * the predicted duration, the C state is not considered a candidate
 * क्रम selection due to a too high perक्रमmance impact. So the higher
 * this multiplier is, the दीर्घer we need to be idle to pick a deep C
 * state, and thus the less likely a busy CPU will hit such a deep
 * C state.
 *
 * Two factors are used in determing this multiplier:
 * a value of 10 is added क्रम each poपूर्णांक of "per cpu load average" we have.
 * a value of 5 poपूर्णांकs is added क्रम each process that is रुकोing क्रम
 * IO on this CPU.
 * (these values are experimentally determined)
 *
 * The load average factor gives a दीर्घer term (few seconds) input to the
 * decision, जबतक the ioरुको value gives a cpu local instantanious input.
 * The ioरुको factor may look low, but realize that this is also alपढ़ोy
 * represented in the प्रणाली load average.
 *
 */

काष्ठा menu_device अणु
	पूर्णांक             needs_update;
	पूर्णांक             tick_wakeup;

	u64		next_समयr_ns;
	अचिन्हित पूर्णांक	bucket;
	अचिन्हित पूर्णांक	correction_factor[BUCKETS];
	अचिन्हित पूर्णांक	पूर्णांकervals[INTERVALS];
	पूर्णांक		पूर्णांकerval_ptr;
पूर्ण;

अटल अंतरभूत पूर्णांक which_bucket(u64 duration_ns, अचिन्हित दीर्घ nr_ioरुकोers)
अणु
	पूर्णांक bucket = 0;

	/*
	 * We keep two groups of stats; one with no
	 * IO pending, one without.
	 * This allows us to calculate
	 * E(duration)|ioरुको
	 */
	अगर (nr_ioरुकोers)
		bucket = BUCKETS/2;

	अगर (duration_ns < 10ULL * NSEC_PER_USEC)
		वापस bucket;
	अगर (duration_ns < 100ULL * NSEC_PER_USEC)
		वापस bucket + 1;
	अगर (duration_ns < 1000ULL * NSEC_PER_USEC)
		वापस bucket + 2;
	अगर (duration_ns < 10000ULL * NSEC_PER_USEC)
		वापस bucket + 3;
	अगर (duration_ns < 100000ULL * NSEC_PER_USEC)
		वापस bucket + 4;
	वापस bucket + 5;
पूर्ण

/*
 * Return a multiplier क्रम the निकास latency that is पूर्णांकended
 * to take perक्रमmance requirements पूर्णांकo account.
 * The more perक्रमmance critical we estimate the प्रणाली
 * to be, the higher this multiplier, and thus the higher
 * the barrier to go to an expensive C state.
 */
अटल अंतरभूत पूर्णांक perक्रमmance_multiplier(अचिन्हित दीर्घ nr_ioरुकोers)
अणु
	/* क्रम IO रुको tasks (per cpu!) we add 10x each */
	वापस 1 + 10 * nr_ioरुकोers;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा menu_device, menu_devices);

अटल व्योम menu_update(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev);

/*
 * Try detecting repeating patterns by keeping track of the last 8
 * पूर्णांकervals, and checking अगर the standard deviation of that set
 * of poपूर्णांकs is below a threshold. If it is... then use the
 * average of these 8 poपूर्णांकs as the estimated value.
 */
अटल अचिन्हित पूर्णांक get_typical_पूर्णांकerval(काष्ठा menu_device *data,
					 अचिन्हित पूर्णांक predicted_us)
अणु
	पूर्णांक i, भागisor;
	अचिन्हित पूर्णांक min, max, thresh, avg;
	uपूर्णांक64_t sum, variance;

	thresh = पूर्णांक_उच्च; /* Discard outliers above this value */

again:

	/* First calculate the average of past पूर्णांकervals */
	min = अच_पूर्णांक_उच्च;
	max = 0;
	sum = 0;
	भागisor = 0;
	क्रम (i = 0; i < INTERVALS; i++) अणु
		अचिन्हित पूर्णांक value = data->पूर्णांकervals[i];
		अगर (value <= thresh) अणु
			sum += value;
			भागisor++;
			अगर (value > max)
				max = value;

			अगर (value < min)
				min = value;
		पूर्ण
	पूर्ण

	/*
	 * If the result of the computation is going to be discarded anyway,
	 * aव्योम the computation altogether.
	 */
	अगर (min >= predicted_us)
		वापस अच_पूर्णांक_उच्च;

	अगर (भागisor == INTERVALS)
		avg = sum >> INTERVAL_SHIFT;
	अन्यथा
		avg = भाग_u64(sum, भागisor);

	/* Then try to determine variance */
	variance = 0;
	क्रम (i = 0; i < INTERVALS; i++) अणु
		अचिन्हित पूर्णांक value = data->पूर्णांकervals[i];
		अगर (value <= thresh) अणु
			पूर्णांक64_t dअगरf = (पूर्णांक64_t)value - avg;
			variance += dअगरf * dअगरf;
		पूर्ण
	पूर्ण
	अगर (भागisor == INTERVALS)
		variance >>= INTERVAL_SHIFT;
	अन्यथा
		करो_भाग(variance, भागisor);

	/*
	 * The typical पूर्णांकerval is obtained when standard deviation is
	 * small (stddev <= 20 us, variance <= 400 us^2) or standard
	 * deviation is small compared to the average पूर्णांकerval (avg >
	 * 6*stddev, avg^2 > 36*variance). The average is smaller than
	 * अच_पूर्णांक_उच्च aka U32_MAX, so computing its square करोes not
	 * overflow a u64. We simply reject this candidate average अगर
	 * the standard deviation is greater than 715 s (which is
	 * rather unlikely).
	 *
	 * Use this result only अगर there is no समयr to wake us up sooner.
	 */
	अगर (likely(variance <= U64_MAX/36)) अणु
		अगर ((((u64)avg*avg > variance*36) && (भागisor * 4 >= INTERVALS * 3))
							|| variance <= 400) अणु
			वापस avg;
		पूर्ण
	पूर्ण

	/*
	 * If we have outliers to the upside in our distribution, discard
	 * those by setting the threshold to exclude these outliers, then
	 * calculate the average and standard deviation again. Once we get
	 * करोwn to the bottom 3/4 of our samples, stop excluding samples.
	 *
	 * This can deal with workloads that have दीर्घ छोड़ोs पूर्णांकerspersed
	 * with sporadic activity with a bunch of लघु छोड़ोs.
	 */
	अगर ((भागisor * 4) <= INTERVALS * 3)
		वापस अच_पूर्णांक_उच्च;

	thresh = max - 1;
	जाओ again;
पूर्ण

/**
 * menu_select - selects the next idle state to enter
 * @drv: cpuidle driver containing state data
 * @dev: the CPU
 * @stop_tick: indication on whether or not to stop the tick
 */
अटल पूर्णांक menu_select(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev,
		       bool *stop_tick)
अणु
	काष्ठा menu_device *data = this_cpu_ptr(&menu_devices);
	s64 latency_req = cpuidle_governor_latency_req(dev->cpu);
	अचिन्हित पूर्णांक predicted_us;
	u64 predicted_ns;
	u64 पूर्णांकeractivity_req;
	अचिन्हित दीर्घ nr_ioरुकोers;
	kसमय_प्रकार delta, delta_tick;
	पूर्णांक i, idx;

	अगर (data->needs_update) अणु
		menu_update(drv, dev);
		data->needs_update = 0;
	पूर्ण

	/* determine the expected residency समय, round up */
	delta = tick_nohz_get_sleep_length(&delta_tick);
	अगर (unlikely(delta < 0)) अणु
		delta = 0;
		delta_tick = 0;
	पूर्ण
	data->next_समयr_ns = delta;

	nr_ioरुकोers = nr_ioरुको_cpu(dev->cpu);
	data->bucket = which_bucket(data->next_समयr_ns, nr_ioरुकोers);

	अगर (unlikely(drv->state_count <= 1 || latency_req == 0) ||
	    ((data->next_समयr_ns < drv->states[1].target_residency_ns ||
	      latency_req < drv->states[1].निकास_latency_ns) &&
	     !dev->states_usage[0].disable)) अणु
		/*
		 * In this हाल state[0] will be used no matter what, so वापस
		 * it right away and keep the tick running अगर state[0] is a
		 * polling one.
		 */
		*stop_tick = !(drv->states[0].flags & CPUIDLE_FLAG_POLLING);
		वापस 0;
	पूर्ण

	/* Round up the result क्रम half microseconds. */
	predicted_us = भाग_u64(data->next_समयr_ns *
			       data->correction_factor[data->bucket] +
			       (RESOLUTION * DECAY * NSEC_PER_USEC) / 2,
			       RESOLUTION * DECAY * NSEC_PER_USEC);
	/* Use the lowest expected idle पूर्णांकerval to pick the idle state. */
	predicted_ns = (u64)min(predicted_us,
				get_typical_पूर्णांकerval(data, predicted_us)) *
				NSEC_PER_USEC;

	अगर (tick_nohz_tick_stopped()) अणु
		/*
		 * If the tick is alपढ़ोy stopped, the cost of possible लघु
		 * idle duration misprediction is much higher, because the CPU
		 * may be stuck in a shallow idle state क्रम a दीर्घ समय as a
		 * result of it.  In that हाल say we might mispredict and use
		 * the known समय till the बंदst समयr event क्रम the idle
		 * state selection.
		 */
		अगर (predicted_ns < TICK_NSEC)
			predicted_ns = data->next_समयr_ns;
	पूर्ण अन्यथा अणु
		/*
		 * Use the perक्रमmance multiplier and the user-configurable
		 * latency_req to determine the maximum निकास latency.
		 */
		पूर्णांकeractivity_req = भाग64_u64(predicted_ns,
					      perक्रमmance_multiplier(nr_ioरुकोers));
		अगर (latency_req > पूर्णांकeractivity_req)
			latency_req = पूर्णांकeractivity_req;
	पूर्ण

	/*
	 * Find the idle state with the lowest घातer जबतक satisfying
	 * our स्थिरraपूर्णांकs.
	 */
	idx = -1;
	क्रम (i = 0; i < drv->state_count; i++) अणु
		काष्ठा cpuidle_state *s = &drv->states[i];

		अगर (dev->states_usage[i].disable)
			जारी;

		अगर (idx == -1)
			idx = i; /* first enabled state */

		अगर (s->target_residency_ns > predicted_ns) अणु
			/*
			 * Use a physical idle state, not busy polling, unless
			 * a समयr is going to trigger soon enough.
			 */
			अगर ((drv->states[idx].flags & CPUIDLE_FLAG_POLLING) &&
			    s->निकास_latency_ns <= latency_req &&
			    s->target_residency_ns <= data->next_समयr_ns) अणु
				predicted_ns = s->target_residency_ns;
				idx = i;
				अवरोध;
			पूर्ण
			अगर (predicted_ns < TICK_NSEC)
				अवरोध;

			अगर (!tick_nohz_tick_stopped()) अणु
				/*
				 * If the state selected so far is shallow,
				 * waking up early won't hurt, so retain the
				 * tick in that हाल and let the governor run
				 * again in the next iteration of the loop.
				 */
				predicted_ns = drv->states[idx].target_residency_ns;
				अवरोध;
			पूर्ण

			/*
			 * If the state selected so far is shallow and this
			 * state's target residency matches the समय till the
			 * बंदst समयr event, select this one to aव्योम getting
			 * stuck in the shallow one क्रम too दीर्घ.
			 */
			अगर (drv->states[idx].target_residency_ns < TICK_NSEC &&
			    s->target_residency_ns <= delta_tick)
				idx = i;

			वापस idx;
		पूर्ण
		अगर (s->निकास_latency_ns > latency_req)
			अवरोध;

		idx = i;
	पूर्ण

	अगर (idx == -1)
		idx = 0; /* No states enabled. Must use 0. */

	/*
	 * Don't stop the tick अगर the selected state is a polling one or अगर the
	 * expected idle duration is लघुer than the tick period length.
	 */
	अगर (((drv->states[idx].flags & CPUIDLE_FLAG_POLLING) ||
	     predicted_ns < TICK_NSEC) && !tick_nohz_tick_stopped()) अणु
		*stop_tick = false;

		अगर (idx > 0 && drv->states[idx].target_residency_ns > delta_tick) अणु
			/*
			 * The tick is not going to be stopped and the target
			 * residency of the state to be वापसed is not within
			 * the समय until the next समयr event including the
			 * tick, so try to correct that.
			 */
			क्रम (i = idx - 1; i >= 0; i--) अणु
				अगर (dev->states_usage[i].disable)
					जारी;

				idx = i;
				अगर (drv->states[i].target_residency_ns <= delta_tick)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस idx;
पूर्ण

/**
 * menu_reflect - records that data काष्ठाures need update
 * @dev: the CPU
 * @index: the index of actual entered state
 *
 * NOTE: it's important to be fast here because this operation will add to
 *       the overall निकास latency.
 */
अटल व्योम menu_reflect(काष्ठा cpuidle_device *dev, पूर्णांक index)
अणु
	काष्ठा menu_device *data = this_cpu_ptr(&menu_devices);

	dev->last_state_idx = index;
	data->needs_update = 1;
	data->tick_wakeup = tick_nohz_idle_got_tick();
पूर्ण

/**
 * menu_update - attempts to guess what happened after entry
 * @drv: cpuidle driver containing state data
 * @dev: the CPU
 */
अटल व्योम menu_update(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev)
अणु
	काष्ठा menu_device *data = this_cpu_ptr(&menu_devices);
	पूर्णांक last_idx = dev->last_state_idx;
	काष्ठा cpuidle_state *target = &drv->states[last_idx];
	u64 measured_ns;
	अचिन्हित पूर्णांक new_factor;

	/*
	 * Try to figure out how much समय passed between entry to low
	 * घातer state and occurrence of the wakeup event.
	 *
	 * If the entered idle state didn't support residency measurements,
	 * we use them anyway अगर they are लघु, and अगर दीर्घ,
	 * truncate to the whole expected समय.
	 *
	 * Any measured amount of समय will include the निकास latency.
	 * Since we are पूर्णांकerested in when the wakeup begun, not when it
	 * was completed, we must subtract the निकास latency. However, अगर
	 * the measured amount of समय is less than the निकास latency,
	 * assume the state was never reached and the निकास latency is 0.
	 */

	अगर (data->tick_wakeup && data->next_समयr_ns > TICK_NSEC) अणु
		/*
		 * The nohz code said that there wouldn't be any events within
		 * the tick boundary (अगर the tick was stopped), but the idle
		 * duration predictor had a dअगरfering opinion.  Since the CPU
		 * was woken up by a tick (that wasn't stopped after all), the
		 * predictor was not quite right, so assume that the CPU could
		 * have been idle दीर्घ (but not क्रमever) to help the idle
		 * duration predictor करो a better job next समय.
		 */
		measured_ns = 9 * MAX_INTERESTING / 10;
	पूर्ण अन्यथा अगर ((drv->states[last_idx].flags & CPUIDLE_FLAG_POLLING) &&
		   dev->poll_समय_limit) अणु
		/*
		 * The CPU निकासed the "polling" state due to a समय limit, so
		 * the idle duration prediction leading to the selection of that
		 * state was inaccurate.  If a better prediction had been made,
		 * the CPU might have been woken up from idle by the next समयr.
		 * Assume that to be the हाल.
		 */
		measured_ns = data->next_समयr_ns;
	पूर्ण अन्यथा अणु
		/* measured value */
		measured_ns = dev->last_residency_ns;

		/* Deduct निकास latency */
		अगर (measured_ns > 2 * target->निकास_latency_ns)
			measured_ns -= target->निकास_latency_ns;
		अन्यथा
			measured_ns /= 2;
	पूर्ण

	/* Make sure our coefficients करो not exceed unity */
	अगर (measured_ns > data->next_समयr_ns)
		measured_ns = data->next_समयr_ns;

	/* Update our correction ratio */
	new_factor = data->correction_factor[data->bucket];
	new_factor -= new_factor / DECAY;

	अगर (data->next_समयr_ns > 0 && measured_ns < MAX_INTERESTING)
		new_factor += भाग64_u64(RESOLUTION * measured_ns,
					data->next_समयr_ns);
	अन्यथा
		/*
		 * we were idle so दीर्घ that we count it as a perfect
		 * prediction
		 */
		new_factor += RESOLUTION;

	/*
	 * We करोn't want 0 as factor; we always want at least
	 * a tiny bit of estimated समय. Fortunately, due to rounding,
	 * new_factor will stay nonzero regardless of measured_us values
	 * and the compiler can eliminate this test as दीर्घ as DECAY > 1.
	 */
	अगर (DECAY == 1 && unlikely(new_factor == 0))
		new_factor = 1;

	data->correction_factor[data->bucket] = new_factor;

	/* update the repeating-pattern data */
	data->पूर्णांकervals[data->पूर्णांकerval_ptr++] = kसमय_प्रकारo_us(measured_ns);
	अगर (data->पूर्णांकerval_ptr >= INTERVALS)
		data->पूर्णांकerval_ptr = 0;
पूर्ण

/**
 * menu_enable_device - scans a CPU's states and करोes setup
 * @drv: cpuidle driver
 * @dev: the CPU
 */
अटल पूर्णांक menu_enable_device(काष्ठा cpuidle_driver *drv,
				काष्ठा cpuidle_device *dev)
अणु
	काष्ठा menu_device *data = &per_cpu(menu_devices, dev->cpu);
	पूर्णांक i;

	स_रखो(data, 0, माप(काष्ठा menu_device));

	/*
	 * अगर the correction factor is 0 (eg first समय init or cpu hotplug
	 * etc), we actually want to start out with a unity factor.
	 */
	क्रम(i = 0; i < BUCKETS; i++)
		data->correction_factor[i] = RESOLUTION * DECAY;

	वापस 0;
पूर्ण

अटल काष्ठा cpuidle_governor menu_governor = अणु
	.name =		"menu",
	.rating =	20,
	.enable =	menu_enable_device,
	.select =	menu_select,
	.reflect =	menu_reflect,
पूर्ण;

/**
 * init_menu - initializes the governor
 */
अटल पूर्णांक __init init_menu(व्योम)
अणु
	वापस cpuidle_रेजिस्टर_governor(&menu_governor);
पूर्ण

postcore_initcall(init_menu);
