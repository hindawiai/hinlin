<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Real-Time Scheduling Class (mapped to the SCHED_FIFO and SCHED_RR
 * policies)
 */
#समावेश "sched.h"

#समावेश "pelt.h"

पूर्णांक sched_rr_बारlice = RR_TIMESLICE;
पूर्णांक sysctl_sched_rr_बारlice = (MSEC_PER_SEC / HZ) * RR_TIMESLICE;
/* More than 4 hours अगर BW_SHIFT equals 20. */
अटल स्थिर u64 max_rt_runसमय = MAX_BW;

अटल पूर्णांक करो_sched_rt_period_समयr(काष्ठा rt_bandwidth *rt_b, पूर्णांक overrun);

काष्ठा rt_bandwidth def_rt_bandwidth;

अटल क्रमागत hrसमयr_restart sched_rt_period_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा rt_bandwidth *rt_b =
		container_of(समयr, काष्ठा rt_bandwidth, rt_period_समयr);
	पूर्णांक idle = 0;
	पूर्णांक overrun;

	raw_spin_lock(&rt_b->rt_runसमय_lock);
	क्रम (;;) अणु
		overrun = hrसमयr_क्रमward_now(समयr, rt_b->rt_period);
		अगर (!overrun)
			अवरोध;

		raw_spin_unlock(&rt_b->rt_runसमय_lock);
		idle = करो_sched_rt_period_समयr(rt_b, overrun);
		raw_spin_lock(&rt_b->rt_runसमय_lock);
	पूर्ण
	अगर (idle)
		rt_b->rt_period_active = 0;
	raw_spin_unlock(&rt_b->rt_runसमय_lock);

	वापस idle ? HRTIMER_NORESTART : HRTIMER_RESTART;
पूर्ण

व्योम init_rt_bandwidth(काष्ठा rt_bandwidth *rt_b, u64 period, u64 runसमय)
अणु
	rt_b->rt_period = ns_to_kसमय(period);
	rt_b->rt_runसमय = runसमय;

	raw_spin_lock_init(&rt_b->rt_runसमय_lock);

	hrसमयr_init(&rt_b->rt_period_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL_HARD);
	rt_b->rt_period_समयr.function = sched_rt_period_समयr;
पूर्ण

अटल व्योम start_rt_bandwidth(काष्ठा rt_bandwidth *rt_b)
अणु
	अगर (!rt_bandwidth_enabled() || rt_b->rt_runसमय == RUNTIME_INF)
		वापस;

	raw_spin_lock(&rt_b->rt_runसमय_lock);
	अगर (!rt_b->rt_period_active) अणु
		rt_b->rt_period_active = 1;
		/*
		 * SCHED_DEADLINE updates the bandwidth, as a run away
		 * RT task with a DL task could hog a CPU. But DL करोes
		 * not reset the period. If a deadline task was running
		 * without an RT task running, it can cause RT tasks to
		 * throttle when they start up. Kick the समयr right away
		 * to update the period.
		 */
		hrसमयr_क्रमward_now(&rt_b->rt_period_समयr, ns_to_kसमय(0));
		hrसमयr_start_expires(&rt_b->rt_period_समयr,
				      HRTIMER_MODE_ABS_PINNED_HARD);
	पूर्ण
	raw_spin_unlock(&rt_b->rt_runसमय_lock);
पूर्ण

व्योम init_rt_rq(काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा rt_prio_array *array;
	पूर्णांक i;

	array = &rt_rq->active;
	क्रम (i = 0; i < MAX_RT_PRIO; i++) अणु
		INIT_LIST_HEAD(array->queue + i);
		__clear_bit(i, array->biपंचांगap);
	पूर्ण
	/* delimiter क्रम bitsearch: */
	__set_bit(MAX_RT_PRIO, array->biपंचांगap);

#अगर defined CONFIG_SMP
	rt_rq->highest_prio.curr = MAX_RT_PRIO-1;
	rt_rq->highest_prio.next = MAX_RT_PRIO-1;
	rt_rq->rt_nr_migratory = 0;
	rt_rq->overloaded = 0;
	plist_head_init(&rt_rq->pushable_tasks);
#पूर्ण_अगर /* CONFIG_SMP */
	/* We start is dequeued state, because no RT tasks are queued */
	rt_rq->rt_queued = 0;

	rt_rq->rt_समय = 0;
	rt_rq->rt_throttled = 0;
	rt_rq->rt_runसमय = 0;
	raw_spin_lock_init(&rt_rq->rt_runसमय_lock);
पूर्ण

#अगर_घोषित CONFIG_RT_GROUP_SCHED
अटल व्योम destroy_rt_bandwidth(काष्ठा rt_bandwidth *rt_b)
अणु
	hrसमयr_cancel(&rt_b->rt_period_समयr);
पूर्ण

#घोषणा rt_entity_is_task(rt_se) (!(rt_se)->my_q)

अटल अंतरभूत काष्ठा task_काष्ठा *rt_task_of(काष्ठा sched_rt_entity *rt_se)
अणु
#अगर_घोषित CONFIG_SCHED_DEBUG
	WARN_ON_ONCE(!rt_entity_is_task(rt_se));
#पूर्ण_अगर
	वापस container_of(rt_se, काष्ठा task_काष्ठा, rt);
पूर्ण

अटल अंतरभूत काष्ठा rq *rq_of_rt_rq(काष्ठा rt_rq *rt_rq)
अणु
	वापस rt_rq->rq;
पूर्ण

अटल अंतरभूत काष्ठा rt_rq *rt_rq_of_se(काष्ठा sched_rt_entity *rt_se)
अणु
	वापस rt_se->rt_rq;
पूर्ण

अटल अंतरभूत काष्ठा rq *rq_of_rt_se(काष्ठा sched_rt_entity *rt_se)
अणु
	काष्ठा rt_rq *rt_rq = rt_se->rt_rq;

	वापस rt_rq->rq;
पूर्ण

व्योम मुक्त_rt_sched_group(काष्ठा task_group *tg)
अणु
	पूर्णांक i;

	अगर (tg->rt_se)
		destroy_rt_bandwidth(&tg->rt_bandwidth);

	क्रम_each_possible_cpu(i) अणु
		अगर (tg->rt_rq)
			kमुक्त(tg->rt_rq[i]);
		अगर (tg->rt_se)
			kमुक्त(tg->rt_se[i]);
	पूर्ण

	kमुक्त(tg->rt_rq);
	kमुक्त(tg->rt_se);
पूर्ण

व्योम init_tg_rt_entry(काष्ठा task_group *tg, काष्ठा rt_rq *rt_rq,
		काष्ठा sched_rt_entity *rt_se, पूर्णांक cpu,
		काष्ठा sched_rt_entity *parent)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	rt_rq->highest_prio.curr = MAX_RT_PRIO-1;
	rt_rq->rt_nr_boosted = 0;
	rt_rq->rq = rq;
	rt_rq->tg = tg;

	tg->rt_rq[cpu] = rt_rq;
	tg->rt_se[cpu] = rt_se;

	अगर (!rt_se)
		वापस;

	अगर (!parent)
		rt_se->rt_rq = &rq->rt;
	अन्यथा
		rt_se->rt_rq = parent->my_q;

	rt_se->my_q = rt_rq;
	rt_se->parent = parent;
	INIT_LIST_HEAD(&rt_se->run_list);
पूर्ण

पूर्णांक alloc_rt_sched_group(काष्ठा task_group *tg, काष्ठा task_group *parent)
अणु
	काष्ठा rt_rq *rt_rq;
	काष्ठा sched_rt_entity *rt_se;
	पूर्णांक i;

	tg->rt_rq = kसुस्मृति(nr_cpu_ids, माप(rt_rq), GFP_KERNEL);
	अगर (!tg->rt_rq)
		जाओ err;
	tg->rt_se = kसुस्मृति(nr_cpu_ids, माप(rt_se), GFP_KERNEL);
	अगर (!tg->rt_se)
		जाओ err;

	init_rt_bandwidth(&tg->rt_bandwidth,
			kसमय_प्रकारo_ns(def_rt_bandwidth.rt_period), 0);

	क्रम_each_possible_cpu(i) अणु
		rt_rq = kzalloc_node(माप(काष्ठा rt_rq),
				     GFP_KERNEL, cpu_to_node(i));
		अगर (!rt_rq)
			जाओ err;

		rt_se = kzalloc_node(माप(काष्ठा sched_rt_entity),
				     GFP_KERNEL, cpu_to_node(i));
		अगर (!rt_se)
			जाओ err_मुक्त_rq;

		init_rt_rq(rt_rq);
		rt_rq->rt_runसमय = tg->rt_bandwidth.rt_runसमय;
		init_tg_rt_entry(tg, rt_rq, rt_se, i, parent->rt_se[i]);
	पूर्ण

	वापस 1;

err_मुक्त_rq:
	kमुक्त(rt_rq);
err:
	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_RT_GROUP_SCHED */

#घोषणा rt_entity_is_task(rt_se) (1)

अटल अंतरभूत काष्ठा task_काष्ठा *rt_task_of(काष्ठा sched_rt_entity *rt_se)
अणु
	वापस container_of(rt_se, काष्ठा task_काष्ठा, rt);
पूर्ण

अटल अंतरभूत काष्ठा rq *rq_of_rt_rq(काष्ठा rt_rq *rt_rq)
अणु
	वापस container_of(rt_rq, काष्ठा rq, rt);
पूर्ण

अटल अंतरभूत काष्ठा rq *rq_of_rt_se(काष्ठा sched_rt_entity *rt_se)
अणु
	काष्ठा task_काष्ठा *p = rt_task_of(rt_se);

	वापस task_rq(p);
पूर्ण

अटल अंतरभूत काष्ठा rt_rq *rt_rq_of_se(काष्ठा sched_rt_entity *rt_se)
अणु
	काष्ठा rq *rq = rq_of_rt_se(rt_se);

	वापस &rq->rt;
पूर्ण

व्योम मुक्त_rt_sched_group(काष्ठा task_group *tg) अणु पूर्ण

पूर्णांक alloc_rt_sched_group(काष्ठा task_group *tg, काष्ठा task_group *parent)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_RT_GROUP_SCHED */

#अगर_घोषित CONFIG_SMP

अटल व्योम pull_rt_task(काष्ठा rq *this_rq);

अटल अंतरभूत bool need_pull_rt_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev)
अणु
	/* Try to pull RT tasks here अगर we lower this rq's prio */
	वापस rq->online && rq->rt.highest_prio.curr > prev->prio;
पूर्ण

अटल अंतरभूत पूर्णांक rt_overloaded(काष्ठा rq *rq)
अणु
	वापस atomic_पढ़ो(&rq->rd->rto_count);
पूर्ण

अटल अंतरभूत व्योम rt_set_overload(काष्ठा rq *rq)
अणु
	अगर (!rq->online)
		वापस;

	cpumask_set_cpu(rq->cpu, rq->rd->rto_mask);
	/*
	 * Make sure the mask is visible beक्रमe we set
	 * the overload count. That is checked to determine
	 * अगर we should look at the mask. It would be a shame
	 * अगर we looked at the mask, but the mask was not
	 * updated yet.
	 *
	 * Matched by the barrier in pull_rt_task().
	 */
	smp_wmb();
	atomic_inc(&rq->rd->rto_count);
पूर्ण

अटल अंतरभूत व्योम rt_clear_overload(काष्ठा rq *rq)
अणु
	अगर (!rq->online)
		वापस;

	/* the order here really करोesn't matter */
	atomic_dec(&rq->rd->rto_count);
	cpumask_clear_cpu(rq->cpu, rq->rd->rto_mask);
पूर्ण

अटल व्योम update_rt_migration(काष्ठा rt_rq *rt_rq)
अणु
	अगर (rt_rq->rt_nr_migratory && rt_rq->rt_nr_total > 1) अणु
		अगर (!rt_rq->overloaded) अणु
			rt_set_overload(rq_of_rt_rq(rt_rq));
			rt_rq->overloaded = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (rt_rq->overloaded) अणु
		rt_clear_overload(rq_of_rt_rq(rt_rq));
		rt_rq->overloaded = 0;
	पूर्ण
