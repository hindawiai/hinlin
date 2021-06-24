<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Per Entity Load Tracking
 *
 *  Copyright (C) 2007 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 *  Interactivity improvements by Mike Galbraith
 *  (C) 2007 Mike Galbraith <efault@gmx.de>
 *
 *  Various enhancements by Dmitry Adamushko.
 *  (C) 2007 Dmitry Adamushko <dmitry.adamushko@gmail.com>
 *
 *  Group scheduling enhancements by Srivatsa Vaddagiri
 *  Copyright IBM Corporation, 2007
 *  Author: Srivatsa Vaddagiri <vatsa@linux.vnet.ibm.com>
 *
 *  Scaled math optimizations by Thomas Gleixner
 *  Copyright (C) 2007, Thomas Gleixner <tglx@linutronix.de>
 *
 *  Adaptive scheduling granularity, math enhancements by Peter Zijlstra
 *  Copyright (C) 2007 Red Hat, Inc., Peter Zijlstra
 *
 *  Move PELT related code from fair.c पूर्णांकo this pelt.c file
 *  Author: Vincent Guittot <vincent.guittot@linaro.org>
 */

#समावेश <linux/sched.h>
#समावेश "sched.h"
#समावेश "pelt.h"

/*
 * Approximate:
 *   val * y^n,    where y^32 ~= 0.5 (~1 scheduling period)
 */
अटल u64 decay_load(u64 val, u64 n)
अणु
	अचिन्हित पूर्णांक local_n;

	अगर (unlikely(n > LOAD_AVG_PERIOD * 63))
		वापस 0;

	/* after bounds checking we can collapse to 32-bit */
	local_n = n;

	/*
	 * As y^PERIOD = 1/2, we can combine
	 *    y^n = 1/2^(n/PERIOD) * y^(n%PERIOD)
	 * With a look-up table which covers y^n (n<PERIOD)
	 *
	 * To achieve स्थिरant समय decay_load.
	 */
	अगर (unlikely(local_n >= LOAD_AVG_PERIOD)) अणु
		val >>= local_n / LOAD_AVG_PERIOD;
		local_n %= LOAD_AVG_PERIOD;
	पूर्ण

	val = mul_u64_u32_shr(val, runnable_avg_yN_inv[local_n], 32);
	वापस val;
पूर्ण

अटल u32 __accumulate_pelt_segments(u64 periods, u32 d1, u32 d3)
अणु
	u32 c1, c2, c3 = d3; /* y^0 == 1 */

	/*
	 * c1 = d1 y^p
	 */
	c1 = decay_load((u64)d1, periods);

	/*
	 *            p-1
	 * c2 = 1024 \Sum y^n
	 *            n=1
	 *
	 *              inf        inf
	 *    = 1024 ( \Sum y^n - \Sum y^n - y^0 )
	 *              n=0        n=p
	 */
	c2 = LOAD_AVG_MAX - decay_load(LOAD_AVG_MAX, periods) - 1024;

	वापस c1 + c2 + c3;
पूर्ण

/*
 * Accumulate the three separate parts of the sum; d1 the reमुख्यder
 * of the last (incomplete) period, d2 the span of full periods and d3
 * the reमुख्यder of the (incomplete) current period.
 *
 *           d1          d2           d3
 *           ^           ^            ^
 *           |           |            |
 *         |<->|<----------------->|<--->|
 * ... |---x---|------| ... |------|-----x (now)
 *
 *                           p-1
 * u' = (u + d1) y^p + 1024 \Sum y^n + d3 y^0
 *                           n=1
 *
 *    = u y^p +					(Step 1)
 *
 *                     p-1
 *      d1 y^p + 1024 \Sum y^n + d3 y^0		(Step 2)
 *                     n=1
 */
अटल __always_अंतरभूत u32
accumulate_sum(u64 delta, काष्ठा sched_avg *sa,
	       अचिन्हित दीर्घ load, अचिन्हित दीर्घ runnable, पूर्णांक running)
