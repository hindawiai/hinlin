<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Deadline Scheduling Class (SCHED_DEADLINE)
 *
 * Earliest Deadline First (EDF) + Constant Bandwidth Server (CBS).
 *
 * Tasks that periodically executes their instances क्रम less than their
 * runसमय won't miss any of their deadlines.
 * Tasks that are not periodic or sporadic or that tries to execute more
 * than their reserved bandwidth will be slowed करोwn (and may potentially
 * miss some of their deadlines), and won't affect any other task.
 *
 * Copyright (C) 2012 Dario Faggioli <raistlin@linux.it>,
 *                    Juri Lelli <juri.lelli@gmail.com>,
 *                    Michael Trimarchi <michael@amarulasolutions.com>,
 *                    Fabio Checconi <fchecconi@gmail.com>
 */
#समावेश "sched.h"
#समावेश "pelt.h"

काष्ठा dl_bandwidth def_dl_bandwidth;

अटल अंतरभूत काष्ठा task_काष्ठा *dl_task_of(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस container_of(dl_se, काष्ठा task_काष्ठा, dl);
पूर्ण

अटल अंतरभूत काष्ठा rq *rq_of_dl_rq(काष्ठा dl_rq *dl_rq)
अणु
	वापस container_of(dl_rq, काष्ठा rq, dl);
पूर्ण

अटल अंतरभूत काष्ठा dl_rq *dl_rq_of_se(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा task_काष्ठा *p = dl_task_of(dl_se);
	काष्ठा rq *rq = task_rq(p);

	वापस &rq->dl;
पूर्ण

अटल अंतरभूत पूर्णांक on_dl_rq(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस !RB_EMPTY_NODE(&dl_se->rb_node);
पूर्ण

#अगर_घोषित CONFIG_RT_MUTEXES
अटल अंतरभूत काष्ठा sched_dl_entity *pi_of(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस dl_se->pi_se;
पूर्ण

अटल अंतरभूत bool is_dl_boosted(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस pi_of(dl_se) != dl_se;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा sched_dl_entity *pi_of(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस dl_se;
पूर्ण

अटल अंतरभूत bool is_dl_boosted(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत काष्ठा dl_bw *dl_bw_of(पूर्णांक i)
अणु
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_sched_held(),
			 "sched RCU must be held");
	वापस &cpu_rq(i)->rd->dl_bw;
पूर्ण

अटल अंतरभूत पूर्णांक dl_bw_cpus(पूर्णांक i)
अणु
	काष्ठा root_करोमुख्य *rd = cpu_rq(i)->rd;
	पूर्णांक cpus;

	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_sched_held(),
			 "sched RCU must be held");

	अगर (cpumask_subset(rd->span, cpu_active_mask))
		वापस cpumask_weight(rd->span);

	cpus = 0;

	क्रम_each_cpu_and(i, rd->span, cpu_active_mask)
		cpus++;

	वापस cpus;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __dl_bw_capacity(पूर्णांक i)
अणु
	काष्ठा root_करोमुख्य *rd = cpu_rq(i)->rd;
	अचिन्हित दीर्घ cap = 0;

	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_sched_held(),
			 "sched RCU must be held");

	क्रम_each_cpu_and(i, rd->span, cpu_active_mask)
		cap += capacity_orig_of(i);

	वापस cap;
पूर्ण

/*
 * XXX Fix: If 'rq->rd == def_root_domain' perक्रमm AC against capacity
 * of the CPU the task is running on rather rd's \Sum CPU capacity.
 */
अटल अंतरभूत अचिन्हित दीर्घ dl_bw_capacity(पूर्णांक i)
अणु
	अगर (!अटल_branch_unlikely(&sched_asym_cpucapacity) &&
	    capacity_orig_of(i) == SCHED_CAPACITY_SCALE) अणु
		वापस dl_bw_cpus(i) << SCHED_CAPACITY_SHIFT;
	पूर्ण अन्यथा अणु
		वापस __dl_bw_capacity(i);
	पूर्ण
पूर्ण

अटल अंतरभूत bool dl_bw_visited(पूर्णांक cpu, u64 gen)
अणु
	काष्ठा root_करोमुख्य *rd = cpu_rq(cpu)->rd;

	अगर (rd->visit_gen == gen)
		वापस true;

	rd->visit_gen = gen;
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा dl_bw *dl_bw_of(पूर्णांक i)
अणु
	वापस &cpu_rq(i)->dl.dl_bw;
पूर्ण

अटल अंतरभूत पूर्णांक dl_bw_cpus(पूर्णांक i)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dl_bw_capacity(पूर्णांक i)
अणु
	वापस SCHED_CAPACITY_SCALE;
पूर्ण

अटल अंतरभूत bool dl_bw_visited(पूर्णांक cpu, u64 gen)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत
व्योम __add_running_bw(u64 dl_bw, काष्ठा dl_rq *dl_rq)
अणु
	u64 old = dl_rq->running_bw;

	lockdep_निश्चित_held(&(rq_of_dl_rq(dl_rq))->lock);
	dl_rq->running_bw += dl_bw;
	SCHED_WARN_ON(dl_rq->running_bw < old); /* overflow */
	SCHED_WARN_ON(dl_rq->running_bw > dl_rq->this_bw);
	/* kick cpufreq (see the comment in kernel/sched/sched.h). */
	cpufreq_update_util(rq_of_dl_rq(dl_rq), 0);
पूर्ण

अटल अंतरभूत
व्योम __sub_running_bw(u64 dl_bw, काष्ठा dl_rq *dl_rq)
अणु
	u64 old = dl_rq->running_bw;

	lockdep_निश्चित_held(&(rq_of_dl_rq(dl_rq))->lock);
	dl_rq->running_bw -= dl_bw;
	SCHED_WARN_ON(dl_rq->running_bw > old); /* underflow */
	अगर (dl_rq->running_bw > old)
		dl_rq->running_bw = 0;
	/* kick cpufreq (see the comment in kernel/sched/sched.h). */
	cpufreq_update_util(rq_of_dl_rq(dl_rq), 0);
पूर्ण

अटल अंतरभूत
व्योम __add_rq_bw(u64 dl_bw, काष्ठा dl_rq *dl_rq)
अणु
	u64 old = dl_rq->this_bw;

	lockdep_निश्चित_held(&(rq_of_dl_rq(dl_rq))->lock);
	dl_rq->this_bw += dl_bw;
	SCHED_WARN_ON(dl_rq->this_bw < old); /* overflow */
पूर्ण

अटल अंतरभूत
व्योम __sub_rq_bw(u64 dl_bw, काष्ठा dl_rq *dl_rq)
अणु
	u64 old = dl_rq->this_bw;

	lockdep_निश्चित_held(&(rq_of_dl_rq(dl_rq))->lock);
	dl_rq->this_bw -= dl_bw;
	SCHED_WARN_ON(dl_rq->this_bw > old); /* underflow */
	अगर (dl_rq->this_bw > old)
		dl_rq->this_bw = 0;
	SCHED_WARN_ON(dl_rq->running_bw > dl_rq->this_bw);
पूर्ण

अटल अंतरभूत
व्योम add_rq_bw(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
	अगर (!dl_entity_is_special(dl_se))
		__add_rq_bw(dl_se->dl_bw, dl_rq);
पूर्ण

अटल अंतरभूत
व्योम sub_rq_bw(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
	अगर (!dl_entity_is_special(dl_se))
		__sub_rq_bw(dl_se->dl_bw, dl_rq);
पूर्ण

अटल अंतरभूत
व्योम add_running_bw(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
	अगर (!dl_entity_is_special(dl_se))
		__add_running_bw(dl_se->dl_bw, dl_rq);
पूर्ण

अटल अंतरभूत
व्योम sub_running_bw(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
	अगर (!dl_entity_is_special(dl_se))
		__sub_running_bw(dl_se->dl_bw, dl_rq);
पूर्ण

अटल व्योम dl_change_utilization(काष्ठा task_काष्ठा *p, u64 new_bw)
अणु
	काष्ठा rq *rq;

	BUG_ON(p->dl.flags & SCHED_FLAG_SUGOV);

	अगर (task_on_rq_queued(p))
		वापस;

	rq = task_rq(p);
	अगर (p->dl.dl_non_contending) अणु
		sub_running_bw(&p->dl, &rq->dl);
		p->dl.dl_non_contending = 0;
		/*
		 * If the समयr handler is currently running and the
		 * समयr cannot be canceled, inactive_task_समयr()
		 * will see that dl_not_contending is not set, and
		 * will not touch the rq's active utilization,
		 * so we are still safe.
		 */
		अगर (hrसमयr_try_to_cancel(&p->dl.inactive_समयr) == 1)
			put_task_काष्ठा(p);
	पूर्ण
	__sub_rq_bw(p->dl.dl_bw, &rq->dl);
	__add_rq_bw(new_bw, &rq->dl);
पूर्ण

/*
 * The utilization of a task cannot be immediately हटाओd from
 * the rq active utilization (running_bw) when the task blocks.
 * Instead, we have to रुको क्रम the so called "0-lag time".
 *
 * If a task blocks beक्रमe the "0-lag time", a समयr (the inactive
 * समयr) is armed, and running_bw is decreased when the समयr
 * fires.
 *
 * If the task wakes up again beक्रमe the inactive समयr fires,
 * the समयr is canceled, whereas अगर the task wakes up after the
 * inactive समयr fired (and running_bw has been decreased) the
 * task's utilization has to be added to running_bw again.
 * A flag in the deadline scheduling entity (dl_non_contending)
 * is used to aव्योम race conditions between the inactive समयr handler
 * and task wakeups.
 *
 * The following diagram shows how running_bw is updated. A task is
 * "ACTIVE" when its utilization contributes to running_bw; an
 * "ACTIVE contending" task is in the TASK_RUNNING state, जबतक an
 * "ACTIVE non contending" task is a blocked task क्रम which the "0-lag time"
 * has not passed yet. An "INACTIVE" task is a task क्रम which the "0-lag"
 * समय alपढ़ोy passed, which करोes not contribute to running_bw anymore.
 *                              +------------------+
 *             wakeup           |    ACTIVE        |
 *          +------------------>+   contending     |
 *          | add_running_bw    |                  |
 *          |                   +----+------+------+
 *          |                        |      ^
 *          |                dequeue |      |
 * +--------+-------+                |      |
 * |                |   t >= 0-lag   |      | wakeup
 * |    INACTIVE    |<---------------+      |
 * |                | sub_running_bw |      |
 * +--------+-------+                |      |
 *          ^                        |      |
 *          |              t < 0-lag |      |
 *          |                        |      |
 *          |                        V      |
 *          |                   +----+------+------+
 *          | sub_running_bw    |    ACTIVE        |
 *          +-------------------+                  |
 *            inactive समयr    |  non contending  |
 *            fired             +------------------+
 *
 * The task_non_contending() function is invoked when a task
 * blocks, and checks अगर the 0-lag समय alपढ़ोy passed or
 * not (in the first हाल, it directly updates running_bw;
 * in the second हाल, it arms the inactive समयr).
 *
 * The task_contending() function is invoked when a task wakes
 * up, and checks अगर the task is still in the "ACTIVE non contending"
 * state or not (in the second हाल, it updates running_bw).
 */
अटल व्योम task_non_contending(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_dl_entity *dl_se = &p->dl;
	काष्ठा hrसमयr *समयr = &dl_se->inactive_समयr;
	काष्ठा dl_rq *dl_rq = dl_rq_of_se(dl_se);
	काष्ठा rq *rq = rq_of_dl_rq(dl_rq);
	s64 zerolag_समय;

	/*
	 * If this is a non-deadline task that has been boosted,
	 * करो nothing
	 */
	अगर (dl_se->dl_runसमय == 0)
		वापस;

	अगर (dl_entity_is_special(dl_se))
		वापस;

	WARN_ON(dl_se->dl_non_contending);

	zerolag_समय = dl_se->deadline -
		 भाग64_दीर्घ((dl_se->runसमय * dl_se->dl_period),
			dl_se->dl_runसमय);

	/*
	 * Using relative बार instead of the असलolute "0-lag time"
	 * allows to simplअगरy the code
	 */
	zerolag_समय -= rq_घड़ी(rq);

	/*
	 * If the "0-lag time" alपढ़ोy passed, decrease the active
	 * utilization now, instead of starting a समयr
	 */
	अगर ((zerolag_समय < 0) || hrसमयr_active(&dl_se->inactive_समयr)) अणु
		अगर (dl_task(p))
			sub_running_bw(dl_se, dl_rq);
		अगर (!dl_task(p) || p->state == TASK_DEAD) अणु
			काष्ठा dl_bw *dl_b = dl_bw_of(task_cpu(p));

			अगर (p->state == TASK_DEAD)
				sub_rq_bw(&p->dl, &rq->dl);
			raw_spin_lock(&dl_b->lock);
			__dl_sub(dl_b, p->dl.dl_bw, dl_bw_cpus(task_cpu(p)));
			__dl_clear_params(p);
			raw_spin_unlock(&dl_b->lock);
		पूर्ण

		वापस;
	पूर्ण

	dl_se->dl_non_contending = 1;
	get_task_काष्ठा(p);
	hrसमयr_start(समयr, ns_to_kसमय(zerolag_समय), HRTIMER_MODE_REL_HARD);
पूर्ण

अटल व्योम task_contending(काष्ठा sched_dl_entity *dl_se, पूर्णांक flags)
अणु
	काष्ठा dl_rq *dl_rq = dl_rq_of_se(dl_se);

	/*
	 * If this is a non-deadline task that has been boosted,
	 * करो nothing
	 */
	अगर (dl_se->dl_runसमय == 0)
		वापस;

	अगर (flags & ENQUEUE_MIGRATED)
		add_rq_bw(dl_se, dl_rq);

	अगर (dl_se->dl_non_contending) अणु
		dl_se->dl_non_contending = 0;
		/*
		 * If the समयr handler is currently running and the
		 * समयr cannot be canceled, inactive_task_समयr()
		 * will see that dl_not_contending is not set, and
		 * will not touch the rq's active utilization,
		 * so we are still safe.
		 */
		अगर (hrसमयr_try_to_cancel(&dl_se->inactive_समयr) == 1)
			put_task_काष्ठा(dl_task_of(dl_se));
	पूर्ण अन्यथा अणु
		/*
		 * Since "dl_non_contending" is not set, the
		 * task's utilization has alपढ़ोy been हटाओd from
		 * active utilization (either when the task blocked,
		 * when the "inactive timer" fired).
		 * So, add it back.
		 */
		add_running_bw(dl_se, dl_rq);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक is_lefपंचांगost(काष्ठा task_काष्ठा *p, काष्ठा dl_rq *dl_rq)
अणु
	काष्ठा sched_dl_entity *dl_se = &p->dl;

	वापस dl_rq->root.rb_lefपंचांगost == &dl_se->rb_node;
पूर्ण

अटल व्योम init_dl_rq_bw_ratio(काष्ठा dl_rq *dl_rq);

व्योम init_dl_bandwidth(काष्ठा dl_bandwidth *dl_b, u64 period, u64 runसमय)
अणु
	raw_spin_lock_init(&dl_b->dl_runसमय_lock);
	dl_b->dl_period = period;
	dl_b->dl_runसमय = runसमय;
पूर्ण

व्योम init_dl_bw(काष्ठा dl_bw *dl_b)
अणु
	raw_spin_lock_init(&dl_b->lock);
	raw_spin_lock(&def_dl_bandwidth.dl_runसमय_lock);
	अगर (global_rt_runसमय() == RUNTIME_INF)
		dl_b->bw = -1;
	अन्यथा
		dl_b->bw = to_ratio(global_rt_period(), global_rt_runसमय());
	raw_spin_unlock(&def_dl_bandwidth.dl_runसमय_lock);
	dl_b->total_bw = 0;
पूर्ण

व्योम init_dl_rq(काष्ठा dl_rq *dl_rq)
अणु
	dl_rq->root = RB_ROOT_CACHED;

#अगर_घोषित CONFIG_SMP
	/* zero means no -deadline tasks */
	dl_rq->earliest_dl.curr = dl_rq->earliest_dl.next = 0;

	dl_rq->dl_nr_migratory = 0;
	dl_rq->overloaded = 0;
	dl_rq->pushable_dl_tasks_root = RB_ROOT_CACHED;
#अन्यथा
	init_dl_bw(&dl_rq->dl_bw);
#पूर्ण_अगर

	dl_rq->running_bw = 0;
	dl_rq->this_bw = 0;
	init_dl_rq_bw_ratio(dl_rq);
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल अंतरभूत पूर्णांक dl_overloaded(काष्ठा rq *rq)
अणु
	वापस atomic_पढ़ो(&rq->rd->dlo_count);
पूर्ण

अटल अंतरभूत व्योम dl_set_overload(काष्ठा rq *rq)
अणु
	अगर (!rq->online)
		वापस;

	cpumask_set_cpu(rq->cpu, rq->rd->dlo_mask);
	/*
	 * Must be visible beक्रमe the overload count is
	 * set (as in sched_rt.c).
	 *
	 * Matched by the barrier in pull_dl_task().
	 */
	smp_wmb();
	atomic_inc(&rq->rd->dlo_count);
पूर्ण

अटल अंतरभूत व्योम dl_clear_overload(काष्ठा rq *rq)
अणु
	अगर (!rq->online)
		वापस;

	atomic_dec(&rq->rd->dlo_count);
	cpumask_clear_cpu(rq->cpu, rq->rd->dlo_mask);
पूर्ण

अटल व्योम update_dl_migration(काष्ठा dl_rq *dl_rq)
अणु
	अगर (dl_rq->dl_nr_migratory && dl_rq->dl_nr_running > 1) अणु
		अगर (!dl_rq->overloaded) अणु
			dl_set_overload(rq_of_dl_rq(dl_rq));
			dl_rq->overloaded = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (dl_rq->overloaded) अणु
		dl_clear_overload(rq_of_dl_rq(dl_rq));
		dl_rq->overloaded = 0;
	पूर्ण
पूर्ण

अटल व्योम inc_dl_migration(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
	काष्ठा task_काष्ठा *p = dl_task_of(dl_se);

	अगर (p->nr_cpus_allowed > 1)
		dl_rq->dl_nr_migratory++;

	update_dl_migration(dl_rq);
पूर्ण

अटल व्योम dec_dl_migration(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
	काष्ठा task_काष्ठा *p = dl_task_of(dl_se);

	अगर (p->nr_cpus_allowed > 1)
		dl_rq->dl_nr_migratory--;

	update_dl_migration(dl_rq);
पूर्ण

#घोषणा __node_2_pdl(node) \
	rb_entry((node), काष्ठा task_काष्ठा, pushable_dl_tasks)

अटल अंतरभूत bool __pushable_less(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	वापस dl_entity_preempt(&__node_2_pdl(a)->dl, &__node_2_pdl(b)->dl);
पूर्ण

/*
 * The list of pushable -deadline task is not a plist, like in
 * sched_rt.c, it is an rb-tree with tasks ordered by deadline.
 */
अटल व्योम enqueue_pushable_dl_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा rb_node *lefपंचांगost;

	BUG_ON(!RB_EMPTY_NODE(&p->pushable_dl_tasks));

	lefपंचांगost = rb_add_cached(&p->pushable_dl_tasks,
				 &rq->dl.pushable_dl_tasks_root,
				 __pushable_less);
	अगर (lefपंचांगost)
		rq->dl.earliest_dl.next = p->dl.deadline;
पूर्ण

अटल व्योम dequeue_pushable_dl_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा dl_rq *dl_rq = &rq->dl;
	काष्ठा rb_root_cached *root = &dl_rq->pushable_dl_tasks_root;
	काष्ठा rb_node *lefपंचांगost;

	अगर (RB_EMPTY_NODE(&p->pushable_dl_tasks))
		वापस;

	lefपंचांगost = rb_erase_cached(&p->pushable_dl_tasks, root);
	अगर (lefपंचांगost)
		dl_rq->earliest_dl.next = __node_2_pdl(lefपंचांगost)->dl.deadline;

	RB_CLEAR_NODE(&p->pushable_dl_tasks);
पूर्ण

अटल अंतरभूत पूर्णांक has_pushable_dl_tasks(काष्ठा rq *rq)
अणु
	वापस !RB_EMPTY_ROOT(&rq->dl.pushable_dl_tasks_root.rb_root);
पूर्ण

अटल पूर्णांक push_dl_task(काष्ठा rq *rq);

अटल अंतरभूत bool need_pull_dl_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev)
अणु
	वापस rq->online && dl_task(prev);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा callback_head, dl_push_head);
अटल DEFINE_PER_CPU(काष्ठा callback_head, dl_pull_head);

अटल व्योम push_dl_tasks(काष्ठा rq *);
अटल व्योम pull_dl_task(काष्ठा rq *);

अटल अंतरभूत व्योम deadline_queue_push_tasks(काष्ठा rq *rq)
अणु
	अगर (!has_pushable_dl_tasks(rq))
		वापस;

	queue_balance_callback(rq, &per_cpu(dl_push_head, rq->cpu), push_dl_tasks);
पूर्ण

अटल अंतरभूत व्योम deadline_queue_pull_task(काष्ठा rq *rq)
अणु
	queue_balance_callback(rq, &per_cpu(dl_pull_head, rq->cpu), pull_dl_task);
पूर्ण

अटल काष्ठा rq *find_lock_later_rq(काष्ठा task_काष्ठा *task, काष्ठा rq *rq);

अटल काष्ठा rq *dl_task_offline_migration(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा rq *later_rq = शून्य;
	काष्ठा dl_bw *dl_b;

	later_rq = find_lock_later_rq(p, rq);
	अगर (!later_rq) अणु
		पूर्णांक cpu;

		/*
		 * If we cannot preempt any rq, fall back to pick any
		 * online CPU:
		 */
		cpu = cpumask_any_and(cpu_active_mask, p->cpus_ptr);
		अगर (cpu >= nr_cpu_ids) अणु
			/*
			 * Failed to find any suitable CPU.
			 * The task will never come back!
			 */
			BUG_ON(dl_bandwidth_enabled());

			/*
			 * If admission control is disabled we
			 * try a little harder to let the task
			 * run.
			 */
			cpu = cpumask_any(cpu_active_mask);
		पूर्ण
		later_rq = cpu_rq(cpu);
		द्विगुन_lock_balance(rq, later_rq);
	पूर्ण

	अगर (p->dl.dl_non_contending || p->dl.dl_throttled) अणु
		/*
		 * Inactive समयr is armed (or callback is running, but
		 * रुकोing क्रम us to release rq locks). In any हाल, when it
		 * will fire (or जारी), it will see running_bw of this
		 * task migrated to later_rq (and correctly handle it).
		 */
		sub_running_bw(&p->dl, &rq->dl);
		sub_rq_bw(&p->dl, &rq->dl);

		add_rq_bw(&p->dl, &later_rq->dl);
		add_running_bw(&p->dl, &later_rq->dl);
	पूर्ण अन्यथा अणु
		sub_rq_bw(&p->dl, &rq->dl);
		add_rq_bw(&p->dl, &later_rq->dl);
	पूर्ण

	/*
	 * And we finally need to fixup root_करोमुख्य(s) bandwidth accounting,
	 * since p is still hanging out in the old (now moved to शेष) root
	 * करोमुख्य.
	 */
	dl_b = &rq->rd->dl_bw;
	raw_spin_lock(&dl_b->lock);
	__dl_sub(dl_b, p->dl.dl_bw, cpumask_weight(rq->rd->span));
	raw_spin_unlock(&dl_b->lock);

	dl_b = &later_rq->rd->dl_bw;
	raw_spin_lock(&dl_b->lock);
	__dl_add(dl_b, p->dl.dl_bw, cpumask_weight(later_rq->rd->span));
	raw_spin_unlock(&dl_b->lock);

	set_task_cpu(p, later_rq->cpu);
	द्विगुन_unlock_balance(later_rq, rq);

	वापस later_rq;
पूर्ण

#अन्यथा

अटल अंतरभूत
व्योम enqueue_pushable_dl_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत
व्योम dequeue_pushable_dl_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत
व्योम inc_dl_migration(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
पूर्ण

अटल अंतरभूत
व्योम dec_dl_migration(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
पूर्ण

अटल अंतरभूत bool need_pull_dl_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम pull_dl_task(काष्ठा rq *rq)
अणु
पूर्ण

अटल अंतरभूत व्योम deadline_queue_push_tasks(काष्ठा rq *rq)
अणु
पूर्ण

अटल अंतरभूत व्योम deadline_queue_pull_task(काष्ठा rq *rq)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम enqueue_task_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);
अटल व्योम __dequeue_task_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);
अटल व्योम check_preempt_curr_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags);

/*
 * We are being explicitly inक्रमmed that a new instance is starting,
 * and this means that:
 *  - the असलolute deadline of the entity has to be placed at
 *    current समय + relative deadline;
 *  - the runसमय of the entity has to be set to the maximum value.
 *
 * The capability of specअगरying such event is useful whenever a -deadline
 * entity wants to (try to!) synchronize its behaviour with the scheduler's
 * one, and to (try to!) reconcile itself with its own scheduling
 * parameters.
 */
अटल अंतरभूत व्योम setup_new_dl_entity(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा dl_rq *dl_rq = dl_rq_of_se(dl_se);
	काष्ठा rq *rq = rq_of_dl_rq(dl_rq);

	WARN_ON(is_dl_boosted(dl_se));
	WARN_ON(dl_समय_beक्रमe(rq_घड़ी(rq), dl_se->deadline));

	/*
	 * We are racing with the deadline समयr. So, करो nothing because
	 * the deadline समयr handler will take care of properly reअक्षरging
	 * the runसमय and postponing the deadline
	 */
	अगर (dl_se->dl_throttled)
		वापस;

	/*
	 * We use the regular wall घड़ी समय to set deadlines in the
	 * future; in fact, we must consider execution overheads (समय
	 * spent on hardirq context, etc.).
	 */
	dl_se->deadline = rq_घड़ी(rq) + dl_se->dl_deadline;
	dl_se->runसमय = dl_se->dl_runसमय;
पूर्ण

/*
 * Pure Earliest Deadline First (EDF) scheduling करोes not deal with the
 * possibility of a entity lasting more than what it declared, and thus
 * exhausting its runसमय.
 *
 * Here we are पूर्णांकerested in making runसमय overrun possible, but we करो
 * not want a entity which is misbehaving to affect the scheduling of all
 * other entities.
 * Thereक्रमe, a budgeting strategy called Constant Bandwidth Server (CBS)
 * is used, in order to confine each entity within its own bandwidth.
 *
 * This function deals exactly with that, and ensures that when the runसमय
 * of a entity is replenished, its deadline is also postponed. That ensures
 * the overrunning entity can't पूर्णांकerfere with other entity in the प्रणाली and
 * can't make them miss their deadlines. Reasons why this kind of overruns
 * could happen are, typically, a entity voluntarily trying to overcome its
 * runसमय, or it just underestimated it during sched_setattr().
 */
अटल व्योम replenish_dl_entity(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा dl_rq *dl_rq = dl_rq_of_se(dl_se);
	काष्ठा rq *rq = rq_of_dl_rq(dl_rq);

	BUG_ON(pi_of(dl_se)->dl_runसमय <= 0);

	/*
	 * This could be the हाल क्रम a !-dl task that is boosted.
	 * Just go with full inherited parameters.
	 */
	अगर (dl_se->dl_deadline == 0) अणु
		dl_se->deadline = rq_घड़ी(rq) + pi_of(dl_se)->dl_deadline;
		dl_se->runसमय = pi_of(dl_se)->dl_runसमय;
	पूर्ण

	अगर (dl_se->dl_yielded && dl_se->runसमय > 0)
		dl_se->runसमय = 0;

	/*
	 * We keep moving the deadline away until we get some
	 * available runसमय क्रम the entity. This ensures correct
	 * handling of situations where the runसमय overrun is
	 * arbitrary large.
	 */
	जबतक (dl_se->runसमय <= 0) अणु
		dl_se->deadline += pi_of(dl_se)->dl_period;
		dl_se->runसमय += pi_of(dl_se)->dl_runसमय;
	पूर्ण

	/*
	 * At this poपूर्णांक, the deadline really should be "in
	 * the future" with respect to rq->घड़ी. If it's
	 * not, we are, क्रम some reason, lagging too much!
	 * Anyway, after having warn userspace abut that,
	 * we still try to keep the things running by
	 * resetting the deadline and the budget of the
	 * entity.
	 */
	अगर (dl_समय_beक्रमe(dl_se->deadline, rq_घड़ी(rq))) अणु
		prपूर्णांकk_deferred_once("sched: DL replenish lagged too much\n");
		dl_se->deadline = rq_घड़ी(rq) + pi_of(dl_se)->dl_deadline;
		dl_se->runसमय = pi_of(dl_se)->dl_runसमय;
	पूर्ण

	अगर (dl_se->dl_yielded)
		dl_se->dl_yielded = 0;
	अगर (dl_se->dl_throttled)
		dl_se->dl_throttled = 0;
पूर्ण

/*
 * Here we check अगर --at समय t-- an entity (which is probably being
 * [re]activated or, in general, enqueued) can use its reमुख्यing runसमय
 * and its current deadline _without_ exceeding the bandwidth it is
 * asचिन्हित (function वापसs true अगर it can't). We are in fact applying
 * one of the CBS rules: when a task wakes up, अगर the residual runसमय
 * over residual deadline fits within the allocated bandwidth, then we
 * can keep the current (असलolute) deadline and residual budget without
 * disrupting the schedulability of the प्रणाली. Otherwise, we should
 * refill the runसमय and set the deadline a period in the future,
 * because keeping the current (असलolute) deadline of the task would
 * result in अवरोधing guarantees promised to other tasks (refer to
 * Documentation/scheduler/sched-deadline.rst क्रम more inक्रमmation).
 *
 * This function वापसs true अगर:
 *
 *   runसमय / (deadline - t) > dl_runसमय / dl_deadline ,
 *
 * IOW we can't recycle current parameters.
 *
 * Notice that the bandwidth check is करोne against the deadline. For
 * task with deadline equal to period this is the same of using
 * dl_period instead of dl_deadline in the equation above.
 */
अटल bool dl_entity_overflow(काष्ठा sched_dl_entity *dl_se, u64 t)
अणु
	u64 left, right;

	/*
	 * left and right are the two sides of the equation above,
	 * after a bit of shuffling to use multiplications instead
	 * of भागisions.
	 *
	 * Note that none of the समय values involved in the two
	 * multiplications are असलolute: dl_deadline and dl_runसमय
	 * are the relative deadline and the maximum runसमय of each
	 * instance, runसमय is the runसमय left क्रम the last instance
	 * and (deadline - t), since t is rq->घड़ी, is the समय left
	 * to the (असलolute) deadline. Even अगर overflowing the u64 type
	 * is very unlikely to occur in both हालs, here we scale करोwn
	 * as we want to aव्योम that risk at all. Scaling करोwn by 10
	 * means that we reduce granularity to 1us. We are fine with it,
	 * since this is only a true/false check and, anyway, thinking
	 * of anything below microseconds resolution is actually fiction
	 * (but still we want to give the user that illusion >;).
	 */
	left = (pi_of(dl_se)->dl_deadline >> DL_SCALE) * (dl_se->runसमय >> DL_SCALE);
	right = ((dl_se->deadline - t) >> DL_SCALE) *
		(pi_of(dl_se)->dl_runसमय >> DL_SCALE);

	वापस dl_समय_beक्रमe(right, left);
पूर्ण

/*
 * Revised wakeup rule [1]: For self-suspending tasks, rather then
 * re-initializing task's runसमय and deadline, the revised wakeup
 * rule adjusts the task's runसमय to aव्योम the task to overrun its
 * density.
 *
 * Reasoning: a task may overrun the density अगर:
 *    runसमय / (deadline - t) > dl_runसमय / dl_deadline
 *
 * Thereक्रमe, runसमय can be adjusted to:
 *     runसमय = (dl_runसमय / dl_deadline) * (deadline - t)
 *
 * In such way that runसमय will be equal to the maximum density
 * the task can use without अवरोधing any rule.
 *
 * [1] Luca Abeni, Giuseppe Lipari, and Juri Lelli. 2015. Constant
 * bandwidth server revisited. SIGBED Rev. 11, 4 (January 2015), 19-24.
 */
अटल व्योम
update_dl_revised_wakeup(काष्ठा sched_dl_entity *dl_se, काष्ठा rq *rq)
अणु
	u64 laxity = dl_se->deadline - rq_घड़ी(rq);

	/*
	 * If the task has deadline < period, and the deadline is in the past,
	 * it should alपढ़ोy be throttled beक्रमe this check.
	 *
	 * See update_dl_entity() comments क्रम further details.
	 */
	WARN_ON(dl_समय_beक्रमe(dl_se->deadline, rq_घड़ी(rq)));

	dl_se->runसमय = (dl_se->dl_density * laxity) >> BW_SHIFT;
पूर्ण

/*
 * Regarding the deadline, a task with implicit deadline has a relative
 * deadline == relative period. A task with स्थिरrained deadline has a
 * relative deadline <= relative period.
 *
 * We support स्थिरrained deadline tasks. However, there are some restrictions
 * applied only क्रम tasks which करो not have an implicit deadline. See
 * update_dl_entity() to know more about such restrictions.
 *
 * The dl_is_implicit() वापसs true अगर the task has an implicit deadline.
 */
अटल अंतरभूत bool dl_is_implicit(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस dl_se->dl_deadline == dl_se->dl_period;
पूर्ण

/*
 * When a deadline entity is placed in the runqueue, its runसमय and deadline
 * might need to be updated. This is करोne by a CBS wake up rule. There are two
 * dअगरferent rules: 1) the original CBS; and 2) the Revisited CBS.
 *
 * When the task is starting a new period, the Original CBS is used. In this
 * हाल, the runसमय is replenished and a new असलolute deadline is set.
 *
 * When a task is queued beक्रमe the begin of the next period, using the
 * reमुख्यing runसमय and deadline could make the entity to overflow, see
 * dl_entity_overflow() to find more about runसमय overflow. When such हाल
 * is detected, the runसमय and deadline need to be updated.
 *
 * If the task has an implicit deadline, i.e., deadline == period, the Original
 * CBS is applied. the runसमय is replenished and a new असलolute deadline is
 * set, as in the previous हालs.
 *
 * However, the Original CBS करोes not work properly क्रम tasks with
 * deadline < period, which are said to have a स्थिरrained deadline. By
 * applying the Original CBS, a स्थिरrained deadline task would be able to run
 * runसमय/deadline in a period. With deadline < period, the task would
 * overrun the runसमय/period allowed bandwidth, अवरोधing the admission test.
 *
 * In order to prevent this misbehave, the Revisited CBS is used क्रम
 * स्थिरrained deadline tasks when a runसमय overflow is detected. In the
 * Revisited CBS, rather than replenishing & setting a new असलolute deadline,
 * the reमुख्यing runसमय of the task is reduced to aव्योम runसमय overflow.
 * Please refer to the comments update_dl_revised_wakeup() function to find
 * more about the Revised CBS rule.
 */
अटल व्योम update_dl_entity(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा dl_rq *dl_rq = dl_rq_of_se(dl_se);
	काष्ठा rq *rq = rq_of_dl_rq(dl_rq);

	अगर (dl_समय_beक्रमe(dl_se->deadline, rq_घड़ी(rq)) ||
	    dl_entity_overflow(dl_se, rq_घड़ी(rq))) अणु

		अगर (unlikely(!dl_is_implicit(dl_se) &&
			     !dl_समय_beक्रमe(dl_se->deadline, rq_घड़ी(rq)) &&
			     !is_dl_boosted(dl_se))) अणु
			update_dl_revised_wakeup(dl_se, rq);
			वापस;
		पूर्ण

		dl_se->deadline = rq_घड़ी(rq) + pi_of(dl_se)->dl_deadline;
		dl_se->runसमय = pi_of(dl_se)->dl_runसमय;
	पूर्ण
पूर्ण

अटल अंतरभूत u64 dl_next_period(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस dl_se->deadline - dl_se->dl_deadline + dl_se->dl_period;
पूर्ण

/*
 * If the entity depleted all its runसमय, and अगर we want it to sleep
 * जबतक रुकोing क्रम some new execution समय to become available, we
 * set the bandwidth replenishment समयr to the replenishment instant
 * and try to activate it.
 *
 * Notice that it is important क्रम the caller to know अगर the समयr
 * actually started or not (i.e., the replenishment instant is in
 * the future or in the past).
 */
अटल पूर्णांक start_dl_समयr(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_dl_entity *dl_se = &p->dl;
	काष्ठा hrसमयr *समयr = &dl_se->dl_समयr;
	काष्ठा rq *rq = task_rq(p);
	kसमय_प्रकार now, act;
	s64 delta;

	lockdep_निश्चित_held(&rq->lock);

	/*
	 * We want the समयr to fire at the deadline, but considering
	 * that it is actually coming from rq->घड़ी and not from
	 * hrसमयr's समय base पढ़ोing.
	 */
	act = ns_to_kसमय(dl_next_period(dl_se));
	now = hrसमयr_cb_get_समय(समयr);
	delta = kसमय_प्रकारo_ns(now) - rq_घड़ी(rq);
	act = kसमय_add_ns(act, delta);

	/*
	 * If the expiry समय alपढ़ोy passed, e.g., because the value
	 * chosen as the deadline is too small, करोn't even try to
	 * start the समयr in the past!
	 */
	अगर (kसमय_us_delta(act, now) < 0)
		वापस 0;

	/*
	 * !enqueued will guarantee another callback; even अगर one is alपढ़ोy in
	 * progress. This ensures a balanced अणुget,putपूर्ण_task_काष्ठा().
	 *
	 * The race against __run_समयr() clearing the enqueued state is
	 * harmless because we're holding task_rq()->lock, thereक्रमe the समयr
	 * expiring after we've करोne the check will रुको on its task_rq_lock()
	 * and observe our state.
	 */
	अगर (!hrसमयr_is_queued(समयr)) अणु
		get_task_काष्ठा(p);
		hrसमयr_start(समयr, act, HRTIMER_MODE_ABS_HARD);
	पूर्ण

	वापस 1;
पूर्ण

/*
 * This is the bandwidth enक्रमcement समयr callback. If here, we know
 * a task is not on its dl_rq, since the fact that the समयr was running
 * means the task is throttled and needs a runसमय replenishment.
 *
 * However, what we actually करो depends on the fact the task is active,
 * (it is on its rq) or has been हटाओd from there by a call to
 * dequeue_task_dl(). In the क्रमmer हाल we must issue the runसमय
 * replenishment and add the task back to the dl_rq; in the latter, we just
 * करो nothing but clearing dl_throttled, so that runसमय and deadline
 * updating (and the queueing back to dl_rq) will be करोne by the
 * next call to enqueue_task_dl().
 */
अटल क्रमागत hrसमयr_restart dl_task_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा sched_dl_entity *dl_se = container_of(समयr,
						     काष्ठा sched_dl_entity,
						     dl_समयr);
	काष्ठा task_काष्ठा *p = dl_task_of(dl_se);
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	rq = task_rq_lock(p, &rf);

	/*
	 * The task might have changed its scheduling policy to something
	 * dअगरferent than SCHED_DEADLINE (through चयनed_from_dl()).
	 */
	अगर (!dl_task(p))
		जाओ unlock;

	/*
	 * The task might have been boosted by someone अन्यथा and might be in the
	 * boosting/deboosting path, its not throttled.
	 */
	अगर (is_dl_boosted(dl_se))
		जाओ unlock;

	/*
	 * Spurious समयr due to start_dl_समयr() race; or we alपढ़ोy received
	 * a replenishment from rt_mutex_setprio().
	 */
	अगर (!dl_se->dl_throttled)
		जाओ unlock;

	sched_घड़ी_प्रकारick();
	update_rq_घड़ी(rq);

	/*
	 * If the throttle happened during sched-out; like:
	 *
	 *   schedule()
	 *     deactivate_task()
	 *       dequeue_task_dl()
	 *         update_curr_dl()
	 *           start_dl_समयr()
	 *         __dequeue_task_dl()
	 *     prev->on_rq = 0;
	 *
	 * We can be both throttled and !queued. Replenish the counter
	 * but करो not enqueue -- रुको क्रम our wakeup to करो that.
	 */
	अगर (!task_on_rq_queued(p)) अणु
		replenish_dl_entity(dl_se);
		जाओ unlock;
	पूर्ण

#अगर_घोषित CONFIG_SMP
	अगर (unlikely(!rq->online)) अणु
		/*
		 * If the runqueue is no दीर्घer available, migrate the
		 * task अन्यथाwhere. This necessarily changes rq.
		 */
		lockdep_unpin_lock(&rq->lock, rf.cookie);
		rq = dl_task_offline_migration(rq, p);
		rf.cookie = lockdep_pin_lock(&rq->lock);
		update_rq_घड़ी(rq);

		/*
		 * Now that the task has been migrated to the new RQ and we
		 * have that locked, proceed as normal and enqueue the task
		 * there.
		 */
	पूर्ण
#पूर्ण_अगर

	enqueue_task_dl(rq, p, ENQUEUE_REPLENISH);
	अगर (dl_task(rq->curr))
		check_preempt_curr_dl(rq, p, 0);
	अन्यथा
		resched_curr(rq);

#अगर_घोषित CONFIG_SMP
	/*
	 * Queueing this task back might have overloaded rq, check अगर we need
	 * to kick someone away.
	 */
	अगर (has_pushable_dl_tasks(rq)) अणु
		/*
		 * Nothing relies on rq->lock after this, so its safe to drop
		 * rq->lock.
		 */
		rq_unpin_lock(rq, &rf);
		push_dl_task(rq);
		rq_repin_lock(rq, &rf);
	पूर्ण
#पूर्ण_अगर

unlock:
	task_rq_unlock(rq, p, &rf);

	/*
	 * This can मुक्त the task_काष्ठा, including this hrसमयr, करो not touch
	 * anything related to that after this.
	 */
	put_task_काष्ठा(p);

	वापस HRTIMER_NORESTART;
पूर्ण

व्योम init_dl_task_समयr(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा hrसमयr *समयr = &dl_se->dl_समयr;

	hrसमयr_init(समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
	समयr->function = dl_task_समयr;
पूर्ण

/*
 * During the activation, CBS checks अगर it can reuse the current task's
 * runसमय and period. If the deadline of the task is in the past, CBS
 * cannot use the runसमय, and so it replenishes the task. This rule
 * works fine क्रम implicit deadline tasks (deadline == period), and the
 * CBS was deचिन्हित क्रम implicit deadline tasks. However, a task with
 * स्थिरrained deadline (deadline < period) might be awakened after the
 * deadline, but beक्रमe the next period. In this हाल, replenishing the
 * task would allow it to run क्रम runसमय / deadline. As in this हाल
 * deadline < period, CBS enables a task to run क्रम more than the
 * runसमय / period. In a very loaded प्रणाली, this can cause a करोmino
 * effect, making other tasks miss their deadlines.
 *
 * To aव्योम this problem, in the activation of a स्थिरrained deadline
 * task after the deadline but beक्रमe the next period, throttle the
 * task and set the replenishing समयr to the begin of the next period,
 * unless it is boosted.
 */
अटल अंतरभूत व्योम dl_check_स्थिरrained_dl(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा task_काष्ठा *p = dl_task_of(dl_se);
	काष्ठा rq *rq = rq_of_dl_rq(dl_rq_of_se(dl_se));

	अगर (dl_समय_beक्रमe(dl_se->deadline, rq_घड़ी(rq)) &&
	    dl_समय_beक्रमe(rq_घड़ी(rq), dl_next_period(dl_se))) अणु
		अगर (unlikely(is_dl_boosted(dl_se) || !start_dl_समयr(p)))
			वापस;
		dl_se->dl_throttled = 1;
		अगर (dl_se->runसमय > 0)
			dl_se->runसमय = 0;
	पूर्ण
पूर्ण

अटल
पूर्णांक dl_runसमय_exceeded(काष्ठा sched_dl_entity *dl_se)
अणु
	वापस (dl_se->runसमय <= 0);
पूर्ण

बाह्य bool sched_rt_bandwidth_account(काष्ठा rt_rq *rt_rq);

/*
 * This function implements the GRUB accounting rule:
 * according to the GRUB reclaiming algorithm, the runसमय is
 * not decreased as "dq = -dt", but as
 * "dq = -max{u / Umax, (1 - Uinact - Uextra)} dt",
 * where u is the utilization of the task, Umax is the maximum reclaimable
 * utilization, Uinact is the (per-runqueue) inactive utilization, computed
 * as the dअगरference between the "total runqueue utilization" and the
 * runqueue active utilization, and Uextra is the (per runqueue) extra
 * reclaimable utilization.
 * Since rq->dl.running_bw and rq->dl.this_bw contain utilizations
 * multiplied by 2^BW_SHIFT, the result has to be shअगरted right by
 * BW_SHIFT.
 * Since rq->dl.bw_ratio contains 1 / Umax multiplied by 2^RATIO_SHIFT,
 * dl_bw is multiped by rq->dl.bw_ratio and shअगरted right by RATIO_SHIFT.
 * Since delta is a 64 bit variable, to have an overflow its value
 * should be larger than 2^(64 - 20 - 8), which is more than 64 seconds.
 * So, overflow is not an issue here.
 */
अटल u64 grub_reclaim(u64 delta, काष्ठा rq *rq, काष्ठा sched_dl_entity *dl_se)
अणु
	u64 u_inact = rq->dl.this_bw - rq->dl.running_bw; /* Utot - Uact */
	u64 u_act;
	u64 u_act_min = (dl_se->dl_bw * rq->dl.bw_ratio) >> RATIO_SHIFT;

	/*
	 * Instead of computing maxअणुu * bw_ratio, (1 - u_inact - u_extra)पूर्ण,
	 * we compare u_inact + rq->dl.extra_bw with
	 * 1 - (u * rq->dl.bw_ratio >> RATIO_SHIFT), because
	 * u_inact + rq->dl.extra_bw can be larger than
	 * 1 * (so, 1 - u_inact - rq->dl.extra_bw would be negative
	 * leading to wrong results)
	 */
	अगर (u_inact + rq->dl.extra_bw > BW_UNIT - u_act_min)
		u_act = u_act_min;
	अन्यथा
		u_act = BW_UNIT - u_inact - rq->dl.extra_bw;

	वापस (delta * u_act) >> BW_SHIFT;
पूर्ण

/*
 * Update the current task's runसमय statistics (provided it is still
 * a -deadline task and has not been हटाओd from the dl_rq).
 */
अटल व्योम update_curr_dl(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *curr = rq->curr;
	काष्ठा sched_dl_entity *dl_se = &curr->dl;
	u64 delta_exec, scaled_delta_exec;
	पूर्णांक cpu = cpu_of(rq);
	u64 now;

	अगर (!dl_task(curr) || !on_dl_rq(dl_se))
		वापस;

	/*
	 * Consumed budget is computed considering the समय as
	 * observed by schedulable tasks (excluding समय spent
	 * in hardirq context, etc.). Deadlines are instead
	 * computed using hard wallसमय. This seems to be the more
	 * natural solution, but the full ramअगरications of this
	 * approach need further study.
	 */
	now = rq_घड़ी_प्रकारask(rq);
	delta_exec = now - curr->se.exec_start;
	अगर (unlikely((s64)delta_exec <= 0)) अणु
		अगर (unlikely(dl_se->dl_yielded))
			जाओ throttle;
		वापस;
	पूर्ण

	schedstat_set(curr->se.statistics.exec_max,
		      max(curr->se.statistics.exec_max, delta_exec));

	curr->se.sum_exec_runसमय += delta_exec;
	account_group_exec_runसमय(curr, delta_exec);

	curr->se.exec_start = now;
	cgroup_account_cpuसमय(curr, delta_exec);

	अगर (dl_entity_is_special(dl_se))
		वापस;

	/*
	 * For tasks that participate in GRUB, we implement GRUB-PA: the
	 * spare reclaimed bandwidth is used to घड़ी करोwn frequency.
	 *
	 * For the others, we still need to scale reservation parameters
	 * according to current frequency and CPU maximum capacity.
	 */
	अगर (unlikely(dl_se->flags & SCHED_FLAG_RECLAIM)) अणु
		scaled_delta_exec = grub_reclaim(delta_exec,
						 rq,
						 &curr->dl);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ scale_freq = arch_scale_freq_capacity(cpu);
		अचिन्हित दीर्घ scale_cpu = arch_scale_cpu_capacity(cpu);

		scaled_delta_exec = cap_scale(delta_exec, scale_freq);
		scaled_delta_exec = cap_scale(scaled_delta_exec, scale_cpu);
	पूर्ण

	dl_se->runसमय -= scaled_delta_exec;

throttle:
	अगर (dl_runसमय_exceeded(dl_se) || dl_se->dl_yielded) अणु
		dl_se->dl_throttled = 1;

		/* If requested, inक्रमm the user about runसमय overruns. */
		अगर (dl_runसमय_exceeded(dl_se) &&
		    (dl_se->flags & SCHED_FLAG_DL_OVERRUN))
			dl_se->dl_overrun = 1;

		__dequeue_task_dl(rq, curr, 0);
		अगर (unlikely(is_dl_boosted(dl_se) || !start_dl_समयr(curr)))
			enqueue_task_dl(rq, curr, ENQUEUE_REPLENISH);

		अगर (!is_lefपंचांगost(curr, &rq->dl))
			resched_curr(rq);
	पूर्ण

	/*
	 * Because -- क्रम now -- we share the rt bandwidth, we need to
	 * account our runसमय there too, otherwise actual rt tasks
	 * would be able to exceed the shared quota.
	 *
	 * Account to the root rt group क्रम now.
	 *
	 * The solution we're working towards is having the RT groups scheduled
	 * using deadline servers -- however there's a few nasties to figure
	 * out beक्रमe that can happen.
	 */
	अगर (rt_bandwidth_enabled()) अणु
		काष्ठा rt_rq *rt_rq = &rq->rt;

		raw_spin_lock(&rt_rq->rt_runसमय_lock);
		/*
		 * We'll let actual RT tasks worry about the overflow here, we
		 * have our own CBS to keep us अंतरभूत; only account when RT
		 * bandwidth is relevant.
		 */
		अगर (sched_rt_bandwidth_account(rt_rq))
			rt_rq->rt_समय += delta_exec;
		raw_spin_unlock(&rt_rq->rt_runसमय_lock);
	पूर्ण
पूर्ण

अटल क्रमागत hrसमयr_restart inactive_task_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा sched_dl_entity *dl_se = container_of(समयr,
						     काष्ठा sched_dl_entity,
						     inactive_समयr);
	काष्ठा task_काष्ठा *p = dl_task_of(dl_se);
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	rq = task_rq_lock(p, &rf);

	sched_घड़ी_प्रकारick();
	update_rq_घड़ी(rq);

	अगर (!dl_task(p) || p->state == TASK_DEAD) अणु
		काष्ठा dl_bw *dl_b = dl_bw_of(task_cpu(p));

		अगर (p->state == TASK_DEAD && dl_se->dl_non_contending) अणु
			sub_running_bw(&p->dl, dl_rq_of_se(&p->dl));
			sub_rq_bw(&p->dl, dl_rq_of_se(&p->dl));
			dl_se->dl_non_contending = 0;
		पूर्ण

		raw_spin_lock(&dl_b->lock);
		__dl_sub(dl_b, p->dl.dl_bw, dl_bw_cpus(task_cpu(p)));
		raw_spin_unlock(&dl_b->lock);
		__dl_clear_params(p);

		जाओ unlock;
	पूर्ण
	अगर (dl_se->dl_non_contending == 0)
		जाओ unlock;

	sub_running_bw(dl_se, &rq->dl);
	dl_se->dl_non_contending = 0;
unlock:
	task_rq_unlock(rq, p, &rf);
	put_task_काष्ठा(p);

	वापस HRTIMER_NORESTART;
पूर्ण

व्योम init_dl_inactive_task_समयr(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा hrसमयr *समयr = &dl_se->inactive_समयr;

	hrसमयr_init(समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
	समयr->function = inactive_task_समयr;
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम inc_dl_deadline(काष्ठा dl_rq *dl_rq, u64 deadline)
अणु
	काष्ठा rq *rq = rq_of_dl_rq(dl_rq);

	अगर (dl_rq->earliest_dl.curr == 0 ||
	    dl_समय_beक्रमe(deadline, dl_rq->earliest_dl.curr)) अणु
		अगर (dl_rq->earliest_dl.curr == 0)
			cpupri_set(&rq->rd->cpupri, rq->cpu, CPUPRI_HIGHER);
		dl_rq->earliest_dl.curr = deadline;
		cpudl_set(&rq->rd->cpudl, rq->cpu, deadline);
	पूर्ण
पूर्ण

अटल व्योम dec_dl_deadline(काष्ठा dl_rq *dl_rq, u64 deadline)
अणु
	काष्ठा rq *rq = rq_of_dl_rq(dl_rq);

	/*
	 * Since we may have हटाओd our earliest (and/or next earliest)
	 * task we must recompute them.
	 */
	अगर (!dl_rq->dl_nr_running) अणु
		dl_rq->earliest_dl.curr = 0;
		dl_rq->earliest_dl.next = 0;
		cpudl_clear(&rq->rd->cpudl, rq->cpu);
		cpupri_set(&rq->rd->cpupri, rq->cpu, rq->rt.highest_prio.curr);
	पूर्ण अन्यथा अणु
		काष्ठा rb_node *lefपंचांगost = dl_rq->root.rb_lefपंचांगost;
		काष्ठा sched_dl_entity *entry;

		entry = rb_entry(lefपंचांगost, काष्ठा sched_dl_entity, rb_node);
		dl_rq->earliest_dl.curr = entry->deadline;
		cpudl_set(&rq->rd->cpudl, rq->cpu, entry->deadline);
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम inc_dl_deadline(काष्ठा dl_rq *dl_rq, u64 deadline) अणुपूर्ण
अटल अंतरभूत व्योम dec_dl_deadline(काष्ठा dl_rq *dl_rq, u64 deadline) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल अंतरभूत
व्योम inc_dl_tasks(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
	पूर्णांक prio = dl_task_of(dl_se)->prio;
	u64 deadline = dl_se->deadline;

	WARN_ON(!dl_prio(prio));
	dl_rq->dl_nr_running++;
	add_nr_running(rq_of_dl_rq(dl_rq), 1);

	inc_dl_deadline(dl_rq, deadline);
	inc_dl_migration(dl_se, dl_rq);
पूर्ण

अटल अंतरभूत
व्योम dec_dl_tasks(काष्ठा sched_dl_entity *dl_se, काष्ठा dl_rq *dl_rq)
अणु
	पूर्णांक prio = dl_task_of(dl_se)->prio;

	WARN_ON(!dl_prio(prio));
	WARN_ON(!dl_rq->dl_nr_running);
	dl_rq->dl_nr_running--;
	sub_nr_running(rq_of_dl_rq(dl_rq), 1);

	dec_dl_deadline(dl_rq, dl_se->deadline);
	dec_dl_migration(dl_se, dl_rq);
पूर्ण

#घोषणा __node_2_dle(node) \
	rb_entry((node), काष्ठा sched_dl_entity, rb_node)

अटल अंतरभूत bool __dl_less(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	वापस dl_समय_beक्रमe(__node_2_dle(a)->deadline, __node_2_dle(b)->deadline);
पूर्ण

अटल व्योम __enqueue_dl_entity(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा dl_rq *dl_rq = dl_rq_of_se(dl_se);

	BUG_ON(!RB_EMPTY_NODE(&dl_se->rb_node));

	rb_add_cached(&dl_se->rb_node, &dl_rq->root, __dl_less);

	inc_dl_tasks(dl_se, dl_rq);
पूर्ण

अटल व्योम __dequeue_dl_entity(काष्ठा sched_dl_entity *dl_se)
अणु
	काष्ठा dl_rq *dl_rq = dl_rq_of_se(dl_se);

	अगर (RB_EMPTY_NODE(&dl_se->rb_node))
		वापस;

	rb_erase_cached(&dl_se->rb_node, &dl_rq->root);

	RB_CLEAR_NODE(&dl_se->rb_node);

	dec_dl_tasks(dl_se, dl_rq);
पूर्ण

अटल व्योम
enqueue_dl_entity(काष्ठा sched_dl_entity *dl_se, पूर्णांक flags)
अणु
	BUG_ON(on_dl_rq(dl_se));

	/*
	 * If this is a wakeup or a new instance, the scheduling
	 * parameters of the task might need updating. Otherwise,
	 * we want a replenishment of its runसमय.
	 */
	अगर (flags & ENQUEUE_WAKEUP) अणु
		task_contending(dl_se, flags);
		update_dl_entity(dl_se);
	पूर्ण अन्यथा अगर (flags & ENQUEUE_REPLENISH) अणु
		replenish_dl_entity(dl_se);
	पूर्ण अन्यथा अगर ((flags & ENQUEUE_RESTORE) &&
		  dl_समय_beक्रमe(dl_se->deadline,
				 rq_घड़ी(rq_of_dl_rq(dl_rq_of_se(dl_se))))) अणु
		setup_new_dl_entity(dl_se);
	पूर्ण

	__enqueue_dl_entity(dl_se);
पूर्ण

अटल व्योम dequeue_dl_entity(काष्ठा sched_dl_entity *dl_se)
अणु
	__dequeue_dl_entity(dl_se);
पूर्ण

अटल व्योम enqueue_task_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	अगर (is_dl_boosted(&p->dl)) अणु
		/*
		 * Because of delays in the detection of the overrun of a
		 * thपढ़ो's runसमय, it might be the हाल that a thपढ़ो
		 * goes to sleep in a rt mutex with negative runसमय. As
		 * a consequence, the thपढ़ो will be throttled.
		 *
		 * While रुकोing क्रम the mutex, this thपढ़ो can also be
		 * boosted via PI, resulting in a thपढ़ो that is throttled
		 * and boosted at the same समय.
		 *
		 * In this हाल, the boost overrides the throttle.
		 */
		अगर (p->dl.dl_throttled) अणु
			/*
			 * The replenish समयr needs to be canceled. No
			 * problem अगर it fires concurrently: boosted thपढ़ोs
			 * are ignored in dl_task_समयr().
			 */
			hrसमयr_try_to_cancel(&p->dl.dl_समयr);
			p->dl.dl_throttled = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!dl_prio(p->normal_prio)) अणु
		/*
		 * Special हाल in which we have a !SCHED_DEADLINE task that is going
		 * to be deboosted, but exceeds its runसमय जबतक करोing so. No poपूर्णांक in
		 * replenishing it, as it's going to वापस back to its original
		 * scheduling class after this. If it has been throttled, we need to
		 * clear the flag, otherwise the task may wake up as throttled after
		 * being boosted again with no means to replenish the runसमय and clear
		 * the throttle.
		 */
		p->dl.dl_throttled = 0;
		BUG_ON(!is_dl_boosted(&p->dl) || flags != ENQUEUE_REPLENISH);
		वापस;
	पूर्ण

	/*
	 * Check अगर a स्थिरrained deadline task was activated
	 * after the deadline but beक्रमe the next period.
	 * If that is the हाल, the task will be throttled and
	 * the replenishment समयr will be set to the next period.
	 */
	अगर (!p->dl.dl_throttled && !dl_is_implicit(&p->dl))
		dl_check_स्थिरrained_dl(&p->dl);

	अगर (p->on_rq == TASK_ON_RQ_MIGRATING || flags & ENQUEUE_RESTORE) अणु
		add_rq_bw(&p->dl, &rq->dl);
		add_running_bw(&p->dl, &rq->dl);
	पूर्ण

	/*
	 * If p is throttled, we करो not enqueue it. In fact, अगर it exhausted
	 * its budget it needs a replenishment and, since it now is on
	 * its rq, the bandwidth समयr callback (which clearly has not
	 * run yet) will take care of this.
	 * However, the active utilization करोes not depend on the fact
	 * that the task is on the runqueue or not (but depends on the
	 * task's state - in GRUB parlance, "inactive" vs "active contending").
	 * In other words, even अगर a task is throttled its utilization must
	 * be counted in the active utilization; hence, we need to call
	 * add_running_bw().
	 */
	अगर (p->dl.dl_throttled && !(flags & ENQUEUE_REPLENISH)) अणु
		अगर (flags & ENQUEUE_WAKEUP)
			task_contending(&p->dl, flags);

		वापस;
	पूर्ण

	enqueue_dl_entity(&p->dl, flags);

	अगर (!task_current(rq, p) && p->nr_cpus_allowed > 1)
		enqueue_pushable_dl_task(rq, p);
पूर्ण

अटल व्योम __dequeue_task_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	dequeue_dl_entity(&p->dl);
	dequeue_pushable_dl_task(rq, p);
पूर्ण

अटल व्योम dequeue_task_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	update_curr_dl(rq);
	__dequeue_task_dl(rq, p, flags);

	अगर (p->on_rq == TASK_ON_RQ_MIGRATING || flags & DEQUEUE_SAVE) अणु
		sub_running_bw(&p->dl, &rq->dl);
		sub_rq_bw(&p->dl, &rq->dl);
	पूर्ण

	/*
	 * This check allows to start the inactive समयr (or to immediately
	 * decrease the active utilization, अगर needed) in two हालs:
	 * when the task blocks and when it is terminating
	 * (p->state == TASK_DEAD). We can handle the two हालs in the same
	 * way, because from GRUB's poपूर्णांक of view the same thing is happening
	 * (the task moves from "active contending" to "active non contending"
	 * or "inactive")
	 */
	अगर (flags & DEQUEUE_SLEEP)
		task_non_contending(p);
पूर्ण

/*
 * Yield task semantic क्रम -deadline tasks is:
 *
 *   get off from the CPU until our next instance, with
 *   a new runसमय. This is of little use now, since we
 *   करोn't have a bandwidth reclaiming mechanism. Anyway,
 *   bandwidth reclaiming is planned क्रम the future, and
 *   yield_task_dl will indicate that some spare budget
 *   is available क्रम other task instances to use it.
 */
अटल व्योम yield_task_dl(काष्ठा rq *rq)
अणु
	/*
	 * We make the task go to sleep until its current deadline by
	 * क्रमcing its runसमय to zero. This way, update_curr_dl() stops
	 * it and the bandwidth समयr will wake it up and will give it
	 * new scheduling parameters (thanks to dl_yielded=1).
	 */
	rq->curr->dl.dl_yielded = 1;

	update_rq_घड़ी(rq);
	update_curr_dl(rq);
	/*
	 * Tell update_rq_घड़ी() that we've just updated,
	 * so we करोn't करो microscopic update in schedule()
	 * and द्विगुन the fastpath cost.
	 */
	rq_घड़ी_skip_update(rq);
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल पूर्णांक find_later_rq(काष्ठा task_काष्ठा *task);

अटल पूर्णांक
select_task_rq_dl(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *curr;
	bool select_rq;
	काष्ठा rq *rq;

	अगर (!(flags & WF_TTWU))
		जाओ out;

	rq = cpu_rq(cpu);

	rcu_पढ़ो_lock();
	curr = READ_ONCE(rq->curr); /* unlocked access */

	/*
	 * If we are dealing with a -deadline task, we must
	 * decide where to wake it up.
	 * If it has a later deadline and the current task
	 * on this rq can't move (provided the waking task
	 * can!) we prefer to send it somewhere अन्यथा. On the
	 * other hand, अगर it has a लघुer deadline, we
	 * try to make it stay here, it might be important.
	 */
	select_rq = unlikely(dl_task(curr)) &&
		    (curr->nr_cpus_allowed < 2 ||
		     !dl_entity_preempt(&p->dl, &curr->dl)) &&
		    p->nr_cpus_allowed > 1;

	/*
	 * Take the capacity of the CPU पूर्णांकo account to
	 * ensure it fits the requirement of the task.
	 */
	अगर (अटल_branch_unlikely(&sched_asym_cpucapacity))
		select_rq |= !dl_task_fits_capacity(p, cpu);

	अगर (select_rq) अणु
		पूर्णांक target = find_later_rq(p);

		अगर (target != -1 &&
				(dl_समय_beक्रमe(p->dl.deadline,
					cpu_rq(target)->dl.earliest_dl.curr) ||
				(cpu_rq(target)->dl.dl_nr_running == 0)))
			cpu = target;
	पूर्ण
	rcu_पढ़ो_unlock();

out:
	वापस cpu;
पूर्ण

अटल व्योम migrate_task_rq_dl(काष्ठा task_काष्ठा *p, पूर्णांक new_cpu __maybe_unused)
अणु
	काष्ठा rq *rq;

	अगर (p->state != TASK_WAKING)
		वापस;

	rq = task_rq(p);
	/*
	 * Since p->state == TASK_WAKING, set_task_cpu() has been called
	 * from try_to_wake_up(). Hence, p->pi_lock is locked, but
	 * rq->lock is not... So, lock it
	 */
	raw_spin_lock(&rq->lock);
	अगर (p->dl.dl_non_contending) अणु
		sub_running_bw(&p->dl, &rq->dl);
		p->dl.dl_non_contending = 0;
		/*
		 * If the समयr handler is currently running and the
		 * समयr cannot be canceled, inactive_task_समयr()
		 * will see that dl_not_contending is not set, and
		 * will not touch the rq's active utilization,
		 * so we are still safe.
		 */
		अगर (hrसमयr_try_to_cancel(&p->dl.inactive_समयr) == 1)
			put_task_काष्ठा(p);
	पूर्ण
	sub_rq_bw(&p->dl, &rq->dl);
	raw_spin_unlock(&rq->lock);
पूर्ण

अटल व्योम check_preempt_equal_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	/*
	 * Current can't be migrated, useless to reschedule,
	 * let's hope p can move out.
	 */
	अगर (rq->curr->nr_cpus_allowed == 1 ||
	    !cpudl_find(&rq->rd->cpudl, rq->curr, शून्य))
		वापस;

	/*
	 * p is migratable, so let's not schedule it and
	 * see अगर it is pushed or pulled somewhere अन्यथा.
	 */
	अगर (p->nr_cpus_allowed != 1 &&
	    cpudl_find(&rq->rd->cpudl, p, शून्य))
		वापस;

	resched_curr(rq);
पूर्ण

अटल पूर्णांक balance_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, काष्ठा rq_flags *rf)
अणु
	अगर (!on_dl_rq(&p->dl) && need_pull_dl_task(rq, p)) अणु
		/*
		 * This is OK, because current is on_cpu, which aव्योमs it being
		 * picked क्रम load-balance and preemption/IRQs are still
		 * disabled aव्योमing further scheduler activity on it and we've
		 * not yet started the picking loop.
		 */
		rq_unpin_lock(rq, rf);
		pull_dl_task(rq);
		rq_repin_lock(rq, rf);
	पूर्ण

	वापस sched_stop_runnable(rq) || sched_dl_runnable(rq);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Only called when both the current and waking task are -deadline
 * tasks.
 */
अटल व्योम check_preempt_curr_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p,
				  पूर्णांक flags)
अणु
	अगर (dl_entity_preempt(&p->dl, &rq->curr->dl)) अणु
		resched_curr(rq);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_SMP
	/*
	 * In the unlikely हाल current and p have the same deadline
	 * let us try to decide what's the best thing to करो...
	 */
	अगर ((p->dl.deadline == rq->curr->dl.deadline) &&
	    !test_tsk_need_resched(rq->curr))
		check_preempt_equal_dl(rq, p);
#पूर्ण_अगर /* CONFIG_SMP */
पूर्ण

#अगर_घोषित CONFIG_SCHED_HRTICK
अटल व्योम start_hrtick_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	hrtick_start(rq, p->dl.runसमय);
पूर्ण
#अन्यथा /* !CONFIG_SCHED_HRTICK */
अटल व्योम start_hrtick_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम set_next_task_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, bool first)
अणु
	p->se.exec_start = rq_घड़ी_प्रकारask(rq);

	/* You can't push away the running task */
	dequeue_pushable_dl_task(rq, p);

	अगर (!first)
		वापस;

	अगर (hrtick_enabled_dl(rq))
		start_hrtick_dl(rq, p);

	अगर (rq->curr->sched_class != &dl_sched_class)
		update_dl_rq_load_avg(rq_घड़ी_pelt(rq), rq, 0);

	deadline_queue_push_tasks(rq);
पूर्ण

अटल काष्ठा sched_dl_entity *pick_next_dl_entity(काष्ठा rq *rq,
						   काष्ठा dl_rq *dl_rq)
अणु
	काष्ठा rb_node *left = rb_first_cached(&dl_rq->root);

	अगर (!left)
		वापस शून्य;

	वापस rb_entry(left, काष्ठा sched_dl_entity, rb_node);
पूर्ण

अटल काष्ठा task_काष्ठा *pick_next_task_dl(काष्ठा rq *rq)
अणु
	काष्ठा sched_dl_entity *dl_se;
	काष्ठा dl_rq *dl_rq = &rq->dl;
	काष्ठा task_काष्ठा *p;

	अगर (!sched_dl_runnable(rq))
		वापस शून्य;

	dl_se = pick_next_dl_entity(rq, dl_rq);
	BUG_ON(!dl_se);
	p = dl_task_of(dl_se);
	set_next_task_dl(rq, p, true);
	वापस p;
पूर्ण

अटल व्योम put_prev_task_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	update_curr_dl(rq);

	update_dl_rq_load_avg(rq_घड़ी_pelt(rq), rq, 1);
	अगर (on_dl_rq(&p->dl) && p->nr_cpus_allowed > 1)
		enqueue_pushable_dl_task(rq, p);
पूर्ण

/*
 * scheduler tick hitting a task of our scheduling class.
 *
 * NOTE: This function can be called remotely by the tick offload that
 * goes aदीर्घ full dynticks. Thereक्रमe no local assumption can be made
 * and everything must be accessed through the @rq and @curr passed in
 * parameters.
 */
अटल व्योम task_tick_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक queued)
अणु
	update_curr_dl(rq);

	update_dl_rq_load_avg(rq_घड़ी_pelt(rq), rq, 1);
	/*
	 * Even when we have runसमय, update_curr_dl() might have resulted in us
	 * not being the lefपंचांगost task anymore. In that हाल NEED_RESCHED will
	 * be set and schedule() will start a new hrtick क्रम the next task.
	 */
	अगर (hrtick_enabled_dl(rq) && queued && p->dl.runसमय > 0 &&
	    is_lefपंचांगost(p, &rq->dl))
		start_hrtick_dl(rq, p);
पूर्ण

अटल व्योम task_विभाजन_dl(काष्ठा task_काष्ठा *p)
अणु
	/*
	 * SCHED_DEADLINE tasks cannot विभाजन and this is achieved through
	 * sched_विभाजन()
	 */
पूर्ण

#अगर_घोषित CONFIG_SMP

/* Only try algorithms three बार */
#घोषणा DL_MAX_TRIES 3

अटल पूर्णांक pick_dl_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक cpu)
अणु
	अगर (!task_running(rq, p) &&
	    cpumask_test_cpu(cpu, &p->cpus_mask))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Return the earliest pushable rq's task, which is suitable to be executed
 * on the CPU, शून्य otherwise:
 */
अटल काष्ठा task_काष्ठा *pick_earliest_pushable_dl_task(काष्ठा rq *rq, पूर्णांक cpu)
अणु
	काष्ठा rb_node *next_node = rq->dl.pushable_dl_tasks_root.rb_lefपंचांगost;
	काष्ठा task_काष्ठा *p = शून्य;

	अगर (!has_pushable_dl_tasks(rq))
		वापस शून्य;

next_node:
	अगर (next_node) अणु
		p = rb_entry(next_node, काष्ठा task_काष्ठा, pushable_dl_tasks);

		अगर (pick_dl_task(rq, p, cpu))
			वापस p;

		next_node = rb_next(next_node);
		जाओ next_node;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल DEFINE_PER_CPU(cpumask_var_t, local_cpu_mask_dl);

अटल पूर्णांक find_later_rq(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा sched_करोमुख्य *sd;
	काष्ठा cpumask *later_mask = this_cpu_cpumask_var_ptr(local_cpu_mask_dl);
	पूर्णांक this_cpu = smp_processor_id();
	पूर्णांक cpu = task_cpu(task);

	/* Make sure the mask is initialized first */
	अगर (unlikely(!later_mask))
		वापस -1;

	अगर (task->nr_cpus_allowed == 1)
		वापस -1;

	/*
	 * We have to consider प्रणाली topology and task affinity
	 * first, then we can look क्रम a suitable CPU.
	 */
	अगर (!cpudl_find(&task_rq(task)->rd->cpudl, task, later_mask))
		वापस -1;

	/*
	 * If we are here, some tarमाला_लो have been found, including
	 * the most suitable which is, among the runqueues where the
	 * current tasks have later deadlines than the task's one, the
	 * rq with the latest possible one.
	 *
	 * Now we check how well this matches with task's
	 * affinity and प्रणाली topology.
	 *
	 * The last CPU where the task run is our first
	 * guess, since it is most likely cache-hot there.
	 */
	अगर (cpumask_test_cpu(cpu, later_mask))
		वापस cpu;
	/*
	 * Check अगर this_cpu is to be skipped (i.e., it is
	 * not in the mask) or not.
	 */
	अगर (!cpumask_test_cpu(this_cpu, later_mask))
		this_cpu = -1;

	rcu_पढ़ो_lock();
	क्रम_each_करोमुख्य(cpu, sd) अणु
		अगर (sd->flags & SD_WAKE_AFFINE) अणु
			पूर्णांक best_cpu;

			/*
			 * If possible, preempting this_cpu is
			 * cheaper than migrating.
			 */
			अगर (this_cpu != -1 &&
			    cpumask_test_cpu(this_cpu, sched_करोमुख्य_span(sd))) अणु
				rcu_पढ़ो_unlock();
				वापस this_cpu;
			पूर्ण

			best_cpu = cpumask_any_and_distribute(later_mask,
							      sched_करोमुख्य_span(sd));
			/*
			 * Last chance: अगर a CPU being in both later_mask
			 * and current sd span is valid, that becomes our
			 * choice. Of course, the latest possible CPU is
			 * alपढ़ोy under consideration through later_mask.
			 */
			अगर (best_cpu < nr_cpu_ids) अणु
				rcu_पढ़ो_unlock();
				वापस best_cpu;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * At this poपूर्णांक, all our guesses failed, we just वापस
	 * 'something', and let the caller sort the things out.
	 */
	अगर (this_cpu != -1)
		वापस this_cpu;

	cpu = cpumask_any_distribute(later_mask);
	अगर (cpu < nr_cpu_ids)
		वापस cpu;

	वापस -1;
पूर्ण

/* Locks the rq it finds */
अटल काष्ठा rq *find_lock_later_rq(काष्ठा task_काष्ठा *task, काष्ठा rq *rq)
अणु
	काष्ठा rq *later_rq = शून्य;
	पूर्णांक tries;
	पूर्णांक cpu;

	क्रम (tries = 0; tries < DL_MAX_TRIES; tries++) अणु
		cpu = find_later_rq(task);

		अगर ((cpu == -1) || (cpu == rq->cpu))
			अवरोध;

		later_rq = cpu_rq(cpu);

		अगर (later_rq->dl.dl_nr_running &&
		    !dl_समय_beक्रमe(task->dl.deadline,
					later_rq->dl.earliest_dl.curr)) अणु
			/*
			 * Target rq has tasks of equal or earlier deadline,
			 * retrying करोes not release any lock and is unlikely
			 * to yield a dअगरferent result.
			 */
			later_rq = शून्य;
			अवरोध;
		पूर्ण

		/* Retry अगर something changed. */
		अगर (द्विगुन_lock_balance(rq, later_rq)) अणु
			अगर (unlikely(task_rq(task) != rq ||
				     !cpumask_test_cpu(later_rq->cpu, &task->cpus_mask) ||
				     task_running(rq, task) ||
				     !dl_task(task) ||
				     !task_on_rq_queued(task))) अणु
				द्विगुन_unlock_balance(rq, later_rq);
				later_rq = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * If the rq we found has no -deadline task, or
		 * its earliest one has a later deadline than our
		 * task, the rq is a good one.
		 */
		अगर (!later_rq->dl.dl_nr_running ||
		    dl_समय_beक्रमe(task->dl.deadline,
				   later_rq->dl.earliest_dl.curr))
			अवरोध;

		/* Otherwise we try again. */
		द्विगुन_unlock_balance(rq, later_rq);
		later_rq = शून्य;
	पूर्ण

	वापस later_rq;
पूर्ण

अटल काष्ठा task_काष्ठा *pick_next_pushable_dl_task(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *p;

	अगर (!has_pushable_dl_tasks(rq))
		वापस शून्य;

	p = rb_entry(rq->dl.pushable_dl_tasks_root.rb_lefपंचांगost,
		     काष्ठा task_काष्ठा, pushable_dl_tasks);

	BUG_ON(rq->cpu != task_cpu(p));
	BUG_ON(task_current(rq, p));
	BUG_ON(p->nr_cpus_allowed <= 1);

	BUG_ON(!task_on_rq_queued(p));
	BUG_ON(!dl_task(p));

	वापस p;
पूर्ण

/*
 * See अगर the non running -deadline tasks on this rq
 * can be sent to some other CPU where they can preempt
 * and start executing.
 */
अटल पूर्णांक push_dl_task(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *next_task;
	काष्ठा rq *later_rq;
	पूर्णांक ret = 0;

	अगर (!rq->dl.overloaded)
		वापस 0;

	next_task = pick_next_pushable_dl_task(rq);
	अगर (!next_task)
		वापस 0;

retry:
	अगर (is_migration_disabled(next_task))
		वापस 0;

	अगर (WARN_ON(next_task == rq->curr))
		वापस 0;

	/*
	 * If next_task preempts rq->curr, and rq->curr
	 * can move away, it makes sense to just reschedule
	 * without going further in pushing next_task.
	 */
	अगर (dl_task(rq->curr) &&
	    dl_समय_beक्रमe(next_task->dl.deadline, rq->curr->dl.deadline) &&
	    rq->curr->nr_cpus_allowed > 1) अणु
		resched_curr(rq);
		वापस 0;
	पूर्ण

	/* We might release rq lock */
	get_task_काष्ठा(next_task);

	/* Will lock the rq it'll find */
	later_rq = find_lock_later_rq(next_task, rq);
	अगर (!later_rq) अणु
		काष्ठा task_काष्ठा *task;

		/*
		 * We must check all this again, since
		 * find_lock_later_rq releases rq->lock and it is
		 * then possible that next_task has migrated.
		 */
		task = pick_next_pushable_dl_task(rq);
		अगर (task == next_task) अणु
			/*
			 * The task is still there. We करोn't try
			 * again, some other CPU will pull it when पढ़ोy.
			 */
			जाओ out;
		पूर्ण

		अगर (!task)
			/* No more tasks */
			जाओ out;

		put_task_काष्ठा(next_task);
		next_task = task;
		जाओ retry;
	पूर्ण

	deactivate_task(rq, next_task, 0);
	set_task_cpu(next_task, later_rq->cpu);

	/*
	 * Update the later_rq घड़ी here, because the घड़ी is used
	 * by the cpufreq_update_util() inside __add_running_bw().
	 */
	update_rq_घड़ी(later_rq);
	activate_task(later_rq, next_task, ENQUEUE_NOCLOCK);
	ret = 1;

	resched_curr(later_rq);

	द्विगुन_unlock_balance(rq, later_rq);

out:
	put_task_काष्ठा(next_task);

	वापस ret;
पूर्ण

अटल व्योम push_dl_tasks(काष्ठा rq *rq)
अणु
	/* push_dl_task() will वापस true अगर it moved a -deadline task */
	जबतक (push_dl_task(rq))
		;
पूर्ण

अटल व्योम pull_dl_task(काष्ठा rq *this_rq)
अणु
	पूर्णांक this_cpu = this_rq->cpu, cpu;
	काष्ठा task_काष्ठा *p, *push_task;
	bool resched = false;
	काष्ठा rq *src_rq;
	u64 dmin = दीर्घ_उच्च;

	अगर (likely(!dl_overloaded(this_rq)))
		वापस;

	/*
	 * Match the barrier from dl_set_overloaded; this guarantees that अगर we
	 * see overloaded we must also see the dlo_mask bit.
	 */
	smp_rmb();

	क्रम_each_cpu(cpu, this_rq->rd->dlo_mask) अणु
		अगर (this_cpu == cpu)
			जारी;

		src_rq = cpu_rq(cpu);

		/*
		 * It looks racy, abd it is! However, as in sched_rt.c,
		 * we are fine with this.
		 */
		अगर (this_rq->dl.dl_nr_running &&
		    dl_समय_beक्रमe(this_rq->dl.earliest_dl.curr,
				   src_rq->dl.earliest_dl.next))
			जारी;

		/* Might drop this_rq->lock */
		push_task = शून्य;
		द्विगुन_lock_balance(this_rq, src_rq);

		/*
		 * If there are no more pullable tasks on the
		 * rq, we're करोne with it.
		 */
		अगर (src_rq->dl.dl_nr_running <= 1)
			जाओ skip;

		p = pick_earliest_pushable_dl_task(src_rq, this_cpu);

		/*
		 * We found a task to be pulled अगर:
		 *  - it preempts our current (अगर there's one),
		 *  - it will preempt the last one we pulled (अगर any).
		 */
		अगर (p && dl_समय_beक्रमe(p->dl.deadline, dmin) &&
		    (!this_rq->dl.dl_nr_running ||
		     dl_समय_beक्रमe(p->dl.deadline,
				    this_rq->dl.earliest_dl.curr))) अणु
			WARN_ON(p == src_rq->curr);
			WARN_ON(!task_on_rq_queued(p));

			/*
			 * Then we pull अगरf p has actually an earlier
			 * deadline than the current task of its runqueue.
			 */
			अगर (dl_समय_beक्रमe(p->dl.deadline,
					   src_rq->curr->dl.deadline))
				जाओ skip;

			अगर (is_migration_disabled(p)) अणु
				push_task = get_push_task(src_rq);
			पूर्ण अन्यथा अणु
				deactivate_task(src_rq, p, 0);
				set_task_cpu(p, this_cpu);
				activate_task(this_rq, p, 0);
				dmin = p->dl.deadline;
				resched = true;
			पूर्ण

			/* Is there any other task even earlier? */
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
 * Since the task is not running and a reschedule is not going to happen
 * anyसमय soon on its runqueue, we try pushing it away now.
 */
अटल व्योम task_woken_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	अगर (!task_running(rq, p) &&
	    !test_tsk_need_resched(rq->curr) &&
	    p->nr_cpus_allowed > 1 &&
	    dl_task(rq->curr) &&
	    (rq->curr->nr_cpus_allowed < 2 ||
	     !dl_entity_preempt(&p->dl, &rq->curr->dl))) अणु
		push_dl_tasks(rq);
	पूर्ण
पूर्ण

अटल व्योम set_cpus_allowed_dl(काष्ठा task_काष्ठा *p,
				स्थिर काष्ठा cpumask *new_mask,
				u32 flags)
अणु
	काष्ठा root_करोमुख्य *src_rd;
	काष्ठा rq *rq;

	BUG_ON(!dl_task(p));

	rq = task_rq(p);
	src_rd = rq->rd;
	/*
	 * Migrating a SCHED_DEADLINE task between exclusive
	 * cpusets (dअगरferent root_करोमुख्यs) entails a bandwidth
	 * update. We alपढ़ोy made space क्रम us in the destination
	 * करोमुख्य (see cpuset_can_attach()).
	 */
	अगर (!cpumask_पूर्णांकersects(src_rd->span, new_mask)) अणु
		काष्ठा dl_bw *src_dl_b;

		src_dl_b = dl_bw_of(cpu_of(rq));
		/*
		 * We now मुक्त resources of the root_करोमुख्य we are migrating
		 * off. In the worst हाल, sched_setattr() may temporary fail
		 * until we complete the update.
		 */
		raw_spin_lock(&src_dl_b->lock);
		__dl_sub(src_dl_b, p->dl.dl_bw, dl_bw_cpus(task_cpu(p)));
		raw_spin_unlock(&src_dl_b->lock);
	पूर्ण

	set_cpus_allowed_common(p, new_mask, flags);
पूर्ण

/* Assumes rq->lock is held */
अटल व्योम rq_online_dl(काष्ठा rq *rq)
अणु
	अगर (rq->dl.overloaded)
		dl_set_overload(rq);

	cpudl_set_मुक्तcpu(&rq->rd->cpudl, rq->cpu);
	अगर (rq->dl.dl_nr_running > 0)
		cpudl_set(&rq->rd->cpudl, rq->cpu, rq->dl.earliest_dl.curr);
पूर्ण

/* Assumes rq->lock is held */
अटल व्योम rq_offline_dl(काष्ठा rq *rq)
अणु
	अगर (rq->dl.overloaded)
		dl_clear_overload(rq);

	cpudl_clear(&rq->rd->cpudl, rq->cpu);
	cpudl_clear_मुक्तcpu(&rq->rd->cpudl, rq->cpu);
पूर्ण

व्योम __init init_sched_dl_class(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_possible_cpu(i)
		zalloc_cpumask_var_node(&per_cpu(local_cpu_mask_dl, i),
					GFP_KERNEL, cpu_to_node(i));
पूर्ण

व्योम dl_add_task_root_करोमुख्य(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;
	काष्ठा dl_bw *dl_b;

	raw_spin_lock_irqsave(&p->pi_lock, rf.flags);
	अगर (!dl_task(p)) अणु
		raw_spin_unlock_irqrestore(&p->pi_lock, rf.flags);
		वापस;
	पूर्ण

	rq = __task_rq_lock(p, &rf);

	dl_b = &rq->rd->dl_bw;
	raw_spin_lock(&dl_b->lock);

	__dl_add(dl_b, p->dl.dl_bw, cpumask_weight(rq->rd->span));

	raw_spin_unlock(&dl_b->lock);

	task_rq_unlock(rq, p, &rf);
पूर्ण

व्योम dl_clear_root_करोमुख्य(काष्ठा root_करोमुख्य *rd)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&rd->dl_bw.lock, flags);
	rd->dl_bw.total_bw = 0;
	raw_spin_unlock_irqrestore(&rd->dl_bw.lock, flags);
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम चयनed_from_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	/*
	 * task_non_contending() can start the "inactive timer" (अगर the 0-lag
	 * समय is in the future). If the task चयनes back to dl beक्रमe
	 * the "inactive timer" fires, it can जारी to consume its current
	 * runसमय using its current deadline. If it stays outside of
	 * SCHED_DEADLINE until the 0-lag समय passes, inactive_task_समयr()
	 * will reset the task parameters.
	 */
	अगर (task_on_rq_queued(p) && p->dl.dl_runसमय)
		task_non_contending(p);

	अगर (!task_on_rq_queued(p)) अणु
		/*
		 * Inactive समयr is armed. However, p is leaving DEADLINE and
		 * might migrate away from this rq जबतक continuing to run on
		 * some other class. We need to हटाओ its contribution from
		 * this rq running_bw now, or sub_rq_bw (below) will complain.
		 */
		अगर (p->dl.dl_non_contending)
			sub_running_bw(&p->dl, &rq->dl);
		sub_rq_bw(&p->dl, &rq->dl);
	पूर्ण

	/*
	 * We cannot use inactive_task_समयr() to invoke sub_running_bw()
	 * at the 0-lag समय, because the task could have been migrated
	 * जबतक SCHED_OTHER in the meanजबतक.
	 */
	अगर (p->dl.dl_non_contending)
		p->dl.dl_non_contending = 0;

	/*
	 * Since this might be the only -deadline task on the rq,
	 * this is the right place to try to pull some other one
	 * from an overloaded CPU, अगर any.
	 */
	अगर (!task_on_rq_queued(p) || rq->dl.dl_nr_running)
		वापस;

	deadline_queue_pull_task(rq);
पूर्ण

/*
 * When चयनing to -deadline, we may overload the rq, then
 * we try to push someone off, अगर possible.
 */
अटल व्योम चयनed_to_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	अगर (hrसमयr_try_to_cancel(&p->dl.inactive_समयr) == 1)
		put_task_काष्ठा(p);

	/* If p is not queued we will update its parameters at next wakeup. */
	अगर (!task_on_rq_queued(p)) अणु
		add_rq_bw(&p->dl, &rq->dl);

		वापस;
	पूर्ण

	अगर (rq->curr != p) अणु
#अगर_घोषित CONFIG_SMP
		अगर (p->nr_cpus_allowed > 1 && rq->dl.overloaded)
			deadline_queue_push_tasks(rq);
#पूर्ण_अगर
		अगर (dl_task(rq->curr))
			check_preempt_curr_dl(rq, p, 0);
		अन्यथा
			resched_curr(rq);
	पूर्ण
पूर्ण

/*
 * If the scheduling parameters of a -deadline task changed,
 * a push or pull operation might be needed.
 */
अटल व्योम prio_changed_dl(काष्ठा rq *rq, काष्ठा task_काष्ठा *p,
			    पूर्णांक oldprio)
अणु
	अगर (task_on_rq_queued(p) || task_current(rq, p)) अणु
#अगर_घोषित CONFIG_SMP
		/*
		 * This might be too much, but unक्रमtunately
		 * we करोn't have the old deadline value, and
		 * we can't argue अगर the task is increasing
		 * or lowering its prio, so...
		 */
		अगर (!rq->dl.overloaded)
			deadline_queue_pull_task(rq);

		/*
		 * If we now have a earlier deadline task than p,
		 * then reschedule, provided p is still on this
		 * runqueue.
		 */
		अगर (dl_समय_beक्रमe(rq->dl.earliest_dl.curr, p->dl.deadline))
			resched_curr(rq);
#अन्यथा
		/*
		 * Again, we करोn't know अगर p has a earlier
		 * or later deadline, so let's blindly set a
		 * (maybe not needed) rescheduling poपूर्णांक.
		 */
		resched_curr(rq);
#पूर्ण_अगर /* CONFIG_SMP */
	पूर्ण
पूर्ण

DEFINE_SCHED_CLASS(dl) = अणु

	.enqueue_task		= enqueue_task_dl,
	.dequeue_task		= dequeue_task_dl,
	.yield_task		= yield_task_dl,

	.check_preempt_curr	= check_preempt_curr_dl,

	.pick_next_task		= pick_next_task_dl,
	.put_prev_task		= put_prev_task_dl,
	.set_next_task		= set_next_task_dl,

#अगर_घोषित CONFIG_SMP
	.balance		= balance_dl,
	.select_task_rq		= select_task_rq_dl,
	.migrate_task_rq	= migrate_task_rq_dl,
	.set_cpus_allowed       = set_cpus_allowed_dl,
	.rq_online              = rq_online_dl,
	.rq_offline             = rq_offline_dl,
	.task_woken		= task_woken_dl,
	.find_lock_rq		= find_lock_later_rq,
#पूर्ण_अगर

	.task_tick		= task_tick_dl,
	.task_विभाजन              = task_विभाजन_dl,

	.prio_changed           = prio_changed_dl,
	.चयनed_from		= चयनed_from_dl,
	.चयनed_to		= चयनed_to_dl,

	.update_curr		= update_curr_dl,
पूर्ण;

/* Used क्रम dl_bw check and update, used under sched_rt_handler()::mutex */
अटल u64 dl_generation;

पूर्णांक sched_dl_global_validate(व्योम)
अणु
	u64 runसमय = global_rt_runसमय();
	u64 period = global_rt_period();
	u64 new_bw = to_ratio(period, runसमय);
	u64 gen = ++dl_generation;
	काष्ठा dl_bw *dl_b;
	पूर्णांक cpu, cpus, ret = 0;
	अचिन्हित दीर्घ flags;

	/*
	 * Here we want to check the bandwidth not being set to some
	 * value smaller than the currently allocated bandwidth in
	 * any of the root_करोमुख्यs.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		rcu_पढ़ो_lock_sched();

		अगर (dl_bw_visited(cpu, gen))
			जाओ next;

		dl_b = dl_bw_of(cpu);
		cpus = dl_bw_cpus(cpu);

		raw_spin_lock_irqsave(&dl_b->lock, flags);
		अगर (new_bw * cpus < dl_b->total_bw)
			ret = -EBUSY;
		raw_spin_unlock_irqrestore(&dl_b->lock, flags);

next:
		rcu_पढ़ो_unlock_sched();

		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम init_dl_rq_bw_ratio(काष्ठा dl_rq *dl_rq)
अणु
	अगर (global_rt_runसमय() == RUNTIME_INF) अणु
		dl_rq->bw_ratio = 1 << RATIO_SHIFT;
		dl_rq->extra_bw = 1 << BW_SHIFT;
	पूर्ण अन्यथा अणु
		dl_rq->bw_ratio = to_ratio(global_rt_runसमय(),
			  global_rt_period()) >> (BW_SHIFT - RATIO_SHIFT);
		dl_rq->extra_bw = to_ratio(global_rt_period(),
						    global_rt_runसमय());
	पूर्ण
पूर्ण

व्योम sched_dl_करो_global(व्योम)
अणु
	u64 new_bw = -1;
	u64 gen = ++dl_generation;
	काष्ठा dl_bw *dl_b;
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;

	def_dl_bandwidth.dl_period = global_rt_period();
	def_dl_bandwidth.dl_runसमय = global_rt_runसमय();

	अगर (global_rt_runसमय() != RUNTIME_INF)
		new_bw = to_ratio(global_rt_period(), global_rt_runसमय());

	क्रम_each_possible_cpu(cpu) अणु
		rcu_पढ़ो_lock_sched();

		अगर (dl_bw_visited(cpu, gen)) अणु
			rcu_पढ़ो_unlock_sched();
			जारी;
		पूर्ण

		dl_b = dl_bw_of(cpu);

		raw_spin_lock_irqsave(&dl_b->lock, flags);
		dl_b->bw = new_bw;
		raw_spin_unlock_irqrestore(&dl_b->lock, flags);

		rcu_पढ़ो_unlock_sched();
		init_dl_rq_bw_ratio(&cpu_rq(cpu)->dl);
	पूर्ण
पूर्ण

/*
 * We must be sure that accepting a new task (or allowing changing the
 * parameters of an existing one) is consistent with the bandwidth
 * स्थिरraपूर्णांकs. If yes, this function also accordingly updates the currently
 * allocated bandwidth to reflect the new situation.
 *
 * This function is called जबतक holding p's rq->lock.
 */
पूर्णांक sched_dl_overflow(काष्ठा task_काष्ठा *p, पूर्णांक policy,
		      स्थिर काष्ठा sched_attr *attr)
अणु
	u64 period = attr->sched_period ?: attr->sched_deadline;
	u64 runसमय = attr->sched_runसमय;
	u64 new_bw = dl_policy(policy) ? to_ratio(period, runसमय) : 0;
	पूर्णांक cpus, err = -1, cpu = task_cpu(p);
	काष्ठा dl_bw *dl_b = dl_bw_of(cpu);
	अचिन्हित दीर्घ cap;

	अगर (attr->sched_flags & SCHED_FLAG_SUGOV)
		वापस 0;

	/* !deadline task may carry old deadline bandwidth */
	अगर (new_bw == p->dl.dl_bw && task_has_dl_policy(p))
		वापस 0;

	/*
	 * Either अगर a task, enters, leave, or stays -deadline but changes
	 * its parameters, we may need to update accordingly the total
	 * allocated bandwidth of the container.
	 */
	raw_spin_lock(&dl_b->lock);
	cpus = dl_bw_cpus(cpu);
	cap = dl_bw_capacity(cpu);

	अगर (dl_policy(policy) && !task_has_dl_policy(p) &&
	    !__dl_overflow(dl_b, cap, 0, new_bw)) अणु
		अगर (hrसमयr_active(&p->dl.inactive_समयr))
			__dl_sub(dl_b, p->dl.dl_bw, cpus);
		__dl_add(dl_b, new_bw, cpus);
		err = 0;
	पूर्ण अन्यथा अगर (dl_policy(policy) && task_has_dl_policy(p) &&
		   !__dl_overflow(dl_b, cap, p->dl.dl_bw, new_bw)) अणु
		/*
		 * XXX this is slightly incorrect: when the task
		 * utilization decreases, we should delay the total
		 * utilization change until the task's 0-lag poपूर्णांक.
		 * But this would require to set the task's "inactive
		 * समयr" when the task is not inactive.
		 */
		__dl_sub(dl_b, p->dl.dl_bw, cpus);
		__dl_add(dl_b, new_bw, cpus);
		dl_change_utilization(p, new_bw);
		err = 0;
	पूर्ण अन्यथा अगर (!dl_policy(policy) && task_has_dl_policy(p)) अणु
		/*
		 * Do not decrease the total deadline utilization here,
		 * चयनed_from_dl() will take care to करो it at the correct
		 * (0-lag) समय.
		 */
		err = 0;
	पूर्ण
	raw_spin_unlock(&dl_b->lock);

	वापस err;
पूर्ण

/*
 * This function initializes the sched_dl_entity of a newly becoming
 * SCHED_DEADLINE task.
 *
 * Only the अटल values are considered here, the actual runसमय and the
 * असलolute deadline will be properly calculated when the task is enqueued
 * क्रम the first समय with its new policy.
 */
व्योम __setparam_dl(काष्ठा task_काष्ठा *p, स्थिर काष्ठा sched_attr *attr)
अणु
	काष्ठा sched_dl_entity *dl_se = &p->dl;

	dl_se->dl_runसमय = attr->sched_runसमय;
	dl_se->dl_deadline = attr->sched_deadline;
	dl_se->dl_period = attr->sched_period ?: dl_se->dl_deadline;
	dl_se->flags = attr->sched_flags;
	dl_se->dl_bw = to_ratio(dl_se->dl_period, dl_se->dl_runसमय);
	dl_se->dl_density = to_ratio(dl_se->dl_deadline, dl_se->dl_runसमय);
पूर्ण

व्योम __getparam_dl(काष्ठा task_काष्ठा *p, काष्ठा sched_attr *attr)
अणु
	काष्ठा sched_dl_entity *dl_se = &p->dl;

	attr->sched_priority = p->rt_priority;
	attr->sched_runसमय = dl_se->dl_runसमय;
	attr->sched_deadline = dl_se->dl_deadline;
	attr->sched_period = dl_se->dl_period;
	attr->sched_flags = dl_se->flags;
पूर्ण

/*
 * Default limits क्रम DL period; on the top end we guard against small util
 * tasks still getting ridiculously दीर्घ effective runबार, on the bottom end we
 * guard against समयr DoS.
 */
अचिन्हित पूर्णांक sysctl_sched_dl_period_max = 1 << 22; /* ~4 seconds */
अचिन्हित पूर्णांक sysctl_sched_dl_period_min = 100;     /* 100 us */

/*
 * This function validates the new parameters of a -deadline task.
 * We ask क्रम the deadline not being zero, and greater or equal
 * than the runसमय, as well as the period of being zero or
 * greater than deadline. Furthermore, we have to be sure that
 * user parameters are above the पूर्णांकernal resolution of 1us (we
 * check sched_runसमय only since it is always the smaller one) and
 * below 2^63 ns (we have to check both sched_deadline and
 * sched_period, as the latter can be zero).
 */
bool __checkparam_dl(स्थिर काष्ठा sched_attr *attr)
अणु
	u64 period, max, min;

	/* special dl tasks करोn't actually use any parameter */
	अगर (attr->sched_flags & SCHED_FLAG_SUGOV)
		वापस true;

	/* deadline != 0 */
	अगर (attr->sched_deadline == 0)
		वापस false;

	/*
	 * Since we truncate DL_SCALE bits, make sure we're at least
	 * that big.
	 */
	अगर (attr->sched_runसमय < (1ULL << DL_SCALE))
		वापस false;

	/*
	 * Since we use the MSB क्रम wrap-around and sign issues, make
	 * sure it's not set (mind that period can be equal to zero).
	 */
	अगर (attr->sched_deadline & (1ULL << 63) ||
	    attr->sched_period & (1ULL << 63))
		वापस false;

	period = attr->sched_period;
	अगर (!period)
		period = attr->sched_deadline;

	/* runसमय <= deadline <= period (अगर period != 0) */
	अगर (period < attr->sched_deadline ||
	    attr->sched_deadline < attr->sched_runसमय)
		वापस false;

	max = (u64)READ_ONCE(sysctl_sched_dl_period_max) * NSEC_PER_USEC;
	min = (u64)READ_ONCE(sysctl_sched_dl_period_min) * NSEC_PER_USEC;

	अगर (period < min || period > max)
		वापस false;

	वापस true;
पूर्ण

/*
 * This function clears the sched_dl_entity अटल params.
 */
व्योम __dl_clear_params(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_dl_entity *dl_se = &p->dl;

	dl_se->dl_runसमय		= 0;
	dl_se->dl_deadline		= 0;
	dl_se->dl_period		= 0;
	dl_se->flags			= 0;
	dl_se->dl_bw			= 0;
	dl_se->dl_density		= 0;

	dl_se->dl_throttled		= 0;
	dl_se->dl_yielded		= 0;
	dl_se->dl_non_contending	= 0;
	dl_se->dl_overrun		= 0;

#अगर_घोषित CONFIG_RT_MUTEXES
	dl_se->pi_se			= dl_se;
#पूर्ण_अगर
पूर्ण

bool dl_param_changed(काष्ठा task_काष्ठा *p, स्थिर काष्ठा sched_attr *attr)
अणु
	काष्ठा sched_dl_entity *dl_se = &p->dl;

	अगर (dl_se->dl_runसमय != attr->sched_runसमय ||
	    dl_se->dl_deadline != attr->sched_deadline ||
	    dl_se->dl_period != attr->sched_period ||
	    dl_se->flags != attr->sched_flags)
		वापस true;

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_SMP
पूर्णांक dl_task_can_attach(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *cs_cpus_allowed)
अणु
	अचिन्हित दीर्घ flags, cap;
	अचिन्हित पूर्णांक dest_cpu;
	काष्ठा dl_bw *dl_b;
	bool overflow;
	पूर्णांक ret;

	dest_cpu = cpumask_any_and(cpu_active_mask, cs_cpus_allowed);

	rcu_पढ़ो_lock_sched();
	dl_b = dl_bw_of(dest_cpu);
	raw_spin_lock_irqsave(&dl_b->lock, flags);
	cap = dl_bw_capacity(dest_cpu);
	overflow = __dl_overflow(dl_b, cap, 0, p->dl.dl_bw);
	अगर (overflow) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		/*
		 * We reserve space क्रम this task in the destination
		 * root_करोमुख्य, as we can't fail after this poपूर्णांक.
		 * We will मुक्त resources in the source root_करोमुख्य
		 * later on (see set_cpus_allowed_dl()).
		 */
		पूर्णांक cpus = dl_bw_cpus(dest_cpu);

		__dl_add(dl_b, p->dl.dl_bw, cpus);
		ret = 0;
	पूर्ण
	raw_spin_unlock_irqrestore(&dl_b->lock, flags);
	rcu_पढ़ो_unlock_sched();

	वापस ret;
पूर्ण

पूर्णांक dl_cpuset_cpumask_can_shrink(स्थिर काष्ठा cpumask *cur,
				 स्थिर काष्ठा cpumask *trial)
अणु
	पूर्णांक ret = 1, trial_cpus;
	काष्ठा dl_bw *cur_dl_b;
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock_sched();
	cur_dl_b = dl_bw_of(cpumask_any(cur));
	trial_cpus = cpumask_weight(trial);

	raw_spin_lock_irqsave(&cur_dl_b->lock, flags);
	अगर (cur_dl_b->bw != -1 &&
	    cur_dl_b->bw * trial_cpus < cur_dl_b->total_bw)
		ret = 0;
	raw_spin_unlock_irqrestore(&cur_dl_b->lock, flags);
	rcu_पढ़ो_unlock_sched();

	वापस ret;
पूर्ण

bool dl_cpu_busy(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags, cap;
	काष्ठा dl_bw *dl_b;
	bool overflow;

	rcu_पढ़ो_lock_sched();
	dl_b = dl_bw_of(cpu);
	raw_spin_lock_irqsave(&dl_b->lock, flags);
	cap = dl_bw_capacity(cpu);
	overflow = __dl_overflow(dl_b, cap, 0, 0);
	raw_spin_unlock_irqrestore(&dl_b->lock, flags);
	rcu_पढ़ो_unlock_sched();

	वापस overflow;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHED_DEBUG
व्योम prपूर्णांक_dl_stats(काष्ठा seq_file *m, पूर्णांक cpu)
अणु
	prपूर्णांक_dl_rq(m, cpu, &cpu_rq(cpu)->dl);
पूर्ण
#पूर्ण_अगर /* CONFIG_SCHED_DEBUG */
