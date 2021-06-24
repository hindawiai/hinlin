<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dynamic byte queue limits.  See include/linux/dynamic_queue_सीमा.स
 *
 * Copyright (c) 2011, Tom Herbert <therbert@google.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/dynamic_queue_सीमा.स>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>

#घोषणा POSDIFF(A, B) ((पूर्णांक)((A) - (B)) > 0 ? (A) - (B) : 0)
#घोषणा AFTER_EQ(A, B) ((पूर्णांक)((A) - (B)) >= 0)

/* Records completed count and recalculates the queue limit */
व्योम dql_completed(काष्ठा dql *dql, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक inprogress, prev_inprogress, limit;
	अचिन्हित पूर्णांक ovlimit, completed, num_queued;
	bool all_prev_completed;

	num_queued = READ_ONCE(dql->num_queued);

	/* Can't complete more than what's in queue */
	BUG_ON(count > num_queued - dql->num_completed);

	completed = dql->num_completed + count;
	limit = dql->limit;
	ovlimit = POSDIFF(num_queued - dql->num_completed, limit);
	inprogress = num_queued - completed;
	prev_inprogress = dql->prev_num_queued - dql->num_completed;
	all_prev_completed = AFTER_EQ(completed, dql->prev_num_queued);

	अगर ((ovlimit && !inprogress) ||
	    (dql->prev_ovlimit && all_prev_completed)) अणु
		/*
		 * Queue considered starved अगर:
		 *   - The queue was over-limit in the last पूर्णांकerval,
		 *     and there is no more data in the queue.
		 *  OR
		 *   - The queue was over-limit in the previous पूर्णांकerval and
		 *     when enqueuing it was possible that all queued data
		 *     had been consumed.  This covers the हाल when queue
		 *     may have becomes starved between completion processing
		 *     running and next समय enqueue was scheduled.
		 *
		 *     When queue is starved increase the limit by the amount
		 *     of bytes both sent and completed in the last पूर्णांकerval,
		 *     plus any previous over-limit.
		 */
		limit += POSDIFF(completed, dql->prev_num_queued) +
		     dql->prev_ovlimit;
		dql->slack_start_समय = jअगरfies;
		dql->lowest_slack = अच_पूर्णांक_उच्च;
	पूर्ण अन्यथा अगर (inprogress && prev_inprogress && !all_prev_completed) अणु
		/*
		 * Queue was not starved, check अगर the limit can be decreased.
		 * A decrease is only considered अगर the queue has been busy in
		 * the whole पूर्णांकerval (the check above).
		 *
		 * If there is slack, the amount of excess data queued above
		 * the amount needed to prevent starvation, the queue limit
		 * can be decreased.  To aव्योम hysteresis we consider the
		 * minimum amount of slack found over several iterations of the
		 * completion routine.
		 */
		अचिन्हित पूर्णांक slack, slack_last_objs;

		/*
		 * Slack is the maximum of
		 *   - The queue limit plus previous over-limit minus twice
		 *     the number of objects completed.  Note that two बार
		 *     number of completed bytes is a basis क्रम an upper bound
		 *     of the limit.
		 *   - Portion of objects in the last queuing operation that
		 *     was not part of non-zero previous over-limit.  That is
		 *     "round down" by non-overlimit portion of the last
		 *     queueing operation.
		 */
		slack = POSDIFF(limit + dql->prev_ovlimit,
		    2 * (completed - dql->num_completed));
		slack_last_objs = dql->prev_ovlimit ?
		    POSDIFF(dql->prev_last_obj_cnt, dql->prev_ovlimit) : 0;

		slack = max(slack, slack_last_objs);

		अगर (slack < dql->lowest_slack)
			dql->lowest_slack = slack;

		अगर (समय_after(jअगरfies,
			       dql->slack_start_समय + dql->slack_hold_समय)) अणु
			limit = POSDIFF(limit, dql->lowest_slack);
			dql->slack_start_समय = jअगरfies;
			dql->lowest_slack = अच_पूर्णांक_उच्च;
		पूर्ण
	पूर्ण

	/* Enक्रमce bounds on limit */
	limit = clamp(limit, dql->min_limit, dql->max_limit);

	अगर (limit != dql->limit) अणु
		dql->limit = limit;
		ovlimit = 0;
	पूर्ण

	dql->adj_limit = limit + completed;
	dql->prev_ovlimit = ovlimit;
	dql->prev_last_obj_cnt = dql->last_obj_cnt;
	dql->num_completed = completed;
	dql->prev_num_queued = num_queued;
पूर्ण
EXPORT_SYMBOL(dql_completed);

व्योम dql_reset(काष्ठा dql *dql)
अणु
	/* Reset all dynamic values */
	dql->limit = 0;
	dql->num_queued = 0;
	dql->num_completed = 0;
	dql->last_obj_cnt = 0;
	dql->prev_num_queued = 0;
	dql->prev_last_obj_cnt = 0;
	dql->prev_ovlimit = 0;
	dql->lowest_slack = अच_पूर्णांक_उच्च;
	dql->slack_start_समय = jअगरfies;
पूर्ण
EXPORT_SYMBOL(dql_reset);

व्योम dql_init(काष्ठा dql *dql, अचिन्हित पूर्णांक hold_समय)
अणु
	dql->max_limit = DQL_MAX_LIMIT;
	dql->min_limit = 0;
	dql->slack_hold_समय = hold_समय;
	dql_reset(dql);
पूर्ण
EXPORT_SYMBOL(dql_init);