अणु
	u32 contrib = (u32)delta; /* p == 0 -> delta < 1024 */
	u64 periods;

	delta += sa->period_contrib;
	periods = delta / 1024; /* A period is 1024us (~1ms) */

	/*
	 * Step 1: decay old *_sum अगर we crossed period boundaries.
	 */
	अगर (periods) अणु
		sa->load_sum = decay_load(sa->load_sum, periods);
		sa->runnable_sum =
			decay_load(sa->runnable_sum, periods);
		sa->util_sum = decay_load((u64)(sa->util_sum), periods);

		/*
		 * Step 2
		 */
		delta %= 1024;
		अगर (load) अणु
			/*
			 * This relies on the:
			 *
			 * अगर (!load)
			 *	runnable = running = 0;
			 *
			 * clause from ___update_load_sum(); this results in
			 * the below usage of @contrib to disappear entirely,
			 * so no poपूर्णांक in calculating it.
			 */
			contrib = __accumulate_pelt_segments(periods,
					1024 - sa->period_contrib, delta);
		पूर्ण
	पूर्ण
	sa->period_contrib = delta;

	अगर (load)
		sa->load_sum += load * contrib;
	अगर (runnable)
		sa->runnable_sum += runnable * contrib << SCHED_CAPACITY_SHIFT;
	अगर (running)
		sa->util_sum += contrib << SCHED_CAPACITY_SHIFT;

	वापस periods;
पूर्ण

/*
 * We can represent the historical contribution to runnable average as the
 * coefficients of a geometric series.  To करो this we sub-भागide our runnable
 * history पूर्णांकo segments of approximately 1ms (1024us); label the segment that
 * occurred N-ms ago p_N, with p_0 corresponding to the current period, e.g.
 *
 * [<- 1024us ->|<- 1024us ->|<- 1024us ->| ...
 *      p0            p1           p2
 *     (now)       (~1ms ago)  (~2ms ago)
 *
 * Let u_i denote the fraction of p_i that the entity was runnable.
 *
 * We then designate the fractions u_i as our co-efficients, yielding the
 * following representation of historical load:
 *   u_0 + u_1*y + u_2*y^2 + u_3*y^3 + ...
 *
 * We choose y based on the with of a reasonably scheduling period, fixing:
 *   y^32 = 0.5
 *
 * This means that the contribution to load ~32ms ago (u_32) will be weighted
 * approximately half as much as the contribution to load within the last ms
 * (u_0).
 *
 * When a period "rolls over" and we have new u_0`, multiplying the previous
 * sum again by y is sufficient to update:
 *   load_avg = u_0` + y*(u_0 + u_1*y + u_2*y^2 + ... )
 *            = u_0 + u_1*y + u_2*y^2 + ... [re-labeling u_i --> u_अणुi+1पूर्ण]
 */
अटल __always_अंतरभूत पूर्णांक
___update_load_sum(u64 now, काष्ठा sched_avg *sa,
		  अचिन्हित दीर्घ load, अचिन्हित दीर्घ runnable, पूर्णांक running)