पूर्ण

अटल व्योम inc_rt_migration(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा task_काष्ठा *p;

	अगर (!rt_entity_is_task(rt_se))
		वापस;

	p = rt_task_of(rt_se);
	rt_rq = &rq_of_rt_rq(rt_rq)->rt;

	rt_rq->rt_nr_total++;
	अगर (p->nr_cpus_allowed > 1)
		rt_rq->rt_nr_migratory++;

	update_rt_migration(rt_rq);
पूर्ण

अटल व्योम dec_rt_migration(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा task_काष्ठा *p;

	अगर (!rt_entity_is_task(rt_se))
		वापस;

	p = rt_task_of(rt_se);
	rt_rq = &rq_of_rt_rq(rt_rq)->rt;

	rt_rq->rt_nr_total--;
	अगर (p->nr_cpus_allowed > 1)
		rt_rq->rt_nr_migratory--;

	update_rt_migration(rt_rq);
पूर्ण

अटल अंतरभूत पूर्णांक has_pushable_tasks(काष्ठा rq *rq)
अणु
	वापस !plist_head_empty(&rq->rt.pushable_tasks);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा callback_head, rt_push_head);
अटल DEFINE_PER_CPU(काष्ठा callback_head, rt_pull_head);

अटल व्योम push_rt_tasks(काष्ठा rq *);
अटल व्योम pull_rt_task(काष्ठा rq *);

अटल अंतरभूत व्योम rt_queue_push_tasks(काष्ठा rq *rq)
अणु
	अगर (!has_pushable_tasks(rq))
		वापस;

	queue_balance_callback(rq, &per_cpu(rt_push_head, rq->cpu), push_rt_tasks);
पूर्ण

अटल अंतरभूत व्योम rt_queue_pull_task(काष्ठा rq *rq)
अणु
	queue_balance_callback(rq, &per_cpu(rt_pull_head, rq->cpu), pull_rt_task);
पूर्ण

अटल व्योम enqueue_pushable_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	plist_del(&p->pushable_tasks, &rq->rt.pushable_tasks);
	plist_node_init(&p->pushable_tasks, p->prio);
	plist_add(&p->pushable_tasks, &rq->rt.pushable_tasks);

	/* Update the highest prio pushable task */
	अगर (p->prio < rq->rt.highest_prio.next)
		rq->rt.highest_prio.next = p->prio;
पूर्ण

अटल व्योम dequeue_pushable_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	plist_del(&p->pushable_tasks, &rq->rt.pushable_tasks);

	/* Update the new highest prio pushable task */
	अगर (has_pushable_tasks(rq)) अणु
		p = plist_first_entry(&rq->rt.pushable_tasks,
				      काष्ठा task_काष्ठा, pushable_tasks);
		rq->rt.highest_prio.next = p->prio;
	पूर्ण अन्यथा अणु
		rq->rt.highest_prio.next = MAX_RT_PRIO-1;
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम enqueue_pushable_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत व्योम dequeue_pushable_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत
व्योम inc_rt_migration(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
पूर्ण

अटल अंतरभूत
व्योम dec_rt_migration(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
पूर्ण

अटल अंतरभूत bool need_pull_rt_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम pull_rt_task(काष्ठा rq *this_rq)
अणु
पूर्ण

अटल अंतरभूत व्योम rt_queue_push_tasks(काष्ठा rq *rq)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम enqueue_top_rt_rq(काष्ठा rt_rq *rt_rq);
अटल व्योम dequeue_top_rt_rq(काष्ठा rt_rq *rt_rq);

अटल अंतरभूत पूर्णांक on_rt_rq(काष्ठा sched_rt_entity *rt_se)
अणु
	वापस rt_se->on_rq;
पूर्ण

#अगर_घोषित CONFIG_UCLAMP_TASK
/*
 * Verअगरy the fitness of task @p to run on @cpu taking पूर्णांकo account the uclamp
 * settings.
 *
 * This check is only important क्रम heterogeneous प्रणालीs where uclamp_min value
 * is higher than the capacity of a @cpu. For non-heterogeneous प्रणाली this
 * function will always वापस true.
 *
 * The function will वापस true अगर the capacity of the @cpu is >= the
 * uclamp_min and false otherwise.
 *
 * Note that uclamp_min will be clamped to uclamp_max अगर uclamp_min
 * > uclamp_max.
 */
अटल अंतरभूत bool rt_task_fits_capacity(काष्ठा task_काष्ठा *p, पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक min_cap;
	अचिन्हित पूर्णांक max_cap;
	अचिन्हित पूर्णांक cpu_cap;

	/* Only heterogeneous प्रणालीs can benefit from this check */
	अगर (!अटल_branch_unlikely(&sched_asym_cpucapacity))
		वापस true;

	min_cap = uclamp_eff_value(p, UCLAMP_MIN);
	max_cap = uclamp_eff_value(p, UCLAMP_MAX);

	cpu_cap = capacity_orig_of(cpu);

	वापस cpu_cap >= min(min_cap, max_cap);
पूर्ण
#अन्यथा
अटल अंतरभूत bool rt_task_fits_capacity(काष्ठा task_काष्ठा *p, पूर्णांक cpu)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_RT_GROUP_SCHED

अटल अंतरभूत u64 sched_rt_runसमय(काष्ठा rt_rq *rt_rq)
अणु
	अगर (!rt_rq->tg)
		वापस RUNTIME_INF;

	वापस rt_rq->rt_runसमय;
पूर्ण

अटल अंतरभूत u64 sched_rt_period(काष्ठा rt_rq *rt_rq)
अणु
	वापस kसमय_प्रकारo_ns(rt_rq->tg->rt_bandwidth.rt_period);
पूर्ण

प्रकार काष्ठा task_group *rt_rq_iter_t;

अटल अंतरभूत काष्ठा task_group *next_task_group(काष्ठा task_group *tg)
अणु
	करो अणु
		tg = list_entry_rcu(tg->list.next,
			typeof(काष्ठा task_group), list);
	पूर्ण जबतक (&tg->list != &task_groups && task_group_is_स्वतःgroup(tg));

	अगर (&tg->list == &task_groups)
		tg = शून्य;

	वापस tg;
पूर्ण

#घोषणा क्रम_each_rt_rq(rt_rq, iter, rq)					\
	क्रम (iter = container_of(&task_groups, typeof(*iter), list);	\
		(iter = next_task_group(iter)) &&			\
		(rt_rq = iter->rt_rq[cpu_of(rq)]);)

#घोषणा क्रम_each_sched_rt_entity(rt_se) \
	क्रम (; rt_se; rt_se = rt_se->parent)

अटल अंतरभूत काष्ठा rt_rq *group_rt_rq(काष्ठा sched_rt_entity *rt_se)
अणु
	वापस rt_se->my_q;
पूर्ण

अटल व्योम enqueue_rt_entity(काष्ठा sched_rt_entity *rt_se, अचिन्हित पूर्णांक flags);
अटल व्योम dequeue_rt_entity(काष्ठा sched_rt_entity *rt_se, अचिन्हित पूर्णांक flags);

अटल व्योम sched_rt_rq_enqueue(काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा task_काष्ठा *curr = rq_of_rt_rq(rt_rq)->curr;
	काष्ठा rq *rq = rq_of_rt_rq(rt_rq);
	काष्ठा sched_rt_entity *rt_se;

	पूर्णांक cpu = cpu_of(rq);

	rt_se = rt_rq->tg->rt_se[cpu];

	अगर (rt_rq->rt_nr_running) अणु
		अगर (!rt_se)
			enqueue_top_rt_rq(rt_rq);
		अन्यथा अगर (!on_rt_rq(rt_se))
			enqueue_rt_entity(rt_se, 0);

		अगर (rt_rq->highest_prio.curr < curr->prio)
			resched_curr(rq);
	पूर्ण
पूर्ण

अटल व्योम sched_rt_rq_dequeue(काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा sched_rt_entity *rt_se;
	पूर्णांक cpu = cpu_of(rq_of_rt_rq(rt_rq));

	rt_se = rt_rq->tg->rt_se[cpu];

	अगर (!rt_se) अणु
		dequeue_top_rt_rq(rt_rq);
		/* Kick cpufreq (see the comment in kernel/sched/sched.h). */
		cpufreq_update_util(rq_of_rt_rq(rt_rq), 0);
	पूर्ण
	अन्यथा अगर (on_rt_rq(rt_se))
		dequeue_rt_entity(rt_se, 0);
पूर्ण

अटल अंतरभूत पूर्णांक rt_rq_throttled(काष्ठा rt_rq *rt_rq)
अणु
	वापस rt_rq->rt_throttled && !rt_rq->rt_nr_boosted;
पूर्ण

अटल पूर्णांक rt_se_boosted(काष्ठा sched_rt_entity *rt_se)
अणु
	काष्ठा rt_rq *rt_rq = group_rt_rq(rt_se);
	काष्ठा task_काष्ठा *p;

	अगर (rt_rq)
		वापस !!rt_rq->rt_nr_boosted;

	p = rt_task_of(rt_se);
	वापस p->prio != p->normal_prio;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत स्थिर काष्ठा cpumask *sched_rt_period_mask(व्योम)
अणु
	वापस this_rq()->rd->span;
पूर्ण
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा cpumask *sched_rt_period_mask(व्योम)
अणु
	वापस cpu_online_mask;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत
काष्ठा rt_rq *sched_rt_period_rt_rq(काष्ठा rt_bandwidth *rt_b, पूर्णांक cpu)
अणु
	वापस container_of(rt_b, काष्ठा task_group, rt_bandwidth)->rt_rq[cpu];
पूर्ण

अटल अंतरभूत काष्ठा rt_bandwidth *sched_rt_bandwidth(काष्ठा rt_rq *rt_rq)
अणु
	वापस &rt_rq->tg->rt_bandwidth;
पूर्ण

#अन्यथा /* !CONFIG_RT_GROUP_SCHED */

अटल अंतरभूत u64 sched_rt_runसमय(काष्ठा rt_rq *rt_rq)
अणु
	वापस rt_rq->rt_runसमय;
पूर्ण

अटल अंतरभूत u64 sched_rt_period(काष्ठा rt_rq *rt_rq)
अणु
	वापस kसमय_प्रकारo_ns(def_rt_bandwidth.rt_period);
पूर्ण

प्रकार काष्ठा rt_rq *rt_rq_iter_t;

#घोषणा क्रम_each_rt_rq(rt_rq, iter, rq) \
	क्रम ((व्योम) iter, rt_rq = &rq->rt; rt_rq; rt_rq = शून्य)

#घोषणा क्रम_each_sched_rt_entity(rt_se) \
	क्रम (; rt_se; rt_se = शून्य)

अटल अंतरभूत काष्ठा rt_rq *group_rt_rq(काष्ठा sched_rt_entity *rt_se)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम sched_rt_rq_enqueue(काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा rq *rq = rq_of_rt_rq(rt_rq);

	अगर (!rt_rq->rt_nr_running)
		वापस;

	enqueue_top_rt_rq(rt_rq);
	resched_curr(rq);
पूर्ण

अटल अंतरभूत व्योम sched_rt_rq_dequeue(काष्ठा rt_rq *rt_rq)
अणु
	dequeue_top_rt_rq(rt_rq);
पूर्ण

अटल अंतरभूत पूर्णांक rt_rq_throttled(काष्ठा rt_rq *rt_rq)
अणु
	वापस rt_rq->rt_throttled;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cpumask *sched_rt_period_mask(व्योम)
अणु
	वापस cpu_online_mask;
पूर्ण

अटल अंतरभूत
काष्ठा rt_rq *sched_rt_period_rt_rq(काष्ठा rt_bandwidth *rt_b, पूर्णांक cpu)
अणु
	वापस &cpu_rq(cpu)->rt;
पूर्ण

अटल अंतरभूत काष्ठा rt_bandwidth *sched_rt_bandwidth(काष्ठा rt_rq *rt_rq)
अणु
	वापस &def_rt_bandwidth;
पूर्ण

#पूर्ण_अगर /* CONFIG_RT_GROUP_SCHED */

bool sched_rt_bandwidth_account(काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा rt_bandwidth *rt_b = sched_rt_bandwidth(rt_rq);

	वापस (hrसमयr_active(&rt_b->rt_period_समयr) ||
		rt_rq->rt_समय < rt_b->rt_runसमय);
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * We ran out of runसमय, see अगर we can borrow some from our neighbours.
 */
अटल व्योम करो_balance_runसमय(काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा rt_bandwidth *rt_b = sched_rt_bandwidth(rt_rq);
	काष्ठा root_करोमुख्य *rd = rq_of_rt_rq(rt_rq)->rd;
	पूर्णांक i, weight;
	u64 rt_period;

	weight = cpumask_weight(rd->span);

	raw_spin_lock(&rt_b->rt_runसमय_lock);
	rt_period = kसमय_प्रकारo_ns(rt_b->rt_period);
	क्रम_each_cpu(i, rd->span) अणु
		काष्ठा rt_rq *iter = sched_rt_period_rt_rq(rt_b, i);
		s64 dअगरf;

		अगर (iter == rt_rq)
			जारी;

		raw_spin_lock(&iter->rt_runसमय_lock);
		/*
		 * Either all rqs have inf runसमय and there's nothing to steal
		 * or __disable_runसमय() below sets a specअगरic rq to inf to
		 * indicate its been disabled and disallow stealing.
		 */
		अगर (iter->rt_runसमय == RUNTIME_INF)
			जाओ next;

		/*
		 * From runqueues with spare समय, take 1/n part of their
		 * spare समय, but no more than our period.
		 */
		dअगरf = iter->rt_runसमय - iter->rt_समय;
		अगर (dअगरf > 0) अणु
			dअगरf = भाग_u64((u64)dअगरf, weight);
			अगर (rt_rq->rt_runसमय + dअगरf > rt_period)
				dअगरf = rt_period - rt_rq->rt_runसमय;
			iter->rt_runसमय -= dअगरf;
			rt_rq->rt_runसमय += dअगरf;
			अगर (rt_rq->rt_runसमय == rt_period) अणु
				raw_spin_unlock(&iter->rt_runसमय_lock);
				अवरोध;
			पूर्ण
		पूर्ण
next:
		raw_spin_unlock(&iter->rt_runसमय_lock);
	पूर्ण
	raw_spin_unlock(&rt_b->rt_runसमय_lock);
पूर्ण

/*
 * Ensure this RQ takes back all the runसमय it lend to its neighbours.
 */
अटल व्योम __disable_runसमय(काष्ठा rq *rq)
अणु
	काष्ठा root_करोमुख्य *rd = rq->rd;
	rt_rq_iter_t iter;
	काष्ठा rt_rq *rt_rq;

	अगर (unlikely(!scheduler_running))
		वापस;

	क्रम_each_rt_rq(rt_rq, iter, rq) अणु
		काष्ठा rt_bandwidth *rt_b = sched_rt_bandwidth(rt_rq);
		s64 want;
		पूर्णांक i;

		raw_spin_lock(&rt_b->rt_runसमय_lock);
		raw_spin_lock(&rt_rq->rt_runसमय_lock);
		/*
		 * Either we're all inf and nobody needs to borrow, or we're
		 * alपढ़ोy disabled and thus have nothing to करो, or we have
		 * exactly the right amount of runसमय to take out.
		 */
		अगर (rt_rq->rt_runसमय == RUNTIME_INF ||
				rt_rq->rt_runसमय == rt_b->rt_runसमय)
			जाओ balanced;
		raw_spin_unlock(&rt_rq->rt_runसमय_lock);

		/*
		 * Calculate the dअगरference between what we started out with
		 * and what we current have, that's the amount of runसमय
		 * we lend and now have to reclaim.
		 */
		want = rt_b->rt_runसमय - rt_rq->rt_runसमय;

		/*
		 * Greedy reclaim, take back as much as we can.
		 */
		क्रम_each_cpu(i, rd->span) अणु
			काष्ठा rt_rq *iter = sched_rt_period_rt_rq(rt_b, i);
			s64 dअगरf;

			/*
			 * Can't reclaim from ourselves or disabled runqueues.
			 */
			अगर (iter == rt_rq || iter->rt_runसमय == RUNTIME_INF)
				जारी;

			raw_spin_lock(&iter->rt_runसमय_lock);
			अगर (want > 0) अणु
				dअगरf = min_t(s64, iter->rt_runसमय, want);
				iter->rt_runसमय -= dअगरf;
				want -= dअगरf;
			पूर्ण अन्यथा अणु
				iter->rt_runसमय -= want;
				want -= want;
			पूर्ण
			raw_spin_unlock(&iter->rt_runसमय_lock);

			अगर (!want)
				अवरोध;
		पूर्ण

		raw_spin_lock(&rt_rq->rt_runसमय_lock);
		/*
		 * We cannot be left wanting - that would mean some runसमय
		 * leaked out of the प्रणाली.
		 */
		BUG_ON(want);
balanced:
		/*
		 * Disable all the borrow logic by pretending we have inf
		 * runसमय - in which हाल borrowing करोesn't make sense.
		 */
		rt_rq->rt_runसमय = RUNTIME_INF;
		rt_rq->rt_throttled = 0;
		raw_spin_unlock(&rt_rq->rt_runसमय_lock);
		raw_spin_unlock(&rt_b->rt_runसमय_lock);

		/* Make rt_rq available क्रम pick_next_task() */
		sched_rt_rq_enqueue(rt_rq);
	पूर्ण
पूर्ण

अटल व्योम __enable_runसमय(काष्ठा rq *rq)
अणु
	rt_rq_iter_t iter;
	काष्ठा rt_rq *rt_rq;

	अगर (unlikely(!scheduler_running))
		वापस;

	/*
	 * Reset each runqueue's bandwidth settings
	 */
	क्रम_each_rt_rq(rt_rq, iter, rq) अणु
		काष्ठा rt_bandwidth *rt_b = sched_rt_bandwidth(rt_rq);

		raw_spin_lock(&rt_b->rt_runसमय_lock);
		raw_spin_lock(&rt_rq->rt_runसमय_lock);
		rt_rq->rt_runसमय = rt_b->rt_runसमय;
		rt_rq->rt_समय = 0;
		rt_rq->rt_throttled = 0;
		raw_spin_unlock(&rt_rq->rt_runसमय_lock);
		raw_spin_unlock(&rt_b->rt_runसमय_lock);
	पूर्ण
पूर्ण

अटल व्योम balance_runसमय(काष्ठा rt_rq *rt_rq)
अणु
	अगर (!sched_feat(RT_RUNTIME_SHARE))
		वापस;

	अगर (rt_rq->rt_समय > rt_rq->rt_runसमय) अणु
		raw_spin_unlock(&rt_rq->rt_runसमय_lock);
		करो_balance_runसमय(rt_rq);
		raw_spin_lock(&rt_rq->rt_runसमय_lock);
	पूर्ण
पूर्ण
#अन्यथा /* !CONFIG_SMP */
अटल अंतरभूत व्योम balance_runसमय(काष्ठा rt_rq *rt_rq) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल पूर्णांक करो_sched_rt_period_समयr(काष्ठा rt_bandwidth *rt_b, पूर्णांक overrun)
अणु
	पूर्णांक i, idle = 1, throttled = 0;
	स्थिर काष्ठा cpumask *span;

	span = sched_rt_period_mask();
#अगर_घोषित CONFIG_RT_GROUP_SCHED
	/*
	 * FIXME: isolated CPUs should really leave the root task group,
	 * whether they are isolcpus or were isolated via cpusets, lest
	 * the समयr run on a CPU which करोes not service all runqueues,
	 * potentially leaving other CPUs indefinitely throttled.  If
	 * isolation is really required, the user will turn the throttle
	 * off to समाप्त the perturbations it causes anyway.  Meanजबतक,
	 * this मुख्यtains functionality क्रम boot and/or troubleshooting.
	 */
	अगर (rt_b == &root_task_group.rt_bandwidth)
		span = cpu_online_mask;
#पूर्ण_अगर
	क्रम_each_cpu(i, span) अणु
		पूर्णांक enqueue = 0;
		काष्ठा rt_rq *rt_rq = sched_rt_period_rt_rq(rt_b, i);
		काष्ठा rq *rq = rq_of_rt_rq(rt_rq);
		पूर्णांक skip;

		/*
		 * When span == cpu_online_mask, taking each rq->lock
		 * can be समय-consuming. Try to aव्योम it when possible.
		 */
		raw_spin_lock(&rt_rq->rt_runसमय_lock);
		अगर (!sched_feat(RT_RUNTIME_SHARE) && rt_rq->rt_runसमय != RUNTIME_INF)
			rt_rq->rt_runसमय = rt_b->rt_runसमय;
		skip = !rt_rq->rt_समय && !rt_rq->rt_nr_running;
		raw_spin_unlock(&rt_rq->rt_runसमय_lock);
		अगर (skip)
			जारी;

		raw_spin_lock(&rq->lock);
		update_rq_घड़ी(rq);

		अगर (rt_rq->rt_समय) अणु
			u64 runसमय;

			raw_spin_lock(&rt_rq->rt_runसमय_lock);
			अगर (rt_rq->rt_throttled)
				balance_runसमय(rt_rq);
			runसमय = rt_rq->rt_runसमय;
			rt_rq->rt_समय -= min(rt_rq->rt_समय, overrun*runसमय);
			अगर (rt_rq->rt_throttled && rt_rq->rt_समय < runसमय) अणु
				rt_rq->rt_throttled = 0;
				enqueue = 1;

				/*
				 * When we're idle and a woken (rt) task is
				 * throttled check_preempt_curr() will set
				 * skip_update and the समय between the wakeup
				 * and this unthrottle will get accounted as
				 * 'runtime'.
				 */
				अगर (rt_rq->rt_nr_running && rq->curr == rq->idle)
					rq_घड़ी_cancel_skipupdate(rq);
			पूर्ण
			अगर (rt_rq->rt_समय || rt_rq->rt_nr_running)
				idle = 0;
			raw_spin_unlock(&rt_rq->rt_runसमय_lock);
		पूर्ण अन्यथा अगर (rt_rq->rt_nr_running) अणु
			idle = 0;
			अगर (!rt_rq_throttled(rt_rq))
				enqueue = 1;
		पूर्ण
		अगर (rt_rq->rt_throttled)
			throttled = 1;

		अगर (enqueue)
			sched_rt_rq_enqueue(rt_rq);
		raw_spin_unlock(&rq->lock);
	पूर्ण

	अगर (!throttled && (!rt_bandwidth_enabled() || rt_b->rt_runसमय == RUNTIME_INF))
		वापस 1;

	वापस idle;
पूर्ण

अटल अंतरभूत पूर्णांक rt_se_prio(काष्ठा sched_rt_entity *rt_se)
अणु
#अगर_घोषित CONFIG_RT_GROUP_SCHED
	काष्ठा rt_rq *rt_rq = group_rt_rq(rt_se);

	अगर (rt_rq)
		वापस rt_rq->highest_prio.curr;
#पूर्ण_अगर

	वापस rt_task_of(rt_se)->prio;
पूर्ण

अटल पूर्णांक sched_rt_runसमय_exceeded(काष्ठा rt_rq *rt_rq)
अणु
	u64 runसमय = sched_rt_runसमय(rt_rq);

	अगर (rt_rq->rt_throttled)
		वापस rt_rq_throttled(rt_rq);

	अगर (runसमय >= sched_rt_period(rt_rq))
		वापस 0;

	balance_runसमय(rt_rq);
	runसमय = sched_rt_runसमय(rt_rq);
	अगर (runसमय == RUNTIME_INF)
		वापस 0;

	अगर (rt_rq->rt_समय > runसमय) अणु
		काष्ठा rt_bandwidth *rt_b = sched_rt_bandwidth(rt_rq);

		/*
		 * Don't actually throttle groups that have no runसमय asचिन्हित
		 * but accrue some समय due to boosting.
		 */
		अगर (likely(rt_b->rt_runसमय)) अणु
			rt_rq->rt_throttled = 1;
			prपूर्णांकk_deferred_once("sched: RT throttling activated\n");
		पूर्ण अन्यथा अणु
			/*
			 * In हाल we did anyway, make it go away,
			 * replenishment is a joke, since it will replenish us
			 * with exactly 0 ns.
			 */
			rt_rq->rt_समय = 0;
		पूर्ण

		अगर (rt_rq_throttled(rt_rq)) अणु
			sched_rt_rq_dequeue(rt_rq);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Update the current task's runसमय statistics. Skip current tasks that
 * are not in our scheduling class.
 */
अटल व्योम update_curr_rt(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *curr = rq->curr;
	काष्ठा sched_rt_entity *rt_se = &curr->rt;
	u64 delta_exec;
	u64 now;

	अगर (curr->sched_class != &rt_sched_class)
		वापस;

	now = rq_घड़ी_प्रकारask(rq);
	delta_exec = now - curr->se.exec_start;
	अगर (unlikely((s64)delta_exec <= 0))
		वापस;

	schedstat_set(curr->se.statistics.exec_max,
		      max(curr->se.statistics.exec_max, delta_exec));

	curr->se.sum_exec_runसमय += delta_exec;
	account_group_exec_runसमय(curr, delta_exec);

	curr->se.exec_start = now;
	cgroup_account_cpuसमय(curr, delta_exec);

	अगर (!rt_bandwidth_enabled())
		वापस;

	क्रम_each_sched_rt_entity(rt_se) अणु
		काष्ठा rt_rq *rt_rq = rt_rq_of_se(rt_se);

		अगर (sched_rt_runसमय(rt_rq) != RUNTIME_INF) अणु
			raw_spin_lock(&rt_rq->rt_runसमय_lock);
			rt_rq->rt_समय += delta_exec;
			अगर (sched_rt_runसमय_exceeded(rt_rq))
				resched_curr(rq);
			raw_spin_unlock(&rt_rq->rt_runसमय_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
dequeue_top_rt_rq(काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा rq *rq = rq_of_rt_rq(rt_rq);

	BUG_ON(&rq->rt != rt_rq);

	अगर (!rt_rq->rt_queued)
		वापस;

	BUG_ON(!rq->nr_running);

	sub_nr_running(rq, rt_rq->rt_nr_running);
	rt_rq->rt_queued = 0;

पूर्ण

अटल व्योम
enqueue_top_rt_rq(काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा rq *rq = rq_of_rt_rq(rt_rq);

	BUG_ON(&rq->rt != rt_rq);

	अगर (rt_rq->rt_queued)
		वापस;

	अगर (rt_rq_throttled(rt_rq))
		वापस;

	अगर (rt_rq->rt_nr_running) अणु
		add_nr_running(rq, rt_rq->rt_nr_running);
		rt_rq->rt_queued = 1;
	पूर्ण

	/* Kick cpufreq (see the comment in kernel/sched/sched.h). */
	cpufreq_update_util(rq, 0);
पूर्ण

#अगर defined CONFIG_SMP

अटल व्योम
inc_rt_prio_smp(काष्ठा rt_rq *rt_rq, पूर्णांक prio, पूर्णांक prev_prio)
अणु
	काष्ठा rq *rq = rq_of_rt_rq(rt_rq);

#अगर_घोषित CONFIG_RT_GROUP_SCHED
	/*
	 * Change rq's cpupri only अगर rt_rq is the top queue.
	 */
	अगर (&rq->rt != rt_rq)
		वापस;
#पूर्ण_अगर
	अगर (rq->online && prio < prev_prio)
		cpupri_set(&rq->rd->cpupri, rq->cpu, prio);
पूर्ण

अटल व्योम
dec_rt_prio_smp(काष्ठा rt_rq *rt_rq, पूर्णांक prio, पूर्णांक prev_prio)
अणु
	काष्ठा rq *rq = rq_of_rt_rq(rt_rq);

#अगर_घोषित CONFIG_RT_GROUP_SCHED
	/*
	 * Change rq's cpupri only अगर rt_rq is the top queue.
	 */
	अगर (&rq->rt != rt_rq)
		वापस;
#पूर्ण_अगर
	अगर (rq->online && rt_rq->highest_prio.curr != prev_prio)
		cpupri_set(&rq->rd->cpupri, rq->cpu, rt_rq->highest_prio.curr);
पूर्ण

#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत
व्योम inc_rt_prio_smp(काष्ठा rt_rq *rt_rq, पूर्णांक prio, पूर्णांक prev_prio) अणुपूर्ण
अटल अंतरभूत
व्योम dec_rt_prio_smp(काष्ठा rt_rq *rt_rq, पूर्णांक prio, पूर्णांक prev_prio) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#अगर defined CONFIG_SMP || defined CONFIG_RT_GROUP_SCHED
अटल व्योम
inc_rt_prio(काष्ठा rt_rq *rt_rq, पूर्णांक prio)
अणु
	पूर्णांक prev_prio = rt_rq->highest_prio.curr;

	अगर (prio < prev_prio)
		rt_rq->highest_prio.curr = prio;

	inc_rt_prio_smp(rt_rq, prio, prev_prio);
पूर्ण

अटल व्योम
dec_rt_prio(काष्ठा rt_rq *rt_rq, पूर्णांक prio)
अणु
	पूर्णांक prev_prio = rt_rq->highest_prio.curr;

	अगर (rt_rq->rt_nr_running) अणु

		WARN_ON(prio < prev_prio);

		/*
		 * This may have been our highest task, and thereक्रमe
		 * we may have some recomputation to करो
		 */
		अगर (prio == prev_prio) अणु
			काष्ठा rt_prio_array *array = &rt_rq->active;

			rt_rq->highest_prio.curr =
				sched_find_first_bit(array->biपंचांगap);
		पूर्ण

	पूर्ण अन्यथा अणु
		rt_rq->highest_prio.curr = MAX_RT_PRIO-1;
	पूर्ण

	dec_rt_prio_smp(rt_rq, prio, prev_prio);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम inc_rt_prio(काष्ठा rt_rq *rt_rq, पूर्णांक prio) अणुपूर्ण
अटल अंतरभूत व्योम dec_rt_prio(काष्ठा rt_rq *rt_rq, पूर्णांक prio) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_SMP || CONFIG_RT_GROUP_SCHED */

#अगर_घोषित CONFIG_RT_GROUP_SCHED

अटल व्योम
inc_rt_group(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
	अगर (rt_se_boosted(rt_se))
		rt_rq->rt_nr_boosted++;

	अगर (rt_rq->tg)
		start_rt_bandwidth(&rt_rq->tg->rt_bandwidth);
पूर्ण

अटल व्योम
dec_rt_group(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
	अगर (rt_se_boosted(rt_se))
		rt_rq->rt_nr_boosted--;

	WARN_ON(!rt_rq->rt_nr_running && rt_rq->rt_nr_boosted);
पूर्ण

#अन्यथा /* CONFIG_RT_GROUP_SCHED */

अटल व्योम
inc_rt_group(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
	start_rt_bandwidth(&def_rt_bandwidth);
पूर्ण

अटल अंतरभूत
व्योम dec_rt_group(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_RT_GROUP_SCHED */

अटल अंतरभूत
अचिन्हित पूर्णांक rt_se_nr_running(काष्ठा sched_rt_entity *rt_se)
अणु
	काष्ठा rt_rq *group_rq = group_rt_rq(rt_se);

	अगर (group_rq)
		वापस group_rq->rt_nr_running;
	अन्यथा
		वापस 1;
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक rt_se_rr_nr_running(काष्ठा sched_rt_entity *rt_se)
अणु
	काष्ठा rt_rq *group_rq = group_rt_rq(rt_se);
	काष्ठा task_काष्ठा *tsk;

	अगर (group_rq)
		वापस group_rq->rr_nr_running;

	tsk = rt_task_of(rt_se);

	वापस (tsk->policy == SCHED_RR) ? 1 : 0;
पूर्ण

अटल अंतरभूत
व्योम inc_rt_tasks(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
	पूर्णांक prio = rt_se_prio(rt_se);

	WARN_ON(!rt_prio(prio));
	rt_rq->rt_nr_running += rt_se_nr_running(rt_se);
	rt_rq->rr_nr_running += rt_se_rr_nr_running(rt_se);

	inc_rt_prio(rt_rq, prio);
	inc_rt_migration(rt_se, rt_rq);
	inc_rt_group(rt_se, rt_rq);
पूर्ण

अटल अंतरभूत
व्योम dec_rt_tasks(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_rq *rt_rq)
अणु
	WARN_ON(!rt_prio(rt_se_prio(rt_se)));
	WARN_ON(!rt_rq->rt_nr_running);
	rt_rq->rt_nr_running -= rt_se_nr_running(rt_se);
	rt_rq->rr_nr_running -= rt_se_rr_nr_running(rt_se);

	dec_rt_prio(rt_rq, rt_se_prio(rt_se));
	dec_rt_migration(rt_se, rt_rq);
	dec_rt_group(rt_se, rt_rq);
पूर्ण

/*
 * Change rt_se->run_list location unless SAVE && !MOVE
 *
 * assumes ENQUEUE/DEQUEUE flags match
 */
अटल अंतरभूत bool move_entity(अचिन्हित पूर्णांक flags)
अणु
	अगर ((flags & (DEQUEUE_SAVE | DEQUEUE_MOVE)) == DEQUEUE_SAVE)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम __delist_rt_entity(काष्ठा sched_rt_entity *rt_se, काष्ठा rt_prio_array *array)
अणु
	list_del_init(&rt_se->run_list);

	अगर (list_empty(array->queue + rt_se_prio(rt_se)))
		__clear_bit(rt_se_prio(rt_se), array->biपंचांगap);

	rt_se->on_list = 0;
पूर्ण

अटल व्योम __enqueue_rt_entity(काष्ठा sched_rt_entity *rt_se, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rt_rq *rt_rq = rt_rq_of_se(rt_se);
	काष्ठा rt_prio_array *array = &rt_rq->active;
	काष्ठा rt_rq *group_rq = group_rt_rq(rt_se);
	काष्ठा list_head *queue = array->queue + rt_se_prio(rt_se);

	/*
	 * Don't enqueue the group अगर its throttled, or when empty.
	 * The latter is a consequence of the क्रमmer when a child group
	 * get throttled and the current group करोesn't have any other
	 * active members.
	 */
	अगर (group_rq && (rt_rq_throttled(group_rq) || !group_rq->rt_nr_running)) अणु
		अगर (rt_se->on_list)
			__delist_rt_entity(rt_se, array);
		वापस;
	पूर्ण

	अगर (move_entity(flags)) अणु
		WARN_ON_ONCE(rt_se->on_list);
		अगर (flags & ENQUEUE_HEAD)
			list_add(&rt_se->run_list, queue);
		अन्यथा
			list_add_tail(&rt_se->run_list, queue);

		__set_bit(rt_se_prio(rt_se), array->biपंचांगap);
		rt_se->on_list = 1;
	पूर्ण
	rt_se->on_rq = 1;

	inc_rt_tasks(rt_se, rt_rq);
पूर्ण

अटल व्योम __dequeue_rt_entity(काष्ठा sched_rt_entity *rt_se, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rt_rq *rt_rq = rt_rq_of_se(rt_se);
	काष्ठा rt_prio_array *array = &rt_rq->active;

	अगर (move_entity(flags)) अणु
		WARN_ON_ONCE(!rt_se->on_list);
		__delist_rt_entity(rt_se, array);
	पूर्ण
	rt_se->on_rq = 0;

	dec_rt_tasks(rt_se, rt_rq);
पूर्ण

/*
 * Because the prio of an upper entry depends on the lower
 * entries, we must हटाओ entries top - करोwn.
 */
अटल व्योम dequeue_rt_stack(काष्ठा sched_rt_entity *rt_se, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sched_rt_entity *back = शून्य;

	क्रम_each_sched_rt_entity(rt_se) अणु
		rt_se->back = back;
		back = rt_se;
	पूर्ण

	dequeue_top_rt_rq(rt_rq_of_se(back));

	क्रम (rt_se = back; rt_se; rt_se = rt_se->back) अणु
		अगर (on_rt_rq(rt_se))
			__dequeue_rt_entity(rt_se, flags);
	पूर्ण
पूर्ण

अटल व्योम enqueue_rt_entity(काष्ठा sched_rt_entity *rt_se, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rq *rq = rq_of_rt_se(rt_se);

	dequeue_rt_stack(rt_se, flags);
	क्रम_each_sched_rt_entity(rt_se)
		__enqueue_rt_entity(rt_se, flags);
	enqueue_top_rt_rq(&rq->rt);
पूर्ण

अटल व्योम dequeue_rt_entity(काष्ठा sched_rt_entity *rt_se, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rq *rq = rq_of_rt_se(rt_se);

	dequeue_rt_stack(rt_se, flags);

	क्रम_each_sched_rt_entity(rt_se) अणु
		काष्ठा rt_rq *rt_rq = group_rt_rq(rt_se);

		अगर (rt_rq && rt_rq->rt_nr_running)
			__enqueue_rt_entity(rt_se, flags);
	पूर्ण
	enqueue_top_rt_rq(&rq->rt);
पूर्ण

/*
 * Adding/removing a task to/from a priority array:
 */
अटल व्योम
enqueue_task_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	काष्ठा sched_rt_entity *rt_se = &p->rt;

	अगर (flags & ENQUEUE_WAKEUP)
		rt_se->समयout = 0;

	enqueue_rt_entity(rt_se, flags);

	अगर (!task_current(rq, p) && p->nr_cpus_allowed > 1)
		enqueue_pushable_task(rq, p);
पूर्ण

अटल व्योम dequeue_task_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	काष्ठा sched_rt_entity *rt_se = &p->rt;

	update_curr_rt(rq);
	dequeue_rt_entity(rt_se, flags);

	dequeue_pushable_task(rq, p);
पूर्ण

/*
 * Put task to the head or the end of the run list without the overhead of
 * dequeue followed by enqueue.
 */
अटल व्योम
requeue_rt_entity(काष्ठा rt_rq *rt_rq, काष्ठा sched_rt_entity *rt_se, पूर्णांक head)
अणु
	अगर (on_rt_rq(rt_se)) अणु
		काष्ठा rt_prio_array *array = &rt_rq->active;
		काष्ठा list_head *queue = array->queue + rt_se_prio(rt_se);

		अगर (head)
			list_move(&rt_se->run_list, queue);
		अन्यथा
			list_move_tail(&rt_se->run_list, queue);
	पूर्ण
पूर्ण

अटल व्योम requeue_task_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक head)
अणु
	काष्ठा sched_rt_entity *rt_se = &p->rt;
	काष्ठा rt_rq *rt_rq;

	क्रम_each_sched_rt_entity(rt_se) अणु
		rt_rq = rt_rq_of_se(rt_se);
		requeue_rt_entity(rt_rq, rt_se, head);
	पूर्ण
पूर्ण

अटल व्योम yield_task_rt(काष्ठा rq *rq)
अणु
	requeue_task_rt(rq, rq->curr, 0);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक find_lowest_rq(काष्ठा task_काष्ठा *task);

अटल पूर्णांक
select_task_rq_rt(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *curr;
	काष्ठा rq *rq;
	bool test;

	/* For anything but wake ups, just वापस the task_cpu */
	अगर (!(flags & (WF_TTWU | WF_FORK)))
		जाओ out;

	rq = cpu_rq(cpu);

	rcu_पढ़ो_lock();
	curr = READ_ONCE(rq->curr); /* unlocked access */

	/*
	 * If the current task on @p's runqueue is an RT task, then
	 * try to see अगर we can wake this RT task up on another
	 * runqueue. Otherwise simply start this RT task
	 * on its current runqueue.
	 *
	 * We want to aव्योम overloading runqueues. If the woken
	 * task is a higher priority, then it will stay on this CPU
	 * and the lower prio task should be moved to another CPU.
	 * Even though this will probably make the lower prio task
	 * lose its cache, we करो not want to bounce a higher task
	 * around just because it gave up its CPU, perhaps क्रम a
	 * lock?
	 *
	 * For equal prio tasks, we just let the scheduler sort it out.
	 *
	 * Otherwise, just let it ride on the affined RQ and the
	 * post-schedule router will push the preempted task away
	 *
	 * This test is optimistic, अगर we get it wrong the load-balancer
	 * will have to sort it out.
	 *
	 * We take पूर्णांकo account the capacity of the CPU to ensure it fits the
	 * requirement of the task - which is only important on heterogeneous
	 * प्रणालीs like big.LITTLE.
	 */
	test = curr &&
	       unlikely(rt_task(curr)) &&
	       (curr->nr_cpus_allowed < 2 || curr->prio <= p->prio);

	अगर (test || !rt_task_fits_capacity(p, cpu)) अणु
		पूर्णांक target = find_lowest_rq(p);

		/*
		 * Bail out अगर we were क्रमcing a migration to find a better
		 * fitting CPU but our search failed.
		 */
		अगर (!test && target != -1 && !rt_task_fits_capacity(p, target))
			जाओ out_unlock;

		/*
		 * Don't bother moving it अगर the destination CPU is
		 * not running a lower priority task.
		 */
		अगर (target != -1 &&
		    p->prio < cpu_rq(target)->rt.highest_prio.curr)
			cpu = target;
	पूर्ण

out_unlock:
	rcu_पढ़ो_unlock();

out:
	वापस cpu;
पूर्ण

अटल व्योम check_preempt_equal_prio(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	/*
	 * Current can't be migrated, useless to reschedule,
	 * let's hope p can move out.
	 */
	अगर (rq->curr->nr_cpus_allowed == 1 ||
	    !cpupri_find(&rq->rd->cpupri, rq->curr, शून्य))
		वापस;

	/*
	 * p is migratable, so let's not schedule it and
	 * see अगर it is pushed or pulled somewhere अन्यथा.
	 */
	अगर (p->nr_cpus_allowed != 1 &&
	    cpupri_find(&rq->rd->cpupri, p, शून्य))
		वापस;

	/*
	 * There appear to be other CPUs that can accept
	 * the current task but none can run 'p', so lets reschedule
	 * to try and push the current task away:
	 */
	requeue_task_rt(rq, p, 1);
	resched_curr(rq);
पूर्ण

अटल पूर्णांक balance_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, काष्ठा rq_flags *rf)
अणु
	अगर (!on_rt_rq(&p->rt) && need_pull_rt_task(rq, p)) अणु
		/*
		 * This is OK, because current is on_cpu, which aव्योमs it being
		 * picked क्रम load-balance and preemption/IRQs are still
		 * disabled aव्योमing further scheduler activity on it and we've
		 * not yet started the picking loop.
		 */
		rq_unpin_lock(rq, rf);
		pull_rt_task(rq);
		rq_repin_lock(rq, rf);
	पूर्ण

	वापस sched_stop_runnable(rq) || sched_dl_runnable(rq) || sched_rt_runnable(rq);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Preempt the current task with a newly woken task अगर needed:
 */
अटल व्योम check_preempt_curr_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	अगर (p->prio < rq->curr->prio) अणु
		resched_curr(rq);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_SMP
	/*
	 * If:
	 *
	 * - the newly woken task is of equal priority to the current task
	 * - the newly woken task is non-migratable जबतक current is migratable
	 * - current will be preempted on the next reschedule
	 *
	 * we should check to see अगर current can पढ़ोily move to a dअगरferent
	 * cpu.  If so, we will reschedule to allow the push logic to try
	 * to move current somewhere अन्यथा, making room क्रम our non-migratable
	 * task.
	 */
	अगर (p->prio == rq->curr->prio && !test_tsk_need_resched(rq->curr))
		check_preempt_equal_prio(rq, p);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम set_next_task_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, bool first)
अणु
	p->se.exec_start = rq_घड़ी_प्रकारask(rq);

	/* The running task is never eligible क्रम pushing */
	dequeue_pushable_task(rq, p);

	अगर (!first)
		वापस;

	/*
	 * If prev task was rt, put_prev_task() has alपढ़ोy updated the
	 * utilization. We only care of the हाल where we start to schedule a
	 * rt task
	 */
	अगर (rq->curr->sched_class != &rt_sched_class)
		update_rt_rq_load_avg(rq_घड़ी_pelt(rq), rq, 0);

	rt_queue_push_tasks(rq);
पूर्ण

अटल काष्ठा sched_rt_entity *pick_next_rt_entity(काष्ठा rq *rq,
						   काष्ठा rt_rq *rt_rq)
अणु
	काष्ठा rt_prio_array *array = &rt_rq->active;
	काष्ठा sched_rt_entity *next = शून्य;
	काष्ठा list_head *queue;
	पूर्णांक idx;

	idx = sched_find_first_bit(array->biपंचांगap);
	BUG_ON(idx >= MAX_RT_PRIO);

	queue = array->queue + idx;
	next = list_entry(queue->next, काष्ठा sched_rt_entity, run_list);

	वापस next;
पूर्ण

अटल काष्ठा task_काष्ठा *_pick_next_task_rt(काष्ठा rq *rq)
अणु
	काष्ठा sched_rt_entity *rt_se;
	काष्ठा rt_rq *rt_rq  = &rq->rt;

	करो अणु
		rt_se = pick_next_rt_entity(rq, rt_rq);
		BUG_ON(!rt_se);
		rt_rq = group_rt_rq(rt_se);
	पूर्ण जबतक (rt_rq);

	वापस rt_task_of(rt_se);
पूर्ण

अटल काष्ठा task_काष्ठा *pick_next_task_rt(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *p;

	अगर (!sched_rt_runnable(rq))
		वापस शून्य;

	p = _pick_next_task_rt(rq);
	set_next_task_rt(rq, p, true);
	वापस p;
पूर्ण

अटल व्योम put_prev_task_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	update_curr_rt(rq);

	update_rt_rq_load_avg(rq_घड़ी_pelt(rq), rq, 1);

	/*
	 * The previous task needs to be made eligible क्रम pushing
	 * अगर it is still active
	 */
	अगर (on_rt_rq(&p->rt) && p->nr_cpus_allowed > 1)
		enqueue_pushable_task(rq, p);
पूर्ण

#अगर_घोषित CONFIG_SMP

/* Only try algorithms three बार */
#घोषणा RT_MAX_TRIES 3

अटल पूर्णांक pick_rt_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक cpu)
अणु
	अगर (!task_running(rq, p) &&
	    cpumask_test_cpu(cpu, &p->cpus_mask))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Return the highest pushable rq's task, which is suitable to be executed
 * on the CPU, शून्य otherwise
 */
अटल काष्ठा task_काष्ठा *pick_highest_pushable_task(काष्ठा rq *rq, पूर्णांक cpu)
अणु
	काष्ठा plist_head *head = &rq->rt.pushable_tasks;
	काष्ठा task_काष्ठा *p;

	अगर (!has_pushable_tasks(rq))
		वापस शून्य;

	plist_क्रम_each_entry(p, head, pushable_tasks) अणु
		अगर (pick_rt_task(rq, p, cpu))
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल DEFINE_PER_CPU(cpumask_var_t, local_cpu_mask);

अटल पूर्णांक find_lowest_rq(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा sched_करोमुख्य *sd;
	काष्ठा cpumask *lowest_mask = this_cpu_cpumask_var_ptr(local_cpu_mask);
	पूर्णांक this_cpu = smp_processor_id();
	पूर्णांक cpu      = task_cpu(task);
	पूर्णांक ret;

	/* Make sure the mask is initialized first */
	अगर (unlikely(!lowest_mask))
		वापस -1;

	अगर (task->nr_cpus_allowed == 1)
		वापस -1; /* No other tarमाला_लो possible */

	/*
	 * If we're on asym प्रणाली ensure we consider the dअगरferent capacities
	 * of the CPUs when searching क्रम the lowest_mask.
	 */
	अगर (अटल_branch_unlikely(&sched_asym_cpucapacity)) अणु

		ret = cpupri_find_fitness(&task_rq(task)->rd->cpupri,
					  task, lowest_mask,
					  rt_task_fits_capacity);
	पूर्ण अन्यथा अणु

		ret = cpupri_find(&task_rq(task)->rd->cpupri,
				  task, lowest_mask);
	पूर्ण

	अगर (!ret)
		वापस -1; /* No tarमाला_लो found */

	/*
	 * At this poपूर्णांक we have built a mask of CPUs representing the
	 * lowest priority tasks in the प्रणाली.  Now we want to elect
	 * the best one based on our affinity and topology.
	 *
	 * We prioritize the last CPU that the task executed on since
	 * it is most likely cache-hot in that location.
	 */
	अगर (cpumask_test_cpu(cpu, lowest_mask))
		वापस cpu;

	/*
	 * Otherwise, we consult the sched_करोमुख्यs span maps to figure
	 * out which CPU is logically बंदst to our hot cache data.
	 */
	अगर (!cpumask_test_cpu(this_cpu, lowest_mask))
		this_cpu = -1; /* Skip this_cpu opt अगर not among lowest */

	rcu_पढ़ो_lock();
	क्रम_each_करोमुख्य(cpu, sd) अणु
		अगर (sd->flags & SD_WAKE_AFFINE) अणु
			पूर्णांक best_cpu;

			/*
			 * "this_cpu" is cheaper to preempt than a
			 * remote processor.
			 */
			अगर (this_cpu != -1 &&
			    cpumask_test_cpu(this_cpu, sched_करोमुख्य_span(sd))) अणु
				rcu_पढ़ो_unlock();
				वापस this_cpu;
			पूर्ण

			best_cpu = cpumask_any_and_distribute(lowest_mask,
							      sched_करोमुख्य_span(sd));
			अगर (best_cpu < nr_cpu_ids) अणु
				rcu_पढ़ो_unlock();
				वापस best_cpu;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * And finally, अगर there were no matches within the करोमुख्यs
	 * just give the caller *something* to work with from the compatible
	 * locations.
	 */
	अगर (this_cpu != -1)
		वापस this_cpu;

	cpu = cpumask_any_distribute(lowest_mask);
	अगर (cpu < nr_cpu_ids)
		वापस cpu;

	वापस -1;
पूर्ण

/* Will lock the rq it finds */
अटल काष्ठा rq *find_lock_lowest_rq(काष्ठा task_काष्ठा *task, काष्ठा rq *rq)
अणु
	काष्ठा rq *lowest_rq = शून्य;
	पूर्णांक tries;
	पूर्णांक cpu;

	क्रम (tries = 0; tries < RT_MAX_TRIES; tries++) अणु
		cpu = find_lowest_rq(task);

		अगर ((cpu == -1) || (cpu == rq->cpu))
			अवरोध;

		lowest_rq = cpu_rq(cpu);

		अगर (lowest_rq->rt.highest_prio.curr <= task->prio) अणु
			/*
			 * Target rq has tasks of equal or higher priority,
			 * retrying करोes not release any lock and is unlikely
			 * to yield a dअगरferent result.
			 */
			lowest_rq = शून्य;
			अवरोध;
		पूर्ण

		/* अगर the prio of this runqueue changed, try again */
		अगर (द्विगुन_lock_balance(rq, lowest_rq)) अणु
			/*
			 * We had to unlock the run queue. In
			 * the mean समय, task could have
			 * migrated alपढ़ोy or had its affinity changed.
			 * Also make sure that it wasn't scheduled on its rq.
			 */
			अगर (unlikely(task_rq(task) != rq ||
				     !cpumask_test_cpu(lowest_rq->cpu, &task->cpus_mask) ||
				     task_running(rq, task) ||
				     !rt_task(task) ||
				     !task_on_rq_queued(task))) अणु

				द्विगुन_unlock_balance(rq, lowest_rq);
				lowest_rq = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण

		/* If this rq is still suitable use it. */
		अगर (lowest_rq->rt.highest_prio.curr > task->prio)
			अवरोध;

		/* try again */
		द्विगुन_unlock_balance(rq, lowest_rq);
		lowest_rq = शून्य;
	पूर्ण

	वापस lowest_rq;
पूर्ण

अटल काष्ठा task_काष्ठा *pick_next_pushable_task(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *p;

	अगर (!has_pushable_tasks(rq))
		वापस शून्य;

	p = plist_first_entry(&rq->rt.pushable_tasks,
			      काष्ठा task_काष्ठा, pushable_tasks);

	BUG_ON(rq->cpu != task_cpu(p));
	BUG_ON(task_current(rq, p));
	BUG_ON(p->nr_cpus_allowed <= 1);

	BUG_ON(!task_on_rq_queued(p));
	BUG_ON(!rt_task(p));

	वापस p;
पूर्ण

/*
 * If the current CPU has more than one RT task, see अगर the non
 * running task can migrate over to a CPU that is running a task
 * of lesser priority.
 */
अटल पूर्णांक push_rt_task(काष्ठा rq *rq, bool pull)
अणु
	काष्ठा task_काष्ठा *next_task;
	काष्ठा rq *lowest_rq;
	पूर्णांक ret = 0;

	अगर (!rq->rt.overloaded)
		वापस 0;

	next_task = pick_next_pushable_task(rq);
	अगर (!next_task)
		वापस 0;

retry:
	अगर (is_migration_disabled(next_task)) अणु
		काष्ठा task_काष्ठा *push_task = शून्य;
		पूर्णांक cpu;

		अगर (!pull || rq->push_busy)
			वापस 0;

		cpu = find_lowest_rq(rq->curr);
		अगर (cpu == -1 || cpu == rq->cpu)
			वापस 0;

		/*
		 * Given we found a CPU with lower priority than @next_task,
		 * thereक्रमe it should be running. However we cannot migrate it
		 * to this other CPU, instead attempt to push the current
		 * running task on this CPU away.
		 */
		push_task = get_push_task(rq);
		अगर (push_task) अणु
			raw_spin_unlock(&rq->lock);
			stop_one_cpu_noरुको(rq->cpu, push_cpu_stop,
					    push_task, &rq->push_work);
			raw_spin_lock(&rq->lock);
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (WARN_ON(next_task == rq->curr))
		वापस 0;

	/*
	 * It's possible that the next_task slipped in of
	 * higher priority than current. If that's the हाल
	 * just reschedule current.
	 */
	अगर (unlikely(next_task->prio < rq->curr->prio)) अणु
		resched_curr(rq);
		वापस 0;
	पूर्ण

	/* We might release rq lock */
	get_task_काष्ठा(next_task);

	/* find_lock_lowest_rq locks the rq अगर found */
	lowest_rq = find_lock_lowest_rq(next_task, rq);
	अगर (!lowest_rq) अणु
		काष्ठा task_काष्ठा *task;
		/*
		 * find_lock_lowest_rq releases rq->lock
		 * so it is possible that next_task has migrated.
		 *
		 * We need to make sure that the task is still on the same
		 * run-queue and is also still the next task eligible क्रम
		 * pushing.
		 */
		task = pick_next_pushable_task(rq);
		अगर (task == next_task) अणु
			/*
			 * The task hasn't migrated, and is still the next
			 * eligible task, but we failed to find a run-queue
			 * to push it to.  Do not retry in this हाल, since
			 * other CPUs will pull from us when पढ़ोy.
			 */
			जाओ out;
		पूर्ण

		अगर (!task)
			/* No more tasks, just निकास */
			जाओ out;

		/*
		 * Something has shअगरted, try again.
		 */
		put_task_काष्ठा(next_task);
		next_task = task;
		जाओ retry;
	पूर्ण

	deactivate_task(rq, next_task, 0);
	set_task_cpu(next_task, lowest_rq->cpu);
	activate_task(lowest_rq, next_task, 0);
	resched_curr(lowest_rq);
	ret = 1;

	द्विगुन_unlock_balance(rq, lowest_rq);
out:
	put_task_काष्ठा(next_task);

	वापस ret;
पूर्ण

अटल व्योम push_rt_tasks(काष्ठा rq *rq)
अणु
	/* push_rt_task will वापस true अगर it moved an RT */
	जबतक (push_rt_task(rq, false))
		;
पूर्ण

#अगर_घोषित HAVE_RT_PUSH_IPI

/*
 * When a high priority task schedules out from a CPU and a lower priority
 * task is scheduled in, a check is made to see अगर there's any RT tasks
 * on other CPUs that are रुकोing to run because a higher priority RT task
 * is currently running on its CPU. In this हाल, the CPU with multiple RT
 * tasks queued on it (overloaded) needs to be notअगरied that a CPU has खोलोed
 * up that may be able to run one of its non-running queued RT tasks.
 *
 * All CPUs with overloaded RT tasks need to be notअगरied as there is currently
 * no way to know which of these CPUs have the highest priority task रुकोing
 * to run. Instead of trying to take a spinlock on each of these CPUs,
 * which has shown to cause large latency when करोne on machines with many
 * CPUs, sending an IPI to the CPUs to have them push off the overloaded
 * RT tasks रुकोing to run.
 *
 * Just sending an IPI to each of the CPUs is also an issue, as on large
 * count CPU machines, this can cause an IPI storm on a CPU, especially
 * अगर its the only CPU with multiple RT tasks queued, and a large number
 * of CPUs scheduling a lower priority task at the same समय.
 *
 * Each root करोमुख्य has its own irq work function that can iterate over
 * all CPUs with RT overloaded tasks. Since all CPUs with overloaded RT
 * task must be checked अगर there's one or many CPUs that are lowering
 * their priority, there's a single irq work iterator that will try to
 * push off RT tasks that are रुकोing to run.
 *
 * When a CPU schedules a lower priority task, it will kick off the
 * irq work iterator that will jump to each CPU with overloaded RT tasks.
 * As it only takes the first CPU that schedules a lower priority task
 * to start the process, the rto_start variable is incremented and अगर
 * the atomic result is one, then that CPU will try to take the rto_lock.
 * This prevents high contention on the lock as the process handles all
 * CPUs scheduling lower priority tasks.
 *
 * All CPUs that are scheduling a lower priority task will increment the
 * rt_loop_next variable. This will make sure that the irq work iterator
 * checks all RT overloaded CPUs whenever a CPU schedules a new lower
 * priority task, even अगर the iterator is in the middle of a scan. Incrementing
 * the rt_loop_next will cause the iterator to perक्रमm another scan.
 *
 */
अटल पूर्णांक rto_next_cpu(काष्ठा root_करोमुख्य *rd)
अणु
	पूर्णांक next;
	पूर्णांक cpu;

	/*
	 * When starting the IPI RT pushing, the rto_cpu is set to -1,
	 * rt_next_cpu() will simply वापस the first CPU found in
	 * the rto_mask.
	 *
	 * If rto_next_cpu() is called with rto_cpu is a valid CPU, it
	 * will वापस the next CPU found in the rto_mask.
	 *
	 * If there are no more CPUs left in the rto_mask, then a check is made
	 * against rto_loop and rto_loop_next. rto_loop is only updated with
	 * the rto_lock held, but any CPU may increment the rto_loop_next
	 * without any locking.
	 */
	क्रम (;;) अणु

		/* When rto_cpu is -1 this acts like cpumask_first() */
		cpu = cpumask_next(rd->rto_cpu, rd->rto_mask);

		rd->rto_cpu = cpu;

		अगर (cpu < nr_cpu_ids)
			वापस cpu;

		rd->rto_cpu = -1;

		/*
		 * ACQUIRE ensures we see the @rto_mask changes
		 * made prior to the @next value observed.
		 *
		 * Matches WMB in rt_set_overload().
		 */
		next = atomic_पढ़ो_acquire(&rd->rto_loop_next);

		अगर (rd->rto_loop == next)
			अवरोध;

		rd->rto_loop = next;
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत bool rto_start_trylock(atomic_t *v)
अणु
	वापस !atomic_cmpxchg_acquire(v, 0, 1);
पूर्ण

अटल अंतरभूत व्योम rto_start_unlock(atomic_t *v)
अणु
	atomic_set_release(v, 0);
पूर्ण

अटल व्योम tell_cpu_to_push(काष्ठा rq *rq)
अणु
	पूर्णांक cpu = -1;

	/* Keep the loop going अगर the IPI is currently active */
	atomic_inc(&rq->rd->rto_loop_next);

	/* Only one CPU can initiate a loop at a समय */
	अगर (!rto_start_trylock(&rq->rd->rto_loop_start))
		वापस;

	raw_spin_lock(&rq->rd->rto_lock);

	/*
	 * The rto_cpu is updated under the lock, अगर it has a valid CPU
	 * then the IPI is still running and will जारी due to the
	 * update to loop_next, and nothing needs to be करोne here.
	 * Otherwise it is finishing up and an ipi needs to be sent.
	 */
	अगर (rq->rd->rto_cpu < 0)
		cpu = rto_next_cpu(rq->rd);

	raw_spin_unlock(&rq->rd->rto_lock);

	rto_start_unlock(&rq->rd->rto_loop_start);

	अगर (cpu >= 0) अणु
		/* Make sure the rd करोes not get मुक्तd जबतक pushing */
		sched_get_rd(rq->rd);
		irq_work_queue_on(&rq->rd->rto_push_work, cpu);
	पूर्ण
पूर्ण

/* Called from hardirq context */
व्योम rto_push_irq_work_func(काष्ठा irq_work *work)
अणु
	काष्ठा root_करोमुख्य *rd =
		container_of(work, काष्ठा root_करोमुख्य, rto_push_work);
	काष्ठा rq *rq;
	पूर्णांक cpu;

	rq = this_rq();

	/*
	 * We करो not need to grab the lock to check क्रम has_pushable_tasks.
	 * When it माला_लो updated, a check is made अगर a push is possible.
	 */
	अगर (has_pushable_tasks(rq)) अणु
		raw_spin_lock(&rq->lock);
		जबतक (push_rt_task(rq, true))
			;
		raw_spin_unlock(&rq->lock);
	पूर्ण

	raw_spin_lock(&rd->rto_lock);

	/* Pass the IPI to the next rt overloaded queue */
	cpu = rto_next_cpu(rd);

	raw_spin_unlock(&rd->rto_lock);

	अगर (cpu < 0) अणु
		sched_put_rd(rd);
		वापस;
	पूर्ण

	/* Try the next RT overloaded CPU */
	irq_work_queue_on(&rd->rto_push_work, cpu);
पूर्ण
#पूर्ण_अगर /* HAVE_RT_PUSH_IPI */

अटल व्योम pull_rt_task(काष्ठा rq *this_rq)
अणु
	पूर्णांक this_cpu = this_rq->cpu, cpu;
	bool resched = false;
	काष्ठा task_काष्ठा *p, *push_task;
	काष्ठा rq *src_rq;
	पूर्णांक rt_overload_count = rt_overloaded(this_rq);

	अगर (likely(!rt_overload_count))
		वापस;

	/*
	 * Match the barrier from rt_set_overloaded; this guarantees that अगर we
	 * see overloaded we must also see the rto_mask bit.
	 */
	smp_rmb();

	/* If we are the only overloaded CPU करो nothing */
	अगर (rt_overload_count == 1 &&
	    cpumask_test_cpu(this_rq->cpu, this_rq->rd->rto_mask))
		वापस;

#अगर_घोषित HAVE_RT_PUSH_IPI
	अगर (sched_feat(RT_PUSH_IPI)) अणु
		tell_cpu_to_push(this_rq);
		वापस;
	पूर्ण
#पूर्ण_अगर

	क्रम_each_cpu(cpu, this_rq->rd->rto_mask) अणु
		अगर (this_cpu == cpu)
			जारी;

		src_rq = cpu_rq(cpu);

		/*
		 * Don't bother taking the src_rq->lock अगर the next highest
		 * task is known to be lower-priority than our current task.
		 * This may look racy, but अगर this value is about to go
		 * logically higher, the src_rq will push this task away.
		 * And अगर its going logically lower, we करो not care
		 */
		अगर (src_rq->rt.highest_prio.next >=
		    this_rq->rt.highest_prio.curr)
			जारी;

		/*
		 * We can potentially drop this_rq's lock in
		 * द्विगुन_lock_balance, and another CPU could
		 * alter this_rq
		 */
		push_task = शून्य;
		द्विगुन_lock_balance(this_rq, src_rq);

		/*
		 * We can pull only a task, which is pushable
		 * on its rq, and no others.
		 */
		p = pick_highest_pushable_task(src_rq, this_cpu);

		/*
		 * Do we have an RT task that preempts
		 * the to-be-scheduled task?
		 */
		अगर (p && (p->prio < this_rq->rt.highest_prio.curr)) अणु
			WARN_ON(p == src_rq->curr);
			WARN_ON(!task_on_rq_queued(p));

			/*
			 * There's a chance that p is higher in priority
			 * than what's currently running on its CPU.
			 * This is just that p is waking up and hasn't
			 * had a chance to schedule. We only pull
			 * p अगर it is lower in priority than the
			 * current task on the run queue
			 */
			अगर (p->prio < src_rq->curr->prio)
				जाओ skip;

			अगर (is_migration_disabled(p)) अणु
				push_task = get_push_task(src_rq);
			पूर्ण अन्यथा अणु
				deactivate_task(src_rq, p, 0);
				set_task_cpu(p, this_cpu);
				activate_task(this_rq, p, 0);
				resched = true;
			पूर्ण
			/*
			 * We जारी with the search, just in
			 * हाल there's an even higher prio task
			 * in another runqueue. (low likelihood
			 * but possible)
			 */
		पूर्ण
skip:
		द्विगुन_unlock_balance(this_rq, src_rq);

		अगर (push_task) अणु
			raw_spin_unlock(&this_rq->lock);
			stop_one_cpu_noरुको(src_rq->cpu, push_cpu_stop,
					    push_task, &src_rq->push_work);
			raw_spin_lock(&this_rq->lock);
		पूर्ण
	पूर्ण

	अगर (resched)
		resched_curr(this_rq);
पूर्ण

/*
 * If we are not running and we are not going to reschedule soon, we should
 * try to push tasks away now
 */
अटल व्योम task_woken_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	bool need_to_push = !task_running(rq, p) &&
			    !test_tsk_need_resched(rq->curr) &&
			    p->nr_cpus_allowed > 1 &&
			    (dl_task(rq->curr) || rt_task(rq->curr)) &&
			    (rq->curr->nr_cpus_allowed < 2 ||
			     rq->curr->prio <= p->prio);

	अगर (need_to_push)
		push_rt_tasks(rq);
पूर्ण

/* Assumes rq->lock is held */
अटल व्योम rq_online_rt(काष्ठा rq *rq)
अणु
	अगर (rq->rt.overloaded)
		rt_set_overload(rq);

	__enable_runसमय(rq);

	cpupri_set(&rq->rd->cpupri, rq->cpu, rq->rt.highest_prio.curr);
पूर्ण

/* Assumes rq->lock is held */
अटल व्योम rq_offline_rt(काष्ठा rq *rq)
अणु
	अगर (rq->rt.overloaded)
		rt_clear_overload(rq);

	__disable_runसमय(rq);

	cpupri_set(&rq->rd->cpupri, rq->cpu, CPUPRI_INVALID);
पूर्ण

/*
 * When चयन from the rt queue, we bring ourselves to a position
 * that we might want to pull RT tasks from other runqueues.
 */
अटल व्योम चयनed_from_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	/*
	 * If there are other RT tasks then we will reschedule
	 * and the scheduling of the other RT tasks will handle
	 * the balancing. But अगर we are the last RT task
	 * we may need to handle the pulling of RT tasks
	 * now.
	 */
	अगर (!task_on_rq_queued(p) || rq->rt.rt_nr_running)
		वापस;

	rt_queue_pull_task(rq);
पूर्ण

व्योम __init init_sched_rt_class(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		zalloc_cpumask_var_node(&per_cpu(local_cpu_mask, i),
					GFP_KERNEL, cpu_to_node(i));
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * When चयनing a task to RT, we may overload the runqueue
 * with RT tasks. In this हाल we try to push them off to
 * other runqueues.
 */
अटल व्योम चयनed_to_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	/*
	 * If we are alपढ़ोy running, then there's nothing
	 * that needs to be करोne. But अगर we are not running
	 * we may need to preempt the current running task.
	 * If that current running task is also an RT task
	 * then see अगर we can move to another run queue.
	 */
	अगर (task_on_rq_queued(p) && rq->curr != p) अणु
#अगर_घोषित CONFIG_SMP
		अगर (p->nr_cpus_allowed > 1 && rq->rt.overloaded)
			rt_queue_push_tasks(rq);
#पूर्ण_अगर /* CONFIG_SMP */
		अगर (p->prio < rq->curr->prio && cpu_online(cpu_of(rq)))
			resched_curr(rq);
	पूर्ण
पूर्ण

/*
 * Priority of the task has changed. This may cause
 * us to initiate a push or pull.
 */
अटल व्योम
prio_changed_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक oldprio)
अणु
	अगर (!task_on_rq_queued(p))
		वापस;

	अगर (task_current(rq, p)) अणु
#अगर_घोषित CONFIG_SMP
		/*
		 * If our priority decreases जबतक running, we
		 * may need to pull tasks to this runqueue.
		 */
		अगर (oldprio < p->prio)
			rt_queue_pull_task(rq);

		/*
		 * If there's a higher priority task रुकोing to run
		 * then reschedule.
		 */
		अगर (p->prio > rq->rt.highest_prio.curr)
			resched_curr(rq);
#अन्यथा
		/* For UP simply resched on drop of prio */
		अगर (oldprio < p->prio)
			resched_curr(rq);
#पूर्ण_अगर /* CONFIG_SMP */
	पूर्ण अन्यथा अणु
		/*
		 * This task is not running, but अगर it is
		 * greater than the current running task
		 * then reschedule.
		 */
		अगर (p->prio < rq->curr->prio)
			resched_curr(rq);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_POSIX_TIMERS
अटल व्योम watchकरोg(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ soft, hard;

	/* max may change after cur was पढ़ो, this will be fixed next tick */
	soft = task_rlimit(p, RLIMIT_RTTIME);
	hard = task_rlimit_max(p, RLIMIT_RTTIME);

	अगर (soft != RLIM_अनन्त) अणु
		अचिन्हित दीर्घ next;

		अगर (p->rt.watchकरोg_stamp != jअगरfies) अणु
			p->rt.समयout++;
			p->rt.watchकरोg_stamp = jअगरfies;
		पूर्ण

		next = DIV_ROUND_UP(min(soft, hard), USEC_PER_SEC/HZ);
		अगर (p->rt.समयout > next) अणु
			posix_cpuसमयrs_rt_watchकरोg(&p->posix_cpuसमयrs,
						    p->se.sum_exec_runसमय);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम watchकरोg(काष्ठा rq *rq, काष्ठा task_काष्ठा *p) अणु पूर्ण
#पूर्ण_अगर

/*
 * scheduler tick hitting a task of our scheduling class.
 *
 * NOTE: This function can be called remotely by the tick offload that
 * goes aदीर्घ full dynticks. Thereक्रमe no local assumption can be made
 * and everything must be accessed through the @rq and @curr passed in
 * parameters.
 */
अटल व्योम task_tick_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक queued)
अणु
	काष्ठा sched_rt_entity *rt_se = &p->rt;

	update_curr_rt(rq);
	update_rt_rq_load_avg(rq_घड़ी_pelt(rq), rq, 1);

	watchकरोg(rq, p);

	/*
	 * RR tasks need a special क्रमm of बारlice management.
	 * FIFO tasks have no बारlices.
	 */
	अगर (p->policy != SCHED_RR)
		वापस;

	अगर (--p->rt.समय_slice)
		वापस;

	p->rt.समय_slice = sched_rr_बारlice;

	/*
	 * Requeue to the end of queue अगर we (and all of our ancestors) are not
	 * the only element on the queue
	 */
	क्रम_each_sched_rt_entity(rt_se) अणु
		अगर (rt_se->run_list.prev != rt_se->run_list.next) अणु
			requeue_task_rt(rq, p, 0);
			resched_curr(rq);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक get_rr_पूर्णांकerval_rt(काष्ठा rq *rq, काष्ठा task_काष्ठा *task)
अणु
	/*
	 * Time slice is 0 क्रम SCHED_FIFO tasks
	 */
	अगर (task->policy == SCHED_RR)
		वापस sched_rr_बारlice;
	अन्यथा
		वापस 0;
पूर्ण

DEFINE_SCHED_CLASS(rt) = अणु

	.enqueue_task		= enqueue_task_rt,
	.dequeue_task		= dequeue_task_rt,
	.yield_task		= yield_task_rt,

	.check_preempt_curr	= check_preempt_curr_rt,

	.pick_next_task		= pick_next_task_rt,
	.put_prev_task		= put_prev_task_rt,
	.set_next_task          = set_next_task_rt,

#अगर_घोषित CONFIG_SMP
	.balance		= balance_rt,
	.select_task_rq		= select_task_rq_rt,
	.set_cpus_allowed       = set_cpus_allowed_common,
	.rq_online              = rq_online_rt,
	.rq_offline             = rq_offline_rt,
	.task_woken		= task_woken_rt,
	.चयनed_from		= चयनed_from_rt,
	.find_lock_rq		= find_lock_lowest_rq,
#पूर्ण_अगर

	.task_tick		= task_tick_rt,

	.get_rr_पूर्णांकerval	= get_rr_पूर्णांकerval_rt,

	.prio_changed		= prio_changed_rt,
	.चयनed_to		= चयनed_to_rt,

	.update_curr		= update_curr_rt,

#अगर_घोषित CONFIG_UCLAMP_TASK
	.uclamp_enabled		= 1,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_RT_GROUP_SCHED
/*
 * Ensure that the real समय स्थिरraपूर्णांकs are schedulable.
 */
अटल DEFINE_MUTEX(rt_स्थिरraपूर्णांकs_mutex);

अटल अंतरभूत पूर्णांक tg_has_rt_tasks(काष्ठा task_group *tg)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा css_task_iter it;
	पूर्णांक ret = 0;

	/*
	 * Autogroups करो not have RT tasks; see स्वतःgroup_create().
	 */
	अगर (task_group_is_स्वतःgroup(tg))
		वापस 0;

	css_task_iter_start(&tg->css, 0, &it);
	जबतक (!ret && (task = css_task_iter_next(&it)))
		ret |= rt_task(task);
	css_task_iter_end(&it);

	वापस ret;
पूर्ण

काष्ठा rt_schedulable_data अणु
	काष्ठा task_group *tg;
	u64 rt_period;
	u64 rt_runसमय;
पूर्ण;

अटल पूर्णांक tg_rt_schedulable(काष्ठा task_group *tg, व्योम *data)
अणु
	काष्ठा rt_schedulable_data *d = data;
	काष्ठा task_group *child;
	अचिन्हित दीर्घ total, sum = 0;
	u64 period, runसमय;

	period = kसमय_प्रकारo_ns(tg->rt_bandwidth.rt_period);
	runसमय = tg->rt_bandwidth.rt_runसमय;

	अगर (tg == d->tg) अणु
		period = d->rt_period;
		runसमय = d->rt_runसमय;
	पूर्ण

	/*
	 * Cannot have more runसमय than the period.
	 */
	अगर (runसमय > period && runसमय != RUNTIME_INF)
		वापस -EINVAL;

	/*
	 * Ensure we करोn't starve existing RT tasks अगर runसमय turns zero.
	 */
	अगर (rt_bandwidth_enabled() && !runसमय &&
	    tg->rt_bandwidth.rt_runसमय && tg_has_rt_tasks(tg))
		वापस -EBUSY;

	total = to_ratio(period, runसमय);

	/*
	 * Nobody can have more than the global setting allows.
	 */
	अगर (total > to_ratio(global_rt_period(), global_rt_runसमय()))
		वापस -EINVAL;

	/*
	 * The sum of our children's runसमय should not exceed our own.
	 */
	list_क्रम_each_entry_rcu(child, &tg->children, siblings) अणु
		period = kसमय_प्रकारo_ns(child->rt_bandwidth.rt_period);
		runसमय = child->rt_bandwidth.rt_runसमय;

		अगर (child == d->tg) अणु
			period = d->rt_period;
			runसमय = d->rt_runसमय;
		पूर्ण

		sum += to_ratio(period, runसमय);
	पूर्ण

	अगर (sum > total)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __rt_schedulable(काष्ठा task_group *tg, u64 period, u64 runसमय)
अणु
	पूर्णांक ret;

	काष्ठा rt_schedulable_data data = अणु
		.tg = tg,
		.rt_period = period,
		.rt_runसमय = runसमय,
	पूर्ण;

	rcu_पढ़ो_lock();
	ret = walk_tg_tree(tg_rt_schedulable, tg_nop, &data);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक tg_set_rt_bandwidth(काष्ठा task_group *tg,
		u64 rt_period, u64 rt_runसमय)
अणु
	पूर्णांक i, err = 0;

	/*
	 * Disallowing the root group RT runसमय is BAD, it would disallow the
	 * kernel creating (and or operating) RT thपढ़ोs.
	 */
	अगर (tg == &root_task_group && rt_runसमय == 0)
		वापस -EINVAL;

	/* No period करोesn't make any sense. */
	अगर (rt_period == 0)
		वापस -EINVAL;

	/*
	 * Bound quota to defend quota against overflow during bandwidth shअगरt.
	 */
	अगर (rt_runसमय != RUNTIME_INF && rt_runसमय > max_rt_runसमय)
		वापस -EINVAL;

	mutex_lock(&rt_स्थिरraपूर्णांकs_mutex);
	err = __rt_schedulable(tg, rt_period, rt_runसमय);
	अगर (err)
		जाओ unlock;

	raw_spin_lock_irq(&tg->rt_bandwidth.rt_runसमय_lock);
	tg->rt_bandwidth.rt_period = ns_to_kसमय(rt_period);
	tg->rt_bandwidth.rt_runसमय = rt_runसमय;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा rt_rq *rt_rq = tg->rt_rq[i];

		raw_spin_lock(&rt_rq->rt_runसमय_lock);
		rt_rq->rt_runसमय = rt_runसमय;
		raw_spin_unlock(&rt_rq->rt_runसमय_lock);
	पूर्ण
	raw_spin_unlock_irq(&tg->rt_bandwidth.rt_runसमय_lock);
unlock:
	mutex_unlock(&rt_स्थिरraपूर्णांकs_mutex);

	वापस err;
पूर्ण

पूर्णांक sched_group_set_rt_runसमय(काष्ठा task_group *tg, दीर्घ rt_runसमय_us)
अणु
	u64 rt_runसमय, rt_period;

	rt_period = kसमय_प्रकारo_ns(tg->rt_bandwidth.rt_period);
	rt_runसमय = (u64)rt_runसमय_us * NSEC_PER_USEC;
	अगर (rt_runसमय_us < 0)
		rt_runसमय = RUNTIME_INF;
	अन्यथा अगर ((u64)rt_runसमय_us > U64_MAX / NSEC_PER_USEC)
		वापस -EINVAL;

	वापस tg_set_rt_bandwidth(tg, rt_period, rt_runसमय);
पूर्ण

दीर्घ sched_group_rt_runसमय(काष्ठा task_group *tg)
अणु
	u64 rt_runसमय_us;

	अगर (tg->rt_bandwidth.rt_runसमय == RUNTIME_INF)
		वापस -1;

	rt_runसमय_us = tg->rt_bandwidth.rt_runसमय;
	करो_भाग(rt_runसमय_us, NSEC_PER_USEC);
	वापस rt_runसमय_us;
पूर्ण

पूर्णांक sched_group_set_rt_period(काष्ठा task_group *tg, u64 rt_period_us)
अणु
	u64 rt_runसमय, rt_period;

	अगर (rt_period_us > U64_MAX / NSEC_PER_USEC)
		वापस -EINVAL;

	rt_period = rt_period_us * NSEC_PER_USEC;
	rt_runसमय = tg->rt_bandwidth.rt_runसमय;

	वापस tg_set_rt_bandwidth(tg, rt_period, rt_runसमय);
पूर्ण

दीर्घ sched_group_rt_period(काष्ठा task_group *tg)
अणु
	u64 rt_period_us;

	rt_period_us = kसमय_प्रकारo_ns(tg->rt_bandwidth.rt_period);
	करो_भाग(rt_period_us, NSEC_PER_USEC);
	वापस rt_period_us;
पूर्ण

अटल पूर्णांक sched_rt_global_स्थिरraपूर्णांकs(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&rt_स्थिरraपूर्णांकs_mutex);
	ret = __rt_schedulable(शून्य, 0, 0);
	mutex_unlock(&rt_स्थिरraपूर्णांकs_mutex);

	वापस ret;
पूर्ण

पूर्णांक sched_rt_can_attach(काष्ठा task_group *tg, काष्ठा task_काष्ठा *tsk)
अणु
	/* Don't accept realसमय tasks when there is no way क्रम them to run */
	अगर (rt_task(tsk) && tg->rt_bandwidth.rt_runसमय == 0)
		वापस 0;

	वापस 1;
पूर्ण

#अन्यथा /* !CONFIG_RT_GROUP_SCHED */
अटल पूर्णांक sched_rt_global_स्थिरraपूर्णांकs(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&def_rt_bandwidth.rt_runसमय_lock, flags);
	क्रम_each_possible_cpu(i) अणु
		काष्ठा rt_rq *rt_rq = &cpu_rq(i)->rt;

		raw_spin_lock(&rt_rq->rt_runसमय_lock);
		rt_rq->rt_runसमय = global_rt_runसमय();
		raw_spin_unlock(&rt_rq->rt_runसमय_lock);
	पूर्ण
	raw_spin_unlock_irqrestore(&def_rt_bandwidth.rt_runसमय_lock, flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_RT_GROUP_SCHED */

अटल पूर्णांक sched_rt_global_validate(व्योम)
अणु
	अगर (sysctl_sched_rt_period <= 0)
		वापस -EINVAL;

	अगर ((sysctl_sched_rt_runसमय != RUNTIME_INF) &&
		((sysctl_sched_rt_runसमय > sysctl_sched_rt_period) ||
		 ((u64)sysctl_sched_rt_runसमय *
			NSEC_PER_USEC > max_rt_runसमय)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम sched_rt_करो_global(व्योम)
अणु
	def_rt_bandwidth.rt_runसमय = global_rt_runसमय();
	def_rt_bandwidth.rt_period = ns_to_kसमय(global_rt_period());
पूर्ण

पूर्णांक sched_rt_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक old_period, old_runसमय;
	अटल DEFINE_MUTEX(mutex);
	पूर्णांक ret;

	mutex_lock(&mutex);
	old_period = sysctl_sched_rt_period;
	old_runसमय = sysctl_sched_rt_runसमय;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);

	अगर (!ret && ग_लिखो) अणु
		ret = sched_rt_global_validate();
		अगर (ret)
			जाओ unकरो;

		ret = sched_dl_global_validate();
		अगर (ret)
			जाओ unकरो;

		ret = sched_rt_global_स्थिरraपूर्णांकs();
		अगर (ret)
			जाओ unकरो;

		sched_rt_करो_global();
		sched_dl_करो_global();
	पूर्ण
	अगर (0) अणु
unकरो:
		sysctl_sched_rt_period = old_period;
		sysctl_sched_rt_runसमय = old_runसमय;
	पूर्ण
	mutex_unlock(&mutex);

	वापस ret;
पूर्ण

पूर्णांक sched_rr_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;
	अटल DEFINE_MUTEX(mutex);

	mutex_lock(&mutex);
	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	/*
	 * Make sure that पूर्णांकernally we keep jअगरfies.
	 * Also, writing zero resets the बारlice to शेष:
	 */
	अगर (!ret && ग_लिखो) अणु
		sched_rr_बारlice =
			sysctl_sched_rr_बारlice <= 0 ? RR_TIMESLICE :
			msecs_to_jअगरfies(sysctl_sched_rr_बारlice);
	पूर्ण
	mutex_unlock(&mutex);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SCHED_DEBUG
व्योम prपूर्णांक_rt_stats(काष्ठा seq_file *m, पूर्णांक cpu)
अणु
	rt_rq_iter_t iter;
	काष्ठा rt_rq *rt_rq;

	rcu_पढ़ो_lock();
	क्रम_each_rt_rq(rt_rq, iter, cpu_rq(cpu))
		prपूर्णांक_rt_rq(m, cpu, rt_rq);
	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर /* CONFIG_SCHED_DEBUG */
