<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_sysctl.h"
#समावेश "xfs_pwork.h"
#समावेश <linux/nmi.h>

/*
 * Parallel Work Queue
 * ===================
 *
 * Abstract away the details of running a large and "obviously" parallelizable
 * task across multiple CPUs.  Callers initialize the pwork control object with
 * a desired level of parallelization and a work function.  Next, they embed
 * काष्ठा xfs_pwork in whatever काष्ठाure they use to pass work context to a
 * worker thपढ़ो and queue that pwork.  The work function will be passed the
 * pwork item when it is run (from process context) and any वापसed error will
 * be recorded in xfs_pwork_ctl.error.  Work functions should check क्रम errors
 * and पात अगर necessary; the non-zeroness of xfs_pwork_ctl.error करोes not
 * stop workqueue item processing.
 *
 * This is the rough equivalent of the xfsprogs workqueue code, though we can't
 * reuse that name here.
 */

/* Invoke our caller's function. */
अटल व्योम
xfs_pwork_work(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_pwork	*pwork;
	काष्ठा xfs_pwork_ctl	*pctl;
	पूर्णांक			error;

	pwork = container_of(work, काष्ठा xfs_pwork, work);
	pctl = pwork->pctl;
	error = pctl->work_fn(pctl->mp, pwork);
	अगर (error && !pctl->error)
		pctl->error = error;
	अगर (atomic_dec_and_test(&pctl->nr_work))
		wake_up(&pctl->poll_रुको);
पूर्ण

/*
 * Set up control data क्रम parallel work.  @work_fn is the function that will
 * be called.  @tag will be written पूर्णांकo the kernel thपढ़ोs.  @nr_thपढ़ोs is
 * the level of parallelism desired, or 0 क्रम no limit.
 */
पूर्णांक
xfs_pwork_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_pwork_ctl	*pctl,
	xfs_pwork_work_fn	work_fn,
	स्थिर अक्षर		*tag)
अणु
	अचिन्हित पूर्णांक		nr_thपढ़ोs = 0;

#अगर_घोषित DEBUG
	अगर (xfs_globals.pwork_thपढ़ोs >= 0)
		nr_thपढ़ोs = xfs_globals.pwork_thपढ़ोs;
#पूर्ण_अगर
	trace_xfs_pwork_init(mp, nr_thपढ़ोs, current->pid);

	pctl->wq = alloc_workqueue("%s-%d",
			WQ_UNBOUND | WQ_SYSFS | WQ_FREEZABLE, nr_thपढ़ोs, tag,
			current->pid);
	अगर (!pctl->wq)
		वापस -ENOMEM;
	pctl->work_fn = work_fn;
	pctl->error = 0;
	pctl->mp = mp;
	atomic_set(&pctl->nr_work, 0);
	init_रुकोqueue_head(&pctl->poll_रुको);

	वापस 0;
पूर्ण

/* Queue some parallel work. */
व्योम
xfs_pwork_queue(
	काष्ठा xfs_pwork_ctl	*pctl,
	काष्ठा xfs_pwork	*pwork)
अणु
	INIT_WORK(&pwork->work, xfs_pwork_work);
	pwork->pctl = pctl;
	atomic_inc(&pctl->nr_work);
	queue_work(pctl->wq, &pwork->work);
पूर्ण

/* Wait क्रम the work to finish and tear करोwn the control काष्ठाure. */
पूर्णांक
xfs_pwork_destroy(
	काष्ठा xfs_pwork_ctl	*pctl)
अणु
	destroy_workqueue(pctl->wq);
	pctl->wq = शून्य;
	वापस pctl->error;
पूर्ण

/*
 * Wait क्रम the work to finish by polling completion status and touch the soft
 * lockup watchकरोg.  This is क्रम callers such as mount which hold locks.
 */
व्योम
xfs_pwork_poll(
	काष्ठा xfs_pwork_ctl	*pctl)
अणु
	जबतक (रुको_event_समयout(pctl->poll_रुको,
				atomic_पढ़ो(&pctl->nr_work) == 0, HZ) == 0)
		touch_softlockup_watchकरोg();
पूर्ण