अणु
	u64 delta;

	delta = now - sa->last_update_समय;
	/*
	 * This should only happen when समय goes backwards, which it
	 * unक्रमtunately करोes during sched घड़ी init when we swap over to TSC.
	 */
	अगर ((s64)delta < 0) अणु
		sa->last_update_समय = now;
		वापस 0;
	पूर्ण

	/*
	 * Use 1024ns as the unit of measurement since it's a reasonable
	 * approximation of 1us and fast to compute.
	 */
	delta >>= 10;
	अगर (!delta)
		वापस 0;

	sa->last_update_समय += delta << 10;

	/*
	 * running is a subset of runnable (weight) so running can't be set अगर
	 * runnable is clear. But there are some corner हालs where the current
	 * se has been alपढ़ोy dequeued but cfs_rq->curr still poपूर्णांकs to it.
	 * This means that weight will be 0 but not running क्रम a sched_entity
	 * but also क्रम a cfs_rq अगर the latter becomes idle. As an example,
	 * this happens during idle_balance() which calls
	 * update_blocked_averages().
	 *
	 * Also see the comment in accumulate_sum().
	 */
	अगर (!load)
		runnable = running = 0;

	/*
	 * Now we know we crossed measurement unit boundaries. The *_avg
	 * accrues by two steps:
	 *
	 * Step 1: accumulate *_sum since last_update_समय. If we haven't
	 * crossed period boundaries, finish.
	 */
	अगर (!accumulate_sum(delta, sa, load, runnable, running))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * When syncing *_avg with *_sum, we must take पूर्णांकo account the current
 * position in the PELT segment otherwise the reमुख्यing part of the segment
 * will be considered as idle समय whereas it's not yet elapsed and this will
 * generate unwanted oscillation in the range [1002..1024[.
 *
 * The max value of *_sum varies with the position in the समय segment and is
 * equals to :
 *
 *   LOAD_AVG_MAX*y + sa->period_contrib
 *
 * which can be simplअगरied पूर्णांकo:
 *
 *   LOAD_AVG_MAX - 1024 + sa->period_contrib
 *
 * because LOAD_AVG_MAX*y == LOAD_AVG_MAX-1024
 *
 * The same care must be taken when a sched entity is added, updated or
 * हटाओd from a cfs_rq and we need to update sched_avg. Scheduler entities
 * and the cfs rq, to which they are attached, have the same position in the
 * समय segment because they use the same घड़ी. This means that we can use
 * the period_contrib of cfs_rq when updating the sched_avg of a sched_entity
 * अगर it's more convenient.
 */
अटल __always_अंतरभूत व्योम
___update_load_avg(काष्ठा sched_avg *sa, अचिन्हित दीर्घ load)
अणु
	u32 भागider = get_pelt_भागider(sa);

	/*
	 * Step 2: update *_avg.
	 */
	sa->load_avg = भाग_u64(load * sa->load_sum, भागider);
	sa->runnable_avg = भाग_u64(sa->runnable_sum, भागider);
	WRITE_ONCE(sa->util_avg, sa->util_sum / भागider);
पूर्ण

/*
 * sched_entity:
 *
 *   task:
 *     se_weight()   = se->load.weight
 *     se_runnable() = !!on_rq
 *
 *   group: [ see update_cfs_group() ]
 *     se_weight()   = tg->weight * grq->load_avg / tg->load_avg
 *     se_runnable() = grq->h_nr_running
 *
 *   runnable_sum = se_runnable() * runnable = grq->runnable_sum
 *   runnable_avg = runnable_sum
 *
 *   load_sum := runnable
 *   load_avg = se_weight(se) * load_sum
 *
 * cfq_rq:
 *
 *   runnable_sum = \Sum se->avg.runnable_sum
 *   runnable_avg = \Sum se->avg.runnable_avg
 *
 *   load_sum = \Sum se_weight(se) * se->avg.load_sum
 *   load_avg = \Sum se->avg.load_avg
 */

पूर्णांक __update_load_avg_blocked_se(u64 now, काष्ठा sched_entity *se)
अणु
	अगर (___update_load_sum(now, &se->avg, 0, 0, 0)) अणु
		___update_load_avg(&se->avg, se_weight(se));
		trace_pelt_se_tp(se);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __update_load_avg_se(u64 now, काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	अगर (___update_load_sum(now, &se->avg, !!se->on_rq, se_runnable(se),
				cfs_rq->curr == se)) अणु

		___update_load_avg(&se->avg, se_weight(se));
		cfs_se_util_change(&se->avg);
		trace_pelt_se_tp(se);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __update_load_avg_cfs_rq(u64 now, काष्ठा cfs_rq *cfs_rq)
अणु
	अगर (___update_load_sum(now, &cfs_rq->avg,
				scale_load_करोwn(cfs_rq->load.weight),
				cfs_rq->h_nr_running,
				cfs_rq->curr != शून्य)) अणु

		___update_load_avg(&cfs_rq->avg, 1);
		trace_pelt_cfs_tp(cfs_rq);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * rt_rq:
 *
 *   util_sum = \Sum se->avg.util_sum but se->avg.util_sum is not tracked
 *   util_sum = cpu_scale * load_sum
 *   runnable_sum = util_sum
 *
 *   load_avg and runnable_avg are not supported and meaningless.
 *
 */

पूर्णांक update_rt_rq_load_avg(u64 now, काष्ठा rq *rq, पूर्णांक running)
अणु
	अगर (___update_load_sum(now, &rq->avg_rt,
				running,
				running,
				running)) अणु

		___update_load_avg(&rq->avg_rt, 1);
		trace_pelt_rt_tp(rq);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * dl_rq:
 *
 *   util_sum = \Sum se->avg.util_sum but se->avg.util_sum is not tracked
 *   util_sum = cpu_scale * load_sum
 *   runnable_sum = util_sum
 *
 *   load_avg and runnable_avg are not supported and meaningless.
 *
 */

पूर्णांक update_dl_rq_load_avg(u64 now, काष्ठा rq *rq, पूर्णांक running)
अणु
	अगर (___update_load_sum(now, &rq->avg_dl,
				running,
				running,
				running)) अणु

		___update_load_avg(&rq->avg_dl, 1);
		trace_pelt_dl_tp(rq);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SCHED_THERMAL_PRESSURE
/*
 * thermal:
 *
 *   load_sum = \Sum se->avg.load_sum but se->avg.load_sum is not tracked
 *
 *   util_avg and runnable_load_avg are not supported and meaningless.
 *
 * Unlike rt/dl utilization tracking that track समय spent by a cpu
 * running a rt/dl task through util_avg, the average thermal pressure is
 * tracked through load_avg. This is because thermal pressure संकेत is
 * समय weighted "delta" capacity unlike util_avg which is binary.
 * "delta capacity" =  actual capacity  -
 *			capped capacity a cpu due to a thermal event.
 */

पूर्णांक update_thermal_load_avg(u64 now, काष्ठा rq *rq, u64 capacity)
अणु
	अगर (___update_load_sum(now, &rq->avg_thermal,
			       capacity,
			       capacity,
			       capacity)) अणु
		___update_load_avg(&rq->avg_thermal, 1);
		trace_pelt_thermal_tp(rq);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_SCHED_AVG_IRQ
/*
 * irq:
 *
 *   util_sum = \Sum se->avg.util_sum but se->avg.util_sum is not tracked
 *   util_sum = cpu_scale * load_sum
 *   runnable_sum = util_sum
 *
 *   load_avg and runnable_avg are not supported and meaningless.
 *
 */

पूर्णांक update_irq_load_avg(काष्ठा rq *rq, u64 running)
अणु
	पूर्णांक ret = 0;

	/*
	 * We can't use घड़ी_pelt because irq समय is not accounted in
	 * घड़ी_प्रकारask. Instead we directly scale the running समय to
	 * reflect the real amount of computation
	 */
	running = cap_scale(running, arch_scale_freq_capacity(cpu_of(rq)));
	running = cap_scale(running, arch_scale_cpu_capacity(cpu_of(rq)));

	/*
	 * We know the समय that has been used by पूर्णांकerrupt since last update
	 * but we करोn't when. Let be pessimistic and assume that पूर्णांकerrupt has
	 * happened just beक्रमe the update. This is not so far from reality
	 * because पूर्णांकerrupt will most probably wake up task and trig an update
	 * of rq घड़ी during which the metric is updated.
	 * We start to decay with normal context समय and then we add the
	 * पूर्णांकerrupt context समय.
	 * We can safely हटाओ running from rq->घड़ी because
	 * rq->घड़ी += delta with delta >= running
	 */
	ret = ___update_load_sum(rq->घड़ी - running, &rq->avg_irq,
				0,
				0,
				0);
	ret += ___update_load_sum(rq->घड़ी, &rq->avg_irq,
				1,
				1,
				1);

	अगर (ret) अणु
		___update_load_avg(&rq->avg_irq, 1);
		trace_pelt_irq_tp(rq);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर
