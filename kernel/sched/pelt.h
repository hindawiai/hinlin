<शैली गुरु>
#अगर_घोषित CONFIG_SMP
#समावेश "sched-pelt.h"

पूर्णांक __update_load_avg_blocked_se(u64 now, काष्ठा sched_entity *se);
पूर्णांक __update_load_avg_se(u64 now, काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se);
पूर्णांक __update_load_avg_cfs_rq(u64 now, काष्ठा cfs_rq *cfs_rq);
पूर्णांक update_rt_rq_load_avg(u64 now, काष्ठा rq *rq, पूर्णांक running);
पूर्णांक update_dl_rq_load_avg(u64 now, काष्ठा rq *rq, पूर्णांक running);

#अगर_घोषित CONFIG_SCHED_THERMAL_PRESSURE
पूर्णांक update_thermal_load_avg(u64 now, काष्ठा rq *rq, u64 capacity);

अटल अंतरभूत u64 thermal_load_avg(काष्ठा rq *rq)
अणु
	वापस READ_ONCE(rq->avg_thermal.load_avg);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
update_thermal_load_avg(u64 now, काष्ठा rq *rq, u64 capacity)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u64 thermal_load_avg(काष्ठा rq *rq)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_SCHED_AVG_IRQ
पूर्णांक update_irq_load_avg(काष्ठा rq *rq, u64 running);
#अन्यथा
अटल अंतरभूत पूर्णांक
update_irq_load_avg(काष्ठा rq *rq, u64 running)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u32 get_pelt_भागider(काष्ठा sched_avg *avg)
अणु
	वापस LOAD_AVG_MAX - 1024 + avg->period_contrib;
पूर्ण

अटल अंतरभूत व्योम cfs_se_util_change(काष्ठा sched_avg *avg)
अणु
	अचिन्हित पूर्णांक enqueued;

	अगर (!sched_feat(UTIL_EST))
		वापस;

	/* Aव्योम store अगर the flag has been alपढ़ोy reset */
	enqueued = avg->util_est.enqueued;
	अगर (!(enqueued & UTIL_AVG_UNCHANGED))
		वापस;

	/* Reset flag to report util_avg has been updated */
	enqueued &= ~UTIL_AVG_UNCHANGED;
	WRITE_ONCE(avg->util_est.enqueued, enqueued);
पूर्ण

/*
 * The घड़ी_pelt scales the समय to reflect the effective amount of
 * computation करोne during the running delta समय but then sync back to
 * घड़ी_प्रकारask when rq is idle.
 *
 *
 * असलolute समय   | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16
 * @ max capacity  ------******---------------******---------------
 * @ half capacity ------************---------************---------
 * घड़ी pelt      | 1| 2|    3|    4| 7| 8| 9|   10|   11|14|15|16
 *
 */
अटल अंतरभूत व्योम update_rq_घड़ी_pelt(काष्ठा rq *rq, s64 delta)
अणु
	अगर (unlikely(is_idle_task(rq->curr))) अणु
		/* The rq is idle, we can sync to घड़ी_प्रकारask */
		rq->घड़ी_pelt  = rq_घड़ी_प्रकारask(rq);
		वापस;
	पूर्ण

	/*
	 * When a rq runs at a lower compute capacity, it will need
	 * more समय to करो the same amount of work than at max
	 * capacity. In order to be invariant, we scale the delta to
	 * reflect how much work has been really करोne.
	 * Running दीर्घer results in stealing idle समय that will
	 * disturb the load संकेत compared to max capacity. This
	 * stolen idle समय will be स्वतःmatically reflected when the
	 * rq will be idle and the घड़ी will be synced with
	 * rq_घड़ी_प्रकारask.
	 */

	/*
	 * Scale the elapsed समय to reflect the real amount of
	 * computation
	 */
	delta = cap_scale(delta, arch_scale_cpu_capacity(cpu_of(rq)));
	delta = cap_scale(delta, arch_scale_freq_capacity(cpu_of(rq)));

	rq->घड़ी_pelt += delta;
