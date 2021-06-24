<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * stop-task scheduling class.
 *
 * The stop task is the highest priority task in the प्रणाली, it preempts
 * everything and will be preempted by nothing.
 *
 * See kernel/stop_machine.c
 */
#समावेश "sched.h"

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक
select_task_rq_stop(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक flags)
अणु
	वापस task_cpu(p); /* stop tasks as never migrate */
पूर्ण

अटल पूर्णांक
balance_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा rq_flags *rf)
अणु
	वापस sched_stop_runnable(rq);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम
check_preempt_curr_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	/* we're never preempted */
पूर्ण

अटल व्योम set_next_task_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *stop, bool first)
अणु
	stop->se.exec_start = rq_घड़ी_प्रकारask(rq);
पूर्ण

अटल काष्ठा task_काष्ठा *pick_next_task_stop(काष्ठा rq *rq)
अणु
	अगर (!sched_stop_runnable(rq))
		वापस शून्य;

	set_next_task_stop(rq, rq->stop, true);
	वापस rq->stop;
पूर्ण

अटल व्योम
enqueue_task_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	add_nr_running(rq, 1);
पूर्ण

अटल व्योम
dequeue_task_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	sub_nr_running(rq, 1);
पूर्ण

अटल व्योम yield_task_stop(काष्ठा rq *rq)
अणु
	BUG(); /* the stop task should never yield, its poपूर्णांकless. */
पूर्ण

अटल व्योम put_prev_task_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev)
अणु
	काष्ठा task_काष्ठा *curr = rq->curr;
	u64 delta_exec;

	delta_exec = rq_घड़ी_प्रकारask(rq) - curr->se.exec_start;
	अगर (unlikely((s64)delta_exec < 0))
		delta_exec = 0;

	schedstat_set(curr->se.statistics.exec_max,
			max(curr->se.statistics.exec_max, delta_exec));

	curr->se.sum_exec_runसमय += delta_exec;
	account_group_exec_runसमय(curr, delta_exec);

	curr->se.exec_start = rq_घड़ी_प्रकारask(rq);
	cgroup_account_cpuसमय(curr, delta_exec);
पूर्ण

/*
 * scheduler tick hitting a task of our scheduling class.
 *
 * NOTE: This function can be called remotely by the tick offload that
 * goes aदीर्घ full dynticks. Thereक्रमe no local assumption can be made
 * and everything must be accessed through the @rq and @curr passed in
 * parameters.
 */
अटल व्योम task_tick_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *curr, पूर्णांक queued)
अणु
पूर्ण

अटल व्योम चयनed_to_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	BUG(); /* its impossible to change to this class */
पूर्ण

अटल व्योम
prio_changed_stop(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक oldprio)
अणु
	BUG(); /* how!?, what priority? */
पूर्ण

अटल व्योम update_curr_stop(काष्ठा rq *rq)
अणु
पूर्ण

/*
 * Simple, special scheduling class क्रम the per-CPU stop tasks:
 */
DEFINE_SCHED_CLASS(stop) = अणु

	.enqueue_task		= enqueue_task_stop,
	.dequeue_task		= dequeue_task_stop,
	.yield_task		= yield_task_stop,

	.check_preempt_curr	= check_preempt_curr_stop,

	.pick_next_task		= pick_next_task_stop,
	.put_prev_task		= put_prev_task_stop,
	.set_next_task          = set_next_task_stop,

#अगर_घोषित CONFIG_SMP
	.balance		= balance_stop,
	.select_task_rq		= select_task_rq_stop,
	.set_cpus_allowed	= set_cpus_allowed_common,
#पूर्ण_अगर

	.task_tick		= task_tick_stop,

	.prio_changed		= prio_changed_stop,
	.चयनed_to		= चयनed_to_stop,
	.update_curr		= update_curr_stop,
पूर्ण;
