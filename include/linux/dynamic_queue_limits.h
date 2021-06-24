<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Dynamic queue limits (dql) - Definitions
 *
 * Copyright (c) 2011, Tom Herbert <therbert@google.com>
 *
 * This header file contains the definitions क्रम dynamic queue limits (dql).
 * dql would be used in conjunction with a producer/consumer type queue
 * (possibly a HW queue).  Such a queue would have these general properties:
 *
 *   1) Objects are queued up to some limit specअगरied as number of objects.
 *   2) Periodically a completion process executes which retires consumed
 *      objects.
 *   3) Starvation occurs when limit has been reached, all queued data has
 *      actually been consumed, but completion processing has not yet run
 *      so queuing new data is blocked.
 *   4) Minimizing the amount of queued data is desirable.
 *
 * The goal of dql is to calculate the limit as the minimum number of objects
 * needed to prevent starvation.
 *
 * The primary functions of dql are:
 *    dql_queued - called when objects are enqueued to record number of objects
 *    dql_avail - वापसs how many objects are available to be queued based
 *      on the object limit and how many objects are alपढ़ोy enqueued
 *    dql_completed - called at completion समय to indicate how many objects
 *      were retired from the queue
 *
 * The dql implementation करोes not implement any locking क्रम the dql data
 * काष्ठाures, the higher layer should provide this.  dql_queued should
 * be serialized to prevent concurrent execution of the function; this
 * is also true क्रम  dql_completed.  However, dql_queued and dlq_completed  can
 * be executed concurrently (i.e. they can be रक्षित by dअगरferent locks).
 */

#अगर_अघोषित _LINUX_DQL_H
#घोषणा _LINUX_DQL_H

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/bug.h>

काष्ठा dql अणु
	/* Fields accessed in enqueue path (dql_queued) */
	अचिन्हित पूर्णांक	num_queued;		/* Total ever queued */
	अचिन्हित पूर्णांक	adj_limit;		/* limit + num_completed */
	अचिन्हित पूर्णांक	last_obj_cnt;		/* Count at last queuing */

	/* Fields accessed only by completion path (dql_completed) */

	अचिन्हित पूर्णांक	limit ____cacheline_aligned_in_smp; /* Current limit */
	अचिन्हित पूर्णांक	num_completed;		/* Total ever completed */

	अचिन्हित पूर्णांक	prev_ovlimit;		/* Previous over limit */
	अचिन्हित पूर्णांक	prev_num_queued;	/* Previous queue total */
	अचिन्हित पूर्णांक	prev_last_obj_cnt;	/* Previous queuing cnt */

	अचिन्हित पूर्णांक	lowest_slack;		/* Lowest slack found */
	अचिन्हित दीर्घ	slack_start_समय;	/* Time slacks seen */

	/* Configuration */
	अचिन्हित पूर्णांक	max_limit;		/* Max limit */
	अचिन्हित पूर्णांक	min_limit;		/* Minimum limit */
	अचिन्हित पूर्णांक	slack_hold_समय;	/* Time to measure slack */
पूर्ण;

/* Set some अटल maximums */
#घोषणा DQL_MAX_OBJECT (अच_पूर्णांक_उच्च / 16)
#घोषणा DQL_MAX_LIMIT ((अच_पूर्णांक_उच्च / 2) - DQL_MAX_OBJECT)

/*
 * Record number of objects queued. Assumes that caller has alपढ़ोy checked
 * availability in the queue with dql_avail.
 */
अटल अंतरभूत व्योम dql_queued(काष्ठा dql *dql, अचिन्हित पूर्णांक count)
अणु
	BUG_ON(count > DQL_MAX_OBJECT);

	dql->last_obj_cnt = count;

	/* We want to क्रमce a ग_लिखो first, so that cpu करो not attempt
	 * to get cache line containing last_obj_cnt, num_queued, adj_limit
	 * in Shared state, but directly करोes a Request For Ownership
	 * It is only a hपूर्णांक, we use barrier() only.
	 */
	barrier();

	dql->num_queued += count;
पूर्ण

/* Returns how many objects can be queued, < 0 indicates over limit. */
अटल अंतरभूत पूर्णांक dql_avail(स्थिर काष्ठा dql *dql)
अणु
	वापस READ_ONCE(dql->adj_limit) - READ_ONCE(dql->num_queued);
पूर्ण

/* Record number of completed objects and recalculate the limit. */
व्योम dql_completed(काष्ठा dql *dql, अचिन्हित पूर्णांक count);

/* Reset dql state */
व्योम dql_reset(काष्ठा dql *dql);

/* Initialize dql state */
व्योम dql_init(काष्ठा dql *dql, अचिन्हित पूर्णांक hold_समय);

#पूर्ण_अगर /* _KERNEL_ */

#पूर्ण_अगर /* _LINUX_DQL_H */