पूर्ण

/*
 * When rq becomes idle, we have to check अगर it has lost idle समय
 * because it was fully busy. A rq is fully used when the /Sum util_sum
 * is greater or equal to:
 * (LOAD_AVG_MAX - 1024 + rq->cfs.avg.period_contrib) << SCHED_CAPACITY_SHIFT;
 * For optimization and computing rounding purpose, we करोn't take पूर्णांकo account
 * the position in the current winकरोw (period_contrib) and we use the higher
 * bound of util_sum to decide.
 */
अटल अंतरभूत व्योम update_idle_rq_घड़ी_pelt(काष्ठा rq *rq)
अणु
	u32 भागider = ((LOAD_AVG_MAX - 1024) << SCHED_CAPACITY_SHIFT) - LOAD_AVG_MAX;
	u32 util_sum = rq->cfs.avg.util_sum;
	util_sum += rq->avg_rt.util_sum;
	util_sum += rq->avg_dl.util_sum;

	/*
	 * Reflecting stolen समय makes sense only अगर the idle
	 * phase would be present at max capacity. As soon as the
	 * utilization of a rq has reached the maximum value, it is
	 * considered as an always running rq without idle समय to
	 * steal. This potential idle समय is considered as lost in
	 * this हाल. We keep track of this lost idle समय compare to
	 * rq's घड़ी_प्रकारask.
	 */
	अगर (util_sum >= भागider)
		rq->lost_idle_समय += rq_घड़ी_प्रकारask(rq) - rq->घड़ी_pelt;
पूर्ण

अटल अंतरभूत u64 rq_घड़ी_pelt(काष्ठा rq *rq)
अणु
	lockdep_निश्चित_held(&rq->lock);
	निश्चित_घड़ी_updated(rq);

	वापस rq->घड़ी_pelt - rq->lost_idle_समय;
पूर्ण

#अगर_घोषित CONFIG_CFS_BANDWIDTH
/* rq->task_घड़ी normalized against any समय this cfs_rq has spent throttled */
अटल अंतरभूत u64 cfs_rq_घड़ी_pelt(काष्ठा cfs_rq *cfs_rq)
अणु
	अगर (unlikely(cfs_rq->throttle_count))
		वापस cfs_rq->throttled_घड़ी_प्रकारask - cfs_rq->throttled_घड़ी_प्रकारask_समय;

	वापस rq_घड़ी_pelt(rq_of(cfs_rq)) - cfs_rq->throttled_घड़ी_प्रकारask_समय;
पूर्ण
#अन्यथा
अटल अंतरभूत u64 cfs_rq_घड़ी_pelt(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस rq_घड़ी_pelt(rq_of(cfs_rq));
पूर्ण
#पूर्ण_अगर

#अन्यथा

अटल अंतरभूत पूर्णांक
update_cfs_rq_load_avg(u64 now, काष्ठा cfs_rq *cfs_rq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
update_rt_rq_load_avg(u64 now, काष्ठा rq *rq, पूर्णांक running)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
update_dl_rq_load_avg(u64 now, काष्ठा rq *rq, पूर्णांक running)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
update_thermal_load_avg(u64 now, काष्ठा rq *rq, u64 capacity)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u64 thermal_load_avg(काष्ठा rq *rq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
update_irq_load_avg(काष्ठा rq *rq, u64 running)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u64 rq_घड़ी_pelt(काष्ठा rq *rq)
अणु
	वापस rq_घड़ी_प्रकारask(rq);
पूर्ण

अटल अंतरभूत व्योम
update_rq_घड़ी_pelt(काष्ठा rq *rq, s64 delta) अणु पूर्ण

अटल अंतरभूत व्योम
update_idle_rq_घड़ी_pelt(काष्ठा rq *rq) अणु पूर्ण

#पूर्ण_अगर


